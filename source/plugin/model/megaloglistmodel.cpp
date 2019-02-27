#include "megaloglistmodel.h"
#include <QIcon>
#include "../../../include/mystd.h"
MegaLogListModel::MegaLogListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mMaxCount = 1024;
}
MegaLogListModel::~MegaLogListModel()
{
    clear();
}

int MegaLogListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return mItemList.size();
}

QVariant MegaLogListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole )
    { return QVariant( mItemList.at(index.row())->mStr ); }

    else if ( role == Qt::DecorationRole )
    {
        LogStr::eLogLevel lev = mItemList.at(index.row())->mLevel;

        if ( lev == LogStr::log_info )
        { return QVariant( QIcon(":/res/image/icon/xiaoxi.png") ); }
        else if ( lev == LogStr::log_warning )
        { return QVariant( QIcon(":/res/image/icon/gantanhaozhong.png") ); }
        else if ( lev == LogStr::log_error )
        { return QVariant( QIcon(":/res/image/icon/shibai2.png") ); }
        else
        { return QVariant( QIcon(":/res/image/icon/xiaoxi.png") ); }
    }
    else
    { return QVariant(); }
}

void MegaLogListModel::append( const QString &content,
                               LogStr::eLogLevel logLev )
{
//    beginInsertRows(  createIndex( mItemList.size(), 0),
//                      mItemList.size() - 1, mItemList.size()
//                      );

//    beginResetModel();

    LogStr *pItem = new LogStr();
    if ( NULL == pItem )
    { return; }

    pItem->mLevel = logLev;
    pItem->mStr = content;

    //! overlap
    if ( mItemList.size() >= mMaxCount )
    { removeRow( 0 ); }

    beginInsertRows(QModelIndex(), mItemList.size(), mItemList.size()+1 );

    mItemList.append( pItem );

    endInsertRows();
}
void MegaLogListModel::clear()
{
    beginResetModel();

    delete_all( mItemList );

    endResetModel();
}
