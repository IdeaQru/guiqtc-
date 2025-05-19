#include "IndividualGraphs.h"
#include "ui_IndividualGraphs.h"

IndividualGraphs::IndividualGraphs(QWidget *parent) : QWidget(parent),
ui(new Ui::IndividualGraphs)
{
    ui->setupUi(this);
    setupDarkTheme();
    setupGraphs();
}

void IndividualGraphs::onGraphClicked(QMouseEvent *event)
{
    // Dapatkan QCustomPlot yang diklik
    QCustomPlot *plot = qobject_cast<QCustomPlot *>(sender());
    if (!plot)
        return;

    // Dapatkan koordinat dalam sistem koordinat grafik
    double x = plot->xAxis->pixelToCoord(event->pos().x());
    double y = plot->yAxis->pixelToCoord(event->pos().y());

    // Cari titik terdekat dalam data
    if (!plot->graph(0)->data()->isEmpty())
    {
        // Gunakan lowerBound untuk menemukan titik terdekat
        QCPGraphDataContainer::const_iterator it = plot->graph(0)->data()->findBegin(x);
        if (it != plot->graph(0)->data()->constEnd())
        {
            double dataX = it->key;
            double dataY = it->value;

            // Tampilkan tooltip dengan warna yang sesuai untuk dark theme
            QToolTip::showText(event->globalPos(),
                               QString("<div style='background-color: #333; color: white; padding: 5px; border: 1px solid #555;'>"
                                       "Waktu: %1 s<br>Nilai: %2</div>").arg(dataX, 0, 'f', 2).arg(dataY, 0, 'f', 2),
                               plot);
        }
    }
}

IndividualGraphs::~IndividualGraphs()
{
    delete ui;
}

void IndividualGraphs::setupDarkTheme()
{
    // Hapus kode yang mereferensikan plotTabs
    // ui->plotTabs->setStyleSheet(...); <- Hapus atau komentari baris ini

    // Ubah warna background widget utama
    this->setStyleSheet("background-color: black;");

    // Atur margin dan spacing pada layout utama untuk tampilan yang lebih rapat
    ui->verticalLayout->setContentsMargins(2, 2, 2, 2);
    ui->verticalLayout->setSpacing(2);
}

