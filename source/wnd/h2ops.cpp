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
    m_RoboName = 0;
    m_strDevInfo = "";

    setupUi();

    setupName();

    buildConnection();

    setupModel();



    qsrand((uint) QTime::currentTime().msec());
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slot_handle_timeout()));
    m_timer.setInterval(1000 * 2); //轮询时间周期
//    m_timer.start();


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

    m_splineChart1->chart()->series()->setPen(QPen(Qt::blue));
    m_splineChart2->chart()->series()->setPen(QPen(Qt::red));

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
    set_name( ui->Debug,        "tab_Debug");
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

void H2Ops::slotSetCurrentRobot(QString strDevInfo, int visa, int name)
{
    if( (m_strDevInfo == strDevInfo) && (m_ViHandle == visa) && (m_RoboName == name) )
    {
        return;//没有切换机器人且机器人状态没有改变
    }

    m_strDevInfo = strDevInfo;
    m_ViHandle = visa;
    m_RoboName = name;
    m_Data.clear();

    qDebug() << "H2OPS " << "m_ViHandle:"  << m_ViHandle << "m_RoboName:" << m_RoboName;
    if(m_ViHandle == 0)
    {
        ui->tabWidget->setEnabled(false);
        if(m_timer.isActive())
        {
            qDebug() << "H2OPS timer stop";
             m_timer.stop();
        }
    }
    else
    {
        ui->tabWidget->setEnabled(true);
        slotLoadConfigAgain();
        if( !m_timer.isActive())
        {
            qDebug() << "H2OPS timer start";
            m_timer.start();
        }
    }
}

void H2Ops::slotLoadConfigAgain()
{
    m_Data.clear();
    MegaXML mXML;
    QString deviceName = m_strDevInfo.split(',').at(3);
    QString fileName = QApplication::applicationDirPath() + "/robots/" + deviceName + ".xml";

    qDebug() << "slotLoadConfigAgain:" << fileName;
    QMap<QString,QString> map = mXML.xmlRead(fileName);
    if(map.isEmpty()) return;
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
    emit signal_focus_in( ui->tabWidget->tabText( index ) );
}

void H2Ops::on_tabWidget_tabBarClicked(int index)
{
    emit signal_focus_in( ui->tabWidget->tabText( index ) );
}


////////////////////////////////////// 点击发送指令
void H2Ops::on_pushButton_starting_home_clicked()
{
   qDebug() << "mrgSetRobotHomeWavetable()" << mrgSetRobotHomeWavetable(m_ViHandle, m_RoboName, -1);
}


//! single move
void H2Ops::on_toolButton_singlestep_x_dec_clicked()
{
    double offset = ui->doubleSpinBox_Increament->value();
    double speed = ui->doubleSpinBox_Velocity->value();
    double time = offset/speed;

    qDebug() << "mrgRobotRelMove" << mrgRobotRelMove(m_ViHandle, m_RoboName, -1, 0-offset, 0, 0, time, -1);
}

void H2Ops::on_toolButton_singlestep_x_inc_clicked()
{
    double offset = ui->doubleSpinBox_Increament->value();
    double speed = ui->doubleSpinBox_Velocity->value();
    double time = offset/speed;

    qDebug() << "mrgRobotRelMove" << mrgRobotRelMove(m_ViHandle, m_RoboName, -1, offset, 0, 0, time, -1);
}

void H2Ops::on_toolButton_singlestep_y_dec_clicked()
{
    double offset = ui->doubleSpinBox_Increament->value();
    double speed = ui->doubleSpinBox_Velocity->value();
    double time = offset/speed;

    qDebug() << "mrgRobotRelMove" << mrgRobotRelMove(m_ViHandle, m_RoboName, -1, 0, 0-offset, 0, time, -1);
}

void H2Ops::on_toolButton_singlestep_y_inc_clicked()
{
    double offset = ui->doubleSpinBox_Increament->value();
    double speed = ui->doubleSpinBox_Velocity->value();
    double time = offset/speed;

    qDebug() << "mrgRobotRelMove" << mrgRobotRelMove(m_ViHandle, m_RoboName, -1, 0, offset, 0, time, -1);
}

