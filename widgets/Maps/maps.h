#ifndef MAPS_H
#define MAPS_H

#include <QWidget>
#include <QWebEngineView>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QWebChannel>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

class Maps : public QWidget
{
    Q_OBJECT

public:
    explicit Maps(QWidget *parent = nullptr);
    ~Maps();
    
    // Method untuk memperbarui posisi pada peta
    void updateLocation(double latitude, double longitude, double speed);
    
    // Method untuk menggambar polygon dari koordinat
    void drawPolygon(const QVector<QPair<double, double>>& coordinates);
    // Add marker method
    void addMarker(double lat, double lng);

    // Add polyline method
    void addPolyline(double lat, double lng);
    // Method untuk menghapus semua data
    void clearAll();

private:
    QWebEngineView *webView;
    QString htmlTemplate;
    QVector<QPair<double, double>> trackCoordinates;
    
    void loadMapHtml();
};

#endif // MAPS_H
