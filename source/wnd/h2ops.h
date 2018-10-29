#ifndef H2OPS_H
#define H2OPS_H

#include <QWidget>

namespace Ui {
class H2Ops;
}

enum log_level
{
    e_log_info,
    e_log_warning,
    e_log_error,
};

class H2Ops : public QWidget
{
    Q_OBJECT

public:
    explicit H2Ops(QWidget *parent = 0);
    ~H2Ops();

public:
    void outConsole( const QString &str, log_level e );
    void outInfo( const QString &str );
    void outWarning( const QString &str );
    void outError( const QString &str );

protected Q_SLOTS:


    void slot_logSelectAll_action();
    void slot_logCopy_action();
    void slot_logClear_action();

private:
    Ui::H2Ops *ui;

    //! actions for the logout
    QAction *mp_logClearAction;
    QAction *mp_logSelectAllAction;
    QAction *mp_logCopyAction;
    QAction *mp_logSepAction;
};

#endif // H2OPS_H
