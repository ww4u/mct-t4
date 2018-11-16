#ifndef MRHT_H
#define MRHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <visa.h>
#include <visatype.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int mrhtOpenDevice(char * ip, int timeout);

int mrhtCloseDevice(int vi);


//! *IDN?
int mrhtIdn_Query(int inst, char* data,int len);


//! :SYSTem:IDENtify <OFF|ON>
int mrhtSystemIdentify(int inst,int state);


//! :TRIGger:SEARch?
int mrhtTriggerSearch_Query(int inst, char* file,int len);


//! :TRIGger:CONFig <file>,<file>,<file>,<file>,<file>
int mrhtTriggerConfig(int inst,char* file1,char* file2,char* file3,char* file4,char* file5);


//! :TRIGger:SAVe
int mrhtTriggerSave(int inst);


//! :DEVice:SEARch
int mrhtDeviceSearch(int inst);


//! :DEVice:COUNt?
int mrhtDeviceCount_Query(int inst, int* count);


//! :DEVice:TYPe? <name>
int mrhtDeviceType_Query(int inst,int name, char* type,int len);


//! :DEVice:NAMe?
int mrhtDeviceName_Query(int inst, int* name);


//! :DEVice:CHANnel:COUNt? <name>
int mrhtDeviceChannelCount_Query(int inst,int name, int* chanNum);


//! :DEVice:FIRMware:ALL?  <name>
int mrhtDeviceFirmwareAll_Query(int inst,int name, char* firmware,int len);


//! :DEVice:FIRMware:HARD?  <name>
int mrhtDeviceFirmwareHard_Query(int inst,int name, char* hard,int len);


//! :DEVice:FIRMware:SOFT?  <name>
int mrhtDeviceFirmwareSoft_Query(int inst,int name, char* soft,int len);


//! :DEVice:FIRMware:SN?  <name>
int mrhtDeviceFirmwareSn_Query(int inst,int name, char* sn,int len);


//! :DEVice:FIRMware:BOOT?  <name>
int mrhtDeviceFirmwareBoot_Query(int inst,int name , char* boot,int len);


//! :DEVice:FIRMware:FPGA?  <name>
int mrhtDeviceFirmwareFpga_Query(int inst,int name , char* fpga,int len);


//! :DEVice:MRQ:IDENtify <name>,<OFF|ON>
int mrhtDeviceMrqIdentify(int inst,int name,int state);


//! :DEVice:MRQ:MOTion:STATe:REPORt <name>,<ch>,<ACTIVE|QUERY>
int mrhtDeviceMrqMotionStateReport(int inst,int name,int chan,int state);


//! :DEVice:MRQ:MOTion:STATe:REPORt? <name>,<ch>
int mrhtDeviceMrqMotionStateReport_Query(int inst,int name,int chan, int* state);


//! :DEVice:MRQ:MOTion:RUN <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqMotionRun(int inst,int name,int chan,int wave);


//! :DEVice:MRQ:MOTion:RUN:STATe? <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqMotionRunState_Query(int inst,int name,int chan,int wave, int* state);


//! :DEVice:MRQ:MOTion:STOP <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqMotionStop(int inst,int name,int chan,int wave);


//! :DEVice:MRQ:MOTion:TRIGger:SOURce <name>,<ch>,<SOFTWARE|DIGITALIO|CAN|ALL>
int mrhtDeviceMrqMotionTriggerSource(int inst,int name,int chan,int trigSource);


//! :DEVice:MRQ:MOTion:TRIGger:SOURce? <name>,<ch>
int mrhtDeviceMrqMotionTriggerSource_Query(int inst,int name,int chan, int* trig);


//! :DEVice:MRQ:MOTion:OFFSet:STATe <name>,<ch>,<OFF|ON>
int mrhtDeviceMrqMotionOffsetState(int inst,int name,int chan,int state);


//! :DEVice:MRQ:MOTion:OFFSet:STATe? <name>,<ch>
int mrhtDeviceMrqMotionOffsetState_Query(int inst,int name,int chan, int* state);


//! :DEVice:MRQ:MOTion:OFFSet:VALue? <name>,<ch>
int mrhtDeviceMrqMotionOffsetValue_Query(int inst, char* value,int len);


//! :DEVice:MRQ:MOTion:ABCOUNt?  <name>,<ch>
int mrhtDeviceMrqMotionAbcount_Query(int inst,int name,int chan, int* count);


//! :DEVice:MRQ:MOTion:ABCOUNt:CLEAr  <name>,<ch>
int mrhtDeviceMrqMotionAbcountClear(int inst,int name,int chan);


//! :DEVice:MRQ:MOTion:ADJust <name>,<CH>,<position>,<time>
int mrhtDeviceMrqMotionAdjust(int inst,int name,int chan,int position,int time);


