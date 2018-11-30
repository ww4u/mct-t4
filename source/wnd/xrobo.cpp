#include "xrobo.h"

XRobo::XRobo( QStackedWidget *pWig, QObject *parent) : QObject(parent)
{

}

QString XRobo::addr() const
{
    return m_addr;
}

void XRobo::setAddr(const QString &addr)
{
    m_addr = addr;
}
