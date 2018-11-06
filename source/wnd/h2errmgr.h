#ifndef H2ERRMGR_H
#define H2ERRMGR_H

#include <QWidget>
#include "xconfig.h"
#include "../model/comboxdelegate.h"
#include "../model/checkdelegate.h"
#include "../model/errmgrmodel.h"

namespace Ui {
class H2ErrMgr;
}

class H2ErrMgr : public XConfig
{
    Q_OBJECT

public:
    explicit H2ErrMgr(QWidget *parent = 0);
    ~H2ErrMgr();
    int setApply(ViSession vi);

public:
    void setModel( ErrMgrModel *pModel );

private:
    Ui::H2ErrMgr *ui;

    checkDelegate *m_pCheckDelegate;
    checkDelegate *m_pRadioDelegate;

    comboxDelegate *m_pErrActionDelegate;
};

#endif // H2ERRMGR_H