//! :DEVice:MRQ:MOTion:REVERSe <name>,<OFF|0|ON|1>
int mrhtDeviceMrqMotionReverse(int inst,int name,int state);


//! :DEVice:MRQ:MOTion:REVERSe? <name>
int mrhtDeviceMrqMotionReverse_Query(int inst,int name, int* state);


//! :DEVice:MRQ:MOTOR:STEP:ANGLe <name>,<CH>,<1.8|0.9|15|7.5>
int mrhtDeviceMrqMotorStepAngle(int inst,int name,int chan,int step);


//! :DEVice:MRQ:MOTOR:STEP:ANGLe? <name>,<CH>
int mrhtDeviceMrqMotorStepAngle_Query(int inst,int name,int chan, int* step);


//! :DEVice:MRQ:MOTOR:MOTion:TYPe <name>,<CH>,<ROTARY|LINEAR>
int mrhtDeviceMrqMotorMotionType(int inst,int name,int chan,int motion);


//! :DEVice:MRQ:MOTOR:MOTion:TYPe? <name>,<CH>
int mrhtDeviceMrqMotorMotionType_Query(int inst,int name,int chan, int* motion);


//! :DEVice:MRQ:MOTOR:POSition:UNIT <name>,<CH>,< ANGLE|RADIAN|MILLIMETER>
int mrhtDeviceMrqMotorPositionUnit(int inst,int name,int chan,int pos);


//! :DEVice:MRQ:MOTOR:POSition:UNIT? <name>,<CH>
int mrhtDeviceMrqMotorPositionUnit_Query(int inst,int name,int chan, int* pos);


//! :DEVice:MRQ:MOTOR:GEAR:RATio <name>,<CH>,<above>,<below>
int mrhtDeviceMrqMotorGearRatio(int inst,int name,int chan,int above,int below);


//! :DEVice:MRQ:MOTOR:GEAR:RATio? <name>,<CH>
int mrhtDeviceMrqMotorGearRatio_Query(int inst,int name,int chan, int* above,int* below);


//! :DEVice:MRQ:MOTOR:LEAD <name>,<CH>,<millimeter>
int mrhtDeviceMrqMotorLead(int inst,int name,int chan,int mm);


//! :DEVice:MRQ:MOTOR:LEAD? <name>,<CH>
int mrhtDeviceMrqMotorLead_Query(int inst,int name,int chan, int* mm);


//! :DEVice:MRQ:MOTOR:SIZE <name>,<CH>,<8|11|14|17|23|24>
int mrhtDeviceMrqMotorSize(int inst,int name,int chan,int size);


//! :DEVice:MRQ:MOTOR:SIZE? <name>,<CH>
int mrhtDeviceMrqMotorSize_Query(int inst,int name,int chan, int* size);


//! :DEVice:MRQ:MOTOR:VOLTage <name>,<CH>,<volt>
int mrhtDeviceMrqMotorVoltage(int inst,int name,int chan,int volt);


//! :DEVice:MRQ:MOTOR:VOLTage? <name>,<CH>
int mrhtDeviceMrqMotorVoltage_Query(int inst,int name,int chan, int* volt);


//! :DEVice:MRQ:MOTOR:CURRent <name>,<CH>,<current>
int mrhtDeviceMrqMotorCurrent(int inst,int name,int chan,int curr);


//! :DEVice:MRQ:MOTOR:CURRent? <name>,<CH>
int mrhtDeviceMrqMotorCurrent_Query(int inst,int name,int chan, int* curr);


//! :DEVice:MRQ:MOTOR:BACKLash <name>,<CH>,<lash>
int mrhtDeviceMrqMotorBacklash(int inst,int name,int chan,int lash);


//! :DEVice:MRQ:MOTOR:BACKLash? <name>,<CH>
int mrhtDeviceMrqMotorBacklash_Query(int inst,int name,int chan, int* lash);


//! :DEVice:MRQ:PVT:CONFig <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<END|CLEAR>
int mrhtDeviceMrqPvtConfig(int inst,int name,int chan,int wave,int state);


//! :DEVice:MRQ:PVT:VALue <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<p>,<v>,<t>
int mrhtDeviceMrqPvtValue(int inst,int name,int chan,int wave,double p,double v,double t);


//! :DEVice:MRQ:PVT:STATe? <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtState_Query(int inst,int name,int chan,int wave, int* state);


//! :DEVice:MRQ:PVT:TSCale <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<speedup>,<speedcut>
int mrhtDeviceMrqPvtTscale(int inst,int name,int chan,int wave,int speedup,int speedcut);


