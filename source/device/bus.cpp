#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bus.h"
#include <pthread.h>
#include <time.h> 

#ifdef _WIN32
#include <WINSOCK2.H>
#include <IPHlpApi.h>
//#include <Ws2tcpip.h> //组播要用到的头文件 
#else //_WIN32

#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#define INVALID_SOCKET (-1)
#define SOCKET int
#define SOCKET_ERROR (-1)
#define SOCKADDR struct sockaddr
#define SOCKADDR_IN struct sockaddr_in

#define IFRSIZE ((int)(size*sizeof(struct ifreq)))

#endif //_WIN32

#define ADD_GROUP//可以不加入组也可以向组内发信息
#define MCASTADDR "224.0.0.251"
#define UDP_PORT  5353//5566
#define MEGA_TCP_SOCKET_PORT (5555)

#ifdef _WIN32
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
#define LOCK()      \
ViStatus viSta = viLock( vi, VI_EXCLUSIVE_LOCK, UINT_MAX, VI_NULL, VI_NULL );\
    if ( viSta != VI_SUCCESS                        \
    && viSta != VI_SUCCESS_NESTED_EXCLUSIVE         \
    && viSta != VI_SUCCESS_NESTED_SHARED )          \
    { return -1; }

#define UNLOCK()    viUnlock( vi );

#endif

#else //_WIN32

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//#define INIT_LOCK() pthread_mutex_init(&mutex,NULL)
#define LOCK()     pthread_mutex_lock(&mutex)
#define UNLOCK()   pthread_mutex_unlock(&mutex)
//#define DESTROY_LOCK() pthread_mutex_destroy(&mutex)

#endif //_WIN32


int socketFindResources(char ip[][100],int len, int timeout);

#ifndef _WIN32
int busFindDevice(int bus, char *output, int len,int method)
{
    int r = 0;
    if (bus == 0)
    {
        if (method == 0)
        {
            strcpy(output, "");
            goto END;
        }
        else if (method == 1)
        {
            char ip_list[256][100];
            int status = socketFindResources(ip_list, 256, 500);
            for (int i = 0; i < status; i++)
            {
                snprintf(&output[r], len - r, "TCPIP0::%s::inst0::INSTR,", ip_list[i]);
                r = strlen(output);
            }
        }
    }
    else if (bus == 1) //USBTMC
    {
        strcpy(output, "");
    }

END:
    return 0;
}

int busOpenDevice(char * ip, int timeout_ms)
{
    // TCPIP0::192.168.1.2::inst0::INSTR,
    char buff[20][64] = {""};
    char *p, *pNext;
    int index = 0;
    p = STRTOK_S(ip, "::", &pNext);
    while ( p && (index<20) )
    {
        strcpy(buff[index++], p);
        p = STRTOK_S(NULL, "::", &pNext);
    }
    char *strIP = buff[1];

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MEGA_TCP_SOCKET_PORT);
    servaddr.sin_addr.s_addr = inet_addr(strIP);
    inet_pton(AF_INET, strIP, &servaddr.sin_addr); //ipV6

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //阻塞
    if(timeout_ms == -1)
    {
        int ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
        if(ret != 0)
        {
            perror("connectBloking");
            close(sockfd);
            return -1;
        }
        return sockfd;
    }

    //设置sockfd非阻塞
    int oldOption = fcntl(sockfd, F_GETFL);
    int newOption = oldOption | O_NONBLOCK;

    fcntl(sockfd, F_SETFL, newOption);

    int ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(ret == 0)
    {
        //连接成功
        fcntl(sockfd, F_SETFL, oldOption);
        return sockfd;
    }
    else if(errno != EINPROGRESS)
    {
        //连接没有立即返回，此时errno若不是EINPROGRESS，表明错误
        perror("connect error != EINPROGRESS");
        return -1;
    }

    fd_set readFds;
    fd_set writeFds;
    struct timeval timeout;

    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);

    FD_SET(sockfd, &writeFds);
    FD_SET(sockfd, &readFds);

    timeout.tv_sec = timeout_ms/1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    ret = select(sockfd+1, &readFds, &writeFds, NULL, &timeout);
    if(ret <= 0)
    {
        if(ret == 0)
            perror("select timeout");
        else
            perror("select error");

        close(sockfd);
        return -1;
    }

    if(FD_ISSET(sockfd, &writeFds))
    {
        //可读可写有两种可能，一是连接错误，二是在连接后服务端已有数据传来
        if(FD_ISSET(sockfd, &readFds))
        {
            if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
            {
                int error=0;
                socklen_t length = sizeof(errno);
                //调用getsockopt来获取并清除sockfd上的错误.
                if(getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &length) < 0)
                {
                    printf("get socket option failed\n");
                    close(sockfd);
                    return -1;
                }
                if(error != EISCONN)
                {
                    perror("connect error != EISCONN");
                    close(sockfd);
                    return -1;
                }
            }
        }
        //此时已排除所有错误可能，表明连接成功
        fcntl(sockfd, F_SETFL, oldOption);
    }
    else
    {
        perror("connect failed");
        close(sockfd);
        return -1;
    }

