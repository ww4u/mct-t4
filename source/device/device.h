#ifndef _DEVICE_H_
#define _DEVICE_H_
#include "bus.h"
//#include "export.h"

#define MEGAGATEWAY_API
#define CALL
/*
* 查找网关。
* bus :总线类型
* output：查找到的设备描述符，多个设备之间以逗号分隔
* len : output的最大容量（字节个数）
* method:当网关设备使用网络连接时，在查找网关设备时有两种查找方式：
            method = 0,使用VISA查找方式；
            method = 1,使用UDP方式查找
* 返回值：查找到的设备个数
*/
MEGAGATEWAY_API  int CALL mrgFindGateWay(char * bus, char *output, int len, int method);
/*
* 打开网关设备。
* desc :findGateWay()返回的设备描述符
* timeout：设备通讯时的最大超时时间
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgOpenGateWay(char * desc, int timeout_ms);
/*
* 关闭网关设备。
* desc :findGateWay()返回的设备描述符
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgCloseGateWay(ViSession  vi);
/*
* 向网关直接发送设置命令。
* vi :设备句柄
* cmd：要发送的设置命令
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgGateWaySendCmd(ViSession  vi, char* cmd, int len);
/*
* 向网关直接发送查询命令。
* vi :设备句柄
* cmd：要发送的设置命令
* output:查询命令的返回
* wantlen:期望查询命令返回的长度，即output的长度
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgGateWayQuery(ViSession  vi, char* cmd, char * output, int wantlen);
/*
* 查询网关设备的*IDN。
* idn :返回的设备描述符
* len：idn缓存长度
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgGateWayIDNQuery(ViSession  vi, char * idn);
/*
* 查找连接在网关上的设备。
* vi :visa设备句柄
* timeout为最长查找时间，单位：ms.
* 返回值：查找到的设备个数
*/
MEGAGATEWAY_API int CALL mrgFindDevice(ViSession vi, int timeout_ms);
/*
* 获取所有与网关相连的设备名称
* vi :visa设备句柄
* names：返回名称的存放处
* names_len：存储区的长度
* 返回值：设备名称个数
*/
MEGAGATEWAY_API int CALL mrgGetDeviceName(ViSession vi, int* names);
/*
* 获取指定设备的类型
* vi :visa设备句柄
* type：返回设备类型的存储区
* type可能的取值： “MRQM2304”，“MRQM2305”，“MRQM2310”，“MRQC23D”，“MRQC23S”，
* type_len：存储区的长度，长度最少8个字节
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgGetDeviceType(ViSession vi, int name, char * type);
/*
* 获取指定设备的信息，包括（序列号：硬件版本号：软件版本号：boot版本号：逻辑版本号）
* vi :visa设备句柄
* info：返回信息的存储区
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgGetDeviceInfo(ViSession vi, int name, char * info);
/*
* 获取指定设备的软件版本号
* vi :visa设备句柄
* version：返回设备版本号的存储区
* len：存储区的长度
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgGetDeviceSoftVersion(ViSession vi, int name, char * version);
/*
* 写入设备的序列号
* idn :返回的设备描述符
* len：idn缓存长度
* 返回值：
* 说明：此函数为工程接口函数，不对外开放
*/
MEGAGATEWAY_API int CALL mrgWriteDeviceSerial(ViSession  vi, int name, char * serial);
/*
* 获取指定设备的序列号
* vi :visa设备句柄
* serial：返回设备序列号的存储区
* len：存储区的长度，长度最少18个字节
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgGetDeviceSerialNumber(ViSession vi, int name, char * serial);

/*
* 识别网关设备（ON时，LED1常亮；OFF时LED闪烁）
* vi :visa设备句柄
* name：机器人
* state：识别状态
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgIdentify(ViSession vi, int state);

#endif // !_DEVICE_H_

