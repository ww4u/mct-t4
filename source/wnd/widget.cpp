#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include "xthread.h"
#include <QProcess>


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
    connect(this, SIGNAL(AppendText(QString)),this,SLOT(SlotAppendText(QString)));
    connect(this, SIGNAL(sigReboot()),this, SLOT(slotReboot()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::attatchRoboConfig(RoboConfig *r)
{
    m_roboConfig = r;
    m_addr = m_roboConfig->currentXPlugin()->addr();
    qDebug() << "update" << m_addr;
    recvID = m_roboConfig->currentXPlugin()->DevId();
}

void Widget::on_buttonBox_clicked(QAbstractButton *button)
{

    if((QPushButton*)(button) == ui->buttonBox->button(QDialogButtonBox::Ok)){
        //m_roboConfig->currentXPlugin()->emit_setting_changed( XPage::e_setting_opened, false );
        button->setEnabled(false);
    }else {
        //! cancle process
        this->close();
        return;
    }

    QString undoExePath = qApp->applicationDirPath() + UNDOEXE;
    QStringList arguments;
    arguments << "-x" << "-p" << sPath;
    QProcess *myProcess = new QProcess(this);
    myProcess->start(undoExePath, arguments);
    connect(myProcess, SIGNAL(finished(int)),this,SLOT(slot_startMRQUpdate(int)));
}

void Widget::on_toolButton_clicked()
{
    sPath = QFileDialog::getOpenFileName(this,
          tr("Open File"), NULL, tr("(*.p)"));
    ui->lineEdit->setText(sPath);
}
#include <QtConcurrent>

void Widget::slot_updateMRH(int i, QProcess::ExitStatus e)
{
    //! mrh
    Append("Notify: MRH Updating...\r\n");
    QFuture<void> future = QtConcurrent::run([=]() {
        QFile mrhFile(sPath.left(sPath.lastIndexOf("/")) + MRH_UPDATE);
        if(!mrhFile.open(QIODevice::ReadOnly)){
            Append("Error: File Error\r\n");
            return;
        }
        QByteArray ba = mrhFile.readAll();
        int ret = mrgStorageWriteFile(m_roboConfig->currentXPlugin()->deviceVi(), 0, (char *)"/media/usb0/",
                                  (char *)MRH_UPDATE, (unsigned char*)(ba.data()), ba.size());
        if(ret!=0){
            Append("Error: MRH Update Fail\r\n");
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
            return;
        }
        ret = mrgSysUpdateFileStart(m_roboConfig->currentXPlugin()->deviceVi(), (char *)MRH_UPDATE);
        if(ret !=0 ){
            Append("Error: MRH Update Start Fail\r\n");
            return;
        }
        Append("Notify: System Update end\r\n");
        QString strCmd = "rm -rf /media/usb0/" + QString(MRH_UPDATE);
        mrgSystemRunCmd(m_roboConfig->currentXPlugin()->deviceVi(), strCmd.toLocal8Bit().data(), 1);

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

void Widget::slot_startMRQUpdate(int)
{
    //! mrq
    QString updateExe = qApp->applicationDirPath() + MRQ_UPDATE_EXE;
    QProcess *updateProcess = new QProcess(this);

    connect(updateProcess, &QProcess::readyRead,this,[=](){
        this->ui->textBrowser->append(updateProcess->readAll());
    });
    connect(updateProcess, SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(slot_updateMRH(int, QProcess::ExitStatus)));
    QStringList arguments;
    arguments << (sPath.left(sPath.lastIndexOf("/")) + MRQ_UPDATE) << m_addr << recvID;
    updateProcess->start(updateExe, arguments);
}
void Widget::Append(const QString &text)
{
    emit AppendText(text);
}
void Widget::SlotAppendText(const QString &text)
{
    ui->textBrowser->append(text);
}
void Widget::slotReboot()
{
    QMessageBox msgBox;
    msgBox.setText(tr("\n\tUpdate Success\t\t \n\n\tReboot?\t \n"));
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    if(msgBox.exec() == QMessageBox::Ok){
        //! reboot
        if(m_roboConfig->currentXPlugin()->isRebootable()){
            mrgSystemRunCmd(m_roboConfig->currentXPlugin()->deviceVi(), (char *)"reboot", 0);
        }
        this->close();
    }
}
void Widget::reboot()
{
    emit sigReboot();
}
