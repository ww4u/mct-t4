#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
namespace Ui {
class MainWindow;
}


#include "h2ops.h"

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


private slots:
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();



private:
    Ui::MainWindow *ui;

    QLabel *m_pLabStatus, *m_pLabMctVer, *m_pLabConVer;

    H2Ops *m_pOps;
};

#endif // MAINWINDOW_H
