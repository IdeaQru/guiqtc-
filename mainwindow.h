#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPair>
#include <QTabWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "widgets/SensorCards/SensorCards.h"
#include "widgets/IndividualGraphs/IndividualGraphs.h"
#include "widgets/CombinedGraph/CombinedGraphs.h"
#include "utils/SerialHandler.h"
#include "widgets/Maps/maps.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();
     void onSensorDataReceived(double afr, double rpm, double temp, double tps, double map, 
                              double lat, double lng, double speed, double timestamp);
    void drawPolygonFromData(const QByteArray& data);
    void onDrawPolygonClicked();
    void onResetMapClicked();

private:
    Ui::MainWindow *ui;
    SensorCards *sensorCards;
    IndividualGraphs *individualGraphs;
    CombinedGraphs *combinedGraphs;
    SerialHandler *serialHandler;
    Maps *mapsWidget;

    void setupConnections();
    void setupDarkTheme();
    void setupTabIcons();
    void setupMapControls();
};

#endif // MAINWINDOW_H
