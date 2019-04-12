#include "checkdelegate.h"
#include <QtWidgets>

#define CHECK_WIDGET    QCheckBox

CheckDelegate::CheckDelegate( checkShape shp,
                              QObject *parent ) : QStyledItemDelegate(parent)
{
    mAlign = Qt::AlignCenter;

    mShape = shp;

    mPrimSize.setWidth( 0 );
    mPrimSize.setHeight( 0 );

    if ( mShape == shape_check )
    {
        QCheckBox chk;
        mPrimSize = chk.sizeHint();
    }
    else if ( mShape == shape_radio )
    {
        QRadioButton rad;
        mPrimSize = rad.sizeHint();
    }
    else
    {}
}

QWidget *CheckDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{
    if ( mShape == shape_check )
    {
        CHECK_WIDGET *pCheckbox = new CHECK_WIDGET( parent );

        pCheckbox->setCheckable( true );

        return pCheckbox;
    }
    else if ( mShape == shape_radio )
    {
        QRadioButton *pRadio = new QRadioButton( parent );

        return pRadio;
    }
    else
    {
        Q_ASSERT( false );
        return NULL;
    }
}

void CheckDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    bool b = index.model()->data(index, Qt::EditRole).toBool();

    CHECK_WIDGET *pCheckBox = static_cast<CHECK_WIDGET*>(editor);

    pCheckBox->setChecked( b );
}
void CheckDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    CHECK_WIDGET *pCheckBox = static_cast<CHECK_WIDGET*>(editor);

    model->setData( index, pCheckBox->isChecked(), Qt::EditRole );
}

void CheckDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if ( mAlign == Qt::AlignCenter )
    {
        QRect localRect;

        localRect = option.rect;
        localRect.setX( option.rect.left() + ( option.rect.width() - mPrimSize.width() ) / 2 );

        editor->setGeometry( localRect );
    }
    else
    {
        editor->setGeometry( option.rect );
    }
}

void CheckDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if ( index.isValid() )
    {}
    else
    { return; }

    //! valid role
    QVariant var = index.data( Qt::UserRole + 2 );
    if ( var.isValid() && var.type() == QVariant::Bool )
    {
        if ( var.toBool() )
        {}
        else
        { return; }
    }
    else
    {  }

    QStyleOption opt=option;
    QStyleOptionButton optBtn;

    optBtn.rect = option.rect;

    //! value
    if ( index.data( Qt::DisplayRole ).toBool() )
    { optBtn.state = QStyle::State_On | QStyle::State_Enabled; }
    else
    { optBtn.state = QStyle::State_Off | QStyle::State_Enabled; }

    //! tune the rect
    if ( mAlign == Qt::AlignCenter )
    { optBtn.rect.setX( optBtn.rect.left() + ( option.rect.width() - mPrimSize.width())/2 ); }
    else
    { }

    painter->save();

        if ( mShape == shape_check )
        {
            QApplication::style()->drawControl( QStyle::CE_CheckBox, &optBtn, painter );
        }
        else if ( mShape == shape_radio )
        {
            QApplication::style()->drawControl( QStyle::CE_RadioButton, &optBtn, painter );
        }
        else
        {}

    painter->restore();

//    logDbg();
}

void CheckDelegate::setShape( checkShape shp )
{ mShape = shp; }
checkShape CheckDelegate::shape()
{ return mShape; }

void CheckDelegate::setAlignment(  Qt::Alignment align )
{ mAlign = align; }
Qt::Alignment CheckDelegate::alignment()
{ return mAlign; }
