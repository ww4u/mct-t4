#ifndef MEGAINTERFACE_H
#define MEGAINTERFACE_H

#include <QMenu>
#include <QStandardItemModel>
#include <QWidget>
#include <QThread>
#include <QMetaType>

namespace Ui {
class MegaInterface;
}

enum _DEV_TYPES
{
    TYPE_LAN = 0,
    TYPE_USB = 1
};

class DeviceSearchThread: public QThread
{
    Q_OBJECT
signals:
    void resultReady(const QString &s);

public:
    void run();
    void setType(int type);

private:
    int m_type;
};


class MegaInterface : public QWidget
{
    Q_OBJECT

public:
    explicit MegaInterface(QWidget *parent = 0);
    ~MegaInterface();

    int visa() const;

signals:
    void getDeviceIP(const QString &strIP);

private slots:
    void slotChangeDeviceType(int index);
    void slotScanDevices();
    void slotScanFinished();
    void insertOneRow(QString str);
    void slotShowContextmenu(const QPoint &pos);
    void soltActionOpen();
    void soltActionClose();

    void on_pushButton_ok_clicked();

private:
    Ui::MegaInterface *ui;
    QStandardItemModel* m_model;
    QList<QStandardItem *> m_itemList;
    QMenu *m_menu;

    int m_devType;
    DeviceSearchThread *m_searchThread;
    void clearListView();
    int deviceOpen();
};


#endif // MEGAINTERFACE_H
