////////////////////////////////////////////////////////////////////////////////
//
// ANPRO10 TCP server
//
// Revision History
// -June/23/2016 - initial release by hkim
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __ANPRO_TCP_SERVER_H__
#define __ANPRO_TCP_SERVER_H__

#include "RTOS.h"
#include "app/list.h"
#include "app/sg_timer.h"

#include "TSNIncludes.h"
#include "TSNMessageQ.h"
#include "anpro_net_util.h"



#define ANPRO_TCP_SERVER_PORT           15533
#define ANPRO_NET_UDP_PORT              15534
#define ANPRO_TCP_FLASH_PROG_PORT       16000

//
// this is actually supposed to be 16K, which is ridiculously long.
// so I define a local duplicate here and set it to 1K, which is again
// ridiculously long.
// -hkim-
//
#define MAX_ANPRO10_MESSAGE_SIZE        (8096 * 2)

typedef struct
{
  struct list_head    anpro_conns;
  s32_t               listen_fd;
  s32_t               flash_fd;

  s32_t               queue_event;
  TSNMessageQ*        urgent_q;
  TSNMessageQ*        normal_q;
  u8_t                q_msg_buf[MAX_ANPRO10_MESSAGE_SIZE];
  u8_t                tx_bounce_buffer[MAX_ANPRO10_MESSAGE_SIZE];

  SGTimer             timer_mgr;
  OS_TIMER            os_timer_tick;
  s32_t               timer_tick_event;
  volatile u16_t      port_number;
  volatile u16_t      flash_port;
  volatile u8_t       initialized;

  volatile u8_t       use_udp_bcast_for_normal_msg;
  volatile u16_t      udp_port_number;
  s32_t               udp_sock;
  ANPRO10_Reader      anp10_udp_reader;
  SGTimerElem         udp_wait_timer;
  enum
  {
    ANPRO_UDP_State_OK,
    ANPRO_UDP_State_Waiting,
  } udp_state;

  //
  // debug interface
  //
  OS_EVENT        debug_req_event;
  OS_EVENT        debug_rsp_event;
  OS_RSEMA        debug_lock;
  volatile char*  msg_buf;
} ANPRO_TCP_Server;

extern void anpro_server_init(ANPRO_TCP_Server* server, u16_t port, u8_t use_udp, u16_t udp_port, u16_t flash_port);
extern s8_t anpro_server_post_message_urgent(ANPRO_TCP_Server* server, void* msg, int size);
extern s8_t anpro_server_post_message_normal(ANPRO_TCP_Server* server, void* msg, int size);
extern void initialize_anpro_tcp_servers(void);
extern u8_t is_this_port_for_anpro_tcp_server(TSNUart* port);
extern void anpro_server_debug(ANPRO_TCP_Server* server, char* msg_buf);

#endif //!__ANPRO_TCP_SERVER_H__
