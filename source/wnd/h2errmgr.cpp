#include "h2errmgr.h"
#include "ui_h2errmgr.h"

H2ErrMgr::H2ErrMgr(QWidget *parent) :
    XConfig(parent),
    ui(new Ui::H2ErrMgr)
{
    ui->setupUi(this);

    setFocusName( "Error_management" );

    //! delegate
    m_pCheckDelegate = new checkDelegate( shape_check, this );
    m_pRadioDelegate = new checkDelegate( shape_radio, this );
    m_pErrActionDelegate = new comboxDelegate( this );

    //! opt
    QStringList errActions;
    errActions << tr("Free-wheeling")
               << tr("QS deceleration")
               << tr("Record deceleration")
               << tr("Finish Record");

    m_pErrActionDelegate->setItems( errActions );

    connect(&mErrManager, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this,SLOT(slotModelChanged(QModelIndex,QModelIndex,QVector<int>)));
}

H2ErrMgr::~H2ErrMgr()
{
    delete ui;
}

void H2ErrMgr::slotModelChanged(QModelIndex index1, QModelIndex index2, QVector<int> vector)
{
    emit signal_data_changed(true);
}

int H2ErrMgr::readDeviceConfig()
{
    return 0;
}

int H2ErrMgr::writeDeviceConfig()
{

    return 0;
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

    ui->tvErr->setItemDelegateForColumn( 5, m_pErrActionDelegate );

    ui->tvErr->setItemDelegateForColumn( 6, m_pCheckDelegate );
    ui->tvErr->setItemDelegateForColumn( 7, m_pCheckDelegate );

}

