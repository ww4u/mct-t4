#include "h2pref.h"
#include "ui_h2pref.h"

H2Pref::H2Pref(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2Pref)
{
    ui->setupUi(this);
}

H2Pref::~H2Pref()
{
    delete ui;
}
