#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../include/mystd.h"

MainWindow *MainWindow::_pBackendProxy = NULL;

void MainWindow::requestLogout( const QString &str, log_level lev )
{
    if( NULL != MainWindow::_pBackendProxy )
    {}
    else
    { return; }

    MainWindow::_pBackendProxy->slot_logout( str, lev );
}

void MainWindow::loadConfig()
{
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/config.xml";
    QMap<QString,QString> map = mXML.xmlRead(fileName);
    if(map["Style"] == "")
    {
        map.clear();
        map.insert("Style", "MegaRobo");
        m_style = STYLE_MEGAROBO;
        mXML.xmlNodeRemove(fileName, "WindowStyle");
        mXML.xmlNodeAppend(fileName, "WindowStyle", map);
    }

    if(map["Language"] == "")
    {
        map.clear();
        map.insert("Language", "English");
        m_language = LANG_EN;
        mXML.xmlNodeRemove(fileName, "WindowLanguage");
        mXML.xmlNodeAppend(fileName, "WindowLanguage", map);
    }

    map = mXML.xmlRead(fileName);
    if(map["Language"] == "English"){
        //默认缺省
        on_actionEnglish_triggered();
        on_actionEnglish_triggered();
    }else{
        on_actionChinese_triggered();
        on_actionChinese_triggered();
    }

    if(map["Style"] == "MegaRobo"){
        on_actionMega_triggered();
        on_actionMega_triggered();
    }else{
        on_actionClassic_triggered();
        on_actionClassic_triggered();
    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pHelpPanel = NULL;

    setupWorkArea();

    setupToolBar();

    setupStatusBar();

    buildConnection();

    //! register the proxy
    MainWindow::_pBackendProxy = this;

    loadConfig();
}

MainWindow::~MainWindow()
{
    delete ui;

    if ( NULL != m_pHelpPanel )
    { delete m_pHelpPanel; }
}

void MainWindow::setupWorkArea()
{
    //! pref
    m_roboConfig = new RoboConfig(this);
    connect( m_roboConfig, SIGNAL(signal_focus_in( const QString &)),
             this, SLOT(slot_focus_in(const QString &)) );

    //! docks
    ui->centralWidget->insertTab( 0, m_roboConfig, tr("Pref") );

    //! dock
    m_pDockOps = new QDockWidget( tr("Ops"), this );
    m_pDockOps->setAllowedAreas(  Qt::BottomDockWidgetArea );
    m_pDockOps->setFeatures( QDockWidget::DockWidgetVerticalTitleBar
                           | m_pDockOps->features() );
    addDockWidget( Qt::BottomDockWidgetArea, m_pDockOps );

    m_pOps = new H2Ops();
    m_pDockOps->setWidget( m_pOps );
    connect( m_pOps, SIGNAL(signal_focus_in( const QString &)),
             this, SLOT(slot_focus_in(const QString &)) );

    connect(m_roboConfig,SIGNAL(signalCurrentRobotChanged(QString,int,int,int)),m_pOps,SLOT(slotSetCurrentRobot(QString,int,int,int)));
    connect(m_roboConfig,SIGNAL(signalApplyClicked()),m_pOps,SLOT(slotLoadConfigAgain()));

    connect(m_roboConfig,SIGNAL(signalCurrentRobotChanged(QString,int,int,int)),this,SLOT(slotSetDockOpsName(QString,int,int,int)));

    ui->menuView->addAction( m_pDockOps->toggleViewAction() );

    //! help
    m_pDockHelp = new QDockWidget( tr("Help"), this  );
    m_pDockHelp->setAllowedAreas(  Qt::RightDockWidgetArea );
    addDockWidget( Qt::RightDockWidgetArea, m_pDockHelp );

    m_pHelpPanel = new HelpPanel();
    m_pDockHelp->setWidget( m_pHelpPanel );
    ui->menuHelp->addAction( m_pDockHelp->toggleViewAction() );
}

void MainWindow::setupToolBar()
{
    ui->mainToolBar->addAction( ui->actionStop );
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction( ui->actionDownload );
    ui->mainToolBar->addAction( ui->actionUpload );
    ui->mainToolBar->addAction( ui->actionStore );
    ui->mainToolBar->addAction( ui->actionSync );
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction( ui->actionSearch );

    connect(ui->actionStop,SIGNAL(triggered(bool)), m_pOps, SLOT(on_pushButton_stop_clicked()));
    connect(ui->actionDownload,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotDownload()));
    connect(ui->actionUpload,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotUpload()));
    connect(ui->actionStore,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotStore()));
    connect(ui->actionSync,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotSync()));
    connect(ui->actionSearch,SIGNAL(triggered(bool)), m_roboConfig, SLOT(slotSearch()));
}

