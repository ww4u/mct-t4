#include "megainterface.h"
#include "ui_megainterface.h"

#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

#include "MegaGateway.h"
#include "sysapi.h"
#include "xthread.h"
#include "../include/mystd.h"

#define ICON_WIDTH      64
#define ICON_HEIGHT     64

QString MegaInterface::megaMrxTypeToString( int type )
{
    if ( type == MRX_TYPE_T4 )
    { return "MRX-T4"; }
    else if ( type == MRX_TYPE_H2 )
    { return "MRX-H2"; }
    else
    { return ""; }
}

MegaInterface::MegaInterface(SysPara *pPara, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MegaInterface), m_pPara( pPara )
{
    ui->setupUi(this);

    m_devType = TYPE_LAN;
    m_menu = NULL;

    setupMenu();

    buildConnection();

    retranslateUi();

    m_model = new QStandardItemModel(ui->tableView);
    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setDefaultAlignment( Qt::AlignLeft );
    ui->tableView->horizontalHeader()->setDefaultSectionSize( 150 );

    //! context menu
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowContextmenu(const QPoint&)));

    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(slotSelectDevices()));

    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(close()));

    //! interface type
    ui->comboBox_DevType->setCurrentIndex( m_pPara->mIntfIndex );
    on_comboBox_DevType_currentIndexChanged( ui->comboBox_DevType->currentIndex() );

    //! \note disable usb
    ui->comboBox_DevType->setEnabled( false );
}

MegaInterface::~MegaInterface()
{
    delete ui;
}

