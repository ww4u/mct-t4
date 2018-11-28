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
#include "roboconfig.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum {
        LANG_EN,
        LANG_CN,
    };

    enum {
        STYLE_MEGAROBO,
        STYLE_CLASSIC,
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static void requestLogout( const QString &str, log_level lev );
    void setUiStyle(const QString &styleFile);

protected:
    static MainWindow *_pBackendProxy;

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

private slots:
    void on_actionAbout_triggered();
    void slotSetDockOpsName(QString strDevInfo, int visa, int deviceName, int roboName);

    void on_actionChinese_triggered();
    void on_actionEnglish_triggered();

    void on_actionMega_triggered();

    void on_actionClassic_triggered();

private:
    Ui::MainWindow *ui;

    int m_style;
    int m_language;
    void loadConfig();

    QLabel *m_pLabStatus, *m_pLabMctVer, *m_pLabConVer;

    QDockWidget *m_pDockOps;
    QDockWidget *m_pDockHelp;

    HelpPanel *m_pHelpPanel;

    H2Ops *m_pOps;
    RoboConfig *m_roboConfig;

    QTranslator m_translator;
    void changeLanguage();
    int writeFile(QString fileName, QString text);
};

#endif // MAINWINDOW_H
