/********************************************************************************
** Form generated from reading UI file 'IndividualGraphs.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDIVIDUALGRAPHS_H
#define UI_INDIVIDUALGRAPHS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_IndividualGraphs
{
public:
    QVBoxLayout *verticalLayout;
    QCustomPlot *plotAFR;
    QCustomPlot *plotRPM;
    QCustomPlot *plotTemp;
    QCustomPlot *plotTPS;
    QCustomPlot *plotMAP;

    void setupUi(QWidget *IndividualGraphs)
    {
        if (IndividualGraphs->objectName().isEmpty())
            IndividualGraphs->setObjectName("IndividualGraphs");
        IndividualGraphs->resize(600, 600);
        verticalLayout = new QVBoxLayout(IndividualGraphs);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        plotAFR = new QCustomPlot(IndividualGraphs);
        plotAFR->setObjectName("plotAFR");
        plotAFR->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(plotAFR);

        plotRPM = new QCustomPlot(IndividualGraphs);
        plotRPM->setObjectName("plotRPM");
        plotRPM->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(plotRPM);

        plotTemp = new QCustomPlot(IndividualGraphs);
        plotTemp->setObjectName("plotTemp");
        plotTemp->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(plotTemp);

        plotTPS = new QCustomPlot(IndividualGraphs);
        plotTPS->setObjectName("plotTPS");
        plotTPS->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(plotTPS);

        plotMAP = new QCustomPlot(IndividualGraphs);
        plotMAP->setObjectName("plotMAP");
        plotMAP->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(plotMAP);


        retranslateUi(IndividualGraphs);

        QMetaObject::connectSlotsByName(IndividualGraphs);
    } // setupUi

    void retranslateUi(QWidget *IndividualGraphs)
    {
        (void)IndividualGraphs;
    } // retranslateUi

};

namespace Ui {
    class IndividualGraphs: public Ui_IndividualGraphs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDIVIDUALGRAPHS_H
