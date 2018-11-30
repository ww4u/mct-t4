#include "roboconfig.h"
#include "ui_roboconfig.h"

#include "mystd.h"
#include "h2robo.h"

RoboConfig::RoboConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoboConfig)
{
    ui->setupUi(this);

    mIndex = -1;
    m_menu = NULL;
    m_megaSerachWidget = NULL;

    m_pRootNode = new QTreeWidgetItem();
    m_pRootNode->setText( 0, "Project");
    ui->treeWidget->addTopLevelItem( m_pRootNode );

    initRootNodeWidget();

    loadXmlConfig();

    connect( ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
             this, SLOT(slot_current_changed(QTreeWidgetItem*,QTreeWidgetItem*)));

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowContextmenu(const QPoint&)));
}

void RoboConfig::initRootNodeWidget()
{
    QWidget *pWidget = new QWidget;
    QVBoxLayout *t_layout = new QVBoxLayout(pWidget);
    QLabel *t_label = new QLabel;
    t_label->setPixmap(QPixmap(":/res/image/m.png"));
    t_label->setAlignment(Qt::AlignHCenter);
    QLabel *t_label2 = new QLabel("www.megarobo.tech");
    t_label2->setAlignment(Qt::AlignHCenter);

    t_layout->addWidget(t_label);
    t_layout->addWidget(t_label2);
    m_pRootNode->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(pWidget) ) );
    pWidget->setEnabled(false);
    ui->stackedWidget->addWidget( pWidget );
}

RoboConfig::~RoboConfig()
{
    delete ui;
}

void RoboConfig::loadXmlConfig()
{
    //! load xml
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath();
    QDir dir(fileName);
    if(!dir.exists()){dir.mkdir(fileName);}

    fileName += "/config.xml";
    mXML.xmlCreate(fileName);

    QMap<QString,QString> mapItems = mXML.xmlRead(fileName);
    QMap<QString,QString>::iterator itMap;
    for ( itMap=mapItems.begin(); itMap != mapItems.end(); ++itMap ) {
        if( "RobotDevice_" == itMap.key().left(QString("RobotDevice_").length()) )
            createRobot(itMap.value());
    }
    ui->treeWidget->setCurrentItem(m_pRootNode);
}

void RoboConfig::createRobot(QString strDevInfo)
{
    RobotInfo robotInfo;
    robotInfo.m_Robo = new H2Robo( ui->stackedWidget, strDevInfo );
    robotInfo.m_strDevInfo = strDevInfo;
    robotInfo.m_Visa = 0;
    robotInfo.m_DeviceName = 0;
    robotInfo.m_RoboName = 0;
    m_RobotList.insert(m_RobotList.count(), robotInfo);

    m_pRootNode->addChild( ((H2Robo *)(robotInfo.m_Robo))->roboNode() );
    ui->treeWidget->setCurrentItem(m_pRootNode->child(m_RobotList.count()-1) );

    mIndex = m_RobotList.count()-1;
    m_pRootNode->setExpanded(true);

    foreach (XConfig *pCfg, ((H2Robo *)(robotInfo.m_Robo))->subConfigs()){
        QString configFileName = robotInfo.m_strDevInfo.split(',').at(3);
        pCfg->setProjectName(configFileName);
        pCfg->loadConfig();
        pCfg->updateShow();
    }

    foreach (XConfig *pCfg, ((H2Robo *)(robotInfo.m_Robo))->subConfigs()){
        pCfg->saveConfig();

        connect( pCfg, SIGNAL(signal_focus_in( const QString &)),
                 this, SIGNAL(signal_focus_in( const QString &)) );

        connect( pCfg, SIGNAL(signalModelDataChanged(bool)),
                 this, SLOT(setApplyButtonEnabled(bool)) );
    }

    setApplyButtonEnabled(false);
    connect(robotInfo.m_Robo,SIGNAL(signal_online_request(QString)),
            this,SLOT(slot_open_close(QString)));
}

