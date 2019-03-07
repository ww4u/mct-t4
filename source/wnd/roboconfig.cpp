#include "roboconfig.h"
#include "ui_roboconfig.h"

#include "mystd.h"
#include "h2robo.h"
#include "xthread.h"
#include "welcomepage.h"

#define plugin_changed()    emit signal_plugins_changed();

RoboConfig::RoboConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoboConfig)
{
//    mIndex = -1;

    m_megaSerachWidget = NULL;
    m_pOpDock = NULL;

    m_pLogModel = NULL;
    m_pPref = NULL;

    m_pRoboContextMenu = NULL;
    m_pActionOpen = NULL;
    m_pActionClose = NULL;
    m_pActionRst = NULL;

    ui->setupUi(this);

    setupUi();

    //! connect
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowContextmenu(const QPoint&)));

    connect( this, SIGNAL(signal_plugins_changed()),
             this, SLOT(slot_plugins_changed()) );

    //! init to hide
    //! \note
    ui->buttonBox->button( QDialogButtonBox::Reset )->setVisible( false );

#ifndef _WIN32
    //! 如果在MRH-T上运行自动添加本地
    addDeviceWithIP("127.0.0.1");
#endif
}

RoboConfig::~RoboConfig()
{
    delete ui;

    delete_all( mPluginList );
}

void RoboConfig::setupUi()
{
    m_pRootNode = new QTreeWidgetItem();
    m_pRootNode->setText( 0, tr("Project"));
    m_pRootNode->setIcon( 0, QIcon( ":/res/image/icon/201.png" ) );
    ui->treeWidget->addTopLevelItem( m_pRootNode );
    ui->treeWidget->setCurrentItem( m_pRootNode );

    //! logon
    WelcomePage *pPage = new WelcomePage();
    m_pRootNode->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(pPage) ) );
    ui->stackedWidget->addWidget( pPage );
}

void RoboConfig::retranslateUi()
{
//    ui->buttonBox->button(QDialogButtonBox::Reset)->setText(tr("Reset"));
    ui->retranslateUi(this);
    m_pRootNode->setText( 0, tr("Project"));
}

//void RoboConfig::loadXmlConfig()
//{
//    //! load xml
//    MegaXML mXML;
//    QString fileName = QApplication::applicationDirPath();
//    QDir dir(fileName);
//    if(!dir.exists()){dir.mkdir(fileName);}

//    fileName += "/config.xml";
//    mXML.xmlCreate(fileName);

//    QMap<QString,QString> mapItems = mXML.xmlRead(fileName);
//    QMap<QString,QString>::iterator itMap;
//    for ( itMap=mapItems.begin(); itMap != mapItems.end(); ++itMap ) {
//        if( "RobotDevice_" == itMap.key().left(QString("RobotDevice_").length()) )
//            createRobot(itMap.value());
//    }
//    ui->treeWidget->setCurrentItem(m_pRootNode);
//}



//! add each robo
void RoboConfig::slotAddNewRobot( const QStringList & strDevInfo)
{
    //! remove the befores
    XPlugin *pPlugin;
    QStringList roboInfo;
    foreach( const QString &str, strDevInfo )
    {
        roboInfo = str.split(',');
        pPlugin = findPlugin( roboInfo.at(0), roboInfo.at(1), roboInfo.at(2) );
        if ( NULL != pPlugin )
        {
            removePlugin( pPlugin );
            sysInfo( roboInfo.join(' ') + " " + tr("removed") );
        }
        else
        { logDbg()<<roboInfo; }
    }

    //! plugin
    //! foreach robot
    foreach( const QString &str, strDevInfo )
    {
        roboInfo = str.split(',');
        createRobot( roboInfo );
    }

//    for(int i=0; i< m_RobotList.count(); i++)
//    {
//        if( m_RobotList[i].m_strDevInfo == strDevInfo)
//        {
//            if( !strDevInfo.contains("127.0.0.1") )
//                QMessageBox::information(this,tr("tips"),tr("The device already exists in the project."));
//            return;
//        }else{
//            //将之前的127.0.0.1从工程中删除
//            if( m_RobotList[i].m_strDevInfo.contains("127.0.0.1") )
//            {
//                //! delete from xml file
//                MegaXML mXML;
//                QString fileName = QApplication::applicationDirPath() + "/config.xml";
//                QMap<QString,QString> mapRead = mXML.xmlRead(fileName);
//                QMap<QString,QString> mapWrite;
//                for (QMap<QString,QString>::iterator itMap=mapRead.begin(); itMap != mapRead.end(); ++itMap )
//                {
//                    if( "RobotDevice_" == itMap.key().left(QString("RobotDevice_").length())
//                            && m_RobotList[i].m_strDevInfo != itMap.value() ){
//                        mapWrite.insert(itMap.key(),itMap.value());
//                    }
//                }
//                mXML.xmlNodeRemove(fileName, "RobotConfigs");
//                mXML.xmlNodeAppend(fileName, "RobotConfigs", mapWrite); //update config.xml
//            }
//        }
//    }
//    qDebug() << "slotAddNewRobot" << strDevInfo;

//    createRobot(strDevInfo);

//    //添加到config.xml中
//    MegaXML mXML;
//    QString fileName = QApplication::applicationDirPath() + "/config.xml";

//    QMap<QString,QString> mapRead = mXML.xmlRead(fileName);
//    QMap<QString,QString> mapWrite;
//    for (QMap<QString,QString>::iterator itMap=mapRead.begin(); itMap != mapRead.end(); ++itMap ) {
//        if( "RobotDevice_" == itMap.key().left(QString("RobotDevice_").length()) )
//        {   mapWrite.insert(itMap.key(),itMap.value()); }
//    }
//    QString proName = QString("RobotDevice_%1").arg(mapWrite.size());
//    mapWrite.insert(proName ,strDevInfo );
//    mXML.xmlNodeRemove(fileName, "RobotConfigs");
//    mXML.xmlNodeAppend(fileName, "RobotConfigs", mapWrite);

//    QString strIP = strDevInfo.split(',').at(0);
//    slot_open_close(strIP); //默认打开设备

//    //第一次打开设备将数据同步到上位机
//    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs()){
//        int ret = pCfg->readDeviceConfig();
//        if(ret != 0){
//            QMessageBox::critical(this,tr("error"), pCfg->focuHelpName() + "\n" +tr("From device upload config faiured"));
//        }
//        pCfg->updateShow();
//        pCfg->saveConfig();
//        emit signalDataChanged();
//    }
}

