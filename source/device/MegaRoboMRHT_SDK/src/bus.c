#include "bus.h"

#if defined(_WIN32) && (!defined(__MINGW64__)) && (!defined(__MINGW32__))
#pragma comment (lib, "ws2_32.lib")  
#pragma comment (lib, "visa32.lib")
#pragma comment (lib, "IPHlpApi.lib")
#pragma comment (lib, "pthreadVC2.lib")
#endif

#define ADD_GROUP
#define MCASTADDR "224.0.0.251"
#define UDP_PORT  5353
#define MEGA_TCP_SOCKET_PORT (5555)

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#define LOCK()     pthread_mutex_lock(&mutex)
#define UNLOCK()   pthread_mutex_unlock(&mutex)


int socketFindResources(char ip[][100], int timeout);
static int  g_bus_type = BUS_LAN;
#ifndef _WIN32
int busFindDevice(int bus, char *output, int len,int method)
{
    int r = 0;
    if (output == NULL)
    {
        return 0;
    }
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
            int status = socketFindResources(ip_list, 500);
            int i;
            for (i = 0; i < status; i++)
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

char _g_device_IP[512] = ""; //设备IP，用于关闭
int _g_timeout = 2000; //收发超时时间
VXI11_CLINK *_g_clink = NULL;    //vxi11句柄

int busOpenDevice(char *ip, int timeout_ms)
{
    if (ip == NULL)
    {
        return -1;
    }
    memset(_g_device_IP,'\0',sizeof(_g_device_IP));
    _g_clink = NULL;
    _g_timeout = 2000;

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

    VXI11_CLINK *clink; //sizeof(VXI11_CLINK)
    if(vxi11_open_device(&clink, strIP, NULL)){
        //        printf("vxi11_open_device error: %s\n", strIP);
        free(clink);
        return -1;
    }

    strcpy(_g_device_IP, strIP);
    _g_clink = clink;
    _g_timeout = timeout_ms;

    srand((int)time(0));
    int value = (unsigned int)rand()/10000+1;
    return value;//随便返回一个非零数字
}

static int SyncSend(int vi, char *buf, int dataLen, int isBlock)
{
    if(_g_clink == NULL || buf == NULL)
        return -1;

    int ret = vxi11_send(_g_clink, buf, dataLen);
    if(ret > 0)
        return ret;
    if(ret < 0){
        perror("SyncSend error!");
    }
    return -1;
}

static int SyncRead(int vi, char *data, int dataLen, int isBlock)
{
    if(_g_clink == NULL || data == NULL)
        return -1;

    int ret = -1;
    if(isBlock)
    {
        ret = vxi11_receive(_g_clink, data, dataLen);
    }
    else
    {
        // -VXI11_NULL_READ_RESP 超时未判断
        ret = vxi11_receive_timeout(_g_clink, data, dataLen, _g_timeout);
    }
    if(ret > 0){
        return ret;
    }
    if(ret < 0 && ret != -VXI11_ERROR_IO_TIMEOUT){
        perror("SyncRead error!");
    }
    return -1;
}

int busCloseDevice(ViSession vi)
{
    if( (_g_clink != NULL) && (0!=strcmp(_g_device_IP,"")) )
    {
        vxi11_close_device(_g_clink, _g_device_IP);
    }

    memset(_g_device_IP,'\0',sizeof(_g_device_IP));
    _g_clink = NULL;
    return 0;
}

unsigned int busWrite(ViSession vi, char *data, unsigned int len)
{
    if (data == NULL)
    {
        return 0;
    }
    LOCK();
    int retCount = SyncSend(vi, data, len, 0);
    if(retCount < 0){
        UNLOCK();
        return 0;
    }
    //    printf("\nTO:\n\t%s", data);
    UNLOCK();
    return (unsigned int)retCount;
}

unsigned int busRead(ViSession vi, char *buf, unsigned int len)
{
    int errCount = 1;
    int retCount = 0;
    if (buf == NULL)
    {
        return 0;
    }
    LOCK();
    while(errCount--)
    {
        retCount = SyncRead(vi, buf, len, 0);
        if(retCount > 0)
        {
            break;
        }
        retCount=0;
        msSleep(5);
    }

    if( (retCount==0) || STRNCASECMP(buf, "Command error", strlen("Command error")) == 0 )
    {
        UNLOCK();
        return 0;
    }
    UNLOCK();
    if(buf[retCount-1] == '\n' && buf[0] != '\#')
        buf[retCount-1] = '\0';
    return (unsigned int)retCount;
}

unsigned int busQuery(ViSession vi, char * input, unsigned int inputlen, char* output, unsigned int wantlen)
{
    int retCount;
    int errCount = 1;
    if (input == NULL || output == NULL)
    {
        return 0;
    }
    LOCK();
    retCount = SyncSend(vi, input, inputlen, 1);
    if(retCount < 0)
    {
        UNLOCK();
        return 0;
    }

    while(errCount--)
    {
        retCount = SyncRead(vi, output, wantlen, 0);
        if(retCount > 0)
        {
            break;
        }
        retCount=0;
        msSleep(5);
    }
    if( (retCount==0) || STRNCASECMP(output, "Command error", strlen("Command error")) == 0 )
    {
        UNLOCK();
        return 0;
    }
    UNLOCK();
    if(output[retCount-1] == '\n' && output[0] != '\#')
        output[retCount-1] = '\0';
    return (unsigned int)retCount;
}

ViSession busOpenSocket(const char *pName, const char *addr, unsigned int port)
{
    //! FIXME
}


/* strHostIp:返回的IP地址
 *  len: IP地址数组长度
 */
int getHostIpAddr(char strHostIp[][100])
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
    if (output == NULL)
    {
        return 0;
    }
    if (bus != BUS_SOCKET)
    {
        /* First we will need to open the default resource manager. */
        status = viOpenDefaultRM(&defaultRM);
        if (status < VI_SUCCESS)
        {
            printf("Could not open a session to the VISA Resource Manager!\n");
            return 0;
        }
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
    g_bus_type = bus;
    if (bus == BUS_LAN || bus == BUS_SOCKET)
    {
        if (method == METHOD_VISA)
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
        else if (method == METHOD_UDP)
        {
            char ip_list[256][100];
            status = socketFindResources(ip_list, 500);
            for (int i = 0; i < status; i++)
            {
                snprintf(&output[r], len - r, "TCPIP0::%s::inst0::INSTR,", ip_list[i]);
                r = strlen(output);
            }
        }
    }
    else if (bus == BUS_USB) //USBTMC
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
        }
    }
