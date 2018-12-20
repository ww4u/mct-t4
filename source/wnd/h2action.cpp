#include "h2action.h"
#include "ui_h2action.h"

H2Action::H2Action(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Action)
{
    ui->setupUi(this);

    setFocusName( "Record_table" );

    m_strLocalFileName = "";
    m_strDeviceFileName = "MCT_motion.mrp";
    m_fileContext = "";
    m_menu = NULL;

    m_pDelegate = new comboxDelegate(this);
    QStringList prxs;
    prxs << tr("PA") << tr("PRN") << tr("PRA");
    m_pDelegate->setItems( prxs );

    m_delegatePosX          = new DoubleSpinBoxDelegate(2, -9999.99, 9999.99, this);
    m_delegatePosY          = new DoubleSpinBoxDelegate(2, -9999.99, 9999.99, this);
    m_delegateVelocity      = new DoubleSpinBoxDelegate(2, 0.01, 9999.99, this);
    m_delegateAcceleration  = new DoubleSpinBoxDelegate(2, 0, 9999.99, this);

    connect(&m_actionModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(slotModelChanged(QModelIndex,QModelIndex,QVector<int>)));

    connect(ui->tableView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowContextmenu(const QPoint&)));

    connect(ui->tableView,&QTableView::clicked,
            this, [this](QModelIndex index){
        emit signalCurrentRowChanged(index.row()+1);
    });

}

H2Action::~H2Action()
{
    delete ui;
}

void H2Action::slotCurrentRowChanged(QModelIndex index)
{
    int currentRow = index.row();

    emit signalCurrentRowChanged(currentRow);
    qDebug() << "slotCurrentRowChanged" << currentRow;
}

int H2Action::readDeviceConfig()
{
    int ret = -1;
    m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".mrp";

    //! 查找文件
    char filenames[1024] = "";
    ret = mrgStorageMotionFileQuery(mViHandle, 0, filenames, sizeof(filenames));
    qDebug() << "mrgStorageMotionFileQuery" << ret;
    if (ret < 0){
        sysError("mrgStorageMotionFileQuery", ret);
        return -1;
    }
    QStringList lst = QString("%1").arg(filenames).split(',');
    if( !lst.contains(m_strDeviceFileName) )
    {
        qDebug() << m_strDeviceFileName + " not exist in device";
        sysError(m_strDeviceFileName + " not exist in device");
        return -1;
    }

    //! 读文件
    int len = 4096 * 1024;
    char *pData = (char *)malloc(len);
    memset(pData, 0, len);
    ret = mrgStorageMotionFileContextRead(mViHandle, m_strDeviceFileName.toLocal8Bit().data(), pData, len);
    qDebug() << "mrgStorageMotionFileContextRead" << ret;
    if(ret <= 0){
        m_fileContext = "";
        sysError("mrgStorageMotionFileContextRead");
        goto ERR;
    }else{
        m_fileContext = QString("%1").arg(pData);//保存到类中

        //保存到本地文件
        if(0 != writeFile(m_strLocalFileName, m_fileContext) ){
            sysError("H2Action:readDeviceConfig:writeFile error");
            goto ERR;
        }

        //保存到model
        if(0 != m_actionModel.input(m_strLocalFileName) ){
            sysError("H2Action:readDeviceConfig:input error");
            goto ERR;
        }
        ret = 0;
        goto END;
    }

ERR:
    ret = -1;
END:
    free(pData);
    return ret;
}

int H2Action::writeDeviceConfig()
{
    m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".mrp";

    int ret = -1;
    ret = mrgStorageMotionFileSaveContext(mViHandle,
                                          m_fileContext.toLocal8Bit().data(),
                                          m_fileContext.size(),
                                          m_strDeviceFileName.toLocal8Bit().data());
    qDebug() << "mrgStorageMotionFileSaveContext" << ret;
    if(ret < 0){
        sysError("mrgStorageMotionFileSaveContext", ret);
        return -1;
    }

    ret = mrgRobotMotionFileImport(mViHandle, mRobotName, m_strDeviceFileName.toLocal8Bit().data());
    qDebug() << "mrgRobotMotionFileImport" << ret;
    if(ret != 0){
        sysError("mrgRobotMotionFileImport", ret);
    }
    return ret;
}