void RoboConfig::slotDownload()
{
    int ret;
    //! for each plugin
    for ( int i = 0; i < mPluginList.size(); i++ )
    {
        //! \todo progress

        if ( mPluginList.at(i)->isOpened() )
        {
            sysInfo( mPluginList.at(i)->SN() + " " + tr("is not opened") );
        }
        else
        { continue; }

        ret = mPluginList.at(i)->download();
        if ( ret != 0 )
        {
            sysError( mPluginList.at(i)->SN() + " " + tr("download fail") );
        }
    }

//    if(mIndex < 0) return;
//    if( m_RobotList[mIndex].m_Visa == 0)
//    {
//        QMessageBox::warning(this,tr("warning"),tr("Current Device In Offline"));
//        return;//offline
//    }

//    bool ok = true;
//    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs()){
//        pCfg->saveConfig();
//        int ret = pCfg->writeDeviceConfig();
//        if(ret != 0){
//            ok = false;
//            QMessageBox::critical(this,tr("error"), pCfg->focuHelpName() + "\n" + tr("Download Failure"));
//            continue;
//        }

//        {   //从设备再重新upload一遍
//            int ret = pCfg->readDeviceConfig();
//            if(ret != 0){
//                ok = false;
//                QMessageBox::critical(this,tr("error"), pCfg->focuHelpName() + "\n" + tr("Download Failure"));
//            }
//            pCfg->updateShow();
//            pCfg->saveConfig();
//        }
//    }
//    emit signalDataChanged();
//    if(ok){
//        QMessageBox::information(this,tr("tips"),tr("Download Success!"));
//    }
//    qDebug() << "slotDownload Finish";

//    return;
}

void RoboConfig::slotUpload()
{
    int ret;
    //! for each plugin
    for ( int i = 0; i < mPluginList.size(); i++ )
    {
        //! \todo progress

        if ( mPluginList.at(i)->isOpened() )
        {
            sysInfo( mPluginList.at(i)->SN() + " " + tr("is not opened") );
        }
        else
        { continue; }

        ret = mPluginList.at(i)->upload();
        if ( ret != 0 )
        {
            sysError( mPluginList.at(i)->SN() + " " + tr("download fail") );
        }
    }

//    if(mIndex < 0) return;

//    if( m_RobotList[mIndex].m_Visa == 0)
//    {
//        QMessageBox::warning(this,tr("warning"),tr("Current Device In Offline"));
//        return;
//    }

//    bool ok = true;
//    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs()){
//        int ret = pCfg->readDeviceConfig();
//        if(ret != 0){
//            ok = false;
//            QMessageBox::critical(this,tr("error"), pCfg->focuHelpName() + "\n" + tr("Upload Faiured"));
//        }
//        pCfg->updateShow();
//        pCfg->saveConfig();
//    }

//    emit signalDataChanged();
//    if(ok){
//        QMessageBox::information(this,tr("tips"),tr("Upload Succeed!"));
//    }
//    qDebug() << "slotUpload Finish";
//    return;
}

