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

    void change_online_status(bool bl);

    int readDeviceConfig(); //从设备上读取配置数据
    int writeDeviceConfig();//将软件界面的数据配置设置到设备
    int loadConfig();       //读取本地配置文件 启动软件或者添加新设备时调用
    int saveConfig();       //将软件界面的数据配置写入到本地配置文件
    void updateShow();      //更新界面

    void translateUI() override;

signals:
    void signal_online_clicked(QString);

private slots:
    void on_toolButton_status_clicked();

private:
    Ui::H2Product *ui;

    QString m_IP;
    QString m_Version;
    QString m_Type;
    QString m_SN;
};

#endif // H2PRODUCT_H
