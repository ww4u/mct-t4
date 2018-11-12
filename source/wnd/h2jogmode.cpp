#include "h2jogmode.h"
#include "ui_h2jogmode.h"

H2JogMode::H2JogMode(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2JogMode)
{
    ui->setupUi(this);

    setName( "jog" );

    connect(ui->doubleSpinBox_CrawlingVelocity, SIGNAL(valueChanged(double)),
            this,SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_CrawlingTime,     SIGNAL(valueChanged(double)),
            this,SLOT(slotOnModelChanged()));
    connect(ui->doubleSpinBox_MaximumVelocity,  SIGNAL(valueChanged(double)),
            this,SLOT(slotOnModelChanged()));
}

H2JogMode::~H2JogMode()
{
    delete ui;
}

int H2JogMode::setApply()
{
//    qDebug() << "H2JogMode:" << mViHandle << mRobotName;
#if 0

    //CrawlingVelocity=10.00


    //CrawlingTime=1000


    //MaximumVelocity=50.00


#endif
    return 0;
}

void H2JogMode::slotOnModelChanged()
{
    m_CrawlingVelocity = ui->doubleSpinBox_CrawlingVelocity->value();
    m_CrawlingTime     = ui->doubleSpinBox_CrawlingTime->value()    ;
    m_MaximumVelocity  = ui->doubleSpinBox_MaximumVelocity->value() ;

//    qDebug() << m_CrawlingVelocity;
//    qDebug() << m_CrawlingTime    ;
//    qDebug() << m_MaximumVelocity ;
}
