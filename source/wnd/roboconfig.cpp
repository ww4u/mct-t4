#include "roboconfig.h"
#include "ui_roboconfig.h"

#include "mystd.h"
//#include "h2robo.h"
#include "xthread.h"
#include "welcomepage.h"

#define plugin_changed()    emit signal_plugins_changed();

//! tcpip::172.16.3.25::inst0::INSTR
QString RoboConfig::extractIp( const QString &ip )
{
    QStringList strList = ip.split("::",QString::SkipEmptyParts );
    logDbg()<<strList;
    if ( strList.size() >= 3 )
    { return strList.at(1); }
    else
    { return ip; }
}

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

    m_pActionHome = NULL;
    m_pActionFold = NULL;

    m_pActionReboot = NULL;
    m_pActionPowerOff = NULL;
    m_pActionExportLog = NULL;
    m_pActionUpdate = NULL;

    m_pProjectContextMenu = NULL;
    m_pActionDelAll = NULL;

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

    qRegisterMetaType<XSetting>( "XSetting" );
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
    ui->retranslateUi(this);
    ui->buttonBox->button( QDialogButtonBox::Reset )->setText(tr("Reset"));
    m_pRootNode->setText( 0, tr("Project"));
    foreach (XPlugin* xPlug, mPluginList){
        xPlug->retranslateUi();
    }
}

void RoboConfig::userRoleChanged()
{
    foreach (XPlugin* xPlug, mPluginList){
        xPlug->emit_setting_changed( XPage::e_setting_user_role, QVariant() );
    }
}

//! add each robo
//! "addr,model,sn,firmwareVer,mechanicalVer"
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
}

void RoboConfig::slotDownload()
{
    int ret;
    int failCnt = 0;
    //! for each plugin
    for ( int i = 0; i < mPluginList.size(); i++ )
    {
        if ( mPluginList.at(i)->isOpened() )
        {

        }
        else
        {
            sysInfo( mPluginList.at(i)->SN() + " " + tr("is not opened") );
            continue;
        }

        ret = mPluginList.at(i)->download();
        if ( ret != 0 )
        {
            sysPrompt( mPluginList.at(i)->SN() + " " + tr("download fail") );
            failCnt++;
        }
    }
    if ( failCnt == 0 )
    { sysPrompt( tr("Download success"), 0 ); }
}

void RoboConfig::slotUpload()
{
    int ret;
    int failCnt = 0;
    //! for each plugin
    for ( int i = 0; i < mPluginList.size(); i++ )
    {
        if ( mPluginList.at(i)->isOpened() )
        {
        }
        else
        {
            sysInfo( mPluginList.at(i)->SN() + " " + tr("is not opened") );
            continue;
        }

        ret = mPluginList.at(i)->upload();
        if ( ret != 0 )
        {
            sysPrompt( mPluginList.at(i)->SN() + " " + tr("upload fail") );
            failCnt++;
        }

    }

    if ( failCnt == 0 )
    { sysPrompt( tr("Upload success"), 0 ); }
}

void RoboConfig::slotStore()
{
    for ( int i = 0; i < mPluginList.size(); i++ )
    {
        mPluginList.at(i)->emit_save();
    }
}

void RoboConfig::slotSync()
{
    slotDownload();
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

void RoboConfig::slot_plugin_home()
{ pluginHome(); }

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

    //! prj node
    if ( curItem == m_pRootNode )
    {
        slotShowContextPrj( pos );
        return;
    }

    //! is root?
    QVariant vRoot = curItem->data( 0, Qt::UserRole+2 );
    if ( vRoot.isValid() )
    {}
    else
    { return; }

    slotShowContextPlugin( pos );
}

