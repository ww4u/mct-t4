#include "../source/wnd/mainwindow.h"
#include <QApplication>
#include <QFile>

class CommonHelper
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! style
    if ( QFile::exists(a.applicationDirPath() + "/style" + "/mega.qss") )
    { CommonHelper::setStyle( a.applicationDirPath() + "/style" + "/mega.qss" ); }
    else
    { CommonHelper::setStyle( ":/res/qss/mega.qss" ); }

    MainWindow w;
    w.showMaximized();

    return a.exec();

#if 0
    QSettings settings("E:\megaRobo.ini", QSettings::IniFormat);
    //write
    settings.beginGroup("GPS");
    settings.setValue("gpsBaud", 4800);
    settings.setValue("gpsPort", "com7");
    settings.endGroup();

    if(settings.contains("GPS/gpsBaud"))
    {
        QString gpsBaud = settings.value("GPS/gpsBaud").toString();
        QString gpsPort = settings.value("GPS/gpsPort").toString();
        qDebug() << gpsBaud << gpsPort;
    }

#endif


}
