#ifndef ERRMGRMODEL_H
#define ERRMGRMODEL_H

#include "megatablemodel.h"
#include "errmgritem.h"

class ErrMgrModel : public MegaTableModel
{
public:
    ErrMgrModel();
    ~ErrMgrModel();

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
    QList< ErrMgrItem *> *items();

    int save( const QString &fileName );
    int load( const QString &fileName );

    int serialOut( QXmlStreamWriter & writer );
    int serialIn( QXmlStreamReader & reader );

    void createDebug();
public:
    QList< ErrMgrItem *> mItems;
};

#endif // ERRMGRMODEL_H
