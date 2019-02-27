#include "t4oppanel.h"
#include "ui_t4oppanel.h"

#include <QFileDialog>

#include "../../plugin/plugin/xplugin.h"

#include "../../device/MegaRobot.h"
#include "../../device/mrqDevice.h"
#include "../../device/errorcode.h"


#include "../../plugin/t4/t4.h"

#include "comassist.h"

#include "../model/debugtable.h"

namespace mrx_t4{

static double _stepRatio[]={ 0.1,0.2,0.5,
                            1,2,5,
                            10,20,50,
                            100 };

T4OpPanel::T4OpPanel(QAbstractListModel *pModel, QWidget *parent) :
    XPage(parent),
    ui(new Ui::T4OpPanel)
{
    ui->setupUi(this);
    m_pDebugContextMenu = NULL;

    ui->spinActTerminal->setSuffix( char_deg );
    ui->spinActWrist->setSuffix( char_deg );

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
    connect( ui->tvDebug, SIGNAL(activated( const QModelIndex &)),
             this, SLOT(slot_debug_table_changed()) );
    connect( ui->tvDebug, SIGNAL(clicked( const QModelIndex &)),
             this, SLOT(slot_debug_table_changed()) );
    connect( ui->tvDebug, SIGNAL(doubleClicked( const QModelIndex &)),
             this, SLOT(slot_debug_table_changed()) );

    connect( &mDebugTable, SIGNAL(signal_data_changed()),
             this, SLOT(slot_save_debug()) );

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
    mTerminalRelations.append( ui->label_26 );
    mTerminalRelations.append( ui->spinActTerminal );
    mTerminalRelations.append( ui->joint5 );

    //! spys
    spySetting( MRX_T4::e_setting_terminal );

    spySetting( MRX_T4::e_setting_record );
}

T4OpPanel::~T4OpPanel()
{
    delete ui;
}

void T4OpPanel::retranslateUi()
{
    //! joint name
    ui->joint1->setJointName( tr("Basement") );
    ui->joint2->setJointName( tr("Big Arm") );
    ui->joint3->setJointName( tr("Little Arm") );
    ui->joint4->setJointName( tr("Wrist") );

    ui->joint5->setJointName( tr("Terminal") );
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
        ui->spinVel
    };

    QDoubleSpinBox *doubleSpinBoxes[]={
        ui->spinDly,

    };

    QComboBox *comboxes[]={
        ui->cmbStepXx
    };

    install_spy();

    //! modified
    connect( ui->controllerStatus, SIGNAL(signal_request_save()),
             this, SLOT(slot_modified()) );
}

void T4OpPanel::posRefreshProc( void *pContext )
{
    //! to local
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    if ( pRobo->isOpened() )
    {}
    else
    { return; }

    do
    {//logDbg()<<QThread::currentThreadId();
        if ( isVisible() )
        {}
        else
        { return; }


        int ret;
        float x,y,z;
        //! record now
        int rec;
        ret = mrgGetRobotCurrentRecord( robot_var(),
                                        &rec );
        if ( ret != 0 )
        { sysError( tr("Record read fail") ); break; }
        else
        {
            ui->spinBox_RecordNumber->setValue( rec );
            ui->spinRecNow->setValue( rec );
        }

        ret = mrgGetRobotTargetPosition( robot_var(),
                                         &x, &y, &z );
        if ( ret != 0 )
        { sysError( tr("Target read fail") ); break; }
        else
        {
            ui->doubleSpinBox_target_position_x->setValue( x );
            ui->doubleSpinBox_target_position_y->setValue( x );
            ui->doubleSpinBox_target_position_z->setValue( x );
        }

        //! x,y,z now
        ret = mrgGetRobotCurrentPosition( robot_var(),
                                          &x, &y, &z );
        if ( ret != 0 )
        { sysError( tr("Current read fail") ); break; }
        else
        {
            //! act
            ui->actPosX->setValue( x );
            ui->actPosY->setValue( y );
            ui->actPosZ->setValue( z );

            ui->doubleSpinBox_homing_actual_pos_x->setValue( x );
            ui->doubleSpinBox_homing_actual_pos_y->setValue( y );
            ui->doubleSpinBox_homing_actual_pos_z->setValue( z );

            ui->spinActX->setValue( x );
            ui->spinActY->setValue( y );
            ui->spinActZ->setValue( z );
        }

        //! angle now
        float angles[4];
        ret = mrgGetRobotCurrentAngle( robot_var(),
                                       angles );
        if ( ret <= 0 )
        { break; }
        else
        {
            //! joint
            ui->joint1->setAngle( angles[0] );
            ui->joint2->setAngle( angles[1] );
            ui->joint3->setAngle( angles[2] );
            ui->joint4->setAngle( angles[3] );

            //! \todo joint5

            //! delta angles
            double dAngles[4];
            int dir []= { -1, -1, 1, -1 };
            for ( int i = 0; i < 4; i++ )
            {
                dAngles[ i ] = normalizeDegreeN180_180( angles[ i ] - pRobo->mAxisZero[i] ) * dir[i];
            }

            ui->joint1->setdAngle( dAngles[0] );
            ui->joint2->setdAngle( dAngles[1] );
            ui->joint3->setdAngle( dAngles[2] );
            ui->joint4->setdAngle( dAngles[3] );
        }

        //! home valid?
        ret = mrgGetRobotHomeRequire( robot_var() );
        do
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

            ui->radHome->setChecked( bHomeValid );
            ui->radioButton_homing_valid->setChecked( bHomeValid );

        }while( 0 );

    }while( 0 );
}

