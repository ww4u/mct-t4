#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QtConcurrent>


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

    connect(this, SIGNAL(AppendText(QString)),this,SLOT(SlotAppendText(QString)));
    connect(this, SIGNAL(sigReboot()),this, SLOT(slotReboot()));

    connect(this, SIGNAL(sigProgress(int)), ui->progressBar, SLOT(setValue(int)));
    connect(this, SIGNAL(sigComplete()), this, SLOT(slot_updateMRH()));
    connect(this, SIGNAL(sigError(QString)),this, SLOT(slotHandleError()));
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
    QProcess *myProcess = new QProcess(this);
    m_undoProcess = myProcess;
    m_undoProcess->start(undoExePath, arguments);
    if( m_undoProcess->waitForFinished(1000) ){
        QByteArray st = m_undoProcess->readAllStandardOutput();
        if(QString(st).contains("Success")){
            slot_startMRQUpdate(0);
            delete m_undoProcess;
            m_undoProcess = NULL;
            return;
        }
    }
    slotHandleError();
    delete m_undoProcess;
    m_undoProcess = NULL;
}

void Widget::on_toolButton_clicked()
{
    sPath = QFileDialog::getOpenFileName(this,
          tr("Open File"), NULL, tr("(*.upd)"));
    ui->lineEdit->setText(sPath);
}

void Widget::slot_updateMRH()
{
    //! mrh
    ui->progressBar->setMaximum(0);
    Append("Notify: MRH Updating...\n");
    QFuture<void> future = QtConcurrent::run([=]() {
        QFile mrhFile(sPath.left(sPath.lastIndexOf("/")) + MRH_UPDATE);
        if(!mrhFile.open(QIODevice::ReadOnly)){
            Append("Error: File Error\n");
            return;
        }
        QByteArray ba = mrhFile.readAll();
        int ret = mrgStorageWriteFile(m_vi, 0, (char *)"/media/usb0/",
                                  (char *)MRH_UPDATE, (unsigned char*)(ba.data()), ba.size());
        if(ret!=0){
            Append("Error: MRH Update Fail\n");
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
            return;
        }
        ret = mrgSysUpdateFileStart(m_vi, (char *)MRH_UPDATE);
        if(ret !=0 ){
            Append("Error: MRH Update Start Fail\n");
            return;
        }
        Append("Notify: System Update end\n");
        QString strCmd = "rm -rf /media/usb0/" + QString(MRH_UPDATE);
        mrgSystemRunCmd(m_vi, strCmd.toLocal8Bit().data(), 1);

        reboot();
      });
}
void Widget::slot_undo_finished(int i, QProcess::ExitStatus e)
{

}
void Widget::slot_updateMRH_finish(int,QProcess::ExitStatus)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
static QStringList pickUpOutput( QString &str)
{
    QRegExp rx("(\\d+)");
    QString _str = str;
    QStringList list;
    int pos = 0;

    while ((pos = rx.indexIn(_str, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }
    return list;
}
void Widget::callback()
{
    m_updateProcess = new QProcess;
//    connect(m_updateProcess,SIGNAL(finished(int,QProcess::ExitStatus)),m_updateProcess,SLOT(deleteLater()));
    connect(m_updateProcess,&QProcess::readyRead,this,[=](){

        ui->progressBar->show();

        QByteArray ba = m_updateProcess->readAll();
        ui->textBrowser->append(QString(ba));

        if( ba.contains("Notify:Update Complete!") ){
            //! update mrh
            slot_updateMRH();
        }

        if( ba.contains("Error") ){
            slotHandleError();
            delete m_updateProcess;
            m_updateProcess = NULL;
        }

        //! percent
        QRegExp rx("(\\d+)");
        QString _str = QString( ba );
        QStringList list;
        int pos = 0;

        while ((pos = rx.indexIn(_str, pos)) != -1) {
            list << rx.cap(1);
            pos += rx.matchedLength();
        }
        foreach (QString item, list) {
            ui->progressBar->setValue( item.toInt() );
        }
    });

    QString updateMRQProgram = qApp->applicationDirPath() + MRQ_UPDATE_EXE;
    QStringList arguments;
    arguments << (sPath.left(sPath.lastIndexOf("/")) + MRQ_UPDATE) << m_addr << recvID;
    m_updateProcess->start(updateMRQProgram, arguments);
    m_updateProcess->waitForFinished(-1);

}

void Widget::slot_startMRQUpdate(int)
{
    QtConcurrent::run(this,&Widget::callback);
}
void Widget::Append(const QString &text)
{
    emit AppendText(text);
}
void Widget::SlotAppendText(const QString &text)
{
    ui->textBrowser->append(text);
    if( text.contains("Error") ){
        ui->labelStatus->setText(tr("Update Error"));
        ui->labelStatus->show();
    }
}
void Widget::slotReboot()
{
    QMessageBox msgBox;
    msgBox.setText(tr("\n\tUpdate Success\t\t \n\n\tReboot?\t \n"));
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    if(msgBox.exec() == QMessageBox::Ok){
        //! reboot
        if(m_pPlugin->isRebootable()){
            mrgSystemRunCmd(m_vi, (char *)"reboot", 0);
        }
        this->close();
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
void Widget::slotHandleError()
{
    ui->labelStatus->setText( tr( "Update Fail" ) );
    ui->labelStatus->show();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
