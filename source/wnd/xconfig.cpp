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

int XConfig::setApply()
{ return 0; }

void XConfig::loadXmlConfig()
{}

void XConfig::slotOnModelChanged()
{}

int XConfig::attachHandle(int handle , int robotName)
{
    mViHandle = handle;
    mRobotName = robotName;
    return 0;
}

int XConfig::detachHandle()
{
    mViHandle = 0;
    return 0;
}

void XConfig::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent( event );
    emit signal_focus_in( mName );
}

QString XConfig::projectName() const
{
    return mProjectName;
}

void XConfig::setProjectName(const QString &projectName)
{
    mProjectName = projectName;
}