END:
    return 0;
}

int busOpenDevice_vxi(char * viSrc, int timeout)
{
    ViStatus status;
    ViSession vi;
    if (viSrc == NULL)
    {
        return 0;
    }
    status = viOpenDefaultRM(&defaultRM);
    if (status < VI_SUCCESS)
    {
        return 0;
    }
//    status = viOpen(defaultRM, viSrc, VI_NO_LOCK, VI_TMO_IMMEDIATE, &vi);

	//windows一个主机仅允许打开一个-T
    status = viOpen(defaultRM, viSrc, VI_EXCLUSIVE_LOCK,VI_TMO_IMMEDIATE, &vi);
    if (status < VI_SUCCESS)
    {
        vi = 0;
        return 0;
    }
    if (_strnicmp(viSrc, "USB",3)== 0)
    {
        viSetAttribute(vi, VI_ATTR_TERMCHAR, 0x0A);
        viSetAttribute(vi, VI_ATTR_TERMCHAR_EN, VI_FALSE);
        viSetAttribute(vi, VI_ATTR_SEND_END_EN, VI_TRUE);
        viSetAttribute(vi, VI_ATTR_IO_PROT, 1);
    }
    else if (_strnicmp(viSrc, "TCPIP", 5) == 0)
    {
        viSetAttribute(vi, VI_ATTR_TCPIP_NODELAY, VI_TRUE);
        viSetAttribute(vi, VI_ATTR_TCPIP_KEEPALIVE, VI_TRUE);
    }
    viSetAttribute(vi, VI_ATTR_TMO_VALUE, timeout);
    return vi;
}


