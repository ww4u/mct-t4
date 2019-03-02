#ifndef MOTORCONFIG_H
#define MOTORCONFIG_H

#include <QWidget>
#include "../plugin/xpage.h"
namespace Ui {
class MotorConfig;
}

namespace mrx_t4 {

class MotorConfig : public XPage
{
    Q_OBJECT

public:
    explicit MotorConfig(QWidget *parent = 0);
    ~MotorConfig();

    virtual void adapteToUserMode( sysPara::eSysMode mode );
    virtual void updateUi();
    virtual void updateData();
protected:
    virtual void spyEdited();
    virtual void retranslateUi();

private:
    Ui::MotorConfig *ui;
};

}

#endif // MOTORCONFIG_H
