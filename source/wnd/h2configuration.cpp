#include "h2configuration.h"
#include "ui_h2configuration.h"

H2Configuration::H2Configuration(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Configuration)
{
    ui->setupUi(this);

    setName( "config" );

    ui->label_family->setText("MRX-H2");

    connect(ui->sizeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSelectSize(int)));

    connect( ui->sizeComboBox,  SIGNAL(currentIndexChanged(int)),   this, SLOT(slotOnModelChanged()));
    connect( ui->spinBox_X,     SIGNAL(valueChanged(QString)),      this, SLOT(slotOnModelChanged()));
    connect( ui->spinBox_Y,     SIGNAL(valueChanged(QString)),      this, SLOT(slotOnModelChanged()));
    connect( ui->radioButton_b, SIGNAL(toggled(bool)),              this, SLOT(slotOnModelChanged()));

    slotSelectSize(0);
}

H2Configuration::~H2Configuration()
{
    delete ui;
}

void H2Configuration::loadXmlConfig()
{
    //! load xml
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mProjectName + ".xml";
    QMap<QString,QString> map = mXML.xmlRead(fileName);
    if(map.isEmpty()) return;

    ui->label_family->setText(map["Family"]);
    ui->sizeComboBox->setCurrentIndex(map["Size"].toInt());
    ui->spinBox_X->setValue(map["WorkStrokeX"].toInt());
    ui->spinBox_Y->setValue(map["WorkStrokeY"].toInt());

    if(map["MotorPosition"].toInt() == 0)
    {
        ui->radioButton_b->setChecked(true);
        ui->radioButton_t->setChecked(false);
    }
    else{
        ui->radioButton_b->setChecked(false);
        ui->radioButton_t->setChecked(true);
    }
}

void H2Configuration::slotOnModelChanged()
{
    m_Family = ui->label_family->text();

    QString model = QString("%1-%2")
            .arg(m_Family)
            .arg(ui->sizeComboBox->currentText());

    m_WorkStrokeX = ui->spinBox_X->value();
    model += "-";
    model += QString::number(m_WorkStrokeX);

    m_WorkStrokeY = ui->spinBox_Y->value();
    model += "-";
    model += QString::number(m_WorkStrokeY);

    if(ui->sizeComboBox->currentIndex() == 0) //small
    {
        model += "-GF";
        m_Size = 0;
    }else{ //big
        model += "-KF";
        m_Size = 1;
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
//    qDebug() << "H2Configuration:" << mViHandle << mRobotName;

#if 0
    int ret = -1;
//    char strIDN[1024] = "";
//    ret = mrhtIdn_Query(mViHandle, strIDN,sizeof(strIDN));
//    qDebug() << strIDN; //MegaRobo Technologies,MRH-T,MRHT000005187U0032,00.00.01.06

    //type:0==>small, 1==>big
    ret = mrhtRobotSubtype(mViHandle, mRobotName, m_size);

    //WorkStrokeX


    //WorkStrokeY


    //states:OFF==>bottom, ON==>top
    ret = mrhtDeviceMrqMotionReverse(mViHandle, mRobotName, m_MotorPosition);

#endif

    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mProjectName + ".xml";
    QMap<QString,QString> map;
    map.insert( "Family", m_Family);
    map.insert( "Size", QString::number(m_Size));
    map.insert( "WorkStrokeX", QString::number(m_WorkStrokeX));
    map.insert( "WorkStrokeY", QString::number(m_WorkStrokeY));
    map.insert( "MotorPosition", QString::number(m_MotorPosition));
    mXML.xmlNodeRemove(fileName,"H2Configuration");
    mXML.xmlNodeAppend(fileName, "H2Configuration", map);

    return 0;
}
