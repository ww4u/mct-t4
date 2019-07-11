#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QtConcurrent>
#include "../../sys/sysapi.h"
#include <QDir>


#define MRQ_UPDATE  "/mrq.dat"
#define MRH_UPDATE  "/mrh.tar.gz"
#define UNDOEXE     "/undo.exe"
#define MRQ_UPDATE_EXE "/MRQ_Update/MegaRobo_Update.exe"

//! file path
#define DIR_TEMP    QDir::tempPath()

#define MRQ_FILE    (DIR_TEMP + "/output/temp.dat")
#define MRH_FILE    (DIR_TEMP + "/output/mrh.dat")

#define UPDATE_FILE (DIR_TEMP + "/output/update.txt")

//! ByteArray to int
static int byteArrayToInt(QByteArray arr)
{
    if (arr.size() < 4)
        return 0;

    int res = 0;

    // 小端模式
    res = arr.at(0) & 0x000000FF;
    res |= (arr.at(1) << 8) & 0x0000FF00;
    res |= (arr.at(2) << 16) & 0x00FF0000;
    res |= (arr.at(3) << 24) & 0xFF000000;

    // 大端模式
//    res = (arr.at(0) << 24) & 0xFF000000;
//    res |= (arr.at(1) << 16) & 0x00FF0000;
//    res |= arr.at(2) << 8 & 0x0000FF00;
//    res |= arr.at(3) & 0x000000FF;
    return res;
}

Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->progressBar->hide();
    ui->btnShow->hide();
    ui->textBrowser->hide();

    m_vi = 0;

    m_updateProcess = NULL;
    m_undoProcess = NULL;
    m_mrqEntity = NULL;
    m_mrhEntity = NULL;

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slotLineEditTextChanged(QString)));

    connect(this, SIGNAL(sigReboot()),this, SLOT(slotReboot()));

    watcher = new QFutureWatcher<int>;
    connect(watcher, SIGNAL(finished()),this, SLOT(slotGetRunState()));

    slotLineEditTextChanged(ui->lineEdit->text());
}

Widget::~Widget()
{
    destory();
    delete ui;
    if(m_vi>0){
        mrgCloseGateWay( m_vi);
        m_vi = 0;
    }
}

void Widget::attatchPlugin(XPlugin *xp)
{
    m_pPlugin = xp;
    m_addr = m_pPlugin->addr();
    isAdmin = m_pPlugin->isAdmin();
}

void Widget::on_buttonBox_clicked(QAbstractButton *button)
{
    begin_page_log();
    end_page_log();
    ui->labelStatus->hide();
    ui->btnShow->show();
    ui->textBrowser->clear();

    if((QPushButton*)(button) == ui->buttonBox->button(QDialogButtonBox::Ok)){
        m_pPlugin->close();

        if(openDevice()<0){
            button->show();
            ui->labelStatus->setText( tr("Open Device Fail") );
            ui->labelStatus->show();
            return;
        }
        button->setDisabled( true );
    }else {
        this->close();
        return;
    }

    int ret = 0;

    do{
        QFile qFile( sPath );
        if( qFile.open( QIODevice::ReadWrite ) ){
        }else{
            ret = -1;
            break;
        }

        QByteArray in = qFile.readAll();
        if( parseUpdateFile(in) < 0){
            ret = -1;
            break;
        }

        if( m_mrqEntity == NULL || m_mrhEntity == NULL ){
            ret = -1;
            break;
        }

        QDir dir;
        if( !dir.mkpath( QDir::tempPath() + "/output" )){
            ret = -1;
            break;
        }
        QFile f( QDir::tempPath() + "/output/temp.dat" );
        if( f.open(QIODevice::WriteOnly) ){

        }else{
            ret = -1;
            break;
        }

        f.write( m_mrqEntity->mPayload );
        f.close();
        qFile.close();

    }while(0);

    //! \todo
    if( ret !=0 ){
        ui->textBrowser->append( tr( "Error: Invalid File" ) );
        return;
    }else{}

    ui->textBrowser->append( tr("Desc:%1").arg( m_desc ) );
    ret = versionComparison(m_desc);
    if( ret == 1 ){
        slot_startMRQUpdate();
    }else {
        //! version = ...
        ui->textBrowser->append( tr( "Notify: Version Is Same.No Need To Update" ) );
    }
    closeDevice();
}

