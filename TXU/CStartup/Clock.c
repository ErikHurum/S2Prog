
/*******************
 *
 * Copyright 1998-2003 IAR Systems. All rights reserved.
 *
 * $Revision: 1.6 $
 *
 * This is the default implementation of the "clock" function of the
 * standard library.  It can be replaced with a system-specific
 * implementation.
 *
 * The "clock" function should return the processor time used by the
 * program from some implementation-defined start time.  The value
 * should be such that if divided by the macro CLOCKS_PER_SEC the
 * result should yield the time in seconds.
 *
 * The value "(clock_t)-1" means that the processor time is not
 * available.
 *
 ********************/

#include <time.h>
#include <rtos.h>

_STD_BEGIN

#pragma module_name = "?clock"

clock_t (clock)(void)
{
  return ((clock_t) OS_Time);
}

_STD_END