void RoboConfig::slotAddNewRobot(QString strDevInfo)
{
    for(int i=0; i< m_RobotList.count(); i++)
    {
        if( m_RobotList[i].m_strDevInfo == strDevInfo)
        {
            QMessageBox::information(this,tr("tips"),tr("The device already exists in the project."));
            return;
        }
    }
    qDebug() << "slotAddNewRobot" << strDevInfo;

    createRobot(strDevInfo);

    //添加到config.xml中
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/config.xml";

    QMap<QString,QString> mapRead = mXML.xmlRead(fileName);
    QMap<QString,QString> mapWrite;
    for (QMap<QString,QString>::iterator itMap=mapRead.begin(); itMap != mapRead.end(); ++itMap ) {
        if( "RobotDevice_" == itMap.key().left(QString("RobotDevice_").length()) )
        {   mapWrite.insert(itMap.key(),itMap.value()); }
    }
    QString proName = QString("RobotDevice_%1").arg(mapWrite.size());
    mapWrite.insert(proName ,strDevInfo );
    mXML.xmlNodeRemove(fileName, "RobotConfigs");
    mXML.xmlNodeAppend(fileName, "RobotConfigs", mapWrite);
}

void RoboConfig::slotDownload()
{

}

void RoboConfig::slotUpload()
{

}

void RoboConfig::slotStore()
{

}

void RoboConfig::slotSync()
{
    if(mIndex < 0) return;
    if( m_RobotList[mIndex].m_Visa != 0)
    {
        bool ok = true;
        foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs()){
            int ret = pCfg->readDeviceConfig();
            if(ret != 0)
            {
                ok = false;
                QMessageBox::information(this,tr("tips"), pCfg->focusName() + tr("\nSync Faiured"));
            }
            pCfg->updateShow();
            pCfg->saveConfig();
        }
        if(ok)
        {   QMessageBox::information(this,tr("tips"),tr("Sync Succeed!"));  }
    }else{
        QMessageBox::information(this,tr("tips"),tr("Current Device In Offline"));
        return;
    }
}

void RoboConfig::slotSearch()
{
    if(m_megaSerachWidget != NULL)
        delete m_megaSerachWidget;

    m_megaSerachWidget = new MegaInterface;
    m_megaSerachWidget->move( x()+100, y()+100);
    m_megaSerachWidget->show();
    connect(m_megaSerachWidget, SIGNAL(signal_selected_info(QString)), this, SLOT(slotAddNewRobot(QString)));
}

void RoboConfig::slotExit()
{
    foreach (RobotInfo robo, m_RobotList ){
        QString strIP = robo.m_strDevInfo.split(',').at(0);
        if(robo.m_Visa != 0){ //如果没有关闭就关闭设备
            slot_open_close(strIP);
        }
    }
}

void RoboConfig::setApplyButtonEnabled(bool bl)
{
    if(mIndex < 0) return;
    ((H2Robo *)(m_RobotList[mIndex].m_Robo))->setApplyEnabled(bl);
    ui->buttonBox->button((QDialogButtonBox::Apply))->setEnabled(bl);
}

void RoboConfig::slotShowContextmenu(const QPoint& pos)
{
    QTreeWidgetItem* curItem = ui->treeWidget->itemAt(pos);  //获取当前被点击的节点
    if(curItem == NULL) return; //即在空白位置右击

    QVariant var = curItem->data(0,Qt::UserRole);
    if( "H2Product*" == QString("%1").arg(var.typeName()) )
    {
        if(m_menu != NULL)
            delete m_menu;

        m_menu = new QMenu(ui->treeWidget);
        QAction *actionClose = m_menu->addAction(tr("close"));
        QAction *actionOpen = m_menu->addAction(tr("delete"));

        connect(actionClose, SIGNAL(triggered(bool)), this, SLOT(soltActionClose()));
        connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(soltActionDelete()));

        m_menu->exec(QCursor::pos());
        ui->treeWidget->selectionModel()->clear();
    }
}

void RoboConfig::soltActionClose()
{
    int index = mIndex;
    QString strIP = m_RobotList[index].m_strDevInfo.split(',').at(0);
    if(m_RobotList[index].m_Visa != 0)
    {   //如果没有关闭就关闭设备
        slot_open_close(strIP);
    }

    m_pRootNode->removeChild(((H2Robo *)m_RobotList[index].m_Robo)->roboNode());
    delete (H2Robo *)m_RobotList[index].m_Robo;
    m_RobotList.removeAt(index);

    ui->treeWidget->setCurrentItem(m_pRootNode);

//    qDebug() << "after close:" << m_RobotList.count() << mIndex;
}

