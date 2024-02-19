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
extern void EEPROM_writeByte(unsigned int uiAddress, unsigned char ucData);
extern unsigned char EEPROM_readByte(unsigned int uiAddress);


// Serial.c
extern void initbootuart(void);
extern void sendchar(char c);
extern void recchar(void);

// Usarts
extern char hostAddress ; 
extern void UsartCheckPackage(void );
extern char CheckActionUart(unsigned short Cmd );
extern void SendPacketUart(void);
extern void ReceivePacketUart(char);
extern char CalcDSTxChecksum(unsigned short Size);
extern short CalcDSRxChecksum(char, unsigned short);
extern __monitor void GoToSyncUART(void);
extern void Uart_BuildTail(void);
extern void Uart_BuildHeader(void) ;


extern void BuildStatusData(char); 
extern void BuildFlashID(char);
extern void EraseFlash(void);
extern void ProgramFlash(unsigned Pointer);
extern void ReadFlash(unsigned Pointer);
extern void ExitBootloader(char);   

extern void WatchdogReset(void);

// structs
extern UARTDataType myUART;

