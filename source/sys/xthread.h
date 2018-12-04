#ifndef XTHREAD_H
#define XTHREAD_H

#include <QThread>
#include <functional>

class XThread : public QThread
{
    Q_OBJECT
public:
    XThread(QObject *parent = NULL);
    XThread(std::function<void(void)> func, QObject *parent = NULL);
    ~XThread(){}

public:
    void setCallback(std::function<void(void)> func);

protected:
    virtual void run();

private:
     std::function<void(void)> m_func;
};


#endif // XTHREAD_H
