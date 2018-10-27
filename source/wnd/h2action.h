#ifndef H2ACTION_H
#define H2ACTION_H

#include <QWidget>
#include <QAbstractTableModel>
#include "../model/comboxdelegate.h"
namespace Ui {
class H2Action;
}

class H2Action : public QWidget
{
    Q_OBJECT

public:
    explicit H2Action( QWidget *parent = 0);
    ~H2Action();

public:
    void setModel( QAbstractTableModel *pModel );

private:
    Ui::H2Action *ui;

    comboxDelegate *m_pDelegate1;
};

#endif // H2ACTION_H
