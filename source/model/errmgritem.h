#ifndef ERRMGRITEM_H
#define ERRMGRITEM_H

#include <QtCore>

enum e_event_type
{
    e_error,
    e_warning,
    e_info
};


enum e_event_action
{
    e_action_freewheel,
    e_action_qs,
    e_action_record_dec,
    e_action_finish,
};

//! bits
enum eColumnAttr
{
    column_unk = 0,
    column_editable = 0,
    column_empty = 1,
};

class ErrMgrItem
{
public:
    static int columns();
    static QString header( int col );

public:
    ErrMgrItem();

public:
    eColumnAttr columnAttr( int col );

    void setEventType( e_event_type evt, bool b );

public:
    int mNr;
    QString mErr;

    e_event_type mEventType;
    int mEventAttr;         //! 1 2 4

    QString mAction;
    int mActionAttr;

    bool mbOutput, mbOutputAble;
    bool mbSaveDiagnosis;
};

#endif // ERRMGRITEM_H
