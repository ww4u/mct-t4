
#ifndef  _MEGA_ROBOT_H_
#define  _MEGA_ROBOT_H_
#include "bus.h"
//#include "export.h"
#define MEGAGATEWAY_API
#define CALL
/*********************** 机器人操作 *******************************/
/*
* 构建一个机器人
* vi :visa设备句柄
* robotType：要构建的机器人类型（MRX-T4,MRX-H2,MRX-DELTA）
* devList：设备列表 “512@0,512@1,”
* 返回值：0表示执行成功，－1表示失败
*/
MEGAGATEWAY_API int CALL mrgBuildRobot(ViSession vi, char * robotType, char * devList, int * robotname);
/*
* 设置当前机器人构形下的子类型
* vi :visa设备句柄
* name:机器人名称
* subtype:子类型。 对于H2来说，0表示小H2（802x494）；1表示大H2（891x769）
* 返回值：0表示执行成功，－1表示失败
* 说明：此函数目前只对H2有效
*/
MEGAGATEWAY_API int CALL mrgSetRobotSubType(ViSession vi, int name, int subtype);
/*
* 查询当前机器人构形下的子类型
* vi :visa设备句柄
* name:机器人名称
* 返回值：子类型。 对于H2来说，0表示小H2（802x494）；1表示大H2（891x769）
* 说明：此函数目前只对H2有效
*/
MEGAGATEWAY_API int CALL mrgGetRobotSubType(ViSession vi, int name);
/*
* 设置当前机器人的坐标系
* vi :visa设备句柄
* name:机器人名称
* coord:坐标系索引（详情参考对应的命令系统）
* 返回值：0表示执行成功，－1表示失败
* 说明：此函数目前只对H2有效
*/
MEGAGATEWAY_API int CALL mrgSetRobotCoordinateSystem(ViSession vi, int name, int coord);
/*
* 查询当前机器人的坐标系
* vi :visa设备句柄
* name:机器人名称
* 返回值：坐标系索引，（详情参考对应的命令系统）
* 说明：此函数目前只对H2有效
*/
MEGAGATEWAY_API int CALL mrgGetRobotCoordinateSystem(ViSession vi, int name);
/*
* 查询CAN网络中机器人的个数
* vi :visa设备句柄
* 返回值：返回机器人个数
*/
MEGAGATEWAY_API int CALL mrgGetRobotCount(ViSession vi);
/*
* 查询当前机器人的所使用的设备
* robotname: 机器人名称
* vi :visa设备句柄
* device：设备名称列表
* 返回值：返回所使用的设备个数
*/
MEGAGATEWAY_API int CALL mrgGetRobotDevice(ViSession vi, int robotname, int * device);

/*
 * 查询当前机器人的名字
 * vi :visa设备句柄
 * name: 输出查询到的机器人名字
 * len: name的长度
 * 返回值: 返回0表示成功，-1表示失败
*/
MEGAGATEWAY_API int CALL mrgGetRobotName(ViSession vi, char *name, int len);

