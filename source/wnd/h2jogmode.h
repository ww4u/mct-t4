#ifndef H2JOGMODE_H
#define H2JOGMODE_H

#include <QWidget>
#include "xconfig.h"
namespace Ui {
class H2JogMode;
}

class H2JogMode : public XConfig
{
    Q_OBJECT

public:
    explicit H2JogMode(QWidget *parent = 0);
    ~H2JogMode();
    int setApply();

protected slots:
    void slotOnModelChanged();

private:
    Ui::H2JogMode *ui;

    double m_CrawlingVelocity;
    double m_CrawlingTime    ;
    double m_MaximumVelocity ;
};

#endif // H2JOGMODE_H
