#include "joint.h"
#include "ui_joint.h"
#include "../../../include/mydef.h"
Joint::Joint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Joint)
{
    ui->setupUi(this);

    //! delta
    ui->label_2->setText( QChar(0x2206) );
    ui->spinAbs->setSuffix( char_deg );
    ui->spinDelta->setSuffix( char_deg );

    //! build connection
    //! single
    connect( ui->singleSub, SIGNAL(clicked(bool)),
             this, SIGNAL( signal_single_sub_clicked() ) );
    connect( ui->singleAdd, SIGNAL(clicked(bool)),
             this, SIGNAL( signal_single_add_clicked() ) );

    connect( ui->singleSub, SIGNAL(pressed()),
             this, SIGNAL( signal_single_sub_pressed() ) );
    connect( ui->singleAdd, SIGNAL(pressed()),
             this, SIGNAL( signal_single_add_pressed() ) );

    connect( ui->singleSub, SIGNAL(released()),
             this, SIGNAL( signal_single_sub_released() ) );
    connect( ui->singleAdd, SIGNAL(released()),
             this, SIGNAL( signal_single_add_released() ) );

    //! zero
    connect( ui->btnZero, SIGNAL(clicked(bool)),
             this, SIGNAL(signal_zero_clicked()));

    //！ enable
    ui->btnZero->setEnabled(true);
}

Joint::~Joint()
{
    delete ui;
}

void Joint::setJointName( const QString &name )
{
    ui->label->setText( name );
    ui->btnZero->setToolTip( ui->groupBox->title() + " " + tr("To zero") );
    ui->singleAdd->setToolTip( name + " " + tr("Step +") );
    ui->singleSub->setToolTip( name + " " + tr("Step -") );

    ui->spinAbs->setToolTip( name + " " + tr("Encoder angle") );
    ui-> spinDelta->setToolTip( name + " " + tr("Delta angle") );
}

void Joint::setAngleVisible( bool bAbs, bool bDelta )
{
    ui->spinAbs->setVisible( bAbs );
    ui->spinDelta->setVisible( bDelta );
    ui->label_2->setVisible( bDelta );
}

void Joint::setAngle( double angle )
{ ui->spinAbs->setValue(angle); }
double Joint::getAngle()
{ return ui->spinAbs->value(); }

void Joint::setdAngle( double v )
{ ui->spinDelta->setValue( v); }
double Joint::getdAngle()
{ return ui->spinDelta->value(); }

