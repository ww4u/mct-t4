#ifndef __MEGA_PLATFORM_H__
#define __MEGA_PLATFORM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h>

#define strcpy_s(x,y,z)     	strncpy(x,z,y)

#ifdef _WIN32
//////////////////////////////////
//Windows头文件

#if (defined(__MINGW64__) || defined(__MINGW32__)) || defined(_UWIN)

#ifdef NTDDI_VERSION
#undef NTDDI_VERSION
#define NTDDI_VERSION NTDDI_WINXPSP3
#endif

#include <pthread.h>
#include "visatype.h"
#include "visa.h"

#include "../../assist.h"
#define msSleep(n)  localSleep( n )

#else // MSVC

#include "msvc/pthread.h"
#include "msvc/visa.h"
#include "msvc/visatype.h"

#pragma warning(disable : 4996)  

#endif

#include <WINSOCK2.H>
#include <windows.h>
#include <IPHlpApi.h>

#define STRCASECMP(x,y)		_stricmp(x,y)
#define STRTOK_S(x,y,z)		strtok_s(x,y,z)

#define EXPORT_API __declspec(dllexport)
#define CALL    __cdecl

//! no exception
#define _msSleep(n)  Sleep( n )

#else
//////////////////////////////////
//Linux 头文件
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>

#define INVALID_SOCKET 	(-1)
#define SOCKET 		int
#define SOCKET_ERROR 	(-1)
#define SOCKADDR 	struct sockaddr
#define SOCKADDR_IN 	struct sockaddr_in

#define IFRSIZE 	((int)(size*sizeof(struct ifreq)))

typedef unsigned long ViSession;
#include "vxi11/vxi11_user.h"

#define STRCASECMP(x,y)		strcasecmp(x,y)
#define STRTOK_S(x,y,z)     	strtok_r(x,y,z)
//#define _strnicmp           strncasecmp

#define _msSleep(n)  usleep( n * n  )

#define EXPORT_API 
#define CALL

#endif //_WIN32




#endif //__PLATFORM_H__