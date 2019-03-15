#ifndef MR_PROJECT_H
#define MR_PROJECT_H
#include "bus.h"
#include "export.h"
/*
* ����ϵͳΪ����ģʽ
* vi :visa�豸���
* state: 0->OFF| 1->ON
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
* ˵��: ֻ���ڹ���ģʽ��,�������ȡIO״̬
*/
EXPORT_API int CALL mrgSetProjectMode(ViSession vi, int state);
/*
* ��ѯ�ⲿIO��״̬
* vi :visa�豸���
* state: ÿһλ��ʾһ��IO��״̬
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
*/
EXPORT_API int CALL mrgProjectGetXinState(ViSession vi, unsigned int *state);
/*
* ����ϵͳ���ⲿ���IO��״̬
* vi :visa�豸���
* index: 0->YOUT1; 1->YOUT2
* state: 0->low| 1->high
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
* ˵��: ֻ���ڹ���ģʽ��,�������ȡIO״̬
*/
EXPORT_API int CALL mrgProjectSetYout(ViSession vi, int index, int state);
/*
* ����ϵͳ�����к�
* vi :visa�豸���
* serial: ���к�
* ����ֵ��0��ʾִ�гɹ�����1��ʾִ��ʧ��
*/
EXPORT_API int CALL mrgProjectSetSerialNum(ViSession vi, char * serial);
/*
* ��ѯϵͳ�����к�
* vi :visa�豸���
* serial: ���к�
* ����ֵ���������кŵĳ���
*/
EXPORT_API int CALL mrgProjectGetSerialNum(ViSession vi, char * serial);
#endif