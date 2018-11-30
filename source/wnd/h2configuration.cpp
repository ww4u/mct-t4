#include "h2configuration.h"
#include "ui_h2configuration.h"

H2Configuration::H2Configuration(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Configuration)
{
    ui->setupUi(this);

    setFocusName( "Configuration" );

    ui->label_family->setText("MRX-H2");
}

H2Configuration::~H2Configuration()
{
    delete ui;
}

int H2Configuration::readDeviceConfig()
{
    return 0;
}

int H2Configuration::writeDeviceConfig()
{
    int ret = 0;
#if 0
    //type:0==>small, 1==>big
    ret += mrhtRobotSubtype(mViHandle, mRobotName, m_Size);

    //WorkStrokeX

    //WorkStrokeY

    //states:OFF==>bottom, ON==>top
    ret += mrqDeviceMrqMotionReverse(mViHandle, mRobotName, m_MotorPosition);

#endif

    return ret;
}

int H2Configuration::loadConfig()
{
    //! load xml
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mProjectName + ".xml";
    QFile file(fileName);
    if( !file.exists() )
        fileName = QApplication::applicationDirPath() + "/robots/default.xml";

    QMap<QString,QString> map = mXML.xmlRead(fileName);
    if(map.isEmpty()) return -1;

    m_Family = map["Family"];
    m_Size = map["Size"].toInt();
    m_WorkStrokeX = map["WorkStrokeX"].toInt();
    m_WorkStrokeY = map["WorkStrokeY"].toInt();
    m_MotorPosition = map["MotorPosition"].toInt();

    return 0;
}

int H2Configuration::saveConfig()
{
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

void H2Configuration::updateShow()
{
    ui->label_family->setText(m_Family);
    ui->sizeComboBox->setCurrentIndex(m_Size);
    ui->spinBox_X->setValue(m_WorkStrokeX);
    ui->spinBox_Y->setValue(m_WorkStrokeY);

    on_sizeComboBox_currentIndexChanged(m_Size);

    if(0 == m_MotorPosition)
    {
        ui->radioButton_b->setChecked(true);
        ui->radioButton_t->setChecked(false);
    }
    else{
        ui->radioButton_b->setChecked(false);
        ui->radioButton_t->setChecked(true);
    }
}

void H2Configuration::changeModelLabel()
{
    m_Family = ui->label_family->text();

    QString model = QString("%1-%2")
            .arg(m_Family)
            .arg(ui->sizeComboBox->currentText());

    model += "-";
    model += QString::number(m_WorkStrokeX);

    model += "-";
    model += QString::number(m_WorkStrokeY);

    if(ui->sizeComboBox->currentIndex() == 0)
    {
        model += "-GF";
    }else{
        model += "-KF";
    }

    if(ui->radioButton_b->isChecked()){
        model += "-B";
    }
    else if(ui->radioButton_t->isChecked()){
        model += "-T";
    }

    ui->label_model->setText(model);
}


void H2Configuration::on_radioButton_b_toggled(bool checked)
{
    if(checked)
        m_MotorPosition = 0;
    changeModelLabel();
    emit signalModelDataChanged(true);
}

void H2Configuration::on_radioButton_t_toggled(bool checked)
{
    if(checked)
        m_MotorPosition = 1;
    changeModelLabel();
    emit signalModelDataChanged(true);
}

void H2Configuration::on_spinBox_X_valueChanged(int arg1)
{
    m_WorkStrokeX = arg1;
    changeModelLabel();
    emit signalModelDataChanged(true);
}

void H2Configuration::on_spinBox_Y_valueChanged(int arg1)
{
    m_WorkStrokeY = arg1;
    changeModelLabel();
    emit signalModelDataChanged(true);
}

void H2Configuration::on_sizeComboBox_currentIndexChanged(int index)
{
    m_Size = index;

    if(index == 0)
    {
        ui->spinBox_X->setRange(0, 494);
        ui->spinBox_X->setValue(494);
        ui->spinBox_X->setToolTip("0-494");

        ui->spinBox_Y->setRange(0, 802);
        ui->spinBox_Y->setValue(802);
        ui->spinBox_Y->setToolTip("0-820");
    }
    else if(index == 1)
    {
        ui->spinBox_X->setRange(0, 770);
        ui->spinBox_X->setValue(770);
        ui->spinBox_X->setToolTip("0-770");

        ui->spinBox_Y->setRange(0, 890);
        ui->spinBox_Y->setValue(890);
        ui->spinBox_Y->setToolTip("0-890");
    }

    changeModelLabel();
    emit signalModelDataChanged(true);
}

void H2Configuration::translateUI()
{
    ui->retranslateUi(this);
}
