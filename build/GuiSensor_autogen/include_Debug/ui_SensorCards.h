/********************************************************************************
** Form generated from reading UI file 'SensorCards.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORCARDS_H
#define UI_SENSORCARDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SensorCards
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *sensorPanel;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *afrLabel;
    QLabel *rpmLabel;
    QLabel *tempLabel;
    QLabel *tpsLabel;
    QLabel *mapLabel;

    void setupUi(QWidget *SensorCards)
    {
        if (SensorCards->objectName().isEmpty())
            SensorCards->setObjectName("SensorCards");
        verticalLayout = new QVBoxLayout(SensorCards);
        verticalLayout->setObjectName("verticalLayout");
        sensorPanel = new QScrollArea(SensorCards);
        sensorPanel->setObjectName("sensorPanel");
        sensorPanel->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName("gridLayout");
        afrLabel = new QLabel(scrollAreaWidgetContents);
        afrLabel->setObjectName("afrLabel");

        gridLayout->addWidget(afrLabel, 0, 0, 1, 1);

        rpmLabel = new QLabel(scrollAreaWidgetContents);
        rpmLabel->setObjectName("rpmLabel");

        gridLayout->addWidget(rpmLabel, 0, 1, 1, 1);

        tempLabel = new QLabel(scrollAreaWidgetContents);
        tempLabel->setObjectName("tempLabel");

        gridLayout->addWidget(tempLabel, 1, 0, 1, 1);

        tpsLabel = new QLabel(scrollAreaWidgetContents);
        tpsLabel->setObjectName("tpsLabel");

        gridLayout->addWidget(tpsLabel, 1, 1, 1, 1);

        mapLabel = new QLabel(scrollAreaWidgetContents);
        mapLabel->setObjectName("mapLabel");

        gridLayout->addWidget(mapLabel, 2, 0, 1, 1);

        sensorPanel->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(sensorPanel);


        retranslateUi(SensorCards);

        QMetaObject::connectSlotsByName(SensorCards);
    } // setupUi

    void retranslateUi(QWidget *SensorCards)
    {
        afrLabel->setText(QCoreApplication::translate("SensorCards", "AFR: --", nullptr));
        afrLabel->setStyleSheet(QCoreApplication::translate("SensorCards", "QLabel {\n"
"              color: #2196F3;\n"
"              background: #1a1a1a;\n"
"              border-radius: 10px;\n"
"              padding: 10px;\n"
"              font-size: 12pt;\n"
"              font-weight: bold;\n"
"          }", nullptr));
        rpmLabel->setText(QCoreApplication::translate("SensorCards", "RPM: --", nullptr));
        rpmLabel->setStyleSheet(QCoreApplication::translate("SensorCards", "QLabel {\n"
"              color: #ff4444;\n"
"              background: #1a1a1a;\n"
"              border-radius: 10px;\n"
"              padding: 10px;\n"
"              font-size: 12pt;\n"
"              font-weight: bold;\n"
"          }", nullptr));
        tempLabel->setText(QCoreApplication::translate("SensorCards", "Temp: --", nullptr));
        tempLabel->setStyleSheet(QCoreApplication::translate("SensorCards", "QLabel {\n"
"              color: #FFD700;\n"
"              background: #1a1a1a;\n"
"              border-radius: 10px;\n"
"              padding: 10px;\n"
"              font-size: 12pt;\n"
"              font-weight: bold;\n"
"          }", nullptr));
        tpsLabel->setText(QCoreApplication::translate("SensorCards", "TPS: --", nullptr));
        tpsLabel->setStyleSheet(QCoreApplication::translate("SensorCards", "QLabel {\n"
"              color: #00FF88;\n"
"              background: #1a1a1a;\n"
"              border-radius: 10px;\n"
"              padding: 10px;\n"
"              font-size: 12pt;\n"
"              font-weight: bold;\n"
"          }", nullptr));
        mapLabel->setText(QCoreApplication::translate("SensorCards", "MAP: --", nullptr));
        mapLabel->setStyleSheet(QCoreApplication::translate("SensorCards", "QLabel {\n"
"              color: #FFA500;\n"
"              background: #1a1a1a;\n"
"              border-radius: 10px;\n"
"              padding: 10px;\n"
"              font-size: 12pt;\n"
"              font-weight: bold;\n"
"          }", nullptr));
        (void)SensorCards;
    } // retranslateUi

};

namespace Ui {
    class SensorCards: public Ui_SensorCards {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORCARDS_H
