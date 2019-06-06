#include "t4oppanel.h"
#include "ui_t4oppanel.h"

#include <QFileDialog>

#include "../../plugin/plugin/xplugin.h"

#include "MegaGateway.h"

#include "../../plugin/t4/t4.h"
#include "../../plugin/xpluginworkingthread.h"

#include "comassist.h"

#include "../model/debugtable.h"

#include "regexpinputdialog.h"

#define WIDGET_MONITOR_INDEX 4
#define DEFAULT_PAGE_INDEX 2
namespace mrx_t4{

static double _stepRatio[]={ 0.1,   //! 0
                             0.5,   //! 1
                             1,     //! 2
                             5,     //! 3
                             10,    //! 4
                             50,    //! 5
                             100 }; //! 6

//! speed
//! 1       0
//! 5       1
//! 10      2
//! 20      3
//! 50      4
//! 100     5

#define new_cache( id ) m_pCaches[id] = new DataCache( this ); \
                        Q_ASSERT( m_pCaches[id] != NULL );\
                        m_pCaches[id]->mWSema.release();

T4OpPanel::T4OpPanel(QAbstractListModel *pModel, QWidget *parent) :
    XPage(parent),
    ui(new Ui::T4OpPanel)
{
    ui->setupUi(this);

    setupUi();

    //! add comment
    QString strRaw, strDecimal, strComment;
    for ( int i = 0; i < ui->cmbStepXx->count(); i++ )
    {
        strRaw = ui->cmbStepXx->itemText( i );
        strDecimal = strRaw;
        strDecimal.remove(0,1);        //! remove the X
        strComment = QString("%1 [%2%3]").arg(strRaw).arg( strDecimal).arg( char_deg );
        mStepxList<<strComment;
    }
//    for ( int i = 0; i < ui->cmbStepXx->count(); i++ ){
//        strRaw = ui->comboBox->itemText( i );
//        strDecimal = strRaw;
//        strDecimal.remove(0,1);        //! remove the X
//        strComment = QString("%1 [%2%3 or mm]").arg(strRaw).arg( strDecimal).arg( char_deg );
//        mJointStepxList<<strComment;
//    }

    m_pDebugContextMenu = NULL;
    m_pMonitorContextMenu = NULL;

    m_pActionExportImage = NULL;
    m_pActionExportData = NULL;
    m_pActionCopy = NULL;

    m_pIOContextMenu = NULL;
    m_pActionRename = NULL;
    currentRenameObj = NULL;

    //! data cache
//    m_pCaches[0] = new DataCache( this ); m_pCaches[0]->mWSema.release();
    new_cache( 0 );
    new_cache( 1 );
    new_cache( 2 );
    new_cache( 3 );
    new_cache( 4 );

    ui->spinTerminalTarget->setSuffix( char_deg );
    ui->spinWristTarget->setSuffix( char_deg );

    ui->actPosTerminal->setSuffix( char_deg );
    ui->actPosWrist->setSuffix( char_deg );

    //! set model
    ui->logout->setModel( pModel );


    ui->tvDebug->setModel( &mDebugTable );
    ui->tvDiagnosis->setModel( &mDiagTable );

    ui->listView->setModel( &mDebugConsoleModel );

    //! build connect
    connect( &mDebugTable, SIGNAL(signal_data_changed()),
             this, SLOT(slot_debug_table_changed()) );

    connect( &mDebugTable, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
             this, SLOT(slot_debug_table_changed()) );
    connect( &mDebugTable, SIGNAL(signal_current_changed(int)),
             this, SLOT(slot_debug_table_changed()) );

    connect( &mDebugTable, SIGNAL(signal_current_changed(int)),
             this, SLOT(slot_debug_current_changed(int)) );


    connect( ui->tvDebug, SIGNAL(activated( const QModelIndex &)),
             this, SLOT(slot_debug_table_changed()) );
    connect( ui->tvDebug, SIGNAL(clicked( const QModelIndex &)),
             this, SLOT(slot_debug_table_changed()) );
    connect( ui->tvDebug, SIGNAL(doubleClicked( const QModelIndex &)),
             this, SLOT(slot_debug_table_changed()) );

    connect( ui->tvDebug, SIGNAL(signal_key_delete()),
             this, SLOT(slot_debug_delete()) );
    connect( ui->tvDebug, SIGNAL(signal_key_insert()),
             this, SLOT(slot_debug_insert()) );

    connect( &mDebugTable, SIGNAL(signal_data_changed()),
             this, SLOT(slot_save_debug()) );

    //! context menu
    connect( ui->tvDebug, SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(slot_customContextMenuRequested(const QPoint &)));

    //! diagnosis
    connect( &mDiagTable, SIGNAL(signal_data_changed()),
             this, SLOT(slot_save_diagnosis()) );

    //! status
    connect( ui->controllerStatus, SIGNAL(signal_device_power(bool)),
             this, SLOT(slot_pwr_checked(bool)) );
    connect( ui->controllerStatus, SIGNAL(signal_mct_checked(bool)),
             this, SLOT(slot_mct_checked(bool)) );
    connect( ui->controllerStatus, SIGNAL(signal_ack_error()),
             this, SLOT(slot_ack_error()) );

    spyEdited();

    //! joint name
    retranslateUi();

    //! terminal relations
    mTerminalRelations.append( ui->joint5 );

    //! spys
    spySetting( MRX_T4::e_setting_terminal );
    spySetting( MRX_T4::e_setting_record );

    //! sync ui
    switchCoordMode();

    ui->btnRead->setVisible(false);

    //! step and speed
    connect( ui->cmbSpeed, SIGNAL(activated(int)),
             this, SLOT(slot_speed_verify()) );
    connect( ui->cmbStepXx, SIGNAL(activated(int)),
             this, SLOT(slot_speed_verify()) );

    //! \todo
    //! init digital inputs name
    connect( ui->radDI1, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radDI2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radDI3, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radDI4, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radDI5, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radDI6, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radStart, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radReset, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radENBLE, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radRDYEN, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radMC, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)));
    connect( ui->radFAULT, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radENABLED, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );
    connect( ui->radACK, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_digitalInputsCustomContextMenuRequested(QPoint)) );

    ui->radDI1->setChecked(false);
    ui->radDI2->setChecked(false);
    ui->radDI3->setChecked(false);
    ui->radDI4->setChecked(false);
    ui->radDI5->setChecked(false);
    ui->radDI6->setChecked(false);
    ui->radStart->setChecked(false);
    ui->radReset->setChecked(false);
    ui->radENBLE->setChecked(false);
    ui->radRDYEN->setChecked(false);
    ui->radMC->setChecked(false);
    ui->radFAULT->setChecked(false);
    ui->radENABLED->setChecked(false);
    ui->radACK->setChecked(false);
}

T4OpPanel::~T4OpPanel()
{
    mSeqMutex.lock();
    delete_all( mSeqList );
    mSeqMutex.unlock();

    delete ui;
}

bool T4OpPanel::event(QEvent *e)
{
    //! proc me
    if ( e->type() >= QEvent::User )
    {
        do
        {
            OpEvent *pEvent = (OpEvent*)e;
            if ( NULL == pEvent )
            { break; }

            if ( (int)pEvent->type() == OpEvent::debug_enter )
            {
                on_debug_enter( pEvent->mVar1.toString(),
                                pEvent->mVar2.toInt(),
                                pEvent->mVars );
            }
            else if ( (int)pEvent->type() == OpEvent::debug_exit )
            {   on_debug_exit( pEvent->mVar1.toInt(), pEvent->mVar2.toInt() ); }
            else if ( (int)pEvent->type() == OpEvent::monitor_event )
            { updateMonitor( e ); }
            else if ( (int)pEvent->type() == OpEvent::update_pose )
            { updateRefreshPara( e ); }
            else if ( (int)pEvent->type() == OpEvent::communicate_fail )
            {
                //! close the plugin

                sysPrompt( tr("Communicate fail") );

                m_pPlugin->stop();
                m_pPlugin->close();

            }
            else
            {}

        }while( 0 );

        e->accept();
        return true;
    }
    else
    { return XPage::event( e ); }
}

