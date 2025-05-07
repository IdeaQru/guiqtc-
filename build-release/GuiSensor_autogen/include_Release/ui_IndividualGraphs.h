/********************************************************************************
** Form generated from reading UI file 'IndividualGraphs.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDIVIDUALGRAPHS_H
#define UI_INDIVIDUALGRAPHS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_IndividualGraphs
{
public:
    QVBoxLayout *verticalLayout;
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

    void setupUi(QWidget *IndividualGraphs)
    {
        if (IndividualGraphs->objectName().isEmpty())
            IndividualGraphs->setObjectName(QString::fromUtf8("IndividualGraphs"));
        verticalLayout = new QVBoxLayout(IndividualGraphs);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plotTabs = new QTabWidget(IndividualGraphs);
        plotTabs->setObjectName(QString::fromUtf8("plotTabs"));
        tabAFR = new QWidget();
        tabAFR->setObjectName(QString::fromUtf8("tabAFR"));
        verticalLayout_2 = new QVBoxLayout(tabAFR);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        plotAFR = new QCustomPlot(tabAFR);
        plotAFR->setObjectName(QString::fromUtf8("plotAFR"));
        plotAFR->setMinimumSize(QSize(0, 300));

        verticalLayout_2->addWidget(plotAFR);

        plotTabs->addTab(tabAFR, QString());
        tabRPM = new QWidget();
        tabRPM->setObjectName(QString::fromUtf8("tabRPM"));
        verticalLayout_3 = new QVBoxLayout(tabRPM);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        plotRPM = new QCustomPlot(tabRPM);
        plotRPM->setObjectName(QString::fromUtf8("plotRPM"));
        plotRPM->setMinimumSize(QSize(0, 300));

        verticalLayout_3->addWidget(plotRPM);

        plotTabs->addTab(tabRPM, QString());
        tabTemp = new QWidget();
        tabTemp->setObjectName(QString::fromUtf8("tabTemp"));
        verticalLayout_4 = new QVBoxLayout(tabTemp);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        plotTemp = new QCustomPlot(tabTemp);
        plotTemp->setObjectName(QString::fromUtf8("plotTemp"));
        plotTemp->setMinimumSize(QSize(0, 300));

        verticalLayout_4->addWidget(plotTemp);

        plotTabs->addTab(tabTemp, QString());
        tabTPS = new QWidget();
        tabTPS->setObjectName(QString::fromUtf8("tabTPS"));
        verticalLayout_5 = new QVBoxLayout(tabTPS);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        plotTPS = new QCustomPlot(tabTPS);
        plotTPS->setObjectName(QString::fromUtf8("plotTPS"));
        plotTPS->setMinimumSize(QSize(0, 300));

        verticalLayout_5->addWidget(plotTPS);

        plotTabs->addTab(tabTPS, QString());
        tabMAP = new QWidget();
        tabMAP->setObjectName(QString::fromUtf8("tabMAP"));
        verticalLayout_6 = new QVBoxLayout(tabMAP);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        plotMAP = new QCustomPlot(tabMAP);
        plotMAP->setObjectName(QString::fromUtf8("plotMAP"));
        plotMAP->setMinimumSize(QSize(0, 300));

        verticalLayout_6->addWidget(plotMAP);

        plotTabs->addTab(tabMAP, QString());

        verticalLayout->addWidget(plotTabs);


        retranslateUi(IndividualGraphs);

        plotTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(IndividualGraphs);
    } // setupUi

    void retranslateUi(QWidget *IndividualGraphs)
    {
        plotTabs->setTabText(plotTabs->indexOf(tabAFR), QCoreApplication::translate("IndividualGraphs", "AFR", nullptr));
        plotTabs->setTabText(plotTabs->indexOf(tabRPM), QCoreApplication::translate("IndividualGraphs", "RPM", nullptr));
        plotTabs->setTabText(plotTabs->indexOf(tabTemp), QCoreApplication::translate("IndividualGraphs", "Temp", nullptr));
        plotTabs->setTabText(plotTabs->indexOf(tabTPS), QCoreApplication::translate("IndividualGraphs", "TPS", nullptr));
        plotTabs->setTabText(plotTabs->indexOf(tabMAP), QCoreApplication::translate("IndividualGraphs", "MAP", nullptr));
        (void)IndividualGraphs;
    } // retranslateUi

};

namespace Ui {
    class IndividualGraphs: public Ui_IndividualGraphs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDIVIDUALGRAPHS_H
