#ifndef CONTROLLERSTATUS_H
#define CONTROLLERSTATUS_H

#include <QWidget>

namespace Ui {
class ControllerStatus;
}

class ControllerStatus : public QWidget
{
    Q_OBJECT

public:
    explicit ControllerStatus(QWidget *parent = 0);
    ~ControllerStatus();

private:
    Ui::ControllerStatus *ui;
};

#endif // CONTROLLERSTATUS_H
