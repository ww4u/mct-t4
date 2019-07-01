#include "maintain.h"
#include "ui_maintain.h"

#include "t4.h"
#include "MegaGateway.h"
#include <qmessagebox.h>
#include "widget.h"

#include "../../wnd/changedpw.h"
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

void Maintain::updateRole()
{
    bool bAdmin = m_pPlugin->isAdmin();
logDbg()<<bAdmin;
    ui->btnResetPw->setVisible( bAdmin );
    ui->cmbRstUser->setVisible( bAdmin );
}

void Maintain::updateUi()
{
    ui->chkAutoLogin->setChecked( m_pPlugin->isAutoLogin() );
}

void Maintain::on_cmbDemo_currentIndexChanged(int index)
{
    //! set the demo info

    QStringList strList;
    strList<<tr("Demo0:\n"
                "* drag and drop in two points.\n"
                )
            <<tr("Demo1:\n"
                 "* Moving in the working space.\n"
                 "* It is used in the factory test procedure.\n"
                  );
//            <<tr("Demo3:\n"
//             "* Draw the logo.\n"
//             "* Draw \"MEGAROBO\".\n"
//              );

    if ( index < strList.size() )
    {
        ui->txtDemoInfo->setText( strList.at(index) );
    }
    else
    {
        ui->txtDemoInfo->setText( tr("No demo descripton") );
    }
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
    Widget w;
    w.attatchPlugin(m_pPlugin);
    w.exec();
}

void Maintain::on_btnHistory_clicked()
{
    //! \todo need the file size api
    QByteArray ary;
    ary.reserve( 1024 * 1024 );

    int ret;
    //! read the history from remote and show
    ret = mrgStorageReadFile( m_pPlugin->deviceVi(), 0,
                        (QString(mct_path) + "/" + "MRX-T4").toLatin1().data(),
                        update_file_name,
                        (quint8*)ary.data() );
    if ( ret <= 0 )
    {
        sysError(tr("Read File Fail"));
        return;
    }

    ary.resize( ret );

    //! write
    QString fileName = QDir::tempPath() + "/" + update_file_name;
    QFile file( fileName );
    if ( file.open(QIODevice::WriteOnly ) )
    {
        file.write( ary );
        file.close();
    }
    else
    { return; }

    //! show doc
    QStringList args;
    QString str;
    str = fileName;
    str.replace("/","\\");
    args<<str;

    //! \todo linux
    QProcess::execute( "explorer.exe", args );
}

void Maintain::on_btnFold_clicked()
{
    m_pPlugin->fold();
}

void Maintain::on_btnBackup_clicked()
{
    FileManager manager;
    manager.attachPlugin(m_pPlugin);
    manager.setPath( m_pPlugin->selfPath()+"/backup/" );
    manager.setMode( BACKUP );
    if( manager.exec() == QDialog::Accepted ){
    }else{ return; }

    QString str = manager.strResult();
    int ret;
    QString cmd, dstPath;
    do{
        dstPath = m_pPlugin->selfPath() + "/backup/" + str;
        cmd = "mkdir -p " + dstPath;
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLocal8Bit().data(), 0 );
        if ( ret != 0 )
        { ret = -1; break; }

        //! copy the data in
        cmd = "cp " + m_pPlugin->selfPath() + "/*.xml " + dstPath;
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLocal8Bit().data(), 0 );
        if ( ret != 0 )
        { ret = -1;break; }

        cmd = "cp " + m_pPlugin->selfPath() + "/*.mrp " + dstPath;
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLocal8Bit().data(), 0 );
        if ( ret != 0 )
        { ret = -1;break; }

        //! copy the log
        cmd = "cp -r /home/megarobo/MRH-T/log " + dstPath + "/log";
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLocal8Bit().data(), 0 );
        if ( ret != 0 )
        { ret = -1;break; }

        //! write the description
        ret = mrgStorageWriteFile( m_pPlugin->deviceVi(),
                                   0,
                                   dstPath.toLocal8Bit().data(),
                                   "description",
                                   (quint8*)str.toLocal8Bit().data(),
                                   str.length()
                                   );
        if ( ret != 0 )
        { ret = -1;break; }
    }while(0);

    if( ret == -1){
        cmd = "rm -rf " + dstPath;
        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );
        sysError(tr("Backup Fail"));

    }else{
        sysInfo(tr("Backup Complete"));
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
    }else{ return; }

    if ( ret != 0 )
    {
        sysPrompt( tr("Clear fail") );
    }
    else
    {
        sysPrompt( tr("Clear completed"),0 );
    }
}

