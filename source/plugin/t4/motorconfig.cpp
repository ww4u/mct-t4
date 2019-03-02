#include "motorconfig.h"
#include "ui_motorconfig.h"
#include "t4.h"
namespace mrx_t4 {

MotorConfig::MotorConfig(QWidget *parent) :
    XPage(parent),
    ui(new Ui::MotorConfig)
{
    ui->setupUi(this);

    spyEdited();

    set_page_rstable();
}

MotorConfig::~MotorConfig()
{
    delete ui;
}

void MotorConfig::adapteToUserMode( sysPara::eSysMode mode )
{
    bool bAdminEn;

    if ( mode == sysPara::e_sys_admin )
    { bAdminEn = true; }
    else
    { bAdminEn = false; }

    setEnabled( bAdminEn );
}

#define set_current( id )   ui->doubleSpinBox##id->setValue( selfPara->mAxisCurrents[id] );
#define get_current( id )   selfPara->mAxisCurrents[id] = ui->doubleSpinBox##id->value();
void MotorConfig::updateUi()
{
    set_current( 0 );
    set_current( 1 );
    set_current( 2 );
    set_current( 3 );

    set_current( 4 );
}

void MotorConfig::updateData()
{
    get_current( 0 );
    get_current( 1 );
    get_current( 2 );
    get_current( 3 );

    get_current( 4 );
}

void MotorConfig::spyEdited()
{
    QGroupBox *gpBox[]=
    {
    };
    QCheckBox *checkBoxes[]=
    {
//        ui->chkEn
    };
    QRadioButton *radBoxes[] = {
    };
    QLineEdit *edits[]={

    };

    QSpinBox *spinBoxes[]={
    };

    QDoubleSpinBox *doubleSpinBoxes[]={
        ui->doubleSpinBox0,
        ui->doubleSpinBox1,
        ui->doubleSpinBox2,
        ui->doubleSpinBox3,
        ui->doubleSpinBox4,
    };

    QComboBox *comboxes[]={

    };

    QSlider *sliders[]
    {
    };

    install_spy();
}

void MotorConfig::retranslateUi()
{ ui->retranslateUi( this ); }

}
