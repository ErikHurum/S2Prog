/*
*********************************************************************************************************
*                                              lwIP TCP/IP Stack
*                                        port for uC/OS-II RTOS on TIC6711 DSK
*
* File : sys_arch.c
* By   : ZengMing @ DEP,Tsinghua University,Beijing,China
* Reference: YangYe's source code for SkyEye project
*********************************************************************************************************
*/

//#include "lwip/debug.h"
#include <stdlib.h>
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/stats.h"

#include "arch/sys_arch.h"
#include "rtos.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Create a new mutex
 * @param mutex pointer to the mutex to create
 * @return a new mutex */
err_t
sys_mutex_new(sys_mutex_t *mutex)
{
  OS_CREATERSEMA(mutex);
  return ERR_OK;
}

/** Lock a mutex
 * @param mutex the mutex to lock */
void
sys_mutex_lock(sys_mutex_t *mutex)
{
  OS_Use(mutex);
}

/** Unlock a mutex
 * @param mutex the mutex to unlock */
void
sys_mutex_unlock(sys_mutex_t *mutex)
{
  OS_Unuse(mutex);
}

/** Delete a semaphore
 * @param mutex the mutex to delete */
void
sys_mutex_free(sys_mutex_t *mutex)
{
  OS_DeleteRSema(mutex);
}


/* Semaphore functions: */

/** Create a new semaphore
 * @param sem pointer to the semaphore to create
 * @param count initial count of the semaphore
 * @return ERR_OK if successful, another err_t otherwise */
err_t
sys_sem_new(sys_sem_t *sem, u8_t count)
{
  err_t err_sem = ERR_MEM;

  /* Sanity check */
  if (sem != NULL) {

    OS_EnterRegion();
    OS_CreateCSema(sem, count);

#if SYS_STATS
    lwip_stats.sys.sem.used++;
    if (lwip_stats.sys.sem.used > lwip_stats.sys.sem.max) {
      lwip_stats.sys.sem.max = lwip_stats.sys.sem.used;
    }

#endif /* SYS_STATS */

#if 0
    if (0 == count) { /* Means we want the sem to be
                         unavailable at init state. */
      OS_SignalCSema(sem);

    }
#endif

    err_sem = ERR_OK;

    OS_LeaveRegion();
  }

  return err_sem;
}

/** Signals a semaphore
 * @param sem the semaphore to signal */
void
sys_sem_signal(sys_sem_t *sem)
{
  OS_SignalCSema(sem);
}

/** Wait for a semaphore for the specified timeout
 * @param sem the semaphore to wait for
 * @param timeout timeout in milliseconds to wait (0 = wait forever)
 * @return time (in milliseconds) waited for the semaphore
 *         or SYS_ARCH_TIMEOUT on timeout */
u32_t
sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
  if ( timeout )
  {
    OS_I32 Wtime = OS_Time;
    if ( OS_WaitCSemaTimed(sem,timeout) )
    {
      return OS_Time - Wtime;
    }
    else
    {
      return SYS_ARCH_TIMEOUT;
    }
  }
  else
  {
    OS_WaitCSema(sem);
    return ERR_OK;
  }
}


/** Delete a semaphore
 * @param sem semaphore to delete */
void
sys_sem_free(sys_sem_t *sem)
{
  /* Sanity check */
  if (sem != NULL)
  {
    OS_DeleteCSema(sem);
  }
}

/** Check if a sempahore is valid/allocated: return 1 for valid, 0 for invalid */
int
sys_sem_valid(sys_sem_t *sem)
{
  int isValid = 0;

  if (sem)
  {
    isValid = 1;
  }
  return isValid;
}

/** Set a semaphore invalid so that sys_sem_valid returns 0 */
void
sys_sem_set_invalid(sys_sem_t *sem)
{
  if (sem)
  {
    //OS_DeleteCSema(sem);
    //sem->WaitObj = NULL;
  }
}


/* Time functions. */
void
sys_msleep(u32_t ms) /* only has a (close to) 1 jiffy resolution. */
{
  OS_Delay(ms);
}


/* Mailbox functions. */

/** Create a new mbox of specified size
 * @param mbox pointer to the mbox to create
 * @param size (miminum) number of messages in this mbox
 * @return ERR_OK if successful, another err_t otherwise */
err_t
sys_mbox_new(sys_mbox_t *mbox, int size)
{
  unsigned *Ptr = malloc(size*sizeof(void *));

  OS_CREATEMB(mbox,sizeof(void *),size,Ptr);
  return ERR_OK;
}

/** Post a message to an mbox - may not fail
 * -> blocks if full, only used from tasks not from ISR
 * @param mbox mbox to posts the message
 * @param msg message to post (ATTENTION: can be NULL) */
void
sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
  OS_PutMail(mbox,&msg);
}

/** Try to post a message to an mbox - may fail if full or ISR
 * @param mbox mbox to posts the message
 * @param msg message to post (ATTENTION: can be NULL) */
err_t
sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
  char HasSendt;

  HasSendt = OS_PutMailCond(mbox,&msg);

  if (HasSendt == 0)
  { 
    return ERR_OK;
  }
  else
  {
    return ERR_INPROGRESS;
  }
}

