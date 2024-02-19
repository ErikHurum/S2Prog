#ifdef __ATMEGA_1280__
#include	"iom1280.h"
#endif

#ifdef __AVR_ATmega1281__
#include	"iom1281.h"
#endif

/*****************************************************************************
*
* Copyright (C) 2004 Scanjet Ariston AS
*
* File          : main.c
* Compiler      : IAR EWAAVR 2.28a
* Output size   : 
* Created       : 8-oct-03
*              
****************************************************************************/
#include "stdio.h"
#include "math.h"
#include "defines.h"
#include "assembly.h"
#include "variables.h"
#include <intrinsics.h>

extern char MyAddress(void);
extern void WDT_Prescaler_Change(void);
extern void EEPROM_writeByte(unsigned int uiAddress, unsigned char ucData);
extern unsigned char EEPROM_readByte(unsigned int uiAddress);
__no_init char BootloaderRevision    @0x21FF;


__C_task void main(void){
    //
    // watchdog off
    // if we don't do this, watchdog keeps
    // reseting the system in case of
    // intentional reset by app
    //

    /*
    asm("WDR");
    char status = MCUSR;
    MCUSR &= ~(1<<WDRF);
    WDTCSR = 0x00;
    (void)status;
    */
    __disable_interrupt();
    __watchdog_reset();
    WDT_Prescaler_Change();
    BootloaderRevision = PROG_VERSION;

    /* Clear WDRF in MCUSR */
    MCUSR &= ~(1<<WDRF);
    __enable_interrupt();

    while ( (EECR & 1<<EEPE) != 0 ) //chech if EEPROM is ready
        ;
    //EEARL = (0x0fff & 0xff);                // check high byte of eeprom 
    //EEARH = (0x0fff >> 8);                  // if date = 0xaa enter uploader mode
    //EECR |= (1<<EERE);                      // else jump to program
    //char ProgramOK = EEDR;
    int ProgramOK = EEPROM_readByte(0x0fff);
    DDRD   =  0x00;      // Port D data
    PORTD  =  0xf0;      // Port D data  //pullup addr
    int MyAddr = MyAddress();
    if ( ProgramOK != 0xaa || MyAddress() == 0xF) {
        EEDR = 0;
        InitSystem();                       // Init the system
        GoToSyncUART() ;                   // go to sync modus for recive
        UART_DATA_REG0 ;                    // read dummy byte
        for(;;) {                           // suuuuuuperloooop here!!
            __watchdog_reset();
            recchar();
             if(myUART.RxState == HANDLE){ // Package OK
                 UsartCheckPackage();
             }
        }                            
    } else {
        AppStart();        					// Jump to Reset vector 0x0000 in Application Section
    }
}



