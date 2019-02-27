#ifndef IOWIDGET_H
#define IOWIDGET_H

#include <QWidget>
#include <QCheckBox>
namespace Ui {
class IOWidget;
}

class IOWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IOWidget(int w = 4, QWidget *parent = 0);
    ~IOWidget();

public:
    void setData( quint32 dat );
    quint32 getData();

private:
    Ui::IOWidget *ui;

    int mWidth;
    QList<QCheckBox*> mBits;
    QList<QWidget*> mSpanWidgets;
};

#endif // IOWIDGET_H
