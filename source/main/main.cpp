
#include <QApplication>
#include "../source/wnd/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! style
//    if ( QFile::exists(a.applicationDirPath() + "/style/mega.qss") )
//    { MainWindow::setUiStyle( a.applicationDirPath() + "/style/mega.qss" ); }
//    else
//    { MainWindow::setUiStyle( ":/res/qss/mega.qss" ); }

    MainWindow w;
    w.showMaximized();

    return a.exec();
}



