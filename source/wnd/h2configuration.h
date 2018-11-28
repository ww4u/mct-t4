#ifndef FORMTEST_H
#define FORMTEST_H

#include <QWidget>
#include "xconfig.h"
namespace Ui {
class H2Configuration;
}

class H2Configuration : public XConfig
{
    Q_OBJECT

public:
    explicit H2Configuration(QWidget *parent = nullptr);
    ~H2Configuration();

    int readDeviceConfig(); //从设备上读取配置数据
    int writeDeviceConfig();//将软件界面的数据配置设置到设备
    int loadConfig();       //读取本地配置文件 启动软件或者添加新设备时调用
    int saveConfig();       //将软件界面的数据配置写入到本地配置文件
    void updateShow();      //更新界面

    void translateUI() override;

private slots:
    void on_radioButton_b_toggled(bool checked);

    void on_radioButton_t_toggled(bool checked);

    void on_spinBox_X_valueChanged(int arg1);

    void on_spinBox_Y_valueChanged(int arg1);

    void on_sizeComboBox_currentIndexChanged(int index);

private:
    Ui::H2Configuration *ui;

    QString m_Family;
    int     m_Size;
    int     m_WorkStrokeX;
    int     m_WorkStrokeY;
    int     m_MotorPosition;

    void changeModelLabel();
};

#endif // FORMTEST_H
