#include "xconfig.h"

XConfig::XConfig(QWidget *parent) : QWidget(parent)
{
    mViHandle = 0;
    setFocusPolicy( Qt::StrongFocus );
}

void XConfig::setName( const QString &name )
{ mName = name; }
QString XConfig::name()
{ return mName; }

int XConfig::readDeviceConfig()
{ return 0; }

int XConfig::writeDeviceConfig()
{ return 0; }

int XConfig::loadConfig()
{ return 0; }

int XConfig::saveConfig()
{ return 0; }

void XConfig::updateShow()
{}

int XConfig::attachHandle(int handle , int deviceName, int robotName)
{
    mViHandle = handle;
    mDeviceName = deviceName;
    mRobotName = robotName;
    return 0;
}

int XConfig::detachHandle()
{
    mViHandle = 0;
    mDeviceName = 0;
    mRobotName = 0;
    return 0;
}

void XConfig::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent( event );
    emit signal_focus_in( mName );
}

void XConfig::setProjectName(const QString &projectName)
{
    mProjectName = projectName;
}
