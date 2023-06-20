/****************************************************************************************
/ Init the project
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
#include "inavr.h"
#include "string.h"

static void Init_IO( void );
static void Init_CPU( void );

// char UnitID;

/*
**===========================================================================
** Init the system according to board type
**===========================================================================
*/ 
void
InitSystem(void)
{
  DDRB   =  0x00 ;      // Port B data direction, bit 0, 4-7 out
  // UnitID = (PINB & 0x0c) >> 2;       //get the unit ID

  Init_CPU();                         // init all processes
  Init_IO();
}

/*
**===========================================================================
**n Init the CPU related registers
**===========================================================================
*/ 
static void
Init_CPU( void )
{
  unsigned char temp;
  __disable_interrupt();

  EIMSK = 0x00 ;        // External interrupt mask register 
  EICRA = 0x00 ;        // External interrupt control register Int 0/1 on low level
  EICRB = 0x00 ;        // External interrupt control register Int 0/1 enabled
  EIMSK = 0x00 ;        // External interrupt mask register 
  MCUCR = 0x00 ;        // MCU control register  External Ram + wait state
  XMCRA = 0x00 ;        // maximum wait states
  XMCRB = 0x00 ;        // Full 16 bit bus + bus keeper
  SREG  = 0x00 ;        // glabal interrupt

  // ResetStatus = MCUCR;       // Remember reset source
  MCUCR = 0x00;              // and reset
  /*--- Initialize buffer ---*/

  // enable bootloader interrupt
  temp = MCUCR;
  MCUCR = temp | (1 << IVCE);       // enable change of interrupt vectors
  MCUCR = temp | (1 << IVSEL);      // move inerrupt vectors to boot flash section 
}

/*
**===========================================================================
** Init the watchdog registers
**===========================================================================
*/ 
/*
__monitor void
Init_Watchdog( void )
{
  asm("WDR");                             // kick the dog!!
  WDTCSR = 0x1f;
  WDTCSR = 0x1f;
  asm("WDR");                             // kick the dog!!

}
*/

/*
**===========================================================================
** Init the IO related registers
**===========================================================================
*/ 
static void
Init_IO(void)
{
  DDRA   =  0x00 ;      // Port A data 
  PORTA  =  0x00 ;      // Port A data
  DDRB   =  0x00 ;      // Port B data 
  PORTB  =  0x00 ;      // Port B data   
  DDRC   =  0x00 ;      // Port C data 
  PORTC  =  0x00 ;      // Port C data
  DDRD   =  0x00 ;      // Port D data   
  PORTD  =  0xf0 ;      // Port D data  //pullup addr
  DDRE   =  0x0E ;      // Port E data direction, all out except rxd
  PORTE  =  0x00 ;      // Port E data 
  DDRF   =  0x00 ;      // Port F data 
  PORTF  =  0x00 ;      // Port F data 
  DDRG   =  0x00 ;      // Port G data 
  PORTG  =  0x00 ;      // Port G data 
}