#if 1
    //设置收发超时
    ret = setsockopt(sockfd , SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));
    if (ret != 0)
    {   return -1;  }

    ret = setsockopt(sockfd , SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(struct timeval));
    if (ret != 0)
    {   return -1;  }
#endif

    return sockfd;
}

ViSession busOpenSocket(const char *pName, const char *addr, unsigned int port)
{
    //! FIXME
}

int busCloseDevice(ViSession vi)
{
    if(vi != 0)
    {   close(vi);    }
    return 0;
}

unsigned int busWrite(ViSession vi, char * buf, unsigned int len)
{
    unsigned int retCount;
    LOCK();
    retCount = send(vi, buf, len, 0);
    if( retCount <= 0 )
    {
        UNLOCK();
        return 0;
    }
    UNLOCK();
    return retCount;
}

unsigned int busRead(ViSession vi, char * buf, unsigned int len)
{
    LOCK();
    unsigned int retCount = recv(vi, buf, len, 0);
    UNLOCK();
    return retCount;
}

unsigned int busQuery(ViSession vi, char * input, unsigned int inputlen, char* output, unsigned int wantlen)
{
    int retCount;
    LOCK();

    retCount = send(vi, input, inputlen, 0);
    if( retCount <= 0 )
    {
        UNLOCK();
        return 0;
    }

    retCount = recv(vi, output, wantlen, 0);
    UNLOCK();
    if(retCount < 0)
    {
        perror("socket recv error!");
        retCount = 0;
    }
    return (unsigned int)retCount;
}

/* strHostIp:返回的IP地址
*  len: IP地址数组长度
*/
int getHostIpAddr(char strHostIp[][100], int len)
{
    struct ifreq ifr;
    struct ifconf ifc;
    char buf[2048];

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1) {
        return -1;
    }

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) {
        return -2;
    }

    struct ifreq* it = ifc.ifc_req;
    const struct ifreq* const end = it + (ifc.ifc_len/sizeof(struct ifreq));

    int count = 0;
    for (; it != end; ++it)
    {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) != 0){
            return -3;
        }else{
            if (!(ifr.ifr_flags & IFF_LOOPBACK))
            { // don't count loopback
                if (ioctl(sock, SIOCGIFADDR, &ifr) == 0){
                    //printf("IP address is: %s\n", inet_ntoa(((struct sockaddr_in *)(&ifr.ifr_addr))->sin_addr));
                }else
                    continue;
                sprintf(strHostIp[count],"%s", inet_ntoa(((struct sockaddr_in *)(&ifr.ifr_addr))->sin_addr));
                count++;
            }
        }
    }

    return count;
}


#else //_WIN32

/*
* 对于网线连接的网关，查找方式有两种： 一种是用VISA方式查找，另一种是用UDP广播方式查找。
* method: 0:表示使用VISA方式查找；1表示使用UDP方式查找
* 当method=0时，按照VISA的规范，需要指定总线类型，所以使用bus来传入总线类型。
* output为输出参数，输出找到的设备信息
*/
ViSession defaultRM;
int busFindDevice(int bus, char *output, int len,int method)
{
    ViStatus status;
    int r = 0;
    static ViUInt32 numInstrs;
    static ViFindList findList;
    char instrDescriptor[VI_FIND_BUFLEN];
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
    if (bus == 0)
    {
        if (method == 0)
        {
            status = viFindRsrc(defaultRM, "TCPIP[0-9]*::?*INSTR", &findList, &numInstrs, instrDescriptor);
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
                strcat(&output[r], ",");
                strcat(output, instrDescriptor);
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
    }
    else if (bus == 1) //USBTMC
    {
        status = viFindRsrc(defaultRM, "USB0::?*::INSTR", &findList, &numInstrs, instrDescriptor);
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
            strcat(&output[r], ",");
            strcat(output, instrDescriptor);
        }    /* end while */
    }
    
END:
    return 0;
}

