//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mrqDevice.h"

#define  SEND_BUF   (100)

char *change(int wavetable)
{
    char *final = NULL;
    switch (wavetable)
    {
    case 0:
        final = "MAIN";
        break;
    case 1:
        final = "SMALL";
        break;
    case 2:
        final = "P1";
        break;
    case 3:
        final = "P2";
        break;
    case 4:
        final = "P3";
        break;
    case 5:
        final = "P4";
        break;
    case 6:
        final = "P5";
        break;
    case 7:
        final = "P6";
        break;
    case 8:
        final = "P7";
        break;
    case 9:
        final = "P8";
        break;
    }
    return final;
}

/*********************** MRQ 设备操作 *******************************/
/*
*MRQ模块识别
*vi :visa设备句柄
*name：机器人
*state：识别状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQIdentify(ViSession vi, int name, int state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:IDENtify %d,%s", name, state ? "ON" : "OFF");
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
*设置运行状态是否自动上报给微控器
*vi :visa设备句柄
*name：机器人
*chan：通道索引
*state：状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionStateReport(ViSession vi, int name, int chan, int state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:STATe:REPORt %d,%d,%s", name, chan, state ? "ACTIVE" : "QUERY");
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
*查询上报状态
*vi :visa设备句柄
*name：机器人
*chan：通道索引
*robotstate:机器人的状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionStateReport_Query(ViSession vi, int name, int chan, int *state)
{
    char args[SEND_BUF];
    char ret[8];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:STATe:REPORt? %d,%d\n", name, chan);
    if ((retLen = busQuery(vi, args, strlen(args), ret, 8)) == 0) {
        return -1;
    }
    else
    {
        ret[retLen - 1] = '\0';
        *state = atoi(ret);
    }
    return 0;
}
/*
*运行指定的波表
*vi :visa设备句柄
* name: 机器人名称
*chan：通道索引
*wavetable:波表索引值，取值范围0~9
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionRun(ViSession vi, int name, int chan, int wavetable)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:STATe:RUN %d,%d,%d\n", name, chan, wavetable);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询运行状态 "ERROR"“IDLE”“LOADING”“READY”“RUNNING”“STOP”
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引值，取值范围0~9
*robotstate:机器人的状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionRunState(ViSession vi, int name, int chan, int wavetable, char *robotstate)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:STATe? %d,%d,%d\n", name, chan, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), robotstate, 10)) == 0) {
        return -1;
    }
    else
    {
        robotstate[retLen - 1] = '\0';
    }
    return 0;
}
/*
*停止指定的波表
*vi :visa设备句柄
* name: 机器人名称
*chan：设备列表 “0@512,1@512,”
*wavetable:波表索引值，取值范围0~9
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionStop(ViSession vi, int name, int chan, int wavetable)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:STOP %d,%d,%d\n", name, chan, wavetable);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*设置启动运行的触发源
*vi :visa设备句柄
* name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*source:触发源
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionTrigSource(ViSession vi, int name, int chan, char *source)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:TRIGger:SOURce %d,%d,%s\n", name, chan, source);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询启动运行触发源
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*source:触发源
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionTrigSource_Query(ViSession vi, int name, int devList, char *source)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:TRIGger:SOURce? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), source, 10)) == 0) {
        return -1;
    }
    else
    {
        source[retLen - 1] = '\0';
    }
    return 0;
}
/*
*设置电机未运动时发生位移是否上报给微控器
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionOffsetState(ViSession vi, int name, int devList, char *state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:OFFSet:STATe %d,%d,%s", name, devList, state);
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
*查询电机未运动时发生位移是否上报给微控器状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*source:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionOffsetState_Query(ViSession vi, int name, int devList, char *source)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:OFFSet:STATe? %d,%d", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), source, 10)) == 0) {
        return -1;
    }
    else
    {
        source[retLen - 1] = '\0';
    }
    return 0;
}
/*
*查询电机未运动时发生的位移
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*displace:位移
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionOffsetValue_Query(ViSession vi, int name, int devList, double *displace)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:OFFSet:VALue? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen] = '\0';
    }
    *displace = atof(state);
    return 0;
}
/*
*查询增量编码器的AB相的计数值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*返回值：AB相的计数值
*/
MEGAGATEWAY_API int CALL mrgMRQMotionABCount_Query(ViSession vi, int name, int devList)
{
    char args[SEND_BUF];
    int retLen = 0;
    if ((retLen = busQuery(vi, "DEVICE:MRQ:MOTion:ABCOUNt?\n", 27, args, 4)) == 0) {
        return 0;
    }
    else {
        args[retLen] = '\0';
        return atoi(args);
    }
}
/*
*清空增量编码器的AB相的计数值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionABCountClear(ViSession vi, int name, int devList)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:ABCOUNt:CLEAr %d,%d\n", name, devList);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*微调
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*position:位置
* time : 移动到目标位置期望使用的时间
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQAdjust(ViSession vi, int name, int devList, float position, float time)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTion:ADJust %d,%d,%f,%f\n", name, devList, position, time);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*时钟同步
*vi :visa设备句柄
*name_list:设备名列表
*time:同步的时间
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQClockSync(ViSession vi, char *name_list, float time)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:CLOCk %s,%f\n", name_list, time);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*设置电机的步距角
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*stepangle:电机的步距角
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorStepAngle(ViSession vi, int name, int devList, float stepangle)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:STEP:ANGLe %d,%d,%f\n", name, devList, stepangle);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机的步距角
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*stepangle:电机的步距角
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorStepAngle_Query(ViSession vi, int name, int devList, double *stepangle)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:STEP:ANGLe? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen] = '\0';
    }

    *stepangle = atof(state);
    return 0;
}
/*
*设置电机的运动类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorMotionType(ViSession vi, int name, int devList, char *state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:MOTion:TYPe %d,%d,%s\n", name, devList, state);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机的运动类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:运动类型
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorMotionType_Query(ViSession vi, int name, int devList, char *type)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:MOTion:TYPe? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), type, 10)) == 0) {
        return -1;
    }
    else
    {
        type[retLen] = '\0';
    }
    return 0;
}
/*
*设置电机运动时的单位
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*unit:电机运动时的单位
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorPositionUnit(ViSession vi, int name, int devList, char *unit)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:POSition:UNIT %d,%d,%s\n", name, devList, unit);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机运动时的单位
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*unit:电机运动时的单位
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorPositionUnit_Query(ViSession vi, int name, int devList, char *unit)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:POSition:UNIT? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), unit, 10)) == 0) {
        return -1;
    }
    else
    {
        unit[retLen] = '\0';
    }
    return 0;
}
/*
*设置电机旋转运动时的速比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*ratio:电机旋转运动时的速比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorGearRatio(ViSession vi, int name, int devList, int a, int b)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:GEAR:RATio %d,%d,%d:%d\n", name, devList, a, b);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机旋转运动时的速比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*ratio:电机旋转运动时的速比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorGearRatio_Query(ViSession vi, int name, int devList, char *ratio)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:GEAR:RATio? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), ratio, 100)) == 0) {
        return -1;
    }
    else
    {
        ratio[retLen - 1] = '\0';
    }
    return 0;
}
/*
*设置电机直线运动时的导程
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*millimeter:电机直线运动时的导程
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorLead(ViSession vi, int name, int devList, float millimeter)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:LEAD %d,%d,%f\n", name, devList, millimeter);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机直线运动时的导程
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*millimeter:电机直线运动时的导程
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorLead_Query(ViSession vi, int name, int devList, double *millimeter)
{
    char args[SEND_BUF];
    char state[64];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:LEAD? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 1024)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *millimeter = atof(state);
    return 0;
}
/*
*设置电机的尺寸
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*size:电机的尺寸
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorSize(ViSession vi, int name, int devList, int size)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:SIZE %d,%d,%d\n", name, devList, size);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机的尺寸
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*size:电机的尺寸
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorSize_Query(ViSession vi, int name, int devList, int *size)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:SIZE? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen] = '\0';
    }

    *size = atoi(state);
    return 0;
}
/*
*设置电机的额定电压
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*volt:电压值
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorVoltate(ViSession vi, int name, int devList, int volt)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:VOLTage %d,%d,%d\n", name, devList, volt);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机的额定电压
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*volt:电压值
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorVoltage_Query(ViSession vi, int name, int devList, int *volt)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:VOLTage? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *volt = atoi(state);
    return 0;

}
/*
*设置电机的额定电流
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*current:额定电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorCurrent(ViSession vi, int name, int devList, double current)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:CURRent %d,%d,%f\n", name, devList, current);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机的额定电流
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*current:额定电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorCurrent_Query(ViSession vi, int name, int devList, double *current)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:CURRent? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 1024)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *current = atof(state);
    return 0;
}
/*
*设置电机的反向间隙
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*lash:电机的反向间隙
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorBackLash(ViSession vi, int name, int devList, double lash)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:BACKLash %d,%d,%f\n", name, devList, lash);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机的反向间隙
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*lash:电机的反向间隙
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorBackLash_Query(ViSession vi, int name, int devList, double *lash)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:MOTOR:BACKLash? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *lash = atof(state);
    return 0;
}
/*
*PVT配置命令
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state:PVT 的配置状态： END 或 CLEAR
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTConfig(ViSession vi, int name, int devList, int wavetable, char *state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:CONFig %d,%d,%d,%s\n", name, devList, wavetable, state);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*下发PVT
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*p:PVT 点的位置
*v:PVT 点的速度
*t:PVT 点的时间值
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTValue(ViSession vi, int name, int devList, int wavetable, float p, float v, float t)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:VALue %d,%d,%d,%f,%f,%f\n", name, devList, wavetable, p, v, t);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询当前PVT下发的状态 "ERROR"“IDLE”“LOADING”“READY”
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state1:PVT下发的状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTState_Query(ViSession vi, int name, int devList, int wavetable, char *state1)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:STATe? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    state1 = state;
    return 0;
}
/*
*设置S曲线的加减速占比，两段一起，千分之
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*speedup:加速占比
*speedcut:加速占比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTTimeScale(ViSession vi, int name, int devList, int wavetable, float speedup, float speedcut)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:TSCale %d,%d,%d,%f,%f\n", name, devList, wavetable, speedup, speedcut);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询模式,包括执行模式,规划模式,运动模式
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeConfig_Query(ViSession vi, int name, int devList, int wavetable, char *pattern)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODe:CONFig? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    pattern = state;
    return 0;
}
/*
*设置模式,包括执行模式,规划模式,运动模式
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*exe:执行模式： CYCLE、或 FIFO
*plan:轨迹规划方式： CUBICPOLY、 TRAPEZOID、或 SCURVE
*motion:运动模式： PVT、 LVT_CORRECT 或 LVT_NOCORRECT
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeConfig(ViSession vi, int name, int devList, int wavetable, char *exe, char *plan, char *motion)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODe:CONFig %d,%d,%d,%s,%s,%s\n", name, devList, wavetable, exe, plan, motion);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*设置执行模式,循环或者FIFO
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeExe(ViSession vi, int name, int devList, int wavetable, char *pattern)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODe:EXE %d,%d,%d,%s\n", name, devList, wavetable, pattern);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询执行模式,循环或者FIFO
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeExe_Query(ViSession vi, int name, int devList, int wavetable, char *pattern)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODe:EXE? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    pattern = state;
    return 0;
}
/*
*设置规划模式:三次插值,线性插值,梯形插值,或五次插值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModePlan(ViSession vi, int name, int devList, int wavetable, char *pattern)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODe:PLAN %d,%d,%d,%s\n", name, devList, wavetable, pattern);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询规划模式:三次插值,线性插值,梯形插值,或五次插值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModePlan_Query(ViSession vi, int name, int devList, int wavetable, char *pattern)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODe:PLAN? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    pattern = state;
    return 0;
}
/*
*设置运动模式:PVT或者LVT
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeMotion(ViSession vi, int name, int devList, int wavetable, char *pattern)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODe:MOTion %d,%d,%d,%s\n", name, devList, wavetable, pattern);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询运动模式:PVT或者LVT
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeMotion_Query(ViSession vi, int name, int devList, int wavetable, char *pattern)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODe:MOTion? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    pattern = state;
    return 0;
}
/*
*设置LVT模式下进行时间调整的占比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*duty:占空比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModifyDuty(ViSession vi, int name, int devList, int wavetable, float duty)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODIFy:DUTY %d,%d,%d,%f\n", name, devList, wavetable, duty);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询LVT模式下进行时间调整的占比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*duty:占空比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModifyDuty_Query(ViSession vi, int name, int devList, int wavetable, double *duty)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:MODIFy:DUTY? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *duty = atof(state);
    return 0;
}
/*
*设置是否为速度保持
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTEndState(ViSession vi, int name, int devList, int wavetable, char *pattern)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:END:STATe %d,%d,%d,%s\n", name, devList, wavetable, pattern);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询是否为速度保持
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTEndState_Query(ViSession vi, int name, int devList, int wavetable, char *pattern)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:END:STATe? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    pattern = state;
    return 0;
}
/*
*设置S曲线的加减速占比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*scale:加速度占比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTDecScale(ViSession vi, int name, int devList, int wavetable, float scale)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:ADEC:SCALe %d,%d,%d,%f\n", name, devList, wavetable, scale);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询S曲线的加减速占比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*scale:加速度占比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTDecScale_Query(ViSession vi, int name, int devList, int wavetable, double *scale)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:ADEC:SCALe? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *scale = atof(state);
    return 0;
}
/*
*设置急停方式,立即停止或者减速停止
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*way:急停方式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopMode(ViSession vi, int name, int devList, int wavetable, char *way)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:STOP:MODe %d,%d,%d,%s\n", name, devList, wavetable, way);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询急停方式,立即停止或者减速停止
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*way:急停方式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopMode_Query(ViSession vi, int name, int devList, int wavetable, char *way)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:STOP:MODe? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    way = state;
    return 0;
}
/*
*设置急停时间
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*time:急停的时间
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopTime(ViSession vi, int name, int devList, int wavetable, float time)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:STOP:TIMe %d,%d,%d,%f\n", name, devList, wavetable, time);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询急停时间
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*time:急停的时间
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopTime_Query(ViSession vi, int name, int devList, int wavetable, double *time)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:STOP:TIMe? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *time = atof(state);
    return 0;
}
/*
*设置减速停止时的减速距离
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*distance:减速距离
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopDistance(ViSession vi, int name, int devList, int wavetable, float distance)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:STOP:DISTance %d,%d,%d,%f\n", name, devList, wavetable, distance);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询减速停止时的减速距离
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*distance:减速距离
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopDistance_Query(ViSession vi, int name, int devList, int  wavetable, double *distance)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:PVT:STOP:DISTance? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *distance = atof(state);
    return 0;
}
/*
*查询失步的状态,阈值及失步后的反应
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state1:失步的状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepLineConfig_Query(ViSession vi, int name, int devList, int wavetable, char *state1)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:LOSTstep:LINe:CONFig? %d,%d,%s\n", name, devList, change(wavetable));
    if ((retLen = busQuery(vi, args, strlen(args), state1, 64)) == 0) {
        return -1;
    }
    else
    {
        state1[retLen - 1] = '\0';
    }
    return 0;
}
/*
*设置失步的状态,阈值及失步后的反应
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state:失步的告警状态
*threshold:失步的阈值
*resp:编码器步数偏差超过阈值后的响应方式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepLineConfig(ViSession vi, int name, int devList, int wavetable, char *state, double threshold, char *resp)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:LOSTstep:LINe:CONFig %d,%d,%s,%s,%f,%s\n", name, devList, change(wavetable), state, threshold, resp);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*设置线间失步告警状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state:警告状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL DeviceMRQLostStepState(ViSession vi, int name, int devList, int wavetable, char *state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:LOSTstep:LINe:STATe %d,%d,%d,%s\n", name, devList, wavetable, state);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询线间失步告警状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state:警告状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL DeviceMRQLostStepState_Query(ViSession vi, int name, int devList, int wavetable, char *state1)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:LOSTstep:LINe:STATe? %d,%d,%d\n", name, devList, wavetable);
    if ((retLen = busQuery(vi, args, strlen(args), state1, 10)) == 0) {
        return -1;
    }
    else
    {
        state1[retLen - 1] = '\0';
    }
    return 0;
}
/*
*设置线间失步阈值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*value:线间失步阈值
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepThreshold(ViSession vi, int name, int devList, int wavetable, double value)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:LOSTstep:LINe:THREShold %d,%d,%s,%f\n", name, devList, change(wavetable), value);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询线间失步阈值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*value:线间失步阈值
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepThreshold_Query(ViSession vi, int name, int devList, int wavetable, double *value)
{
    char args[SEND_BUF];
    char state[64];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:LOSTstep:LINe:THREShold? %d,%d,%s\n", name, devList, change(wavetable));
    if ((retLen = busQuery(vi, args, strlen(args), state, 1024)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *value = atof(state);
    return 0;
}
/*
*设置当步数偏差超过LOSTNUM后的响应方式
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepResponse(ViSession vi, int name, int devList, int wavetable, char *state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:LOSTstep:LINe:RESPonse %d,%d,%s,%s\n", name, devList, change(wavetable), state);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询当步数偏差超过LOSTNUM后的响应方式
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int mrgMRQLostStepResponse_Query(ViSession vi, int name, int devList, int wavetable, char *state1)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:LOSTstep:LINe:RESPonse? %d,%d,%s\n", name, devList, change(wavetable));
    if ((retLen = busQuery(vi, args, strlen(args), state1, 10)) == 0) {
        return -1;
    }
    else
    {
        state1[retLen - 1] = '\0';
    }
    return 0;
}
/*
*查询上报功能配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportConfig_Query(ViSession vi, int name, int devList, char *funs)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:REPort:CONFig? %d,%d,%s\n", name, devList, funs);
    if ((retLen = busQuery(vi, args, strlen(args), funs, 10)) == 0) {
        return -1;
    }
    else
    {
        funs[retLen - 1] = '\0';
    }
    return 0;
}
/*
*设置上报功能配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*state:状态on/off
*period:指定类型数据的上报周期
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportConfig(ViSession vi, int name, int devList, char *funs, char *state, double period)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:REPort:CONFig %d,%d,%s,%s,%f\n", name, devList, funs, state, period);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*设置上报状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*state:状态on/off
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportState(ViSession vi, int name, int devList, char *funs, char *state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:REPort:STATe %d,%d,%s,%s\n", name, devList, funs, state);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询上报状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*state1:状态on/off
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportState_Query(ViSession vi, int name, int devList, char *funs, char *state1)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:REPort:STATe? %d,%d,%s\n", name, devList, funs);
    if ((retLen = busQuery(vi, args, strlen(args), state1, 10)) == 0) {
        return -1;
    }
    else
    {
        state1[retLen - 1] = '\0';
    }
    return 0;
}
/*
*设置上报周期
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*period:指定类型数据的上报周期
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportPeriod(ViSession vi, int name, int devList, char *funs, double period)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:REPort:PERiod %d,%d,%s,%f\n", name, devList, funs, period);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询上报周期
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*period:指定类型数据的上报周期
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportPeriod_Query(ViSession vi, int name, int devList, char *funs, int *period)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:REPort:PERiod? %d,%d,%s\n", name, devList, funs);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *period = atoi(state);
    return 0;
}
/*
*查询自动上报数据
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*index:上报数据类型： TORQUE（能效曲线的百分比）、 CYCLE（循环模式下的循环次数）、 SGALL、
SGSE 或 DIST（测距传感器的值）
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportData_Query(ViSession vi, int name, int devList, char *index, char *data)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:REPort:DATA? %d,%d,%s\n", name, devList, index);
    if ((retLen = busQuery(vi, args, strlen(args), data, 10)) == 0) {
        return -1;
    }
    else
    {
        data[retLen - 1] = '\0';
    }
    return 0;
}
/*
*设置触发输入的模式,码型触发或电平触发
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*mode:触发输入的模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerMode(ViSession vi, int name, int devList, char *mode)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:MODe %d,%d,%s\n", name, devList, mode);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}

/*
*查询触发输入的模式,码型触发或电平触发
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*mode:触发输入的模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerMode_Query(ViSession vi, int name, int devList, char *mode)
{
    char args[SEND_BUF];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:MODe? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), mode, 10)) == 0) {
        return -1;
    }
    else
    {
        mode[retLen - 1] = '\0';
    }
    return 0;
}
/*
*查询电平触发配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*buf:返回信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelConfig_Query(ViSession vi, int name, int devList, char *trig, char *buf)
{
    char args[SEND_BUF];
    char state[40];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:CONFig? %d,%d,%s\n", name, devList, trig);
    if ((retLen = busQuery(vi, args, strlen(args), state, 40)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    buf = state;
    return 0;
}
/*
*设置电平触发配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*buf:返回信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelConfig(ViSession vi, int name, int devList, char *trig, char *state, char *type, float period, char *response)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:CONFig %d,%d,%s,%s,%s,%f,%s\n", name, devList, trig, state, type, period, response);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*设置电平触发，打开或关闭
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*state:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelState(ViSession vi, int name, int devList, char *trig, char *state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:STATe %d,%d,%s,%s\n", name, devList, trig, state);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电平触发，打开或关闭
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelState_Query(ViSession vi, int name, int devList, char *trig, char *state1)
{
    char args[SEND_BUF];
    char state[40];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:STATe? %d,%d,%s\n", name, devList, trig);
    if ((retLen = busQuery(vi, args, strlen(args), state, 40)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    state1 = state;
    return 0;
}
/*
*设置触发电平类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*type:电平触发类型： RESERVE|LOW|RISE|FALL|HIGH
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelType(ViSession vi, int name, int devList, char *trig, char *type)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:TYPe %d,%d,%s,%s\n", name, devList, trig, type);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询触发电平类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*type:电平触发类型： RESERVE|LOW|RISE|FALL|HIGH
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelType_Query(ViSession vi, int name, int devList, char *trig, char *type)
{
    char args[SEND_BUF];
    char state[40];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:TYPe? %d,%d,%s\n", name, devList, trig);
    if ((retLen = busQuery(vi, args, strlen(args), state, 40)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    type = state;
    return 0;
}
/*
*设置触发电平响应
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*resp:电平触发的响应方式： NONE|ALARM|STOP|ALARM&STOP
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelResponse(ViSession vi, int name, int devList, char *trig, char *resp)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:RESPonse %d,%d,%s,%s\n", name, devList, trig, resp);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询触发电平响应
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*resp:电平触发的响应方式： NONE|ALARM|STOP|ALARM&STOP
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelResponse_Query(ViSession vi, int name, int devList, char *trig, char *resp)
{
    char args[SEND_BUF];
    char state[40];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:RESPonse? %d,%d,%s\n", name, devList, trig);
    if ((retLen = busQuery(vi, args, strlen(args), state, 40)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    resp = state;
    return 0;
}
/*
*设置触发电平采样周期
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*period:采样周期
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelPeriod(ViSession vi, int name, int devList, char *trig, float period)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:PERIod %d,%d,%s,%f\n", name, devList, trig, period);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询触发电平采样周期
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*period:采样周期
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelPeriod_Query(ViSession vi, int name, int devList, char *trig, double *period)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:TRIGger:LEVel:PERIod? %d,%d,%s\n", name, devList, trig);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *period = atof(state);
    return 0;
}
/*
*查询驱动板配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*buf:信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverConfig_Query(ViSession vi, int name, int devList, char *buf)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DRIVER:CONFig? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    buf = state;
    return 0;
}
/*
*设置驱动板配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*buf:信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverConfig(ViSession vi, int name, int devList, char *state, int microstep, float current)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DRIVER:CONFig %d,%d,%s,%d,%f\n", name, devList, state, microstep, current);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询驱动板类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:驱动板的类型
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverType_Query(ViSession vi, int name, int devList, char *type)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DRIVER:TYPe? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    type = state;
    return 0;
}
/*
*设置驱动板电流
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*current:驱动板电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverCurrent(ViSession vi, int name, int devList, float current)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DRIVER:CURRent %d,%d,%f\n", name, devList, current);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询驱动板电流
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*current:驱动板电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverCurrent_Query(ViSession vi, int name, int devList, double *current)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DRIVER:CURRent? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *current = atof(state);
    return 0;
}
/*
*设置电机微步数
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*microstep:电机的微步数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverMicroStep(ViSession vi, int name, int devList, int microstep)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DRIVER:MICROStep %d,%d,%d\n", name, devList, microstep);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机微步数
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*microstep:电机的微步数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverMicroStep_Query(ViSession vi, int name, int devList, int *microstep)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DRIVER:MICROStep? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *microstep = atoi(state);
    return 0;
}
/*
*设置驱动开关状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state:状态on/off
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverState(ViSession vi, int name, int devList, char *state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DRIVER:STATe %d,%d,%s\n", name, devList, state);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询驱动开关状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state1:状态on/off
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverState_Query(ViSession vi, int name, int devList, char *state1)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DRIVER:STATe? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    state1 = state;
    return 0;
}
/*
*查询编码器的状态,类型,线数及通道个数.状态为OFF时,后面的参数可以省略
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*buf:信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderConfig_Query(ViSession vi, int name, int devList, char *buf)
{
    char args[SEND_BUF];
    char state[40];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:CONFig? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 40)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    buf = state;
    return 0;
}
/*
*设置编码器的状态,类型,线数及通道个数.状态为OFF时,后面的参数可以省略
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state:状态
*type:编码器的类型： INCREMENTAL 或 ABSOLUTE
*linenum:增量型编码器光电码盘一周的线数： 500、 1000、 1024、 2000、 2048、 4000、 4096 或 5000
*channelnum:增量型编码器的通道数： 1 或 3
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderConfig(ViSession vi, int name, int devList, char *state, char *type, int linenum, int channelnum)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:CONFig %d,%d,%s,%s,%d,%d\n", name, devList, state, type, linenum, channelnum);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*设置编码器线数
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*num:编码器线数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderLineNum(ViSession vi, int name, int devList, int num)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:LINe:NUMber %d,%d,%d\n", name, devList, num);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询编码器线数
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*num:编码器线数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderLineNum_Query(ViSession vi, int name, int devList, int *num)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:LINe:NUMber? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *num = atoi(state);
    return 0;
}
/*
*设置编码器通道
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*channelnum:增量型编码器的通道数： 1 或 3
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderChannelNum(ViSession vi, int name, int devList, int channelnum)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:CHANnel:NUMber %d,%d,%d\n", name, devList, channelnum);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询编码器通道
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*channelnum:增量型编码器的通道数： 1 或 3
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderChannelNum_Query(ViSession vi, int name, int devList, int *channelnum)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:CHANnel:NUMber? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *channelnum = atoi(state);
    return 0;
}
/*
*设置编码器类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:编码器的类型： INCREMENTAL 或 ABSOLUTE
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderType(ViSession vi, int name, int devList, char *type)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:TYPe %d,%d,%s\n", name, devList, type);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询编码器类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:编码器的类型： INCREMENTAL 或 ABSOLUTE
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderType_Query(ViSession vi, int name, int devList, char *type)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:TYPe? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    type = state;
    return 0;
}
/*
*设置编码器信号的倍乘
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*multiple:倍乘
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderMultiple(ViSession vi, int name, int devList, char *multiple)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:MULTIPLe %d,%d,%s\n", name, devList, multiple);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询编码器信号的倍乘
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*multiple:倍乘
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderMultiple_Query(ViSession vi, int name, int devList, char *multiple)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:MULTIPLe? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    multiple = state;
    return 0;
}
/*
*设置编码器状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state:编码器的状态： NONE、 OFF 或 ON
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderState(ViSession vi, int name, int devList, char *state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:STATe %d,%d,%s\n", name, devList, state);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询编码器状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state1:编码器的状态： NONE、 OFF 或 ON
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderState_Query(ViSession vi, int name, int devList, char *state1)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:STATe? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    state1 = state;
    return 0;
}
/*
*设置LVT模式下编码器反馈比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*feed:编码器反馈比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderFeedback(ViSession vi, int name, int devList, float feed)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:FEEDBACK %d,%d,%f\n", name, devList, feed);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询LVT模式下编码器反馈比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*feed:编码器反馈比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderFeedback_Query(ViSession vi, int name, int devList, double *feed)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:ENCODer:FEEDBACK? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *feed = atof(state);
    return 0;
}
/*
*设置串口应用配置，配置校验位、数据位、停止位
*vi :visa设备句柄
*name: 设备名称
*port: 串口, 取值[1，2]
*parity:RS232 的校验方式： NONE、 EVEN 或 ODD
*wordlen:RS232 的数据长度： 8 或 9
*stopbit:RS232 数据帧中停止位的位数： 1、 0.5、 2 或 1.5
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartApply(ViSession vi, int name,int port,char *parity, int wordlen, float stopbit)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:UART%d:APPLy %d,%s,%d,%f\n",port, name, parity, wordlen, stopbit);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询串口应用配置，配置校验位、数据位、停止位
*vi :visa设备句柄
*name: 设备名称
*port: 串口, 取值[1，2]
*buf:信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartApply_Query(ViSession vi, int name,int port, char *buf)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:UART%d:APPLy? %d\n",port, name);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    buf = state;
    return 0;
}
/*
*设置串口硬件控制流
*vi :visa设备句柄
*name: 机器人名称
*port: 串口, 取值[1，2]
*mode:RS232 的流控制方式： NONE、 RTS、 CTS 或 RTS&CTS
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartFlowctrl(ViSession vi, int name,int port, char *mode)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:UART%d:FLOWctrl %d,%s\n", port,name, mode);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询串口硬件控制流
*vi :visa设备句柄
*name: 机器人名称
*port: 串口, 取值[1，2]
*mode:RS232 的流控制方式： NONE、 RTS、 CTS 或 RTS&CTS
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartFlowctrl_Query(ViSession vi, int name,int port, char *mode)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:UART%d:FLOWctrl? %d\n",port, name);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    mode = state;
    return 0;
}
/*
*设置串口传感器状态，打开或关闭
*vi :visa设备句柄
*name: 机器人名称
*port: 串口, 取值[1，2]
*state:打开或关闭
*返回值：0表示执行成功，－1表示失败
*/
//MEGAGATEWAY_API int CALL mrgMRQUartSensorState(ViSession vi, int name,int port,int index, int state)
//{
//    char args[SEND_BUF];
//    snprintf(args, SEND_BUF, "DEVICE:MRQ:UART%d:SENSor%d:STATe %d,%s\n",port,index, name, state?"ON":"OFF");
//    if (busWrite(vi, args, strlen(args)) == 0) {
//        return -1;
//    }
//    return 0;
//}
/*
*查询串口传感器状态，打开或关闭
*vi :visa设备句柄
*name: 机器人名称
*state1:打开或关闭
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartSensorState_Query(ViSession vi, int name,int port,int index, char *state1)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:UART%d:SENSor%d:STATe? %d\n",port,index, name);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    state1 = state;
    return 0;
}
/*
*设置传感器配置，数据帧头、帧长度、周期内接收的帧数、切换周期
*/
MEGAGATEWAY_API int CALL mrgMRQUartSensorConfAll(ViSession vi, int name)
{
    return 0;
}
/*
*查询传感器数据
*vi :visa设备句柄
*name: 机器人名称
*buf:数据
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartSensorData_Query(ViSession vi, int name,int port,int index, char *buf)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:UART%d:SENSor%d:DATA? %d\n",port,index, name);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    buf = state;
    return 0;
}
/*
*查询测距报警的状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
//MEGAGATEWAY_API int CALL mrgMRQDistanceAlarmState_Query(ViSession vi, int name, int devList, char *state1)
//{
//    char args[SEND_BUF];
//    char state[10];
//    int retLen = 0;
//    snprintf(args, SEND_BUF, "DEVICE:MRQ:DALarm:STATe? %d,%d\n", name, devList);
//    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
//        return -1;
//    }
//    else
//    {
//        state[retLen - 1] = '\0';
//    }

//    state1 = state;
//    return 0;
//}
/*
*设置测距报警的状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
//MEGAGATEWAY_API int CALL mrgMRQDistanceAlarmState(ViSession vi, int name, int devList,int state)
//{
//    char args[SEND_BUF];
//    snprintf(args, SEND_BUF, "DEVICE:MRQ:DALarm:STATe %d,%d,%s\n", name, devList, state?"ON":"OFF");
//    if (busWrite(vi, args, strlen(args)) == 0) {
//        return -1;
//    }
//    return 0;
//}
/*
*设置测距报警的响应距离
*alarm:ALARm1,ALARm2,ALARm3
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*distance:测距报警的响应距离
*返回值：0表示执行成功，－1表示失败
*/
//MEGAGATEWAY_API int CALL mrgMRQDistanceAlarm(ViSession vi, int name, int devList, float distance,  int alarm)
//{
//    char args[SEND_BUF];
//    snprintf(args, SEND_BUF, "DEVICE:MRQ:DALarm%d:DISTance %d,%d,%f\n", alarm, name, devList, distance);
//    if (busWrite(vi, args, strlen(args)) == 0) {
//        return -1;
//    }
//    return 0;
//}
/*
*查询测距报警的响应距离
*vi :visa设备句柄
*alarm:ALARm1,ALARm2,ALARm3
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*distance:测距报警的响应距离
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDistanceAlarm_Query(ViSession vi, int name, int devList, int alarm, double *distance)
{
    char args[SEND_BUF];
    char ret[12];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:DALarm:%d:DISTance? %d,%d\n", alarm, name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), ret, 12)) == 0) {
        return -1;
    }
    else
    {
        ret[retLen - 1] = '\0';
    }

    *distance = atof(ret);
    return 0;
}
/*
*查询驱动板类型（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:驱动板类型
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverType_Query(ViSession vi, int name, int devList, char *type)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:NDRiver:TYPe? %d,%d\n", name, devList);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    type = state;
    return 0;
}
/*
*设置驱动板电流（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*current:驱动板电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverCurrent(ViSession vi, int name, float current)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:NDRiver:CURRent %d,%f\n", name, current);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询驱动板电流（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*current:驱动板电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverCurrent_Query(ViSession vi, int name, double *current)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:NDRiver:CURRent? %d\n", name);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *current = atof(state);
    return 0;
}
/*
*设置电机微步数（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*microstep:电机的微步数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverMicrosteps(ViSession vi, int name, int microstep)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:NDRiver:MICRosteps %d,%d\n", name, microstep);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询电机微步数（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*microstep:电机的微步数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverMicrosteps_Query(ViSession vi, int name, int *microstep)
{
    char args[SEND_BUF];
    char state[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:NDRiver:MICRosteps? %d\n", name);
    if ((retLen = busQuery(vi, args, strlen(args), state, 10)) == 0) {
        return -1;
    }
    else
    {
        state[retLen - 1] = '\0';
    }

    *microstep = atoi(state);
    return 0;
}
/*
*查询驱动开关状态（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*chan：通道索引
state：开关状态
*返回值：0表示执行成功， 小于零表示过程出错
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverState_Query(ViSession vi, int name, int chan, int * state)
{
    char args[SEND_BUF];
    char ret[10];
    int retLen = 0;
    snprintf(args, SEND_BUF, "DEVICE:MRQ:NDRiver:STATe? %d,%d\n", name, chan);
    if ((retLen = busQuery(vi, args, strlen(args), ret, 10)) == 0) {
        return -1;
    }
    else
    {
        ret[retLen - 1] = '\0';
    }
    if (_stricmp(ret, "ON") == 0 || _stricmp(ret, "1") == 0)
    {
        *state = 1;
    }
    else
    {
        *state = 0;
    }
    return 0;
}
/*
*设置驱动开关状态（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverState(ViSession vi, int name, int devList, int state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "DEVICE:MRQ:NDRiver:STATe %d,%d,%s\n", name, devList, state?"ON":"OFF");
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }
    return 0;
}


