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

    m_pRecordModel = NULL;
    m_pRecordView = NULL;
}

MRX_T4::~MRX_T4()
{
    delete m_pRecordModel;
}

//! role: page
//! role+1: plugin

QTreeWidgetItem* MRX_T4::createPrefPages( QStackedWidget *stack )
{
    //! root
    m_pRootWidgetItem = new QTreeWidgetItem();
    QTreeWidgetItem *pRoot;
    pRoot = m_pRootWidgetItem;
    mTreeItems.append( m_pRootWidgetItem );

    //! attach user role
    m_pRootWidgetItem->setData( 0, Qt::UserRole+1, QVariant::fromValue( this ) );
    //! identify the root
    m_pRootWidgetItem->setData( 0, Qt::UserRole+2, true );

    //! pages
    XPage *pWig;
    mrx_t4::ErrorMgrTable *pErrCfgTable;

    new_root_widget( mrx_t4::Info, pWig, tr("MRX-T4"), ":/res/image/icon/205.png", m_pRootWidgetItem );
    new_widget( mrx_t4::Config, pWig, tr("Configuration"), ":/res/image/icon/config.png" );
    new_widget( mrx_t4::AdvPara, pWig, tr("Misc"), ":/res/image/icon/qita.png" );
//    new_widget( mrx_t4::Coordinate, pWig, tr("Coordinate"), ":/res/image/icon/205.png" );
    new_widget( mrx_t4::MotorConfig, pWig, tr("Motor"), ":/res/image/icon/motor.png" );
    new_widget( mrx_t4::ActionTable, m_pRecordView, tr("Record Table"), ":/res/image/icon/table.png" );
    new_widget( mrx_t4::ErrorMgrTable, pErrCfgTable, tr("Error Management"), ":/res/image/icon/ErrorSetting.png" );
//    new_widget( mrx_t4::TracePlot, pWig, tr("Trace"), ":/res/image/icon/409.png" );logDbg();
//    new_widget( mrx_t4::ScriptEditor, pWig, tr("Script"), ":/res/image/icon/activity.png" );logDbg();

    //! default
    QByteArray ary;
    ErrorMgrTable(ary);
    mErrorConfigTable.load( ary );

    //! record table
    QStringList headerList;
    headerList<<"id"<<"type"
              //<<"coordinate"<<"para."
              <<"x(mm)"<<"y(mm)"<<"z(mm)"
              <<QString("w(%1)").arg(char_deg)<<QString("h(%1)").arg( char_deg )
              <<QString("v(%)")<<("Line")<<"Delay(s)"
              <<"comment";

//    headerList<<"id"<<"type"<<"coord";

    m_pRecordModel = new TreeModel( headerList,"" );
    m_pRecordModel->setColumnReadonly( 0 );
#ifndef QT_DEBUG
    rstRecordTable();
#else
    m_pRecordModel->loadIn("G:/work/mct/doc/template2.mrp");
#endif

    //! attach model
    m_pRecordView->setModel( m_pRecordModel );
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

    pPanel->attachPref( m_pPref );

    pPanel->attachPlugin( this );
    pPanel->attachWorkings();


    return pPanel;
}
void MRX_T4::retranslateUi()
{logDbg();
    mTreeItems.at(0)->setText( 0, tr("MRX-T4") ) ;
    mTreeItems.at(1)->setText( 0, tr("Configuration") ) ;
    mTreeItems.at(2)->setText( 0, tr("Misc") ) ;
    mTreeItems.at(3)->setText( 0, tr("Motor") ) ;
    mTreeItems.at(4)->setText( 0, tr("Record Table") ) ;
    mTreeItems.at(5)->setText( 0, tr("Error Management") ) ;
}
//! mgr table
void MRX_T4::rstErrorMgrTable()
{
    QByteArray ary;
    ErrorMgrTable(ary);
    mErrorConfigTable.load( ary );
}
void MRX_T4::rstRecordTable()
{
    QByteArray ary;
    RecordData( ary );

    QTextStream stream( ary );
    m_pRecordModel->loadIn( stream );
}

const char _meta_tables[]=
{
    #include "./dataset/errmgr_default.cpp"
};
void MRX_T4::ErrorMgrTable( QByteArray &ary )
{
    ary.clear();
    ary.setRawData( _meta_tables, sizeof( _meta_tables )/sizeof( _meta_tables[0] ) );
}

const char _record_datas[]=
{
    #include "./dataset/template_raw.cpp"
};
void MRX_T4::RecordData( QByteArray &ary )
{
    //! \todo
    ary.clear();
    ary.setRawData( _record_datas, sizeof( _record_datas )/sizeof( _record_datas[0] ) );
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
        { m_pRootWidgetItem->setIcon( 0, QIcon(":/res/image/h2product/connect.png") );}
        else
        { m_pRootWidgetItem->setIcon( 0, QIcon(":/res/image/h2product/disconnect.png") );}
    }
}