void T4OpPanel::setupUi()
{
    //! delegate
    m_pISpinDelegateId = new iSpinDelegate( this );
    m_pDSpinDelegateTime = new dSpinDelegate( this );

    m_pISpinDelegateId->setMax( 31 );
    m_pISpinDelegateId->setMin( 1 );

    m_pDSpinDelegateTime->setMax( 1000 );
    m_pDSpinDelegateTime->setMin( 0 );

    ui->tvDebug->setItemDelegateForColumn( 0, m_pISpinDelegateId );
    ui->tvDebug->setItemDelegateForColumn( 1, m_pDSpinDelegateTime );

    //! config the obj name
    QStringList strList;
    strList <<"logout"
            <<"operate"
//            <<"dio"
//            <<"homing"
            <<"control"
            <<"debug"          
            <<"diagnosis"
              ;
    Q_ASSERT( strList.size() == ui->tabWidget->count() );
    for ( int i = 0; i < ui->tabWidget->count(); i++ )
    { ui->tabWidget->widget( i )->setObjectName( strList.at( i ) ); }

    //! terminal
    ui->joint5->setAngleVisible( true, false );

    //! disabled ui
    //! \todo for coord control
    ui->groupBox_14->setVisible( false );
}

void T4OpPanel::retranslateUi()
{
    //! base ui
    ui->retranslateUi( this );

    //! to the control status
    ui->controllerStatus->translateUi();

    //! cmb stepx
//    for( int i = 0; i < mStepxList.size(); i++ )
//    {
//        ui->cmbStepXx->setItemText( i, mStepxList.at( i ) );
//    }

    //! joint name
    ui->joint1->setJointName( tr("Base") );
    ui->joint2->setJointName( tr("Shoulder") );
    ui->joint3->setJointName( tr("Elbow") );
    ui->joint4->setJointName( tr("Wrist") );

    ui->joint5->setJointName( tr("Terminal") );

    //! monitor context
    if ( NULL != m_pActionExportImage )
    { m_pActionExportImage->setText(tr("Exmport image...")); }
    if ( NULL != m_pActionExportData )
    { m_pActionExportData->setText(tr("Exmport data...")); }
    if ( NULL != m_pActionCopy )
    { m_pActionCopy->setText(tr("Copy")); }
}

void T4OpPanel::focusInEvent(QFocusEvent *event)
{
    on_tabWidget_currentChanged( ui->tabWidget->currentIndex() );
}

void T4OpPanel::updateMonitor(QEvent *e )
{
    OpEvent *pOpEvent = (OpEvent*)e;

    Q_ASSERT( NULL != pOpEvent );
    Q_ASSERT( pOpEvent->mVar1.isValid() );

    int joint = pOpEvent->mVar1.toInt();

    //! proc the cache
    Q_ASSERT( m_pCaches[joint]->v1.size() == m_pCaches[joint]->v2.size() );

    //! has data
    if ( m_pCaches[joint]->v1.size() > 0 )
    {
        for ( int i = 0; i < m_pCaches[joint]->v1.size(); i++ )
        {

        }
    }
    //! no data
    else
    {}

    m_pCaches[joint]->mWSema.release();
}

void T4OpPanel::spyEdited()
{
    QGroupBox *gpBox[]=
    {
    };
    QCheckBox *checkBoxes[]=
    {
//        ui->chkEn
    };
    QRadioButton *radBoxes[] = {
    };
    QLineEdit *edits[]={

    };

    QSpinBox *spinBoxes[]={

    };

    QDoubleSpinBox *doubleSpinBoxes[]={
        ui->spinDly,

    };

    QComboBox *comboxes[]={
        ui->cmbStepXx,
        ui->cmbSpeed
    };

    QSlider *sliders[]
    {

    };

    install_spy();

    manual_enable_edit( ui->spinDly, true );
    manual_enable_edit( ui->cmbStepXx, true );
    manual_enable_edit( ui->cmbSpeed, true );

    //! modified
    connect( ui->controllerStatus, SIGNAL(signal_request_save()),
             this, SLOT(slot_modified()) );
}

void T4OpPanel::updateRefreshPara( QEvent *e )
{
    //! record now
    if ( m_pPlugin->m_pMissionWorking->isRunning() )
    {   ui->spinBox_RecordNumber->setSpecialValueText(mRefreshPara.recNow);
        ui->spinBox_debugRecord->setSpecialValueText(mRefreshPara.recNow);
    }

    //! target
    ui->doubleSpinBox_target_position_x->setValue( mRefreshPara.poseAim.x );
    ui->doubleSpinBox_target_position_y->setValue( mRefreshPara.poseAim.y );
    ui->doubleSpinBox_target_position_z->setValue( mRefreshPara.poseAim.z );

    //! actual
    ui->actPosX->setValue( mRefreshPara.poseNow.x );
    ui->actPosY->setValue( mRefreshPara.poseNow.y );
    ui->actPosZ->setValue( mRefreshPara.poseNow.z );

    ui->doubleSpinBox_debug_posX->setValue( mRefreshPara.poseNow.x );
    ui->doubleSpinBox_debug_posY->setValue( mRefreshPara.poseNow.y );
    ui->doubleSpinBox_debug_posZ->setValue( mRefreshPara.poseNow.z );

    ui->joint3->setDistance( mRefreshPara.poseNow.x );
    ui->joint2->setDistance( mRefreshPara.poseNow.y );
    ui->joint1->setDistance( mRefreshPara.poseNow.z );

    //! angles
    //! joint
    ui->joint1->setAngle( mRefreshPara.angles[0] );
    ui->joint2->setAngle( mRefreshPara.angles[1] );
    ui->joint3->setAngle( mRefreshPara.angles[2] );
    ui->joint4->setAngle( mRefreshPara.angles[3] );
    ui->joint5->setAngle( mRefreshPara.angles[4] );

    //! delta
    ui->joint1->setdAngle( mRefreshPara.deltaAngles[0] );
    ui->joint2->setdAngle( mRefreshPara.deltaAngles[1] );
    ui->joint3->setdAngle( mRefreshPara.deltaAngles[2] );
    ui->joint4->setdAngle( mRefreshPara.deltaAngles[3] );

    //! hand
    ui->actPosTerminal->setValue( mRefreshPara.angles[4] );

    //! home valid
    ui->radHome->setChecked( mRefreshPara.bHomeValid );

    //! \todo IOs,status,warning,error
    ui->controllerStatus->setRecordName( mRefreshPara.mRecordName );
    ui->controllerStatus->setWorkingStatus( mRefreshPara.mRoboState );
}