//! jog move
void H2Ops::on_toolButton_jogmode_x_dec_pressed()
{
    double cr_speed = m_Data["CrawlingVelocity"].toDouble();
    double cr_time = m_Data["CrawlingTime"].toDouble();
    double speed = m_Data["MaximumVelocity"].toDouble();

//    qDebug() << QString("mrhtRobotMoveJog(%1,%2,%3,%4,%5)").arg(0).arg(cr_time).arg(0-cr_speed).arg(speed).arg(-1)
//             << mrhtRobotMoveJog(m_ViHandle, m_RoboName, 0, cr_time, 0-cr_speed, speed, -1);
}

void H2Ops::on_toolButton_jogmode_x_inc_pressed()
{
    double cr_speed = m_Data["CrawlingVelocity"].toDouble();
    double cr_time = m_Data["CrawlingTime"].toDouble();
    double speed = m_Data["MaximumVelocity"].toDouble();

//    qDebug() << "mrhtRobotMoveJog"
//             << mrhtRobotMoveJog(m_ViHandle, m_RoboName, 0, cr_time, cr_speed, speed, -1);
}

void H2Ops::on_toolButton_jogmode_y_dec_pressed()
{
    double cr_speed = m_Data["CrawlingVelocity"].toDouble();
    double cr_time = m_Data["CrawlingTime"].toDouble();
    double speed = m_Data["MaximumVelocity"].toDouble();

//    qDebug() << "mrhtRobotMoveJog"
//             << mrhtRobotMoveJog(m_ViHandle, m_RoboName, 1, cr_time, 0-cr_speed, speed, -1);
}

void H2Ops::on_toolButton_jogmode_y_inc_pressed()
{
    double cr_speed = m_Data["CrawlingVelocity"].toDouble();
    double cr_time = m_Data["CrawlingTime"].toDouble();
    double speed = m_Data["MaximumVelocity"].toDouble();

//    qDebug() << "mrhtRobotMoveJog"
//             << mrhtRobotMoveJog(m_ViHandle, m_RoboName, 1, cr_time, cr_speed, speed, -1);
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
    qDebug() << "mrgRobotStop:" << mrgRobotStop(m_ViHandle, m_RoboName, -1);
}



void H2Ops::on_pushButton_apply_clicked()
{

}



/////////////////////////////////////////////////////////////
//更新标签的实时数值
void H2Ops::slot_handle_timeout()
{
    if(m_strDevInfo == "")
        return;

    updateDeviceStatus();
    updateOperate();
    updateDigitalIO();
    updateHoming();
    updateManual();
    updateMonitor();
    updateDebug();
    updateDiagnosis();

}


void H2Ops::updateDeviceStatus()
{
//    ui->H2Status_1
//    ui->H2Status_2

}

void H2Ops::updateOperate()
{
    double rand = qrand() % 50;
    ui->doubleSpinBox_RecordNumber->setValue(rand);
    ui->doubleSpinBox_target_position_x->setValue(rand);
    ui->doubleSpinBox_target_position_y->setValue(rand);
    ui->doubleSpinBox_actual_position_x->setValue(rand);
    ui->doubleSpinBox_actual_position_y->setValue(rand);
    ui->doubleSpinBox_Mileage_x->setValue(rand);
    ui->doubleSpinBox_Mileage_y->setValue(rand);

    if( qrand()%2 )
    {
        ui->radHome->setChecked(true);
        ui->radES->setChecked(false);
    }
    else
    {
        ui->radHome->setChecked(false);
        ui->radES->setChecked(true);
    }

}

void H2Ops::updateDigitalIO()
{

}

void H2Ops::updateHoming()
{
    ui->label_homing_target->setText(m_Data["Target"]);
    ui->label_homing_direction->setText(m_Data["Direction"]);

    double rand = qrand() % 101;
    ui->doubleSpinBox_homing_actual_pos_x->setValue(rand);

    rand = qrand() % 101;
    ui->doubleSpinBox_homing_actual_pos_y->setValue(rand);

}

void H2Ops::updateManual()
{

    double rand = qrand() % 101;
    ui->doubleSpinBox_currentPos_x->setValue(rand);

    rand = qrand() % 101;
    ui->doubleSpinBox_currentPos_y->setValue(rand);
}


void H2Ops::updateMonitor()
{
    double rand = qrand() % 101;
    m_splineChart1->dataAppend(rand);

    rand = qrand() % 101;
    m_splineChart2->dataAppend(rand);

}

void H2Ops::updateDebug()
{

}

void H2Ops::updateDiagnosis()
{

}
