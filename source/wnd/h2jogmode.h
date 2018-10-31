#ifndef H2JOGMODE_H
#define H2JOGMODE_H

#include <QWidget>

namespace Ui {
class H2JogMode;
}

class H2JogMode : public QWidget
{
    Q_OBJECT

public:
    explicit H2JogMode(QWidget *parent = 0);
    ~H2JogMode();

private:
    Ui::H2JogMode *ui;
};

#endif // H2JOGMODE_H
