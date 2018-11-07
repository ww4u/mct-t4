#include "h2robo.h"

#include "h2product.h"
#include "h2configuration.h"
#include "h2jogmode.h"
#include "h2homing.h"
#include "h2measurement.h"
#include "h2action.h"
#include "h2errmgr.h"

#define new_widget( type, title, icon ) type *p_##type = new type();\
                                        Q_ASSERT( NULL != p_##type ); \
                                        plwItem = new QTreeWidgetItem();\
                                        Q_ASSERT( NULL != plwItem ); \
                                        plwItem->setText( 0, title ); \
                                        plwItem->setIcon( 0, QIcon( icon) ); \
                                        plwItem->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(p_##type) ) ); \
                                        m_pRoboNode->addChild(plwItem); \
                                        mSubConfigs.append( p_##type );\
                                        pWig->addWidget( p_##type );

H2Robo::H2Robo(QStackedWidget *pWig, QString strDevInfo, QObject *pObj ) : XRobo( pWig, pObj )
{
    Q_ASSERT( NULL != pWig );

    QStringList strListDev = strDevInfo.split(',', QString::SkipEmptyParts);
    QString strDeviceName;
    if(strListDev.count() == 0)
    {   return;     }
    if(strListDev.count() > 2)
    {   strDeviceName = strListDev.at(0) + "[" + strListDev.at(2) + "]";    }
    else
    {   strDeviceName = strListDev.at(0);    }

    XConfig *pConfig;
    QTreeWidgetItem *plwItem;

    //! roboNode
    pConfig = new H2Product(strDevInfo);
    Q_ASSERT( NULL != pConfig );
    mSubConfigs.append( pConfig );
    pWig->addWidget( pConfig );

    //! base
    m_pRoboNode = new QTreeWidgetItem();
    m_pRoboNode->setText( 0, strDeviceName );
    m_pRoboNode->setIcon( 0, QIcon( ":/res/image/icon/205.png" ) );
    m_pRoboNode->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(pConfig) ) );


    new_widget( H2Configuration, tr("Configuration"), ":/res/image/icon/205.png" );
    new_widget( H2Measurement, tr("Measurements") , ":/res/image/icon/54.png");
    new_widget( H2Homing, tr("Homing") , ":/res/image/icon/address.png");
    new_widget( H2JogMode, tr("Jog Mode"), ":/res/image/icon/409.png" );
    new_widget( H2Action, tr("Record Table"), ":/res/image/icon/activity.png" );
    new_widget( H2ErrMgr, tr("Error Management"), ":/res/image/icon/remind.png" );

    //! load data
    loadDataSet();

    //! apply data
    p_H2Action->setModel( &mActions );
    p_H2ErrMgr->setModel( &mErrManager );

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
    foreach( XConfig *pCfg, mSubConfigs )
    {
        Q_ASSERT( NULL != pCfg );

        connect( pCfg, SIGNAL(signal_focus_in( const QString &)),
                 this, SIGNAL(signal_focus_in( const QString &)));
    }
}
