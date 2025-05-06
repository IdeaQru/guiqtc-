#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QPen>
#include <QDebug>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Inisialisasi serial port dan timer
    mSerial = new QSerialPort(this);
    mUpdateTimer = new QTimer(this);
    mPortRefreshTimer = new QTimer(this);
    
    // Koneksi signal-slot
    connect(mSerial, &QSerialPort::readyRead, this, &MainWindow::onSerialDataReceived);
    connect(mUpdateTimer, &QTimer::timeout, this, &MainWindow::updatePlots);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(mPortRefreshTimer, &QTimer::timeout, this, &MainWindow::refreshPorts);
    
    // Tambahkan koneksi untuk error serial
    connect(mSerial, &QSerialPort::errorOccurred, [=](QSerialPort::SerialPortError error) {
        if (error != QSerialPort::NoError) {
            qDebug() << "Serial error:" << mSerial->errorString();
            if (isConnected) {
                mSerial->close();
                ui->connectButton->setText("Connect");
                statusBar()->showMessage("Error: " + mSerial->errorString());
                isConnected = false;
            }
        }
    });
    
    // Inisialisasi plot
    setupPlots();
    
    // Start timer untuk update plot dan refresh port
    mUpdateTimer->start(50);
    mPortRefreshTimer->start(3000); // Refresh port setiap 3 detik
    
    // Populasi daftar port
    populatePorts();
    
    qDebug() << "MainWindow constructed";
}

MainWindow::~MainWindow()
{
    // Pastikan port ditutup sebelum aplikasi exit
    if (mSerial && mSerial->isOpen()) {
        mSerial->close();
    }
    
    delete ui;
    qDebug() << "MainWindow destroyed";
}

void MainWindow::setupPlots()
{
    // AFR Plot
    ui->plotAFR->addGraph();
    ui->plotAFR->graph(0)->setPen(QPen(QColor(Qt::blue), 2, Qt::SolidLine));
    ui->plotAFR->xAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotAFR->yAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotAFR->xAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotAFR->yAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotAFR->xAxis->setLabel("Time (s)");
    ui->plotAFR->yAxis->setLabel("AFR");
    ui->plotAFR->yAxis->setRange(10, 20);
    
    // RPM Plot
    ui->plotRPM->addGraph();
    ui->plotRPM->graph(0)->setPen(QPen(QColor(Qt::red), 2, Qt::SolidLine));
    ui->plotRPM->xAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotRPM->yAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotRPM->xAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotRPM->yAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotRPM->xAxis->setLabel("Time (s)");
    ui->plotRPM->yAxis->setLabel("RPM");
    ui->plotRPM->yAxis->setRange(0, 6000);
    
    // Temp Plot
    ui->plotTemp->addGraph();
    ui->plotTemp->graph(0)->setPen(QPen(QColor(Qt::yellow), 2, Qt::SolidLine));
    ui->plotTemp->xAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotTemp->yAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotTemp->xAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotTemp->yAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotTemp->xAxis->setLabel("Time (s)");
    ui->plotTemp->yAxis->setLabel("Temp");
    ui->plotTemp->yAxis->setRange(0, 120);
    
    // TPS Plot
    ui->plotTPS->addGraph();
    ui->plotTPS->graph(0)->setPen(QPen(QColor(Qt::green), 2, Qt::SolidLine));
    ui->plotTPS->xAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotTPS->yAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotTPS->xAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotTPS->yAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotTPS->xAxis->setLabel("Time (s)");
    ui->plotTPS->yAxis->setLabel("TPS");
    ui->plotTPS->yAxis->setRange(0, 100);
    
    // MAP Plot
    ui->plotMAP->addGraph();
    ui->plotMAP->graph(0)->setPen(QPen(QColor(Qt::magenta), 2, Qt::SolidLine));
    ui->plotMAP->xAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotMAP->yAxis->setTickPen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    ui->plotMAP->xAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotMAP->yAxis->setBasePen(QPen(QColor(Qt::gray)));
    ui->plotMAP->xAxis->setLabel("Time (s)");
    ui->plotMAP->yAxis->setLabel("MAP");
    ui->plotMAP->yAxis->setRange(0, 150);
}

void MainWindow::populatePorts()
{
    ui->portComboBox->clear();
    mAvailablePorts = QSerialPortInfo::availablePorts();
    
    qDebug() << "Available ports count:" << mAvailablePorts.count();
    
    for(const QSerialPortInfo &port : mAvailablePorts) {
        ui->portComboBox->addItem(port.portName(), port.systemLocation());
        qDebug() << "Detected port:" << port.portName() 
                 << "Description:" << port.description()
                 << "Manufacturer:" << port.manufacturer();
    }
}

void MainWindow::refreshPorts()
{
    // Simpan port yang dipilih saat ini
    QString currentPort = ui->portComboBox->currentText();
    
    // Update daftar port
    populatePorts();
    
    // Kembalikan ke port yang dipilih sebelumnya jika masih ada
    int index = ui->portComboBox->findText(currentPort);
    if (index >= 0) {
        ui->portComboBox->setCurrentIndex(index);
    }
    
    qDebug() << "Ports refreshed";
}

