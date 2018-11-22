
#include "h2action.h"
#include "ui_h2action.h"

H2Action::H2Action(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2Action)
{
    ui->setupUi(this);

    setName( "Record_table" );

    m_strLocalFileName = "";
    m_strDeviceFileName = "MCT_motion.mrp";
    m_fileContext = "";

    m_pDelegate = new comboxDelegate(this);
    QStringList prxs;
    prxs << tr("PA") << tr("PRN") << tr("PRA");
    m_pDelegate->setItems( prxs );

}

H2Action::~H2Action()
{
    delete ui;
}


int H2Action::readDeviceConfig()
{
    int ret = -1;
    m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".mrp";

    int len = 4096 * 1024;
    char *pData = (char *)malloc(len);
    memset(pData, 0, len);
    ret = mrgStorageMotionFileContextRead(mViHandle, m_strDeviceFileName.toLatin1().data(), pData, len);
    if(ret > 0)
    {
        m_fileContext = QString("%1").arg(pData);//保存到类中
        writeFile(m_strLocalFileName, m_fileContext); //保存到本地文件
        m_actionModel.input(m_strLocalFileName); //保存到action

        qDebug() << "mrgStorageMotionFileContextRead" << ret;
        ret = 0;
    }else{
        qDebug() << "mrgStorageMotionFileContextRead error" << ret;
        ret = -1;
    }
    free(pData);
    return ret;
}

int H2Action::writeDeviceConfig()
{
    m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".mrp";
    qDebug() << "mrgStorageMotionFileSave:"
             << mrgStorageMotionFileSave(mViHandle,
                                         m_strLocalFileName.toLatin1().data(),
                                         m_strDeviceFileName.toLatin1().data());

    return 0;
}

int H2Action::loadConfig()
{
    m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".mrp";
    QFile file(m_strLocalFileName);
    //如果不存在配置文件就用公共的默认的配置文件
    if( !file.exists() )
        m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/action_default.mrp";

    //! load action from csv
    int ret = m_actionModel.input(m_strLocalFileName);//保存到action
    m_fileContext = readFile(m_strLocalFileName);//保存到类中

    return ret;
}

int H2Action::saveConfig()
{
    //! save action to csv
    m_strLocalFileName = QApplication::applicationDirPath() + "/dataset/" + mProjectName + ".mrp";
    int ret = m_actionModel.output( m_strLocalFileName );//将界面数据保存到本地文件
    return ret;
}

void H2Action::updateShow()
{
    ui->tableView->setModel( &m_actionModel );
    ui->tableView->setItemDelegateForColumn( 0, m_pDelegate );
}

QString H2Action::readFile(QString fileName)
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

int H2Action::writeFile(QString fileName, QString text)
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