ViSession busOpenDevice_socket(const char *rawip,int timeout_ms)
{
    WSADATA Data;
    int status;
    fd_set rfd;
    FD_ZERO(&rfd);
    struct timeval timeout;  //时间结构体
    BOOL bDontLinger = FALSE;
    timeout.tv_sec = 2;//秒
    timeout.tv_usec = 0;//一百万分之一秒，微
    /* initialize the Windows Socket DLL */
    status = WSAStartup(MAKEWORD(1, 1), &Data);
    if (status != 0)
    {
        return 0;
    }
        
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);//建立套接字
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr(rawip);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(MEGA_TCP_SOCKET_PORT);

    /* connect to the server */
    connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//连接到目的主机
    FD_SET(sockClient, &rfd);
    status = select(0, 0, &rfd, 0, &timeout);
    if (status <= 0)
    {
        closesocket(sockClient);
        WSACleanup();
        return 0;
    }
    setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout_ms, sizeof(int));
    setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout_ms, sizeof(int));
    //在调用closesocket后强制关闭
    setsockopt(sockClient, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL));
    int nZero = 0;
    setsockopt(sockClient, SOL_SOCKET, SO_SNDBUF,(char*)&nZero, sizeof(int));
    setsockopt(sockClient, SOL_SOCKET, SO_RCVBUF,(char*)&nZero, sizeof(int));
    return sockClient;
}
int busOpenDevice(char * viSrc, int timeout)
{
    if (g_bus_type == BUS_SOCKET)
    {
        char *p = NULL;
        char * next = NULL;
        /* ip = TCPIP0::192.168.2.116::inst0::INSTR*/
        p = STRTOK_S(viSrc, "::", &next);
        if (p != NULL)
        {
            p = STRTOK_S(NULL, "::", &next);
        }
        else
        {
            return 0;
        }
        return busOpenDevice_socket(p, timeout);
    }
    else
    {
        return busOpenDevice_vxi(viSrc, timeout);
    }
}
int busCloseDevice(ViSession vi)
{
    if (g_bus_type == BUS_SOCKET)
    {
        return closesocket(vi);
    }
    else
    {
        return viClose(vi);
    }
}

unsigned int busWrite(ViSession vi, char * buf, unsigned int len)
{
    //返回VI_ERROR_CONN_LOST 表示断开连接
    ViUInt32 retCount = 0;
    if (buf == NULL)
    {
        return 0;
    }
    LOCK();
    if (g_bus_type == BUS_SOCKET)
    {
        if ((retCount = send(vi, buf, len, 0)) != len)
        {
            UNLOCK();
            return 0;
        }
    }
    else
    {
        if (viWrite(vi, (ViBuf)buf, len, &retCount) != VI_SUCCESS)
        {
            UNLOCK();
            return 0;
        }
    }
    UNLOCK();
    return retCount;
}

unsigned int busRead(ViSession vi, char * buf, unsigned int len)
{
    //返回VI_ERROR_CONN_LOST 表示断开连接
    ViUInt32 retCount = 0;
    int errCount = 1;
    if (buf == NULL)
    {
        return 0;
    }
    LOCK();
    while(errCount--)
    {
        if (g_bus_type == BUS_SOCKET)
        {
            retCount = recv(vi, buf, len, 0);
        }
        else
        {
            viRead(vi, (ViBuf)buf, len, &retCount);
        }
        
        if(retCount > 0)
        {
            break;
        }
        retCount = 0;
        _msSleep(5);
    }
    if( (retCount == 0) ||  STRNCASECMP(buf, "Command error", strlen("Command error")) == 0 )
    {
        UNLOCK();
        return 0;
    }
    UNLOCK();
    if(buf[retCount-1] == '\n' && buf[0] != '\#')
        buf[retCount-1] = '\0';
    return retCount;
}

