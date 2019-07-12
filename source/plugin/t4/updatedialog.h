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
class MThead;
class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(QWidget *parent = 0);
    ~UpdateDialog();

    void attatchPlugin(XPlugin *xp);

protected:
    void showError(const QString &text);

    int openDevice();

    int loadRemoteInfo( int vi );

    int parseUpdateFile(QByteArray &in );

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    int versionComparison(const QString &fileVer,
                          const QByteArray &remoteVerStream );

    void on_toolButton_clicked();

    void slot_updateMRH();

    void slot_startMRQUpdate();

    void slotReadMRQResult(QString);

private slots:
    void slotGetRunState(int state);

    void on_btnShow_clicked();

    void slotLineEditTextChanged(QString);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Widget *ui;

    Entity *m_mrqEntity, *m_mrhEntity;

    QByteArray mRemoteVerionStream;

    QProcess *proUpdateMRQ;
    QString m_addr,recvID;
    MThead *m_mrhThread;
    XPlugin *m_pPlugin;
    MThead *m_threaad;
    QString m_desc;
    QString sPath;
    int m_robotID;
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

    void setAddr( QString str ){ m_addr = str; }
    void setId( int i ){ id = i; }
    void setPayload( QByteArray &in ){ mPayLoad = in; }

protected:
    virtual void run();

signals:
    void resultReady( QString );
    void resultReady( int );

private:
    QProcess *m_process;

    QString cmd;
    QStringList argument;

    int id;

    QByteArray mPayLoad;
    QString m_addr;

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
