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

class ErrMgrItem
{
public:
    static int columns();
    static QString header( int col );

public:
    ErrMgrItem();

public:
    int mNr;
    QString mErr;
    e_event_type mEventType;
    int mEventAttr;     //! 1 2 4

    e_event_action mAction;
    int mActionAttr;

    bool mbOutput, mbOutputAble;
    bool mbSaveDiagnosis;
};

#endif // ERRMGRITEM_H