/** Wait for a new message to arrive in the mbox
 * @param mbox mbox to get a message from
 * @param msg pointer where the message is storeuuuud
 * @param timeout maximum time (in milliseconds) to wait for a message
 * @return time (in milliseconds) waited for a message, may be 0 if not waited
           or SYS_ARCH_TIMEOUT on timeout
 *         The returned time has to be accurate to prevent timer jitter! */
u32_t
sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
  OS_I32 Wtime1 = OS_Time;
  u32_t tmpMsg;
  void* dummyptr;

  if(msg == NULL)
  {
    msg = &dummyptr;
  }

  if(timeout == 0)
  {
    // block forever
    OS_GetMail(mbox,&tmpMsg);
    *msg = (void*)tmpMsg;
    OS_I32 Wtime2 = OS_Time - Wtime1;
    return Wtime2;
  }
  else
  {
    if(!OS_GetMailTimed(mbox,&tmpMsg,timeout))
    {
      *msg = (void*)tmpMsg;
      OS_I32 Wtime2 = OS_Time - Wtime1;
      return Wtime2;
    }
    else
    {
      return SYS_ARCH_TIMEOUT;
    }
  }
}

/* Allow port to override with a macro, e.g. special timout for sys_arch_mbox_fetch() */
#ifndef sys_arch_mbox_tryfetch
/** Wait for a new message to arrive in the mbox
 * @param mbox mbox to get a message from
 * @param msg pointer where the message is stored
 * @param timeout maximum time (in milliseconds) to wait for a message
 * @return 0 (milliseconds) if a message has been received
 *         or SYS_MBOX_EMPTY if the mailbox is empty */
u32_t
sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
  u32_t tmpMsg;
  void* dummyptr;

  if(msg == NULL)
  {
    msg = &dummyptr;
  }

  if(OS_GetMailCond(mbox,&tmpMsg) == 0)
  {
    *msg = (void*)tmpMsg;
    return ERR_OK;
  }
  else
  {
    return SYS_MBOX_EMPTY;
  }
}

#endif

/** For now, we map straight to sys_arch implementation. */
#define sys_mbox_tryfetch(mbox, msg) sys_arch_mbox_tryfetch(mbox, msg)
/** Delete an mbox
 * @param mbox mbox to delete */
void
sys_mbox_free(sys_mbox_t *mbox)
{
  char *DataPtr = mbox->pData;

  if (DataPtr )
  {
    free(DataPtr);
    OS_DeleteMB(mbox);
    mbox->sizeofMsg = 0;
    mbox->pData     = NULL;
  }
}
#define sys_mbox_fetch(mbox, msg) sys_arch_mbox_fetch(mbox, msg, 0)

/** Check if an mbox is valid/allocated: return 1 for valid, 0 for invalid */
int
sys_mbox_valid(sys_mbox_t *mbox)
{
  if (mbox->sizeofMsg)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/** Set an mbox invalid so that sys_mbox_valid returns 0 */
void
sys_mbox_set_invalid(sys_mbox_t *mbox)
{
  char *DataPtr = mbox->pData;

  if (DataPtr )
  {
    /* bullshit, -hkim-
    free(DataPtr);
    OS_DeleteMB(mbox);
    mbox->sizeofMsg = 0;
    mbox->pData     = NULL;
    */
  }
}

/** The only thread function:
 * Creates a new thread
 * @param name human-readable name for the thread (used for debugging purposes)
 * @param thread thread-function
 * @param arg parameter passed to 'thread'
 * @param stacksize stack size in bytes for the new thread (may be ignored by ports)
 * @param prio priority of the new thread (may be ignored by ports) */
static int TaskCnt = 0;
static OS_TASK TaskList[LWIP_TASK_MAX];
static OS_STACKPTR char NetworkStack[LWIP_TASK_MAX][LWIP_STK_SIZE];

sys_thread_t
sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
  OS_TASK *pTask = NULL;
  
  OS_IncDI();
  if (TaskCnt >= LWIP_TASK_MAX)
  {
    static OS_TASK DummyTask;
    pTask = &DummyTask;
  }
  else
  {
    pTask = &TaskList[TaskCnt];
    OS_STACKPTR char *StackPtr = NetworkStack[TaskCnt++];
    OS_CreateTaskEx(pTask,(const char*)name,(unsigned char)prio,thread,StackPtr,LWIP_STK_SIZE,2,arg);
  }
  OS_DecRI();
  return *pTask;
}

/* sys_init() must be called before anthing else. */
void
sys_init(void)
{
}

#ifndef sys_jiffies
/** Ticks/jiffies since power up. */
u32_t
sys_jiffies(void)
{
  return OS_Time;
}
#endif

/** Returns the current time in milliseconds,
 * may be the same as sys_jiffies or at least based on it. */
u32_t
sys_now(void)
{
  return OS_Time;
}

sys_prot_t
sys_arch_protect(void)
{
  OS_EnterRegion();
  return 1;
}

/**
 * Leaves a critical section.
 *
 * @param the preivous protection level
 */
void
sys_arch_unprotect(sys_prot_t val)
{
  (void)val;
  OS_LeaveRegion();
}

#ifdef __cplusplus
}
#endif
