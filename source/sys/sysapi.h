#ifndef SYSAPI_H
#define SYSAPI_H

#include <QtCore>

void sysInfo( const QString &str );
void sysInfo(const QString &info, const QString &str2 );
void sysInfo( const QString &info, const int &val );

void sysWarning( const QString &str );

void sysError( const QString &str );
void sysError( const QString &info , const int &val);

#endif // SYSAPI_H
