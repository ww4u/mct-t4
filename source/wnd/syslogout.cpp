#include "syslogout.h"
#include "ui_syslogout.h"

SysLogout::SysLogout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SysLogout)
{
    ui->setupUi(this);
}

SysLogout::~SysLogout()
{
    delete ui;
}

void SysLogout::attachLogModel( QAbstractListModel *pModel )
{
    Q_ASSERT( NULL != pModel );

    ui->listView->setModel( pModel );
}