//! \note 24bit encoder
#define ABS_ANGLE_TO_DEG( angle )   (360.0f* ( (angle)&(0x0ffffff))) /((1<<18)-1)
int T4OpPanel::posRefreshProc( void *pContext )
{
    //! to local
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    if ( pRobo->isOpened() )
    {}
    else
    { return 0; }

    do
    {
        int ret;
        float fx,fy,fz;
        double dx,dy,dz;
        //! record now
        char t[1024];
        ret = mrgGetRobotCurrentRecord( robot_var(),
                                        t );
        if ( ret != 0 )
        { sysError( tr("Record read fail"), e_out_log ); break; }
        else
        {
            mRefreshPara.recNow = QString(t);
        }

        ret = mrgGetRobotTargetPosition( robot_var(),
                                         &fx, &fy, &fz );
        if ( ret != 0 )
        { sysError( tr("Target read fail"), e_out_log ); break; }
        else
        {
            mRefreshPara.poseAim.x = fx;
            mRefreshPara.poseAim.y = fy;
            mRefreshPara.poseAim.z = fz;
        }

        //! x,y,z now
        ret = mrgGetRobotCurrentPosition( robot_var(),
                                          &fx, &fy, &fz );
        if ( ret != 0 )
        { sysError( tr("Current read fail"), e_out_log ); break; }
        {
            mRefreshPara.poseNow.x = fx;
            mRefreshPara.poseNow.y = fy;
            mRefreshPara.poseNow.z = fz;
        }

        //! angle now
        float angles[5];

        quint32 encData;
        for ( int i = 0; i < 4; i++ )
        {
            ret = mrgMRQReportData_Query( device_var(), i, 5, &encData );
            if ( ret <= 0 )
            {sysError( tr("report data query fail"), e_out_log );break; }

            angles[i] = ABS_ANGLE_TO_DEG( encData );
        }
        if ( ret <= 0 )
        { break; }

        //! convert
        {
            mRefreshPara.angles[0] = angles[0];
            mRefreshPara.angles[1] = angles[1];
            mRefreshPara.angles[2] = angles[2];
            mRefreshPara.angles[3] = angles[3];

            //! delta angles
            double dAngles[4];
            int dir []= { -1, -1, 1, -1 };

//            double baseAngles[] = { 0, 180, 90, 90 };
            for ( int i = 0; i < 4; i++ )
            {
                dAngles[ i ] = normalizeDegreeN180_180( angles[ i ] - pRobo->mAxisZero[i] ) * dir[i];
            }

            mRefreshPara.deltaAngles[0] = dAngles[0];
            mRefreshPara.deltaAngles[1] = dAngles[1];
            mRefreshPara.deltaAngles[2] = dAngles[2];
            mRefreshPara.deltaAngles[3] = dAngles[3];
        }

        //! joint5
        ret = mrgGetRobotToolPosition( robot_var(), angles );
        if ( ret < 0 )
        { sysError( tr("get tool position fail"), e_out_log );break; }
        else
        {
            mRefreshPara.angles[4] = angles[0];
        }

        //! \todo joint5 target

        //! \todo wrist current and target

        //! \todo device status: running/stoped/error_stoped
        {
            char roboStates[128];
            ret = mrgRobotGetState( robot_var(), wave_table, roboStates );
            if ( ret != 0 )
            { sysError( tr("get state fail"), e_out_log );break; }

            mRefreshPara.mRoboState = QString( roboStates );
        }

//        mRefreshPara.mRecordName = "Record Table";

        //! home valid?
        ret = mrgGetRobotHomeRequire( robot_var() );
        {
            bool bHomeValid;
            if ( ret == 0 )             //! valid
            { bHomeValid = true; }
            else if ( ret == 1 )        //! invalid
            { bHomeValid = false; }
            else
            {
                sysError( tr("Homeing status"), e_out_log );
                break;
            }

            mRefreshPara.bHomeValid = bHomeValid;
        }

        //! post refresh
        OpEvent *updateEvent = new OpEvent( OpEvent::update_pose );
        if ( NULL != updateEvent )
        { qApp->postEvent( this, updateEvent ); }

        return 0;

    }while( 0 );

    return -1;
}

void T4OpPanel::terminalValidate( bool b )
{
    foreach( QWidget *pWig, mTerminalRelations )
    {
        Q_ASSERT( NULL != pWig );
        pWig->setVisible( b );
    }
}

int T4OpPanel::monitorRefreshProc( void *pContext )
{
    //! to local
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    if ( pRobo->isOpened() )
    {}
    else
    { return 0; }

    return 0;
}

int T4OpPanel::pingTick( void *pContext )
{
    //! to local
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    if ( pRobo->isOpened() )
    {}
    else
    { return 0; }

    //! read only one time
    int ret;
    char idn[128];
    for ( int i = 0; i < 1; i++ )
    {
        ret = mrgGateWayIDNQuery( (ViSession)pRobo->deviceVi(), idn );
        //! read fail
        if ( ret != 0 )
        {}
        else
        { return 0; }
    }

    //! try fail
    OpEvent *commFailEvent = new OpEvent( OpEvent::communicate_fail );
    if ( NULL == commFailEvent )
    {
        return 0;
    }
    else
    { }
    //! post event
    qApp->postEvent( this, commFailEvent );

    return 0;
}

int T4OpPanel::refreshDiagnosisInfo( void *pContext )
{
    //! to local
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    if ( pRobo->isOpened() )
    {}
    else
    { return 0; }

    QByteArray ary;
    ary.reserve( 4096 );

    int ret;

    ret = mrgErrorLogUpload( pRobo->deviceVi(), 0,
                             ary.data());

    //! fill the model
    if ( ret > 0 )
    {
        //! remove all
        ui->tvDiagnosis->model()->removeRows( 0, ui->tvDiagnosis->model()->rowCount() );

        ary.resize( ret );

        //! code, counter, info
        QList<QByteArray> aryList = ary.split('\n');
        QList<QByteArray> itemList;

        //! model
        DiagnosisTable *pModel = (DiagnosisTable*)ui->tvDiagnosis->model();

        int code, counter;
        bool bOk;

        foreach( QByteArray item, aryList )
        {
            itemList = item.split(',');

            if ( itemList.size() >= 3 )
            {}
            else
            { continue; }

            code = itemList.at(0).toInt( &bOk );
            if ( !bOk )
            { continue; }

            counter = itemList.at(1).toInt( &bOk );
            if ( !bOk )
            { continue; }

            pModel->append( code,
                            counter,
                            itemList.at(2)
                        );
        }
        return 0;
    }
    else
    //! \todo read error!
    { return 0; }
}

void T4OpPanel::attachWorkings()
{
    if ( sysHasArgv("-noupdate") )
    { return; }

    //! attach
    attachUpdateWorking( (XPage::procDo)( &T4OpPanel::posRefreshProc),
                         tr("Position refresh"),
                         NULL,
                         m_pPref->refreshIntervalMs() );

//    attachUpdateWorking( (XPage::procDo)( &T4OpPanel::monitorRefreshProc ),
//                         tr("Monitor refresh"),
//                         NULL,
//                         m_pPref->refreshIntervalMs() );

    attachUpdateWorking( (XPage::procDo)( &T4OpPanel::pingTick ),
                         tr("ping tick"),
                         NULL,
                         m_pPref->refreshIntervalMs() );
    //! \todo
    //! \note bypass for simplify the MRH load
    //! diagnosis
//    attachUpdateWorking( (XPage::procDo)( &T4OpPanel::refreshDiagnosisInfo ),
//                         tr("Diagnosis refresh"),
//                         NULL,
//                         m_pPref->refreshIntervalMs() );
}

void T4OpPanel::updateUi()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    ui->cmbStepXx->setCurrentIndex( pRobo->mStepIndex );
    //! \todo the display format
    ui->cmbSpeed->setCurrentText( QString("%1").arg( pRobo->mSpeed ) );

    slot_speed_verify();

    //! checked
    ui->controllerStatus->setMctChecked( pRobo->mbMctEn );
    ui->controllerStatus->setDevicePower( pRobo->mbAxisPwr );

    //! default page
    ui->tabWidget->setCurrentIndex( DEFAULT_PAGE_INDEX );

    //! update digital inputs name
    ui->radDI1->setText( pRobo->listIoName.at(0) );
    ui->radDI2->setText( pRobo->listIoName.at(1) );
    ui->radDI3->setText( pRobo->listIoName.at(2) );
    ui->radDI4->setText( pRobo->listIoName.at(3) );
    ui->radDI5->setText( pRobo->listIoName.at(4) );
    ui->radDI6->setText( pRobo->listIoName.at(5) );
    ui->radStart->setText( pRobo->listIoName.at(6) );
    ui->radReset->setText( pRobo->listIoName.at(7) );
    ui->radRDYEN->setText( pRobo->listIoName.at(8) );
    ui->radENBLE->setText( pRobo->listIoName.at(9) );
    ui->radACK->setText( pRobo->listIoName.at(10) );
    ui->radENABLED->setText( pRobo->listIoName.at(11) );
    ui->radFAULT->setText( pRobo->listIoName.at(12) );
    ui->radMC->setText( pRobo->listIoName.at(13) );
}

void T4OpPanel::updateData()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    //! save
    pRobo->mStepIndex = ui->cmbStepXx->currentIndex();
    pRobo->mSpeed = ui->cmbSpeed->currentText().toDouble();

    pRobo->mbMctEn = ui->controllerStatus->isMctChecked();
    pRobo->mbAxisPwr = ui->controllerStatus->getDevicePower();
}

void T4OpPanel::startup()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    //! operate
    setOperAble( pRobo->mbMctEn );

    if ( pRobo->mbMctEn )
    { setOnLine( pRobo->mbAxisPwr ); }
}

void T4OpPanel::updateRole()
{
    //! \note the role changed
    switchCoordMode();
}