void RoboConfig::slotShowContextPrj( const QPoint &pos )
{
    //! project
    {
        if ( m_pProjectContextMenu != NULL )
        {}
        else
        {
            m_pProjectContextMenu = new QMenu( ui->treeWidget );
            if ( NULL == m_pProjectContextMenu )
            { return; }

            m_pActionDelAll = m_pProjectContextMenu->addAction( tr("Delete all") );
            if ( NULL == m_pActionDelAll )
            { return; }
            m_pActionDelAll->setIcon( QIcon(":/res/image/icon/trash.png") );

            //! connect
            connect(m_pActionDelAll, SIGNAL(triggered(bool)), this, SLOT(slotActionDelAll()));
        }

        //! plugins enabled
        m_pActionDelAll->setEnabled( mPluginList.size() > 0 );

        //! pop proc
        m_pProjectContextMenu->exec(QCursor::pos());
    }
}
void RoboConfig::slotShowContextPlugin( const QPoint &pos )
{
    //! current item
    QTreeWidgetItem* curItem = ui->treeWidget->itemAt(pos);
    if(curItem == NULL)
    { return; }

    //! is root?
    QVariant vRoot = curItem->data(0,Qt::UserRole+2);
    if ( vRoot.isValid() )
    {}
    else
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

            if ( NULL== m_pRoboContextMenu->addSeparator() )
            { gc_context_menu(); return; }

            m_pActionHome = m_pRoboContextMenu->addAction( tr("Home") );
            m_pActionHome->setIcon( QIcon(":/res/image/icon/address.png") );
            if ( NULL == m_pActionHome )
            { gc_context_menu(); return; }

            m_pActionFold = m_pRoboContextMenu->addAction( tr("Fold") );
            m_pActionFold->setIcon( QIcon(":/res/image/icon/stealth.png") );
            if ( NULL == m_pActionFold )
            { gc_context_menu(); return; }

            if ( NULL== m_pRoboContextMenu->addSeparator() )
            { gc_context_menu(); return; }

            QAction *actionDelete = m_pRoboContextMenu->addAction(tr("Delete"));
            actionDelete->setIcon( QIcon(":/res/image/icon/trash.png") );
            if ( NULL == actionDelete )
            { gc_context_menu(); return; }

            if ( NULL== m_pRoboContextMenu->addSeparator() )
            { gc_context_menu(); return; }

            m_pActionReboot = m_pRoboContextMenu->addAction( tr("Reboot") );
            m_pActionReboot->setIcon( QIcon(":/res/image/icon/332.png") );
            if ( NULL == m_pActionReboot )
            { gc_context_menu(); return; }

            m_pActionPowerOff = m_pRoboContextMenu->addAction( tr("Power Off") );
            m_pActionPowerOff->setIcon( QIcon(":/res/image/icon/246.png") );
            if ( NULL == m_pActionPowerOff )
            { gc_context_menu(); return; }

            if ( NULL== m_pRoboContextMenu->addSeparator() )
            { gc_context_menu(); return; }

            m_pActionExportLog = m_pRoboContextMenu->addAction( tr("Export log...") );
            if ( NULL == m_pActionExportLog )
            { gc_context_menu(); return; }
            m_pActionExportLog->setIcon( QIcon(":/res/image/icon/219.png") );

            m_pActionUpdate = m_pRoboContextMenu->addAction( tr("Update...") );
            if ( NULL == m_pActionUpdate )
            { gc_context_menu(); return; }
            m_pActionUpdate->setIcon( QIcon(":/res/image/icon/fuzhi.png") );

            QAction *actionExplorer = m_pRoboContextMenu->addAction( tr("Explorer") );
            if ( NULL == actionExplorer )
            { gc_context_menu(); return; }
            actionExplorer->setIcon( QIcon(":/res/image/icon/manage.png") );


            //! add action
            connect(m_pActionOpen, SIGNAL(triggered(bool)), this, SLOT(slotActionOpen()));
            connect(m_pActionClose, SIGNAL(triggered(bool)), this, SLOT(slotActionClose()));
            connect(m_pActionRst, SIGNAL(triggered(bool)), this, SLOT(slotActionRst()));

            connect(m_pActionHome, SIGNAL(triggered(bool)), this, SLOT(slotActionHome()));
            connect(m_pActionFold, SIGNAL(triggered(bool)), this, SLOT(slotActionFold()));

            connect(m_pActionReboot, SIGNAL(triggered(bool)), this, SLOT(slotActionReboot()));
            connect(m_pActionPowerOff, SIGNAL(triggered(bool)), this, SLOT(slotActionPoweroff()));

            connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(slotActionDelete()));
            connect(m_pActionExportLog, SIGNAL(triggered(bool)),this, SLOT(slotActionExportLog()) );
            connect(m_pActionUpdate, SIGNAL(triggered(bool)),this, SLOT(slotActionUpdate()) );
            connect(actionExplorer, SIGNAL(triggered(bool)), this, SLOT(slotActionExplorer()));
        }

        //! modify
        if ( m_pCurPlugin->isOpened() )
        {
            m_pActionOpen->setVisible(false);
            m_pActionClose->setVisible(true);
            m_pActionRst->setVisible( true );

            m_pActionHome->setVisible( true && m_pCurPlugin->isOnLine() );
            m_pActionFold->setVisible( m_pCurPlugin->isFoldable() && m_pCurPlugin->isOnLine() );

            m_pActionReboot->setVisible( m_pCurPlugin->isRebootable() );
            m_pActionPowerOff->setVisible( m_pCurPlugin->isPowerOffable() );

            m_pActionExportLog->setVisible( true );
            m_pActionUpdate->setVisible( true );
        }
        else
        {
            m_pActionOpen->setVisible(true);
            m_pActionClose->setVisible(false);
            m_pActionRst->setVisible( false );

            m_pActionHome->setVisible( false );
            m_pActionFold->setVisible( false );

            m_pActionReboot->setVisible( false );
            m_pActionPowerOff->setVisible( false );

            m_pActionExportLog->setVisible( false );
            m_pActionUpdate->setVisible( false );
        }

        //! pop proc
        m_pRoboContextMenu->exec(QCursor::pos());
    }
}