void RoboConfig::slotStore()
{
//    if(mIndex < 0) return;
//    int visa = m_RobotList[mIndex].m_Visa;
//    if( visa == 0) {
//        QMessageBox::warning(this,tr("warning"),tr("Current Device In Offline"));
//        return;
//    }

//    auto func = [=](int &ret)
//    {
//        qDebug() << "mrgGetRobotConfigState1";
//        if (mrgGetRobotConfigState(visa) == 1){
//            qDebug() << "mrgGetRobotConfigState == 1";
//            ret = -1;
//            return;
//        }
//        qDebug() << "mrgGetRobotConfigState2";

//        int timeout = 10000;
//        int state = 0;
//        qDebug() << "mrgExportRobotConfig";
//        mrgExportRobotConfig(visa);
//        while (timeout > 0)
//        {
//            QThread::msleep(500);
//            qDebug() << "mrgGetRobotConfigState";
//            state = mrgGetRobotConfigState(visa);
//            if (state != 1) { break;}
//            timeout -= 500;
//        }

//        if(timeout <= 0){
//            ret = -2;
//            return;
//        }

//        if (state == 0){
//            ret = 0;
//        }else{
//            ret = -3;
//        }
//        return;
//    };

//    XThread *thread = new XThread(func);
//    connect(thread,SIGNAL(signalFinishResult(int)),this,SLOT(slotStoreEnd(int)));
//    thread->start();
}

//void RoboConfig::slotStoreEnd(int val)
//{
//    switch (val) {
//    case 0:
//        QMessageBox::information(this,tr("tips"),tr("Store success!"));
//        break;
//    case -1:
//        QMessageBox::warning(this,tr("warning"),tr("Operation in progress!"));
//        break;
//    case -2:
//        QMessageBox::warning(this,tr("warning"),tr("Store timeout!"));
//        break;
//    case -3:
//        QMessageBox::critical(this,tr("error"),tr("Store error!"));
//        break;
//    default:
//        break;
//    }
//}

void RoboConfig::slotSync()
{
    //! TODO
    QMessageBox::warning(this,tr("warning"),tr("unable"));
}

void RoboConfig::slotSearch()
{
    //! create
    if(m_megaSerachWidget == NULL)
    {
        m_megaSerachWidget = new MegaInterface( m_pPref, this );
        if ( NULL == m_megaSerachWidget )
        { return; }

        connect(m_megaSerachWidget, SIGNAL(signalSelectedInfo(const QStringList &)),
                this, SLOT(slotAddNewRobot(const QStringList &)));

        connect( m_megaSerachWidget, SIGNAL(signal_setting_changed()),
                 this, SIGNAL(signal_save_sysPref()) );
    }

    m_megaSerachWidget->show();

    //! auto search
    m_megaSerachWidget->on_pushButton_Scan_clicked();
}

void RoboConfig::slotConnect()
{
    if ( pluginsConnectState() )
    { plginsClose(); }
    else
    { pluginsOpen(); }
}

void RoboConfig::slot_plugins_stop()
{
    pluginsStop();
}

void RoboConfig::slotWifi()
{
//    if(mIndex < 0) return;
//    if( m_RobotList[mIndex].m_Visa == 0)
//    {
//        QMessageBox::warning(this,tr("warning"),tr("Current Device In Offline"));
//        return;
//    }

//    int ret = -1;
//    char wifiList[1024] = "";
//    ret = mrgSysWifiSearch(m_RobotList[mIndex].m_Visa, wifiList);
//    if(ret < 0)
//    {
//        QMessageBox::critical(this,tr("error"),tr("Wifi search error or empty!"));
//        qDebug() << "mrgSysWifiSearch" << ret;
//        return;
//    }

//    QStringList StrList = QString(wifiList).split(",", QString::SkipEmptyParts);

//    //显示选择对话框
//    QString wifiName = QInputDialog::getItem(this, tr("Wifi"), tr("Please choose wifi:"), StrList, -1, false);
//    if(wifiName == "")
//        return;

//    //显示输入对话框获取输入的wifi密码
//    QString password = QInputDialog::getText(this, tr("Input"), tr("Please input wifi password:"), QLineEdit::Password);
//    if(password == "")
//        return;

//    ret = mrgSysWifiConnect(m_RobotList[mIndex].m_Visa, wifiName.toLocal8Bit().data(), password.toLocal8Bit().data());
//    if(ret == 1){
//        QMessageBox::information(this,tr("tips"),tr("Wifi Connect success!"));
//    }
//    else{
//        QMessageBox::critical(this,tr("error"),tr("Wifi Connect error!"));
//        qDebug() << "mrgSysWifiConnect" << ret;
//    }
//    return;
}

//void RoboConfig::slotExit()
//{
//    foreach (RobotInfo robo, m_RobotList ){
//        QString strIP = robo.m_strDevInfo.split(',').at(0);
//        if(robo.m_Visa != 0){
//            //如果没有关闭就关闭设备
//            slot_open_close(strIP);
//        }
//    }

//    if(m_megaSerachWidget != NULL){
//        m_megaSerachWidget->close();
//    }
//}

