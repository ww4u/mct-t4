#ifndef MEGATABLEMODEL_H
#define MEGATABLEMODEL_H

#include <QAbstractTableModel>
#include <QAbstractItemView>

class MegaTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MegaTableModel( QObject *parent=Q_NULLPTR );
    virtual ~MegaTableModel()
    {}

    QString fmtString( const QStringList &list );

Q_SIGNALS:
    void signal_data_changed();

};

#endif // MEGATABLEMODEL_H
