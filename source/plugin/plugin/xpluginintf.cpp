#include "xpluginintf.h"

XPluginIntf::XPluginIntf( QObject *parent ) : QObject( parent )
{
    mVi = -1;

    mbOperateAble = true;
}

//! addr
//! model
//! sn
bool XPluginIntf::isEqual( XPluginIntf *p )
{
    return isEqual( p->addr(), p->model(), p->SN() );
}

bool XPluginIntf::isEqual( const QString &_addr,
              const QString &_model,
              const QString &_sn )
{
    if ( QString::compare( addr(), _addr, Qt::CaseInsensitive) != 0 )
    { return false; }

    if ( QString::compare( model(), _model, Qt::CaseInsensitive) != 0 )
    { return false; }

    if ( QString::compare( SN(), _sn, Qt::CaseInsensitive) != 0 )
    { return false; }

    return true;
}

//! addr,model,sn,firmwareVer,mechanicalVer
QString XPluginIntf::description()
{
    QStringList strList;

    strList<<addr()<<model()<<SN()<<firmwareVer()<<mechanicalVer();

    return strList.join(',');
}

void XPluginIntf::setOperateAble( bool b )
{
    mbOperateAble = b;

    onOperateAble( b );
}
bool XPluginIntf::operateAble()
{ return mbOperateAble; }

void XPluginIntf::onOperateAble( bool b )
{}

void XPluginIntf::setModel( const QString &model )
{ mModel = model; }
QString XPluginIntf::model()
{ return mModel; }

void XPluginIntf::setAddr( const QString &addr )
{ mAddr = addr; }
QString XPluginIntf::addr()
{ return mAddr; }

void XPluginIntf::setViewAddr( const QString &vAddr )
{ mViewAddr = vAddr; }
QString XPluginIntf::viewAddr()
{ return mViewAddr; }

void XPluginIntf::setSN( const QString &sn )
{ mSN = sn; }
QString XPluginIntf::SN()
{ return mSN; }

void XPluginIntf::setFirmwareVer( const QString &ver )
{ mFirmwareVer = ver; }
QString XPluginIntf::firmwareVer()
{ return mFirmwareVer; }

void XPluginIntf::setMechanicalVer( const QString &ver )
{ mMechanicalVer = ver; }
QString XPluginIntf::mechanicalVer()
{ return mMechanicalVer; }

int XPluginIntf::save( QXmlStreamWriter &writer )
{
    writer.writeTextElement( "model", mModel );
    writer.writeTextElement( "addr", mAddr );

    return 0;
}
int XPluginIntf::load( QXmlStreamReader &reader )
{
    while( reader.readNextStartElement() )
    {
        if ( reader.name() == "model" )
        {
            if ( mModel.length() > 0 )
            { reader.skipCurrentElement(); }
            else
            { mModel = reader.readElementText(); }
        }
        else if ( reader.name() == "addr" )
        {
            if ( mAddr.length() > 0 )
            { reader.skipCurrentElement(); }
            else
            { mAddr = reader.readElementText(); }
        }
        else
        { reader.skipCurrentElement(); }
    }

    return 0;
}

int XPluginIntf::open()
{ return -1; }
void XPluginIntf::close()
{}

int XPluginIntf::stop()
{ return 0; }

bool XPluginIntf::isOpened()
{ return ( mVi > 0 ); }

int XPluginIntf::deviceVi()
{ return mVi; }
