#ifndef CONFIG_H
#define CONFIG_H

#include <QWidget>
#include "../plugin/xpage.h"
namespace Ui {
class Config;
}

namespace mrx_t4 {

class Config : public XPage
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = 0);
    ~Config();

private:
    Ui::Config *ui;
};

}

#endif // CONFIG_H
