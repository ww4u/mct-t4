#include "maintain.h"
#include "ui_maintain.h"

#include "t4.h"

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

}
