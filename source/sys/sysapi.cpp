#include "sysapi.h"

#include "../wnd/mainwindow.h"

void sysInfo( const QString &str )
{ MainWindow::requestLogout( str, e_log_info ); }

void sysInfo( const QString &str1, const QString &str2 )
{
    QString str = QString("%1 %2").arg(str1).arg(str2);
    MainWindow::requestLogout( str, e_log_info );
}

void sysWarning( const QString &str )
{ MainWindow::requestLogout( str, e_log_warning ); }

void sysError( const QString &str )
{ MainWindow::requestLogout( str, e_log_error ); }
