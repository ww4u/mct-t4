#include "project.h"

/*
* 设置系统为工程模式
* vi :visa设备句柄
* state: 0->OFF| 1->ON
* 返回值：0表示执行成功；－1表示执行失败,-2表示参数错误
* 说明: 只有在工程模式下,才允许读取IO状态
*/
EXPORT_API int CALL mrgSetProjectMode(ViSession vi, int state)
{
    char args[SEND_LEN];
    if (state != 0 && state != 1)
    {
        return -2;
    }
    snprintf(args, SEND_LEN, "PROJect:STATe %s\n", state ? "ON" : "OFF");
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
* 查询外部IO的状态
* vi :visa设备句柄
* index: 0->所有,1->X1,2->X2...
* strState: 各个IO的状态,使用逗号分隔. "H,H,L,L"
* 返回值：0表示执行成功；－1表示执行失败,-2表示参数错误
*/
EXPORT_API int CALL mrgProjectIOGet(ViSession vi, IOGET_INDEX index, char *strState)
{
    char args[SEND_LEN];
    char as8Ret[RECV_LEN];
    int retLen = 0;
    char *ps8IOtables[] = {"ALL","X1","X2","X3","X4","X5","X6","X7","X8","X9","X10",
                           "Y1","Y2","Y3","Y4","STOP", "DB15"};
    if (index >= IOGET_MAXNUM || index < 0 || strState == NULL)
    {
        return -2;
    }
    snprintf(args, SEND_LEN, "PROJect:XREAD? %s\n",ps8IOtables[index]);
    if ((retLen = busQuery(vi, args, strlen(args), as8Ret, sizeof(as8Ret))) <= 0)
    {
        return -1;
    }
    strcpy(strState, as8Ret);
    return 0;
}
/*
* 查询外部IO的状态
* vi :visa设备句柄
* state: 每一位表示一个IO的状态
* 返回值：0表示执行成功；－1表示执行失败,-2表示参数错误
*/
EXPORT_API int CALL mrgProjectIOGetAll(ViSession vi, int *state)
{
    char args[SEND_LEN];
    char as8Ret[RECV_LEN];
    int retLen = 0;
   
    snprintf(args, SEND_LEN, "PROJect:XREAD? 0\n");
    if ((retLen = busQuery(vi, args, strlen(args), as8Ret, sizeof(as8Ret))) <= 0)
    {
        return -1;
    }
    *state = atoi(as8Ret);
    return 0;
}
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
EXPORT_API int CALL mrgProjectIOSet(ViSession vi, IOSET_INDEX index, int state,int mask)
{
    char args[SEND_LEN];
    char *ps8OutTable[] = {"ALL","Y1","Y2","Y3","Y4","READY","FAULT","ACK","MC","ENABLED"};
    if (index >= IOSET_MAXNUM || index < 0)
    {
        return -2;
    }
    if (index == 0)
    {
        snprintf(args, SEND_LEN, "PROJect:YWRITE ALL,%d,%d\n",state, mask);
    }
    else
    {
        snprintf(args, SEND_LEN, "PROJect:YWRITE %s,%s\n", ps8OutTable[index], (state&0x01) ? "H" : "L");
    }
    
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
* 设置系统的序列号
* vi :visa设备句柄
* ps8Serial: 序列号
* 返回值：0表示执行成功；－1表示执行失败,-2表示参数错误
*/
EXPORT_API int CALL mrgProjectSetSerialNum(ViSession vi, char * ps8Serial)
{
    char args[SEND_LEN];
    if (ps8Serial == NULL)
    {
        return -2;
    }
    snprintf(args, SEND_LEN, "PROJect:SN %s\n", ps8Serial);
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
* 查询系统的序列号
* vi :visa设备句柄
* serial: 序列号
* 返回值：返回序列号的长度
*/
EXPORT_API int CALL mrgProjectGetSerialNum(ViSession vi, char * ps8Serial)
{
    char args[SEND_LEN];
    char as8Ret[RECV_LEN];
    int retLen = 0;
    snprintf(args, SEND_LEN, "PROJect:SN?\n");
    if (ps8Serial == NULL)
    {
        return 0;
    }
    if ((retLen = busQuery(vi, args, strlen(args), as8Ret, sizeof(as8Ret))) <= 0)
    {
        return 0;
    }
    strcpy(ps8Serial, as8Ret);
    return retLen-1;
}
/*
 * 写入设备的序列号
 * idn :返回的设备描述符
 * len：idn缓存长度
 * 返回值：
 * 说明：此函数为工程接口函数，不对外开放
 */
EXPORT_API int CALL mrgWriteDeviceSerial(ViSession  vi, int name, char * ps8Serial)
{
    char args[SEND_LEN];
    if (ps8Serial == NULL)
    {
        return -2;
    }
    snprintf(args, SEND_LEN, "PROJECT:DEVICE:SN %d,%s\n", name, ps8Serial);
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}

#pragma region 测试命令,不对外开放
EXPORT_API int CALL mrgCanTestStart(ViSession  vi, int name)
{
    char args[SEND_LEN];
    snprintf(args, SEND_LEN, "DEBUG:CAN:TEST:START %d\n", name);
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
EXPORT_API int CALL mrgCanTestStop(ViSession  vi, int name)
{
    char args[SEND_LEN];
    snprintf(args, SEND_LEN, "DEBUG:CAN:TEST:STOP %d\n", name);
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
EXPORT_API int CALL mrgGetCanTestResult(ViSession  vi, int name,unsigned int * pu32Send, unsigned int * pu32Rec, unsigned int * pu32Lost, unsigned int * pu32Time_ms)
{
    char as8Ret[100];
    int retLen = 0;
    char args[SEND_LEN];
    char *p;
    char *pNext;
    snprintf(args, SEND_LEN, "DEBUG:CAN:TEST:INFO? %d\n", name);
    if (pu32Send == NULL || pu32Rec == NULL || pu32Lost == NULL || pu32Time_ms== NULL)
    {
        return -2;
    }
    if ((retLen = busQuery(vi, args, strlen(args), as8Ret, 100)) <= 0)
    {
        return -1;
    }
    as8Ret[retLen - 1] = 0;
    p = STRTOK_S(as8Ret, ",", &pNext);
    if (p)
    {
        *pu32Send = strtoul(p, NULL, 0);
    }
    p = STRTOK_S(NULL, ",", &pNext);
    if (p)
    {
        *pu32Rec = strtoul(p, NULL, 0);
    }
    p = STRTOK_S(NULL, ",", &pNext);
    if (p)
    {
        *pu32Lost = strtoul(p, NULL, 0);
    }
    p = STRTOK_S(NULL, ",", &pNext);
    if (p)
    {
        *pu32Time_ms = strtoul(p, NULL, 0);
    }
    return 0;
}
#pragma endregion

