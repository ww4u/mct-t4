#ifndef IOINDICATOR_H
#define IOINDICATOR_H

#include <QWidget>

namespace Ui {
class IoIndicator;
}

class IoIndicator : public QWidget
{
    Q_OBJECT

public:
    explicit IoIndicator(QWidget *parent = 0);
    ~IoIndicator();

    void setIndication( const QStringList &indi );

    void setChecked( bool b );
    bool isChecked( );

    void setText( const QString &text );
    QString text();

private:
    Ui::IoIndicator *ui;

    QStringList mIOIndiction;
};

#endif // IOINDICATOR_H
