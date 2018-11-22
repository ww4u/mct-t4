#include "h2ops.h"
#include "ui_h2ops.h"
#include "mydebug.h"

#include <QClipboard>
#include <QTime>
#include <QFileDialog>

#include "../sys/sysapi.h"
#include "../widget/megamessagebox.h"

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
    m_timerGlobal.setInterval(1000 * 1); //所有状态信息的轮询间隔时间

    connect(&m_timerCurrentPos, SIGNAL(timeout()), this, SLOT(updateDeviceCurrentPosition()));
    m_timerCurrentPos.setInterval(100); //0.1S

    connect(&m_timerSpline, SIGNAL(timeout()), this, SLOT(updateMonitor()));
    m_timerSpline.setInterval(1000); //1s

    ui->tabWidget->setCurrentIndex(0);
//    ui->tabWidget->setEnabled(false);
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

    m_splineChart1->chart()->series1()->setPen(QPen(Qt::blue));
    m_splineChart1->chart()->series2()->setPen(QPen(Qt::red));

    m_splineChart2->chart()->series1()->setPen(QPen(Qt::blue));
    m_splineChart2->chart()->series2()->setPen(QPen(Qt::red));

    ui->horizontalLayout_3->addWidget(m_splineChart1);
    ui->horizontalLayout_3->addWidget(m_splineChart2);
    ui->horizontalLayout_3->addStretch();
}

#define set_name( the, name )   the->setName( name );\
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

void H2Ops::outConsole( const QString &str, log_level e )
{
//    QString fmtStr = QString("%1:%2").arg( QTime::currentTime().toString("yyyy:MM::dd hh:mm:ss.zzz") ).arg(str);
    QString fmtStr = QDateTime::currentDateTime().toString("yyyy/M/d h/m/s.z") + " " + str;

    if ( e == e_log_info )
    { outInfo( fmtStr); }
    else if ( e == e_log_warning )
    { outWarning( fmtStr ); }
    else if ( e == e_log_error )
    { outError( fmtStr ); }
    else
    {}
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

    qDebug() << "H2OPS " << "m_ViHandle:"  << m_ViHandle
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
        qDebug() << "slotLoadConfigAgain error";
        return;
    }

    m_Data = map;
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
{ logDbg();
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
    fDlg.setNameFilter( tr("Debug (*.xml)") );

    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    m_pDebugModel->load( fDlg.selectedFiles().first() );

    sysInfo( fDlg.selectedFiles().first(), tr("load completed") );
}

void H2Ops::on_btnExport_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptSave );
    fDlg.setNameFilter( tr("Debug (*.xml)") );

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
    fDlg.setNameFilter( tr("Diagnosis (*.xml)") );

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


void H2Ops::updateDeviceCurrentPosition()
{
    int ret = -1;
    float position_x = 0.0f, position_y = 0.0f, position_z = 0.0f;
    ret = mrgGetRobotCurrentPosition(m_ViHandle, m_RoboName, &position_x, &position_y, &position_z);
    if(ret != 0)
    {
        position_x = 0;
        position_y = 0;
        position_z = 0;
    }

    qDebug() << "mrgGetRobotCurrentPosition:" << ret << "(x,y):" << position_x << position_y;

    ui->doubleSpinBox_currentPos_x->setValue(position_x);
    ui->doubleSpinBox_currentPos_y->setValue(position_y);

    ui->doubleSpinBox_actual_position_x->setValue(position_x);
    ui->doubleSpinBox_actual_position_y->setValue(position_y);

    ui->doubleSpinBox_homing_actual_pos_x->setValue(position_x);
    ui->doubleSpinBox_homing_actual_pos_y->setValue(position_y);
}

////////////////////////////////////// 点击发送指令
#include <pthread.h>
struct ThreadGoHomingArg{
    QPushButton *btn;
    int vi;
    int roboname;
    int timeout;
};

void* threadGoHoming(void *args)
{
    ThreadGoHomingArg *arg = (ThreadGoHomingArg *)args;
    qDebug() << "mrgRobotGoHome" << mrgRobotGoHome(arg->vi, arg->roboname, arg->timeout);
    arg->btn->setEnabled(true);
    pthread_exit(NULL);
}

