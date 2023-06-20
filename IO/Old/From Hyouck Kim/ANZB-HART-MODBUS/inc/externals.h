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
extern char TxBufferCh1[];
extern char RxBufferCh1[];

extern char TxBuf16552Ch0[];
extern char RxBuf16552Ch0[];
extern char TxBuf16552Ch1[];
extern char RxBuf16552Ch1[];

extern char UnitID;
extern volatile char PortPair;

extern char RestartStatus;

extern volatile char EEPWriteOK;

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
extern volatile char *pWriteBuffer;
extern volatile char WriteCount;
extern char RestoreStat;
extern char TestEEPROM( void );
extern char ReadEEPROMByte( unsigned int );
extern void WriteEEPROMByte( unsigned int, char) ;
extern void WriteEEPROMU16( unsigned int, unsigned int) ;
extern void ReadEEPROMString( unsigned int , int* );
extern void WriteEEPROMString( unsigned int, char* ) ;
extern void ReadEEPROMBuffer( unsigned int , char , char* );
extern void WriteEEPROMBuffer( unsigned int , char , char* );
extern char EEPROMVersion(void);
extern void EEPROMReset(void);

// Usarts
extern volatile char hostAddress ;
extern void UsartCheckPackage(char );
extern char CheckActionUart(char, unsigned short);
extern void ReceivePacketUart(char);
extern char CalcDSTxChecksum(char, unsigned short);
extern short CalcDSRxChecksum(char, unsigned short);
extern __monitor void GoToSyncUART(char);
extern void Uart_BuildTail(char);
extern void Uart_BuildHeader(char) ;

extern void BuildStatusData(char);
extern void BuildStackStatus(char, short);
extern void GetResetEEPROM(char, short);
extern void GetGotoBootloader(char, short);
extern void GetEEPROMData(char, short);
extern void BuildEEPROMData(char, short);
extern void BuildADInt(char, short) ;

extern void GetADData(char, short);
extern void BuildADEpromdata(char, char );

extern void GetRS4Setup(char, short) ;
extern void BuildRS4Setup(char, short) ;
extern void BuildMData485(char, short) ;
extern void BuildRData485(char, short) ;
extern void BuildRadarInfo(char, short);
extern void BuildWHdata(char, short );
 

extern void GetANASetup(char, short) ;
extern void BuildANASetup(char, short) ;
extern void GetANAFilter(char, short) ;
extern void BuildANAFilter(char, short) ;
extern void BuildMDataANA(char, short);
extern void BuildMDataHart(char, short) ;


// AD7715
extern void SetAnaPort(void);
extern char ReadAdByte(void);
extern void WriteAdByte(char);

//PC16552
extern void Usart16552CheckPackage(char) ;
extern char CheckActionUart16552(char, unsigned short);
extern void ReceivePTOData(char, unsigned short) ;
extern void ReceiveWHData(char, unsigned short);
extern void ReceiveRData(char, unsigned short) ;
extern void ReceiveCData(char, unsigned short) ;
extern void ReceiveCardStatus(char, unsigned short) ;
extern void ReceiveConfigData(char, unsigned short) ;
extern void ReceiveCardEEPROMData(char, unsigned short) ;
extern void ReceiveWISData(char, unsigned short) ;
extern void ReceiveWISStatus(char, unsigned short) ;
extern void ReceiveWISXData(char, unsigned short);
extern void ReceiveRadarData(char, unsigned short);
extern void ReceiveRadarInfo(char, unsigned short); 

extern void SetRS4Port(void);
extern void Uart_BuildSndData(char);
extern void Uart_BuildReqM16552(char);
extern void Uart_BuildReqR16552(char);
extern void Uart_BuildReqC16552(char);
extern void Uart_BuildReqCardStatus(char);
extern void Uart_BuildReqConfig(char);
extern void Uart_BuildReqEEPROMData(char);
extern void Uart_BuildReqWISData(char);
extern void Uart_BuildReqWISCardStatus(char);
extern void Uart_BuildReqWISXData(char, char);
extern void Uart_BuildReqRadarData(char);
extern void Uart_BuildReqRadarInfo(char); 

extern void Uart_BuildHeader16552(char);
extern void Uart_BuildTail16552(char);
extern void ReceivePacketUart16552(char);
extern char CalcDSTxChecksumUART16552(char, unsigned short);
extern short CalcDSRxChecksum16552(char);
extern void GoToSyncUART16552(char);
extern void EmptyRxBuf16552(char);
extern void Init16552( char, unsigned long);


// ADc.c
extern volatile char ADChannel;

extern void WatchdogReset(void);

// structs
extern UARTDataType    UART[];
extern UARTDataType    UART16552[];
extern AnalogInt       ADInt ;
extern TargetData      TData;

