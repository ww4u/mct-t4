#ifndef H2MEASUREMENT_H
#define H2MEASUREMENT_H

#include <QWidget>

namespace Ui {
class H2Measurement;
}

class H2Measurement : public QWidget
{
    Q_OBJECT

public:
    explicit H2Measurement(QWidget *parent = 0);
    ~H2Measurement();

private:
    Ui::H2Measurement *ui;
};

#endif // H2MEASUREMENT_H
