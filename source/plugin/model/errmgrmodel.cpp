#include <QFile>
#include "../../../include/mystd.h"
#include "errmgrmodel.h"

QString ErrorMgrItem::encode( bool b )
{ return b ? "11" : "10"; }
bool ErrorMgrItem::decode( const QString &str )
{
    if ( str=="10" )
    { return false; }
    else
    { return true; }
}

ErrorMgrItem::ErrorMgrItem()
{ }

void ErrorMgrItem::setOutput( bool b )
{ mOutput=encode(b); }
bool ErrorMgrItem::getOutput()
{ return decode(mOutput); }
bool ErrorMgrItem::isOutputAble()
{ return mOutput != "00"; }

void ErrorMgrItem::setLed( bool b )
{ mLed=encode(b); }
bool ErrorMgrItem::getLed()
{ return decode(mLed); }
bool ErrorMgrItem::isLedAble()
{ return mLed != "00" ; }

ErrorMgrModel::ErrorMgrModel() : MegaTableModel()
{
    mHeaderList<<QObject::tr("No.")
               <<QObject::tr("Error Text")
               <<QObject::tr("Type")
               <<QObject::tr("Reason")
               <<QObject::tr("Action")
               <<QObject::tr("Output stage on")
               <<QObject::tr("Blink");
}

ErrorMgrModel::~ErrorMgrModel()
{
    qDeleteAll( mItems );
}

int ErrorMgrModel::rowCount(const QModelIndex &parent) const
{ return mItems.count(); }
int ErrorMgrModel::columnCount(const QModelIndex &parent) const
{ return mHeaderList.size(); }

QVariant ErrorMgrModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
    { return QVariant(); }

    //! index
    int col = index.column();
    int row = index.row();

    //! visible
    if ( role == Qt::UserRole )
    {
        if ( col == 5 )
        { return mItems.at(row)->isOutputAble(); }
        else if ( col == 6 )
        { return mItems.at(row)->isLedAble(); }
        else
        { return QVariant(); }
    }

    if ( role == Qt::DisplayRole )
    {
        if ( col == 0 )
        { return mItems.at( row )->mCode; }
        else if ( col == 1 )
        { return mItems.at(row)->mBrief[0]; }
        else if ( col == 2 )
        { return mItems.at(row)->mType; }
        else if ( col == 3 )
        { return mItems.at(row)->mReason[0]; }
        else if ( col == 4 )
        { return mItems.at(row)->mAction; }
        else
        { }
    }

    if ( role == Qt::DisplayRole
         || role == Qt::EditRole )
    {
        if ( col == 5 )
        {
            if ( mItems.at(row)->isOutputAble() )
            {}
            else
            { return QVariant(); }

            return mItems.at( row )->decode( mItems.at(row)->mOutput );
        }
        else if ( col == 6 )
        {
            if ( mItems.at(row)->isLedAble() )
            {}
            else
            { return QVariant(); }

            return mItems.at( row )->decode( mItems.at(row)->mLed );
        }
        else
        {}
    }

    return QVariant();
}

bool ErrorMgrModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int col = index.column();
    int row = index.row();

    if (index.isValid() && role == Qt::EditRole)
    {
        if ( col == 5 )
        { mItems[row]->setOutput( value.toBool() );}
        else if ( col == 6 )
        { mItems[row]->setLed( value.toBool() );}
        else
        { return false; }

        emit dataChanged(index, index);

        return true;
    }
    else
    {
        return false;
    }
}

#define enable_flags( b )   b ? ( Qt::ItemIsSelectable \
                                  | Qt::ItemIsEditable \
                                  | Qt::ItemIsEnabled \
                                    ) : ( Qt::NoItemFlags )
Qt::ItemFlags ErrorMgrModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
          return Qt::ItemIsEnabled;

    if ( index.isValid() )
    {}
    else
    { return Qt::NoItemFlags; }

    int col = index.column();
    int row = index.row();

    if ( col == 5 )
    {
        return enable_flags ( mItems.at(row)->isOutputAble() );
    }
    else if ( col == 6 )
    {
        return enable_flags ( mItems.at(row)->isLedAble() );
    }
    else
    {}

    return Qt::NoItemFlags;
}