//! exchange
int T4OpPanel::upload()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    //! \note get power
    int ret, state;
    ret = mrgMRQDriverState_Query( device_var(), 0, &state );
    if ( ret == 0 )
    {
        pRobo->mbAxisPwr = state > 0 ;
    }

    return ret;
}
int T4OpPanel::download()
{
    return 0;
}

void T4OpPanel::onSetting(XSetting setting)
{
    XPage::onSetting( setting );

    if ( (int)setting.mSetting == (int)MRX_T4::e_setting_terminal )
    {
        if ( setting.mPara1.isValid() )
        {}
        else
        { return; }

        terminalValidate( setting.mPara1.toBool() );
    }
    else if ( (int)setting.mSetting == (int)MRX_T4::e_setting_record )
    {
        bool bEn = ( setting.mPara1.toInt() > 0 );
        ui->btnAdd->setEnabled( bEn );
    }
    else
    {}
}

void T4OpPanel::home()
{
    QVariant var;

    m_pPlugin->attachMissionWorking( this, (XPage::onMsg)(&T4OpPanel::onHoming), var, tr("Homing") );
}
void T4OpPanel::fold()
{
    QVariant var;

    m_pPlugin->attachMissionWorking( this, (XPage::onMsg)(&T4OpPanel::onFolding), var, tr("Folding") );
}

double T4OpPanel::localSpeed()
{
    return ui->cmbSpeed->currentText().toDouble();
}

double T4OpPanel::localStep()
{
    Q_ASSERT( ui->cmbStepXx->currentIndex() < sizeof_array( _stepRatio) );
    return _stepRatio[ ui->cmbStepXx->currentIndex() ];
}

bool T4OpPanel::isContinous()
{ return ui->chkContinous->isChecked(); }
bool T4OpPanel::isCoordJoint()
{ return ui->radCoordJoint->isChecked(); }

void T4OpPanel::enterMission()
{
    QList<int> exceptWidget;
    exceptWidget<<WIDGET_MONITOR_INDEX;

    ui->controllerStatus->setEnabled( false );

    //! \note the page 1 is logout
    for( int i = 1; i < ui->tabWidget->count();i++ )
    {
        if ( exceptWidget.contains( i) )
        {}
        else
        { ui->tabWidget->widget( i )->setEnabled( false ); }
    }
}
void T4OpPanel::exitMission( )
{
    ui->controllerStatus->setEnabled( true );

    for( int i = 0; i < ui->tabWidget->count();i++ )
    {
        ui->tabWidget->widget( i )->setEnabled( true );
    }

    //! awake update
    m_pPlugin->awakeUpdate();
}

#define local_on_line()  ( ui->controllerStatus->getDevicePower() && ui->controllerStatus->isMctChecked() )
void T4OpPanel::setOperAble( bool b )
{
    ui->controllerStatus->setDevicePowerEnable( b );

    //! \note the page 1 is logout
    for( int i = 1; i < ui->tabWidget->count();i++ )
    {
        ui->tabWidget->widget( i )->setEnabled( b );
    }

    ui->tabWidget->widget( 2 )->setEnabled( local_on_line() );
}

void T4OpPanel::setOnLine( bool b )
{
    //! \note disable the run
    ui->tabWidget->widget( 2 )->setEnabled( local_on_line() );
    ui->toolButton_debugRun->setEnabled( local_on_line() );
}

void T4OpPanel::setOpened( bool b )
{
    //! enabled
    if ( b )
    { exitMission();  }
    //! disabled
    else
    { enterMission(); }
}

void T4OpPanel::stepProc( int jId, int dir )
{
    //! joint step
    if ( isCoordJoint() || jId >= 4 )
    {
        QList<QVariant> vars;
        vars<<(jId-1)<<dir;
        QVariant var( vars );
        on_post_setting( T4OpPanel, onJointStep, tr("Joint step") );
    }
    //! x,y,z step
    else
    {
        _step( jId == 3 ? dir : 0,
               jId == 2 ? dir : 0,
               jId == 1 ? dir : 0
               );
    }
}

void T4OpPanel::jogProc( int jId, int dir, bool b )
{
    //! jog on
    if ( b )
    {}
    else
    {
        //! \todo stop2
        onJointJogEnd();
        return;
    }

    //! joint jog
    QList<QVariant> vars;
    if ( isCoordJoint() || jId >= 4 )
    {
        vars<<(jId-1)<<dir<<1;
        QVariant var( vars );
        on_post_setting_n_mission( T4OpPanel, onJointJog, tr("Joint jog") );
    }
    //! x,y,z step
    else
    {

        QList<QVariant> vars;

        vars<<(double)(jId == 3 ? dir : 0)
            <<(double)(jId == 2 ? dir : 0)
            <<(double)(jId == 1 ? dir : 0)
            <<localSpeed();

        QVariant var( vars );

        on_post_setting_n_mission( T4OpPanel, onTcpJog, tr("TCP jog") );
    }
}

void T4OpPanel::_step( double x, double y, double z )
{
    QList<QVariant> vars;

    double rat = localStep();

    vars<<x * rat <<y * rat <<z * rat <<localSpeed() / 100.0;

    QVariant var( vars );

    on_post_setting( T4OpPanel, onStep, tr("Step") );
    logDbg()<<QThread::currentThreadId();
}

int T4OpPanel::onStep( QVariant var )
{
    check_connect_ret( -1 );

    QList<QVariant> vars;

    vars = var.toList();
logDbg()<<QThread::currentThreadId()
       <<vars.at(0).toDouble()
      <<vars.at(1).toDouble()
      <<vars.at(2).toDouble();

        float dist =  MRX_T4::eulaDistance( 0,0,0,
                                        vars.at(0).toDouble(),
                                        vars.at(1).toDouble(),
                                        vars.at(2).toDouble() );

        //! percent * max speed
        float t = dist / ( vars.at(3).toDouble() * pRobo->mMaxTerminalSpeed );
logDbg()<<t<<vars.at(3).toDouble()<<dist<<guess_dist_time_ms( t, dist );
        //! wait idle
        //! \todo speed
        int ret = mrgRobotRelMove( robot_var(),
                                   wave_table,
                                   vars.at(0).toDouble(),
                                   vars.at(1).toDouble(),
                                   vars.at(2).toDouble(),
                                   t,
                                   guess_dist_time_ms( t, dist )
                                   );

    logDbg()<<ret;
    return ret;
}

int T4OpPanel::onHoming( QVariant var )
{
    check_connect_ret( -1 );

    int ret;
logDbg()<<pRobo->mHomeTimeout;
    ret = mrgRobotGoHome( robot_var(),
                          pRobo->mHomeTimeout*1000 );
logDbg();
    return ret;
}

int T4OpPanel::onFolding( QVariant var )
{
    check_connect_ret( -1 );

    int ret;

    ret = mrgSetRobotFold( robot_var(),
                           pRobo->mPackagesAxes[0],
                           pRobo->mPackagesAxes[1],
                           pRobo->mPackagesAxes[2],
                           pRobo->mPackagesAxes[3],
                           120000);
    return ret;
}

int T4OpPanel::onJointStep( QVariant var /*int jId, int dir*/ )
{
    check_connect_ret( -1 );

    int jId, dir;

    QList<QVariant> vars;

    vars = var.toList();
    jId = vars[0].toInt();
    dir = vars[1].toInt();

    float t, p;

    double stp = localStep();

    double spd = pRobo->mMaxJointSpeeds.at(jId) * localSpeed() / 100.0;

    int ret = mrgMRQAdjust( device_var(), jId, 0, dir * stp, stp/spd, guess_dist_time_ms( stp/spd, stp ) );
    return ret;
}
int T4OpPanel::onJointZero( QVariant var )
{logDbg();
    check_connect_ret( -1 );

    int jId, dir;

    QList<QVariant> vars;

    vars = var.toList();
    jId = vars[0].toInt();
    dir = vars[1].toInt();

    //! \todo
    //! joint home speed
    int ret = mrgRobotJointHome( robot_var(),
                       jId,
                       20,
                       guess_dist_time_ms( 360/20, 20 ) );

    return ret;
}

