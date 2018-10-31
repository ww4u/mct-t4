#include "h2config.h"
#include "ui_h2config.h"

#include "h2pref.h"
#include "h2zero.h"
#include "h2action.h"
#include "h2configuration.h"

#include "h2jogmode.h"
#include "h2homing.h"

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
    new_widget( H2Configuration, pConfiguration , tr("Configuration"), ":/res/image/icon/54.png" );

    //! jog mode
    new_widget( H2JogMode, pJogMode , tr("Jog Mode"), ":/res/image/icon/409.png" );

    //! jog mode
    new_widget( H2Homing, pHoming , tr("Homing"), ":/res/image/icon/address.png" );

    //! pref
    new_widget( H2Pref, pPref, tr("Pref"), ":/res/image/icon/205.png" )

    //! zero
    new_widget( H2Zero, pZero, tr("Zero"), ":/res/image/icon/address.png" )

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

}

H2Config::~H2Config()
{
    delete ui;
}
