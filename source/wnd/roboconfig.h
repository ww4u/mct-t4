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

public:
    int open();
    int close();

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

private:
    Ui::RoboConfig *ui;

    QTreeWidgetItem *m_pRootNode;

    QList<XRobo*> mRobos;
};

#endif // H2CONFIG_H
