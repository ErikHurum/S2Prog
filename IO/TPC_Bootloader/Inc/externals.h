/****************************************************************************
 **             - externals.h -
 **
 **
 ***************************************************************************/
#include "constants.h"
#include "Anpro1Const.h"
#include "defines.h"
#include "structs.h"
#include "version.h"

extern void (*AppStart)( void ); 

// externals for USARTs
extern char TxBufferCh0[];   
extern char RxBufferCh0[]; 
extern char TxBufferCh1[];   
extern char RxBufferCh1[]; 

extern char UnitID;  

extern char RestartStatus;                      

extern char PageBuffer[];
extern char NoBLow;

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
extern char MyPriAddress ;
extern char MySecAddress ;
extern char hostAddress;
extern char MyAddress(void);


// Serial.c
extern void initbootuart(void);
extern void sendchar(char, char );
extern void recchar(void);

// Usarts
extern void UsartCheckPackage(char );
extern char CheckActionUart(char, unsigned short);
extern void SendPacketUart(char);
extern void ReceivePacketUart(char);
extern char CalcDSTxChecksum(char, unsigned short);
extern short CalcDSRxChecksum(char, unsigned short);
extern __monitor void GoToSyncUART(char);
extern void Uart_BuildTail(char);
extern void Uart_BuildHeader(char) ;


extern void BuildStatusData(char); 
extern void BuildFlashID(char);
extern void EraseFlash(char);
extern void ProgramFlash(char, unsigned short);
extern void ReadFlash(char, unsigned short);
extern void ExitBootloader(char);   

extern void WatchdogReset(void);

// EEPROM
extern char ReadEEPROMByte( unsigned int );
extern void WriteEEPROMByte( unsigned int, char  ) ;   


// structs
extern UARTDataType UART[];

