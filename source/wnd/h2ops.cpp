#include "h2ops.h"
#include "ui_h2ops.h"
#include "mydebug.h"

#include <QClipboard>
#include <QTime>
#include <QFileDialog>

#include "mystd.h"
#include "sysapi.h"
#include "megamessagebox.h"
#include "megaxml.h"

H2Ops::H2Ops(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Ops)
{
    ui->setupUi(this);

    m_ViHandle = 0;
    m_DeviceName = 0;
    m_RoboName = 0;
    m_strDevInfo = "";

    setupUi();

    setupName();

    buildConnection();

    setupModel();

    connect(&m_timerGlobal, SIGNAL(timeout()), this, SLOT(updateDeviceAllStatus()));
    m_timerGlobal.setInterval(2000 * 1); //所有状态信息的轮询间隔时间

    connect(&m_timerCurrentPos, SIGNAL(timeout()), this, SLOT(updateCurrentPosition()));
    m_timerCurrentPos.setInterval(100); //0.1S

    connect(&m_timerSpline, SIGNAL(timeout()), this, SLOT(updateMonitor()));
    m_timerSpline.setInterval(1000); //1s

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setEnabled(false);
}

H2Ops::~H2Ops()
{
    delete ui;
}

void H2Ops::setupUi()
{
    //! actions for the logout
    mp_logClearAction = new QAction( tr("Clear"), this );
    mp_logSelectAllAction = new QAction( tr("Select All"), this );
    mp_logCopyAction = new QAction( tr("Copy"), this );

    mp_logSepAction = new QAction( this );
    mp_logSepAction->setSeparator( true );

    QList<QAction*> actions;
    actions<<mp_logSelectAllAction<<mp_logCopyAction<<mp_logSepAction<<mp_logClearAction;

    ui->lstLogout->addActions( actions );

    //! monitor
    m_splineChart1 = new MegaSplineChart(tr("Energy1"));
    m_splineChart2 = new MegaSplineChart(tr("Energy2"));


    m_splineChart1->chart()->series1()->setPen(QPen(Qt::red));
    m_splineChart1->chart()->series2()->setPen(QPen(Qt::blue));

    m_splineChart2->chart()->series1()->setPen(QPen(Qt::red));
    m_splineChart2->chart()->series2()->setPen(QPen(Qt::blue));

    ui->horizontalLayout_3->addWidget(m_splineChart1);
    ui->horizontalLayout_3->addWidget(m_splineChart2);
    ui->horizontalLayout_3->addStretch();
}

void H2Ops:: changeLanguage(QString qmFile)
{
    ui->h2Status->changeLanguage(qmFile);
    m_splineChart1->changeLanguage(qmFile);
    m_splineChart2->changeLanguage(qmFile);

    qApp->removeTranslator(&m_translator);
    m_translator.load(qmFile);
    qApp->installTranslator(&m_translator);
    ui->retranslateUi(this);
}

#define set_name( the, name )   the->setFocusName( name );\
                                mSubTabs.append( the );
void H2Ops::setupName()
{
    set_name( ui->tab_LogOut,   "tab_LogOut");
    set_name( ui->tab_Operate,  "tab_Operate");
    set_name( ui->tab_DigitalIO,"tab_DigitalIO");
    set_name( ui->tab_Homing,   "tab_Homing");
    set_name( ui->tab_Manual,   "tab_Manual");
    set_name( ui->tab_Monitor,  "tab_Monitor");
    set_name( ui->tab_Debug,    "tab_Debug");
    set_name( ui->tab_Diagnosis,"tab_Diagnosis");
}

void H2Ops::setupModel()
{
    //! model
    m_pDiagnosisModel= new DiagnosisModel();
    ui->tvDiagnosis->setModel( m_pDiagnosisModel );

    m_pDebugModel = new DebugModel();
    ui->tvDebug->setModel( m_pDebugModel );
}

