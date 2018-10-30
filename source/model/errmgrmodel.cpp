#include "errmgrmodel.h"

#include "mystd.h"

ErrMgrModel::ErrMgrModel() : MegaTableModel()
{

}

ErrMgrModel::~ErrMgrModel()
{
    delete_all( mItems );
}

int ErrMgrModel::rowCount(const QModelIndex &parent) const
{ return mItems.count(); }
int ErrMgrModel::columnCount(const QModelIndex &parent) const
{ return ErrMgrItem::columns(); }

QVariant ErrMgrModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
    { return QVariant(); }

    //! index
    int col = index.column();
    int row = index.row();

    if ( role != Qt::DisplayRole && role != Qt::EditRole )
    { return QVariant(); }

    if ( col == 0 )
    { return QVariant( mItems[ row ]->mNr ); }
    else if ( col == 1 )
    { return QVariant( ( mItems[ row ]->mErr ) ); }
    else if ( col == 2 )
    { return QVariant( ( mItems[ row ]->mEventType ) ); }
    else if ( col == 3 )
    { return QVariant( mItems[ row ]->mAction ); }
    else if ( col == 4 )
    { return QVariant( mItems[ row ]->mbOutput ); }
    else if ( col == 5 )
    { return QVariant( mItems[ row ]->mbSaveDiagnosis ); }
    else
    { return QVariant(); }
}

bool ErrMgrModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        int col = index.column();
        int row = index.row();
        if ( col == 0 )
        { mItems[ row ]->mNr = value.toInt(); }
        else if ( index.column() == 1 )
        { mItems[ row ]->mErr = value.toString(); }
        else if ( index.column() == 2 )
        { mItems[ row ]->mEventType = (e_event_type)value.toInt(); }
        else if ( index.column() == 3 )
        { mItems[ row ]->mAction = (e_event_action)value.toInt(); }
        else if( index.column() == 4 )
        { mItems[ row ]->mbOutput = value.toInt() > 0 ; }
        else if ( index.column() == 5 )
        { mItems[ row ]->mbSaveDiagnosis = value.toInt() > 0; }
        else
        {}

        emit dataChanged(index, index);

        return true;
    }
    else
    {
        return false;
    }
}
Qt::ItemFlags ErrMgrModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
          return Qt::ItemIsEnabled;

    //! \todo for other columns
    Qt::ItemFlag flag = Qt::NoItemFlags;
    if( index.column() == 0
        || index.column() == 1 )
    {}
    else
    {}

    return QAbstractItemModel::flags(index) | flag;
}

bool ErrMgrModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    if ( position < 0 || rows < 0 )
    { return false; }

    beginInsertRows(QModelIndex(), position, position+rows-1);

    ErrMgrItem *pItem;
    for (int row = 0; row < rows; ++row)
    {
        pItem = new ErrMgrItem();
        mItems.insert( position+row, pItem );
    }

    endInsertRows();
    return true;
}
bool ErrMgrModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    if ( position < 0 || rows < 1 )
    { return false; }

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row)
    {
        delete mItems[position];
        mItems.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QVariant ErrMgrModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
    if ( role != Qt::DisplayRole )
    { return QVariant(); }

    if ( orientation == Qt::Horizontal )
    { return QVariant( ErrMgrItem::header(section)); }
    else
    { return QVariant(section);}
}

QList< ErrMgrItem *> *ErrMgrModel::items()
{
    return &mItems;
}

int ErrMgrModel::save( const QString &fileName )
{
    QFile fileOut( fileName );

    if ( !fileOut.open( QIODevice::WriteOnly) )
    { return -1; }

    QXmlStreamWriter writer( &fileOut );

    int ret;

    writer.writeStartDocument();

    writer.writeStartElement("event");

    ret = serialOut( writer );

    writer.writeEndElement();

    writer.writeEndDocument();

    fileOut.close();

    return ret;
}

int ErrMgrModel::load( const QString &fileName )
{
    //! check ver
    QFile fileIn(fileName);
    if ( !fileIn.open( QIODevice::ReadOnly) )
    { return -1; }

    QXmlStreamReader reader( &fileIn );

    int ret = 0;
    while( reader.readNextStartElement() )
    {
        if ( reader.name() == "event" )
        {
            ret = serialIn( reader );
        }
        else
        { reader.skipCurrentElement(); }
    }

    fileIn.close();

    return ret;
}

int ErrMgrModel::serialOut( QXmlStreamWriter & writer )
{
    foreach( ErrMgrItem *pAction, mItems )
    {
        Q_ASSERT( NULL != pAction );

        writer.writeStartElement( "item" );

        writer.writeTextElement( "mNr", QString::number( pAction->mNr ) );
        writer.writeTextElement( "mErr", ( pAction->mErr ) );
        writer.writeTextElement( "mEventType", QString::number( pAction->mEventType ) );
        writer.writeTextElement( "mEventAttr", QString::number( pAction->mEventAttr ) );

        writer.writeTextElement( "mAction", QString::number( pAction->mAction ) );
        writer.writeTextElement( "mActionAttr", QString::number(pAction->mActionAttr) );

        writer.writeTextElement( "mbOutput", QString::number(pAction->mbOutput) );
        writer.writeTextElement( "mbOutputAble", QString::number(pAction->mbOutputAble) );
        writer.writeTextElement( "mbSaveDiagnosis", QString::number(pAction->mbSaveDiagnosis) );

        writer.writeEndElement();
    }

    return 0;

}
int ErrMgrModel::serialIn( QXmlStreamReader & reader )
{
    //! item
    ErrMgrItem *pItem;
    QList< ErrMgrItem * > localItems;

    while( reader.readNextStartElement() )
    {
        if ( reader.name() == "item" )
        {
            pItem = new ErrMgrItem();
            Q_ASSERT( NULL != pItem );

            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "mNr" )
                { pItem->mNr = reader.readElementText().toInt(); }
                else if ( reader.name() == "mErr" )
                { pItem->mErr = reader.readElementText(); }
                else if ( reader.name() == "mEventType" )
                { pItem->mEventType = (e_event_type)reader.readElementText().toInt(); }
                else if ( reader.name() == "mEventAttr" )
                { pItem->mEventAttr = reader.readElementText().toInt(); }

                else if ( reader.name() == "mAction" )
                { pItem->mAction = (e_event_action)reader.readElementText().toInt(); }
                else if ( reader.name() == "mActionAttr" )
                { pItem->mActionAttr = reader.readElementText().toInt(); }

                else if ( reader.name() == "mbOutput" )
                { pItem->mbOutput = reader.readElementText().toInt() > 0; }
                else if ( reader.name() == "mbOutputAble" )
                { pItem->mbOutputAble = reader.readElementText().toInt() > 0; }
                else if ( reader.name() == "mbSaveDiagnosis" )
                { pItem->mbSaveDiagnosis = reader.readElementText().toInt() > 0; }

                else
                { reader.skipCurrentElement(); }
            }

            localItems.append( pItem );
        }
        else
        { reader.skipCurrentElement(); }
    }

    //! assign
    delete_all( mItems );
    mItems = localItems;

    endResetModel();

    return 0;
}

