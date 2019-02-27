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

    install_spy();
}

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
