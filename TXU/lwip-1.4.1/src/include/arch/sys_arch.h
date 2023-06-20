/*
*********************************************************************************************************
*                                              lwIP TCP/IP Stack
*                                        port for uC/OS-II RTOS on TIC6711 DSK
*
* File : sys_arch.h
* By   : ZengMing @ DEP,Tsinghua University,Beijing,China
* Reference: YangYe's source code for SkyEye project
*********************************************************************************************************
*/
#ifndef __SYS_ARCH_H__
#define __SYS_ARCH_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "rtos.h"

#define LWIP_STK_SIZE      8192

#define LWIP_TASK_MAX    5  //max number of lwip tasks
#define LWIP_START_PRIO  5   //first prio of lwip tasks
    //!!!! so priority of lwip tasks is from 5-9

#define SYS_MBOX_NULL   (void*)0
#define SYS_SEM_NULL    (void*)0

#define MAX_QUEUES        20
#define MAX_QUEUE_ENTRIES 20

typedef struct {
    OS_EVENT*   pQ;
    void*       pvQEntries[MAX_QUEUE_ENTRIES];
} TQ_DESCR, *PQ_DESCR;

typedef OS_CSEMA   sys_sem_t;
typedef OS_MAILBOX sys_mbox_t;//the structure defined above
typedef OS_TASK    sys_thread_t;
typedef OS_RSEMA   sys_mutex_t;

err_t sys_mutex_new(sys_mutex_t *mutex);
void sys_mutex_lock(sys_mutex_t *mutex);
void sys_mutex_unlock(sys_mutex_t *mutex);
void sys_mutex_free(sys_mutex_t *mutex);
void sys_mutex_set_invalid(sys_mutex_t *mutex);


/* Semaphore functions: */
err_t sys_sem_new(sys_sem_t *sem, u8_t count);
void sys_sem_signal(sys_sem_t *sem);
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout);
void sys_sem_free(sys_sem_t *sem);


/* Time functions. */
#define sys_msleepFunc
void sys_msleep(u32_t ms); /* only has a (close to) 1 jiffy resolution. */

/* Mailbox functions. */

err_t sys_mbox_new(sys_mbox_t *mbox, int size);
void sys_mbox_post(sys_mbox_t *mbox, void *msg);
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg);
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout);
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg);
void sys_mbox_free(sys_mbox_t *mbox);

#if 0
/* Critical Region Protection */
/* These functions must be implemented in the sys_arch.c file.
   In some implementations they can provide a more light-weight protection
   mechanism than using semaphores. Otherwise semaphores can be used for
   implementation */
/** SYS_ARCH_DECL_PROTECT
 * declare a protection variable. This macro will default to defining a variable of
 * type sys_prot_t. If a particular port needs a different implementation, then
 * this macro may be defined in sys_arch.h.
 */
#define SYS_ARCH_DECL_PROTECT(lev)
/** SYS_ARCH_PROTECT
 * Perform a "fast" protect. This could be implemented by
 * disabling interrupts for an embedded system or by using a semaphore or
 * mutex. The implementation should allow calling SYS_ARCH_PROTECT when
 * already protected. The old protection level is returned in the variable
 * "lev". This macro will default to calling the sys_arch_protect() function
 * which should be implemented in sys_arch.c. If a particular port needs a
 * different implementation, then this macro may be defined in sys_arch.h
 */
#define SYS_ARCH_PROTECT(lev) OS_EnterRegion()
/** SYS_ARCH_UNPROTECT
 * Perform a "fast" set of the protection level to "lev". This could be
 * implemented by setting the interrupt level to "lev" within the MACRO or by
 * using a semaphore or mutex.  This macro will default to calling the
 * sys_arch_unprotect() function which should be implemented in
 * sys_arch.c. If a particular port needs a different implementation, then
 * this macro may be defined in sys_arch.h
 */
#define SYS_ARCH_UNPROTECT(lev) OS_LeaveRegion()
#endif

#ifdef __cplusplus
}
#endif
#endif
