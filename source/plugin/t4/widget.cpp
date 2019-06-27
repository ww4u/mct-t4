#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QtConcurrent>
#include "../../sys/sysapi.h"
#include <QDir>


#define MRQ_UPDATE  "/mrq.dat"
#define MRH_UPDATE  "/mrh.dat"
#define UNDOEXE     "/undo.exe"
#define MRQ_UPDATE_EXE "/MRQ_Update/MegaRobo_Update.exe"

//! file path
#define DIR_TEMP    QDir::tempPath()

#define MRQ_FILE    (DIR_TEMP + "/output/mrq.dat")
#define MRH_FILE    (DIR_TEMP + "/output/mrh.dat")

#define UPDATE_FILE (DIR_TEMP + "/output/update.txt")



Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint);
    ui->progressBar->hide();
    ui->btnShow->hide();
    ui->textBrowser->hide();

    m_vi = 0;

    m_updateProcess = NULL;
    m_undoProcess = NULL;

    connect(this, SIGNAL(sigReboot()),this, SLOT(slotReboot()));

    watcher = new QFutureWatcher<int>;
    connect(watcher, SIGNAL(finished()),this, SLOT(slotGetRunState()));
}

Widget::~Widget()
{
    destory();
    delete ui;
    if(m_vi>0){
        mrgCloseGateWay( m_vi);
    }
}

void Widget::attatchPlugin(XPlugin *xp)
{
    m_pPlugin = xp;
    m_addr = m_pPlugin->addr();
    isAdmin = m_pPlugin->isAdmin();
}
int Widget::reOpenDevice()
{
    int ret;
    m_pPlugin->close();

    do{
        m_vi = mrgOpenGateWay(m_addr.toLocal8Bit().data(), 200);
        if( m_vi < 0){
            ret = -1;
            sysInfo("Open GateWay Fail", 1);
            break;
        }

        int robotNames[128] = {0};
        ret = mrgGetRobotName(m_vi, robotNames);
        if(ret <=0){
            sysInfo("Get Robot Name Fail", 1);
            ret = -1;
            break;
        }
        m_robotID = robotNames[0];

        int deviceNames[128] = {0};
        //ret = mrgGetRobotDevice(m_vi, m_robotID, deviceNames);
        recvID = QString::number(1);

    }while(0);

    return ret;
}
void Widget::on_buttonBox_clicked(QAbstractButton *button)
{
    ui->labelStatus->hide();
    ui->btnShow->show();
    ui->textBrowser->clear();

    if((QPushButton*)(button) == ui->buttonBox->button(QDialogButtonBox::Ok)){
        if(reOpenDevice()<0){
            //!reopen error
            button->show();
            ui->labelStatus->setText( tr("Open Device Fail") );
            ui->labelStatus->show();
            return;
        }
        button->hide();
    }else {
        destory();
        if(m_vi > 0){
            mrgCloseGateWay( m_vi);
        }
        this->close();
        return;
    }

    QString undoExePath = qApp->applicationDirPath() + UNDOEXE;
    QStringList arguments;
    arguments << "-x" << "-p" << sPath;

    MThead *mthread = new MThead;
    connect(mthread,SIGNAL(resultReady(QString)),this,SLOT(slotReadUndoResult(QString)));
    mthread->setExeCmd(undoExePath);
    mthread->setArguments(arguments);
    mthread->start();
}

void Widget::on_toolButton_clicked()
{
    sPath = QFileDialog::getOpenFileName(this,
          tr("Open File"), NULL, tr("(*.upd)"));
    ui->lineEdit->setText(sPath);
}

