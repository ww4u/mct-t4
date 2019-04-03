#include <QtWidgets>
#include "config.h"
#include "ui_config.h"

#include "t4.h"
#include "MegaGateway.h"


#define ABS_ANGLE_TO_DEG( angle )   (360.0f*(angle))/((1<<18)-1)
#define INC_ANGLE_TO_DEG( angle )   (360.0f*(angle))/(1<<18)

#define VALUE_TO_ABS_ANGLE( val )   (quint32)( (val) * ((1<<18)-1) / 360.0f )
#define VALUE_TO_INC_ANGLE( val )   (quint32)( (val) * ((1<<18)) / 360.0f )

#define pnVALUE_TO_ABS_ANGLE( val )   (qint32)( (val) * ((1<<18)-1) / 360.0f )

namespace mrx_t4 {

Config::Config(QWidget *parent) :
    XPage(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);

    setContextHelp("config");

    spyEdited();

    set_page_rstable();

    //! \note to the first page
    ui->tabWidget->setCurrentIndex( 0 );

    //! deg
    ui->spinZero0->setSuffix( char_deg );
    ui->spinZero1->setSuffix( char_deg );
    ui->spinZero2->setSuffix( char_deg );
    ui->spinZero3->setSuffix( char_deg );

    ui->spinL0->setSuffix( char_deg );
    ui->spinL1->setSuffix( char_deg );
    ui->spinL2->setSuffix( char_deg );
    ui->spinL3->setSuffix( char_deg );

    ui->spinU0->setSuffix( char_deg );
    ui->spinU1->setSuffix( char_deg );
    ui->spinU2->setSuffix( char_deg );
    ui->spinU3->setSuffix( char_deg );

}

Config::~Config()
{
    delete ui;
}

void Config::setOperAble( bool b )
{
    //! for each page operate able
    setOpened( b );

}
void Config::setOpened( bool b )
{
    //! for each page operate
    for ( int i = 0; i < ui->tabWidget->count(); i++ )
    {
        ui->tabWidget->widget(i)->setEnabled( b );
    }
}

void Config::adapteToUserMode( sysPara::eSysMode mode )
{
//    XPage::adapteToUserMode( mode );

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

    //! slow
    ui->spinMult->setValue( selfPara->mSlowMult );
    ui->spinDiv->setValue( selfPara->mSlowDiv );
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

    selfPara->mSlowMult = ui->spinMult->value();
    selfPara->mSlowDiv = ui->spinDiv->value();
}

