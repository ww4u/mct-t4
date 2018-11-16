#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

#define SEND_BUF  (100)
/*
* 查询存储器中，可用的运动文件
* vi :visa设备句柄
* type:0表示本地存储（本地文件系统）；1表示外部存储（U盘之类）
* fileList: 点坐标文件名列表，以逗号分隔
* len : fileList的缓存长度
* 返回值：大于零表示返回实际的字节数，小于零表示出错
*/
MEGAGATEWAY_API int CALL mrgStorageMotionFileQuery(ViSession vi, int type, char* fileList, int len)
{
    int retlen = 0;
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "STORage:FILe:MOTion:%s?\n", (type == 0) ? "LOCAL" : "EXTERNAL");
    if ((retlen = busQuery(vi, args, strlen(args), fileList, len)) == 0) {
        return -1;
    }
    if (retlen < len)
    {
        fileList[retlen - 1] = 0;
    }
    return 0;
}

/*
* 读取运动文件内容到上位机
* vi :visa设备句柄
* filename: 文件名
* context：读取到的内容
* wantlen： context（存储区）的长度
* 返回值：返回实际的文件长度
*/
MEGAGATEWAY_API int CALL mrgStorageMotionFileContextRead(ViSession vi, char* filename, char* context, int wantlen)
{
    int retlen = 0;
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "STORage:FILe:MOTion:CONTEXT:READ? %s\n", filename);
    // 1. 先读回一个#9的头。
    // 2. 根据长度读取内容
    if ((retlen = busQuery(vi, args, strlen(args), context, wantlen)) == 0) {
        return -1;
    }
    context[retlen] = 0;
    return 0;
}

