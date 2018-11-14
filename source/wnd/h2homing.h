#ifndef H2HOMING_H
#define H2HOMING_H

#include <QWidget>
#include "xconfig.h"
namespace Ui {
class H2Homing;
}

class H2Homing : public XConfig
{
    Q_OBJECT

public:
    explicit H2Homing(QWidget *parent = 0);
    ~H2Homing();
    int setApply();
    void loadXmlConfig();

public slots:
    void slot_set_direction(QString text);

protected slots:
    void slotOnModelChanged();

private:
    Ui::H2Homing *ui;

    double m_SearchVelocity;
    double m_Acceleration  ;
    double m_ForceLimit    ;
};

#endif // H2HOMING_H
