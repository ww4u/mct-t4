#ifndef ACTIONTABLE_H
#define ACTIONTABLE_H

#include <QWidget>

#include "../plugin/xpage.h"

namespace Ui {
class ActionTable;
}

namespace mrx_t4 {

class ActionTable : public XPage
{
    Q_OBJECT

public:
    explicit ActionTable(QWidget *parent = 0);
    ~ActionTable();

private:
    Ui::ActionTable *ui;
};

}

#endif // ACTIONTABLE_H
