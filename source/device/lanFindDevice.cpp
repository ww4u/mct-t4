#include "lanfinddevice.h"

//#include "stdafx.h"
#include <WINSOCK2.H>
#include <stdio.h>
#include <Ws2tcpip.h> //组播要用到的头文件
#include <string.h>
#define ADD_GROUP//可以不加入组也可以向组内发信息
#define MCASTADDR "224.0.0.251"
#define UDP_PORT  5353//5566
#pragma comment(lib, "ws2_32")

#include <iostream>
#include <IPHlpApi.h>
#pragma comment(lib,"IPHlpApi.lib") //需要添加Iphlpapi.lib库

//#define DEBUG_INFO printf("%s,%s,%d\n",__FILE__,__func__,__LINE__)

using namespace std;

int getHostIpAddr(string* strHostIp, unsigned int len);

#if 1
/*
    timeout 一次查询设备的最长时间
    desc :查询到的设备描述符
    返回找到的仪器的个数
*/
int findResources(char* ip,int timeout)
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

	hostIpCount = getHostIpAddr(strHostIpAddr, 1024);
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


int getHostIpAddr(string* strHostIp, unsigned int len)
{
	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
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
		delete pIpAdapterInfo;
		//重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
		//输出网卡信息
		//可能有多网卡,因此通过循环去判断
		while (pIpAdapterInfo)
		{			
			IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);

			do
			{
				//cout << "该网卡上的IP数量：" << ++IPnumPerNetCard << endl;
				//cout << "IP 地址：" << pIpAddrString->IpAddress.String << endl;
				//cout << "子网地址：" << pIpAddrString->IpMask.String << endl;
				//cout << "网关地址：" << pIpAdapterInfo->GatewayList.IpAddress.String << endl;

				if (strcmp("0.0.0.0", pIpAddrString->IpAddress.String) == 0)
				{

				}
				else
				{
					strHostIp[ipcount] = string(pIpAddrString->IpAddress.String);
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
		delete pIpAdapterInfo;
	}

	return ipcount;
}
