#include "xconfig.h"
#include "../include/mystd.h"

XConfig::XConfig(QWidget *parent) : QWidget(parent)
{
    mViHandle = 0;
    setFocusPolicy( Qt::StrongFocus );
}

void XConfig::setName( const QString &name )
{ mName = name; }
QString XConfig::name()
{ return mName; }

int XConfig::setApply( ViSession vi )
{ return 0; }

int XConfig::attachHandle( int handle )
{
    mViHandle = handle;
    return 0;
}

int XConfig::detachHandle( int handle )
{
    //! \todo detach handle
    mViHandle = 0;
    return 0;
}

void XConfig::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent( event );

    emit signal_focus_in( mName );
}
