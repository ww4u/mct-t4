#ifndef SYSLOGOUT_H
#define SYSLOGOUT_H

#include <QWidget>
#include <QAbstractListModel>

namespace Ui {
class SysLogout;
}

class SysLogout : public QWidget
{
    Q_OBJECT

public:
    explicit SysLogout(QWidget *parent = 0);
    ~SysLogout();

    void attachLogModel( QAbstractListModel *pModel );

private:
    Ui::SysLogout *ui;
};

#endif // SYSLOGOUT_H
