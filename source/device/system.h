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

#endif // !MR_SYSTEM_H

