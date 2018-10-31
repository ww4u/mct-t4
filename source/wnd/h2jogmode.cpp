#include "h2jogmode.h"
#include "ui_h2jogmode.h"

H2JogMode::H2JogMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2JogMode)
{
    ui->setupUi(this);
}

H2JogMode::~H2JogMode()
{
    delete ui;
}