void RoboConfig::slotActionDelAll()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        delete_all( mPluginList )
        plugin_changed();

        QList<QTreeWidgetItem*> childs;
        for ( int i = 0; i < m_pRootNode->childCount(); i++ )
        {
            childs.append( m_pRootNode->child( i ) );
        }

        foreach( QTreeWidgetItem *pItem, childs )
        {
            m_pRootNode->removeChild( pItem );
            delete pItem;
        }

    QApplication::restoreOverrideCursor();
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

#include <qmessagebox.h>
#define msgBox_Warning_ok( title, content )     (QMessageBox::warning(this, title, content, QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok ? 1:0)
#define msgBox_Information_ok( title, content ) (QMessageBox::information(this, title, content, QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok ? 1:0)

void RoboConfig::slotActionRst()
{
    Q_ASSERT( NULL != m_pCurPlugin );
    if ( msgBox_Warning_ok( tr("Warning"), tr("Confirm Reset?") ))
        m_pCurPlugin->rst();
}

void RoboConfig::slotActionHome()
{
    Q_ASSERT( NULL != m_pCurPlugin );
    m_pCurPlugin->home();
}
void RoboConfig::slotActionFold()
{
    Q_ASSERT( NULL != m_pCurPlugin );
    m_pCurPlugin->fold();
}

