#include "xthread.h"
#include <QDebug>

XThread::XThread(QObject *parent)
    : QThread(parent)
{
    m_func = nullptr;
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
//    this->exec();
}


XThread::XThread(std::function<void(void)> func, QObject *parent)
    : QThread(parent)
{
    m_func = func;
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}


void XThread::run()
{
    if (m_func != nullptr)
        m_func();
}

void XThread::setCallback(std::function<void(void)> func)
{
    m_func = func;
}


//! eg应用事例
#if 0
auto func1 = [&](){
    qDebug() << "Thread1";
};

XThread *thread1 = new XThread;
thread1->setCallback(func1);
thread1->start();

auto func2 = [&](){
    qDebug() << "Thread1";
};

XThread *thread2 = new XThread(func2);
thread2->start();
#endif
