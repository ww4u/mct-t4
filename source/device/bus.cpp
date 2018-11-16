#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bus.h"
#include "pthread.h"
#include <WINSOCK2.H>
#include <time.h> 
//#include <Ws2tcpip.h> //组播要用到的头文件 

#include <IPHlpApi.h>

#define ADD_GROUP//可以不加入组也可以向组内发信息
#define MCASTADDR "224.0.0.251"
#define UDP_PORT  5353//5566


#pragma comment (lib, "ws2_32")
#pragma comment (lib, "visa32.lib")
#pragma comment (lib,"IPHlpApi.lib") //需要添加Iphlpapi.lib库
#if 1
#pragma comment (lib, "pthreadVC2.lib")
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//#define INIT_LOCK() pthread_mutex_init(&mutex,NULL)
#define LOCK()     pthread_mutex_lock(&mutex)
#define UNLOCK()   pthread_mutex_unlock(&mutex)
//#define DESTROY_LOCK() pthread_mutex_destroy(&mutex)
#else
#define LOCK()      ViStatus viSta = viLock( vi, VI_EXCLUSIVE_LOCK, UINT_MAX, VI_NULL, VI_NULL );\
                    if ( viSta != VI_SUCCESS \
                         && viSta != VI_SUCCESS_NESTED_EXCLUSIVE \
                         && viSta != VI_SUCCESS_NESTED_SHARED ) \
                    { return -1; }
#define UNLOCK()    viUnlock( vi );
#endif
int socketFindResources(char ip[][100],int len, int timeout);
ViSession defaultRM;
/*
* 对于网线连接的网关，查找方式有两种： 一种是用VISA方式查找，另一种是用UDP广播方式查找。
* method: 0:表示使用VISA方式查找；1表示使用UDP方式查找
* 当method=0时，按照VISA的规范，需要指定总线类型，所以使用bus来传入总线类型。
* output为输出参数，输出找到的设备信息
*/
#if 0
int busFindDevice(char * bus, char *output, int len,int method)
{
    ViStatus status;
    int r = 0;
    /* First we will need to open the default resource manager. */
    status = viOpenDefaultRM(&defaultRM);
    if (status < VI_SUCCESS)
    {
        printf("Could not open a session to the VISA Resource Manager!\n");
        return 0;
    }
    /*
    * Find all the VISA resources in our system and store the number of resources
    * in the system in numInstrs.  Notice the different query descriptions a
    * that are available.

    Interface         Expression
    --------------------------------------
    GPIB              "GPIB[0-9]*::?*INSTR"
    VXI               "VXI?*INSTR"
    GPIB-VXI          "GPIB-VXI?*INSTR"
    Any VXI           "?*VXI[0-9]*::?*INSTR"
    Serial            "ASRL[0-9]*::?*INSTR"
    PXI               "PXI?*INSTR"
    All instruments   "?*INSTR"
    All resources     "?*"
    */
    if (method == 0)
    {
        static ViUInt32 numInstrs;
        static ViFindList findList;
        char instrDescriptor[VI_FIND_BUFLEN];
        status = viFindRsrc(defaultRM, bus, &findList, &numInstrs, instrDescriptor);
        if (status < VI_SUCCESS)
        {
            viClose(defaultRM);
            return 0;
        }
        strcpy(&output[r], instrDescriptor);
        while (--numInstrs)
        {
            /* stay in this loop until we find all instruments */
            status = viFindNext(findList, instrDescriptor);  /* find next desriptor */
            if (status < VI_SUCCESS)
            {
                goto END;
            }
            /* Now we will open a session to the instrument we just found */
            //if (lanTryConnectDev(instrDescriptor))
            {
                strcat(&output[r], ",");
                strcat(output, instrDescriptor);
            }
        }    /* end while */
    }
    else if (method == 1)
    {
        char ip_list[256][100];
        char * ptr = NULL;
        status = socketFindResources(ip_list, 256, 500);
        for (int i = 0; i < status; i++)
        {
            snprintf(&output[r], len - r, "TCPIP0::%s::inst0::INSTR,", ip_list[i]);
            r = strlen(output);
        }
    } 
END:
    return 0;
}


