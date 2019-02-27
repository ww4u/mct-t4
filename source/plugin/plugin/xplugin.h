#ifndef XPLUGIN_H
#define XPLUGIN_H

#include <QObject>
#include <QStackedWidget>
#include <QTreeWidgetItem>
#include <QDockWidget>
#include <QThread>

#include "../../../source/wnd/syspref.h"
#include "xpage.h"
#include "xpluginintf.h"


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
    void signal_setting_changed( XSetting setting );
    void signal_request_save();
    void signal_request_load();

public:
    virtual QTreeWidgetItem* createPrefPages( QStackedWidget *stack );
    virtual QWidget *createOpsPanel( QAbstractListModel *pModel,
                                     QWidget *parent=nullptr );

    virtual void setActive( );

    virtual void ErrorMgrTable( QByteArray &ary );

    virtual void onOperateAble( bool b );
public:
    virtual int save( const QString &filename );
    virtual int load( const QString &filename );

    virtual int serialOut( QXmlStreamWriter &writer );
    virtual int serialIn( QXmlStreamReader &reader );

    virtual bool isEnabled( void *context );

    virtual void onSetting( XSetting setting );

public:
    virtual int stop();

    virtual int upload();
    virtual int download();
    virtual int diff();


public:
    void emit_setting_changed( XPage::eXSetting setting, bool b );
    void emit_setting_changed( XPage::eXSetting setting, QVariant var );

    void emit_save();
    void emit_load();

    void setViewObj( void *pObj );
    void *viewObj();

    void attachDock( QDockWidget *pDock );
    void attachPanel( QWidget *pPanel );

    QWidget *panel();

    QString homePath();
public:
    void lockWorking();
    void unlockWorking();

    void attachUpdateWorking( XPage *pObj,
                        XPage::procDo proc,
                        void *pContext = NULL
                        );
    void attachUpdateWorking( XPage *pObj,
                        XPage::procDo proc,
                        XPage::preDo pre,
                        XPage::postDo post,
                        void *pContext = NULL
                        );

    void attachMissionWorking( XPage *pObj,
                        XPage::onMsg onmsg,
                        QVariant var
                        );

    void attachEmergencyWorking( XPage *pObj,
                        XPage::onMsg onmsg,
                        QVariant var
                        );

    //! plugin
    void attachBgWorking(
                        XPlugin::bgProc proc
                        );
    void cancelBgWorking();

protected:
    QWidget *m_pPanelWidget;
    QDockWidget *m_pDock;

    QList<QWidget*> mPluginWidgets;
    void *m_pViewObj;
public:
    XPluginWorkingThread *m_pEmergencyWorking;
    XPluginWorkingThread *m_pMissionWorking;
    XPluginWorkingThread *m_pUpdateWorking;

    XPluginBgThread *m_pBgWorking;

    QMutex mEmergMutex, mMissionMutex, mUpdateMutex;

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

