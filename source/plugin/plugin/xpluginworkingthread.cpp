#include "xpluginworkingthread.h"

WorkingApi::WorkingApi( QObject *parent ) : QObject( parent )
{
    mWorkingType = e_work_loop;
    mWorkingClass = e_work_mission;

    m_pObj = NULL;
    m_pContext = NULL;

    m_pPreDo = NULL;
    m_pProcDo = NULL;
    m_pPostDo = NULL;

    m_pOnMsg = NULL;
    m_pIsEnabled = NULL;

    m_pTimer = NULL;
}

WorkingApi::~WorkingApi()
{
    if ( NULL != m_pTimer )
    { delete m_pTimer; }
}

void WorkingApi::setType( WorkingApi::eWorkingType type )
{ mWorkingType = type; }
WorkingApi::eWorkingType WorkingApi::getType()
{ return mWorkingType; }

void WorkingApi::setClass( WorkingApi::eWorkingClass cls )
{ mWorkingClass = cls; }
WorkingApi::eWorkingClass WorkingApi::getClass()
{ return mWorkingClass; }

XPluginWorkingThread::XPluginWorkingThread( QObject *parent ) : QThread( parent )
{
    m_pWorkMutex = NULL;

    mTickms = 100;
}

XPluginWorkingThread::~XPluginWorkingThread()
{
    delete_all( mApis );
}

void XPluginWorkingThread::attachMutex( QMutex *pMutex )
{
    Q_ASSERT( NULL != pMutex );

    m_pWorkMutex = pMutex;
    logDbg()<<m_pWorkMutex;
}

void XPluginWorkingThread::slot_api_proc( QObject *pApi )
{
    Q_ASSERT( NULL != pApi );

    procApi( (WorkingApi*)pApi );
}

void XPluginWorkingThread::slot_api_operate( QObject *pApi, bool b )
{
    Q_ASSERT( NULL != pApi );

    WorkingApi *pWorkingApi;

    pWorkingApi = (WorkingApi*)pApi;
    Q_ASSERT( NULL != pWorkingApi && NULL != pWorkingApi->m_pTimer );
    if ( b )
    {
        pWorkingApi->m_pTimer->start();
    }
    else
    { pWorkingApi->m_pTimer->stop(); }
}

void XPluginWorkingThread::attach( WorkingApi * pApi )
{
    Q_ASSERT( NULL != pApi );

    mMutex.lock();

    mApis.append( pApi );

    mMutex.unlock();
}
void XPluginWorkingThread::detach()
{
    mMutex.lock();

    //! \todo api

    mMutex.unlock();
}

void XPluginWorkingThread::setTick( int ms )
{ mTickms = ms; }
int XPluginWorkingThread::tick()
{ return mTickms; }

void XPluginWorkingThread::run()
{
    forever
    {
        if ( isInterruptionRequested() )
        { break; }

        if ( mApis.size() < 1 )
        {
            QThread::msleep( XPluginWorkingThread::_tickms);
            continue;
        }

        //! proc
        int ret;
        foreach( WorkingApi *pApi, mApis )
        {
            Q_ASSERT( NULL != pApi );
            Q_ASSERT( NULL != pApi->m_pObj );

            procApi( pApi );

            //! remove
            if ( pApi->mWorkingType == WorkingApi::e_work_loop )
            {  }
            else
            {
                delete pApi;
                mMutex.lock();
                mApis.removeAll( pApi );
                mMutex.unlock();
            }

//            mMutex.unlock();
            if ( mTickms > 0 )
            { QThread::msleep( mTickms ); }
        }
    }

    qDeleteAll( mApis );
    logDbg();
}

void XPluginWorkingThread::procApi( WorkingApi *pApi )
{
    Q_ASSERT( NULL != pApi );
    int ret;

    emit signal_enter_working( pApi );

        do
        {
            //! enabled
            if ( pApi->m_pIsEnabled &&
                 !(pApi->m_pObj->*(pApi->m_pIsEnabled))( pApi->m_pContext ) )
            { break; }
            else
            {  }

            if ( NULL != m_pWorkMutex  )
            { m_pWorkMutex->lock(); }

            if ( pApi->m_pPreDo )
            {  (pApi->m_pObj->*(pApi->m_pPreDo))( pApi->m_pContext ); }

            //! call the api
            if ( pApi->m_pProcDo )
            {  ret = (pApi->m_pObj->*(pApi->m_pProcDo))( pApi->m_pContext ); }
            else
            { ret = 0; }

            //! msg api
            if ( pApi->m_pOnMsg )
            { ret = (pApi->m_pObj->*(pApi->m_pOnMsg))( pApi->mVar ); }

            if ( pApi->m_pPostDo )
            {  (pApi->m_pObj->*(pApi->m_pPostDo))( pApi->m_pContext, ret ); }

            if ( NULL != m_pWorkMutex )
            { m_pWorkMutex->unlock(); }

        }while( 0 );

        //! \note delete in this thread
        //! alert to be used in slot
    emit signal_exit_working( pApi, ret );
}

XPluginUpdateingThread::XPluginUpdateingThread( QObject *parent )
                        : XPluginWorkingThread(parent)
{}

XPluginUpdateingThread::~XPluginUpdateingThread()
{}

void XPluginUpdateingThread::run()
{
    QThread::run();
    qDeleteAll( mApis );
    logDbg();
}