int T4OpPanel::onJointJog( QVariant var )
{
    check_connect_ret( -1 );

    int jId, dir, btnId;

    QList<QVariant> vars;

    vars = var.toList();
    jId = vars[0].toInt();
    dir = vars[1].toInt();
    btnId = vars[2].toInt();

    double speed = pRobo->mMaxJointSpeeds.at(jId) * localSpeed() / 100.0;

    int ret = -1;
    //! \todo stop2
    if(btnId){
        ret = mrgRobotJointMoveOn( robot_var(), jId, speed*dir);
    }else{
        ret = mrgRobotStop( robot_var(), 0);
    }
    return ret;
}

void T4OpPanel::onJointJogEnd( )
{
    int ret = m_pPlugin->stop();
    if ( ret != 0 )
    {
        sysError( tr("Jog end fail") );
    }
}

int T4OpPanel::onTcpJog( QVariant var )
{
    check_connect_ret( -1 );

    QList<QVariant> vars;

    vars = var.toList();

    return mrgRobotMoveOn( robot_var(), 0,
                    vars.at(0).toDouble(),
                    vars.at(1).toDouble(),
                    vars.at(2).toDouble(),
                    vars.at(3).toDouble() * pRobo->mMaxTerminalSpeed / 100 );

}

int T4OpPanel::onSequence( QVariant var )
{
    check_connect_ret( -1 );
logDbg()<<QThread::currentThreadId();
    //! proc the sequence

    int ret = _onSequence( var );

    //! exec fail
    if ( ret != 0 )
    {
        sysError( tr("Exec fail") );
    }

    mSeqMutex.lock();
        delete_all( mSeqList );
    mSeqMutex.unlock();

    return ret;
}

int T4OpPanel::_onSequence( QVariant var )
{
    int ret;

    //! rpp
    Q_ASSERT( NULL != m_pPlugin->pref() );
    if ( m_pPlugin->pref()->mbAutoRpp )
    {
        check_connect_ret( -1 );
        ret = mrgRobotGoHome( robot_var(),
                              pRobo->mHomeTimeout*1000 );
        if ( ret != 0 )
        {
            sysError( tr("RPP fail") );
            return ret;
        }
    }

    //! find the first line
    int anchorSeq = -1;
    for( int i = 0; i < mSeqList.size(); i++ )
    {
        if ( mSeqList.at(i)->mbAnchor )
        {
            anchorSeq = i;
            break;
        }
    }

    if ( anchorSeq < 0 )
    {
        sysError( tr("Anchor fail") );
        return -2;
    }

    //! do loop
    QVariantList vars;
    do
    {
        for( int i = anchorSeq; i < mSeqList.size(); i++, anchorSeq = 0 )
        {
            if ( QThread::currentThread()->isInterruptionRequested() )
            { return 0; }

            //! enter
            vars.clear();
            vars<<mSeqList.at(i)->x
                <<mSeqList.at(i)->y
                <<mSeqList.at(i)->z
                <<mSeqList.at(i)->pw
                <<mSeqList.at(i)->h;
            post_debug_enter( mSeqList.at(i)->id, mSeqList.at(i)->vRow, vars );

            //! enable?
            if ( procSequenceEn( mSeqList.at( i )) )
            {
                ret = procSequence( mSeqList.at( i ) );
                //! \todo the action delay
                if ( ret == 0 )
                {
                    if ( mSeqList.at(i)->delay > 0 )
                    {
                        //! sleep s
                        QThread::sleep( mSeqList.at(i)->delay );
                    }
                    else
                    {}

                    //! exit
                    post_debug_exit( mSeqList.at(i)->id, mSeqList.at(i)->vRow );
                }
                //! exec fail
                else
                {
                    //! exit
                    post_debug_exit( mSeqList.at(i)->id, mSeqList.at(i)->vRow );

                    return -1;
                }
            }
            else
            {
                post_debug_exit( mSeqList.at(i)->id, mSeqList.at(i)->vRow );
            }

        }
    }while( ui->chkCyclic->isChecked() );

    //! cyclic
    if ( ui->chkCyclic->isChecked() )
    {}
    else
    {
        sysPrompt( tr("Single execute completed"), 0 );
    }

    return 0;
}

bool T4OpPanel::procSequenceEn( SequenceItem* pItem )
{
    Q_ASSERT( NULL != pItem );
    check_connect_ret( false );

    return ( pItem->bValid );
}

//int vRow;
//QString mType;
//double x, y, z, pw, h, v, line;
//do
//double delay;

int T4OpPanel::procSequence( SequenceItem* pItem )
{
    Q_ASSERT( NULL != pItem );
    check_connect_ret( -1 );
    int ret;
    if ( str_is( pItem->mType, "PA") )
    {
        ret = pRobo->absMove( "",
                              pItem->x, pItem->y, pItem->z,
                              pItem->pw, pItem->h,
                              rel_to_abs_speed( pItem->v ), pItem->bLine );
    }
    else if ( str_is( pItem->mType, "PRA")
              || str_is( pItem->mType, "PRN"))
    {
        ret = pRobo->relMove( "",
                              pItem->x, pItem->y, pItem->z,
                              pItem->pw, pItem->h,
                              rel_to_abs_speed( pItem->v ), pItem->bLine );
    }
    else
    { return -1; }

    //! \note print comment
    if ( pItem->mComment.length() > 0 )
    {
        mDebugConsoleModel.append( pItem->mComment );
    }

    //! \todo DO
    int iVal = pItem->mDo;
    for( int i = 0; i < 2; i++ ){
        int t = iVal & 0x03;
        //! set io state
        switch(t)
        {
            case 0x02:   /* low 10*/
                //mrgProjectSetYout(device_var_vi(), i, 0);
                mrgProjectIOSet(device_var_vi(), IOSET_INDEX(i+1),0);
                break;
            case 0x00:   /*reserve 00*/
                break;
            case 0x03:   /* high 11*/
                //mrgProjectSetYout(device_var_vi(), i, 1);
                mrgProjectIOSet(device_var_vi(), IOSET_INDEX(i+1), 1);
                break;
        }
        iVal = iVal >> 2;
    }

    //! \todo Wrist move
    float angle,speed;
    angle = pItem->pw;
    speed = pRobo->mMaxJointSpeeds.at(3) * pItem->v / 100.0;

    ret = mrgSetRobotWristPose(robot_var(), 0, angle, speed, guess_dist_time_ms( 180/speed, 180 ));
    logDbg() << angle << speed << ret;
    if( ret != 0 )
        return ret;

    //! \todo Terminal move
    speed = pRobo->mMaxJointSpeeds.at(4) * pItem->v / 100.0;
    //ret = mrgRobotToolExe(robot_var(), pItem->h, 80/speed, guess_dist_time_ms( 80/speed, 80 ));
    ret = mrgRobotJointMove(robot_var(), 4, pItem->h, 80/speed, guess_dist_time_ms( 80/speed, 80 ));

    return ret;
}


int T4OpPanel::exportDataSets( QTextStream &stream,
                               QStringList &headers,
                               QList<PlotDataSets*> &dataSets )
{
    //! headers
    foreach( const QString &str, headers )
    {
       stream<<str<<",";
    }
    stream<<"\n";

    //! for each dataset
    QPointF a,b;
    bool bRet;
    bool bEnd;
    for ( ;; )
    {
        //! check end
        bEnd = true;
        for( int i = 0; i < dataSets.size(); i++ )
        {
            if ( dataSets[i]->isEnd() )
            { }
            else
            { bEnd = false; break; }
        }

        if ( bEnd )
        { break; }

        //! for each data sets
        for ( int i = 0; i < dataSets.size(); i++ )
        {
            bRet = dataSets[i]->getNext( a, b );
            if ( bRet )
            { stream<<a.x()<<","<<a.y()<<","<<b.y()<<","; }
            else
            { stream<<",,,"; }
        }

        stream<<"\n";
    }

    return 0;
}

