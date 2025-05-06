/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *controlPanel;
    QHBoxLayout *horizontalLayout;
    QComboBox *portComboBox;
    QPushButton *connectButton;
    QLabel *statusLabel;
    QScrollArea *sensorPanel;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *afrLabel;
    QLabel *rpmLabel;
    QLabel *tempLabel;
    QLabel *tpsLabel;
    QLabel *mapLabel;
    QTabWidget *plotTabs;
    QWidget *tabAFR;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *plotAFR;
    QWidget *tabRPM;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *plotRPM;
    QWidget *tabTemp;
    QVBoxLayout *verticalLayout_4;
    QCustomPlot *plotTemp;
    QWidget *tabTPS;
    QVBoxLayout *verticalLayout_5;
    QCustomPlot *plotTPS;
    QWidget *tabMAP;
    QVBoxLayout *verticalLayout_6;
    QCustomPlot *plotMAP;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        controlPanel = new QWidget(centralWidget);
        controlPanel->setObjectName(QString::fromUtf8("controlPanel"));
        horizontalLayout = new QHBoxLayout(controlPanel);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        portComboBox = new QComboBox(controlPanel);
        portComboBox->setObjectName(QString::fromUtf8("portComboBox"));

        horizontalLayout->addWidget(portComboBox);

        connectButton = new QPushButton(controlPanel);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout->addWidget(connectButton);

        statusLabel = new QLabel(controlPanel);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        horizontalLayout->addWidget(statusLabel);


        verticalLayout->addWidget(controlPanel);

        sensorPanel = new QScrollArea(centralWidget);
        sensorPanel->setObjectName(QString::fromUtf8("sensorPanel"));
        sensorPanel->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        afrLabel = new QLabel(scrollAreaWidgetContents);
        afrLabel->setObjectName(QString::fromUtf8("afrLabel"));

        gridLayout->addWidget(afrLabel, 0, 0, 1, 1);

        rpmLabel = new QLabel(scrollAreaWidgetContents);
        rpmLabel->setObjectName(QString::fromUtf8("rpmLabel"));

        gridLayout->addWidget(rpmLabel, 0, 1, 1, 1);

        tempLabel = new QLabel(scrollAreaWidgetContents);
        tempLabel->setObjectName(QString::fromUtf8("tempLabel"));

        gridLayout->addWidget(tempLabel, 1, 0, 1, 1);

        tpsLabel = new QLabel(scrollAreaWidgetContents);
        tpsLabel->setObjectName(QString::fromUtf8("tpsLabel"));

        gridLayout->addWidget(tpsLabel, 1, 1, 1, 1);

        mapLabel = new QLabel(scrollAreaWidgetContents);
        mapLabel->setObjectName(QString::fromUtf8("mapLabel"));

        gridLayout->addWidget(mapLabel, 2, 0, 1, 1);

        sensorPanel->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(sensorPanel);

        plotTabs = new QTabWidget(centralWidget);
        plotTabs->setObjectName(QString::fromUtf8("plotTabs"));
        tabAFR = new QWidget();
        tabAFR->setObjectName(QString::fromUtf8("tabAFR"));
        verticalLayout_2 = new QVBoxLayout(tabAFR);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        plotAFR = new QCustomPlot(tabAFR);
        plotAFR->setObjectName(QString::fromUtf8("plotAFR"));
        plotAFR->setMinimumSize(QSize(0, 200));

        verticalLayout_2->addWidget(plotAFR);

        plotTabs->addTab(tabAFR, QString());
        tabRPM = new QWidget();
        tabRPM->setObjectName(QString::fromUtf8("tabRPM"));
        verticalLayout_3 = new QVBoxLayout(tabRPM);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        plotRPM = new QCustomPlot(tabRPM);
        plotRPM->setObjectName(QString::fromUtf8("plotRPM"));
        plotRPM->setMinimumSize(QSize(0, 200));

        verticalLayout_3->addWidget(plotRPM);

        plotTabs->addTab(tabRPM, QString());
        tabTemp = new QWidget();
        tabTemp->setObjectName(QString::fromUtf8("tabTemp"));
        verticalLayout_4 = new QVBoxLayout(tabTemp);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        plotTemp = new QCustomPlot(tabTemp);
        plotTemp->setObjectName(QString::fromUtf8("plotTemp"));
        plotTemp->setMinimumSize(QSize(0, 200));

        verticalLayout_4->addWidget(plotTemp);

        plotTabs->addTab(tabTemp, QString());
        tabTPS = new QWidget();
        tabTPS->setObjectName(QString::fromUtf8("tabTPS"));
        verticalLayout_5 = new QVBoxLayout(tabTPS);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        plotTPS = new QCustomPlot(tabTPS);
        plotTPS->setObjectName(QString::fromUtf8("plotTPS"));
        plotTPS->setMinimumSize(QSize(0, 200));

        verticalLayout_5->addWidget(plotTPS);

        plotTabs->addTab(tabTPS, QString());
        tabMAP = new QWidget();
        tabMAP->setObjectName(QString::fromUtf8("tabMAP"));
        verticalLayout_6 = new QVBoxLayout(tabMAP);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        plotMAP = new QCustomPlot(tabMAP);
        plotMAP->setObjectName(QString::fromUtf8("plotMAP"));
        plotMAP->setMinimumSize(QSize(0, 200));

        verticalLayout_6->addWidget(plotMAP);

        plotTabs->addTab(tabMAP, QString());

        verticalLayout->addWidget(plotTabs);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        plotTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Sensor Monitor", nullptr));
        portComboBox->setStyleSheet(QCoreApplication::translate("MainWindow", "QComboBox {\n"
"              background: #2d2d2d;\n"
"              color: #ffffff;\n"
"              border-radius: 5px;\n"
"              border: 1px solid #3d3d3d;\n"
"              padding: 4px;\n"
"          }\n"
"          QComboBox QAbstractItemView {\n"
"              background: #2d2d2d;\n"
"              color: #ffffff;\n"
"          }", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        connectButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"              background: #4CAF50;\n"
"              color: white;\n"
"              border-radius: 5px;\n"
"              padding: 8px;\n"
"          }\n"
"          QPushButton:hover {\n"
"              background: #45a049;\n"
"          }", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Disconnected", nullptr));
        statusLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "QLabel {\n"
"              color: #ff4444;\n"
"              font-weight: bold;\n"
"          }", nullptr));
        afrLabel->setText(QCoreApplication::translate("MainWindow", "AFR: --", nullptr));
        afrLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "QLabel {\n"
