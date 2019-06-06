#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractButton>
#include <QDialog>
#include <QProcess>
#include "MegaGateway.h"
#include "../plugin/xplugin.h"


namespace Ui {
class Widget;
}
class XPlugin;
class Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void attatchPlugin(XPlugin *xp);

    void reOpenDevice();

    void Append(const QString &text);

    void reboot();

    void remove();

    void destory();

    void callback();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_toolButton_clicked();

    void slot_updateMRH();

    void slot_undo_finished(int i, QProcess::ExitStatus e);

    void slot_updateMRH_finish(int i, QProcess::ExitStatus e);

    void slot_startMRQUpdate(int);

signals:
    void AppendText(const QString &text);
    void sigReboot();
    void sigError( QString s );
    void sigProgress( int i );
    void sigComplete();
private slots:
    void SlotAppendText(const QString &text);
    void slotReboot();
    void on_btnShow_toggled(bool checked);
    void slotHandleError();

private:
    Ui::Widget *ui;
    QString sPath;
    XPlugin *m_pPlugin;
    QString m_addr,recvID;
    QProcess *m_updateProcess,*m_undoProcess;

    ViSession   m_vi;
    int         m_robotID;

    QProcess *proUpdateMRQ;

};

#endif // WIDGET_H
