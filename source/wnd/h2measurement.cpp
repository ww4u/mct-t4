#include "h2measurement.h"
#include "ui_h2measurement.h"

H2Measurement::H2Measurement(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Measurement)
{
    ui->setupUi(this);
    connect(ui->comboBox_AxesZeroPoint,SIGNAL(currentIndexChanged(int)),this,SLOT(slotChangeCornerPicture(int)));
}

H2Measurement::~H2Measurement()
{
    delete ui;
}

int H2Measurement::setApply()
{
    int ret = -1;
    qDebug() << "H2Measurement:" << mViHandle << mRobotName.toInt();

#if 0
    //ZeroPoint=[0,1,2,3]
    char value = ui->comboBox_AxesZeroPoint->currentIndex();
    ret = mrhtRobotProjectzero(mViHandle, mRobotName.toInt(), &value);

    //ProjectZeroPointX=0.00


    //ProjectZeroPointY=0.00


    //SWLimitPositiveX=0.00


    //SWLimitPositiveY=0.00


    //SWLimitNegativeX=0.00


    //SWLimitNegativeY=0.00


#endif
    return 0;
}

void H2Measurement::slotChangeCornerPicture(int index)
{
    QString strPixmap = ":/res/image/h2measurement/CornerPoint";
    strPixmap += QString::number(index+1);
    strPixmap += ".PNG";

    ui->label_picture->setPixmap(QPixmap(strPixmap));
    emit signal_AxesZeroPoint_currentTextChanged(ui->comboBox_AxesZeroPoint->currentText());
}

