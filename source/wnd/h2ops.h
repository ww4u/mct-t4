#ifndef H2OPS_H
#define H2OPS_H

#include <QWidget>

namespace Ui {
class H2Ops;
}

class H2Ops : public QWidget
{
    Q_OBJECT

public:
    explicit H2Ops(QWidget *parent = 0);
    ~H2Ops();

private:
    Ui::H2Ops *ui;
};

#endif // H2OPS_H
