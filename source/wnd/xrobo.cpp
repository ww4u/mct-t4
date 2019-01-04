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

void XRobo::changeLanguage(QString qmFile)
{
    //  翻译文件
    qApp->removeTranslator(&m_translator);
    m_translator.load(qmFile);
    qApp->installTranslator(&m_translator);

    translateUI();
}

void XRobo::translateUI()
{
//    ui->retranslateUi(this);
}
