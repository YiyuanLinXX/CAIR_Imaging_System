/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *portLabel;
    QLineEdit *readPort;
    QLabel *baudLabel;
    QLineEdit *readBaud;
    QLineEdit *debugOutput;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QPushButton *gps_pushBtn;
    QLabel *latLabel;
    QLCDNumber *LcdLatitude;
    QLabel *longLabel;
    QLCDNumber *LcdLongitude;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *start_recording;
    QLineEdit *folderName;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(503, 338);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 130, 185, 89));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        portLabel = new QLabel(layoutWidget);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));

        gridLayout->addWidget(portLabel, 0, 0, 1, 1);

        readPort = new QLineEdit(layoutWidget);
        readPort->setObjectName(QString::fromUtf8("readPort"));

        gridLayout->addWidget(readPort, 0, 1, 1, 1);

        baudLabel = new QLabel(layoutWidget);
        baudLabel->setObjectName(QString::fromUtf8("baudLabel"));

        gridLayout->addWidget(baudLabel, 1, 0, 1, 1);

        readBaud = new QLineEdit(layoutWidget);
        readBaud->setObjectName(QString::fromUtf8("readBaud"));

        gridLayout->addWidget(readBaud, 1, 1, 1, 1);

        debugOutput = new QLineEdit(layoutWidget);
        debugOutput->setObjectName(QString::fromUtf8("debugOutput"));

        gridLayout->addWidget(debugOutput, 2, 0, 1, 2);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 51, 327, 54));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gps_pushBtn = new QPushButton(layoutWidget1);
        gps_pushBtn->setObjectName(QString::fromUtf8("gps_pushBtn"));

        gridLayout_2->addWidget(gps_pushBtn, 0, 0, 2, 1);

        latLabel = new QLabel(layoutWidget1);
        latLabel->setObjectName(QString::fromUtf8("latLabel"));
        latLabel->setLayoutDirection(Qt::LeftToRight);
        latLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(latLabel, 0, 1, 1, 1);

        LcdLatitude = new QLCDNumber(layoutWidget1);
        LcdLatitude->setObjectName(QString::fromUtf8("LcdLatitude"));
        LcdLatitude->setDigitCount(16);

        gridLayout_2->addWidget(LcdLatitude, 0, 2, 1, 1);

        longLabel = new QLabel(layoutWidget1);
        longLabel->setObjectName(QString::fromUtf8("longLabel"));
        longLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(longLabel, 1, 1, 1, 1);

        LcdLongitude = new QLCDNumber(layoutWidget1);
        LcdLongitude->setObjectName(QString::fromUtf8("LcdLongitude"));
        LcdLongitude->setDigitCount(16);

        gridLayout_2->addWidget(LcdLongitude, 1, 2, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 240, 237, 27));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        start_recording = new QPushButton(widget);
        start_recording->setObjectName(QString::fromUtf8("start_recording"));

        horizontalLayout->addWidget(start_recording);

        folderName = new QLineEdit(widget);
        folderName->setObjectName(QString::fromUtf8("folderName"));

        horizontalLayout->addWidget(folderName);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 503, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        portLabel->setText(QApplication::translate("MainWindow", "Port", nullptr));
        baudLabel->setText(QApplication::translate("MainWindow", "Baud", nullptr));
        gps_pushBtn->setText(QApplication::translate("MainWindow", "Start GPS", nullptr));
        latLabel->setText(QApplication::translate("MainWindow", "Latitude", nullptr));
        longLabel->setText(QApplication::translate("MainWindow", "Longitude", nullptr));
        start_recording->setText(QApplication::translate("MainWindow", "Record GPS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
