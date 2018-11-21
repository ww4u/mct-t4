#ifndef MR_STORAGE_H
#define MR_STORAGE_H
#include "bus.h"
#include "export.h"
/*
* 查询存储器中，可用的运动文件
* vi :visa设备句柄
* type:0表示本地存储（本地文件系统）；1表示外部存储（U盘之类）
* fileList: 点坐标文件名列表，以逗号分隔
* len : fileList的缓存长度
* 返回值：大于零表示返回实际的字节数，小于零表示出错
*/
EXPORT_API int CALL mrgStorageMotionFileQuery(ViSession vi, int type, char* fileList, int len);
/*
* 读取运动文件内容到上位机
* vi :visa设备句柄
* filename: 文件名
* context：读取到的内容
* wantlen： context（存储区）的长度
* 返回值：返回实际的文件长度
*/
EXPORT_API int CALL mrgStorageMotionFileContextRead(ViSession vi, char* filename, char* context, int wantlen);


EXPORT_API int CALL mrgStorageMotionFileSave(ViSession vi, char* srcFileName,char* saveFileName);
#endif // !MR_SYSTEM_H