#define gc_context_menu() { delete m_pRoboContextMenu; m_pRoboContextMenu = NULL; }
void RoboConfig::slotShowContextmenu(const QPoint& pos)
{
    //! current item
    QTreeWidgetItem* curItem = ui->treeWidget->itemAt(pos);
    if(curItem == NULL)
    { return; }

    //! plugin
    QVariant var = curItem->data(0,Qt::UserRole+1);
    if ( var.isValid() )
    {}
    else
    { return; }

    XPlugin *pPlugin = var.value<XPlugin*>();
    if ( NULL == pPlugin )
    { return; }

    //! current
    m_pCurPlugin = pPlugin;
    m_pCurTreeItem = ui->treeWidget->currentItem();

    //! robo type
//    if( "H2Product*" == QString("%1").arg(var.typeName()) )
    {
        if(m_pRoboContextMenu != NULL)
        {}
        else
        {
            m_pRoboContextMenu = new QMenu(ui->treeWidget);
            if ( NULL == m_pRoboContextMenu )
            { return; }

            m_pActionOpen = m_pRoboContextMenu->addAction(tr("Connect"));
            m_pActionOpen->setIcon( QIcon(":/res/image/h2product/connect.png") );
            if ( NULL == m_pActionOpen )
            { gc_context_menu(); return; }

            m_pActionClose = m_pRoboContextMenu->addAction(tr("Disconnect"));
            m_pActionClose->setIcon( QIcon(":/res/image/h2product/disconnect.png") );
            if ( NULL == m_pActionClose )
            { gc_context_menu(); return; }

            m_pActionRst = m_pRoboContextMenu->addAction(tr("Reset"));
            m_pActionRst->setIcon( QIcon(":/res/image/icon/beauty.png") );
            if ( NULL == m_pActionRst )
            { gc_context_menu(); return; }

            QAction *actionDelete = m_pRoboContextMenu->addAction(tr("Delete"));
            actionDelete->setIcon( QIcon(":/res/image/icon/trash.png") );
            if ( NULL == actionDelete )
            { gc_context_menu(); return; }

            if ( NULL== m_pRoboContextMenu->addSeparator() )
            { gc_context_menu(); return; }

            QAction *actionExplorer = m_pRoboContextMenu->addAction( tr("Explorer") );
            actionExplorer->setIcon( QIcon(":/res/image/icon/manage.png") );
            if ( NULL == actionExplorer )
            { gc_context_menu(); return; }

            //! add action
            connect(m_pActionOpen, SIGNAL(triggered(bool)), this, SLOT(slotActionOpen()));
            connect(m_pActionClose, SIGNAL(triggered(bool)), this, SLOT(slotActionClose()));
            connect(m_pActionRst, SIGNAL(triggered(bool)), this, SLOT(slotActionRst()));
            connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(slotActionDelete()));
            connect(actionExplorer, SIGNAL(triggered(bool)), this, SLOT(slotActionExplorer()));
        }

        //! modify
        if ( m_pCurPlugin->isOpened() )
        {
            m_pActionOpen->setVisible(false);
            m_pActionClose->setVisible(true);
            m_pActionRst->setVisible( true );
        }
        else
        {
            m_pActionOpen->setVisible(true);
            m_pActionClose->setVisible(false);
            m_pActionRst->setVisible( false );
        }

        //! pop proc
        m_pRoboContextMenu->exec(QCursor::pos());
    }
}

void RoboConfig::slotActionOpen()
{
    int ret = m_pCurPlugin->open();
    if ( ret != 0 )
    { sysError( tr("Open fail") );}
    else
    {
        //! \todo changed enabled
    }
}

void RoboConfig::slotActionClose()
{
    //! \note lock in the close()
    Q_ASSERT( NULL != m_pCurPlugin );
    m_pCurPlugin->close();
}

void RoboConfig::slotActionRst()
{
    Q_ASSERT( NULL != m_pCurPlugin );
    m_pCurPlugin->rst();
}

void RoboConfig::slotActionDelete()
{
    //! delete + remove the root
    mPluginList.removeAll( m_pCurPlugin );
    plugin_changed();

    delete m_pCurPlugin;

    Q_ASSERT( NULL != m_pCurTreeItem );
    ui->treeWidget->removeItemWidget( m_pCurTreeItem, 0 );
    delete m_pCurTreeItem;
}

void RoboConfig::slotActionExplorer()
{
    Q_ASSERT( NULL != m_pCurPlugin );

    QStringList args;
    QString str;
    str = m_pCurPlugin->homePath();
    str.replace("/", QDir::separator() );
    args<<str;
    //! \todo linux

    QProcess::execute( "explorer.exe", args );
}

void RoboConfig::on_treeWidget_currentItemChanged(QTreeWidgetItem *current,
                                                  QTreeWidgetItem *previous)
{
    stackPageChange( current, previous );

    panelPageChange( current, previous );

    //! change help
}

void RoboConfig::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole( button );
    if ( QDialogButtonBox::ResetRole == role )
    {
        do
        {
            if ( QMessageBox::Yes
                 == QMessageBox::question( this, tr("Reset"), tr("Sure to reset all?") ) )
            { }
            else
            { break; }

            setReset();
        }while( 0 );
    }
    else
    {    }
}

//void RoboConfig::slot_current_changed( QTreeWidgetItem* cur,QTreeWidgetItem* prv )
//{
//    if ( cur == NULL )
//    { return; }

//    QVariant var = QVariant(cur->data( 0, Qt::UserRole) );
//    if ( var.isValid() )
//    {
//        QObject *pObj = var.value<QObject*>();
//        if ( NULL != pObj )
//        {
//            ui->stackedWidget->setCurrentWidget( (QWidget*)pObj );
//        }

//        XPage *pPage = dynamic_cast<XPage*>(pObj);
//        bool bV;
//        if ( NULL != pObj )
//        {
//            bV = has_attr( pPage->pageAttr(), XPage::page_rst_able );
//        }
//        else
//        { bV = false; }
//        ui->buttonBox->button( QDialogButtonBox::Reset )->setVisible( bV );
//    }
//}

//void RoboConfig::slot_open_close(QString strIP)
//{
//    if(mIndex < 0) return;
//    H2Robo *pRobo = (H2Robo *)(m_RobotList[mIndex].m_Robo);

//    if(m_RobotList[mIndex].m_Visa == 0){
//        int ret = deviceOpen(strIP);
//        if(ret > 0){
//            pRobo->change_online_status(true);
//            emit signalDeviceConnect(true);
//        }
//        else{
//            QMessageBox::information(this,tr("tips"),tr("Device Open Failure!!!"));
//        }
//    }else{
//        deviceClose();
//        pRobo->change_online_status(false);
//        emit signalDeviceConnect(true);
//    }

//    //通知OPS
//    emit signalCurrentRobotChanged(m_RobotList[mIndex].m_strDevInfo,
//                                   m_RobotList[mIndex].m_Visa,
//                                   m_RobotList[mIndex].m_DeviceName,
//                                   m_RobotList[mIndex].m_RoboName);
//}

//int RoboConfig::deviceOpen(QString strID)
//{
//    if(mIndex < 0) return -1;
//    int ret = -1;

//    QString strDesc;
//    if(strID.left(3) != "USB")
//    {
//        strDesc = QString("TCPIP0::%1::inst0::INSTR").arg(strID);
//    }
//    else
//    {
//        //USB0::0xA1B2::0x5722::MRHT00000000000001::INSTR
//        QStringList lst = strID.split('_', QString::SkipEmptyParts);
//        strDesc = QString("%1::%2::%3::%4::INSTR")
//                .arg(lst.at(0))
//                .arg(lst.at(1))
//                .arg(lst.at(2))
//                .arg(lst.at(3));
//    }

//    int visa = mrgOpenGateWay(strDesc.toLocal8Bit().data(), 2000);
//    if(visa <= 0){
//        qDebug() << "mrgOpenGateWay error" << visa;
//        sysError("mrgOpenGateWay error");
//        return -1;
//    }

////! 直接搜索机器人和驱控器名字
//    int deviceNames[32] = {0};
//    int roboNames[32] = {0};
//    int deviceName = -1;
//    int roboName = -1;

//    {
//        ret = mrgGetRobotName(visa, roboNames);
//        if( (ret <= 0) || (roboNames[0] == 0) )
//        {
//            qDebug() << "mrgGetRobotName error" << ret;
//            sysError("mrgGetRobotName error");
//            goto BUILD;
//        }
//        roboName = roboNames[0];//默认选择第一个机器人

//        ret = mrgGetRobotDevice(visa, roboName, deviceNames);
//        if( (ret <= 0) || (deviceNames[0] == 0) )
//        {
//            qDebug() << "mrgGetRobotDevice error" << ret;
//            sysError("mrgGetRobotDevice error");
//            goto BUILD;
//        }
//        deviceName = deviceNames[0];//默认选择第一个驱控器
//        goto END;
//    }

//BUILD:
//    {
//        //! 构建机器人
//        ret = mrgFindDevice(visa, 2000);
//        if(ret <= 0){
//            qDebug() << "mrgFindDevice error" << ret;
//            sysError("mrgFindDevice error", ret);
//            return -4;
//        }

//        //读取设备名称
//        ret = mrgGetDeviceName(visa, deviceNames);
//        if ( (ret == 0) || (deviceNames[0] == 0) ){
//            qDebug() << "mrgGetDeviceName error" << ret;
//            sysError("mrgGetDeviceName error", ret);
//            return -5;
//        }
//        deviceName = deviceNames[0];//默认选择第一个驱控器

//        char deviceType[128] = "";
//        if ( mrgGetDeviceType(visa, deviceName, deviceType) != 0 ){
//            qDebug() << "mrgGetDeviceType error";
//            sysError("mrgGetDeviceType error");
//            return -6;
//        }

//        ret = mrgBuildRobot(visa, "MRX-H2", QString("0@%1,1@%1").arg(deviceName).toLocal8Bit().data(), roboNames);
//        if( (ret < 0) || (roboNames[0] == 0)){
//            qDebug() << "mrgBuildRobot error" << ret;
//            sysError("mrgBuildRobot error", ret);
//            return -7;
//        }
//        ret = mrgGetRobotName(visa, roboNames);
//        if( (ret <= 0) || (roboNames[0] == 0) ){
//            qDebug() << "mrgGetRobotName error" << ret;
//            sysError("mrgGetRobotName error");
//            return -8;
//        }
//        roboName = roboNames[0];//默认选择第一个机器人
//    }