//! :DEVice:MRQ:PVT:MODe:EXE <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<CYCLE|FIFO>
int mrhtDeviceMrqPvtModeExe(int inst,int name,int chan,int wave,int exe);


//! :DEVice:MRQ:PVT:MODe:EXE? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtModeExe_Query(int inst,int name,int chan,int wave, int* exe);


//! :DEVice:MRQ:PVT:MODe:PLAN <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<CUBICPOLY|LINEAR|UNIFORM|TRAPEZOID>
int mrhtDeviceMrqPvtModePlan(int inst,int name,int chan,int wave,int plan);


//! :DEVice:MRQ:PVT:MODe:PLAN? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtModePlan_Query(int inst,int name,int chan,int wave, int* plan);


//! :DEVice:MRQ:PVT:MODe:MOTion <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<PVT|LVT_CORRECT|LVT_NOCORRECT>
int mrhtDeviceMrqPvtModeMotion(int inst,int name,int chan,int wave,int motion);


//! :DEVice:MRQ:PVT:MODe:MOTion? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtModeMotion_Query(int inst,int name,int chan,int wave, int* motion);


//! :DEVice:MRQ:PVT:MODIFy:DUTY <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<1/4|1/8|1/16|1/32>
int mrhtDeviceMrqPvtModifyDuty(int inst,int name,int chan,int wave,int duty);


//! :DEVice:MRQ:PVT:MODIFy:DUTY? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtModifyDuty_Query(int inst,int name,int chan,int wave, int* duty);


//! :DEVice:MRQ:PVT:END:STATe <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<STOP|HOLD>
int mrhtDeviceMrqPvtEndState(int inst,int name,int chan,int wave,int state);


//! :DEVice:MRQ:PVT:END:STATe? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtEndState_Query(int inst,int name,int chan,int wave, int* state);


//! :DEVice:MRQ:PVT:ADEC:SCALe <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<scaleA>,<scaleD>
int mrhtDeviceMrqPvtAdecScale(int inst,int name,int chan,int wave,int scaleA,int scaleD);


//! :DEVice:MRQ:PVT:ADEC:SCALe? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtAdecScale_Query(int inst,int name,int chan,int wave, int* scaleA,int* scaleD);


//! :DEVice:MRQ:PVT:STOP:MODe <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,< IMMEDIATE|DISTANCE>
int mrhtDeviceMrqPvtStopMode(int inst,int name,int chan,int wave,int mode);


//! :DEVice:MRQ:PVT:STOP:MODe? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtStopMode_Query(int inst,int name,int chan,int wave, int* mode);


//! :DEVice:MRQ:PVT:STOP:DISTance <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<dist>
int mrhtDeviceMrqPvtStopDistance(int inst,int name,int chan,int wave,int dist);


//! :DEVice:MRQ:PVT:STOP:DISTance? <name>,<CH>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqPvtStopDistance_Query(int inst,int name,int chan,int wave, int* dist);


//! :DEVice:MRQ:LOSTstep:LINe:STATe <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<OFF|ON>
int mrhtDeviceMrqLoststepLineState(int inst,int name,int chan,int wave,int state);


//! :DEVice:MRQ:LOSTstep:LINe:STATe? <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqLoststepLineState_Query(int inst,int name,int chan,int wave, int* state);


//! :DEVice:MRQ:LOSTstep:LINe:THREShold <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<value>
int mrhtDeviceMrqLoststepLineThreshold(int inst,int name,int chan,int wave,int value);


//! :DEVice:MRQ:LOSTstep:LINe:THREShold? <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqLoststepLineThreshold_Query(int inst,int name,int chan,int wave, int* value);


//! :DEVice:MRQ:LOSTstep:LINe:RESPonse <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>,<NONE|ALARM|STOP|ALARM&STOP>
int mrhtDeviceMrqLoststepLineResponse(int inst,int name,int chan,int wave,int resp);


//! :DEVice:MRQ:LOSTstep:LINe:RESPonse? <name>,<ch>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtDeviceMrqLoststepLineResponse_Query(int inst,int name,int chan,int wave, int* resp);


//! :DEVice:MRQ:REPort:STATe <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>,<OFF|ON>
int mrhtDeviceMrqReportState(int inst,int name,int chan,int index,int state);


//! :DEVice:MRQ:REPort:STATe? <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>
int mrhtDeviceMrqReportState_Query(int inst,int name,int chan,int index, int* state);


//! :DEVice:MRQ:REPort:PERiod <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>,<ms>
int mrhtDeviceMrqReportPeriod(int inst,int name,int chan,int index,int ms);


//! :DEVice:MRQ:REPort:PERiod? <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>
int mrhtDeviceMrqReportPeriod_Query(int inst,int name,int chan,int index, int* ms);


