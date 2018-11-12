#ifndef ROBO_CONFIG_H
#define ROBO_CONFIG_H

#include <QtWidgets>


namespace Ui {
class RoboConfig;
}

#include "xrobo.h"

class RoboConfig : public QWidget
{
    Q_OBJECT

public:
    explicit RoboConfig(QWidget *parent = 0);
    ~RoboConfig();

signals:
    void signalCurrentRobotChanged(int,int);

public slots:
    void slotAddNewRobot(QString strDevInfo );

protected:
    int setApply();
    int setReset();
    int setOK();

Q_SIGNALS:
    void signal_focus_in( const QString &);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void slot_current_changed( QTreeWidgetItem* pre,QTreeWidgetItem* nxt );
    void slot_open_close(QString strIP);

private:
    Ui::RoboConfig *ui;

    QTreeWidgetItem *m_pRootNode;
    QList<XRobo*> mRobos;
    QList<int> mVisas;
    QList<int> mRoboNames;
    int mIndex;

    int deviceOpen(QString strIP);
    int deviceClose();
    QStringList m_strListDevInfo;
};

#endif // H2CONFIG_H