//END:
//    //判断机器人类型是否是H2
////    if(2 != mrgGetRobotType(visa, roboName)){
//        QMessageBox::critical(this,tr("error"),tr("Robot type not") + "MRX-H2");
////        return -10;
////    }

//    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
//    {    pCfg->attachHandle( visa, deviceName, roboName);  }

//    mrgIdentify(visa, 0); //关闭识别防止用户之前打开

//    qDebug() << "device open" << strID << visa;
//    sysInfo("Device Open", visa);

//    m_RobotList[mIndex].m_Visa = visa;
//    m_RobotList[mIndex].m_DeviceName = deviceName;
//    m_RobotList[mIndex].m_RoboName = roboName;
//    return visa;
//}

//int RoboConfig::deviceClose()
//{
//    if(mIndex < 0) return -1;

//    mrgIdentify(m_RobotList[mIndex].m_Visa, 0);

    //电机关闭
//    int ret = mrgMRQDriverState(m_RobotList[mIndex].m_Visa, m_RobotList[mIndex].m_DeviceName, 0, 0);
//    qDebug() << "mrgMRQDriverState0 OFF" << ret;

//    ret = mrgMRQDriverState(m_RobotList[mIndex].m_Visa, m_RobotList[mIndex].m_DeviceName, 1, 0);
//    qDebug() << "mrgMRQDriverState1 OFF" << ret;
//    QThread::msleep(300);

//    ret = mrgCloseGateWay(m_RobotList[mIndex].m_Visa);

//    qDebug() << "device close" << m_RobotList[mIndex].m_Visa << ret;
//    sysInfo("Device Close");

//    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
//    {    pCfg->detachHandle();  }

//    m_RobotList[mIndex].m_Visa = 0;
//    m_RobotList[mIndex].m_DeviceName = 0;
//    m_RobotList[mIndex].m_RoboName = 0;

//    return ret;
//}

//void RoboConfig::changeLanguage(QString qmFile)
//{
//    for(int index=0; index<m_RobotList.size(); index++)
//    {
//        m_RobotList[index].m_Robo->changeLanguage(qmFile);
//        foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[index].m_Robo)->subConfigs()){
//            pCfg->changeLanguage(qmFile);
//        }
//    }

//    qApp->removeTranslator(&m_translator);
//    m_translator.load(qmFile);
//    qApp->installTranslator(&m_translator);

//    translateUi();
//}


//void RoboConfig::slotSetOneRecord(int row, QString type, double x, double y, double v, double a)
//{
//    if(mIndex < 0) return;
//    if(row < 0) return;

//    H2Robo *pRobo = (H2Robo *)(m_RobotList[mIndex].m_Robo);
//    H2Action *pAction = (H2Action *)(pRobo->subConfigs().at(5));

//    if(m_RobotList[mIndex].m_Visa > 0){
//        pAction->modfiyOneRecord(row-1, type, x, y, v, a);
//    }
//}

//void RoboConfig::addDeviceWithIP(QString strID)
//{
//    QString strDesc;
//    if(strID.left(3) != "USB")
//    {
//        strDesc = QString("TCPIP0::%1::inst0::INSTR").arg(strID);
//    }
//    else
//    {
//        //USB0::0xA1B2::0x5722::MRHT00000000000001::INSTR
//        QStringList lst = strID.split('_', QString::SkipEmptyParts);
//        strDesc = QString("%1::%2::%3::%4::INSTR")
//                .arg(lst.at(0))
//                .arg(lst.at(1))
//                .arg(lst.at(2))
//                .arg(lst.at(3));
//    }

//    int visa =  mrgOpenGateWay(strDesc.toLocal8Bit().data(), 2000);
//    if(visa <= 0) {
//        return;
//    }

//    char IDN[1024] = "";
//    int ret = mrgGateWayIDNQuery(visa,IDN);
//    if(ret != 0)
//    {
//        mrgCloseGateWay(visa);
//        return;
//    }else{
//        int len = strlen(IDN);
//        IDN[len-1] = '\0';
//    }
//    mrgCloseGateWay(visa);

//    QStringList lst = strDesc.split("::", QString::SkipEmptyParts);
//    QString devInfo = lst.at(1) + QString(",%1").arg(IDN);
//    slotAddNewRobot(devInfo);
//}

void RoboConfig::attachOpDock( QDockWidget *pDock )
{
    Q_ASSERT( NULL != pDock );
    m_pOpDock = pDock;
}

void RoboConfig::attachLogModel( MegaLogListModel *pModel )
{
    Q_ASSERT( NULL != pModel );
    m_pLogModel = pModel;
}

void RoboConfig::attachSysPref( SysPara *pPref )
{
    Q_ASSERT( NULL != pPref );
    m_pPref = pPref;
}

void RoboConfig::attachConnectWidget( QAction *pAction )
{
    Q_ASSERT( NULL != pAction );
    m_pConnAction = pAction;
}

