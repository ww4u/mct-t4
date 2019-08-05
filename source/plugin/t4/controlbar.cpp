#include "controlbar.h"
#include "ui_controlbar.h"

ControlBar::ControlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlBar)
{
    ui->setupUi(this);
}

ControlBar::~ControlBar()
{
    delete ui;
}

void ControlBar::on_HSlider_valueChanged(int value)
{
    ui->spinBox->setValue( value );
}

void ControlBar::on_spinBox_valueChanged(int arg1)
{
    ui->HSlider->setValue( arg1 );
}

double ControlBar::getSpeed()
{
    return ui->spinBox->value();
}

int ControlBar::stepIndex()
{
    return ui->comboBox->currentIndex();
}

void ControlBar::setSpeed( int iV )
{
    ui->HSlider->setValue( iV );
    ui->spinBox->setValue( iV );
}
void ControlBar::setCurrentIndex( int iIndex )
{
    ui->comboBox->setCurrentIndex( iIndex );
}
int ControlBar::count()
{
    return ui->comboBox->count();
}
QString ControlBar::combContent( int iIndex )
{
    return ui->comboBox->itemText( iIndex );
}
void ControlBar::setItemText( int i, QString str )
{
    ui->comboBox->setItemText( i, str );
}
