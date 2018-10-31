#ifndef H2ERRMGR_H
#define H2ERRMGR_H

#include <QWidget>
#include "../model/comboxdelegate.h"
#include "../model/errmgrmodel.h"

namespace Ui {
class H2ErrMgr;
}

class H2ErrMgr : public QWidget
{
    Q_OBJECT

public:
    explicit H2ErrMgr(QWidget *parent = 0);
    ~H2ErrMgr();

public:
    void setModel( ErrMgrModel *pModel );

private:
    Ui::H2ErrMgr *ui;

    comboxDelegate *m_pErrActionDelegate;
};

#endif // H2ERRMGR_H
