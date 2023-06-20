#ifndef __EVENTS_DEF_H__
#define __EVENTS_DEF_H__

#define EVENTS_FLAG_1MS_TIMER     0

#define EVENTS_FLAG_UART0_RX      1
#define EVENTS_FLAG_UART1_RX      2

#define EVENTS_FLAG_UART0_TXC     3
#define EVENTS_FLAG_UART1_TXC     4

#define EVENTS_FLAG_UART0_T35     5
#define EVENTS_FLAG_UART1_T35     6

#define EVENTS_FLAG_RESET         7

#define EVENTS_NUM_EVENTS         (EVENTS_FLAG_RESET + 1)

typedef void (*evt_handler_t)(unsigned char evt);

extern void init_loop_events(void);
extern void set_event(unsigned char evt);
extern void register_event_handler(unsigned char evt, evt_handler_t handler);
extern void run_event_dispatcher(void);

#endif /* !__EVENTS_DEF_H__ */


