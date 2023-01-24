/*
# MIT License

# Copyright (c) 2022 Kristopher Krasnosky

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
*/


#include "hello_gui.h"
#include "ui_hello_gui.h"

HelloGui::HelloGui(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::HelloGui)
  //node_("hello_gui")
{
  ui->setupUi(this);

  using std::placeholders::_1;

  // instantiate the node
  node_ = std::make_shared<rclcpp::Node>("hello_gui");

  // create publisher
  node_->declare_parameter("chatter_topic", "~/chatter");
  std::string listen_topic = node_->get_parameter("chatter_topic").get_parameter_value().get<std::string>();
  hello_pub_ = node_->create_publisher<std_msgs::msg::String>(listen_topic, 10);

  // create subscriber
  node_->declare_parameter("hello_topic", "~/chatter");
  std::string hello_topic = node_->get_parameter("hello_topic").get_parameter_value().get<std::string>();
  chatter_sub_ = node_->create_subscription<std_msgs::msg::String>(
        hello_topic, 1, std::bind(&HelloGui::chatterCallback, this, _1));

  // setup the timer that will signal ros stuff to happen
  ros_timer = new QTimer(this);
  connect(ros_timer, SIGNAL(timeout()), this, SLOT(spinOnce()));
  ros_timer->start(10);  // set the rate to 10ms  You can change this if you want to increase/decrease update rate

  // tell the window to display itself
  this->show();
}

HelloGui::~HelloGui()
{
  delete ui;
  delete ros_timer;
}


void HelloGui::spinOnce(){
  if(rclcpp::ok()){
    rclcpp::spin_some(node_);
  }
  else{
    QApplication::quit();
  }
}


void HelloGui::chatterCallback(const std_msgs::msg::String::SharedPtr msg){
  auto qstring_msg = QString::fromStdString( msg->data.c_str() );

  ui->chatter->setText(qstring_msg);
}

void HelloGui::on_hi_button_clicked()
{
  std_msgs::msg::String msg;
  std::stringstream ss;
  ss << "hello world " << ui->hi_num->value();
  msg.data = ss.str();

  hello_pub_->publish(msg);

  ui->hi_num->setValue(ui->hi_num->value()+1);
}
