#include "xconfig.h"

XConfig::XConfig(QWidget *parent) : QWidget(parent)
{
    mViHandle = 0;
    setFocusPolicy( Qt::StrongFocus );
}

QString XConfig::focuHelpName() const
{
    return mFocuHelpName;
}
void XConfig::setFocuHelpName(const QString &focusName)
{
    mFocuHelpName = focusName;
}

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

void XConfig::changeLanguage(QString qmFile)
{
    //  翻译文件
    qApp->removeTranslator(&m_translator);
    m_translator.load(qmFile);
    qApp->installTranslator(&m_translator);

    translateUI();
}

void XConfig::translateUI()
{
//    ui->retranslateUi(this);
}

int XConfig::attachHandle(int vihandle , int deviceName, int robotName)
{
    mViHandle = vihandle;
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
    emit signal_focus_in( mFocuHelpName );
}

void XConfig::setConfigFileName(const QString &projectName)
{
    mConfigFileName = projectName;
}
