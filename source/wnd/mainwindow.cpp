#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "login.h"
#include "syspref.h"

#define pref_file_path  QDir::homePath() + "/mct"
#define pref_file_name  pref_file_path + "/mct_pref.xml"

MainWindow *MainWindow::_pBackendProxy = NULL;

void MainWindow::requestLogout( const QString &str, LogStr::eLogLevel lev )
{
    if( NULL == MainWindow::_pBackendProxy )
    { return; }

    MainWindow::_pBackendProxy->emit_logout( str, lev );
}

void MainWindow::requestProgress( const QString &info, bool b, int now, int mi, int ma  )
{
    if( NULL == MainWindow::_pBackendProxy )
    { return; }

    MainWindow::_pBackendProxy->emit_progress( info, b, now, mi, ma );
}

void MainWindow::showStatus( const QString str)
{
    if( NULL == MainWindow::_pBackendProxy )
    { return; }

    MainWindow::_pBackendProxy->emit_status(str);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pLabStatus = NULL;
    m_pLabMctVer = NULL;
    m_pLabConVer = NULL;
    m_roboConfig = NULL;
    m_pDockOps   = NULL;

    m_pDockHelp  = NULL;
    m_pHelpPanel = NULL;
    m_pProgress  = NULL;

    //! default
    mPref.init();

    setupWorkArea();

    setupMenu();

    setupToolBar();

    setupStatusBar();

    buildConnection();

    loadConfig();

    //! register the proxy
    MainWindow::_pBackendProxy = this;
}

MainWindow::~MainWindow()
{
    delete ui;

    if ( NULL != m_pHelpPanel )
    { delete m_pHelpPanel; }

    if ( NULL != m_pProgress )
    { delete m_pProgress; }
}

void MainWindow::setupWorkArea()
{
    //! pref
    m_roboConfig = new RoboConfig(this);
    ui->centralWidget->insertTab( 0, m_roboConfig, tr("Pref") );

    //! connect
    connect( m_roboConfig, SIGNAL(signal_request_sysOpPanel()),
             this, SLOT(slot_request_sysOpPanel()) );
    connect( m_roboConfig, SIGNAL(signal_save_sysPref()),
             this, SLOT(slot_save_sysPref()) );

    //! dock
    m_pDockOps = new QDockWidget( tr("Ops"), this );
    m_pDockOps->setAllowedAreas(  Qt::BottomDockWidgetArea );
    m_pDockOps->setFeatures( QDockWidget::DockWidgetVerticalTitleBar | m_pDockOps->features() );
    addDockWidget( Qt::BottomDockWidgetArea, m_pDockOps );

    m_roboConfig->attachOpDock( m_pDockOps );
    m_roboConfig->attachLogModel( &mLogModel );
    m_roboConfig->attachSysPref( &mPref );
    m_roboConfig->attachConnectWidget( ui->actionConnect );

    m_pSysLogout = new SysLogout( this );
    m_pDockOps->setWidget( m_pSysLogout );

    m_pSysLogout->attachLogModel( &mLogModel );

    ui->menuView->addAction( m_pDockOps->toggleViewAction() );

    //! help
    m_pDockHelp = new QDockWidget( tr("Help"), this  );
    m_pDockHelp->setAllowedAreas(  Qt::RightDockWidgetArea );
    addDockWidget( Qt::RightDockWidgetArea, m_pDockHelp );

    m_pHelpPanel = new HelpPanel();
    m_pDockHelp->setWidget( m_pHelpPanel );    
    m_pDockHelp->toggleViewAction()->setText(tr("&ShowHelp"));
    ui->menuHelp->addAction( m_pDockHelp->toggleViewAction() );
    m_pDockHelp->hide();
}

void MainWindow::setupMenu()
{
    QActionGroup * langGroup = new QActionGroup( ui->menuView );
    m_pChAction = langGroup->addAction( tr("Chinese") );
    m_pChAction->setCheckable( true );
    m_pEnAction = langGroup->addAction( tr("English") );
    m_pEnAction->setCheckable( true );

    QActionGroup * styleGroup = new QActionGroup(ui->menuView);
    m_pMegaAction = styleGroup->addAction( tr("MEGAROBO") );
    m_pMegaAction->setCheckable( true );
    m_pClasAction = styleGroup->addAction( tr("Classic") );
    m_pClasAction->setCheckable( true );

    ui->menuView->addSection( tr("Language") );
    ui->menuView->addActions( langGroup->actions() );

    ui->menuView->addSection( tr("Style") );
    ui->menuView->addActions( styleGroup->actions() );
}