//bool ErrorMgrModel::insertRows(int position, int rows, const QModelIndex &parent)
//{
//    if ( position < 0 || rows < 0 )
//    { return false; }

//    beginInsertRows(QModelIndex(), position, position+rows-1);

//    ErrorMgrItem *pItem;
//    for (int row = 0; row < rows; ++row)
//    {
//        pItem = new ErrorMgrItem();
//        mItems.insert( position+row, pItem );
//    }

//    endInsertRows();
//    return true;
//}
//bool ErrorMgrModel::removeRows(int position, int rows, const QModelIndex &parent)
//{
//    if ( position < 0 || rows < 1 )
//    { return false; }

//    beginRemoveRows(QModelIndex(), position, position+rows-1);

//    for (int row = 0; row < rows; ++row)
//    {
//        delete mItems[position];
//        mItems.removeAt(position);
//    }

//    endRemoveRows();
//    return true;
//}

QVariant ErrorMgrModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
    if ( role != Qt::DisplayRole )
    { return QVariant(); }

    if ( orientation == Qt::Horizontal )
    { return QVariant( mHeaderList.at(section) ); }
    else
    { return QVariant(section);}
}

//#define role_visible( b )   QVariant(b)
//QVariant ErrorMgrModel::userRole_Visible( const QModelIndex &index ) const
//{
//    if ( !index.isValid() )
//    { return QVariant(); }

//    //! index
//    int col = index.column();
//    int row = index.row();

//    if ( col == 2 )
//    { return role_visible(mItems[row]->mbErrorAble); }
//    else if ( col == 3 )
//    { return role_visible(mItems[row]->mbWarnAble); }
//    else if ( col == 4 )
//    { return role_visible(mItems[row]->mbInfoAble); }
//    else if ( col == 5 )
//    {
//        return role_visible( mItems[row]->mbActionAble );
////        return role_visible(mItems[row]->mActionList.size() > 0 );
//    }
//    else if ( col == 6 )
//    { return role_visible(mItems[row]->mbOutputAble); }
//    else if ( col == 7 )
//    {return role_visible(mItems[row]->mbSaveAble); }
//    else
//    { return QVariant(); }
//}

//#define back_role( b )  if ( b ){}else{ break; }
//QVariant ErrorMgrModel::backRole( const QModelIndex &index ) const
//{
//    if ( !index.isValid() )
//    { return QVariant(); }

//    //! index
//    int col = index.column();
//    int row = index.row();

//    do
//    {
//        if ( col == 2 )
//        {  back_role(mItems[row]->mbErrorAble); }
//        else if ( col == 3 )
//        {  back_role(mItems[row]->mbWarnAble); }
//        else if ( col == 4 )
//        {  back_role(mItems[row]->mbInfoAble); }
//        else if ( col == 5 )
//        {
//            back_role(mItems[row]->mbActionAble );
//        }
//        else if ( col == 6 )
//        {  back_role(mItems[row]->mbOutputAble); }
//        else if ( col == 7 )
//        {  back_role(mItems[row]->mbSaveAble); }
//        else
//        { return QVariant(); }

//        //! default
//        return QVariant();
//    }while ( 0 );

//    //! disabled
//    return QVariant( QColor( Qt::darkGray ) );
//}

QList< ErrorMgrItem *> *ErrorMgrModel::items()
{
    return &mItems;
}

//int ErrorMgrModel::save( const QString &fileName )
//{
//    QFile fileOut( fileName );

//    if ( !fileOut.open( QIODevice::WriteOnly) )
//    { return -1; }

//    QXmlStreamWriter writer( &fileOut );

//    int ret;

//    writer.writeStartDocument();

//    writer.writeStartElement("event");

//    ret = serialOut( writer );

//    writer.writeEndElement();

//    writer.writeEndDocument();

//    fileOut.close();

//    return ret;
//}

int ErrorMgrModel::load( const QString &fileName )
{
    //! check ver
    QFile fileIn(fileName);
    if ( !fileIn.open( QIODevice::ReadOnly) )
    { return -1; }

    QByteArray ary = fileIn.readAll();

    fileIn.close();

    return load( ary );
}

