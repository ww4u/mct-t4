#ifndef MEGAINTERFACE_H
#define MEGAINTERFACE_H

#include <QMenu>
#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class MegaInterface;
}


class MegaInterface : public QWidget
{
    Q_OBJECT

public:
    enum _DEV_TYPES
    {
        TYPE_LAN = 0,
        TYPE_USB = 1
    };

public:
    explicit MegaInterface(QWidget *parent = 0);
    ~MegaInterface();

    void insertOneRow(QString str);

protected slots:
    void slotChangeDeviceType(int index);
    void slotScanDevices();

    void slotShowContextmenu(const QPoint &pos);    
    void soltActionOpen();
    void soltActionClose();

private:
    Ui::MegaInterface *ui;
    QStandardItemModel* m_model;

    QList<QStandardItem *> m_itemList;
    QMenu *m_menu;

    int m_devType;
    void clearListView();
};

#endif // MEGAINTERFACE_H
