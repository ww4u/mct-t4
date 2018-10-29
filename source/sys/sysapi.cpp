#include "sysapi.h"

#include "../wnd/mainwindow.h"

void sysInfo( const QString &str )
{ MainWindow::requestLogout( str, e_log_info ); }

void sysWarning( const QString &str )
{ MainWindow::requestLogout( str, e_log_warning ); }

void sysError( const QString &str )
{ MainWindow::requestLogout( str, e_log_error ); }
