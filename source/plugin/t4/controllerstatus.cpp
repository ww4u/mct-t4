#include "controllerstatus.h"
#include "ui_controllerstatus.h"

ControllerStatus::ControllerStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControllerStatus)
{
    ui->setupUi(this);
}

ControllerStatus::~ControllerStatus()
{
    delete ui;
}
