#include "SerialHandler.h"
#include <QSerialPortInfo>
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <QCoreApplication>

SerialHandler::SerialHandler(QObject *parent)
    : QObject(parent)
    , serialPort(new QSerialPort(this))
    , startTime(QDateTime::currentMSecsSinceEpoch())
    , lastError("")
{
    setupSerialPort();
}

SerialHandler::~SerialHandler()
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }
}

void SerialHandler::setupSerialPort()
{
    // Connect signal/slot untuk error handling
    QObject::connect(serialPort, &QSerialPort::errorOccurred, this, &SerialHandler::handleError);
    QObject::connect(serialPort, &QSerialPort::readyRead, this, &SerialHandler::readData);
}

QStringList SerialHandler::getAvailablePorts()
{
    QStringList ports;
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    qDebug() << "Mencari port yang tersedia...";
    if (serialPortInfos.isEmpty()) {
        qDebug() << "Tidak ada port serial yang ditemukan!";
        lastError = "Tidak ada port serial yang ditemukan";
        emit errorOccurred(lastError);
    }

    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        ports << portInfo.portName();
        bool isPortBusy = false;
        QSerialPort testPort;
        testPort.setPortName(portInfo.portName());
        if (!testPort.open(QIODevice::ReadWrite)) {
            isPortBusy = true;
        }
        testPort.close();

        qDebug() << "Port ditemukan:" << portInfo.portName()
                 << "- Deskripsi:" << portInfo.description()
                 << "- Manufacturer:" << portInfo.manufacturer()
                 << "- Serial Number:" << portInfo.serialNumber()
                 << "- System Location:" << portInfo.systemLocation();

        if (portInfo.hasVendorIdentifier()) {
            qDebug() << "  Vendor ID:" << QString("0x%1").arg(portInfo.vendorIdentifier(), 4, 16, QChar('0'));
        }
        if (portInfo.hasProductIdentifier()) {
            qDebug() << "  Product ID:" << QString("0x%1").arg(portInfo.productIdentifier(), 4, 16, QChar('0'));
        }
        qDebug() << "  Busy:" << (isPortBusy ? "Yes" : "No");
    }

    return ports;
}

bool SerialHandler::connectToPort(const QString &portName, int baudRate)
{
    qDebug() << "Mencoba membuka port serial: " << portName << " dengan baud rate: " << baudRate;

    if (serialPort->isOpen()) {
        qDebug() << "Port sudah terbuka, menutup port terlebih dahulu...";
        serialPort->close();
        QThread::msleep(200); // Tunggu agar port benar-benar tertutup
    }

    // Reset error
    lastError = "";

    // Konfigurasi port
    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    // Coba buka port dengan mode ReadWrite
    if (!serialPort->open(QIODevice::ReadWrite)) {
        lastError = QString("Error opening port %1: %2").arg(portName).arg(serialPort->errorString());
        qDebug() << lastError;
        emit errorOccurred(lastError);
        return false;
    }

    // Tambahkan delay kecil setelah membuka port
    QThread::msleep(200);

    // Reset buffer dan timer
    startTime = QDateTime::currentMSecsSinceEpoch();
    buffer.clear();

    // Aktifkan DTR (Data Terminal Ready)
    serialPort->setDataTerminalReady(true);

    // Flush buffer
    serialPort->clear();

    qDebug() << "Port" << portName << "berhasil dibuka dengan baudrate" << baudRate;
    emit connectionStatusChanged(true);


    // Proses events untuk memastikan sinyal diproses
    QCoreApplication::processEvents();

    return true;
}

void SerialHandler::disconnect()
{
    if (serialPort->isOpen()) {
        serialPort->clear();
        serialPort->close();
        qDebug() << "Port ditutup";
        emit connectionStatusChanged(false);
    }

}

bool SerialHandler::isConnected() const
{
    return serialPort->isOpen();
}

QString SerialHandler::getLastError() const
{
    return lastError;
}

void SerialHandler::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) {
        return;
    }

    lastError = QString("Serial port error: %1 (%2)").arg(serialPort->errorString()).arg(error);
    qDebug() << lastError;

    // Tutup port jika terjadi error serius
    if (error != QSerialPort::TimeoutError && error != QSerialPort::NotOpenError) {
        if (serialPort->isOpen()) {
            serialPort->close();
            emit connectionStatusChanged(false);
        }
    }

    emit errorOccurred(lastError);
}

void SerialHandler::readData()
{
    QByteArray data = serialPort->readAll();
    if (data.isEmpty()) {
        qDebug() << "No data received.";
        return;
    }

    qDebug() << "Data diterima:" << data;
    buffer.append(data);

    // Cari baris lengkap
    int endIndex;
    while ((endIndex = buffer.indexOf('\n')) != -1) {
        QByteArray line = buffer.left(endIndex).trimmed();
        buffer.remove(0, endIndex + 1);

        if (!line.isEmpty()) {
            qDebug() << "Parsing line:" << line;
            parseData(QString::fromUtf8(line));
        }
    }
}

void SerialHandler::parseData(const QString &data)
{
    // Format data yang diharapkan: "AFR,RPM,TEMP,TPS,MAP,LAT,LNG,SPEED"
    QStringList parts = data.split(',');
    qDebug() << "Data parts:" << parts;

    if (parts.size() >= 8) {
        bool ok1, ok2, ok3, ok4, ok5, ok6, ok7, ok8;
        double afr = parts[0].toDouble(&ok1);
        double rpm = parts[1].toDouble(&ok2);
        double temp = parts[2].toDouble(&ok3);
        double tps = parts[3].toDouble(&ok4);
        double map = parts[4].toDouble(&ok5);
        double lat = parts[5].toDouble(&ok6);   // Latitude
        double lng = parts[6].toDouble(&ok7);   // Longitude
        double speed = parts[7].toDouble(&ok8); // Speed

        if (ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7 && ok8) {
            // Hitung timestamp (detik sejak koneksi)
            double timestamp = (QDateTime::currentMSecsSinceEpoch() - startTime) / 1000.0;

            qDebug() << "Emitting data:" << afr << rpm << temp << tps << map << lat << lng << speed << timestamp;
            emit dataReceived(afr, rpm, temp, tps, map, lat, lng, speed, timestamp);  // Include lat, lng, and speed
        } else {
            qDebug() << "Konversi data gagal:" << data;
        }
    } else {
        qDebug() << "Format data tidak valid:" << data;
    }
}
