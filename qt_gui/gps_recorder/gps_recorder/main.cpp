#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "qt_gps_gui");
    QApplication a(argc, argv);
    MainWindow w(argc, argv);
    w.show();
    return a.exec();
}
