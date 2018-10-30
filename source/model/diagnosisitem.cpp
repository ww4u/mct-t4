#include "diagnosisitem.h"
#include "mystd.h"

static QString _headers[]=
{
    QStringLiteral("No."),
    QStringLiteral("Type"),
    QStringLiteral("Timestamp"),
    QStringLiteral("Additional Info"),
    QStringLiteral("Counter"),
    QStringLiteral("Message"),
};

int DiagnosisItem::columns()
{
    return sizeof_array( _headers );
}
QString DiagnosisItem::header( int col )
{
    Q_ASSERT( col >= 0 && col <= sizeof_array(_headers) );

    return _headers[ col ];
}

DiagnosisItem::DiagnosisItem()
{
    mNr = 0;
    mCounter = 0;
}
