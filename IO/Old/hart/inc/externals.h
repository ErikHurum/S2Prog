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
extern OS_TASK  TCB_USART0, TCB_USART1, TCB_WATCHDOG, TCB_RS485Ctl, TCB_RS485Rec, TCB_AD7715;               // Task-control-blocks
extern OS_TIMER TimerUSART0, TimerUSART1, TimerUART0, TimerUART1, TimerUSART0On, TimerUSART1On;
extern void Usart0Handler(void);
extern void Usart1Handler(void);
extern void WatchDogHandler(void);
extern void ExtRS485Ctl(void);
extern void ExtRS485Rec(void);
extern void AD7715(void);

// OS-semaphores
extern OS_RSEMA    UARTSEND;

//OS timers
extern void TimoutUSART0(void);
extern void TimoutUSART1(void);
extern void TimoutUSART0On(void);
extern void TimoutUSART1On(void);
extern void TimoutUART0(void);
extern void TimoutUART1(void);


// externals for USARTs
extern char TxBufferCh0[];
extern char RxBufferCh0[];
extern char MailBufCh0[MBUF_SIZE];

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
extern void Init_USART(char, unsigned long) ;
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
extern volatile char hostAddress ;
extern void ReceivePacketUart(char);
extern char CalcDSTxChecksum(UARTDataType *pUART, unsigned short Length);
extern short CalcDSRxChecksum(char, unsigned short);
extern __monitor void GoToSyncUART(char);
extern void Uart_BuildTail(UARTDataType *pUART);
extern void Uart_BuildHeader(UARTDataType *pUART) ;

extern void BuildStatusData(char);
extern void BuildStackStatus(char, unsigned char*);
extern void GetResetEEPROM(char, unsigned char*);
extern void GetGotoBootloader(char, unsigned char*);
extern void GetEEPROMData(char, unsigned char*);
extern void BuildEEPROMData(char, unsigned char*);
extern void BuildADInt(char, unsigned char*) ;

extern void GetADData(char, unsigned char*);

extern void GetHartSetup(char, unsigned char*) ;
extern void BuildHartSetup(char, unsigned char*) ;
extern void GetHartFilter(char, unsigned char*) ;
extern void BuildHartFilter(char, unsigned char*) ;
extern void BuildMDataHart(UARTDataType *pUART);

// AD7715
extern void SetAnaPort(void);
extern char ReadAdByte(void);
extern void WriteAdByte(char);

// ADc.c
extern volatile char ADChannel;

extern void WatchdogReset(void);

// structs
extern UARTDataType    UART[];
extern AnalogInt       ADInt ;
extern TargetData      TData;


