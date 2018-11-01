#include "megainterface.h"
#include "ui_megainterface.h"

#include <QByteArray>
#include <QDebug>

//#include "visa.h"
//#include "MegaGateway.h"


MegaInterface::MegaInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MegaInterface),
    m_devType(TYPE_LAN),
    m_menu(NULL)
{
    ui->setupUi(this);

    connect(ui->comboBox_DevType,SIGNAL(currentIndexChanged(int)),this,SLOT(slotChangeDeviceType(int)));
    connect(ui->pushButton_Scan,SIGNAL(clicked(bool)),this,SLOT(slotScanDevices()));

    m_model = new QStandardItemModel(ui->listView);
    ui->listView->setModel(m_model);

    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowContextmenu(const QPoint&)));


}

MegaInterface::~MegaInterface()
{
    delete ui;
}

void MegaInterface::insertOneRow(QString str)
{
    int maxRow = m_model->rowCount();
    QStandardItem *t_item = new QStandardItem(str);
    m_itemList.append(t_item);
    m_model->setItem(maxRow, 0, m_itemList.at(maxRow));

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
        m_devType = TYPE_LAN;
    }
}

void MegaInterface::clearListView()
{
    for(int i=0; i<m_itemList.count(); i++)
    {   delete m_itemList.at(i);   }
    m_itemList.clear();
    m_model->clear();
}

void MegaInterface::slotScanDevices()
{

    if(m_devType == TYPE_LAN)
    {        
        clearListView();
#if 0
        char out[1024] = "";
        mrgFindGateWay(QString("").toLatin1().data(), out, sizeof(out), 1);
        QString desc = QString("%1").arg(out);
        if(desc.length() == 0)
        {
            qDebug() << "mrgFindGateWay failure";
            return;
        }
        QStringList descLst = desc.split(',', QString::SkipEmptyParts);
        qDebug() << descLst;
        for(int devIndex=0; devIndex<descLst.count(); devIndex++)
        {   insertOneRow(descLst.at(devIndex));     }
#else
        insertOneRow("test_device11");
        insertOneRow("test_device22");
        insertOneRow("test_device33");
#endif

    }else if(m_devType == TYPE_USB)
    {



    }
}

void MegaInterface::soltActionOpen()
{
    qDebug() << "open " << ui->listView->selectionModel()->selectedIndexes();
}
void MegaInterface::soltActionClose()
{
    qDebug() << "close " << ui->listView->selectionModel()->selectedIndexes();
}

void MegaInterface::slotShowContextmenu(const QPoint& pos)
{
    if(!((ui->listView->selectionModel()->selectedIndexes()).empty()))
    {
        qDebug() << "slotShowContextmenu" << ui->listView->selectionModel()->selectedIndexes();

        if(m_menu != NULL)
            delete m_menu;

        m_menu = new QMenu(ui->listView);
        QAction *actionOpen = m_menu->addAction("打开");
        QAction *actionClose = m_menu->addAction("关闭");

        connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(soltActionOpen()));
        connect(actionClose, SIGNAL(triggered(bool)), this, SLOT(soltActionClose()));

        m_menu->exec(QCursor::pos()); //在当前鼠标位置显示

        //把选中的清楚
        ui->listView->selectionModel()->clear();
    }
}



