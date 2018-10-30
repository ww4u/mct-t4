#include "debugitem.h"


#include "mystd.h"

static QString _headers[]=
{
    QStringLiteral("No."),
    QStringLiteral("Delay(s)"),
};

int DebugItem::columns()
{
    return sizeof_array( _headers );
}
QString DebugItem::header( int col )
{
    Q_ASSERT( col >= 0 && col <= sizeof_array(_headers) );

    return _headers[ col ];
}

DebugItem::DebugItem()
{
    mId = 0;
    mDelay = 1.0;
}