int ErrorMgrModel::load( QByteArray &ary )
{
//    QXmlStreamReader reader( ary );

//    int ret = 0;
//    while( reader.readNextStartElement() )
//    {
//        if ( reader.name() == "event" )
//        {
//            ret = serialIn( reader );
//        }
//        else
//        { reader.skipCurrentElement(); }
//    }

    QTextStream stream( ary, QIODevice::ReadOnly );

    int ret = serialIn( stream );

    return ret;
}

//int ErrorMgrModel::serialOut( QXmlStreamWriter & writer )
//{
//    foreach( ErrorMgrItem *pAction, mItems )
//    {
//        Q_ASSERT( NULL != pAction );

//        writer.writeStartElement( "item" );

//        writer.writeTextElement( "mNr", QString::number( pAction->mNr ) );
//        writer.writeTextElement( "mErr", ( pAction->mErr ) );
//        writer.writeTextElement( "mEventType", QString::number( pAction->mEventType ) );

//        writer.writeTextElement( "mbErrorAble", QString::number( pAction->mbErrorAble ) );
//        writer.writeTextElement( "mbWarnAble", QString::number( pAction->mbWarnAble ) );
//        writer.writeTextElement( "mbInfoAble", QString::number( pAction->mbInfoAble ) );

//        writer.writeTextElement( "mAction", ( pAction->mAction ) );
//        writer.writeTextElement( "mActionList", pAction->mActionList.join(';') );

//        writer.writeTextElement( "mbOutput", QString::number(pAction->mbOutput) );
//        writer.writeTextElement( "mbOutputAble", QString::number(pAction->mbOutputAble) );
//        writer.writeTextElement( "mbSaveDiagnosis", QString::number(pAction->mbSaveDiagnosis) );
//        writer.writeTextElement( "mbSaveAble", QString::number(pAction->mbSaveAble) );

//        writer.writeEndElement();
//    }

//    return 0;

//}
//int ErrorMgrModel::serialIn( QXmlStreamReader & reader )
//{
//    //! item
//    ErrorMgrItem *pItem;
//    QList< ErrorMgrItem * > localItems;

//    while( reader.readNextStartElement() )
//    {
//        if ( reader.name() == "item" )
//        {
//            pItem = new ErrorMgrItem();
//            Q_ASSERT( NULL != pItem );

//            while( reader.readNextStartElement() )
//            {
//                if ( reader.name() == "mNr" )
//                { pItem->mNr = reader.readElementText().toInt(); }
//                else if ( reader.name() == "mErr" )
//                { pItem->mErr = reader.readElementText(); }
//                else if ( reader.name() == "mEventType" )
//                { pItem->mEventType = (ErrorMgrItem::e_event_type)reader.readElementText().toInt(); }

//                else if ( reader.name() == "mbErrorAble" )
//                { pItem->mbErrorAble = reader.readElementText().toInt() > 0; }
//                else if ( reader.name() == "mbWarnAble" )
//                { pItem->mbWarnAble = reader.readElementText().toInt() > 0; }
//                else if ( reader.name() == "mbInfoAble" )
//                { pItem->mbInfoAble = reader.readElementText().toInt() > 0; }

//                else if ( reader.name() == "mAction" )
//                { pItem->mAction = reader.readElementText(); }
//                else if ( reader.name() == "mActionList" )
//                {
//                    QStringList strList = reader.readElementText().split( ';', QString::SkipEmptyParts );
//                    foreach( const QString &subStr, strList )
//                    {
//                        pItem->mActionList<< subStr.trimmed();
//                    }
//                }
//                else if ( reader.name() == "mbOutput" )
//                { pItem->mbOutput = reader.readElementText().toInt() > 0; }
//                else if ( reader.name() == "mbOutputAble" )
//                { pItem->mbOutputAble = reader.readElementText().toInt() > 0; }
//                else if ( reader.name() == "mbSaveDiagnosis" )
//                { pItem->mbSaveDiagnosis = reader.readElementText().toInt() > 0; }
//                else if ( reader.name() == "mbSaveAble" )
//                { pItem->mbSaveAble = reader.readElementText().toInt() > 0; }
//                else
//                { reader.skipCurrentElement(); }

