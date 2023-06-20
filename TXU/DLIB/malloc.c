/* malloc function */
/* Copyright (C) 2003 IAR Systems.  All rights reserved. */
#include "xalloc.h"
#include "yfuns.h"
#include "xinstantiate.h"
_STD_BEGIN

#pragma language=extended

/* Debugging components */
#ifdef DEBUG

#define __HEAP_MEM_HELPER1__(M, I)              \
int M##_OK_Cell(M##_Cell M * p)                 \
        {                                       \
        ASSERT(SIZE_CELL(M) <= p->_Size);       \
        return 1;                               \
        }
__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__


#define __HEAP_MEM_HELPER1__(M, I)              \
typedef struct M##_DB_Altab {                   \
        M##_size_t total_heap;                  \
        M##_size_t total_alloc;                 \
        M##_size_t total_free;                  \
        } M#_DB_Altab;
__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__


#define __HEAP_MEM_HELPER1__(M, I)              \
M##_DB_Altab M##_DB_Altab_object = {0};
__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__


#define __HEAP_MEM_HELPER1__(M, I)                              \
void M##_UPD_Altab(M##_size_t d_heap, M##_size_t d_alloc,       \
                   M##_size_t d_free)                           \
        {                                                       \
        M##_DB_Altab *pd = &M##_DB_Altab_object;                \
        pd->total_heap += d_heap;                               \
        pd->total_alloc += d_alloc;                             \
        pd->total_free += d_free;                               \
        }
__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__


#define __HEAP_MEM_HELPER1__(M, I)                                      \
int M##_OK_Altab(M##_Altab M *p)                                        \
        {                                                               \
        M##_DB_Altab *pd = &M##_DB_Altab_object;                        \
        M##_Cell M *q;                                                  \
        size_t total_free = 0;                                          \
        if (p->_Head == 0)                                              \
                return 1;                                               \
        for (q = p->_Head; q != 0; q = q->_Next)                        \
                {                                                       \
                total_free += q->_Size;                                 \
                M##_OK_Cell(q);                                         \
                if (q->_Next != 0)                                      \
                        {                                               \
                        ASSERT(_PTR_NORM((char M *)q + q->_Size) <=     \
                                _PTR_NORM((char M *)q->_Next));         \
                        ASSERT(_PTR_NORM(q) < _PTR_NORM(q->_Next));     \
                        }                                               \
                }                                                       \
        ASSERT(pd->total_heap == pd->total_alloc + pd->total_free);     \
        ASSERT(total_free == pd->total_free);                           \
        return 1;                                                       \
        }
__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__

#endif /* DEBUG */

                /* static data */

#define __HEAP_MEM_HELPER1__(M, I)                                      \
M M##_Altab M##_Aldata = {0};   /* heap initially empty */
__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__


#define __HEAP_MEM_HELPER1__(M, I)                                      \
static M##_Cell M * M* M##_findmem(M##_size_t size)                     \
{       /* find storage */                                              \
  M##_Cell M * q;                                                       \
  M##_Cell M * M * qb;                                                  \
                                                                        \
  for (; ; )                                                            \
  {     /* check freed space first */                                   \
    if ((qb = M##_Aldata._Plast) == 0)                                  \
    {   /* take it from the top */                                      \
      for (qb = &M##_Aldata._Head; *qb != 0;                            \
           qb = &(*qb)->_Next)                                          \
        if (size <= (*qb)->_Size)                                       \
          return (qb);                                                  \
    }                                                                   \
    else                                                                \
    {   /* resume where we left off */                                  \
      for (; *qb != 0; qb = &(*qb)->_Next)                              \
        if (size <= (*qb)->_Size)                                       \
          return (qb);                                                  \
      q = *M##_Aldata._Plast;                                           \
      for (qb = &M##_Aldata._Head; *qb != q;                            \
           qb = &(*qb)->_Next)                                          \
        if (size <= (*qb)->_Size)                                       \
          return (qb);                                                  \
    }                                                                   \
    {   /* try to buy more space */                                     \
      /* IAR has changed this to allow for multiple areas of            \
         heap memory. */                                                \
      if ((q = (M##_Cell M *)M##_GetMemChunk()) == 0)                   \
        return 0;       /* no storage */                                \
                                                                        \
      /* got storage: add to heap and retry */                          \
      _UPD_ALTAB(M, q->_Size, q->_Size, 0); /* heap=alloc+free */       \
      M##_free((char M *)q + CELL_OFF(M));                              \
    }                                                                   \
  }                                                                     \
}
__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__



#define __HEAP_MEM_HELPER1__(M, I)                                      \
void M *(M##_malloc)(M##_size_t size_arg)                               \
{       /* allocate a data object on the heap */                        \
  if (_HEAP_REDIRECT(I))                                                \
  {                                                                     \
    /* Redirect to another heap */                                      \
    _GLUE(_HEAP_REDIRECT_TO(I),_size_t) size_arg2 = size_arg;           \
    if (size_arg2 != size_arg)                                          \
      return 0;                                                         \
    return _GLUE(_HEAP_REDIRECT_TO(I),_malloc)(size_arg2);              \
  }                                                                     \
  else                                                                  \
  {                                                                     \
    M##_Cell M * q;                                                     \
    M##_Cell M * M * qb;                                                \
    size_t size = (size_arg + (CELL_OFF(M) + M_MASK)) & ~M_MASK;        \
                                                                        \
    _Locksyslock(_LOCK_MALLOC);                                         \
    _OK_ALTAB(M, &M##_Aldata);                                          \
    if (size <= size_arg)                                               \
    {   /* size_arg too large */                                        \
      _Unlocksyslock(_LOCK_MALLOC);                                     \
      return (0);                                                       \
    }                                                                   \
    if (size < SIZE_CELL(M)) /* round up size */                        \
      size = SIZE_CELL(M);                                              \
    if ((qb = M##_findmem(size)) == 0)                                  \
    {   /* no memory to be found */                                     \
      _Unlocksyslock(_LOCK_MALLOC);                                     \
      return (0);                                                       \
    }                                                                   \
    q = *qb;                                                            \
    if (q->_Size - SIZE_CELL(M) < size)                                 \
      *qb = q->_Next;   /* use entire cell */                           \
    else                                                                \
    {   /* peel off a residual cell */                                  \
      *qb = (M##_Cell M *)((char M *)q + size);                         \
      (*qb)->_Next = q->_Next;                                          \
      (*qb)->_Size = q->_Size - size;                                   \
      q->_Size = size;                                                  \
    }                                                                   \
    M##_Aldata._Plast = *qb && (*qb)->_Next ? &(*qb)->_Next : 0;        \
    _UPD_ALTAB(M, 0, q->_Size, -q->_Size); /* heap=alloc+free */        \
    _OK_ALTAB(M, &M##_Aldata);                                          \
    _Unlocksyslock(_LOCK_MALLOC);                                       \
    return ((char M *)q + CELL_OFF(M));                                 \
  }                                                                     \
}
__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__


_INSTANTIATE(malloc);

_STD_END

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
