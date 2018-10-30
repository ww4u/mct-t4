#ifndef SYSAPI_H
#define SYSAPI_H

#include <QtCore>

void sysInfo( const QString &str );
void sysInfo( const QString &str1, const QString &str2 );

void sysWarning( const QString &str );
void sysError( const QString &str );

#endif // SYSAPI_H
