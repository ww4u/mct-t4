#include "welcomepage.h"
#include "ui_welcomepage.h"

WelcomePage::WelcomePage(QWidget *parent) :
    XPage(parent),
    ui(new Ui::WelcomePage)
{
    ui->setupUi(this);
}

WelcomePage::~WelcomePage()
{
    delete ui;
}
