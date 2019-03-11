#include <float.h>
#include "actiontable.h"
#include "ui_actiontable.h"

#include "../../plugin/t4/t4.h"
#include "../../device/MegaRobot.h"
#include "../../device/mrqDevice.h"
#include "../../device/storage.h"

#include "../model/treeitem.h"
#include "../model/treemodel.h"

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
    m_pActionAddBefore = NULL;
    m_pActionAddBelow = NULL;
    m_pActionDelete = NULL;

    m_pActionUp = NULL;
    m_pActionDown = NULL;

    m_pActionExpandAll = NULL;
    m_pActionCollapseAll = NULL;

    m_pActionResize = NULL;

    QStringList strList;
    strList<<"PA"<<"RA";//<<"STOP"<<"CONTINUE"<<"ZERO";
    m_pTypeDelegate->setItems( strList );

    ui->view->setItemDelegateForColumn( 1, m_pTypeDelegate );

    //! connection
    connect( ui->view, SIGNAL(customContextMenuRequested(const QPoint &)),
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

void ActionTable::setModel( QAbstractItemModel *pModel )
{
    Q_ASSERT( NULL != pModel );

    ui->view->setModel( pModel );

    TreeModel *pMegaModel = (TreeModel*)pModel;
    if ( NULL != pMegaModel )
    {
        connect( pMegaModel, SIGNAL(signal_data_changed()),
                 this, SLOT(slot_request_save()) );

        connect( pMegaModel, SIGNAL(signal_data_changed()),
                 this, SLOT(slot_data_changed()) );
    }

    slot_resize();

    bool hasCurrent = ui->view->selectionModel()->currentIndex().isValid();

    if (hasCurrent) {
        ui->view->closePersistentEditor( ui->view->selectionModel()->currentIndex());
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

    pRobo->rstRecordTable();
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
    if ( ui->view->currentIndex().isValid() )
    { return ui->view->currentIndex().row(); }
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
    pModel = ui->view->model();
    if ( NULL == pModel )
    { return; }

    //! current row
    int cRow;
    QModelIndex index = ui->view->currentIndex();
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

    modelIndex = pModel->index( cRow, 1, index.parent() );
    pModel->setData( modelIndex, "PA" );

    //! x/y/z/pw/h
    for ( int i = 0; i < 5; i++ )
    {
        modelIndex = pModel->index( cRow, i + 4 );
        pModel->setData( modelIndex, vals.at( i ) );
    }

    MRX_T4 *pRobo = (MRX_T4*)m_pPlugin;
    Q_ASSERT( NULL != pRobo );

    //! vel,acc
    modelIndex = pModel->index( cRow, 9 );
    pModel->setData( modelIndex, pRobo->mDefSpeed );

    modelIndex = pModel->index( cRow, 10 );
    pModel->setData( modelIndex, pRobo->mDefAcc );

//    ui->view->model()->setData( )
//    ui->view->currentIndex()
}

void ActionTable::doSave()
{
    TreeModel *pTable = (TreeModel*)ui->view->model();
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
    TreeModel *pTable = (TreeModel*)ui->view->model();
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
{ doSave(); }

void ActionTable::slot_request_load()
{ doLoad(); }

void ActionTable::slot_data_changed()
{
    //! add to the record
    Q_ASSERT( NULL != m_pPlugin );

    QVariant var;
//    QList<QVariant> coords;

//    coords.append( ui->view->model()->rowCount() );

    var.setValue( ui->view->model()->rowCount() );

    m_pPlugin->emit_setting_changed( (eXSetting)(MRX_T4::e_setting_record), var );
}

#define get_data( val, col )    dataIndex  = ui->view->model()->index( index.row(), col );\
val = ui->view->model()->data( dataIndex );\
vars<<val;logDbg()<<val.toDouble();

void ActionTable::slot_toHere()
{
    QModelIndex index = ui->view->currentIndex();
    if ( index.isValid() )
    {}
    else
    { return; }

    QVariant _var;
    bool bOk;
    QVariant x, y, z, pw, h, v, a;
    QList<QVariant> vars;

    QModelIndex dataIndex;

    get_data( x, 4 );
    get_data( y, 5 );
    get_data( z, 6 );
    get_data( pw, 7 );

    get_data( h, 8 );
    get_data( v, 9 );
    get_data( a, 10 );

    QVariant var( vars );

    //! action
    on_post_setting( ActionTable, onToHere );
}

void ActionTable::slot_add_before()
{
    QModelIndex index = ui->view->selectionModel()->currentIndex();

    //! get data
    QVector<QVariant> vars;
    QModelIndex iterIndex;
    for ( int i = 0; i < ui->view->model()->columnCount(); i++ )
    {
        iterIndex = ui->view->model()->index( index.row(), i, index.parent() );
        vars<<ui->view->model()->data( iterIndex );
    }

    if ( ui->view->model()->insertRow( index.row(), index.parent() ) )
    {}
    else
    { return; }

    //! add data
    for ( int i = 0; i < ui->view->model()->columnCount(); i++ )
    {
        iterIndex = ui->view->model()->index( index.row(), i, index.parent() );
        ui->view->model()->setData( iterIndex, vars.at(i) );
    }

    return;
}
void ActionTable::slot_add_below()
{
    QModelIndex index = ui->view->selectionModel()->currentIndex();

    //! parent?
    TreeItem *pItem = static_cast<TreeItem*>( index.internalPointer() );
    if ( NULL == pItem )
    { return; }

    //! get data
    QVector<QVariant> vars;
    QModelIndex iterIndex;
    for ( int i = 0; i < ui->view->model()->columnCount(); i++ )
    {
        iterIndex = ui->view->model()->index( index.row(), i, index.parent() );
        vars<<ui->view->model()->data( iterIndex );
    }

    //! section
    int dstRow;
    QModelIndex parIndex;
    if ( pItem->level() == 1 )
    {
        if ( ui->view->model()->insertRow( 0 , index ) )
        { }
        else
        { return; }

        logDbg()<<index;
        parIndex = ui->view->model()->index( index.row(), 0, index.parent() );
        logDbg()<<parIndex;
        dstRow = 0;
    }
    //! sibling
    else
    {
        if ( ui->view->model()->insertRow( index.row()+1, index.parent() ) )
        {}
        else
        { return; }

        parIndex = index.parent();
        dstRow = index.row() + 1;
    }

    //! add data
    bool bRet;
    for ( int i = 0; i < ui->view->model()->columnCount(); i++ )
    {
        iterIndex = ui->view->model()->index( dstRow, i, parIndex );
        logDbg()<<iterIndex<<parIndex;
        bRet = ui->view->model()->setData( iterIndex, vars.at(i) );
        if ( !bRet )
        { return; }
    }

    return;
}
void ActionTable::slot_delete()
{
    QModelIndex index = ui->view->selectionModel()->currentIndex();

    if ( ui->view->model()->removeRow( index.row(), index.parent() ) )
    {}
    else
    { return; }

    return;
}

void ActionTable::slot_up()
{
    QModelIndex index = ui->view->selectionModel()->currentIndex();

    ui->view->model()->moveRow( index.parent(),
                                index.row(),
                                index.parent(),
                                index.row() - 1 );
}
void ActionTable::slot_down()
{
    QModelIndex index = ui->view->selectionModel()->currentIndex();

    ui->view->model()->moveRow( index.parent(),
                                index.row(),
                                index.parent(),
                                index.row() + 1 );
}

void ActionTable::slot_expandAll()
{
    ui->view->expandAll();
}
void ActionTable::slot_collapseAll()
{
    ui->view->collapseAll();
}

void ActionTable::slot_resize()
{
    for (int column = 0; column < ui->view->model()->columnCount(); ++column)
    {
        ui->view->resizeColumnToContents(column);
    }
}

void ActionTable::slot_customContextMenuRequested(const QPoint &pos)
{
    if ( mbMissionWorking )
    { return; }

    //! valid
    if ( ui->view->currentIndex().isValid() )
    {
        if(m_pContextMenu == NULL )
        {
            m_pContextMenu = new QMenu(ui->view);
            if ( NULL == m_pContextMenu )
            { return; }

            //! create
            QAction *actionToHere = m_pContextMenu->addAction(tr("To Here"));
            if ( NULL == actionToHere )
            { return; }

            m_pContextMenu->addSeparator();
            m_pActionAddBefore = m_pContextMenu->addAction( tr("Add Before") );
            m_pActionAddBelow = m_pContextMenu->addAction( tr("Add Below") );
            m_pActionDelete = m_pContextMenu->addAction( tr("Delete") );

            m_pContextMenu->addSeparator();
            m_pActionUp = m_pContextMenu->addAction( tr("Up") );
            m_pActionDown = m_pContextMenu->addAction( tr("Down") );

            m_pContextMenu->addSeparator();
            m_pActionExpandAll = m_pContextMenu->addAction( tr("All Expand") );
            m_pActionCollapseAll = m_pContextMenu->addAction( tr("All Collapse") );

            m_pContextMenu->addSeparator();
            m_pActionResize = m_pContextMenu->addAction( tr("Auto Resize") );
//            m_pContextMenu->addSeparator();
//            m_pActionReset = m_pContextMenu->addAction( tr("Reset") );

            //! connect
            connect(m_pActionAddBefore, SIGNAL(triggered(bool)),
                    this, SLOT( slot_add_before( ) ) );
            connect(m_pActionAddBelow, SIGNAL(triggered(bool)),
                    this, SLOT( slot_add_below( ) ) );
            connect(m_pActionDelete, SIGNAL(triggered(bool)),
                    this, SLOT( slot_delete( ) ) );

            connect(m_pActionUp, SIGNAL(triggered(bool)),
                    this, SLOT( slot_up( ) ) );
            connect(m_pActionDown, SIGNAL(triggered(bool)),
                    this, SLOT( slot_down( ) ) );

            connect(m_pActionExpandAll, SIGNAL(triggered(bool)),
                    this, SLOT( slot_expandAll() ) );
            connect(m_pActionCollapseAll, SIGNAL(triggered(bool)),
                    this, SLOT( slot_collapseAll() ) );

            connect(m_pActionResize, SIGNAL(triggered(bool)),
                    this, SLOT( slot_resize() ) );

//            connect(m_pActionReset, SIGNAL(triggered(bool)),
//                    this, SLOT( slot_reset( ) ) );

        }
        else
        {}

        //! \todo
//        ui->view->selectRow( ui->view->currentIndex().row() );

//        ui->view->sele
        QModelIndex index = ui->view->currentIndex();
        if ( index.isValid() )
        {}
        else
        { return; }

        TreeItem *pItem = static_cast<TreeItem*>( index.internalPointer() );
        if ( NULL == pItem )
        { return; }

        TreeItem *pParent = pItem->parent();
        if ( NULL == pParent )
        { return; }

        //! menu
        if ( pItem->level() == 1 )
        {
            m_pActionAddBefore->setEnabled( false );
            m_pActionAddBelow->setEnabled( true );
            m_pActionDelete->setEnabled( false );
        }
        else if ( pItem->level() == 2 )
        {
            m_pActionAddBefore->setEnabled( true );
            m_pActionAddBelow->setEnabled( true );
            m_pActionDelete->setEnabled( true );
        }
        else
        { return; }

        //! rst
        m_pActionUp->setEnabled( true );
        m_pActionDown->setEnabled( true );
        if ( index.row() < 1 )
        { m_pActionUp->setEnabled( false ); }

        if ( index.row() >= pParent->childCount() - 1 )
        { m_pActionDown->setEnabled( false ); }

        m_pContextMenu->exec(QCursor::pos());
    }
}

}
