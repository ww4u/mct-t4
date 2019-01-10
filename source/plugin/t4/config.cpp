#include "config.h"
#include "ui_config.h"

namespace mrx_t4 {

Config::Config(QWidget *parent) :
    XPage(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);
}

Config::~Config()
{
    delete ui;
}

}
