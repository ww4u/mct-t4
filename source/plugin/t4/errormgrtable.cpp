#include "errormgrtable.h"
#include "ui_errormgrtable.h"

namespace mrx_t4 {

ErrorMgrTable::ErrorMgrTable(QWidget *parent) :
    XPage(parent),
    ui(new Ui::ErrorMgrTable)
{
    ui->setupUi(this);
}

ErrorMgrTable::~ErrorMgrTable()
{
    delete ui;
}

}