void H2Ops::on_pushButton_starting_home_clicked()
{
    pthread_t tid = 0;
    ThreadGoHomingArg arg = {ui->pushButton_starting_home,
                            m_ViHandle,
                            m_RoboName,
                            0};

    ui->pushButton_starting_home->setEnabled(false);
    if(0 != pthread_create(&tid, NULL, threadGoHoming, &arg))
        qDebug() << "threadGoHoming is created failed";
    else
    {
        while(1)
        {
            updateDeviceCurrentPosition();
            if(ui->pushButton_starting_home->isEnabled())
            {   break; }
            else
            {
                //sleep 0.2s
                QTime dieTime = QTime::currentTime().addMSecs(200);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            }
        }
    }
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
    float offset = ui->doubleSpinBox_Increament->value();
    float speed = ui->doubleSpinBox_Velocity->value();
    float time = offset/speed;

    m_timerCurrentPos.start();
    qDebug() << "mrgRobotRelMove" << mrgRobotRelMove(m_ViHandle, m_RoboName, -1, 0-offset, 0, 0, time, -1);
    setButtonDisableTime(ui->toolButton_singlestep_x_dec, time*1000);
    m_timerCurrentPos.stop();
}

void H2Ops::on_toolButton_singlestep_x_inc_clicked()
{
    float offset = ui->doubleSpinBox_Increament->value();
    float speed = ui->doubleSpinBox_Velocity->value();
    float time = offset/speed;

    m_timerCurrentPos.start();
    qDebug() << "mrgRobotRelMove" << mrgRobotRelMove(m_ViHandle, m_RoboName, -1, offset, 0, 0, time, -1);
    setButtonDisableTime(ui->toolButton_singlestep_x_inc, time*1000);
    m_timerCurrentPos.stop();
}

void H2Ops::on_toolButton_singlestep_y_dec_clicked()
{
    float offset = ui->doubleSpinBox_Increament->value();
    float speed = ui->doubleSpinBox_Velocity->value();
    float time = offset/speed;

    m_timerCurrentPos.start();
    qDebug() << "mrgRobotRelMove" << mrgRobotRelMove(m_ViHandle, m_RoboName, -1, 0, 0-offset, 0, time, -1);
    setButtonDisableTime(ui->toolButton_singlestep_y_dec, time*1000);
    m_timerCurrentPos.stop();
}

void H2Ops::on_toolButton_singlestep_y_inc_clicked()
{
    float offset = ui->doubleSpinBox_Increament->value();
    float speed = ui->doubleSpinBox_Velocity->value();
    float time = offset/speed;

    m_timerCurrentPos.start();
    qDebug() << "mrgRobotRelMove" << mrgRobotRelMove(m_ViHandle, m_RoboName, -1, 0, offset, 0, time, -1);
    setButtonDisableTime(ui->toolButton_singlestep_y_inc, time*1000);
    m_timerCurrentPos.stop();
}

//! jog move
void H2Ops::on_toolButton_jogmode_x_dec_pressed()
{
    float cr_speed = m_Data["CrawlingVelocity"].toFloat();
    float cr_time = m_Data["CrawlingTime"].toFloat() / 1000; //ms --> s
    float speed = m_Data["MaximumVelocity"].toFloat();

    m_timerCurrentPos.start();
    qDebug() << "mrhtRobotMoveJog"
             << mrgRobotMoveJog(m_ViHandle, m_RoboName, -1, 0, cr_time, 0-cr_speed, speed);
}

void H2Ops::on_toolButton_jogmode_x_inc_pressed()
{
    float cr_speed = m_Data["CrawlingVelocity"].toFloat();
    float cr_time = m_Data["CrawlingTime"].toFloat() / 1000; //ms --> s
    float speed = m_Data["MaximumVelocity"].toFloat();

    m_timerCurrentPos.start();
    qDebug() << "mrhtRobotMoveJog"
             << mrgRobotMoveJog(m_ViHandle, m_RoboName, -1, 0, cr_time, cr_speed, speed);
}

void H2Ops::on_toolButton_jogmode_y_dec_pressed()
{
    float cr_speed = m_Data["CrawlingVelocity"].toFloat();
    float cr_time = m_Data["CrawlingTime"].toFloat() / 1000; //ms --> s
    float speed = m_Data["MaximumVelocity"].toFloat();

    m_timerCurrentPos.start();
    qDebug() << "mrhtRobotMoveJog"
             << mrgRobotMoveJog(m_ViHandle, m_RoboName, -1, 1, cr_time, 0-cr_speed, speed);
}

