#include "TestPanelDialog.h"
#include "ui_TestPanelDialog.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

TestPanelDialog::TestPanelDialog(ViSession vi, int robot, int device, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestPanelDialog)
{
    ui->setupUi(this);
    m_vi = vi;
    m_robotID = robot;
    m_deviceID = device;

     m_isDebugRunFlag = false;
     m_threadOpsDebug = NULL;

     ui->textBrowser->setHidden(true);

     //隐藏
     ui->spinBox_record->setVisible(false);

}

TestPanelDialog::~TestPanelDialog()
{
    delete ui;
    if( m_threadOpsDebug != NULL ){
        m_threadOpsDebug->requestInterruption();
        m_threadOpsDebug->wait();
        delete m_threadOpsDebug;
    }
}

void TestPanelDialog::on_pushButton_updateFirmware_clicked()
{
    QString absPathFileName = QFileDialog::getOpenFileName(this, "文件对话框", "", "升级文件(*.mrh)");
    qDebug() << absPathFileName;
    if(absPathFileName == "")
        return;

    auto lambda = [=](int &ret)
    {
        time_t tm_begin = time(NULL);

        QFile file(absPathFileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << QString("Can't ReadOnly open the file: %1").arg(absPathFileName);
            return;
        }

        int filesize = file.size();
        QString filename = absPathFileName.split("/", QString::SkipEmptyParts).last();

        qDebug() << "download file start:" << filename << filesize;
        ui->pushButton_updateFirmware->setText("正在下载...");

        unsigned char *ptr = file.map(0, filesize);

        ret = mrgStorageWriteFile(m_vi, 0, (char *)"/media/usb0/",
                                  filename.toLocal8Bit().data(), ptr, filesize);
        file.unmap(ptr);
        file.close();
        qDebug() << "download file end:" << filename << ret;
        if(ret != 0)
        {
            ret = -1;
            return;
        }

        qDebug() << "system update start:" << filename;
        ui->pushButton_updateFirmware->setText("正在升级...");

        ret = mrgSysUpdateFileStart(m_vi, filename.toLocal8Bit().data());
        qDebug() << "system update end:" << ret;

        QString strCmd = "rm -rf /media/usb0/" + filename;
        mrgSystemRunCmd(m_vi, strCmd.toLocal8Bit().data(), 1);
        if(ret != 0)
        {
            ret = -2;
            return;
        }

        qDebug() << "Run time:" << time(NULL) - tm_begin;
        ret = 0;
        return;
    };

    XThread *thread = new XThread(lambda);
    connect(thread, SIGNAL(signalFinishResult(int)), this, SLOT(updateFirmwareEndTips(int)));
    thread->start();

    return;
}

void TestPanelDialog::updateFirmwareEndTips(int ret)
{
    ui->pushButton_updateFirmware->setText("升级固件");
    if(ret == 0)
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("\n\t升级成功\t\t \n\n\t是否重启MRH-T？\t \n");
        msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        if(msgBox->exec() == QMessageBox::Ok)
        {
            //! 重启-T
            mrgSystemRunCmd(m_vi, (char *)"reboot", 0);
        }
    }
    else if(ret == -1)
    {
        QMessageBox::critical(this, "错误", "下载失败!");
    }
    else if(ret == -2)
    {
        QMessageBox::critical(this, "错误", "升级失败!");
    }
    else
    {
        QMessageBox::critical(this, "错误", "失败(" + QString::number(ret) + ")");
    }
    return;
}

void TestPanelDialog::on_pushButton_ScanMotionFile_clicked()
{
    auto lambda = [&]()
    {
        QString strFindMotionFiles = "";
        char buff[4096] = "";

        //! 搜索网络
        memset(buff, 0, sizeof(buff));
        mrgStorageMotionFileQuery(m_vi, 0, buff, sizeof(buff));
        strFindMotionFiles = QString("%1").arg(buff);

        if(strFindMotionFiles.toLower().contains(".pvt") || strFindMotionFiles.toLower().contains(".mrp"))
        {
            ui->comboBox_MotionFile->addItems(strFindMotionFiles.split(',', QString::SkipEmptyParts));
        }
    };

    ui->comboBox_MotionFile->clear();
    XThread *thread = new XThread(lambda);
    thread->start();
}

