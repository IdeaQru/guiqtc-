#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QIcon>
#include <QToolButton>
#include <QJsonDocument>
#include <QJsonArray>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sensorCards(new SensorCards(this))
    , individualGraphs(new IndividualGraphs(this))
    , combinedGraphs(new CombinedGraphs(this))
    , serialHandler(new SerialHandler(this))
    , mapsWidget(new Maps(this))
{
    ui->setupUi(this);

    // Terapkan dark theme
    setupDarkTheme();
  // Setup tab icons dengan tooltip
    setupTabIcons();

    // Tambahkan widget ke tab
    ui->tabSensorCards->layout()->addWidget(sensorCards);
    ui->tabIndividualGraphs->layout()->addWidget(individualGraphs);
    ui->tabCombinedGraphs->layout()->addWidget(combinedGraphs);
    ui->tabMaps->layout()->addWidget(mapsWidget);

    // Isi combobox port serial
    foreach(const QString &port, serialHandler->getAvailablePorts()) {
        ui->portComboBox->addItem(port);
    }

  
    setupConnections();

    // Tambahkan tombol untuk Maps
    setupMapControls();
}

void MainWindow::setupMapControls()
{
    // Buat tombol untuk Maps
    QPushButton* drawPolygonBtn = new QPushButton("Draw Polygon", this);
    QPushButton* resetMapBtn = new QPushButton("Reset Map", this);

    // Styling untuk dark mode
    drawPolygonBtn->setStyleSheet("background-color: #4CAF50; color: white; border-radius: 5px; padding: 8px;");
    resetMapBtn->setStyleSheet("background-color: #f44336; color: white; border-radius: 5px; padding: 8px;");

    // Tambahkan tombol ke layout
    QHBoxLayout* mapControlLayout = new QHBoxLayout();
    mapControlLayout->addWidget(drawPolygonBtn);
    mapControlLayout->addWidget(resetMapBtn);
    mapControlLayout->addStretch();

    // Tambahkan layout tombol ke tab Maps
    QVBoxLayout* mapsLayout = qobject_cast<QVBoxLayout*>(ui->tabMaps->layout());
    if (mapsLayout) {
        mapsLayout->insertLayout(0, mapControlLayout);
    }

    // Connect signals
    connect(drawPolygonBtn, &QPushButton::clicked, this, &MainWindow::onDrawPolygonClicked);
    connect(resetMapBtn, &QPushButton::clicked, this, &MainWindow::onResetMapClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDarkTheme()
{
    // Terapkan dark stylesheet ke seluruh aplikasi
    QString darkStylesheet = R"(
        QMainWindow, QWidget {
            background-color: #121212;
            color: #e0e0e0;
        }
        QPushButton {
            background-color: #333333;
            color: #e0e0e0;
            border-radius: 5px;
            border: 1px solid #444444;
            padding: 6px;
        }
        QPushButton:hover {
            background-color: #444444;
        }
        QComboBox {
            background-color: #2d2d2d;
            color: #ffffff;
            border-radius: 5px;
            border: 1px solid #3d3d3d;
            padding: 4px;
        }
        QComboBox QAbstractItemView {
            background-color: #2d2d2d;
            color: #ffffff;
            selection-background-color: #3d3d3d;
        }
        QLabel {
            color: #e0e0e0;
        }
        QTabWidget::pane {
            border: 1px solid #444444;
            background-color: #121212;
        }
        QTabBar::tab {
            background-color: #1e1e1e;
            color: #b0b0b0;
            padding: 8px 12px;
            margin-right: 2px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
        }
        QTabBar::tab:selected {
            background-color: #2d2d2d;
            color: #ffffff;
            border-bottom: 2px solid #0078d7;
        }
        QTabBar::tab:hover:!selected {
            background-color: #252525;
        }
        QStatusBar {
            background-color: #1e1e1e;
            color: #b0b0b0;
        }
        QToolTip {
            background-color: #2d2d2d;
            color: #ffffff;
            border: 1px solid #3d3d3d;
            padding: 2px;
        }
    )";

    this->setStyleSheet(darkStylesheet);

    // Ubah warna tombol Connect menjadi hijau
    ui->connectButton->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border-radius: 5px;
            padding: 8px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
    )");

    // Ubah warna status label
    ui->statusLabel->setStyleSheet("color: #ff4444; font-weight: bold;");
}

