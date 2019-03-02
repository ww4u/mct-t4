#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QDockWidget>

#include "syspara.h"

#include "helppanel.h"
#include "aboutdlg.h"
#include "h2ops.h"
#include "roboconfig.h"
#include "stopwidget.h"

#include "syslogout.h"

#include "../plugin/model/megaloglistmodel.h"

namespace Ui {
class MainWindow;
}

enum {
    LANG_EN = 0,
    LANG_CN,
    LANG_TR_CN,
};

enum {
    STYLE_MEGAROBO,
    STYLE_CLASSIC,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static MainWindow *_pBackendProxy;
    static void requestLogout( const QString &str, LogStr::eLogLevel lev );
    static void requestProgress( const QString &info, bool b, int now, int mi=0, int ma = 100 );

    static void showStatus(const QString str);

protected:
    virtual void changeEvent( QEvent *event );

public:
    void emit_logout( const QString &info, int level );
    void emit_status( const QString &str );
    void emit_progress( const QString &info, bool b, int now, int mi, int ma );

protected:
    void retranslateUi();

    void savePref();
    void loadPref();

    void setupWorkArea();
    void setupMenu();
    void setupToolBar();
    void setupStatusBar();
    void buildConnection();
    void loadConfig();

    void changeLanguage();
    void changeStyle();
    void setUiStyle(const QString &styleFile);

signals:
    void signal_pref_changed();
    void signal_logout( const QString &str, int lev );
    void signal_status( const QString &str );

    void signal_progress( const QString &info, bool b, int now, int mi, int ma );

private slots:
    void slot_request_sysOpPanel();
    void slot_save_sysPref();

    void slot_post_startup();

    void slot_lang_changed();
    void slot_style_changed();

    void slot_logout( const QString &str, int lev );

    void slot_status(const QString &str);

    void slot_progress( const QString &info, bool b, int now, int mi, int ma );
    void slot_progress_canceled();


    void slot_focus_in( const QString &name );

    void on_actionAbout_triggered();

    void on_actionPoweroff_triggered();

    void on_actionReboot_triggered();

    void on_actionWifi_triggered();

    void on_actionPref_triggered();

    void on_actiontest_triggered();

private:
    Ui::MainWindow *ui;

    StopWidget *m_pStopWidget;

    //! lang/style action
    QAction *m_pChAction, *m_pEnAction, *m_pMegaAction, *m_pClasAction;

    QLabel *m_pLabStatus, *m_pLabMctVer, *m_pLabConVer;

    QDockWidget *m_pDockOps;

    QProgressDialog *m_pProgress;

    QDockWidget *m_pDockHelp;
    HelpPanel *m_pHelpPanel;

    RoboConfig *m_roboConfig;
    SysLogout *m_pSysLogout;

    //! sys para
    SysPara mPref;

    //! common
    MegaLogListModel mLogModel;

    QTranslator mTranslator;
};

#endif // MAINWINDOW_H
