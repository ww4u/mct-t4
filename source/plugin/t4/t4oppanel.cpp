#include "t4oppanel.h"
#include "ui_t4oppanel.h"

#include <QFileDialog>

#include "../../plugin/plugin/xplugin.h"

#include "MegaGateway.h"

#include "../../plugin/t4/t4.h"

#include "comassist.h"

#include "../model/debugtable.h"

#define WIDGET_MONITOR_INDEX 5
#define DEFAULT_PAGE_INDEX 4
namespace mrx_t4{

static double _stepRatio[]={ 0.1,0.2,0.5,
                            1,2,5,
                            10,20,50,
                            100 };

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
//    for ( int i = 0; i < ui->cmbStepXx->count(); i++ )
//    {
//        strRaw = ui->cmbStepXx->itemText( i );
//        strDecimal = strRaw;
//        strDecimal.remove(0,1);        //! remove the X
//        strComment = QString("%1 [%2%3]").arg(strRaw).arg( strDecimal).arg( char_deg );
//        mStepxList<<strComment;
//    }
    for ( int i = 0; i < ui->roboControlBar->count(); i++ ){
        strRaw = ui->roboControlBar->combContent( i );
        strDecimal = strRaw;
        strDecimal.remove(0,1);        //! remove the X
        strComment = QString("%1 [%2%3 or mm]").arg(strRaw).arg( strDecimal).arg( char_deg );
        mStepxList<<strComment;
    }

    for ( int i = 0; i < ui->controlBar->count(); i++ ){
        strRaw = ui->controlBar->combContent( i );
        strDecimal = strRaw;
        strDecimal.remove(0,1);        //! remove the X
        strComment = QString("%1 [%2%3 or mm]").arg(strRaw).arg( strDecimal).arg( char_deg );
        mJointStepxList<<strComment;
    }

    m_pDebugContextMenu = NULL;
    m_pMonitorContextMenu = NULL;

    m_pActionExportImage = NULL;
    m_pActionExportData = NULL;
    m_pActionCopy = NULL;

    //! data cache
//    m_pCaches[0] = new DataCache( this ); m_pCaches[0]->mWSema.release();
    new_cache( 0 );
    new_cache( 1 );
    new_cache( 2 );
    new_cache( 3 );
    new_cache( 4 );

    ui->spinActTerminal->setSuffix( char_deg );
    ui->spinActWrist->setSuffix( char_deg );

    ui->spinTerminalTarget->setSuffix( char_deg );
    ui->spinWristTarget->setSuffix( char_deg );

    ui->actPosTerminal->setSuffix( char_deg );
    ui->actPosWrist->setSuffix( char_deg );

    //! set model
    ui->logout->setModel( pModel );

    //! debug
//    mDebugTable.createDebug();
//    mDiagTable.createDebug();

    ui->tvDebug->setModel( &mDebugTable );
    ui->tvDiagnosis->setModel( &mDiagTable );

    //! build connect
    connect( &mDebugTable, SIGNAL(signal_data_changed()),
             this, SLOT(slot_debug_table_changed()) );

    connect( &mDebugTable, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
             this, SLOT(slot_debug_table_changed()) );

    connect( ui->tvDebug, SIGNAL(activated( const QModelIndex &)),
             this, SLOT(slot_debug_table_changed()) );
    connect( ui->tvDebug, SIGNAL(clicked( const QModelIndex &)),
             this, SLOT(slot_debug_table_changed()) );
    connect( ui->tvDebug, SIGNAL(doubleClicked( const QModelIndex &)),
             this, SLOT(slot_debug_table_changed()) );

    connect( &mDebugTable, SIGNAL(signal_data_changed()),
             this, SLOT(slot_save_debug()) );

    //! context menu
    connect( ui->tvDebug, SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(slot_customContextMenuRequested(const QPoint &)));

