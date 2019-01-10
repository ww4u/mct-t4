#include "xpage.h"

XPage::XPage(QWidget *parent) : QWidget(parent)
{
    m_pPlugin = NULL;
}

void XPage::attachPlugin( XPlugin *pPlugin )
{
    Q_ASSERT( NULL != pPlugin );

    m_pPlugin = pPlugin;
}
XPlugin *XPage::pulgin()
{ return m_pPlugin; }
