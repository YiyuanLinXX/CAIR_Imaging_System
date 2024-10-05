#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <ros/ros.h>
#include<sensor_msgs/NavSatFix.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int &argc, char **argv, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_gps_pushBtn_clicked();
    void spinROS();

private:
    void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &msg);
    void loadSettings();
    Ui::MainWindow *ui;
    QProcess *startGpsProcess;

    ros::NodeHandle nh;
    ros::Subscriber gpsSub;
    QTimer* timer;
    ros::Time lastGPSTime;

public Q_SLOTS:
    void checkSensorUpdates();
};
#endif // MAINWINDOW_H