int busOpenDevice(char * ip, int timeout)
{
    ViStatus status;
    ViSession vi;
    status = viOpen(defaultRM, ip, VI_NO_LOCK, VI_TMO_IMMEDIATE, &vi);
    if (status < VI_SUCCESS)
    {
        vi = -1;
        return status;
    }
    viSetAttribute(vi, VI_ATTR_TCPIP_NODELAY, VI_TRUE);
    //viSetAttribute(vi, VI_ATTR_SEND_END_EN, VI_TRUE);
    viSetAttribute(vi, VI_ATTR_TCPIP_KEEPALIVE, VI_TRUE);
    //viSetAttribute(g_stLanInfo.instr_list[DevIndex], VI_ATTR_TERMCHAR, 0X0A);
    viSetAttribute(vi, VI_ATTR_TMO_VALUE, timeout);
    return vi;
}
#else

#include <iostream>
using namespace std;

static int _getHostIpAddr(string* strHostIp, unsigned int len)
{
    //PIP_ADAPTER_INFO结构体指针存储本机网卡信息
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
    //得到结构体大小,用于GetAdaptersInfo参数
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    //调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
    int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    int ipcount = 0;
    if (ERROR_BUFFER_OVERFLOW == nRel)
    {
        //如果函数返回的是ERROR_BUFFER_OVERFLOW
        //则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
        //这也是说明为什么stSize既是一个输入量也是一个输出量
        //释放原来的内存空间
        delete pIpAdapterInfo;
        //重新申请内存空间用来存储所有网卡信息
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        //再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
        nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    }
    if (ERROR_SUCCESS == nRel)
    {
        while (pIpAdapterInfo)
        {
            IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
            do
            {
                if (strcmp("0.0.0.0", pIpAddrString->IpAddress.String) != 0)
                {
                    strHostIp[ipcount] = string(pIpAddrString->IpAddress.String);
                    ipcount++;
                }
                pIpAddrString = pIpAddrString->Next;
            } while (pIpAddrString);
            pIpAdapterInfo = pIpAdapterInfo->Next;
        }
    }
    //释放内存空间
    if (pIpAdapterInfo)
    {
        delete pIpAdapterInfo;
    }
    return ipcount;
}

static int _findResources(char* ip, int timeout)
{
    WSADATA ws;
    int ret,count = 0, hostIpCount = 0;
    SOCKET sock[1024];
    SOCKADDR_IN localAddr, remoteAddr, servaddr;
    int len = sizeof(SOCKADDR);
    char recvBuf[50];
    char s;
    int timeout_s = timeout*1000; //秒转为毫秒
    ip[0] = 0;

    string strHostIpAddr[1024];
    hostIpCount = _getHostIpAddr(strHostIpAddr, 1024);
    if (hostIpCount <= 0)
    {
        return -1;
    }

    ret = WSAStartup(MAKEWORD(2, 2), &ws);
    if (0 != ret)
    {
        return -1;
    }

    for (int i = 0; i < hostIpCount; i++)
    {
        sock[i] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (INVALID_SOCKET == sock[i])
        {
            WSACleanup();
            return -1;
        }
        localAddr.sin_family = AF_INET;
        localAddr.sin_port = htons(0);
        localAddr.sin_addr.S_un.S_addr = inet_addr(strHostIpAddr[i].c_str());//htonl(INADDR_ANY);
        ret = bind(sock[i], (SOCKADDR*)&localAddr, sizeof(SOCKADDR));
        if (SOCKET_ERROR == ret)
        {
            return -1;
        }

        ret = setsockopt(sock[i], SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout_s, sizeof(int));
        if (ret != 0)
        {
            printf("SO_RCVTIMEO ERROR!CODE IS:%d\n", WSAGetLastError());
            return -1;
        }

        bool bOpt = true;
        //设置该套接字为广播类型
        setsockopt(sock[i], SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));
    }

    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(6000);
    remoteAddr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");//htonl(INADDR_ANY);

    for (int i = 0; i < hostIpCount; i++)
    {
        sendto(sock[i], "*?", 2, 0, (SOCKADDR*)&remoteAddr, sizeof(SOCKADDR));
        while (1)
        {
            memset(recvBuf, 0, 50);
            try
            {
                ret = recvfrom(sock[i], recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&servaddr, &len);
            }
            catch (exception& e)
            {
                break;
            }

            if (ret > 0)
            {
                count++;
                strcat_s(ip, 1024, inet_ntoa(servaddr.sin_addr));
                strcat_s(ip, 1024, ";");
            }
            else
            {
                break;
            }
        }
    }
    for (int i = 0; i < hostIpCount; i++)
    {
        shutdown(sock[i], 2);//这里的"2"在win32中可以写为SD_BOTH
        closesocket(sock[i]);
    }
    WSACleanup();
    return count;
}

