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

    connect( ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
             this, SLOT(slot_current_changed(QTreeWidgetItem*,QTreeWidgetItem*)));
}

RoboConfig::~RoboConfig()
{
    delete ui;
    delete_all( mRobos );
}

void RoboConfig::slotAddNewRobot(QString strDevInfo)
{
    if(m_strListDevInfo.contains(strDevInfo))
    {
        QMessageBox::information(this,tr("tips"),tr("The Device Added Already"));
        return;
    }

    qDebug() << "slotAddNewRobot" << strDevInfo;
    H2Robo *pRobo = new H2Robo( ui->stackedWidget, strDevInfo );
    mRobos.insert(mRobos.count(), pRobo);
    mVisas.insert(mVisas.count(), 0);
    mRoboNames.insert(mRoboNames.count(), 0);
    m_strListDevInfo.insert(m_strListDevInfo.count(), strDevInfo);

    m_pRootNode->addChild( pRobo->roboNode() );
    ui->treeWidget->setCurrentItem(m_pRootNode->child(mRobos.count()-1));
    m_pRootNode->setExpanded(true);
    pRobo->roboNode()->setExpanded(true);

    connect( mRobos.last(), SIGNAL(signal_focus_in( const QString &)),
             this, SIGNAL(signal_focus_in( const QString &)) );
    connect(mRobos.last(),SIGNAL(signal_online_request(QString)),
            this,SLOT(slot_open_close(QString)));
}

int RoboConfig::setApply()
{
    if(mIndex < 0) return -1;
    if(mVisas[mIndex] != 0)
    {
        foreach (XConfig *pCfg, ((H2Robo *)mRobos[mIndex])->subConfigs()){
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
        if(0 != mVisas[mIndex])
        {   emit signalCurrentRobotChanged(mVisas[mIndex], mRoboNames[mIndex]); }
    }

    qDebug() << "slot_current_changed" << cur->text(0) << index;

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
    H2Robo *pRobo = (H2Robo *)(mRobos.at(mIndex));
    H2Product *pProduct = (H2Product *)(pRobo->subConfigs().at(0));

    if(mVisas[mIndex] == 0)
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
    int visa = mrhtOpenDevice(strIP.toLatin1().data(), 2000);
    if(visa <= 0)
    {    return -1; }

    char sName[8] = "";
    bool bl = false;
    int ret = mrhtRobotName_Query(visa, sName, sizeof(sName));
    int iName = QString("%1").arg(sName).toInt(&bl);
    if((ret < 0) || (bl == false))
    {   return -1;  }

    foreach (XConfig *pCfg, ((H2Robo *)mRobos[mIndex])->subConfigs())
    {    pCfg->attachHandle( visa, iName);  }

    mrhtSystemIdentify(visa, 1);

    qDebug() << "device open" << strIP << visa;
    mVisas[mIndex] = visa;
    mRoboNames[mIndex] = iName;
    return visa;
}

int RoboConfig::deviceClose()
{
    mrhtSystemIdentify(mVisas[mIndex], 0);
    int ret = mrhtCloseDevice(mVisas[mIndex]);

    qDebug() << "device close" << mVisas[mIndex] << ret;

    foreach (XConfig *pCfg, ((H2Robo *)mRobos[mIndex])->subConfigs())
    {    pCfg->detachHandle();  }

    mVisas[mIndex] = 0;
    mRoboNames[mIndex] = 0;
    return ret;
}