//! return value:0 =; 1: !=;
int Widget::versionComparison( QString inVersion )
{
    //! MRX-T4_R0.0.0.1
    //! MRX-T4_M0.0.0.1

    QByteArray ary;
    ary.reserve( 1024 * 1024 );

    int ret = 0;
    QString version, mrh, mrq, builTime;

    //! read the history from remote and show
    ret = mrgStorageReadFile( m_vi, 0,
                        (QString(mct_path) + "/" + "MRX-T4").toLatin1().data(),
                        "update.xml",
                        (quint8*)ary.data() );
    if( ret  == 0 ){
        return 1;
    }
    ary.resize( ret );

    QXmlStreamReader reader(ary);
    while( reader.readNextStartElement() ){
        if( reader.name() == "data" ){
            while( reader.readNextStartElement() ){
                if( reader.name() == "block" ){
                    if( reader.attributes().hasAttribute("id") ){
                        qDebug() << reader.attributes().value("id").toString();
                        while(reader.readNextStartElement()){
                            if( reader.name() == "version" ){
                                version = reader.readElementText();
                            }else if( reader.name() == "mrh" ){
                                mrh = reader.readElementText();
                            }else if( reader.name() == "mrq" ){
                                mrq = reader.readElementText();
                            }else if( reader.name() == "build_time" ){
                                builTime = reader.readElementText();
                            }else{
                                reader.skipCurrentElement();
                            }
                        }
                        break;
                    }
                }else{
                    reader.skipCurrentElement();
                }
                break;
            }
        }else{
            reader.skipCurrentElement();
        }
    }

    QStringList inList = inVersion.mid(8).split(".");
    QStringList tList = version.mid( 8 ).split(".");
    for( int i = 0; i < inList.size(); i++ ){
        if( inList.at( i ) != tList.at( i ) )
        return 1;
    }
    return 0;
}

void Widget::on_toolButton_clicked()
{
    begin_page_log();
    end_page_log();

    sPath = QFileDialog::getOpenFileName(this,
          tr("Open File"), NULL, tr("(*.upd)"));
    ui->lineEdit->setText(sPath);
}

// return: -1: system error ; -2: net; -3:invalid file;
int Widget::upgressMRH()
{
    begin_page_log();
    end_page_log();

    int ret = 0;
    //! \todo
    m_vi = mrgOpenGateWay(m_addr.toLocal8Bit().data(), 2000);
    if( m_vi < 0 ){
        m_vi = 0;
        return -2;
    }

    do{
        if( m_mrhEntity == NULL ){
            ret = -3;
            break;
        }

        QByteArray ba = m_mrhEntity->mPayload;
        ret = mrgStorageWriteFile(m_vi, 0, (char *)"/media/usb0/",
                                  (char *)MRH_UPDATE,
                                  (unsigned char*)(ba.data()),
                                  ba.size());
        if(ret!=0){
            ret = -2;
            break;
        }

//        QString strCmd = "rm -rf /media/usb0/" + QString(MRH_UPDATE);
        QString strCmd = "sh /home/megarobo/MCT/MRX-T4/update.sh";
        ret = mrgSystemRunCmd(m_vi, strCmd.toLocal8Bit().data(), 0);
        logDbg() << ret;
        if(ret !=0){
            ret = -3;
            break;
        }

        ret = mrgSysUpdateFileStart(m_vi, (char *)"mrh.dat");
        if(ret !=0 ){
            ret = -1;
            break;
        }

    }while(0);

    QString str = "rm -rf /media/usb0/*";
    mrgSystemRunCmd(m_vi, str.toLocal8Bit().data(), 0);

    if(ret!=0){
        closeDevice();
    }else{}

    return ret;
}
void Widget::showError(const QString &text)
{
    ui->textBrowser->append(text);
    if( text.contains("Error") ){
        ui->labelStatus->setText(tr("Update Error"));
        ui->labelStatus->show();
    }
}

void Widget::slot_updateMRH()
{
    begin_page_log();
    end_page_log();

    ui->progressBar->setMaximum(0);
    ui->textBrowser->append("Notify: MRH Updating...\n");

    QFuture<int> future = QtConcurrent::run(this, &Widget::upgressMRH);
    watcher->setFuture(future);
}

void Widget::slot_startMRQUpdate()
{
    begin_page_log();
    end_page_log();

    MThead *mthread = new MThead;
    connect(mthread,SIGNAL(resultReady(QString)),
            this,SLOT(slotReadMRQResult(QString)));

    QString updateMRQProgram = qApp->applicationDirPath()
                                + MRQ_UPDATE_EXE;

    QStringList arguments;
    arguments << MRQ_FILE << m_addr << recvID;

    mthread->setExeCmd(updateMRQProgram);
    mthread->setArguments(arguments);
    mthread->start();
}