void MainWindow::setupToolBar()
{
    ui->mainToolBar->addAction( ui->actionDownload );
    ui->mainToolBar->addAction( ui->actionUpload );
//    ui->mainToolBar->addAction( ui->actionStore );
//    ui->mainToolBar->addAction( ui->actionSync );
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction( ui->actionSearch );
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction( ui->actionConnect );

//    QWidget *pWidget;
//    pWidget->setLayout();
//    ui->mainToolBar->addWidget( new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum)
//                                );

    ui->mainToolBar->addSeparator();
    m_pStopWidget = new StopWidget();
    ui->mainToolBar->addWidget( m_pStopWidget );


//    ui->mainToolBar->addAction( ui->actionStop );
//    ui->mainToolBar->addAction( ui->actionIP );

#ifdef _WIN32
    //! windows禁用这些功能
    ui->actionReboot->setVisible(false);
    ui->actionPoweroff->setVisible(false);
    ui->actionWifi->setVisible(false);
#endif

}

void MainWindow::setupStatusBar()
{
    m_pLabStatus = new QLabel("MegaRobo Configuration Tool");
    m_pLabMctVer = new QLabel( QString("Version: %1  ").arg( qApp->applicationVersion() ) );
    m_pLabConVer = new QLabel( "Build: " __DATE__ );

    ui->statusBar->insertWidget( 0, m_pLabStatus, 1 );
    ui->statusBar->insertWidget( 1, m_pLabMctVer, 0 );
    ui->statusBar->insertWidget( 2, m_pLabConVer, 0 );
}



void MainWindow::buildConnection()
{
    connect( this, SIGNAL(signal_pref_changed()),
             this, SLOT(slot_save_sysPref()) );

    connect( m_roboConfig, SIGNAL(signal_focus_in( const QString &)),
             this, SLOT(slot_focus_in(const QString &)) );

    //! direct connect
    connect(ui->actionDownload,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotDownload()));
    connect(ui->actionUpload,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotUpload()));
    connect(ui->actionStore,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotStore()));
    connect(ui->actionSync,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotSync()));
    connect(ui->actionSearch,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotSearch()));
    connect(ui->actionConnect,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotConnect()));

    connect( m_pStopWidget, SIGNAL(signal_stop_clicked(bool)),
             m_roboConfig, SLOT(slot_plugins_stop()));

    //! connect menu
    connect( m_pEnAction, SIGNAL(triggered(bool)), this, SLOT(slot_lang_changed()) );
    connect( m_pChAction, SIGNAL(triggered(bool)), this, SLOT(slot_lang_changed()) );

    connect( m_pMegaAction, SIGNAL(triggered(bool)), this, SLOT(slot_style_changed()) );
    connect( m_pClasAction, SIGNAL(triggered(bool)), this, SLOT(slot_style_changed()) );

    //! logout
    connect( this, SIGNAL(signal_logout(const QString &,int)),
             this, SLOT(slot_logout(const QString &, int)),
             Qt::QueuedConnection );

    //! status
    connect( this, SIGNAL(signal_status(const QString &)),
             this, SLOT(slot_status(const QString&)),
             Qt::QueuedConnection );

    //! progress
    connect( this, SIGNAL(signal_progress(const QString &,bool,int,int,int)),
             this, SLOT(slot_progress(const QString &,bool,int,int,int)),
             Qt::QueuedConnection );


}

void MainWindow::loadConfig()
{
    //! load pref
    loadPref();

    changeLanguage();

    changeStyle();

    do
    {
        //! skip, use the last mode
        if ( mPref.mbAutoLogin )
        { break; }

        //! log in
        LogIn logIn;
        if ( logIn.exec() == QDialog::Accepted )
        {
            if ( logIn.getUserRole() == 0 )
            { setSysMode( sysPara::e_sys_user ); }
            else
            { setSysMode( sysPara::e_sys_admin ); }

            //! save mode
            mPref.mSysMode = logIn.getUserRole();
            mPref.mbAutoLogin = logIn.getAutoLogin();

            QTimer::singleShot( 0, this, SLOT( slot_save_sysPref()) );
        }
        else
        {
            QTimer::singleShot( 0, qApp, SLOT(quit()) );
            return;
        }

    }while( 0 );

    //! post startup
    QTimer::singleShot( 0, this, SLOT(slot_post_startup()) );
}