//! switch mode
void T4OpPanel::switchCoordMode()
{
    bool bAbsAngleVisible = ( sysMode() == sysPara::e_sys_admin);

    //! joint
    if ( ui->radCoordJoint->isChecked() )
    {
        ui->joint1->setJointName( tr("Base") );
        ui->joint2->setJointName( tr("Shoulder") );
        ui->joint3->setJointName( tr("Elbow") );

        ui->joint1->setAngleVisible( bAbsAngleVisible, true );
        ui->joint2->setAngleVisible( bAbsAngleVisible, true );
        ui->joint3->setAngleVisible( bAbsAngleVisible, true );
        ui->joint4->setAngleVisible( bAbsAngleVisible, true );

        ui->joint1->setViewMode( Joint::view_angle );
        ui->joint2->setViewMode( Joint::view_angle );
        ui->joint3->setViewMode( Joint::view_angle );

        ui->label_2->setPixmap( QPixmap(":/res/image/t4/sinanju_pn_256px_nor@2x.png"));
    }
    //! x/y/z
    else
    {
        ui->joint1->setJointName( "Z" );
        ui->joint2->setJointName( "Y" );
        ui->joint3->setJointName( "X" );

        ui->joint1->setAngleVisible( false, false );
        ui->joint2->setAngleVisible( false, false );
        ui->joint3->setAngleVisible( false, false );
        ui->joint4->setAngleVisible( bAbsAngleVisible, true );

        ui->joint1->setViewMode( Joint::view_distance );
        ui->joint2->setViewMode( Joint::view_distance );
        ui->joint3->setViewMode( Joint::view_distance );

        ui->label_2->setPixmap( QPixmap(":/res/image/t4/mrx-mrx-t4_geo.png"));
    }

    //! \todo other apis
}


void T4OpPanel::slot_mct_checked( bool b )
{
    check_connect( );

    //! \todo
    //!
    pRobo->setOperateAble( b );
}
void T4OpPanel::slot_pwr_checked( bool b )
{
    check_connect( );

    int ret;
    for ( int jId = 0; jId < 5; jId++ )
    {
        ret = mrgMRQDriverState( device_var(), jId, b );
    }

    if ( ret != 0 )
    { sysError( tr("power config fail") );}

    //! operable
    pRobo->setOnLine( b );
}
void T4OpPanel::slot_ack_error()
{
    check_connect( );

    int ret = mrgErrorLogClear( pRobo->deviceVi() );
    if ( ret != 0 )
    { sysError( tr("ack_error") );}
}

void T4OpPanel::slot_save_debug()
{
    Q_ASSERT( NULL != m_pPlugin );
    int ret;

    //! debug
    QString fileName = m_pPlugin->homePath() + "/debug.xml";
    ret = mDebugTable.save( fileName );
    if ( ret != 0 )
    {
        sysError( fileName + tr(" save fail") );
    }
    logDbg();
}
void T4OpPanel::slot_save_diagnosis()
{
    Q_ASSERT( NULL != m_pPlugin );
    int ret;

    //! diagnosis
    QString fileName = m_pPlugin->homePath() + "/diagnosis.xml";
    ret = mDiagTable.save( fileName );
    if ( ret != 0 )
    {
        sysError( fileName + tr(" load fail") );
    }
}

void T4OpPanel::slot_request_save()
{
    slot_save_debug();

    slot_save_diagnosis();
}
void T4OpPanel::slot_request_load()
{
    Q_ASSERT( NULL != m_pPlugin );
    int ret;
    QString fileName = m_pPlugin->homePath() + "/debug.xml";
    ret = mDebugTable.load( fileName );
    if ( ret != 0 )
    {
        sysError( fileName + tr(" load fail") );
    }

    fileName = m_pPlugin->homePath() + "/diagnosis.xml";
    ret = mDiagTable.load( fileName );
    if ( ret != 0 )
    {
        sysError( fileName + tr(" load fail") );
    }
}

void T4OpPanel::slot_debug_table_changed()
{
    //! update the enable
    if ( ui->tvDebug->model()->rowCount() > 0 )
    {
        ui->btnExport->setEnabled( true );
        ui->btnClr->setEnabled( true );
    }
    else
    {
        ui->btnExport->setEnabled( false );
        ui->btnClr->setEnabled( false );
    }

    QModelIndex curIndex = ui->tvDebug->currentIndex();
    if ( curIndex.isValid() )
    {
        ui->btnDel->setEnabled( true );
    }
    else
    {
        ui->btnDel->setEnabled( false );

        ui->btnUp->setEnabled( false );
        ui->btnDown->setEnabled( false );

        return;
    }

    if ( ui->tvDebug->model()->rowCount() > 1 )
    {}
    else
    {
        ui->btnUp->setEnabled( false );
        ui->btnDown->setEnabled( false );

        return;
    }

    if ( curIndex.row() > 0 )
    { ui->btnUp->setEnabled( true ); }
    else
    { ui->btnUp->setEnabled( false ); }

    if ( curIndex.row() < ui->tvDebug->model()->rowCount() - 1 )
    { ui->btnDown->setEnabled(true); }
    else
    { ui->btnDown->setEnabled( false ); }
}

void T4OpPanel::slot_debug_current_changed( int cur )
{
    QModelIndex index = ui->tvDebug->model()->index( cur,  ui->tvDebug->currentIndex().column() );

    ui->tvDebug->setCurrentIndex( index );
}

void T4OpPanel::slot_customContextMenuRequested( const QPoint &pt )
{
    if ( ui->tvDebug->currentIndex().isValid() )
    {
        if(m_pDebugContextMenu == NULL )
        {
            m_pDebugContextMenu = new QMenu(ui->tvDebug);
            if ( NULL == m_pDebugContextMenu )
            { return; }

            QAction *actionToHere = m_pDebugContextMenu->addAction(tr("To Here"));
            if ( NULL == actionToHere )
            { return; }

            connect(actionToHere, SIGNAL(triggered(bool)),
                    this, SLOT( slot_toHere( ) ) );
        }
        else
        {}

        m_pDebugContextMenu->exec(QCursor::pos());
    }
}

void T4OpPanel::slot_toHere()
{
    //! \todo
}

void T4OpPanel::slot_digitalInputsCustomContextMenuRequested( const QPoint &p )
{logDbg();

    IoIndicator *pIoState = dynamic_cast<IoIndicator *>(sender());

    if( m_pIOContextMenu == NULL ){
        m_pIOContextMenu = new QMenu( ui->groupBox );
        if( m_pIOContextMenu ==NULL ){
        return;
    }
    m_pActionRename = m_pIOContextMenu->addAction( tr( "Rename" ) );
    if( m_pActionRename == NULL ){
        delete m_pIOContextMenu;
        m_pIOContextMenu = NULL;
        return;
    }
    m_pActionRename->setIcon( QIcon(":/res/image/icon/stealth.png") );

    connect( m_pActionRename, SIGNAL( triggered(bool)), this, SLOT(slot_Rename()) );

    }else{
    }
    currentRenameObj = pIoState;
    m_pIOContextMenu->exec(QCursor::pos());
}

void T4OpPanel::slot_Rename()
{logDbg();

    bool ok;
    QRegExp regExp("\\w+");
    regExp.setPatternSyntax(QRegExp::Wildcard);
    QString text=RegExpInputDialog::getText(this, tr("Rename"), tr("New Name"), currentRenameObj->text(), regExp, &ok);

    if (ok && !text.isEmpty()){
        if( currentRenameObj ){
            currentRenameObj->setText(text);

            //! update config.xml
            MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
            Q_ASSERT( pRobo != NULL );

            pRobo->listIoName.clear();
            pRobo->listIoName << ui->radDI1->text() << ui->radDI2->text() << ui->radDI3->text() << ui->radDI4->text() << ui->radDI5->text()
                              << ui->radDI6->text() << ui->radStart->text() << ui->radReset->text() << ui->radRDYEN->text() << ui->radENBLE->text()
                              << ui->radACK->text() << ui->radENABLED->text() << ui->radFAULT->text() << ui->radMC->text();

            //t->emit_save(); not work
            pRobo->save( pRobo->homePath() + "/" + "config.xml" );
        }
    }
}

void T4OpPanel::slot_debug_delete()
{
    if ( ui->btnDel->isEnabled() )
    { on_btnDel_clicked(); }
}
void T4OpPanel::slot_debug_insert()
{
    if ( ui->btnAdd->isEnabled() )
    { on_btnAdd_clicked(); }
}

