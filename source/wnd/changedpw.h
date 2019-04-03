#ifndef CHANGEDPW_H
#define CHANGEDPW_H

#include <QDialog>

namespace Ui {
class ChangedPw;
}

class ChangedPw : public QDialog
{
    Q_OBJECT

public:
    explicit ChangedPw(QWidget *parent = 0);
    ~ChangedPw();
public:
    QString getPw();

protected:
    void updateControl();

private slots:
    void on_edtPw1_textChanged(const QString &arg1);

    void on_edtPw2_textChanged(const QString &arg1);

private:
    Ui::ChangedPw *ui;
};

#endif // CHANGEDPW_H