//! :DEVice:MRQ:REPort:DATA:VALue? <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>
int mrhtDeviceMrqReportDataValue_Query(int inst,int name,int chan,int index, char* data,int len);


//! :DEVice:MRQ:REPort:DATA:Queue? <name>,<ch>,<TORQUE|CYCLE|SGALL|SGSE|DIST|ABSEN>[,count]
int mrhtDeviceMrqReportDataQueue_Query(int inst,int name,int chan,int index,int count, int * value);


//! :DEVice:MRQ:TRIGger:MODe <name>,<ch>,<PATTERN|LEVEL>
int mrhtDeviceMrqTriggerMode(int inst,int name,int chan,int mode);


//! :DEVice:MRQ:TRIGger:MODe? <name>,<ch>
int mrhtDeviceMrqTriggerMode_Query(int inst,int name,int chan, int* mode);


//! :DEVice:MRQ:TRIGger:LEVel:STATe <name>,<ch>,<TRIGL|TRIGR>,<OFF|ON>
int mrhtDeviceMrqTriggerLevelState(int inst,int name,int chan,int trig,int state);


//! :DEVice:MRQ:TRIGger:LEVel:STATe? <name>,<ch>,<TRIGL|TRIGR>
int mrhtDeviceMrqTriggerLevelState_Query(int inst,int name,int chan,int trig, int* state);


//! :DEVice:MRQ:TRIGger:LEVel:TYPe <name>,<ch>,<TRIGL|TRIGR>,<RESERVE|LOW|RISE|FALL|HIGH>
int mrhtDeviceMrqTriggerLevelType(int inst,int name,int chan,int trig,int type);


//! :DEVice:MRQ:TRIGger:LEVel:TYPe? <name>,<ch>,<TRIGL|TRIGR>
int mrhtDeviceMrqTriggerLevelType_Query(int inst,int name,int chan,int trig, int* type);


//! :DEVice:MRQ:TRIGger:LEVel:RESPonse <name>,<ch>,<TRIGL|TRIGR>,<NONE|ALARM|STOP|ALARM&STOP>
int mrhtDeviceMrqTriggerLevelResponse(int inst,int name,int chan,int trig,int resp);


//! :DEVice:MRQ:TRIGger:LEVel:RESPonse? <name>,<ch>,<TRIGL|TRIGR>
int mrhtDeviceMrqTriggerLevelResponse_Query(int inst,int name,int chan,int trig, int* resp);


//! :DEVice:MRQ:TRIGger:LEVel:PERIod <name>,<ch>,<TRIGL|TRIGR>,<period>
int mrhtDeviceMrqTriggerLevelPeriod(int inst,int name,int chan,int trig,int period);


//! :DEVice:MRQ:TRIGger:LEVel:PERIod? <name>,<ch>,<TRIGL|TRIGR>
int mrhtDeviceMrqTriggerLevelPeriod_Query(int inst,int name,int chan,int trig, int* period);


//! :DEVice:MRQ:DRIVER:TYPe? <name>,<ch>
int mrhtDeviceMrqDriverType_Query(int inst,int name,int chan, char* type,int len);


//! :DEVice:MRQ:DRIVER:CURRent <name>,<CH>,<current>
int mrhtDeviceMrqDriverCurrent(int inst,int name,int chan,int curr);


//! :DEVice:MRQ:DRIVER:CURRent? <name>,<CH>
int mrhtDeviceMrqDriverCurrent_Query(int inst,int name,int chan, int* curr);


//! :DEVice:MRQ:DRIVER:MICROStep <name>,<CH>,<256|128|64|32|16|8|4|2|1>
int mrhtDeviceMrqDriverMicrostep(int inst,int name,int chan,int micr);


//! :DEVice:MRQ:DRIVER:MICROStep? <name>,<CH>
int mrhtDeviceMrqDriverMicrostep_Query(int inst,int name,int chan, int* micr);


//! :DEVice:MRQ:DRIVER:STATe <name>,<CH>,<OFF|ON>
int mrhtDeviceMrqDriverState(int inst,int name,int chan,int state);


//! :DEVice:MRQ:DRIVER:STATe? <name>,<CH>
int mrhtDeviceMrqDriverState_Query(int inst,int name,int chan, int* state);


//! :DEVice:MRQ:ENCODer:LINe:NUMber <name>,<ch>,<num>
int mrhtDeviceMrqEncoderLineNumber(int inst,int name,int chan,int num);


//! :DEVice:MRQ:ENCODer:LINe:NUMber? <name>,<ch>
int mrhtDeviceMrqEncoderLineNumber_Query(int inst,int name,int chan, int* num);


