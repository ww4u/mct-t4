
#include <QApplication>
#include <QFile>

#include "../source/wnd/mainwindow.h"

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
}



