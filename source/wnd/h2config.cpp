#include "h2config.h"
#include "ui_h2config.h"

#include "h2action.h"
#include "h2configuration.h"
#include "h2jogmode.h"
#include "h2homing.h"
//#include "h2measurement.h"

#define new_widget( type, name, title ) type *name = new type();\
                                        ui->stackedWidget->addWidget( name );\
                                        ui->listWidget->addItem( title );

H2Config::H2Config(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2Config)
{
    ui->setupUi(this);

    //! build data
    for ( int i = 0; i < 31; i++ )
    { mActions.insertRow( i ); }

    //! configuration
    new_widget( H2Configuration, pConfiguration , tr("Configuration") );

    //! Measurement
//    new_widget( H2Measurement, pMeasurement , tr("Measurements") );

    //! Homing
    new_widget( H2Homing, pHoming , tr("Homing") );

    //! jog mode
    new_widget( H2JogMode, pJogMode , tr("Jog Mode") );

    //! load data
    //! \todo

    //! action
    new_widget( H2Action, pAction, tr("Record Table") )
    pAction->setModel( &mActions );

    //! connect
    connect( ui->listWidget, SIGNAL(currentRowChanged(int)),
             ui->stackedWidget, SLOT(setCurrentIndex(int)));

}

H2Config::~H2Config()
{
    delete ui;
}
