#ifndef ACTIONTABLE_H
#define ACTIONTABLE_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QMenu>
#include "../plugin/xpage.h"

#include "./model/iodelegate.h"
#include "../model/delegate/comboxdelegate.h"

namespace Ui {
class ActionTable;
}

namespace mrx_t4 {

class ActionTable : public XPage
{
    Q_OBJECT

public:
    explicit ActionTable(QWidget *parent = 0);
    ~ActionTable();

protected:
    virtual void retranslateUi();

public:
    void setModel( QAbstractTableModel *pModel );

    virtual void onSetting(XSetting setting);

    virtual int upload();
    virtual int download();
    virtual int diff();    

protected:
    virtual void enterMission();
    virtual void exitMission();

public:
    int currentIndex();

protected:
    void addRecord( XSetting setting );
    void doSave();
    void doLoad();

protected:
    int onToHere( QVariant var );

private:
    Ui::ActionTable *ui;
//    IODelegate *m_pIDelegate, *m_pODelegate;
    ComboxDelegate *m_pTypeDelegate;

    QMenu *m_pContextMenu;

protected Q_SLOTS:
    void slot_request_save();
    void slot_request_load();

    void slot_data_changed();

    void slot_toHere();

    void slot_customContextMenuRequested(const QPoint &pos);
};

}

#endif // ACTIONTABLE_H
