#include "errormgrtable.h"

#include "ui_errormgrtable.h"
#include "../../plugin/t4/t4.h"
#include "../../device/errorcode.h"
//#include "../../model/errmgritem.h"

namespace mrx_t4 {

ErrorMgrTable::ErrorMgrTable(QWidget *parent) :
    XPage(parent),
    ui(new Ui::ErrorMgrTable)
{
    ui->setupUi(this);

    set_page_rstable();

    m_pCheckDelegate = new CheckDelegate( shape_check, this );
    m_pRadioDelegate = new CheckDelegate( shape_radio, this );

    ui->tableView->setItemDelegateForColumn( 2, m_pRadioDelegate );
    ui->tableView->setItemDelegateForColumn( 3, m_pRadioDelegate );
    ui->tableView->setItemDelegateForColumn( 4, m_pRadioDelegate );

    ui->tableView->setItemDelegateForColumn( 6, m_pCheckDelegate );
    ui->tableView->setItemDelegateForColumn( 7, m_pCheckDelegate );
}

ErrorMgrTable::~ErrorMgrTable()
{
    delete ui;
}

void ErrorMgrTable::retranslateUi()
{
    ui->retranslateUi( this );
}

void ErrorMgrTable::setModel( QAbstractTableModel *pModel )
{
    Q_ASSERT( NULL != pModel );

    ui->tableView->setModel( pModel );

    MegaTableModel *pMegaModel = (MegaTableModel*)pModel;
    if ( NULL != pMegaModel )
    {
        connect( pMegaModel, SIGNAL(signal_data_changed()),
                 this, SLOT(slot_request_save()) );

//        connect( pMegaModel, SIGNAL(signal_data_changed()),
//                 this, SLOT(slot_data_changed()) );
    }
}
//QT_TRANSLATE_NOOP("HEADER", "No."),
//QT_TRANSLATE_NOOP("HEADER", "Error Text"),
//QT_TRANSLATE_NOOP("HEADER", "Error"),
//QT_TRANSLATE_NOOP("HEADER", "Warning"),
//QT_TRANSLATE_NOOP("HEADER", "Information"),
//QT_TRANSLATE_NOOP("HEADER", "Reaction on error"),
//QT_TRANSLATE_NOOP("HEADER", "Output stage on"),
//QT_TRANSLATE_NOOP("HEADER", "Save diagnosis"),
int ErrorMgrTable::upload()
{
    ErrorMgrModel *pModel;

    pModel = (ErrorMgrModel*)ui->tableView->model();
    if ( NULL==pModel )
    { return -1; }

    //! to local
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    int ret, code;
    int type, diagnosis, response, enable;

//    ui->tableVie
    QModelIndex index;
    for ( int i = 0; i < pModel->rowCount(QModelIndex()); i++ )
    {
        index = pModel->index( i,0 );
        code = pModel->data( index, Qt::EditRole ).toInt( );

        ret = mrgErrorCodeConfigUpload( pRobo->deviceVi(),
                                        code,
                                        &type,
                                        &diagnosis,
                                        &response,
                                        &enable );
        if ( ret != 0 )
        { return ret; }
        else
        {
            logDbg()<<code<<type<<diagnosis<<response<<enable;

            //! config the code
        }
    }

    return 0;
}
int ErrorMgrTable::download()
{
    ErrorMgrModel *pModel;

    pModel = (ErrorMgrModel*)ui->tableView->model();
    if ( NULL==pModel )
    { return -1; }

    //! to local
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    int ret, code;
    int type, diagnosis, response, enable;

    QList< ErrorMgrItem *> *pItems = pModel->items();
    for ( int i = 0; i < pItems->size(); i++ )
    {
        //! snap
        pItems->at( i )->snap( code, type, response, diagnosis, enable );

        ret = mrgErrorCodeConfigDownload( pRobo->deviceVi(),
                                        code,
                                        type,
                                        diagnosis,
                                        response,
                                        enable );
        logDbg()<<code<<type<<diagnosis<<response<<enable<<ret;
        if ( ret != 0 )
        { return ret; }
        else
        {
        }
    }

    return 0;
}
int ErrorMgrTable::diff()
{
    return 0;
}

void ErrorMgrTable::doSave()
{
    MegaTableModel *pTable = (MegaTableModel*)ui->tableView->model();
    if ( NULL == pTable )
    {
        sysError( tr("Save record fail") );
        return;
    }

    int ret;

    Q_ASSERT( NULL != m_pPlugin );
    ret = assurePath( m_pPlugin->homePath() );
    if ( ret != 0 )
    { return; }

    QString fileName = m_pPlugin->homePath() + "/errmgr.xml";
    ret = pTable->save( fileName );
    if ( ret != 0 )
    {
        sysError( fileName + " " + tr("save fail") );
        return;
    }
}
void ErrorMgrTable::doLoad()
{
    QString fileName = m_pPlugin->homePath() +"/errmgr.xml";
    int ret;

    MegaTableModel *pTable = (MegaTableModel*)ui->tableView->model();
    if ( NULL == pTable )
    {
        sysError( tr("Load record fail") );
        return;
    }

    ret = pTable->load( fileName );
    if ( ret != 0 )
    {
        sysError( fileName + " " + tr("load fail") );
        return;
    }logDbg();
}

void ErrorMgrTable::slot_request_save()
{ doSave(); logDbg(); }

void ErrorMgrTable::slot_request_load()
{ doLoad(); }

void ErrorMgrTable::slot_data_changed()
{
//    //! add to the record
//    Q_ASSERT( NULL != m_pPlugin );

//    QVariant var;
////    QList<QVariant> coords;

////    coords.append( ui->tableView->model()->rowCount() );

//    var.setValue( ui->tableView->model()->rowCount() );

//    m_pPlugin->emit_setting_changed( (eXSetting)(MRX_T4::e_setting_record), var );
}

}

