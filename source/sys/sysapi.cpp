#include "sysapi.h"
#include "mainwindow.h"

void sysInfo( const QString &str )
{ MainWindow::requestLogout( str, eLogInfo ); }

void sysInfo( const QString &info, const QString &str2 )
{
    QString str = QString("%1 %2").arg(info).arg(str2);
    MainWindow::requestLogout( str, eLogInfo );
}

void sysInfo( const QString &info, const int &val )
{
    QString str = QString("%1 : %2").arg(info).arg(val);
    MainWindow::requestLogout( str, eLogInfo );
}

void sysWarning( const QString &str )
{ MainWindow::requestLogout( str, eLogWarning ); }

void sysError( const QString &str )
{ MainWindow::requestLogout( str, eLogError ); }

void sysError( const QString &info , const int &val)
{
    QString str = QString("%1 : %2").arg(info).arg(val);
    MainWindow::requestLogout( str, eLogError );
}