void MainWindow::changeLanguage()
{
    //! set lang
    do
    {
        QLocale::Language lang;
        QLocale::Country area;
        if ( mPref.mLangIndex == LANG_EN )
        {
            lang = QLocale::English;
            area = QLocale::AnyCountry;
//            qmFile = ":/res/ts/qt_EN.qm";
        }
        else if ( mPref.mLangIndex == LANG_CN )
        {
            lang = QLocale::Chinese;
            area = QLocale::China;
//            qmFile = ":/res/ts/qt_CN.qm";
        }
        else
        {
            lang = QLocale::AnyLanguage;
            area = QLocale::AnyCountry;
            sysError( tr("Invalid language"));
            return;
        }

        if ( mTranslator.isEmpty() )
        {}
        else
        { qApp->removeTranslator( &mTranslator ); }

        //! local
        QLocale local( lang, area );
        local.setDefault( QLocale(QLocale::English) );

        logDbg()<<local.uiLanguages();

        if ( mTranslator.load( local,
                              QLatin1String("mct"),
                              QLatin1String("_"),
                              qApp->applicationDirPath() + "/translate",
                              ".qm")
             && qApp->installTranslator(&mTranslator) )
        {
        }
        else
        {
            QMessageBox::information( NULL,
                                    QObject::tr("Info"),
                                    QObject::tr("language loss"));
        }
    }while( 0 );
}

void MainWindow::changeStyle()
{
    if ( mPref.mStyleIndex == STYLE_MEGAROBO )
    {

//        setUiStyle(":/res/qss/mega.qss");
        setUiStyle( qApp->applicationDirPath() + "/style/mega.qss" );
    }
    else
    {
//        setUiStyle(":/res/qss/classic.qss");
        setUiStyle( qApp->applicationDirPath() + "/style/classic.qss" );
    }
}

void MainWindow::setUiStyle(const QString &styleFile)
{
    if( ! QFile::exists(styleFile) )
    {
        qDebug() << "setStyleSheet file not exists!";
        sysError("setStyleSheet file not exists!" + styleFile);
        return;
    }

    QFile qss(styleFile);
    if( qss.open(QFile::ReadOnly) )
    {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
    else
    { sysError( tr("Style apply fail") );}
}

void MainWindow::slot_request_sysOpPanel()
{
    Q_ASSERT( NULL != m_pDockOps );
    Q_ASSERT( NULL != m_pSysLogout );

    m_pDockOps->setWidget( m_pSysLogout );
}

void MainWindow::slot_save_sysPref()
{ savePref(); }

//! change the language
void MainWindow::slot_post_startup()
{
    //! change the language
    if ( mPref.mLangIndex == 0 )
    { m_pEnAction->setChecked( true ); }
    else
    { m_pChAction->setChecked( true ); }

//    changeLanguage();

    //! change the style
    if ( mPref.mStyleIndex == 0 )
    { m_pMegaAction->setChecked( true ); }
    else
    { m_pClasAction->setChecked( true ); }

//    changeStyle();

    Q_ASSERT( NULL != m_roboConfig );
    m_roboConfig->postStartup();

}

void MainWindow::on_actionAbout_triggered()
{
    aboutDlg dlg(this);
    dlg.exec();
}

void MainWindow::slot_lang_changed()
{
    if ( m_pEnAction->isChecked() )
    { mPref.mLangIndex = LANG_EN; }
    else
    { mPref.mLangIndex = LANG_CN; }

    changeLanguage();

    emit signal_pref_changed();
}
void MainWindow::slot_style_changed()
{
    if ( m_pMegaAction->isChecked() )
    {
        mPref.mStyleIndex = STYLE_MEGAROBO;
    }
    else
    {
        mPref.mStyleIndex = STYLE_CLASSIC;
    }

    changeStyle();

    emit signal_pref_changed();
}

void MainWindow::slot_logout( const QString &str, int lev )
{
    mLogModel.append( str, (LogStr::eLogLevel)lev );
}

void MainWindow::slot_status( const QString &str )
{
    if ( m_pLabStatus!=NULL )
    { m_pLabStatus->setText(str); }
}

void MainWindow::slot_progress( const QString &info, bool b, int now, int mi, int ma )
{
    if ( NULL == m_pProgress )
    {
        m_pProgress = new QProgressDialog();
        if ( NULL == m_pProgress )
        { return; }

        connect( m_pProgress, SIGNAL(canceled()),
                 this, SLOT(slot_progress_canceled()) );
    }
    else
    {}
    if ( b )
    {
        m_pProgress->setMinimum( mi );
        m_pProgress->setMaximum( ma );
        m_pProgress->setValue( now );
        m_pProgress->show();
    }
    else
    { m_pProgress->hide(); }
}

void MainWindow::slot_progress_canceled()
{
    m_roboConfig->cancelBgWorking();
}

void MainWindow::slot_focus_in( const QString &name )
{
    QString strName =  QApplication::applicationDirPath() + "/doc/" + name + ".html";
//    logDbg() << name;
    if ( name.length() <= 0 )
    { return; }

    if ( m_pHelpPanel == NULL )
    { return; }

    m_pHelpPanel->setFile( strName );
}

void MainWindow::changeEvent( QEvent * event )
{
    QMainWindow::changeEvent( event );

    Q_ASSERT( NULL != event && NULL != ui );

    //! language change
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi( this );

        m_pClasAction->setText( tr("Classic") );
        m_pMegaAction->setText( tr("MEGAROBO") );

        //! \todo for each plugin and widgets
//        for ( int i = 0; i < ui->widget->count(); i++ )
//        {
//            Q_ASSERT( NULL != ui->widget->widget(i) );

//            qApp->postEvent( (modelView*)ui->widget->widget( i ),
//                          new QEvent( QEvent::LanguageChange )
//                          );
//        }
    }
}

