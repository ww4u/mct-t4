#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
namespace Ui {
class MainWindow;
}

#include <QDockWidget>

#include "helppanel.h"
#include "aboutdlg.h"
#include "h2ops.h"
#include "h2config.h"
#include "h2ops.h"
#include "megainterface.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static void requestLogout( const QString &str, log_level lev );
protected:
    static MainWindow *_pBackendProxy;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void setupWorkArea();
    void setupToolBar();
    void setupStatusBar();

    void buildConnection();

Q_SIGNALS:
    void signal_logout_request( QString str, log_level lev );

protected Q_SLOTS:
    void slot_post_startup();
    void slot_logout( const QString &str, log_level lev = e_log_info );

    void slot_focus_in( const QString &name );

    void slot_action_search();

private slots:
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    QLabel *m_pLabStatus, *m_pLabMctVer, *m_pLabConVer;

    QDockWidget *m_pDockOps;
    QDockWidget *m_pDockHelp;

    HelpPanel *m_pHelpPanel;

    H2Ops *m_pOps;
    H2Config *m_pConfig;

    MegaInterface *m_megaSerachWidget;
    int m_visa;
};

#endif // MAINWINDOW_H
