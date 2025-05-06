#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QVector>
#include <QDebug>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnectClicked();
    void onSerialDataReceived();
    void updatePlots();
    void parseSerialData(const QString &data);
    void refreshPorts();

private:
    Ui::MainWindow *ui;
    QSerialPort *mSerial;
    QTimer *mUpdateTimer;
    QTimer *mPortRefreshTimer;
    QList<QSerialPortInfo> mAvailablePorts;
    QVector<double> timeData, afrData, rpmData, tempData, tpsData, mapData;
    double timeCounter = 0;
    bool isConnected = false;

    void setupPlots();
    void populatePorts();
};

#endif // MAINWINDOW_H
