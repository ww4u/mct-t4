#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>

#include "h2config.h"
#include "h2ops.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupWorkArea();

    setupToolBar();
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

    H2Ops *pOps = new H2Ops();
    pDock->setWidget( pOps );

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
