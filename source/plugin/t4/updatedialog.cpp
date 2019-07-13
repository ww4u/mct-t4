#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QFileDialog>
#include <QDebug>
#include <QtConcurrent>
#include "../../sys/sysapi.h"
#include <QDir>
#include "../../device/assist.h"
#include <QStatusBar>
#include <QVBoxLayout>

#define MRQ_UPDATE  "/mrq.dat"
#define MRH_UPDATE  "/mrh.tar.gz"
#define MRQ_UPDATE_EXE "/MRQ_Update/MegaRobo_Update.exe"

//! file path
#define DIR_TEMP    QDir::tempPath()
#define DIR_TEMP_OUTPUT (DIR_TEMP + "/output")
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

    m_mrqEntity = NULL;
    m_mrhEntity = NULL;

    ui->desLineEdit->hide();

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),
            this,SLOT(slotLineEditTextChanged(QString)));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled( false );

    //! update thread
    pWorkThead = new MThead;
    connect( this, SIGNAL(changeTheadWorkMode(int)), pWorkThead, SLOT(switchWorkMode(int)) );
    connect( pWorkThead, SIGNAL( resultReady(int)), this, SLOT( updateUi( int ) ) );
    connect( pWorkThead, SIGNAL( resultReady(QString)), this, SLOT( updateProgress( QString ) ));

    pStatusBar = new QStatusBar(this);
}

UpdateDialog::~UpdateDialog()
{
    pWorkThead->requestInterruption();
    pWorkThead->wait();

    delete pWorkThead;
    delete ui;
}

void UpdateDialog::attatchPlugin(XPlugin *xp)
{
    m_pPlugin = xp;
    m_addr = m_pPlugin->addr();
    isAdmin = m_pPlugin->isAdmin();
}

void UpdateDialog::updateUi( int i )
{
    //! \todo ui

    QString str;

    switch (i)
    {
        case -1:
            str = tr("System Error");
            break;
        case -2:
            str = tr("Net Error");
            break;
        case -3:
            str = tr("File Invalid");
            break;
        case -4:
            str = tr("Connect Fail");
            break;
        case -5:
            str = tr("");
            break;
        case -6:
            str = tr("");
            break;
        case -7:
            str = tr("");
            break;
        case -8:
            str = tr("");
            break;
        case -9:
            str = tr("");
            break;
        case -10:
            str = tr("");
            break;
        case -11:
            str = tr("");
            break;
        case -12:
            str = tr("");
            break;
        case -13:
            str = tr("");
            break;
        case -14:
            str = tr("");
            break;
        case -15:
            str = tr("");
            break;
        case -16:
            str = tr("");
            break;
        case -18:
            str = tr("");
            break;
        case 0:
            str = tr("MRH Update Complete");
            break;
        case 1:
            str = tr("MRQ Begin Update");
            break;
        case 2:
            str = tr("MRH Begin Update");
            break;
        case 9:
            str = tr("MRQ Update Complete");
            break;
    }

    pStatusBar->showMessage( str );
}
void UpdateDialog::updateProgress( QString str )
{
    ui->progressBar->setValue( str.toInt() );
    ui->progressBar->show();
}

