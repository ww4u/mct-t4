#ifndef T4OPPANEL_H
#define T4OPPANEL_H

#include <QWidget>
#include <QAbstractListModel>
#include <QMenu>

#include "../plugin/xpage.h"

#include "./model/debugtable.h"
#include "../model/diagnosistable.h"

namespace Ui {
class T4OpPanel;
}

#define joint_action( joint )  void on_##joint##_signal_zero_clicked();\
void on_##joint##_signal_single_add_clicked(); \
void on_##joint##_signal_single_sub_clicked();

namespace mrx_t4{

class T4OpPanel : public XPage
{
    Q_OBJECT

public:
    explicit T4OpPanel( QAbstractListModel *pModel, QWidget *parent = 0);
    ~T4OpPanel();

public:
    void retranslateUi();

protected:
    virtual void spyEdited();

public:
    void posRefreshProc( void *pContext );
    void terminalValidate( bool b );

public:
    virtual void attachWorkings();

    virtual void updateUi();
    virtual void updateData();

    virtual void onSetting(XSetting setting);

protected:
    double localSpeed();

    void enterMission();
    void exitMission( int ret );

    void _step( double x, double y, double z );

    int onStep( QVariant var );
    int onHoming( QVariant var );

    int onJointStep( QVariant var );
    int onJointZero( QVariant var );

protected:

protected Q_SLOTS:
    //! status
    void slot_mct_checked( bool b );
    void slot_pwr_checked( bool b );
    void slot_ack_error();

    //! diagnosis
    void slot_save_debug();
    void slot_save_diagnosis();

    void slot_request_save();
    void slot_request_load();

    void slot_debug_table_changed();
    void slot_customContextMenuRequested( const QPoint &);
    void slot_toHere();

    void on_toolSingleXN_clicked();
    void on_toolSingleXP_clicked();
    void on_toolSingleYP_clicked();
    void on_toolSingleYN_clicked();
    void on_toolSingleZP_clicked();
    void on_toolSingleZN_clicked();

private:
    Ui::T4OpPanel *ui;

protected:
    DebugTable mDebugTable;
    DiagnosisTable mDiagTable;

    QList<QWidget*> mTerminalRelations;
    QMenu *m_pDebugContextMenu;

private slots:
//    void on_pushButton_2_clicked();

    void on_pushButton_starting_home_clicked();

    void on_toolSingleAdd_clicked();
    void on_toolButton_15_clicked();
    void on_btnImport_clicked();
    void on_btnExport_clicked();
    void on_btnAdd_clicked();
    void on_btnDel_clicked();
    void on_btnClr_clicked();
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_btnDelete_clicked();
    void on_btnRead_clicked();
    void on_btnExport_2_clicked();

    //! joint op.
    joint_action( joint1 )
    joint_action( joint2 )
    joint_action( joint3 )
    joint_action( joint4 )

    joint_action( joint5 )

//    void on_cmbStepXx_activated(int index);

protected:
    virtual void slot_enter_mission( WorkingApi *pApi );
    virtual void slot_exit_mission( WorkingApi *pApi, int ret );

};

}

#endif // T4OPPANEL_H

