/****************************************************************************************
/ Uart communication to external ADcards
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
#include "version.h"
#include "RTOS.H"

/*************************************************************************
*
*  Usart handler
*
*************************************************************************/
void ADCOM(void) {
  while (1) {
  //    PORTE = ~PORTE & 0x04;
    OS_Delay (500);
  }
}

