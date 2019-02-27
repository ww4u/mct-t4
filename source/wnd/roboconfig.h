#ifndef ROBO_CONFIG_H
#define ROBO_CONFIG_H

#include <QtWidgets>
#include "xrobo.h"
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
//    void signalCurrentRobotChanged(QString,int,int,int);
    void signal_focus_in( const QString &);
//    void signalDataChanged();
//    void signal_record_selected(int);
//    void signalDeviceConnect(bool);

    void signal_plugins_changed();

    void signal_request_sysOpPanel();
    void signal_save_sysPref();

//    void changeLanguage(QString qmFile);
//    void addDeviceWithIP(QString strID);
protected:
    void setupUi();

    void retranslateUi();

public:
    void attachOpDock( QDockWidget *pDock );
    void attachLogModel( MegaLogListModel *pModel );
    void attachSysPref( SysPara *pPref );

    void postStartup();

    void cancelBgWorking();

    QTreeWidgetItem *rootItem();
    QStackedWidget *stackWidget();

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

public slots:
    void slotDownload();
    void slotUpload();
    void slotStore();
    void slotSync();

    void slotSearch();

//    void slotExit();

    void slotWifi();
    void slotConnect();

//    void slotSetOneRecord(int row,QString type,double x,double y,double v,double a);

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current,
                                          QTreeWidgetItem *previous);
    void on_buttonBox_clicked(QAbstractButton *button);

//    void slot_current_changed( QTreeWidgetItem* pre,QTreeWidgetItem* nxt );
//    void slot_open_close(QString strIP);

    void slotAddNewRobot( const QStringList &strDevInfo );

    void slotShowContextmenu(const QPoint &pos);
    void slotActionOpen();
    void slotActionClose();
    void slotActionDelete();
    void slotActionExplorer();

//    void slotStoreEnd(int val);



    void slot_plugins_changed();

private:
    Ui::RoboConfig *ui;

    MegaInterface *m_megaSerachWidget;
    QDockWidget *m_pOpDock;
    MegaLogListModel *m_pLogModel;
    SysPara *m_pPref;

    QMenu *m_pRoboContextMenu;
    QAction *m_pActionOpen, *m_pActionClose;

    //! info
    XPlugin *m_pCurPlugin;
    QTreeWidgetItem *m_pCurTreeItem;

//    class RobotInfo
//    {
//    public:
//        XRobo*  m_Robo;
//        int     m_Visa;
//        int     m_DeviceName;
//        int     m_RoboName;
//        QString m_strDevInfo;
//    };

    QTreeWidgetItem *m_pRootNode;
//    QList<RobotInfo> m_RobotList;
//    int mIndex;

    QList<XPlugin*> mPluginList;


//    void loadXmlConfig();

//    void createRobot(const QString &strDevInfo, const QString &model="" );


//    int  deviceOpen(QString strIP);
//    int  deviceClose();
//    int  setApply();


//    QMenu *m_menu;
//    QTranslator m_translator;


};

#endif // H2CONFIG_H
