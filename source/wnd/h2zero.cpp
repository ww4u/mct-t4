#include "h2zero.h"
#include "ui_h2zero.h"

H2Zero::H2Zero(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2Zero)
{
    ui->setupUi(this);
}

H2Zero::~H2Zero()
{
    delete ui;
}