void T4OpPanel::terminalValidate( bool b )
{
    foreach( QWidget *pWig, mTerminalRelations )
    {
        Q_ASSERT( NULL != pWig );
        pWig->setVisible( b );
    }
}

void T4OpPanel::attachWorkings()
{
    //! attach
    attachUpdateWorking( (XPage::procDo)( &T4OpPanel::posRefreshProc) );
}

//void T4OpPanel::connectPlugin()
//{
//    Q_ASSERT( NULL != m_pPlugin );

//    //! spy it
//    spySetting( MRX_T4::e_setting_terminal );

//    connect( m_pPlugin, SIGNAL(signal_setting_changed( XSetting ) ),
//             this, SLOT(slot_plugin_setting_changed( XSetting)) ) ;
//}

void T4OpPanel::updateUi()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    ui->cmbStepXx->setCurrentIndex( pRobo->mStepIndex );
    ui->spinVel->setValue( pRobo->mSpeed );
    ui->sliderVel->setValue( pRobo->mSpeed );

    //! checked
    ui->controllerStatus->setMctChecked( pRobo->mbMctEn );
    ui->controllerStatus->setDevicePower( pRobo->mbAxisPwr );
}

void T4OpPanel::updateData()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    //! save
    pRobo->mStepIndex = ui->cmbStepXx->currentIndex();
    pRobo->mSpeed = ui->spinVel->value();

    pRobo->mbMctEn = ui->controllerStatus->isMctChecked();
    pRobo->mbAxisPwr = ui->controllerStatus->isDevicePowerEnable();
}

