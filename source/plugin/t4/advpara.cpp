#include "advpara.h"
#include "ui_advpara.h"
#include <QtWidgets>

#include "t4.h"
#include "../../../include/mydef.h"

namespace mrx_t4 {


AdvPara::AdvPara(QWidget *parent) :
    XPage(parent),
    ui(new Ui::AdvPara)
{
    ui->setupUi(this);

    spyEdited();

    set_page_rstable();

    ui->spinHomeSpeed->setSuffix( QString("%1/s").arg( char_deg )  );
    ui->spinAcc->setSuffix( QString("mm/s%1").arg( char_square ) );

    ui->spinJointSpeed->setSuffix( QString("%1/s").arg( char_deg ) );
}

AdvPara::~AdvPara()
{
    delete ui;
}

void AdvPara::adapteToUserMode( sysPara::eSysMode mode )
{
    setEnabled( mode == sysPara::e_sys_admin );
}

void AdvPara::updateUi()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

//    ui->spinHomeSpeed->setValue( pRobo->mHomeSpeed );
//    ui->spinHomeTimeout->setValue( pRobo->mHomeTimeout );

//    ui->spinVel->setValue( pRobo->mDefSpeed );
//    ui->spinAcc->setValue( pRobo->mDefAcc );

//    ui->spinJointSpeed->setValue( pRobo->mMaxJointSpeed );
//    ui->spinTerminalSpeed->setValue( pRobo->mMaxTerminalSpeed );

    bool bDir = true;

    exchange_spin( spinHomeSpeed, pRobo->mHomeSpeed, bDir );
    exchange_spin( spinHomeTimeout, pRobo->mHomeTimeout, bDir )

    exchange_spin( spinVel, pRobo->mDefSpeed, bDir )
    exchange_spin( spinAcc, pRobo->mDefAcc, bDir )

    exchange_spin( spinJointSpeed, pRobo->mMaxJointSpeed, bDir )
    exchange_spin( spinTerminalSpeed, pRobo->mMaxTerminalSpeed, bDir )
}

void AdvPara::updateData()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    bool bDir = false;

    exchange_spin( spinHomeSpeed, pRobo->mHomeSpeed, bDir );
    exchange_spin( spinHomeTimeout, pRobo->mHomeTimeout, bDir )

    exchange_spin( spinVel, pRobo->mDefSpeed, bDir )
    exchange_spin( spinAcc, pRobo->mDefAcc, bDir )

    exchange_spin( spinJointSpeed, pRobo->mMaxJointSpeed, bDir )
    exchange_spin( spinTerminalSpeed, pRobo->mMaxTerminalSpeed, bDir )
}

void AdvPara::spyEdited()
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
        ui->spinHomeSpeed,
        ui->spinHomeTimeout,

        ui->spinVel,
        ui->spinAcc,

        ui->spinJointSpeed,
        ui->spinTerminalSpeed,
    };

    QComboBox *comboxes[]={
//        ui->cmbInterpMode,
    };

    QSlider *sliders[]
    {
    };

    install_spy();

//    foreach( QLineEdit *pEdit, mAxesEdits )
//    {
//        spy_control_edit( pEdit );
//    }
}

void AdvPara::retranslateUi()
{ ui->retranslateUi( this ); }

}