//! :DEVice:MRQ:ENCODer:CHANnel:NUMber <name>,<ch>,<1|3>
int mrhtDeviceMrqEncoderChannelNumber(int inst,int name,int chan,int chanNum);


//! :DEVice:MRQ:ENCODer:CHANnel:NUMber? <name>,<ch>
int mrhtDeviceMrqEncoderChannelNumber_Query(int inst,int name,int chan, int* chanNum);


//! :DEVice:MRQ:ENCODer:TYPe <name>,<ch>,<INCREMENTAL|ABSOLUTE>
int mrhtDeviceMrqEncoderType(int inst,int name,int chan,int type);


//! :DEVice:MRQ:ENCODer:TYPe? <name>,<ch>
int mrhtDeviceMrqEncoderType_Query(int inst,int name,int chan, int* type);


//! :DEVice:MRQ:ENCODer:MULTIPLe <name>,<ch>,<multiple>
int mrhtDeviceMrqEncoderMultiple(int inst,int name,int chan,int multiple);


//! :DEVice:MRQ:ENCODer:MULTIPLe? <name>,<ch>
int mrhtDeviceMrqEncoderMultiple_Query(int inst,int name,int chan, int* multiple);


//! :DEVice:MRQ:ENCODer:STATe <name>,<ch>,<NONE|OFF|ON>
int mrhtDeviceMrqEncoderState(int inst,int name,int chan,int state);


//! :DEVice:MRQ:ENCODer:STATe? <name>,<ch>
int mrhtDeviceMrqEncoderState_Query(int inst,int name,int chan, int* state);


//! :DEVice:MRQ:ENCODerFEEDBACK <name>,<ch>,<feed>
int mrhtDeviceMrqEncoderfeedback(int inst,int name,int chan,int feed);


//! :DEVice:MRQ:ENCODerFEEDBACK? <name>,<ch>
int mrhtDeviceMrqEncoderfeedback_Query(int inst,int name,int chan, int* feed);


//! :DEVice:MRQ:UART<n>:APPLy <name>,<parity>,<wordlen>,<stopbit>
int mrhtDeviceMrqUartApply(int inst,int uart,int name,int parity,int wordlen,int stopbit);


//! :DEVice:MRQ:UART<n>:APPLy? <name>
int mrhtDeviceMrqUartApply_Query(int inst,int uart,int name, int* parity,int* wordlen,int* stopbit);


//! :DEVice:MRQ:UART<n>:FLOWctrl <name>,<NONE|RTS|CTS|RTS_CTS>
int mrhtDeviceMrqUartFlowctrl(int inst,int uart,int name,int flow);


//! :DEVice:MRQ:UART<n>:FLOWctrl? <name>
int mrhtDeviceMrqUartFlowctrl_Query(int inst,int uart,int name, int* flow);


//! :DEVice:MRQ:UART<n>:SENSor<n>:STATe <name>,<OFF|ON>
int mrhtDeviceMrqUartSensorState(int inst,int uart,int sensor,int name,int state);


//! :DEVice:MRQ:UART<n>:SENSor<n>:STATe? <name>
int mrhtDeviceMrqUartSensorState_Query(int inst,int uart,int sensor,int name, int* state);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig  :ALL <name>,<sof>,<framelen>,<num>,<period>
int mrhtDeviceMrqUartSensorConfig(int inst,int uart,int sensor,int name,int sof,int framelen,int num,int period);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:ALL? <name>
int mrhtDeviceMrqUartSensorConfigAll_Query(int inst,int uart,int sensor,int name, int* sof,int* framelen,int* num,int* period);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:SOF <name>,<sof>
int mrhtDeviceMrqUartSensorConfigSof(int inst,int uart,int sensor,int name,int sof);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:SOF? <name>
int mrhtDeviceMrqUartSensorConfigSof_Query(int inst,int uart,int sensor,int name, int* sof);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:FRAMELen <name>,<len>
int mrhtDeviceMrqUartSensorConfigFramelen(int inst,int uart,int sensor,int name,int len);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:FRAMELen? <name>
int mrhtDeviceMrqUartSensorConfigFramelen_Query(int inst,int uart,int sensor,int name, int* len);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:NUM <name>,<num>
int mrhtDeviceMrqUartSensorConfigNum(int inst,int uart,int sensor,int name,int num);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:NUM? <name>
int mrhtDeviceMrqUartSensorConfigNum_Query(int inst,int uart,int sensor,int name, int* num);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:PERIod <name>,<time>
int mrhtDeviceMrqUartSensorConfigPeriod(int inst,int uart,int sensor,int name,int time);


//! :DEVice:MRQ:UART<n>:SENSor<n>:CONFig:PERIod? <name>
int mrhtDeviceMrqUartSensorConfigPeriod_Query(int inst,int uart,int sensor,int name, int* time);