unsigned int busQuery(ViSession vi, char * input, unsigned int inputlen,char* output, unsigned int wantlen)
{
    ViUInt32 retCount;
    int errCount = 1;
    if (input == NULL || output == NULL)
    {
        return 0;
    }
    LOCK();
	if (g_bus_type == BUS_SOCKET)
	{
                if ((retCount = send(vi, input, inputlen, 0)) != inputlen)
		{
			UNLOCK();
			return 0;
		}
	}
	else
	{
		if (viWrite(vi, (ViBuf)input, inputlen, &retCount) != VI_SUCCESS)
		{
			UNLOCK();
			return 0;
		}
	}
    while(errCount--)
    {
        if (g_bus_type == BUS_SOCKET)
        {
            retCount = recv(vi, output, wantlen, 0);
        }
        else
        {
            viRead(vi, (ViBuf)output, wantlen, &retCount);
        }
        if(retCount > 0)
        {
            break;
        }
        retCount = 0;
        _msSleep(5);
    }
    if( (retCount == 0) ||  STRNCASECMP(output, "Command error", strlen("Command error")) == 0 )
    {
        UNLOCK();
        return 0;
    }
    UNLOCK();
    if(output[retCount-1] == '\n' && output[0] != '\#')
        output[retCount-1] = '\0';
    return retCount;
}

int getHostIpAddr(char strHostIp[][100])
{
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    PIP_ADAPTER_INFO pIpAdapterInfo = (PIP_ADAPTER_INFO)malloc(stSize);
    int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    int ipcount = 0;
    if (ERROR_BUFFER_OVERFLOW == nRel)
    {
        free(pIpAdapterInfo);
        pIpAdapterInfo = (PIP_ADAPTER_INFO)malloc(stSize);
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
                    strcpy_s(strHostIp[ipcount],100, pIpAddrString->IpAddress.String);
                    ipcount++;
                }
                pIpAddrString = pIpAddrString->Next;
            } while (pIpAddrString);
            pIpAdapterInfo = pIpAdapterInfo->Next;
        }
    }
    if (pIpAdapterInfo)
    {
        free(pIpAdapterInfo);
    }
    return ipcount;
}
#endif //_WIN32

int socketFindResources(char ip[][100],int timeout_ms)
{
#if _WIN32
    WSADATA ws;
#endif
    int ret;
    int count = 0;
    int hostIpCount = 0;
    int i;
    SOCKET sock[256];
    SOCKADDR_IN localAddr;
    SOCKADDR_IN remoteAddr;
    SOCKADDR_IN servaddr;

#ifdef _WIN32
    int len = sizeof(SOCKADDR);
#else
    socklen_t len = sizeof(SOCKADDR);
#endif
    char recvBuf[50];
    
    char strHostIpAddr[256][100];
    hostIpCount = getHostIpAddr(strHostIpAddr);
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
    for (i = 0; i < hostIpCount; i++)
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
        timeout.tv_sec = timeout_ms/1000;
        timeout.tv_usec = (timeout_ms % 1000) * 1000;
        ret = setsockopt(sock[i], SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));
#endif
        if (ret != 0)
        {
            return -1;
        }
#ifdef _WIN32		
        char bOpt = 1;
#else
        int bOpt = 1;
#endif

#ifdef _WIN32
        ret = setsockopt(sock[i], SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));
#else
        ret = setsockopt(sock[i], SOL_SOCKET, SO_BROADCAST | SO_REUSEADDR, (char*)&bOpt, sizeof(bOpt));
#endif
        if(ret != 0)
        {
            return -1;
        }
    }
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(6000);
#ifdef _WIN32
    remoteAddr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");
#else
    remoteAddr.sin_addr.s_addr = inet_addr("255.255.255.255");//htonl(INADDR_ANY);
#endif

    for (i = 0; i < hostIpCount; i++)
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
            }
            else
            {
                break;
            }
        }
    }
    for (i = 0; i < hostIpCount; i++)
    {
#ifdef _WIN32
        shutdown(sock[i], 2);
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