void RoboConfig::postStartup()
{
    Q_ASSERT( NULL != m_pPref );
logDbg();
    //! search
    if ( m_pPref->mbAutoSearch )
    { slotSearch(); }
logDbg();
    //! load
    //! \note load last corrupt
    //! \todo
    if ( m_pPref->mbAutoLoad )
    {
        QString strItem;

        //! get the back up
        QStringList lastPlugin = m_pPref->mPlugins;
        for ( int i = 0; i < lastPlugin.size(); i++ )
        {
            strItem = lastPlugin.at(i);
            createRobot( strItem.split(',') );
        }
    }

    on_treeWidget_currentItemChanged( ui->treeWidget->currentItem(),
                                      NULL );
}

void RoboConfig::cancelBgWorking()
{
    foreach( XPlugin *pPlugin, mPluginList )
    {
        Q_ASSERT( NULL != pPlugin );
        pPlugin->cancelBgWorking();
    }
}

QTreeWidgetItem *RoboConfig::rootItem()
{ return m_pRootNode; }
QStackedWidget *RoboConfig::stackWidget()
{ return ui->stackedWidget; }


void RoboConfig::stackPageChange( QTreeWidgetItem *current,
                      QTreeWidgetItem *previous )
{
    if ( current == NULL )
    { return; }

    QVariant var = QVariant(current->data( 0, Qt::UserRole) );
    if ( var.isValid() )
    {
        QObject *pObj = var.value<QObject*>();
        if ( NULL != pObj )
        {
            ui->stackedWidget->setCurrentWidget( (QWidget*)pObj );
        }

        //! page
        XPage *pPage = dynamic_cast<XPage*>(pObj);
        bool bV;
        if ( NULL != pObj )
        { bV = has_attr( pPage->pageAttr(), XPage::page_rst_able ); }
        else
        { bV = false; }
        ui->buttonBox->button( QDialogButtonBox::Reset )->setVisible( bV );
    }
}
void RoboConfig::panelPageChange( QTreeWidgetItem *current,
                      QTreeWidgetItem *previous )
{
    do
    {
        if ( NULL == current )
        { return; }

        //! page or robot
        QVariant var;
        var = current->data( 0, Qt::UserRole );
        if ( var.isValid() )
        {
            if ( m_pRootNode == current )
            { break; }
        }
        else
        { break; }

        //! plugin
        var = current->data( 0, Qt::UserRole + 1 );
        if ( var.isValid() )
        {
            //! switch the robot
            XPlugin *pPlugin = var.value<XPlugin*>();
            if ( NULL == pPlugin )
            { return; }

            //! active
            pPlugin->setActive();
            return;
        }
    }while( 0 );

    //! no plugin, switch to the root op panel
    emit signal_request_sysOpPanel();
}

#include "../plugin/factory/pluginfactory.h"
//! addr,model,sn,firmwareVer,mechanicalVer
void RoboConfig::createRobot( const QStringList &strInfos )
{logDbg()<<strInfos;
    //! create
    XPlugin *plugin = PluginFactory::createPlugin( strInfos.at(1), strInfos.at(0) );
    if ( NULL == plugin )
    {
        sysError( tr("No model") + " " + strInfos.at(1) );
        return;
    }

    //! connect plugin
    connect( plugin, SIGNAL(signal_focus_changed(const QString &,const QString &)),
             this, SIGNAL(signal_focus_in(const QString &,const QString &)));

    //! config plugin
    plugin->setAddr( strInfos.at(0) );
    plugin->setModel( strInfos.at(1) );

    plugin->setSN( strInfos.at(2) );
    plugin->setFirmwareVer( strInfos.at(3) );
    plugin->setMechanicalVer( strInfos.at(4) );

    //! cache plugin
    addPlugin( plugin );

    //! ops panel
    Q_ASSERT( NULL != m_pLogModel );
    QWidget *pWig = plugin->createOpsPanel( m_pLogModel, nullptr );
    if ( NULL != pWig )
    {
        pWig->show();
        m_pOpDock->setWidget( pWig );
    }

    plugin->attachDock( m_pOpDock );
    plugin->attachPanel( pWig );

logDbg();
    //! pref pages
    //! \note pRoboRoot is managed by the tree
    QTreeWidgetItem *pRoboRoot = plugin->createPrefPages( stackWidget() );logDbg()<<pRoboRoot;
    pRoboRoot->setToolTip( 0, plugin->addr() );
    plugin->setViewObj( pRoboRoot );
    rootItem()->addChild( pRoboRoot );
logDbg();
    //! auto expand
    rootItem()->setExpanded( true );
    { pRoboRoot->setExpanded( m_pPref->mbAutoExpand ); }

    //! try load the setup from the local
    plugin->emit_load();

    //! open
    if ( plugin->open() == 0 )
    {}
    else
    {
        sysError(  strInfos.at(0) + " " + tr("open fail") );
    }

    //! synclize the setup from the device
    //! \todo
logDbg();

}

void RoboConfig::removePlugin( XPlugin *plugin )
{
    Q_ASSERT( NULL != plugin );

    rootItem()->removeChild( (QTreeWidgetItem*)plugin->viewObj() );

    mPluginList.removeAll( plugin );
    plugin_changed();

    delete plugin;
}

