#ifndef ROBO_CONFIG_H
#define ROBO_CONFIG_H

#include <QtWidgets>
#include "xrobo.h"
#include "megainterface.h"
#include "MegaGateway.h"

namespace Ui {
class RoboConfig;
}

class RoboConfig : public QWidget
{
    Q_OBJECT

signals:
    void signalCurrentRobotChanged(QString,int,int,int);
    void signal_focus_in( const QString &);
    void signalDataChanged();
    void signal_record_selected(int);

public:
    explicit RoboConfig(QWidget *parent = 0);
    ~RoboConfig();
    void changeLanguage(QString qmFile);

public slots:
    void slotDownload();
    void slotUpload();
    void slotStore();
    void slotSync();
    void slotSearch();
    void slotExit();

    void slotAddNewRobot(QString strDevInfo );
    void slotSetOneRecord(int row,QString type,double x,double y,double v,double a);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void slot_current_changed( QTreeWidgetItem* pre,QTreeWidgetItem* nxt );
    void slot_open_close(QString strIP);
    void slotShowContextmenu(const QPoint &pos);
    void soltActionClose();
    void soltActionDelete();
    void slotStoreTips(int val);

private:
    Ui::RoboConfig *ui;
    MegaInterface *m_megaSerachWidget;

    class RobotInfo
    {
    public:
        XRobo*  m_Robo;
        int     m_Visa;
        int     m_DeviceName;
        int     m_RoboName;
        QString m_strDevInfo;
    };

    QTreeWidgetItem *m_pRootNode;
    QList<RobotInfo> m_RobotList;
    int mIndex;

    void initRootNodeWidget();
    void loadXmlConfig();
    void createRobot(QString strDevInfo);
    int  deviceOpen(QString strIP);
    int  deviceClose();
    int  setApply();
    int  setReset();

    QMenu *m_menu;
    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    QTranslator m_translator;
    int m_retVal;
};

#endif // H2CONFIG_H