void Maintain::on_cmbUser_currentIndexChanged(int index)
{
    //! is equal
    if ( index == (int)m_pPlugin->userRole() )
    { return; }

    bool bOk;
    QString adminPw;

    adminPw = m_pPlugin->getPw( XPluginIntf::user_admin, bOk );
    if ( bOk && adminPw.length() > 0 )
    {}
    else
    { return; }

    //! require
    //! to user
    if ( index == 0 )
    {
        m_pPlugin->setUserRole( (XPluginIntf::eUserRole)index );
    }
    //! to admin
    else if ( index == 1 )
    {
        do
        {
            QString pw;
            pw = QInputDialog::getText( this, tr("Password"), tr("Password"), QLineEdit::Password, QString(), &bOk );

            if ( bOk && adminPw == pw )
            {
                m_pPlugin->setUserRole( (XPluginIntf::eUserRole)index );
                break;
            }
            if ( bOk )
            {
                QMessageBox::critical( this, tr("Error"), tr("Invalid password") );
            }
            ui->cmbUser->setCurrentIndex( 0 );
        }while( 0 );
    }
}

void Maintain::on_btnChange_clicked()
{
    ChangedPw changePw;

    if ( QDialog::Accepted != changePw.exec() )
    { return; }

    //! check pw
    bool bOk;
    if ( changePw.getOldPw() == m_pPlugin->getPw( (XPluginIntf::eUserRole)ui->cmbUser->currentIndex(), bOk) && bOk )
    {}
    else
    {
        QMessageBox::critical( this, tr("Error"), tr("Invalid password") );
        return;
    }

    //! check the pw
    m_pPlugin->setPw( (XPluginIntf::eUserRole)ui->cmbUser->currentIndex(),
                      changePw.getNewPw() );
}

//! \note only for admin
void Maintain::on_btnResetPw_clicked()
{
    bool bOk;
    QString pw;
    pw = QInputDialog::getText( this, tr("Password"), tr("Admin Password"), QLineEdit::Password, QString(), &bOk );
    if ( bOk && pw.simplified().size() > 0 )
    {}
    else
    { return; }

    if ( pw == m_pPlugin->getPw( XPluginIntf::user_admin, bOk) && bOk )
    {}
    else
    {
        QMessageBox::critical( this, tr("Error"), tr("Invalid password") );
        return;
    }

    //! reset
    m_pPlugin->rstPw( (XPluginIntf::eUserRole)ui->cmbRstUser->currentIndex() );
}

void Maintain::on_chkAutoLogin_stateChanged(int arg1)
{
    Q_ASSERT( m_pPlugin != NULL );
    m_pPlugin->setAutoLogin( ui->chkAutoLogin->isChecked() );
}

