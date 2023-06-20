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
#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "defines.h"
#include "assembly.h"
#include "variables.h"


__C_task void main(void){

    while ( (EECR & 1<<EEWE) != 0 ) //chech if EEPROM is ready
        ;
    EEARL = (0x0fff & 0xff);                // check high byte of eeprom 
    EEARH = (0x0fff >> 8);                  // if date = 0xaa enter uploader mode
    EECR |= (1<<EERE);                      // else jump to program
    if (EEDR != 0xaa ) {
        InitSystem();                       // Init the system
        GoToSyncUART(0) ;                   // go to sync modus for recive
        UART_DATA_REG0 ;                    // read dummy byte
        GoToSyncUART(1) ;                   // go to sync modus for recive
        UART_DATA_REG1 ;                    // read dummy byte
        for(;;) {                           // suuuuuuperloooop here!!
            recchar();
             if(UART[0].RxState == HANDLE){ // Package OK ch 0
                UsartCheckPackage(0);
             }
             if(UART[1].RxState == HANDLE){ // Package OK ch 1
                 UsartCheckPackage(1);
             }
        }                            
    } else {
        AppStart();        					// Jump to Reset vector 0x0000 in Application Section
    }
}



