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
    static QString encode( bool b );
    static bool decode( const QString &str );

public:
    ErrorMgrItem();

public:
    void setOutput( bool b );
    bool getOutput();
    bool isOutputAble();

    void setLed( bool b );
    bool getLed();
    bool isLedAble();

public:
    QString mCodeKey; QString mCode;
    QString mTypeKey; QString mType;

    QStringList mBriefKey;
    QStringList mBrief;

    QStringList mReasonKey;
    QStringList mReason;

    QStringList mDetailKey;
    QStringList mDetail;

    QString mActionKey;
    QString mAction;

    QString mOutputKey;
    QString mOutput;

    QString mLedKey;
    QString mLed;
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

//    virtual bool insertRows(int position, int rows, const QModelIndex &parent);
//    virtual bool removeRows(int position, int rows, const QModelIndex &parent);

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

protected:
//    QVariant userRole_Visible( const QModelIndex &index ) const;
//    QVariant backRole( const QModelIndex &index ) const;

public:
    QList< ErrorMgrItem *> *items();

//    int save( const QString &fileName );
    int load( const QString &fileName );
    int load( QByteArray &ary );

//    int serialOut( QXmlStreamWriter & writer );
//    int serialIn( QXmlStreamReader & reader );

    int serialOut( QTextStream & writer );
    int serialIn( QTextStream & reader );

//    void createDebug();

public:
    QList< ErrorMgrItem *> mItems;
};

#endif // ERRMGRMODEL_H
