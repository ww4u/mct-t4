#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include "aboutdlg.h"

#include "h2config.h"
#include "h2ops.h"

MainWindow *MainWindow::_pBackendProxy = NULL;

void MainWindow::requestLogout( const QString &str, log_level lev )
{
    if( NULL != MainWindow::_pBackendProxy )
    {}
    else
    { return; }

    MainWindow::_pBackendProxy->slot_logout( str, lev );
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupWorkArea();

    setupToolBar();

    setupStatusBar();

    buildConnection();

    //! register the proxy
    MainWindow::_pBackendProxy = this;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWorkArea()
{
    H2Config *pPref = new H2Config( this );

    //! docks
    ui->centralWidget->insertTab( 0, pPref, tr("Pref") );

    //! dock
    QDockWidget *pDock;
    pDock = new QDockWidget( tr("Ops"), this );
    pDock->setAllowedAreas(  Qt::BottomDockWidgetArea );
    pDock->setFeatures( QDockWidget::DockWidgetVerticalTitleBar
                           | pDock->features() );
    addDockWidget( Qt::BottomDockWidgetArea, pDock );

    m_pOps = new H2Ops();
    pDock->setWidget( m_pOps );

    ui->menuView->addAction( pDock->toggleViewAction() );
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
    ui->mainToolBar->addAction( ui->actionConnect );
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
    slot_logout( tr("start completed") );
    slot_logout( tr("start warning"), e_log_warning );
    slot_logout( tr("start error"), e_log_error );
}

void MainWindow::slot_logout( const QString &str, log_level lev )
{
    Q_ASSERT( NULL != m_pOps );

    m_pOps->outConsole( str, lev );
}


void MainWindow::on_actionAbout_triggered()
{
    aboutDlg dlg(this);
    dlg.exec();
}
void MainWindow::on_actionHelp_triggered()
{

}

