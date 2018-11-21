#include "MegaGateway.h"

EXPORT_API int CALL robo_getIdn(int vi, char * val)
{
    return mrgGateWayIDNQuery(vi, val);
}
EXPORT_API int CALL robo_getVersion(int vi, char * val)
{
    //return mrgGetDeviceSoftVersion(vi, val);
    return 0;
}
EXPORT_API int CALL robo_program(int vi, int ax, int page, char *name)
{
    //mrgRobotPointLoadFile(vi,ax, name);
    return mrgRobotPointResolve(vi, ax, page,0);
}
EXPORT_API int CALL robo_call(int vi, int ax, int page,int cycle,int mode)
{
    return mrgRobotRun(vi, ax, page);
}
EXPORT_API int CALL robo_run(int vi, int ax, int page)
{
    return mrgRobotRun(vi, ax, page);
}
EXPORT_API int CALL robo_stop(int vi, int ax, int page)
{
    return mrgRobotStop(vi, ax, page);
}
//等待计算完成
EXPORT_API int CALL  robo_waitEnd(int vi,int ax,int page,int timeout_ms)
{ 
    return mrgRobotWaitReady(vi, ax, page, timeout_ms);
}
EXPORT_API int CALL  robo_waitIdle(int vi, int ax, int page, int timeout_ms)
{
    return mrgRobotWaitEnd(vi, ax, page, timeout_ms);  //等待运行完成
}
EXPORT_API int CALL  robo_center(int vi, int ax, int page)
{
    return mrgRobotGoHome(vi, ax, 0);
}
EXPORT_API int CALL  Sinanju_move(int vi, int ax, int page, int mode,
    float x1, float y1, float z1, float h1,
    float x2, float y2, float z2, float h2,
    float t)
{
    mrgRobotPointClear(vi, ax);
    mrgRobotPointLoad(vi, ax, x1, y1, z1, h1, 0.0f,0);
    mrgRobotPointLoad(vi, ax, x2, y2, z2, h2, t,mode);
    mrgRobotPointResolve(vi, ax, page,0);
    mrgRobotRun(vi, ax, page);
    mrgRobotWaitEnd(vi, ax, page,0);
    return 0;
}

EXPORT_API int CALL  Sinanju_preMove(int vi, int ax, int page, int mode,
    float x1, float y1, float z1, float h1,
    float x2, float y2, float z2, float h2,
    float t)
{
    mrgRobotPointClear(vi, ax);
    mrgRobotPointLoad(vi, ax, x1, y1, z1, h1, 0.0f,0);
    mrgRobotPointLoad(vi, ax, x2, y2, z2, h2, t,mode);
    return mrgRobotPointResolve(vi, ax, page,0);
}

EXPORT_API int CALL  Sinanju_goto(int vi, int ax, int page, int mode,float x1, float y1, float z1,float t)
{
    if (mode == 0)
    {
        return mrgRobotMove(vi, ax, page,x1, y1, z1, t,-1);
    }
    else
    {
        return mrgRobotMoveL(vi, ax,page, x1, y1, z1, t,-1);
    }
}

EXPORT_API int CALL  Sinanju_stepX(int vi, int ax, int page, int mode,float d,float t)
{
    if (mode == 0)
    {
        return  mrgRobotRelMove(vi, ax, page, d, 0.0f, 0.0f, t,-1);
    }
    else
    {
        return mrgRobotRelMoveL(vi, ax, page, d, 0.0f, 0.0f, t,-1);
    }
}
EXPORT_API int CALL  Sinanju_stepY(int vi, int ax, int page, int mode,float d,float t)
{
    if (mode == 0)
    {
        return  mrgRobotRelMove(vi, ax, page, 0.0f, d, 0.0f, t,-1);
    }
    else
    {
        return mrgRobotRelMoveL(vi, ax, page, 0.0f, d, 0.0f, t,-1);
    }
}
EXPORT_API int CALL  Sinanju_stepZ(int vi, int ax, int page, int mode,float d,float t)
{
    if (mode == 0)
    {
        return  mrgRobotRelMove(vi, ax, page, 0.0f, 0.0f, d, t,-1);
    }
    else
    {
        return mrgRobotRelMoveL(vi, ax, page, 0.0f, 0.0f, d, t,-1);
    }
}
EXPORT_API int CALL  Sinanju_stepH(int vi, int ax, int page, int mode, float d,float t)
{
    return mrgRobotToolExe(vi, ax, d, t,0);
}

EXPORT_API int CALL  Sinanju_Center(int vi, int ax, int page)
{
    return robo_center(vi, ax, page);
}
EXPORT_API int CALL  Sinanju_Fold(int vi, int ax, int page)
{
    return 0; //which robot?
}
EXPORT_API int CALL  Sinanju_getPose(int vi,float *val0,float *val1,float *val2,float *val3)
{
    return 0; //which robot?
}
EXPORT_API int CALL  Sinanju_getDist(int vi,float *val0,float *val1,float *val2,float *val3)
{
    return 0; //which robot?
}
EXPORT_API int CALL  Sinanju_getRad(int vi, float *val0,float *val1,float *val2,float *val3)
{
    return 0; //which robot?
}

EXPORT_API int CALL  h2_move(ViSession vi, int ax, int page, int mode,
    float x1, float y1, 
    float x2, float y2, 
    float t)
{
    mrgRobotPointClear(vi, ax);
    mrgRobotPointLoad(vi, ax, x1, y1, 0.0f, 0.0f, 0.0f,0);
    mrgRobotPointLoad(vi, ax, x2, y2, 0.0f, 0.0, t,mode);
    mrgRobotPointResolve(vi, ax, page, 0);
    mrgRobotRun(vi, ax, page);
    mrgRobotWaitEnd(vi, ax, page, 0);
    return 0;
}
EXPORT_API int CALL  h2_getPose(int vi, float *val0, float *val1)
{
    return 0; //which robot?
}

