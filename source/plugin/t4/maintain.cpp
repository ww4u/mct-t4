#include "maintain.h"
#include "ui_maintain.h"
namespace mrx_t4 {
Maintain::Maintain(QWidget *parent) :
    XPage(parent),
    ui(new Ui::Maintain)
{
    ui->setupUi(this);

    setContextHelp("maintain");
}

Maintain::~Maintain()
{
    delete ui;
}

}
