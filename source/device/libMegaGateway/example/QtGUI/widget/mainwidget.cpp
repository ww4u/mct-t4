#include "ui_mainwidget.h"
#include <QTimer>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QFile>
#include <QDebug>
#include <QThread>
#include <QInputDialog>

#include "mainwidget.h"
#include "sysapi.h"

#define CONFIG_FILE  (QApplication::applicationDirPath()+"/conf.txt")

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    m_vi = 0;
    m_IDN = "";
    m_robotID = 0;
    m_robotType = "";
    m_deviceID = 0;
    m_deviceType = "";
    m_strCmdList.clear();

    m_model = new QStandardItemModel(ui->tableView);
    ui->tableView->setModel(m_model);
    m_menu = NULL;

    m_threadUpdateInfo = NULL;

    connect(ui->pushButtonSearchMRHT, SIGNAL(clicked(bool)), this, SLOT(slotSearchGateway()));
    connect(ui->pushButtonOpenMRHT, SIGNAL(clicked(bool)), this, SLOT(slotOpenGateway()));
    connect(ui->pushButton_Send, SIGNAL(clicked(bool)), this, SLOT(slotGatewaySend()));

    connect(ui->pushButton_searchRobot, SIGNAL(clicked(bool)), this, SLOT(slotSearchRobot()));
    connect(ui->pushButton_goHome, SIGNAL(clicked(bool)), this, SLOT(slotRobotGoHome()));
    connect(ui->pushButton_stop, SIGNAL(clicked(bool)), this, SLOT(slotRobotStop()));

    connect(ui->lineEdit,SIGNAL(returnPressed()),ui->pushButton_Send,SLOT(click()));

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(slotViewLineClicked(QModelIndex)));

    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(slotViewLineDoubleClicked(QModelIndex)));

    connect(ui->tableView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowContextmenu(const QPoint&)));

    //! load config file
    loadConfigFile();

    //! search gateway
    QTimer::singleShot(1000, this, SLOT(slotSearchGateway()) );

    initUpdateInfoThread();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::slotSearchGateway()
{
    auto lambda = [&]()
    {
        QString strFindDevices = "";
        char buff[4096] = "";

        //! 搜索网络
        memset(buff, 0, sizeof(buff));
        mrgFindGateWay(0, buff, sizeof(buff), 1);
        strFindDevices = QString("%1").arg(buff);

        //! 搜索USB
        memset(buff, 0, sizeof(buff));
        mrgFindGateWay(1, buff, sizeof(buff), 1);
        strFindDevices += QString("%1").arg(buff);

        ui->comboBox->addItems(strFindDevices.split(',', QString::SkipEmptyParts));
    };

    ui->comboBox->clear();
    sysShowProgressBar(true);
    XThread *thread = new XThread(lambda);
    connect(thread, &XThread::finished,
            this,[](){
        sysShowProgressBar(false);
    });

    thread->start();
}

void MainWidget::slotOpenGateway()
{
    if( m_IDN == "")
    {
        slotCloseGateway();
        m_vi = mrgOpenGateWay(ui->comboBox->currentText().toLocal8Bit().data(), 200);
        if(m_vi <= 0)
        {
            QMessageBox::critical(this, "错误", "打开网关失败 " + QString::number(m_vi));
            m_vi = 0;
            m_IDN = "";
            return;
        }
        char idn[128] = "";
        mrgGateWayIDNQuery(m_vi, idn);
        if(strlen(idn) == 0)
        {
            QMessageBox::critical(this, "错误", "获取IDN失败");
            slotCloseGateway();
        }
        m_IDN = QString("%1").arg(idn);
        ui->labelIDN->setText(m_IDN);
        ui->pushButtonOpenMRHT->setText("关闭");

        slotSearchRobot();
    }
    else
    {
        slotCloseGateway();
        ui->pushButtonOpenMRHT->setText("打开");
    }
}

void MainWidget::slotCloseGateway()
{
    if(m_vi != 0)
    {
        mrgCloseGateWay(m_vi);
        m_vi = 0;
        m_IDN = "";
        m_robotID = 0;
        m_robotType = "";
        m_deviceID = 0;
        m_deviceType = "";
    }
    ui->labelIDN->setText(m_IDN);
    ui->label_RobotID->setText("");
    ui->label_DeviceID->setText("");
    ui->label_RobotType->setText("");
    ui->label_DeviceType->setText("");
    ui->radioButton_updatePos->setChecked(false);

}

