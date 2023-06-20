/*******************
 *
 * Copyright 1998-2003 IAR Systems. All rights reserved.
 *
 * $Revision: 1.4 $
 *
 * This is the default implementation of the "time" function of the
 * standard library.  It can be replaced with a system-specific
 * implementation.
 *
 * The "time" function returns the current calendar time.  (time_t)-1
 * should be returned if the calendar time is not available.  The time
 * is measured in seconds since the first of January 1970.
 *
 ********************/

#include <time.h>
extern 	volatile time_t CurrentTime;
#pragma module_name = "?time"

time_t (time)(time_t *t)
{
  if (t)
  {
    *t = CurrentTime;

  }
  return CurrentTime;
}
