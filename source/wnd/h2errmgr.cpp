#include "h2errmgr.h"
#include "ui_h2errmgr.h"

H2ErrMgr::H2ErrMgr(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2ErrMgr)
{
    ui->setupUi(this);
    m_errorFileInfo = "";

    setFocusName( "Error_management" );

    connect(&mErrManager, &ErrMgrModel::dataChanged,
            [=](){emit signalModelDataChanged(true);} );


    //! 建立错误响应通信和显示对应表
    m_mapResponse.insert( "A", 1 );
    m_mapResponse.insert( "B", 2 );
    m_mapResponse.insert( "C", 3 );
    m_mapResponse.insert( "D", 4 );
    m_mapResponse.insert( "E", 5 );
    m_mapResponse.insert( "F", 6 );
    m_mapResponse.insert( "G", 7 );

    //! 创建表格代理
    m_pCheckDelegate = new checkDelegate( shape_check, this );
    m_pRadioDelegate = new checkDelegate( shape_radio, this );
    m_pReactionCombox = new comboxDelegate( 1, this );

    //! 错误响应设置过滤
//    QStringList errActions;
//    for (QMap<int, QString>::iterator itMap=m_mapResponse.begin();
//         itMap != m_mapResponse.end();
//         ++itMap )
//    {
//        errActions << itMap.value();
//    }
//    m_pReactionCombox->setItems( errActions );

    //!

}

H2ErrMgr::~H2ErrMgr()
{
    delete ui;
}

int H2ErrMgr::readDeviceConfig()
{
    ////////////////////////
//    return 0;

    int isOk = 0;
    for(int i=0; i<ui->tvErr->model()->rowCount(); i++)
    {
        int code = mErrManager.items()->at(i)->mNr;;
        char buffer[4096] = "";
        int ret=  mrgErrorCodeConfigUpload(mViHandle, code, buffer, sizeof(buffer));
        qDebug() << "ErrorCodeUpload" << code << QString("%1").arg(buffer);
        if(ret < 0){
            sysError("mrgErrorCodeConfigUpload", code);
            isOk = -1;
            continue;
        }

        QStringList lst = QString("%1").arg(buffer).split(",", QString::SkipEmptyParts);
        qDebug() << code << ":" << lst;

#if 0
        int code            = mErrManager.items()->at(i)->mNr;
        QString errorText   = mErrManager.items()->at(i)->mErr;
        int type            = mErrManager.items()->at(i)->mEventType;

        str                 = mErrManager.items()->at(i)->mAction;
        int response        = m_mapResponse[str];

        bl                  = mErrManager.items()->at(i)->mbOutputAble;
        int outputAble      = bl ? 1 : 0 ;

        bl                  = mErrManager.items()->at(i)->mbSaveDiagnosis;
        int diagnose        = bl ? 1 : 0 ;

        int enable = 1; //默认使能,界面上没有对应的列
#endif


    }

    return isOk;
}

int H2ErrMgr::writeDeviceConfig()
{
    ////////////////////////
//    return 0;

    int isOk = 0;
    int ret = -1;
    bool bl = false;
    QString str;

    for(int i=0; i<ui->tvErr->model()->rowCount(); i++)
    {
        int code            = mErrManager.items()->at(i)->mNr;
        QString errorText   = mErrManager.items()->at(i)->mErr;
        int type            = mErrManager.items()->at(i)->mEventType;

        str                 = mErrManager.items()->at(i)->mAction;
        int response        = m_mapResponse[str];

        bl                  = mErrManager.items()->at(i)->mbOutputAble;
        int outputAble      = bl ? 1 : 0 ;

        bl                  = mErrManager.items()->at(i)->mbSaveDiagnosis;
        int diagnose        = bl ? 1 : 0 ;

        int enable = 1; //默认使能,界面上没有对应的列

        ret = mrgErrorCodeConfigDownload(mViHandle, code, type, diagnose, response, enable);
        qDebug() << "ErrorCodeDownload:" << code << type << diagnose << response << enable << "ret:" << ret;
        if(ret < 0){
            sysError("mrgErrorCodeConfigDownload", code);
            isOk = -1;
            continue;
        }
    }

    return isOk;
}

int H2ErrMgr::loadConfig()
{
    QString fileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".xml";
    QFile file(fileName);
    if( !file.exists() )
        fileName = QApplication::applicationDirPath() + "/dataset/errmgr_default.xml";

    //! load event from xml
    int ret = mErrManager.load( fileName );

    return ret;
}

int H2ErrMgr::saveConfig()
{
    //! save event to xml
    QString fileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".xml";
    int ret = mErrManager.save( fileName );
    return ret;
}

void H2ErrMgr::updateShow()
{
    ui->tvErr->setModel( &mErrManager );

    ui->tvErr->setItemDelegateForColumn( 2, m_pRadioDelegate );
    ui->tvErr->setItemDelegateForColumn( 3, m_pRadioDelegate );
    ui->tvErr->setItemDelegateForColumn( 4, m_pRadioDelegate );

    ui->tvErr->setItemDelegateForColumn( 5, m_pReactionCombox );

    ui->tvErr->setItemDelegateForColumn( 6, m_pCheckDelegate );
    ui->tvErr->setItemDelegateForColumn( 7, m_pCheckDelegate );

}

void H2ErrMgr::translateUI()
{
    ui->retranslateUi(this);
}

QString H2ErrMgr::readFile(QString fileName)
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

int H2ErrMgr::writeFile(QString fileName, QString text)
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
