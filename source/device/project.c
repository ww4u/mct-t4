#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"


#define SEND_BUF  (100)
/*
* ����ϵͳΪ����ģʽ
* vi :visa�豸���
* state: 0->OFF| 1->ON
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
* ˵��: ֻ���ڹ���ģʽ��,�������ȡIO״̬
*/
EXPORT_API int CALL mrgSetProjectMode(ViSession vi, int state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "PROJect:STATe %s\n", state ? "ON" : "OFF");
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
* ��ѯ�ⲿIO��״̬
* vi :visa�豸���
* state: ÿһλ��ʾһ��IO��״̬
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
*/
EXPORT_API int CALL mrgProjectGetXinState(ViSession vi, unsigned int *state)
{
    char args[SEND_BUF];
    char as8Ret[100];
    int retLen = 0;
    snprintf(args, SEND_BUF, "PROJect:XREAD? 0\n");

    if ((retLen = busQuery(vi, args, strlen(args), as8Ret, 100)) <= 0)
    {
        return -1;
    }
    as8Ret[retLen - 1] = 0;
    *state = strtoul(as8Ret, NULL, 0);
    return 0;
}
/*
* ����ϵͳ���ⲿ���IO��״̬
* vi :visa�豸���
* index: 0->YOUT1; 1->YOUT2
* state: 0->low| 1->high
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
* ˵��: ֻ���ڹ���ģʽ��,�������ȡIO״̬
*/
EXPORT_API int CALL mrgProjectSetYout(ViSession vi, int index, int state)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "PROJect:YWRITE %s,%s\n", index ? "Y2" : "Y1", state ? "H" : "L");
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
* ����ϵͳ�����к�
* vi :visa�豸���
* serial: ���к�
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
*/
EXPORT_API int CALL mrgProjectSetSerialNum(ViSession vi, char * serial)
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "PROJect:SN %s\n", serial);
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
/*
* ��ѯϵͳ�����к�
* vi :visa�豸���
* serial: ���к�
* ����ֵ���������кŵĳ���
*/
EXPORT_API int CALL mrgProjectGetSerialNum(ViSession vi, char * serial)
{
    char args[SEND_BUF];
    char as8Ret[100];
    int retLen = 0;
    snprintf(args, SEND_BUF, "PROJect:SN?\n");

    if ((retLen = busQuery(vi, args, strlen(args), as8Ret, 100)) <= 0)
    {
        return 0;
    }
    as8Ret[retLen - 1] = 0;
    strcpy(serial, as8Ret);
    return retLen-1;
}
