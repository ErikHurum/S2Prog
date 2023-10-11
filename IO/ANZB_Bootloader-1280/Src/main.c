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
#include <intrinsics.h>

extern char MyAddress(void);

void WDT_off(void)
{
    __disable_interrupt();
    __watchdog_reset();
    /* Clear WDRF in MCUSR */
    MCUSR &= ~(1<<WDRF);
    /* Write logical one to WDCE and WDE */
    /* Keep old prescaler setting to prevent unintentional time-out
    */
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    /* Turn off WDT */
    WDTCSR = 0x00;
    __enable_interrupt();
}

void WDT_Prescaler_Change(void)
{
    __disable_interrupt();
    __watchdog_reset();
    /* Start timed equence */
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    /* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
    //WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP0);
    /* Set new prescaler(time-out) value = 256K cycles (~2.0 s) */
    //WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
    /* Set new prescaler(time-out) value = 256K cycles (~4.0 s) */
    WDTCSR = (1<<WDE) | (1<<WDP3) ;


__enable_interrupt();
}



__C_task void main(void){
    //
    // watchdog off
    // if we don't do this, watchdog keeps
    // reseting the system in case of
    // intentional reset by app
    //
    WDT_off();
    WDT_Prescaler_Change();
    while ( (EECR & 1<<EEPE) != 0 );        //chech if EEPROM is ready
    EEARL = (0x0fff & 0xff);                // check high byte of eeprom 
    EEARH = (0x0fff >> 8);                  // if date = 0xaa enter uploader mode
    EECR |= (1<<EERE);                      // else jump to program
    if ( EEDR != 0xaa || MyAddress() == 0xF) {
        EEDR = 0;
        InitSystem();                       // Init the system

        GoToSyncUART() ;                    // go to sync modus for recive
        UART_DATA_REG0 ;                    // read dummy byte
        for(;;) {                           // suuuuuuperloooop here!!
            recchar(); 
             if(myUART.RxState == HANDLE){  // Package OK
                 UsartCheckPackage();
             }
        }                            
    } else {
        AppStart();        					// Jump to Reset vector 0x0000 in Application Section
    }
}



