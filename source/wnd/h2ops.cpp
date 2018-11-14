#include "h2ops.h"
#include "ui_h2ops.h"
#include "mydebug.h"

#include <QClipboard>
#include <QTime>
#include <QFileDialog>

#include "megasplinechart.h"

#include "../sys/sysapi.h"
#include "../widget/megamessagebox.h"

H2Ops::H2Ops(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Ops)
{
    ui->setupUi(this);

    setupUi();

    setupName();

    buildConnection();

    setupModel();
}

H2Ops::~H2Ops()
{
    delete ui;
}

void H2Ops::setupUi()
{
    //! actions for the logout
    mp_logClearAction = new QAction( tr("Clear"), this );
    mp_logSelectAllAction = new QAction( tr("Select All"), this );
    mp_logCopyAction = new QAction( tr("Copy"), this );

    mp_logSepAction = new QAction( this );
    mp_logSepAction->setSeparator( true );

    QList<QAction*> actions;
    actions<<mp_logSelectAllAction<<mp_logCopyAction<<mp_logSepAction<<mp_logClearAction;

    ui->lstLogout->addActions( actions );

    //! monitor
    MegaSplineChart *m_splineChart1 = new MegaSplineChart(tr("Energy1"));
    MegaSplineChart *m_splineChart2 = new MegaSplineChart(tr("Energy2"));

    m_splineChart1->chart()->series()->setPen(QPen(Qt::blue));
    m_splineChart2->chart()->series()->setPen(QPen(Qt::red));

    ui->horizontalLayout_3->setMargin(0);
    ui->horizontalLayout_3->setSpacing(1);

    ui->horizontalLayout_3->addWidget(m_splineChart1);
    ui->horizontalLayout_3->addWidget(m_splineChart2);
    ui->horizontalLayout_3->addStretch();
}

#define set_name( the, name )   the->setName( name );\
                                mSubTabs.append( the );
void H2Ops::setupName()
{
    set_name( ui->tab_LogOut,   "tab_LogOut");
    set_name( ui->tab_Operate,  "tab_Operate");
    set_name( ui->tab_DigitalIO,"tab_DigitalIO");
    set_name( ui->tab_Homing,   "tab_Homing");
    set_name( ui->tab_Manual,   "tab_Manual");
    set_name( ui->tab_Monitor,  "tab_Monitor");
    set_name( ui->Debug,        "tab_Debug");
    set_name( ui->tab_Diagnosis,"tab_Diagnosis");
}

void H2Ops::setupModel()
{
    //! model
    m_pDiagnosisModel= new DiagnosisModel();
    ui->tvDiagnosis->setModel( m_pDiagnosisModel );

    m_pDebugModel = new DebugModel();
    ui->tvDebug->setModel( m_pDebugModel );
}

void H2Ops::buildConnection()
{
    //! connect
    connect( mp_logClearAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_logClear_action()) );
    connect( mp_logSelectAllAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_logSelectAll_action()) );
    connect( mp_logCopyAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_logCopy_action()) );

    //! option
    foreach( XConfig *pCfg, mSubTabs )
    {
        connect( pCfg, SIGNAL(signal_focus_in( const QString &)),
                 this, SIGNAL(signal_focus_in( const QString &)));
    }
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