int Config::upload()
{
    check_connect_ret( -1 );

    int ret, val;
    double angle;

    //! get zero
    QList<QDoubleSpinBox*> spins;
    spins<<ui->spinZero0<<ui->spinZero1<<ui->spinZero2<<ui->spinZero3;
    for ( int i = 0; i < 4; i++ )
    {
        ret = mrgMRQAbsEncoderZeroValue_Query( device_var(),
                                                i,
                                                &val );
        if ( ret != 0 )
        { return -1; }

        //! convert the value
        angle = ABS_ANGLE_TO_DEG( val );
        spins[i]->setValue( angle );
    }

    //! limit
    QList<QDoubleSpinBox*> downSpins, upSpins;
    downSpins<<ui->spinL0<<ui->spinL1<<ui->spinL2<<ui->spinL3;
    upSpins<<ui->spinU0<<ui->spinU1<<ui->spinU2<<ui->spinU3;
    for ( int i = 0; i < 4; i++ )
    {
        //! down
        mrgMRQAbsEncoderAlarmDownLimit_Query( device_var(),
                                        i,
                                        &val );
        if ( ret != 0 )
        { return -1; }

        //! convert the value
        angle = ABS_ANGLE_TO_DEG( val );
        downSpins[i]->setValue( angle );

        //! up
        mrgMRQAbsEncoderAlarmUpLimit_Query( device_var(),
                                        i,
                                        &val );
        if ( ret != 0 )
        { return -1; }

        //! convert the value
        angle = ABS_ANGLE_TO_DEG( val );
        upSpins[i]->setValue( angle );
    }

    //! arm length
    //! \todo
    float link[5];
    int linkCnt;
    ret = mrgGetRobotLinks( robot_var(), link, &linkCnt );
    if ( ret != 0 )
    { logDbg(); return -1; }

    ui->spinBase->setValue( link[0] );
    ui->spinBA->setValue( link[1] );
    ui->spinLA->setValue( link[2] );

    //! slow ratio
    int a, b;
    char type[1]={0};
    //int ret = mrgRobotGetToolType(device_var(), type);
    if( int(type[0]) == TERMINAL_TYPE::USER ){
        ret = mrgMRQMotorGearRatio_Query( device_var(),
                                    4,
                                    &a, &b );
        if ( ret == 0 )
        {
            ui->spinMult->setValue( a );
            ui->spinDiv->setValue( b );
            ui->gpSlow->setVisible( true );
        }else{
            return ret;
        }
    }else{
        ui->gpSlow->setVisible( false );
    }

    return 0;
}
int Config::download()
{
    check_connect_ret( -1 );

    int ret, val;
    double angle;

    //! set terminal
    int type = ui->cmbTypeTerminal->currentIndex();

    char t[4] = {0};
    itoa(robot_var_handle(), t, 10);

    QByteArray baStr("4@");
    baStr.append(t);
    ret = mrgRobotToolSet( robot_var(), type, baStr.data());
    if(ret != 0){
        return -1;
    }
    //! set zero
    QList<QDoubleSpinBox*> spins;
    spins<<ui->spinZero0<<ui->spinZero1<<ui->spinZero2<<ui->spinZero3;
    for ( int i = 0; i < 4; i++ )
    {
        angle = spins[i]->value();

        //! convert the value
        val = VALUE_TO_ABS_ANGLE( angle );

        ret = mrgMRQAbsEncoderZeroValue( device_var(),
                                                i,
                                                val );
logDbg();        if ( ret != 0 )
        { return -1; }
    }

    //! limit
    QList<QDoubleSpinBox*> downSpins, upSpins;
    downSpins<<ui->spinL0<<ui->spinL1<<ui->spinL2<<ui->spinL3;
    upSpins<<ui->spinU0<<ui->spinU1<<ui->spinU2<<ui->spinU3;
    for ( int i = 0; i < 4; i++ )
    {
        //! down
        angle = downSpins[i]->value();
        val = pnVALUE_TO_ABS_ANGLE( angle );

        mrgMRQAbsEncoderAlarmDownLimit( device_var(),
                                        i,
                                        val );
        if ( ret != 0 )
        { return -1; }

        //! up
        angle = upSpins[i]->value();
        val = pnVALUE_TO_ABS_ANGLE( angle );

        mrgMRQAbsEncoderAlarmUpLimit( device_var(),
                                        i,
                                        val );
        if ( ret != 0 )
        { return -1; }
    }

    //! arm length
    float links[]={
                    (float)ui->spinBase->value(),
                    (float)ui->spinBA->value(),
                    (float)ui->spinLA->value()
                };
    ret = mrgSetRobotLinks( robot_var(), links, 3 );
    if ( ret != 0 )
    { return -1; }

    return 0;
}
int Config::diff()
{
    return 0;
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
        ui->spinMult,
        ui->spinDiv
    };

    QDoubleSpinBox *doubleSpinBoxes[]={
        ui->spinBase,
        ui->spinBA,
        ui->spinLA,

        ui->spinZero0,
        ui->spinZero1,
        ui->spinZero2,
        ui->spinZero3,

        ui->spinL0,ui->spinU0,
        ui->spinL1,ui->spinU1,
        ui->spinL2,ui->spinU2,
        ui->spinL3,ui->spinU3,
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
{logDbg();
    QIcon icon = ui->cmbTypeTerminal->itemIcon( index );
    if ( icon.isNull() )
    {
        ui->labelTerminalImg->setVisible( false );
        ui->gpSlow->setVisible( false );
    }
    else
    {
        ui->labelTerminalImg->setPixmap( icon.pixmap( 160,160 ) );
        ui->labelTerminalImg->setVisible( true );
        if( index == TERMINAL_TYPE::USER ){
            ui->gpSlow->setVisible( true );
        }else{
            ui->gpSlow->setVisible( false );
        }
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
