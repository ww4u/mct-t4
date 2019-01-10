#include "actiontable.h"
#include "ui_actiontable.h"

namespace mrx_t4 {

ActionTable::ActionTable(QWidget *parent) :
    XPage(parent),
    ui(new Ui::ActionTable)
{
    ui->setupUi(this);
}

ActionTable::~ActionTable()
{
    delete ui;
}

}
