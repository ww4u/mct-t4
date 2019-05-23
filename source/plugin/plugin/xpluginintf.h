#ifndef XPLUGININTF_H
#define XPLUGININTF_H

#include <QObject>
#include <QtCore>

class XPluginIntf : public QObject
{
public:
    enum ePluginAttr{
        plugin_attr_none = 0,
        plugin_attr_foldable = 1,
        plugin_attr_reboot_able = 2,
        plugin_attr_poweroff_able = 4,
    };

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

    void setOnLine( bool b );
    bool onLine();

    virtual void onOnLine( bool b );

    void setModel( const QString &model );
    QString model();

    //! internal addr
    void setAddr( const QString &addr );
    QString addr();

    //! view addr
    void setViewAddr( const QString &vAddr );
    QString viewAddr();

    void setSN( const QString &sn );
    QString SN();

    void setFirmwareVer( const QString &ver );
    QString firmwareVer();

    void setMechanicalVer( const QString &ver );
    QString mechanicalVer();

    //!
    void setType_MRQ( const QString &s ){ mType = s; }
    QString Type_MRQ(){ return  mType; }

    void setSN_MRQ( const QString &s ){ mSN_MRQ = s; }
    QString SN_MRQ(){ return mSN_MRQ; }

    void setSoftVer_MRQ( const QString &s ){ mSoftVer_MRQ = s; }
    QString SoftVer_MRQ(){ return mSoftVer_MRQ; }

    void setFirmWareHard_MRQ( const QString &s ){ mFirmWareHard_MRQ = s; }
    QString FirmWareHard_MRQ(){ return mFirmWareHard_MRQ; }

    void setFirmWareBoot_MRQ( const QString &s ){ mFirmWareHard_MRQ = s; }
    QString FirmWareBoot_MRQ(){ return mFirmWareHard_MRQ; }

    void setFirmWareFpga_MRQ( const QString &s ){ mFirmWareFpga_MRQ = s; }
    QString FirmWareFpga_MRQ(){ return mFirmWareFpga_MRQ; }

    void setDevId( const int id ){ mDevId = id; }
    int DevId(){ return mDevId; }

    int save( QXmlStreamWriter &writer );
    int load( QXmlStreamReader &reader );

public:
    virtual int open();
    virtual void close();

    virtual int stop();
    virtual int fStop();

    bool isOpened();
    bool isFoldable();
    bool isRebootable();
    bool isPowerOffable();

    virtual bool isOnLine();

    int deviceVi();

protected:
    bool mbOperateAble;
    bool mbOnLine;

    //! \note view addr for the user view
    QString mModel, mAddr, mViewAddr;
    int mVi;

    QString mSN, mFirmwareVer, mMechanicalVer;

    //! MRQ info
    QString mType, mSN_MRQ, mSoftVer_MRQ, mFirmWareHard_MRQ, mFirmWareBoot_MRQ, mFirmWareFpga_MRQ;

    ePluginAttr mAttr;
    int mDevId;

};

#endif // XPLUGININTF_H
