#include "xpluginworkingthread.h"

WorkingApi::WorkingApi()
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
{}

XPluginWorkingThread::~XPluginWorkingThread()
{
    delete_all( mApis );
}

void XPluginWorkingThread::attachMutex( QMutex *pMutex )
{
    Q_ASSERT( NULL != pMutex );

    m_pWorkMutex = pMutex;
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

                //! \note delete
            emit signal_exit_working( pApi, ret );

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

            QThread::msleep( XPluginWorkingThread::_tickms );
        }
    }
}
