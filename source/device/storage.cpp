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
EXPORT_API int CALL mrgStorageMotionFileQuery(ViSession vi, int type, char* fileList, int len)
{
    int retlen = 0;
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "STOR:FIL:MOT:%s?\n", (type == 0) ? "LOC" : "EXTER");
    if ((retlen = busQuery(vi, args, strlen(args), fileList, len)) == 0) {
        return -1;
    }
    if (retlen < len)
    {
        fileList[retlen - 1] = 0;
        return retlen - 1;
    }
    else
    {
        return len;
    }
    
}

/*
* 读取运动文件内容到上位机
* vi :visa设备句柄
* filename: 文件名
* context：读取到的内容
* wantlen： context（存储区）的长度
* 返回值：返回实际的文件长度
*/
EXPORT_API int CALL mrgStorageMotionFileContextRead(ViSession vi, char* filename, char* context, int wantlen)
{
    int retlen = 0,count = 0,lenOfLen = 0,readLen = 0;
    int start = 0;
    char args[SEND_BUF];
    char as8Ret[1024],as8StrLen[20];
    snprintf(args, SEND_BUF, "STORage:FILe:MOTion:CONTEXT:READ? %s\n", filename);
    if (busWrite(vi, args, strlen(args)) == 0)
    {
        return 0;
    }
    // 1. 先读回一个#9的头。
    while ((retlen = busRead(vi, as8Ret, 12)) > 0)
    {
        start = -1;
        for (int i = 0; i < 12; i++)
        {
            if (as8Ret[i] == '#')
            {
                start = i;
                break;
            }
        }
        if (start == -1)//格式错误
        {
            return count;
        }
        lenOfLen = as8Ret[start + 1] - 0x30;
        memcpy(as8StrLen, &as8Ret[start + 2], lenOfLen);//取出长度字符串
        readLen = strtoul(as8StrLen, NULL, 10);
        if (readLen != 0)
        {
            as8Ret[0] = as8Ret[start + 11];
            if ((retlen = busRead(vi, &as8Ret[1], readLen - 1)) == 0)
            {
                return count;
            }
        }
        else //长度为零，认为文件结束
        {
            return count;
        }
        memcpy(&context[count], as8Ret, retlen + 1);
        count += retlen + 1;
    }
    return 0;
}
/*
* 保存运动文件内容到本地存储器
* vi :visa设备句柄
* filename: 文件名
* 返回值：  0：写入成功；1：写入失败
*/
EXPORT_API int CALL mrgStorageMotionFileSave(ViSession vi, char* srcFileName, char * saveFileName)
{
    int retlen = 0, count = 0, filesize = 0, writeLen = 0, cmdLen = 0;
    char args[SEND_BUF];
    char as8Ret[1024], as8StrLen[20];
    FILE * pFile = NULL;
    snprintf(args, SEND_BUF, "STORage:FILe:MOTion:CONTEXT:WRITe:NAMe %s\n", saveFileName);
    if ((pFile = fopen(srcFileName, "r")) == NULL)
    {
        return -1;
    }
    fseek(pFile, 0L, SEEK_END);
    filesize = ftell(pFile);
    fseek(pFile, 0L, SEEK_SET);
    if (busWrite(vi, args, strlen(args)) == 0)//写入文件名
    {
        fclose(pFile);
        return -1;
    }
    //写入文件内容
    while (filesize > 0)
    {
        writeLen = filesize > 512 ? 512 : filesize;
        snprintf(as8Ret, 1024, "STORage:FILe:MOTion:CONText:WRITe:DATa #9%09d", writeLen);
        cmdLen = strlen(as8Ret);
        fread(&as8Ret[cmdLen], 1, writeLen, pFile);
        if (busWrite(vi, as8Ret, writeLen+cmdLen) == 0)
        {
            fclose(pFile);
            return -1;
        }
        filesize -= writeLen;
    }
    snprintf(args, SEND_BUF, "STORage:FILe:MOTion:CONTEXT:WRITe:END\n");
    if (busWrite(vi, args, strlen(args)) == 0)//写入文件结束
    {
        fclose(pFile);
        return -1;
    }
    fclose(pFile);
    return 0;
}

