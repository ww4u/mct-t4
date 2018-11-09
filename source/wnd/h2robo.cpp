#include "h2robo.h"

#define new_widget( type, var, title, icon ) do{\
    var = new type;\
    Q_ASSERT( NULL != var ); \
    QTreeWidgetItem *plwItem = new QTreeWidgetItem();\
    Q_ASSERT( NULL != plwItem ); \
    plwItem->setText( 0, title ); \
    plwItem->setIcon( 0, QIcon( icon) ); \
    plwItem->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(var) ) ); \
    m_pRoboNode->addChild(plwItem); \
    mSubConfigs.append( var );\
    pWig->addWidget( var ); \
}while(0)

H2Robo::H2Robo(QStackedWidget *pWig, QString strDevInfo, QObject *pObj ) : XRobo( pWig, pObj )
{
    Q_ASSERT( NULL != pWig );
    QStringList strListDev = strDevInfo.split(',', QString::SkipEmptyParts);
    QString strDeviceName;
    if(strListDev.count() == 0)
    {   return;     }
    if(strListDev.count() > 2)
    {   strDeviceName = strListDev.at(2) + "[" + strListDev.at(0) + "]";    }
    else
    {   strDeviceName = strListDev.at(0);    }

    //! roboNode
    m_pProduct = new H2Product(strDevInfo);
    Q_ASSERT( NULL != m_pProduct );
    m_pRoboNode = new QTreeWidgetItem();
    m_pRoboNode->setText( 0, strDeviceName );
    m_pRoboNode->setIcon( 0, QIcon( ":/res/image/icon/201.png" ) );
    m_pRoboNode->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(m_pProduct) ) );
    mSubConfigs.append( m_pProduct );
    pWig->addWidget( m_pProduct );

    new_widget( H2Configuration, m_pH2Configuration, tr("Configuration"), ":/res/image/icon/205.png" );
    new_widget( H2Measurement, m_pH2Measurement, tr("Measurements") , ":/res/image/icon/54.png");
    new_widget( H2Homing, m_pH2Homing, tr("Homing") , ":/res/image/icon/address.png");
    new_widget( H2JogMode, m_pH2JogMode, tr("Jog Mode"), ":/res/image/icon/409.png" );
    new_widget( H2Action, m_pH2Action, tr("Record Table"), ":/res/image/icon/activity.png" );
    new_widget( H2ErrMgr, m_pH2ErrMgr, tr("Error Management"), ":/res/image/icon/remind.png" );

    //! load data
    loadDataSet();

    //! apply data
    m_pH2Action->setModel( &mActions );
    m_pH2ErrMgr->setModel( &mErrManager );

    //! connection
    buildConnection();
}

QTreeWidgetItem *H2Robo::roboNode()
{ return m_pRoboNode; }

int H2Robo::loadDataSet()
{
    int ret;

    //! load action
    ret = mActions.input( QApplication::applicationDirPath() + "/dataset/mrx-h2_action.csv");
    if ( ret != 0 )
    { return ret; }

    //! load event
    //!
    ret = mErrManager.load( QApplication::applicationDirPath() + "/dataset/mrx-h2_errmgr.xml");
    if ( ret != 0 )
    { return ret; }

    return 0;
}

void H2Robo::buildConnection()
{
    connect(m_pProduct,SIGNAL(signal_online_clicked(QString)),this,SIGNAL(signal_online_request(QString)));

    connect(m_pH2Measurement,SIGNAL(signal_AxesZeroPoint_currentTextChanged(QString)),
            m_pH2Homing,SLOT(slot_set_direction(QString)));

    foreach( XConfig *pCfg, mSubConfigs )
    {
        Q_ASSERT( NULL != pCfg );
        connect( pCfg, SIGNAL(signal_focus_in( const QString &)),
                 this, SIGNAL(signal_focus_in( const QString &)));
    }
}

QList<XConfig *> H2Robo::subConfigs() const
{
    return mSubConfigs;
}
