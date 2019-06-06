#include "info.h"
#include "ui_info.h"
#include "../plugin/xplugin.h"
#include "../../plugin/t4/t4.h"

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

    //! T4 cell items
    for( int i = 0; i < ui->tableWidget2->rowCount(); i++){
        for(int j = 0; j < ui->tableWidget2->columnCount(); j++){
            m_T4Items.append( new QTableWidgetItem );
            ui->tableWidget2->setItem( i, j, m_T4Items.last() );
        }
    }
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
    mTableItems[5]->setData( Qt::DisplayRole, m_pPlugin->viewAddr() );
    mTableItems[7]->setData( Qt::DisplayRole, m_pPlugin->firmwareVer() );
    mTableItems[9]->setData( Qt::DisplayRole, m_pPlugin->mechanicalVer() );

    m_T4Items[1]->setData( Qt::DisplayRole, m_pPlugin->Type_MRQ() );
    m_T4Items[3]->setData( Qt::DisplayRole, m_pPlugin->SN_MRQ() );
    m_T4Items[5]->setData( Qt::DisplayRole, m_pPlugin->SoftVer_MRQ() );
    m_T4Items[7]->setData( Qt::DisplayRole, m_pPlugin->FirmWareHard_MRQ() );
    m_T4Items[9]->setData( Qt::DisplayRole, m_pPlugin->FirmWareBoot_MRQ() );
    m_T4Items[11]->setData( Qt::DisplayRole, m_pPlugin->FirmWareFpga_MRQ() );

}

void Info::retranslateUi()
{
    ui->retranslateUi( this );

    mTableItems[0]->setData( Qt::DisplayRole, tr("Model") );
    mTableItems[2]->setData( Qt::DisplayRole, tr("SN") );
    mTableItems[4]->setData( Qt::DisplayRole, tr("Addr") );
    mTableItems[6]->setData( Qt::DisplayRole, tr("Firmware") );
    mTableItems[8]->setData( Qt::DisplayRole, tr("Mechanical") );

    m_T4Items[0]->setData( Qt::DisplayRole, tr("Type") );
    m_T4Items[2]->setData( Qt::DisplayRole, tr("SN") );
    m_T4Items[4]->setData( Qt::DisplayRole, tr("Firmware") );
    m_T4Items[6]->setData( Qt::DisplayRole, tr("Hardware") );
    m_T4Items[8]->setData( Qt::DisplayRole, tr("Boot") );
    m_T4Items[10]->setData( Qt::DisplayRole, tr("FPGA") );
}

void Info::onSetting(XSetting setting)
{
    XPage::onSetting( setting );

    if ( (int)setting.mSetting == XPage::e_setting_user_role )
    {
        bool bVisible = ( sysMode() == sysPara::e_sys_admin);
        ui->tableWidget2->setVisible(bVisible);
    }
}

}

