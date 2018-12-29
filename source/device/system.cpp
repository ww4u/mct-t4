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


int mrgSysWifiSearch(ViSession vi, char *wifiList)
{
    char args[SEND_BUF];
    char ret[1024] = {0};
    int retlen = 0;
    snprintf(args, SEND_BUF, "SYSTEM:WIFI:SEARCH?\n");
    if ((retlen = busQuery(vi, args, strlen(args),ret,sizeof(ret))) <= 0)
    {
        return -1;
    }
    ret[retlen - 1] = 0;
    strcpy(wifiList,ret);
    return 0;
}

int mrgSysWifiConnect(ViSession vi, char *wifi, char *password)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "SYSTEM:WIFI:CONFig %s,%s\n", wifi, password);
    if (busWrite(vi, args, strlen(args)) == 0) {
        return -1;
    }

    int time = 0, intervalTime = 20;
    while (1)
    {
        if (time > 200)
        {
            return 0;
        }
        if(mrgSysWifiStatusQuery(vi) != 1)
        {
            Sleep(intervalTime);
            time += intervalTime;
            continue;
        }
        return 1;
    }
}

int mrgSysWifiStatusQuery(ViSession vi)
{
    char args[SEND_BUF];
    char state[1024] = {0};
    int retlen = 0;
    snprintf(args, SEND_BUF, "SYSTEM:WIFI:STATe?\n");
    if ((retlen = busQuery(vi, args, strlen(args),state,sizeof(state))) <= 0)
    {
        return -1;
    }
    state[retlen - 1] = 0;

    if( STRCASECMP(state, "ON") == 0 )
        return 1;
    else if( STRCASECMP(state, "OFF") == 0 )
        return 0;
    else
        return -1;
}