int busFindDevice(char * bus, char *output, int len,int method)
{
    if(method == 1) //socket find
    {
        return _findResources(output, 1);
    }
    else //visa find
    {
        ViStatus status;
        int r = 0;
        /* First we will need to open the default resource manager. */
        status = viOpenDefaultRM(&defaultRM);
        if (status < VI_SUCCESS)
        {
//            printf("Could not open a session to the VISA Resource Manager!\n");
            return 0;
        }

        static ViUInt32 numInstrs;
        static ViFindList findList;
        char instrDescriptor[VI_FIND_BUFLEN];
        status = viFindRsrc(defaultRM, bus, &findList, &numInstrs, instrDescriptor);
        if (status < VI_SUCCESS)
        {
            viClose(defaultRM);
            return 0;
        }
        strcpy(&output[r], instrDescriptor);
        while (--numInstrs)
        {
            /* stay in this loop until we find all instruments */
            status = viFindNext(findList, instrDescriptor);  /* find next desriptor */
            if (status < VI_SUCCESS)
            {
                return status;
            }
            /* Now we will open a session to the instrument we just found */
            //if (lanTryConnectDev(instrDescriptor))
            {
                strcat(&output[r], ",");
                strcat(output, instrDescriptor);
            }
        }    /* end while */
    }

}

int busOpenDevice(char *ip, int timeout)
{
    ViStatus status;
    ViSession vi;
    status = viOpenDefaultRM(&defaultRM);
    if (status != VI_SUCCESS)
        return 0;

    char rsrc[64];
    snprintf(rsrc, 64, "TCPIP0::%s::inst0::INSTR", ip);

    status = viOpen(defaultRM, rsrc, VI_NO_LOCK, VI_TMO_IMMEDIATE, &vi);
    if (status != VI_SUCCESS)
        return -1;

    viSetAttribute(vi, VI_ATTR_TCPIP_NODELAY, VI_TRUE);
    //viSetAttribute(vi, VI_ATTR_SEND_END_EN, VI_TRUE);
    viSetAttribute(vi, VI_ATTR_TCPIP_KEEPALIVE, VI_TRUE);
    //viSetAttribute(g_stLanInfo.instr_list[DevIndex], VI_ATTR_TERMCHAR, 0X0A);
    viSetAttribute(vi, VI_ATTR_TMO_VALUE, timeout);
    return vi;
}

#endif

ViSession busOpenSocket(const char *pName, const char *addr, unsigned int port)
{
    ViStatus viSta;
    ViSession viDef, viDev;
    viSta = viOpenDefaultRM(&viDef);
    if (viSta != VI_SUCCESS)
    {
        return 0;
    }

    //! cat name
    char rsrc[64];
    snprintf(rsrc, 64, "TCPIP::%s::%d::SOCKET", addr, port);

    viSta = viOpen(viDef, rsrc, 0, 2000, &viDev);
    if (viSta != VI_SUCCESS)
    {
        return 0;
    }

    //set attribute
    viSetAttribute(viDev, VI_ATTR_TERMCHAR, 0X0A);
    viSetAttribute(viDev, VI_ATTR_TERMCHAR_EN, VI_TRUE);

    //set the name
    viPrintf(viDev, "%s\n", pName);
    viFlush(viDev, VI_WRITE_BUF);
    return viDev;
}
int busCloseDevice(ViSession vi)
{
    return viClose(vi);
}
unsigned int busWrite(ViSession vi, char * buf, unsigned int len)
{
    ViUInt32 retCount;
    LOCK();
    if(viWrite(vi, (ViBuf)buf, len, &retCount) != VI_SUCCESS)
    {
        UNLOCK();
        return 0;
    }
    UNLOCK();
    return retCount;
}

unsigned int busRead(ViSession vi, char * buf, unsigned int len)
{
    ViUInt32 retCount;
    LOCK();
    if (viRead(vi, (ViBuf)buf, len, &retCount) != VI_SUCCESS)
    {
        UNLOCK();
        return 0;
    }
    UNLOCK();
    return retCount;
}

unsigned int busQuery(ViSession vi, char * input, unsigned int inputlen,char* output, unsigned int wantlen)
{
    ViUInt32 retCount;
    LOCK();
    if (viWrite(vi, (ViBuf)input, inputlen, &retCount) != VI_SUCCESS)
    {
        UNLOCK();
        return 0;
    }
    if (viRead(vi, (ViBuf)output, wantlen, &retCount) != VI_SUCCESS)
    {
        UNLOCK();
        return 0;
    }
    UNLOCK();
    return retCount;
}


