#ifndef XPLUGIN_H
#define XPLUGIN_H

#include <QObject>
#include <QStackedWidget>
#include <QTreeWidgetItem>

class XPlugin : public QObject
{
    Q_OBJECT

public:
    XPlugin( QObject *parent = nullptr );

public:
    virtual QTreeWidgetItem* createPrefPages( QStackedWidget *stack );
    virtual QWidget *createOpsPanel( QWidget *parent=nullptr );
};

#endif
