#ifndef HELLO_GUI_H
#define HELLO_GUI_H

#include <QWidget>
#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>

namespace Ui {
class HelloGui;
}

class HelloGui : public QWidget
{
  Q_OBJECT

public:
  explicit HelloGui(QWidget *parent = nullptr);
  ~HelloGui();
  void chatterCallback(const std_msgs::String::ConstPtr& msg);

public slots:
  void spinOnce();

private slots:
  void on_hi_button_clicked();

private:
  Ui::HelloGui *ui;
  QTimer *ros_timer;

  ros::NodeHandlePtr nh_;
  ros::Subscriber chatter_sub_;
  ros::Publisher  hello_pub_;
};

#endif // HELLO_GUI_H