void MainWindow::emit_logout( const QString &info, int level )
{
    emit signal_logout( info, level );
}

void MainWindow::emit_status( const QString &str )
{ emit signal_status( str ); }

void MainWindow::emit_progress( const QString &info, bool b, int now, int mi, int ma )
{
    emit signal_progress( info, b, now, mi, ma );
}

void MainWindow::retranslateUi()
{}

void MainWindow::savePref()
{
    int ret;

    //! create path
    ret = assurePath( pref_file_path );
    if ( ret != 0 )
    { return; }

    //! save file
    ret = mPref.save( pref_file_name );
    if ( ret != 0 )
    {
        sysError( tr("Pref save fail") );

        logDbg()<<pref_file_name;
    }
}
void MainWindow::loadPref()
{
    int ret;
    ret = mPref.load( pref_file_name );
    if ( ret != 0 )
    {
        sysError( tr("Pref load fail") );
    }
}

void MainWindow::on_actionPoweroff_triggered()
{
//    m_roboConfig->slotExit();
    QThread::msleep(1000);
#ifndef _WIN32
    system("poweroff");
#else
    system("shutdown -s -t 0");
#endif
}

void MainWindow::on_actionReboot_triggered()
{
//    m_roboConfig->slotExit();
    QThread::msleep(1000);
#ifndef _WIN32
    system("reboot");
#else
    system("shutdown -s -r 0");
#endif
}

void MainWindow::on_actionWifi_triggered()
{
    m_roboConfig->slotWifi();
}

void MainWindow::on_actionPref_triggered()
{
    //! get from the pref
    SysPref pref( mPref );

    if ( pref.exec() == QDialog::Accepted )
    {
        mPref = pref;
        savePref();
    }
    else
    {}
}

//! test used
#include "../plugin/factory/pluginfactory.h"
void MainWindow::on_actiontest_triggered()
{
//    XPlugin *plugin = PluginFactory::createPlugin( "mrx-t4","" );
//    if ( NULL == plugin )
//    { return; }

//    //! ops panel
//    QWidget *pWig = plugin->createOpsPanel( nullptr );
//    if ( NULL != pWig )
//    {
//        pWig->show();
//        m_pDockOps->setWidget( pWig );
//    }

//    //! pref pages
//    QTreeWidgetItem *pRoboRoot = plugin->createPrefPages( m_roboConfig->stackWidget() );
//    m_roboConfig->rootItem()->addChild( pRoboRoot );
}