//! xyz:
//! step:   v:(%)
//! ~10]    ~5]
//! ~50]     ~20]
//! ~100]    ~100]
//! joint
//! ~10]    ~5]
//! ~50]    ~20]
//! ~100]   ~100]
void T4OpPanel::slot_speed_verify()
{
    QList<int> speedList;
    speedList<<1<<5<<10<<20<<50<<100;

    QList<float> stepList;
    stepList<<0.1<<0.5<<1<<5<<10<<50<<100;

    //! x,y,z
    int maxSpeed;
    if ( ui->radCoordXyz->isChecked() )
    {
        if ( stepList.at( ui->cmbStepXx->currentIndex()) <= 10 )
        { maxSpeed=5; }
        else if ( stepList.at( ui->cmbStepXx->currentIndex()) <= 50 )
        { maxSpeed = 20; }
        else
        { maxSpeed = 100; }
    }
    //! joint
    else
    {
        if ( stepList.at( ui->cmbStepXx->currentIndex()) <= 10 )
        { maxSpeed=10; }
        else if ( stepList.at( ui->cmbStepXx->currentIndex()) <= 50 )
        { maxSpeed = 20; }
        else
        { maxSpeed = 100; }
    }

    //! remove all
    int curIndex;
    curIndex = ui->cmbSpeed->currentIndex();
    for ( int i = ui->cmbSpeed->count(); i >=0 ; i-- )
    {
        ui->cmbSpeed->removeItem( i );
    }

    //! add again
    for ( int i = ui->cmbSpeed->count();
          i < speedList.size();
          i++ )
    {
        if ( speedList.at(i) <= maxSpeed )
        {
            ui->cmbSpeed->addItem( QString::number( speedList.at(i) ) );
        }
        else
        { break; }
    }

    //! change the cur index
    if ( curIndex > ui->cmbSpeed->count() )
    {
        ui->cmbSpeed->setCurrentIndex( ui->cmbSpeed->count() -1 );
        sysPrompt( tr("Current speed changed"), 0 );
    }
    else
    {
        ui->cmbSpeed->setCurrentIndex( curIndex );
    }
}

void T4OpPanel::on_toolSingleAdd_clicked()
{
    //! add to the record
    Q_ASSERT( NULL != m_pPlugin );

    QVariant var;
    QList<QVariant> coords;

    coords.append( ui->joint3->getDistance() );
    coords.append( ui->joint2->getDistance() );
    coords.append( ui->joint1->getDistance() );

    coords.append( ui->joint4->getdAngle() );
    coords.append( ui->joint5->getAngle() );

    var.setValue( coords );

    m_pPlugin->emit_setting_changed( (eXSetting)(MRX_T4::e_add_record), var );
}

void T4OpPanel::on_toolSingleEdit_clicked()
{
    //! add to the record
    Q_ASSERT( NULL != m_pPlugin );

    QVariant var;
    QList<QVariant> coords;

    coords.append( ui->joint3->getDistance() );
    coords.append( ui->joint2->getDistance() );
    coords.append( ui->joint1->getDistance() );

    coords.append( ui->joint4->getdAngle() );
    coords.append( ui->joint5->getAngle() );

    var.setValue( coords );

    m_pPlugin->emit_setting_changed( (eXSetting)(MRX_T4::e_edit_record), var );
}

//! debug tab
void T4OpPanel::on_btnImport_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptOpen );
    fDlg.setNameFilter( tr("Debug(*.dbg)") );
    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    QString fileName;
    fileName = fDlg.selectedFiles().first();

    DebugTable *pModel = (DebugTable*)ui->tvDebug->model();
    Q_ASSERT( NULL != pModel );

    int ret;
    ret = pModel->load( fileName );
    if ( ret != 0 )
    { sysError( fileName + " " + tr("save fail") );}
    else
    {}
}

void T4OpPanel::on_btnExport_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptSave );
    fDlg.setNameFilter( tr("Debug(*.dbg)") );
    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    QString fileName;
    fileName = fDlg.selectedFiles().first();

    DebugTable *pModel = (DebugTable*)ui->tvDebug->model();
    Q_ASSERT( NULL != pModel );

    int ret;
    ret = pModel->save( fileName );
    if ( ret != 0 )
    { sysError( fileName + " " + tr("save fail") );}
    else
    {}
}

void T4OpPanel::on_btnAdd_clicked()
{
    //! \todo
    QAbstractItemModel *pModel;
    pModel = ui->tvDebug->model();
    if ( NULL == pModel )
    { return; }

    //! current row
    int cRow;
    QModelIndex index = ui->tvDebug->currentIndex();
    if ( index.isValid() )
    { cRow = index.row() + 1;  }
    else
    { cRow = pModel->rowCount(); }

    //! check current index
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );
    if ( pRobo->currentRecordIndex() >= 0 )
    {}
    else
    { return; }

    //! insert
    if ( pModel->insertRow( cRow ) )
    { logDbg(); }
    else
    { logDbg(); return; }

    //! from index
    QModelIndex modelIndex;

    //! current
    modelIndex = pModel->index( cRow, 0 );
    ui->tvDebug->setCurrentIndex( modelIndex );
    ui->tvDebug->scrollTo( modelIndex );

    //! id
    modelIndex = pModel->index( cRow, 0 );
    { pModel->setData( modelIndex, pRobo->currentRecordIndex() + 1 ); }

    //! delay
    modelIndex = pModel->index( cRow, 1 );
    pModel->setData( modelIndex, ui->spinDly->value() );
}

void T4OpPanel::on_btnDel_clicked()
{
    QModelIndex modelIndex;

    modelIndex = ui->tvDebug->currentIndex();
    if ( modelIndex.isValid() )
    {}
    else
    { return; }

    ui->tvDebug->model()->removeRow( modelIndex.row() );
}

void T4OpPanel::on_btnClr_clicked()
{
    int rCount = ui->tvDebug->model()->rowCount();
    if ( rCount > 0 )
    {
        ui->tvDebug->model()->removeRows( 0, rCount );
    }
}

void T4OpPanel::on_btnUp_clicked()
{
    QModelIndex modelIndex = ui->tvDebug->currentIndex();
    if ( modelIndex.isValid() )
    {}
    else
    { return; }

    if ( modelIndex.row() > 0 )
    {
        DebugTable *pModel = (DebugTable*)ui->tvDebug->model();
        Q_ASSERT( NULL != pModel );
        pModel->exchange( modelIndex.row(), modelIndex.row() - 1  );

        //! change current index
        modelIndex = pModel->index( modelIndex.row() - 1, modelIndex.column() );
        ui->tvDebug->setCurrentIndex( modelIndex );
    }
}

void T4OpPanel::on_btnDown_clicked()
{
    QModelIndex modelIndex = ui->tvDebug->currentIndex();
    if ( modelIndex.isValid() )
    {}
    else
    { return; }

    if ( modelIndex.row() < ui->tvDebug->model()->rowCount() - 1 )
    {
        DebugTable *pModel = (DebugTable*)ui->tvDebug->model();
        Q_ASSERT( NULL != pModel );
        pModel->exchange( modelIndex.row(), modelIndex.row() + 1  );

        //! change current index
        modelIndex = pModel->index( modelIndex.row() + 1, modelIndex.column() );
        ui->tvDebug->setCurrentIndex( modelIndex );
    }
}

//! diagnosis   set invisiable
void T4OpPanel::on_btnRead_clicked()
{
//    check_connect();

//    QByteArray ary;
//    ary.reserve( 4096 );

//    int ret;

//    ret = mrgErrorLogUpload( pRobo->deviceVi(), 0,
//                             ary.data());

//    //! fill the model
//    if ( ret > 0 )
//    {
//        //! remove all
//        ui->tvDiagnosis->model()->removeRows( 0, ui->tvDiagnosis->model()->rowCount() );

//        ary.resize( ret );

//        //! code, counter, info
//        QList<QByteArray> aryList = ary.split('\n');
//        QList<QByteArray> itemList;

//        //! model
//        DiagnosisTable *pModel = (DiagnosisTable*)ui->tvDiagnosis->model();

//        int code, counter;
//        bool bOk;

//        foreach( QByteArray item, aryList )
//        {
//            itemList = item.split(',');

//            if ( itemList.size() >= 3 )
//            {}
//            else
//            { continue; }

//            code = itemList.at(0).toInt( &bOk );
//            if ( !bOk )
//            { continue; }

//            counter = itemList.at(1).toInt( &bOk );
//            if ( !bOk )
//            { continue; }

//            pModel->append( code,
//                            counter,
//                            itemList.at(2)
//                        );
//        }
//    }
//    else
//    {}
}

