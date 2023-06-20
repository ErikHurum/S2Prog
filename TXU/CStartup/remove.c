/*******************
 *
 * Copyright 1998-2003 IAR Systems. All rights reserved.
 *
 * $Revision: 1.5 $
 *
 * This is a template implementation of the "remove" function of the
 * standard library.  Replace it with a system-specific
 * implementation.
 *
 * The "remove" function should remove the file named "filename".  It
 * should return 0 on success and nonzero on failure.
 *
 ********************/

#include <stdio.h>

_STD_BEGIN

#pragma module_name = "?remove"

int remove(const char * filename)
{
  return 0;
}

_STD_END
