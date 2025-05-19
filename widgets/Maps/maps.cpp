#include "Maps.h"
#include <Qlabel.h>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem> // For drawing markers

Maps::Maps(QWidget *parent) : QWidget(parent)
{
    // Setup layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    
    // Buat QWebEngineView
    webView = new QWebEngineView(this);
    layout->addWidget(webView);
    
    // Load HTML template
    loadMapHtml();
    
    // Set layout
    setLayout(layout);
}

Maps::~Maps()
{
}
void Maps::addMarker(double lat, double lng)
{
    // Example: Create a marker as a red circle on the map.
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsEllipseItem *marker = scene->addEllipse(-5, -5, 10, 10);
    marker->setBrush(Qt::red);  // Set marker color to red

    // Convert lat/lng to map coordinates (this is just a placeholder)
    marker->setPos(lat, lng); // You should convert lat/lng to map coordinates here
}

void Maps::addPolyline(double lat, double lng)
{
    // Example: Draw a line (polyline) between the points.
    // You need to store previous coordinates and connect them with a line.
    
    static QVector<QPair<double, double>> previousPoints; // Store previous points for the polyline

    // Add the new point to the polyline
    previousPoints.append(qMakePair(lat, lng));

    // If there are more than 1 point, draw the polyline
    if (previousPoints.size() > 1) {
        QGraphicsScene *scene = new QGraphicsScene(this);

        for (int i = 0; i < previousPoints.size() - 1; ++i) {
            double lat1 = previousPoints[i].first;
            double lng1 = previousPoints[i].second;
            double lat2 = previousPoints[i + 1].first;
            double lng2 = previousPoints[i + 1].second;

            // Convert lat/lng to your map coordinates
            // For now, we are just drawing a line as an example
            scene->addLine(lat1, lng1, lat2, lng2);  // This is a placeholder; map your lat/lng to scene coordinates
        }
    }
}
void Maps::loadMapHtml()
{
    // Baca file HTML dari resources
    QFile file(":/resources/maps.html");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        htmlTemplate = stream.readAll();
        file.close();
        
        // Tambahkan opsi untuk menonaktifkan akselerasi hardware di HTML
        htmlTemplate.replace("<head>", 
                            "<head>\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\">"
                            "\n<style>* { transform: translateZ(0); }</style>");
        
        // Load HTML ke webView
        webView->setHtml(htmlTemplate);
        
        // Tambahkan penanganan error
        connect(webView->page(), &QWebEnginePage::loadFinished, this, [this](bool success) {
            if (!success) {
                qWarning() << "Failed to load map HTML";
                // Tampilkan pesan error di UI
                QLabel *errorLabel = new QLabel("Failed to load map. Please check your GPU drivers.", this);
                errorLabel->setStyleSheet("color: red; background-color: #333; padding: 10px;");
                QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(this->layout());
                if (layout) {
                    layout->addWidget(errorLabel);
                }
            }
        });
    } else {
        qWarning() << "Failed to load maps.html from resources";
    }
}


void Maps::updateLocation(double latitude, double longitude, double speed)
{
    // Simpan koordinat untuk tracking
    trackCoordinates.append(qMakePair(latitude, longitude));
    
    // Panggil fungsi JavaScript untuk memperbarui posisi
    QString jsCode = QString("updatePosition(%1, %2, %3);").arg(latitude).arg(longitude).arg(speed);
    webView->page()->runJavaScript(jsCode);
}

void Maps::drawPolygon(const QVector<QPair<double, double>>& coordinates)
{
    // Buat array JSON untuk koordinat
    QString jsArray = "[";
    for (int i = 0; i < coordinates.size(); ++i) {
        if (i > 0) jsArray += ",";
        jsArray += QString("[%1,%2]").arg(coordinates[i].first).arg(coordinates[i].second);
    }
    jsArray += "]";
    
    // Panggil fungsi JavaScript untuk menggambar polygon
    QString jsCode = QString("drawPolygon(%1);").arg(jsArray);
    webView->page()->runJavaScript(jsCode);
}

void Maps::clearAll()
{
    // Reset koordinat tracking
    trackCoordinates.clear();
    
    // Panggil fungsi JavaScript untuk menghapus semua data
    webView->page()->runJavaScript("clearAll();");
}
