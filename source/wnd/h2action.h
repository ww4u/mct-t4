#ifndef H2ACTION_H
#define H2ACTION_H

#include <QWidget>
#include <QAbstractTableModel>
#include "xconfig.h"

#include "../model/comboxdelegate.h"
#include "../model/h2actionmodel.h"

namespace Ui {
class H2Action;
}

class H2Action : public XConfig
{
    Q_OBJECT

public:
    explicit H2Action( QWidget *parent = 0);
    ~H2Action();

    int readDeviceConfig(); //从设备上读取配置数据
    int writeDeviceConfig();//将软件界面的数据配置设置到设备
    int loadConfig();       //读取本地配置文件 启动软件或者添加新设备时调用
    int saveConfig();       //将软件界面的数据配置写入到本地配置文件
    void updateShow();      //更新界面

private slots:
    void slotModelChanged(QModelIndex index1, QModelIndex index2, QVector<int> vector);

private:
    Ui::H2Action *ui;
    H2ActionModel   m_actionModel;
    comboxDelegate *m_pDelegate;

    QString m_strLocalFileName;
    QString m_strDeviceFileName;

    QString m_fileContext;

    QString readFile(QString fileName);
    int writeFile(QString fileName, QString text);
};

#endif // H2ACTION_H
