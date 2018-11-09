#include "h2configuration.h"
#include "ui_h2configuration.h"

H2Configuration::H2Configuration(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Configuration)
{
    ui->setupUi(this);

    setName( "config" );

    connect(ui->sizeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSelectSize(int)));

    connect( ui->sizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnModelChanged()));
    connect( ui->spinBox_X, SIGNAL(valueChanged(QString)), this, SLOT(slotOnModelChanged()));
    connect( ui->spinBox_Y, SIGNAL(valueChanged(QString)), this, SLOT(slotOnModelChanged()));
    connect( ui->radioButton_b, SIGNAL(toggled(bool)), this, SLOT(slotOnModelChanged()));
    connect( ui->radioButton_t, SIGNAL(toggled(bool)), this, SLOT(slotOnModelChanged()));

    slotSelectSize(0);
    slotOnModelChanged();
}

H2Configuration::~H2Configuration()
{
    delete ui;
}

void H2Configuration::slotOnModelChanged()
{
    QString model = QString("%1-%2")
            .arg(ui->label_family->text())
            .arg(ui->sizeComboBox->currentText());

    QString str = ui->spinBox_X->text().left(ui->spinBox_X->text().length()-2);
    m_WorkStrokeX = str.toInt();
    model += "-";
    model += str;

    str = ui->spinBox_Y->text().left(ui->spinBox_Y->text().length()-2);
    m_WorkStrokeY = str.toInt();
    model += "-";
    model += str;

    if(ui->sizeComboBox->currentIndex() == 0) //small
    {
        model += "-GF";
        m_size = 0;
    }else{ //big
        model += "-KF";
        m_size = 1;
    }

    if(ui->radioButton_b->isChecked()){
        model += "-B";
        m_MotorPosition = 0;
    }else{
        model += "-T";
        m_MotorPosition = 1;
    }

    ui->label_model->setText(model);
}

void H2Configuration::slotSelectSize(int index)
{
    if(index == 0)
    {
        ui->spinBox_X->setMaximum(494);
        ui->spinBox_X->setValue(494);
        ui->spinBox_X->setToolTip("0-494");

        ui->spinBox_Y->setMaximum(802);
        ui->spinBox_Y->setValue(802);
        ui->spinBox_Y->setToolTip("0-820");
    }
    else if(index == 1)
    {
        ui->spinBox_X->setMaximum(770);
        ui->spinBox_X->setValue(770);
        ui->spinBox_X->setToolTip("0-770");

        ui->spinBox_Y->setMaximum(890);
        ui->spinBox_Y->setValue(890);
        ui->spinBox_Y->setToolTip("0-890");
    }
}


int H2Configuration::setApply()
{
    qDebug() << "H2Configuration:" << mViHandle << mRobotName.toInt();

#if 0
    int ret = -1;
//    char strIDN[1024] = "";
//    ret = mrhtIdn_Query(mViHandle, strIDN,sizeof(strIDN));
//    qDebug() << strIDN; //MegaRobo Technologies,MRH-T,MRHT000005187U0032,00.00.01.06

    //type:0==>small, 1==>big
    ret = mrhtRobotSubtype(mViHandle, mRobotName.toInt(), m_size);

    //WorkStrokeX


    //WorkStrokeY


    //states:OFF==>bottom, ON==>top
    ret = mrhtDeviceMrqMotionReverse(mViHandle, mRobotName.toInt(), m_MotorPosition);

#endif
    return 0;
}
