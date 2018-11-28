#include "h2jogmode.h"
#include "ui_h2jogmode.h"

H2JogMode::H2JogMode(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2JogMode)
{
    ui->setupUi(this);

    setFocusName( "Jogmode" );
}

H2JogMode::~H2JogMode()
{
    delete ui;
}

int H2JogMode::readDeviceConfig()
{
    return 0;
}

int H2JogMode::writeDeviceConfig()
{

    return 0;
}

int H2JogMode::loadConfig()
{
    //! load xml
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mProjectName + ".xml";
    QFile file(fileName);
    if( !file.exists() )
        fileName = QApplication::applicationDirPath() + "/robots/default.xml";

    QMap<QString,QString> map = mXML.xmlRead(fileName);
    if(map.isEmpty()) return -1;

    m_CrawlingVelocity = map["CrawlingVelocity"].toDouble();
    m_CrawlingTime     = map["CrawlingTime"].toDouble();
    m_MaximumVelocity  = map["MaximumVelocity"].toDouble();

    return 0;
}

int H2JogMode::saveConfig()
{
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mProjectName + ".xml";
    QMap<QString,QString> map;

    map.insert("CrawlingVelocity",  QString::number(m_CrawlingVelocity,10,2));
    map.insert("CrawlingTime",      QString::number(m_CrawlingTime,10,2));
    map.insert("MaximumVelocity",   QString::number(m_MaximumVelocity,10,2));

    mXML.xmlNodeRemove(fileName,"H2JogMode");
    mXML.xmlNodeAppend(fileName, "H2JogMode", map);

    return 0;
}

void H2JogMode::updateShow()
{
    ui->doubleSpinBox_CrawlingVelocity->setValue(m_CrawlingVelocity);
    ui->doubleSpinBox_CrawlingTime->setValue(m_CrawlingTime);
    ui->doubleSpinBox_MaximumVelocity->setValue(m_MaximumVelocity);
}

void H2JogMode::on_doubleSpinBox_CrawlingVelocity_valueChanged(double arg1)
{
    m_CrawlingVelocity = arg1;
    emit signal_data_changed(true);
}

void H2JogMode::on_doubleSpinBox_CrawlingTime_valueChanged(double arg1)
{
    m_CrawlingTime     = arg1;
    emit signal_data_changed(true);
}

void H2JogMode::on_doubleSpinBox_MaximumVelocity_valueChanged(double arg1)
{
    m_MaximumVelocity  =arg1;
    emit signal_data_changed(true);
}

void H2JogMode::translateUI()
{
    ui->retranslateUi(this);
}
