#ifndef JOINT_H
#define JOINT_H

#include <QWidget>

namespace Ui {
class Joint;
}

class Joint : public QWidget
{
    Q_OBJECT

public:
    explicit Joint(QWidget *parent = 0);
    ~Joint();

private:
    Ui::Joint *ui;
};

#endif // JOINT_H
