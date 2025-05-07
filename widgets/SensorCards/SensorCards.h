#pragma once

#include <QWidget>
#include <QLabel>

namespace Ui {
class SensorCards;
}

class SensorCards : public QWidget
{
    Q_OBJECT

public:
    explicit SensorCards(QWidget *parent = nullptr);
    ~SensorCards();

    void updateValues(double afr, double rpm, double temp, double tps, double map);

private:
    Ui::SensorCards *ui;
};