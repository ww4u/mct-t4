#include "errormgrtable.h"

#include "ui_errormgrtable.h"
#include "../../plugin/t4/t4.h"

#include "MegaGateway.h"

namespace mrx_t4 {

///**
// * @brief calcResponse
// * @param reaction 1,2,3,4
// * @param outputAble 0,1
// * @return 小于零失败
// */
//int ErrorMgrTable::calcResponse(int reaction, int outputAble)
//{
//    if(reaction<1 || reaction>4 || outputAble<0 || outputAble>1 ) {
//        return -1;
//    }

//    //! 1
//    if(reaction == 1){
//        return 1;
//    }

//    //! 2 3 4
//    if(reaction != 1 && outputAble == 1){
//        return reaction;
//    }

//    //! 5 6 7
//    if(reaction != 1 && outputAble == 0){
//        return reaction + 3;
//    }

//    return -1;
//}

///**
// * @brief H2ErrMgr::parseResponse
// * @param response 1,2,3,4,5,6,7
// * @param reaction 输出1,2,3,4
// * @param outputAble 输出0或1
// * @return 小于零失败
// */
//int ErrorMgrTable::parseResponse(int response,int *reaction, int *outputAble)
//{
//    if(response == 1) {
//        *reaction = 1;
//        return 0;
//    }

//    if(response>=2 && response<=4) {
//        *reaction = response;
//        *outputAble = 1;
//        return 0;
//    }
//    else if(response>=5 && response<=7) {
//        *reaction = response - 3;
//        *outputAble = 0;
//        return 0;
//    }
//    else {
//        return -1;
//    }
//}

ErrorMgrTable::ErrorMgrTable(QWidget *parent) :
    XPage(parent),
    ui(new Ui::ErrorMgrTable)
{
    ui->setupUi(this);

    setContextHelp( "errorconfig" );

    set_page_rstable();

    m_pCheckDelegate = new CheckDelegate( shape_check, this );
//    m_pRadioDelegate = new CheckDelegate( shape_radio, this );

//    //! visible role
//    //! \note set errmodel
    m_pCheckDelegate->setVisibleRole( Qt::UserRole );
//    m_pRadioDelegate->setVisibleRole( Qt::UserRole );

//    m_pComboxDelegate = new ComboxDelegate( 1, this );

//    ui->tableView->setItemDelegateForColumn( 2, m_pRadioDelegate );
//    ui->tableView->setItemDelegateForColumn( 3, m_pRadioDelegate );
//    ui->tableView->setItemDelegateForColumn( 4, m_pRadioDelegate );

//    ui->tableView->setItemDelegateForColumn( 5, m_pComboxDelegate );

    ui->tableView->setItemDelegateForColumn( 5, m_pCheckDelegate );
    ui->tableView->setItemDelegateForColumn( 6, m_pCheckDelegate );
}

ErrorMgrTable::~ErrorMgrTable()
{
    delete ui;
}

void ErrorMgrTable::retranslateUi()
{
    ui->retranslateUi( this );
}

void ErrorMgrTable::onPluginChanged()
{
    XPage::onPluginChanged();

    //! \note get the error message from template
    rst();
}

#define def_width     120
#define wider1_width  200
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

    //! width
    ui->tableView->setColumnWidth( 0, def_width );
    ui->tableView->setColumnWidth( 1, wider1_width );

    ui->tableView->setColumnWidth( 2, def_width );
    ui->tableView->setColumnWidth( 3, wider1_width );
    ui->tableView->setColumnWidth( 4, wider1_width );

    ui->tableView->setColumnWidth( 5, def_width );
    ui->tableView->setColumnWidth( 6, def_width );
//    ui->tableView->setColumnWidth( 7, def_width );
}

void ErrorMgrTable::rst()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    if ( NULL == pRobo )
    { return; }

    pRobo->rstErrorMgrTable();
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
//    ErrorMgrModel *pModel;

//    pModel = (ErrorMgrModel*)ui->tableView->model();
//    if ( NULL==pModel )
//    { return -1; }

//    //! to local
//    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
//    Q_ASSERT( NULL != pRobo );

//    int ret, code;
//    int type, diagnosis, response, enable;
//    int reaction, output;

////    ui->tableview
//    QModelIndex index;
//    for ( int i = 0; i < pModel->rowCount(QModelIndex()); i++ )
//    {
//        index = pModel->index( i,0 );
//        code = pModel->data( index, Qt::EditRole ).toInt( );

