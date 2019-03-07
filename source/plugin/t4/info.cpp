#include "info.h"
#include "ui_info.h"
#include "../plugin/xplugin.h"
namespace mrx_t4 {

Info::Info(QWidget *parent) :
    XPage(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);

    setContextHelp( "info" );

    //! cell items
    for ( int i = 0; i < ui->tableWidget->rowCount(); i++ )
    {
        for ( int j = 0; j < ui->tableWidget->columnCount(); j++ )
        {
            mTableItems.append( new QTableWidgetItem() );

            ui->tableWidget->setItem( i, j, mTableItems.last() );
        }
    }

    //! translate
//    retranslateUi();
}

Info::~Info()
{
    delete ui;
}

void Info::updateUi()
{
    //! title config
    retranslateUi();

    Q_ASSERT( NULL != m_pPlugin );
    mTableItems[1]->setData( Qt::DisplayRole, m_pPlugin->model() );
    mTableItems[3]->setData( Qt::DisplayRole, m_pPlugin->SN() );
    mTableItems[5]->setData( Qt::DisplayRole, m_pPlugin->addr() );
    mTableItems[7]->setData( Qt::DisplayRole, m_pPlugin->firmwareVer() );
    mTableItems[9]->setData( Qt::DisplayRole, m_pPlugin->mechanicalVer() );
}

void Info::retranslateUi()
{
    ui->retranslateUi( this );

    mTableItems[0]->setData( Qt::DisplayRole, tr("Model") );
    mTableItems[2]->setData( Qt::DisplayRole, tr("SN") );
    mTableItems[4]->setData( Qt::DisplayRole, tr("Addr") );
    mTableItems[6]->setData( Qt::DisplayRole, tr("Firmware") );
    mTableItems[8]->setData( Qt::DisplayRole, tr("Mechanical") );
}

}

