#ifndef ERRMGRMODEL_H
#define ERRMGRMODEL_H

#include <QXmlStreamWriter>
#include "model.h"

#define ACTION_FREEWHEEL    "Free-wheeling"
#define ACTION_QSDEC        "QS deceleration"
#define ACTION_RECDEC       "Record deceleration"
#define ACTION_FINISH       "Finish Record"

class ErrorMgrItem
{
public:
    enum e_event_type
    {
        e_error = 1,
        e_warning,
        e_info
    };

    //! bits
    enum eColumnAttr
    {
        column_unk = 0,
        column_editable = 0,
        column_empty = 1,
    };
public:
    ErrorMgrItem();

public:
    void setEventType( e_event_type evt, bool b );
    e_event_type eventType();

    void snap( int &code, int &type, int &action, int &output, int &save );
public:
    bool mbErrorAble, mbWarnAble, mbInfoAble;
    bool mbOutputAble;
    bool mbSaveAble;
    bool mbActionAble;

    int mNr;
    QString mErr;
    e_event_type mEventType;
    QString mAction;
    QStringList mActionList;
    bool mbOutput;
    bool mbSaveDiagnosis;
};

class ErrorMgrModel : public MegaTableModel
{
public:
    ErrorMgrModel();
    ~ErrorMgrModel();

public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;

    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual bool insertRows(int position, int rows, const QModelIndex &parent);
    virtual bool removeRows(int position, int rows, const QModelIndex &parent);

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

protected:
    QVariant userRole_Visible( const QModelIndex &index ) const;
    QVariant backRole( const QModelIndex &index ) const;

public:
    QList< ErrorMgrItem *> *items();

    int save( const QString &fileName );
    int load( const QString &fileName );
    int load( QByteArray &ary );

    int serialOut( QXmlStreamWriter & writer );
    int serialIn( QXmlStreamReader & reader );

    void createDebug();

public:
    QList< ErrorMgrItem *> mItems;
};

#endif // ERRMGRMODEL_H