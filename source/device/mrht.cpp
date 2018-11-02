#include "mrht.h"



int _write(ViSession vi, char *cmd, unsigned int cmdlen)
{
    ViStatus status = 0;
    ViUInt32 retCnt = 0;

    status = viWrite(vi, (ViBuf)cmd, cmdlen, &retCnt);
    if(status != VI_SUCCESS)
    {
        return status;
    }
    
    return retCnt;
}




int _query(ViSession vi, char *cmd, unsigned int cmdlen, char *buf, unsigned int buflen)
{
    ViStatus status = 0;
    ViUInt32 retCnt = 0;

    status = viWrite(vi, (ViBuf)cmd, cmdlen, &retCnt);
    if(status != VI_SUCCESS)
    {
        return status;
    }
    
    status = viRead(vi, (ViPBuf)buf, buflen, &retCnt);
    if(status != VI_SUCCESS)
    {
        return status;
    }

    buf[retCnt - 1] = 0;
    return retCnt;

}


//! *IDN?
int mrhtIdn_Query(int inst, char* data,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8data = data;


    sprintf(as8FmtCmd, "*IDN?");
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8data, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :TRIGger:SEARch?
int mrhtTriggerSearch_Query(int inst, char* file,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8file = file;


    sprintf(as8FmtCmd, ":TRIGger:SEARch?");
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8file, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :TRIGger:CONFig <file>,<file>,<file>,<file>,<file>
int mrhtTriggerConfig(int inst,char* file1,char* file2,char* file3,char* file4,char* file5)
{
    char as8FmtCmd[100] = {0};


    char* ps8file1 = file1;

    char* ps8file2 = file2;

    char* ps8file3 = file3;

    char* ps8file4 = file4;

    char* ps8file5 = file5;

    sprintf(as8FmtCmd, ":TRIGger:CONFig %s,%s,%s,%s,%s",ps8file1,ps8file2,ps8file3,ps8file4,ps8file5);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :TRIGger:SAVe
int mrhtTriggerSave(int inst)
{
    char as8FmtCmd[100] = {0};


    sprintf(as8FmtCmd, ":TRIGger:SAVe");
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:SEARch
int mrhtDeviceSearch(int inst)
{
    char as8FmtCmd[100] = {0};


    sprintf(as8FmtCmd, ":DEVice:SEARch");
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:COUNt?
int mrhtDeviceCount_Query(int inst, int* count)
{
    char as8FmtCmd[100] = {0};
    char as8count[100] = {0};


    sprintf(as8FmtCmd, ":DEVice:COUNt?");
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8count, 100) == 0)
    {
        return -1;
    }
    
    *count = atoi(as8count);
    return 0;
}




//! :DEVice:TYPe? <name>
int mrhtDeviceType_Query(int inst,int name, char* type,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8type = type;

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:TYPe? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8type, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:NAMe?
int mrhtDeviceName_Query(int inst, int* name)
{
    char as8FmtCmd[100] = {0};
    char as8name[100] = {0};


    sprintf(as8FmtCmd, ":DEVice:NAMe?");
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8name, 100) == 0)
    {
        return -1;
    }
    
    *name = atoi(as8name);
    return 0;
}




//! :DEVice:CHANnel:COUNt? <name>
int mrhtDeviceChannelCount_Query(int inst,int name, int* chanNum)
{
    char as8FmtCmd[100] = {0};
    char as8chanNum[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:CHANnel:COUNt? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8chanNum, 100) == 0)
    {
        return -1;
    }
    
    *chanNum = atoi(as8chanNum);
    return 0;
}




//! :DEVice:FIRMware:ALL?  <name>
int mrhtDeviceFirmwareAll_Query(int inst,int name, char* firmware,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8firmware = firmware;

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:FIRMware:ALL? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8firmware, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:FIRMware:HARD?  <name>
int mrhtDeviceFirmwareHard_Query(int inst,int name, char* hard,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8hard = hard;

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:FIRMware:HARD? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8hard, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:FIRMware:SOFT?  <name>
int mrhtDeviceFirmwareSoft_Query(int inst,int name, char* soft,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8soft = soft;

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:FIRMware:SOFT? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8soft, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:FIRMware:SN?  <name>
int mrhtDeviceFirmwareSn_Query(int inst,int name, char* sn,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8sn = sn;

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:FIRMware:SN? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8sn, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:FIRMware:BOOT?  <name>
int mrhtDeviceFirmwareBoot_Query(int inst,int name , char* boot,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8boot = boot;

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:FIRMware:BOOT? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8boot, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:FIRMware:FPGA?  <name>
int mrhtDeviceFirmwareFpga_Query(int inst,int name , char* fpga,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8fpga = fpga;

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:FIRMware:FPGA? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8fpga, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:IDENtify <name>,<OFF|ON>
int mrhtDeviceMrqIdentify(int inst,int name,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "OFF";
    }
    else if(state == 1)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:IDENtify %d,%s",s32name,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:STATe:REPORt <name>,<ch>,<ACTIVE|QUERY>
int mrhtDeviceMrqMotionStateReport(int inst,int name,int chan,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "ACTIVE";
    }
    else if(state == 1)
    {
        ps8state = "QUERY";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:STATe:REPORt %d,%d,%s",s32name,s32chan,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:STATe:REPORt? <name>,<ch>
int mrhtDeviceMrqMotionStateReport_Query(int inst,int name,int chan, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:STATe:REPORt? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "ACTIVE") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "QUERY") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:MOTion:RUN <name>,<ch>,<<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>>
int mrhtDeviceMrqMotionRun(int inst,int name,int chan,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:RUN %d,%d,%s",s32name,s32chan,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:RUN:STATe? <name>,<ch>,<<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>>
int mrhtDeviceMrqMotionRunState_Query(int inst,int name,int chan,int wave, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:RUN:STATe? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "ERROR") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "READY") == 0)
    {
        *state = 1;
    }

    else if(strcmp(as8state, "LOADING") == 0)
    {
        *state = 2;
    }

    else if(strcmp(as8state, "IDLE") == 0)
    {
        *state = 3;
    }

    else if(strcmp(as8state, "RUNNING") == 0)
    {
        *state = 4;
    }

    return 0;
}




//! :DEVice:MRQ:MOTion:STOP <name>,<ch>,<<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>>
int mrhtDeviceMrqMotionStop(int inst,int name,int chan,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:STOP %d,%d,%s",s32name,s32chan,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:TRIGger[:SOURce] <name>,<ch>,<SOFTWARE|DIGITALIO|CAN|ALL>
int mrhtDeviceMrqMotionTriggerSource(int inst,int name,int chan,int trigSource)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8trigSource = NULL;
    if(trigSource == 0)
    {
        ps8trigSource = "SOFTWARE";
    }
    else if(trigSource == 1)
    {
        ps8trigSource = "DIGITALIO";
    }
    else if(trigSource == 2)
    {
        ps8trigSource = "CAN";
    }
    else if(trigSource == 3)
    {
        ps8trigSource = "ALL";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:TRIGger:SOURce %d,%d,%s",s32name,s32chan,ps8trigSource);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:TRIGger[:SOURce]? <name>,<ch>
int mrhtDeviceMrqMotionTriggerSource_Query(int inst,int name,int chan, int* trig)
{
    char as8FmtCmd[100] = {0};
    char as8trig[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:TRIGger:SOURce? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8trig, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8trig, "SOFTWARE") == 0)
    {
        *trig = 0;
    }

    else if(strcmp(as8trig, "DIGITALIO") == 0)
    {
        *trig = 1;
    }

    else if(strcmp(as8trig, "CAN") == 0)
    {
        *trig = 2;
    }

    else if(strcmp(as8trig, "ALL") == 0)
    {
        *trig = 3;
    }

    return 0;
}




//! :DEVice:MRQ:MOTion:OFFSet[:STATe] <name>,<ch>,<OFF|ON>
int mrhtDeviceMrqMotionOffsetState(int inst,int name,int chan,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "OFF";
    }
    else if(state == 1)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:OFFSet:STATe %d,%d,%s",s32name,s32chan,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:OFFSet[:STATe]? <name>,<ch>
int mrhtDeviceMrqMotionOffsetState_Query(int inst,int name,int chan, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:OFFSet:STATe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "OFF") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "ON") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:MOTion:OFFSet:VALue? <name>,<ch>
int mrhtDeviceMrqMotionOffsetValue_Query(int inst, char* value,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8value = value;


    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:OFFSet:VALue? ");
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8value, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:ABCOUNt? <name>,<ch>
int mrhtDeviceMrqMotionAbcount_Query(int inst,int name,int chan, int* count)
{
    char as8FmtCmd[100] = {0};
    char as8count[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:ABCOUNt? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8count, 100) == 0)
    {
        return -1;
    }
    
    *count = atoi(as8count);
    return 0;
}




//! :DEVice:MRQ:MOTion:ABCOUNt:CLEAr <name>,<ch>
int mrhtDeviceMrqMotionAbcountClear(int inst,int name,int chan)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:ABCOUNt:CLEAr %d,%d",s32name,s32chan);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:ADJust <name>,<CH>,<position>,<time>
int mrhtDeviceMrqMotionAdjust(int inst,int name,int chan,int position,int time)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32position = position;
    int s32time = time;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:ADJust %d,%d,%d,%d",s32name,s32chan,s32position,s32time);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:REVERSe <name>,<OFF|ON>
int mrhtDeviceMrqMotionReverse(int inst,int name,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "OFF";
    }
    else if(state == 1)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:REVERSe %d,%s",s32name,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTion:REVERSe? <name>
int mrhtDeviceMrqMotionReverse_Query(int inst,int name, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTion:REVERSe? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "OFF") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "ON") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:MOTOR:STEP:ANGLe <name>,<CH>,<1.8|0.9|15|7.5>
int mrhtDeviceMrqMotorStepAngle(int inst,int name,int chan,int step)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8step = NULL;
    if(step == 0)
    {
        ps8step = "1.8";
    }
    else if(step == 1)
    {
        ps8step = "0.9";
    }
    else if(step == 2)
    {
        ps8step = "15";
    }
    else if(step == 3)
    {
        ps8step = "7.5";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:STEP:ANGLe %d,%d,%s",s32name,s32chan,ps8step);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTOR:STEP:ANGLe? <name>,<CH>
int mrhtDeviceMrqMotorStepAngle_Query(int inst,int name,int chan, int* step)
{
    char as8FmtCmd[100] = {0};
    char as8step[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:STEP:ANGLe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8step, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8step, "1.8") == 0)
    {
        *step = 0;
    }

    else if(strcmp(as8step, "0.9") == 0)
    {
        *step = 1;
    }

    else if(strcmp(as8step, "15") == 0)
    {
        *step = 2;
    }

    else if(strcmp(as8step, "7.5") == 0)
    {
        *step = 3;
    }

    return 0;
}




//! :DEVice:MRQ:MOTOR:MOTion:TYPe <name>,<CH>,<ROTARY|LINEAR>
int mrhtDeviceMrqMotorMotionType(int inst,int name,int chan,int motion)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8motion = NULL;
    if(motion == 0)
    {
        ps8motion = "ROTARY";
    }
    else if(motion == 1)
    {
        ps8motion = "LINEAR";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:MOTion:TYPe %d,%d,%s",s32name,s32chan,ps8motion);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTOR:MOTion:TYPe? <name>,<CH>
int mrhtDeviceMrqMotorMotionType_Query(int inst,int name,int chan, int* motion)
{
    char as8FmtCmd[100] = {0};
    char as8motion[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:MOTion:TYPe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8motion, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8motion, "ROTARY") == 0)
    {
        *motion = 0;
    }

    else if(strcmp(as8motion, "LINEAR") == 0)
    {
        *motion = 1;
    }

    return 0;
}




//! :DEVice:MRQ:MOTOR:POSition:UNIT <name>,<CH>,<ANGLE|RADIAN|MILLIMETER>
int mrhtDeviceMrqMotorPositionUnit(int inst,int name,int chan,int pos)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8pos = NULL;
    if(pos == 0)
    {
        ps8pos = "ANGLE";
    }
    else if(pos == 1)
    {
        ps8pos = "RADIAN";
    }
    else if(pos == 2)
    {
        ps8pos = "MILLIMETER";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:POSition:UNIT %d,%d,%s",s32name,s32chan,ps8pos);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTOR:POSition:UNIT? <name>,<CH>
int mrhtDeviceMrqMotorPositionUnit_Query(int inst,int name,int chan, int* pos)
{
    char as8FmtCmd[100] = {0};
    char as8pos[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:POSition:UNIT? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8pos, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8pos, "ANGLE") == 0)
    {
        *pos = 0;
    }

    else if(strcmp(as8pos, "RADIAN") == 0)
    {
        *pos = 1;
    }

    else if(strcmp(as8pos, "MILLIMETER") == 0)
    {
        *pos = 2;
    }

    return 0;
}




//! :DEVice:MRQ:MOTOR:GEAR:RATio <name>,<CH>,<above>,<below>
int mrhtDeviceMrqMotorGearRatio(int inst,int name,int chan,int above,int below)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32above = above;
    int s32below = below;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:GEAR:RATio %d,%d,%d,%d",s32name,s32chan,s32above,s32below);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTOR:GEAR:RATio? <name>,<CH>
int mrhtDeviceMrqMotorGearRatio_Query(int inst,int name,int chan, int* above,int* below)
{
    char as8FmtCmd[100] = {0};
    char as8above[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:GEAR:RATio? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8above, 100) == 0)
    {
        return -1;
    }
    
    char* ps8Delims = ",";
    char* result = NULL;
    char* ret[10] = {NULL};
    int count = 0;
    result = strtok(as8above, ps8Delims);
    while(result != NULL)
    {
        ret[count] = result;
        count++;
        result = strtok(NULL, ps8Delims);
    }

    *above = atoi(ret[0]);
    *below = atoi(ret[1]);

    return 0;
}




//! :DEVice:MRQ:MOTOR:LEAD <name>,<CH>,<millimeter>
int mrhtDeviceMrqMotorLead(int inst,int name,int chan,int mm)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32mm = mm;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:LEAD %d,%d,%d",s32name,s32chan,s32mm);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTOR:LEAD? <name>,<CH>
int mrhtDeviceMrqMotorLead_Query(int inst,int name,int chan, int* mm)
{
    char as8FmtCmd[100] = {0};
    char as8mm[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:LEAD? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8mm, 100) == 0)
    {
        return -1;
    }
    
    *mm = atoi(as8mm);
    return 0;
}




//! :DEVice:MRQ:MOTOR:SIZE <name>,<CH>,<8|11|14|17|23|24>
int mrhtDeviceMrqMotorSize(int inst,int name,int chan,int size)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8size = NULL;
    if(size == 0)
    {
        ps8size = "8";
    }
    else if(size == 1)
    {
        ps8size = "11";
    }
    else if(size == 2)
    {
        ps8size = "14";
    }
    else if(size == 3)
    {
        ps8size = "17";
    }
    else if(size == 4)
    {
        ps8size = "23";
    }
    else if(size == 5)
    {
        ps8size = "24";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:SIZE %d,%d,%s",s32name,s32chan,ps8size);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTOR:SIZE? <name>,<CH>
int mrhtDeviceMrqMotorSize_Query(int inst,int name,int chan, int* size)
{
    char as8FmtCmd[100] = {0};
    char as8size[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:SIZE? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8size, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8size, "8") == 0)
    {
        *size = 0;
    }

    else if(strcmp(as8size, "11") == 0)
    {
        *size = 1;
    }

    else if(strcmp(as8size, "14") == 0)
    {
        *size = 2;
    }

    else if(strcmp(as8size, "17") == 0)
    {
        *size = 3;
    }

    else if(strcmp(as8size, "23") == 0)
    {
        *size = 4;
    }

    else if(strcmp(as8size, "24") == 0)
    {
        *size = 5;
    }

    return 0;
}




//! :DEVice:MRQ:MOTOR:VOLTage <name>,<CH>,<volt>
int mrhtDeviceMrqMotorVoltage(int inst,int name,int chan,int volt)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32volt = volt;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:VOLTage %d,%d,%d",s32name,s32chan,s32volt);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTOR:VOLTage? <name>,<CH>
int mrhtDeviceMrqMotorVoltage_Query(int inst,int name,int chan, int* volt)
{
    char as8FmtCmd[100] = {0};
    char as8volt[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:VOLTage? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8volt, 100) == 0)
    {
        return -1;
    }
    
    *volt = atoi(as8volt);
    return 0;
}




//! :DEVice:MRQ:MOTOR:CURRent <name>,<CH>,<current>
int mrhtDeviceMrqMotorCurrent(int inst,int name,int chan,int curr)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32curr = curr;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:CURRent %d,%d,%d",s32name,s32chan,s32curr);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTOR:CURRent? <name>,<CH>
int mrhtDeviceMrqMotorCurrent_Query(int inst,int name,int chan, int* curr)
{
    char as8FmtCmd[100] = {0};
    char as8curr[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:CURRent? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8curr, 100) == 0)
    {
        return -1;
    }
    
    *curr = atoi(as8curr);
    return 0;
}




