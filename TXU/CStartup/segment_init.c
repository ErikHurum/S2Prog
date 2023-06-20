/**************************************************
 *
 * Segment initialization that must be
 * performed before main is called.
 *
 * Since this function is called from cstartup,
 * it is located in the same segment, ICODE.
 *
 * Copyright 1999 IAR Systems. All rights reserved.
 *
 * $Revision: 1.6 $
 *
 * $Log: segment_init.c $
 * Revision 1.6  2003/02/10 16:20:17  pny
 * Revision 1.5  2002/09/27 17:15:14  pny
 * Revision 1.4  2002/05/03 13:22:39  pny
 * Revision 1.3  1999/12/22 08:00:16  apikas
 *
 **************************************************/

#include "segment_init.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma language=extended

#pragma location="ICODE"
void __segment_init(void)
{
  extern InitBlock_Type const * const __segment_begin_INITTAB;
  InitBlock_Type const * const initTableBegin = __segment_begin_INITTAB;
  extern InitBlock_Type const * const __segment_end_INITTAB;
  InitBlock_Type const * const initTableEnd = __segment_end_INITTAB;
  InitBlock_Type const * initTableP;

  /* Loop over all elements in the initialization table. */
  
  for (initTableP=initTableBegin; initTableP<initTableEnd; initTableP++)
  {
    /* If src=dest then we should clear a memory
     * block, otherwise it's a copy operation. */
    if (initTableP->Src == initTableP->Dst)
    {
      memset(initTableP->Dst, 0, initTableP->Size);
    }
    else
    {
      memcpy(initTableP->Dst, initTableP->Src, initTableP->Size);
    }
  }
 
}

#pragma language=default

#ifdef __cplusplus
}
#endif
