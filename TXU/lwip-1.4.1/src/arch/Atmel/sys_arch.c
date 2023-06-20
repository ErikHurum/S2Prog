/*****************************************************************************
*
* \file
*
* \brief lwIP system architecture layer for SAM.
*
* Copyright (c) 2012 Atmel Corporation. All rights reserved.
*
* \asf_license_start
*
* \page License
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3. The name of Atmel may not be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* 4. This software may only be redistributed and used in connection with an
*    Atmel microcontroller product.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* \asf_license_stop
*
*****************************************************************************/

#include "lwip/debug.h"
#include "lwip/sys.h"
#include "lwip/opt.h"
#include "lwip/stats.h"

#define SYS_ARCH_BLOCKING_TICKTIMEOUT    ((portTickType)10000)

/* Structure associating a thread to a struct sys_timeouts */
struct TimeoutlistPerThread {
    sys_thread_t pid;        /* The thread id */
};

/* Thread & struct sys_timeouts association statically allocated per thread.
   Note: SYS_THREAD_MAX is the max number of thread created by sys_thread_new()
   that can run simultaneously; it is defined in conf_lwip_threads.h. */
static struct TimeoutlistPerThread Threads_TimeoutsList[SYS_THREAD_MAX];

/* Number of active threads. */
static u16_t NbActiveThreads = 0;

void sys_init(void) {
    int i;

    /* Initialize the the per-thread sys_timeouts structures
       make sure there are no valid pids in the list */
    for (i = 0; i < SYS_THREAD_MAX; i++) {
        Threads_TimeoutsList[i].pid = 0;
    }

    /* Keep track of how many threads have been created */
    NbActiveThreads = 0;
}


/** Create a new semaphore
 * @param sem pointer to the semaphore to create
 * @param count initial count of the semaphore
 * @return ERR_OK if successful, another err_t otherwise */
err_t sys_sem_new(sys_sem_t *sem, u8_t count) {
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

        if (0 == count) { /* Means we want the sem to be
                             unavailable at init state. */
            OS_SignalCSema(sem, 1);
        }

        err_sem = ERR_OK;

        OS_LeaveRegion();
    }

    return err_sem;
}

void sys_sem_free(sys_sem_t *sem) {
    /* Sanity check */
    if (sem != NULL) {
        if (SYS_SEM_NULL != *sem) {
#ifdef SYS_STATS
            lwip_stats.sys.sem.used--;
#endif /* SYS_STATS */
            vQueueDelete(*sem);
        }
    }
}

void sys_sem_signal(sys_sem_t *sem) {
    /* Sanity check */
    if (sem != NULL) {
        xSemaphoreGive(*sem);
    }
}

u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout) {
    portTickType TickStart;
    portTickType TickStop;
    /* Express the timeout in OS tick. */
    portTickType TickElapsed = (portTickType)(timeout / portTICK_RATE_MS);

    /* Sanity check */
    if (sem != NULL) {
        if (timeout && !TickElapsed) {
            TickElapsed = 1; /* Wait at least one tick */
        }

        if (0 == TickElapsed) {
            TickStart = xTaskGetTickCount();
            /* If timeout=0, then the function should block indefinitely */
            while (pdFALSE == xSemaphoreTake(*sem, SYS_ARCH_BLOCKING_TICKTIMEOUT)) {}
        } else {
            TickStart = xTaskGetTickCount();
            if (pdFALSE == xSemaphoreTake(*sem, TickElapsed)) {
                /* if the function times out, it should return SYS_ARCH_TIMEOUT */
                return (SYS_ARCH_TIMEOUT);
            }
        }

        /* If the function acquires the semaphore, it should return how
          many milliseconds expired while waiting for the semaphore */
        TickStop = xTaskGetTickCount();
        /* Take care of wrap-around */
        if (TickStop >= TickStart) {
            TickElapsed = TickStop - TickStart;
        } else {
            TickElapsed = portMAX_DELAY - TickStart + TickStop;
        }

        return (TickElapsed * portTICK_RATE_MS);
    } else {
        return ERR_MEM;
    }
}

#ifndef sys_sem_valid

int sys_sem_valid(sys_sem_t *sem) {
    return ((int)(*sem));
}

#endif

#ifndef sys_sem_set_invalid

void sys_sem_set_invalid(sys_sem_t *sem) {
    *sem = NULL;
}
#endif

err_t sys_mbox_new(sys_mbox_t *mBoxNew, int size) {
    err_t err_mbox = ERR_MEM;

    /* Sanity check */
    if (mBoxNew != NULL) {
        *mBoxNew = xQueueCreate(size, sizeof(void *));
#if SYS_STATS
        if (SYS_MBOX_NULL != *mBoxNew) {
            lwip_stats.sys.mbox.used++;
            if (lwip_stats.sys.mbox.used > lwip_stats.sys.mbox.max) {
                lwip_stats.sys.mbox.max = lwip_stats.sys.mbox.used;
            }
        }

#endif /* SYS_STATS */
        err_mbox = ERR_OK;
    }

    return (err_mbox);
}

void sys_mbox_free(sys_mbox_t *mbox) {
    /* Sanity check */
    if (mbox != NULL) {
        if (SYS_MBOX_NULL != *mbox) {
#ifdef SYS_STATS
            lwip_stats.sys.mbox.used--;
#endif /* SYS_STATS */
            vQueueDelete(*mbox);
        }
    }
}