//! :DEVice:MRQ:UART<n>:SENSor<n>:DATA? <name>
int mrhtDeviceMrqUartSensorData_Query(int inst,int uart,int sensor,int name, char* data,int len);


//! :DEVice:MRQ:DALarm:STATe? <name>,<ch>
int mrhtDeviceMrqDalarmState_Query(int inst,int name,int chan, int* state);


//! :DEVice:MRQ:DALarm:STATe <name>,<ch>,<ON|OFF>
int mrhtDeviceMrqDalarmState(int inst,int name,int chan,int state);


//! :DEVice:MRQ:DALarm:ALARm1:DISTance <name>,<ch>,<dist>
int mrhtDeviceMrqDalarmAlarm1Distance(int inst,int name,int chan,int dist);


//! :DEVice:MRQ:DALarm:ALARm1:DISTance? <name>,<ch>
int mrhtDeviceMrqDalarmAlarm1Distance_Query(int inst,int name,int chan, int* dist);


//! :DEVice:MRQ:DALarm:ALARm2:DISTance <name>,<ch>,<dist>
int mrhtDeviceMrqDalarmAlarm2Distance(int inst,int name,int chan,int dist);


//! :DEVice:MRQ:DALarm:ALARm2:DISTance? <name>,<ch>
int mrhtDeviceMrqDalarmAlarm2Distance_Query(int inst,int name,int chan, int* dist);


//! :DEVice:MRQ:DALarm:ALARm3:DISTance <name>,<ch>,<dist>
int mrhtDeviceMrqDalarmAlarm3Distance(int inst,int name,int chan,int dist);


//! :DEVice:MRQ:DALarm:ALARm3:DISTance? <name>,<ch>
int mrhtDeviceMrqDalarmAlarm3Distance_Query(int inst,int name,int chan, int* dist);


//! :DEVice:MRQ:NDRiver:TYPe? <name>,<ch>
int mrhtDeviceMrqNdriverType_Query(int inst,int name,int chan, char* type,int len);


//! :DEVice:MRQ:NDRiver:CURRent <name>,<current>
int mrhtDeviceMrqNdriverCurrent(int inst,int name,int curr);


//! :DEVice:MRQ:NDRiver:CURRent? <name>
int mrhtDeviceMrqNdriverCurrent_Query(int inst,int name, int* curr);


//! :DEVice:MRQ:NDRiver:MICRosteps <name>,<RESERVE|RESERVE|RESERVE|32|16|8|4|2|1>
int mrhtDeviceMrqNdriverMicrosteps(int inst,int name,int micr);


//! :DEVice:MRQ:NDRiver:MICRosteps? <name>
int mrhtDeviceMrqNdriverMicrosteps_Query(int inst,int name, int* micr);


//! :DEVice:MRQ:NDRiver:STATe? <name>,<ch>
int mrhtDeviceMrqNdriverState_Query(int inst,int name,int chan, int* state);


//! :DEVice:MRQ:NDRiver:STATe <name>,<ch>,<OFF|ON>
int mrhtDeviceMrqNdriverState(int inst,int name,int chan,int state);


//! :DEVice:MRV:PT <>
int mrhtDeviceMrvPt(int inst);


//! :ROBOT:ALLOC? <MRX-T4|MRX-AS|MRX-H2|MRX-DELTA>,<(CH_LIST)>
int mrhtRobotAlloc_Query(int inst,int configuration,char* chanList, int* name);


//! :ROBOT:CONFIGuration:FILe:RESET
int mrhtRobotConfigurationFileReset(int inst);


//! :ROBOT:CONFIGuration:FILe:EXPort 
int mrhtRobotConfigurationFileExport(int inst);


//! :ROBOT:CONFIGuration:FILe:IMPort   
int mrhtRobotConfigurationFileImport(int inst);


//! :ROBOT:CONFIGuration:FILe:STATe?
int mrhtRobotConfigurationFileState_Query(int inst, int* state);


//! :ROBOT:CONFIGuration:FILe:READ?
int mrhtRobotConfigurationFileRead_Query(int inst, char* file,int len);


//! :ROBOT:CONFIGuration? <name>
int mrhtRobotConfiguration_Query(int inst,int name, char* configuration,int len);


//! :ROBOT:DELETe <name>
int mrhtRobotDelete(int inst);


//! :ROBOT:SUBTYPE <name>,<type>
int mrhtRobotSubtype(int inst,int name,int type);


//! :ROBOT:SUBTYPE? <name>
int mrhtRobotSubtype_Query(int inst,int name, int* type);


