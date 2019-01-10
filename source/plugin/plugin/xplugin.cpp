#include "xplugin.h"


XPlugin::XPlugin( QObject *parent ) : QObject( parent )
//XPlugin::XPlugin( QObject *parent )
{

}

QTreeWidgetItem* XPlugin::createPrefPages( QStackedWidget *stack )
{ return NULL; }
QWidget *XPlugin::createOpsPanel( QWidget *parent )
{ return NULL; }
