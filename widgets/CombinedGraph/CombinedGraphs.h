#ifndef COMBINEDGRAPHS_H
#define COMBINEDGRAPHS_H

#include <QWidget>
#include <QMouseEvent>

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
    void onCombinedGraphClicked(QMouseEvent *event);
    void onCheckBoxToggled();

private:
    Ui::CombinedGraphs *ui;
    void setupGraph();
    void setupDarkTheme();
    void updateLegend();
};

#endif // COMBINEDGRAPHS_H
