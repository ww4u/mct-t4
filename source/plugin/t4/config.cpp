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

#define set_zero( id )  ui->spinZero##id->setValue( selfPara->mAxisZero[id] );

#define get_zero( id )  selfPara->mAxisZero[id] = ui->spinZero##id->value();

void Config::updateUi()
{
    //! set type
    ui->cmbTypeTerminal->setCurrentIndex( (int)selfPara->mTerminalType );
    on_cmbTypeTerminal_currentIndexChanged( ui->cmbTypeTerminal->currentIndex() );
logDbg()<<selfPara->mAxisZero[0];
    //! zero
//    ui->spinZero0->setValue( selfPara->mAxisZero[0] );
    set_zero( 0 );
    set_zero( 1 );
    set_zero( 2 );
    set_zero( 3 )

    //! range
    ui->lmtSafeArea->setLimitOn( selfPara->mbAxisSafeEnable );
    ui->lmtSoftLimit->setLimitOn( selfPara->mbAxisSoftEnable );
    for ( int i = 0; i < selfPara->_limit_axis_cnt; i++ )
    {
        ui->lmtSafeArea->setRange( i, selfPara->mAxisSafeLower[i], selfPara->mAxisSafeUpper[i] );
        ui->lmtSoftLimit->setRange( i, selfPara->mAxisSoftLower[i], selfPara->mAxisSoftUpper[i] );
    }

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
    double h, l;
    int ret;
    selfPara->mbAxisSafeEnable = ui->lmtSafeArea->limitOn();
    selfPara->mbAxisSoftEnable = ui->lmtSoftLimit->limitOn();
    for ( int i; i < selfPara->_limit_axis_cnt ; i++ )
    {
        ret = ui->lmtSafeArea->range( i, l, h);
        if ( ret != 0 )
        { continue; }
        selfPara->mAxisSafeLower[ i ] = l;
        selfPara->mAxisSafeUpper[ i ] = h;

        ret = ui->lmtSoftLimit->range( i, l, h );
        if ( ret != 0 )
        { continue; }
        selfPara->mAxisSoftLower[ i ] = l;
        selfPara->mAxisSoftUpper[ i ] = h;
    }

    //! ratio
    selfPara->mSlowMult = ui->spinMult->value();
    selfPara->mSlowDiv = ui->spinDiv->value();
}

int Config::upload()
{
    check_connect_ret( -1 );

    int ret, val;
    double angle;

    //! get zero
//    QList<QDoubleSpinBox*> spins;
//    spins<<ui->spinZero0<<ui->spinZero1<<ui->spinZero2<<ui->spinZero3;
    for ( int i = 0; i < 4; i++ )
    {
        ret = mrgMRQAbsEncoderZeroValue_Query( device_var(),
                                                i,
                                                &val );
        if ( ret != 0 )
        { return -1; }

        //! convert the value
        angle = ABS_ANGLE_TO_DEG( val );
//        spins[i]->setValue( angle );
        selfPara->mAxisZero[i] = angle;
    }

    //! limit
    double lmtL, lmtH;
    int lmtOnOff;
    bool lmtsOnOff = true;
    for ( int i = 0; i < 4; i++ )
    {
        //! down
        ret = mrgMRQAbsEncoderAlarmDownLimit_Query( device_var(),
                                        i,
                                        &val );
        if ( ret != 0 )
        { return -1; }

        //! convert the value
        lmtL = ABS_ANGLE_TO_DEG( val );

        //! up
        ret = mrgMRQAbsEncoderAlarmUpLimit_Query( device_var(),
                                        i,
                                        &val );
        if ( ret != 0 )
        { return -1; }

        //! convert the value
        lmtH = ABS_ANGLE_TO_DEG( val );

//        ui->lmtSoftLimit->setRange( i, lmtL, lmtH );

        selfPara->mAxisSoftLower[i] = lmtL;
        selfPara->mAxisSoftUpper[i] = lmtH;

        ret = mrgMRQAbsEncoderAlarmState_Query( device_var(), i, &lmtOnOff );
        if ( ret != 0 )
        { return ret; }

        lmtsOnOff = lmtsOnOff && (lmtOnOff > 0 );
    }
    selfPara->mbAxisSoftEnable = lmtsOnOff;

    //! \todo safe area


    //! arm length
    //! \todo
    float link[5];
    int linkCnt;
    ret = mrgGetRobotLinks( robot_var(), link, &linkCnt );
    if ( ret != 0 )
    { logDbg(); return -1; }

//    ui->spinBase->setValue( link[0] );
//    ui->spinBA->setValue( link[1] );
//    ui->spinLA->setValue( link[2] );

    for ( int al = 0; al < 3; al++ )
    {
        selfPara->mArmLength[al] = link[al];
    }

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
//            ui->spinMult->setValue( a );
//            ui->spinDiv->setValue( b );
//            ui->gpSlow->setVisible( true );

            selfPara->mSlowMult = a;
            selfPara->mSlowDiv = b;

        }else{
            return ret;
        }
    }else{
//        ui->gpSlow->setVisible( false );
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

    QString baStr = QString("4@%1").arg( robot_var_handle() );
    ret = mrgRobotToolSet( robot_var(), type, baStr.toLatin1().data() );
    if(ret != 0){
        return -1;
    }
    //! set zero
    if( ui->tabZero->isEnabled() )
    {
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
            if ( ret != 0 )
            { return -1; }
        }
    }

    //! limit
    if ( ui->tabSoftLimit->isEnabled() )
    {
        double lmtL, lmtH;
        for ( int i = 0; i < 4; i++ )
        {
            ret = ui->lmtSoftLimit->range( i, lmtL, lmtH );
            if ( ret != 0 )
            { return -1; }

            //! down
            val = pnVALUE_TO_ABS_ANGLE( lmtL );

            ret = mrgMRQAbsEncoderAlarmDownLimit( device_var(),
                                            i,
                                            val );
            if ( ret != 0 )
            { return -1; }

            //! up
            val = pnVALUE_TO_ABS_ANGLE( lmtH );

            ret = mrgMRQAbsEncoderAlarmUpLimit( device_var(),
                                            i,
                                            val );
            if ( ret != 0 )
            { return -1; }

            //! on off
            ret = mrgMRQAbsEncoderAlarmState( device_var(), i, ui->lmtSoftLimit->limitOn() );
        }
    }

    //! \todo soft area

    //! arm length
    if ( ui->tabArm->isEnabled() )
    {
        float links[]={
                    (float)ui->spinBase->value(),
                    (float)ui->spinBA->value(),
                    (float)ui->spinLA->value()
                };
        ret = mrgSetRobotLinks( robot_var(), links, 3 );
        if ( ret != 0 )
        { return -1; }
    }

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

void Config::updateRole()
{
    bool bEditable = sysMode() == sysPara::e_sys_admin;

    ui->tabZero->setEnabled( bEditable );
    ui->tabSoftLimit->setEnabled( bEditable );
    ui->tabArm->setEnabled( bEditable );
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