void T4OpPanel::on_btnDelete_clicked()
{
    int rCount = ui->tvDiagnosis->model()->rowCount();
    if ( rCount > 0 )
    {
        ui->tvDiagnosis->model()->removeRows( 0, rCount );
    }
}

void T4OpPanel::on_btnExport_2_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptSave );
    fDlg.setNameFilter( tr("Diagnosis(*.dia)") );
    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    QString fileName;
    fileName = fDlg.selectedFiles().first();

    DiagnosisTable *pModel = (DiagnosisTable*)ui->tvDiagnosis->model();
    Q_ASSERT( NULL != pModel );

    int ret;
    ret = pModel->save( fileName );
    if ( ret != 0 )
    { sysError( fileName + " " + tr("save fail") );}
    else
    {}
}

//! joint op.
#define on_joint_actions( id ) \
void T4OpPanel::on_joint##id##_signal_zero_clicked() \
{\
    QList<QVariant> vars;\
    vars<<(id-1)<<1; \
    QVariant var( vars );\
    on_post_setting( T4OpPanel, onJointZero, tr("Joint zero") );\
}\
void T4OpPanel::on_joint##id##_signal_single_add_clicked() \
{ \
    if ( isContinous() ) \
    { return;}\
    else\
    {}\
\
    stepProc( id, 1 );\
} \
void T4OpPanel::on_joint##id##_signal_single_sub_clicked() \
{ \
    if ( isContinous() ) \
    { return;}\
    else\
    {}\
    \
    stepProc( id, -1 );\
}\
void T4OpPanel::on_joint##id##_signal_single_add_pressed() \
{ \
    if ( !isContinous() ) \
    { return;}\
    else\
    {}\
    jogProc( id, 1, true );\
}\
void T4OpPanel::on_joint##id##_signal_single_add_released() \
{ \
    if ( !isContinous() ) \
    { return;}\
    else\
    {}\
    jogProc( id, 1, false );\
}\
void T4OpPanel::on_joint##id##_signal_single_sub_pressed() \
{ \
    if ( !isContinous() ) \
    { return;}\
    else\
    {}\
    jogProc( id, -1, true );\
}\
void T4OpPanel::on_joint##id##_signal_single_sub_released() \
{\
    if ( !isContinous() ) \
    { return;}\
    else\
    {}\
    jogProc( id, -1, false );\
}

on_joint_actions( 1 )
on_joint_actions( 2 )
on_joint_actions( 3 )
on_joint_actions( 4 )

on_joint_actions( 5 )

void T4OpPanel::on_tabWidget_currentChanged(int index)
{
    emit signal_focus_changed( m_pPlugin->model(),
                               ui->tabWidget->currentWidget()->objectName() );
}

//! sequence
int T4OpPanel::buildSequence( QList<SequenceItem*> &list )
{
    check_connect_ret( -1 );

    //! export the debug list
    QVariant var1, var2;
    SequenceItem *pItem;
    bool bOk;

    int id;
    double delay;

    QList< QVector<QVariant> > varList;
    QVector<QVariant> var;
    for ( int i = 0; i < ui->tvDebug->model()->rowCount(); i++ )
    {

        var1 = ui->tvDebug->model()->data(  ui->tvDebug->model()->index(i,0) );
        var2 = ui->tvDebug->model()->data(  ui->tvDebug->model()->index(i,1) );

        //! valid?
        if ( !var1.isValid() || !var2.isValid() )
        { return -1; }

        //! return
        id = var1.toInt( &bOk );
        if ( !bOk ){ return -1; }
        delay = var2.toDouble( &bOk );
        if ( !bOk ){ return -1; }

        //! plane tree
        varList.clear();
        //! \note id from 1
        pRobo->m_pRecordModel->planeTree(
                                            pRobo->m_pRecordModel->index( id - 1, 0 ),
                                            varList
                                        );

        //! create the sequence list
//        headers<<"id"<<"type"<<"coord"<<"para"
//               <<"x"<<"y"<<"z"<<"w"<<"h"<<"v"<<"a"
//               <<"comment";
        for( int j = 0; j < varList.size(); j++ )
        {
            pItem = new SequenceItem();
            if ( NULL == pItem )
            { return -1; }

            pItem->id = id;
            pItem->vRow = i;

            var = varList.at(j);
            pItem->bValid = var.at(0).toBool();
            pItem->mType = var.at( 2 ).toString();
            pItem->x = var.at( 3 ).toDouble();
            pItem->y = var.at( 4 ).toDouble();
            pItem->z = var.at( 5 ).toDouble();

            pItem->pw = var.at( 6 ).toDouble();
            pItem->h = var.at( 7 ).toDouble();

            pItem->v = var.at( 8 ).toDouble();
            pItem->bLine = var.at( 9 ).toBool();
            pItem->mDo = var.at( 10 ).toInt();
            pItem->delay = var.at( 11 ).toDouble();

            pItem->mComment = var.at( 12 ).toString();

            //! \note split the first anchor
            if ( i == ui->tvDebug->currentIndex().row() && j == 0 )
            { pItem->mbAnchor = true; }
            else
            { pItem->mbAnchor = false; }

            //! \note the last one
            if ( j == varList.size() - 1 )
            { pItem->delay += delay; }

            list.append( pItem );
        }
    }

    return 0;
}

void T4OpPanel::post_debug_enter( int id, int r, QVariantList vars )
{
    OpEvent *pEvent= new OpEvent( OpEvent::debug_enter, mRefreshPara.recNow, r );
    if ( NULL == pEvent )
    { return; }

    pEvent->setVars( vars );

    qApp->postEvent( this, pEvent );
//

}
void T4OpPanel::post_debug_exit( int id, int r )
{

}

void T4OpPanel::on_debug_enter( QString recordNow, int r, QVariantList &vars )
{
    ui->tvDebug->selectRow( r );
    ui->spinBox_debugRecord->setSpecialValueText(recordNow);
    ui->spinBox_RecordNumber->setSpecialValueText(recordNow);

    ui->doubleSpinBox_target_position_x->setValue( vars.at(0).toDouble() );
    ui->doubleSpinBox_target_position_y->setValue( vars.at(1).toDouble() );
    ui->doubleSpinBox_target_position_z->setValue( vars.at(2).toDouble() );
    ui->spinWristTarget->setValue( vars.at(3).toDouble() );
    ui->spinTerminalTarget->setValue( vars.at(4).toDouble() );

}
void T4OpPanel::on_debug_exit( int id, int r )
{

}

//! start the run thread
void T4OpPanel::on_toolButton_debugRun_clicked()
{
    //! invalid row
    if ( !ui->tvDebug->currentIndex().isValid() && ui->tvDebug->model()->rowCount() > 0 )
    { ui->tvDebug->selectRow( 0 ); }

    //! build
    mSeqMutex.lock();
        delete_all( mSeqList );
        buildSequence( mSeqList );
    mSeqMutex.unlock();

    logDbg()<<mSeqList.size();
    for ( int i = 0; i < mSeqList.size(); i++ )
    {
        logDbg()<<i
                <<mSeqList.at(i)->vRow
                <<mSeqList.at(i)->mType
                <<mSeqList.at(i)->x
                <<mSeqList.at(i)->y
                <<mSeqList.at(i)->z
                <<mSeqList.at(i)->v
                <<mSeqList.at(i)->pw
                <<mSeqList.at(i)->h
                <<mSeqList.at(i)->bLine;

    }

    if ( mSeqList.size() > 0 )
    {}
    else
    { return; }

    //! vars
    QVariant var;
    on_post_setting( T4OpPanel, onSequence, "Debug" );

}

void T4OpPanel::on_radCoordXyz_clicked()
{
    switchCoordMode();
}

void T4OpPanel::on_radCoordJoint_clicked()
{
    switchCoordMode();
}

}