    //! customconst QPoint &
    connect( ui->jointChart1,SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(slot_monitorContextMenuRequested(const QPoint &)) );
    connect( ui->jointChart2,SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(slot_monitorContextMenuRequested(const QPoint &)) );
    connect( ui->jointChart3,SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(slot_monitorContextMenuRequested(const QPoint &)) );
    connect( ui->jointChart4,SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(slot_monitorContextMenuRequested(const QPoint &)) );
    connect( ui->jointChart5,SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(slot_monitorContextMenuRequested(const QPoint &)) );

//    connect( ui->tab_5, SIGNAL(customContextMenuRequested(const QPoint &)),
//             this, SLOT(slot_monitorContextMenuRequested(const QPoint &)) );

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
    mTerminalRelations.append( ui->label_26 );
    mTerminalRelations.append( ui->spinActTerminal );
    mTerminalRelations.append( ui->joint5 );
    mTerminalRelations.append( ui->jointChart5 );

    //! spys
    spySetting( MRX_T4::e_setting_terminal );
    spySetting( MRX_T4::e_setting_record );
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
                on_debug_enter( pEvent->mVar1.toInt(), pEvent->mVar2.toInt()  );
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

#define config_chart( wig, title )  ui->wig->chart()->setTitle( title );\
                                    ui->wig->chart()->series1()->setPen(QPen(Qt::red));\
                                    ui->wig->chart()->series2()->setPen(QPen(Qt::blue));
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
            <<"dio"
            <<"homing"
            <<"control"
            <<"monitor"
            <<"debug"
            <<"diagnosis"
              ;
    Q_ASSERT( strList.size() == ui->tabWidget->count() );
    for ( int i = 0; i < ui->tabWidget->count(); i++ )
    { ui->tabWidget->widget( i )->setObjectName( strList.at( i ) ); }

    //! terminal
    ui->joint5->setAngleVisible( true, false );


    //! config the chart
    config_chart( jointChart1, tr("Basement") );
    config_chart( jointChart2, tr("Big Arm") );
    config_chart( jointChart3, tr("Little Arm") );
    config_chart( jointChart4, tr("Wrist") );

    config_chart( jointChart5, tr("Terminal") );

    //! cache
    mJointCharts.append( ui->jointChart1 );
    mJointCharts.append( ui->jointChart2 );
    mJointCharts.append( ui->jointChart3 );
    mJointCharts.append( ui->jointChart4 );

    mJointCharts.append( ui->jointChart5 );

    //! disabled ui
    //! \todo for coord control
    ui->groupBox_14->setVisible( false );
}

void T4OpPanel::retranslateUi()
{
    //! base ui
    ui->retranslateUi( this );

    //! cmb stepx
    for( int i = 0; i < mStepxList.size(); i++ )
    {
//        ui->cmbStepXx->setItemText( i, mStepxList.at( i ) );
        ui->roboControlBar->setItemText( i, mStepxList.at( i ) );
    }
    for( int i = 0; i < mJointStepxList.size(); i++ ){
        ui->controlBar->setItemText( i, mJointStepxList.at( i ));
    }
    //! joint name
    ui->joint4->setJointName( tr("Wrist") );
    ui->joint1->setJointName( tr("Base") );
    ui->joint2->setJointName( tr("Shoulder") );
    ui->joint3->setJointName( tr("Elbow") );

    ui->joint5->setJointName( tr("Terminal") );

    ui->jointChart1->chart()->setTitle( tr("Base") );
    ui->jointChart2->chart()->setTitle( tr("Shoulder") );
    ui->jointChart3->chart()->setTitle( tr("Elbow") );
    ui->jointChart4->chart()->setTitle( tr("Wrist") );

    ui->jointChart5->chart()->setTitle( tr("Terminal") );

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

    mJointCharts[joint]->chart()->beginChangeData();
    for ( int i = 0; i < m_pCaches[joint]->v1.size(); i++ )
    {
        mJointCharts[joint]->chart()->dataAppend( m_pCaches[joint]->v1.at(i),
                                         m_pCaches[joint]->v2.at(i)
                                        );
    }
    mJointCharts[joint]->chart()->endChangeData();

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

//    QSpinBox *spinBoxes[]={
//        ui->spinVel
//    };

    QDoubleSpinBox *doubleSpinBoxes[]={
        ui->spinDly,

    };

//    QComboBox *comboxes[]={
//        ui->cmbStepXx
//    };

//    QSlider *sliders[]
//    {
//        ui->sliderVel
//    };

    install_spy();

//    manual_enable_edit( ui->spinVel, true );
    manual_enable_edit( ui->spinDly, true );
//    manual_enable_edit( ui->cmbStepXx, true );
//    manual_enable_edit( ui->sliderVel, true );

//    manual_enable_edit( ui->comboBox, true );
//    manual_enable_edit( ui->spinBox, true );
//    manual_enable_edit( ui->horizontalSlider, true );

    //! modified
    connect( ui->controllerStatus, SIGNAL(signal_request_save()),
             this, SLOT(slot_modified()) );
}

