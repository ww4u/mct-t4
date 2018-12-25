#ifndef SYSAPI_H
#define SYSAPI_H

#include <QtCore>

void sysInfo( const QString &str );
void sysInfo(const QString &info, const QString &str2 );
void sysInfo( const QString &info, const int &val );

void sysWarning( const QString &str );

void sysError( const QString &str );
void sysError( const QString &info , const int &val);

bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);

QString readFile(QString fileName);

int writeFile(QString fileName, QString text);

#endif // SYSAPI_H
