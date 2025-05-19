#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QStringList>

class SerialHandler : public QObject
{
    Q_OBJECT
public:
    explicit SerialHandler(QObject *parent = nullptr);
    ~SerialHandler();
    
    QStringList getAvailablePorts();
    bool connectToPort(const QString &portName, int baudRate = QSerialPort::Baud115200);
    void disconnect();
    bool isConnected() const;
    QString getLastError() const;

signals:
    void dataReceived(double afr, double rpm, double temp, double tps, double map,double lat, double lng,double speed, double timestamp);
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString &errorMessage);

private slots:
    void readData();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *serialPort;
    QByteArray buffer;
    qint64 startTime;
    QString lastError;
    
    void parseData(const QString &data);
    void setupSerialPort();
};
#endif // SERIALHANDLER_H