void Widget::slotReadMRQResult(QString text)
{
    begin_page_log();
    end_page_log();

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

void Widget::slotReboot()
{
    begin_page_log();
    end_page_log();

    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue( 100 );
    if( msgBox_Information_ok("Information", "Please Restart Now") ){
        if(m_pPlugin->isRebootable()){
            mrgSystemRunCmd(m_vi, (char *)"reboot", 0);
        }
        this->close();
    }else{
        closeDevice();
    }
}
void Widget::reboot()
{
    emit sigReboot();
}

void Widget::destory()
{
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

void Widget::slotGetRunState()
{
    begin_page_log();
    end_page_log();

    int state = watcher->result();
    //-1: system error ; -2: net; -3:invalid file;
    QString strError;
    if( state == -1 ){
        strError = tr( "Error: System Error" );
    }else if( state == -2){
        strError = tr( "Error: Network Error" );
    }else if( state == -3 ){
        strError = tr( "Error: Data Check Fail" );
    }else if( state == 0 ){
        strError = tr( "Notify: Update Complete" );
        reboot();
        return;
    }else{}

    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
    showError( strError );
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
        emit resultReady(QString("Error: Start Exe Fail"));
        return;
    }
    m_process->waitForFinished(-1);
}

void MThead::slotReadyRead()
{
    QByteArray ba = m_process->readAll();
    qDebug() << ba;
    emit resultReady(QString(ba));
}

void Widget::on_btnShow_clicked()
{
    ui->textBrowser->setVisible( !ui->btnShow->isChecked() );
    if( ui->btnShow->isChecked() )
    { ui->btnShow->setText( tr("Show detail") ); }
    else
    { ui->btnShow->setText( tr("Hide detail") ); }
}

void Widget::slotLineEditTextChanged(QString s)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(s.length()>0);
}

int Widget::openDevice()
{
    begin_page_log();
    end_page_log();

    int ret = 0;
    do{
        m_vi = mrgOpenGateWay(m_addr.toLocal8Bit().data(), 2000);
        if( m_vi < 0){
            ret = -1;
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
    if(m_vi>0 && ret<0){
        mrgCloseGateWay(m_vi);
    }

    return ret;
}
void Widget::closeDevice()
{
    begin_page_log();
    end_page_log();

    if(m_vi >0){
        mrgCloseGateWay(m_vi);
        m_vi = 0;
    }
}

int Widget::parseUpdateFile(QByteArray &in)
{
    int iDesLen =  byteArrayToInt( in.mid( 0, 4 ) );
    m_desc = QString::fromLocal8Bit( in.mid( 4, iDesLen ) );
    int iId = byteArrayToInt( in.mid( 4+iDesLen, 4 ) );
    if( iId != Entity::PACKAGE ){
        return -1;
    }
    int iSize = byteArrayToInt( in.mid( iDesLen+8, 4 ) );
    int iCheck = byteArrayToInt( in.mid( iDesLen+12, 4 ) );
    int iFormat = byteArrayToInt( in.mid( iDesLen+16, 4 ));
    int iSections = byteArrayToInt( in.mid( iDesLen+20, 4 ));
    QByteArray ba = in.mid( iDesLen+24, iSize );
    QByteArray t = qUncompress( ba );

    for( quint32 i=0; i< iSections; i++ )
    {
        Entity *e = new Entity(this);
        e->mDescLen = byteArrayToInt( t.mid(0, 4) );
        e->mDescription = QString::fromLocal8Bit( t.mid( 4, e->mDescLen ) );
        e->mId = byteArrayToInt(t.mid( 4+e->mDescLen, 4 ));
        e->mSize = byteArrayToInt(t.mid( e->mDescLen+8, 4 ));
        e->mCheck = byteArrayToInt(t.mid( e->mDescLen+12, 4 ));
        e->mFormat = byteArrayToInt(t.mid( e->mDescLen+16, 4 ));
        e->mSections = byteArrayToInt(t.mid( e->mDescLen+20, 4 ));
        e->mPayload = t.mid( e->mDescLen+24, e->mSize );

        if( e->mId == Entity::MRQ_ENTITY ){
            m_mrqEntity = e;
        }else if( e->mId == Entity::MRH_ENTITY ){
            m_mrhEntity = e;
        }else{}

        t = t.mid( e->mDescLen+24+e->mSize );
    }

    return 0;
}

Entity::Entity(QObject *parent) : QObject(parent)
{

}
