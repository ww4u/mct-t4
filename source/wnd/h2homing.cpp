#include "h2homing.h"
#include "ui_h2homing.h"

H2Homing::H2Homing(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Homing),
    m_strDirXtoY(tr("First in direction of X,then Y")),
    m_strDirYtoX(tr("First in direction of Y,then X"))
{
    ui->setupUi(this);


    setName( "homing" );

    ui->comboBox_target->addItem("Block");

    ui->comboBox_movement->addItem(m_strDirXtoY);
//    ui->comboBox_movement->addItem(m_strDirYtoX);

//    connect(ui->comboBox_movement,SIGNAL(currentTextChanged(QString)),this,SLOT(slotChangePicture(QString)));

    ui->label_picture->setPixmap(QPixmap(":/res/image/h2homing/dir_X_Y.PNG"));

}

H2Homing::~H2Homing()
{
    delete ui;
}

int H2Homing::setApply(ViSession vi)
{
    qDebug() << "H2Homing:" << vi;
    return 0;
}


//void H2Homing::slotChangePicture(QString str)
//{
//    if(str == m_strDirXtoY)
//        ui->label_picture->setPixmap(QPixmap(":/res/image/h2homing/dir_X_Y.PNG"));
//    else if(str == m_strDirYtoX)
//        ui->label_picture->setPixmap(QPixmap(":/res/image/h2homing/dir_Y_X.PNG"));
//}


