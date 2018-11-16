#ifndef _MRQ_DEVICE_H_
#define _MRQ_DEVICE_H_
#include "bus.h"
//#include "export.h"
#define MEGAGATEWAY_API
#define CALL
/*
*MRQ模块识别
*vi :visa设备句柄
*name：机器人
*state：识别状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQIdentify(ViSession vi, int name, int state);
/*
*设置运行状态是否自动上报给微控器
*vi :visa设备句柄
*name：机器人
*chan：通道号索引
*state：状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionStateReport(ViSession vi, int name, int chan, int state);
/*
*查询上报状态
*vi :visa设备句柄
*name：机器人
*chan：通道号索引
*state:自动上报状态 0：表示非自动上报；1：表示自动上报
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionStateReport_Query(ViSession vi, int name, int chan, int *state);
/*
*运行指定的波表
*vi :visa设备句柄
* name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引值，取值范围0~9
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionRun(ViSession vi, int name, int chan, int wavetable);
/*
*查询运行状态 "ERROR"“IDLE”“LOADING”“READY”“RUNNING”“STOP”
*vi :visa设备句柄
*name: 机器人名称
*chan：通道索引
*wavetable:波表索引值，取值范围[0，9]
*state:指定通道的运动状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionRunState(ViSession vi, int name, int chan, int wavetable, char *state);
/*
*停止指定的波表
*vi :visa设备句柄
* name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引值，取值范围0~9
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionStop(ViSession vi, int name, int chan, int wavetable);
/*
*设置启动运行的触发源
*vi :visa设备句柄
* name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*source:触发源
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionTrigSource(ViSession vi, int name, int chan, char *source);
/*
*查询启动运行触发源
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*source:触发源
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionTrigSource_Query(ViSession vi, int name, int chan, char *source);
/*
*设置电机未运动时发生位移是否上报给微控器
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionOffsetState(ViSession vi, int name, int chan, char *state);
/*
*查询电机未运动时发生位移是否上报给微控器状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*source:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionOffsetState_Query(ViSession vi, int name, int chan, char *source);
/*
*查询电机未运动时发生的位移
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*displace:位移
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionOffsetValue_Query(ViSession vi, int name, int chan, double *displace);
/*
*查询增量编码器的AB相的计数值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*返回值：AB相的计数值
*/
MEGAGATEWAY_API int CALL mrgMRQMotionABCount_Query(ViSession vi, int name, int chan);
/*
*清空增量编码器的AB相的计数值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotionABCountClear(ViSession vi, int name, int devList);
/*
*微调
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*position:位置
* time : 移动到目标位置期望使用的时间
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQAdjust(ViSession vi, int name, int devList, float position, float time);
/*
*时钟同步
*vi :visa设备句柄
*name_list:设备名列表
*time:同步的时间
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQClockSync(ViSession vi, char *name_list, float time);
/*
*设置电机的步距角
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*stepangle:电机的步距角
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorStepAngle(ViSession vi, int name, int devList, float stepangle);
/*
*查询电机的步距角
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*stepangle:电机的步距角
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorStepAngle_Query(ViSession vi, int name, int devList, double *stepangle);
/*
*设置电机的运动类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorMotionType(ViSession vi, int name, int devList, char *state);
/*
*查询电机的运动类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:运动类型
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorMotionType_Query(ViSession vi, int name, int devList, char *type);
/*
*设置电机运动时的单位
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*unit:电机运动时的单位
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorPositionUnit(ViSession vi, int name, int devList, char *unit);
/*
*查询电机运动时的单位
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*unit:电机运动时的单位
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorPositionUnit_Query(ViSession vi, int name, int devList, char *unit);
/*
*设置电机旋转运动时的速比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*ratio:电机旋转运动时的速比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorGearRatio(ViSession vi, int name, int devList, int a, int b);
/*
*查询电机旋转运动时的速比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*ratio:电机旋转运动时的速比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorGearRatio_Query(ViSession vi, int name, int devList, char *ratio);
/*
*设置电机直线运动时的导程
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*millimeter:电机直线运动时的导程
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorLead(ViSession vi, int name, int devList, float millimeter);
/*
*查询电机直线运动时的导程
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*millimeter:电机直线运动时的导程
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorLead_Query(ViSession vi, int name, int devList, double *millimeter);
/*
*设置电机的尺寸
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*size:电机的尺寸
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorSize(ViSession vi, int name, int devList, int size);
/*
*查询电机的尺寸
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*size:电机的尺寸
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorSize_Query(ViSession vi, int name, int devList, int *size);
/*
*设置电机的额定电压
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*volt:电压值
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorVoltate(ViSession vi, int name, int devList, int volt);
/*
*查询电机的额定电压
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*volt:电压值
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorVoltage_Query(ViSession vi, int name, int devList, int *volt);
/*
*设置电机的额定电流
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*current:额定电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorCurrent(ViSession vi, int name, int devList, double current);
/*
*查询电机的额定电流
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*current:额定电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorCurrent_Query(ViSession vi, int name, int devList, double *current);
/*
*设置电机的反向间隙
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*lash:电机的反向间隙
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorBackLash(ViSession vi, int name, int devList, double lash);
/*
*查询电机的反向间隙
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*lash:电机的反向间隙
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQMotorBackLash_Query(ViSession vi, int name, int devList, double *lash);
/*
*PVT配置命令
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state:PVT 的配置状态： END 或 CLEAR
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTConfig(ViSession vi, int name, int devList, int wavetable, char *state);
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
MEGAGATEWAY_API int CALL mrgMRQPVTValue(ViSession vi, int name, int devList, int wavetable, float p, float v, float t);
/*
*查询当前PVT下发的状态 "ERROR"“IDLE”“LOADING”“READY”
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state1:PVT下发的状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTState_Query(ViSession vi, int name, int devList, int wavetable, char *state1);
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
MEGAGATEWAY_API int CALL mrgMRQPVTTimeScale(ViSession vi, int name, int devList, int wavetable, float speedup, float speedcut);
/*
*查询模式,包括执行模式,规划模式,运动模式
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeConfig_Query(ViSession vi, int name, int devList, int wavetable, char *pattern);
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
MEGAGATEWAY_API int CALL mrgMRQPVTModeConfig(ViSession vi, int name, int devList, int wavetable, char *exe, char *plan, char *motion);
/*
*设置执行模式,循环或者FIFO
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeExe(ViSession vi, int name, int devList, int wavetable, char *pattern);
/*
*查询执行模式,循环或者FIFO
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeExe_Query(ViSession vi, int name, int devList, int wavetable, char *pattern);
/*
*设置规划模式:三次插值,线性插值,梯形插值,或五次插值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModePlan(ViSession vi, int name, int devList, int wavetable, char *pattern);
/*
*查询规划模式:三次插值,线性插值,梯形插值,或五次插值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModePlan_Query(ViSession vi, int name, int devList, int wavetable, char *pattern);
/*
*设置运动模式:PVT或者LVT
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeMotion(ViSession vi, int name, int devList, int wavetable, char *pattern);
/*
*查询运动模式:PVT或者LVT
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModeMotion_Query(ViSession vi, int name, int devList, int wavetable, char *pattern);
/*
*设置LVT模式下进行时间调整的占比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*duty:占空比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModifyDuty(ViSession vi, int name, int devList, int wavetable, float duty);
/*
*查询LVT模式下进行时间调整的占比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*duty:占空比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTModifyDuty_Query(ViSession vi, int name, int devList, int wavetable, double *duty);
/*
*设置是否为速度保持
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTEndState(ViSession vi, int name, int devList, int wavetable, char *pattern);
/*
*查询是否为速度保持
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*pattern:模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTEndState_Query(ViSession vi, int name, int devList, int wavetable, char *pattern);
/*
*设置S曲线的加减速占比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*scale:加速度占比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTDecScale(ViSession vi, int name, int devList, int wavetable, float scale);
/*
*查询S曲线的加减速占比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*scale:加速度占比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTDecScale_Query(ViSession vi, int name, int devList, int wavetable, double *scale);
/*
*设置急停方式,立即停止或者减速停止
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*way:急停方式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopMode(ViSession vi, int name, int devList, int wavetable, char *way);
/*
*查询急停方式,立即停止或者减速停止
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*way:急停方式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopMode_Query(ViSession vi, int name, int devList, int wavetable, char *way);
/*
*设置急停时间
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*time:急停的时间
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopTime(ViSession vi, int name, int devList, int wavetable, float time);
/*
*查询急停时间
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*time:急停的时间
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopTime_Query(ViSession vi, int name, int devList, int wavetable, double *time);
/*
*设置减速停止时的减速距离
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*distance:减速距离
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopDistance(ViSession vi, int name, int devList, int wavetable, float distance);
/*
*查询减速停止时的减速距离
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*distance:减速距离
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQPVTStopDistance_Query(ViSession vi, int name, int devList, int  wavetable, double *distance);
/*
*查询失步的状态,阈值及失步后的反应
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state1:失步的状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepLineConfig_Query(ViSession vi, int name, int devList, int wavetable, char *state1);
/*
*设置失步的状态,阈值及失步后的反应
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state1:失步的状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepLineConfig(ViSession vi, int name, int devList, int wavetable, char *state, double threshold, char *resp);
/*
*设置线间失步告警状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state:警告状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL DeviceMRQLostStepState(ViSession vi, int name, int devList, int wavetable, char *state);
/*
*查询线间失步告警状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state:警告状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL DeviceMRQLostStepState_Query(ViSession vi, int name, int devList, int wavetable, char *state1);
/*
*设置线间失步阈值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*value:线间失步阈值
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepThreshold(ViSession vi, int name, int devList, int wavetable, double value);
/*
*查询线间失步阈值
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*value:线间失步阈值
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepThreshold_Query(ViSession vi, int name, int devList, int wavetable, double *value);
/*
*设置当步数偏差超过LOSTNUM后的响应方式
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQLostStepResponse(ViSession vi, int name, int devList, int wavetable, char *state);
/*
*查询当步数偏差超过LOSTNUM后的响应方式
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*wavetable:波表索引，取值范围： MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int mrgMRQLostStepResponse_Query(ViSession vi, int name, int devList, int wavetable, char *state1);
/*
*查询上报功能配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportConfig_Query(ViSession vi, int name, int devList, char *funs);
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
MEGAGATEWAY_API int CALL mrgMRQReportConfig(ViSession vi, int name, int devList, char *funs, char *state, double period);
/*
*设置上报状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*state:状态on/off
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportState(ViSession vi, int name, int devList, char *funs, char *state);
/*
*查询上报状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*state1:状态on/off
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportState_Query(ViSession vi, int name, int devList, char *funs, char *state1);
/*
*设置上报周期
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*period:指定类型数据的上报周期
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportPeriod(ViSession vi, int name, int devList, char *funs, double period);
/*
*查询上报周期
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*funs:功能
*period:指定类型数据的上报周期
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQReportPeriod_Query(ViSession vi, int name, int devList, char *funs, int *period);
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
MEGAGATEWAY_API int CALL mrgMRQReportData_Query(ViSession vi, int name, int devList, char *index, char *data);
/*
*设置触发输入的模式,码型触发或电平触发
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*mode:触发输入的模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerMode(ViSession vi, int name, int devList, char *mode);
/*
*查询触发输入的模式,码型触发或电平触发
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*mode:触发输入的模式
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerMode_Query(ViSession vi, int name, int devList, char *mode);
/*
*查询电平触发配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*buf:返回信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelConfig_Query(ViSession vi, int name, int devList, char *trig, char *buf);
/*
*设置电平触发配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*buf:返回信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelConfig(ViSession vi, int name, int devList, char *trig, char *state, char *type, float period, char *response);
/*
*设置电平触发，打开或关闭
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*state:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelState(ViSession vi, int name, int devList, char *trig, char *state);
/*
*查询电平触发，打开或关闭
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelState_Query(ViSession vi, int name, int devList, char *trig, char *state1);
/*
*设置触发电平类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*type:电平触发类型： RESERVE|LOW|RISE|FALL|HIGH
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelType(ViSession vi, int name, int devList, char *trig, char *type);
/*
*查询触发电平类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*type:电平触发类型： RESERVE|LOW|RISE|FALL|HIGH
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelType(ViSession vi, int name, int devList, char *trig, char *type);
/*
*设置触发电平响应
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*resp:电平触发的响应方式： NONE|ALARM|STOP|ALARM&STOP
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelResponse(ViSession vi, int name, int devList, char *trig, char *resp);
/*
*查询触发电平响应
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*resp:电平触发的响应方式： NONE|ALARM|STOP|ALARM&STOP
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelResponse_Query(ViSession vi, int name, int devList, char *trig, char *resp);
/*
*设置触发电平采样周期
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*period:采样周期
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelPeriod(ViSession vi, int name, int devList, char *trig, float period);
/*
*查询触发电平采样周期
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*trig:电平触发编号： TRIGL 或 TRIGR
*period:采样周期
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQTriggerLevelPeriod_Query(ViSession vi, int name, int devList, char *trig, double *period);
/*
*查询驱动板配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*buf:信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverConfig_Query(ViSession vi, int name, int devList, char *buf);
/*
*设置驱动板配置
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*buf:信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverConfig(ViSession vi, int name, int devList, char *state, int microstep, float current);
/*
*查询驱动板类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:驱动板的类型
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverType_Query(ViSession vi, int name, int devList, char *type);
/*
*设置驱动板电流
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*current:驱动板电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverCurrent(ViSession vi, int name, int devList, float current);
/*
*查询驱动板电流
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*current:驱动板电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverCurrent_Query(ViSession vi, int name, int devList, double *current);
/*
*设置电机微步数
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*microstep:电机的微步数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverMicroStep(ViSession vi, int name, int devList, int microstep);
/*
*查询电机微步数
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*microstep:电机的微步数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverMicroStep_Query(ViSession vi, int name, int devList, int *microstep);
/*
*设置驱动开关状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state:状态on/off
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverState(ViSession vi, int name, int devList, char *state);
/*
*查询驱动开关状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state1:状态on/off
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDriverState_Query(ViSession vi, int name, int devList, char *state1);
/*
*查询编码器的状态,类型,线数及通道个数.状态为OFF时,后面的参数可以省略
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*buf:信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderConfig_Query(ViSession vi, int name, int devList, char *buf);
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
MEGAGATEWAY_API int CALL mrgMRQEncoderConfig(ViSession vi, int name, int devList, char *state, char *type, int linenum, int channelnum);
/*
*设置编码器线数
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*num:编码器线数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderLineNum(ViSession vi, int name, int devList, int num);
/*
*查询编码器线数
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*num:编码器线数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderLineNum_Query(ViSession vi, int name, int devList, int *num);
/*
*设置编码器通道
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*channelnum:增量型编码器的通道数： 1 或 3
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderChannelNum(ViSession vi, int name, int devList, int channelnum);
/*
*查询编码器通道
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*channelnum:增量型编码器的通道数： 1 或 3
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderChannelNum_Query(ViSession vi, int name, int devList, int *channelnum);
/*
*设置编码器类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:编码器的类型： INCREMENTAL 或 ABSOLUTE
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderType(ViSession vi, int name, int devList, char *type);
/*
*查询编码器类型
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:编码器的类型： INCREMENTAL 或 ABSOLUTE
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderType_Query(ViSession vi, int name, int devList, char *type);
/*
*设置编码器信号的倍乘
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*multiple:倍乘
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderMultiple(ViSession vi, int name, int devList, char *multiple);
/*
*查询编码器信号的倍乘
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*multiple:倍乘
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderMultiple_Query(ViSession vi, int name, int devList, char *multiple);
/*
*设置编码器状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state:编码器的状态： NONE、 OFF 或 ON
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderState(ViSession vi, int name, int devList, char *state);
/*
*查询编码器状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state1:编码器的状态： NONE、 OFF 或 ON
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderState_Query(ViSession vi, int name, int devList, char *state1);
/*
*设置LVT模式下编码器反馈比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*feed:编码器反馈比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderFeedback(ViSession vi, int name, int devList, float feed);
/*
*查询LVT模式下编码器反馈比
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*feed:编码器反馈比
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQEncoderFeedback_Query(ViSession vi, int name, int devList, double *feed);
/*
*设置串口应用配置，配置校验位、数据位、停止位
*vi :visa设备句柄
*name: 机器人名称
*parity:RS232 的校验方式： NONE、 EVEN 或 ODD
*wordlen:RS232 的数据长度： 8 或 9
*stopbit:RS232 数据帧中停止位的位数： 1、 0.5、 2 或 1.5
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartApply(ViSession vi, int name, int port,char *parity, int wordlen, float stopbit);
/*
*查询串口应用配置，配置校验位、数据位、停止位
*vi :visa设备句柄
*name: 机器人名称
*buf:信息
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartApply_Query(ViSession vi, int name, int port,char *buf);
/*
*设置串口硬件控制流
*vi :visa设备句柄
*name: 机器人名称
*mode:RS232 的流控制方式： NONE、 RTS、 CTS 或 RTS&CTS
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartFlowctrl(ViSession vi, int name, int port, char *mode);
/*
*查询串口硬件控制流
*vi :visa设备句柄
*name: 机器人名称
*mode:RS232 的流控制方式： NONE、 RTS、 CTS 或 RTS&CTS
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartFlowctrl_Query(ViSession vi, int name, int port, char *mode);
/*
*设置串口传感器状态，打开或关闭
*vi :visa设备句柄
*name: 机器人名称
*state:打开或关闭
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartSensorState(ViSession vi, int name, int port, int index, char *state);
/*
*查询串口传感器状态，打开或关闭
*vi :visa设备句柄
*name: 机器人名称
*state1:打开或关闭
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartSensorState_Query(ViSession vi, int name, int port, int index,char *state1);
/*
*查询传感器数据
*vi :visa设备句柄
*name: 机器人名称
*buf:数据
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQUartSensorData_Query(ViSession vi, int name, int port, int index, char *buf);
/*
*查询测距报警的状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDistanceAlarmState_Query(ViSession vi, int name, int devList, int state);
/*
*设置测距报警的状态
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*state1:状态
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDistanceAlarmState(ViSession vi, int name, int devList, int *state1);
/*
*设置测距报警的响应距离
*alarm:ALARm1,ALARm2,ALARm3
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*distance:测距报警的响应距离
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDistanceAlarm(ViSession vi, int name, int devList,int alarm, float distance);
/*
*查询测距报警的响应距离
*vi :visa设备句柄
*alarm:ALARm1,ALARm2,ALARm3
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*distance:测距报警的响应距离
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQDistanceAlarm_Query(ViSession vi, int name, int devList, int alarm, double *distance);
/*
*查询驱动板类型（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*devList：设备列表 “0@512,1@512,”
*type:驱动板类型
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverType_Query(ViSession vi, int name, int devList, char *type);
/*
*设置驱动板电流（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*current:驱动板电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverCurrent(ViSession vi, int name, float current);
/*
*查询驱动板电流（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*current:驱动板电流
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverCurrent_Query(ViSession vi, int name, double *current);
/*
*设置电机微步数（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*microstep:电机的微步数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverMicrosteps(ViSession vi, int name, int microstep);
/*
*查询电机微步数（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*microstep:电机的微步数
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverMicrosteps_Query(ViSession vi, int name, int *microstep);
/*
*查询驱动开关状态（只支持10轴）
*vi :visa设备句柄
*name: 机器人名称
*chan：通道索引
state：开关状态
*返回值：0表示执行成功， 小于零表示过程出错
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverState_Query(ViSession vi, int name, int chan,int * state);
/*
*设置驱动开关状态（只支持10轴）
*vi :visa设备句柄
*name: 设备名称
*chan：通道索引
*state:状态 取值[0，1]
*返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgMRQNewDriverState(ViSession vi, int name, int chan, int state);




#endif // !_MRQ_DEVICE_H_
