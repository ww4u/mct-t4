#include <QDir>
#include "t4.h"

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

    QString path = selfPath();

    //! save file
    QString setupfileName = path + "/" + config_file_name;
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

    QString path = selfPath();

    //! save file
    QString setupfileName = path + "/" + config_file_name;
    ret = load( setupfileName );
    if ( ret != 0 )
    {
        sysError( tr("Config load fail") );
    }

    XPlugin::slot_load_setting();
    logDbg()<<setupfileName;
}
