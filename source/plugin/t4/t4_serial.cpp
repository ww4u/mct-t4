#include <QDir>
#include "t4.h"


#define cfg_file_path  QDir::homePath() + "/mct"
#define cfg_file_name  cfg_file_path + "/sn.xml"

int MRX_T4::serialOut(QXmlStreamWriter &writer)
{
    return T4Para::serialOut( writer );
}
int MRX_T4::serialIn(QXmlStreamReader &reader)
{
    return T4Para::serialIn( reader );
}

void MRX_T4::slot_save_setting()
{
    int ret;

    QString path = homePath();

    //! create path
    ret = assurePath( path );
    if ( ret != 0 )
    { return; }

    //! save file
    QString setupfileName = path + "/" + "config.xml";
    ret = save( setupfileName );
    if ( ret != 0 )
    {
        sysError( tr("Config save fail") );
    }

    logDbg()<<setupfileName;
}

void MRX_T4::slot_load_setting()
{
    int ret;

    QString path = homePath();

    //! save file
    QString setupfileName = path + "/" + "config.xml";
    ret = load( setupfileName );
    if ( ret != 0 )
    {
        sysError( tr("Config load fail") );
    }

    XPlugin::slot_load_setting();
    logDbg()<<setupfileName;
}
