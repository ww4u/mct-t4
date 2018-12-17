#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"

#define SEND_BUF  (100)
/*
*切换 MRH-T 的模式
*vi :visa设备句柄
*mode:MRH-T 的模式，取值范围： [0, 1]
*返回值：0表示执行成功，－1表示失败
*/
EXPORT_API int CALL mrgSysModeSwitch(ViSession vi, int mode)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "SYSTEM:MODe:SWITch %d\n", mode);
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
*查询 MRH-T 的模式
*vi :visa设备句柄
*mode:MRH-T 的模式，取值范围： [0, 1]
*返回值：0表示执行成功，－1表示失败
*/
EXPORT_API int CALL mrgGetSysMode(ViSession vi)
{
    char args[SEND_BUF];
    char ret[8] = {0};
    int retlen = 0;
    snprintf(args, SEND_BUF, "SYSTEM:MODe:SWITch?\n");
    if ((retlen = busQuery(vi, args, strlen(args),ret,8)) <= 0)
    {
        return -1;
    }
    ret[retlen - 1] = 0;
    return atoi(ret);
}



