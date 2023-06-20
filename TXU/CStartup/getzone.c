/*******************
 *
 * Copyright 2003 IAR Systems.  All rights reserved.
 *
 * $Revision: 1.1 $
 *
 * This is the default implementation of the __getzone that returns
 * the current time-zone.
 *
 * The default implementation specifies that the time-zone is UTC.
 *
 * The return value should be a string on the following form:
 *
 * :[XXX[:YYY:[NNN]]]
 *
 * Where XXX is the standard time-zone name, YYY is the daylight
 * savings time-zone name, and NNN is the time zone offset.  The
 * offset is specified as a number, possibly negative (east is
 * positive), on the format HHMM, where HH is hours and MM is minutes.
 *
 ********************/

#include <yfuns.h>

_STD_BEGIN

char const * __getzone()
{
  return ":60";
}


_STD_END
