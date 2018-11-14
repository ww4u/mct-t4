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

    m_pRootNode = new QTreeWidgetItem();
    m_pRootNode->setText( 0, tr("Project") );
    ui->treeWidget->addTopLevelItem( m_pRootNode );

    loadXmlConfig();

    connect( ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
             this, SLOT(slot_current_changed(QTreeWidgetItem*,QTreeWidgetItem*)));
}

RoboConfig::~RoboConfig()
{
    delete ui;
}

void RoboConfig::loadXmlConfig()
{
    //! load xml
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + m_pRootNode->text(0) + ".xml";
    mXML.xmlCreate(fileName);

    QMap<QString,QString> mapItems = mXML.xmlRead(fileName);
//    qDebug() << fileName << mapItems;
    QMap<QString,QString>::iterator itMap; //遍历map
    for ( itMap=mapItems.begin(); itMap != mapItems.end(); ++itMap ) {
        if( "RobotDevice_" == itMap.key().left(QString("RobotDevice_").length()) )
            createNewRobot(itMap.value());
    }
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
    ui->treeWidget->setCurrentItem(m_pRootNode->child(m_RobotList.count()-1));
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
    QMap<QString,QString> map;
    QString proName = QString("RobotDevice_%1").arg(mXML.xmlRead(fileName).size());
    map.insert(proName ,strDevInfo );
    mXML.xmlNodeAppend(fileName, "Config", map);
    createNewRobot(strDevInfo);
}

int RoboConfig::setApply()
{
    if(mIndex < 0) return -1;
    if( m_RobotList[mIndex].m_Visa != 0)
    {
        foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs()){
            pCfg->setApply();
        }
    }else{
        QMessageBox::information(this,tr("tips"),"Current Device In Offline");
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
    else if ( QDialogButtonBox::AcceptRole == role )
    {
        setOK();
    }
    else if ( QDialogButtonBox::ApplyRole == role )
    {
        setApply();
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
        if(0 != m_RobotList[mIndex].m_Visa)
        {
            emit signalCurrentRobotChanged(m_RobotList[mIndex].m_strDevInfo,
                                           m_RobotList[mIndex].m_Visa,
                                           m_RobotList[mIndex].m_RoboName);
        }
    }

//    qDebug() << "slot_current_changed" << cur->text(0) << index;

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
}

int RoboConfig::deviceOpen(QString strIP)
{
    if(mIndex < 0) return -1;
    int visa = mrhtOpenDevice(strIP.toLatin1().data(), 2000);
    if(visa <= 0)
    {    return -1; }

    char sName[8] = "";
    bool bl = false;
    int ret = mrhtRobotName_Query(visa, sName, sizeof(sName));
    int iName = QString("%1").arg(sName).toInt(&bl);
    if((ret < 0) || (bl == false))
    {   return -1;  }

    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
    {    pCfg->attachHandle( visa, iName);  }

    mrhtSystemIdentify(visa, 1);

//    qDebug() << "device open" << strIP << visa;
    m_RobotList[mIndex].m_Visa = visa;
    m_RobotList[mIndex].m_RoboName = iName;
    return visa;
}

int RoboConfig::deviceClose()
{
    if(mIndex < 0) return -1;
    mrhtSystemIdentify(m_RobotList[mIndex].m_Visa, 0);
    int ret = mrhtCloseDevice(m_RobotList[mIndex].m_Visa);

//    qDebug() << "device close" << m_RobotList[mIndex].m_Visa << ret;

    foreach (XConfig *pCfg, ((H2Robo *)m_RobotList[mIndex].m_Robo)->subConfigs())
    {    pCfg->detachHandle();  }

    m_RobotList[mIndex].m_Visa = 0;
    m_RobotList[mIndex].m_RoboName = 0;
    return ret;
}
