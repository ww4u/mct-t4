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

void Maintain::retranslateUi()
{
    ui->retranslateUi( this );
}

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

    ui->btnResetPw->setVisible( bAdmin );
    ui->cmbRstUser->setVisible( bAdmin );
    ui->btnBuild->setVisible( bAdmin );
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

//    QString descripton;
//    bool bOk;
//    descripton = QInputDialog::getText( this,
//                                        tr("Descripton"),
//                                        tr("Backup description:"),
//                                        QLineEdit::Normal,
//                                        QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz" ),
//                                        &bOk
//                                        );
//    if ( !bOk )
//    { return; }

//    descripton = descripton.simplified();
//    if ( descripton.isEmpty() )
//    {
//        sysPrompt( tr("Invalid description"), 0 );
//        return;
//    }

//    int ret;
//    QString cmd, dstPath;
//    do
//    {
//        //! make dir
//        QString uuid = QDateTime::currentDateTimeUtc().toString("yyyyMMddhhmmss_zzz");
//        dstPath = m_pPlugin->selfPath() + "/backup/" + uuid;
//        cmd = "mkdir -p " + dstPath;
//        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );
//        if ( ret != 0 )
//        { break; }

//        //! copy the data in
//        cmd = "cp " + m_pPlugin->selfPath() + "/*.xml " + dstPath;
//        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );
//        if ( ret != 0 )
//        { break; }

//        cmd = "cp " + m_pPlugin->selfPath() + "/*.mrp " + dstPath;
//        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );
//        if ( ret != 0 )
//        { break; }

//        //! copy the log
//        cmd = "cp -r /home/megarobo/MRH-T/log " + dstPath + "/log";
//        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );
//        if ( ret != 0 )
//        { break; }

//        //! write the description
//        ret = mrgStorageWriteFile( m_pPlugin->deviceVi(),
//                                   0,
//                                   dstPath.toLatin1().data(),
//                                   "description",
//                                   (quint8*)descripton.toLatin1().data(),
//                                   descripton.length()
//                                   );
//        if ( ret != 0 )
//        { break; }

//    }while( 0 );

//    if ( ret != 0 )
//    {
//        cmd = "rm -rf " + dstPath;
//        ret = mrgSystemRunCmd( m_pPlugin->deviceVi(), cmd.toLatin1().data(), 0 );

//        sysPrompt( tr("Backup fail") );
//    }
//    else
//    {
//        sysPrompt( tr("Backup completed"), 0 );
//    }
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

//    QString dir = QFileDialog::getExistingDirectory(this, tr("Open"));
//    logDbg() << dir;
//    QString path;
//    int ret;
//    do{
//        path = m_pPlugin->selfPath() + "/backup/";
//        char buf[4096]="";
//        int iLen = sizeof(buf);
//        ret = mrgStorageDirectoryEnum( m_pPlugin->deviceVi(), 0, path.toLocal8Bit().data(), buf, &iLen);
//        if(ret<0){
//            ret = -1;
//            break;
//        }else{
//            if(ret==0){
//                sysPrompt(tr("No File To Export"),2);
//                return;
//            }
//        }

//        QStringList dirList = QString(buf).split("\n", QString::SkipEmptyParts);
//        foreach (QString str, dirList) {
//            //! file list
//            char tBuf[4096]={0};
//            int tLen = sizeof(tBuf);
//            ret = mrgStorageDirectoryEnum( m_pPlugin->deviceVi(), 0, (path + str).toLocal8Bit().data(), tBuf, &tLen);
//            if( ret < 0 ){
//                ret = -1;
//                break;
//            }

//            QStringList tList = QString(tBuf).split("\n", QString::SkipEmptyParts);
//            QStringList subDirList,subFileList;
//            foreach (QString t, tList) {
//                if(t.endsWith("/")){
//                    subDirList << t;
//                }else{
//                    subFileList << t;
//                }
//            }

//            //! subFile
//            foreach (QString s, subFileList) {
//                QByteArray ba;
//                ret = mrgStorageGetFileSize(m_pPlugin->deviceVi(), 0, (path + str).toLocal8Bit().data(), s.toLocal8Bit().data());
//                if( ret < 0){
//                    continue;
//                }
//                ba.resize(ret);
//                ret = mrgStorageReadFile(m_pPlugin->deviceVi(), 0, (path+str).toLocal8Bit().data(), s.toLocal8Bit().data(),(quint8*)ba.data());
//                if( ret <=0 ){
//                    continue;
//                }
//                QDir tDir;
//                if( !tDir.mkpath(dir + "/" + str) )
//                    continue;
//                QFile f(dir+"/"+str+s);
//                if(!f.open(QIODevice::WriteOnly)){
//                    continue;
//                }
//                f.write(ba);
//                f.close();
//            }

//            //! subDir
//            foreach (QString sd, subDirList) {
//                char sdBuf[4096]="";
//                int sdLen = sizeof(sdBuf);
//                ret = mrgStorageDirectoryEnum(m_pPlugin->deviceVi(), 0, (path+str+sd).toLocal8Bit().data(), sdBuf, &sdLen);
//                if(ret<0){
//                    continue;
//                }
//                QStringList subFileList = QString(sdBuf).split("\n", QString::SkipEmptyParts);
//                foreach (QString sFile, subFileList) {
//                    QByteArray ba;
//                    ret = mrgStorageGetFileSize(m_pPlugin->deviceVi(), 0, (path+str+sd).toLocal8Bit().data(), sFile.toLocal8Bit().data());
//                    if(ret<0){
//                        continue;
//                    }
//                    ba.resize(ret);
//                    ret = mrgStorageReadFile(m_pPlugin->deviceVi(), 0, (path+str+sd).toLocal8Bit().data(), sFile.toLocal8Bit().data(),(quint8*)ba.data());
//                    if( ret <0 ){
//                        continue;
//                    }
//                    QDir tDir;logDbg() << dir+"/"+str+sd+sFile;
//                    if( !tDir.mkpath(dir +"/"+ str+sd) )
//                        continue;
//                    QFile f(dir+"/"+str+sd+sFile);
//                    if(!f.open(QIODevice::WriteOnly)){
//                        continue;
//                    }
//                    f.write(ba);
//                    f.close();
//                }
//            }

//        }
//    }while(0);
}

void Maintain::on_btnBuild_clicked()
{
    //! \todo send file

}
}

