#include "h2measurement.h"
#include "ui_h2measurement.h"

H2Measurement::H2Measurement(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Measurement)
{
    ui->setupUi(this);
    connect(ui->comboBox_AxesZeroPoint,SIGNAL(currentIndexChanged(int)),this,SLOT(slotChangeCornerPicture(int)));

    connect(ui->comboBox_AxesZeroPoint,SIGNAL(currentIndexChanged(int)),this,SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_pzpX, SIGNAL(valueChanged(double)), this, SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_pzpY, SIGNAL(valueChanged(double)), this, SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_swlp_X, SIGNAL(valueChanged(double)), this, SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_swlp_Y, SIGNAL(valueChanged(double)), this, SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_swln_X, SIGNAL(valueChanged(double)), this, SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_swln_Y, SIGNAL(valueChanged(double)), this, SLOT(slotOnModelChanged()));

}

H2Measurement::~H2Measurement()
{
    delete ui;
}

int H2Measurement::setApply()
{
    int ret = -1;
    qDebug() << "H2Measurement:" << mViHandle << mRobotName;

#if 0
    //ZeroPoint=[0,1,2,3]
    char value = ui->comboBox_AxesZeroPoint->currentIndex();
    ret = mrhtRobotProjectzero(mViHandle, mRobotName, &value);

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

void H2Measurement::slotOnModelChanged()
{
    m_ZeroPoint = ui->comboBox_AxesZeroPoint->currentIndex();
    m_ProjectZeroPointX = ui->doubleSpinBox_pzpX->value();
    m_ProjectZeroPointY = ui->doubleSpinBox_pzpY->value();
    m_SWLimitPositiveX  = ui->doubleSpinBox_swlp_X->value();
    m_SWLimitPositiveY  = ui->doubleSpinBox_swlp_Y->value();
    m_SWLimitNegativeX  = ui->doubleSpinBox_swln_X->value();
    m_SWLimitNegativeY  = ui->doubleSpinBox_swln_Y->value();

//    qDebug() << "m_ZeroPoint        " << m_ZeroPoint         ;
//    qDebug() << "m_ProjectZeroPointX" << m_ProjectZeroPointX ;
//    qDebug() << "m_ProjectZeroPointY" << m_ProjectZeroPointY ;
//    qDebug() << "m_SWLimitPositiveX " << m_SWLimitPositiveX  ;
//    qDebug() << "m_SWLimitPositiveY " << m_SWLimitPositiveY  ;
//    qDebug() << "m_SWLimitNegativeX " << m_SWLimitNegativeX  ;
//    qDebug() << "m_SWLimitNegativeY " << m_SWLimitNegativeY  ;
}

