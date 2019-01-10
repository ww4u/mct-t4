#ifndef T4OPPANEL_H
#define T4OPPANEL_H

#include <QWidget>
#include "../plugin/xpage.h"

namespace Ui {
class T4OpPanel;
}

namespace mrx_t4{

class T4OpPanel : public XPage
{
    Q_OBJECT

public:
    explicit T4OpPanel(QWidget *parent = 0);
    ~T4OpPanel();

private:
    Ui::T4OpPanel *ui;
};

}

#endif // T4OPPANEL_H
