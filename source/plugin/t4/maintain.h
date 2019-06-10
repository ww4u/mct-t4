#ifndef MAINTAIN_H
#define MAINTAIN_H

#include <QWidget>
#include "../plugin/xpage.h"
namespace Ui {
class Maintain;
}

namespace mrx_t4 {

class Maintain : public XPage
{
    Q_OBJECT

public:
    explicit Maintain(QWidget *parent = 0);
    ~Maintain();

protected:
    virtual void enterMission();
    virtual void exitMission();
public:
    virtual void setOperAble( bool b );
    virtual void setOpened( bool b );

    virtual void updateRole();

    virtual void updateUi();
private slots:
    void on_cmbDemo_currentIndexChanged(int index);

    void on_btnDemo_clicked();

    void on_btnRestart_clicked();

    void on_btnShutDown_clicked();

    void on_btnReset_clicked();

    void on_btnUpdate_clicked();

    void on_btnFold_clicked();

    void on_btnBackup_clicked();

    void on_btnClearBackup_clicked();

    void on_cmbUser_currentIndexChanged(int index);

    void on_btnChange_clicked();

    void on_btnResetPw_clicked();

    void on_chkAutoLogin_stateChanged(int arg1);

private:
    Ui::Maintain *ui;
};

}

#endif // MAINTAIN_H
