#ifndef XCONFIG_H
#define XCONFIG_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

#include "../include/mystd.h"
#include "MegaGateway.h"
#include "megaxml.h"

class XConfig : public QWidget
{
    Q_OBJECT
public:
    explicit XConfig(QWidget *parent = nullptr);

public:
    void setName( const QString &name );
    QString name();

    void setProjectName(const QString &projectName);
    int attachHandle(int handle, int deviceName, int robotName);
    int detachHandle();

    virtual int  readDeviceConfig();    //从设备上读取数据设置到类成员
    virtual int  writeDeviceConfig();   //将类成员数据设置到设备
    virtual int  loadConfig();          //读取本地配置文件，将数据保存到类成员 启动软件或者添加新设备时调用 如果没用对应的配置就用默认的配置
    virtual int  saveConfig();          //将类成员写入到本地配置文件
    virtual void updateShow();          //将类成员更新到界面

protected:
    virtual void focusInEvent(QFocusEvent *event);

signals:
    void signal_focus_in( const QString &name );

protected:
    QString mName;
    int mViHandle;
    int mRobotName;
    int mDeviceName;

    QString mProjectName;
};

#endif // XCONFIG_H
