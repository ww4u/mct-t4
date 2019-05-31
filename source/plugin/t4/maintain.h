#ifndef MAINTAIN_H
#define MAINTAIN_H

#include <QWidget>
#include "../plugin/xpage.h"
namespace Ui {
class Maintain;
}

namespace mrx_t4 {

class Maintain : public XPage
{
    Q_OBJECT

public:
    explicit Maintain(QWidget *parent = 0);
    ~Maintain();

private:
    Ui::Maintain *ui;
};

}

#endif // MAINTAIN_H
