#include <float.h>
#include "actiontable.h"
#include "ui_actiontable.h"

#include "../../plugin/t4/t4.h"
#include "../../device/MegaRobot.h"
#include "../../device/mrqDevice.h"
#include "../../device/storage.h"

#include "../model/recordtable.h"

#define record_file_name  "record.mrp"

namespace mrx_t4 {

ActionTable::ActionTable(QWidget *parent) :
    XPage(parent),
    ui(new Ui::ActionTable)
{
    ui->setupUi(this);

    setContextHelp( "record" );

    set_page_rstable();

    setUri( "record" );

    m_pTypeDelegate = new ComboxDelegate( 0, this );
    m_pContextMenu = NULL;

    QStringList strList;
    strList<<"PA"<<"RA";//<<"STOP"<<"CONTINUE"<<"ZERO";
    m_pTypeDelegate->setItems( strList );

    ui->tableView->setItemDelegateForColumn( 0, m_pTypeDelegate );

    //! connection
    connect( ui->tableView, SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(slot_customContextMenuRequested(const QPoint &)));

    spySetting( MRX_T4::e_add_record );
}

ActionTable::~ActionTable()
{
    delete ui;
}

void ActionTable::retranslateUi()
{
    ui->retranslateUi( this );
}

void ActionTable::setModel( QAbstractTableModel *pModel )
{
    Q_ASSERT( NULL != pModel );

    ui->tableView->setModel( pModel );

    MegaTableModel *pMegaModel = (MegaTableModel*)pModel;
    if ( NULL != pMegaModel )
    {
        connect( pMegaModel, SIGNAL(signal_data_changed()),
                 this, SLOT(slot_request_save()) );

        connect( pMegaModel, SIGNAL(signal_data_changed()),
                 this, SLOT(slot_data_changed()) );
    }
}

void ActionTable::onSetting(XSetting setting)
{
    XPage::onSetting( setting );

    if ( (int)setting.mSetting == (int)MRX_T4::e_add_record )
    {
        logDbg();

        QList<QVariant> coords;

        coords = setting.mPara1.toList();

        foreach (QVariant var, coords)
        {
            logDbg()<<var.toDouble();
        }

        addRecord( setting );

//        slot_request_save();
    }
    else
    {}
}

void ActionTable::rst()
{
    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    if ( NULL == pRobo )
    { return; }

    pRobo->rstRecordTable();logDbg();
}

int ActionTable::upload()
{
    check_connect_ret( -1 );

    QByteArray ary;

    int capacity = 1024*1024;
    ary.reserve( capacity );

    do
    {
        QString fileAry = m_pPlugin->SN() + "_" + record_file_name;
        int ret = mrgStorageMotionFileContextRead( pRobo->deviceVi(),
                                               fileAry.toLatin1().data(),
                                               ary.data(),
                                               capacity );

        if ( ret <= 0 )
        { break; }

        //! save the file
        QFile file( m_pPlugin->homePath() + "/" + record_file_name );
        if ( file.open( QIODevice::WriteOnly ) )
        {}
        else
        { break; }

        if ( ret != file.write( ary.data(), ret ) )
        {
            file.close();
            break;
        }

        file.close();

        //! write success + reload
        doLoad();

        return 0;

    }while( 0 );

    sysError( tr("Record load fail") );
    return -1;
}
int ActionTable::download()
{
    check_connect_ret( -1 );

    QString fileName = m_pPlugin->homePath() + "/" + record_file_name;
    QString fileOutName = m_pPlugin->SN() + "_" + record_file_name;
    int ret = mrgStorageMotionFileSave( pRobo->deviceVi(),
                              fileName.toLatin1().data(),
                              fileOutName.toLatin1().data()
                              );
    if ( ret != 0 )
    {
        sysError( tr("Record save fail") );
    }

    return ret;
}
int ActionTable::diff()
{
    return 0;
}

void ActionTable::enterMission()
{
    if ( NULL != m_pContextMenu )
    { m_pContextMenu->setEnabled( false ); }
}
void ActionTable::exitMission()
{
    if ( NULL != m_pContextMenu )
    { m_pContextMenu->setEnabled( true ); }
}

int ActionTable::currentIndex()
{
    if ( ui->tableView->currentIndex().isValid() )
    { return ui->tableView->currentIndex().row(); }
    else
    { return -1; }
}

void ActionTable::addRecord( XSetting setting )
{
    QList<QVariant> coords;
    QList<double> vals;
    coords = setting.mPara1.toList();

    bool bOk;
    foreach (QVariant var, coords)
    {
//        logDbg()<<var.toDouble();
        vals<<var.toDouble( &bOk );
        if ( bOk )
        {}
        else
        { return; }
    }

    QAbstractItemModel *pModel;
    pModel = ui->tableView->model();
    if ( NULL == pModel )
    { return; }

    //! current row
    int cRow;
    QModelIndex index = ui->tableView->currentIndex();
    if ( index.isValid() )
    { cRow = index.row(); }
    else
    { return; }
//    { cRow = pModel->rowCount(); }

    //! insert
//    if ( pModel->insertRow( cRow ) )
//    { logDbg(); }
//    else
//    { logDbg(); return; }

    //! from index
    QModelIndex modelIndex;

    modelIndex = pModel->index( cRow, 0 );
    pModel->setData( modelIndex, "PA" );

    //! x/y/z/pw/h
    for ( int i = 0; i < 5; i++ )
    {
        modelIndex = pModel->index( cRow, i + 2 );
        pModel->setData( modelIndex, vals.at( i ) );
    }

    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    //! vel,acc
    modelIndex = pModel->index( cRow, 7 );
    pModel->setData( modelIndex, pRobo->mDefSpeed );

    modelIndex = pModel->index( cRow, 8 );
    pModel->setData( modelIndex, pRobo->mDefAcc );

//    ui->tableView->model()->setData( )
//    ui->tableView->currentIndex()
}

void ActionTable::doSave()
{
    RecordTable *pTable = (RecordTable*)ui->tableView->model();
    if ( NULL == pTable )
    {
        sysError( tr("Save record fail") );
        return;
    }

    int ret;

    Q_ASSERT( NULL != m_pPlugin );
    ret = assurePath( m_pPlugin->homePath() );
    if ( ret != 0 )
    {
        sysError( tr("Save record fail") );
        return;
    }

    //! mrp
    QString fileName = m_pPlugin->homePath() + "/" + record_file_name;
    ret = pTable->exportOut( fileName );
    if ( ret != 0 )
    {
        sysError( fileName + " " + tr("save fail") );
        return;
    }
}

void ActionTable::doLoad()
{
    QString fileName = m_pPlugin->homePath() + "/" + record_file_name;
    RecordTable *pTable = (RecordTable*)ui->tableView->model();
    if ( NULL == pTable )
    {
        sysError( tr("Load record fail") );
        return;
    }

    int ret = pTable->loadIn( fileName );
    if ( ret != 0 )
    {
        sysError( tr("Load record fail") );
    }
}

//! x,y,z,pw,h,v,a
int ActionTable::onToHere( QVariant var )
{
    check_connect_ret( -1 );

    QList<QVariant> vars;

    vars = var.toList();
logDbg()<<QThread::currentThreadId()
       <<vars.at(0).toDouble()
      <<vars.at(1).toDouble()
      <<vars.at(2).toDouble()
      <<vars.at(3).toDouble()
      <<vars.at(4).toDouble()
      <<vars.at(5).toDouble()
      <<vars.at(6).toDouble();

    //! get remote pos
    int ret;
    float x,y,z;
    ret = mrgGetRobotCurrentPosition( robot_var(),
                                &x, &y, &z );
    if ( ret != 0 )
    {
        sysError( tr("Position read fail") );
        return -1;
    }

    //! calc the distance
    float dist = sqrt( pow(  x - vars.at(0).toDouble(), 2) +
                       pow(  y - vars.at(1).toDouble(), 2) +
                       pow(  z - vars.at(1).toDouble(), 2)
                       );
    float time = qAbs( dist ) / pRobo->velocity();
    if ( time < FLT_MIN * 2 )
    {
        sysError( tr("Time too short") );
        return -1;
    }

    ret = mrgRobotRelMove( robot_var(),
                               wave_table,
                               vars.at(0).toDouble(),
                               vars.at(1).toDouble(),
                               vars.at(2).toDouble(),
                               time,
                               60000 + time
                               );

    return ret;
}

void ActionTable::slot_request_save()
{ doSave(); logDbg(); }

void ActionTable::slot_request_load()
{ doLoad(); }

void ActionTable::slot_data_changed()
{
    //! add to the record
    Q_ASSERT( NULL != m_pPlugin );

    QVariant var;
//    QList<QVariant> coords;

//    coords.append( ui->tableView->model()->rowCount() );

    var.setValue( ui->tableView->model()->rowCount() );

    m_pPlugin->emit_setting_changed( (eXSetting)(MRX_T4::e_setting_record), var );
}

#define get_data( val, col )    dataIndex  = ui->tableView->model()->index( index.row(), col );\
val = ui->tableView->model()->data( dataIndex );\
vars<<val;logDbg()<<val.toDouble();

void ActionTable::slot_toHere()
{
    QModelIndex index = ui->tableView->currentIndex();
    if ( index.isValid() )
    {}
    else
    { return; }

    QVariant _var;
    bool bOk;
    QVariant x, y, z, pw, h, v, a;
    QList<QVariant> vars;

    QModelIndex dataIndex;

    get_data( x, 2 );
    get_data( y, 3 );
    get_data( z, 4 );
    get_data( pw, 5 );

    get_data( h, 6 );
    get_data( v, 7 );
    get_data( a, 8 );

    QVariant var( vars );

    //! action
    on_post_setting( ActionTable, onToHere );
}

void ActionTable::slot_customContextMenuRequested(const QPoint &pos)
{
    if ( mbMissionWorking )
    { return; }

    //! valid
    if ( ui->tableView->currentIndex().isValid() )
    {
        if(m_pContextMenu == NULL )
        {
            m_pContextMenu = new QMenu(ui->tableView);
            if ( NULL == m_pContextMenu )
            { return; }

            QAction *actionToHere = m_pContextMenu->addAction(tr("To Here"));
            if ( NULL == actionToHere )
            { return; }

            connect(actionToHere, SIGNAL(triggered(bool)),
                    this, SLOT( slot_toHere( ) ) );
        }
        else
        {}

//        int row = ui->tableView->selectionModel()->selectedIndexes().first().row();
        ui->tableView->selectRow( ui->tableView->currentIndex().row() );
        m_pContextMenu->exec(QCursor::pos());

//        ui->tableView->selectionModel()->clear();
    }
}

}
