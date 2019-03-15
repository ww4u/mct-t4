#ifndef _EXPORT_H_
#define _EXPORT_H_

/*************************************************/
#ifdef _MSC_VER //MSVC

#ifdef MEGAGATEWAY_EXPORTS
#define EXPORT_API __declspec(dllexport)
#else
#define MEGAGATEWAY_API __declspec(dllimport)
#endif

//#define CALL    __cdecl
//#define CALL  __stdcall

#else   // _MSC_VER

#define EXPORT_API
#define CALL

#endif //_MSC_VER
/*************************************************/
#ifdef _WIN32

#define STRCASECMP          _stricmp
#define STRTOK_S            strtok_s

//#include <windows.h>
#include "assist.h"
#define Sleep( n )        localSleep( n )

#else

#define STRCASECMP          strcasecmp
#define STRTOK_S            strtok_r
#define strcpy_s(x,y,z)     strncpy(x,z,y)
#define _strnicmp           strncasecmp

#define Sleep(x)            usleep( ((x) * 1000) )

#endif //_WIN32
/*************************************************/

#endif // !EXPORT_H_

