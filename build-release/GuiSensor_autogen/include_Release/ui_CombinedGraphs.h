/********************************************************************************
** Form generated from reading UI file 'CombinedGraphs.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBINEDGRAPHS_H
#define UI_COMBINEDGRAPHS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_CombinedGraphs
{
public:
    QVBoxLayout *verticalLayout;
    QCustomPlot *plotCombined;
    QWidget *legendWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkAFR;
    QCheckBox *checkRPM;
    QCheckBox *checkTemp;
    QCheckBox *checkTPS;
    QCheckBox *checkMAP;

    void setupUi(QWidget *CombinedGraphs)
    {
        if (CombinedGraphs->objectName().isEmpty())
            CombinedGraphs->setObjectName(QString::fromUtf8("CombinedGraphs"));
        verticalLayout = new QVBoxLayout(CombinedGraphs);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plotCombined = new QCustomPlot(CombinedGraphs);
        plotCombined->setObjectName(QString::fromUtf8("plotCombined"));
        plotCombined->setMinimumSize(QSize(0, 400));

        verticalLayout->addWidget(plotCombined);

        legendWidget = new QWidget(CombinedGraphs);
        legendWidget->setObjectName(QString::fromUtf8("legendWidget"));
        horizontalLayout = new QHBoxLayout(legendWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkAFR = new QCheckBox(legendWidget);
        checkAFR->setObjectName(QString::fromUtf8("checkAFR"));
        checkAFR->setChecked(true);

        horizontalLayout->addWidget(checkAFR);

        checkRPM = new QCheckBox(legendWidget);
        checkRPM->setObjectName(QString::fromUtf8("checkRPM"));
        checkRPM->setChecked(true);

        horizontalLayout->addWidget(checkRPM);

        checkTemp = new QCheckBox(legendWidget);
        checkTemp->setObjectName(QString::fromUtf8("checkTemp"));
        checkTemp->setChecked(true);

        horizontalLayout->addWidget(checkTemp);

        checkTPS = new QCheckBox(legendWidget);
        checkTPS->setObjectName(QString::fromUtf8("checkTPS"));
        checkTPS->setChecked(true);

        horizontalLayout->addWidget(checkTPS);

        checkMAP = new QCheckBox(legendWidget);
        checkMAP->setObjectName(QString::fromUtf8("checkMAP"));
        checkMAP->setChecked(true);

        horizontalLayout->addWidget(checkMAP);


        verticalLayout->addWidget(legendWidget);


        retranslateUi(CombinedGraphs);

        QMetaObject::connectSlotsByName(CombinedGraphs);
    } // setupUi

    void retranslateUi(QWidget *CombinedGraphs)
    {
        checkAFR->setText(QCoreApplication::translate("CombinedGraphs", "AFR", nullptr));
        checkAFR->setStyleSheet(QCoreApplication::translate("CombinedGraphs", "QCheckBox {\n"
"             color: #2196F3;\n"
"             font-weight: bold;\n"
"         }", nullptr));
        checkRPM->setText(QCoreApplication::translate("CombinedGraphs", "RPM", nullptr));
        checkRPM->setStyleSheet(QCoreApplication::translate("CombinedGraphs", "QCheckBox {\n"
"             color: #ff4444;\n"
"             font-weight: bold;\n"
"         }", nullptr));
        checkTemp->setText(QCoreApplication::translate("CombinedGraphs", "Temp", nullptr));
        checkTemp->setStyleSheet(QCoreApplication::translate("CombinedGraphs", "QCheckBox {\n"
"             color: #FFD700;\n"
"             font-weight: bold;\n"
"         }", nullptr));
        checkTPS->setText(QCoreApplication::translate("CombinedGraphs", "TPS", nullptr));
        checkTPS->setStyleSheet(QCoreApplication::translate("CombinedGraphs", "QCheckBox {\n"
"             color: #00FF88;\n"
"             font-weight: bold;\n"
"         }", nullptr));
        checkMAP->setText(QCoreApplication::translate("CombinedGraphs", "MAP", nullptr));
        checkMAP->setStyleSheet(QCoreApplication::translate("CombinedGraphs", "QCheckBox {\n"
"             color: #FFA500;\n"
"             font-weight: bold;\n"
"         }", nullptr));
        (void)CombinedGraphs;
    } // retranslateUi

};

namespace Ui {
    class CombinedGraphs: public Ui_CombinedGraphs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBINEDGRAPHS_H
