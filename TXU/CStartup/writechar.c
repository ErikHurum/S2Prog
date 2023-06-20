/*******************
 *
 * Copyright 1999 IAR Systems.  All rights reserved.
 *
 * $Revision: 1.3 $
 *
 * This is the default implementation of the __writechar function used
 * by the standard library.  This implementation sends characters
 * written to the file descriptors associated with stdout and stderr
 * to the debugger.  Replace one of __write and __writechar with a
 * system-specific implementation.
 *
 ********************/

#include <stdio.h>
#include <yfuns.h>

_STD_BEGIN

int __writechar(int Handle, unsigned char c)
{
  if (Handle == 1 || Handle == 2)
    return __putchar(c);
  else
    return -1;
}

_STD_END