void T4OpPanel::updateRefreshPara( QEvent *e )
{
    //! record now
    ui->spinBox_RecordNumber->setValue( mRefreshPara.recNow );
    ui->spinRecNow->setValue( mRefreshPara.recNow );

    //! target
    ui->doubleSpinBox_target_position_x->setValue( mRefreshPara.poseAim.x );
    ui->doubleSpinBox_target_position_y->setValue( mRefreshPara.poseAim.y );
    ui->doubleSpinBox_target_position_z->setValue( mRefreshPara.poseAim.z );

    //! actual
    ui->actPosX->setValue( mRefreshPara.poseNow.x );
    ui->actPosY->setValue( mRefreshPara.poseNow.y );
    ui->actPosZ->setValue( mRefreshPara.poseNow.z );

    ui->doubleSpinBox_homing_actual_pos_x->setValue( mRefreshPara.poseNow.x );
    ui->doubleSpinBox_homing_actual_pos_y->setValue( mRefreshPara.poseNow.y );
    ui->doubleSpinBox_homing_actual_pos_z->setValue( mRefreshPara.poseNow.z );

    ui->doubleSpinBox_debug_posX->setValue( mRefreshPara.poseNow.x );
    ui->doubleSpinBox_debug_posY->setValue( mRefreshPara.poseNow.y );
    ui->doubleSpinBox_debug_posZ->setValue( mRefreshPara.poseNow.z );

    ui->spinActX->setValue( mRefreshPara.poseNow.x );
    ui->spinActY->setValue( mRefreshPara.poseNow.y );
    ui->spinActZ->setValue( mRefreshPara.poseNow.z );

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
    ui->spinActTerminal->setValue( mRefreshPara.angles[4] );
    ui->actPosTerminal->setValue( mRefreshPara.angles[4] );

    //! home valid
    ui->radHome->setChecked( mRefreshPara.bHomeValid );
    ui->radioButton_homing_valid->setChecked( mRefreshPara.bHomeValid );
}

