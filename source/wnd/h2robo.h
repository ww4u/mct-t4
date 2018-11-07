#ifndef H2ROBO_H
#define H2ROBO_H

#include <QTreeWidgetItem>
#include "xrobo.h"

#include "../include/mystd.h"

#include "xconfig.h"

#include "../model/h2actionmodel.h"
#include "../model/errmgrmodel.h"

class H2Robo : public XRobo
{
    Q_OBJECT

public:
    H2Robo( QStackedWidget *pWig, QString strDevInfo = "", QObject *pObj = Q_NULLPTR );

public:
    QTreeWidgetItem *roboNode();

protected:
    int loadDataSet();
    void buildConnection();

protected:
    H2ActionModel mActions;
    ErrMgrModel mErrManager;

    QList<XConfig*> mSubConfigs;

    QTreeWidgetItem *m_pRoboNode;
};

#endif // H2ROBO_H
