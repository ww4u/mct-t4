#ifndef H2STATUS_H
#define H2STATUS_H

#include <QWidget>

namespace Ui {
class H2Status;
}

class H2Status : public QWidget
{
    Q_OBJECT

public:
    explicit H2Status(QWidget *parent = 0);
    ~H2Status();

private slots:
    void on_chkMct_clicked();

private:
    Ui::H2Status *ui;
};

#endif // H2STATUS_H
