#ifndef COORDINATE_H
#define COORDINATE_H

#include <QWidget>
#include "../plugin/xpage.h"

namespace Ui {
class Coordinate;
}

namespace mrx_t4 {

class Coordinate : public XPage
{
    Q_OBJECT

public:
    explicit Coordinate(QWidget *parent = 0);
    ~Coordinate();

public:
    virtual void updateUi();

protected:
    virtual void spyEdited();

private:
    Ui::Coordinate *ui;
};

}

#endif // COORDINATE_H
