#include "h2config.h"
#include "ui_h2config.h"

#include "h2action.h"
#include "h2configuration.h"

#include "h2jogmode.h"
#include "h2homing.h"
#include "h2measurement.h"

#include "h2errmgr.h"


#define new_widget( type, name, title, icon ) type *name = new type();\
                                        ui->stackedWidget->addWidget( name );\
                                        plwItem = new QListWidgetItem( QIcon(icon), title );\
                                        ui->listWidget->addItem( plwItem );

H2Config::H2Config(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2Config)
{
    ui->setupUi(this);

    //! build data
    for ( int i = 0; i < 31; i++ )
    { mActions.insertRow( i ); }


    //! load data
    //! \todo

    //! list item
    QListWidgetItem *plwItem;

    //! configuration
    new_widget( H2Configuration, pConfiguration , tr("Configuration"), ":/res/image/icon/205.png" );

    //! Measurement
    new_widget( H2Measurement, pMeasurement , tr("Measurements") , ":/res/image/icon/54.png");

    //! Homing
    new_widget( H2Homing, pHoming , tr("Homing") , ":/res/image/icon/address.png");

    //! jog mode
    new_widget( H2JogMode, pJogMode , tr("Jog Mode"), ":/res/image/icon/409.png" );

    //! action
    new_widget( H2Action, pAction, tr("Record Table"), ":/res/image/icon/activity.png" )
    pAction->setModel( &mActions );

    //! err mgr
    new_widget( H2ErrMgr, pErrMgr, tr("Error Management"), ":/res/image/icon/remind.png" );
    mErrManager.createDebug();
    pErrMgr->setModel( &mErrManager );

    //! connect
    connect( ui->listWidget, SIGNAL(currentRowChanged(int)),
             ui->stackedWidget, SLOT(setCurrentIndex(int)));

    //! for each
    XConfig *pCfg;
    for ( int i = 0; i < ui->stackedWidget->count(); i++ )
    {
        pCfg = (XConfig*)ui->stackedWidget->widget( i );
        if ( NULL != pCfg )
        {
            connect( pCfg, SIGNAL(signal_focus_in( const QString &)),
                     this, SIGNAL(signal_focus_in( const QString &)));
        }
    }
}

H2Config::~H2Config()
{
    delete ui;
}
