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
    CommonHelper::setStyle( a.applicationDirPath() + "/style" + "/mega.qss" );

    MainWindow w;
    w.show();

    return a.exec();
}
