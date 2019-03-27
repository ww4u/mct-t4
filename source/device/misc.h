#ifndef MR_MISC_H
#define MR_MISC_H

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif


#include "bus.h"
//#include "export.h"

int getXIn(ViSession vi, unsigned int *pScan );
int setYOut(ViSession vi, int id, int v );

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // !MR_SYSTEM_H

