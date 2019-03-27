
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"

#define SEND_BUF  (100)

int getXIn(ViSession vi, unsigned int *pScan )
{
    int retlen = 0;
    char args[SEND_BUF];
    char as8Ret[100];

    snprintf(args, SEND_BUF, "PROJECT:XREAD? 0\n" );
    if ((retlen = busQuery(vi, args, strlen(args), as8Ret, 100) ) == 0 )
    {
        return -1;
    }
    *pScan = atoi(as8Ret);
    return 0;
}

//! id from 0
int setYOut(ViSession vi, int id, int v )
{
    char args[SEND_BUF];
    snprintf(args, SEND_BUF, "PROJECT:YWRITE Y%d, %s\n", (id+1), v ? "H":"L");
    if (busWrite(vi, args, strlen(args)) <= 0)
    {
        return -1;
    }
    return 0;
}
