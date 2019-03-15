#ifndef DSPINDELEGATE_H
#define DSPINDELEGATE_H
#include <QStyledItemDelegate>
#include <QtWidgets>

class dSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    dSpinDelegate(QObject *parent = 0);
    dSpinDelegate(double mi, double ma, QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const override;

public:
    void setMax( double v );
    void setMin( double v );
    void setDecimal( int d );

protected:
    int mDecimal;
    double mMax, mMin;
};

#endif // DSPINDELEGATE_H
