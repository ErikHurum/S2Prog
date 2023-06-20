/****************************************************************************
 **             - externals.h -
 **
 **
 ***************************************************************************/
#include "constants.h"
#include "Anpro10Const.h"
#include "Anpro1Const.h"
#include "structs.h"
#include "RTOS.H"


// OS-tasks
extern OS_TASK  TCB_USART0, TCB_WATCHDOG, TCB_AD7715,TCB_INT_ADC;               // Task-control-blocks
extern void Usart0Handler(void);
extern void WatchDogHandler(void);
extern void AD7715(void);

//OS timers
extern void TimoutUSART0On(void);

extern char UnitID;
extern volatile char PortPair;

extern char RestartStatus;

extern char EEPWriteOK;

// constant.h
extern __farflash const char crc[] ;

// init.c
extern void InitSystem(void);
extern void Init_CPU(void);
extern __monitor void Init_Watchdog(void);
extern void Init_IO(void);
extern void Init_TMR(void) ;
extern void Init_USART(unsigned long) ;
extern void Init_Values(void);

// Misc.c
extern char MyAddress(void);
extern char IsFloat(float);

// eeprom.c
extern char *pWriteBuffer;
extern char WriteCount;
extern char RestoreStat;
extern char TestEEPROM( void );
extern char ReadEEPROMByte( unsigned int );
extern void WriteEEPROMByte( unsigned int, char) ;
extern void ReadEEPROMString( unsigned int , int* );
extern void WriteEEPROMString( unsigned int, char* ) ;
extern void ReadEEPROMBuffer( unsigned int , char , char* );
extern void WriteEEPROMBuffer( unsigned int , char , char* );
extern char EEPROMVersion(void);
extern void EEPROMReset(void);

// Usarts

extern char hasStartedUARTTask;
extern volatile char CriticalComError;
extern volatile char hostAddress ;
extern void ReceivePacketMy485UART(char);
extern char CalcDSTxChecksum(unsigned Length);
extern void My485UART_BuildTail(void);
extern void My485UART_BuildHeader(void) ;

extern void BuildStatusData(void);
extern void BuildStackStatus( char *pointer);
extern void GetResetEEPROM(void);
extern void GetGotoBootloader( char* pointer);
extern void GetEEPROMData( char*);
extern void BuildEEPROMData( char *pointer);
extern void BuildADInt(  char *pointer) ;

extern void GetADData(char,  char*);

extern void GetHartSetup( char* pointer, unsigned Size) ;
extern void BuildHartSetup( char *pointer) ;
extern void GetHartFilter( char *pointer) ;
extern void BuildHartFilter(  char *pointer) ;
extern void BuildMDataHart(void);

// AD7715
extern OS_U32 Last_ADC_FuckUpTime;
extern OS_U32 Last_ADC_OK_Time   ;

extern char ReadAdByte(void);
extern void WriteAdByte(char);

// ADc.c


// structs
extern My485UARTDataType    My485UART;
extern AnalogInt       ADInt ;
extern TargetData      TData;


extern char StackTest1[];
extern char StackTest2[];
extern char StackTest3[];
extern char StackTest4[];
extern char StackTest5[];
extern char StackTest6[];