//                if(pItem->mActionList.size() > 1)
//                {pItem->mbActionAble = true; }
//                else
//                {pItem->mbActionAble = false; }
//            }

//            localItems.append( pItem );
//        }
//        else
//        { reader.skipCurrentElement(); }
//    }

//    //! assign
//    delete_all( mItems );
//    mItems = localItems;

//    endResetModel();

//    return 0;
//}

#define output_item( item )    writer<<item##Key<<item<<endl;
#define output_items(  items  ) Q_ASSERT( items.size() == items##Key.size() );\
                                for ( int i = 0; i < items.size(); i++ )\
                                {  \
                                    writer<<items##Key.at(i)<<items.at(i)<<endl;\
                                }
int ErrorMgrModel::serialOut( QTextStream & writer )
{
    foreach( ErrorMgrItem *pItem, mItems )
    {
        writer<<"################"<<endl;
        output_item( pItem->mCode );
        output_item( pItem->mType );

        output_items( pItem->mBrief );
        output_items( pItem->mReason );
        output_items( pItem->mDetail );

        output_item( pItem->mAction );
        output_item( pItem->mOutput );

        output_item( pItem->mLed );
    }

    return 0;
}

#define cat_items( tItem ) \
    kvlist = lineStr.split( ":", QString::SkipEmptyParts );\
if ( kvlist.size() == 2 )\
{\
    tItem##Key.append( kvlist.at(0) );\
    tItem.append( kvlist.at(1));\
}\
else\
{\
    tItem##Key.append( lineStr );\
    tItem.append("");\
}

#define assign_item( tItem ) \
    kvlist = lineStr.split( ":", QString::SkipEmptyParts );\
if ( kvlist.size() == 2 )\
{\
    tItem##Key = kvlist.at(0);\
    tItem = kvlist.at(1);\
}\
else\
{\
    tItem##Key = lineStr;\
}

int ErrorMgrModel::serialIn( QTextStream & reader )
{
    //! item
    ErrorMgrItem *pItem = NULL;
    QList< ErrorMgrItem * > localItems;

    QString lineStr;
    QStringList kvlist;

    while( !reader.atEnd() )
    {
        lineStr = reader.readLine();
        lineStr.trimmed();

        //! deparse the item
        if ( lineStr.startsWith("#") )
        { continue; }

        if ( lineStr.startsWith("[code]:") )
        {
            pItem = new ErrorMgrItem();
            //! add item
            if ( NULL == pItem )
            {
                delete_all( localItems );
                return -1;
            }
            localItems.append( pItem );

            assign_item( pItem->mCode );

        }
        else if ( lineStr.startsWith("[brief]") )
        {
            cat_items( pItem->mBrief );
        }
        else if ( lineStr.startsWith("[reason]") )
        {
            cat_items( pItem->mReason );
        }
        else if ( lineStr.startsWith("[handle]") )
        {
            assign_item( pItem->mAction );
        }
        else if ( lineStr.startsWith("[detail]") )
        {
            cat_items( pItem->mDetail );
        }
        else if ( lineStr.startsWith("[level]") )
        {
            cat_items( pItem->mType );
        }
        else if ( lineStr.startsWith("[response]") )
        {
            assign_item( pItem->mOutput );
        }
        else if ( lineStr.startsWith("[led]") )
        {
            assign_item( pItem->mLed );
        }
        else
        {}
    }

    //! assign
    delete_all( mItems );
    mItems = localItems;

    endResetModel();

    return 0;
}

//void ErrMgrModel::createDebug()
//{
//    ErrMgrItem *pItem;

//    pItem = new ErrMgrItem();
//    pItem->mNr = 1;
//    pItem->mErr = "hello";

//    pItem->mEventType = e_error;

//    pItem->mbOutput = true;
//    pItem->mbOutputAble = true;
//    pItem->mbSaveDiagnosis = true;

//    mItems.append( pItem );
//}