//! :DEVice:MRQ:MOTOR:BACKLash <name>,<CH>,<lash>
int mrhtDeviceMrqMotorBacklash(int inst,int name,int chan,int lash)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32lash = lash;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:BACKLash %d,%d,%d",s32name,s32chan,s32lash);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:MOTOR:BACKLash? <name>,<CH>
int mrhtDeviceMrqMotorBacklash_Query(int inst,int name,int chan, int* lash)
{
    char as8FmtCmd[100] = {0};
    char as8lash[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:MOTOR:BACKLash? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8lash, 100) == 0)
    {
        return -1;
    }
    
    *lash = atoi(as8lash);
    return 0;
}




//! :DEVice:MRQ:PVT:CONFig <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<END|CLEAR>
int mrhtDeviceMrqPvtConfig(int inst,int name,int chan,int wave,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "END";
    }
    else if(state == 1)
    {
        ps8state = "CLEAR";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:CONFig %d,%d,%s,%s",s32name,s32chan,ps8wave,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:VALue <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<p>,<v>,<t>
int mrhtDeviceMrqPvtValue(int inst,int name,int chan,int wave,double p,double v,double t)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }
    double f64p = p;
    double f64v = v;
    double f64t = t;

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:VALue %d,%d,%s,%f,%f,%f",s32name,s32chan,ps8wave,f64p,f64v,f64t);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:STATe? <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtState_Query(int inst,int name,int chan,int wave, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:STATe? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "ERROR") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "READY") == 0)
    {
        *state = 1;
    }

    else if(strcmp(as8state, "LOADING") == 0)
    {
        *state = 2;
    }

    else if(strcmp(as8state, "IDLE") == 0)
    {
        *state = 3;
    }

    else if(strcmp(as8state, "RUNNING") == 0)
    {
        *state = 4;
    }

    return 0;
}




//! :DEVice:MRQ:PVT:TSCale <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<speedup>,<speedcut>
int mrhtDeviceMrqPvtTscale(int inst,int name,int chan,int wave,int speedup,int speedcut)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }
    int s32speedup = speedup;
    int s32speedcut = speedcut;

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:TSCale %d,%d,%s,%d,%d",s32name,s32chan,ps8wave,s32speedup,s32speedcut);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:MODe:EXE <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<CYCLE|FIFO>
int mrhtDeviceMrqPvtModeExe(int inst,int name,int chan,int wave,int exe)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    char* ps8exe = NULL;
    if(exe == 0)
    {
        ps8exe = "CYCLE";
    }
    else if(exe == 1)
    {
        ps8exe = "FIFO";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:MODe:EXE %d,%d,%s,%s",s32name,s32chan,ps8wave,ps8exe);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:MODe:EXE? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtModeExe_Query(int inst,int name,int chan,int wave, int* exe)
{
    char as8FmtCmd[100] = {0};
    char as8exe[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:MODe:EXE? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8exe, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8exe, "CYCLE") == 0)
    {
        *exe = 0;
    }

    else if(strcmp(as8exe, "FIFO") == 0)
    {
        *exe = 1;
    }

    return 0;
}