void RoboConfig::slotActionReboot()
{
    Q_ASSERT( NULL != m_pCurPlugin );
    if( msgBox_Warning_ok( tr("Warning"), tr("Confirm Reboot?") ) )
        m_pCurPlugin->reboot();
}
void RoboConfig::slotActionPoweroff()
{
    Q_ASSERT( NULL != m_pCurPlugin );
    if(msgBox_Warning_ok( tr("Warning"), tr("Confirm PowerOff?") ))
        m_pCurPlugin->powerOff();
}
void RoboConfig::slotActionDelete()
{
    if(  msgBox_Warning_ok( tr("Warning"), tr("Confirm Delete?") ) ){
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

            //! delete + remove the root
            mPluginList.removeAll( m_pCurPlugin );
            plugin_changed();

            delete m_pCurPlugin;

            Q_ASSERT( NULL != m_pCurTreeItem );
            ui->treeWidget->removeItemWidget( m_pCurTreeItem, 0 );
            delete m_pCurTreeItem;

        QApplication::restoreOverrideCursor();
        msgBox_Information_ok( tr("Information"), tr("Delete Success!") );
    }
}

void RoboConfig::slotActionExportLog()
{
    //! \todo api for export
}
#include "classwizard.h"
void RoboConfig::slotActionUpdate()
{
    //! \todo update
    return;
    ClassWizard *wizard = new ClassWizard(this);
    wizard->show();
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
            if ( msgBox_Warning_ok( tr("Reset"), tr("Sure to reset all?") ) )
            { }
            else
            { break; }

            setReset();
        }while( 0 );
    }
    else
    {    }
}

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

    //! hide the reset and download
//    ui->buttonBox->button( QDialogButtonBox::Reset )->setVisible( false );

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

bool RoboConfig::downloadVisible()
{
    return true;
}
bool RoboConfig::resetVisible()
{
    return true;
}

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

        //! modify the reset attribute
        ui->buttonBox->button( QDialogButtonBox::Reset )->setVisible( bV && resetVisible() );
        ui->buttonBox->button( QDialogButtonBox::Reset )->setEnabled( pPage->isEnabled() );
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
    //! extract the ip
    plugin->setViewAddr( extractIp( strInfos.at(0) ) );
    plugin->setModel( strInfos.at(1) );

    plugin->setSN( strInfos.at(2) );
    plugin->setFirmwareVer( strInfos.at(3) );
    plugin->setMechanicalVer( strInfos.at(4) );

    //! pref
    plugin->attachPref( m_pPref );

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

    //! pref pages
    //! \note pRoboRoot is managed by the tree
    QTreeWidgetItem *pRoboRoot = plugin->createPrefPages( stackWidget() );logDbg()<<pRoboRoot;
    pRoboRoot->setToolTip( 0, plugin->viewAddr() );
    plugin->setViewObj( pRoboRoot );
    rootItem()->addChild( pRoboRoot );

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

    //! adapt the role
    plugin->emit_setting_changed( XPage::e_setting_user_role, QVariant() );

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

//! reset all
int RoboConfig::setReset()
{
    XPage *pPage;

    pPage = (XPage*)ui->stackedWidget->currentWidget();
    if ( NULL == pPage )
    { return -1; }

    pPage->pulgin()->rst();

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
        mPluginList[i]->fStop();
    end_foreach_plugin()
}

void RoboConfig::pluginHome()
{
    //! home the active plugin
    if ( mPluginList.size() > 1 )
    {
        QMessageBox::information( this, tr("Too many device"), tr("Operate the device from the node") );
    }
    else
    {
        mPluginList[0]->home();
    }
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

            emit signal_plugins_operable( true );
        }
        else
        {
            m_pConnAction->setIcon( QIcon(":/res/image/h2product/disconnect.png") );
            m_pConnAction->setToolTip( tr("Disconnect") );

            emit signal_plugins_operable( false );
        }
    }
    //! op able
    else if ( setting.mSetting == XPage::e_setting_op_able )
    {
        emit signal_plugins_operable( setting.mPara1.toBool() );
    }
    //! on line
    else if ( setting.mSetting == XPage::e_setting_online )
    {
        emit signal_plugins_online( setting.mPara1.toBool() );
    }
    else if ( setting.mSetting == XPage::e_setting_mission_working )
    {
        bool bOperable = setting.mPara1.toBool();
        emit signal_plugins_operable( !bOperable );
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
