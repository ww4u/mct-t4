#include "h2pref.h"
#include "ui_h2pref.h"

H2Pref::H2Pref(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Pref)
{
    ui->setupUi(this);

    setName( "pref" );
}

H2Pref::~H2Pref()
{
    delete ui;
}
