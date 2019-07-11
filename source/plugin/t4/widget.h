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
class Entity;
class Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void attatchPlugin(XPlugin *xp);

    void reboot();

    void destory();

    int upgressMRH();

    void showError(const QString &text);

    int openDevice();
    void closeDevice();

    int parseUpdateFile(QByteArray &in );

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    int versionComparison(QString);

    void on_toolButton_clicked();

    void slot_updateMRH();

    void slot_startMRQUpdate();

    void slotReadMRQResult(QString);

signals:
    void AppendText(const QString &text);
    void sigReboot();
    void sigProgress( int i );

private slots:
//    void SlotAppendText(const QString &text);
    void slotReboot();

    void slotGetRunState();

    void on_btnShow_clicked();

    void slotLineEditTextChanged(QString);

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

    Entity *m_mrqEntity, *m_mrhEntity;

    QString m_desc;

    bool isAdmin;

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

//! entity
class Entity : public QObject
{
    Q_OBJECT
public:
    enum ID{
        MRH_ENTITY,
        MRQ_ENTITY,
        MCT_ENTITY,
        PACKAGE
    };
public:
    int mDescLen;
    QString mDescription;
    quint32 mId;
    quint32 mSize;
    quint32 mCheck;
    quint32 mFormat;
    quint32 mSections;
    QByteArray mPayload;

public:
    Entity(QObject *parent = nullptr);
};