/* strHostIp:返回的IP地址
*  len: IP地址数组长度
*/
int getHostIpAddr(char strHostIp[][100], int len)
{
    //得到结构体大小,用于GetAdaptersInfo参数
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    //PIP_ADAPTER_INFO结构体指针存储本机网卡信息
    PIP_ADAPTER_INFO pIpAdapterInfo = (PIP_ADAPTER_INFO)malloc(stSize);
    //调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
    int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    //记录网卡数量
    int netCardNum = 0;
    int ipcount = 0;

    //记录每张网卡上的IP地址数量
    int IPnumPerNetCard = 0;
    if (ERROR_BUFFER_OVERFLOW == nRel)
    {
        //如果函数返回的是ERROR_BUFFER_OVERFLOW
        //则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
        //这也是说明为什么stSize既是一个输入量也是一个输出量
        //释放原来的内存空间
        free(pIpAdapterInfo);
        //重新申请内存空间用来存储所有网卡信息
        pIpAdapterInfo = (PIP_ADAPTER_INFO)malloc(stSize);
        //再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
        nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    }
    if (ERROR_SUCCESS == nRel)
    {
        //输出网卡信息
        //可能有多网卡,因此通过循环去判断
        while (pIpAdapterInfo)
        {
            //可能网卡有多IP,因此通过循环去判断
            IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
            do
            {
                if (strcmp("0.0.0.0", pIpAddrString->IpAddress.String) != 0)
                {
                    strcpy_s(strHostIp[ipcount],100, pIpAddrString->IpAddress.String);
                    ipcount++;
                }
                pIpAddrString = pIpAddrString->Next;
            } while (pIpAddrString);
            pIpAdapterInfo = pIpAdapterInfo->Next;
            //cout << "--------------------------------------------------------------------" << endl;
        }
    }
    //释放内存空间
    if (pIpAdapterInfo)
    {
        free(pIpAdapterInfo);
    }
    return ipcount;
}
#if 1
/*
ip: 输出参数，返回找到的IP地址
timeout 一次查询设备的最长时间
len :ip长度
返回找到的仪器的个数
*/
int socketFindResources(char ip[][100], int ip_len,int timeout_ms)
{
    WSADATA ws;
    int ret, count = 0, hostIpCount = 0;
    SOCKET sock[256];
    SOCKADDR_IN localAddr, remoteAddr, servaddr;
    int len = sizeof(SOCKADDR);
    char recvBuf[50];
    
    char strHostIpAddr[256][100];
    hostIpCount = getHostIpAddr(strHostIpAddr,256);
    if (hostIpCount <= 0)
    {
        return -1;
    }

    ret = WSAStartup(MAKEWORD(2, 2), &ws);
    if (0 != ret)
    {
        return -1;
    }
    for (int i = 0; i < hostIpCount; i++)
    {
        sock[i] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (INVALID_SOCKET == sock[i])
        {
            WSACleanup();
            return -1;
        }
        localAddr.sin_family = AF_INET;
        localAddr.sin_port = htons(0);
        localAddr.sin_addr.S_un.S_addr = inet_addr(strHostIpAddr[i]);//htonl(INADDR_ANY);
        ret = bind(sock[i], (SOCKADDR*)&localAddr, sizeof(SOCKADDR));
        if (SOCKET_ERROR == ret)
        {
            return -1;
        }
        ret = setsockopt(sock[i], SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout_ms, sizeof(int));
        if (ret != 0)
        {
            printf("SO_RCVTIMEO ERROR!CODE IS:%d\n", WSAGetLastError());
            return -1;
        }
        char bOpt = 1;
        //设置该套接字为广播类型
        setsockopt(sock[i], SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));
    }
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(6000);
    remoteAddr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");//htonl(INADDR_ANY);

    for (int i = 0; i < hostIpCount; i++)
    {
        sendto(sock[i], "*?", 2, 0, (SOCKADDR*)&remoteAddr, sizeof(SOCKADDR));
        while (1)
        {
            memset(recvBuf, 0, 50);
            ret = recvfrom(sock[i], recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&servaddr, &len);
            if (ret > 0)
            {
                strcpy_s(ip[count], 100, inet_ntoa(servaddr.sin_addr));
                count++;
                //printf("%s response to us : %s \n", inet_ntoa(servaddr.sin_addr), recvBuf);
            }
            else
            {
                break;
            }
        }
    }
    for (int i = 0; i < hostIpCount; i++)
    {
        shutdown(sock[i], 2);//这里的"2"在win32中可以写为SD_BOTH
        closesocket(sock[i]);
    }
    WSACleanup();
    return count;
}
#endif




