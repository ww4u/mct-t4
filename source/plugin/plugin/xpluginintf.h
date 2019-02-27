#ifndef XPLUGININTF_H
#define XPLUGININTF_H

#include <QObject>
#include <QtCore>

class XPluginIntf : public QObject
{
    Q_OBJECT
public:
    XPluginIntf( QObject *parent = nullptr );

public:
    bool isEqual( XPluginIntf *p );
    bool isEqual( const QString &addr,
                  const QString &model,
                  const QString &sn );

    QString description();

    void setOperateAble( bool b );
    bool operateAble();

    virtual void onOperateAble( bool b );

    void setModel( const QString &model );
    QString model();

    void setAddr( const QString &addr );
    QString addr();

    void setSN( const QString &sn );
    QString SN();

    void setFirmwareVer( const QString &ver );
    QString firmwareVer();

    void setMechanicalVer( const QString &ver );
    QString mechanicalVer();


    int save( QXmlStreamWriter &writer );
    int load( QXmlStreamReader &reader );

public:
    virtual int open();
    virtual void close();

    bool isOpened();

    int deviceVi();

protected:
    bool mbOperateAble;

    QString mModel, mAddr;
    int mVi;

    QString mSN, mFirmwareVer, mMechanicalVer;

};

#endif // XPLUGININTF_H
