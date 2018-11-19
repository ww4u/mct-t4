#include "roboconfig.h"
#include "ui_roboconfig.h"

#include "../include/mystd.h"

#include "h2robo.h"

RoboConfig::RoboConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoboConfig)
{
    ui->setupUi(this);

    mIndex = -1;
    m_menu = NULL;

    m_pRootNode = new QTreeWidgetItem();
    m_pRootNode->setText( 0, tr("Project") );
    ui->treeWidget->addTopLevelItem( m_pRootNode );

    QWidget *pWidget = new QWidget;
    m_pRootNode->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(pWidget) ) );
    ui->stackedWidget->addWidget( pWidget );

    loadXmlConfig();

    connect( ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
             this, SLOT(slot_current_changed(QTreeWidgetItem*,QTreeWidgetItem*)));

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowContextmenu(const QPoint&)));
}

RoboConfig::~RoboConfig()
{
    delete ui;
}

void RoboConfig::loadXmlConfig()
{
    //! load xml
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/";
    QDir dir(fileName);
    if(!dir.exists()){dir.mkdir(fileName);}

    fileName += m_pRootNode->text(0) + ".xml";
    mXML.xmlCreate(fileName);

    QMap<QString,QString> mapItems = mXML.xmlRead(fileName);
    QMap<QString,QString>::iterator itMap;
    for ( itMap=mapItems.begin(); itMap != mapItems.end(); ++itMap ) {
        if( "RobotDevice_" == itMap.key().left(QString("RobotDevice_").length()) )
            createNewRobot(itMap.value());
    }
    ui->treeWidget->setCurrentItem(m_pRootNode);
}

void RoboConfig::createNewRobot(QString strDevInfo)
{
    RobotInfo robotInfo;
    robotInfo.m_Robo = new H2Robo( ui->stackedWidget, strDevInfo );
    robotInfo.m_strDevInfo = strDevInfo;
    robotInfo.m_Visa = 0;
    robotInfo.m_RoboName = 0;
    m_RobotList.insert(m_RobotList.count(), robotInfo);

    m_pRootNode->addChild( ((H2Robo *)(robotInfo.m_Robo))->roboNode() );
    ui->treeWidget->setCurrentItem(m_pRootNode->child(m_RobotList.count()-1) );

    mIndex = m_RobotList.count()-1;
    m_pRootNode->setExpanded(true);

    foreach (XConfig *pCfg, ((H2Robo *)(robotInfo.m_Robo))->subConfigs()){
        pCfg->setProjectName(robotInfo.m_strDevInfo.split(',').at(3));
        pCfg->loadXmlConfig();
        pCfg->slotOnModelChanged();
    }

    connect( robotInfo.m_Robo, SIGNAL(signal_focus_in( const QString &)),
             this, SIGNAL(signal_focus_in( const QString &)) );
    connect(robotInfo.m_Robo,SIGNAL(signal_online_request(QString)),
            this,SLOT(slot_open_close(QString)));
}

void RoboConfig::slotAddNewRobot(QString strDevInfo)
{
    for(int i=0; i< m_RobotList.count(); i++)
    {
        if( m_RobotList[i].m_strDevInfo == strDevInfo)
        {   return;    }
    }
    qDebug() << "slotAddNewRobot" << strDevInfo;

    //添加到project.xml中
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + m_pRootNode->text(0) + ".xml";

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
    createNewRobot(strDevInfo);

    QString strIP = strDevInfo.split(',').at(0);
    slot_open_close(strIP); //default open device
    setApply(); //create xml file
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
    QString strIP = m_RobotList[mIndex].m_strDevInfo.split(',').at(0);
    if(m_RobotList[mIndex].m_Visa != 0)
    {   //如果没有关闭就关闭设备
        slot_open_close(strIP);
    }

    m_pRootNode->removeChild(((H2Robo *)m_RobotList[mIndex].m_Robo)->roboNode());
    delete (H2Robo *)m_RobotList[mIndex].m_Robo;
    m_RobotList.removeAt(mIndex);

    ui->treeWidget->setCurrentItem(m_pRootNode);

    qDebug() << "after close:" << m_RobotList.count() << mIndex;
}

