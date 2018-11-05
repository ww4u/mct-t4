#include "megainterface.h"
#include "ui_megainterface.h"

#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

#include <lanfinddevice.h>
#include <mrht.h>

MegaInterface::MegaInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MegaInterface),
    m_devType(TYPE_LAN),
    m_menu(NULL),
    m_searchThread(NULL),
    m_visa(-1)
{
    ui->setupUi(this);

    connect(ui->comboBox_DevType,SIGNAL(currentIndexChanged(int)),this,SLOT(slotChangeDeviceType(int)));
    connect(ui->pushButton_Scan,SIGNAL(clicked(bool)),this,SLOT(slotScanDevices()));

    m_model = new QStandardItemModel(ui->listView);
    ui->listView->setModel(m_model);

    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowContextmenu(const QPoint&)));

    connect(ui->pushButton_ok,SIGNAL(pressed()),this,SLOT(deviceOpenAndRobotBuild()));
}

MegaInterface::~MegaInterface()
{
    delete ui;
}

int MegaInterface::visa() const
{
    return m_visa;
}


void MegaInterface::slotChangeDeviceType(int index)
{
    if(index == TYPE_LAN)
    {
        //! LAN
        ui->label_icon->setPixmap(QPixmap(":/res/image/icon/network.ico"));
        m_devType = TYPE_LAN;
    }else if(index == TYPE_USB)
    {
        //! USB
        ui->label_icon->setPixmap(QPixmap(":/res/image/icon/usb.ico"));
        m_devType = TYPE_USB;
    }
}

void MegaInterface::slotScanDevices()
{
    clearListView();

    m_searchThread = new DeviceSearchThread;
    m_searchThread->setType(m_devType);
    connect(m_searchThread, SIGNAL(resultReady(QString)), this, SLOT(insertOneRow(QString)));
    connect(m_searchThread, SIGNAL(finished()), this, SLOT(slotScanFinished()));
    connect(m_searchThread, SIGNAL(finished()), m_searchThread, SLOT(deleteLater()));

    m_searchThread->start();
    ui->pushButton_Scan->setEnabled(false);
    ui->progressBar->setMaximum(0);
}

void MegaInterface::slotScanFinished()
{
    ui->pushButton_Scan->setEnabled(true);
    ui->progressBar->setMaximum(100);
}

void MegaInterface::insertOneRow(QString str)
{
    int maxRow = m_model->rowCount();
    QStandardItem *t_item = new QStandardItem(str);
    m_itemList.append(t_item);
    m_model->setItem(maxRow, 0, m_itemList.at(maxRow));
}

void MegaInterface::clearListView()
{
    for(int i=0; i<m_itemList.count(); i++)
    {
        delete m_itemList.at(i);
    }
    m_itemList.clear();
    m_model->clear();
}

void MegaInterface::slotShowContextmenu(const QPoint& pos)
{
    if(!((ui->listView->selectionModel()->selectedIndexes()).empty()))
    {
        if(m_menu != NULL)
            delete m_menu;

        m_menu = new QMenu(ui->listView);
        QAction *actionOpen = m_menu->addAction(tr("ON"));
        QAction *actionClose = m_menu->addAction(tr("OFF"));

        connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(soltActionOpen()));
        connect(actionClose, SIGNAL(triggered(bool)), this, SLOT(soltActionClose()));

        m_menu->exec(QCursor::pos());
        ui->listView->selectionModel()->clear();
    }
}

void MegaInterface::soltActionOpen()
{
    int visa = deviceOpen();
    if(visa < 0)
        return;

    mrhtSystemIdentify(visa, 1);
    mrhtCloseDevice(visa);
}

void MegaInterface::soltActionClose()
{
    int visa = deviceOpen();
    if(visa < 0)
        return;

    mrhtSystemIdentify(visa, 0);
    mrhtCloseDevice(visa);
}

int MegaInterface::deviceOpen()
{
    QModelIndex index = ui->listView->selectionModel()->selectedIndexes().at(0);
    QString strIP = m_model->data(index,Qt::DisplayRole).toString();
    qDebug() << "open " << strIP;
    int visa =  mrhtOpenDevice(strIP.toLatin1().data(), 2000);
    if(visa < 0)
        QMessageBox::warning(this,tr("error"),tr("open device error"));

    return visa;
}

void MegaInterface::deviceOpenAndRobotBuild()
{
    int ret = -1;
    int visa = deviceOpen();
    if(visa < 0)
    {
        QMessageBox::warning(this,tr("error"),tr("open device error"));
        return;
    }
    m_visa = visa;

    {
        char strIDN[1024] = "";
        ret = mrhtIdn_Query(visa,strIDN,sizeof(strIDN));
        qDebug() << strIDN; //MegaRobo Technologies,MRH-T,MRHT000005187U0032,00.00.01.06
    }

#if 0
    {
        //搜索驱控器
        int devNames[128] = {0};
        ret = mrhtDeviceName_Query(visa,devNames);
        if(ret != 0)
        {
            QMessageBox::warning(this,tr("error"),tr("search DeviceName failure"));
            return;
        }
        qDebug() << devNames[0];

        char strType[128] = "";
        ret = mrhtDeviceType_Query(visa, devNames[0], strType,sizeof(strType));
        if(ret != 0)
        {
            QMessageBox::warning(this,tr("error"),tr("search GetDeviceType failure"));
            return;
        }
        qDebug() << strType;


        //构建机器人
        //    mrhtRobotAlloc_Query(visa,  );
    }
#endif

}











/////////////////////////////////////////////////////////////
void DeviceSearchThread::run()
{
    QString strDevices;
    if(m_type == TYPE_LAN)
    {
        char buff[4096] = "";
        findResources(buff, 1);
        strDevices = QString("%1").arg(buff);
        if(strDevices.length() == 0)
        {
            qDebug() << "mrgFindGateWay failure";
            return;
        }
    }
    else if(m_type == TYPE_USB)
    {
        //FILL strDevices


    }

    QStringList devList = strDevices.split(';', QString::SkipEmptyParts);
    qDebug() << devList;
    for(int devIndex=0; devIndex<devList.count(); devIndex++)
    {
        emit resultReady(devList.at(devIndex));
        qDebug() << devList.at(devIndex);
    }
}

void DeviceSearchThread::setType(int type)
{
    m_type = type;
}