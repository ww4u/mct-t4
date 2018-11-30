
#include <QApplication>
#include "../source/wnd/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



//    QString str1 = "shi";
//    QString str2 = "zhong";

//    qDebug() << QString("%1,%2").arg(str1, 8, 'x').arg(str2, 8, 'x');


    MainWindow w;
    w.showNormal();
    return a.exec();
}



