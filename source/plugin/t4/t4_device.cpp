
#include "t4.cpp"
#include "../../device/MegaGateway.h"
#include "../../../include/mystd.h"
int MRX_T4::open()
{
    int vi;
logDbg()<<mAddr;
    vi = mrgOpenGateWay( mAddr.toLatin1().data(), 500 );

    if ( vi > 0 )
    {
        mVi = vi;

        //! changed
        emit_setting_changed( XPage::e_setting_opened, true );
    }
    else
    {
        emit_setting_changed( XPage::e_setting_opened, false );
        return -1;
    }

    //! get robot handle
    int names[16];
    int ret;

    //! \todo names overflow
    ret = mrgGetRobotName( mVi, names );
    if ( ret > 16 || ret < 1 )
    { return -1; }

    mRobotHandle = names[0];
    sysInfo( tr("Robot"), mRobotHandle );

    //! device handle
    int deviceHandles[16];
    ret = mrgGetRobotDevice( mVi, mRobotHandle, deviceHandles );
    if ( ret > 16 || ret < 1 )
    { return -1; }
    mDeviceHandle = deviceHandles[0];
    sysInfo( tr("Device"), mDeviceHandle );

    //! update the angle
    float zeroAngles[4];
    ret = mrgGetRobotHomeAngle( mVi, mRobotHandle, zeroAngles );
    if ( ret < 0 )
    { sysError( tr("Zero Angle update fail") ); }
    else
    {
        for ( int i = 0; i < ret && i < T4Para::_axis_cnt; i++ )
        { mAxisZero[ i ] = zeroAngles[ i ]; }
    }

    //! update the current
    for ( int i = 0; i < T4Para::_axis_cnt; i++ )
    {
        ret = mrgMRQMotorCurrent_Query( mVi, mDeviceHandle, i, mAxisCurrents + i );
        if ( ret != 0 )
        {
            sysError( tr("Current read fail") );
            break;
        }
    }

    return 0;
}
void MRX_T4::close()
{
    lockWorking();
        if ( mVi > 0 )
        {
            mrgCloseGateWay( mVi);
            mVi = -1;
        }
        else
        {}
    unlockWorking();

    emit_setting_changed( XPage::e_setting_opened, false );
}

int MRX_T4::stop()
{
    //! \todo
    return 0;
}

int MRX_T4::upload()
{
    attachBgWorking( (XPlugin::bgProc)(&MRX_T4::uploadProc) );
    return 0;
}
int MRX_T4::download()
{
    attachBgWorking( (XPlugin::bgProc)(&MRX_T4::downloadProc) );
    return 0;
}
int MRX_T4::diff()
{
    attachBgWorking( (XPlugin::bgProc)(&MRX_T4::diffProc) );
    return 0;
}

int MRX_T4::_uploadProc()
{
    //! foeach pages
    int ret;
    XPage *pPage;
    int i = 0;
    foreach( QWidget *pWig, mPluginWidgets )
    {
        sysProgress( "Downloading...", true, i++ );

        Q_ASSERT( NULL != pWig );
        pPage = dynamic_cast<XPage*>( pWig );
        if ( NULL != pPage )
        {
            ret = pPage->upload();
            if ( ret != 0 )
            {
                logDbg()<<pPage->objectName();
                sysError( tr("Upload fail") );
                return ret;
            }
        }
    }

    return 0;
}

int MRX_T4::uploadProc()
{
    int ret;

    sysProgress( "Downloading...", true, 0 );

    ret = _uploadProc();

    sysProgress( "Downloading...", false );

    return 0;
}

int MRX_T4::_downloadProc()
{
    int ret;
    XPage *pPage;
    int i = 0;
    foreach( QWidget *pWig, mPluginWidgets )
    {
        sysProgress( "Downloading...", true, i++ );

        Q_ASSERT( NULL != pWig );
        pPage = dynamic_cast<XPage*>( pWig );
        if ( NULL != pPage )
        {
            ret = pPage->download();
            if ( ret != 0 )
            {
                logDbg()<<pPage->objectName();
                sysError( tr("Download fail") );
                return ret;
            }
        }
    }
    return 0;
}
int MRX_T4::downloadProc()
{
    int ret;

    sysProgress( "Downloading...", true, 0 );

    ret = _downloadProc();

    sysProgress( "Downloading...", false );

    return 0;
}

int MRX_T4::_diffProc()
{ return 0; }
int MRX_T4::diffProc()
{
    //! \todo
    return 0;
}

int MRX_T4::robotHandle()
{ return mRobotHandle; }

int MRX_T4::deviceHandle()
{ return mDeviceHandle; }

//!
int MRX_T4::currentRecordIndex()
{
    Q_ASSERT( NULL != m_pReccordTable );

    return m_pReccordTable->currentIndex();
}

