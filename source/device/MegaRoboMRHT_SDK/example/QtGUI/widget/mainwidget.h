#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMenu>
#include <QStandardItemModel>
#include <QWidget>
#include <QTcpSocket>

#include "MegaGateway.h"
#include "xthread.h"
#include "TestPanelDialog.h"

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

    void slotGatewayIdentify(bool isOn);

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

    void on_pushButtonTest_clicked();

    void slotTcpRead();

    void slotTcpError(QAbstractSocket::SocketError);


private:
    Ui::MainWidget *ui;

    ViSession   m_vi; //当前句柄

    QString     m_strVisaDesc; //Visa描述信息,如:TCPIP0::169.254.1.2::...

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

    TestPanelDialog *m_testPanelDialog;

    QTcpSocket *m_tcpClient;
};

#endif // MAINWIDGET_H
