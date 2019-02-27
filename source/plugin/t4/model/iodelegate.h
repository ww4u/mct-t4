#ifndef IODELEGATE_H
#define IODELEGATE_H

#include <QStyledItemDelegate>

class IODelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    static QString toString( quint32 _do, int w=4 );

public:
    IODelegate(int w, QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    int mWidth;
};

#endif // IODELEGATE_H