void RoboConfig::soltActionDelete()
{
    //! delete from xml file
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + m_pRootNode->text(0) + ".xml";
    QMap<QString,QString> mapRead = mXML.xmlRead(fileName);
    QMap<QString,QString> mapWrite;
    for (QMap<QString,QString>::iterator itMap=mapRead.begin(); itMap != mapRead.end(); ++itMap ) {
        if( "RobotDevice_" == itMap.key().left(QString("RobotDevice_").length())
                && m_RobotList[mIndex].m_strDevInfo != itMap.value() )
        {
            mapWrite.insert(itMap.key(),itMap.value());
        }
    }
    mXML.xmlNodeRemove(fileName, "RobotConfigs");
    mXML.xmlNodeAppend(fileName, "RobotConfigs", mapWrite); //update project.xml

    //delete device.xml
    fileName = QApplication::applicationDirPath() + "/robots/" + m_RobotList[mIndex].m_strDevInfo.split(',').at(3) + ".xml";
    QFile file(fileName);
    if(file.exists())
    {   file.remove();  }
    //!

    soltActionClose();
}

int RoboConfig::setApply()
{
    if(mIndex < 0) return -100;
    if( m_RobotList[mIndex].m_Visa != 0)
    {
        foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs()){
            int ret = pCfg->setApply();
            if(ret != 0)  return -1;
        }
        emit signalApplyClicked();
    }else{
        return -2;//offline
    }
    return 0;
}

int RoboConfig::setReset()
{
    //! \todo for each prop

    return 0;
}

int RoboConfig::setOK()
{
    //! setApply
    setApply();

    //! close

    return 0;
}

void RoboConfig::on_buttonBox_clicked(QAbstractButton *button)
{
    Q_ASSERT( NULL != button );

    QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole( button );
    if ( QDialogButtonBox::ResetRole == role )
    {
        setReset();
    }
    else if ( QDialogButtonBox::AcceptRole == role ||
              QDialogButtonBox::ApplyRole == role )
    {
        int ret = setApply();
        if(ret == 0)
        {
            QMessageBox::information(this,tr("tips"),tr("Apply Success!"));
        }
        else if(ret == -1){
            QMessageBox::information(this,tr("tips"),tr("Apply Failure"));
        }
        else if(ret == -2){
            QMessageBox::information(this,tr("tips"),tr("Current Device In Offline"));
        }
    }
    else
    {}
}

void RoboConfig::slot_current_changed( QTreeWidgetItem* cur,QTreeWidgetItem* prv )
{
    if ( cur == NULL )
    { return; }

    int index = m_pRootNode->indexOfChild(cur);
    if(-1 == index)
    {   index = m_pRootNode->indexOfChild(cur->parent()); }

    if(-1 != index)
    {
        mIndex = index;
        qDebug() << "slot_current_changed" << cur->text(0) << index;
        emit signalCurrentRobotChanged(m_RobotList[mIndex].m_strDevInfo,
                                       m_RobotList[mIndex].m_Visa,
                                       m_RobotList[mIndex].m_RoboName);
    }

    QVariant var;
    QObject *pObj;
    var = cur->data( 0, Qt::UserRole );
    if ( var.isValid() )
    {
        pObj = var.value<QObject*>();
        if ( NULL != pObj )
        {
            ui->stackedWidget->setCurrentWidget( (QWidget*)pObj );
        }
    }
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
                                   m_RobotList[mIndex].m_RoboName);
}

int RoboConfig::deviceOpen(QString strIP)
{
    if(mIndex < 0) return -1;
    QString strDesc = QString("TCPIP0::%1::inst0::INSTR").arg(strIP);
    int visa = mrgOpenGateWay(strDesc.toLatin1().data(), 2000);
    if(visa <= 0)
    {
        qDebug() << "mrgOpenGateWay error" << visa;
        return -1;
    }

    int sName[32] = {0};
    int ret = mrgGetRobotName(visa, sName);
    if(ret <= 0)
    {
        qDebug() << "mrhtRobotName_Query error" << ret;
        return -1;
    }
    int iName = sName[0];//默认选择第一个

    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
    {    pCfg->attachHandle( visa, iName);  }

    mrgIdentify(visa, 1);

//    qDebug() << "device open" << strIP << visa;
    m_RobotList[mIndex].m_Visa = visa;
    m_RobotList[mIndex].m_RoboName = iName;
    return visa;
}

int RoboConfig::deviceClose()
{
    if(mIndex < 0) return -1;
    mrgIdentify(m_RobotList[mIndex].m_Visa, 0);
    int ret = mrgCloseGateWay(m_RobotList[mIndex].m_Visa);

//    qDebug() << "device close" << m_RobotList[mIndex].m_Visa << ret;

    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
    {    pCfg->detachHandle();  }

    m_RobotList[mIndex].m_Visa = 0;
    m_RobotList[mIndex].m_RoboName = 0;
    return ret;
}
