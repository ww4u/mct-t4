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
    int setApply(ViSession vi);

protected slots:
    void slotOnModelChanged();
    void slotSelectSize(QString text);

private slots:
    void slotShowConfigPicture(bool bl);
    void slotUserDefinedStrokeX(QString text);
    void slotUserDefinedStrokeY(QString text);

private:
    Ui::H2Configuration *ui;
    void selectSize10();
    void selectSize30();
};

#endif // FORMTEST_H
