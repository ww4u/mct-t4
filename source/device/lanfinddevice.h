#ifndef LANFINDDEVICE_H
#define LANFINDDEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/*
    timeout 一次查询设备的最长时间
    desc :查询到的设备描述符
    返回找到的仪器的个数
*/
int findResources(char* ip,int timeout);

#ifdef __cplusplus
}
#endif
#endif // LANFINDDEVICE_H