void MainWidget::slotGatewaySend()
{
    QString cmd = ui->lineEdit->text();
    if(cmd == "" || m_vi == 0)
    {
        return;
    }

    addItemToTableView(cmd);
    writeFile(CONFIG_FILE, cmd+"\n", true);

    if(cmd.contains("?"))
    {
        slotGatewayQeury();
        return;
    }

    int ret = mrgGateWaySendCmd(m_vi, cmd.toLocal8Bit().data(), cmd.length());
    if(ret <= 0)
    {
        QMessageBox::critical(this, "错误", "发送失败 " + QString::number(ret));
    }
    else
    {
        ui->lineEdit->clear();
    }
    ui->textBrowser->clear();
}

void MainWidget::slotGatewayQeury()
{
    char buff[1024] = "";
    int ret = mrgGateWayQuery(m_vi, ui->lineEdit->text().toLocal8Bit().data(), buff, 1024);
    if(ret <= 0)
    {
        QMessageBox::critical(this, "错误", "查询失败 " + QString::number(ret));
    }
    else
    {
        ui->lineEdit->clear();
        ui->textBrowser->clear();
        ui->textBrowser->setText(QString("%1").arg(buff));
    }
}

void MainWidget::slotSearchRobot()
{
    if(m_vi <= 0)
    {
        return;
    }

    int robotNames[128] = {0};
    int ret = mrgGetRobotName(m_vi, robotNames);
    if(ret <= 0)
    {
        QMessageBox::critical(this, "错误", "获取机器人失败 " + QString::number(ret));
        return;
    }

    if(ret == 1)
    {
        m_robotID = robotNames[0];
    }
    else
    {
        QStringList strRobotList;
        for(int i=0; i<ret; i++)
        {
            int robotID = robotNames[i];
            strRobotList << QString("%1:%2").arg(robotID).arg(parseRobotType(robotID));
        }

        QString strRobotName = QInputDialog::getItem(this, tr("机器人列表"), tr("请选择机器人: "), strRobotList, -1, false);
        if(strRobotName == "")
            return;

        m_robotID = strRobotName.split(":", QString::SkipEmptyParts).at(0).toInt();
    }

    m_robotType = parseRobotType(m_robotID);
    ui->label_RobotID->setText( QString("%1").arg(m_robotID));
    ui->label_RobotType->setText( m_robotType );

    slotSearchDevice();
}

QString MainWidget::parseRobotType(int robotID)
{
    QString strRobotType = "";
    if(m_vi <= 0 || robotID <= 0)
        return strRobotType;

    int ret = mrgGetRobotType(m_vi, robotID);
    switch (ret) {
    case MRX_TYPE_T4:
        strRobotType = "MRX-T4";
        break;
    case MRX_TYPE_H2:
        strRobotType = "MRX-H2";
        break;
    default:
        strRobotType = "UNKOWN";
//        QMessageBox::critical(this, "错误", "机器人类型错误");
        break;
    }
    return strRobotType;
}

void MainWidget::slotSearchDevice()
{
    if(m_vi <= 0)
    {
        return;
    }
    int deviceNames[128] = {0};
    int ret;
    ret = mrgGetRobotDevice(m_vi, m_robotID, deviceNames);
    if(ret <= 0)
    {
        QMessageBox::critical(this, "错误", "获取设备失败 " + QString::number(ret));
        return;
    }
    m_deviceID = deviceNames[0];

    char type[128] = "";
    ret = mrgGetDeviceType(m_vi, m_deviceID, type);
    if(0 != ret)
    {
        QMessageBox::critical(this, "错误", "获取设备类型失败");
    }
    m_deviceType = QString("%1").arg(type);
    ui->label_DeviceID->setText(QString("%1").arg(m_deviceID));
    ui->label_DeviceType->setText(m_deviceType);
}

void MainWidget::slotRobotStop()
{
    if(m_vi <= 0 || m_robotID <= 0)
    {
        return;
    }

    auto lambda = [&]()
    {
        mrgRobotStop(m_vi, m_robotID, -1);
    };

    XThread *thread = new XThread(lambda);
    thread->start();
}

void MainWidget::slotRobotGoHome()
{
    if(m_vi <= 0 || m_robotID <= 0)
    {
        return;
    }
    auto lambda = [&]()
    {
        ui->pushButton_goHome->setEnabled(false);
        mrgRobotGoHome(m_vi, m_robotID, 0);
        ui->pushButton_goHome->setEnabled(true);
    };

    XThread *thread = new XThread(lambda);
    thread->start();
}

