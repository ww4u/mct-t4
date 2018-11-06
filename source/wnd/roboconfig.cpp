#include "roboconfig.h"
#include "ui_roboconfig.h"

#include "../include/mystd.h"

#include "h2robo.h"

RoboConfig::RoboConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoboConfig)
{
    ui->setupUi(this);

    m_pRootNode = new QTreeWidgetItem();
    m_pRootNode->setText( 0, tr("Project") );
    ui->treeWidget->addTopLevelItem( m_pRootNode );

    H2Robo *pRobo = new H2Robo( ui->stackedWidget );
    Q_ASSERT( NULL != pRobo );
    mRobos.append(  pRobo );

    m_pRootNode->addChild( pRobo->roboNode() );

    //! build connection
    connect( ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
             this, SLOT(slot_current_changed(QTreeWidgetItem*,QTreeWidgetItem*)));

}

RoboConfig::~RoboConfig()
{
    delete ui;

    delete_all( mRobos );
}

void RoboConfig::slotAddNewRobot( const QString &strIP)
{

}

int RoboConfig::open()
{
    //! \todo open the device
//    mHandle = vi

    //! attach

    return 0;
}
int RoboConfig::close()
{
    //! \todo close device

//    XConfig *pCfg;
//    for ( int i = 0; i < ui->stackedWidget->count(); i++ )
//    {
//        pCfg = (XConfig*)ui->stackedWidget->widget( i );
//        pCfg->detachHandle( mHandle );
//    }

    return 0;
}

int RoboConfig::setApply()
{
    return 0;
}

int RoboConfig::setReset()
{
    //! \todo for each prop

    return 0;
}
int RoboConfig::setOK()
{
    //! setApply


    //! close

    return 0;
}

void RoboConfig::on_buttonBox_clicked(QAbstractButton *button)
{
    Q_ASSERT( NULL != button );

    QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole( button );
    if ( QDialogButtonBox::ResetRole == role )
    {

    }
    else if ( QDialogButtonBox::AcceptRole == role )
    {

    }
    else if ( QDialogButtonBox::ApplyRole == role )
    {
        setApply();
    }
    else
    {}
}

void RoboConfig::slot_current_changed( QTreeWidgetItem* cur,QTreeWidgetItem* prv )
{
    if ( cur != NULL )
    {}
    else
    { return; }

    QVariant var;
    QObject *pObj;
    var = cur->data( 0, Qt::UserRole );
    if ( var.isValid() )
    {
        pObj = var.value<QObject*>();
        if ( NULL != pObj )
        {
            ui->stackedWidget->setCurrentWidget( (QWidget*)pObj );
        }
    }
}
