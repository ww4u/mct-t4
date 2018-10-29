#include "h2status.h"
#include "ui_h2status.h"

H2Status::H2Status(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2Status)
{
    ui->setupUi(this);
}

H2Status::~H2Status()
{
    delete ui;
}

void H2Status::on_chkMct_clicked()
{
    if ( ui->chkMct->isChecked() )
    {}
    else
    {
        ui->chkPwr->setChecked(false);
        ui->chkPwr->setCheckable( false );
    }
}
