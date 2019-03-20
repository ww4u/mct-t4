#ifndef ROBO_CONFIG_H
#define ROBO_CONFIG_H

#include <QtWidgets>
//#include "xrobo.h"
#include "megainterface.h"
#include "MegaGateway.h"

#include "syspref.h"

#include "../plugin/model/megaloglistmodel.h"
#include "../plugin/plugin/xplugin.h"

namespace Ui {
class RoboConfig;
}

class RoboConfig : public QWidget
{
    Q_OBJECT

public:
    explicit RoboConfig(QWidget *parent = 0);
    ~RoboConfig();

signals:
    void signal_focus_in( const QString &model, const QString &help );

    void signal_plugins_changed();
    void signal_plugins_operable( bool b );

    void signal_request_sysOpPanel();
    void signal_save_sysPref();
protected:
    void setupUi();

    void retranslateUi();

public:
    void attachOpDock( QDockWidget *pDock );
    void attachLogModel( MegaLogListModel *pModel );
    void attachSysPref( SysPara *pPref );
    void attachConnectWidget( QAction *pAction );

    void postStartup();

    void cancelBgWorking();

    QTreeWidgetItem *rootItem();
    QStackedWidget *stackWidget();

    bool downloadVisible();
    bool resetVisible();

protected:
    void stackPageChange( QTreeWidgetItem *current, QTreeWidgetItem *previous );
    void panelPageChange( QTreeWidgetItem *current, QTreeWidgetItem *previous );

    void createRobot( const QStringList &strInfos );

    //! remove the plugin
    void removePlugin( XPlugin *plugin );
    void addPlugin( XPlugin *plugin );

    XPlugin* findPlugin( const QString &_addr,
                     const QString &_model,
                     const QString &_sn );

    int  setReset();

    bool pluginsConnectState();
    void pluginsOpen();
    void plginsClose();

    void pluginsStop();

public slots:
    void slotDownload();
    void slotUpload();
    void slotStore();
    void slotSync();

    void slotSearch();

    void slotConnect();

    void slotWifi();

    void slot_plugins_stop();

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current,
                                          QTreeWidgetItem *previous);
    void on_buttonBox_clicked(QAbstractButton *button);

    void slotAddNewRobot( const QStringList &strDevInfo );

    void slotShowContextmenu(const QPoint &pos);
    void slotActionOpen();
    void slotActionClose();
    void slotActionRst();
    void slotActionDelete();
    void slotActionExplorer();

//    void slotStoreEnd(int val);

    void slot_plugins_changed();
    void slot_plugin_setting_changed( XSetting setting );

    void on_stackedWidget_currentChanged(int arg1);

private:
    Ui::RoboConfig *ui;

    MegaInterface *m_megaSerachWidget;
    QDockWidget *m_pOpDock;
    MegaLogListModel *m_pLogModel;
    SysPara *m_pPref;

    QAction *m_pConnAction;

    QMenu *m_pRoboContextMenu;
    QAction *m_pActionOpen, *m_pActionClose, *m_pActionRst;

    //! info
    XPlugin *m_pCurPlugin;
    QTreeWidgetItem *m_pCurTreeItem;

    QTreeWidgetItem *m_pRootNode;
    QList<XPlugin*> mPluginList;
};

#endif // H2CONFIG_H
