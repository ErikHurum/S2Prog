/**************************************************
 *
 * Declarations for segment initialization.
 *
 * Copyright 1999 IAR Systems. All rights reserved.
 *
 * $Revision: 1.1 $
 *
 * $Log: segment_init.h $
 * Revision 1.1  1999/10/28 16:46:51  apikas
 * Initial revision
 *
 **************************************************/

#ifndef __SEGMENT_INIT_H_INCLUDED
#define __SEGMENT_INIT_H_INCLUDED

/* Structure of an element in the segment initialization table
 * in segment INITTAB. Used for both zero-initialization and copying. */
typedef struct
{
  long   Size;                  /* Number of bytes to initialize */
  char*  Dst;                   /* Destination. If Dst==Src, then init to 0 */
  char*  Src;                   /* Source address. Usually in ROM. */
} InitBlock_Type;


#endif /* __SEGMENT_INIT_H_INCLUDED */
