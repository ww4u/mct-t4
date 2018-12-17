
#include <QApplication>
#include "../source/wnd/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //解决中文字符乱码的问题，使用下面转化方式
    //! QString->char * ==> str.toLocal8Bit().data()
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

#if 0
    QString path = "D:/share/release/MCT-史蒂夫/dataset/action_default.mrp";
    FILE *pFile = NULL;
    pFile = _wfopen( reinterpret_cast<const wchar_t *>( path.utf16() ) ,
                     reinterpret_cast<const wchar_t *>( QString("r").utf16() ));

    if (pFile == NULL)
    {
        perror("111111");
        qDebug() << "fopen error";
        return -1;
    }
    else{
        qDebug() << "fopen ok";
    }
#endif

    MainWindow w;
#ifdef _WIN32
    w.showNormal();
#else
    w.showFullScreen();
#endif
    return a.exec();
}



