#ifndef FIXEDVARIABLES_H
#define FIXEDVARIABLES_H

struct ProgramVersionInfo {
	U8 ProdNo,
	PacketFormat,
	NewFunctions,
	Build;
};

//////////////////////////////////////////////////
//
// 	Static variables with fixed location
//	Mainly used to record reason for a restart
//
//////////////////////////////////////////////////
#define TASK_NAME_LENGTH    0x20

#if 1
#ifndef __cplusplus
__no_init struct ProgramVersionInfo BootVersion  		    @ 0x31fff000;
__no_init volatile unsigned        LastOSError              @ 0x31fff010;
__no_init volatile unsigned        LastErrAddress           @ 0x31fff048;
__no_init char                     LastOSErrorTask[ 0x20 ]  @ 0x31fff01C;
#else
#if defined(S2TXU) || defined(ANBOOTLOADER)
__no_init ProgramVersionInfo BootVersion  		   @ 0x31fff000;
__no_init volatile unsigned  LastOSError           @ 0x31fff010;
__no_init volatile unsigned  ProgProgress          @ 0x31fff014;
__no_init volatile unsigned  FlashErrorStatus      @ 0x31fff018;
__no_init char LastOSErrorTask[TASK_NAME_LENGTH]   @ 0x31fff01C;
__no_init volatile time_t LastStartTime            @ 0x31fff03C;
__no_init volatile int RestartRetryCnt             @ 0x31fff040;
__no_init volatile bool IsPowerOn                  @ 0x31fff044;
__no_init volatile unsigned LastErrAddress         @ 0x31fff048;  // This Also must be updated in RTOSInit_TXU.c
#else
extern ProgramVersionInfo BootVersion;
extern volatile unsigned  LastOSError         ;
extern volatile unsigned  ProgProgress        ;
extern volatile unsigned  FlashErrorStatus    ;
extern volatile char LastOSErrorTask[TASK_NAME_LENGTH];
extern volatile time_t LastStartTime          ;
extern volatile int RestartRetryCnt           ;
extern volatile bool IsPowerOn                ;
extern volatile unsigned LastErrAddress       ;

#endif
#endif
#else
#ifndef __cplusplus
__no_init volatile unsigned  LastOSError           @ 0x303ff010;
__no_init volatile unsigned  LastErrAddress        @ 0x303ff048;
__no_init char LastOSErrorTask[0x20]      		   @ 0x303ff01C;
#else
#if defined(S2TXU) || defined(ANBOOTLOADER)
__no_init ProgramVersionInfo BootVersion  		   @ 0x303ff000;
__no_init volatile unsigned  LastOSError           @ 0x303ff010;
__no_init volatile unsigned  ProgProgress          @ 0x303ff014;
__no_init volatile unsigned  FlashErrorStatus      @ 0x303ff018;
__no_init char LastOSErrorTask[TASK_NAME_LENGTH]   @ 0x303ff01C;
__no_init volatile time_t LastStartTime            @ 0x303ff03C;
__no_init volatile int RestartRetryCnt             @ 0x303ff040;
__no_init volatile bool IsPowerOn                  @ 0x303ff044;
__no_init volatile unsigned LastErrAddress         @ 0x303ff048;  // This Also must be updated in RTOSInit_TXU.c
#else
extern ProgramVersionInfo BootVersion;
extern volatile unsigned  LastOSError         ;
extern volatile unsigned  ProgProgress        ;
extern volatile unsigned  FlashErrorStatus    ;
extern volatile char LastOSErrorTask[0x20]    ;
extern volatile time_t LastStartTime          ;
extern volatile int RestartRetryCnt           ;
extern volatile bool IsPowerOn                ;
extern volatile unsigned LastErrAddress       ;

#endif
#endif
#endif
#endif