void sys_mbox_post(sys_mbox_t *mbox, void *msg) {
    /* Sanit check */
    if (mbox != NULL) {
        while (pdTRUE != xQueueSend(*mbox, &msg, SYS_ARCH_BLOCKING_TICKTIMEOUT)) {}
    }
}

err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg) {
    err_t err_mbox = ERR_MEM;

    /* Sanity check */
    if (mbox != NULL) {
        if (errQUEUE_FULL != xQueueSend(*mbox, &msg, 0)) {
            err_mbox = ERR_OK;
        }
    }

    return (err_mbox);
}

u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout) {
    portTickType TickStart;
    portTickType TickStop;
    void *tempoptr;
    /* Express the timeout in OS tick. */
    portTickType TickElapsed = (portTickType)(timeout / portTICK_RATE_MS);

    /* Sanity check */
    if (mbox != NULL) {
        if (timeout && !TickElapsed) {
            TickElapsed = 1; /* Wait at least one tick */
        }

        if (msg == NULL) {
            msg = &tempoptr;
        }

        /* NOTE: INCLUDE_xTaskGetSchedulerState must be set to 1 in
         * FreeRTOSConfig.h for xTaskGetTickCount() to be available */
        if (0 == TickElapsed) {
            TickStart = xTaskGetTickCount();
            /* If "timeout" is 0, the thread should be blocked until
             * a message arrives */
            while (pdFALSE == xQueueReceive(*mbox, &(*msg),
                                            SYS_ARCH_BLOCKING_TICKTIMEOUT)) {}
        } else {
            TickStart = xTaskGetTickCount();
            if (pdFALSE == xQueueReceive(*mbox, &(*msg), TickElapsed)) {
                *msg = NULL;
                /* if the function times out, it should return
                 * SYS_ARCH_TIMEOUT. */
                return (SYS_ARCH_TIMEOUT);
            }
        }

        /* If the function gets a msg, it should return the number of ms
         * spent waiting. */
        TickStop = xTaskGetTickCount();
        /* Take care of wrap-around. */
        if (TickStop >= TickStart) {
            TickElapsed = TickStop - TickStart;
        } else {
            TickElapsed = portMAX_DELAY - TickStart + TickStop;
        }

        return (TickElapsed * portTICK_RATE_MS);
    } else {
        return ERR_MEM;
    }
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg) {
    void *tempoptr;

    /* Sanity check */
    if (mbox != NULL) {
        if (msg == NULL) {
            msg = &tempoptr;
        }

        if (pdFALSE == xQueueReceive(*mbox, &(*msg), 0)) {
            /* if a message is not present in the mailbox, it
             * immediately returns with */
            /* the code SYS_MBOX_EMPTY. */
            return (SYS_MBOX_EMPTY);
        }

        /* On success 0 is returned. */
        return (0);
    } else {
        return (SYS_MBOX_EMPTY);
    }
}

#ifndef sys_mbox_valid

int sys_mbox_valid(sys_mbox_t *mbox) {
    return ((int)(*mbox));
}
#endif

#ifndef sys_mbox_set_invalid

void sys_mbox_set_invalid(sys_mbox_t *mbox) {
    *mbox = NULL;
}

#endif

sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg,
                            int stacksize, int prio) {
    sys_thread_t newthread;
    portBASE_TYPE result;
    SYS_ARCH_DECL_PROTECT(protectionLevel);

    result = xTaskCreate(thread, (signed portCHAR *)name, stacksize, arg,
                         prio, &newthread);

    /* Need to protect this -- preemption here could be a problem! */
    SYS_ARCH_PROTECT(protectionLevel);
    if (pdPASS == result) {
        /* For each task created, store the task handle (pid) in the
         * timers array. */
        /* This scheme doesn't allow for threads to be deleted */
        Threads_TimeoutsList[NbActiveThreads++].pid = newthread;
    } else {
        newthread = NULL;
    }

    SYS_ARCH_UNPROTECT(protectionLevel);

    return (newthread);
}

/* Mutex functions: */

#if !LWIP_COMPAT_MUTEX

err_t sys_mutex_new(sys_mutex_t *mutex) {
}

void sys_mutex_lock(sys_mutex_t *mutex) {
}

void sys_mutex_unlock(sys_mutex_t *mutex) {
}

void sys_mutex_free(sys_mutex_t *mutex) {
}

#ifndef sys_mutex_valid

int sys_mutex_valid(sys_mutex_t *mutex) {
    return ((int)(*mutex));
}

#endif

#ifndef sys_mutex_set_invalid

void sys_mutex_set_invalid(sys_mutex_t *mutex) {
    *mutex = NULL;
}

#endif
#endif

/* This optional function does a "fast" critical region protection and returns
 * the previous protection level. This function is only called during very short
 * critical regions. An embedded system which supports ISR-based drivers might
 * want to implement this function by disabling interrupts. Task-based systems
 * might want to implement this by using a mutex or disabling tasking. This
 * function should support recursive calls from the same task or interrupt. In
 * other words, sys_arch_protect() could be called while already protected. In
 * that case the return value indicates that it is already protected.*/
extern volatile unsigned portLONG ulCriticalNesting;
sys_prot_t sys_arch_protect(void) {
    vPortEnterCritical();
    return 1; /* Not used */
}

void sys_arch_unprotect(sys_prot_t pval) {
    vPortExitCritical();
}