void MainWindow::setupTabIcons()
{
    // Hapus teks dari tab dan ganti dengan icon
    ui->mainTabWidget->setTabText(0, "");
    ui->mainTabWidget->setTabIcon(0, QIcon(":/resources/icons/dashboard.png"));
    ui->mainTabWidget->setTabToolTip(0, "Sensor Cards");

    ui->mainTabWidget->setTabText(1, "");
    ui->mainTabWidget->setTabIcon(1, QIcon(":/resources/icons/chart_individual.png"));
    ui->mainTabWidget->setTabToolTip(1, "Individual Graphs");

    ui->mainTabWidget->setTabText(2, "");
    ui->mainTabWidget->setTabIcon(2, QIcon(":/resources/icons/chart_combined.png"));
    ui->mainTabWidget->setTabToolTip(2, "Combined Graph");

    ui->mainTabWidget->setTabText(3, "");
    ui->mainTabWidget->setTabIcon(3, QIcon(":/resources/icons/map.png")); // Tambahkan icon untuk Maps
    ui->mainTabWidget->setTabToolTip(3, "Maps");

    // Atur ukuran icon
    ui->mainTabWidget->setIconSize(QSize(24, 24));
}

void MainWindow::setupConnections()
{
    // Hubungkan sinyal dari SerialHandler ke slot untuk memperbarui UI
    connect(serialHandler, &SerialHandler::dataReceived,
            this, &MainWindow::onSensorDataReceived);

    // // Connect button
    // connect(ui->connectButton, &QPushButton::clicked,
    //         this, &MainWindow::on_connectButton_clicked);
}

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

void MainWindow::onSensorDataReceived(double afr, double rpm, double temp, double tps, double map, double lat, double lng, double speed, double timestamp)
{
    // Perbarui kartu sensor
    sensorCards->updateValues(afr, rpm, temp, tps, map);

    // Perbarui grafik individual
    individualGraphs->updateGraphs(afr, rpm, temp, tps, map, timestamp);

    // Perbarui grafik gabungan
    combinedGraphs->updateGraph(afr, rpm, temp, tps, map, timestamp);

    // // Perbarui lokasi di peta
    mapsWidget->updateLocation(lat, lng, speed);
    mapsWidget->addMarker(lat, lng); // Tambahkan marker
    mapsWidget->addPolyline(lat, lng); // Menghubungkan titik dengan polyline
}


void MainWindow::drawPolygonFromData(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isArray()) {
        QJsonArray array = doc.array();
        QVector<QPair<double, double>> coordinates;

        for (int i = 0; i < array.size(); ++i) {
            QJsonArray point = array[i].toArray();
            if (point.size() == 2) {
                double lat = point[0].toDouble();
                double lng = point[1].toDouble();
                coordinates.append(qMakePair(lat, lng));
            }
        }

        if (!coordinates.isEmpty()) {
            mapsWidget->drawPolygon(coordinates);
        }
    }
}

void MainWindow::onDrawPolygonClicked()
{
    // Contoh data polygon (dalam aplikasi nyata, gunakan data sebenarnya)
    QVector<QPair<double, double>> polygonData = {
        {-6.5971, 106.8060},
        {-6.5980, 106.8100},
        {-6.6000, 106.8080},
        {-6.5990, 106.8050},
        {-6.5971, 106.8060}
    };

    mapsWidget->drawPolygon(polygonData);
}

void MainWindow::onResetMapClicked()
{
    mapsWidget->clearAll();
}
