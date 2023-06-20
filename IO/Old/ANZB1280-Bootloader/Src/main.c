#ifdef __ATMEGA_1280__
#include	"iom1280.h"
#endif

#ifdef __ATMEGA_1281__
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


extern char MyAddress(void);

__C_task void main(void){
    //
    // watchdog off
    // if we don't do this, watchdog keeps
    // reseting the system in case of
    // intentional reset by app
    //
    asm("WDR");
    char status = MCUSR;
    MCUSR &= ~(1<<WDRF);
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    WDTCSR = 0x00;
    (void)status;

    while ( (EECR & 1<<EEPE) != 0 ) //chech if EEPROM is ready
        ;
    EEARL = (0x0fff & 0xff);                // check high byte of eeprom 
    EEARH = (0x0fff >> 8);                  // if date = 0xaa enter uploader mode
    EECR |= (1<<EERE);                      // else jump to program
    if (EEDR != 0xaa || MyAddress() == 0xF) {
        InitSystem();                       // Init the system

        GoToSyncUART(0) ;                   // go to sync modus for recive
        UART_DATA_REG0 ;                    // read dummy byte
        for(;;) {                           // suuuuuuperloooop here!!
            recchar();
             if(myUART.RxState == HANDLE){ // Package OK
                 UsartCheckPackage(0);
             }
        }                            
    } else {
        AppStart();        					// Jump to Reset vector 0x0000 in Application Section
    }
}



