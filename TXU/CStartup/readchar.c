/*******************
 *
 * Copyright 1999 IAR Systems.  All rights reserved.
 *
 * $Revision: 1.3 $
 *
 * This is the default implementation of the __readchar function used
 * by the standard library.  This implementation reads characters from
 * the file descriptors associated with stdin from the debugger.
 * Replace one of __read and __readchar with a system-specific
 * implementation.
 *
 ********************/

#include <stdio.h>
#include <yfuns.h>

_STD_BEGIN

int __readchar(int Handle)
{
  if (Handle == 0)
    return __getchar();
  else
    return -1;
}

_STD_END
