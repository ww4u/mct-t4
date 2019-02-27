#include "h2configuration.h"
#include "ui_h2configuration.h"

H2Configuration::H2Configuration(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Configuration)
{
    ui->setupUi(this);

    setFocuHelpName( "Configuration" );

    ui->label_family->setText("MRX-H2");

    //暂时隐藏此选择项
    ui->groupBox_motorPos->setEnabled(false);
    ui->groupBox_motorPos->setHidden(true);
}

H2Configuration::~H2Configuration()
{
    delete ui;
}

int H2Configuration::readDeviceConfig()
{
//    int ret = -1;
//    int type = mrgGetRobotType(mViHandle, mRobotName);
//    qDebug() << "mrgGetRobotType" << type;
//    if (type == e_MRX_T4){
//        m_Family = "MRX-T4";
//    }
//    else if (type == e_MRX_AS){
//        m_Family = "MRX-AS";
//    }
//    else if (type == e_MRX_H2){
//        m_Family = "MRX-H2";
//    }
//    else if (type == e_MRX_DELTA){
//        m_Family = "MRX-DELTA";
//    }
//    else if (type == e_MRX_RAW){
//        m_Family = "MRX-RAW";
//    }else{
//        sysError("mrgGetRobotType error", type);
//        return -1;
//    }

//    ret = mrgGetRobotSubType(mViHandle, mRobotName);
//    qDebug() << "mrgGetRobotSubType" << ret;
//    if(ret < 0) {
//        sysError("mrgGetRobotSubType", ret);
//        return -1;
//    }
//    m_Size = ret;

//#if 0
//    int val = 0;
//    ret = mrgMRQMotionReverse_Query(mViHandle, mDeviceName, &val);
//    qDebug() << "mrgMRQMotionReverse_Query" << ret;
//    if(ret < 0) {
//        sysError("mrgMRQMotionReverse_Query", ret);
//        return -1;
//    }
//    m_MotorPosition = val;
//#endif

    return 0;
}

int H2Configuration::writeDeviceConfig()
{
    int ret = -1;

    //type:0==>small, 1==>big
    ret = mrgSetRobotSubType(mViHandle, mRobotName, m_Size);
    qDebug() << "mrgSetRobotSubType" << ret;
    if(ret != 0){
        sysError("mrgSetRobotSubType", ret);
        return -1;
    }

    //WorkStrokeX


    //WorkStrokeY

#if 0
    //states:OFF==>bottom, ON==>top
    ret = mrgMRQMotionReverse(mViHandle, mDeviceName, m_MotorPosition);
    qDebug() << "mrgMRQMotionReverse" << ret;
    if(ret != 0){
        sysError("mrgMRQMotionReverse", ret);
        return -1;
    }
#endif

    return ret;
}

int H2Configuration::loadConfig()
{
    //! load xml
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mConfigFileName + ".xml";
    QFile file(fileName);
    if( !file.exists() )
        fileName = QApplication::applicationDirPath() + "/robots/default.xml";

    QMap<QString,QString> map = mXML.xmlRead(fileName);
    if(map.isEmpty()) return -1;

    m_Family = map["Family"];
    m_Size = map["Size"].toInt();
    m_WorkStrokeX = map["WorkStrokeX"].toDouble();
    m_WorkStrokeY = map["WorkStrokeY"].toDouble();
    m_MotorPosition = map["MotorPosition"].toInt();

    return 0;
}

int H2Configuration::saveConfig()
{
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mConfigFileName + ".xml";
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
    ui->doubleSpinBox_X->setValue(m_WorkStrokeX);
    ui->doubleSpinBox_Y->setValue(m_WorkStrokeY);

    on_sizeComboBox_currentIndexChanged(m_Size);

    if(0 == m_MotorPosition){
        ui->radioButton_b->setChecked(true);
        ui->radioButton_t->setChecked(false);
    }else{
        ui->radioButton_b->setChecked(false);
        ui->radioButton_t->setChecked(true);
    }

}

void H2Configuration::changeModelLabel()
{
    QString model = "";

    m_Family = ui->label_family->text();
    model += m_Family;

    //! 目前暂时未知大尺寸H2的型号，暂时写死为小号H2的型号
    model += "-M";

#if 0
    if(ui->sizeComboBox->currentIndex() == 0){
        model += "-M";
    }else{
        model += "-L";
    }

    model += "-";
    model += QString::number(m_WorkStrokeX);

    model += "-";
    model += QString::number(m_WorkStrokeY);


    if(ui->radioButton_b->isChecked()){
        model += "-B";
    }
    else if(ui->radioButton_t->isChecked()){
        model += "-T";
    }
#endif

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

void H2Configuration::on_sizeComboBox_currentIndexChanged(int index)
{
    if(index < 0) return;
    m_Size = index;

    if(index == 0){
        //! MRX-H2-M 370 x 390
        ui->doubleSpinBox_X->setRange(0, 370);
        ui->doubleSpinBox_X->setToolTip("0-370");

        ui->doubleSpinBox_Y->setRange(0, 390);
        ui->doubleSpinBox_Y->setToolTip("0-390");
    }
    else if(index == 1){

        ui->doubleSpinBox_X->setRange(0, 770);
        ui->doubleSpinBox_X->setToolTip("0-770");

        ui->doubleSpinBox_Y->setRange(0, 890);
        ui->doubleSpinBox_Y->setToolTip("0-890");
    }

    changeModelLabel();
    emit signalModelDataChanged(true);
}

void H2Configuration::translateUI()
{
    ui->retranslateUi(this);
}

void H2Configuration::on_doubleSpinBox_X_valueChanged(double arg1)
{
    m_WorkStrokeX = arg1;
    changeModelLabel();
    emit signalModelDataChanged(true);
    emit WorkStrokeXChanged(m_WorkStrokeX);
}

void H2Configuration::on_doubleSpinBox_Y_valueChanged(double arg1)
{
    m_WorkStrokeY = arg1;
    changeModelLabel();
    emit signalModelDataChanged(true);
    emit WorkStrokeYChanged(m_WorkStrokeY);
}