void T4OpPanel::onSetting(XSetting setting)
{
    XPage::onSetting( setting );

    if ( setting.mSetting == XPage::e_setting_op_able )
    {
        if ( setting.mPara1.isValid() )
        {}
        else
        { return; }

        //! enable/disable
        ui->tabWidget->setEnabled( setting.mPara1.toBool() );
        ui->controllerStatus->setDevicePowerEnable( setting.mPara1.toBool() );
    }
    else if ( (int)setting.mSetting == (int)MRX_T4::e_setting_terminal )
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

//void T4OpPanel::slot_plugin_setting_changed( XSetting setting )
//{
//    //! filter
//    if ( filterSetting( setting) )
//    { return; }

//    if ( setting.mSetting == MRX_T4::e_setting_terminal )
//    {
//        if ( setting.mPara1.isValid() )
//        {}
//        else
//        { return; }
//        logDbg();
//        terminalValidate( setting.mPara1.toBool() );
//    }
//    else
//    {}
//}

void T4OpPanel::enterMission()
{
    setEnabled( false );
}
void T4OpPanel::exitMission( int ret )
{
    setEnabled( true );
}

void T4OpPanel::_step( double x, double y, double z )
{
    QList<QVariant> vars;

    Q_ASSERT( ui->cmbStepXx->currentIndex() < sizeof_array( _stepRatio) );
    double rat = _stepRatio[ ui->cmbStepXx->currentIndex() ];

    vars<<x * rat <<y * rat <<z * rat <<ui->spinVel->value() / 100.0;

    QVariant var( vars );

//    m_pPlugin->attachMissionWorking( this, (XPage::onMsg)(&T4OpPanel::onStep), var );
    on_post_setting( T4OpPanel, onStep );
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

        //! wait idle
        //! \todo speed
        int ret = mrgRobotRelMove( robot_var(),
                                   wave_table,
                                   vars.at(0).toDouble(),
                                   vars.at(1).toDouble(),
                                   vars.at(2).toDouble(),
                                   1,
                                   60000
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
                          pRobo->mHomeSpeed,
                          pRobo->mHomeTimeout*1000 );
logDbg();
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

    Q_ASSERT( ui->cmbStepXx->currentIndex() < sizeof_array( _stepRatio) );
    double stp = _stepRatio[ ui->cmbStepXx->currentIndex() ];

    double spd = pRobo->mMaxJointSpeed * ui->spinVel->value() / 100.0;

    int ret = mrgMRQAdjust( device_var(), jId, dir * stp, stp/spd, 0 );

    return ret;
}
int T4OpPanel::onJointZero( QVariant var )
{
    //! \todo
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

    int ret = mrgMRQDriverState( device_var(), 0, b );

    if ( ret != 0 )
    { sysError( tr("power") );}
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

//        int row = ui->tableView->selectionModel()->selectedIndexes().first().row();
//        ui->tvDebug->selectRow( ui->tvDebug->currentIndex().row() );
        m_pDebugContextMenu->exec(QCursor::pos());

//        ui->tableView->selectionModel()->clear();
    }
}

void T4OpPanel::slot_toHere()
{
    //! \todo
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

void T4OpPanel::on_toolButton_15_clicked()
{
    on_toolSingleAdd_clicked();
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
    { cRow = index.row(); }
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
    pModel->setData( modelIndex, 0 );

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
                             ary.data(),
                             ary.size() );
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
    \
}\
void T4OpPanel::on_joint##id##_signal_single_add_clicked() \
{ \
    QList<QVariant> vars;\
    vars<<(id-1)<<1; \
    QVariant var( vars );\
    on_post_setting( T4OpPanel, onJointStep );\
} \
void T4OpPanel::on_joint##id##_signal_single_sub_clicked() \
{ \
    QList<QVariant> vars;\
    vars<<(id-1)<<-1; \
    QVariant var( vars );\
    on_post_setting( T4OpPanel, onJointStep );\
}

on_joint_actions( 1 )
on_joint_actions( 2 )
on_joint_actions( 3 )
on_joint_actions( 4 )

on_joint_actions( 5 )

////! joint op.
//void T4OpPanel::on_joint1_signal_zero_clicked()
//{
//    //! \todo
//}
//void T4OpPanel::on_joint1_signal_single_add_clicked()
//{ jointStep( 0, 1 ); }
//void T4OpPanel::on_joint1_signal_single_sub_clicked()
//{ jointStep( 0, -1 );  }

//void T4OpPanel::on_joint2_signal_zero_clicked()
//{}
//void on_joint2_signal_single_add_clicked();
//void on_joint2_signal_single_sub_clicked();

//void on_joint3_signal_zero_clicked();
//void on_joint3_signal_single_add_clicked();
//void on_joint3_signal_single_sub_clicked();

//void on_joint4_signal_zero_clicked();
//void on_joint4_signal_single_add_clicked();
//void on_joint4_signal_single_sub_clicked();

//void on_joint5_signal_zero_clicked();
//void on_joint5_signal_single_add_clicked();
//void on_joint5_signal_single_sub_clicked();

void T4OpPanel::slot_enter_mission( WorkingApi *pApi )
{
    enterMission();
}
void T4OpPanel::slot_exit_mission( WorkingApi *pApi, int ret )
{
    exitMission( ret );
}

}

