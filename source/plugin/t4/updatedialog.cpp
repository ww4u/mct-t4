#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QFileDialog>
#include <QDebug>
#include <QtConcurrent>
#include "../../sys/sysapi.h"
#include <QDir>
#include "../../device/assist.h"

#define MRQ_UPDATE  "/mrq.dat"
#define MRH_UPDATE  "/mrh.tar.gz"
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

    return res;
}

UpdateDialog::UpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->progressBar->hide();
    ui->btnShow->hide();
    ui->textBrowser->hide();

    m_mrqEntity = NULL;
    m_mrhEntity = NULL;

    ui->desLineEdit->hide();

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),
            this,SLOT(slotLineEditTextChanged(QString)));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled( false );

    m_threaad = new MThead;
    m_threaad->setId( 0 );
    connect(m_threaad,SIGNAL(resultReady(QString)),
            this,SLOT(slotReadMRQResult(QString)));

    m_mrhThread = new MThead;
    m_mrhThread->setId( 1 );
    connect(m_mrhThread, SIGNAL(resultReady(int)),
            this,SLOT(slotGetRunState(int)));
}

UpdateDialog::~UpdateDialog()
{
    m_threaad->requestInterruption();
    m_threaad->wait();

    m_mrhThread->requestInterruption();
    m_mrhThread->wait();

    delete m_threaad;
    delete m_mrhThread;

    delete ui;
}

void UpdateDialog::attatchPlugin(XPlugin *xp)
{
    m_pPlugin = xp;
    m_addr = m_pPlugin->addr();
    isAdmin = m_pPlugin->isAdmin();
}

void UpdateDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    begin_page_log();
    end_page_log();

    ui->labelStatus->hide();
    ui->btnShow->show();
    ui->textBrowser->clear();
    ui->lineEdit->setReadOnly(true);

    if((QPushButton*)(button) == ui->buttonBox->button(QDialogButtonBox::Ok)){
        m_pPlugin->close();

        if(openDevice()<0){
            button->show();
            ui->labelStatus->setText( tr("Open Device Fail") );
            ui->labelStatus->show();
            return;
        }
        else
        {}

        button->setDisabled( true );

        ui->lineEdit->setEnabled( false );
        ui->toolButton->setEnabled( false );

    }else {
        this->close();
        return;
    }

    int ret = 0;

    do{

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

    }while(0);

    //! \todo
    if( ret !=0 ){
        ui->textBrowser->append( tr( "Error: Invalid File" ) );
        return;
    }else{}

    //! version compare
    //! \todo remote from the plugin
    ret = versionComparison( m_desc, mRemoteVerionStream );
    if( ret == 1 ){
        slot_startMRQUpdate();
    }else {
        //! version = ...
        ui->textBrowser->append( tr( "Notify: Version Is Same, No Need To Update." ) );
    }
}

//! return value:0 =; 1: !=;
int UpdateDialog::versionComparison( const QString &inVersion,
                               const QByteArray &remoteVerStream )
{
    //! MRX-T4_R0.0.0.1
    //! MRX-T4_M0.0.0.1

    int ret = 0;
    QString version, mrh, mrq, builTime;

    QXmlStreamReader reader( remoteVerStream );
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
    //! \todo check version
    QStringList inList = inVersion.mid(8).split(".");
    QStringList tList = version.mid( 8 ).split(".");
    for( int i = 0; i < inList.size(); i++ ){
        if( inList.at( i ) != tList.at( i ) )
        return 1;
    }
    return 0;
}

void UpdateDialog::on_toolButton_clicked()
{
    begin_page_log();
    end_page_log();

    sPath = QFileDialog::getOpenFileName(this,
          tr("Open File"), NULL, tr("(*.upd)"));
    ui->lineEdit->setText(sPath);
}

// return: -1: system error ; -2: net; -3:invalid file;
void UpdateDialog::showError(const QString &text)
{
    ui->textBrowser->append(text);
    if( text.contains("Error") ){
        ui->labelStatus->setText(tr("Update Error"));
        ui->labelStatus->show();
    }
}

void UpdateDialog::slot_updateMRH()
{
    begin_page_log();
    end_page_log();

    ui->progressBar->setMaximum(0);
    ui->textBrowser->append( "Notify: MRH Updating...\n" );

    m_mrhThread->setPayload( m_mrhEntity->mPayload );
    m_mrhThread->setAddr(m_addr);
    m_mrhThread->start();
}

void UpdateDialog::slot_startMRQUpdate()
{
    begin_page_log();
    end_page_log();

    QString updateMRQProgram = qApp->applicationDirPath()
                                + MRQ_UPDATE_EXE;

    QStringList arguments;
    arguments << MRQ_FILE << m_addr << recvID;

    m_threaad->setExeCmd(updateMRQProgram);
    m_threaad->setArguments(arguments);
    m_threaad->start();
}

