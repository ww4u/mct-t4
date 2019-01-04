#include "diagnosisitem.h"
#include "mystd.h"

const static char *_headers[] =
{
    QT_TRANSLATE_NOOP("HEADER", "No."),
    QT_TRANSLATE_NOOP("HEADER", "Type"),
    QT_TRANSLATE_NOOP("HEADER", "Timestamp"),
    QT_TRANSLATE_NOOP("HEADER", "Additional Info"),
    QT_TRANSLATE_NOOP("HEADER", "Counter"),
    QT_TRANSLATE_NOOP("HEADER", "Message"),
};

int DiagnosisItem::columns()
{
    return sizeof_array( _headers );
}
QString DiagnosisItem::header( int col )
{
    Q_ASSERT( col >= 0 && col <= sizeof_array(_headers) );

    return qApp->translate("HEADER", _headers[col]);
}

DiagnosisItem::DiagnosisItem()
{
    mNr = 0;
    mCounter = 0;
}
