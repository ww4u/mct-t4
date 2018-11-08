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
//    qDebug() << "H2Homing:" << mViHandle;
    return 0;
}


