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
extern __near char TxBufferCh0[TXSIZE_UART];
extern __near char RxBufferCh0[RXSIZE_UART]; 

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
extern void Init_USART(unsigned long Baud) ;
extern void Init_AD(void);
extern void Init_Values(void);

// Misc.c
extern char MyAddress(void);

// Serial.c
extern void initbootuart(void);
extern void sendchar(char c);
extern void recchar(void);

// Usarts
extern char hostAddress ; 
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

// structs
extern UARTDataType myUART;

