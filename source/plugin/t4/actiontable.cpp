#include <float.h>
#include "actiontable.h"
#include "ui_actiontable.h"

#include "../../plugin/t4/t4.h"
#include "../../device/MegaGateway.h"

#include "../model/treeitem.h"
#include "../model/treemodel.h"

#define record_file_name  "motion.mrp"

namespace mrx_t4 {

ActionTable::ActionTable(QWidget *parent) :
    XPage(parent),
    ui(new Ui::ActionTable)
{
    ui->setupUi(this);

    ui->view->setColumnWidth( 0, 20 );
    for ( int i = 1; i < 11; i++ )
    {
        ui->view->setColumnWidth( i, 20 );
    }

    setContextHelp( "record" );

    set_page_rstable();

    setUri( "record" );

    m_pDelegateXYZ = new dSpinDelegate( -1000, 1000, this );
    m_pDelegatePw = new dSpinDelegate( -360, 360, this );
    m_pDelegateH = new dSpinDelegate( -360, 360, this );
    m_pDelegateV = new dSpinDelegate( 1, 100, this );
    m_pDelegateV->setSuffix( "%" );

    m_pCheckDelegate = new CheckDelegate( shape_check, this );
    m_pCheckDelegate->setAlignment( Qt::AlignLeft );

    ui->view->setItemDelegateForColumn( 2, m_pDelegateXYZ );
    ui->view->setItemDelegateForColumn( 3, m_pDelegateXYZ );
    ui->view->setItemDelegateForColumn( 4, m_pDelegateXYZ );

    ui->view->setItemDelegateForColumn( 5, m_pDelegatePw );
    ui->view->setItemDelegateForColumn( 6, m_pDelegateH );

    ui->view->setItemDelegateForColumn( 7, m_pDelegateV );
    ui->view->setItemDelegateForColumn( 8, m_pCheckDelegate );

    m_pContextMenu = NULL;

    m_pActionToHere = NULL;
    m_pActionAddBefore = NULL;
    m_pActionAddBelow = NULL;
    m_pActionDelete = NULL;

    m_pActionUp = NULL;
    m_pActionDown = NULL;

    m_pActionExpandAll = NULL;
    m_pActionCollapseAll = NULL;

    m_pActionResize = NULL;

    m_pTypeDelegate = new ComboxDelegate( 0, this );

    QStringList strList;
    strList<<"PA"<<"PRA"<<"PRN";//<<"STOP"<<"CONTINUE"<<"ZERO";
    m_pTypeDelegate->setItems( strList );

    ui->view->setItemDelegateForColumn( 1, m_pTypeDelegate );

    //! connection
    connect( ui->view, SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(slot_customContextMenuRequested(const QPoint &)));

    spySetting( MRX_T4::e_add_record );
    spySetting( MRX_T4::e_edit_record );
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
    {logDbg();
        addRecord( setting );
    }
    else if ( (int)setting.mSetting == (int)MRX_T4::e_edit_record )
    {logDbg();
        editRecord( setting );
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
        //! query
        QByteArray fileListAry;
        int fileListCapacity = 1024*1024;
        fileListAry.reserve( fileListCapacity );
        int fileListLen;
        fileListLen = mrgStorageMotionFileQuery( pRobo->deviceVi(),
                                   0,
                                   fileListAry.data(),
                                   fileListCapacity );
        if ( fileListLen < fileListCapacity )
        {}
        else
        {
            sysError( tr("Too many files") );
            return -1;
        }

        //! file list
        QString fileList( QByteArray( fileListAry, fileListLen ) );

        //! check the file exist
        QString fileAry = m_pPlugin->model().toLower() + "_" + record_file_name;

        if ( fileList.contains( fileAry.toLatin1().data() ) )
        {}
        else
        {
            sysError( tr("File do not exist") + " " + fileAry );
            return -1;
        }

        //! read data
        int ret = mrgStorageMotionFileContextRead( pRobo->deviceVi(),
                                               fileAry.toLatin1().data(),
                                               ary.data(),
                                               capacity );

        if ( ret <= 0 )
        {
            sysError( tr("File read fail") + " " + fileAry );
            break;
        }

        //! save the file
        QFile file( m_pPlugin->homePath() + "/up_" + record_file_name );
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

        //! read success + reload
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
    QString fileOutName = m_pPlugin->model().toLower() + record_file_name;
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

//! \note return the parent row
int ActionTable::currentIndex()
{
    if ( ui->view->currentIndex().isValid() )
    {
        TreeItem* pItem = (TreeItem*)ui->view->currentIndex().internalPointer();
        if ( pItem == NULL )
        { return -1; }

        if ( pItem->level() == 0 )
        {
            return -1;
        }
        else if ( pItem->level() == 1 )
        {
            return ui->view->currentIndex().row();
        }
        else if ( pItem->level() == 2 )
        {
            //! \todo notify
            if ( ui->view->currentIndex().parent().isValid() )
            { return ui->view->currentIndex().parent().row(); }
            else
            { return -1; }
        }
        else
        { return -1; }
    }
    else
    { return -1; }
}

void ActionTable::addRecord( XSetting setting )
{
    //! add below
    slot_add_below();

    //! edit the data
    editRecord( setting );
}

//! keep the v and acc
void ActionTable::editRecord( XSetting setting )
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

    //! from index
    QModelIndex modelIndex;

    modelIndex = pModel->index( cRow, 1, index.parent() );
    pModel->setData( modelIndex, "PA" );

    //! x/y/z/pw/h
    for ( int i = 0; i < 5; i++ )
    {
        modelIndex = pModel->index( cRow, i + 2, index.parent() );
        pModel->setData( modelIndex, vals.at( i ) );
    }

    //! \note keep vel,acc

}

void ActionTable::doSave()
{logDbg();
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
       <<vars.at(0).toString()
      <<vars.at(1).toDouble()
      <<vars.at(2).toDouble()
      <<vars.at(3).toDouble()
      <<vars.at(4).toDouble()
      <<vars.at(5).toDouble()
      <<vars.at(6).toDouble()
      <<vars.at(7).toBool();

    if ( str_is( vars.at(0).toString(), "PA" ) )
    {
        return absToHere( vars );
    }
    else if ( str_is( vars.at(0).toString(), "RRA" )
              || str_is( vars.at(0).toString(), "RRN" ))
    {
        return relToHere( vars );
    }
    else
    {
        sysError( tr("Invalid input") );
        return -1;
    }


}

int ActionTable::relToHere( QList<QVariant> &vars )
{
    check_connect_ret( -1 );

    int ret;
    //! \note the speed
    ret = pRobo->relMove( "",
                          vars.at(1).toDouble(), vars.at(2).toDouble(), vars.at(3).toDouble(),
                          vars.at(4).toDouble(), vars.at(5).toDouble(),
                          rel_to_abs_speed( vars.at(6).toDouble() ), vars.at(7).toBool()
                          );
    return ret;
}
int ActionTable::absToHere( QList<QVariant> &vars )
{
    check_connect_ret( -1 );

    int ret;
    ret = pRobo->absMove( "",
                          vars.at(1).toDouble(), vars.at(2).toDouble(), vars.at(3).toDouble(),
                          vars.at(4).toDouble(), vars.at(5).toDouble(),
                          rel_to_abs_speed( vars.at(6).toDouble() ), vars.at(7).toBool()
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

#define get_data( val, col )    val = pItem->dataSets().at( col );\
vars<<val;

void ActionTable::slot_toHere()
{
    QModelIndex index = ui->view->currentIndex();
    if ( index.isValid() )
    {}
    else
    { return; }

    QVariant type, x, y, z, pw, h, v, line;
    QList<QVariant> vars;

    TreeItem *pItem = (TreeItem*)index.internalPointer();
    if ( NULL == pItem )
    { return; }

    get_data( type, 1 );
    get_data( x, 2 );
    get_data( y, 3 );
    get_data( z, 4 );
    get_data( pw, 5 );

    get_data( h, 6 );
    get_data( v, 7 );
    get_data( line, 8 );

    QVariant var( vars );

    //! action
    on_post_setting( ActionTable, onToHere, tr("To here") );
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

    //! set current
    ui->view->setCurrentIndex( ui->view->model()->index( dstRow, 0, parIndex ) );
    ui->view->expanded( ui->view->model()->index( dstRow, 0, parIndex ) );
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
//        ui->view->resizeColumnToContents(column);
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
            m_pActionToHere = m_pContextMenu->addAction(tr("To Here"));
            if ( NULL == m_pActionToHere )
            { return; }
            m_pActionToHere->setIcon( QIcon(":/res/image/icon/skip.png") );

            m_pContextMenu->addSeparator();
            m_pActionAddBefore = m_pContextMenu->addAction( tr("Add Before") );
            m_pActionAddBelow = m_pContextMenu->addAction( tr("Add Below") );
            m_pActionDelete = m_pContextMenu->addAction( tr("Delete") );

            m_pActionAddBefore->setIcon( QIcon(":/res/image/icon/xiangshangzhanhang.png") );
            m_pActionAddBelow->setIcon( QIcon(":/res/image/icon/xiangxiazhanhang.png") );
            m_pActionDelete->setIcon( QIcon(":/res/image/icon/trash.png") );

            m_pContextMenu->addSeparator();
            m_pActionUp = m_pContextMenu->addAction( tr("Up") );
            m_pActionDown = m_pContextMenu->addAction( tr("Down") );

            m_pActionUp->setIcon( QIcon(":/res/image/icon/arrowup.png") );
            m_pActionDown->setIcon( QIcon(":/res/image/icon/arrowdown.png") );

            m_pContextMenu->addSeparator();
            m_pActionExpandAll = m_pContextMenu->addAction( tr("All Expand") );
            m_pActionCollapseAll = m_pContextMenu->addAction( tr("All Collapse") );

//            m_pContextMenu->addSeparator();
//            m_pActionResize = m_pContextMenu->addAction( tr("Auto Resize") );
//            m_pContextMenu->addSeparator();
//            m_pActionReset = m_pContextMenu->addAction( tr("Reset") );

            //! connect
            connect( m_pActionToHere, SIGNAL(triggered(bool)),
                     this, SLOT(slot_toHere()) );

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

//            connect(m_pActionResize, SIGNAL(triggered(bool)),
//                    this, SLOT( slot_resize() ) );

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

        //! change the to here
        QString strToHereSuffix;
        strToHereSuffix = QString("(%1,%2,%3)").arg( pItem->data(2).toDouble(),0,'f',2 )
                                               .arg( pItem->data(3).toDouble(),0,'f',2 )
                                               .arg( pItem->data(4).toDouble(),0,'f',2 );

        //! PA && RA
        if ( str_is( pItem->data( 1 ).toString(), "PA") )
        { m_pActionToHere->setText( tr("To:") + " " + strToHereSuffix ); }
        else
        { m_pActionToHere->setText( tr("Step:") + " " + strToHereSuffix );}

        m_pContextMenu->exec(QCursor::pos());
    }
}

}