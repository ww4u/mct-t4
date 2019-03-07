#ifndef XPLUGINWORKINGTHREAD_H
#define XPLUGINWORKINGTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "xpage.h"

class WorkingApi : public QObject
{
    Q_OBJECT

public:
    enum eWorkingType
    {
        e_work_loop,
        e_work_single
    };

    enum eWorkingClass
    {
        e_work_emergency,
        e_work_mission,
        e_work_update,
    };
public:
    WorkingApi( QObject *parent = Q_NULLPTR );
    ~WorkingApi();

    void setType( WorkingApi::eWorkingType type );
    WorkingApi::eWorkingType getType();

    void setClass( WorkingApi::eWorkingClass cls );
    WorkingApi::eWorkingClass getClass();

public:
    eWorkingType mWorkingType;
    eWorkingClass mWorkingClass;

    XPage *m_pObj;
    void *m_pContext;
    XPage::preDo m_pPreDo;
    XPage::procDo m_pProcDo;
    XPage::postDo m_pPostDo;

    QVariant mVar;
    XPage::onMsg m_pOnMsg;
    XPage::isEnable m_pIsEnabled;

    QTimer *m_pTimer;
};

//Q_DECLARE_METATYPE( WorkingApi * )
//Q_DECLARE_METATYPE( WorkingApi )

class XPluginWorkingThread : public QThread
{
    Q_OBJECT
public:
    XPluginWorkingThread( QObject *parent =  Q_NULLPTR );
    virtual ~XPluginWorkingThread();

    void attachMutex( QMutex *pMutex );
Q_SIGNALS:
    void signal_enter_working( WorkingApi *api);
    void signal_exit_working( WorkingApi *api, int );

protected Q_SLOTS:
    void slot_api_proc( QObject *pApi );
    void slot_api_operate( QObject *pApi, bool b );

public:
    void attach( WorkingApi * pApi );
    void detach();

    void setTick( int ms );
    int tick();

protected:
    virtual void run();

protected:
    void procApi( WorkingApi *pApi );

protected:
    const int _tickms = 100;

    QList< WorkingApi *> mApis;

    int mTickms;

    QMutex mMutex;

    QMutex *m_pWorkMutex;
};

class XPluginUpdateingThread : public XPluginWorkingThread
{
    Q_OBJECT
public:
    XPluginUpdateingThread( QObject *parent =  Q_NULLPTR );
    virtual ~XPluginUpdateingThread();

protected:
    virtual void run();
};

#endif // XPLUGINWORKINGTHREAD_H
