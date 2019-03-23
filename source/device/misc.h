#ifndef MR_MISC_H
#define MR_MISC_H

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif


#include "bus.h"
#include "export.h"

EXPORT_API int CALL getXIn(ViSession vi, unsigned int *pScan );
EXPORT_API int CALL setYOut(ViSession vi, int id, int v );

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif // !MR_SYSTEM_H

