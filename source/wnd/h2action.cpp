
#include "h2action.h"
#include "ui_h2action.h"

H2Action::H2Action(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Action)
{
    ui->setupUi(this);

    setName( "action" );

    m_pDelegate1 = new comboxDelegate(this);
    QStringList prxs;
    prxs<<tr("PA")<<tr("PRN")<<tr("PRA");
    m_pDelegate1->setItems( prxs );
}

H2Action::~H2Action()
{
    delete ui;
}

int H2Action::setApply(ViSession vi)
{
    qDebug() << "H2Action:" << vi;
    return 0;
}

void H2Action::setModel( QAbstractTableModel *pModel )
{
    ui->tableView->setModel( pModel );

    ui->tableView->setItemDelegateForColumn( 0, m_pDelegate1 );
}