void MegaInterface::setupMenu()
{
    m_menu = new QMenu( this );
    Q_ASSERT( NULL != m_menu );

    m_pActionOpen = m_menu->addAction( tr("Identify ON") );
    m_pActionClose = m_menu->addAction( tr("Identify OFF") );

    Q_ASSERT( NULL != m_pActionOpen );
    Q_ASSERT( NULL != m_pActionClose );
}
void MegaInterface::buildConnection()
{
    connect( m_pActionOpen, SIGNAL(triggered(bool)),
             this, SLOT(soltActionOpen()));
    connect( m_pActionClose, SIGNAL(triggered(bool)),
             this, SLOT(soltActionClose()));
}
void MegaInterface::retranslateUi()
{
    m_pActionOpen->setText( tr("Identify ON") );
    m_pActionClose->setText( tr("Identify OFF") );
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

int MegaInterface::deviceOpen()
{
    //! current
    QModelIndex index = ui->tableView->selectionModel()->selectedIndexes().at(0);
    QString strAddr = m_model->data(index,Qt::DisplayRole).toString();

    //! open
    int visa =  mrgOpenGateWay( strAddr.toLocal8Bit().data(), 3000 );
    if(visa <= 0){
        QMessageBox::critical(this,tr("error"),tr("open device error"));
    }
    return visa;
}

void MegaInterface::slotDeviceScanEnd()
{
    ui->pushButton_Scan->setEnabled(true);
    ui->progressBar->setMaximum(100);
    ui->progressBar->hide();
}

void MegaInterface::slotShowSearchResult( QVariant var )
{
    if ( var.isValid() )
    {}
    else
    { return; }

    QStringList strListHeader;
    if(m_devType == TYPE_LAN)
    {
        strListHeader<< tr("IP")
                     << tr("Type")
                     << tr("SN")
                     << tr("Version")
                     << tr("Model");
    }
    else if(m_devType == TYPE_USB)
    {
        strListHeader<<tr("USBID")
                     << tr("Type")
                     << tr("SN")
                     << tr("Version")
                     << tr("Model");
    }
    else
    { Q_ASSERT(false); }

    m_model->setHorizontalHeaderLabels(strListHeader);

    QStandardItem *t_item;
    int rowCnt = 0;
    foreach( const RoboInfo &info, mSearchRobos )
    {

        t_item = new QStandardItem( info.mAddr );
        m_model->setItem( rowCnt, 0, t_item );

        t_item = new QStandardItem( info.mFMModel );
        m_model->setItem( rowCnt, 1, t_item );

        t_item = new QStandardItem( info.mFMSN );
        m_model->setItem( rowCnt, 2, t_item );

        t_item = new QStandardItem( info.mFMVer );
        m_model->setItem( rowCnt, 3, t_item );

        t_item = new QStandardItem( info.mRoboModel );
        m_model->setItem( rowCnt, 4, t_item );

//        t_item = new QStandardItem( info.mId );
//        m_model->setItem( rowCnt, 5, t_item );

        rowCnt++;
    }
}

//void MegaInterface::slotShowSearchResult(QString strDevices)
//{
//    QStringList strListHeader;
//    if(m_devType == TYPE_LAN)
//    {
//        strListHeader << tr("IP") << tr("Manufacturer") << tr("Type") << tr("SN") << tr("Version");
//    }
//    else if(m_devType == TYPE_USB)
//    {
//        strListHeader << tr("USBID") << tr("Manufacturer") << tr("Type") << tr("SN") << tr("Version");
//    }
//    else
//    { Q_ASSERT(false); }

//    m_model->setHorizontalHeaderLabels(strListHeader);

//    foreach (QString strDev, strDevices.split("::", QString::SkipEmptyParts))
//    {
//        int maxRow = m_model->rowCount();
//        QStringList strListInfo = strDev.split(',', QString::SkipEmptyParts);
//        for(int index=0; index<strListInfo.count(); index++)
//        {
//            QStandardItem *t_item = new QStandardItem(strListInfo.at(index));
//            m_itemList.append(t_item);
//            m_model->setItem(maxRow, index, t_item);
//        }
//    }

//    //! 自动调整列宽
//    ui->tableView->resizeColumnsToContents();
//    for(int i = 0; i < ui->tableView->horizontalHeader()->count() - 1; i++){
//        ui->tableView->setColumnWidth(i, ui->tableView->columnWidth(i) + 10);
//    }
//    ui->tableView->horizontalHeader()->setStretchLastSection(true);
//}

void MegaInterface::slotShowContextmenu(const QPoint& pos)
{
    //! selected
    if(!((ui->tableView->selectionModel()->selectedIndexes()).empty()))
    {
        Q_ASSERT( NULL != m_menu );

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
    //! only one item
    QString strAddr = m_model->data( m_model->index(  ui->tableView->currentIndex().row(), 0 ), Qt::DisplayRole ).toString();
    QString strFullAddr = strAddr;

    QString strModel = m_model->data( m_model->index(  ui->tableView->currentIndex().row(), 4 ), Qt::DisplayRole ).toString();

    QString firmwareVer = m_model->data( m_model->index(  ui->tableView->currentIndex().row(), 3 ), Qt::DisplayRole ).toString();
    QString sn = m_model->data( m_model->index(  ui->tableView->currentIndex().row(), 2 ), Qt::DisplayRole ).toString();
    //! \todo get the mechanical ver from the protocol
    QString mechanicalVer = "1.0";

    //! append the item
    //! "addr,model,sn,firmwareVer,mechanicalVer"
    //!
    QStringList strList;
    strList<<QString("%1,%2,%3,%4,%5").arg( strFullAddr).arg( strModel ).arg(sn).arg(firmwareVer).arg(mechanicalVer);
    logDbg()<<strList;

    emit signalSelectedInfo(strList);
}

void MegaInterface::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole( button );
    if ( QDialogButtonBox::AcceptRole == role )
    {
        slotSelectDevices();
    }
    close();
}

void MegaInterface::on_pushButton_Scan_clicked()
{
//    auto func = [this]( QString &strRet )
//    auto func = [this]( QList<RoboInfo> &robos )
    auto func = [this]( void *ptr )
    {
        Q_ASSERT( NULL != ptr );
        QList<RoboInfo> *pRoboList = (QList<RoboInfo> *)ptr;

        QString strFindDevices = "";

        char buff[4096] = "";

        int devCnt;
        if(m_devType == TYPE_LAN)
        { devCnt = mrgFindGateWay(0, buff, sizeof(buff), 1); }
        else if(m_devType == TYPE_USB)
        { devCnt = mrgFindGateWay(1, buff, sizeof(buff), 1); }
        else
        { return; }

        //! split
        strFindDevices = QString("%1").arg(buff);
        sysInfo( strFindDevices );

        int idCnt;
        RoboInfo tInfo;
        foreach ( QString strDevice, strFindDevices.split(',', QString::SkipEmptyParts) )
        {
            sysInfo( strDevice );

            int visa =  mrgOpenGateWay(strDevice.toLocal8Bit().data(), 2000);
            if(visa <= 0)
            {
                sysError( strDevice + " " + tr("Open fail!")  );
                continue;
            }

            do
            {
                //! idn query
                char IDN[128] = "";
                int ret = mrgGateWayIDNQuery(visa,IDN);
                if(ret != 0)
                {
                    break;
                }

                tInfo.mAddr = strDevice;
                tInfo.mRawInfo = QString("%1").arg( IDN );

                //! split the idn
                QStringList infoList;
                infoList = tInfo.mRawInfo.split(',', QString::SkipEmptyParts );
                if ( infoList.size() == 4 )
                {}
                else
                { break; }
                tInfo.mFMModel = infoList.at( 1 );
                tInfo.mFMSN = infoList.at(2);
                tInfo.mFMVer = infoList.at(3);

                //! device name
                int roboIds[128];
                idCnt = mrgGetRobotName( visa, roboIds );
                if ( idCnt < 1 )
                { break; }

//                char roboType[64];
                QString strType;
                for ( int i = 0; i < idCnt; i++ )
                {
                    logDbg()<<roboIds[i];
                    ret = mrgGetRobotType( visa, roboIds[i] );
                    if ( ret < 0 || ret >= MRX_TYPE_UNKOWN )
                    { continue; }
                    else
                    {  }

                    strType = megaMrxTypeToString( ret );
                    if ( strType.length() < 1 )
                    { continue; }

                    tInfo.mId = roboIds[i];
                    tInfo.mRoboModel = QString("%1").arg( strType );
                    tInfo.mRoboSN = "";

                    sysInfo( IDN );
                    sysInfo( QString("%1 %2").arg( tInfo.mRoboModel).arg( tInfo.mId ) );

                    //! append
                    pRoboList->append( tInfo );
                }

            }while( 0 );

            mrgCloseGateWay(visa);
        }

        return;
    };

    //! init
    clearListView();

    mSearchRobos.clear();

    //! attach
    XThread *thread = new XThread( func, &mSearchRobos );

    connect(thread, SIGNAL(finished()), this, SLOT(slotDeviceScanEnd()));
    connect(thread, SIGNAL(signalFinishResult( QVariant ) ),
            this, SLOT(slotShowSearchResult( QVariant )));

    ui->pushButton_Scan->setEnabled(false);
    ui->progressBar->setMaximum(0);
    ui->progressBar->show();

    thread->start();
}

void MegaInterface::on_comboBox_DevType_currentIndexChanged(int index)
{
    QIcon icon = ui->comboBox_DevType->itemIcon( index );
    if( icon.isNull() )
    { ui->label_icon->setVisible(false);}
    else
    {
        ui->label_icon->setVisible( true );
        ui->label_icon->setPixmap( icon.pixmap( ICON_WIDTH, ICON_HEIGHT ) );

        //! save the setting
        m_pPara->mIntfIndex = index;
        emit signal_setting_changed();
    }
}
