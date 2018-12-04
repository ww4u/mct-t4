#ifndef H2OPS_H
#define H2OPS_H

#include <QToolButton>
#include <QWidget>

#include "diagnosismodel.h"
#include "debugmodel.h"
#include "xconfig.h"
#include "megasplinechart.h"


namespace Ui {
class H2Ops;
}

enum LogLevel
{
    eLogInfo,
    eLogWarning,
    eLogError,
};

class H2Ops : public XConfig
{
    Q_OBJECT
public:
    explicit H2Ops(QWidget *parent = 0);
    ~H2Ops();

    void outConsole( const QString &str, LogLevel e );
    void outInfo( const QString &str );
    void outWarning( const QString &str );
    void outError( const QString &str );

    void changeLanguage(QString qmFile)  override;

public slots:
    void slotSetCurrentRobot(QString strDevInfo, int visa, int deviceName, int roboName);
    void slotLoadConfigAgain();

    void slot_logSelectAll_action();
    void slot_logCopy_action();
    void slot_logClear_action();
    void on_pushButton_stop_clicked();

private slots:
    void updateDeviceAllStatus();

    void on_btnUp_clicked();

    void on_btnDown_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_btnClr_clicked();

    void on_btnImport_clicked();

    void on_btnExport_clicked();

    void on_btnRead_clicked();

    void on_btnDelete_clicked();

    void on_btnExport_2_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_tabBarClicked(int index);


    void on_pushButton_starting_home_clicked();
    void slot_starting_home_over(int ret);

    void on_toolButton_singlestep_x_dec_clicked();

    void on_toolButton_singlestep_x_inc_clicked();

    void on_toolButton_singlestep_y_dec_clicked();

    void on_toolButton_singlestep_y_inc_clicked();

    void on_pushButton_apply_clicked();

    void on_toolButton_jogmode_x_dec_pressed();

    void on_toolButton_jogmode_x_dec_released();

    void on_toolButton_jogmode_x_inc_pressed();

    void on_toolButton_jogmode_x_inc_released();

    void on_toolButton_jogmode_y_dec_pressed();

    void on_toolButton_jogmode_y_dec_released();

    void on_toolButton_jogmode_y_inc_pressed();

    void on_toolButton_jogmode_y_inc_released();

    void updatePositionOnceTimer(int msec);
    void updateCurrentPosition();
    void updateCurrentMileage();
    void updateTargetPosition();

    void updateRecordNumber();

    void updateDeviceStatus();
    void updateDigitalIO();
    void updateHoming();
    void updateMonitor();
    void updateDebug();
    void updateDiagnosis();


protected:
    void setupUi();
    void setupName();
    void setupModel();
    void buildConnection();

private:
    Ui::H2Ops *ui;

    QList<XConfig*> mSubTabs;

    //! actions for the logout
    QAction *mp_logClearAction;
    QAction *mp_logSelectAllAction;
    QAction *mp_logCopyAction;
    QAction *mp_logSepAction;

    //! diagnosis model
    DiagnosisModel *m_pDiagnosisModel;

    //! debug
    DebugModel *m_pDebugModel;

    MegaSplineChart *m_splineChart1;
    MegaSplineChart *m_splineChart2;

    int m_ViHandle;
    int m_DeviceName;
    int m_RoboName;
    QString m_strDevInfo;
    QMap<QString,QString> m_Data;

    QTimer *m_timerCurrentPos;   //更新实时位置显示的定时器
    QTimer *m_timerSpline;       //能效曲线添加新数值的定时器
    QTimer *m_timerGlobal;       //其他所有动态更新的数据

    void setButtonDisableTime(QToolButton *btn, int msec);
    void setTimerStop(QTimer *timer);
    void setTimerStart(QTimer *timer);
    void setTimerSplineStop();  //关闭动态曲线的定时器
    void setTimerSplineStart(); //打开动态曲线的定时器
};


struct ThreadGoHomingArg{
    int vi;
    int roboname;
    int timeout;
};

class ThreadGoHoming: public QThread
{
    Q_OBJECT
public:
    void setArgs(const ThreadGoHomingArg &args)
    {   m_args = args; }

signals:
    void signalThreadGoHomeEnd(int);

protected:
    void run() {
        int ret = mrgRobotGoHome(m_args.vi, m_args.roboname, m_args.timeout);
        qDebug() << "mrgRobotGoHome" << ret;
        sysInfo("mrgRobotGoHome", ret);
        emit signalThreadGoHomeEnd(ret);
    }

private:
    ThreadGoHomingArg m_args;
};

#endif // H2OPS_H