void MainWindow::onConnectClicked()
{
    if(ui->connectButton->text() == "Connect") {
        if(ui->portComboBox->currentText().isEmpty()) {
            QMessageBox::warning(this, "Warning", "No serial port selected!");
            return;
        }
        
        // Pastikan port ditutup sebelum dibuka lagi
        if(mSerial->isOpen()) {
            mSerial->close();
        }
        
        mSerial->setPortName(ui->portComboBox->currentText());
        mSerial->setBaudRate(QSerialPort::Baud115200);
        mSerial->setDataBits(QSerialPort::Data8);
        mSerial->setParity(QSerialPort::NoParity);
        mSerial->setStopBits(QSerialPort::OneStop);
        mSerial->setFlowControl(QSerialPort::NoFlowControl);

        if(mSerial->open(QIODevice::ReadWrite)) {
            mSerial->setDataTerminalReady(true); // Penting untuk Windows
            ui->connectButton->setText("Disconnect");
            statusBar()->showMessage("Connected to " + mSerial->portName());
            isConnected = true;
            qDebug() << "Port opened successfully:" << mSerial->portName();
        } else {
            QMessageBox::critical(this, "Error", "Gagal membuka port:\n" + mSerial->errorString());
            ui->connectButton->setText("Connect");
            isConnected = false;
            qDebug() << "Failed to open port:" << mSerial->errorString();
        }
    } else {
        mSerial->close();
        ui->connectButton->setText("Connect");
        statusBar()->showMessage("Disconnected");
        isConnected = false;
        qDebug() << "Port closed";
    }
}

void MainWindow::onSerialDataReceived()
{
    if(!mSerial->isOpen()) {
        qDebug() << "Serial port not open in onSerialDataReceived";
        return;
    }
    
    QByteArray data = mSerial->readAll();
    if(data.isEmpty()) {
        return;
    }
    
    static QString buffer;
    buffer += QString::fromUtf8(data);
    qDebug() << "Received data:" << data;
    
    int endIndex;
    while((endIndex = buffer.indexOf('\n')) != -1) {
        QString completeMessage = buffer.left(endIndex).trimmed();
        buffer = buffer.mid(endIndex + 1);
        
        if(!completeMessage.isEmpty()) {
            qDebug() << "Processing message:" << completeMessage;
            parseSerialData(completeMessage);
        }
    }
}

void MainWindow::parseSerialData(const QString &data)
{
    QStringList params = data.split(',');
    foreach(QString param, params)
    {
        QStringList keyValue = param.split(':');
        if(keyValue.size() == 2)
        {
            QString key = keyValue[0].trimmed();
            double value = keyValue[1].toDouble();
            
            if(key == "AFR") afrData.append(value);
            else if(key == "RPM") rpmData.append(value);
            else if(key == "Temp") tempData.append(value);
            else if(key == "TPS") tpsData.append(value);
            else if(key == "MAP") mapData.append(value);
            
            // Update label nilai sensor
            if(key == "AFR") ui->afrLabel->setText(QString("AFR: %1").arg(value, 0, 'f', 2));
            else if(key == "RPM") ui->rpmLabel->setText(QString("RPM: %1").arg(value, 0, 'f', 0));
            else if(key == "Temp") ui->tempLabel->setText(QString("Temp: %1").arg(value, 0, 'f', 1));
            else if(key == "TPS") ui->tpsLabel->setText(QString("TPS: %1").arg(value, 0, 'f', 1));
            else if(key == "MAP") ui->mapLabel->setText(QString("MAP: %1").arg(value, 0, 'f', 1));
        }
    }
    
    timeData.append(timeCounter);
    timeCounter += 0.05;
    
    // Batasi jumlah data untuk mencegah memory leak
    const int MAX_DATA_POINTS = 1000;
    while(timeData.size() > MAX_DATA_POINTS) {
        timeData.removeFirst();
        afrData.removeFirst();
        rpmData.removeFirst();
        tempData.removeFirst();
        tpsData.removeFirst();
        mapData.removeFirst();
    }
}

void MainWindow::updatePlots()
{
    // Periksa apakah ada data sebelum update
    if(timeData.isEmpty()) return;

    // Update AFR plot
    if(ui->plotAFR->graphCount() > 0 && !afrData.isEmpty()) {
        ui->plotAFR->graph(0)->setData(timeData, afrData);
        ui->plotAFR->xAxis->setRange(timeData.last() - 10, timeData.last());
        ui->plotAFR->replot();
    }
    
    // Update RPM plot
    if(ui->plotRPM->graphCount() > 0 && !rpmData.isEmpty()) {
        ui->plotRPM->graph(0)->setData(timeData, rpmData);
        ui->plotRPM->xAxis->setRange(timeData.last() - 10, timeData.last());
        ui->plotRPM->replot();
    }
    
    // Update Temp plot
    if(ui->plotTemp->graphCount() > 0 && !tempData.isEmpty()) {
        ui->plotTemp->graph(0)->setData(timeData, tempData);
        ui->plotTemp->xAxis->setRange(timeData.last() - 10, timeData.last());
        ui->plotTemp->replot();
    }
    
    // Update TPS plot
    if(ui->plotTPS->graphCount() > 0 && !tpsData.isEmpty()) {
        ui->plotTPS->graph(0)->setData(timeData, tpsData);
        ui->plotTPS->xAxis->setRange(timeData.last() - 10, timeData.last());
        ui->plotTPS->replot();
    }
    
    // Update MAP plot
    if(ui->plotMAP->graphCount() > 0 && !mapData.isEmpty()) {
        ui->plotMAP->graph(0)->setData(timeData, mapData);
        ui->plotMAP->xAxis->setRange(timeData.last() - 10, timeData.last());
        ui->plotMAP->replot();
    }
}
