#ifndef H2PRODUCT_H
#define H2PRODUCT_H

#include <QWidget>
#include "xconfig.h"

namespace Ui {
class H2Product;
}

class H2Product : public XConfig
{
    Q_OBJECT

public:
    explicit H2Product(QWidget *parent = 0);
    ~H2Product();
    int setApply(ViSession visa);

private:
    Ui::H2Product *ui;
};

#endif // H2PRODUCT_H
