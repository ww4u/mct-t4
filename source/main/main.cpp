
#define TOOLVERION "0.0.1.0"

#include <QApplication>
#include "../source/wnd/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationVersion(TOOLVERION);
    MainWindow w;
    w.showNormal();
    return a.exec();
}



