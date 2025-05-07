#pragma once

#include <QWidget>
#include <QCheckBox>
#include "qcustomplot.h"

namespace Ui {
class CombinedGraphs;
}

class CombinedGraphs : public QWidget
{
    Q_OBJECT

public:
    explicit CombinedGraphs(QWidget *parent = nullptr);
    ~CombinedGraphs();

    void updateGraph(double afr, double rpm, double temp, double tps, double map, double timestamp);

private slots:
    void onCheckBoxToggled();
    void onCombinedGraphClicked(QMouseEvent *event);

private:
    Ui::CombinedGraphs *ui;
    
    void setupGraph();
    void updateLegend();
};