int Widget::upgressMRH()
{
    int ret;
    do{
        QFile mrhFile(MRH_FILE);
        if(!mrhFile.open(QIODevice::ReadOnly)){
            ret = -1;
            break;
        }

        QByteArray ba = mrhFile.readAll();
        ret = mrgStorageWriteFile(m_vi, 0, (char *)"/media/usb0/",
                                  (char *)MRH_UPDATE, (unsigned char*)(ba.data()), ba.size());
        if(ret!=0){
            break;
        }

        ret = mrgSysUpdateFileStart(m_vi, (char *)MRH_UPDATE);
        if(ret !=0 ){
            break;
        }

        QString strCmd = "rm -rf /media/usb0/" + QString(MRH_UPDATE);
        mrgSystemRunCmd(m_vi, strCmd.toLocal8Bit().data(), 1);

        ret = copyDemo();
        if( ret != 0 )
            break;

        ret = copyUpdateInfo();
        if(ret != 0)
            break;
    }while(0);

    if(ret!=0){
        return -1;
    }else{
        return 0;
    }
}
void Widget::showError(const QString &text)
{
    ui->textBrowser->append(text);
    if( text.contains("Error") ){
        ui->labelStatus->setText(tr("Update Error"));
        ui->labelStatus->show();
    }
}

int Widget::copyDemo()
{
    QMap<QString, QStringList> demoMap;

    demoMap["0"] = QStringList() << "MCT_motion.mrp" << "debug.xml";
    demoMap["1"] = QStringList() << "MCT_motion.mrp" << "debug.xml";
    demoMap["2"] = QStringList() << "MCT_motion.mrp" << "debug.xml";

    QString cmd;
    int ret;
    int count=0;

    QMapIterator<QString, QStringList> it(demoMap);
    while(it.hasNext()){
        it.next();
        cmd = "mkdir -p " + m_pPlugin->demoPath() + "/" + it.key();
        ret = mrgSystemRunCmd( m_vi, cmd.toLatin1().data(), 0 );
        if(ret != 0){
            sysInfo("mkdir fail", 1);
            continue;
        }

        foreach (QString str, it.value()) {

            QByteArray ba;
            {
                QString path = QString("%1%2/%3/%4").arg(DIR_TEMP).arg("/output/demo").arg(it.key()).arg(str);
                qDebug() << path;
                QFile f( path );
                if( !f.open(QIODevice::ReadOnly) ){
                    continue;
                }
                ba = f.readAll();
                f.close();
            }

            ret = mrgStorageWriteFile( m_vi,
                                       0,
                                       (m_pPlugin->demoPath()+"/" + it.key()).toLatin1().data(),
                                       str.toLatin1().data(),
                                       (unsigned char*)(ba.data()),
                                       ba.size()
                                       );
            if(ret !=0){
                continue;
                //sysInfo("Write File fail", 1);
            }else{
                count += 1;
            }
        }
    }

    //! count = keysnum * length
    int num = demoMap.keys().size() * demoMap.value(demoMap.firstKey()).size();qDebug() << num;
    //! file num
    if(count != num){
        //! \todo error
        return -1;
    }
    return 0;
}

int Widget::copyUpdateInfo()
{
    QString cmd;
    int ret;
    do{
        cmd = "mkdir -p " + m_pPlugin->modelPath();
        ret = mrgSystemRunCmd( m_vi, cmd.toLatin1().data(), 0 );
        if(ret != 0){
            sysInfo("Mkdir Fail", 1);
            break;
        }

        QFile f(UPDATE_FILE);
        if(!f.open(QIODevice::ReadOnly)){
            sysInfo("Open Update.txt Fail", 1);
            ret = -1;
            break;
        }

        QByteArray ba;
        ba = f.readAll();
        f.close();

        ret = mrgStorageWriteFile( m_vi,
                                   0,
                                   m_pPlugin->modelPath().toLatin1().data(),
                                   QString("update.txt").toLatin1().data(),
                                   (unsigned char*)(ba.data()),
                                   ba.size()
                                   );
        if(ret != 0){
            sysInfo("Write update.txt Fail", 1);
            break;
        }

    }while(0);
    return ret;
}

void Widget::slot_updateMRH()
{
    ui->progressBar->setMaximum(0);
    ui->textBrowser->append("Notify: MRH Updating...\n");

    QFuture<int> future = QtConcurrent::run(this, &Widget::upgressMRH);
    watcher->setFuture(future);
}

