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
    void setAddr( const QString &addr );
    QString addr();

signals:
    void signal_focus_in( const QString & );

public slots:

protected:
    QString mAddr;

};

#endif // XROBO_H
