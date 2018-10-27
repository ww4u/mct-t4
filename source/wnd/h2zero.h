#ifndef H2ZERO_H
#define H2ZERO_H

#include <QWidget>

namespace Ui {
class H2Zero;
}

class H2Zero : public QWidget
{
    Q_OBJECT

public:
    explicit H2Zero(QWidget *parent = 0);
    ~H2Zero();

private:
    Ui::H2Zero *ui;
};

#endif // H2ZERO_H
