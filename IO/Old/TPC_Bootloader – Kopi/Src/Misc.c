/****************************************************************************************
/  Misc. routines
/
***************************************************************************************/
#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "inavr.h"
#include "string.h"


/*************************************************************************
*
*  Get my address
*
*************************************************************************/
char MyAddress(void) {

    MyPriAddress = ReadEEPROMByte(EEPROM_PRI_ADDR) ; // Get sec address from EEPROM
    MySecAddress = ReadEEPROMByte(EEPROM_SEC_ADDR) ; // Get sec address from EEPROM
    return MySecAddress;

//    return (0x00) ; //AStmark to be set in some way .......
}
