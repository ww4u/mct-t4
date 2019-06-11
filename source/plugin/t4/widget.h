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

    int upgressMRH();

    void showError(const QString &text);

    int copyDemo();

    int copyUpdateInfo();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_toolButton_clicked();

    void slot_updateMRH();

    void slot_startMRQUpdate(int);

    void slotReadUndoResult(QString);

    void slotReadMRQResult(QString);

signals:
    void AppendText(const QString &text);
    void sigReboot();
    void sigProgress( int i );

private slots:
//    void SlotAppendText(const QString &text);
    void slotReboot();
    void on_btnShow_toggled(bool checked);
    void slotGetRunState();

private:
    Ui::Widget *ui;
    QString sPath;
    XPlugin *m_pPlugin;
    QString m_addr,recvID;
    QProcess *m_updateProcess,*m_undoProcess;

    ViSession   m_vi;
    int         m_robotID;

    QProcess *proUpdateMRQ;

    QFutureWatcher<int> *watcher;

};

#endif // WIDGET_H

class MThead: public QThread
{
    Q_OBJECT

public:
    MThead(QObject *parent = 0);

    void setExeCmd(const QString &str){ cmd = str; }
    void setArguments(const QStringList &list){ argument = list; }

protected:
    virtual void run();

signals:
    void resultReady( QString );

private:
    QProcess *m_process;

    QString cmd;
    QStringList argument;

private slots:
    void slotReadyRead();
};

