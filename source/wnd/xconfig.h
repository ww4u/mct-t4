#ifndef XCONFIG_H
#define XCONFIG_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>

#include "lanfinddevice.h"
#include "visa.h"
#include "mrht.h"

class XConfig : public QWidget
{
    Q_OBJECT
public:
    explicit XConfig(QWidget *parent = nullptr);

public:
    void setName( const QString &name );
    QString name();

public:
    virtual int setApply();
    int attachHandle( int handle, int robotName);
    int detachHandle();

protected:
    virtual void focusInEvent(QFocusEvent *event);

signals:
    void signal_focus_in( const QString &name );

protected:
    QString mName;
    int mViHandle;
    int mRobotName;
};

#endif // XCONFIG_H
