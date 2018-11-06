#ifndef H2CONFIG_H
#define H2CONFIG_H

#include <QtWidgets>


namespace Ui {
class H2Config;
}

#include "../model/h2actionmodel.h"
#include "../model/errmgrmodel.h"

class H2Config : public QWidget
{
    Q_OBJECT

public:
    explicit H2Config(QWidget *parent = 0);
    ~H2Config();

protected:
    int loadDataset();

    int setApply();
    int setReset();
    int setOK();


Q_SIGNALS:
    void signal_focus_in( const QString &);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void slot_current_changed( QTreeWidgetItem* pre,QTreeWidgetItem* nxt );

private:
    Ui::H2Config *ui;

    H2ActionModel mActions;
    ErrMgrModel mErrManager;
};

#endif // H2CONFIG_H
