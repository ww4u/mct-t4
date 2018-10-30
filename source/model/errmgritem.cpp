#include "errmgritem.h"
#include "mystd.h"

static QString _headers[]=
{
    QStringLiteral("No."),
    QStringLiteral("Error Text"),
    QStringLiteral("Error"),
    QStringLiteral("Warning"),
    QStringLiteral("Information"),
    QStringLiteral("Recation on error"),
    QStringLiteral("Output stage on"),
    QStringLiteral("Save diagnosis"),
};

int ErrMgrItem::columns()
{
    return sizeof_array( _headers );
}
QString ErrMgrItem::header( int col )
{
    Q_ASSERT( col >= 0 && col <= sizeof_array(_headers) );

    return _headers[ col ];
}

ErrMgrItem::ErrMgrItem()
{
    mNr = 0;

    mEventType = e_error;
    mEventAttr = 0;

    mAction = e_action_freewheel;
    mActionAttr = 0;

    mbOutput = false;
    mbOutputAble = false;

    mbSaveDiagnosis = false;
}
