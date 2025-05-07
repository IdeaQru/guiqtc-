#include "SensorCards.h"
#include "ui_SensorCards.h"

SensorCards::SensorCards(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorCards)
{
    ui->setupUi(this);
}

SensorCards::~SensorCards()
{
    delete ui;
}

void SensorCards::updateValues(double afr, double rpm, double temp, double tps, double map)
{
    ui->afrLabel->setText(QString("AFR: %1").arg(afr, 0, 'f', 2));
    ui->rpmLabel->setText(QString("RPM: %1").arg(rpm, 0, 'f', 0));
    ui->tempLabel->setText(QString("Temp: %1°C").arg(temp, 0, 'f', 1));
    ui->tpsLabel->setText(QString("TPS: %1%").arg(tps, 0, 'f', 1));
    ui->mapLabel->setText(QString("MAP: %1 kPa").arg(map, 0, 'f', 1));
}