void H2Ops::buildConnection()
{
    //! connect
    connect( mp_logClearAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_logClear_action()) );
    connect( mp_logSelectAllAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_logSelectAll_action()) );
    connect( mp_logCopyAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_logCopy_action()) );

    //! option
    foreach( XConfig *pCfg, mSubTabs )
    {
        connect( pCfg, SIGNAL(signal_focus_in( const QString &)),
                 this, SIGNAL(signal_focus_in( const QString &)));
    }
}

void H2Ops::outConsole( const QString &str, LogLevel e )
{
//    QString fmtStr = QString("%1:%2").arg( QTime::currentTime().toString("yyyy:MM::dd hh:mm:ss.zzz") ).arg(str);
//    QString fmtStr = QDateTime::currentDateTime().toString("yyyy/M/d h/m/s.z") + "   " + str;
    QString fmtStr = QDateTime::currentDateTime().toString("hh:mm:ss.zzz") + "   " + str;

    if ( e == eLogInfo )
    { outInfo( fmtStr); }
    else if ( e == eLogWarning )
    { outWarning( fmtStr ); }
    else if ( e == eLogError )
    { outError( fmtStr ); }
    else
    {}

    ui->lstLogout->scrollToBottom();
}

void H2Ops::outInfo( const QString &str )
{
    QListWidgetItem *pItem = new QListWidgetItem( QIcon(":/res/image/icon/xiaoxi.png"), str );
    ui->lstLogout->addItem( pItem );

}
void H2Ops::outWarning( const QString &str )
{
    QListWidgetItem *pItem = new QListWidgetItem( QIcon(":/res/image/icon/gantanhaozhong.png"), str );
    ui->lstLogout->addItem( pItem );
}
void H2Ops::outError( const QString &str )
{
    QListWidgetItem *pItem = new QListWidgetItem( QIcon(":/res/image/icon/shibai2.png"), str );
    ui->lstLogout->addItem( pItem );
}

void H2Ops::slotSetCurrentRobot(QString strDevInfo, int visa, int deviceName, int roboName)
{
    if( (m_strDevInfo == strDevInfo) && (m_ViHandle == visa) && (m_RoboName == roboName) )
    {
        return;//没有切换机器人且状态没有改变
    }

    m_strDevInfo = strDevInfo;
    m_ViHandle = visa;
    m_DeviceName = deviceName;
    m_RoboName = roboName;
    m_Data.clear();

    qDebug() << "H2OPS "
             << "m_ViHandle:"  << m_ViHandle
             << "m_DeviceName:" << m_DeviceName
             << "m_RoboName:" << m_RoboName;

    if(m_ViHandle == 0)
    {
        ui->tabWidget->setEnabled(false);

        this->setTimerStop(m_timerGlobal);
        this->setTimerSplineStop();
    }
    else
    {
        ui->tabWidget->setEnabled(true);
        slotLoadConfigAgain();

        this->setTimerStart(m_timerGlobal);
    }
}

void H2Ops::slotLoadConfigAgain()
{
    m_Data.clear();
    MegaXML mXML;
    QString deviceName = m_strDevInfo.split(',').at(3);
    QString fileName = QApplication::applicationDirPath() + "/robots/" + deviceName + ".xml";
    QFile file(fileName);
    if( !file.exists() )
        fileName = QApplication::applicationDirPath() + "/robots/default.xml";

//    qDebug() << "slotLoadConfigAgain:" << fileName;
    QMap<QString,QString> map = mXML.xmlRead(fileName);
    if(map.isEmpty())
    {
        sysError("slotLoadConfigAgain error");
        return;
    }

    m_Data = map;
    updateHoming();
}

void H2Ops::slot_logSelectAll_action()
{
    ui->lstLogout->selectAll();
}

