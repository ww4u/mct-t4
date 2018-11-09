#ifndef H2MEASUREMENT_H
#define H2MEASUREMENT_H

#include <QWidget>
#include "xconfig.h"
namespace Ui {
class H2Measurement;
}

class H2Measurement : public XConfig
{
    Q_OBJECT

public:
    explicit H2Measurement(QWidget *parent = 0);
    ~H2Measurement();
    int setApply();

signals:
    void signal_AxesZeroPoint_currentTextChanged(QString);

protected slots:
    void slotChangeCornerPicture(int index);

private:
    Ui::H2Measurement *ui;
};

#endif // H2MEASUREMENT_H
