#ifndef ERRORMGRTABLE_H
#define ERRORMGRTABLE_H

#include <QWidget>

#include "../plugin/xpage.h"

namespace Ui {
class ErrorMgrTable;
}

namespace mrx_t4 {

class ErrorMgrTable : public XPage
{
    Q_OBJECT

public:
    explicit ErrorMgrTable(QWidget *parent = 0);
    ~ErrorMgrTable();

private:
    Ui::ErrorMgrTable *ui;
};
}

#endif // ERRORMGRTABLE_H
