#include "h2measurement.h"
#include "ui_h2measurement.h"

H2Measurement::H2Measurement(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Measurement)
{
    ui->setupUi(this);
    m_ZeroPoint = 0;

    setFocusName("Measurement");

    connect(ui->comboBox_AxesZeroPoint,SIGNAL(currentIndexChanged(int)),this,SLOT(slotChangeCornerPicture(int)));

}

H2Measurement::~H2Measurement()
{
    delete ui;
}

void H2Measurement::slotChangeCornerPicture(int index)
{
    QString strPixmap = ":/res/image/h2measurement/CornerPoint";
    strPixmap += QString::number(index+1);
    strPixmap += ".PNG";

    ui->label_picture->setPixmap(QPixmap(strPixmap));
    emit signal_AxesZeroPoint_currentTextChanged(ui->comboBox_AxesZeroPoint->currentText());
}

int H2Measurement::readDeviceConfig()
{
    m_ZeroPoint = mrgGetRobotCoordinateSystem(mViHandle, mRobotName);

    double x, y, z;
    if(0 == mrgGetRobotProjectZero(mViHandle, mRobotName, &x, &y, &z) )
    {
        m_ProjectZeroPointX = x;
        m_ProjectZeroPointY = y;
        qDebug() << "mrgGetRobotProjectZero" << x << y;
    }else{
        return -1;
    }

    if(0 == mrgGetRobotSoftWareLimit(mViHandle, mRobotName, 0, &x, &y, &z) )
    {
        m_SWLimitPositiveX = x;
        m_SWLimitPositiveY = y;
        qDebug() << "mrgGetRobotSoftWareLimit Positive" << x << y;
    }else{
        return -1;
    }

    if(0 == mrgGetRobotSoftWareLimit(mViHandle, mRobotName, 1, &x, &y, &z) )
    {
        m_SWLimitNegativeX  = x;
        m_SWLimitNegativeY  = y;
        qDebug() << "mrgGetRobotSoftWareLimit Negative" << x << y;
    }else{
        return -1;
    }

    return 0;
}

int H2Measurement::writeDeviceConfig()
{
    int ret = 0;

    int value = ui->comboBox_AxesZeroPoint->currentIndex();
    ret = mrgSetRobotCoordinateSystem(mViHandle, mRobotName, value);
    qDebug() << "mrgSetRobotCoordinateSystem" << ret;
    if( 0 != ret) return -1;

    ret = mrgSetRobotProjectZero(mViHandle, mRobotName, m_ProjectZeroPointX, m_ProjectZeroPointY, 0);
    qDebug() << "mrgSetRobotProjectZero" << ret;
    if( 0 != ret) return -1;

    ret = mrgSetRobotSoftWareLimit(mViHandle, mRobotName, 0, m_SWLimitPositiveX, m_SWLimitPositiveY, 0);
    qDebug() << "mrgSetRobotSoftWareLimit Positive" << ret;
    if( 0 != ret) return -1;

    ret = mrgSetRobotSoftWareLimit(mViHandle, mRobotName, 1, m_SWLimitNegativeX, m_SWLimitNegativeY, 0);
    qDebug() << "mrgSetRobotSoftWareLimit Negative" << ret;
    if( 0 != ret) return -1;

    return ret;
}

int H2Measurement::loadConfig()
{
    //! load xml
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mProjectName + ".xml";
    QFile file(fileName);
    if( !file.exists() )
        fileName = QApplication::applicationDirPath() + "/robots/default.xml";

    QMap<QString,QString> map = mXML.xmlRead(fileName);
    if(map.isEmpty()) return -1;

    m_ZeroPoint         = map["ZeroPoint"].toInt();
    m_ProjectZeroPointX = map["ProjectZeroPointX"].toDouble();
    m_ProjectZeroPointY = map["ProjectZeroPointY"].toDouble();
    m_SWLimitPositiveX  = map["SWLimitPositiveX"].toDouble();
    m_SWLimitPositiveY  = map["SWLimitPositiveY"].toDouble();
    m_SWLimitNegativeX  = map["SWLimitNegativeX"].toDouble();
    m_SWLimitNegativeY  = map["SWLimitNegativeY"].toDouble();

    return 0;
}

int H2Measurement::saveConfig()
{
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mProjectName + ".xml";
    QMap<QString,QString> map;

    map.insert("ZeroPoint"  , QString::number(m_ZeroPoint));
    map.insert("Direction"  , ui->comboBox_AxesZeroPoint->currentText() );
    map.insert("ProjectZeroPointX" , QString::number( m_ProjectZeroPointX, 10, 2));
    map.insert("ProjectZeroPointY" , QString::number( m_ProjectZeroPointY, 10, 2));
    map.insert("SWLimitPositiveX"  , QString::number( m_SWLimitPositiveX, 10, 2 ));
    map.insert("SWLimitPositiveY"  , QString::number( m_SWLimitPositiveY, 10, 2 ));
    map.insert("SWLimitNegativeX"  , QString::number( m_SWLimitNegativeX, 10, 2 ));
    map.insert("SWLimitNegativeY"  , QString::number( m_SWLimitNegativeY, 10, 2 ));

    mXML.xmlNodeRemove(fileName,"H2Measurement");
    mXML.xmlNodeAppend(fileName, "H2Measurement", map);

    return 0;
}

void H2Measurement::updateShow()
{
    ui->comboBox_AxesZeroPoint->setCurrentIndex(m_ZeroPoint);
    ui->doubleSpinBox_pzpX->setValue( m_ProjectZeroPointX );
    ui->doubleSpinBox_pzpY->setValue( m_ProjectZeroPointY );
    ui->doubleSpinBox_swlp_X->setValue( m_SWLimitPositiveX );
    ui->doubleSpinBox_swlp_Y->setValue( m_SWLimitPositiveY );
    ui->doubleSpinBox_swln_X->setValue( m_SWLimitNegativeX );
    ui->doubleSpinBox_swln_Y->setValue( m_SWLimitNegativeY );
}

void H2Measurement::on_comboBox_AxesZeroPoint_currentIndexChanged(int index)
{
    m_ZeroPoint = index;
    emit signalModelDataChanged(true);
}

void H2Measurement::on_doubleSpinBox_pzpX_valueChanged(double arg1)
{
    m_ProjectZeroPointX = arg1;
    emit signalModelDataChanged(true);
}

void H2Measurement::on_doubleSpinBox_pzpY_valueChanged(double arg1)
{
    m_ProjectZeroPointY = arg1;
    emit signalModelDataChanged(true);
}

void H2Measurement::on_doubleSpinBox_swlp_X_valueChanged(double arg1)
{
    m_SWLimitPositiveX = arg1;
    emit signalModelDataChanged(true);
}

void H2Measurement::on_doubleSpinBox_swlp_Y_valueChanged(double arg1)
{
    m_SWLimitPositiveY = arg1;
    emit signalModelDataChanged(true);
}

void H2Measurement::on_doubleSpinBox_swln_X_valueChanged(double arg1)
{
    m_SWLimitNegativeX = arg1;
    emit signalModelDataChanged(true);
}

void H2Measurement::on_doubleSpinBox_swln_Y_valueChanged(double arg1)
{
    m_SWLimitNegativeY = arg1;
    emit signalModelDataChanged(true);
}

void H2Measurement::translateUI()
{
    ui->retranslateUi(this);
}
