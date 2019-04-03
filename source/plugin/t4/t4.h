#ifndef MRX_T4_H
#define MRX_T4_H

#include <QObject>
#include <float.h>
#include "../plugin/xplugin.h"
#include "../model/errmgrmodel.h"

#include "./model/treemodel.h"

#include "t4para.h"

#define selfPara  ((MRX_T4*)m_pPlugin)

#define check_connect() MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;\
                        Q_ASSERT( NULL != pRobo );\
                        \
                        if ( pRobo->isOpened() )\
                        {}\
                        else\
                        { return; }

#define check_connect_ret( ret ) MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;\
                        Q_ASSERT( NULL != pRobo );\
                        \
                        if ( pRobo->isOpened() )\
                        {}\
                        else\
                        { return ret; }

#define robot_var() (ViSession)pRobo->deviceVi(), pRobo->robotHandle()
#define device_var() (ViSession)pRobo->deviceVi(), pRobo->deviceHandle()
#define robot_var_handle() pRobo->robotHandle()

#define self_check_connect() \
                        if ( isOpened() )\
                        {}\
                        else\
                        { return; }

#define self_check_connect_ret( ret ) \
                        if ( isOpened() )\
                        {}\
                        else\
                        { return ret; }

#define self_robot_var()  (ViSession)deviceVi(),robotHandle()
#define self_device_var()    (ViSession)deviceVi(),deviceHandle()

#define _on_post_setting( cls, onSetting, desc, bMission )    m_pPlugin->attachMissionWorking( this, (XPage::onMsg)(&cls::onSetting), var, desc, bMission );

#define on_post_setting( cls, onSetting, desc )    _on_post_setting( cls, onSetting, desc, true )
#define on_post_setting_n_mission( cls, onSetting, desc )    _on_post_setting( cls, onSetting, desc, false )

#define on_post_setting_emerge( cls, onSetting, desc ) m_pPlugin->attachEmergencyWorking( this, (XPage::onMsg)(&cls::onSetting), var, desc );

#define wave_table  0
#define distance_error      (0.001)

#define guess_dist_calc_time_ms( dist )    (dist * 1000)

#define guess_dist_time_ms( ts, dist )     ( (ts)*1000 + guess_dist_calc_time_ms(dist) )

#define rel_to_abs_speed( rel ) ( rel/100.0*pRobo->mMaxTerminalSpeed )


namespace mrx_t4 {
class ActionTable;
}

class MRX_T4 : public XPlugin, public T4Para
{
    Q_OBJECT

public:
    enum eT4Settings
    {
        e_setting_terminal = XPage::e_setting_user,
        e_setting_current,
        e_add_record,
        e_edit_record,
        e_setting_record,
    };

public:
    MRX_T4( QObject *parent = nullptr );
    ~MRX_T4();

public:
    virtual QTreeWidgetItem* createPrefPages( QStackedWidget *stack );
    virtual QWidget *createOpsPanel( QAbstractListModel *pModel,
                                     QWidget *parent=nullptr );
    virtual void retranslateUi();

public:
    virtual void rstErrorMgrTable();
    virtual void rstRecordTable();

protected:
    void ErrorMgrTable( QByteArray &ary );
    void RecordData( QByteArray &ary );
public:
    virtual void onSetting(XSetting setting);
public:
    virtual int serialOut(QXmlStreamWriter &writer);
    virtual int serialIn(QXmlStreamReader &reader);

protected Q_SLOTS:
    void slot_save_setting();
    void slot_load_setting();

public:
    virtual int open();
    virtual void close();

    virtual int stop();

    virtual void rst();

    virtual int upload();
    virtual int download();
    virtual int diff();

protected:
    int _uploadProc();
    int uploadProc();

    int _downloadProc();
    int downloadProc();

    int _diffProc();
    int diffProc();

    int onStop( QVariant var );

public:
    int robotHandle();
    int deviceHandle();

public:
    int currentRecordIndex();

    //! api
public:
    static double eulaDistance( double x, double y, double z,
                                double x1, double y1, double z1 );
public:
    int relMove( QString para,
                 double x, double y, double z,
                 double pw, double h,
                 double v, bool bLine );
    int absMove( QString para,
                 double x, double y, double z,
                 double pw, double h,
                 double v, bool bLine );

public:
    TreeModel* m_pRecordModel;
protected:
    ErrorMgrModel mErrorConfigTable;

    int mRobotHandle;
    int mDeviceHandle;

private:
    mrx_t4::ActionTable *m_pRecordView;


};

#endif // T4_H
