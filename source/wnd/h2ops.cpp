#include "h2ops.h"
#include "ui_h2ops.h"
#include "mydebug.h"

#include <QClipboard>
#include <QTime>

#include "megasplinechart.h"

H2Ops::H2Ops(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2Ops)
{
    ui->setupUi(this);


    //! actions for the logout
    mp_logClearAction = new QAction( tr("Clear"), this );
    mp_logSelectAllAction = new QAction( tr("Select All"), this );
    mp_logCopyAction = new QAction( tr("Copy"), this );

    mp_logSepAction = new QAction( this );
    mp_logSepAction->setSeparator( true );

    QList<QAction*> actions;
    actions<<mp_logSelectAllAction<<mp_logCopyAction<<mp_logSepAction<<mp_logClearAction;

    ui->lstLogout->addActions( actions );

    //! connect
    connect( mp_logClearAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_logClear_action()) );
    connect( mp_logSelectAllAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_logSelectAll_action()) );
    connect( mp_logCopyAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_logCopy_action()) );

    MegaSplineChart *m_splineChart1 = new MegaSplineChart("spline1 [%]");
    MegaSplineChart *m_splineChart2 = new MegaSplineChart("spline2 [%]");

    m_splineChart1->chart()->series()->setPen(QPen(Qt::blue));
    m_splineChart2->chart()->series()->setPen(QPen(Qt::red));

    ui->horizontalLayout_3->setMargin(0);
    ui->horizontalLayout_3->setSpacing(1);

    ui->horizontalLayout_3->addWidget(m_splineChart1);
    ui->horizontalLayout_3->addWidget(m_splineChart2);
    ui->horizontalLayout_3->addStretch();


}

H2Ops::~H2Ops()
{
    delete ui;
}

void H2Ops::outConsole( const QString &str, log_level e )
{
//    QString fmtStr = QString("%1:%2").arg( QTime::currentTime().toString("yyyy:MM::dd hh:mm:ss.zzz") ).arg(str);
    QString fmtStr = QDateTime::currentDateTime().toString("yyyy/M/d h/m/s.z") + " " + str;

    if ( e == e_log_info )
    { outInfo( fmtStr); }
    else if ( e == e_log_warning )
    { outWarning( fmtStr ); }
    else if ( e == e_log_error )
    { outError( fmtStr ); }
    else
    {}
}

void H2Ops::outInfo( const QString &str )
{
    QListWidgetItem *pItem = new QListWidgetItem( QIcon(":/res/image/icon/xiaoxi.png"), str );
    ui->lstLogout->addItem( pItem );

}
void H2Ops::outWarning( const QString &str )
{
    QListWidgetItem *pItem = new QListWidgetItem( QIcon(":/res/image/icon/gantanhaozhong.png"), str );
    ui->lstLogout->addItem( pItem );
}
void H2Ops::outError( const QString &str )
{
    QListWidgetItem *pItem = new QListWidgetItem( QIcon(":/res/image/icon/shibai2.png"), str );
    ui->lstLogout->addItem( pItem );
}

void H2Ops::slot_logSelectAll_action()
{
    ui->lstLogout->selectAll();
}
void H2Ops::slot_logCopy_action()
{
    //! cat text
    QString str;
    for ( int i = 0; i < ui->lstLogout->count(); i++ )
    {
        if ( ui->lstLogout->item(i)->isSelected() )
        {
            str.append( ui->lstLogout->item( i )->text() );
            str.append( '\n' );
        }
    }

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText( str );
}
void H2Ops::slot_logClear_action()
{ logDbg();
    ui->lstLogout->clear();
}