void H2Ops::slot_logCopy_action()
{
    //! cat text
    QString str;
    for ( int i = 0; i < ui->lstLogout->count(); i++ )
    {
        if ( ui->lstLogout->item(i)->isSelected() )
        {
            str.append( ui->lstLogout->item( i )->text() );
            str.append( '\n' );
        }
    }

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText( str );
}

void H2Ops::slot_logClear_action()
{
    ui->lstLogout->clear();
}

//! debug
void H2Ops::on_btnUp_clicked()
{
    //! current valid
    if ( ui->tvDebug->currentIndex().isValid() )
    {}
    else
    { return; }

    //! check up index
    QModelIndex prev = m_pDebugModel->index( ui->tvDebug->currentIndex().row() - 1,
                                             ui->tvDebug->currentIndex().column() );
    if ( prev.isValid() )
    {}
    else
    { return; }

    DebugItem *pItem = m_pDebugModel->items()->takeAt( ui->tvDebug->currentIndex().row() );
    if ( NULL == pItem )
    { return; }

    //! exchange
    m_pDebugModel->items()->insert( ui->tvDebug->currentIndex().row() - 1, pItem );
    m_pDebugModel->signal_dataChanged(m_pDebugModel->index( ui->tvDebug->currentIndex().row()-1, 0 ),
                                      m_pDebugModel->index( ui->tvDebug->currentIndex().row(), 1 ));

    ui->tvDebug->setCurrentIndex( prev );

}

void H2Ops::on_btnDown_clicked()
{
    if ( ui->tvDebug->currentIndex().isValid() )
    {}
    else
    { return; }

    //! check next index
    QModelIndex next = m_pDebugModel->index( ui->tvDebug->currentIndex().row() + 1,
                                             ui->tvDebug->currentIndex().column() );
    if ( next.isValid() )
    {}
    else
    { return; }

    DebugItem *pItem = m_pDebugModel->items()->takeAt( ui->tvDebug->currentIndex().row() );
    if ( NULL == pItem )
    { return; }

    m_pDebugModel->items()->insert( next.row(), pItem );
    m_pDebugModel->signal_dataChanged(m_pDebugModel->index( ui->tvDebug->currentIndex().row(), 0 ),
                                        m_pDebugModel->index( ui->tvDebug->currentIndex().row()+1, 1));
    ui->tvDebug->setCurrentIndex( next );
}

void H2Ops::on_btnAdd_clicked()
{
    if ( ui->tvDebug->currentIndex().isValid() )
    {
        m_pDebugModel->insertRow( ui->tvDebug->currentIndex().row() + 1 );
        m_pDebugModel->setData( m_pDebugModel->index( ui->tvDebug->currentIndex().row()+1, 1),
                                QVariant( ui->spinDly->value()),
                                Qt::EditRole );
    }
    else
    {
        m_pDebugModel->insertRow( 0 );
        m_pDebugModel->setData( m_pDebugModel->index( 0, 1),
                                QVariant( ui->spinDly->value()),
                                Qt::EditRole );
        return;
    }
}

void H2Ops::on_btnDel_clicked()
{
    if ( ui->tvDebug->currentIndex().isValid() )
    {}
    else
    { return; }

    m_pDebugModel->removeRow( ui->tvDebug->currentIndex().row() );
}

void H2Ops::on_btnClr_clicked()
{
    MegaDeleteAffirmMessageBox msgBox;
    int ret = msgBox.exec();
    if ( ret == QMessageBox::Ok )
    {
        m_pDebugModel->removeRows( 0, m_pDebugModel->items()->count(), QModelIndex() );
    }
}

void H2Ops::on_btnImport_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptOpen );
    fDlg.setNameFilter( "Debug (*.xml)" );

    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    m_pDebugModel->load( fDlg.selectedFiles().first() );

    sysInfo( fDlg.selectedFiles().first(), tr("load completed") );
}

void H2Ops::on_btnExport_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptSave );
    fDlg.setNameFilter( "Debug (*.xml)" );

    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    m_pDebugModel->save( fDlg.selectedFiles().first() );

    sysInfo( fDlg.selectedFiles().first(), tr("save completed") );
}

