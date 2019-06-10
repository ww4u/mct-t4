#ifndef SYSAPI_H
#define SYSAPI_H

#include <QtCore>

class sysPara
{
public:
//    enum eSysMode
//    {
//        e_sys_user,
//        e_sys_admin,
//    };
public:
//    eSysMode mMode;

    int mArgc;
    char **mArgv;
};

enum eOutHandle
{
    e_out_console,
    e_out_log
};

//void setSysMode( sysPara::eSysMode mode );
//sysPara::eSysMode sysMode();

void sysSetArg( int argc, char **argv );
int sysArgc();
char** sysArgv( const QString &arg );

bool sysHasArgv( const QString &arg );

void sysInfo( const QString &str, eOutHandle oHandle = e_out_console );
void sysInfo(const QString &info, const QString &str2, eOutHandle oHandle = e_out_console );
void sysInfo( const QString &info, const int &val, eOutHandle oHandle = e_out_console );

void sysWarning( const QString &str , eOutHandle oHandle = e_out_console);

void sysError( const QString &str, eOutHandle oHandle = e_out_console );
void sysError( const QString &info , const int &val, eOutHandle oHandle = e_out_console );

void sysProgress( const QString &info, bool b, int now = 0, int mi=0, int ma=100 );

void sysPrompt( const QString &info, int lev=2 );

void sysShowStatus(const QString &statusInfo);

bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);

QString readFile(QString fileName);

int writeFile(QString fileName, QString text);

int assurePath( const QString &path );

#endif // SYSAPI_H
