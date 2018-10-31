#include "h2measurement.h"
#include "ui_h2measurement.h"

H2Measurement::H2Measurement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2Measurement)
{
    ui->setupUi(this);
}

H2Measurement::~H2Measurement()
{
    delete ui;
}
