#ifndef MRX_T4_H
#define MRX_T4_H

#include <QObject>

#include "../plugin/xplugin.h"

class MRX_T4 : public XPlugin
{
    Q_OBJECT

public:
    MRX_T4( QObject *parent = nullptr );

public:
    virtual QTreeWidgetItem* createPrefPages( QStackedWidget *stack );
    virtual QWidget *createOpsPanel( QWidget *parent=nullptr );

};

#endif // T4_H
