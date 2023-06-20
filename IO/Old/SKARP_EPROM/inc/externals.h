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
extern OS_TIMER TimerUSART0, TimerUSART1, TimerUART0, TimerUART1;
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
extern void Init_AD(void);
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
extern void ReadEEPROMString( unsigned int , char* );
extern void WriteEEPROMString( unsigned int, char* ) ;
extern void ReadEEPROMBuffer( unsigned int , char , char* );
extern void WriteEEPROMBuffer( unsigned int , char , char* );
extern char EEPROMVersion(void);
extern void EEPROMReset(void);

// Usarts
extern volatile char hostAddress ;
extern void UsartCheckPackage(char );
extern char CheckActionUart(char, unsigned int);
extern void ReceivePacketUart(char);
extern char CalcDSTxChecksum(char, unsigned int);
extern int CalcDSRxChecksum(char, unsigned int);
extern __monitor void GoToSyncUART(char);
extern void Uart_BuildTail(char);
extern void Uart_BuildHeader(char) ;

extern void BuildStatusData(char);
extern void BuildStackStatus(char, int);
extern void BuildPromData(char, int) ;

extern void GetResetEEPROM(char, int);
extern void GetGotoBootloader(char, int);
extern void GetEEPROMData(char, int);
extern void BuildEEPROMData(char, int);
extern void BuildADInt(char, int) ;

extern void GetADData(char, int);
extern void BuildADEpromdata(char, char );

extern void GetRS4Setup(char, int) ;
extern void BuildRS4Setup(char, int) ;
extern void BuildMData485(char, int) ;
extern void BuildRData485(char, int) ;

extern void GetANASetup(char, int) ;
extern void BuildANASetup(char, int) ;
extern void GetANAFilter(char, int) ;
extern void BuildANAFilter(char, int) ;
extern void BuildMDataANA(char, int) ;


// AD7715
extern void SetAnaPort(void);
extern char ReadAdByte(void);
extern void WriteAdByte(char);

//PC16552
extern void Usart16552CheckPackage(char) ;
extern char CheckActionUart16552(char, unsigned int);
extern void ReceivePTOData(char, unsigned int) ;
extern void ReceiveRData(char, unsigned int) ;
extern void ReceiveCData(char, unsigned int) ;
extern void ReceiveCardStatus(char, unsigned int) ;
extern void ReceiveConfigData(char, unsigned int) ;
extern void ReceiveCardEEPROMData(char, unsigned int) ;
extern void ReceiveWISData(char, unsigned int) ;
extern void ReceiveWISStatus(char, unsigned int) ;
extern void ReceiveWISXData(char, unsigned int);

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

extern void Uart_BuildHeader16552(char);
extern void Uart_BuildTail16552(char);
extern void ReceivePacketUart16552(char);
extern char CalcDSTxChecksumUART16552(char, unsigned int);
extern int CalcDSRxChecksum16552(char);
extern void GoToSyncUART16552(char);
extern void Write16552(char, char );
extern char Read16552(char);
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