void Maintain::on_btnRestore_clicked()
{
    FileManager manage;
    QString str;
    int ret;
    manage.setPath(m_pPlugin->selfPath()+"/backup/");
    manage.attachPlugin(m_pPlugin);
    manage.setMode(RESTORE);
    if( manage.exec() == QDialog::Accepted ){
    }else{return;}

    do{
        str = manage.strResult();
        QString sourcePath = m_pPlugin->selfPath()+"/backup/"+str;

        QString cmd = "cp " + sourcePath + "*.xml " + m_pPlugin->selfPath();
        ret = mrgSystemRunCmd(m_pPlugin->deviceVi(), cmd.toLocal8Bit().data(), 0);
        if( ret !=0 )
        { ret = -1; break; }

        cmd = "cp " + sourcePath + "*.mrp " + m_pPlugin->selfPath();
        ret = mrgSystemRunCmd(m_pPlugin->deviceVi(), cmd.toLocal8Bit().data(), 0);
        if(ret !=0)
        { ret = -1; break; }

        //! log ?

    }while(0);

    if(ret ==-1){
        sysError(tr("Restore Fail"));
    }else{
        sysInfo(tr("Restore Complete"));
    }
}

void Maintain::on_btnExport_clicked()
{
    int ret;
    FileManager manager;
    manager.setMode(EXPORT);
    manager.attachPlugin(m_pPlugin);
    manager.setPath(m_pPlugin->selfPath()+"/backup/");
    if(manager.exec() == QDialog::Accepted){

    }else{ return; }

    QString str = manager.strResult();

    QString sourceDir = m_pPlugin->selfPath()+"/backup/"+str;
    QString distDir = QFileDialog::getExistingDirectory(this,tr("Export"));
    if(distDir.isEmpty())   return;

    QDir dir;
    bool bOk = dir.mkpath( distDir+"/"+ str +"log" );
    if(bOk){

    }else{ sysInfo(tr("Mkdir Fail"),1);return; }

    QStringList fileList;
    fileList << "config.xml" << "debug.xml" << "description"
             << "diagnosis.xml" << "MCT_motion.mrp" << "password.xml";

    foreach (QString s, fileList) {
        QByteArray ba;
        ret = mrgStorageGetFileSize(m_pPlugin->deviceVi(), 0,
                                        sourceDir.toLocal8Bit().data(),
                                        s.toLocal8Bit().data());
        if(ret<0){
            ret = -1;
            break;
        }

        ba.resize(ret);
        ret = mrgStorageReadFile(m_pPlugin->deviceVi(), 0,
                                 sourceDir.toLocal8Bit().data(),
                                 s.toLocal8Bit().data(),
                                 (quint8*)ba.data());
        if( ret <0 ){logDbg()<<s<<ret;
            ret = -1;
            break;
        }

        //! write
        QFile f(distDir+"/"+str+s);
        if(!f.open(QIODevice::WriteOnly)){
            sysInfo(tr("Open Fail"),1);
            ret = -1;
            break;
        }
        f.write(ba);
        f.close();
    }

    //! log
    char Buf[4096]="";
    int iLen = sizeof(Buf);
    ret = mrgStorageDirectoryEnum(m_pPlugin->deviceVi(),0,
                            (sourceDir+"log/").toLocal8Bit().data(),
                            Buf,
                            &iLen);
    if(ret <0){ sysInfo(tr("Enum log fail"));return; }

    QStringList logList = QString(Buf).split("\n", QString::SkipEmptyParts);
    foreach (QString l, logList) {
        QByteArray ba;
        ret = mrgStorageGetFileSize(m_pPlugin->deviceVi(), 0,
                                    (sourceDir+"log/").toLocal8Bit().data(),
                                     l.toLocal8Bit().data());
        if(ret<0){
            break;
        }

        ba.resize(ret);
        ret = mrgStorageReadFile(m_pPlugin->deviceVi(), 0,
                                 (sourceDir+"log/").toLocal8Bit().data(),
                                 l.toLocal8Bit().data(),
                                 (quint8*)ba.data());
        if( ret <0 ){logDbg()<<l<<ret;
            break;
        }

        //! write
        QFile f(distDir+"/"+str+"log/"+l);
        if(!f.open(QIODevice::WriteOnly)){
            sysInfo(tr("Open Fail"),1);
            break;
        }
        f.write(ba);
        f.close();
    }
}

void Maintain::on_btnBuild_clicked()
{
    //! \todo send file

}
}

