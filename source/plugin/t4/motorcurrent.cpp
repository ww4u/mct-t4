#include "motorcurrent.h"
#include "ui_motorcurrent.h"

MotorCurrent::MotorCurrent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorCurrent)
{
    ui->setupUi(this);
}

MotorCurrent::~MotorCurrent()
{
    delete ui;
}

void MotorCurrent::setData( double dC, double iC, double sT )
{
    ui->spinDriver->setValue( dC );
    ui->spinIdle->setValue( iC );
    ui->spinSwitchTime->setValue( sT );
}
void MotorCurrent::getData( double &dC, double &iC, double &sT )
{
    dC = ui->spinDriver->value();
    iC = ui->spinIdle->value();
    sT = ui->spinSwitchTime->value();
}

QDoubleSpinBox *MotorCurrent::doubleSpinCurrent()
{ return ui->spinDriver; }
QDoubleSpinBox *MotorCurrent::doubleSpinIdleCurrent()
{ return ui->spinIdle; }
QDoubleSpinBox *MotorCurrent::doubleSpinSwitchTime()
{ return ui->spinSwitchTime; }