//! :ROBOT:COORDinate <name>,<coordiante>
int mrhtRobotCoordinate(int inst,int name,int coordiante);


//! :ROBOT:COORDinate? <name>
int mrhtRobotCoordinate_Query(int inst,int name, int* coordiante);


//! :ROBOT:ZERO:AXIS <name>,<x>,<y>[,<z>]
int mrhtRobotZeroAxis(int inst,int name,int x,int y,int z);


//! :ROBOT:ZERO:AXIS?  <name>
int mrhtRobotZeroAxis_Query(int inst,int name, int* x,int* y,int* z);


//! :ROBOT:ZERO:PROJect <name>,<x>,<y>[,<z>]
int mrhtRobotZeroProject(int inst,int name,int x,int y,int z);


//! :ROBOT:ZERO:PROJect? <name>
int mrhtRobotZeroProject_Query(int inst,int name, char* value,int len);


//! :ROBOT:LIMIt:SOFT:POSITive <name>,<x>,<y>[,<z>]
int mrhtRobotLimitSoftPositive(int inst,int name,int x,int y,int z);


//! :ROBOT:LIMIt:SOFT:POSITive? <name>
int mrhtRobotLimitSoftPositive_Query(int inst,int name, int* x,int* y,int* z);


//! :ROBOT:LIMIt:SOFT:NEGATive <name>,<x>,<y>[,<z>]
int mrhtRobotLimitSoftNegative(int inst,int name,int x,int y,int z);


//! :ROBOT:LIMIt:SOFT:NEGATive? <name>
int mrhtRobotLimitSoftNegative_Query(int inst,int name, int* x,int* y,int* z);


//! :ROBOT:DEVice:NAMe? <name>
int mrhtRobotDeviceName_Query(int inst,int name, int* devname);


//! :ROBOT:NAMe?
int mrhtRobotName_Query(int inst, char* name,int len);


//! :ROBOT:COUNt?
int mrhtRobotCount_Query(int inst, int* count);


//! :ROBOT:WAVETABLE <name>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtRobotWavetable(int inst,int name,int wave);


//! :ROBOT:WAVETABLE?  <name>
int mrhtRobotWavetable_Query(int inst,int name, int* wave);


//! :ROBOT:IDENtify <OFF|ON>
int mrhtRobotIdentify(int inst,int state);


//! :ROBOT:RUN <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotRun(int inst,int name, int wave);


//! :ROBOT:STATe? <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotState_Query(int inst,int name,int wave, int* state);


//! :ROBOT:STOP <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotStop(int inst,int name,int wave);


//! :ROBOT:HOMe:WAVETABLE <name>,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>
int mrhtRobotHomeWavetable(int inst,int name,int wave);


//! :ROBOT:HOMe:WAVETABLE?  <name>
int mrhtRobotHomeWavetable_Query(int inst,int name, int* wave);


//! :ROBOT:HOMe:POSITION? <name>
int mrhtRobotHomePosition_Query(int inst,int name, char* pos,int len);


//! :ROBOT:HOMe:ANGLE?  <name>
int mrhtRobotHomeAngle_Query(int inst,int name, char* angle,int len);


//! :ROBOT:HOMe:RUN  <name>[,<time>]
int mrhtRobotHomeRun(int inst,int name,int time);


//! :ROBOT:HOMe:STOP <name>
int mrhtRobotHomeStop(int inst,int name);


//! :ROBOT:HOMe:STATe? <name>
int mrhtRobotHomeState_Query(int inst,int name, int* state);


//! :ROBOT:HOMe:MODe <name>,<mode>
int mrhtRobotHomeMode(int inst,int name,int mode);


//! :ROBOT:HOMe:MODe? <name>
int mrhtRobotHomeMode_Query(int inst,int name, int* mode);


//! :ROBOT:MOVe <name>,<x>,<y>,<z>,<t>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMove(int inst,int name,double x,double y,double z,double t,int wave);


//! :ROBOT:MOVe:HOLD <name>,<axle>,<speed>,<dir>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMoveHold(int inst,int name,int axle,int speed,int dir,int wave);


//! :ROBOT:MOVe:RELATive <name>,<x>,<y>,<z>,<t>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMoveRelative(int inst,int name,double x,double y,double z,double t,int wave);


//! :ROBOT:MOVe:LINear <name>,<x>,<y>,<z>,<t>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMoveLinear(int inst,int name,double x,double y,double z,double t,int wave);


//! :ROBOT:MOVe:LINear:RELATive <name>,<x>,<y>,<z>,<t>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMoveLinearRelative(int inst,int name,double x,double y,double z,double t,int wave);


//! :ROBOT:MOVe:JOG <name>,<axle>,<cr_time>,<cr_speed>,<speed>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotMoveJog(int inst,int name,int axle,double cr_time,double cr_speed,double speed,int wave);


