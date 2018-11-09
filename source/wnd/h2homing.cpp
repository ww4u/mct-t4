#include "h2homing.h"
#include "ui_h2homing.h"

H2Homing::H2Homing(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Homing),
    m_strDirXtoY(tr("First in direction of X,then Y"))
{
    ui->setupUi(this);

    setName( "homing" );

    ui->comboBox_target->addItem("Block");

    ui->comboBox_movement->addItem(m_strDirXtoY);

}

H2Homing::~H2Homing()
{
    delete ui;
}

int H2Homing::setApply()
{
//    qDebug() << "H2Homing:" << mViHandle << mRobotName.toInt();
#if 0
    //SearchVelocity=50.00


    //Acceleration=5.000


    //ForceLimit=75.0

#endif
    return 0;
}

void H2Homing::slot_set_direction(QString text)
{
    ui->label_direction->setText(text);
}


