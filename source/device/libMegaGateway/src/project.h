#ifndef MR_PROJECT_H
#define MR_PROJECT_H

#include "bus.h"

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*
* ����ϵͳΪ����ģʽ
* vi :visa�豸���
* state: 0->OFF| 1->ON
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
* ˵��: ֻ���ڹ���ģʽ��,�������ȡIO״̬
*/
int mrgSetProjectMode(ViSession vi, int state);
/*
* ��ѯ�ⲿIO��״̬
* vi :visa�豸���
* state: ÿһλ��ʾһ��IO��״̬
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
*/
int mrgProjectGetXinState(ViSession vi, unsigned int *state);
/*
* ����ϵͳ���ⲿ���IO��״̬
* vi :visa�豸���
* index: 0->YOUT1; 1->YOUT2
* state: 0->low| 1->high
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
* ˵��: ֻ���ڹ���ģʽ��,�������ȡIO״̬
*/
int mrgProjectSetYout(ViSession vi, int index, int state);
/*
* ����ϵͳ�����к�
* vi :visa�豸���
* serial: ���к�
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
*/
int mrgProjectSetSerialNum(ViSession vi, char * serial);
/*
* ��ѯϵͳ�����к�
* vi :visa�豸���
* serial: ���к�
* ����ֵ���������кŵĳ���
*/
int mrgProjectGetSerialNum(ViSession vi, char * serial);
/*
* д���豸�����к�
* idn :���ص��豸������
* len��idn���泤��
* ����ֵ��
* ˵�����˺���Ϊ���̽ӿں����������⿪��
*/
 int mrgWriteDeviceSerial(ViSession  vi, int name, char * serial);

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif
