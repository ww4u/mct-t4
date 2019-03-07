#include "xplugin.h"
#include "../../../include/mystd.h"
#include "xpluginworkingthread.h"

XPlugin::XPlugin( QObject *parent ) : XPluginIntf( parent )
{
    m_pRootWidgetItem = NULL;
    m_pDock = NULL;
    m_pPanelWidget = NULL;
    m_pViewObj = NULL;

    //! updateing
    m_pUpdateWorking = new XPluginUpdateingThread( this );
    m_pUpdateWorking->attachMutex( &mUpdateMutex );
    m_pUpdateWorking->start();

    m_pMissionWorking = new XPluginWorkingThread( this );
    m_pMissionWorking->attachMutex( &mMissionMutex );
    m_pMissionWorking->start();

    m_pEmergencyWorking = new XPluginWorkingThread( this );
    m_pEmergencyWorking->attachMutex( &mEmergMutex );
    m_pEmergencyWorking->start();

    m_pBgWorking = new XPluginBgThread( this, this );
    m_pBgWorking->start();

    connect( this, SIGNAL(signal_request_load()),
             this, SLOT(slot_load_setting()) );

    connect( this, SIGNAL(signal_setting_changed(XSetting)),
             this, SLOT(slot_plugin_setting_changed(XSetting)));

    //! signal
    connect( this, SIGNAL(signal_api_operate(QObject*,bool)),
             m_pUpdateWorking, SLOT(slot_api_operate(QObject*,bool)));

    //! maped object
    connect( &mMapper, SIGNAL(mapped(QObject*)),
             m_pUpdateWorking, SLOT(slot_api_proc(QObject*)) );
}

XPlugin::~XPlugin()
{
//    m_pUpdateWorking->requestInterruption();
    m_pUpdateWorking->quit( );
    m_pUpdateWorking->wait();

    m_pMissionWorking->requestInterruption();
    m_pMissionWorking->wait();

    m_pEmergencyWorking->requestInterruption();
    m_pEmergencyWorking->wait();

    m_pBgWorking->requestInterruption();
    m_pBgWorking->wait();

    //! delete the plugins widgets
    foreach( QWidget *pWidget, mPluginWidgets )
    {
        pWidget->close();
        delete pWidget;
    }

    close();
}

QTreeWidgetItem* XPlugin::createPrefPages( QStackedWidget *stack )
{ return NULL; }
QWidget *XPlugin::createOpsPanel( QAbstractListModel *pModel,
                                  QWidget *parent )
{ return NULL; }

void XPlugin::setActive( )
{
    Q_ASSERT( NULL != m_pDock && NULL != m_pPanelWidget );

    m_pDock->setWidget( m_pPanelWidget );
}

void XPlugin::rstErrorMgrTable()
{}
void XPlugin::rstRecordTable()
{}

//void XPlugin::ErrorMgrTable( QByteArray &ary )
//{}
//void XPlugin::RecordTable( QByteArray &ary )
//{}
void XPlugin::onOperateAble( bool b )
{
    emit_setting_changed( XPage::e_setting_op_able, b );
}

int XPlugin::save( const QString &fileName )
{
    QFile file( fileName );
    if ( file.open( QIODevice::WriteOnly ) )
    {}
    else
    { return -1; }

    QXmlStreamWriter writer( &file );

    writer.writeStartDocument();

    writer.writeStartElement("config");

        writer.writeStartElement("intf");
            XPluginIntf::save( writer );
        writer.writeEndElement();

        writer.writeStartElement("setup");
            serialOut( writer );
        writer.writeEndElement();

    writer.writeEndElement();

    writer.writeEndDocument();

    file.close();

    return 0;
}
int XPlugin::load( const QString &fileName )
{
    QFile file( fileName );
    if ( file.open( QIODevice::ReadOnly ) )
    {}
    else
    { return -1; }

    QXmlStreamReader reader( &file );

    while( reader.readNextStartElement() )
    {
        if ( reader.name() == "config" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "intf" )
                {
                    XPluginIntf::load( reader );
                }
                else if ( reader.name() == "setup" )
                {
                    serialIn( reader );
                }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else
        { reader.skipCurrentElement(); }
    }

    file.close();

    return 0;
}

int XPlugin::serialOut( QXmlStreamWriter &writer )
{ return 0; }
int XPlugin::serialIn( QXmlStreamReader &reader )
{ return 0; }

bool XPlugin::isEnabled( void *context )
{ return isOpened(); }

void XPlugin::onSetting( XSetting setting )
{}

void XPlugin::updateUi()
{
    XPage *pPage;
    foreach( QWidget *pWidget, mPluginWidgets )
    {
        Q_ASSERT( NULL != pWidget );
        pPage = dynamic_cast<XPage*>( pWidget );
        if ( NULL != pPage )
        { pPage->updateUi(); }
    }
}

void XPlugin::rst()
{}

int XPlugin::upload()
{ return 0; }
int XPlugin::download()
{ return 0; }
int XPlugin::diff()
{ return 0; }

void XPlugin::emit_setting_changed( XPage::eXSetting setting, bool b )
{
    XSetting lSetting;

    lSetting.mSetting = setting;
    lSetting.mPara1.setValue( b );
    emit signal_setting_changed( lSetting );
}

void XPlugin::emit_setting_changed( XPage::eXSetting setting, QVariant var )
{
    XSetting lSetting;

    lSetting.mSetting = setting;
    lSetting.mPara1 = var;
    emit signal_setting_changed( lSetting );
}

void XPlugin::emit_save()
{ emit signal_request_save(); }
void XPlugin::emit_load()
{ emit signal_request_load(); }

void XPlugin::setViewObj( void *pObj )
{
    Q_ASSERT( NULL != pObj );
    m_pViewObj = pObj;
}
void *XPlugin::viewObj()
{ return m_pViewObj; }

void XPlugin::attachDock( QDockWidget *pDock )
{
    Q_ASSERT( NULL != pDock );

    m_pDock = pDock;
}
void XPlugin::attachPanel( QWidget *pPanel )
{
    Q_ASSERT( NULL != pPanel );
    m_pPanelWidget = pPanel;
}
QWidget *XPlugin::panel()
{
    return m_pPanelWidget;
}

QString XPlugin::homePath()
{
    return QDir::homePath() + "/AppData/Roaming/mct/" + model() + "/" + SN();
}

void XPlugin::lockWorking()
{
    mEmergMutex.lock();
    mMissionMutex.lock();
    mUpdateMutex.lock();
}
void XPlugin::unlockWorking()
{
    mEmergMutex.unlock();
    mMissionMutex.unlock();
    mUpdateMutex.unlock();
}

void XPlugin::attachUpdateWorking( XPage *pObj,
                             XPage::procDo proc,
                             void *pContext,
                             int tmoms
                    )
{
    Q_ASSERT( NULL != pObj );

    attachUpdateWorking( pObj, proc, NULL, NULL, pContext, tmoms );

//    WorkingApi *pApi = new WorkingApi();
//    if ( NULL == pApi )
//    { return; }

//    pApi->m_pIsEnabled = isEnabled;

//    pApi->m_pProcDo = proc;
//    pApi->m_pContext = pContext;
//    pApi->m_pObj = pObj;

//    Q_ASSERT( m_pUpdateWorking );
//    m_pUpdateWorking->attach( pApi );
}
void XPlugin::attachUpdateWorking(
                    XPage *pObj,
                    XPage::procDo proc,
                    XPage::preDo pre,
                    XPage::postDo post,
                    void *pContext,
                    int tmoms
                    )
{
    Q_ASSERT( NULL != pObj );

    WorkingApi *pApi = new WorkingApi();
    if ( NULL == pApi )
    { return; }

    pApi->m_pIsEnabled = isEnabled;

    pApi->m_pProcDo = proc;
    pApi->m_pContext = pContext;
    pApi->m_pObj = pObj;

    pApi->m_pPreDo = pre;
    pApi->m_pPostDo = post;

    do
    {
        //! tmo
        Q_ASSERT( m_pUpdateWorking );
        if ( tmoms > 0 )
        {
            //! in the update working thread
            QTimer *pTimer = new QTimer( m_pUpdateWorking );
            if ( NULL == pTimer )
            { break; }

            pApi->m_pTimer = pTimer;
            pTimer->setInterval( tmoms );

            //! connect
//            connect( pTimer, SIGNAL(timeout()),
//                     m_pUpdateWorking, SLOT())
//            connect( pTimer, SIGNAL(timeout()),
//                     m_pUpdateWorking,  [=]{ slot_api_proc( pApi); } );

            //! mapped
            connect( pTimer, SIGNAL(timeout()),
                     &mMapper, SLOT(map()));
            mMapper.setMapping( pTimer, pApi );

            //! enable
            emit signal_api_operate( pApi, true );
        }

//        m_pUpdateWorking->attach( pApi );

        return;
    }while( 0 );

    delete pApi;
}

void XPlugin::attachMissionWorking( XPage *pObj,
                    XPage::onMsg onmsg,
                    QVariant var
                    )
{
    Q_ASSERT( NULL != pObj );

    WorkingApi *pApi = new WorkingApi();
    if ( NULL == pApi )
    { return; }

    pApi->m_pObj = pObj;

    pApi->m_pIsEnabled = isEnabled;

    pApi->m_pOnMsg = onmsg;
    pApi->mVar = var;

    pApi->setType( WorkingApi::e_work_single );

    Q_ASSERT( m_pMissionWorking!=NULL );
    m_pMissionWorking->attach( pApi );
}

void XPlugin::attachEmergencyWorking( XPage *pObj,
                    XPage::onMsg onmsg,
                    QVariant var
                    )
{
    Q_ASSERT( NULL != pObj );

    WorkingApi *pApi = new WorkingApi();
    if ( NULL == pApi )
    { return; }

    pApi->m_pObj = pObj;

    pApi->m_pIsEnabled = isEnabled;

    pApi->m_pOnMsg = onmsg;
    pApi->mVar = var;

    pApi->setType( WorkingApi::e_work_single );

    Q_ASSERT( m_pEmergencyWorking );
    m_pEmergencyWorking->attach( pApi );
}

void XPlugin::attachBgWorking(
                    XPlugin::bgProc proc
                    )
{
    Q_ASSERT( NULL != m_pBgWorking );
    m_pBgWorking->attachBgProc( proc );
}

void XPlugin::cancelBgWorking()
{
    Q_ASSERT( NULL != m_pBgWorking );
    m_pBgWorking->requestInterruption();
    m_pBgWorking->wait();
}

void XPlugin::slot_save_setting()
{
}

void XPlugin::slot_load_setting()
{ updateUi(); }

void XPlugin::slot_plugin_setting_changed( XSetting setting )
{
//    do
//    {
//        //! sys setting
//        if ( (int)setting.mSetting < (int)e_setting_user )
//        { break; }

//        //! not in filter
//        if ( filterSetting( setting ) )
//        { return; }

//    }while( 0 );

    onSetting( setting );
}

XPluginBgThread::XPluginBgThread( XPlugin *plugin, QObject *parent ) :QThread(parent),m_pPlugin(plugin)
{}

void XPluginBgThread::run()
{
    XPlugin::bgProc proc;
    int ret;

    while( !mApis.isEmpty() )
    {
        if ( isInterruptionRequested() )
        { break; }

        proc = mApis.dequeue();

        ret = (m_pPlugin->*proc)();
    }
}

void XPluginBgThread::attachBgProc( XPlugin::bgProc proc )
{
    mMutex.lock();
        mApis.enqueue( proc );
    mMutex.unlock();

    if ( isRunning() )
    {}
    else
    { start(); }
}
