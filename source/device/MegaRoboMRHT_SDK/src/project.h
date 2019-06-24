#ifndef MR_PROJECT_H
#define MR_PROJECT_H

#include "bus.h"

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

typedef enum
{
    IOGET_ALL,
    IOGET_X1,
    IOGET_X2,
    IOGET_X3,
    IOGET_X4,
    IOGET_X5,
    IOGET_X6,
    IOGET_X7,
    IOGET_X8,
    IOGET_X9,
    IOGET_X10,
    IOGET_Y1,
    IOGET_Y2,
    IOGET_Y3,
    IOGET_Y4,
    IOGET_STOP,
    IOGET_DB15,
    IOGET_MAXNUM,
}IOGET_INDEX;

typedef enum
{
    IOSET_ALL,
    IOSET_Y1,
    IOSET_Y2,
    IOSET_Y3,
    IOSET_Y4,
    IOSET_READY,
    IOSET_FAULT,
    IOSET_ACK,
    IOSET_MC,
    IOSET_ENABLED,
    IOSET_MAXNUM,
}IOSET_INDEX;

/*
* 设置系统为工程模式
* vi :visa设备句柄
* state: 0->OFF| 1->ON
* 返回值：0表示执行成功；－1表示执行失败,-2表示参数错误
* 说明: 只有在工程模式下,才允许读取IO状态
*/
EXPORT_API int CALL mrgSetProjectMode(ViSession vi, int state);
/*
* 查询外部IO的状态
* vi :visa设备句柄
* index: 0->所有,1->X1,2->X2...
* strState: 各个IO的状态,使用逗号分隔. "H,H,L,L"
* 返回值：0表示执行成功；－1表示执行失败,-2表示参数错误
*/
EXPORT_API int CALL mrgProjectIOGet(ViSession vi, IOGET_INDEX index, char *strState);
/*
* 查询外部IO的状态
* vi :visa设备句柄
* state: 每一位表示一个IO的状态
* 返回值：0表示执行成功；－1表示执行失败,-2表示参数错误
*/
EXPORT_API int CALL mrgProjectIOGetAll(ViSession vi,int *state);
/*
* 设置系统的外部输出IO的状态
* vi :visa设备句柄
* index: 0->ALL, 1->YOUT1, 2->YOUT2,3->YOUT3, 4->YOUT4
* state: 0->low| 1->high
* mask: 屏蔽位. 如果某一位为1表示屏蔽此位,0表示不屏蔽
* 返回值：0表示执行成功；－1表示执行失败,-2表示参数错误
* 说明: 当index为零时,表示要同时写出YOUT,此时的state的每一位,表示一个YOUT的状态,mask为相应的屏蔽码.
*      对于MRHT-29,同步写出,目前只对扩展YOUT有效,暂不支持DB15.
*/
EXPORT_API int CALL mrgProjectIOSet(ViSession vi, IOSET_INDEX index, int state, int mask);
/*
* 设置系统的序列号
* vi :visa设备句柄
* serial: 序列号
* 返回值：0表示执行成功；－1表示执行失败,-2表示参数错误
*/
EXPORT_API int CALL mrgProjectSetSerialNum(ViSession vi, char * ps8Serial);
/*
* 查询系统的序列号
* vi :visa设备句柄
* serial: 序列号
* 返回值：返回序列号的长度
*/
EXPORT_API int CALL mrgProjectGetSerialNum(ViSession vi, char * ps8Serial);
/*
 * 写入设备的序列号
 * idn :返回的设备描述符
 * len：idn缓存长度
 * 返回值：
 * 说明：此函数为工程接口函数，不对外开放
 */
EXPORT_API int CALL mrgWriteDeviceSerial(ViSession  vi, int name, char * ps8Serial);

EXPORT_API int CALL mrgCanTestStart(ViSession  vi, int name);
EXPORT_API int CALL mrgCanTestStop(ViSession  vi, int name);
EXPORT_API int CALL mrgGetCanTestResult(ViSession  vi, int name, unsigned int * pu32Send, unsigned int * pu32Rec, unsigned int * pu32Lost, unsigned int * pu32Time_ms);


#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif
