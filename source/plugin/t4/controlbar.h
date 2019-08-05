#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QWidget>

namespace Ui {
class ControlBar;
}

class ControlBar : public QWidget
{
    Q_OBJECT

public:
    explicit ControlBar(QWidget *parent = 0);
    ~ControlBar();

    //! speed %
    double getSpeed();

    //! step
    int stepIndex();

    void setSpeed( int iV );
    void setCurrentIndex( int iIndex );

    int count();

    QString combContent( int iIndex);
    void setItemText( int i, QString str );

private slots:
    void on_HSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::ControlBar *ui;
};

#endif // CONTROLBAR_H
