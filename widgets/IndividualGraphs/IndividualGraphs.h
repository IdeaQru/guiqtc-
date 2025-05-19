#ifndef INDIVIDUALGRAPHS_H
#define INDIVIDUALGRAPHS_H

#include <QWidget>
#include <QMouseEvent>
#include <QToolTip>
#include "qcustomplot.h"

namespace Ui {
class IndividualGraphs;
}

class IndividualGraphs : public QWidget
{
    Q_OBJECT

public:
    explicit IndividualGraphs(QWidget *parent = nullptr);
    ~IndividualGraphs();
    void updateGraphs(double afr, double rpm, double temp, double tps, double map, double timestamp);

private slots:
    void onGraphClicked(QMouseEvent *event);

private:
    Ui::IndividualGraphs *ui;
    void setupGraphs();
    void setupGraph(QCustomPlot *plot, const QString &title, const QColor &color);
    void setupDarkTheme();
    void addCurrentValueLabel(QCustomPlot *plot, const QString &name, const QColor &color);
    void updateValueLabel(QCustomPlot *plot, double value);
};

#endif // INDIVIDUALGRAPHS_H
