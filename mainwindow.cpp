#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sensorCards(new SensorCards(this))
    , individualGraphs(new IndividualGraphs(this))
    , combinedGraphs(new CombinedGraphs(this))
    , serialHandler(new SerialHandler(this))
{
    ui->setupUi(this);
    
    // Tambahkan widget ke tab
    ui->tabSensorCards->layout()->addWidget(sensorCards);
    ui->tabIndividualGraphs->layout()->addWidget(individualGraphs);
    ui->tabCombinedGraphs->layout()->addWidget(combinedGraphs);
    
    // Isi combobox port serial
    foreach(const QString &port, serialHandler->getAvailablePorts()) {
        ui->portComboBox->addItem(port);
    }
    
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // Hubungkan sinyal dari SerialHandler ke slot untuk memperbarui UI
    connect(serialHandler, &SerialHandler::dataReceived, 
            this, &MainWindow::onSensorDataReceived);
}

// Di MainWindow.cpp
void MainWindow::on_connectButton_clicked()
{
    if (serialHandler->isConnected()) {
        serialHandler->disconnect();
        ui->connectButton->setText("Connect");
        ui->portComboBox->setEnabled(true);
    } else {
        QString portName = ui->portComboBox->currentText();
        if (serialHandler->connectToPort(portName)) {
            ui->connectButton->setText("Disconnect");
            ui->portComboBox->setEnabled(false);
        }
    }
}

void MainWindow::onSensorDataReceived(double afr, double rpm, double temp, double tps, double map, double timestamp)
{
    // Perbarui kartu sensor
    sensorCards->updateValues(afr, rpm, temp, tps, map);
    
    // Perbarui grafik individual
    individualGraphs->updateGraphs(afr, rpm, temp, tps, map, timestamp);
    
    // Perbarui grafik gabungan
    combinedGraphs->updateGraph(afr, rpm, temp, tps, map, timestamp);
}
