#ifndef H2CONFIG_H
#define H2CONFIG_H

#include <QWidget>

namespace Ui {
class H2Config;
}


#include "h2action.h"
#include "../model/h2actionmodel.h"

class H2Config : public QWidget
{
    Q_OBJECT

public:
    explicit H2Config(QWidget *parent = 0);
    ~H2Config();

private:
    Ui::H2Config *ui;

    H2ActionModel mActions;
};

#endif // H2CONFIG_H
