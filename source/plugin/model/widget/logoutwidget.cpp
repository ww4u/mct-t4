#include "logoutwidget.h"
#include <QGuiApplication>
#include <QClipboard>

#include "../megaloglistmodel.h"

//#include "ui_logoutwidget.h"

LogoutWidget::LogoutWidget(QWidget *parent): QListView( parent )/*, ui( new Ui::LogoutWidget )*/
{
    setupUi();

    setContextMenuPolicy( Qt::CustomContextMenu );
    setSelectionMode( QAbstractItemView::ExtendedSelection );
    buildConnection();

    retranslateUi();
}

LogoutWidget::~LogoutWidget()
{
}

void LogoutWidget::setupUi()
{
    //! create menu
    m_pContextMenu = new QMenu( this );
    Q_ASSERT( NULL != m_pContextMenu );

    m_pClearAction = m_pContextMenu->addAction( tr("Clear") );
    m_pSelectAllAction = m_pContextMenu->addAction( tr("Select All") );
    m_pCopyAction = m_pContextMenu->addAction( tr("Copy") );
}
void LogoutWidget::buildConnection()
{
    connect( this, SIGNAL(customContextMenuRequested( const QPoint &)),
             this, SLOT(slot_contextmenu( const QPoint &)));

    //! copy
    connect( m_pClearAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_clear()) );

    connect( m_pSelectAllAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_selectall()) );

    connect( m_pCopyAction, SIGNAL(triggered(bool)),
             this, SLOT(slot_copy()) );

}

void LogoutWidget::retranslateUi()
{
    m_pClearAction->setText( tr("Clear") );
    m_pSelectAllAction->setText( tr("Select All") );
    m_pCopyAction->setText( tr("Copy") );
}

void LogoutWidget::slot_contextmenu( const QPoint &pt )
{
    Q_ASSERT( NULL != m_pContextMenu );

    m_pContextMenu->exec( mapToGlobal( pt ) );
}

void LogoutWidget::slot_clear()
{
    ( (MegaLogListModel*)model() ) ->clear();
}

void LogoutWidget::slot_selectall()
{
    selectAll();
}

void LogoutWidget::slot_copy()
{
    QModelIndexList list = selectionModel()->selectedRows();

    QString str, itemStr;

    foreach( QModelIndex index, list )
    {
        itemStr = model()->data( index ).toString();
        str.append( itemStr );
        str.append( "\n");
    }

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText( str );
}


