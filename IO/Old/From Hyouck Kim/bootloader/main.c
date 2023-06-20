#ifdef __ATMEGA_1280__
#include	"iom1280.h"
#endif

#ifdef __ATMEGA_1281__
#include	"iom1281.h"
#endif

#include <inavr.h>
#include <stdio.h>

#include "events.h"
#include "timer.h"
#include "flash.h"

extern void InitSystem(void);
extern void modbus_init(void);

void (*AppStart)( void ) = 0x0000;       // Set up function pointer to RESET vector

unsigned char
read_boot_eeprom(void)
{
  unsigned char ret;

  while (EECR & (1<<EEPE))
    ;

  EEAR = EEPROM_BOOT_FLAG_ADDR;
  EECR |= (1 << EERE);

  ret = EEDR;

  return ret;
}

void
write_eeprom(unsigned short addr, unsigned char data)
{
  while (EECR & (1<<EEPE))
    ;

  EEAR = (addr & 0x0fff);

  EEDR = data;

  EECR |= (1<<EEMPE);
  EECR |= (1<<EEPE);
  
  while (EECR & (1<<EEPE))
    ;
}

static void
system_reset(unsigned char evt) 
{
  WDTCSR = 0x08;               //Start watchdog to genetate restart
}

#ifdef __ATMEGA_1280__
char
MyAddress(void)
{
  int Address = (~(PINE>>4) & 0x0f);

  return Address;
}
#endif

#ifdef __ATMEGA_1281__
char
MyAddress(void)
{
  int Address = (~(PIND>>4) & 0x0f);

  return Address;
}
#endif
int
main(void)
{
  unsigned char status;
  unsigned short first_2,
                 eep;

  //
  // watchdog off
  // if we don't do this, watchdog keeps
  // reseting the system in case of
  // intentional reset by app
  //
  asm("WDR");
  status = MCUSR;
  MCUSR &= ~(1<<WDRF);
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 0x00;
  (void)status;
  
  flash_read(0x0, (unsigned char*)&first_2, 2);
  eep = read_boot_eeprom();

  if (MyAddress() == 15 || eep == 0xaa || first_2 == 0xffff)
  {
    if(eep == 0xaa)
    {
      //
      // better this way in case of power recycle
      // so that board can enter normal app mode
      //
      write_eeprom(EEPROM_BOOT_FLAG_ADDR, 0xff);
    }

    InitSystem();

    // interrupt is disabled at this point

    init_loop_events();

    timer_init();
    modbus_init();

    register_event_handler(EVENTS_FLAG_RESET, system_reset);

    __enable_interrupt();

    run_event_dispatcher();
  }
  else if(eep == 0xbb)
  {
    // clear eeprom
    for (unsigned short addr = 0; addr < 4096; addr++)
    {
      write_eeprom(addr, 0xff);
    }
    // continue to boot
  }

  AppStart();

  //
  // BUG if we reach here
  //
  return 0;
}
