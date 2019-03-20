#ifndef XPLUGIN_H
#define XPLUGIN_H

#include <QObject>
#include <QStackedWidget>
#include <QTreeWidgetItem>
#include <QDockWidget>
#include <QThread>

#include "../../../source/wnd/syspara.h"
#include "xpage.h"
#include "xpluginintf.h"

//! macros
#define new_widget( type, var, txt, icon ) \
do{ \
    var = new type;\
    Q_ASSERT( NULL != var ); \
    var->adapteToUserMode(sysMode());\
    var->attachPref( m_pPref );\
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
    var->attachWorkings();\
    var->setObjectName( txt );\
    \
    \
    root->setIcon( 0, QIcon( icon) ); \
    root->setText( 0, tr(txt) ); \
    root->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(var) ) ); \
    stack->addWidget( var ); \
    mPluginWidgets.append( var ); \
}while(0)

class XPluginWorkingThread;
class XPluginBgThread;
class XPlugin : public XPluginIntf
{
    Q_OBJECT
public:
    typedef int (XPlugin::*bgProc)();

public:
    XPlugin( QObject *parent = nullptr );
    virtual ~XPlugin();

signals:
    void signal_focus_changed( const QString &model,
                               const QString &contextHelp );
    void signal_setting_changed( XSetting setting );
    void signal_request_save();
    void signal_request_load();

    void signal_api_operate( QObject *pApi, bool );
    void signal_timer_op( QTimer *pTimer, int tmo, bool );

public:
    virtual QTreeWidgetItem* createPrefPages( QStackedWidget *stack );
    virtual QWidget *createOpsPanel( QAbstractListModel *pModel,
                                     QWidget *parent=nullptr );

    virtual void setActive( );

    virtual void rstErrorMgrTable();
    virtual void rstRecordTable();

//    virtual void ErrorMgrTable( QByteArray &ary );
//    virtual void RecordTable( QByteArray &ary );

    virtual void onOperateAble( bool b );
public:
    virtual int save( const QString &filename );
    virtual int load( const QString &filename );

    virtual int serialOut( QXmlStreamWriter &writer );
    virtual int serialIn( QXmlStreamReader &reader );

    virtual bool isEnabled( void *context );

    virtual void onSetting( XSetting setting );

public:
    virtual void updateUi();

    virtual void rst();

    virtual int upload();
    virtual int download();
    virtual int diff();


public:
    void emit_timer_op( QTimer *pTimer, int tmo, bool b );

    void emit_setting_changed( XPage::eXSetting setting, bool b );
    void emit_setting_changed( XPage::eXSetting setting, QVariant var );

    void emit_save();
    void emit_load();

    void setViewObj( void *pObj );
    void *viewObj();

    void attachDock( QDockWidget *pDock );
    void attachPanel( QWidget *pPanel );

    void attachPref( SysPara *pPref );
    SysPara * pref();

    QWidget *panel();

    QString homePath();
public:
    void lockWorking();
    void unlockWorking();

    void attachUpdateWorking( XPage *pObj,
                        XPage::procDo proc,
                        const QString &desc="",
                        void *pContext = NULL,
                        int tmoms = 100
                        );
    void attachUpdateWorking( XPage *pObj,
                        XPage::procDo proc,
                        XPage::preDo pre,
                        XPage::postDo post,
                        const QString &desc="",
                        void *pContext = NULL,
                        int tmoms = 100
                        );

    void _attachUpdateWorking( XPage *pObj,
                        XPage::procDo proc,
                        XPage::preDo pre,
                        XPage::postDo post,
                        const QString &desc="",
                        void *pContext = NULL,
                        int tmoms = 100
                        );

    void attachMissionWorking( XPage *pObj,
                        XPage::onMsg onmsg,
                        QVariant var,
                        const QString &desc=""
                        );

    void attachEmergencyWorking( XPage *pObj,
                        XPage::onMsg onmsg,
                        QVariant var,
                        const QString &desc=""
                        );

    //! plugin
    void attachBgWorking(
                        XPlugin::bgProc proc,
                        const QString &desc=""
                        );
    void cancelBgWorking();

protected:
    QTreeWidgetItem *m_pRootWidgetItem;
    QWidget *m_pPanelWidget;
    QDockWidget *m_pDock;

    QList<QWidget*> mPluginWidgets;
    void *m_pViewObj;

    SysPara *m_pPref;

public:
    XPluginWorkingThread *m_pEmergencyWorking;
    XPluginWorkingThread *m_pMissionWorking;
    XPluginWorkingThread *m_pUpdateWorking;

//    XPluginWorkingThread *m_pPoolWorking;
//    XPluginWorkingThread *m_pPoolWorking;

    XPluginBgThread *m_pBgWorking;

    QMutex mEmergMutex, mMissionMutex, mUpdateMutex;

//    QSignalMapper mMapper;
//    QSignalMapper *m_pMapper;

protected Q_SLOTS:
    virtual void slot_save_setting();
    virtual void slot_load_setting();

    void slot_plugin_setting_changed( XSetting setting );
};

class XPluginBgThread : public QThread
{
    Q_OBJECT
public:
    XPluginBgThread( XPlugin *plugin, QObject *parent = NULL );

protected:
    virtual void run();

public:
    void attachBgProc( XPlugin::bgProc );

protected:
    XPlugin *m_pPlugin;
    QQueue< XPlugin::bgProc > mApis;
    QMutex mMutex;
};




#endif
