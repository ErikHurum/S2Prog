/****************************************************************************************
/  Misc. routines
/
***************************************************************************************/
#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
#include "inavr.h"
#include "string.h"

/*************************************************************************
*   (This is a task)
*  Watchdog handler
*
*   NB!
*  This task runs on the lovest priority and all othr tasks will run.
*  In case of faul a task on higher priority will use all resources and
*  the watchdog will kick the CPU.
*************************************************************************/
void WatchDogHandler(void) {

    OS_Delay(100);                         // wait 2 seconds for other tasks to start and set TaskStatus
    asm("WDR");                             // kick the dog!!
    WDTCR = 0x1f;
    WDTCR = 0x0f;
    asm("WDR");                             // kick the dog!!
    while (1) {
        OS_Delay(100);
        __watchdog_reset();               //kick the dog
    }
}


/*************************************************************************
*
*  Get my address
*
*************************************************************************/
char MyAddress(void) {

#if (OS_UART == 0)
#else
    MyPriAddress = ReadEEPROMByte(EEPROM_PRI_ADDR) ; // Get sec address from EEPROM
    MySecAddress = ReadEEPROMByte(EEPROM_SEC_ADDR) ; // Get sec address from EEPROM
    return MySecAddress;
    //return 0x00;
#endif
}

/*************************************************************************
*
* 	Convert char to ASCII
*
*************************************************************************/
void CharToAscii(char data, char * buf){
    char i ;
    
    i= (data / 100) ;
    buf[0] = i + 0x30 ;
    data -= (i * 100) ;
    i= data /10 ;
    buf[1] = i + 0x30 ;
    data -= (i *10) ;
    buf[2] = data + 0x30 ;
    if (buf[0] == 0x30) {
        buf[0] = 0x20 ; // space
    }
    if ((buf[1] == 0x30) && (buf[0] == 0x20)) {
        buf[1] = 0x20 ; // space
    }
}