int T4OpPanel::posRefreshProc( void *pContext )
{
    //! to local
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );
//logDbg()<<QThread::currentThreadId();
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
        int rec;
        ret = mrgGetRobotCurrentRecord( robot_var(),
                                        &rec );
        if ( ret != 0 )
        { sysError( tr("Record read fail") ); break; }
        else
        {
            mRefreshPara.recNow = rec;
        }

        ret = mrgGetRobotTargetPosition( robot_var(),
                                         &fx, &fy, &fz );
        if ( ret != 0 )
        { sysError( tr("Target read fail") ); break; }
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
        { sysError( tr("Current read fail") ); break; }
        {
            mRefreshPara.poseNow.x = fx;
            mRefreshPara.poseNow.y = fy;
            mRefreshPara.poseNow.z = fz;
        }

        //! angle now
        float angles[5];
        ret = mrgGetRobotCurrentAngle( robot_var(),
                                       angles );
        if ( ret <= 0 )
        { break; }
        else
        {
            mRefreshPara.angles[0] = angles[0];
            mRefreshPara.angles[1] = angles[1];
            mRefreshPara.angles[2] = angles[2];
            mRefreshPara.angles[3] = angles[3];

            //! delta angles
            double dAngles[4];
            int dir []= { -1, -1, 1, -1 };
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
        { break; }
        else
        {
            mRefreshPara.angles[4] = angles[0];
        }

        //! \todo joint5 target

        //! \todo wrist current and target


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
                sysError( tr("Homeing status") );
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
//logDbg()<<QThread::currentThreadId();
    if ( pRobo->isOpened() )
    {}
    else
    { return 0; }

    unsigned int array[1024] = {0};
    int ret, v1, v2;

    //! foreach sub plot
    for( int joint = 0; joint < mJointCharts.size(); joint++ )
    {
        //! get from device
        //! \todo
        ret = mrgMRQReportQueue_Query( device_var(), joint, 0, array);
        if ( ret <= 0 )
        {
            sysError( tr("Monitor update fail") );
            continue;
        }

        m_pCaches[joint]->mWSema.acquire();

        m_pCaches[joint]->v1.clear();
        m_pCaches[joint]->v2.clear();

        //! debug used
//        ret = rand() % 100;
//        for ( int i = 0; i < ret; i++ )
//        { array[i] = rand()%100; }

//        logDbg()<<joint<<ret;
        //! update the data
        if ( ret > 0 )
        {
            for(int i=0; i < ret; i++)
            {
                v1 = (array[i] >> 8) & 0xFF;        //! SG
                v2 = array[i] & 0xFF;               //! SE
                if( v1>=0 && v1<=100 && v2>=0 && v2<=100 )
                {
    //                jointCharts[joint]->dataAppend(v1,v2);
                    m_pCaches[joint]->v1.append( v1 );
                    m_pCaches[joint]->v2.append( v2 );
                }
            }
        }

//        m_pCaches[joint]->mRSema.release();
        do
        {
            OpEvent *refreshEvent = new OpEvent( OpEvent::monitor_event );
            if ( NULL == refreshEvent )
            {
                m_pCaches[joint]->mWSema.release();
                break;
            }
            else
            { }

            refreshEvent->setPara( joint, 0 );
            qApp->postEvent( this, refreshEvent );
        }while( 0 );
    }

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

    int ret;
    char idn[128];
    for ( int i = 0; i < 3; i++ )
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

void T4OpPanel::attachWorkings()
{
    if ( sysHasArgv("-noupdate") )
    { return; }

    //! attach
    attachUpdateWorking( (XPage::procDo)( &T4OpPanel::posRefreshProc),
                         tr("Position refresh"),
                         NULL,
                         m_pPref->refreshIntervalMs() );

    attachUpdateWorking( (XPage::procDo)( &T4OpPanel::monitorRefreshProc ),
                         tr("Monitor refresh"),
                         NULL,
                         m_pPref->refreshIntervalMs() );

    attachUpdateWorking( (XPage::procDo)( &T4OpPanel::pingTick ),
                         tr("ping tick"),
                         NULL,
                         m_pPref->refreshIntervalMs() );
}

void T4OpPanel::updateUi()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

//    ui->cmbStepXx->setCurrentIndex( pRobo->mStepIndex );
//    ui->spinVel->setValue( pRobo->mSpeed );
//    ui->sliderVel->setValue( pRobo->mSpeed );

//    ui->comboBox->setCurrentIndex( pRobo->mJointStepIndex );
//    ui->spinBox->setValue( pRobo->mJointSpeed );
//    ui->horizontalSlider->setValue( pRobo->mJointSpeed );

    ui->roboControlBar->setCurrentIndex( pRobo->mStepIndex );
    ui->roboControlBar->setSpeed( pRobo->mSpeed );

    ui->controlBar->setCurrentIndex( pRobo->mJointStepIndex );
    ui->controlBar->setSpeed( pRobo->mJointSpeed );

    ui->controlBar->setCurrentIndex( pRobo->mJointStepIndex );
    ui->controlBar->setSpeed( pRobo->mJointSpeed );

    //! checked
    ui->controllerStatus->setMctChecked( pRobo->mbMctEn );
    ui->controllerStatus->setDevicePower( pRobo->mbAxisPwr );

    //! default page
    ui->tabWidget->setCurrentIndex( DEFAULT_PAGE_INDEX );
}

