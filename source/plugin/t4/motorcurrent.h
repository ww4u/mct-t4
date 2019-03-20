#ifndef MOTORCURRENT_H
#define MOTORCURRENT_H

#include <QtWidgets>

namespace Ui {
class MotorCurrent;
}

class MotorCurrent : public QWidget
{
    Q_OBJECT

public:
    explicit MotorCurrent(QWidget *parent = 0);
    ~MotorCurrent();

    void setData( double dC, double iC, double sT );
    void getData( double &dC, double &iC, double &sT );

    QDoubleSpinBox *doubleSpinCurrent();
    QDoubleSpinBox *doubleSpinIdleCurrent();
    QDoubleSpinBox *doubleSpinSwitchTime();

private:
    Ui::MotorCurrent *ui;
};

#endif // MOTORCURRENT_H
