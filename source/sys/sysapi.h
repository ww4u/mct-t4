#ifndef SYSAPI_H
#define SYSAPI_H

#include <QtCore>

class sysPara
{
public:
    enum eSysMode
    {
        e_sys_user,
        e_sys_admin,
    };
public:
    eSysMode mMode;
};

void setSysMode( sysPara::eSysMode mode );
sysPara::eSysMode sysMode();

void sysInfo( const QString &str );
void sysInfo(const QString &info, const QString &str2 );
void sysInfo( const QString &info, const int &val );

void sysWarning( const QString &str );

void sysError( const QString &str );
void sysError( const QString &info , const int &val);

void sysProgress( const QString &info, bool b, int now = 0, int mi=0, int ma=100 );

void sysShowStatus(const QString &statusInfo);

bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);

QString readFile(QString fileName);

int writeFile(QString fileName, QString text);

int assurePath( const QString &path );

#endif // SYSAPI_H
