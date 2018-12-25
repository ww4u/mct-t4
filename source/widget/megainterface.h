#ifndef MEGAINTERFACE_H
#define MEGAINTERFACE_H

#include <QMenu>
#include <QStandardItemModel>
#include <QWidget>
#include <QMetaType>
#include <QAbstractItemView>
#include <QTableWidget>
#include <QAbstractButton>

namespace Ui {
class MegaInterface;
}

enum _DEV_TYPES
{
    TYPE_LAN = 0,
    TYPE_USB = 1
};


class MegaInterface : public QWidget
{
    Q_OBJECT

public:
    explicit MegaInterface(QWidget *parent = 0);
    ~MegaInterface();

signals:
    void signalSelectedInfo(const QString &strDevInfo);

private slots:
    void slotChangeDeviceType(int index);
    void slotDeviceScan();
    void slotDeviceScanEnd();
    void slotShowSearchResult(QString strDevices);
    void slotShowContextmenu(const QPoint &pos);
    void soltActionOpen();
    void soltActionClose();

    void slotSelectDevices();
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::MegaInterface *ui;
    QStandardItemModel* m_model;
    QList<QStandardItem *> m_itemList;

    QMenu *m_menu;

    int m_devType;
    void clearListView();
    int deviceOpen();
};


#endif // MEGAINTERFACE_H
