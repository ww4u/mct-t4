#include <QtWidgets>
#include "config.h"
#include "ui_config.h"

#include "t4.h"

namespace mrx_t4 {

Config::Config(QWidget *parent) :
    XPage(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);

    setContextHelp("config");

    spyEdited();

    set_page_rstable();
    //! post set
//    on_cmbTypeTerminal_currentIndexChanged( ui->cmbTypeTerminal->currentIndex() );
}

Config::~Config()
{
    delete ui;
}

void Config::adapteToUserMode( sysPara::eSysMode mode )
{
    bool bAdminEn;

    if ( mode == sysPara::e_sys_admin )
    { bAdminEn = true; }
    else
    { bAdminEn = false; }

    ui->tab_2->setEnabled( bAdminEn );
    ui->tab_4->setEnabled( bAdminEn );
}

#define set_zero( id )  ui->spinZero##id->setValue( selfPara->mAxisZero[id] );
#define set_lower( id ) ui->spinL##id->setValue( selfPara->mAxisSoftLower[id] );
#define set_upper( id ) ui->spinU##id->setValue( selfPara->mAxisSoftUpper[id] );

#define get_zero( id )  selfPara->mAxisZero[id] = ui->spinZero##id->value();
#define get_lower( id ) selfPara->mAxisSoftLower[id] = ui->spinL##id->value();
#define get_upper( id ) selfPara->mAxisSoftUpper[id] = ui->spinU##id->value();
void Config::updateUi()
{
    //! set type
    ui->cmbTypeTerminal->setCurrentIndex( (int)selfPara->mTerminalType );
    on_cmbTypeTerminal_currentIndexChanged( ui->cmbTypeTerminal->currentIndex() );

    //! zero
//    ui->spinZero0->setValue( selfPara->mAxisZero[0] );
    set_zero( 0 );
    set_zero( 1 );
    set_zero( 2 );
    set_zero( 3 )

    //! range
//    ui->spinL0->setValue( selfPara->mAxisSoftLower[0] );
    set_lower( 0 );
    set_lower( 1 );
    set_lower( 2 );
    set_lower( 3 );

    set_upper( 0 );
    set_upper( 1 );
    set_upper( 2 );
    set_upper( 3 );

    //! arm length
    ui->spinBase->setValue( selfPara->mArmLength[0] );
    ui->spinBA->setValue( selfPara->mArmLength[1] );
    ui->spinLA->setValue( selfPara->mArmLength[2] );
}

void Config::updateData()
{
    selfPara->mTerminalType = (T4Para::eTerminalType)ui->cmbTypeTerminal->currentIndex();

    get_zero( 0 );
    get_zero( 1 );
    get_zero( 2 );
    get_zero( 3 );

    //! range
    get_lower( 0 );
    get_lower( 1 );
    get_lower( 2 );
    get_lower( 3 );

    get_upper( 0 );
    get_upper( 1 );
    get_upper( 2 );
    get_upper( 3 );
}

void Config::spyEdited()
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
        ui->spinBase,
        ui->spinBA,
        ui->spinLA,
    };

    QComboBox *comboxes[]={
        ui->cmbTypeTerminal
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

void Config::retranslateUi()
{
    ui->retranslateUi( this );
}

void Config::on_cmbTypeTerminal_currentIndexChanged(int index)
{
    QIcon icon = ui->cmbTypeTerminal->itemIcon( index );
    if ( icon.isNull() )
    { ui->labelTerminalImg->setVisible( false );}
    else
    {
        ui->labelTerminalImg->setPixmap( icon.pixmap( 160,160 ) );
        ui->labelTerminalImg->setVisible( true );
    }

    //! validate the terminal
    if ( index == 3 || index == 4 )
    {
        Q_ASSERT( NULL != m_pPlugin );
        m_pPlugin->emit_setting_changed( (eXSetting)MRX_T4::e_setting_terminal, false );
    }
    else
    {
        Q_ASSERT( NULL != m_pPlugin );
        m_pPlugin->emit_setting_changed( (eXSetting)MRX_T4::e_setting_terminal, true );
    }
}

}
