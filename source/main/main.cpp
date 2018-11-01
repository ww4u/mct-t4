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
    QDesktopWidget *desktop=QApplication::desktop();
    w.move((desktop->width()-w.width())/2,(desktop->height()-w.height())/2);
    w.show();

    return a.exec();
}
