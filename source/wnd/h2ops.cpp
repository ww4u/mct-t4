#include "h2ops.h"
#include "ui_h2ops.h"

H2Ops::H2Ops(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2Ops)
{
    ui->setupUi(this);
}

H2Ops::~H2Ops()
{
    delete ui;
}
