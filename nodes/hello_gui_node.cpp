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

#include <QApplication>
#include <QIcon>
#include <template_gui_package/hello_gui.h>
#include <rclcpp/duration.hpp>

#include "rclcpp/rclcpp.hpp"


using namespace std::chrono_literals;

class QApplicationNode: public rclcpp::Node{
public:
  QApplicationNode(int &argc, char **argv)
    : Node("qapplication_node"),
      app_(argc, argv)
  {
    timer_ = this->create_wall_timer(
          1ms, std::bind(&QApplicationNode::timer_callback, this));
  }
private:
  void timer_callback(){
    app_.processEvents();
  }
  QApplication app_;
  rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto app = std::make_shared<QApplicationNode>(argc,argv);
  auto w   = std::make_shared<HelloGui>();

  rclcpp::executors::SingleThreadedExecutor exec;
  exec.add_node(app);
  exec.add_node(w);
  exec.spin();
}
