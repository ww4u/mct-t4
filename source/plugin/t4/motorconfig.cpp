#include "motorconfig.h"
#include "ui_motorconfig.h"

namespace mrx_t4 {

MotorConfig::MotorConfig(QWidget *parent) :
    XPage(parent),
    ui(new Ui::MotorConfig)
{
    ui->setupUi(this);
}

MotorConfig::~MotorConfig()
{
    delete ui;
}

}
