#ifndef ROBO_CONFIG_H
#define ROBO_CONFIG_H

#include <QtWidgets>
#include "xrobo.h"

namespace Ui {
class RoboConfig;
}

class RoboConfig : public QWidget
{
    Q_OBJECT

signals:
    void signalCurrentRobotChanged(QString,int,int);
    void signal_focus_in( const QString &);

public:
    explicit RoboConfig(QWidget *parent = 0);
    ~RoboConfig();

public slots:
    void slotAddNewRobot(QString strDevInfo );

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void slot_current_changed( QTreeWidgetItem* pre,QTreeWidgetItem* nxt );
    void slot_open_close(QString strIP);

private:
    Ui::RoboConfig *ui;

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
    void createNewRobot(QString strDevInfo);
    int  deviceOpen(QString strIP);
    int  deviceClose();
    int  setApply();
    int  setReset();
    int  setOK();
};

#endif // H2CONFIG_H
