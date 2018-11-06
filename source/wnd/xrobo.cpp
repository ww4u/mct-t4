#include "xrobo.h"

XRobo::XRobo( QStackedWidget *pWig, QObject *parent) : QObject(parent)
{

}

void XRobo::setAddr( const QString &addr )
{ mAddr = addr; }
QString XRobo::addr()
{ return mAddr; }
