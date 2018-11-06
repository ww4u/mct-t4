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

    int setApply(ViSession vi);

protected slots:
//    void slotChangePicture(QString str);

private:
    Ui::H2Homing *ui;
    QString m_strDirXtoY;
    QString m_strDirYtoX;
};

#endif // H2HOMING_H
