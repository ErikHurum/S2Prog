/*******************
 *
 * Copyright 1998 IAR Systems. All rights reserved.
 *
 * $Revision: 1.5 $
 *
 * $Log: dtor_rec.h $
 * Revision 1.5  2003/10/10 12:26:58Z  grzm
 * Handle vector construction/destruction in different memories.
 * Revision 1.4  2002/03/15 13:28:33Z  Grzm
 * SCR11675: Avoid calling destructors with an extra parameter.
 * Revision 1.3  1998/10/28 14:23:47  Grzm
 * Use double indirection for next field in __dtor_rec.
 * Revision 1.2  1998/09/28 12:21:29  AndersL
 *
 ********************/


#ifndef _DTOR_REC_H
#define _DTOR_REC_H

#ifndef FUNCATTR
#define FUNCATTR
#endif


typedef FUNCATTR void (* __func_ptr) (void);
typedef FUNCATTR void (* __def_dtor_ptr) (void *);

#pragma language = extended

#define __VAR_MEM_HELPER1__(M, I)                                             \
typedef FUNCATTR void (* M##_dtor_ptr) (void M *);                            \
typedef FUNCATTR void (* M##_ctor_ptr) (void M *);                            \
typedef FUNCATTR void (* M##_cctor_ptr)(void M *, void M *);
__VAR_MEMORY_LIST1__()
#undef __VAR_MEM_HELPER1__

#pragma language = default


typedef struct __dtor_rec __dtor_rec;
struct __dtor_rec {
  __dtor_rec const * * next;
  void *               object;
  __func_ptr           dtor;
};


_EXTERN_C
void __record_needed_destruction( __dtor_rec const * );
_END_EXTERN_C


#endif /*_DTOR_REC_H */
