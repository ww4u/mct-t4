#ifndef FORMTEST_H
#define FORMTEST_H

#include <QWidget>
#include "xconfig.h"
namespace Ui {
class H2Configuration;
}

class H2Configuration : public XConfig
{
    Q_OBJECT

public:
    explicit H2Configuration(QWidget *parent = nullptr);
    ~H2Configuration();
    int setApply();

protected slots:
    void slotOnModelChanged();
    void slotSelectSize(int index);

private:
    Ui::H2Configuration *ui;
    QString m_Family;
    int     m_Size;
    int     m_WorkStrokeX;
    int     m_WorkStrokeY;
    int     m_MotorPosition;
};

#endif // FORMTEST_H