void UpdateDialog::slotReadMRQResult(QString text)
{
    begin_page_log();
    end_page_log();

    ui->progressBar->show();

    if( text.contains("Notify:Update Complete!") ){
        //! update mrh
        slot_updateMRH();
        ui->textBrowser->append(text);
    }

    if( text.contains("Error") ){
        ui->labelStatus->setText(tr("Update MRQ Fail"));
        ui->labelStatus->show();

        ui->textBrowser->append(text);
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

void UpdateDialog::slotGetRunState(int state)
{
    begin_page_log();
    end_page_log();

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
    //! \todo

    if( id == 0 ){
        try{
            Q_ASSERT(cmd != NULL);
            Q_ASSERT(!argument.isEmpty());
            //            QProcess::execute( cmd, argument );
            //            emit resultReady(QString("Notify:Update Complete!"));
            m_process = new QProcess;

            connect(m_process,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
            m_process->start(cmd,argument);
            if(!m_process->waitForStarted()){
                emit resultReady(QString("Error: Start Exe Fail"));
                return;
            }
            logDbg();
            //! \todo add tmo
            do
            {
                localSleep( 100 );
                //! process complted
                if ( m_process->waitForFinished(0) )
                { break; }
                else
                {}
                //            }while( m_process->state() != QProcess::NotRunning );
            }while( true );
            logDbg();
        }
        catch(QException e){
            m_process->terminate();
        }
        delete m_process;

    }else if( id == 1 ){
        int ret = 0;
        int vi;
        try{

            vi = mrgOpenGateWay(1, m_addr.toLocal8Bit().data(), 2000);
            if( vi < 0 ){
                ret = -2;
            }

            do{
                if( mPayLoad.isEmpty() ){
                    ret = -3;
                    break;
                }

                ret = mrgStorageWriteFile(vi, 0, (char *)"/media/usb0/",
                                          (char *)MRH_UPDATE,
                                          (unsigned char*)(mPayLoad.data()),
                                          mPayLoad.size());
                if(ret!=0){
                    ret = -2;
                    break;
                }

                QString strCmd = "sh /home/megarobo/MCT/MRX-T4/update.sh";
                ret = mrgSystemRunCmd(vi, strCmd.toLocal8Bit().data(), 0);
                logDbg() << ret;
                if(ret !=0){
                    ret = -3;
                    break;
                }

                ret = mrgSysUpdateFileStart(vi, (char *)"mrh.dat");
                if(ret !=0 ){
                    ret = -1;
                    break;
                }

            }while(0);

            QString str = "rm -rf /media/usb0/*";
            mrgSystemRunCmd(vi, str.toLocal8Bit().data(), 0);

            mrgSystemRunCmd( vi, (char *)"reboot", 0 );

            resultReady(ret);
        }catch(QException &e){
            logDbg();
        }

        mrgCloseGateWay(vi);
    }
}
void MThead::slotReadyRead()
{
    QByteArray ba = m_process->readAll();
    qDebug() << ba;
    emit resultReady(QString(ba));
}

void UpdateDialog::on_btnShow_clicked()
{
    ui->textBrowser->setVisible( !ui->btnShow->isChecked() );
    if( ui->btnShow->isChecked() )
    { ui->btnShow->setText( tr("Show detail") ); }
    else
    { ui->btnShow->setText( tr("Hide detail") ); }
}

void UpdateDialog::slotLineEditTextChanged(QString s)
{
    QFile f(s);
    if( f.open(QIODevice::ReadOnly) ){

    }else{return;}

    QByteArray ba = f.readAll();
    if( ba.isEmpty()){
        return;
    }

    if( parseUpdateFile( ba ) != 0){
        ui->labelStatus->setText( tr("Invalid File") );
    }else{
        ui->desLineEdit->setText( m_desc );
        ui->desLineEdit->show();
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(s.length()>0);
    }
}

void UpdateDialog::on_lineEdit_textChanged(const QString &arg1)
{
    ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( arg1.length() );
}

int UpdateDialog::openDevice()
{
    begin_page_log();
    end_page_log();

    int ret = 0;
    int vi = -1;
    do{
        //! device handle
        vi = mrgOpenGateWay( 1, m_addr.toLocal8Bit().data(), 2000);
        if( vi < 0){
            ret = -1;
            break;
        }

        int robotNames[128] = {0};
        ret = mrgGetRobotName(vi, robotNames);
        if(ret <=0){
            sysInfo("Get Robot Name Fail", 1);
            ret = -1;
            break;
        }
        m_robotID = robotNames[0];

        int deviceNames[128] = {0};
        //ret = mrgGetRobotDevice(m_vi, m_robotID, deviceNames);
        recvID = QString::number(1);

        //! info
        ret = loadRemoteInfo( vi );
        if ( ret != 0 )
        { break; }

    }while(0);
    if ( vi > 0 ){
        mrgCloseGateWay( vi );
    }

    return ret;
}

int UpdateDialog::loadRemoteInfo( int vi )
{
    QByteArray ary;
    ary.reserve( 1024 * 1024 );

    int ret = 0;

    //! read the history from remote and show
    ret = mrgStorageReadFile( vi, 0,
                        (QString(mct_path) + "/" + "MRX-T4").toLatin1().data(),
                        "update.xml",
                        (quint8*)ary.data() );
    if( ret  == 0 ){
        return 1;
    }
    ary.resize( ret );

    mRemoteVerionStream = ary;

    return 0;
}

int UpdateDialog::parseUpdateFile(QByteArray &in)
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


