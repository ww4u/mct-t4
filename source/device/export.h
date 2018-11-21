#ifndef _EXPORT_H_
#define _EXPORT_H_

//#ifdef MEGAGATEWAY_EXPORTS
//#define EXPORT_API __declspec(dllexport)
//#else
//#define MEGAGATEWAY_API __declspec(dllimport)
//#endif

#ifdef _WIN32
#define STRCASECMP    _stricmp
#define STRTOK_S      strtok_s
#else
#define STRCASECMP    strcasecmp
#define STRTOK_S      strtok_r
#endif

//#define CALL    __cdecl
//#define CALL  __stdcall

#define EXPORT_API
#define CALL

#endif // !EXPORT_H_