void RoboConfig::soltActionDelete()
{
    //! delete from xml file
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/config.xml";
    QMap<QString,QString> mapRead = mXML.xmlRead(fileName);
    QMap<QString,QString> mapWrite;
    for (QMap<QString,QString>::iterator itMap=mapRead.begin(); itMap != mapRead.end(); ++itMap )
    {
        if( "RobotDevice_" == itMap.key().left(QString("RobotDevice_").length())
                && m_RobotList[mIndex].m_strDevInfo != itMap.value() )
        {
            mapWrite.insert(itMap.key(),itMap.value());
        }
    }
    mXML.xmlNodeRemove(fileName, "RobotConfigs");
    mXML.xmlNodeAppend(fileName, "RobotConfigs", mapWrite); //update config.xml

    QString strIDn = m_RobotList[mIndex].m_strDevInfo.split(',').at(3);

    //delete device.xml
    fileName = QApplication::applicationDirPath() + "/robots/" + strIDn + ".xml";
    {
        QFile file(fileName);
        if(file.exists())
        {   file.remove();  }
    }
    //!

    fileName = QApplication::applicationDirPath() + "/dataset/" + strIDn + ".mrp";
    {
        QFile file(fileName);
        if(file.exists())
        {   file.remove();  }
    }

    fileName = QApplication::applicationDirPath() + "/dataset/" + strIDn + ".xml";
    {
        QFile file(fileName);
        if(file.exists())
        {   file.remove();  }
    }

    soltActionClose();
}

int RoboConfig::setApply()
{
    if(mIndex < 0) return -100;
    bool ok = true;
    if( m_RobotList[mIndex].m_Visa != 0)
    {
        foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs()){
            int ret = pCfg->writeDeviceConfig();
            if(ret != 0)
            {
                ok = false;
                QMessageBox::information(this,tr("tips"), pCfg->focusName() + tr("\tApply Failure"));
            }
            pCfg->saveConfig();
        }
        emit signalApplyClicked();
    }else{
        QMessageBox::information(this,tr("tips"),tr("Current Device In Offline"));
        return -2;//offline
    }

    if(ok)
    {
        setApplyButtonEnabled(false);
        QMessageBox::information(this,tr("tips"),tr("Apply Success!"));
        return 0;
    }
    else{
        return -1;
    }
}

int RoboConfig::setReset()
{
    if(mIndex < 0) return -100;
    bool ok = true;
    if( m_RobotList[mIndex].m_Visa != 0)
    {
        //将默认的配置文件替换掉对应的配置文件，更新界面，写入设备
        QString strIDN = m_RobotList[mIndex].m_strDevInfo.split(',').at(3);
        copyFileToPath(QApplication::applicationDirPath() + "/robots/default.xml",
                       QApplication::applicationDirPath() + "/robots/" + strIDN + ".xml",
                       true);

        copyFileToPath(QApplication::applicationDirPath() + "/dataset/action_default.mrp",
                       QApplication::applicationDirPath() + "/dataset/" + strIDN + ".mrp",
                       true);

        copyFileToPath(QApplication::applicationDirPath() + "/dataset/errmgr_default.xml",
                       QApplication::applicationDirPath() + "/dataset/" + strIDN + ".xml",
                       true);

        foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
        {
            pCfg->loadConfig();
            pCfg->updateShow();
            int ret = pCfg->writeDeviceConfig();
            if(ret != 0)
            {
                ok = false;
                QMessageBox::information(this,tr("tips"), pCfg->focusName() + tr("\tReset Failure"));
            }
        }
        emit signalApplyClicked();
    }else{
        QMessageBox::information(this,tr("tips"),tr("Current Device In Offline"));
        return -2;//offline
    }
    if(ok)
    {
        QMessageBox::information(this,tr("tips"),tr("Reset Success!"));
        return 0;
    }else{
        return -1;
    }
}

void RoboConfig::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole( button );
    if ( QDialogButtonBox::ResetRole == role )
    {
        setReset();
    }
    else if (QDialogButtonBox::ApplyRole == role )
    {
        setApply();
    }
}