//! diagnosis
void H2Ops::on_btnRead_clicked()
{
    //! \todo read from device
    //! debug for the model
    m_pDiagnosisModel->createDemoData();
}

void H2Ops::on_btnDelete_clicked()
{
    MegaDeleteAffirmMessageBox msgBox;
    int ret = msgBox.exec();
    if ( ret == QMessageBox::Ok )
    {
        m_pDiagnosisModel->removeRows( 0, m_pDiagnosisModel->items()->count(), QModelIndex() );
    }
}

void H2Ops::on_btnExport_2_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptSave );
    fDlg.setNameFilter( "Diagnosis (*.xml)" );

    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    m_pDiagnosisModel->save( fDlg.selectedFiles().first() );

    sysInfo( fDlg.selectedFiles().first(), tr("save completed") );
}

void H2Ops::on_tabWidget_currentChanged(int index)
{
    QString strName = ui->tabWidget->tabText( index );
    emit signal_focus_in( strName );

    if(m_ViHandle == 0)
    {   return;     }
    //进入到Monitor就查询绘制曲线,离开就停止
    if( strName == "Monitor" && ui->tab_Monitor->isEnabled() ){
        this->setTimerSplineStart();
    }else{
        this->setTimerSplineStop();
    }
}

void H2Ops::on_tabWidget_tabBarClicked(int index)
{
    emit signal_focus_in( ui->tabWidget->tabText( index ) );
}

