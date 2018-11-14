#ifndef H2OPS_H
#define H2OPS_H

#include <QWidget>

#include "../model/diagnosismodel.h"
#include "../model/debugmodel.h"
#include "xconfig.h"
namespace Ui {
class H2Ops;
}

enum log_level
{
    e_log_info,
    e_log_warning,
    e_log_error,
};

class H2Ops : public XConfig
{
    Q_OBJECT

public:
    explicit H2Ops(QWidget *parent = 0);
    ~H2Ops();

    void outConsole( const QString &str, log_level e );
    void outInfo( const QString &str );
    void outWarning( const QString &str );
    void outError( const QString &str );

public slots:
    void slotSetCurrentRobot(QString strDevType, int visa, int name);

    void slot_logSelectAll_action();
    void slot_logCopy_action();
    void slot_logClear_action();

private slots:
    void on_btnUp_clicked();

    void on_btnDown_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_btnClr_clicked();

    void on_btnImport_clicked();

    void on_btnExport_clicked();

    void on_btnRead_clicked();

    void on_btnDelete_clicked();

    void on_btnExport_2_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_tabBarClicked(int index);

protected:
    void setupUi();
    void setupName();
    void setupModel();
    void buildConnection();

private:
    Ui::H2Ops *ui;

    QList<XConfig*> mSubTabs;

    //! actions for the logout
    QAction *mp_logClearAction;
    QAction *mp_logSelectAllAction;
    QAction *mp_logCopyAction;
    QAction *mp_logSepAction;

    //! diagnosis model
    DiagnosisModel *m_pDiagnosisModel;

    //! debug
    DebugModel *m_pDebugModel;

    int m_ViHandle;
    int m_RoboName;

    QString getDeviceTypeName(QString strDevInfo);
};

#endif // H2OPS_H
