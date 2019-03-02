#ifndef MRX_T4_H
#define MRX_T4_H

#include <QObject>

#include "../plugin/xplugin.h"

#include "./model/recordtable.h"
#include "../model/errmgrmodel.h"

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

#define robot_var() pRobo->deviceVi(), pRobo->robotHandle()
#define device_var() pRobo->deviceVi(), pRobo->deviceHandle()

#define on_post_setting( cls, onSetting )    m_pPlugin->attachMissionWorking( this, (XPage::onMsg)(&cls::onSetting), var );

#define wave_table  0

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
        e_setting_record,
    };

public:
    MRX_T4( QObject *parent = nullptr );

public:
    virtual QTreeWidgetItem* createPrefPages( QStackedWidget *stack );
    virtual QWidget *createOpsPanel( QAbstractListModel *pModel,
                                     QWidget *parent=nullptr );
public:
    virtual void ErrorMgrTable( QByteArray &ary );
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

public:
    int robotHandle();
    int deviceHandle();

public:
    int currentRecordIndex();

protected:
    mrx_t4::RecordTable mRecordTable;
    ErrorMgrModel mErrorConfigTable;

    int mRobotHandle;
    int mDeviceHandle;

private:
    mrx_t4::ActionTable *m_pReccordTable;

};

#endif // T4_H
