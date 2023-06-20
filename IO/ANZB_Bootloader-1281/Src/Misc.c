/****************************************************************************************
/  Misc. routines
/
***************************************************************************************/
#ifdef __ATMEGA_1280__
#include	"iom1280.h"
#endif

#ifdef __ATMEGA_1281__
#include	"iom1281.h"
#endif
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
    //return 0;
    char Address = (~(PINE>>4) & 0x0f) ;
    return Address;
}
