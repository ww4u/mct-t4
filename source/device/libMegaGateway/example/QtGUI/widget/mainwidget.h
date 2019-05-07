#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMenu>
#include <QStandardItemModel>
#include <QWidget>
#include "MegaGateway.h"
#include "xthread.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void slotSearchGateway();

    void slotOpenGateway();

    void slotCloseGateway();

    void slotGatewaySend();

    void slotGatewayQeury();

    void slotSearchRobot();

    void slotSearchDevice();

    void slotRobotStop();

    void slotRobotGoHome();

    void slotViewLineClicked(QModelIndex index);

    void slotViewLineDoubleClicked(QModelIndex index);

    void slotShowContextmenu(const QPoint &pos);

    void soltActionRemove();

    void soltActionClear();

    void loadConfigFile();

    void saveConfigFile();

    void addItemToTableView(QString cmd);

private:
    Ui::MainWidget *ui;

    ViSession   m_vi; //当前句柄

    QString     m_IDN;

    int         m_robotID;
    QString     m_robotType;

    int         m_deviceID;
    QString     m_deviceType;

    QStandardItemModel* m_model;
    QMenu *m_menu;

    QStringList m_strCmdList;

    XThread *m_threadUpdateInfo;

    void initUpdateInfoThread();
    QString parseRobotType(int robotID);
    QString getRobotCurrentState();
};

#endif // MAINWIDGET_H
