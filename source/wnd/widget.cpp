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
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::attatchRoboConfig(RoboConfig *r)
{
    m_roboConfig = r;
    m_addr = m_roboConfig->currentXPlugin()->addr();
    recvID = m_roboConfig->currentXPlugin()->DevId();
}

void Widget::on_buttonBox_clicked(QAbstractButton *button)
{
    m_roboConfig->currentXPlugin()->close();

    if((QPushButton*)(button) == ui->buttonBox->button(QDialogButtonBox::Ok)){
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
void Widget::slot_finished(int i, QProcess::ExitStatus e)
{
    //! mrh
    ui->textBrowser->append(tr("Notify: MRH Updating..."));
    QFile mrhFile(sPath.left(sPath.lastIndexOf("/")) + MRH_UPDATE);
    if(!mrhFile.open(QIODevice::ReadOnly)){
        ui->textBrowser->append("Error: File Error ");
        return;
    }
    QByteArray ba = mrhFile.readAll();
    int ret = mrgStorageWriteFile(m_roboConfig->currentXPlugin()->deviceVi(), 0, (char *)"/media/usb0/",
                              (char *)"mrh.dat", (unsigned char*)(ba.data()), ba.size());
    if(ret!=0){
        ui->textBrowser->append("Error: MRH Update Fail ");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        return;
    }
    ret = mrgSysUpdateFileStart(m_roboConfig->currentXPlugin()->deviceVi(), (char *)"mrh.dat");
    if(ret !=0 ){
        ui->textBrowser->append("Error: MRH Update Start Fail ");
        return;
    }
    ui->textBrowser->append("Notify: System Update end ");
    mrgSystemRunCmd(m_roboConfig->currentXPlugin()->deviceVi(), (char *)"rm -rf /media/usb0/*", 1);
    //!

    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText(tr("\n\tUpdate Success\t\t \n\n\tReboot?\t \n"));
    msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    if(msgBox->exec() == QMessageBox::Ok){
        //! reboot
        if(m_roboConfig->currentXPlugin()->isRebootable()){
            mrgSystemRunCmd(m_roboConfig->currentXPlugin()->deviceVi(), (char *)"reboot", 0);
        }
    }
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
    connect(updateProcess, SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(slot_finished(int, QProcess::ExitStatus)));
    QStringList arguments;
    arguments << (sPath.left(sPath.lastIndexOf("/")) + MRQ_UPDATE) << m_addr << recvID;
    updateProcess->start(updateExe, arguments);
}
