#ifndef H2PRODUCT_H
#define H2PRODUCT_H

#include <QWidget>
#include "xconfig.h"

namespace Ui {
class H2Product;
}

class H2Product : public XConfig
{
    Q_OBJECT

public:
    explicit H2Product(QString strDevInfo = "", QWidget *parent = 0);
    ~H2Product();
    int setApply(ViSession visa);
signals:
    void signal_device_open(int visa);
    void signal_device_close();

private slots:
    void on_toolButton_status_clicked();

private:
    Ui::H2Product *ui;
    bool m_online;
    int m_visa;

    QString m_IP;
    QString m_Version;
    QString m_Type;
    QString m_SN;

    int deviceOpen();
    int deviceClose();

};

#endif // H2PRODUCT_H
