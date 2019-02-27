#include "t4.h"
#include <QTreeWidgetItem>

#include "t4oppanel.h"
#include "info.h"
#include "config.h"
#include "motorconfig.h"
#include "traceplot.h"
#include "actiontable.h"
#include "advpara.h"
#include "errormgrtable.h"
#include "coordinate.h"
#include "scripteditor.h"

MRX_T4::MRX_T4( QObject *parent ) : XPlugin( parent )
{
    mRobotHandle = -1;

    m_pReccordTable = NULL;
    m_pRootWidgetItem = NULL;
}

//! role: page
//! role+1: plugin

#define new_widget( type, var, txt, icon ) \
do{ \
    var = new type;\
    Q_ASSERT( NULL != var ); \
    var->adapteToUserMode(sysMode());\
    var->attachPlugin( this );\
    var->attachWorkings(); \
    var->setObjectName( txt );\
    \
    QTreeWidgetItem *plwItem = new QTreeWidgetItem();   \
    Q_ASSERT( NULL != plwItem ); \
    plwItem->setIcon( 0, QIcon( icon) ); \
    plwItem->setText( 0, tr(txt) ); \
    plwItem->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(var) ) ); \
    plwItem->setData( 0, Qt::UserRole + 1, QVariant( QVariant::fromValue(this) ) ); \
    pRoot->addChild(plwItem); \
    stack->addWidget( var );     \
    mPluginWidgets.append( var ); \
}while(0)

#define new_root_widget( type, var, txt, icon, root ) \
do{ \
    var = new type;\
    Q_ASSERT( NULL != var ); \
    var->adapteToUserMode(sysMode());\
    var->attachPlugin( this );\
    var->attachWorkings(); \
    var->setObjectName( txt );\
    \
    \
    root->setIcon( 0, QIcon( icon) ); \
    root->setText( 0, tr(txt) ); \
    root->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(var) ) ); \
    stack->addWidget( var );     \
    mPluginWidgets.append( var ); \
}while(0)

QTreeWidgetItem* MRX_T4::createPrefPages( QStackedWidget *stack )
{
    m_pRootWidgetItem = new QTreeWidgetItem();
    QTreeWidgetItem *pRoot;
    pRoot = m_pRootWidgetItem;
//    pRoot->setText( 0, "MRX-T4" );
    //! attach user role
    m_pRootWidgetItem->setData( 0, Qt::UserRole+1, QVariant::fromValue( this ) );

    XPage *pWig;

//    mrx_t4::ActionTable *pRecordTable;
    mrx_t4::ErrorMgrTable *pErrCfgTable;

    new_root_widget( mrx_t4::Info, pWig, "MRX-T4", ":/res/image/icon/205.png", m_pRootWidgetItem );
    new_widget( mrx_t4::Config, pWig, "Configuration", ":/res/image/icon/205.png" );
    new_widget( mrx_t4::AdvPara, pWig, "Misc", ":/res/image/icon/205.png" );
    new_widget( mrx_t4::Coordinate, pWig, "Coordinate", ":/res/image/icon/205.png" );
    new_widget( mrx_t4::MotorConfig, pWig, "Motor", ":/res/image/icon/205.png" );
    new_widget( mrx_t4::ActionTable, m_pReccordTable, "Record Table", ":/res/image/icon/activity.png" );
    new_widget( mrx_t4::ErrorMgrTable, pErrCfgTable, "Error Management", ":/res/image/icon/205.png" );
//    new_widget( mrx_t4::TracePlot, pWig, "Trace", ":/res/image/icon/409.png" );logDbg();
//    new_widget( mrx_t4::ScriptEditor, pWig, "Script", ":/res/image/icon/activity.png" );logDbg();

    //! recordtable
//    mRecordTable.createDebug();
//    mErrorConfigTable.createDebug();

    //! default
    QByteArray ary;
    ErrorMgrTable(ary);
    mErrorConfigTable.load( ary );

    //! attach model
    m_pReccordTable->setModel( &mRecordTable );
    pErrCfgTable->setModel( &mErrorConfigTable );

    return pRoot;
}
QWidget *MRX_T4::createOpsPanel( QAbstractListModel *pModel,
                                 QWidget *parent )
{
    mrx_t4::T4OpPanel *pPanel;

    pPanel = new mrx_t4::T4OpPanel( pModel, parent );
    Q_ASSERT( NULL != pPanel );
    pPanel->setObjectName( "panel" );

    //! manage the plugin
    mPluginWidgets.append( pPanel );

    pPanel->attachPlugin( this );
    pPanel->attachWorkings();

    return pPanel;
}

const char _meta_tables[]=
{
    #include "./dataset/errmgr_default.cpp"
};
void MRX_T4::ErrorMgrTable( QByteArray &ary )
{
    ary.setRawData( _meta_tables, sizeof( _meta_tables )/sizeof( _meta_tables[0] ) );
}

void MRX_T4::onSetting(XSetting setting)
{
    if ( setting.mSetting == XPage::e_setting_opened )
    {
        if ( setting.mPara1.isValid() )
        {}
        else
        { return; }

        Q_ASSERT( NULL != m_pRootWidgetItem );
        if ( setting.mPara1.toBool() )
        { m_pRootWidgetItem->setIcon( 0, QIcon(":/res/image/icon/guanlianshebei.png") );}
        else
        { m_pRootWidgetItem->setIcon( 0, QIcon(":/res/image/icon/tupianjiazaishibai.png") );}
    }
}
