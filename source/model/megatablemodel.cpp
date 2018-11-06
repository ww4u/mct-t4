#include "megatablemodel.h"

MegaTableModel::MegaTableModel( QObject *parent  ) : QAbstractTableModel( parent )
{
    connect( this, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
             this, SIGNAL(signal_data_changed()));

    connect( this, SIGNAL(rowsInserted(QModelIndex,int,int)),
             this, SIGNAL(signal_data_changed()));

    connect( this, SIGNAL(rowsRemoved(QModelIndex,int,int)),
             this, SIGNAL(signal_data_changed()));

    connect( this, SIGNAL(modelReset()),
             this, SIGNAL(signal_data_changed()));
}

QString MegaTableModel::fmtString( const QStringList &list )
{
    QStringList strList;
    for ( int i = 1; i <= list.size(); i++ )
    {
        strList<<QString("\%%1").arg( i );
    }

    return strList.join('/');
}

