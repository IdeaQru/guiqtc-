#include "IndividualGraphs.h"
#include "ui_IndividualGraphs.h"

IndividualGraphs::IndividualGraphs(QWidget *parent) : QWidget(parent),
                                                      ui(new Ui::IndividualGraphs)
{
    ui->setupUi(this);
    setupGraphs();
}
// Di IndividualGraphs.cpp
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

            // Tampilkan tooltip
            QToolTip::showText(event->globalPos(),
                               QString("Waktu: %1 s\nNilai: %2").arg(dataX, 0, 'f', 2).arg(dataY, 0, 'f', 2),
                               plot);
        }
    }
}

IndividualGraphs::~IndividualGraphs()
{
    delete ui;
}

void IndividualGraphs::setupGraphs()
{
    setupGraph(ui->plotAFR, "Air Fuel Ratio", QColor("#2196F3"));
    setupGraph(ui->plotRPM, "Engine RPM", QColor("#ff4444"));
    setupGraph(ui->plotTemp, "Temperature", QColor("#FFD700"));
    setupGraph(ui->plotTPS, "Throttle Position", QColor("#00FF88"));
    setupGraph(ui->plotMAP, "Manifold Pressure", QColor("#FFA500"));
    // Di konstruktor IndividualGraphs atau di setupGraphs()
    connect(ui->plotAFR, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
    connect(ui->plotRPM, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
    connect(ui->plotTemp, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
    connect(ui->plotTPS, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
    connect(ui->plotMAP, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onGraphClicked(QMouseEvent *)));
}

void IndividualGraphs::setupGraph(QCustomPlot *plot, const QString &title, const QColor &color)
{
    plot->addGraph();
    plot->graph(0)->setPen(QPen(color));
    plot->xAxis->setLabel("Time (s)");
    plot->yAxis->setLabel(title);
    plot->setInteraction(QCP::iRangeDrag, true);
    plot->setInteraction(QCP::iRangeZoom, true);
    plot->axisRect()->setupFullAxesBox();
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
    while (ui->plotAFR->graph(0)->dataCount() > maxDataPoints)
    {
        if (!ui->plotAFR->graph(0)->data()->isEmpty())
        {
            double firstKey = ui->plotAFR->graph(0)->data()->constBegin()->key;
            ui->plotAFR->graph(0)->data()->remove(firstKey);
        }
    }

    // Rescale axes jika diperlukan
    if (ui->plotAFR->graph(0)->dataCount() > 1)
    {
        ui->plotAFR->xAxis->setRange(timestamp - 30, timestamp + 1);
        ui->plotAFR->yAxis->rescale();

        ui->plotRPM->xAxis->setRange(timestamp - 30, timestamp + 1);
        ui->plotRPM->yAxis->rescale();

        ui->plotTemp->xAxis->setRange(timestamp - 30, timestamp + 1);
        ui->plotTemp->yAxis->rescale();

        ui->plotTPS->xAxis->setRange(timestamp - 30, timestamp + 1);
        ui->plotTPS->yAxis->rescale();

        ui->plotMAP->xAxis->setRange(timestamp - 30, timestamp + 1);
        ui->plotMAP->yAxis->rescale();
    }

    // Replot semua grafik
    ui->plotAFR->replot();
    ui->plotRPM->replot();
    ui->plotTemp->replot();
    ui->plotTPS->replot();
    ui->plotMAP->replot();
}