void IndividualGraphs::setupGraphs()
{
    setupGraph(ui->plotAFR, "Air Fuel Ratio", QColor(0, 255, 0));       // Hijau
    setupGraph(ui->plotRPM, "Engine RPM", QColor(255, 255, 0));         // Kuning
    setupGraph(ui->plotTemp, "Temperature", QColor(0, 150, 255));       // Biru
    setupGraph(ui->plotTPS, "Throttle Position", QColor(255, 100, 0));  // Oranye
    setupGraph(ui->plotMAP, "Manifold Pressure", QColor(0, 255, 255));  // Cyan

    // Connect signal untuk interaksi mouse
    connect(ui->plotAFR, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
    connect(ui->plotRPM, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
    connect(ui->plotTemp, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
    connect(ui->plotTPS, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
    connect(ui->plotMAP, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
    
    // Tambahkan label nilai saat ini untuk setiap grafik
    addCurrentValueLabel(ui->plotAFR, "AFR", QColor(0, 255, 0));
    addCurrentValueLabel(ui->plotRPM, "RPM", QColor(255, 255, 0));
    addCurrentValueLabel(ui->plotTemp, "TEMP", QColor(0, 150, 255));
    addCurrentValueLabel(ui->plotTPS, "TPS", QColor(255, 100, 0));
    addCurrentValueLabel(ui->plotMAP, "MAP", QColor(0, 255, 255));
}

void IndividualGraphs::addCurrentValueLabel(QCustomPlot *plot, const QString &name, const QColor &color)
{
    // Buat text item untuk label nilai
    QCPItemText *valueLabel = new QCPItemText(plot);
    
    // Posisikan di pojok kiri bawah, di samping sumbu x
    valueLabel->setPositionAlignment(Qt::AlignLeft|Qt::AlignBottom);
    
    // Posisi di dekat sumbu x di sebelah kiri
    valueLabel->position->setCoords(plot->xAxis->range().lower + (plot->xAxis->range().size() * 0.01), 
                                   plot->yAxis->range().lower + (plot->yAxis->range().size() * 0.05));
    
    // Format teks secara horizontal
    valueLabel->setText(name + ": 0.0");
    valueLabel->setColor(color);
    valueLabel->setFont(QFont("Arial", 11, QFont::Bold));
    valueLabel->setPadding(QMargins(6, 3, 6, 3));
    
    // Tambahkan background semi-transparan dengan border
    valueLabel->setBrush(QBrush(QColor(0, 0, 0, 180)));
    valueLabel->setPen(QPen(color, 1));
    
    // Simpan pointer ke label dalam property plot
    plot->setProperty("valueLabel", QVariant::fromValue<void*>(valueLabel));
}



void IndividualGraphs::setupGraph(QCustomPlot *plot, const QString &title, const QColor &color)
{
    // Background hitam
    plot->setBackground(QBrush(QColor(0, 0, 0)));
    
    // Tambahkan grafik dengan warna yang sesuai
    plot->addGraph();
    plot->graph(0)->setPen(QPen(color, 2)); // Garis lebih tebal
    
    // Warna axis dan grid
    plot->xAxis->setBasePen(QPen(QColor(120, 120, 120)));
    plot->yAxis->setBasePen(QPen(QColor(120, 120, 120)));
    plot->xAxis->setTickPen(QPen(QColor(120, 120, 120)));
    plot->yAxis->setTickPen(QPen(QColor(120, 120, 120)));
    plot->xAxis->setSubTickPen(QPen(QColor(80, 80, 80)));
    plot->yAxis->setSubTickPen(QPen(QColor(80, 80, 80)));
    plot->xAxis->setTickLabelColor(QColor(180, 180, 180));
    plot->yAxis->setTickLabelColor(QColor(180, 180, 180));
    plot->xAxis->setLabelColor(QColor(180, 180, 180));
    plot->yAxis->setLabelColor(QColor(180, 180, 180));
    
    // Grid abu-abu gelap
    plot->xAxis->grid()->setPen(QPen(QColor(50, 50, 50)));
    plot->yAxis->grid()->setPen(QPen(QColor(50, 50, 50)));
    
    // Label axis
    plot->xAxis->setLabel("Time (s)");
    plot->yAxis->setLabel(title);
    
    // Interaksi
    plot->setInteraction(QCP::iRangeDrag, true);
    plot->setInteraction(QCP::iRangeZoom, true);
    
    // Setup range yang sesuai berdasarkan jenis data
    if (title == "Engine RPM") {
        plot->yAxis->setRange(0, 8000);
    } else if (title == "Air Fuel Ratio") {
        plot->yAxis->setRange(10, 18);
    } else if (title == "Temperature") {
        plot->yAxis->setRange(0, 120);
    } else if (title == "Throttle Position") {
        plot->yAxis->setRange(0, 100);
    } else if (title == "Manifold Pressure") {
        plot->yAxis->setRange(0, 250);
    }
}
void IndividualGraphs::updateValueLabel(QCustomPlot *plot, double value)
{
    QCPItemText *valueLabel = static_cast<QCPItemText*>(plot->property("valueLabel").value<void*>());
    if (valueLabel) {
        // Dapatkan nama dari label (bagian sebelum ":")
        QString name = valueLabel->text().split(":")[0];
        
        // Format nilai dengan 1 desimal
        QString formattedValue = QString::number(value, 'f', 1);
        
        // Update teks label dalam format horizontal
        valueLabel->setText(name + ": " + formattedValue);
        
        // Update posisi label agar tetap di pojok kiri bawah
        valueLabel->position->setCoords(plot->xAxis->range().lower + (plot->xAxis->range().size() * 0.01), 
                                       plot->yAxis->range().lower + (plot->yAxis->range().size() * 0.05));
    }
}

void IndividualGraphs::updateGraphs(double afr, double rpm, double temp, double tps, double map, double timestamp)
{
    // Tambahkan data ke grafik
    ui->plotAFR->graph(0)->addData(timestamp, afr);
    ui->plotRPM->graph(0)->addData(timestamp, rpm);
    ui->plotTemp->graph(0)->addData(timestamp, temp);
    ui->plotTPS->graph(0)->addData(timestamp, tps);
    ui->plotMAP->graph(0)->addData(timestamp, map);

    // Batasi jumlah titik data (opsional, untuk performa)
    const int maxDataPoints = 1000;
    QList<QCustomPlot*> plots = {ui->plotAFR, ui->plotRPM, ui->plotTemp, ui->plotTPS, ui->plotMAP};
    
    for (QCustomPlot* plot : plots) {
        while (plot->graph(0)->dataCount() > maxDataPoints) {
            if (!plot->graph(0)->data()->isEmpty()) {
                double firstKey = plot->graph(0)->data()->constBegin()->key;
                plot->graph(0)->data()->remove(firstKey);
            }
        }
    }

    // Update range untuk semua grafik
    if (ui->plotAFR->graph(0)->dataCount() > 1) {
        for (QCustomPlot* plot : plots) {
            plot->xAxis->setRange(timestamp - 30, timestamp + 1);
        }
    }

    // Update nilai saat ini pada label
    updateValueLabel(ui->plotAFR, afr);
    updateValueLabel(ui->plotRPM, rpm);
    updateValueLabel(ui->plotTemp, temp);
    updateValueLabel(ui->plotTPS, tps);
    updateValueLabel(ui->plotMAP, map);

    // Replot semua grafik dengan mode antrian untuk performa lebih baik
    for (QCustomPlot* plot : plots) {
        plot->replot(QCustomPlot::rpQueuedReplot);
    }
}



