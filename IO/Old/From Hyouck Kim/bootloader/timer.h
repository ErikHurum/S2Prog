#ifndef __TIMER_DEF_H__
#define __TIMER_DEF_H__

#define NUM_TIMERS_SUPPORTED      3

typedef enum
{
  timer_num_0 = 0,
  timer_num_1,
  timer_num_2,
} timer_num_t;

extern unsigned long _tick;

extern void timer_init(void);
extern void start_timer(timer_num_t num, unsigned char ms, unsigned char evt);
extern void stop_timer(timer_num_t num);

#endif /* !__TIMER_DEF_H__ */