void T4OpPanel::updateData()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    //! save robo
//    pRobo->mStepIndex = ui->cmbStepXx->currentIndex();
//    pRobo->mSpeed = ui->spinVel->value();
    pRobo->mJointStepIndex = ui->roboControlBar->stepIndex();
    pRobo->mJointSpeed = ui->roboControlBar->getSpeed();

    //! save joint
    pRobo->mJointStepIndex = ui->controlBar->stepIndex();
    pRobo->mJointSpeed = ui->controlBar->getSpeed();

    pRobo->mbMctEn = ui->controllerStatus->isMctChecked();
    pRobo->mbAxisPwr = ui->controllerStatus->isDevicePowerEnable();
}

void T4OpPanel::onSetting(XSetting setting)
{
    XPage::onSetting( setting );

 /*   if ( setting.mSetting == XPage::e_setting_op_able )
    {
        check_para1();

        //! enable/disable
        ui->tabWidget->setEnabled( setting.mPara1.toBool() );
        ui->controllerStatus->setDevicePowerEnable( setting.mPara1.toBool() );
    }

    else */if ( (int)setting.mSetting == (int)MRX_T4::e_setting_terminal )
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
}

void T4OpPanel::setOperAble( bool b )
{
    ui->controllerStatus->setDevicePowerEnable( b );

    //! \note the page 1 is logout
    for( int i = 1; i < ui->tabWidget->count();i++ )
    {
        ui->tabWidget->widget( i )->setEnabled( b );
    }
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

void T4OpPanel::_step( double x, double y, double z )
{
    QList<QVariant> vars;

//    Q_ASSERT( ui->cmbStepXx->currentIndex() < sizeof_array( _stepRatio) );
//    double rat = _stepRatio[ ui->cmbStepXx->currentIndex() ];

//    vars<<x * rat <<y * rat <<z * rat <<ui->spinVel->value() / 100.0;

    Q_ASSERT( ui->roboControlBar->stepIndex() < sizeof_array( _stepRatio) );
    double rat = _stepRatio[ ui->roboControlBar->stepIndex() ];
    vars<<x * rat <<y * rat <<z * rat <<ui->roboControlBar->getSpeed() / 100.0;

    QVariant var( vars );

//    m_pPlugin->attachMissionWorking( this, (XPage::onMsg)(&T4OpPanel::onStep), var );
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
logDbg();
    ret = mrgRobotGoHome( robot_var(),
                          pRobo->mHomeTimeout*1000 );
logDbg();
    return ret;
}

int T4OpPanel::onFolding( QVariant var )
{
    check_connect_ret( -1 );

    int ret;

    ret = mrgGetRobotFold( robot_var(),
                           wave_table,
                           pRobo->mPackagesAxes[0],
                           pRobo->mPackagesAxes[1],
                           pRobo->mPackagesAxes[2],
                           pRobo->mPackagesAxes[3]
                           );
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

//    Q_ASSERT( ui->comboBox->currentIndex() < sizeof_array( _stepRatio) );
//    double stp = _stepRatio[ ui->comboBox->currentIndex() ];

//    double spd = pRobo->mMaxJointSpeed * ui->spinBox->value() / 100.0;
//    logDbg()<<spd<<stp/spd<<pRobo->mMaxJointSpeed;

    Q_ASSERT( ui->controlBar->stepIndex() < sizeof_array( _stepRatio) );
    double stp = _stepRatio[ ui->controlBar->stepIndex() ];

    double spd = pRobo->mMaxJointSpeed * ui->controlBar->getSpeed() / 100.0;
    logDbg()<<stp<<spd<<pRobo->mMaxJointSpeed;

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
    int ret = 0;
    if( jId == 4 ){
        //! terminal home
        ret = mrgRobotToolGoHome( robot_var(), guess_dist_time_ms( 360/20, 20 ) );
    }else{
        ret = mrgRobotJointHome( robot_var(),
                                 jId,
                                 20,
                                 guess_dist_time_ms( 360/20, 20 ) );
    }

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

    //double speed = pRobo->mMaxJointSpeed * ui->spinBox->value() / 100.0;
    double speed = pRobo->mMaxJointSpeed * ui->controlBar->getSpeed() / 100.0;
    logDbg() << speed;

    int ret = -1;
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
    do
    {
        for( int i = 0; i < mSeqList.size(); i++ )
        {
            if ( QThread::currentThread()->isInterruptionRequested() )
            { return 0; }

            //! enter
            post_debug_enter( mSeqList.at(i)->id, mSeqList.at(i)->vRow );

            //! enable?
            if ( procSequenceEn( mSeqList.at( i )) )
            {
                ret = procSequence( mSeqList.at( i ) );

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

void T4OpPanel::slot_monitorContextMenuRequested( const QPoint &)
{logDbg();
    if(m_pMonitorContextMenu == NULL )
    {
        m_pMonitorContextMenu = new QMenu( ui->tab_5 );
        if ( NULL == m_pMonitorContextMenu )
        { return; }

        m_pActionExportImage = m_pMonitorContextMenu->addAction(tr("Export image..."));
        if ( NULL == m_pActionExportImage )
        {
            delete m_pMonitorContextMenu;
            m_pMonitorContextMenu = NULL;
            return;
        }

        m_pActionExportData = m_pMonitorContextMenu->addAction(tr("Export data..."));
        if ( NULL == m_pActionExportData )
        {
            delete m_pMonitorContextMenu;
            m_pMonitorContextMenu = NULL;
            return;
        }

        m_pActionCopy = m_pMonitorContextMenu->addAction(tr("Copy"));
        if ( NULL == m_pActionCopy )
        {
            delete m_pMonitorContextMenu;
            m_pMonitorContextMenu = NULL;
            return;
        }

        //! set icon
        m_pActionExportImage->setIcon( QIcon(":/res/image/icon/xingzhuang-tupian.png") );
        m_pActionExportData->setIcon( QIcon(":/res/image/icon/activity.png") );
        m_pActionCopy->setIcon( QIcon(":/res/image/icon/fuzhi.png") );

        connect(m_pActionExportImage, SIGNAL(triggered(bool)),
                this, SLOT( slot_monitorExportImage() ) );
        connect(m_pActionExportData, SIGNAL(triggered(bool)),
                this, SLOT( slot_monitorExportData() ) );
        connect(m_pActionCopy, SIGNAL(triggered(bool)),
                this, SLOT( slot_monitorCopy() ) );
    }
    else
    {}

    m_pMonitorContextMenu->exec(QCursor::pos());
}

void T4OpPanel::slot_monitorExportImage()
{
    QString strFileName = QFileDialog::getSaveFileName( this,
                                  tr("Export"),
                                  m_pPlugin->homePath(),
                                  tr("Image Files (*.png *.jpg *.bmp)")
                                  );
    if ( !strFileName.isEmpty() )
    {
        QPixmap pixmap = ui->scrollAreaWidgetContents->grab();
        pixmap.save( strFileName );
    }
}

void T4OpPanel::slot_monitorExportData()
{
    QString strFileName = QFileDialog::getSaveFileName( this,
                                  tr("Export"),
                                  m_pPlugin->homePath(),
                                  tr("Data (*.csv)")
                                  );
    if ( !strFileName.isEmpty() )
    {
//        QPixmap pixmap = ui->scrollAreaWidgetContents->grab();
//        pixmap.save( strFileName );
        //! \todo
        //!
        //!

        QFile file( strFileName );
        if ( file.open( QIODevice::WriteOnly ) )
        {}
        else
        {
            sysError( strFileName + " " + tr("save fail") );
            return;
        }

        QTextStream txtStream( &file );

        m_pPlugin->lockWorking();
            PointList *p11, *p12;
            PointList *p21, *p22;
            PointList *p31, *p32;
            PointList *p41, *p42;
            PointList *p51, *p52;

            //! snap
            ui->jointChart1->chart()->snapDataSet( &p11, &p12 );
            ui->jointChart2->chart()->snapDataSet( &p21, &p22 );
            ui->jointChart3->chart()->snapDataSet( &p31, &p32 );
            ui->jointChart4->chart()->snapDataSet( &p41, &p42 );

            ui->jointChart5->chart()->snapDataSet( &p51, &p52 );

            //! datasets
            PlotDataSets d1( p11, p12 );
            PlotDataSets d2( p21, p22 );
            PlotDataSets d3( p31, p32 );
            PlotDataSets d4( p41, p42 );
            PlotDataSets d5( p51, p52 );

            QList<PlotDataSets*> dataSets;
            dataSets<<&d1<<&d2<<&d3<<&d4;
            if ( ui->jointChart5->isVisible() )
            { dataSets<<&d5; }

            QStringList headers;
            headers<<"t(base)"<<"sg(base)"<<"se(base)"
                   <<"t(ba)"<<"sg(ba)"<<"se(ba)"
                   <<"t(la))"<<"sg(la)"<<"se(la)"
                   <<"t(wrist)"<<"sg(wrist)"<<"se(wrist)"
                   <<"t(terminal)"<<"sg(terminal)"<<"se(terminal)";
            exportDataSets( txtStream, headers, dataSets );

            file.close();

        m_pPlugin->unlockWorking();
    }
}

void T4OpPanel::slot_monitorCopy()
{
    QPixmap pixmap = ui->scrollAreaWidgetContents->grab();

    QClipboard *clipboard = QGuiApplication::clipboard();
    if ( NULL == clipboard )
    { return; }

    clipboard->setImage( pixmap.toImage() );
}

//void T4OpPanel::on_pushButton_2_clicked()
//{
//    int ret;
//    ret = m_pPlugin->save( "abc.xml" );
//    logDbg()<<ret;
//}

void T4OpPanel::on_toolSingleXN_clicked()
{
    _step( -1, 0, 0 );
}

void T4OpPanel::on_toolSingleXP_clicked()
{
    _step( 1, 0, 0 );
}

void T4OpPanel::on_toolSingleYP_clicked()
{
    _step( 0, 1, 0 );
}

void T4OpPanel::on_toolSingleYN_clicked()
{
    _step( 0, -1, 0 );
}

void T4OpPanel::on_toolSingleZP_clicked()
{
    _step( 0, 0, 1 );
}

void T4OpPanel::on_toolSingleZN_clicked()
{
    _step( 0, 0, -1 );
}

void T4OpPanel::on_pushButton_starting_home_clicked()
{
    QVariant var;

    m_pPlugin->attachMissionWorking( this, (XPage::onMsg)(&T4OpPanel::onHoming), var );
}


void T4OpPanel::on_btnFold_clicked()
{
    QVariant var;

    m_pPlugin->attachMissionWorking( this, (XPage::onMsg)(&T4OpPanel::onFolding), var );
}

void T4OpPanel::on_toolSingleAdd_clicked()
{
    //! add to the record
    Q_ASSERT( NULL != m_pPlugin );

    QVariant var;
    QList<QVariant> coords;

    coords.append( ui->spinActX->value() );
    coords.append( ui->spinActY->value() );
    coords.append( ui->spinActZ->value() );

    coords.append( ui->spinActWrist->value() );
    coords.append( ui->spinActTerminal->value() );

    var.setValue( coords );

    m_pPlugin->emit_setting_changed( (eXSetting)(MRX_T4::e_add_record), var );
}

void T4OpPanel::on_toolSingleEdit_clicked()
{
    //! add to the record
    Q_ASSERT( NULL != m_pPlugin );

    QVariant var;
    QList<QVariant> coords;

    coords.append( ui->spinActX->value() );
    coords.append( ui->spinActY->value() );
    coords.append( ui->spinActZ->value() );

    coords.append( ui->spinActWrist->value() );
    coords.append( ui->spinActTerminal->value() );

    var.setValue( coords );

    m_pPlugin->emit_setting_changed( (eXSetting)(MRX_T4::e_edit_record), var );
}

//void T4OpPanel::on_toolButton_15_clicked()
//{
//    on_toolSingleAdd_clicked();
//}

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
    { cRow = index.row() + 1; }
    else
    { cRow = pModel->rowCount(); }

    //! insert
    if ( pModel->insertRow( cRow ) )
    { logDbg(); }
    else
    { logDbg(); return; }

    //! from index
    QModelIndex modelIndex;

    //! id
    modelIndex = pModel->index( cRow, 0 );

    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );
    if ( pRobo->currentRecordIndex() >= 0 )
    { pModel->setData( modelIndex, pRobo->currentRecordIndex() + 1 ); }
    else
    { return; }

    //! delay
    modelIndex = pModel->index( cRow, 1 );
    pModel->setData( modelIndex, ui->spinDly->value() );

    logDbg();
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

//! diagnosis
void T4OpPanel::on_btnRead_clicked()
{
    check_connect();

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
    }
    else
    {}
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
    QList<QVariant> vars;\
    vars<<(id-1)<<1; \
    QVariant var( vars );\
    on_post_setting( T4OpPanel, onJointStep, tr("Joint step") );\
} \
void T4OpPanel::on_joint##id##_signal_single_sub_clicked() \
{ \
    QList<QVariant> vars;\
    vars<<(id-1)<<-1; \
    QVariant var( vars );\
    on_post_setting( T4OpPanel, onJointStep, tr("Joint step") );\
}\
void T4OpPanel::on_joint##id##_signal_jog_add_pressed() \
{logDbg();\
    QList<QVariant> vars;\
    vars<<(id-1)<<1<<1; \
    QVariant var( vars );\
    on_post_setting_n_mission( T4OpPanel, onJointJog, tr("Jog +") );\
}\
void T4OpPanel::on_joint##id##_signal_jog_add_released()\
{logDbg();\
    QList<QVariant> vars;\
    vars<<(id-1)<<1<<0; \
    QVariant var( vars );\
    onJointJogEnd();\
    \
}\
void T4OpPanel::on_joint##id##_signal_jog_sub_pressed() \
{logDbg();\
    QList<QVariant> vars;\
    vars<<(id-1)<<-1<<1; \
    QVariant var( vars );\
    on_post_setting_n_mission( T4OpPanel, onJointJog, tr("Jog -") );\
}\
void T4OpPanel::on_joint##id##_signal_jog_sub_released()\
{logDbg();\
    QList<QVariant> vars;\
    vars<<(id-1)<<-1<<0; \
    QVariant var( vars );\
    onJointJogEnd();\
}

//on_post_setting_n_mission( T4OpPanel, onJointJog, tr("Jog + end") );
//on_post_setting_n_mission( T4OpPanel, onJointJog, tr("Jog - end") );

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

            pItem->delay = delay;

            list.append( pItem );
        }
    }

    return 0;
}

void T4OpPanel::post_debug_enter( int id, int r )
{
    OpEvent *pEvent= new OpEvent( OpEvent::debug_enter, id, r );
    if ( NULL == pEvent )
    { return; }

    qApp->postEvent( this, pEvent );
//

}
void T4OpPanel::post_debug_exit( int id, int r )
{

}

void T4OpPanel::on_debug_enter( int id, int r )
{
    logDbg()<<id<<r;
    ui->tvDebug->selectRow( r );
    ui->doubleSpinBox_debugRecord->setValue( id );
}
void T4OpPanel::on_debug_exit( int id, int r )
{

}

//! start the run thread
void T4OpPanel::on_toolButton_debugRun_clicked()
{
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


}