void RoboConfig::slot_current_changed( QTreeWidgetItem* cur,QTreeWidgetItem* prv )
{
    if ( cur == NULL )
    { return; }

    QVariant var = QVariant(cur->data( 0, Qt::UserRole) );
    if ( var.isValid() ){
        QObject *pObj = var.value<QObject*>();
        if ( NULL != pObj ){
            ui->stackedWidget->setCurrentWidget( (QWidget*)pObj );
        }
    }

    int index = -1, row = -1;
    if(NULL == cur->parent() ){// 根节点-1,0
        ui->buttonBox->button((QDialogButtonBox::Apply))->setEnabled(false);
        return;
    }
    else if( NULL == cur->parent()->parent() ) { //子节点 x,0
        index = cur->parent()->indexOfChild(cur);
        row = 0;
    } else { //孙节点 x,y
        index = cur->parent()->parent()->indexOfChild(cur->parent());
        row = cur->parent()->indexOfChild(cur) + 1;
    }

    if(mIndex != index){
        sysInfo("Current Robot Changed: ", mIndex);
    }

    mIndex = index;
    qDebug() << "slot_current_changed" << mIndex;

    emit signalCurrentRobotChanged(m_RobotList[mIndex].m_strDevInfo,
                                   m_RobotList[mIndex].m_Visa,
                                   m_RobotList[mIndex].m_DeviceName,
                                   m_RobotList[mIndex].m_RoboName);

    bool bl = ((H2Robo *)(m_RobotList[mIndex].m_Robo))->applyEnabled();
    setApplyButtonEnabled(bl);
}

void RoboConfig::slot_open_close(QString strIP)
{
    if(mIndex < 0) return;
    H2Robo *pRobo = (H2Robo *)(m_RobotList[mIndex].m_Robo);
    H2Product *pProduct = (H2Product *)(pRobo->subConfigs().at(0));

    if(m_RobotList[mIndex].m_Visa == 0)
    {
        int ret = deviceOpen(strIP);
        if(ret > 0){
            pProduct->change_online_status(true);
        }
        else{
            QMessageBox::information(this,tr("tips"),tr("Device Open Failure!!!"));
        }
    }
    else
    {
        deviceClose();
        pProduct->change_online_status(false);
    }

    //通知OPS
    emit signalCurrentRobotChanged(m_RobotList[mIndex].m_strDevInfo,
                                   m_RobotList[mIndex].m_Visa,
                                   m_RobotList[mIndex].m_DeviceName,
                                   m_RobotList[mIndex].m_RoboName);
}

int RoboConfig::deviceOpen(QString strIP)
{
    if(mIndex < 0) return -1;
    int ret = -1;
    QString strDesc = QString("TCPIP0::%1::inst0::INSTR").arg(strIP);
    int visa = mrgOpenGateWay(strDesc.toLatin1().data(), 2000);
    if(visa <= 0)
    {
        qDebug() << "mrgOpenGateWay error" << visa;
        sysError("mrgOpenGateWay error");
        return -1;
    }

    int deviceNames[32] = {0};
    int roboNames[32] = {0};
    int deviceName = -1;
    int roboName = -1;

    ret = mrgGetRobotName(visa, roboNames);
    if(ret <= 0)
    {
        qDebug() << "mrhtRobotName_Query error" << ret;
        sysError("mrhtRobotName_Query error");
        return -2;
    }
    roboName = roboNames[0];//默认选择第一个机器人

    ret = mrgGetRobotDevice(visa, roboName, deviceNames);
    if(ret <= 0)
    {
        qDebug() << "mrgGetRobotDevice error" << ret;
        sysError("mrgGetRobotDevice error");
        return -3;
    }
    deviceName = deviceNames[0];//默认选择第一个驱控器

    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
    {    pCfg->attachHandle( visa, deviceName, roboName);  }

    mrgIdentify(visa, 1);

    qDebug() << "device open" << strIP << visa;
    sysInfo("Device Open", visa);

    m_RobotList[mIndex].m_Visa = visa;
    m_RobotList[mIndex].m_DeviceName = deviceName;
    m_RobotList[mIndex].m_RoboName = roboName;
    return visa;
}

int RoboConfig::deviceClose()
{
    if(mIndex < 0) return -1;
    mrgIdentify(m_RobotList[mIndex].m_Visa, 0);
    int ret = mrgCloseGateWay(m_RobotList[mIndex].m_Visa);

    qDebug() << "device close" << m_RobotList[mIndex].m_Visa << ret;
    sysInfo("Device Close");

    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
    {    pCfg->detachHandle();  }

    m_RobotList[mIndex].m_Visa = 0;
    m_RobotList[mIndex].m_DeviceName = 0;
    m_RobotList[mIndex].m_RoboName = 0;
    return ret;
}

bool RoboConfig::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

void RoboConfig::changeLanguage(QString qmFile)
{
    for(int index=0; index<m_RobotList.size(); index++)
    {
        foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[index].m_Robo)->subConfigs()){
            pCfg->changeLanguage(qmFile);
        }
    }

    qApp->removeTranslator(&m_translator);
    m_translator.load(qmFile);
    qApp->installTranslator(&m_translator);
    ui->retranslateUi(this);
}
