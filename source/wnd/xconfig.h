#ifndef XCONFIG_H
#define XCONFIG_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>

#include "MegaGateway.h"

#include "megaxml.h"

class XConfig : public QWidget
{
    Q_OBJECT
public:
    explicit XConfig(QWidget *parent = nullptr);

public:
    void setName( const QString &name );
    QString name();

    QString projectName() const;
    void setProjectName(const QString &projectName);

    virtual int setApply();
    virtual void loadXmlConfig();
    virtual void slotOnModelChanged();

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

    QString mProjectName;
};

#endif // XCONFIG_H
