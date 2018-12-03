#ifndef ROBO_CONFIG_H
#define ROBO_CONFIG_H

#include <QtWidgets>
#include "xrobo.h"
#include "megainterface.h"
#include "MegaGateway.h"

namespace Ui {
class RoboConfig;
}

class ThreadExport: public QThread
{
    Q_OBJECT
public:
    void setVisa(int vi){
        this->m_visa = vi;
    }

signals:
    void signalThreadEnd(int);

protected:
    void run() {
        int timeout = 10000;
        int state = 0;
        mrgSaveRobotConfig(m_visa);
        while (timeout > 0)
        {
            QThread::msleep(500);
            qDebug() << "mrgSaveRobotConfig";
            state = mrgGetRobotConfigState(m_visa);
            if (state != 1) { break;}
            timeout -= 500;
        }

        if(timeout <= 0){
            emit signalThreadEnd(-1);
        }
        else{
            if (state == 0){
                emit signalThreadEnd(0);
            }
            else{
                emit signalThreadEnd(-2);
            }
        }
    }
private:
    int m_visa = 0;
};

class RoboConfig : public QWidget
{
    Q_OBJECT

signals:
    void signalCurrentRobotChanged(QString,int,int,int);
    void signal_focus_in( const QString &);
    void signalDataChanged();

public:
    explicit RoboConfig(QWidget *parent = 0);
    ~RoboConfig();
    void changeLanguage(QString qmFile);

public slots:
    void slotAddNewRobot(QString strDevInfo );

    void slotDownload();
    void slotUpload();
    void slotStore();
    void slotSync();
    void slotSearch();
    void slotExit();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void slot_current_changed( QTreeWidgetItem* pre,QTreeWidgetItem* nxt );
    void slot_open_close(QString strIP);
    void slotShowContextmenu(const QPoint &pos);
    void soltActionClose();
    void soltActionDelete();
    void slotStoreEnd(int ret);

private:
    Ui::RoboConfig *ui;
    MegaInterface *m_megaSerachWidget;

    class RobotInfo
    {
    public:
        XRobo*  m_Robo;
        int     m_Visa;
        int     m_DeviceName;
        int     m_RoboName;
        QString m_strDevInfo;
    };

    QTreeWidgetItem *m_pRootNode;
    QList<RobotInfo> m_RobotList;
    int mIndex;

    void initRootNodeWidget();
    void loadXmlConfig();
    void createRobot(QString strDevInfo);
    int  deviceOpen(QString strIP);
    int  deviceClose();
    int  setApply();
    int  setReset();

    QMenu *m_menu;
    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    QTranslator m_translator;
};

#endif // H2CONFIG_H
