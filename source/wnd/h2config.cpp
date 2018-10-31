#include "h2config.h"
#include "ui_h2config.h"

#include "h2pref.h"
#include "h2zero.h"
#include "h2action.h"
#include "h2configuration.h"
#include "h2jogmode.h"
#include "h2homing.h"

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

    //! jog mode
    new_widget( H2JogMode, pJogMode , tr("Jog Mode") );

    //! jog mode
    new_widget( H2Homing, pHoming , tr("Homing") );


    //! load data
    //! \todo

    //! pref
    new_widget( H2Pref, pPref, tr("Pref") )

    //! zero
    new_widget( H2Zero, pZero, tr("Zero") )

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