void RoboConfig::addPlugin( XPlugin *plugin )
{
    Q_ASSERT( NULL != plugin );

    mPluginList.append( plugin );

    connect( plugin, SIGNAL(signal_setting_changed(XSetting)),
             this, SLOT(slot_plugin_setting_changed(XSetting)));

    plugin_changed();
}

XPlugin* RoboConfig::findPlugin( const QString &_addr,
                             const QString &_model,
                             const QString &_sn )
{
    foreach( XPlugin *pPlugin, mPluginList )
    {
        Q_ASSERT( NULL != pPlugin );

        if ( pPlugin->isEqual( _addr, _model, _sn ) )
        { return pPlugin; }
    }

    return NULL;
}

int RoboConfig::setReset()
{
    //! \todo reset the current page


//    ui->stackedWidget->curr
    XPage *pPage;

    pPage = (XPage*)ui->stackedWidget->currentWidget();
    if ( NULL == pPage )
    { return -1; }

    //! page rst
    pPage->rst();


//    if(mIndex < 0) return -100;

//    //将默认的配置文件替换掉对应的配置文件，更新界面，写入设备
//    QString strIDN = m_RobotList[mIndex].m_strDevInfo.split(',').at(3);
//    copyFileToPath(QApplication::applicationDirPath() + "/robots/default.xml",
//                   QApplication::applicationDirPath() + "/robots/" + strIDN + ".xml",
//                   true);

//    copyFileToPath(QApplication::applicationDirPath() + "/dataset/action_default.mrp",
//                   QApplication::applicationDirPath() + "/dataset/" + strIDN + ".mrp",
//                   true);

//    copyFileToPath(QApplication::applicationDirPath() + "/dataset/errmgr_default.xml",
//                   QApplication::applicationDirPath() + "/dataset/" + strIDN + ".xml",
//                   true);

//    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
//    {
//        pCfg->loadConfig();
//        pCfg->updateShow();
//    }

//    bool ok = true;
//    if( m_RobotList[mIndex].m_Visa == 0)
//    {
//        QMessageBox::warning(this,tr("warning"),tr("Current Device In Offline"));
//        return -2;//offline
//     }

//    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
//    {
//        int ret = pCfg->writeDeviceConfig();
//        if(ret != 0){
//            ok = false;
//            QMessageBox::critical(this,tr("error"), pCfg->focuHelpName() + "\t" + tr("Reset Failure"));
//        }
//    }
//    emit signalDataChanged();

//    if(ok){
//        QMessageBox::information(this,tr("tips"),tr("Reset Success!"));
//        return 0;
//    }else{
//        return -1;
//    }
    return 0;
}

bool RoboConfig::pluginsConnectState()
{
    bool bFullOpened;

    for( int i = 0; i < mPluginList.size(); i++ )
    {
        if ( mPluginList[i]->isOpened() )
        { bFullOpened = true; }
        else
        { bFullOpened = false; break; }
    }

    return bFullOpened;
}

#define foreach_plugin()    for( int i = 0; i < mPluginList.size(); i++ ){
#define end_foreach_plugin() }
void RoboConfig::pluginsOpen()
{
//    for( int i = 0; i < mPluginList.size(); i++ )
    foreach_plugin()
        if ( mPluginList[i]->isOpened() )
        {  }
        else if ( mPluginList[i]->open() == 0 )
        {}
        else
        { sysError( mPluginList[i]->addr() + " " + tr("connect fail") );}
    end_foreach_plugin()
}
void RoboConfig::plginsClose()
{
    foreach_plugin()
        mPluginList[i]->close();
    end_foreach_plugin()
}

void RoboConfig::pluginsStop()
{
    foreach_plugin()
        mPluginList[i]->stop();
    end_foreach_plugin()
}

void RoboConfig::slot_plugins_changed()
{
    Q_ASSERT( NULL != m_pPref );

    m_pPref->mPlugins.clear();
    foreach ( XPlugin *pPlugin, mPluginList )
    {
        Q_ASSERT( NULL != pPlugin );

        m_pPref->mPlugins.append( pPlugin->description() );
    }

    //! save pref
    emit signal_save_sysPref();
}

//! update the plugin open status
void RoboConfig::slot_plugin_setting_changed( XSetting setting )
{
    if ( setting.mSetting == XPage::e_setting_opened )
    {
        //! full opened
        Q_ASSERT( NULL != m_pConnAction );
        if ( pluginsConnectState() )
        {
            m_pConnAction->setIcon( QIcon(":/res/image/h2product/connect.png") );
            m_pConnAction->setToolTip( tr("Connect") );
        }
        else
        {
            m_pConnAction->setIcon( QIcon(":/res/image/h2product/disconnect.png") );
            m_pConnAction->setToolTip( tr("Disconnect") );
        }
    }
    else
    {}
}

void RoboConfig::on_stackedWidget_currentChanged(int arg1)
{
    //! xpage

    XPage *pPage = (XPage*)ui->stackedWidget->currentWidget();
    if ( pPage == NULL )
    { return; }

    pPage->showFocusHelp();
}
