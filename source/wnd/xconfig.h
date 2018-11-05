#ifndef XCONFIG_H
#define XCONFIG_H

#include <QWidget>
#include "visa.h"

class XConfig : public QWidget
{
    Q_OBJECT
public:
    explicit XConfig(QWidget *parent = nullptr);

public:
    void setName( const QString &name );
    QString name();

public:
    virtual int setApply( ViSession vi );

protected:
    virtual void focusInEvent(QFocusEvent *event);

signals:
    void signal_focus_in( const QString &name );

public slots:

protected:
    QString mName;
};

#endif // XCONFIG_H