int busOpenDevice(char * ip, int timeout)
{
    ViStatus status;
    ViSession vi;
    status = viOpenDefaultRM(&defaultRM);
    if (status < VI_SUCCESS)
    {
        printf("Could not open a session to the VISA Resource Manager!\n");
        return 0;
    }
    status = viOpen(defaultRM, ip, VI_NO_LOCK, VI_TMO_IMMEDIATE, &vi);
    if (status < VI_SUCCESS)
    {
        vi = -1;
        printf("viOpen failured:%d\n",status);
        return status;
    }
    if (_strnicmp(ip, "USB",3)== 0)
    {
        viSetAttribute(vi, VI_ATTR_TERMCHAR, 0x0D);
        viSetAttribute(vi, VI_ATTR_TERMCHAR_EN, VI_TRUE);
    }
    else if (_strnicmp(ip, "TCPIP", 5) == 0)
    {
        viSetAttribute(vi, VI_ATTR_TCPIP_NODELAY, VI_TRUE);
        viSetAttribute(vi, VI_ATTR_TCPIP_KEEPALIVE, VI_TRUE);
    }
    viSetAttribute(vi, VI_ATTR_TMO_VALUE, timeout);
    return vi;
}

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
    ViUInt32 retCount = 0;
    LOCK();
    viRead(vi, (ViBuf)buf, len, &retCount); //有可能返回错误码，但读到了数据，只是数据 还没有读完！！！！
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
    viRead(vi, (ViBuf)output, wantlen, &retCount);
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
#endif //_WIN32

/*
ip: 输出参数，返回找到的IP地址
timeout 一次查询设备的最长时间
len :ip长度
返回找到的仪器的个数
*/
int socketFindResources(char ip[][100], int ip_len,int timeout_ms)
{
#if _WIN32
    WSADATA ws;
#endif
    int ret, count = 0, hostIpCount = 0;
    SOCKET sock[256];
    SOCKADDR_IN localAddr, remoteAddr, servaddr;

#ifdef _WIN32
    int len = sizeof(SOCKADDR);
#else
   socklen_t len = sizeof(SOCKADDR);
#endif
    char recvBuf[50];
    
    char strHostIpAddr[256][100];
    hostIpCount = getHostIpAddr(strHostIpAddr,256);
    if (hostIpCount <= 0)
    {
        return -1;
    }

#if _WIN32
    ret = WSAStartup(MAKEWORD(2, 2), &ws);
    if (0 != ret)
    {
        return -1;
    }
#endif	
    for (int i = 0; i < hostIpCount; i++)
    {
        sock[i] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (INVALID_SOCKET == sock[i])
        {
#ifdef _WIN32		
            WSACleanup();
#endif
            return -1;
        }
        localAddr.sin_family = AF_INET;
        localAddr.sin_port = htons(0);
#ifdef _WIN32
        localAddr.sin_addr.S_un.S_addr = inet_addr(strHostIpAddr[i]);//htonl(INADDR_ANY);
#else
		localAddr.sin_addr.s_addr  = inet_addr(strHostIpAddr[i]);//htonl(INADDR_ANY);
#endif
        ret = bind(sock[i], (SOCKADDR*)&localAddr, sizeof(SOCKADDR));
        if (SOCKET_ERROR == ret)
        {
            return -1;
        }

#ifdef _WIN32
        ret = setsockopt(sock[i], SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout_ms, sizeof(int));
#else
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = timeout_ms*1000;
        ret = setsockopt(sock[i], SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));
#endif
        if (ret != 0)
        {
//            printf("SO_RCVTIMEO ERROR!CODE IS:%d\n", WSAGetLastError());
            return -1;
        }
#ifdef _WIN32		
        char bOpt = 1;
#else
		int bOpt = 1;
#endif
        //设置该套接字为广播类型
        ret = setsockopt(sock[i], SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));
        if(ret != 0)
            return -1;
    }
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(6000);
#ifdef _WIN32
    remoteAddr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");//htonl(INADDR_ANY);
#else
	remoteAddr.sin_addr.s_addr = inet_addr("255.255.255.255");//htonl(INADDR_ANY);
#endif

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
#ifdef _WIN32
        shutdown(sock[i], 2);//这里的"2"在win32中可以写为SD_BOTH
        closesocket(sock[i]);
#else
		close(sock[i]);
#endif		
    }
#ifdef _WIN32
    WSACleanup();
#endif
    return count;
}





