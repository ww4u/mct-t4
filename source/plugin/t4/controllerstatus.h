#ifndef CONTROLLERSTATUS_H
#define CONTROLLERSTATUS_H

#include <QWidget>
#include "../../plugin/xpage.h"

namespace Ui {
class ControllerStatus;
}

class ControllerStatus : public XPage
{
    Q_OBJECT

public:
    explicit ControllerStatus(QWidget *parent = 0);
    ~ControllerStatus();

public:
    virtual void spyEdited();

public:
    void setMctChecked( bool b );
    bool isMctChecked();

    void setDevicePower( bool b );
    bool getDevicePower();

    void setDevicePowerEnable( bool b );
    bool isDevicePowerEnable();

private:
    Ui::ControllerStatus *ui;

Q_SIGNALS:
    void signal_mct_checked( bool b );
    bool signal_device_power( bool b );
    void signal_ack_error();
};

#endif // CONTROLLERSTATUS_H
