#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class LogIn;
}

class LogIn : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = 0);
    ~LogIn();

//protected:
//    virtual void accept();

public:
//    void setPw( const QByteArray &ary );
    QString getPw();
    int getUserRole();

private slots:
//    void on_comboBox_currentIndexChanged(int index);

    void on_edtPw_textChanged(const QString &arg1);

private:
    Ui::LogIn *ui;
//    QByteArray mPw;
};

#endif // LOGIN_H