////////////////////////////////////// 点击发送指令
void H2Ops::on_pushButton_starting_home_clicked()
{
    if(m_ViHandle <= 0) return;
    ThreadGoHomingArg arg = {m_ViHandle, m_RoboName, 0};
    ThreadGoHoming *thread = new ThreadGoHoming;
    thread->setArgs(arg);
    connect(thread, SIGNAL(signalThreadGoHomeEnd(int)),this,SLOT(slot_starting_home_over(int)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    ui->pushButton_starting_home->setEnabled(false);
    m_timerCurrentPos.start();
    thread->start();
}
void H2Ops::slot_starting_home_over(int ret)
{
    if(ret != 0){
        QMessageBox::information(this,tr("tips"),tr("Starting Home failure"));
    }
    m_timerCurrentPos.stop();
    ui->pushButton_starting_home->setEnabled(true);
}

void H2Ops::setButtonDisableTime(QToolButton *btn, int msec)
{
    btn->setEnabled(false);
    //非阻塞延时
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    btn->setEnabled(true);
}

void H2Ops::setTimerStop(QTimer &timer)
{
    if( timer.isActive() )
        timer.stop();
}

void H2Ops::setTimerStart(QTimer &timer)
{
    if( !timer.isActive() )
        timer.start();
}

void H2Ops::setTimerSplineStop()
{
    if( m_timerSpline.isActive() )
    {
        m_timerSpline.stop();
        //关闭上报状态
        mrgMRQReportState(this->m_ViHandle,this->m_DeviceName, 0, 0, 0);
        mrgMRQReportState(this->m_ViHandle,this->m_DeviceName, 1, 0, 0);
    }
}

void H2Ops::setTimerSplineStart()
{
    if(m_ViHandle <= 0) return;
    if( !m_timerSpline.isActive() )
    {
        //打开上报状态
        mrgMRQReportState(this->m_ViHandle,this->m_DeviceName, 0, 0, 1);
        mrgMRQReportState(this->m_ViHandle,this->m_DeviceName, 1, 0, 1);
        m_timerSpline.start();
    }
}

//! single move
void H2Ops::on_toolButton_singlestep_x_dec_clicked()
{
    if(m_ViHandle <= 0) return;
    float offset = ui->doubleSpinBox_Increament->value();
    float speed = ui->doubleSpinBox_Velocity->value();
    float time = offset/speed;

    m_timerCurrentPos.start();
    int ret = mrgRobotRelMove(m_ViHandle, m_RoboName, -1, 0-offset, 0, 0, time, -1);
    sysInfo("mrgRobotRelMove", ret);
    setButtonDisableTime(ui->toolButton_singlestep_x_dec, time*1000);
    m_timerCurrentPos.stop();
}

void H2Ops::on_toolButton_singlestep_x_inc_clicked()
{
    if(m_ViHandle <= 0) return;
    float offset = ui->doubleSpinBox_Increament->value();
    float speed = ui->doubleSpinBox_Velocity->value();
    float time = offset/speed;

    m_timerCurrentPos.start();
    int ret = mrgRobotRelMove(m_ViHandle, m_RoboName, -1, offset, 0, 0, time, -1);
    sysInfo("mrgRobotRelMove", ret);
    setButtonDisableTime(ui->toolButton_singlestep_x_inc, time*1000);
    m_timerCurrentPos.stop();
}

void H2Ops::on_toolButton_singlestep_y_dec_clicked()
{
    if(m_ViHandle <= 0) return;
    float offset = ui->doubleSpinBox_Increament->value();
    float speed = ui->doubleSpinBox_Velocity->value();
    float time = offset/speed;

    m_timerCurrentPos.start();
    int ret = mrgRobotRelMove(m_ViHandle, m_RoboName, -1, 0, 0-offset, 0, time, -1);
    sysInfo("mrgRobotRelMove", ret);
    setButtonDisableTime(ui->toolButton_singlestep_y_dec, time*1000);
    m_timerCurrentPos.stop();
}

void H2Ops::on_toolButton_singlestep_y_inc_clicked()
{
    if(m_ViHandle <= 0) return;
    float offset = ui->doubleSpinBox_Increament->value();
    float speed = ui->doubleSpinBox_Velocity->value();
    float time = offset/speed;

    m_timerCurrentPos.start();
    int ret = mrgRobotRelMove(m_ViHandle, m_RoboName, -1, 0, offset, 0, time, -1);
    sysInfo("mrgRobotRelMove", ret);
    setButtonDisableTime(ui->toolButton_singlestep_y_inc, time*1000);
    m_timerCurrentPos.stop();
}

//! jog move
void H2Ops::on_toolButton_jogmode_x_dec_pressed()
{
    if(m_ViHandle <= 0) return;
    float cr_speed = m_Data["CrawlingVelocity"].toFloat();
    float cr_time = m_Data["CrawlingTime"].toFloat() / 1000; //ms --> s
    float speed = m_Data["MaximumVelocity"].toFloat();

    m_timerCurrentPos.start();
    int ret = mrgRobotMoveJog(m_ViHandle, m_RoboName, -1, 0, cr_time, 0-cr_speed, speed);
    sysInfo("mrhtRobotMoveJog", ret);
}

void H2Ops::on_toolButton_jogmode_x_inc_pressed()
{
    if(m_ViHandle <= 0) return;
    float cr_speed = m_Data["CrawlingVelocity"].toFloat();
    float cr_time = m_Data["CrawlingTime"].toFloat() / 1000; //ms --> s
    float speed = m_Data["MaximumVelocity"].toFloat();

    m_timerCurrentPos.start();
    int ret = mrgRobotMoveJog(m_ViHandle, m_RoboName, -1, 0, cr_time, cr_speed, speed);
    sysInfo("mrhtRobotMoveJog", ret);
}

void H2Ops::on_toolButton_jogmode_y_dec_pressed()
{
    if(m_ViHandle <= 0) return;
    float cr_speed = m_Data["CrawlingVelocity"].toFloat();
    float cr_time = m_Data["CrawlingTime"].toFloat() / 1000; //ms --> s
    float speed = m_Data["MaximumVelocity"].toFloat();

    m_timerCurrentPos.start();
    int ret = mrgRobotMoveJog(m_ViHandle, m_RoboName, -1, 1, cr_time, 0-cr_speed, speed);
    sysInfo("mrhtRobotMoveJog", ret);
}

void H2Ops::on_toolButton_jogmode_y_inc_pressed()
{
    if(m_ViHandle <= 0) return;
    float cr_speed = m_Data["CrawlingVelocity"].toFloat();
    float cr_time = m_Data["CrawlingTime"].toFloat() / 1000; //ms --> s
    float speed = m_Data["MaximumVelocity"].toFloat();

    m_timerCurrentPos.start();
    int ret = mrgRobotMoveJog(m_ViHandle, m_RoboName, -1, 1, cr_time, cr_speed, speed);
    sysInfo("mrhtRobotMoveJog", ret);
}


void H2Ops::on_toolButton_jogmode_x_dec_released()
{   on_pushButton_stop_clicked();   }

void H2Ops::on_toolButton_jogmode_x_inc_released()
{   on_pushButton_stop_clicked();   }

void H2Ops::on_toolButton_jogmode_y_dec_released()
{   on_pushButton_stop_clicked();   }

void H2Ops::on_toolButton_jogmode_y_inc_released()
{   on_pushButton_stop_clicked();   }


void H2Ops::on_pushButton_stop_clicked()
{
    if(m_ViHandle <= 0) return;

    int ret = mrgRobotStop(m_ViHandle, m_RoboName, -1);
    sysInfo("mrgRobotStop", ret);

    this->setTimerStop(m_timerCurrentPos);

    ui->toolButton_singlestep_x_dec->setEnabled(true);
    ui->toolButton_singlestep_x_inc->setEnabled(true);
    ui->toolButton_singlestep_y_dec->setEnabled(true);
    ui->toolButton_singlestep_y_inc->setEnabled(true);
}



void H2Ops::on_pushButton_apply_clicked()
{

}

/////////////////////////////////////////////////////////////
//更新标签的实时数值
void H2Ops::updateDeviceAllStatus()
{
    int homeVaild = mrgGetRobotHomeRequire(m_ViHandle, m_RoboName);
    if(homeVaild == 1)
    {//表示需要回零
        sysInfo("Robot Need Go Home");

        ui->radHome->setChecked(false);
        ui->radioButton_homing_valid->setChecked(false);

        ui->tab_Manual->setEnabled(false);
        ui->tab_Debug->setEnabled(false);
        ui->tab_Monitor->setEnabled(false);

        this->setTimerSplineStop();
        setTimerStop(m_timerCurrentPos);
        return;
    }
    else if(homeVaild == 0)
    {//表示不需要回零
        ui->radHome->setChecked(true);
        ui->radioButton_homing_valid->setChecked(true);

        ui->tab_Manual->setEnabled(true);
        ui->tab_Debug->setEnabled(true);
        ui->tab_Monitor->setEnabled(true);
    }
    else
    {
        sysError("mrgGetRobotHomeRequire error");
        return;
    }

#if 0
    //! 如果外部停止按钮被按下，禁止所有可用操作
    int isStop = 0;

    if(isStop == 1)
    {//表示外部停止按钮被按下
        ui->radES->setChecked(false);
        ui->tab_Homing->setEnabled(false);
        ui->tab_Manual->setEnabled(false);
        ui->tab_Debug->setEnabled(false);

        this->setTimerSplineStop();
        setTimerStop(m_timerCurrentPos);
        return;
    }
    else if(isStop == 0)
    {//表示外部停止按钮没有被按下
        ui->radES->setChecked(true);
        ui->tab_Homing->setEnabled(true);
        ui->tab_Manual->setEnabled(true);
        ui->tab_Debug->setEnabled(true);
    }
    else
    {
        sysError("query stop status error");
        return;
    }
#endif

    updateCurrentMileage();
    updateTargetPosition();

    updateDeviceStatus();

    updateRecordNumber();

    updateDigitalIO();
    updateDebug();
    updateDiagnosis();
}

//! 更新当前位置
void H2Ops::updateCurrentPosition()
{
    int ret = -1;
    float fx = 0.0f, fy = 0.0f, fz = 0.0f;
    ret = mrgGetRobotCurrentPosition(m_ViHandle, m_RoboName, &fx, &fy, &fz);
    if(ret != 0)
    {
        fx = 0;
        fy = 0;
    }

    qDebug() << "mrgGetRobotCurrentPosition:" << ret << "(x,y):" << fx << fy;

    ui->doubleSpinBox_currentPos_x->setValue(fx);
    ui->doubleSpinBox_currentPos_y->setValue(fy);

    ui->doubleSpinBox_actual_position_x->setValue(fx);
    ui->doubleSpinBox_actual_position_y->setValue(fy);

    ui->doubleSpinBox_homing_actual_pos_x->setValue(fx);
    ui->doubleSpinBox_homing_actual_pos_y->setValue(fy);
}

//! 更新当前里程
void H2Ops::updateCurrentMileage()
{
    long long llx, lly, llz;
    int ret = mrgGetRobotCurrentMileage(m_ViHandle, m_RoboName, &llx, &lly, &llz);
    qDebug() << "mrgGetRobotCurrentMileage:" << llx << lly;
    if(ret == 0){
        ui->doubleSpinBox_Mileage_x->setValue( llx );
        ui->doubleSpinBox_Mileage_y->setValue( lly );
    }
}

//! 更新目标位置
void H2Ops::updateTargetPosition()
{
    double dx, dy, dz;
    int ret =  mrgGetRobotTargetPosition(m_ViHandle, m_RoboName, &dx, &dy, &dz);
    qDebug() << "mrgGetRobotTargetPosition" << ret;
    if(ret == 0){
        ui->doubleSpinBox_target_position_x->setValue( dx );
        ui->doubleSpinBox_target_position_y->setValue( dy );
    }
}

//! 更新记录编号
void H2Ops::updateRecordNumber()
{
#if 0
    qsrand((uint) QTime::currentTime().msec());

    ui->doubleSpinBox_RecordNumber->setValue(qrand() % 50);
#endif
}

void H2Ops::updateHoming()
{
    ui->label_homing_target->setText(m_Data["Target"]);
    ui->label_homing_direction->setText(m_Data["Direction"]);
}


void H2Ops::updateDeviceStatus()
{


}

void H2Ops::updateMonitor()
{
    unsigned int array1[4096] = {0};
    unsigned int array2[4096] = {0};
    int count = -1;

    //查询第一个电机
    memset(array1, 0, sizeof(array1));
    count = mrgMRQReportQueue_Query(m_ViHandle, m_DeviceName, 0, 0, array1);
    if(count <= 0)
        return;

    //查询第二个电机
    memset(array2, 0, sizeof(array2));
    count = mrgMRQReportQueue_Query(m_ViHandle, m_DeviceName, 1, 0, array2);
    if(count <= 0)
        goto LAB1;

    for(int i=0; i<count; i++)
    {
        int v1 = (array2[i] >> 8) & 0xFF;
        int v2 = array2[i] & 0xFF;
        m_splineChart2->dataAppend(v1,v2);
//        qDebug() << "m_splineChart2" << i << v1 << v2;
    }

LAB1:
    for(int i=0; i<count; i++)
    {
        int v1 = (array1[i] >> 8) & 0xFF;
        int v2 = array1[i] & 0xFF;
        m_splineChart1->dataAppend(v1,v2);
//        qDebug() << "m_splineChart1" << i << v1 << v2;
    }

}


void H2Ops::updateDigitalIO()
{
    //!TODO
}

void H2Ops::updateDebug()
{
    //!TODO

}

void H2Ops::updateDiagnosis()
{
    //!TODO
}
