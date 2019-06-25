#include "filemanager.h"
#include "ui_filemanager.h"
#include "../plugin/xplugin.h"
#include "storage.h"
#include "../../sys/sysapi.h"
#include <QStandardItemModel>

FileManager::FileManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManager)
{
    ui->setupUi(this);

    connect( ui->treeView, SIGNAL(clicked(const QModelIndex &)),
             this, SLOT(on_treeView_activated(const QModelIndex &)) );


    on_lineEdit_textChanged( ui->lineEdit->text() );
}

void FileManager::showEvent(QShowEvent *e)
{
    doStartWork();
    return QWidget::showEvent(e);
}

void FileManager::attachPlugin(XPlugin *p)
{
    m_pPlugin = p;
}

void FileManager::setTitle(const QString title)
{
    this->setWindowTitle(title);
}
QString FileManager::title()
{
    return this->windowTitle();
}
QString FileManager::fileName()
{
    return ui->lineEdit->text();
}
void FileManager::doStartWork()
{
    if(getDirInfo() !=0)
        return;

    //! view
    QStandardItemModel *model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<tr("Name")<<tr("Type"));
    for(int i=0; i < m_dirList.size(); i++){
        QList<QStandardItem*> itemList;
        QStandardItem *item1 = new QStandardItem(QIcon(":/res/image/icon/folder.png"), m_dirList.at(i));
        QStandardItem *item2 = new QStandardItem(tr("Folder"));
        itemList.append(item1);
        itemList.append(item2);
        model->appendRow(itemList);
    }

    ui->treeView->setModel(model);
    ui->treeView->setColumnWidth(0,300);
}

void FileManager::_doStarkWork(QString dir)
{
    //! file
    int ret;
    char cBuf[4096]="";
    int len = sizeof(cBuf);
    int iRow = ui->treeView->currentIndex().row();
    ret = mrgStorageDirectoryEnum(m_pPlugin->deviceVi(), 0, (m_Path+m_dirList.at(iRow)).toLocal8Bit().data(), cBuf, &len);
    if(ret < 0){
        ret = -1;
        return;
    }

    QStringList list = QString(cBuf).split("\n", QString::SkipEmptyParts);
    QStringList ltList;
    foreach (QString s, list) {
        if(!s.endsWith("/")){
            ltList.append(s);
        }
    }

    foreach (QString s, ltList) {
        QByteArray ba;
        ret = mrgStorageGetFileSize(m_pPlugin->deviceVi(), 0, (m_Path + m_dirList.at(iRow)).toLocal8Bit().data(), s.toLocal8Bit().data());
        if( ret < 0){
            sysInfo(tr("Export ")+m_Path + m_dirList.at(iRow)+tr("Fail"));
            continue;
        }
        ba.resize(ret);
        ret = mrgStorageReadFile(m_pPlugin->deviceVi(), 0, (m_Path + m_dirList.at(iRow)).toLocal8Bit().data(), s.toLocal8Bit().data(),(quint8*)ba.data());
        if( ret <=0 ){
            sysInfo(tr("Read ")+m_Path + m_dirList.at(iRow)+tr("Fail"));
            continue;
        }
        QDir tDir;
        if( !tDir.mkpath(dir + "/" + m_dirList.at(iRow)) )
            continue;
        QFile f(dir+"/" + m_dirList.at(iRow)+s);
        if(!f.open(QIODevice::WriteOnly)){
            continue;
        }
        f.write(ba);
        f.close();
    }

    //! subdir ---> log
    //! \todo
    char sdBuf[4096]="";
    int sdLen = sizeof(sdBuf);
    ret = mrgStorageDirectoryEnum(m_pPlugin->deviceVi(), 0, (m_Path+m_dirList.at(iRow)+"/log/").toLocal8Bit().data(), sdBuf, &sdLen);
    if(ret == -1){
        sysPrompt(tr("Export Log Error"));
        return;
    }
    QStringList subFileList = QString(sdBuf).split("\n", QString::SkipEmptyParts);
    foreach (QString sFile, subFileList) {
        QByteArray ba;
        ret = mrgStorageGetFileSize(m_pPlugin->deviceVi(), 0, (m_Path+m_dirList.at(iRow)+"/log/").toLocal8Bit().data(), sFile.toLocal8Bit().data());
        if(ret<0){
            continue;
        }
        ba.resize(ret);
        ret = mrgStorageReadFile(m_pPlugin->deviceVi(), 0, (m_Path+m_dirList.at(iRow)+"/log/").toLocal8Bit().data(), sFile.toLocal8Bit().data(),(quint8*)ba.data());
        if( ret <0 ){
            continue;
        }
        QDir tDir;logDbg() << dir+"/"+m_dirList.at(iRow)+"/log/";
        if( !tDir.mkpath(dir+"/"+m_dirList.at(iRow)+"/log/") )
            continue;
        QFile f(dir+"/"+m_dirList.at(iRow)+"/log/"+sFile);
        if(!f.open(QIODevice::WriteOnly)){
            continue;
        }
        f.write(ba);
        f.close();
    }
    if ( ret == -1 )
    {
        sysPrompt( tr("Export fail") );
    }
    else
    {
        sysPrompt( tr("Export completed"),0 );
    }
}

int FileManager::getDirInfo()
{
    Q_ASSERT( m_Path !=NULL );
    m_dirList.clear();
    m_fileList.clear();
    int ret;
    do{
        //path = m_pPlugin->selfPath() + "/backup/";
        char buf[4096]="";
        int iLen = sizeof(buf);
        ret = mrgStorageDirectoryEnum( m_pPlugin->deviceVi(), 0, m_Path.toLocal8Bit().data(), buf, &iLen);
        if( ret == -1 ){
            return -1;
        }

        QStringList tList = QString(buf).split("\n", QString::SkipEmptyParts);
        foreach (QString s, tList) {
            if(s.endsWith("/")){
                m_dirList << s;
            }else{
                m_fileList << s;
            }
        }

    }while(0);

    return 0;
}

int FileManager::iGetFileContent(const QString &path, const QString &name, QByteArray &_ba)
{
    //! size
    QByteArray ba;
    int ret;

    ret = mrgStorageGetFileSize(m_pPlugin->deviceVi(), 0, path.toLocal8Bit().data(), name.toLocal8Bit().data());
    if( ret < 0){
        return -1;
    }
    ba.resize(ret);
    mrgStorageReadFile(m_pPlugin->deviceVi(), 0, path.toLocal8Bit().data(), name.toLocal8Bit().data(),(quint8*)ba.data());
    _ba = ba;

    return 0;
}

void FileManager::setMode(MODE mode)
{
    m_mode = mode;
}
MODE FileManager::mode()
{
    return m_mode;
}

FileManager::~FileManager()
{
    delete ui;
}

void FileManager::on_lineEdit_textChanged(const QString &arg1)
{
    ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( arg1.length() > 0 );
}

void FileManager::on_treeView_activated(const QModelIndex &index)
{
    //! \todo
    int iRow = index.row();
    ui->lineEdit->setText( m_dirList.at(iRow));
}

