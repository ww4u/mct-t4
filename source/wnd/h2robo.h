#ifndef H2ROBO_H
#define H2ROBO_H

#include <QTreeWidgetItem>
#include "xrobo.h"

#include "../include/mystd.h"

#include "xconfig.h"

#include "../model/h2actionmodel.h"
#include "../model/errmgrmodel.h"

#include "h2product.h"
#include "h2configuration.h"
#include "h2jogmode.h"
#include "h2homing.h"
#include "h2measurement.h"
#include "h2action.h"
#include "h2errmgr.h"

class H2Robo : public XRobo
{
    Q_OBJECT

public:
    H2Robo( QStackedWidget *pWig, QString strDevInfo = "", QObject *pObj = Q_NULLPTR );

public:
    QTreeWidgetItem *roboNode();

    H2Product *pProduct() const;
    QList<XConfig *> subConfigs() const;

protected:
    int loadDataSet();
    void buildConnection();

signals:
    void signal_online_request(QString);

private:
    H2ActionModel mActions;
    ErrMgrModel mErrManager;
    H2Product *m_pProduct;
    QList<XConfig*> mSubConfigs;
    QTreeWidgetItem *m_pRoboNode;
};

#endif // H2ROBO_H
