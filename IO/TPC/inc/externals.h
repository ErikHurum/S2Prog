/****************************************************************************
 **             - externals.h -
 **
 **
 ***************************************************************************/
#include "constants.h"
#include "Anpro1Const.h"
#include "structs.h"
#include "RTOS.H"


// OS-tasks
extern OS_TASK  TCB_USART0, TCB_WATCHDOG, TCB_DispCtl, TCB_Blink, TCB_Info;                // Task-control-blocks 
extern OS_TIMER TimerUSART0;
extern void Usart0Handler(void);
extern void DisplayHandler(void);
extern void DisplayBlink(void);
extern void WatchDogHandler(void);
extern void Info(void);

// OS-semaphores
extern OS_RSEMA    UARTSEND;

//OS timers
extern void TimoutUSART0(void);

// externals for USARTs
extern char TxBufferCh0[];   
extern char RxBufferCh0[]; 

extern char UnitID;  
extern char HostAddress ; 
extern char MyPriAddress ; 
extern char MySecAddress ; 

extern char RestartStatus;                      

extern char BlinkStatus;

extern char kbd_delay_cnt;     
extern char tx_status;
extern char RXTimeout;

extern char  packed_data[] ; 

// constant.h
extern __farflash const char crc[] ;
extern __farflash const char ascii_table[][3][5];
extern __farflash const char DispDrv140[][3];
extern __farflash const char DispArr196[];

//Display
extern void printLoDi(char);
extern void rorLoDis(char*, char);
extern void RefreshDisplay(char);
extern void PrintComError(char *, char);
extern void printXDi(char);

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
extern void CharToAscii(char, char *);

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
extern void UsartCheckPackage(char );
extern char CheckActionUart(char, unsigned short);
extern void ReceivePacketUart(char);
extern char CalcDSTxChecksum(char, unsigned short);
extern short CalcDSRxChecksum(char, unsigned short);
extern  char CheckADData( char *);
extern  char CheckEepData( char *);
extern __monitor void GoToSyncUART(char);
extern void Uart_BuildTail(char);
extern void Uart_BuildHeader(char) ;

extern void BuildEepData(char, short);
extern void BuildAPWriteData(char, short);
extern void BuildEEPWriteData(char, short);
extern void BuildDallasData(char, short);
extern void BuildStatusData(char, short pointer); 
extern void BuildCardData(char, short);
extern void BuildStackStatus(char, short);

extern void RecXText(char, short);
extern void RecLowText(char, short);
extern void RecHighText(char, short);
extern void RecPriBarVal(char, short);
extern void RecSecBarVal(char, short);
extern void RecAlStatus(char, short);
extern void RecAckStatus(char, short);   
extern void RecLoGraph(char, short);
extern void RecHiImage(char, short);
extern void RecValDisp(char, short);
extern void RecDisableDisp(char, short);
extern void RecEepData(char, short);
extern void RecSetupData(char, short);

extern void GetGotoBootloader(char, short);   

extern void WatchdogReset(void);

// structs
extern UARTDataType    UART[];
extern volatile DispData        Disp; 

