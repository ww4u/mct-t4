#ifndef XROBO_H
#define XROBO_H

#include <QObject>
#include <QStackedWidget>
class XRobo : public QObject
{
    Q_OBJECT
public:
    explicit XRobo( QStackedWidget *pWig, QObject *parent = nullptr);

public:
    QString addr() const;
    void setAddr(const QString &addr);

protected:
    QString m_addr;
};

#endif // XROBO_H
