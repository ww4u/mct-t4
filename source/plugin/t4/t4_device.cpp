#include <float.h>
#include "t4.h"

#include "MegaGateway.h"

#include "../../../include/mystd.h"

#include "../../plugin/xpluginworkingthread.h"

#include "actiontable.h"

int MRX_T4::open()
{
    int vi;
logDbg()<<mAddr;
    vi = mrgOpenGateWay( mAddr.toLatin1().data(), 2000 );
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
    ret = mrgGetRobotDevice( self_robot_var(), deviceHandles );
    if ( ret > 16 || ret < 1 )
    { return -1; }
    mDeviceHandle = deviceHandles[0];
    sysInfo( tr("Device"), mDeviceHandle );

    //! update the angle
    float zeroAngles[4];
    ret = mrgGetRobotHomeAngle( self_robot_var(), zeroAngles );
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
        ret = mrgMRQMotorCurrent_Query( self_device_var(), i, mAxisCurrents + i );
        if ( ret != 0 )
        {
            sysError( tr("Current read fail") );
            break;
        }
    }

    //! \note
    //! \todo
    //! config the data
    for ( int i = 0; i < T4Para::_axis_cnt; i++ )
    {
       ret = mrgMRQReportState( self_device_var(), i, 0, 1 );
       if ( ret != 0 )
       {
           sysError( tr("Data report state fail") );
           break;
       }

       ret = mrgMRQReportPeriod( self_device_var(), i, 0, 1000 );
       if ( ret != 0 )
       {
           sysError( tr("Data report state fail") );
           break;
       }

//       ret = mrgMRQReportState( self_device_var(), i, 0, 0 );
//       if ( ret != 0 )
//       {
//           sysError( tr("Data report state fail") );
//           break;
//       }
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
    //! stop working
    m_pMissionWorking->requestInterruption();
    m_pMissionWorking->wait();

    int ret = mrgSysSetEmergencyStop( mVi, 1 );
    if ( ret != 0 )
    { sysError( tr("Stop fail") );}

    //! request the upload

//    post_setting( )

    return 0;
}

void MRX_T4::rst()
{
    rstRecordTable();

    rstErrorMgrTable();

    T4Para::rst();

    emit_setting_changed( XPage::e_setting_update_ui, true );

    //! update ui
    slot_save_setting();
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
        sysProgress( "Uploading...", true, i++ );

        Q_ASSERT( NULL != pWig );
        pPage = dynamic_cast<XPage*>( pWig );
        if ( NULL != pPage )
        {
            //! upload
            ret = pPage->upload();
            if ( ret != 0 )
            {
                logDbg()<<pPage->objectName();
                sysError( tr("Upload fail") );
                //! \todo
//                return ret;
                return 0;
            }

            //! update data
            if ( ret == 0 )
            { pPage->updateData(); }
        }
    }

    return 0;
}

int MRX_T4::uploadProc()
{
    int ret;

    sysProgress( "Uploading...", true, 0 );

    ret = _uploadProc();

    //! save
    if ( ret == 0 )
    { slot_save_setting(); }

    sysProgress( "Uploading...", false );

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

int MRX_T4::onStop( QVariant var )
{
    return 0;
}

int MRX_T4::robotHandle()
{ return mRobotHandle; }

int MRX_T4::deviceHandle()
{ return mDeviceHandle; }

//!
int MRX_T4::currentRecordIndex()
{
    Q_ASSERT( NULL != m_pRecordView );

    return m_pRecordView->currentIndex();
}

double MRX_T4::eulaDistance( double x, double y, double z,
                            double x1, double y1, double z1 )
{
    //! calc the distance
    double dist = sqrt( pow(  x - x1, 2) +
                       pow(  y - y1, 2) +
                       pow(  z - z1, 2)
                       );
    return dist;
}

int MRX_T4::relMove( QString para,
             double x, double y, double z,
             double pw, double h,
             double v, bool bLine )
{logDbg();
    self_check_connect_ret( -1 );

    int ret;

    //! calc the distance
    double dist = eulaDistance( 0,0,0,
                                x, y, z
                                );
    if ( dist < distance_error )
    { return 0; }

    Q_ASSERT( v > 0 );
    float t = qAbs( dist ) / v;

    logDbg()<<x<<y<<z<<t<<guess_dist_time_ms( t, dist );
    if ( bLine )
    {
        ret = mrgRobotRelMoveL( self_robot_var(),
                          wave_table,
                          x,
                          y,
                          z,
                          t,
                          guess_dist_time_ms( t, dist )
                          );
    }
    else
    {
        ret = mrgRobotRelMove( self_robot_var(),
                               wave_table,
                               x,
                               y,
                               z,
                               t,
                               guess_dist_time_ms( t, dist )
                               );
    }

    return ret;
}

int MRX_T4::absMove( QString para,
             double x, double y, double z,
             double pw, double h,
             double v, bool bLine )
{
    self_check_connect_ret( -1 );

    //! get remote pos
    int ret;
    float xn,yn,zn;
    ret = mrgGetRobotCurrentPosition( self_robot_var(),
                                      &xn, &yn, &zn );
    if ( ret != 0 )
    {
        sysError( tr("Position read fail") );
        return -1;
    }

    //! calc the distance
    double dist = eulaDistance( xn,yn,zn,
                                x, y, z
                                );

    //! \note distance error
    if ( dist < distance_error )
    { return 0; }

    Q_ASSERT( v > 0 );

    float t = qAbs( dist ) / v;

    logDbg()<<x<<y<<z<<t<<guess_dist_time_ms( t, dist );

    if ( bLine )
    {
        ret = mrgRobotMoveL( self_robot_var(),
                             wave_table,
                             x,
                             y,
                             z,
                             t,
                             guess_dist_time_ms( v, dist )
                             );
    }
    else
    {
        ret = mrgRobotMove( self_robot_var(),
                               wave_table,
                               x,
                               y,
                               z,
                               t,
                               guess_dist_time_ms( v, dist )
                               );
    }

    return ret;
}

