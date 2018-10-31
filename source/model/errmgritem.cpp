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

eColumnAttr ErrMgrItem::columnAttr( int col )
{
    return column_unk;
}

void ErrMgrItem::setEventType( e_event_type evt, bool b )
{
    //! \todo according the event attr
    if ( evt == e_error )
    {
        if ( b )
        { mEventType = e_error; }
        else
        { mEventType = e_warning; }
    }
    else if ( evt == e_warning )
    {
        if ( b )
        { mEventType = e_warning; }
        else
        { mEventType = e_info; }
    }
    else if ( evt == e_info )
    {
        if ( b )
        { mEventType = e_info; }
        else
        { mEventType = e_error; }
    }
    else
    { Q_ASSERT(false); }
}
