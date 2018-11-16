
#ifndef _BUS_H_
#define _BUS_H_

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

#include "visa.h"
int busFindDevice(char * bus, char *output, int len,int method);
int busOpenDevice(char * ip, int timeout);
ViSession busOpenSocket(const char *pName, const char *addr, unsigned int port);
int busCloseDevice(ViSession vi);
unsigned int busWrite(ViSession vi, char * buf, unsigned int len);
unsigned int busRead(ViSession vi, char * buf, unsigned int len);
unsigned int busQuery(ViSession vi, char * input, unsigned int inputlen, char* output, unsigned int wantlen);

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif


#endif // !_BUS_H_

