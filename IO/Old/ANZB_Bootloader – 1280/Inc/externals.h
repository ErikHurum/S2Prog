/****************************************************************************
 **             - externals.h -
 **
 **
 ***************************************************************************/
#include "constants.h"
#include "Anpro10Const.h"
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

extern char ResetStatus;                      

// constant.h
extern __farflash const char crc[] ;

// init.c 
extern void InitSystem(void);
extern void Init_CPU(void);
extern __monitor void Init_Watchdog(void);
extern void Init_IO(void);
extern void Init_TMR(void) ;
extern void Init_USART(unsigned long) ;
extern void Init_AD(void);
extern void Init_Values(void);

// Misc.c
extern char MyAddress(void);

// Serial.c
extern void initbootuart(void);
extern void sendchar(char);
extern void recchar(void);

// Usarts
extern char hostAddress ; 
extern void UsartCheckPackage(void );
extern char CheckActionUart(unsigned short);
extern void SendPacketUart(void);
extern void ReceivePacketUart(void);
extern char CalcDSTxChecksum(unsigned short);
extern short CalcDSRxChecksum(unsigned short);
extern __monitor void GoToSyncUART(void);
extern void Uart_BuildTail(void);
extern void Uart_BuildHeader(void) ;


extern void BuildStatusData(void); 
extern void BuildFlashID(void);
extern void EraseFlash(void);
extern void ProgramFlash(unsigned short);
extern void ReadFlash( unsigned short);
extern void ExitBootloader(void);   

extern void WatchdogReset(void);

// structs
extern UARTDataType My485UART;

