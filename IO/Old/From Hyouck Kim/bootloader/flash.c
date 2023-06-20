#ifdef __ATMEGA_1280__
#include <iom1280.h>
#endif

#ifdef __ATMEGA_1281__
#include <iom1281.h>
#endif

#include <inavr.h>

#include "flash.h"
#include "flash_asm.h"

void
flash_erase(unsigned long addr)
{
  unsigned short a;
  
  __disable_interrupt();
  
  RAMPZ = (addr >> 16) & 0xff;
  a = (addr & 0xffff);

  do_spm(a,(1<<PGERS) + (1<<SPMEN));
  do_spm(a, (1<<RWWSRE) + (1<<SPMEN));

  RAMPZ = 0x00;
  __enable_interrupt();
}

char
flash_program(unsigned long addr, unsigned char* buf, unsigned short len)
{
  unsigned short a,
                 i,
                 tmp;
  __disable_interrupt();
  
  RAMPZ = (addr >> 16) & 0xff;

  a = (addr & 0xffff);
  for(i = 0; i < len; i+=2, a += 2)
  {
    unsigned int data = buf[i] | buf[i + 1] << 8;
    
    fill_temp_buffer(data, a);
  }
  
  a = (addr & 0xffff);
  
  do_spm(a, (1<<PGWRT) + (1<<SPMEN));
  do_spm(a, (1<<RWWSRE) + (1<<SPMEN));

  //
  // verify
  //
  for(i = 0; i < len; i+= 2, a += 2)
  {
    // low byte low address, high byte high address
    tmp = read_program_memory(a, 0x00);

    if((buf[i] != (tmp & 0xff)) || (buf[i + 1] != ((tmp >> 8) & 0xff)))
    {
      __enable_interrupt();
      return 0;
    }
  }
  __enable_interrupt();
  return 1;
}

void
flash_read(unsigned long addr, unsigned char* buf, unsigned short len)
{
  unsigned short a,
                 i,
                 tmp;

  RAMPZ = (addr >> 16) & 0xff;

  a = (addr & 0xffff);
  for(i = 0; i < len; i += 2, a += 2)
  {
    // low byte low address, high byte high address
    tmp= read_program_memory(a, 0x00);
    buf[i + 0] = tmp & 0xff;
    buf[i + 1] = (tmp >> 8) & 0xff;
  }
  
  RAMPZ = 0;
}
