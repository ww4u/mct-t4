#ifndef H2PREF_H
#define H2PREF_H

#include <QWidget>
#include "xconfig.h"
namespace Ui {
class H2Pref;
}

class H2Pref : public XConfig
{
    Q_OBJECT

public:
    explicit H2Pref(QWidget *parent = 0);
    ~H2Pref();

private:
    Ui::H2Pref *ui;
};

#endif // H2PREF_H