//! :ROBOT:CURRENT:ANGLE?  <name>
int mrhtRobotCurrentAngle_Query(int inst,int name, char* angle,int len);


//! :ROBOT:CURRENT:POSITION? <name>
int mrhtRobotCurrentPosition_Query(int inst,int name, char* pos,int len);


//! :ROBOT:POINt:LOAD <name>,<x>,<y>,<z>,<e>,<t>,<mode>
int mrhtRobotPointLoad(int inst,int name,double x,double y,double z,double e,double t,int mode);


//! :ROBOT:POINt:COUNt? <name>
int mrhtRobotPointCount_Query(int inst,int name, int* count);


//! :ROBOT:POINt:RESOLVe <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotPointResolve(int inst,int name,int wave);


//! :ROBOT:POINt:CLEAr <name>
int mrhtRobotPointClear(int inst,int name);


//! :ROBOT:PVT:LOAD <name>,<p>,<v>,<t>,<axle>
int mrhtRobotPvtLoad(int inst,int name,double p,double v,double t,int axle);


//! :ROBOT:PVT:RESOLVe <name>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]
int mrhtRobotPvtResolve(int inst,int name,int wave);


//! :ROBOT:PVT:CLEAr <name>[,<axle>]
int mrhtRobotPvtClear(int inst,int name,int axle);


//! :ROBOT:FILe:IMPORT <name>,<filename>
int mrhtRobotFileImport(int inst,int name,char* file);


//! :ROBOT:FILe:EXPORT :LOCal <name>,<filename>
int mrhtRobotFileExport(int inst,int name,char* file);


//! :ROBOT:FILe:EXPORT:EXTERnal <name>,<filename>
int mrhtRobotFileExportExternal(int inst,int name,char* file);


//! :ROBOT:FILe:RESOLVe <name>,<section>[,<line>[,<MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8>]]
int mrhtRobotFileResolve(int inst,int name,int section,int line,int wave);


//! :ROBOT:INTERPOLATe:MODe <name>,<mode>
int mrhtRobotInterpolateMode(int inst,int name,int mode);


//! :ROBOT:INTERPOLATe:MODe? <name>
int mrhtRobotInterpolateMode_Query(int inst,int name, int* mode);


//! :ROBOT:INTERPOLATe:STEP <name>,<step>
int mrhtRobotInterpolateStep(int inst,int name,int step);


//! :ROBOT:INTERPOLATe:STEP? <name>
int mrhtRobotInterpolateStep_Query(int inst,int name, int* step);


//! :ROBOT:EFFECTor:SET  <name>,<type>,<CH>
int mrhtRobotEffectorSet(int inst,int name,int type,int chan);


//! :ROBOT:EFFECTor:DELETe <name>
int mrhtRobotEffectorDelete(int inst,int name);


//! :ROBOT:EFFECTor:EXEC  <name>,<p>,<t>
int mrhtRobotEffectorExec(int inst,int name,int p,int t);


//! :ROBOT:EFFECTor:EXEC:STOP  <name>
int mrhtRobotEffectorExecStop(int inst,int name);


//! :ROBOT:EFFECTor:EXEC:STATe? <name>
int mrhtRobotEffectorExecState_Query(int inst,int name, int* state);


//! :ROBOT:EFFECTor:HOMe <name>
int mrhtRobotEffectorHome(int inst,int name);


//! :ROBOT:EFFECTor:HOMe:STOP  <name>
int mrhtRobotEffectorHomeStop(int inst,int name);


//! :ROBOT:EFFECTor:HOMe:STATe? <name>
int mrhtRobotEffectorHomeState_Query(int inst,int name, int* state);


//! :STORage:FILe:MOTion:LOCal?
int mrhtStorageFileMotionLocal_Query(int inst, char* file,int len);


//! :STORage:FILe:MOTion:EXTERnal?
int mrhtStorageFileMotionExternal_Query(int inst, char* file,int len);


//! :STORage:FILe:MOTion:CONText:READ? <filename>
int mrhtStorageFileMotionContextRead_Query(int inst,char* file, char* context,int len);


//! :STORage:FILe:MOTion:CONText:WRITe :NAMe <filename>
int mrhtStorageFileMotionContextWrite(int inst,char* file);


//! :STORage:FILe:MOTion:CONText:WRITe:DATa <context>
int mrhtStorageFileMotionContextWriteData(int inst,char* context);


//! :STORage:FILe:MOTion:CONText:WRITe:END
int mrhtStorageFileMotionContextWriteEnd(int inst);



#ifdef __cplusplus
}
#endif
#endif  // MRHT_H