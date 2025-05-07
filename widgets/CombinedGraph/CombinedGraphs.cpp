#include "CombinedGraphs.h"
#include "ui_CombinedGraphs.h"
#include <QToolTip>

CombinedGraphs::CombinedGraphs(QWidget *parent) : QWidget(parent),
                                                  ui(new Ui::CombinedGraphs)
{
    ui->setupUi(this);
    setupGraph();

    // Connect checkbox signals
    connect(ui->checkAFR, &QCheckBox::toggled, this, &CombinedGraphs::onCheckBoxToggled);
    connect(ui->checkRPM, &QCheckBox::toggled, this, &CombinedGraphs::onCheckBoxToggled);
    connect(ui->checkTemp, &QCheckBox::toggled, this, &CombinedGraphs::onCheckBoxToggled);
    connect(ui->checkTPS, &QCheckBox::toggled, this, &CombinedGraphs::onCheckBoxToggled);
    connect(ui->checkMAP, &QCheckBox::toggled, this, &CombinedGraphs::onCheckBoxToggled);
}

CombinedGraphs::~CombinedGraphs()
{
    delete ui;
}

void CombinedGraphs::onCombinedGraphClicked(QMouseEvent *event)
{
    // Dapatkan koordinat dalam sistem koordinat grafik
    double x = ui->plotCombined->xAxis->pixelToCoord(event->pos().x());

    // Buat string untuk tooltip
    QString tooltipText = QString("Waktu: %1 s\n").arg(x, 0, 'f', 2);

    // Cek setiap grafik untuk nilai pada waktu x
    QVector<QString> sensorNames = {"AFR", "RPM", "Temp", "TPS", "MAP"};

    for (int i = 0; i < ui->plotCombined->graphCount() && i < sensorNames.size(); ++i)
    {
        if (!ui->plotCombined->graph(i)->data()->isEmpty())
        {
            // Cari titik terdekat
            QCPGraphDataContainer::const_iterator it = ui->plotCombined->graph(i)->data()->findBegin(x);
            if (it != ui->plotCombined->graph(i)->data()->constEnd())
            {
                double value = it->value;
                tooltipText += QString("%1: %2\n").arg(sensorNames[i]).arg(value, 0, 'f', 2);
            }
        }
    }

    // Tampilkan tooltip
    QToolTip::showText(event->globalPos(), tooltipText, ui->plotCombined);
}

void CombinedGraphs::setupGraph()
{
    // Di konstruktor CombinedGraphs atau di setupGraph()
    connect(ui->plotCombined, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onCombinedGraphClicked(QMouseEvent *)));

    // Setup plot
    ui->plotCombined->setInteraction(QCP::iRangeDrag, true);
    ui->plotCombined->setInteraction(QCP::iRangeZoom, true);
    ui->plotCombined->axisRect()->setupFullAxesBox();

    // Setup legend
    ui->plotCombined->legend->setVisible(true);
    ui->plotCombined->legend->setFont(QFont("Arial", 9));
    ui->plotCombined->legend->setBrush(QBrush(QColor(255, 255, 255, 100)));
    ui->plotCombined->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);

    // Setup primary Y axis (left)
    ui->plotCombined->yAxis->setLabel("AFR / TPS (%) / MAP (kPa)");

    // Setup secondary Y axis (right) for RPM and Temperature
    ui->plotCombined->yAxis2->setVisible(true);
    ui->plotCombined->yAxis2->setLabel("RPM / Temperature (°C)");

    // Setup X axis
    ui->plotCombined->xAxis->setLabel("Time (s)");

    // Add graphs for each sensor
    ui->plotCombined->addGraph();
    ui->plotCombined->graph(0)->setPen(QPen(QColor("#2196F3")));
    ui->plotCombined->graph(0)->setName("AFR");

    ui->plotCombined->addGraph(ui->plotCombined->xAxis, ui->plotCombined->yAxis2);
    ui->plotCombined->graph(1)->setPen(QPen(QColor("#ff4444")));
    ui->plotCombined->graph(1)->setName("RPM");

    ui->plotCombined->addGraph(ui->plotCombined->xAxis, ui->plotCombined->yAxis2);
    ui->plotCombined->graph(2)->setPen(QPen(QColor("#FFD700")));
    ui->plotCombined->graph(2)->setName("Temp");

    ui->plotCombined->addGraph();
    ui->plotCombined->graph(3)->setPen(QPen(QColor("#00FF88")));
    ui->plotCombined->graph(3)->setName("TPS");

    ui->plotCombined->addGraph();
    ui->plotCombined->graph(4)->setPen(QPen(QColor("#FFA500")));
    ui->plotCombined->graph(4)->setName("MAP");
}

void CombinedGraphs::onCheckBoxToggled()
{
    ui->plotCombined->graph(0)->setVisible(ui->checkAFR->isChecked());
    ui->plotCombined->graph(1)->setVisible(ui->checkRPM->isChecked());
    ui->plotCombined->graph(2)->setVisible(ui->checkTemp->isChecked());
    ui->plotCombined->graph(3)->setVisible(ui->checkTPS->isChecked());
    ui->plotCombined->graph(4)->setVisible(ui->checkMAP->isChecked());

    updateLegend();
    ui->plotCombined->replot();
}

void CombinedGraphs::updateLegend()
{
    for (int i = 0; i < ui->plotCombined->graphCount(); ++i)
    {
        ui->plotCombined->graph(i)->removeFromLegend();
        if (ui->plotCombined->graph(i)->visible())
        {
            ui->plotCombined->graph(i)->addToLegend();
        }
    }
}

void CombinedGraphs::updateGraph(double afr, double rpm, double temp, double tps, double map, double timestamp)
{
    // Tambahkan data ke grafik
    ui->plotCombined->graph(0)->addData(timestamp, afr);
    ui->plotCombined->graph(1)->addData(timestamp, rpm);
    ui->plotCombined->graph(2)->addData(timestamp, temp);
    ui->plotCombined->graph(3)->addData(timestamp, tps);
    ui->plotCombined->graph(4)->addData(timestamp, map);

    // Batasi jumlah titik data (opsional, untuk performa)
    const int maxDataPoints = 1000;
    for (int i = 0; i < ui->plotCombined->graphCount(); ++i)
    {
        while (ui->plotCombined->graph(i)->dataCount() > maxDataPoints)
        {
            if (!ui->plotCombined->graph(i)->data()->isEmpty())
            {
                double firstKey = ui->plotCombined->graph(i)->data()->constBegin()->key;
                ui->plotCombined->graph(i)->data()->remove(firstKey);
            }
        }
    }

    // Rescale axes jika diperlukan
    if (ui->plotCombined->graph(0)->dataCount() > 1)
    {
        ui->plotCombined->xAxis->setRange(timestamp - 30, timestamp + 1);

        // Rescale primary Y axis (AFR, TPS, MAP)
        bool rescaleYAxis = ui->checkAFR->isChecked() || ui->checkTPS->isChecked() || ui->checkMAP->isChecked();
        if (rescaleYAxis)
        {
            ui->plotCombined->yAxis->rescale();
        }

        // Rescale secondary Y axis (RPM, Temp)
        bool rescaleY2Axis = ui->checkRPM->isChecked() || ui->checkTemp->isChecked();
        if (rescaleY2Axis)
        {
            ui->plotCombined->yAxis2->rescale();
        }
    }

    ui->plotCombined->replot();
}