int H2Action::loadConfig()
{
    m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".mrp";
    QFile file(m_strLocalFileName);
    //如果不存在配置文件就用公共的默认的配置文件
    if( !file.exists() )
        m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/action_default.mrp";

    //! load action from csv
    sysInfo("H2Action::loadConfig",m_strLocalFileName);
    int ret = m_actionModel.input(m_strLocalFileName);  //保存到model
    m_fileContext = readFile(m_strLocalFileName);       //保存到类中

    return ret;
}

int H2Action::saveConfig()
{
    //! save action to csv
    m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".mrp";
    int ret = m_actionModel.output( m_strLocalFileName );   //将界面数据保存到本地文件
    m_fileContext = readFile(m_strLocalFileName);       //保存到类中
    return ret;
}

void H2Action::updateShow()
{
    ui->tableView->setModel( &m_actionModel );
    ui->tableView->setItemDelegateForColumn( 0, m_pDelegate );

    ui->tableView->setItemDelegateForColumn( 1, m_delegatePosX );
    ui->tableView->setItemDelegateForColumn( 2, m_delegatePosY );
    ui->tableView->setItemDelegateForColumn( 3, m_delegateVelocity );
    ui->tableView->setItemDelegateForColumn( 4, m_delegateAcceleration );

}

void H2Action::slotModelChanged(QModelIndex index1, QModelIndex index2, QVector<int> vector)
{
//    qDebug() << "slotModelChanged:" << index1 << index2 << vector;
    emit signalModelDataChanged(true);
}

QString H2Action::readFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << QString("Can't ReadOnly open the file: %1").arg(fileName);
        return "";
    }

    QByteArray array = file.readAll();
    file.close();
    return QString(array);
}

int H2Action::writeFile(QString fileName, QString text)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << QString("Can't WriteOnly open the file: %1").arg(fileName);
        return -1;
    }

    file.write(text.toUtf8());
    file.close();
    return 0;
}

void H2Action::translateUI()
{
    ui->retranslateUi(this);
}

void H2Action::modfiyOneRecord(int row, QString type, double x, double y, double v, double a)
{
    if (row < 0)
        return;

    if(type != "")
        m_actionModel.setData( m_actionModel.index( row, 0), QVariant( type), Qt::EditRole );

    if(x >= 0)
        m_actionModel.setData( m_actionModel.index( row, 1), QVariant( x ), Qt::EditRole );

    if(y >= 0)
        m_actionModel.setData( m_actionModel.index( row, 2), QVariant( y ), Qt::EditRole );

    if(v >= 0)
        m_actionModel.setData( m_actionModel.index( row, 3), QVariant( v ), Qt::EditRole );

    if(a >= 0)
        m_actionModel.setData( m_actionModel.index( row, 4), QVariant( a ), Qt::EditRole );
}

void H2Action::setWorkStrokeX(double WorkStrokeX)
{
    m_delegatePosX->slotSetValueRange(0-WorkStrokeX, WorkStrokeX);
}

void H2Action::setWorkStrokeY(double WorkStrokeY)
{
    m_delegatePosY->slotSetValueRange(0-WorkStrokeY, WorkStrokeY);
}

void H2Action::slotShowContextmenu(const QPoint& pos)
{
    if(!((ui->tableView->selectionModel()->selectedIndexes()).empty()))
    {
        if(m_menu != NULL)
            delete m_menu;

        m_menu = new QMenu(ui->tableView);
        QAction *actionRun = m_menu->addAction(tr("Run"));
        connect(actionRun, SIGNAL(triggered(bool)), this, SLOT(soltActionRun()));

        m_menu->exec(QCursor::pos());
        ui->tableView->selectionModel()->clear();
    }
}

