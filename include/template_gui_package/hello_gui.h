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

#ifndef HELLO_GUI_H
#define HELLO_GUI_H

#include <QWidget>
#include <rclcpp/rclcpp.hpp>
#include <qtimer.h>
#include <std_msgs/msg/string.hpp>

namespace Ui {
class HelloGui;
}

class HelloGui : public QWidget
{
  Q_OBJECT

public:
  explicit HelloGui(QWidget *parent = nullptr);
  ~HelloGui();
  void chatterCallback(const std_msgs::msg::String::SharedPtr msg);

  rclcpp::Node::SharedPtr node_;
public slots:
  void spinOnce();

private slots:
  void on_hi_button_clicked();

private:
  Ui::HelloGui *ui;
  rclcpp::Executor::SharedPtr exec_;
  QTimer *ros_timer;

  //ros::NodeHandlePtr nh_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr chatter_sub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr  hello_pub_;
};

#endif // HELLO_GUI_H
