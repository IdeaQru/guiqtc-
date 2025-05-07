#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

#include "widgets/SensorCards/SensorCards.h"
#include "widgets/IndividualGraphs/IndividualGraphs.h"
#include "widgets/CombinedGraph/CombinedGraphs.h"
#include "utils/SerialHandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();
    void onSensorDataReceived(double afr, double rpm, double temp, double tps, double map, double timestamp);

private:
    Ui::MainWindow *ui;
    SensorCards *sensorCards;
    IndividualGraphs *individualGraphs;
    CombinedGraphs *combinedGraphs;
    SerialHandler *serialHandler;

    void setupConnections();
};

#endif // MAINWINDOW_H