//! :DEVice:MRQ:PVT:MODe:PLAN <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<CUBICPOLY|LINEAR|UNIFORM|TRAPEZOID>
int mrhtDeviceMrqPvtModePlan(int inst,int name,int chan,int wave,int plan)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    char* ps8plan = NULL;
    if(plan == 0)
    {
        ps8plan = "CUBICPOLY";
    }
    else if(plan == 1)
    {
        ps8plan = "LINEAR";
    }
    else if(plan == 2)
    {
        ps8plan = "UNIFORM";
    }
    else if(plan == 3)
    {
        ps8plan = "TRAPEZOID";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:MODe:PLAN %d,%d,%s,%s",s32name,s32chan,ps8wave,ps8plan);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:MODe:PLAN? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtModePlan_Query(int inst,int name,int chan,int wave, int* plan)
{
    char as8FmtCmd[100] = {0};
    char as8plan[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:MODe:PLAN? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8plan, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8plan, "CUBICPOLY") == 0)
    {
        *plan = 0;
    }

    else if(strcmp(as8plan, "LINEAR") == 0)
    {
        *plan = 1;
    }

    else if(strcmp(as8plan, "UNIFORM") == 0)
    {
        *plan = 2;
    }

    else if(strcmp(as8plan, "TRAPEZOID") == 0)
    {
        *plan = 3;
    }

    return 0;
}




//! :DEVice:MRQ:PVT:MODe:MOTion <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<PVT|LVT_CORRECT|LVT_NOCORRECT>
int mrhtDeviceMrqPvtModeMotion(int inst,int name,int chan,int wave,int motion)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    char* ps8motion = NULL;
    if(motion == 0)
    {
        ps8motion = "PVT";
    }
    else if(motion == 1)
    {
        ps8motion = "LVT_CORRECT";
    }
    else if(motion == 2)
    {
        ps8motion = "LVT_NOCORRECT";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:MODe:MOTion %d,%d,%s,%s",s32name,s32chan,ps8wave,ps8motion);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:MODe:MOTion? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtModeMotion_Query(int inst,int name,int chan,int wave, int* motion)
{
    char as8FmtCmd[100] = {0};
    char as8motion[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:MODe:MOTion? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8motion, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8motion, "PVT") == 0)
    {
        *motion = 0;
    }

    else if(strcmp(as8motion, "LVT_CORRECT") == 0)
    {
        *motion = 1;
    }

    else if(strcmp(as8motion, "LVT_NOCORRECT") == 0)
    {
        *motion = 2;
    }

    return 0;
}




//! :DEVice:MRQ:PVT:MODIFy:DUTY <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<1/4|1/8|1/16|1/32>
int mrhtDeviceMrqPvtModifyDuty(int inst,int name,int chan,int wave,int duty)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    char* ps8duty = NULL;
    if(duty == 0)
    {
        ps8duty = "1/4";
    }
    else if(duty == 1)
    {
        ps8duty = "1/8";
    }
    else if(duty == 2)
    {
        ps8duty = "1/16";
    }
    else if(duty == 3)
    {
        ps8duty = "1/32";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:MODIFy:DUTY %d,%d,%s,%s",s32name,s32chan,ps8wave,ps8duty);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:MODIFy:DUTY? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtModifyDuty_Query(int inst,int name,int chan,int wave, int* duty)
{
    char as8FmtCmd[100] = {0};
    char as8duty[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:MODIFy:DUTY? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8duty, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8duty, "1/4") == 0)
    {
        *duty = 0;
    }

    else if(strcmp(as8duty, "1/8") == 0)
    {
        *duty = 1;
    }

    else if(strcmp(as8duty, "1/16") == 0)
    {
        *duty = 2;
    }

    else if(strcmp(as8duty, "1/32") == 0)
    {
        *duty = 3;
    }

    return 0;
}




//! :DEVice:MRQ:PVT:END:STATe <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<STOP|HOLD>
int mrhtDeviceMrqPvtEndState(int inst,int name,int chan,int wave,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "STOP";
    }
    else if(state == 1)
    {
        ps8state = "HOLD";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:END:STATe %d,%d,%s,%s",s32name,s32chan,ps8wave,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:END:STATe? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtEndState_Query(int inst,int name,int chan,int wave, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:END:STATe? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "STOP") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "HOLD") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:PVT:ADEC:SCALe <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<scaleA>,<scaleD>
int mrhtDeviceMrqPvtAdecScale(int inst,int name,int chan,int wave,int scaleA,int scaleD)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }
    int s32scaleA = scaleA;
    int s32scaleD = scaleD;

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:ADEC:SCALe %d,%d,%s,%d,%d",s32name,s32chan,ps8wave,s32scaleA,s32scaleD);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:ADEC:SCALe? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtAdecScale_Query(int inst,int name,int chan,int wave, int* scaleA,int* scaleD)
{
    char as8FmtCmd[100] = {0};
    char as8scaleA[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:ADEC:SCALe? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8scaleA, 100) == 0)
    {
        return -1;
    }
    
    char* ps8Delims = ",";
    char* result = NULL;
    char* ret[10] = {NULL};
    int count = 0;
    result = strtok(as8scaleA, ps8Delims);
    while(result != NULL)
    {
        ret[count] = result;
        count++;
        result = strtok(NULL, ps8Delims);
    }

    *scaleA = atoi(ret[0]);
    *scaleD = atoi(ret[1]);

    return 0;
}




//! :DEVice:MRQ:PVT:STOP:MODe <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,< IMMEDIATE|DISTANCE>
int mrhtDeviceMrqPvtStopMode(int inst,int name,int chan,int wave,int mode)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    char* ps8mode = NULL;
    if(mode == 0)
    {
        ps8mode = "";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:STOP:MODe %d,%d,%s,%s",s32name,s32chan,ps8wave,ps8mode);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:STOP:MODe? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtStopMode_Query(int inst,int name,int chan,int wave, int* mode)
{
    char as8FmtCmd[100] = {0};
    char as8mode[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:STOP:MODe? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8mode, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8mode, " IMMEDIATE") == 0)
    {
        *mode = 0;
    }

    else if(strcmp(as8mode, "DISTANCE") == 0)
    {
        *mode = 1;
    }

    return 0;
}




//! :DEVice:MRQ:PVT:STOP:DISTance <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<dist>
int mrhtDeviceMrqPvtStopDistance(int inst,int name,int chan,int wave,int dist)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }
    int s32dist = dist;

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:STOP:DISTance %d,%d,%s,%d",s32name,s32chan,ps8wave,s32dist);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:PVT:STOP:DISTance? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtStopDistance_Query(int inst,int name,int chan,int wave, int* dist)
{
    char as8FmtCmd[100] = {0};
    char as8dist[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:PVT:STOP:DISTance? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8dist, 100) == 0)
    {
        return -1;
    }
    
    *dist = atoi(as8dist);
    return 0;
}




//! :DEVice:MRQ:LOSTstep:LINe:STATe <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<OFF|ON>
int mrhtDeviceMrqLoststepLineState(int inst,int name,int chan,int wave,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "OFF";
    }
    else if(state == 1)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:LOSTstep:LINe:STATe %d,%d,%s,%s",s32name,s32chan,ps8wave,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:LOSTstep:LINe:STATe? <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqLoststepLineState_Query(int inst,int name,int chan,int wave, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:LOSTstep:LINe:STATe? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "OFF") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "ON") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:LOSTstep:LINe:THREShold <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<value>
int mrhtDeviceMrqLoststepLineThreshold(int inst,int name,int chan,int wave,int value)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }
    int s32value = value;

    sprintf(as8FmtCmd, ":DEVice:MRQ:LOSTstep:LINe:THREShold %d,%d,%s,%d",s32name,s32chan,ps8wave,s32value);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:LOSTstep:LINe:THREShold? <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqLoststepLineThreshold_Query(int inst,int name,int chan,int wave, int* value)
{
    char as8FmtCmd[100] = {0};
    char as8value[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:LOSTstep:LINe:THREShold? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8value, 100) == 0)
    {
        return -1;
    }
    
    *value = atoi(as8value);
    return 0;
}