void UpdateDialog::on_buttonBox_clicked(QAbstractButton *button)
{

    begin_page_log();
    end_page_log();

    if((QPushButton*)(button) == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        m_pPlugin->close();

        button->setDisabled( true );

        pWorkThead->setAddr( m_addr );
        pWorkThead->attachEntity_MRQ( m_mrqEntity );
        pWorkThead->attachEntity_MRH( m_mrhEntity );
        changeTheadWorkMode(1);
        pWorkThead->start();
    }else{
        pWorkThead->requestInterruption();
        pWorkThead->wait();
    }


//    ui->labelStatus->hide();
//    ui->btnShow->show();
//    ui->textEdit->clear();
//    ui->lineEdit->setReadOnly(true);

//    if((QPushButton*)(button) == ui->buttonBox->button(QDialogButtonBox::Ok)){
//        m_pPlugin->close();

//        if(openDevice()<0){
//            button->show();
//            ui->labelStatus->setText( tr("Open Device Fail") );
//            ui->labelStatus->show();
//            return;
//        }
//        else
//        {}

//        button->setDisabled( true );

//        ui->lineEdit->setEnabled( false );
//        ui->toolButton->setEnabled( false );

//    }else {
//        this->close();
//        return;
//    }

//    int ret = 0;

//    do{

//        if( m_mrqEntity == NULL || m_mrhEntity == NULL ){
//            ret = -1;
//            break;
//        }

//        QDir dir;
//        if( !dir.mkpath( QDir::tempPath() + "/output" )){
//            ret = -1;
//            break;
//        }
//        QFile f( QDir::tempPath() + "/output/temp.dat" );
//        if( f.open(QIODevice::WriteOnly) ){

//        }else{
//            ret = -1;
//            break;
//        }

//        f.write( m_mrqEntity->mPayload );
//        f.close();

//    }while(0);

//    //! \todo
//    if( ret !=0 ){
//        ui->textEdit->append( tr( "Error: Invalid File" ) );
//        return;
//    }else{}

//    //! version compare
//    //! \todo remote from the plugin
//    ret = versionComparison( m_desc, mRemoteVerionStream );
//    if( ret == 1 ){
//        slot_startMRQUpdate();
//    }else {
//        //! version = ...
//        ui->textEdit->append( tr( "Notify: Version Is Same, No Need To Update." ) );
//    }
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
        pStatusBar->showMessage( tr("Invalid File") );
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


//! Class MThead
MThead::MThead(QObject *parent):
    QThread(parent),
    pProc(NULL),
    iFlag(0),
    pEntity_MRQ(NULL),
    PEntity_MRH(NULL),
    iEndFlag(0)
{

}

int MThead::generateDevUpdateFile()
{
    Q_ASSERT( pEntity_MRQ != NULL );

    QDir dir;
    if( !dir.mkpath( QString(DIR_TEMP_OUTPUT) ) )
    {
        return -1;
    }

    QFile f( MRQ_FILE );
    if( f.open(QIODevice::WriteOnly) ){

    }else{
        return -1;
    }

    f.write( pEntity_MRQ->mPayload );
    f.close();

    return 0;
}

int MThead::updateDevice()
{logDbg();
    //! \todo err code
    if( generateDevUpdateFile() != 0 ){logDbg();
        return -1;
    }

    if( pProc != NULL ){
        delete pProc;
        pProc = NULL;
    }
    pProc = new QProcess;

    QStringList argument;

    argument << MRQ_FILE << m_addr <<QString::number(1);
    connect( pProc,
             SIGNAL(readyRead()),
             this,
             SLOT(parseStandOutput())
            );

    pProc->start( (qApp->applicationDirPath() + MRQ_UPDATE_EXE), argument );
    pProc->waitForStarted(-1);

    do{
        localSleep( 100 );
        //! process complted
        if ( pProc->waitForFinished(0) )
        { break; }
        else
        {}
    }while( true );
    logDbg();

    return 0;
}

int MThead::updateController()
{
    int ret = 0;
    int vi;

        vi = mrgOpenGateWay(1, m_addr.toLocal8Bit().data(), 2000);
        if( vi < 0 ){
            ret = -2;
        }

        do{
            if( PEntity_MRH->mPayload.isEmpty() ){
                ret = -3;
                break;
            }

            ret = mrgStorageWriteFile(vi, 0, (char *)"/media/usb0/",
                                      (char *)MRH_UPDATE,
                                      (unsigned char*)(PEntity_MRH->mPayload.data()),
                                      PEntity_MRH->mPayload.size());
            if(ret!=0){
                ret = -2;
                break;
            }

            emit resultReady( QString::number( 60 ) );

            QString strCmd = "tar xzvf /media/usb0/mrh.tar.gz -C /media/usb0/";
            ret = mrgSystemRunCmd(vi, strCmd.toLocal8Bit().data(), 0);
            if( ret !=0 ){
                ret = -3;
                break;
            }

            emit resultReady( QString::number( 70 ) );

            strCmd = "cp /media/usb0/update.sh /home/megarobo/MCT/MRX-T4/update.sh";
            ret = mrgSystemRunCmd(vi, strCmd.toLocal8Bit().data(), 0);
            if( ret !=0 ){
                ret = -3;
                break;
            }

            strCmd = "sh /home/megarobo/MCT/MRX-T4/update.sh";
            ret = mrgSystemRunCmd(vi, strCmd.toLocal8Bit().data(), 0);
            logDbg() << ret;
            if(ret !=0){
                ret = -3;
                break;
            }

            emit resultReady( QString::number( 80 ) );

            ret = mrgSysUpdateFileStart(vi, (char *)"mrh.dat");
            if(ret !=0 ){
                ret = -1;
                break;
            }
            emit resultReady( QString::number( 100 ) );

        }while(0);

        QString str = "rm -rf /media/usb0/*";
        mrgSystemRunCmd(vi, str.toLocal8Bit().data(), 0);

        mrgSystemRunCmd( vi, (char *)"reboot", 0 );

    mrgCloseGateWay(vi);

    return ret;
}

void MThead::run()
{logDbg();
    //! \todo
    try{
        while( iFlag )
        {logDbg();
            iProgress = 0;

            //! mrq

            emit resultReady(1);

            updateDevice();

            if( iEndFlag == 1 ){
                emit resultReady(2);

                int ret = updateController();

                emit resultReady( ret );

                iEndFlag = 0;
            }
            iFlag = 0;

            localSleep(500);
        }
    }
    catch( QException &e )
    {
        //! \todo free
        pProc->terminate();
    }
    delete pProc;
}
void MThead::slotReadyRead()
{
    QByteArray ba = pProc->readAll();
    qDebug() << ba;
    emit resultReady(QString(ba));
}

void MThead::switchWorkMode(int mode)
{
    iFlag = mode;
}

void MThead::parseStandOutput()
{
    iProgress += 10;
    QByteArray ba = pProc->readAll();
    //! \todo err code
    int ret = 99;
    if( ba.contains("Error:Cannot establish communication!") ){
        ret = -5;
    }else if( ba.contains( "Error:The BOOT version is very old" ) ){
        ret = -6;
    }else if( ba.contains( "Error:The update file is invalid" ) ){
        ret = -7;
    }else if( ba.contains( "Error:Cannot get the BOOT version" ) ){
        ret = -8;
    }else if( ba.contains( "Error:Reload failed" ) ){
        ret = -9;
    }else if( ba.contains( "Error:Cannot get the software version" ) ){
        ret = -10;
    }else if( ba.contains( "Error:ARM file has validation error" ) ){
        ret = -11;
    }else if( ba.contains( "Error:BOOT data download failed" ) ){
        ret = -12;
    }else if( ba.contains( "Error:Does not respond" ) ){
        ret = -13;
    }else if( ba.contains( "Error:FPGA1 file has validation" ) ){
        ret = -14;
    }else if( ba.contains( "Error:Erase the FLASH failed" ) ){
        ret = -15;
    }else if( ba.contains( "FPGA2 file has validation error" ) ){
        ret = -16;
    }else if( ba.contains( "Notify:Open MRH-T Failed" ) ){
        ret = -18;
    }else if( ba.contains( "Notify:Update Complete" ) ){
        iEndFlag = 1;
        iProgress = 50;
        ret = 9;
    }
    qDebug() << ba;
    emit resultReady(ret);
    emit resultReady( QString::number(iProgress) );
    //! percent
//    QRegExp rx("(\\d+)");
//    QString _str = QString( ba );
//    QStringList list;
//    int pos = 0;

//    while ((pos = rx.indexIn(_str, pos)) != -1) {
//        list << rx.cap(1);
//        pos += rx.matchedLength();
//    }
}

//! Class Entity
Entity::Entity(QObject *parent) : QObject(parent)
{

}


