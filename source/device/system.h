#ifndef MR_SYSTEM_H
#define MR_SYSTEM_H
#include "bus.h"
#include "export.h"
/*
*切换 MRH-T 的模式
*vi :visa设备句柄
*mode:MRH-T 的模式，取值范围： [0, 1]
*返回值：0表示执行成功，－1表示失败
*/
EXPORT_API int CALL mrgSysModeSwitch(ViSession vi, int mode);

/**
 * @brief 搜索Wifi
 * @param vi: visa设备句柄
 * @param wifiList: 输出wifi列表
 * @return 0表示成功, -1表示失败
 */
EXPORT_API int CALL mrgSysWifiSearch(ViSession vi, char *wifiList);

/**
 * @brief 连接或断开wifi
 * @param vi: visa设备句柄
 * @param wifi: wifi名称
 * @param password: wifi密码
 * @return 1表示连接成功,0表示连接失败, -1表示出错
 */
EXPORT_API int CALL mrgSysWifiConnect(ViSession vi, char *wifi, char *password);

/**
 * @brief 查询wifi连接状态
 * @param vi: visa设备句柄
 * @return 1表示已连接，0表示未连接，-1表示失败
 */
EXPORT_API int CALL mrgSysWifiStatusQuery(ViSession vi);

#endif // !MR_SYSTEM_H