//        ret = mrgErrorCodeConfigUpload( pRobo->deviceVi(),
//                                        code,
//                                        &type,
//                                        &response,
//                                        &diagnosis,
//                                        &enable );
//        if ( ret != 0 )
//        { return ret; }
//        else
//        {
//            //! deparse
//            parseResponse( response, &reaction, &output );

//            QStringList strReactionList;
//            strReactionList << "Free-wheeling" << "QS deceleration" << "Record deceleration" << "Finish Record";

//            logDbg()<<code<<type<<diagnosis<<response<<enable;

//            do
//            {
//                //! type
//                if ( type == ErrorMgrItem::e_error )
//                { pModel->setData( pModel->index( i, 2 ), true, Qt::EditRole ); }
//                else if ( type == ErrorMgrItem::e_warning )
//                { pModel->setData( pModel->index( i, 3 ), true, Qt::EditRole ); }
//                else if ( type == ErrorMgrItem::e_info )
//                { pModel->setData( pModel->index( i, 4 ), true, Qt::EditRole ); }
//                else
//                { break; }

//                //! action
//                pModel->setData( pModel->index( i, 5 ), strReactionList.at(reaction - 1), Qt::EditRole );

//                //! output
//                pModel->setData( pModel->index( i, 6 ), output > 0, Qt::EditRole );

//                //! save
//                pModel->setData( pModel->index( i, 7 ), diagnosis > 0, Qt::EditRole );
//             }while( 0 );

//        }
//    }

    return 0;
}
int ErrorMgrTable::download()
{
//    ErrorMgrModel *pModel;

//    pModel = (ErrorMgrModel*)ui->tableView->model();
//    if ( NULL==pModel )
//    { return -1; }

//    //! to local
//    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
//    Q_ASSERT( NULL != pRobo );

//    int ret, code;
//    int type, response, output, save;
//    int reaction;
//    QList< ErrorMgrItem *> *pItems = pModel->items();
//    for ( int i = 0; i < pItems->size(); i++ )
//    {
//        //! snap
//        pItems->at( i )->snap( code, type, reaction, output, save );

//        response = calcResponse( reaction, output );

//        //! config
//        ret = mrgErrorCodeConfigDownload( pRobo->deviceVi(),
//                                        code,
//                                        type,
//                                        response,
//                                        save,
//                                        1 );
//        logDbg()<<code<<type<<response<<output<<save<<ret;
//        if ( ret != 0 )
//        { return ret; }
//        else
//        {
//        }
//    }

    return 0;
}
int ErrorMgrTable::diff()
{
    return 0;
}

//void ErrorMgrTable::doSave()
//{
//    QString fileName = m_pPlugin->selfPath() + "/" + error_mgr_file_name;

//    int ret = -1;
//    do
//    {
//        MegaTableModel *pTable = (MegaTableModel*)ui->tableView->model();
//        if ( NULL == pTable )
//        {
//            ret = -1;
//            break;
//        }

//        //! export
//        QByteArray theAry;
//        ret = pTable->save( theAry );
//        if ( ret != 0 )
//        { break; }

//        //! save
//        ret = mrgStorageWriteFile( plugin_root_dir(),
//                                   error_mgr_file_name,
//                                   (quint8*)theAry.data(),
//                                   theAry.length() );

//        if ( ret != 0 )
//        { break; }

//    }while( 0 );

//    if ( ret != 0 )
//    {
//        sysError( fileName + " " + tr("save fail") );
//    }
//}
//void ErrorMgrTable::doLoad()
//{
//    QString fileName = m_pPlugin->selfPath() + "/" + error_mgr_file_name;
//    int ret = -1;

//    do
//    {
//        MegaTableModel *pTable = (MegaTableModel*)ui->tableView->model();
//        if ( NULL == pTable )
//        {
//            ret = -1;
//            break;
//        }

//        QByteArray theAry;
//        theAry.reserve( max_file_size );
//        ret = mrgStorageReadFile( plugin_root_dir(),
//                                  error_mgr_file_name,
//                                  (quint8*)theAry.data() );
//        if ( ret <= 0 )
//        {
//            ret = -2;
//            break;
//        }
//        theAry.resize( ret );

//        pTable->load( theAry );

//    }while( 0 );

//    if ( ret < 0 )
//    {
//        sysError( fileName + " " + tr("load fail") );
//    }logDbg();

//}

//void ErrorMgrTable::slot_request_save()
//{ doSave(); logDbg(); }

//void ErrorMgrTable::slot_request_load()
//{ doLoad(); }

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

