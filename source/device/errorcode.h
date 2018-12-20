#ifndef _MEGA_ERROR_CODE_H_
#define _MEGA_ERROR_CODE_H_

#include "bus.h"
#include "export.h"

/*
上传错误代码配置
vi :visa设备句柄
code:错误代码值
error:返回错误代码配置值 
len: 长度
*/
EXPORT_API int CALL mrgErrorCodeConfigUpload(ViSession vi, int code, char* error, int len);

/*
下载错误代码配置
vi :visa设备句柄
code:错误代码值
type:类型，F/W/I ->错误/警告/信息 -> 1,2,3
diagnose: 诊断器是否配置 必配/选配 -> 0,1
response: 错误响应，A/B/C/D/E/F/G -> 1,2,3,4,5,6,7
enable: 是否使能 Y/N ->0,1
*/
EXPORT_API int CALL mrgErrorCodeConfigDownload(ViSession vi, int code, int type, int diagnose, int response, int enable);


/*
*返回错误文件
*vi :visa设备句柄
*format: NORMAL|ZIP|TARGZ|TAR -> 0,1,2,3
*errorLog:返回错误日志
*len: 长度
*/
EXPORT_API int CALL mrgErrorLogUpload(ViSession vi, int format, char* errorLog, int len);

/*
清除错误日志
vi :visa设备句柄
*/
EXPORT_API int CALL mrgErrorLogClear(ViSession vi);

#endif

