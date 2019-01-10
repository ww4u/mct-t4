#include "t4.h"
#include <QTreeWidgetItem>

#include "t4oppanel.h"
#include "config.h"
#include "motorconfig.h"
#include "traceplot.h"
#include "actiontable.h"
#include "errormgrtable.h"

MRX_T4::MRX_T4( QObject *parent ) : XPlugin( parent )
{

}

#define new_widget( type, var, txt, icon ) \
do{ \
    var = new type;\
    Q_ASSERT( NULL != var ); \
    QTreeWidgetItem *plwItem = new QTreeWidgetItem();   \
    Q_ASSERT( NULL != plwItem ); \
    plwItem->setIcon( 0, QIcon( icon) ); \
    plwItem->setText( 0, tr(txt) ); \
    plwItem->setData( 0, Qt::UserRole, QVariant( QVariant::fromValue(var) ) ); \
    pRoot->addChild(plwItem); \
    stack->addWidget( var );     \
}while(0)

QTreeWidgetItem* MRX_T4::createPrefPages( QStackedWidget *stack )
{
    QTreeWidgetItem *pRoot = new QTreeWidgetItem();
    pRoot->setText( 0, "mrx-t4" );
    QWidget *pWig;

    new_widget( mrx_t4::Config, pWig, "Config", ":/res/image/icon/205.png" );
    new_widget( mrx_t4::MotorConfig, pWig, "Motor", ":/res/image/icon/205.png" );
    new_widget( mrx_t4::ActionTable, pWig, "Record", ":/res/image/icon/205.png" );
    new_widget( mrx_t4::ErrorMgrTable, pWig, "Error", ":/res/image/icon/205.png" );
    new_widget( mrx_t4::TracePlot, pWig, "Trace", ":/res/image/icon/205.png" );

    return pRoot;
}
QWidget *MRX_T4::createOpsPanel( QWidget *parent )
{
    return new mrx_t4::T4OpPanel( parent );
}
