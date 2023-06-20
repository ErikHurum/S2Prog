////////////////////////////////////////////////////////////////////////////////
//
// single threaded timer
// freeing you from all the hassels of dealing with concurrency
//
// revision history
// - released too a long time ago to remember by hkim.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __SG_TIMER_H__
#define __SG_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "app/list.h"

struct _sg_timer_elem;

/**
 * timer callback function
 */
typedef void (*timer_cb)(struct _sg_timer_elem*);

/**
 * timer element representing one timer
 */
typedef struct _sg_timer_elem
{
   struct list_head  next;       /** a list head for next timer element in the bucket  */
   timer_cb          cb;         /** timeout callback                                  */
   unsigned int      tick;       /** absolute timeout tick count                       */
   void*             priv;       /** private argument for timeout callback             */
} SGTimerElem;

/**
 * a context block for timer manager
 */
typedef struct _timer
{
   int                  num_buckets;         /** number of buckets for timer management         */
   int                  tick_rate;           /** tick rate 100 means a tick per 0.1 sec         */
   unsigned int         tick;                /** current tick                                   */
   struct list_head*    buckets;             /** bucket array                                   */
} SGTimer;

extern int init_timer(SGTimer* timer, int tick_rate, int n_buckets);
extern void deinit_timer(SGTimer* timer);
extern void init_timer_elem(SGTimerElem* elem);
extern void add_timer(SGTimer* timer, SGTimerElem* elem, int expires);
extern void del_timer(SGTimer* timer, SGTimerElem* elem);
extern void drive_timer(SGTimer* timer);

/**
 * @brief check if a given timer element is currently running
 *
 * @param elem timer element to check with
 * @return 0 if timer elemnt is not running, 1 if running
 */
static inline int
is_timer_running(SGTimerElem* elem)
{
   if(elem->next.next == &elem->next && elem->next.prev == &elem->next)
   {
      return 0;
   }
   return 1;
}

/**
 * @brief calculate timer tick count from given milli second
 *
 * @param timer timer manager context block
 * @param milsec desired millisecond
 * @return the closes tick count for a given tick rate
 */
static inline unsigned int
get_tick_from_milsec(SGTimer* timer, int milsec)
{
  unsigned int   tick,
                 mod;

  tick = milsec / timer->tick_rate;
  mod  = milsec % timer->tick_rate;

  if(mod != 0)
  {
    tick += 1;
  }
  return tick;
}

#ifdef __cplusplus
}
#endif

#endif //!__SG_TIMER_H__