void Widget::slot_startMRQUpdate(int)
{
    MThead *mthread = new MThead;
    connect(mthread,SIGNAL(resultReady(QString)),this,SLOT(slotReadMRQResult(QString)));

    QString updateMRQProgram = qApp->applicationDirPath() + MRQ_UPDATE_EXE;
    QStringList arguments;
    //arguments << (sPath.left(sPath.lastIndexOf("/")) + MRQ_UPDATE) << m_addr << recvID;
    arguments << MRQ_FILE << m_addr << recvID;

    mthread->setExeCmd(updateMRQProgram);
    mthread->setArguments(arguments);
    mthread->start();
}

void Widget::slotReadUndoResult(QString text)
{
    ui->textBrowser->append(text);
    if(text.contains("Success")){
        slot_startMRQUpdate(0);
    }
    if( text.contains("Error") ){
        ui->labelStatus->setText( tr("File Error") );
        ui->labelStatus->show();
        ui->buttonBox->button(QDialogButtonBox::Ok)->show();
    }
}

void Widget::slotReadMRQResult(QString text)
{
    ui->textBrowser->append(text);
    ui->progressBar->show();

    if( text.contains("Notify:Update Complete!") ){
        //! update mrh
        slot_updateMRH();
    }

    if( text.contains("Error") ){
        ui->labelStatus->setText(tr("Update MRQ Fail"));
        ui->labelStatus->show();
        return;
    }

    //! percent
    QRegExp rx("(\\d+)");
    QString _str = text;
    QStringList list;
    int pos = 0;

    while ((pos = rx.indexIn(_str, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }
    foreach (QString item, list) {
        ui->progressBar->setValue( item.toInt() );
    }
}

void Widget::Append(const QString &text)
{
    emit AppendText(text);
}

void Widget::slotReboot()
{
    if( QMessageBox::information(this,tr("reboot"),tr("Reboot now?")) == QMessageBox::Ok ){
        if(m_pPlugin->isRebootable()){
            mrgSystemRunCmd(m_vi, (char *)"reboot", 0);
        }
        this->close();

        //！ delete

    }else{

    }
}
void Widget::reboot()
{
    emit sigReboot();
}
void Widget::remove()
{
    QString qfilePath = qApp->applicationDirPath() + MRQ_UPDATE;
    QString hfilePath = qApp->applicationDirPath() + MRH_UPDATE;
    QFile qfile(qfilePath);
    QFile hfile(hfilePath);
    if(qfile.exists()){
        qfile.remove();
    }
    if(hfile.exists()){
        hfile.remove();
    }
}
void Widget::destory()
{
    remove();
    if(m_updateProcess){
        m_updateProcess->close();
        delete m_updateProcess;
        m_updateProcess = NULL;
    }
    if(m_undoProcess){
        m_undoProcess->close();
        delete m_undoProcess;
        m_undoProcess = NULL;
    }
}

void Widget::on_btnShow_toggled(bool checked)
{
    if(checked){
        ui->btnShow->setText( tr("Hide Information") );
        ui->textBrowser->show();
    }else{
        ui->btnShow->setText( tr("Show Information") );
        ui->textBrowser->hide();
    }
}

void Widget::slotGetRunState()
{
    int state = watcher->result();qDebug() << "state:" << state;
    if( state != 0 ){
        showError( "Error: MRH Update Fail" );
        ui->buttonBox->button(QDialogButtonBox::Ok)->show();
    }
    else{
        ui->progressBar->setValue(100);
        ui->labelStatus->setText( tr("Update Complete!") );
        reboot();
    }
}


MThead::MThead(QObject *parent):
    QThread(parent)
{

}

void MThead::run()
{
    Q_ASSERT(cmd != NULL);
    Q_ASSERT(!argument.isEmpty());
    m_process = new QProcess;
    connect(m_process,SIGNAL(finished(int)),this,SLOT(deleteLater()));
    connect(m_process,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
    m_process->start(cmd,argument);
    if(!m_process->waitForStarted()){
        qDebug() << "Error: Start Fail";
    }
    m_process->waitForFinished(-1);
}

void MThead::slotReadyRead()
{
    QByteArray ba = m_process->readAll();
    qDebug() << ba;
    emit resultReady(QString(ba));
}
