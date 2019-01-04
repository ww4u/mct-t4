#include "debugitem.h"


#include "mystd.h"

const static char *_headers[] =
{
    QT_TRANSLATE_NOOP("HEADER", "No."),
    QT_TRANSLATE_NOOP("HEADER", "Delay(s)"),
};

int DebugItem::columns()
{
    return sizeof_array( _headers );
}
QString DebugItem::header( int col )
{
    Q_ASSERT( col >= 0 && col <= sizeof_array(_headers) );

    return qApp->translate("HEADER", _headers[col]);
}

DebugItem::DebugItem()
{
    mId = 0;
    mDelay = 1.0;
}
