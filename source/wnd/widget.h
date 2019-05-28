#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractButton>
#include "roboconfig.h"
namespace Ui {
class Widget;
}

class Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void attatchRoboConfig(RoboConfig *);

    void Append(const QString &text);

    void reboot();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_toolButton_clicked();

    void slot_updateMRH(int i, QProcess::ExitStatus e);

    void slot_undo_finished(int i, QProcess::ExitStatus e);

    void slot_updateMRH_finish(int i, QProcess::ExitStatus e);

    void slot_startMRQUpdate(int);

signals:
    void AppendText(const QString &text);
    void sigReboot();
private slots:
    void SlotAppendText(const QString &text);
    void slotReboot();
private:
    Ui::Widget *ui;
    QString sPath;
    RoboConfig *m_roboConfig;
    QString m_addr,recvID;

    int flagFinish;
};

#endif // WIDGET_H
