////////////////////////////////////////////////////////////////////////////////
//
// an old invention of hkim and open nature of the internet
//
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include "sg_timer.h"

/**
 * initialize a timer manager
 *
 * @param timer timer manager context block
 * @param tick_rate desired tick rate
 * @param n_buckets number of buckets desired
 * @return 0 on success, -1 on failure
 */
int
init_timer(SGTimer* timer, int tick_rate, int n_buckets)
{  
   int i;

   timer->num_buckets         = n_buckets;
   timer->tick_rate           = tick_rate;
   timer->tick                = 0;

   timer->buckets = (struct list_head*)malloc(sizeof(struct list_head) * timer->num_buckets);
   if(timer->buckets == NULL)
   {
      return -1;
   }

   for(i = 0; i < timer->num_buckets; i++)
   {
      INIT_LIST_HEAD(&timer->buckets[i]);
   }

   return 0; 
}  

/**
 * deinitialize a timer manager
 *
 * @param timer timer context block
 */
void
deinit_timer(SGTimer* timer)
{
   free(timer->buckets);
}

/**
 * initialize a timer element before using it
 *
 * @param elem timer element to initialize
 */
void
init_timer_elem(SGTimerElem* elem)
{
   INIT_LIST_HEAD(&elem->next);
}

/**
 * start a stopped timer element by adding it to timer manager
 *
 * @param timer timer manager context block
 * @param elem new timer element to add to timer manager
 * @param expires desired timeout value in milliseconds
 */
void
add_timer(SGTimer* timer, SGTimerElem* elem, int expires)
{
   int target;

   if(is_timer_running(elem))
   {
      char* crash = NULL;
      *crash = 0;
   }

   INIT_LIST_HEAD(&elem->next);

   elem->tick     = timer->tick + get_tick_from_milsec(timer, expires);
   target         = elem->tick % timer->num_buckets;

   list_add_tail(&elem->next, &timer->buckets[target]);
}

/**
 * stop a running timer element by deleting it from timer manager
 *
 * @param timer tmier manager context block
 * @param elem timer elemen to delete
 */
void
del_timer(SGTimer* timer, SGTimerElem* elem)
{
   if(!is_timer_running(elem))
   {
      return;
   }
   list_del_init(&elem->next);
}

static void
timer_tick(SGTimer* timer)
{
   int               current;
   SGTimerElem       *p, *n;
   struct list_head  timeout_list = LIST_HEAD_INIT(timeout_list);

   timer->tick++;

   current = timer->tick % timer->num_buckets;

   //
   // be careful with this code..
   // Here is the logic behind this
   // 1. once timer expires, it should be able to re-add the same timer again
   // 2. when a timer expires, it should be able to remove
   //    other timers including ones timed out inside the timeout handler
   //
   list_for_each_entry_safe(p, n, &timer->buckets[current], next, SGTimerElem)
   {
      if(p->tick == timer->tick)
      {
         list_del(&p->next);
         list_add_tail(&p->next, &timeout_list);
      }
   }

   while(!list_empty(&timeout_list))
   {
      p = list_first_entry(&timeout_list, SGTimerElem, next);
      list_del_init(&p->next);
      p->cb(p);
   }
}

/**
 * drive a given timer manager
 * this routine should be called every tick rate as close as possible
 * On non-realtime systems,  some late timeout is just inevitable
 *
 * @param timer timer manager context block
 */
void
drive_timer(SGTimer* timer)
{
   timer_tick(timer);
}
