#include "device.h"

/*
* 查找网关。
* bus :总线类型. ＝0，网络接口；＝1，USBTMC接口
* output：查找到的设备描述符，多个设备之间以逗号分隔
* len : output的最大容量（字节个数）
* method:当网关设备使用网络连接时，在查找网关设备时有两种查找方式：
    method = 0,使用VISA查找方式；
    method = 1,使用UDP方式查找
* 返回值：查找到的设备个数
*/
EXPORT_API int CALL mrgFindGateWay(int  bus, char *output, int len,int method)
{
    return busFindDevice(bus, output, len,method);
}
/*
* 打开网关设备。
* desc: mrgFindGateWay返回的设备描述符
* timeout_ms: 设备通讯时的最大超时时间
* 返回值：visa句柄
*/
EXPORT_API int CALL mrgOpenGateWay(char * desc, int timeout_ms)
{
    return busOpenDevice(desc, timeout_ms);
}
/*
* 关闭网关设备。
* desc :findGateWay()返回的设备描述符
* timeout：设备通讯时的最大超时时间
* 返回值: 关闭的值
*/
EXPORT_API int CALL mrgCloseGateWay(ViSession  vi)
{
    return busCloseDevice(vi);
}
/*
* 向网关直接发送设置命令。
* vi :设备句柄
* cmd：要发送的设置命令
* len:命令长度
* 返回值：0表示执行成功，－1表示失败
*/
EXPORT_API int CALL mrgGateWaySendCmd(ViSession  vi, char* cmd, int len)
{
    return busWrite(vi, cmd, len);
}
/*
* 向网关发送读取命令。
* vi :设备句柄
* output:查询命令的返回
* wantlen:期望查询命令返回的长度，即output的长度
* 返回值：实际返回的数据长度
*/
EXPORT_API int CALL mrgGateWayRead(ViSession  vi, char * output, int wantlen)
{
    int retlen = 0;
    retlen = busRead(vi,output, wantlen>1024?1024:wantlen);
    return retlen;
}
/*
* 向网关直接发送查询命令。
* vi :设备句柄
* cmd：要发送的设置命令
* len:命令长度
* output:查询命令的返回
* wantlen:期望查询命令返回的长度，即output的长度
* 返回值：实际返回的数据长度
*/
EXPORT_API int CALL mrgGateWayQuery(ViSession  vi, char* cmd, char * output, int wantlen)
{
    int retlen = 0;
    retlen = busQuery(vi, cmd, strlen(cmd), output, wantlen>1024?1024:wantlen);
    return retlen;
}

/*
* 查询网关设备的*IDN。
* idn :返回的设备描述符
* len：idn缓存长度
* 返回值：查找到的设备个数
*/
EXPORT_API int CALL mrgGateWayIDNQuery(ViSession  vi, char * idn)
{
    char args[SEND_LEN];
    int retlen = 0;
    char as8Ret[RECV_LEN] = "";
    snprintf(args, SEND_LEN, "*IDN?\n");
    if ((retlen = busQuery(vi, args, strlen(args), as8Ret, sizeof(as8Ret))) <= 0)
    {
        return -1;
    }
    strcpy(idn, as8Ret);
    return 0;
}

