#include "h2actionitem.h"
#include "mystd.h"

static QString _headers[]=
{
    QStringLiteral("Type"),
    QStringLiteral("Target X"),
    QStringLiteral("Target Y"),
    QStringLiteral("Velocity"),
    QStringLiteral("Acceleration"),
    QStringLiteral("Comment"),
};

int H2ActionItem::columns()
{
    return sizeof_array( _headers );
}
QString H2ActionItem::header( int col )
{
    Q_ASSERT( col >= 0 && col <= sizeof_array(_headers) );

    return _headers[ col ];
}

H2ActionItem::H2ActionItem()
{
    mType = "PA";
    mX = 0;
    mY = 0;

    mAcc = 1;
    mVel = 1;
}

