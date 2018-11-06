#include "h2jogmode.h"
#include "ui_h2jogmode.h"

H2JogMode::H2JogMode(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2JogMode)
{
    ui->setupUi(this);

    setName( "jog" );
}

H2JogMode::~H2JogMode()
{
    delete ui;
}

int H2JogMode::setApply(ViSession vi)
{
    qDebug() << "H2JogMode:" << vi;
    return 0;
}