void TestPanelDialog::on_pushButton_ImportMotionFile_clicked()
{
    if(m_robotID <= 0)
    {
        QMessageBox::critical(this, "错误", "没有机器人");
        return;
    }

    QString strMotionFileName = ui->comboBox_MotionFile->currentText();
    if(strMotionFileName == "")
    {
        QMessageBox::critical(this, "错误", "选择文件名为空");
        return;
    }
    int ret = mrgRobotMotionFileImport(m_vi, m_robotID, strMotionFileName.toLocal8Bit().data());
    if(ret != 0){
        QMessageBox::critical(this, "错误", "文件导入失败" + QString::number(ret));
    }
}

void TestPanelDialog::on_pushButton_RunStop_clicked()
{

    auto func = [this](int &ret)
    {
        int section = ui->spinBox_section->value();
        int line = ui->spinBox_record->value();
        bool isCyclic = ui->checkBox_Cyclic->isChecked();
        bool noBreak = true;
        do
        {
#if 0       //! 默认方式,1.21之前的版本
            ret = mrgRobotFileResolve(m_vi, m_robotID, section, line, 0, 20000);
            if(ret != 0) {
                qDebug() << "mrgRobotFileResolve" << ret;
                return;
            }

            ret = mrgRobotRun(m_vi, m_robotID, 0);
            if(ret != 0) {
                qDebug() << "mrgRobotRun" << ret;
                return;
            }

            while(1)
            {
                char buff[8] = "";
                mrgGetRobotCurrentRecord(m_vi, m_robotID, buff);
                QStringList lst = QString(buff).split(":", QString::SkipEmptyParts);
                if(lst.size() >= 2)
                {
                    ui->lcdNumber_section->display(lst.at(0));
                    ui->lcdNumber_record->display(lst.at(1));
                }

                QThread::msleep(500);
                char state[8] = "";
                mrgGetRobotStates(m_vi, m_robotID, 0, state);
                QString strState = QString(state);
                if(strState == "ERROR")
                {
                    qDebug() << "mrgRobotFileResolve Run:" << strState;
                    return;
                }

                if(strState == "IDLE" || strState == "STOP")
                {
                    break;
                }
                if ( m_threadOpsDebug->isInterruptionRequested() ){
                    mrgRobotStop(m_vi, m_robotID, -1);
                    noBreak = false;
                    break;
                }
            }
#endif

#if 0
            // 1.21之后的版本,永久等待
            ret = mrgRobotFileResolve(m_vi, m_robotID, section, line, 0, 0);
            qDebug() << "mrgRobotFileResolve" << ret;
            if(ret != 0) {
                return;
            }
            if ( m_threadOpsDebug->isInterruptionRequested() ){
                mrgRobotStop(m_vi, m_robotID, -1);
                noBreak = false;
                break;
            }
#else            
            ret = mrgRobotFileResolve(m_vi, m_robotID, section, line, 0, -1);
            if(ret != 0) {
                qDebug() << "mrgRobotFileResolve" << ret;
                return;
            }

            QString strLastStates = "";
            while(1)
            {
                QThread::msleep(100);

                char buff[8] = "";
                mrgGetRobotCurrentRecord(m_vi, m_robotID, buff);
                QStringList lst = QString(buff).split(":", QString::SkipEmptyParts);
                if(lst.size() >= 2)
                {
                    ui->lcdNumber_section->display(lst.at(0));
                    ui->lcdNumber_record->display(lst.at(1));
                }

                char state[8] = "";
                mrgGetRobotStates(m_vi, m_robotID, 0, state);
                QString strState = QString(state);
                if(strState == "ERROR")
                {
                    qDebug() << "mrgRobotFileResolve Run:" << strState;
                    return;
                }

                if( (strState == "IDLE" || strState == "STOP")
                        && (strLastStates == strState) )
                {
                    qDebug() << strState << "Running End";
                    break;
                }

                strLastStates = strState;

                if ( m_threadOpsDebug->isInterruptionRequested() ){
                    mrgRobotStop(m_vi, m_robotID, -1);
                    noBreak = false;
                    break;
                }
            }
#endif

            isCyclic = ui->checkBox_Cyclic->isChecked();
        }while(isCyclic && noBreak);

        ui->pushButton_RunStop->setText("运行");
        m_isDebugRunFlag = false;
    }; //end func


    if(m_isDebugRunFlag) //正在运行
    {
        m_isDebugRunFlag = false;

        if( m_threadOpsDebug != NULL ){
            m_threadOpsDebug->requestInterruption();
            m_threadOpsDebug->wait();
        }
        ui->pushButton_RunStop->setText("运行");
    }
    else
    {
        m_isDebugRunFlag = true;
        ui->pushButton_RunStop->setText("停止");

        if(m_vi <= 0) return;
        m_threadOpsDebug = new XThread(func);
        connect(m_threadOpsDebug,&XThread::finished,[&](){ m_threadOpsDebug = NULL; });
        m_threadOpsDebug->start(QThread::LowestPriority);
    }

}

