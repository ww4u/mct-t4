#include "joint.h"
#include "ui_joint.h"

Joint::Joint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Joint)
{
    ui->setupUi(this);

    //! delta
    ui->label_2->setText( QChar(0x2206) );
}

Joint::~Joint()
{
    delete ui;
}