/*
* 设置当前机器人的项目零点
* vi :visa设备句柄
* name:机器人名称
* x,y，z:项目零点值（x,y,z）
* 返回值：0表示执行成功，－1表示失败
* 说明：此函数目前只对H2有效
*/
MEGAGATEWAY_API int CALL mrgSetRobotProjectZero(ViSession vi, int name, double x, double y, double z);
/*
* 查询当前机器人的项目零点
* vi :visa设备句柄
* name:机器人名称
* x,y,z: 输出参数，项目零点值
* 返回值：0表示执行成功，－1表示失败
* 说明：此函数目前只对H2有效
*/
MEGAGATEWAY_API int CALL mrgGetRobotProjectZero(ViSession vi, int name, double * x, double *y, double *z);
/*
* 设置指定机器人的波表
* vi :visa设备句柄
* name: 机器人名称
* wavetable:波表索引值，取值范围0~9
* 返回值：0表示设置成功，否则表示设置失败
*/
MEGAGATEWAY_API int CALL mrgSetRobotWavetable(ViSession vi, int name, int wavetable);
/*
* 查询指定机器人的波表
* vi :visa设备句柄
* name: 机器人名称
* wavetable:波表索引值，取值范围0~9
* 返回值：大于0表示波表索引，小于零表示查询失败
*/
MEGAGATEWAY_API int CALL mrgRobotWavetableQuery(ViSession vi, int name);
/*
* 启动机器人的运行
* vi :visa设备句柄
* name: 机器人名称
* wavetable:波表索引，－1表示使用默认索引（调用mrgSetRobotWavetable设置的波表索引）
* 返回值：0表示启动成功，否则表示启动失败
*/
MEGAGATEWAY_API int CALL mrgRobotRun(ViSession vi, int name, int wavetable);
/*
* 停止机器人的运行
* vi :visa设备句柄
* name: 机器人名称
* wavetable:波表索引，－1表示使用默认索引（调用mrgSetRobotWavetable设置的波表索引）
* 返回值：0表示停止成功，否则表示停止失败
*/
MEGAGATEWAY_API int CALL mrgRobotStop(ViSession vi, int name, int wavetable);

/*
* 等待机器人的特定波表的ready状态（等待模块设备解算完成）
* vi :visa设备句柄
* name: 机器人名称
* wavetable ：波表索引，－1表示使用默认索引（调用mrgSetRobotWavetable设置的波表索引）
* timeout_ms：等待超时时间
* 返回值：0表示等待成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示等待超时
*/
MEGAGATEWAY_API int CALL mrgRobotWaitReady(ViSession vi, int name, int wavetable, int timeout_ms);
/*
* 等待机器人的特定波表的ready状态（等待模块设备解算完成）
* vi :visa设备句柄
* name: 机器人名称
* wavetable ：波表索引，－1表示使用默认索引（调用mrgSetRobotWavetable设置的波表索引）
* timeout_ms：等待超时时间
* 返回值：0表示等待成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示等待超时;-4:参数出错
*/
MEGAGATEWAY_API int CALL mrgRobotWaitEnd(ViSession vi, int name, char wavetable, int timeout_ms);
/*
* 机器人从当前位置移动到指定位置（随机移动）
* vi :visa设备句柄
* name: 机器人名称
* wavetable ：波表索引，－1表示使用默认索引（调用mrgSetRobotWavetable设置的波表索引）
* x,y,z: 位置坐标
* time : 移动到目标位置期望使用的时间
* timeout_ms:表示等待超时时间,0表示无限等待，－1表示不等待，立即返回
* 返回值：0表示执行成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示等待超时
* 说明：绝对位置移动,末端保持不动
*/
MEGAGATEWAY_API int CALL mrgRobotMove(ViSession vi, int name, int wavetable, float x, float y, float z, float time, int timeout_ms);
/*
* 机器人末端沿指定的坐标轴持续运动
* vi :visa设备句柄
* name: 机器人名称
* wavetable ：波表索引，－1表示使用默认索引（调用mrgSetRobotWavetable设置的波表索引）
* ax: 坐标轴，0表示X轴;1表示Y轴 ; 2表示Z轴
* speed : 移动的速度。单位： 度/秒
* dir: 0表示沿坐标轴负向运动，1表示沿坐标轴正向运动
* 返回值：0表示执行成功，否则表示过程中出错
* 说明：非阻塞函数
*/
MEGAGATEWAY_API int CALL mrgRobotMoveOn(ViSession vi, int name, int wavetable, int ax, float speed, int dir);
/*
* 机器人从当前位置移动给定的距离（随机移动）
* vi :visa设备句柄
* name: 机器人名称
* wavetable ：波表索引，－1表示使用默认索引（调用mrgSetRobotWavetable设置的波表索引）
* x,y,z: 位置坐标
* time : 移动到目标位置期望使用的时间
* timeout_ms:表示等待超时时间,0表示无限等待，－1表示不等待，立即返回
* 返回值：0表示执行成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示等待超时
* 说明：相对位置移动,末端保持不动
*/
MEGAGATEWAY_API int CALL mrgRobotRelMove(ViSession vi, int name, int wavetable, float x, float y, float z, float time, int timeout_ms);
/*
* 机器人从当前位置移动到指定位置（直线移动）
* vi :visa设备句柄
* name: 机器人名称
* wavetable ：波表索引，－1表示使用默认索引（调用mrgSetRobotWavetable设置的波表索引）
* x,y,z: 位置坐标
* time : 移动到目标位置期望使用的时间
* timeout_ms:表示等待超时时间,0表示无限等待，－1表示不等待，立即返回
* 返回值：0表示执行成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示等待超时
* 说明：绝对位置移动,末端保持不动
*/
MEGAGATEWAY_API int CALL mrgRobotMoveL(ViSession vi, int name, int wavetable, float x, float y, float z, float time, int timeout_ms);
/*
* 机器人从当前位置移动给定的距离（直线移动）
* vi :visa设备句柄
* name: 机器人名称
* wavetable ：波表索引，－1表示使用默认索引（调用mrgSetRobotWavetable设置的波表索引）
* x,y,z: 位置坐标
* time : 移动到目标位置期望使用的时间
* timeout_ms:表示等待超时时间,0表示无限等待，－1表示不等待，立即返回
* 返回值：0表示执行成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示等待超时
* 说明：相对位置移动,末端保持不动
*/
MEGAGATEWAY_API int CALL mrgRobotRelMoveL(ViSession vi, int name, int wavetable, float x, float y, float z, float time, int timeout_ms);