/*
* 查找连接在网关上的设备。
* vi :visa设备句柄
* timeout为最长查找时间，单位：ms.
* 返回值：查找到的设备个数
*/
EXPORT_API int CALL mrgFindDevice(ViSession vi, int timeout_ms)
{
    char ret[RECV_LEN];
    char args[SEND_LEN];
    int retlen = 0;
    snprintf(args, SEND_LEN, "DEVICE:SEARCH\n");
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return 0;
    }
    msSleep(timeout_ms);
    snprintf(args, SEND_LEN, "DEVICE:COUNT?\n");
    if ((retlen = busQuery(vi, args, strlen(args), ret, sizeof(ret))) <= 0)
    {
        return 0;
    }
    return atoi(ret);
}
/*
* 获取所有与网关相连的设备名称（sendid的字符形式）
* vi :visa设备句柄
* names：返回名称的存放处
* 返回值：大于零表示设备名称个数; -1表示没有返回,-2表示参数错误
*/
EXPORT_API int CALL mrgGetDeviceName(ViSession vi, int * name)
{
    int count = 0;
    int retlen = 0;
    int tmp = 0;
    char args[SEND_LEN];
    char names[RECV_LEN];
    char *p;
    char *pNext = NULL;
    if (name == NULL)
    {
        return -2;
    }
    snprintf(args, SEND_LEN, "DEVICE:NAME?\n");
    if ((retlen = busQuery(vi, args, strlen(args), names, sizeof(names))) == 0)
    {
        return -1;
    }
    p = STRTOK_S(names, ",", &pNext);
    while (p)
    {
        tmp = atoi(p);
        if (tmp != 0)
        {
            name[count++] = tmp;
        }
        p = STRTOK_S(NULL, ",", &pNext);
    }
    return count;
}
/*
* 获取指定设备的类型
* vi :visa设备句柄
* type：返回设备类型的存储区
* type可能的取值： “MRQM2304”，“MRQM2305”，“MRQT2305”，“MRQM2310”，“MRQC23D”，“MRQC23S”，
* 返回值：0表示执行成功，－1表示失败; -2表示参数错误
*/
EXPORT_API int CALL mrgGetDeviceType(ViSession vi, int name, char * ps8Type)
{
    char args[SEND_LEN];
    char as8Ret[RECV_LEN];
    int len = 0;
    if (ps8Type == NULL)
    {
        return -2;
    }
    snprintf(args, SEND_LEN, "DEVICE:TYPe? %d\n", name);
    if ((len = busQuery(vi, args, strlen(args), as8Ret, sizeof(as8Ret))) == 0)
    {
        return -1;
    }
    strcpy(ps8Type,as8Ret);
    return 0;
}
/*
*查询指定设备的通道个数,name为仪器名
*vi :visa设备句柄
*name:机器人的名字
*返回值：大于零，表示通道个数，小于或等于零表示失败
*/
EXPORT_API int CALL mrgGetDeviceChannelCount(ViSession vi, int name)
{
    char args[SEND_LEN];
    int retLen = 0;
    char state[RECV_LEN];
    snprintf(args, SEND_LEN, "DEVice:CHANnel:COUNt? %d\n", name);
    if ((retLen = busQuery(vi, args, strlen(args), state, sizeof(state))) == 0) {
        return -1;
    }
    return atoi(state);
}
/*
* 获取指定设备的信息，包括（序列号：硬件版本号：软件版本号：boot版本号：逻辑版本号）
* vi :visa设备句柄
* ps8Info：返回信息的存储区. ps8Info是不安全的,请保持ps8Info最小长度为100字节
* 返回值：0表示执行成功，－1表示失败; -2表示参数错误
*/
EXPORT_API int CALL mrgGetDeviceInfo(ViSession vi, int name, char * ps8Info)
{
    char args[SEND_LEN];
    char as8Ret[RECV_LEN];
    int retlen = 0;
    snprintf(args, SEND_LEN, "DEVICE:FIRMWARE:ALL? %d\n", name);
    if ((retlen = busQuery(vi, args, strlen(args), as8Ret, sizeof(as8Ret))) == 0) {
        return -1;
    }
    strcpy(ps8Info,as8Ret);
    return 0;
}
/*
* 获取指定设备的软件版本号
* vi :visa设备句柄
* version：返回设备版本号的存储区

* 返回值：0表示执行成功，－1表示失败; -2表示参数错误
*/
EXPORT_API int CALL mrgGetDeviceSoftVersion(ViSession vi, int name, char * ps8Version)
{
    char args[SEND_LEN];
    int len = 0;
    char as8Ret[RECV_LEN];
    snprintf(args, SEND_LEN, "DEVICE:FIRMWARE:SOFT? %d\n", name);
    if ((len = busQuery(vi, args, strlen(args), as8Ret, sizeof(as8Ret))) == 0) {
        return -1;
    }
    strcpy(ps8Version, as8Ret);
    return 0;
}
/*
*查询设备硬件版本号
*vi :visa设备句柄
*name:机器人的名字
*buf:设备硬件版本号,长度最少12个字节
*返回值：0表示执行成功，－1表示失败; -2表示参数错误
*/
EXPORT_API int CALL mrgGetDeviceFirmWareHard(ViSession vi, int name, char *buf)
{
    char args[SEND_LEN];
    char as8Ret[RECV_LEN];
    int retLen = 0;
    snprintf(args, SEND_LEN, "DEVice:FIRMware:HARD? %d\n", name);
    if ((retLen = busQuery(vi, args, strlen(args), as8Ret, sizeof(as8Ret))) == 0) {
        return -1;
    }
    strcpy(buf, as8Ret);
    return 0;
}
/*
*查询设备BOOT版本号
*vi :visa设备句柄
*name:机器人的名字
*buf:设备BOOT版本号
*返回值：0表示执行成功，－1表示失败; -2表示参数错误
*/
EXPORT_API int CALL mrgGetDeviceFirmWareBoot(ViSession vi, int name, char *buf)
{
    char args[SEND_LEN];
    int retLen = 0;
    snprintf(args, SEND_LEN, "DEVice:FIRMware:BOOT? %d\n", name);
    if ((retLen = busQuery(vi, args, strlen(args), buf, RECV_LEN)) == 0) {
        return -1;
    }
    return 0;
}
/*
*查询设备逻辑版本号
*vi :visa设备句柄
*name:机器人的名字
*buf:设备逻辑版本号
*返回值：0表示执行成功，－1表示失败; -2表示参数错误
*/
EXPORT_API int CALL mrgGetDeviceFirmWareFpga(ViSession vi, int name, char *buf)
{
    char args[SEND_LEN];
    int retLen = 0;
    snprintf(args, SEND_LEN, "DEVice:FIRMware:FPGA? %d\n", name);
    if ((retLen = busQuery(vi, args, strlen(args), buf, RECV_LEN)) == 0) {
        return -1;
    }
    return 0;
}
/*
 * 获取指定设备的序列号
 * vi :visa设备句柄
 * ps8Serial：返回设备序列号的存储区
 * 返回值：0表示执行成功，－1表示失败; -2表示参数错误
 */
EXPORT_API int CALL mrgGetDeviceSerialNumber(ViSession vi, int name, char * ps8Serial)
{
    char args[SEND_LEN];
    int len = 0;
    snprintf(args, SEND_LEN, "DEVICE:FIRMWARE:SN? %d\n", name);
    if ((len = busQuery(vi, args, strlen(args), ps8Serial, RECV_LEN)) == 0) {
        return -1;
    }
    return 0;
}

