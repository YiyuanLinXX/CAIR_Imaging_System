#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int &argc, char **argv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    nh()
{
    ui->setupUi(this);
    ui->folderName->setText("day1");
    ui->start_recording->setText("Start Recording");
    QString settingsFilePath = QDir::homePath() + "/Projects/ros_temp/src/gps_publisher/config/gps_config.txt";
    QFile file(settingsFilePath);
    if (!file.exists()){
        ui->readPort->setText("/dev/ttyS0");
        ui->readBaud->setText("9200");
    } else {
        loadSettings();
    }

    ros::init(argc, argv, "qt_ros_subscriber");
    gpsSub = nh.subscribe("/robot/main_gps_fix", 10, &MainWindow::gpsCallback, this);

    startGpsProcess = new QProcess(this);
    startDataRecorderProcess = new QProcess(this);

    // ros spin every 10 ms
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(spinROS()));
    timer->start(10); // Check for ROS topics every 10 ms

    // gps check every 10 ms
    QTimer *timer_sensor_check = new QTimer(this);
    connect(timer_sensor_check, SIGNAL(timeout()), this, SLOT(checkSensorUpdates()));
    timer_sensor_check->start(10);  // Check GPS messages every 500 ms
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::spinROS() {
    ros::spinOnce();
}

void MainWindow::on_gps_pushBtn_clicked()
{
    QString settingsDir = QDir::homePath() + "/Projects/ros_temp/src/gps_publisher/config";
    QString settingsFilePath = settingsDir + "/gps_config.txt";
    QFile file(settingsFilePath);
    if (1==1) {
        QDir dir(settingsDir);
        if (!dir.exists()) {
            dir.mkpath(settingsDir);
        }

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->readPort->text() << "\n";
            out << ui->readBaud->text() << "\n";
            file.close();
        }
    }

    if(startGpsProcess->state() == QProcess::NotRunning){
        QString com_port = ui->readPort->text();
        QString baud = ui->readBaud->text();
        QString command = QString("bash -c \"source /home/cairlab/Projects/ros_temp/devel/setup.bash && roslaunch gps_publisher start_gps.launch com_port:=%1 baud:=%2\"")
                          .arg(com_port)
                          .arg(baud);
        startGpsProcess->start(command);
        ui->gps_pushBtn->setStyleSheet("background-color: green");
        ui->gps_pushBtn->setText("Stop GPS");
    } else {
        startGpsProcess->terminate();
        startGpsProcess->waitForFinished();
        startGpsProcess->kill();
        ui->gps_pushBtn->setStyleSheet("background-color: red");
        ui->gps_pushBtn->setText("Start GPS");
    }
}

void MainWindow::checkSensorUpdates()
{
    ros::Duration d = ros::Time::now() - lastGPSTime;
    if (d.toSec() > 2.0) {
        ui->latLabel->setStyleSheet("QLabel { background-color : red; color : black; }");
        ui->longLabel->setStyleSheet("QLabel { background-color : red; color : black; }");
        ui->debugOutput->setText("!!GPS NOT ready!!");
    } else {
        ui->latLabel->setStyleSheet("QLabel { background-color : green; color : black; }");
        ui->longLabel->setStyleSheet("QLabel { background-color : green; color : black; }");
        ui->debugOutput->setText("GPS READY");
    }

}

void MainWindow::gpsCallback(const sensor_msgs::NavSatFix::ConstPtr &msg) {
    lastGPSTime = ros::Time::now();
    // Display on LCD Number widgets
     ui->LcdLatitude->display(msg->latitude);
     ui->LcdLongitude->display(msg->longitude);
     //Non fix gps fix error
     if (msg->status.status==4 ) {
//         ui->gps_pushBtn->setStyleSheet("QLabel { background-color : red; color : black; }");
         ui->debugOutput->setText("GPS FIXED");
     } else if(msg->status.status==5){
//         ui->gps_pushBtn->setStyleSheet("QLabel { background-color : green; color : black; }");
         ui->debugOutput->setText("GPS FLOAT");
     } else if(msg->status.status==1){
//         ui->gps_pushBtn->setStyleSheet("QLabel { background-color : green; color : black; }");
         ui->debugOutput->setText("GPS SINGLE");
     } else {
//         ui->gps_pushBtn->setStyleSheet("QLabel { background-color : green; color : black; }");
         ui->debugOutput->setText("GPS UNKNOWN");
     } 
}

void MainWindow::loadSettings() {
    QString settingsFilePath = QDir::homePath() + "/Projects/ros_temp/src/gps_publisher/config/gps_config.txt";
    QFile file(settingsFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString port = in.readLine();
        QString baud = in.readLine();
        if (!port.isEmpty()) {
            ui->readPort->setText(port);
        }
        if (!baud.isEmpty()) {
            ui->readBaud->setText(baud);
        }
        file.close();
    } else {
        // Default values
        ui->readPort->setText("/dev/ttyS0");
        ui->readBaud->setText("115200");
    }
}

void MainWindow::on_start_recording_clicked()
{
    if(startDataRecorderProcess->state() == QProcess::NotRunning){
        QString folderName = ui->folderName->text();
        QString command = "bash -c \"source /home/cairlab/Projects/ros_temp/devel/setup.bash && roslaunch gps_recorder gps_recorder.launch folder_:='" + folderName + "/'\"";
        startDataRecorderProcess->start(command);
        ui->start_recording->setStyleSheet("background-color: green");
        ui->start_recording->setText("Stop Recording");
    } else {
        startDataRecorderProcess->terminate();
        startDataRecorderProcess->waitForFinished();
        startDataRecorderProcess->kill();
        ui->start_recording->setStyleSheet("background-color: red");
        ui->start_recording->setText("Start Recording");
    }
}
