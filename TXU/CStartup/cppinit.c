/*
 *     cppinit.c - The IAR Systems C++ runtime library.
 *
 *     This file contains the dynamic initialization of C++ objects.
 *
 *     Created 1998-09-07 IASL
 *
 *     $Id: cppinit.c 1.9 2003/10/10 12:26:58Z grzm Review $
 */


#include <stdlib.h>
#include <string.h>

#include "dtor_rec.h"

#ifdef __cplusplus
#error This file should be compiled in C mode
#endif

#pragma language = extended

/* Define _DIFUNCT_MEMORY if the DIFUNCT segment is not located in
   default memory. */
#ifdef _DIFUNCT_MEMORY
typedef __func_ptr _DIFUNCT_MEMORY * difunct_ptr;
#else /* !_DIFUNCT_MEMORY */
typedef __func_ptr * difunct_ptr;
#endif /* _DIFUNCT_MEMORY */

/*
 *  Function: __call_ctors
 *
 *  Description: Call each constructor for each global object defined
 *               in the application.
 *
 *               The constructors are placed in a segment named DIFUNCT.
 *               This function is assumed to be called from the cstartup
 *               assembler routine using code similar to:
 *                   MOV   SFB DIFUNCT, <first argument register>
 *                   MOV   SFE DIFUNCT, <second argument register>
 */

void __call_ctors(difunct_ptr start, difunct_ptr end_plus_one)
{
  while (start != end_plus_one)
    {
      (*start)();

      start ++;
    }
}


/*
 *  Function: __pure_virtual_called
 *
 *  Description: This function is called whenever a pure virtual function
 *               is called.
 *
 *               When called the program is aborted.
 */

void __pure_virtual_called(void)
{
  abort();
}


/*
 *  Function: __record_needed_destruction
 *
 *  Description: Called for each object that need destruction.
 */

static __dtor_rec const * dtor_head /* = NULL */;


extern void * __cstart_call_dtors;

#pragma required = __cstart_call_dtors
void __record_needed_destruction( __dtor_rec const * rec )
{
  /*
   * Check if record already is linked in the list;
   */
  if (   *rec->next != NULL
      || rec == dtor_head)
    {
      abort();
    }

  /*
   * Link in the record at the beginning of the list.
   */
  *rec->next = dtor_head;
  dtor_head = rec;
}



/*
 *  Function: __call_dtors
 *
 *  Description: Ensure that each destructor for each created object
 *               will be called.
 */

void __call_dtors()
{
  __dtor_rec const * rec;

  while (dtor_head != NULL)
    {
      /*
       * First we unlink the record from the list so that we won't
       * call it recursively by mistake.  Also it is possible for the
       * value of dtor_head to change (e.g. if a new object is
       * created in a destructor).
       */
      rec = dtor_head;
      dtor_head = *dtor_head->next;

      if (rec->object)
        {
          ((__def_dtor_ptr)rec->dtor)(rec->object);
        }
      else
        {
          (rec->dtor)();
        }
    }
}


/*
 * Function: __memzero
 *
 * Description: Clears a block of memory.
 */

#define __VAR_MEM_HELPER1__(M, I)                                             \
void M##_memzero( void M * buf, M##_size_t size)                              \
{                                                                             \
  char M * p;                                                                 \
  char M * e;                                                                 \
  for (p = buf, e = p + size; p != e; ++p)                                    \
    *p = 0;                                                                   \
}
__VAR_MEMORY_LIST1__()
#undef __VAR_MEM_HELPER1__


/*
 *  Function: __vec_cctor
 *
 *  Description: Copies an entire array using a copy constructor for each
 *  array element.
 */

#define __VAR_MEM_HELPER1__(M, I)                                             \
void M##_vec_cctor(void M * dest, M##_size_t no, M##_size_t element_size,     \
                 M##_cctor_ptr cctor, void M * src)                           \
{                                                                             \
  M##_size_t i;                                                               \
                                                                              \
  /* We must work with character pointers in order to perform                 \
   * pointer arithmetic operations on src and dest.                           \
   */                                                                         \
  char M * src_charp =  (char M *) src;                                       \
  char M * dest_charp = (char M *) dest;                                      \
                                                                              \
  if (cctor != NULL)                                                          \
    {                                                                         \
      for (i=0; i < no; i++)                                                  \
        {                                                                     \
          (*cctor)((void M *)dest_charp, (void M *)src_charp);                \
                                                                              \
          src_charp += element_size;                                          \
          dest_charp += element_size;                                         \
        }                                                                     \
    }                                                                         \
}
__VAR_MEMORY_LIST1__()
#undef __VAR_MEM_HELPER1__