void TestPanelDialog::on_pushButton_ReadMotionFile_clicked()
{
    ui->textBrowser->clear();

    if(ui->textBrowser->isHidden())
    {
        //! 读文件
        int len = 4096 * 1024;
        char *pData = (char *)malloc(len);
        memset(pData, 0, len);

        QString strMotionFileName = ui->comboBox_MotionFile->currentText();
        if(strMotionFileName == "")
        {
            QMessageBox::critical(this, "错误", "选择文件名为空");
            return;
        }

        int ret = mrgStorageMotionFileContextRead(m_vi, strMotionFileName.toLocal8Bit().data(), pData);
        qDebug() << "mrgStorageMotionFileContextRead" << ret;
        QString strFileText = QString(pData);
        free(pData);
        if(ret <= 0){
            QMessageBox::critical(this, "错误", "文件读取失败" + QString::number(ret));
            return;
        }

        ui->textBrowser->setText(strFileText);
        ui->textBrowser->setHidden(false);
        ui->pushButton_ReadMotionFile->setText("关闭文件");
    }
    else
    {
        ui->textBrowser->setHidden(true);
        ui->pushButton_ReadMotionFile->setText("读取文件");
    }
}

void TestPanelDialog::on_pushButton_test_clicked()
{
#if 0
    {   //! test 1
        //! 测试系统配置MRQ的序列号和版本号
        char version[32] = "11.22.33";
        char sn[32] = "1357924680";

        int ret = mrgSystemSetMRQConfig(m_vi, version, sn);
        qDebug() << "set" << "version:" << version << "sn:" << sn << "ret:" << ret;

        QThread::sleep(2);

        memset(version, 0, sizeof(version));
        memset(sn, 0, sizeof(sn));
        ret = mrgSystemGetMRQConfig(m_vi, version, sn);
        qDebug() << "get" << "version:" << version << "sn:" << sn << "ret:" << ret;
    }
#endif

#if 0
    {   //! test 2
        //! 测试下载文件到MRH-T上一个指定的位置
        QString absPathFileName = QFileDialog::getOpenFileName(this, "文件对话框", "", "所有文件(*.*)");
        qDebug() << absPathFileName;
        if(absPathFileName == "")
            return;

        QString targetAbsPath = QInputDialog::getText(this, tr("输入框"), tr("请输入保存在MRH-T的位置"));
        if(targetAbsPath == "")
            return;

        auto lambda = [=](int &ret)
        {
            time_t tm_begin = time(NULL);

            QFile file(absPathFileName);
            if(!file.open(QIODevice::ReadOnly))
            {
                qDebug() << QString("Can't ReadOnly open the file: %1").arg(absPathFileName);
                return;
            }

            int filesize = file.size();
            QString filename = absPathFileName.split("/", QString::SkipEmptyParts).last();

            qDebug() << "download file start:" << filename << "size:" << filesize;
            unsigned char *ptr = file.map(0, filesize);
            ret = mrgStorageWriteFile(m_vi, 0, targetAbsPath.toLocal8Bit().data(),
                                      filename.toLocal8Bit().data(), ptr, filesize);
            file.unmap(ptr);
            file.close();
            qDebug() << "download file end:" << filename << ((ret!=0)?"ERROR":"OK");
            if(ret != 0)
            {
                ret = -1;
                return;
            }

            qDebug() << "Run time:" << time(NULL) - tm_begin;
            ret = 0;
            return;
        };

        XThread *thread = new XThread(lambda);
        thread->start();
    }
#endif


    {   //! test 3
        //! 测试下载一个目录到MRH-T上

    }

}
