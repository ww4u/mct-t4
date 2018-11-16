
#ifndef _MR_GATEWAY_
#define _MR_GATEWAY_
//#include "export.h"

#define MEGAGATEWAY_API
#define CALL

#include "device.h"       /* 通用设备 */
#include "mrqDevice.h"    /* MRQ设备 */
#include "megaRobot.h"    /* 机器人  */

/********************** 兼容 MiSA 接口函数 ************************************/
MEGAGATEWAY_API int CALL robo_getIdn(int vi, char* val);
MEGAGATEWAY_API int CALL robo_program(int vi, int ax, int page, char *name);
MEGAGATEWAY_API int CALL robo_call(int vi, int ax, int page, int cycle, int mode);
MEGAGATEWAY_API int CALL robo_run(int vi, int ax, int page);
MEGAGATEWAY_API int CALL robo_stop(int vi, int ax, int page);
MEGAGATEWAY_API int CALL  robo_waitEnd(int vi, int ax, int page, int timeout_ms);
MEGAGATEWAY_API int CALL  robo_waitIdle(int vi, int ax, int page, int timeout_ms);
MEGAGATEWAY_API int CALL  robo_center(int vi, int ax, int page);
MEGAGATEWAY_API int CALL  Sinanju_move(int vi, int ax, int page, int mode,
    float x1, float y1, float z1, float h1,
    float x2, float y2, float z2, float h2,
    float t);
MEGAGATEWAY_API int CALL  Sinanju_preMove(int vi, int ax, int page, int mode,
    float x1, float y1, float z1, float h1,
    float x2, float y2, float z2, float h2,
    float t);
MEGAGATEWAY_API int CALL  Sinanju_goto(int vi, int ax, int page, int mode,
    float x1, float y1, float z1,
    float t);

MEGAGATEWAY_API int CALL  Sinanju_stepX(int vi, int ax, int page, int mode, float d, float t);
MEGAGATEWAY_API int CALL  Sinanju_stepY(int vi, int ax, int page, int mode, float d, float t);
MEGAGATEWAY_API int CALL  Sinanju_stepZ(int vi, int ax, int page, int mode, float d, float t);
MEGAGATEWAY_API int CALL  Sinanju_stepH(int vi, int ax, int page, int mode, float d, float t);

MEGAGATEWAY_API int CALL  Sinanju_Center(int vi, int ax, int page);
MEGAGATEWAY_API int CALL  Sinanju_Fold(int vi, int ax, int page);
MEGAGATEWAY_API int CALL  Sinanju_getPose(int vi, float *val0, float *val1, float *val2, float *val3);
MEGAGATEWAY_API int CALL  Sinanju_getDist(int vi, float *val0, float *val1, float *val2, float *val3);
MEGAGATEWAY_API int CALL  Sinanju_getRad(int vi, float *val0, float *val1, float *val2, float *val3);

#endif
