#include "h2homing.h"
#include "ui_h2homing.h"

H2Homing::H2Homing(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Homing)
{
    ui->setupUi(this);

    setName( "homing" );

    connect(ui->doubleSpinBox_SearchVelocity,SIGNAL(valueChanged(double)), this, SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_Acceleration,  SIGNAL(valueChanged(double)), this, SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_ForceLimit,    SIGNAL(valueChanged(double)), this, SLOT(slotOnModelChanged()));
}

H2Homing::~H2Homing()
{
    delete ui;
}

int H2Homing::setApply()
{
//    qDebug() << "H2Homing:" << mViHandle << mRobotName;
#if 0
    //SearchVelocity=50.00


    //Acceleration=5.000


    //ForceLimit=75.0

#endif

    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mProjectName + ".xml";
    QMap<QString,QString> map;

    map.insert("SearchVelocity", QString::number(m_SearchVelocity,10,2));
    map.insert("Acceleration", QString::number(m_Acceleration,10,2));
    map.insert("ForceLimit", QString::number(m_ForceLimit,10,2));

    mXML.xmlNodeRemove(fileName,"H2Homing");
    mXML.xmlNodeAppend(fileName, "H2Homing", map);

    return 0;
}

void H2Homing::loadXmlConfig()
{
    //! load xml
    MegaXML mXML;
    QString fileName = QApplication::applicationDirPath() + "/robots/" + mProjectName + ".xml";
    QMap<QString,QString> map = mXML.xmlRead(fileName);
    if(map.isEmpty()) return;

    ui->doubleSpinBox_SearchVelocity->setValue(map["SearchVelocity"].toDouble());
    ui->doubleSpinBox_Acceleration->setValue(map["Acceleration"].toDouble());
    ui->doubleSpinBox_ForceLimit->setValue(map["ForceLimit"].toDouble());
}

void H2Homing::slot_set_direction(QString text)
{
    ui->label_direction->setText(text);
}

void H2Homing::slotOnModelChanged()
{
    m_SearchVelocity = ui->doubleSpinBox_SearchVelocity->value();
    m_Acceleration   = ui->doubleSpinBox_Acceleration->value();
    m_ForceLimit     = ui->doubleSpinBox_ForceLimit->value();

//    qDebug() << m_SearchVelocity;
//    qDebug() << m_Acceleration  ;
//    qDebug() << m_ForceLimit    ;
}


