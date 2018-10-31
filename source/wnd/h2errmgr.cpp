#include "h2errmgr.h"
#include "ui_h2errmgr.h"

H2ErrMgr::H2ErrMgr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H2ErrMgr)
{
    ui->setupUi(this);


    //! delegate
    m_pErrActionDelegate = new comboxDelegate( this );

    QStringList errActions;
    errActions<<tr("Free-wheeling")
              <<tr("QS deceleration")
              <<tr("Record deceleration")
              <<tr("Finish Record");
    m_pErrActionDelegate->setItems( errActions );
    ui->tvErr->setItemDelegateForColumn( 5, m_pErrActionDelegate );

}

H2ErrMgr::~H2ErrMgr()
{
    delete ui;

}

void H2ErrMgr::setModel( ErrMgrModel *pModel )
{
    Q_ASSERT( NULL != pModel );

    ui->tvErr->setModel( pModel );
}
