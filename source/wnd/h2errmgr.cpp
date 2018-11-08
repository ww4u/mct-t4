#include "h2errmgr.h"
#include "ui_h2errmgr.h"

H2ErrMgr::H2ErrMgr(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2ErrMgr)
{
    ui->setupUi(this);

    setName( "error_mgr" );

    //! delegate
    m_pCheckDelegate = new checkDelegate( shape_check, this );
    m_pRadioDelegate = new checkDelegate( shape_radio, this );
    m_pErrActionDelegate = new comboxDelegate( this );

    //! opt
    QStringList errActions;
    errActions<<tr("Free-wheeling")
              <<tr("QS deceleration")
              <<tr("Record deceleration")
              <<tr("Finish Record");
    m_pErrActionDelegate->setItems( errActions );

    ui->tvErr->setItemDelegateForColumn( 2, m_pRadioDelegate );
    ui->tvErr->setItemDelegateForColumn( 3, m_pRadioDelegate );
    ui->tvErr->setItemDelegateForColumn( 4, m_pRadioDelegate );

    ui->tvErr->setItemDelegateForColumn( 5, m_pErrActionDelegate );

    ui->tvErr->setItemDelegateForColumn( 6, m_pCheckDelegate );
    ui->tvErr->setItemDelegateForColumn( 7, m_pCheckDelegate );

}

H2ErrMgr::~H2ErrMgr()
{
    delete ui;

}

int H2ErrMgr::setApply()
{
//    qDebug() << "H2ErrMgr:" << mViHandle;
    return 0;
}

void H2ErrMgr::setModel( ErrMgrModel *pModel )
{
    Q_ASSERT( NULL != pModel );

    ui->tvErr->setModel( pModel );
}