/*
* 设置机器人回零位时使用的波表
* vi :visa设备句柄
* name: 机器人名称
* wavetable:波表索引
* 返回值：0表示执行成功，－1：表示出错
*/
MEGAGATEWAY_API int CALL mrgSetRobotHomeWavetable(ViSession vi, int name, int wavetable);
/*
* 查询机器人回零位时使用的波表
* vi :visa设备句柄
* name: 机器人名称
* wavetable:返回的波表索引
* 返回值：大于等于0表示查询到的波表索引，小于零：表示出错
*/
MEGAGATEWAY_API int CALL mrgGetRobotHomeWavetable(ViSession vi, int name);
/*
* 机器人回零位操作
* vi :visa设备句柄
* name: 机器人名称
* timeout_ms:表示等待超时时间
* 返回值：0表示执行成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示执行超时
* 说明：末端保持不动
*/
MEGAGATEWAY_API int CALL mrgRobotGoHome(ViSession vi, int name, int timeout_ms);
/*
* 停止机器人回零位操作
* vi :visa设备句柄
* name: 机器人名称
* 返回值：0表示执行成功，-1:表示失败
*/
MEGAGATEWAY_API int CALL mrgRobotGoHomeStop(ViSession vi, int name);
/*
* 等待机器人回零位结束状态（等待运行完成）
* vi :visa设备句柄
* name: 机器人名称
* timeout_ms：等待超时时间，为零表示无限等待
* 返回值：0表示等待成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示等待超时
*/
MEGAGATEWAY_API int CALL mrgRobotWaitHomeEnd(ViSession vi, int name, int timeout_ms);
/*
* 获取机器人在原点时的各关节的角度
* vi :visa设备句柄
* name: 机器人名称
* 返回值：0表示执行成功，否则表示失败
* 说明：angles是不安全的，请在外部确保angles的空间足够
*/
MEGAGATEWAY_API int CALL mrgGetRobotHomeAngle(ViSession vi, int name, float * angles);
/*
* 获取机器人在零位时，末端的坐标点值
* vi :visa设备句柄
* name: 机器人名称
* 返回值：0表示执行成功， －1：表示执行失败
*/
MEGAGATEWAY_API int CALL mrgGetRobotHomePosition(ViSession vi, int name, float * x, float *y, float* z);
/*
* 设置机器人的回零方式
* vi :visa设备句柄
* name: 机器人名称
* mode: 回零方式。 0： 先x后y ； 1：先y后x
* 返回值：0表示执行成功，－1：表示出错，
* 说明：此命令目前只对H2有效
*/
MEGAGATEWAY_API int CALL mrgSetRobotHomeMode(ViSession vi, int name, int mode);
/*
* 查询机器人的回零方式
* vi :visa设备句柄
* name: 机器人名称
* 返回值：大于等于0表示回零方式，否则表示出错，
* 说明：此命令目前只对H2有效
*/
MEGAGATEWAY_API int CALL mrgGetRobotHomeMode(ViSession vi, int name);
/*
* 给指定的机器人加载坐标点
* vi :visa设备句柄
* name: 机器人名称
* 返回值：0表示执行成功，否则表示失败
* 说明：在调 用mrgRobotPointLoad（）函数前，请使用此函数清空上次的坐标点
*/
MEGAGATEWAY_API int CALL mrgRobotPointClear(ViSession vi, int name);
/*
* 给指定的机器人加载坐标点
* vi :visa设备句柄
* name: 机器人名称
* x,y,z: 坐标点信息
* end: 末端执行器电机转动的角度值
* time: 时间，表示当前点在主时间轴上的位置
* mod :是否插值
* 返回值：0表示执行成功，否则表示失败
* 说明：此函数只是将上位机的坐标点信息下载到MRG中，MRG并未开始解算.
*  另，  在调用此函数开始下发坐标点前，务必使用mrgRobotPointClear()函数，通知机器人清空其缓存中的坐标点。
*/
MEGAGATEWAY_API int CALL mrgRobotPointLoad(ViSession vi, int name, float x, float y, float z, float end, float time, int mod);
/*
* 通知机器人开始解算其缓存中的坐标点，并下发给模块设备，直到模块设备解算完成
* vi :visa设备句柄
* name: 机器人名称
* wavetable: 解算到指定的波表。 如果为－1，表示解算到当前机器人默认的波表中
* timeout_ms:表示等待超时时间,0表示无限等待，－1表示不等待，立即返回
* 返回值：0表示执行成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示等待超时
*/
MEGAGATEWAY_API int CALL mrgRobotPointResolve(ViSession vi, int name, int wavetable, int timeout_ms);
/*
* 从外部存储器（U盘）中，导入点坐标文件到机器人缓存中
* vi :visa设备句柄
* name: 机器人名称
* filename: 点坐标文件名
* 返回值：0表示执行成功，否则表示失败
*/
MEGAGATEWAY_API int CALL mrgRobotPointLoadFile(ViSession vi, int name, char* filename);
/*
* 查询外部存储器（U盘）中，可用的点坐标文件
* vi :visa设备句柄
* name: 机器人名称
* fileList: 点坐标文件名列表，以逗号分隔
* len : fileList的缓存长度
* 返回值：0表示执行成功，否则表示失败
*/
MEGAGATEWAY_API int CALL mrgRobotPointLoadFileQuery(ViSession vi, char* fileList, int len);
/*
* 通知机器人清空PVT缓存
* vi :visa设备句柄
* name: 机器人名称
* 返回值：0表示执行成功，否则表示失败
* 说明：在调 用mrgRobotPvtLoad（）函数前，请使用此函数清空上次的PVT
*/
MEGAGATEWAY_API int CALL mrgRobotPvtClear(ViSession vi, int name);
/*
* 给指定的机器人加载坐标点
* vi :visa设备句柄
* name: 机器人名称
* p,v,t: pvt信息
* axle: 轴索引
* 返回值：0表示执行成功，否则表示失败
* 说明：此函数只是将上位机的坐标点信息下载到MRG中，MRG并未开始解算.
*  另，  在调用此函数开始下发坐标点前，务必使用mrgRobotPvtClear()函数，通知机器人清空其缓存中的坐标点。
*/
MEGAGATEWAY_API int CALL mrgRobotPvtLoad(ViSession vi, int name, float p, float v, float t, int axle);
/*
* 通知机器人开始下发其缓存中的PVT到模块设备，直到模块设备解算完成
* vi :visa设备句柄
* name: 机器人名称
* wavetable: 解算到指定的波表。 如果为－1，表示解算到当前机器人默认的波表中
* timeout_ms:表示等待超时时间,0表示无限等待，－1表示不等待，立即返回
* 返回值：0表示执行成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示等待超时
*/
MEGAGATEWAY_API int CALL mrgRobotPvtResolve(ViSession vi, int name, int wavetable, int timeout_ms);
/*
* 从外部存储器（U盘）中，导入PVT文件到机器人缓存中
* vi :visa设备句柄
* name: 机器人名称
* filename: 点坐标文件名
* 返回值：0表示执行成功，否则表示失败
*/
MEGAGATEWAY_API int CALL mrgRobotPvtLoadFile(ViSession vi, int name, char* filename);
/*
* 查询外部存储器（U盘）中，可用的PVT文件
* vi :visa设备句柄
* name: 机器人名称
* fileList: 点坐标文件名列表，以逗号分隔
* len : fileList的缓存长度
* 返回值：0表示执行成功，否则表示失败
*/
MEGAGATEWAY_API int CALL mrgRobotPvtLoadFileQuery(ViSession vi, char* fileList, int len);
/*
* 设置末端执行器类型及相应的设备
* vi :visa设备句柄
* name: 机器人名称
* type: 末端执行器类型
* dev : 末端执行器对应的通道设备
* 返回值：0表示执行成功，－1：表示出错
*/
MEGAGATEWAY_API int CALL mrgRobotToolSet(ViSession vi, int robotname, char * type, char* dev);
/*
* 等待末端执行器执行完成
* vi :visa设备句柄
* name: 机器人名称
* timeout_ms : 末端执行器执行的超时时间，0表示无限等待
* 返回值：0表示执行成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示执行超时
*/
MEGAGATEWAY_API int CALL mrgRobotWaitToolExeEnd(ViSession vi, int name, int timeout_ms);
/*
* 执行末端执行器
* vi :visa设备句柄
* name: 机器人名称
* position: 末端执行器电机转动的角度
* time : 末端执行器电机转动的角度所用时间
* timeout_ms : 末端执行器执行的超时时间, 0表示无限等待; -1表示不等待
* 返回值：0表示执行成功，－1：表示等待过程中出错，－2：表示运行状态出错；－3：表示执行超时
*/
MEGAGATEWAY_API int CALL mrgRobotToolExe(ViSession vi, int name, float position, float time, int timeout_ms);
/*
* 停止末端执行器
* vi :visa设备句柄
* name: 机器人名称
* 返回值：0表示执行成功，否则表示失败
*/
MEGAGATEWAY_API int CALL mrgRobotToolStop(ViSession vi, int name);
/*
* 中止末端执行器回初始位
* vi :visa设备句柄
* name: 机器人名称
* 返回值：0表示执行成功，否则表示失败
*/
MEGAGATEWAY_API int CALL mrgRobotToolStopGoHome(ViSession vi, int name);
/*
* 末端执行器回初始位
* vi :visa设备句柄
* name: 机器人名称
* timeout_ms: 等待的超时时间, 0表示无限等待; -1表示不等待
* 返回值：0表示执行成功，否则表示失败
*/
MEGAGATEWAY_API int CALL mrgRobotToolGoHome(ViSession vi, int name, int timeout_ms);
/*
* 获取机器人当前各关节的角度值
* vi :visa设备句柄
* name: 机器人名称
* 返回值：大于零 表示返回角度值的个数，小于等于零表示出错
* 注： angles是不安全的，外部一定要保证angles的空间足够
*/
MEGAGATEWAY_API int CALL mrgGetRobotCurrentAngle(ViSession vi, int name, float * angles);
/*
* 获取机器人末端的位置坐标
* vi :visa设备句柄
* name: 机器人名称
* 返回值：0表示执行成功， －1：表示执行失败
*/
MEGAGATEWAY_API int CALL mrgGetRobotCurrentPosition(ViSession vi, int name, float * x, float *y, float* z);


#endif // ! _MEGA_ROBOT_H_


