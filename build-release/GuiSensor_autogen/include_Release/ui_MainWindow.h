/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QTabWidget *mainTabWidget;
    QWidget *tabSensorCards;
    QVBoxLayout *verticalLayout_7;
    QWidget *tabIndividualGraphs;
    QVBoxLayout *verticalLayout_8;
    QWidget *tabCombinedGraphs;
    QVBoxLayout *verticalLayout_9;
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

        mainTabWidget = new QTabWidget(centralWidget);
        mainTabWidget->setObjectName(QString::fromUtf8("mainTabWidget"));
        tabSensorCards = new QWidget();
        tabSensorCards->setObjectName(QString::fromUtf8("tabSensorCards"));
        verticalLayout_7 = new QVBoxLayout(tabSensorCards);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        mainTabWidget->addTab(tabSensorCards, QString());
        tabIndividualGraphs = new QWidget();
        tabIndividualGraphs->setObjectName(QString::fromUtf8("tabIndividualGraphs"));
        verticalLayout_8 = new QVBoxLayout(tabIndividualGraphs);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        mainTabWidget->addTab(tabIndividualGraphs, QString());
        tabCombinedGraphs = new QWidget();
        tabCombinedGraphs->setObjectName(QString::fromUtf8("tabCombinedGraphs"));
        verticalLayout_9 = new QVBoxLayout(tabCombinedGraphs);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        mainTabWidget->addTab(tabCombinedGraphs, QString());

        verticalLayout->addWidget(mainTabWidget);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        mainTabWidget->setCurrentIndex(0);


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
"          }", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        connectButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"              background: #4CAF50;\n"
"              color: white;\n"
"              border-radius: 5px;\n"
"              padding: 8px;\n"
"          }", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Disconnected", nullptr));
        statusLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "QLabel {\n"
"              color: #ff4444;\n"
"              font-weight: bold;\n"
"          }", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabSensorCards), QCoreApplication::translate("MainWindow", "Sensor Cards", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabIndividualGraphs), QCoreApplication::translate("MainWindow", "Individual Graphs", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabCombinedGraphs), QCoreApplication::translate("MainWindow", "Combined Graph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
