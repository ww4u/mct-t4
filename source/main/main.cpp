
#include <QApplication>
#include "../source/wnd/mainwindow.h"


//#define MCTVERSION "0.0.1.4"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! --splash
    QPixmap pixmap( ":res/image/image/full.png" );
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage( a.applicationVersion() );
    a.processEvents();

    //! 解决中文字符乱码的问题，使用下面转化方式
    //! QString->char * ==> str.toLocal8Bit().data()
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    MainWindow w;

    //! process
    a.processEvents();

    splash.hide();

    w.show();

    return a.exec();
}