void H2Ops::on_toolButton_jogmode_y_inc_pressed()
{
    float cr_speed = m_Data["CrawlingVelocity"].toFloat();
    float cr_time = m_Data["CrawlingTime"].toFloat() / 1000; //ms --> s
    float speed = m_Data["MaximumVelocity"].toFloat();

    m_timerCurrentPos.start();
    qDebug() << "mrhtRobotMoveJog"
             << mrgRobotMoveJog(m_ViHandle, m_RoboName, -1, 1, cr_time, cr_speed, speed);
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
    qDebug() << "mrgRobotStop:" << mrgRobotStop(m_ViHandle, m_RoboName, -1);

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
    updateDeviceStatus();
    updateOperate();
    updateDigitalIO();
    updateHoming();
    updateManual();
//    updateMonitor();
    updateDebug();
    updateDiagnosis();
}


void H2Ops::updateDeviceStatus()
{


}

void H2Ops::updateOperate()
{
#if 0
    qsrand((uint) QTime::currentTime().msec());

    ui->doubleSpinBox_RecordNumber->setValue(qrand() % 50);

    ui->doubleSpinBox_target_position_x->setValue(qrand() % 50);
    ui->doubleSpinBox_target_position_y->setValue(qrand() % 50);

    ui->doubleSpinBox_Mileage_x->setValue(qrand() % 50);
    ui->doubleSpinBox_Mileage_y->setValue(qrand() % 50);
#endif

    int homeVaild = mrgGetRobotHomeRequire(m_ViHandle, m_RoboName);
    if(homeVaild == 0)
    {//表示不需要回零
        ui->radHome->setChecked(true);
        ui->radioButton_homing_valid->setChecked(true);

        ui->tab_Manual->setEnabled(true);
        ui->tab_Debug->setEnabled(true);
        ui->tab_Monitor->setEnabled(true);
    }
    else if(homeVaild == 1)
    {//表示需要回零
        ui->radHome->setChecked(false);
        ui->radioButton_homing_valid->setChecked(false);

        ui->tab_Manual->setEnabled(false);
        ui->tab_Debug->setEnabled(false);
        ui->tab_Monitor->setEnabled(false);

        this->setTimerSplineStop();
        setTimerStop(m_timerCurrentPos);
    }
    else
    {
        qDebug() << "mrgGetRobotHomeRequire error" << homeVaild;
    }

#if 0
    //! 如果外部停止按钮被按下，禁止所有可用操作
    int isStop = 0;

    if(isStop == 0)
    {//表示不需要回零
        ui->radES->setChecked(true);
        ui->tab_Homing->setEnabled(true);
        ui->tab_Manual->setEnabled(true);
        ui->tab_Debug->setEnabled(true);
    }
    else if(isStop == 1)
    {//表示需要回零
        ui->radES->setChecked(false);
        ui->tab_Homing->setEnabled(false);
        ui->tab_Manual->setEnabled(false);
        ui->tab_Debug->setEnabled(false);

        this->setTimerSplineStop();
        setTimerStop(m_timerCurrentPos);
    }
    else
    {
        qDebug() << "query stop status error";
    }

#endif
}

void H2Ops::updateDigitalIO()
{
    //!TODO
}

void H2Ops::updateHoming()
{
    //!DONE
    ui->label_homing_target->setText(m_Data["Target"]);
    ui->label_homing_direction->setText(m_Data["Direction"]);
    //radioButton_homing_valid 的状态在updateOperate同步更新
}

void H2Ops::updateManual()
{
    //!NOTHING TODO
}


void H2Ops::updateMonitor()
{
    unsigned int array[4096] = {0};
    int count = -1;

    //查询第一个电机
    memset(array, 0, sizeof(array));
    count = mrgMRQReportQueue_Query(m_ViHandle, m_DeviceName, 0, 0, array);
    if(count <= 0)
        return;

    for(int i=0; i<count; i++)
    {
        int v1 = array[i] & 0xFF00;
        int v2 = array[i] & 0x00FF;
        m_splineChart1->dataAppend(v1,v2);
    }

    //查询第二个电机
    memset(array, 0, sizeof(array));
    count = mrgMRQReportQueue_Query(m_ViHandle, m_DeviceName, 1, 0, array);
    if(count <= 0)
        return;

    for(int i=0; i<count; i++)
    {
        int v1 = array[i] & 0xFF00;
        int v2 = array[i] & 0x00FF;
        m_splineChart2->dataAppend(v1,v2);
    }
}


void H2Ops::updateDebug()
{
    //!TODO

}

void H2Ops::updateDiagnosis()
{
    //!TODO
}
