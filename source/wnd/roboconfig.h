#ifndef ROBO_CONFIG_H
#define ROBO_CONFIG_H

#include <QtWidgets>
#include "xrobo.h"
#include "megainterface.h"

namespace Ui {
class RoboConfig;
}

class RoboConfig : public QWidget
{
    Q_OBJECT

signals:
    void signalCurrentRobotChanged(QString,int,int);
    void signal_focus_in( const QString &);
    void signalApplyClicked();

public:
    explicit RoboConfig(QWidget *parent = 0);
    ~RoboConfig();

public slots:
    void slotAddNewRobot(QString strDevInfo );

    void slotDownload();
    void slotUpload();
    void slotStore();
    void slotSync();
    void slotSearch();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void slot_current_changed( QTreeWidgetItem* pre,QTreeWidgetItem* nxt );
    void slot_open_close(QString strIP);
    void slotShowContextmenu(const QPoint &pos);
    void soltActionClose();
    void soltActionDelete();

private:
    Ui::RoboConfig *ui;
    MegaInterface *m_megaSerachWidget;

    class RobotInfo
    {
    public:
        XRobo*  m_Robo;
        int     m_Visa;
        int     m_RoboName;
        QString m_strDevInfo;
    };

    QTreeWidgetItem *m_pRootNode;
    QList<RobotInfo> m_RobotList;
    int mIndex;

    void loadXmlConfig();
    void createRobot(QString strDevInfo);
    int  deviceOpen(QString strIP);
    int  deviceClose();
    int  setApply();
    int  setReset();
    int  setOK();

    QMenu *m_menu;
    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
};

#endif // H2CONFIG_H
