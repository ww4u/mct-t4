#include "controllerstatus.h"
#include "ui_controllerstatus.h"


ControllerStatus::ControllerStatus(QWidget *parent) :
    XPage(parent),
    ui(new Ui::ControllerStatus)
{
    ui->setupUi(this);

    //! connect ui
    connect( ui->chkMct,SIGNAL(toggled(bool)),
             this, SIGNAL(signal_mct_checked(bool)) );
    connect( ui->chkPwr,SIGNAL(toggled(bool)),
             this, SIGNAL(signal_device_power(bool)));
    connect( ui->btnAckError, SIGNAL(clicked(bool)),
             this, SIGNAL(signal_ack_error()) );

    spyEdited();

    //! debug
    ui->radEn->setChecked( true );
    ui->radError->setChecked( true );
    ui->radWarning->setChecked( true );
    ui->radReady->setChecked( true );

    ui->radMc->setChecked( true );
    ui->radTo->setChecked( true );

    IoIndicatorList << ui->radEn << ui->radTo << ui->radReady << ui->radMc << ui->radError << ui->radWarning;
}

ControllerStatus::~ControllerStatus()
{
    delete ui;
}

void ControllerStatus::spyEdited()
{
    QGroupBox *gpBox[]=
    {
    };
    QCheckBox *checkBoxes[]=
    {
        ui->chkMct,
        ui->chkPwr
    };
    QRadioButton *radBoxes[] = {
    };
    QLineEdit *edits[]={

    };

    QSpinBox *spinBoxes[]={

    };

    QDoubleSpinBox *doubleSpinBoxes[]={


    };

    QComboBox *comboxes[]={

    };

    QSlider *sliders[]
    {
    };

    install_spy();
}

void ControllerStatus::retranslateUi()
{
    //! base
    ui->retranslateUi( this );

    ui->radEn->setText( tr("Enable") );
    ui->radReady->setText( tr("Ready") );
    ui->radError->setText( tr("Error") );
    ui->radMc->setText( tr("MC") );

    ui->radTo->setText( tr("TO") );
    ui->radWarning->setText( tr("Warning") );
}

void ControllerStatus::setOut( SysOut e, bool b )
{}
void ControllerStatus::setWorkingMode( const QString &mode )
{ ui->edtOpMode->setText( mode ); }
void ControllerStatus::setWarning( const QString &warning )
{ ui->edtWarning->setText( warning ); }
void ControllerStatus::setError( const QString &error )
{ ui->edtError->setText( error ); }

void ControllerStatus::setRole( int role )
{
    if ( role == 0 )
    {
        ui->labRole->setText( tr("Operator") );
    }
    else
    {
        ui->labRole->setText( tr("Administrator") );
    }
}
void ControllerStatus::setWorkingStatus( const QString &status )
{ ui->labWorkingStatus->setText( status );}
void ControllerStatus::setRecordName( const QString &name )
{ ui->labReccordName->setText( name ); }

void ControllerStatus::setMctChecked( bool b )
{ ui->chkMct->setChecked( b ); }
bool ControllerStatus::isMctChecked()
{ return ui->chkMct->isChecked(); }

void ControllerStatus::setDevicePower( bool b )
{ ui->chkPwr->setChecked( b ); }
bool ControllerStatus::getDevicePower()
{ return ui->chkPwr->isChecked(); }

void ControllerStatus::setDevicePowerEnable( bool b )
{ ui->chkPwr->setEnabled( b ); }
bool ControllerStatus::isDevicePowerEnable()
{ return ui->chkPwr->isEnabled(); }

void ControllerStatus::setDeviceStatCheck(int index, bool b)
{
    IoIndicatorList.at(index)->setChecked(b);
}
