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

typedef struct
{
  unsigned char ms_left;
  unsigned char running;
  unsigned char evt;
} timer_t;

#define TIMER_TICK_COUNT_FOR_1MS        250

static timer_t  _timers[NUM_TIMERS_SUPPORTED] =
{
  {
    .ms_left = 0,
    .running = 0,
    .evt = 0,
  },
  {
    .ms_left = 0,
    .running = 0,
    .evt = 0,
  },
  {
    .ms_left = 0,
    .running = 0,
    .evt = 0,
  },
};


unsigned long _tick;

#pragma vector = TIMER0_COMPA_vect
__interrupt void ISR_Tick(void) 
{ 
  set_event(EVENTS_FLAG_1MS_TIMER);
}

static void
__timer_tick_event(unsigned char evt)
{
  _tick++;

  for(char i = 0; i < NUM_TIMERS_SUPPORTED; i++)
  {
    if(_timers[i].running)
    {
      _timers[i].ms_left--;
      if(_timers[i].ms_left == 0)
      {
        set_event(_timers[i].evt);
        _timers[i].running = 0;
      }
    }
  }
}

void
timer_init(void)
{
  register_event_handler(EVENTS_FLAG_1MS_TIMER, __timer_tick_event);

  TCCR0A  = (1 << WGM01) | (0 << WGM00) |                /* CTC mode.        */
            (0 << COM0A1) | (0 << COM0A0) |              /* OC0A disabled.   */
            (0 << COM0B1) | (0 << COM0B0);               /* OC0B disabled.   */
  TCCR0B  = (0 << WGM02) | (1 << CS01) | (1 << CS00);    /* CTC mode., 64 prescale  */
  OCR0A   = TIMER_TICK_COUNT_FOR_1MS - 1;
  TCNT0   = 0;                                           /* Reset counter.   */
  TIFR0   = (1 << OCF0A);                                /* Reset pending.   */
  TIMSK0  = (1 << OCIE0A);                               /* IRQ on compare.  */
}

void
start_timer(timer_num_t num, unsigned char ms, unsigned char evt)
{
  _timers[num].ms_left = ms;
  _timers[num].evt = evt;
  _timers[num].running = 1;
}

void
stop_timer(timer_num_t num)
{
  _timers[num].running = 0;
}
