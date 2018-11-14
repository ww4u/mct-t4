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
    void loadXmlConfig();

signals:
    void signal_AxesZeroPoint_currentTextChanged(QString);

protected slots:
    void slotChangeCornerPicture(int index);
    void slotOnModelChanged();

private:
    Ui::H2Measurement *ui;

    int m_ZeroPoint        ;
    double m_ProjectZeroPointX;
    double m_ProjectZeroPointY;
    double m_SWLimitPositiveX ;
    double m_SWLimitPositiveY ;
    double m_SWLimitNegativeX ;
    double m_SWLimitNegativeY ;
};

#endif // H2MEASUREMENT_H
