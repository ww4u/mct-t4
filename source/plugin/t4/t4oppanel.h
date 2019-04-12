#ifndef T4OPPANEL_H
#define T4OPPANEL_H

#include <QWidget>
#include <QAbstractListModel>
#include <QMenu>

#include "../plugin/xpage.h"

#include "./model/debugtable.h"
#include "../model/diagnosistable.h"
#include "megasplinechart.h"

//! delegate
#include "../../model/delegate/dspindelegate.h"
#include "../../model/delegate/ispindelegate.h"

//#define MONITOR_EVENT   (QEvent::Type)( QEvent::User + 1 )
typedef QList<QPointF> PointList;

class PlotDataSets
{
protected:
    QList< PointList *> mDataSets;
    int mIndex;
public:
    PlotDataSets( PointList *a, PointList *b )
    {
        mDataSets.append( a );
        mDataSets.append( b );

        Q_ASSERT( a->size() == b->size() );
        mIndex = 0;
    }

public:
    void toHead()
    { mIndex = 0; }
    bool isEnd()
    {
        if ( mIndex >= mDataSets.at(0)->size() )
        { return true; }
        else
        { return false; }
    }
    bool getNext( QPointF &a, QPointF &b )
    {
        if ( mDataSets.size() > 0 )
        {}
        else
        { return false; }

        //! end?
        if ( isEnd() )
        { return false; };

        a = mDataSets.at(0)->at( mIndex );
        b = mDataSets.at(1)->at( mIndex );
        mIndex++;
        //! get success
        return true;
    }
};

class SequenceItem
{
public:
    bool bValid;
    int id;     //! record id
    int vRow;
    QString mType;
    double x, y, z, pw, h, v;
    bool bLine;
    double delay;
    int mDo;    //! -1 INVALID

public:
    SequenceItem()
    {
        bValid = false;

        id = 0;
        vRow = 0;

        x = 0;
        y = 0;
        z = 0;
        pw =0;
        h = 0;
        v = 100;

        bLine = false;

        delay = 0;
    }

    SequenceItem &operator=( const SequenceItem &item )
    {
        bValid = item.bValid;
        vRow = item.vRow;

        mType = item.mType;

        x = item.x;
        y = item.y;
        z = item.z;
        pw =item.pw;
        h = item.h;
        v = item.v;

        delay = item.delay;
        bLine = item.bLine;

        return *this;
    }

    SequenceItem( const SequenceItem &item )
    {
        *this = item;
    }
};

namespace Ui {
class T4OpPanel;
}

#define joint_action( joint )  void on_##joint##_signal_zero_clicked();\
void on_##joint##_signal_single_add_clicked(); \
void on_##joint##_signal_single_sub_clicked(); \
void on_##joint##_signal_single_add_pressed(); \
void on_##joint##_signal_single_sub_pressed(); \
void on_##joint##_signal_single_add_released(); \
void on_##joint##_signal_single_sub_released();


namespace mrx_t4{

class DataCache : public QObject
{
    Q_OBJECT
public:
    DataCache( QObject *parent ) : QObject( parent )
    {}

public:
    QList<int> v1;
    QList<int> v2;

    QSemaphore mWSema, mRSema;
};

class OpEvent : public QEvent
{
public:
    enum T4EventType
    {
        debug_enter = QEvent::User + 1,
        debug_exit,
        monitor_event,
        update_pose,
        communicate_fail,
    };

public:
    OpEvent( int tpe) : QEvent( (QEvent::Type)tpe )
    {}

    OpEvent( int tpe, QVariant v1 ) : QEvent( (QEvent::Type)tpe )
    { mVar1 = v1; }

    OpEvent( int tpe, QVariant v1, QVariant v2 ) : QEvent( (QEvent::Type)tpe )
    {
        mVar1 = v1;
        mVar2 = v2;
    }

public:
    QVariant mVar1;
    QVariant mVar2;

public:
    void setPara( QVariant v1, QVariant v2 )
    {
        mVar1 = v1;
        mVar2 = v2;
    }
};

class CPose
{
public:
    double x, y, z, w, h;
};

class RefreshPara
{
public:
    CPose poseNow;
    double angles[5];
    double deltaAngles[5];

    int recNow;

    CPose poseAim;

    bool bHomeValid;
};

class T4OpPanel : public XPage
{
    Q_OBJECT

public:
    explicit T4OpPanel( QAbstractListModel *pModel, QWidget *parent = 0);
    ~T4OpPanel();

public:
    bool event(QEvent *e);

public:
    void setupUi();
protected:
    virtual void retranslateUi();

protected:
    virtual void focusInEvent(QFocusEvent *event);

protected:
    void updateMonitor( QEvent *e );
    virtual void spyEdited();

