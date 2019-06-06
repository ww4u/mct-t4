#include "maintain.h"
#include "ui_maintain.h"

#include "t4.h"
#include "MegaGateway.h"
#include <qmessagebox.h>
#define msgBox_Warning_ok( title, content )     (QMessageBox::warning(this, title, content, QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok ? 1:0)
#define msgBox_Information_ok( title, content ) (QMessageBox::information(this, title, content, QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok ? 1:0)


namespace mrx_t4 {
Maintain::Maintain(QWidget *parent) :
    XPage(parent),
    ui(new Ui::Maintain)
{
    ui->setupUi(this);

    setContextHelp("maintain");

    on_cmbDemo_currentIndexChanged( ui->cmbDemo->currentIndex() );
}

Maintain::~Maintain()
{
    delete ui;
}

void Maintain::enterMission()
{ setOperAble( false ) ;}
void Maintain::exitMission()
{ setOperAble( true ); }

void Maintain::setOperAble( bool b )
{
    //! for each page operate able
    setOpened( b );
}
void Maintain::setOpened( bool b )
{
    //! for each page operate
    for ( int i = 0; i < ui->tabWidget->count(); i++ )
    {
        ui->tabWidget->widget(i)->setEnabled( b );
    }

    logDbg()<<b;
}

void Maintain::on_cmbDemo_currentIndexChanged(int index)
{
    //! set the demo info
    //! \todo add more info
    QString demo1Info = tr( "The Test file" );

    ui->txtDemoInfo->setText( demo1Info );
}

void Maintain::on_btnDemo_clicked()
{
    Q_ASSERT( NULL != m_pPlugin );

    int ret = m_pPlugin->startDemo( ui->cmbDemo->currentIndex() );

    if ( ret != 0 )
    {
        sysPrompt( tr("Demo fail"), 0 );
    }
}

void Maintain::on_btnRestart_clicked()
{
    if( msgBox_Warning_ok( tr("Warning"), tr("Confirm Reboot?") ) )
    { m_pPlugin->reboot(); }
}

void Maintain::on_btnShutDown_clicked()
{
    if(msgBox_Warning_ok( tr("Warning"), tr("Confirm PowerOff?") ))
    { m_pPlugin->powerOff(); }
}

void Maintain::on_btnReset_clicked()
{
    if ( msgBox_Warning_ok( tr("Warning"), tr("Confirm Reset?") ))
    { m_pPlugin->rst(); }
}

void Maintain::on_btnUpdate_clicked()
{
    //! \todo
}

void Maintain::on_btnFold_clicked()
{
    m_pPlugin->fold();
}

void Maintain::on_btnBackup_clicked()
{
    QString descripton;
    bool bOk;
    descripton = QInputDialog::getText( this,
                                        tr("Descripton"),
                                        tr("Backup description:"),
                                        QLineEdit::Normal,
                                        QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz" ),
                                        &bOk
                                        );
    if ( !bOk )
    { return; }

    if ( descripton.isEmpty() )
    {
        sysPrompt( tr("Invalid description"), 0 );
        return;
    }

    int ret;
    QString cmd, dstPath;
    do
    {
        //! make dir
        QString uuid = QDateTime::currentDateTimeUtc().toString("yyyyMMddhhmmss_zzz");
        dstPath = m_pPlugin->selfPath() + "/backup/" + uuid;
        cmd = "mkdir -p " + dstPath;
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );
        if ( ret != 0 )
        { break; }

        //! copy the data in
        cmd = "cp " + m_pPlugin->selfPath() + "/*.xml " + dstPath;
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );
        if ( ret != 0 )
        { break; }

        cmd = "cp " + m_pPlugin->selfPath() + "/*.mrp " + dstPath;
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );
        if ( ret != 0 )
        { break; }
logDbg()<<dstPath<<descripton;
        //! write the description
        ret = mrgStorageWriteFile( m_pPlugin->deviceVi(),
                                   0,
                                   dstPath.toLatin1().data(),
                                   "description",
                                   (quint8*)descripton.toLatin1().data(),
                                   descripton.length()
                                   );
        if ( ret != 0 )
        { break; }

    }while( 0 );

    if ( ret != 0 )
    {
        cmd = "rm -rf " + dstPath;
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );

        sysPrompt( tr("Backup fail") );
    }
    else
    {
        sysPrompt( tr("Backup completed"), 0 );
    }
}

void Maintain::on_btnClearBackup_clicked()
{
    int ret = -1;
    if( msgBox_Warning_ok( tr("Warning"), tr("Confirm Clear?") ) )
    {
        QString cmd;

        cmd = "rm -rf " + m_pPlugin->selfPath() + "/backup";
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );
    }

    if ( ret != 0 )
    {
        sysPrompt( tr("Clear fail") );
    }
    else
    {
        sysPrompt( tr("Clear completed"),0 );
    }
}

}