void H2Ops::slotSetCurrentRobot(QString strDevType, int visa, int name)
{
    m_ViHandle = visa;
    m_RoboName = name;

//    qDebug() << "H2OPS:" << m_ViHandle << m_RoboName;
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

//! debug
void H2Ops::on_btnUp_clicked()
{
    //! current valid
    if ( ui->tvDebug->currentIndex().isValid() )
    {}
    else
    { return; }

    //! check up index
    QModelIndex prev = m_pDebugModel->index( ui->tvDebug->currentIndex().row() - 1,
                                             ui->tvDebug->currentIndex().column() );
    if ( prev.isValid() )
    {}
    else
    { return; }

    DebugItem *pItem = m_pDebugModel->items()->takeAt( ui->tvDebug->currentIndex().row() );
    if ( NULL == pItem )
    { return; }

    //! exchange
    m_pDebugModel->items()->insert( ui->tvDebug->currentIndex().row() - 1, pItem );
    m_pDebugModel->signal_dataChanged(m_pDebugModel->index( ui->tvDebug->currentIndex().row()-1, 0 ),
                                      m_pDebugModel->index( ui->tvDebug->currentIndex().row(), 1 ));

    ui->tvDebug->setCurrentIndex( prev );

}

void H2Ops::on_btnDown_clicked()
{
    if ( ui->tvDebug->currentIndex().isValid() )
    {}
    else
    { return; }

    //! check next index
    QModelIndex next = m_pDebugModel->index( ui->tvDebug->currentIndex().row() + 1,
                                             ui->tvDebug->currentIndex().column() );
    if ( next.isValid() )
    {}
    else
    { return; }

    DebugItem *pItem = m_pDebugModel->items()->takeAt( ui->tvDebug->currentIndex().row() );
    if ( NULL == pItem )
    { return; }

    m_pDebugModel->items()->insert( next.row(), pItem );
    m_pDebugModel->signal_dataChanged(
                                        m_pDebugModel->index( ui->tvDebug->currentIndex().row(), 0 ),
                                        m_pDebugModel->index( ui->tvDebug->currentIndex().row()+1, 1 )
                                    );
    ui->tvDebug->setCurrentIndex( next );
}

void H2Ops::on_btnAdd_clicked()
{
    if ( ui->tvDebug->currentIndex().isValid() )
    {
        m_pDebugModel->insertRow( ui->tvDebug->currentIndex().row() + 1 );
        m_pDebugModel->setData( m_pDebugModel->index( ui->tvDebug->currentIndex().row()+1, 1),
                                QVariant( ui->spinDly->value()),
                                Qt::EditRole );
    }
    else
    {
        m_pDebugModel->insertRow( 0 );
        m_pDebugModel->setData( m_pDebugModel->index( 0, 1),
                                QVariant( ui->spinDly->value()),
                                Qt::EditRole );
        return;
    }
}

void H2Ops::on_btnDel_clicked()
{
    if ( ui->tvDebug->currentIndex().isValid() )
    {}
    else
    { return; }

    m_pDebugModel->removeRow( ui->tvDebug->currentIndex().row() );
}

void H2Ops::on_btnClr_clicked()
{
    MegaDeleteAffirmMessageBox msgBox;
    int ret = msgBox.exec();
    if ( ret == QMessageBox::Ok )
    {
        m_pDebugModel->removeRows( 0, m_pDebugModel->items()->count(), QModelIndex() );
    }
}

void H2Ops::on_btnImport_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptOpen );
    fDlg.setNameFilter( tr("Debug (*.xml)") );

    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    m_pDebugModel->load( fDlg.selectedFiles().first() );

    sysInfo( fDlg.selectedFiles().first(), tr("load completed") );
}

void H2Ops::on_btnExport_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptSave );
    fDlg.setNameFilter( tr("Debug (*.xml)") );

    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    m_pDebugModel->save( fDlg.selectedFiles().first() );

    sysInfo( fDlg.selectedFiles().first(), tr("save completed") );
}

//! diagnosis
void H2Ops::on_btnRead_clicked()
{
    //! \todo read from device
    //! debug for the model
    m_pDiagnosisModel->createDemoData();
}

void H2Ops::on_btnDelete_clicked()
{
    MegaDeleteAffirmMessageBox msgBox;
    int ret = msgBox.exec();
    if ( ret == QMessageBox::Ok )
    {
        m_pDiagnosisModel->removeRows( 0, m_pDiagnosisModel->items()->count(), QModelIndex() );
    }
}

void H2Ops::on_btnExport_2_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptSave );
    fDlg.setNameFilter( tr("Diagnosis (*.xml)") );

    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    m_pDiagnosisModel->save( fDlg.selectedFiles().first() );

    sysInfo( fDlg.selectedFiles().first(), tr("save completed") );
}

void H2Ops::on_tabWidget_currentChanged(int index)
{
    emit signal_focus_in( ui->tabWidget->tabText( index ) );
}

void H2Ops::on_tabWidget_tabBarClicked(int index)
{
    emit signal_focus_in( ui->tabWidget->tabText( index ) );
}

QString H2Ops::getDeviceTypeName(QString strDevInfo)
{
    QStringList strListDev = strDevInfo.split(',', QString::SkipEmptyParts);
    QString strDeviceName = "";
    if(strListDev.count() == 0)
    {   return "";     }

    if(strListDev.count() > 2)
    {   strDeviceName = strListDev.at(2) + "[" + strListDev.at(0) + "]";    }
    else
    {   strDeviceName = strListDev.at(0);    }

    return strDeviceName;
}
