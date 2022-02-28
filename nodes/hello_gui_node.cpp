#include <QApplication>
#include "hello_gui.h"


int main(int argc, char *argv[])
{

  ros::init(argc, argv, "hello_gui_node",ros::init_options::AnonymousName);
  QApplication a(argc, argv);

  HelloGui w;
  w.setWindowTitle(QString::fromStdString(
                       ros::this_node::getName()));
  w.show();
  return a.exec();
}
