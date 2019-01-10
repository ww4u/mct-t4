#include "t4oppanel.h"
#include "ui_t4oppanel.h"

namespace mrx_t4{

T4OpPanel::T4OpPanel(QWidget *parent) :
    XPage(parent),
    ui(new Ui::T4OpPanel)
{
    ui->setupUi(this);
}

T4OpPanel::~T4OpPanel()
{
    delete ui;
}

}
