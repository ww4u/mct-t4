
#define TOOLVERION "0.0.0.3"

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