    void updateRefreshPara( QEvent *e );

public:
    int posRefreshProc( void *pContext );
    void terminalValidate( bool b );

    int monitorRefreshProc( void *pContext );

    int pingTick( void *pContext );

    int refreshDiagnosisInfo( void *pContext );
public:
    virtual void attachWorkings();

    virtual void updateUi();
    virtual void updateData();

    virtual void onSetting(XSetting setting);

    void home();
    void fold();

protected:
    double localSpeed();
    double localStep();
    bool   isContinous();
    bool   isCoordJoint();

    virtual void enterMission();
    virtual void exitMission();

    virtual void setOperAble( bool b );
    virtual void setOpened( bool b );

    void stepProc( int jId, int dir );
    void jogProc( int jId, int dir, bool b );

    void _step( double x, double y, double z );

    int onStep( QVariant var );
    int onHoming( QVariant var );
    int onFolding( QVariant var );

    int onJointStep( QVariant var );
    int onJointZero( QVariant var );
    int onJointJog( QVariant var );
    void onJointJogEnd( );

    int onSequence( QVariant var );
    int _onSequence( QVariant var );

    bool procSequenceEn( SequenceItem* pItem );
    int procSequence( SequenceItem* pItem );

    int exportDataSets( QTextStream &stream,
                        QStringList &headers,
                        QList<PlotDataSets*> &dataSets );

    void switchCoordMode();

protected:
    int buildSequence( QList<SequenceItem*> &list );

    void post_debug_enter( int id, int r );
    void post_debug_exit( int id, int r );

    void on_debug_enter( int id, int r );
    void on_debug_exit( int id, int r );

private:
    Ui::T4OpPanel *ui;

    iSpinDelegate *m_pISpinDelegateId;
    dSpinDelegate *m_pDSpinDelegateTime;

    QStringList mStepxList;
    QStringList mJointStepxList;
protected:
    DebugTable mDebugTable;
    DiagnosisTable mDiagTable;

    RefreshPara mRefreshPara;

    QList<QWidget*> mTerminalRelations;
    QMenu *m_pDebugContextMenu;
    QMenu *m_pMonitorContextMenu;

    QList<MegaSplineChart*> mJointCharts;
    DataCache *m_pCaches[5];

    QMutex mSeqMutex;
    QList<SequenceItem*> mSeqList;

    QAction *m_pActionExportImage;
    QAction *m_pActionExportData;
    QAction *m_pActionCopy;

Q_SIGNALS:
//    void signal_debug_enter( int i );
//    void signal_debug_exit( int i );

protected Q_SLOTS:
    //! status
    void slot_mct_checked( bool b );
    void slot_pwr_checked( bool b );
    void slot_ack_error();

    //! diagnosis
    void slot_save_debug();
    void slot_save_diagnosis();

    void slot_request_save();
    void slot_request_load();

    void slot_debug_table_changed();
    void slot_customContextMenuRequested( const QPoint &);
    void slot_toHere();

    void slot_monitorContextMenuRequested( const QPoint &);
    void slot_monitorExportImage();
    void slot_monitorExportData();
    void slot_monitorCopy();

//    void on_toolSingleXN_clicked();
//    void on_toolSingleXP_clicked();
//    void on_toolSingleYP_clicked();
//    void on_toolSingleYN_clicked();
//    void on_toolSingleZP_clicked();
//    void on_toolSingleZN_clicked();

private slots:
//    void on_pushButton_starting_home_clicked();
//    void on_btnFold_clicked();

    void on_toolSingleAdd_clicked();
    void on_toolSingleEdit_clicked();

//    void on_toolButton_15_clicked();
    void on_btnImport_clicked();
    void on_btnExport_clicked();
    void on_btnAdd_clicked();
    void on_btnDel_clicked();
    void on_btnClr_clicked();
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_btnDelete_clicked();
    void on_btnRead_clicked();
    void on_btnExport_2_clicked();

    //! joint op.
    joint_action( joint1 )
    joint_action( joint2 )
    joint_action( joint3 )
    joint_action( joint4 )

    joint_action( joint5 )

    void on_tabWidget_currentChanged(int index);

    void on_toolButton_debugRun_clicked();

    void on_radCoordXyz_clicked();
    void on_radCoordJoint_clicked();
};

}

#endif // T4OPPANEL_H

