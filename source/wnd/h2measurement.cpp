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

int H2Measurement::setApply(ViSession vi)
{
    qDebug() << "H2Measurement:" << vi;
    return 0;
}

void H2Measurement::slotChangeCornerPicture(int index)
{
    QString strPixmap = ":/res/image/h2measurement/CornerPoint";
    strPixmap += QString::number(index+1);
    strPixmap += ".PNG";

    ui->label_picture->setPixmap(QPixmap(strPixmap));
}
