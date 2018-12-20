
#include <QApplication>
#include "../source/wnd/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //解决中文字符乱码的问题，使用下面转化方式
    //! QString->char * ==> str.toLocal8Bit().data()
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    MainWindow w;
#ifdef _WIN32
    w.showNormal();
//    w.showMaximized();
#else
    w.showFullScreen();
#endif
    return a.exec();
}



