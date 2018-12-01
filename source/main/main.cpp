
#include <QApplication>
#include "../source/wnd/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.showNormal();
    return a.exec();
}