QString MainWidget::getRobotCurrentState()
{
    if(m_vi <= 0 || m_robotID <= 0)
    {
        return "";
    }
    char args[100];
    char state[100];
    int retlen = 0;
    snprintf(args, 100, "ROBOT:STATe? %d\n", m_robotID);
    if ((retlen = mrgGateWayQuery(m_vi, args, state, 100)) <= 0)
    {
        return "";
    }
    state[retlen - 1] = '\0';//去掉回车符
    return QString(state);
}

void MainWidget::initUpdateInfoThread()
{
    auto lambda = [&]()
    {
        while(1)
        {
            //! 如果取消打钩或关闭网关或没有构建机器人, 就不更新位置信息
            if ( !ui->radioButton_updatePos->isChecked() || m_vi <= 0 || m_robotID <= 0)
            {
                QThread::msleep(3000);
                ui->doubleSpinBox_posX->setValue(0);
                ui->doubleSpinBox_posY->setValue(0);
                ui->doubleSpinBox_posZ->setValue(0);
                continue;
            }

            float fx = -1, fy = -1, fz = -1;
            int ret = mrgGetRobotCurrentPosition(m_vi, m_robotID, &fx, &fy, &fz);
            if(ret != 0)
            {
                fx = -1;
                fy = -1;
                fz = -1;
            }
            ui->doubleSpinBox_posX->setValue(fx);
            ui->doubleSpinBox_posY->setValue(fy);
            ui->doubleSpinBox_posZ->setValue(fz);

            ui->label_robotState->setText(getRobotCurrentState());

            QThread::msleep(500);
        }
    };

    m_threadUpdateInfo = new XThread(lambda);
    m_threadUpdateInfo->start();
}

void MainWidget::loadConfigFile()
{
    QString config = readFile(CONFIG_FILE);
    m_strCmdList = config.split("\n", QString::SkipEmptyParts);

    saveConfigFile();

    foreach (QString line, m_strCmdList) {
        addItemToTableView(line);
    }
}

void MainWidget::saveConfigFile()
{
    removeListSame(m_strCmdList);
    writeFile(CONFIG_FILE, m_strCmdList.join('\n') + "\n");
}

void MainWidget::slotViewLineClicked(QModelIndex index)
{
    QString str = index.data().toString();
    ui->lineEdit->setText(str);
}

void MainWidget::slotViewLineDoubleClicked(QModelIndex index)
{
    QString str = index.data().toString();
    ui->lineEdit->setText(str);
    ui->pushButton_Send->click();
}

void MainWidget::slotShowContextmenu(const QPoint& pos)
{
    if(!((ui->tableView->selectionModel()->selectedIndexes()).empty()))
    {
        if(m_menu != NULL)
            delete m_menu;

        m_menu = new QMenu(ui->tableView);
        QAction *actionRemove = m_menu->addAction(tr("remove"));
        QAction *actionClear = m_menu->addAction(tr("clear"));

        connect(actionRemove, SIGNAL(triggered(bool)), this, SLOT(soltActionRemove()));
        connect(actionClear, SIGNAL(triggered(bool)), this, SLOT(soltActionClear()));

        m_menu->exec(QCursor::pos());
        ui->tableView->selectionModel()->clear();
    }
}

//! 列表删除一条数据
void MainWidget::soltActionRemove()
{
    int curRow = ui->tableView->currentIndex().row();
    m_model->removeRow(curRow);
//    m_strCmdList.removeOne( m_model->index(curRow, 0).data().toString() );
    m_strCmdList.removeAt(curRow);
    saveConfigFile();
}

//! 清空列表
void MainWidget::soltActionClear()
{
    m_model->clear();
    m_strCmdList.clear();
    saveConfigFile();
}

//! 列表增加一条数据
void MainWidget::addItemToTableView(QString cmd)
{
    if(!m_strCmdList.contains(cmd))
    {
        m_strCmdList << cmd;
        saveConfigFile();
    }

    bool isExist = false;
    int maxRow = m_model->rowCount();
    for(int index=0; index<maxRow; index++)
    {
        if(cmd == m_model->index(index, 0).data().toString())
        {
            isExist = true;
        }
    }
    if(!isExist)
    {
        QStandardItem *item = new QStandardItem(cmd);
        m_model->appendRow(item);
    }
}


