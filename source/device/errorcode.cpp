#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errorcode.h"

#define  SEND_BUF   (100)

/*
上传错误代码配置
vi :visa设备句柄
code:错误代码值
error:返回错误代码配置值
len: 长度
*/
EXPORT_API int CALL mrgErrorCodeConfigUpload(ViSession vi, int code, char* error, int len)
{
	char args[SEND_BUF];
	int retlen = 0;
	snprintf(args, SEND_BUF, ":ERRCode:UPLoad? %d", code);
	if ((retlen = busQuery(vi, args, strlen(args), error, len)) == 0) {
		return -1;
	}
	return 0;
}

/*
下载错误代码配置
vi :visa设备句柄
code:错误代码值
type:类型，F/W/I ->错误/警告/信息 -> 1,2,3
diagnose: 诊断器是否配置 必配/选配 -> 0,1
response: 错误响应，A/B/C/D/E/F/G -> 1,2,3,4,5,6,7
enable: 是否使能 Y/N ->0,1
*/
EXPORT_API int CALL mrgErrorCodeConfigDownload(ViSession vi, int code, int type, int diagnose, int response, int enable)
{
	char args[SEND_BUF];
	int retlen = 0;

	char* ps8Type = NULL;
	char* ps8Diagnose = NULL;
	char* ps8Response = NULL;
	char* ps8Enable = NULL;

	if (type == 1)
	{
		ps8Type = "F";
	}
	else if (type == 2)
	{
		ps8Type = "W";
	}
	else if (type == 3)
	{
		ps8Type = "I";
	}
	else
	{
		return -1;
	}


	if (diagnose == 0)
	{
		ps8Diagnose = "ON";
	}
	else if (diagnose == 1)
	{
		ps8Diagnose = "OFF";
	}
	else
	{
		return -2;
	}

	if (diagnose == 0)
	{
		ps8Diagnose = "OFF";
	}
	else if (diagnose == 1)
	{
		ps8Diagnose = "ON";
	}
	else
	{
		return -2;
	}

	if (response == 1)
	{
		ps8Response = "A";
	}
	else if (response == 2)
	{
		ps8Response = "B";
	}
	else if (response == 3)
	{
		ps8Response = "C";
	}
	else if (response == 4)
	{
		ps8Response = "D";
	}
	else if (response == 5)
	{
		ps8Response = "E";
	}
	else if (response == 6)
	{
		ps8Response = "F";
	}
	else if (response == 7)
	{
		ps8Response = "G";
	}
	else
	{
		return -3;
	}

	if (enable == 0)
	{
		ps8Enable == "N";
	}
	else if (enable == 1)
	{
		ps8Enable = "Y";
	}
	else
	{
		return -4;
	}

	snprintf(args, SEND_BUF, ":ERRCode:DOWNLoad %d,%s,%s,%s,%s", code, ps8Type, ps8Diagnose, ps8Response, ps8Enable);
	if ((retlen = busWrite(vi, args, strlen(args))) <= 0) {
		return -5;
	}
	return 0;
}


/*
返回错误文件
vi :visa设备句柄
format: NORMAL|ZIP|TARGZ|TAR -> 0,1,2,3
errorLog:返回错误日志
len: 长度
*/
EXPORT_API int CALL mrgErrorLogUpload(ViSession vi, int format, char* errorLog, int len)
{
	char args[SEND_BUF];
	int retlen = 0;

	char* ps8Format = NULL;

	if (format == 0)
	{
		ps8Format = "NORMAL";
	}
	else if (format == 1)
	{
		ps8Format = "ZIP";
	}
	else if (format == 2)
	{
		ps8Format = "TARGZ";
	}
	else if (format == 3)
	{
		ps8Format = "TAR";
	}
	else
	{
		return -2;
	}


	snprintf(args, SEND_BUF, ":ERRCode:UPLoad? %s", ps8Format);
	if ((retlen = busQuery(vi, args, strlen(args), errorLog, len)) == 0) {
		return -1;
	}
	return 0;
}

/*
清除错误日志
vi :visa设备句柄
*/
EXPORT_API int CALL mrgErrorLogClear(ViSession vi)
{
	char args[SEND_BUF];
	int retlen = 0;

	snprintf(args, SEND_BUF, ":ERRCode:CLEar");
	if ((retlen = busWrite(vi, args, strlen(args))) == 0) {
		return -1;
	}
	return 0;
}

