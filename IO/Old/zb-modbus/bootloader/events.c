///////////////////////////////////////////////////////////////////////
//
// minimal event loop
//
///////////////////////////////////////////////////////////////////////
#ifdef __ATMEGA_1280__
#include <iom1280.h>
#endif

#ifdef __ATMEGA_1281__
#include <iom1281.h>
#endif

#include <inavr.h>
#include <stdio.h>
#include "events.h"

static volatile unsigned char _events = 0;
static evt_handler_t          _handlers[EVENTS_NUM_EVENTS];

void
set_event(unsigned char evt)
{
  __disable_interrupt();
  _events |= (1 << evt);
  __enable_interrupt();
}

void
register_event_handler(unsigned char evt, evt_handler_t handler)
{
  _handlers[evt] = handler;
}

void
init_loop_events(void)
{
  unsigned char i;

  for(i = 0; i < EVENTS_NUM_EVENTS; i++)
  {
    _handlers[i] = NULL;
  }
  _events = 0;
}

void
run_event_dispatcher(void)
{
  unsigned char flags,
                evt;

  while(1)
  {
    __disable_interrupt();
    flags = _events;
    _events = 0;
    __enable_interrupt();

    for(evt = 0; evt < EVENTS_NUM_EVENTS; evt++)
    {
      if(flags & ( 1 << evt))
      {
        _handlers[evt](evt);
      }
    }
  }
}
