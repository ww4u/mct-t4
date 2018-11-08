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
//    qDebug() << "slotAddNewRobot" << strDevInfo;

    H2Robo *pRobo = new H2Robo( ui->stackedWidget, strDevInfo );
    mRobos.insert(mRobos.count(), pRobo);
    mVisas.insert(mVisas.count(), 0);

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
    if(mVisas[mIndex] != 0)
    {
#if 0 //for all robot
        XConfig *pCfg;
        for ( int i = 0; i < ui->stackedWidget->count(); i++ )
        {
            pCfg = (XConfig*)ui->stackedWidget->widget( i );
            pCfg->setApply();
        }
#else //for current robot
        foreach (XConfig *pCfg, ((H2Robo *)mRobos[mIndex])->subConfigs()){
            pCfg->setApply();
        }
#endif
    }else
    {
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

//    ui->treeWidget->topLevelItem(1)->child(0)->text(0);

    if ( cur == NULL )
    { return; }

    int index = m_pRootNode->indexOfChild(cur);
    if(-1 == index)
    {   index = m_pRootNode->indexOfChild(cur->parent()); }

    if(-1 != index)
    {   mIndex = index; }

    qDebug() << "slot_current_changed"
             << cur->text(0) << index;

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
    if(mVisas[mIndex] == 0)
    {
        int ret = deviceOpen(strIP);
        if(ret > 0)
        {
            mVisas[mIndex] = ret;
            ((H2Robo *)(mRobos.at(mIndex)))->pProduct()->change_online_status(true);
        }
        qDebug() << "device open" << strIP << mVisas[mIndex] << ret;
    }
    else
    {
        int ret = deviceClose();
        mVisas[mIndex] = 0;
        ((H2Robo *)(mRobos.at(mIndex)))->pProduct()->change_online_status(false);
        qDebug() << "device close" << strIP << mVisas[mIndex] << ret;
    }
}

int RoboConfig::deviceOpen(QString strIP)
{
    int visa = mrhtOpenDevice(strIP.toLatin1().data(), 2000);
    if(visa <= 0)
    {    return -1; }

    mrhtSystemIdentify(mVisas[mIndex], 1);

    foreach (XConfig *pCfg, ((H2Robo *)mRobos[mIndex])->subConfigs()){
        qDebug() << pCfg << visa;
        pCfg->attachHandle( visa );
    }
    return visa;
}

int RoboConfig::deviceClose()
{
    mrhtSystemIdentify(mVisas[mIndex], 0);
    int ret = mrhtCloseDevice(mVisas[mIndex]);

    foreach (XConfig *pCfg, ((H2Robo *)mRobos[mIndex])->subConfigs()){
        pCfg->detachHandle();
    }

    return ret;
}
