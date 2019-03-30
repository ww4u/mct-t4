#include "sysapi.h"
#include "mainwindow.h"

static sysPara _sysPara = { sysPara::e_sys_user };

void setSysMode( sysPara::eSysMode mode )
{
    _sysPara.mMode = mode;
}
sysPara::eSysMode sysMode()
{ return _sysPara.mMode; }

void sysInfo( const QString &str )
{ MainWindow::requestLogout( str, LogStr::log_info ); }

void sysInfo( const QString &info, const QString &str2 )
{
    QString str = QString("%1 %2").arg(info).arg(str2);
    MainWindow::requestLogout( str, LogStr::log_info );
}

void sysInfo( const QString &info, const int &val )
{
    QString str = QString("%1 : %2").arg(info).arg(val);
    MainWindow::requestLogout( str, LogStr::log_info );
}

void sysWarning( const QString &str )
{ MainWindow::requestLogout( str, LogStr::log_warning ); }

void sysError( const QString &str )
{ MainWindow::requestLogout( str, LogStr::log_error ); }

void sysError( const QString &info , const int &val)
{
    QString str = QString("%1 : %2").arg(info).arg(val);
    MainWindow::requestLogout( str, LogStr::log_error );
}

void sysProgress( const QString &info, bool b, int now, int mi, int ma )
{
    MainWindow::requestProgress( info, b, now, mi, ma );
}

void sysPrompt( const QString &info, int lev )
{ MainWindow::requestPrompt( info, lev ); }

void sysShowStatus(const QString &statusInfo)
{
    MainWindow::showStatus(statusInfo);
}

bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

QString readFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << QString("Can't ReadOnly open the file: %1").arg(fileName);
        return "";
    }

    QByteArray array = file.readAll();
    file.close();
    return QString(array);
}

int writeFile(QString fileName, QString text)
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

int assurePath( const QString &path )
{
    //! create path
    QDir dir( path );
    if ( dir.exists() )
    {}
    else
    {
        if ( dir.mkpath( path) )
        {}
        else
        {
            sysError( path + " " + QObject::tr("create fail") );
            return -1;
        }
    }

    return 0;
}