"               color: #2196F3;\n"
"               background: #1a1a1a;\n"
"               border-radius: 10px;\n"
"               padding: 10px;\n"
"               font-size: 12pt;\n"
"               font-weight: bold;\n"
"           }", nullptr));
        rpmLabel->setText(QCoreApplication::translate("MainWindow", "RPM: --", nullptr));
        rpmLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "QLabel {\n"
"               color: #ff4444;\n"
"               background: #1a1a1a;\n"
"               border-radius: 10px;\n"
"               padding: 10px;\n"
"               font-size: 12pt;\n"
"               font-weight: bold;\n"
"           }", nullptr));
        tempLabel->setText(QCoreApplication::translate("MainWindow", "Temp: --", nullptr));
        tempLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "QLabel {\n"
"               color: #FFD700;\n"
"               background: #1a1a1a;\n"
"               border-radius: 10px;\n"
"               padding: 10px;\n"
"               font-size: 12pt;\n"
"               font-weight: bold;\n"
"           }", nullptr));
        tpsLabel->setText(QCoreApplication::translate("MainWindow", "TPS: --", nullptr));
        tpsLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "QLabel {\n"
"               color: #00FF88;\n"
"               background: #1a1a1a;\n"
"               border-radius: 10px;\n"
"               padding: 10px;\n"
"               font-size: 12pt;\n"
"               font-weight: bold;\n"
"           }", nullptr));
        mapLabel->setText(QCoreApplication::translate("MainWindow", "MAP: --", nullptr));
        mapLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "QLabel {\n"
"               color: #FFA500;\n"
"               background: #1a1a1a;\n"
"               border-radius: 10px;\n"
"               padding: 10px;\n"
"               font-size: 12pt;\n"
"               font-weight: bold;\n"
"           }", nullptr));
        plotTabs->setTabText(plotTabs->indexOf(tabAFR), QCoreApplication::translate("MainWindow", "AFR", nullptr));
        plotTabs->setTabText(plotTabs->indexOf(tabRPM), QCoreApplication::translate("MainWindow", "RPM", nullptr));
        plotTabs->setTabText(plotTabs->indexOf(tabTemp), QCoreApplication::translate("MainWindow", "Temp", nullptr));
        plotTabs->setTabText(plotTabs->indexOf(tabTPS), QCoreApplication::translate("MainWindow", "TPS", nullptr));
        plotTabs->setTabText(plotTabs->indexOf(tabMAP), QCoreApplication::translate("MainWindow", "MAP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