//! :DEVice:MRQ:LOSTstep:LINe:RESPonse <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<NONE|ALARM|STOP|ALARM&STOP>
int mrhtDeviceMrqLoststepLineResponse(int inst,int name,int chan,int wave,int resp)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    char* ps8resp = NULL;
    if(resp == 0)
    {
        ps8resp = "NONE";
    }
    else if(resp == 1)
    {
        ps8resp = "ALARM";
    }
    else if(resp == 2)
    {
        ps8resp = "STOP";
    }
    else if(resp == 3)
    {
        ps8resp = "ALARM&STOP";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:LOSTstep:LINe:RESPonse %d,%d,%s,%s",s32name,s32chan,ps8wave,ps8resp);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:LOSTstep:LINe:RESPonse? <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqLoststepLineResponse_Query(int inst,int name,int chan,int wave, int* resp)
{
    char as8FmtCmd[100] = {0};
    char as8resp[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:LOSTstep:LINe:RESPonse? %d,%d,%s",s32name,s32chan,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8resp, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8resp, "NONE") == 0)
    {
        *resp = 0;
    }

    else if(strcmp(as8resp, "ALARM") == 0)
    {
        *resp = 1;
    }

    else if(strcmp(as8resp, "STOP") == 0)
    {
        *resp = 2;
    }

    else if(strcmp(as8resp, "ALARM&STOP") == 0)
    {
        *resp = 3;
    }

    return 0;
}




//! :DEVice:MRQ:REPort:STATe <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>,<OFF|ON>
int mrhtDeviceMrqReportState(int inst,int name,int chan,int index,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8index = NULL;
    if(index == 0)
    {
        ps8index = "TORQUE";
    }
    else if(index == 1)
    {
        ps8index = "CYCLE";
    }
    else if(index == 2)
    {
        ps8index = "SGALL";
    }
    else if(index == 3)
    {
        ps8index = "SGSE";
    }
    else if(index == 4)
    {
        ps8index = "DIST";
    }
    else if(index == 5)
    {
        ps8index = "ABSEN";
    }

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "OFF";
    }
    else if(state == 1)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:REPort:STATe %d,%d,%s,%s",s32name,s32chan,ps8index,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:REPort:STATe? <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>
int mrhtDeviceMrqReportState_Query(int inst,int name,int chan,int index, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8index = NULL;
    if(index == 0)
    {
        ps8index = "TORQUE";
    }
    else if(index == 1)
    {
        ps8index = "CYCLE";
    }
    else if(index == 2)
    {
        ps8index = "SGALL";
    }
    else if(index == 3)
    {
        ps8index = "SGSE";
    }
    else if(index == 4)
    {
        ps8index = "DIST";
    }
    else if(index == 5)
    {
        ps8index = "ABSEN";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:REPort:STATe? %d,%d,%s",s32name,s32chan,ps8index);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "OFF") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "ON") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:REPort:PERiod <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>,<ms>
int mrhtDeviceMrqReportPeriod(int inst,int name,int chan,int index,int ms)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8index = NULL;
    if(index == 0)
    {
        ps8index = "TORQUE";
    }
    else if(index == 1)
    {
        ps8index = "CYCLE";
    }
    else if(index == 2)
    {
        ps8index = "SGALL";
    }
    else if(index == 3)
    {
        ps8index = "SGSE";
    }
    else if(index == 4)
    {
        ps8index = "DIST";
    }
    else if(index == 5)
    {
        ps8index = "ABSEN";
    }
    int s32ms = ms;

    sprintf(as8FmtCmd, ":DEVice:MRQ:REPort:PERiod %d,%d,%s,%d",s32name,s32chan,ps8index,s32ms);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:REPort:PERiod? <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>
int mrhtDeviceMrqReportPeriod_Query(int inst,int name,int chan,int index, int* ms)
{
    char as8FmtCmd[100] = {0};
    char as8ms[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8index = NULL;
    if(index == 0)
    {
        ps8index = "TORQUE";
    }
    else if(index == 1)
    {
        ps8index = "CYCLE";
    }
    else if(index == 2)
    {
        ps8index = "SGALL";
    }
    else if(index == 3)
    {
        ps8index = "SGSE";
    }
    else if(index == 4)
    {
        ps8index = "DIST";
    }
    else if(index == 5)
    {
        ps8index = "ABSEN";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:REPort:PERiod? %d,%d,%s",s32name,s32chan,ps8index);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8ms, 100) == 0)
    {
        return -1;
    }
    
    *ms = atoi(as8ms);
    return 0;
}




//! :DEVice:MRQ:REPort:DATA? <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>
int mrhtDeviceMrqReportData_Query(int inst,int name,int chan,int index, char* data,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8data = data;

    int s32name = name;
    int s32chan = chan;

    char* ps8index = NULL;
    if(index == 0)
    {
        ps8index = "TORQUE";
    }
    else if(index == 1)
    {
        ps8index = "CYCLE";
    }
    else if(index == 2)
    {
        ps8index = "SGALL";
    }
    else if(index == 3)
    {
        ps8index = "SGSE";
    }
    else if(index == 4)
    {
        ps8index = "DIST";
    }
    else if(index == 5)
    {
        ps8index = "ABSEN";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:REPort:DATA? %d,%d,%s",s32name,s32chan,ps8index);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8data, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:TRIGger:MODe <name>,<ch>,<PATTERN|LEVEL>
int mrhtDeviceMrqTriggerMode(int inst,int name,int chan,int mode)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8mode = NULL;
    if(mode == 0)
    {
        ps8mode = "PATTERN";
    }
    else if(mode == 1)
    {
        ps8mode = "LEVEL";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:MODe %d,%d,%s",s32name,s32chan,ps8mode);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:TRIGger:MODe? <name>,<ch>
int mrhtDeviceMrqTriggerMode_Query(int inst,int name,int chan, int* mode)
{
    char as8FmtCmd[100] = {0};
    char as8mode[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:MODe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8mode, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8mode, "PATTERN") == 0)
    {
        *mode = 0;
    }

    else if(strcmp(as8mode, "LEVEL") == 0)
    {
        *mode = 1;
    }

    return 0;
}




//! :DEVice:MRQ:TRIGger:LEVel:STATe <name>,<ch>,<TRIGL|TRIGR>,<OFF|ON>
int mrhtDeviceMrqTriggerLevelState(int inst,int name,int chan,int trig,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8trig = NULL;
    if(trig == 0)
    {
        ps8trig = "TRIGL";
    }
    else if(trig == 1)
    {
        ps8trig = "TRIGR";
    }

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "OFF";
    }
    else if(state == 1)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:LEVel:STATe %d,%d,%s,%s",s32name,s32chan,ps8trig,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:TRIGger:LEVel:STATe? <name>,<ch>,<TRIGL|TRIGR>
int mrhtDeviceMrqTriggerLevelState_Query(int inst,int name,int chan,int trig, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8trig = NULL;
    if(trig == 0)
    {
        ps8trig = "TRIGL";
    }
    else if(trig == 1)
    {
        ps8trig = "TRIGR";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:LEVel:STATe? %d,%d,%s",s32name,s32chan,ps8trig);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "OFF") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "ON") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:TRIGger:LEVel:TYPe <name>,<ch>,<TRIGL|TRIGR>,<RESERVE|LOW|RISE|FALL|HIGH>
int mrhtDeviceMrqTriggerLevelType(int inst,int name,int chan,int trig,int type)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8trig = NULL;
    if(trig == 0)
    {
        ps8trig = "TRIGL";
    }
    else if(trig == 1)
    {
        ps8trig = "TRIGR";
    }

    char* ps8type = NULL;
    if(type == 0)
    {
        ps8type = "RESERVE";
    }
    else if(type == 1)
    {
        ps8type = "LOW";
    }
    else if(type == 2)
    {
        ps8type = "RISE";
    }
    else if(type == 3)
    {
        ps8type = "FALL";
    }
    else if(type == 4)
    {
        ps8type = "HIGH";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:LEVel:TYPe %d,%d,%s,%s",s32name,s32chan,ps8trig,ps8type);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:TRIGger:LEVel:TYPe? <name>,<ch>,<TRIGL|TRIGR>
int mrhtDeviceMrqTriggerLevelType_Query(int inst,int name,int chan,int trig, int* type)
{
    char as8FmtCmd[100] = {0};
    char as8type[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8trig = NULL;
    if(trig == 0)
    {
        ps8trig = "TRIGL";
    }
    else if(trig == 1)
    {
        ps8trig = "TRIGR";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:LEVel:TYPe? %d,%d,%s",s32name,s32chan,ps8trig);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8type, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8type, "RESERVE") == 0)
    {
        *type = 0;
    }

    else if(strcmp(as8type, "LOW") == 0)
    {
        *type = 1;
    }

    else if(strcmp(as8type, "RISE") == 0)
    {
        *type = 2;
    }

    else if(strcmp(as8type, "FALL") == 0)
    {
        *type = 3;
    }

    else if(strcmp(as8type, "HIGH") == 0)
    {
        *type = 4;
    }

    return 0;
}




//! :DEVice:MRQ:TRIGger:LEVel:RESPonse <name>,<ch>,<TRIGL|TRIGR>,<NONE|ALARM|STOP|ALARM&STOP>
int mrhtDeviceMrqTriggerLevelResponse(int inst,int name,int chan,int trig,int resp)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8trig = NULL;
    if(trig == 0)
    {
        ps8trig = "TRIGL";
    }
    else if(trig == 1)
    {
        ps8trig = "TRIGR";
    }

    char* ps8resp = NULL;
    if(resp == 0)
    {
        ps8resp = "NONE";
    }
    else if(resp == 1)
    {
        ps8resp = "ALARM";
    }
    else if(resp == 2)
    {
        ps8resp = "STOP";
    }
    else if(resp == 3)
    {
        ps8resp = "ALARM&STOP";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:LEVel:RESPonse %d,%d,%s,%s",s32name,s32chan,ps8trig,ps8resp);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:TRIGger:LEVel:RESPonse? <name>,<ch>,<TRIGL|TRIGR>
int mrhtDeviceMrqTriggerLevelResponse_Query(int inst,int name,int chan,int trig, int* resp)
{
    char as8FmtCmd[100] = {0};
    char as8resp[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8trig = NULL;
    if(trig == 0)
    {
        ps8trig = "TRIGL";
    }
    else if(trig == 1)
    {
        ps8trig = "TRIGR";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:LEVel:RESPonse? %d,%d,%s",s32name,s32chan,ps8trig);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8resp, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8resp, "NONE") == 0)
    {
        *resp = 0;
    }

    else if(strcmp(as8resp, "ALARM") == 0)
    {
        *resp = 1;
    }

    else if(strcmp(as8resp, "STOP") == 0)
    {
        *resp = 2;
    }

    else if(strcmp(as8resp, "ALARM&STOP") == 0)
    {
        *resp = 3;
    }

    return 0;
}




//! :DEVice:MRQ:TRIGger:LEVel:PERIod <name>,<ch>,<TRIGL|TRIGR>,<period>
int mrhtDeviceMrqTriggerLevelPeriod(int inst,int name,int chan,int trig,int period)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8trig = NULL;
    if(trig == 0)
    {
        ps8trig = "TRIGL";
    }
    else if(trig == 1)
    {
        ps8trig = "TRIGR";
    }
    int s32period = period;

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:LEVel:PERIod %d,%d,%s,%d",s32name,s32chan,ps8trig,s32period);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:TRIGger:LEVel:PERIod? <name>,<ch>,<TRIGL|TRIGR>
int mrhtDeviceMrqTriggerLevelPeriod_Query(int inst,int name,int chan,int trig, int* period)
{
    char as8FmtCmd[100] = {0};
    char as8period[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8trig = NULL;
    if(trig == 0)
    {
        ps8trig = "TRIGL";
    }
    else if(trig == 1)
    {
        ps8trig = "TRIGR";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:TRIGger:LEVel:PERIod? %d,%d,%s",s32name,s32chan,ps8trig);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8period, 100) == 0)
    {
        return -1;
    }
    
    *period = atoi(as8period);
    return 0;
}




//! :DEVice:MRQ:DRIVER:TYPe? <name>,<ch>
int mrhtDeviceMrqDriverType_Query(int inst,int name,int chan, char* type,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8type = type;

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DRIVER:TYPe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8type, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:DRIVER:CURRent <name>,<CH>,<current>
int mrhtDeviceMrqDriverCurrent(int inst,int name,int chan,int curr)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32curr = curr;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DRIVER:CURRent %d,%d,%d",s32name,s32chan,s32curr);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:DRIVER:CURRent? <name>,<CH>
int mrhtDeviceMrqDriverCurrent_Query(int inst,int name,int chan, int* curr)
{
    char as8FmtCmd[100] = {0};
    char as8curr[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DRIVER:CURRent? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8curr, 100) == 0)
    {
        return -1;
    }
    
    *curr = atoi(as8curr);
    return 0;
}




//! :DEVice:MRQ:DRIVER:MICROStep <name>,<CH>,<256|128|64|32|16|8|4|2|1>
int mrhtDeviceMrqDriverMicrostep(int inst,int name,int chan,int micr)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8micr = NULL;
    if(micr == 0)
    {
        ps8micr = "256";
    }
    else if(micr == 1)
    {
        ps8micr = "128";
    }
    else if(micr == 2)
    {
        ps8micr = "64";
    }
    else if(micr == 3)
    {
        ps8micr = "32";
    }
    else if(micr == 4)
    {
        ps8micr = "16";
    }
    else if(micr == 5)
    {
        ps8micr = "8";
    }
    else if(micr == 6)
    {
        ps8micr = "4";
    }
    else if(micr == 7)
    {
        ps8micr = "2";
    }
    else if(micr == 8)
    {
        ps8micr = "1";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:DRIVER:MICROStep %d,%d,%s",s32name,s32chan,ps8micr);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:DRIVER:MICROStep? <name>,<CH>
int mrhtDeviceMrqDriverMicrostep_Query(int inst,int name,int chan, int* micr)
{
    char as8FmtCmd[100] = {0};
    char as8micr[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DRIVER:MICROStep? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8micr, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8micr, "256") == 0)
    {
        *micr = 0;
    }

    else if(strcmp(as8micr, "128") == 0)
    {
        *micr = 1;
    }

    else if(strcmp(as8micr, "64") == 0)
    {
        *micr = 2;
    }

    else if(strcmp(as8micr, "32") == 0)
    {
        *micr = 3;
    }

    else if(strcmp(as8micr, "16") == 0)
    {
        *micr = 4;
    }

    else if(strcmp(as8micr, "8") == 0)
    {
        *micr = 5;
    }

    else if(strcmp(as8micr, "4") == 0)
    {
        *micr = 6;
    }

    else if(strcmp(as8micr, "2") == 0)
    {
        *micr = 7;
    }

    else if(strcmp(as8micr, "1") == 0)
    {
        *micr = 8;
    }

    return 0;
}




//! :DEVice:MRQ:DRIVER:STATe <name>,<CH>,<OFF|ON>
int mrhtDeviceMrqDriverState(int inst,int name,int chan,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "OFF";
    }
    else if(state == 1)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:DRIVER:STATe %d,%d,%s",s32name,s32chan,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:DRIVER:STATe? <name>,<CH>
int mrhtDeviceMrqDriverState_Query(int inst,int name,int chan, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DRIVER:STATe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "OFF") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "ON") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:ENCODer:LINe:NUMber <name>,<ch>,<num>
int mrhtDeviceMrqEncoderLineNumber(int inst,int name,int chan,int num)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32num = num;

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:LINe:NUMber %d,%d,%d",s32name,s32chan,s32num);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:ENCODer:LINe:NUMber? <name>,<ch>
int mrhtDeviceMrqEncoderLineNumber_Query(int inst,int name,int chan, int* num)
{
    char as8FmtCmd[100] = {0};
    char as8num[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:LINe:NUMber? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8num, 100) == 0)
    {
        return -1;
    }
    
    *num = atoi(as8num);
    return 0;
}




//! :DEVice:MRQ:ENCODer:CHANnel:NUMber <name>,<ch>,<1|3>
int mrhtDeviceMrqEncoderChannelNumber(int inst,int name,int chan,int chanNum)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8chanNum = NULL;
    if(chanNum == 0)
    {
        ps8chanNum = "1";
    }
    else if(chanNum == 1)
    {
        ps8chanNum = "3";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:CHANnel:NUMber %d,%d,%s",s32name,s32chan,ps8chanNum);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:ENCODer:CHANnel:NUMber? <name>,<ch>
int mrhtDeviceMrqEncoderChannelNumber_Query(int inst,int name,int chan, int* chanNum)
{
    char as8FmtCmd[100] = {0};
    char as8chanNum[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:CHANnel:NUMber? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8chanNum, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8chanNum, "1") == 0)
    {
        *chanNum = 0;
    }

    else if(strcmp(as8chanNum, "3") == 0)
    {
        *chanNum = 1;
    }

    return 0;
}




//! :DEVice:MRQ:ENCODer:TYPe <name>,<ch>,<INCREMENTAL|ABSOLUTE>
int mrhtDeviceMrqEncoderType(int inst,int name,int chan,int type)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8type = NULL;
    if(type == 0)
    {
        ps8type = "INCREMENTAL";
    }
    else if(type == 1)
    {
        ps8type = "ABSOLUTE";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:TYPe %d,%d,%s",s32name,s32chan,ps8type);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:ENCODer:TYPe? <name>,<ch>
int mrhtDeviceMrqEncoderType_Query(int inst,int name,int chan, int* type)
{
    char as8FmtCmd[100] = {0};
    char as8type[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:TYPe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8type, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8type, "INCREMENTAL") == 0)
    {
        *type = 0;
    }

    else if(strcmp(as8type, "ABSOLUTE") == 0)
    {
        *type = 1;
    }

    return 0;
}




//! :DEVice:MRQ:ENCODer:MULTIPLe <name>,<ch>,<multiple>
int mrhtDeviceMrqEncoderMultiple(int inst,int name,int chan,int multiple)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32multiple = multiple;

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:MULTIPLe %d,%d,%d",s32name,s32chan,s32multiple);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:ENCODer:MULTIPLe? <name>,<ch>
int mrhtDeviceMrqEncoderMultiple_Query(int inst,int name,int chan, int* multiple)
{
    char as8FmtCmd[100] = {0};
    char as8multiple[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:MULTIPLe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8multiple, 100) == 0)
    {
        return -1;
    }
    
    *multiple = atoi(as8multiple);
    return 0;
}




//! :DEVice:MRQ:ENCODer:STATe <name>,<ch>,<NONE|OFF|ON>
int mrhtDeviceMrqEncoderState(int inst,int name,int chan,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "NONE";
    }
    else if(state == 1)
    {
        ps8state = "OFF";
    }
    else if(state == 2)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:STATe %d,%d,%s",s32name,s32chan,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:ENCODer:STATe? <name>,<ch>
int mrhtDeviceMrqEncoderState_Query(int inst,int name,int chan, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODer:STATe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "NONE") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "OFF") == 0)
    {
        *state = 1;
    }

    else if(strcmp(as8state, "ON") == 0)
    {
        *state = 2;
    }

    return 0;
}




//! :DEVice:MRQ:ENCODerFEEDBACK <name>,<ch>,<feed>
int mrhtDeviceMrqEncoderfeedback(int inst,int name,int chan,int feed)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32feed = feed;

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODerFEEDBACK %d,%d,%d",s32name,s32chan,s32feed);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:ENCODerFEEDBACK? <name>,<ch>
int mrhtDeviceMrqEncoderfeedback_Query(int inst,int name,int chan, int* feed)
{
    char as8FmtCmd[100] = {0};
    char as8feed[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:ENCODerFEEDBACK? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8feed, 100) == 0)
    {
        return -1;
    }
    
    *feed = atoi(as8feed);
    return 0;
}




//! :DEVice:MRQ:UART<n>:APPLy <name>,<parity>,<wordlen>,<stopbit>
int mrhtDeviceMrqUartApply(int inst,int uart,int name,int parity,int wordlen,int stopbit)
{
    char as8FmtCmd[100] = {0};

    int s32uart = uart;
    int s32name = name;
    int s32parity = parity;
    int s32wordlen = wordlen;
    int s32stopbit = stopbit;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:APPLy %d,%d,%d,%d",s32uart,s32name,s32parity,s32wordlen,s32stopbit);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:UART<n>:APPLy? <name>
int mrhtDeviceMrqUartApply_Query(int inst,int uart,int name, int* parity,int* wordlen,int* stopbit)
{
    char as8FmtCmd[100] = {0};
    char as8parity[100] = {0};

    int s32uart = uart;
    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:APPLy? %d",s32uart,s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8parity, 100) == 0)
    {
        return -1;
    }
    
    char* ps8Delims = ",";
    char* result = NULL;
    char* ret[10] = {NULL};
    int count = 0;
    result = strtok(as8parity, ps8Delims);
    while(result != NULL)
    {
        ret[count] = result;
        count++;
        result = strtok(NULL, ps8Delims);
    }

    *parity = atoi(ret[0]);
    *wordlen = atoi(ret[1]);
    *stopbit = atoi(ret[2]);

    return 0;
}




//! :DEVice:MRQ:UART<n>:FLOWctrl <name>,<NONE|RTS|CTS|RTS_CTS>
int mrhtDeviceMrqUartFlowctrl(int inst,int uart,int name,int flow)
{
    char as8FmtCmd[100] = {0};

    int s32uart = uart;
    int s32name = name;

    char* ps8flow = NULL;
    if(flow == 0)
    {
        ps8flow = "NONE";
    }
    else if(flow == 1)
    {
        ps8flow = "RTS";
    }
    else if(flow == 2)
    {
        ps8flow = "CTS";
    }
    else if(flow == 3)
    {
        ps8flow = "RTS_CTS";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:FLOWctrl %d,%s",s32uart,s32name,ps8flow);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:UART<n>:FLOWctrl? <name>
int mrhtDeviceMrqUartFlowctrl_Query(int inst,int uart,int name, int* flow)
{
    char as8FmtCmd[100] = {0};
    char as8flow[100] = {0};

    int s32uart = uart;
    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:FLOWctrl? %d",s32uart,s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8flow, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8flow, "NONE") == 0)
    {
        *flow = 0;
    }

    else if(strcmp(as8flow, "RTS") == 0)
    {
        *flow = 1;
    }

    else if(strcmp(as8flow, "CTS") == 0)
    {
        *flow = 2;
    }

    else if(strcmp(as8flow, "RTS_CTS") == 0)
    {
        *flow = 3;
    }

    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:STATe <name>,<OFF|ON>
int mrhtDeviceMrqUartSensorState(int inst,int uart,int sensor,int name,int state)
{
    char as8FmtCmd[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "OFF";
    }
    else if(state == 1)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:STATe %d,%s",s32uart,s32sensor,s32name,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:STATe? <name>
int mrhtDeviceMrqUartSensorState_Query(int inst,int uart,int sensor,int name, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:STATe? %d",s32uart,s32sensor,s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "OFF") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "ON") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig  :ALL <name>,<sof>,<framelen>,<num>,<period>
int mrhtDeviceMrqUartSensorConfig(int inst,int uart,int sensor,int name,int sof,int framelen,int num,int period)
{
    char as8FmtCmd[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;
    int s32sof = sof;
    int s32framelen = framelen;
    int s32num = num;
    int s32period = period;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig %d,%d,%d,%d,%d",s32uart,s32sensor,s32name,s32sof,s32framelen,s32num,s32period);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:ALL? <name>
int mrhtDeviceMrqUartSensorConfigAll_Query(int inst,int uart,int sensor,int name, int* sof,int* framelen,int* num,int* period)
{
    char as8FmtCmd[100] = {0};
    char as8sof[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig:ALL? %d",s32uart,s32sensor,s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8sof, 100) == 0)
    {
        return -1;
    }
    
    char* ps8Delims = ",";
    char* result = NULL;
    char* ret[10] = {NULL};
    int count = 0;
    result = strtok(as8sof, ps8Delims);
    while(result != NULL)
    {
        ret[count] = result;
        count++;
        result = strtok(NULL, ps8Delims);
    }

    *sof = atoi(ret[0]);
    *framelen = atoi(ret[1]);
    *num = atoi(ret[2]);
    *period = atoi(ret[3]);

    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:SOF <name>,<sof>
int mrhtDeviceMrqUartSensorConfigSof(int inst,int uart,int sensor,int name,int sof)
{
    char as8FmtCmd[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;
    int s32sof = sof;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig:SOF %d,%d",s32uart,s32sensor,s32name,s32sof);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:SOF? <name>
int mrhtDeviceMrqUartSensorConfigSof_Query(int inst,int uart,int sensor,int name, int* sof)
{
    char as8FmtCmd[100] = {0};
    char as8sof[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig:SOF? %d",s32uart,s32sensor,s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8sof, 100) == 0)
    {
        return -1;
    }
    
    *sof = atoi(as8sof);
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:FRAMELen <name>,<len>
int mrhtDeviceMrqUartSensorConfigFramelen(int inst,int uart,int sensor,int name,int len)
{
    char as8FmtCmd[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;
    int s32len = len;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig:FRAMELen %d,%d",s32uart,s32sensor,s32name,s32len);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:FRAMELen? <name>
int mrhtDeviceMrqUartSensorConfigFramelen_Query(int inst,int uart,int sensor,int name, int* len)
{
    char as8FmtCmd[100] = {0};
    char as8len[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig:FRAMELen? %d",s32uart,s32sensor,s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8len, 100) == 0)
    {
        return -1;
    }
    
    *len = atoi(as8len);
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:NUM <name>,<num>
int mrhtDeviceMrqUartSensorConfigNum(int inst,int uart,int sensor,int name,int num)
{
    char as8FmtCmd[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;
    int s32num = num;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig:NUM %d,%d",s32uart,s32sensor,s32name,s32num);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:NUM? <name>
int mrhtDeviceMrqUartSensorConfigNum_Query(int inst,int uart,int sensor,int name, int* num)
{
    char as8FmtCmd[100] = {0};
    char as8num[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig:NUM? %d",s32uart,s32sensor,s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8num, 100) == 0)
    {
        return -1;
    }
    
    *num = atoi(as8num);
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:PERIod <name>,<time>
int mrhtDeviceMrqUartSensorConfigPeriod(int inst,int uart,int sensor,int name,int time)
{
    char as8FmtCmd[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;
    int s32time = time;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig:PERIod %d,%d",s32uart,s32sensor,s32name,s32time);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:PERIod? <name>
int mrhtDeviceMrqUartSensorConfigPeriod_Query(int inst,int uart,int sensor,int name, int* time)
{
    char as8FmtCmd[100] = {0};
    char as8time[100] = {0};

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:CONFig:PERIod? %d",s32uart,s32sensor,s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8time, 100) == 0)
    {
        return -1;
    }
    
    *time = atoi(as8time);
    return 0;
}




//! :DEVice:MRQ:UART<n>:SENSor<n>:DATA? <name>
int mrhtDeviceMrqUartSensorData_Query(int inst,int uart,int sensor,int name, char* data,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8data = data;

    int s32uart = uart;
    int s32sensor = sensor;
    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:UART%d:SENSor%d:DATA? %d",s32uart,s32sensor,s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8data, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:DALarm:STATe? <name>,<ch>
int mrhtDeviceMrqDalarmState_Query(int inst,int name,int chan, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DALarm:STATe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "ON") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "OFF") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:DALarm:STATe <name>,<ch>,<ON|OFF>
int mrhtDeviceMrqDalarmState(int inst,int name,int chan,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "ON";
    }
    else if(state == 1)
    {
        ps8state = "OFF";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:DALarm:STATe %d,%d,%s",s32name,s32chan,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:DALarm:ALARm1:DISTance <name>,<ch>,<dist>
int mrhtDeviceMrqDalarmAlarm1Distance(int inst,int name,int chan,int dist)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32dist = dist;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DALarm:ALARm1:DISTance %d,%d,%d",s32name,s32chan,s32dist);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:DALarm:ALARm1:DISTance? <name>,<ch>
int mrhtDeviceMrqDalarmAlarm1Distance_Query(int inst,int name,int chan, int* dist)
{
    char as8FmtCmd[100] = {0};
    char as8dist[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DALarm:ALARm1:DISTance? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8dist, 100) == 0)
    {
        return -1;
    }
    
    *dist = atoi(as8dist);
    return 0;
}




//! :DEVice:MRQ:DALarm:ALARm2:DISTance <name>,<ch>,<dist>
int mrhtDeviceMrqDalarmAlarm2Distance(int inst,int name,int chan,int dist)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32dist = dist;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DALarm:ALARm2:DISTance %d,%d,%d",s32name,s32chan,s32dist);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:DALarm:ALARm2:DISTance? <name>,<ch>
int mrhtDeviceMrqDalarmAlarm2Distance_Query(int inst,int name,int chan, int* dist)
{
    char as8FmtCmd[100] = {0};
    char as8dist[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DALarm:ALARm2:DISTance? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8dist, 100) == 0)
    {
        return -1;
    }
    
    *dist = atoi(as8dist);
    return 0;
}




//! :DEVice:MRQ:DALarm:ALARm3:DISTance <name>,<ch>,<dist>
int mrhtDeviceMrqDalarmAlarm3Distance(int inst,int name,int chan,int dist)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;
    int s32dist = dist;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DALarm:ALARm3:DISTance %d,%d,%d",s32name,s32chan,s32dist);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:DALarm:ALARm3:DISTance? <name>,<ch>
int mrhtDeviceMrqDalarmAlarm3Distance_Query(int inst,int name,int chan, int* dist)
{
    char as8FmtCmd[100] = {0};
    char as8dist[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:DALarm:ALARm3:DISTance? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8dist, 100) == 0)
    {
        return -1;
    }
    
    *dist = atoi(as8dist);
    return 0;
}




//! :DEVice:MRQ:NDRiver:TYPe? <name>,<ch>
int mrhtDeviceMrqNdriverType_Query(int inst,int name,int chan, char* type,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8type = type;

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:NDRiver:TYPe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8type, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:NDRiver:CURRent <name>,<current>
int mrhtDeviceMrqNdriverCurrent(int inst,int name,int curr)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32curr = curr;

    sprintf(as8FmtCmd, ":DEVice:MRQ:NDRiver:CURRent %d,%d",s32name,s32curr);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:NDRiver:CURRent? <name>
int mrhtDeviceMrqNdriverCurrent_Query(int inst,int name, int* curr)
{
    char as8FmtCmd[100] = {0};
    char as8curr[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:NDRiver:CURRent? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8curr, 100) == 0)
    {
        return -1;
    }
    
    *curr = atoi(as8curr);
    return 0;
}




//! :DEVice:MRQ:NDRiver:MICRosteps <name>,<RESERVE|RESERVE|RESERVE|32|16|8|4|2|1>
int mrhtDeviceMrqNdriverMicrosteps(int inst,int name,int micr)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8micr = NULL;
    if(micr == 0)
    {
        ps8micr = "RESERVE";
    }
    else if(micr == 1)
    {
        ps8micr = "RESERVE";
    }
    else if(micr == 2)
    {
        ps8micr = "RESERVE";
    }
    else if(micr == 3)
    {
        ps8micr = "32";
    }
    else if(micr == 4)
    {
        ps8micr = "16";
    }
    else if(micr == 5)
    {
        ps8micr = "8";
    }
    else if(micr == 6)
    {
        ps8micr = "4";
    }
    else if(micr == 7)
    {
        ps8micr = "2";
    }
    else if(micr == 8)
    {
        ps8micr = "1";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:NDRiver:MICRosteps %d,%s",s32name,ps8micr);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRQ:NDRiver:MICRosteps? <name>
int mrhtDeviceMrqNdriverMicrosteps_Query(int inst,int name, int* micr)
{
    char as8FmtCmd[100] = {0};
    char as8micr[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":DEVice:MRQ:NDRiver:MICRosteps? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8micr, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8micr, "RESERVE") == 0)
    {
        *micr = 0;
    }

    else if(strcmp(as8micr, "RESERVE") == 0)
    {
        *micr = 1;
    }

    else if(strcmp(as8micr, "RESERVE") == 0)
    {
        *micr = 2;
    }

    else if(strcmp(as8micr, "32") == 0)
    {
        *micr = 3;
    }

    else if(strcmp(as8micr, "16") == 0)
    {
        *micr = 4;
    }

    else if(strcmp(as8micr, "8") == 0)
    {
        *micr = 5;
    }

    else if(strcmp(as8micr, "4") == 0)
    {
        *micr = 6;
    }

    else if(strcmp(as8micr, "2") == 0)
    {
        *micr = 7;
    }

    else if(strcmp(as8micr, "1") == 0)
    {
        *micr = 8;
    }

    return 0;
}




//! :DEVice:MRQ:NDRiver:STATe? <name>,<ch>
int mrhtDeviceMrqNdriverState_Query(int inst,int name,int chan, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":DEVice:MRQ:NDRiver:STATe? %d,%d",s32name,s32chan);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "ON") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "OFF") == 0)
    {
        *state = 1;
    }

    return 0;
}




//! :DEVice:MRQ:NDRiver:STATe <name>,<ch>,<ON|OFF>
int mrhtDeviceMrqNdriverState(int inst,int name,int chan,int state)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32chan = chan;

    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "ON";
    }
    else if(state == 1)
    {
        ps8state = "OFF";
    }

    sprintf(as8FmtCmd, ":DEVice:MRQ:NDRiver:STATe %d,%d,%s",s32name,s32chan,ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :DEVice:MRV:PT <>
int mrhtDeviceMrvPt(int inst)
{
    char as8FmtCmd[100] = {0};


    sprintf(as8FmtCmd, ":DEVice:MRV:PT ");
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:ALLOC? <MRX-T4|MRX-AS|MRX-H2|MRX-DELTA>,<(CH_LIST)>
int mrhtRobotAlloc_Query(int inst,int configuration,char* chanList, int* name)
{
    char as8FmtCmd[100] = {0};
    char as8name[100] = {0};


    char* ps8configuration = NULL;
    if(configuration == 0)
    {
        ps8configuration = "MRX-T4";
    }
    else if(configuration == 1)
    {
        ps8configuration = "MRX-AS";
    }
    else if(configuration == 2)
    {
        ps8configuration = "MRX-H2";
    }
    else if(configuration == 3)
    {
        ps8configuration = "MRX-DELTA";
    }

    char* ps8chanList = chanList;

    sprintf(as8FmtCmd, ":ROBOT:ALLOC? %s,%s",ps8configuration,ps8chanList);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8name, 100) == 0)
    {
        return -1;
    }
    
    *name = atoi(as8name);
    return 0;
}




//! :ROBOT:ALLOC:FILe? <configfile>
int mrhtRobotAllocFile_Query(int inst,char* file, int* name)
{
    char as8FmtCmd[100] = {0};
    char as8name[100] = {0};


    char* ps8file = file;

    sprintf(as8FmtCmd, ":ROBOT:ALLOC:FILe? %s",ps8file);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8name, 100) == 0)
    {
        return -1;
    }
    
    *name = atoi(as8name);
    return 0;
}




//! :ROBOT:DELETe <name>
int mrhtRobotDelete(int inst)
{
    char as8FmtCmd[100] = {0};


    sprintf(as8FmtCmd, ":ROBOT:DELETe ");
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:CONFIGRATION? <name>
int mrhtRobotConfigration_Query(int inst,int name, char* configuration,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8configuration = configuration;

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:CONFIGRATION? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8configuration, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:SUBTYPE <name>,<type>
int mrhtRobotSubtype(int inst,int name,int type)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32type = type;

    sprintf(as8FmtCmd, ":ROBOT:SUBTYPE %d,%d",s32name,s32type);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:SUBTYPE? <name>
int mrhtRobotSubtype_Query(int inst,int name, int* type)
{
    char as8FmtCmd[100] = {0};
    char as8type[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:SUBTYPE? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8type, 100) == 0)
    {
        return -1;
    }
    
    *type = atoi(as8type);
    return 0;
}




//! :ROBOT:COORDinate <name>,<coordiante>
int mrhtRobotCoordinate(int inst,int name,int coordiante)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32coordiante = coordiante;

    sprintf(as8FmtCmd, ":ROBOT:COORDinate %d,%d",s32name,s32coordiante);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:COORDinate? <name>
int mrhtRobotCoordinate_Query(int inst,int name, int* coordiante)
{
    char as8FmtCmd[100] = {0};
    char as8coordiante[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:COORDinate? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8coordiante, 100) == 0)
    {
        return -1;
    }
    
    *coordiante = atoi(as8coordiante);
    return 0;
}




//! :ROBOT:DEVice:NAMe? <name>
int mrhtRobotDeviceName_Query(int inst,int name, int* subname)
{
    char as8FmtCmd[100] = {0};
    char as8subname[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:DEVice:NAMe? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8subname, 100) == 0)
    {
        return -1;
    }
    
    *subname = atoi(as8subname);
    return 0;
}




//! :ROBOT:NAMe?
int mrhtRobotName_Query(int inst, char* name,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8name = name;


    sprintf(as8FmtCmd, ":ROBOT:NAMe?");
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8name, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:COUNt?
int mrhtRobotCount_Query(int inst, int* count)
{
    char as8FmtCmd[100] = {0};
    char as8count[100] = {0};


    sprintf(as8FmtCmd, ":ROBOT:COUNt?");
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8count, 100) == 0)
    {
        return -1;
    }
    
    *count = atoi(as8count);
    return 0;
}




//! :ROBOT:PROJECTZERO <name>,<(value)>
int mrhtRobotProjectzero(int inst,int name,char* value)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8value = value;

    sprintf(as8FmtCmd, ":ROBOT:PROJECTZERO %d,%s",s32name,ps8value);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:PROJECTZERO? <name>
int mrhtRobotProjectzero_Query(int inst,int name, char* value,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8value = value;

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:PROJECTZERO? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8value, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:WAVETABLE <name>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtRobotWavetable(int inst,int name,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:WAVETABLE %d,%s",s32name,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:WAVETABLE?  <name>
int mrhtRobotWavetable_Query(int inst,int name, int* wave)
{
    char as8FmtCmd[100] = {0};
    char as8wave[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:WAVETABLE? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8wave, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8wave, "MAIN") == 0)
    {
        *wave = 0;
    }

    else if(strcmp(as8wave, "SMALL") == 0)
    {
        *wave = 1;
    }

    else if(strcmp(as8wave, "P1") == 0)
    {
        *wave = 2;
    }

    else if(strcmp(as8wave, "P2") == 0)
    {
        *wave = 3;
    }

    else if(strcmp(as8wave, "P3") == 0)
    {
        *wave = 4;
    }

    else if(strcmp(as8wave, "P4") == 0)
    {
        *wave = 5;
    }

    else if(strcmp(as8wave, "P5") == 0)
    {
        *wave = 6;
    }

    else if(strcmp(as8wave, "P6") == 0)
    {
        *wave = 7;
    }

    else if(strcmp(as8wave, "P7") == 0)
    {
        *wave = 8;
    }

    else if(strcmp(as8wave, "P8") == 0)
    {
        *wave = 9;
    }

    return 0;
}




//! :ROBOT:IDENtify <OFF|ON>
int mrhtRobotIdentify(int inst,int state)
{
    char as8FmtCmd[100] = {0};


    char* ps8state = NULL;
    if(state == 0)
    {
        ps8state = "OFF";
    }
    else if(state == 1)
    {
        ps8state = "ON";
    }

    sprintf(as8FmtCmd, ":ROBOT:IDENtify %s",ps8state);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:RUN <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotRun(int inst,int name, int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:RUN %d,%s",s32name,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:STATe? <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotState_Query(int inst,int name,int wave, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:STATe? %d,%s",s32name,ps8wave);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "ERROR") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "READY") == 0)
    {
        *state = 1;
    }

    else if(strcmp(as8state, "LOADING") == 0)
    {
        *state = 2;
    }

    else if(strcmp(as8state, "IDLE") == 0)
    {
        *state = 3;
    }

    else if(strcmp(as8state, "RUNNING") == 0)
    {
        *state = 4;
    }

    return 0;
}




//! :ROBOT:STOP <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotStop(int inst,int name,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:STOP %d,%s",s32name,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:HOMe:WAVETABLE <name>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtRobotHomeWavetable(int inst,int name,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:HOMe:WAVETABLE %d,%s",s32name,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:HOMe:WAVETABLE?  <name>
int mrhtRobotHomeWavetable_Query(int inst,int name, int* wave)
{
    char as8FmtCmd[100] = {0};
    char as8wave[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:HOMe:WAVETABLE? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8wave, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8wave, "MAIN") == 0)
    {
        *wave = 0;
    }

    else if(strcmp(as8wave, "SMALL") == 0)
    {
        *wave = 1;
    }

    else if(strcmp(as8wave, "P1") == 0)
    {
        *wave = 2;
    }

    else if(strcmp(as8wave, "P2") == 0)
    {
        *wave = 3;
    }

    else if(strcmp(as8wave, "P3") == 0)
    {
        *wave = 4;
    }

    else if(strcmp(as8wave, "P4") == 0)
    {
        *wave = 5;
    }

    else if(strcmp(as8wave, "P5") == 0)
    {
        *wave = 6;
    }

    else if(strcmp(as8wave, "P6") == 0)
    {
        *wave = 7;
    }

    else if(strcmp(as8wave, "P7") == 0)
    {
        *wave = 8;
    }

    else if(strcmp(as8wave, "P8") == 0)
    {
        *wave = 9;
    }

    return 0;
}




//! :ROBOT:HOMe:POSITION? <name>
int mrhtRobotHomePosition_Query(int inst,int name, char* pos,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8pos = pos;

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:HOMe:POSITION? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8pos, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:HOMe:ANGLE?  <name>
int mrhtRobotHomeAngle_Query(int inst,int name, char* angle,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8angle = angle;

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:HOMe:ANGLE? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8angle, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:HOMe:RUN  <name>[,<time>]
int mrhtRobotHomeRun(int inst,int name,int time)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32time = time;

    sprintf(as8FmtCmd, ":ROBOT:HOMe:RUN %d,%d",s32name,s32time);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:HOMe:STOP <name>
int mrhtRobotHomeStop(int inst,int name)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:HOMe:STOP %d",s32name);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:HOMe:STATe? <name>
int mrhtRobotHomeState_Query(int inst,int name, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:HOMe:STATe? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "ERROR") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "READY") == 0)
    {
        *state = 1;
    }

    else if(strcmp(as8state, "LOADING") == 0)
    {
        *state = 2;
    }

    else if(strcmp(as8state, "IDLE") == 0)
    {
        *state = 3;
    }

    else if(strcmp(as8state, "RUNNING") == 0)
    {
        *state = 4;
    }

    return 0;
}




//! :ROBOT:HOMe:MODe <name>,<mode>
int mrhtRobotHomeMode(int inst,int name,int mode)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32mode = mode;

    sprintf(as8FmtCmd, ":ROBOT:HOMe:MODe %d,%d",s32name,s32mode);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:HOMe:MODe? <name>
int mrhtRobotHomeMode_Query(int inst,int name, int* mode)
{
    char as8FmtCmd[100] = {0};
    char as8mode[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:HOMe:MODe? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8mode, 100) == 0)
    {
        return -1;
    }
    
    *mode = atoi(as8mode);
    return 0;
}




//! :ROBOT:MOVe <name>,<x>,<y>,<z>,<t>[,<<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>>]
int mrhtRobotMove(int inst,int name,int x,int y,int z,int t,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32x = x;
    int s32y = y;
    int s32z = z;
    int s32t = t;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:MOVe %d,%d,%d,%d,%d,%s",s32name,s32x,s32y,s32z,s32t,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:MOVe:HOLD <name>,<axle>,<speed>,<dir>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMoveHold(int inst,int name,int axle,int speed,int dir,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32axle = axle;
    int s32speed = speed;
    int s32dir = dir;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:MOVe:HOLD %d,%d,%d,%d,%s",s32name,s32axle,s32speed,s32dir,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:MOVe:RELATive <name>,<x>,<y>,<z>,<t>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMoveRelative(int inst,int name,int x,int y,int z,int t,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32x = x;
    int s32y = y;
    int s32z = z;
    int s32t = t;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:MOVe:RELATive %d,%d,%d,%d,%d,%s",s32name,s32x,s32y,s32z,s32t,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:MOVe:LINear <name>,<x>,<y>,<z>,<t>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMoveLinear(int inst,int name,int x,int y,int z,int t,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32x = x;
    int s32y = y;
    int s32z = z;
    int s32t = t;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:MOVe:LINear %d,%d,%d,%d,%d,%s",s32name,s32x,s32y,s32z,s32t,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:MOVe:LINear:RELATive <name>,<x>,<y>,<z>,<t>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMoveLinearRelative(int inst,int name,int x,int y,int z,int t,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32x = x;
    int s32y = y;
    int s32z = z;
    int s32t = t;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:MOVe:LINear:RELATive %d,%d,%d,%d,%d,%s",s32name,s32x,s32y,s32z,s32t,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:CURRENT:ANGLE?  <name>
int mrhtRobotCurrentAngle_Query(int inst,int name, char* angle,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8angle = angle;

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:CURRENT:ANGLE? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8angle, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:CURRENT:POSITION? <name>
int mrhtRobotCurrentPosition_Query(int inst,int name, char* pos,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8pos = pos;

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:CURRENT:POSITION? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8pos, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:POINt:LOAD <name>,<x>,<y>,<z>,<e>,<t>,<mode>
int mrhtRobotPointLoad(int inst,int name,int x,int y,int z,int e,int t,int mode)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32x = x;
    int s32y = y;
    int s32z = z;
    int s32e = e;
    int s32t = t;
    int s32mode = mode;

    sprintf(as8FmtCmd, ":ROBOT:POINt:LOAD %d,%d,%d,%d,%d,%d,%d",s32name,s32x,s32y,s32z,s32e,s32t,s32mode);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:POINt:COUNt? <name>
int mrhtRobotPointCount_Query(int inst,int name, int* count)
{
    char as8FmtCmd[100] = {0};
    char as8count[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:POINt:COUNt? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8count, 100) == 0)
    {
        return -1;
    }
    
    *count = atoi(as8count);
    return 0;
}




//! :ROBOT:POINt:RESOLVe <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotPointResolve(int inst,int name,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:POINt:RESOLVe %d,%s",s32name,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:POINt:CLEAr <name>
int mrhtRobotPointClear(int inst,int name)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:POINt:CLEAr %d",s32name);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:POINt:FILe:IMPORT <name>,<filename>
int mrhtRobotPointFileImport(int inst,int name,char* file)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8file = file;

    sprintf(as8FmtCmd, ":ROBOT:POINt:FILe:IMPORT %d,%s",s32name,ps8file);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:POINt:FILe:EXPORT <name>,<filename>
int mrhtRobotPointFileExport(int inst,int name,char* file)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8file = file;

    sprintf(as8FmtCmd, ":ROBOT:POINt:FILe:EXPORT %d,%s",s32name,ps8file);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:POINt:FILe?
int mrhtRobotPointFile_Query(int inst, char* file,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8file = file;


    sprintf(as8FmtCmd, ":ROBOT:POINt:FILe?");
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8file, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:PVT:LOAD <name>,<p>,<v>,<t>,<axle>
int mrhtRobotPvtLoad(int inst,int name,int p,int v,int t,int axle)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32p = p;
    int s32v = v;
    int s32t = t;
    int s32axle = axle;

    sprintf(as8FmtCmd, ":ROBOT:PVT:LOAD %d,%d,%d,%d,%d",s32name,s32p,s32v,s32t,s32axle);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:PVT:RESOLVe <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotPvtResolve(int inst,int name,int wave)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8wave = NULL;
    if(wave == 0)
    {
        ps8wave = "MAIN";
    }
    else if(wave == 1)
    {
        ps8wave = "SMALL";
    }
    else if(wave == 2)
    {
        ps8wave = "P1";
    }
    else if(wave == 3)
    {
        ps8wave = "P2";
    }
    else if(wave == 4)
    {
        ps8wave = "P3";
    }
    else if(wave == 5)
    {
        ps8wave = "P4";
    }
    else if(wave == 6)
    {
        ps8wave = "P5";
    }
    else if(wave == 7)
    {
        ps8wave = "P6";
    }
    else if(wave == 8)
    {
        ps8wave = "P7";
    }
    else if(wave == 9)
    {
        ps8wave = "P8";
    }

    sprintf(as8FmtCmd, ":ROBOT:PVT:RESOLVe %d,%s",s32name,ps8wave);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:PVT:CLEAr <name>[,<axle>]
int mrhtRobotPvtClear(int inst,int name,int axle)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32axle = axle;

    sprintf(as8FmtCmd, ":ROBOT:PVT:CLEAr %d,%d",s32name,s32axle);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:PVT:FILe:IMPORT <name>,<filename>
int mrhtRobotPvtFileImport(int inst,int name,char* file)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8file = file;

    sprintf(as8FmtCmd, ":ROBOT:PVT:FILe:IMPORT %d,%s",s32name,ps8file);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:PVT:FILe:EXPORT <name>,<filename>
int mrhtRobotPvtFileExport(int inst,int name,char* file)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    char* ps8file = file;

    sprintf(as8FmtCmd, ":ROBOT:PVT:FILe:EXPORT %d,%s",s32name,ps8file);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:PVT:FILe?
int mrhtRobotPvtFile_Query(int inst, char* file,int len)
{
    char as8FmtCmd[100] = {0};
    char* ps8file = file;


    sprintf(as8FmtCmd, ":ROBOT:PVT:FILe?");
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),ps8file, len) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:INTERPOLATe:MODe <name>,<mode>
int mrhtRobotInterpolateMode(int inst,int name,int mode)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32mode = mode;

    sprintf(as8FmtCmd, ":ROBOT:INTERPOLATe:MODe %d,%d",s32name,s32mode);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:INTERPOLATe:MODe? <name>
int mrhtRobotInterpolateMode_Query(int inst,int name, int* mode)
{
    char as8FmtCmd[100] = {0};
    char as8mode[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:INTERPOLATe:MODe? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8mode, 100) == 0)
    {
        return -1;
    }
    
    *mode = atoi(as8mode);
    return 0;
}




//! :ROBOT:INTERPOLATe:STEP <name>,<step>
int mrhtRobotInterpolateStep(int inst,int name,int step)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32step = step;

    sprintf(as8FmtCmd, ":ROBOT:INTERPOLATe:STEP %d,%d",s32name,s32step);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:INTERPOLATe:STEP? <name>
int mrhtRobotInterpolateStep_Query(int inst,int name, int* step)
{
    char as8FmtCmd[100] = {0};
    char as8step[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:INTERPOLATe:STEP? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8step, 100) == 0)
    {
        return -1;
    }
    
    *step = atoi(as8step);
    return 0;
}




//! :ROBOT:EFFECTor:SET  <name>,<type>,<CH>
int mrhtRobotEffectorSet(int inst,int name,int type,int chan)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32type = type;
    int s32chan = chan;

    sprintf(as8FmtCmd, ":ROBOT:EFFECTor:SET %d,%d,%d",s32name,s32type,s32chan);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:EFFECTor:DELETe <name>
int mrhtRobotEffectorDelete(int inst,int name)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:EFFECTor:DELETe %d",s32name);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:EFFECTor:EXEC  <name>,<p>,<t>
int mrhtRobotEffectorExec(int inst,int name,int p,int t)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;
    int s32p = p;
    int s32t = t;

    sprintf(as8FmtCmd, ":ROBOT:EFFECTor:EXEC %d,%d,%d",s32name,s32p,s32t);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:EFFECTor:EXEC:STOP  <name>
int mrhtRobotEffectorExecStop(int inst,int name)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:EFFECTor:EXEC:STOP %d",s32name);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:EFFECTor:EXEC:STATe? <name>
int mrhtRobotEffectorExecState_Query(int inst,int name, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:EFFECTor:EXEC:STATe? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "ERROR") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "READY") == 0)
    {
        *state = 1;
    }

    else if(strcmp(as8state, "LOADING") == 0)
    {
        *state = 2;
    }

    else if(strcmp(as8state, "IDLE") == 0)
    {
        *state = 3;
    }

    else if(strcmp(as8state, "RUNNING") == 0)
    {
        *state = 4;
    }

    return 0;
}




//! :ROBOT:EFFECTor:HOMe <name>
int mrhtRobotEffectorHome(int inst,int name)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:EFFECTor:HOMe %d",s32name);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:EFFECTor:HOMe:STOP  <name>
int mrhtRobotEffectorHomeStop(int inst,int name)
{
    char as8FmtCmd[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:EFFECTor:HOMe:STOP %d",s32name);
    if(_write(inst, as8FmtCmd, strlen(as8FmtCmd)) == 0)
    {
        return -1;
    }
    
    return 0;
}




//! :ROBOT:EFFECTor:HOMe:STATe? <name>
int mrhtRobotEffectorHomeState_Query(int inst,int name, int* state)
{
    char as8FmtCmd[100] = {0};
    char as8state[100] = {0};

    int s32name = name;

    sprintf(as8FmtCmd, ":ROBOT:EFFECTor:HOMe:STATe? %d",s32name);
    if(_query(inst, as8FmtCmd, strlen(as8FmtCmd),as8state, 100) == 0)
    {
        return -1;
    }
    
    if(strcmp(as8state, "ERROR") == 0)
    {
        *state = 0;
    }

    else if(strcmp(as8state, "READY") == 0)
    {
        *state = 1;
    }

    else if(strcmp(as8state, "LOADING") == 0)
    {
        *state = 2;
    }

    else if(strcmp(as8state, "IDLE") == 0)
    {
        *state = 3;
    }

    else if(strcmp(as8state, "RUNNING") == 0)
    {
        *state = 4;
    }

    return 0;
}