void H2Action::soltActionRun()
{
    int row = ui->tableView->selectionModel()->selectedIndexes().at(0).row();
    qDebug() << "soltActionRun" << row;

    //查询点击使能状态
    int ret = -1, v1 = 0, v2 = 0;
    ret = mrgMRQDriverState_Query(mViHandle, mDeviceName, 0, &v1);
    ret += mrgMRQDriverState_Query(mViHandle, mDeviceName, 0, &v2);
    qDebug() << "mrgMRQDriverState_Query" << ret << ":" << v1 << v2;
    if((ret != 0) || (v1 != 1) || (v2 != 1)){
        QMessageBox::warning(this,tr("warning"),tr("Device motor uneable"));
        return;
    }

    int homeVaild = mrgGetRobotHomeRequire(mViHandle, mRobotName);
    qDebug() << "mrgGetRobotHomeRequire" << homeVaild;
    if(homeVaild == 1)
    {//表示需要回零
        QMessageBox::warning(this,tr("warning"),tr("Device Homing Invalid"));
        return;
    }
    ui->tableView->selectRow(row);

    int recordNumber = row+1;
    QString strType = ui->tableView->model()->index(row, 0).data().toString();
    double posX = ui->tableView->model()->index(row, 1).data().toDouble();
    double posY = ui->tableView->model()->index(row, 2).data().toDouble();
    double velocity = ui->tableView->model()->index(row, 3).data().toDouble();
    double acceleration = ui->tableView->model()->index(row, 4).data().toDouble();

#if 0
    //! 先将数据下载设备，然后发送文件行索引号进行移动
    ret = saveConfig();
    ret += writeDeviceConfig();
    if(ret != 0){
        QMessageBox::warning(this,tr("warning"),tr("Data download to device error!"));
        return;
    }

    auto func = [&]()
    {
        ret = mrgRobotFileResolve(mViHandle, mRobotName, 0, recordNumber, 0, 20000);
        qDebug() << "mrgRobotFileResolve" << ret;
        if(ret != 0) {
            sysError("mrgRobotFileResolve", ret);
            return;
        }

        ret = mrgRobotRun(mViHandle, mRobotName, 0);
        qDebug() << "mrgRobotRun" << ret;
        if(ret != 0) {
            sysError("mrgRobotRun", ret);
            return;
        }

        ret = mrgRobotWaitEnd(mViHandle, mRobotName, 0, 0);
        qDebug() << "mrgRobotWaitEnd" << ret;
        if(ret != 0) {
            sysError("mrgRobotWaitEnd", ret);
            return;
        }
    };

#else
    //! 解析界面的数据PA PRA PRN,手工移动
    auto func = [=]()
    {
        int ret = -1;
        float time = -1;

        if(strType == "PA"){
            float fx = -1, fy = -1, fz = -1;
            ret = mrgGetRobotCurrentPosition(mViHandle, mRobotName, &fx, &fy, &fz);
            if(ret < 0) {
                sysError("mrgGetRobotCurrentPosition", ret);
                return;
            }

            time = sqrt( pow(posX-fx,2) + pow(posY-fy,2) ) / (0.7 * velocity) ;
            qDebug() << "mrgRobotMoveL PA offset time" << posX << posY << time;
#if 0
            ret = mrgRobotMoveL(mViHandle, mRobotName, -1, posX, posY, 0, time, 0); //函数执行暂时存在问题
#else
            ret = mrgRobotRelMoveL(mViHandle, mRobotName, -1, posX-fx, posY-fy, 0, time, 0);
#endif
        }
        else if(strType == "PRA" || strType == "PRN" ){
            time = sqrt( pow(posX,2) + pow(posY,2) ) / (0.7 * velocity) ;
            qDebug() << "mrgRobotRelMoveL PRA/PRN offset time" << posX << posY << time;
            ret = mrgRobotRelMoveL(mViHandle, mRobotName, -1, posX, posY, 0, time, 0);
        }
        else{
            qDebug() << "soltActionRun type error!";
        }
        qDebug() << "soltActionRun end" << ret;
    };
#endif

    XThread *thread = new XThread(func);
    thread->start();
}
