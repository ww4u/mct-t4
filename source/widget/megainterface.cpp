#include "megainterface.h"
#include "ui_megainterface.h"

#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

#include "MegaGateway.h"
#include "sysapi.h"

MegaInterface::MegaInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MegaInterface),
    m_devType(TYPE_LAN),
    m_menu(NULL),
    m_searchThread(NULL)
{
    ui->setupUi(this);

    connect(ui->comboBox_DevType,SIGNAL(currentIndexChanged(int)),this,SLOT(slotChangeDeviceType(int)));
    connect(ui->pushButton_Scan,SIGNAL(clicked(bool)),this,SLOT(slotScanDevices()));

    m_model = new QStandardItemModel(ui->tableView);
    ui->tableView->setModel(m_model);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowContextmenu(const QPoint&)));

    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(slotSelectDevices()));

    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(close()));

}

MegaInterface::~MegaInterface()
{
    delete ui;
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
#if 1
    QStringList strListHeader;
    strListHeader << "IP" << "Manufacturer" << "Type" << "SN" << "Version";
    m_model->setHorizontalHeaderLabels(strListHeader);
#endif

    int maxRow = m_model->rowCount();
    QStringList strListInfo = str.split(',', QString::SkipEmptyParts);
    for(int index=0; index<strListInfo.count(); index++)
    {
        QStandardItem *t_item = new QStandardItem(strListInfo.at(index));
        m_itemList.append(t_item);
        m_model->setItem(maxRow, index, t_item);
    }
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
    if(!((ui->tableView->selectionModel()->selectedIndexes()).empty()))
    {
        if(m_menu != NULL)
            delete m_menu;

        m_menu = new QMenu(ui->tableView);
        QAction *actionOpen = m_menu->addAction(tr("ON"));
        QAction *actionClose = m_menu->addAction(tr("OFF"));

        connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(soltActionOpen()));
        connect(actionClose, SIGNAL(triggered(bool)), this, SLOT(soltActionClose()));

        m_menu->exec(QCursor::pos());
        ui->tableView->selectionModel()->clear();
    }
}

void MegaInterface::soltActionOpen()
{
    int visa = deviceOpen();
    if(visa <= 0)
        return;

    mrgIdentify(visa, 1);
    mrgCloseGateWay(visa);
}

void MegaInterface::soltActionClose()
{
    int visa = deviceOpen();
    if(visa <= 0)
        return;

    mrgIdentify(visa, 0);
    mrgCloseGateWay(visa);
}

void MegaInterface::slotSelectDevices()
{
    QString strDevInfo = "";
    QList<QModelIndex> modelList =  ui->tableView->selectionModel()->selectedIndexes();
    for(int i=0;i<modelList.count(); i++)
    {
        strDevInfo += m_model->data(modelList.at(i),Qt::DisplayRole).toString();
        strDevInfo += ",";
    }
    if(strDevInfo.split(",").count() >= 5)
    {
        emit signal_selected_info(strDevInfo);
    }
}

int MegaInterface::deviceOpen()
{
    QModelIndex index = ui->tableView->selectionModel()->selectedIndexes().at(0);
    QString strIP = m_model->data(index,Qt::DisplayRole).toString();
    QString strDesc = QString("TCPIP0::%1::inst0::INSTR").arg(strIP);
    int visa =  mrgOpenGateWay(strDesc.toLocal8Bit().data(), 3000);
    if(visa <= 0){
        QMessageBox::critical(this,tr("error"),tr("open device error"));
    }
    return visa;
}

void MegaInterface::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole( button );
    if ( QDialogButtonBox::AcceptRole == role )
    {
        slotSelectDevices();
    }
    else
    {}
    close();
}


/////////////////////////////////////////////////////////////
void DeviceSearchThread::run()
{
    QString strFindDevices;
    if(m_type == TYPE_LAN)
    {
        char buff[4096] = "";
        mrgFindGateWay(0, buff, sizeof(buff), 1);
        strFindDevices = QString("%1").arg(buff);
        if(strFindDevices.length() == 0)
        {
            sysError("mrgFindGateWay LAN Null!");
            return;
        }
    }
    else if(m_type == TYPE_USB)
    {
        char buff[4096] = "";
        mrgFindGateWay(1, buff, sizeof(buff), 1);
        strFindDevices = QString("%1").arg(buff);
        if(strFindDevices.length() == 0)
        {
            sysError("mrgFindGateWay USB error!");
            return;
        }
    }
    qDebug() << "find devices:" << strFindDevices;

    QStringList listFindDevices = strFindDevices.split(',', QString::SkipEmptyParts);
    for(int devIndex=0; devIndex<listFindDevices.count(); devIndex++)
    {
        QString strDevice = listFindDevices.at(devIndex);
        int visa =  mrgOpenGateWay(strDevice.toLocal8Bit().data(), 2000);
        if(visa <= 0) {
            continue;
        }

        char IDN[1024] = "";
        int ret = mrgGateWayIDNQuery(visa,IDN);
        if(ret != 0)
        {
            mrgCloseGateWay(visa);
            continue;
        }else{
            int len = strlen(IDN);
            IDN[len-1] = '\0';  // '\n' ===> '\0'
        }
        mrgCloseGateWay(visa);

        QStringList lst = strDevice.split("::", QString::SkipEmptyParts);
        emit resultReady(lst.at(1) + QString(",%1").arg(IDN));
    }
}

void DeviceSearchThread::setType(int type)
{
    m_type = type;
}
