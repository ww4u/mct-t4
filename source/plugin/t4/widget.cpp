#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QtConcurrent>
#include "../../sys/sysapi.h"


#define MRQ_UPDATE  "/mrq.dat"
#define MRH_UPDATE  "/mrh.dat"
#define UNDOEXE     "/undo.exe"
#define MRQ_UPDATE_EXE "/MRQ_Update/MegaRobo_Update.exe"

Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint);
    ui->progressBar->hide();
    ui->btnShow->hide();
    ui->textBrowser->hide();

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
}

void Widget::attatchPlugin(XPlugin *xp)
{
    m_pPlugin = xp;
    m_addr = m_pPlugin->addr();
}
void Widget::reOpenDevice()
{
    m_pPlugin->close();
    m_vi = mrgOpenGateWay(m_addr.toLocal8Bit().data(), 200);
    if(m_vi <= 0){
        //! \todo
    }
    int robotNames[128] = {0};
    int ret = mrgGetRobotName(m_vi, robotNames);
    if(ret <=0){
        //! \todo
    }else if(ret ==1){
        m_robotID = robotNames[0];
    }else{}

    int deviceNames[128] = {0};
    //ret = mrgGetRobotDevice(m_vi, m_robotID, deviceNames);
    recvID = QString::number(1);

}
void Widget::on_buttonBox_clicked(QAbstractButton *button)
{
    ui->labelStatus->hide();
    ui->btnShow->show();
    ui->textBrowser->clear();

    if((QPushButton*)(button) == ui->buttonBox->button(QDialogButtonBox::Ok)){
        reOpenDevice();
        button->hide();
    }else {
        destory();
        this->close();
        return;
    }

    QString undoExePath = qApp->applicationDirPath() + UNDOEXE;
    QStringList arguments;
    arguments << "-x" << "-p" << sPath;
//    QProcess *myProcess = new QProcess(this);
//    m_undoProcess = myProcess;
//    m_undoProcess->start(undoExePath, arguments);
//    if( m_undoProcess->waitForFinished(1000) ){
//        QByteArray st = m_undoProcess->readAllStandardOutput();
//        if(QString(st).contains("Success")){
//            slot_startMRQUpdate(0);
//            delete m_undoProcess;
//            m_undoProcess = NULL;
//            return;
//        }
//    }
//    slotHandleError();
//    delete m_undoProcess;
//    m_undoProcess = NULL;
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
        QFile mrhFile(sPath.left(sPath.lastIndexOf("/")) + MRH_UPDATE);
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
                QFile f( qApp->applicationDirPath()+"/dataset/demo/" +it.key() + "/" + str );
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
                sysInfo("Write File fail", 1);
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
            sysInfo("mkdir fail", 1);
            break;
        }

        QFile f(qApp->applicationDirPath()+"/doc/readme.txt");
        if(!f.open(QIODevice::ReadOnly)){
            sysInfo("Open readme.txt fail", 1);
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
            sysInfo("Write update.txt fail", 1);
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

void Widget::callback()
{
//    m_updateProcess = new QProcess;
//    connect(m_updateProcess,SIGNAL(finished(int,QProcess::ExitStatus)),m_updateProcess,SLOT(deleteLater()));
//    connect(m_updateProcess,&QProcess::readyRead,this,[=](){

//        ui->progressBar->show();

//        QByteArray ba = m_updateProcess->readAll();
//        ui->textBrowser->append(QString(ba));

//        if( ba.contains("Notify:Update Complete!") ){
//            //! update mrh
//            slot_updateMRH();
//        }

//        if( ba.contains("Error") ){
//            slotHandleError();
//            delete m_updateProcess;
//            m_updateProcess = NULL;
//        }

//        //! percent
//        QRegExp rx("(\\d+)");
//        QString _str = QString( ba );
//        QStringList list;
//        int pos = 0;

//        while ((pos = rx.indexIn(_str, pos)) != -1) {
//            list << rx.cap(1);
//            pos += rx.matchedLength();
//        }
//        foreach (QString item, list) {
//            ui->progressBar->setValue( item.toInt() );
//        }
//    });

//    QString updateMRQProgram = qApp->applicationDirPath() + MRQ_UPDATE_EXE;
//    QStringList arguments;
//    arguments << (sPath.left(sPath.lastIndexOf("/")) + MRQ_UPDATE) << m_addr << recvID;
//    m_updateProcess->start(updateMRQProgram, arguments);
//    m_updateProcess->waitForFinished(-1);

}

void Widget::slot_startMRQUpdate(int)
{
//    QtConcurrent::run(this,&Widget::callback);
    MThead *mthread = new MThead;
    connect(mthread,SIGNAL(resultReady(QString)),this,SLOT(slotReadMRQResult(QString)));

    QString updateMRQProgram = qApp->applicationDirPath() + MRQ_UPDATE_EXE;
    QStringList arguments;
    arguments << (sPath.left(sPath.lastIndexOf("/")) + MRQ_UPDATE) << m_addr << recvID;

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
//    QMessageBox msgBox();
//    msgBox.setText(tr("\n\tUpdate Success\t\t \n\n\tReboot?\t \n"));
//    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
//    if(msgBox.exec() == QMessageBox::Ok){
//        //! reboot
//        if(m_pPlugin->isRebootable()){
//            mrgSystemRunCmd(m_vi, (char *)"reboot", 0);
//        }
//        this->close();
//    }
    if( QMessageBox::information(this,tr("reboot"),tr("Reboot will work")) == QMessageBox::Ok ){
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
