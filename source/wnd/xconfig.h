#ifndef XCONFIG_H
#define XCONFIG_H

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTranslator>

#include "mystd.h"
#include "sysapi.h"
#include "megaxml.h"
#include "MegaGateway.h"
#include "xthread.h"

class XConfig : public QWidget
{
    Q_OBJECT
public:
    explicit XConfig(QWidget *parent = nullptr);

public:
    QString focuHelpName() const;
    void setFocuHelpName(const QString &focuHelpName);

    void setConfigFileName(const QString &projectName);

    int attachHandle(int vihandle, int deviceName, int robotName);
    int detachHandle();

    virtual int  readDeviceConfig();    //从设备上读取数据设置到类成员
    virtual int  writeDeviceConfig();   //将类成员数据设置到设备
    virtual int  loadConfig();          //读取本地配置文件，将数据保存到类成员 启动软件或者添加新设备时调用 如果没用对应的配置就用默认的配置
    virtual int  saveConfig();          //将类成员写入到本地配置文件

public slots:
    virtual void updateShow();          //将类成员更新到界面

    virtual void changeLanguage(QString qmFile);
    virtual void translateUI();

protected:
    virtual void focusInEvent(QFocusEvent *event);

signals:
    void signal_focus_in( const QString &name );
    void signalModelDataChanged(const bool &bl);

protected:
    QString mFocuHelpName;

    QString mConfigFileName;

    int mViHandle;
    int mDeviceName;
    int mRobotName;

    QTranslator m_translator;

};

#endif // XCONFIG_H