void MainWindow::setupStatusBar()
{
    m_pLabStatus = new QLabel();
    m_pLabMctVer = new QLabel( QString("%1:%2").arg( ( qApp->applicationName() ) ).arg( qApp->applicationVersion() ) );
    m_pLabConVer = new QLabel();

    ui->statusBar->insertWidget( 0, m_pLabStatus, 1 );
    ui->statusBar->insertWidget( 1, m_pLabMctVer, 0 );
    ui->statusBar->insertWidget( 2, m_pLabConVer, 0 );
}

void MainWindow::buildConnection()
{
    QTimer::singleShot( 0, this, SLOT(slot_post_startup()));
}

void MainWindow::slot_post_startup()
{
    slot_logout( "start completed" );
    slot_logout( "start warning", e_log_warning );
    slot_logout( "start error", e_log_error );
}

void MainWindow::slot_logout( const QString &str, log_level lev )
{
    Q_ASSERT( NULL != m_pOps );

    m_pOps->outConsole( str, lev );
}

void MainWindow::slot_focus_in( const QString &name )
{
//    logDbg() << name;

    if ( name.length() <= 0 )
    { return; }

    if ( m_pHelpPanel == NULL )
    { return; }

    m_pHelpPanel->setFile( "./" + name + ".html" );
}

void MainWindow::on_actionAbout_triggered()
{
    aboutDlg dlg(this);
    dlg.exec();
}

void MainWindow::slotSetDockOpsName(QString strDevInfo, int visa, int deviceName,int roboName)
{
    QStringList strListDev = strDevInfo.split(',', QString::SkipEmptyParts);
    QString strDeviceName = strListDev.at(2) + "[" + strListDev.at(0) + "]";
    m_pDockOps->setWindowTitle("Ops: " + strDeviceName);
}

void MainWindow::on_actionChinese_triggered()
{
    if( !ui->actionEnglish->isChecked() && !ui->actionChinese->isChecked())
    {
        ui->actionChinese->setChecked(true);
        return;
    }
    ui->actionEnglish->setChecked(false);

    m_language = LANG_CN;
    changeLanguage();
    changeLanguage();
}

void MainWindow::on_actionEnglish_triggered()
{
    if( !ui->actionEnglish->isChecked() && !ui->actionChinese->isChecked())
    {
        ui->actionEnglish->setChecked(true);
        return;
    }

    ui->actionChinese->setChecked(false);

    m_language = LANG_EN;
    changeLanguage();
    changeLanguage();
}

void MainWindow::changeLanguage()
{
    QString qmFile = "";
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/config.xml";
    QMap<QString,QString> map;

    if( m_language == LANG_CN ){
         qmFile = ":/res/ts/qt_CN.qm";
         map.insert("Language", "Chinese");
    }
    else if( m_language == LANG_EN )
    {
        qmFile = ":/res/ts/qt_EN.qm";
        map.insert("Language", "English");
    }

    qDebug() << "changeLanguage:" << qmFile;
    m_roboConfig->changeLanguage(qmFile);
    m_pOps->changeLanguage(qmFile);

    qApp->removeTranslator(&m_translator);
    m_translator.load(qmFile);
    qApp->installTranslator(&m_translator);
    ui->retranslateUi(this);

    mXML.xmlNodeRemove(fileName, "WindowLanguage");
    mXML.xmlNodeAppend(fileName, "WindowLanguage", map);
}

void MainWindow::on_actionMega_triggered()
{
    if( !ui->actionClassic->isChecked() && !ui->actionMega->isChecked())
    {
        ui->actionMega->setChecked(true);
        return;
    }
    ui->actionClassic->setChecked(false);

    m_style = STYLE_MEGAROBO;
    setUiStyle(":/res/qss/mega.qss");
}

void MainWindow::on_actionClassic_triggered()
{
    if( !ui->actionClassic->isChecked() && !ui->actionMega->isChecked())
    {
        ui->actionClassic->setChecked(true);
        return;
    }

    ui->actionMega->setChecked(false);
    m_style = STYLE_CLASSIC;

//    QString qssText = qApp->styleSheet();
//    writeFile(QApplication::applicationDirPath() + "/style/111.qss",qssText);

    setUiStyle(":/res/qss/classic.qss");
}


void MainWindow::setUiStyle(const QString &styleFile)
{
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/config.xml";
    QMap<QString,QString> map;
    if( m_style == STYLE_MEGAROBO){
        map.insert("Style", "MegaRobo");
    }else{
        map.insert("Style", "Classic");
    }

    mXML.xmlNodeRemove(fileName, "WindowStyle");
    mXML.xmlNodeAppend(fileName, "WindowStyle", map);

    if( ! QFile::exists(styleFile) )
    {
        qDebug() << "setStyleSheet file not exists!";
        return;
    }


    QFile qss(styleFile);
    if( qss.open(QFile::ReadOnly) ){
        qApp->setStyleSheet(qss.readAll());
        qDebug() << "setStyleSheet:" << styleFile;
        qss.close();
    }
}

int MainWindow::writeFile(QString fileName, QString text)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << QString("Can't WriteOnly open the file: %1").arg(fileName);
        return -1;
    }

    file.write(text.toUtf8());
    file.close();
    return 0;
}

