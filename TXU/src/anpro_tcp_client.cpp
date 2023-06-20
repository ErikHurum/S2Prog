////////////////////////////////////////////////////////////////////////////////
//
// ANPRO10 TCP Client
//
// Revision History
// -June/27/2016 - initial release by hkim
//
////////////////////////////////////////////////////////////////////////////////
#include "lwip/opt.h"

#if LWIP_SOCKET

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "anpro_net_util.h"
#include "anpro_tcp_client.h"
#include "anpro_udp.h"

#include "lwip/mem.h"
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/api.h"
#include "lwip/stats.h"
#include "lwip/sockets.h"

#include "app/circ_buffer.h"

#include "TSNIncludes.h"

////////////////////////////////////////////////////////////////////////////////
// 
// internal typedefs for connection management
//
////////////////////////////////////////////////////////////////////////////////
#define ANPRO_CLIENT_SELECT_TIMEOUT   100000        // 100ms  change it later to infinity or something
#define ANPRO_TCP_TX_TIMEOUT          15000          // if TX window situation doesn't get batter within this,
#define ANPRO_TCP_CONNECT_TIMEOUT     4000
#define ANPRO_TCP_RECONNECT_TIMEOUT   3000

#define ANPRO_UDP_TIMEOUT             1000


typedef struct __anpro_client
{
  struct  list_head     con_list;       // list head for connection management
  s32_t                 sd;             // socket descriptor
  CircBuffer            tx_buffer;      // circular buffer for async TX
  SGTimerElem           generic_timer;  // tx timer
  ANPRO_TCP_ClientMgr*  climgr;         // tcp server this connection belongs to
  struct sockaddr_in    server_addr;
  u16_t                 station_id;     // destination station ID
  ANPRO10_Reader        anp10_reader;   // ANPRO10 RX handler
  u8_t                  tx_pending;

  enum
  {
    ANPRO_Client_Not_Connected,
    ANPRO_Client_Connecting,
    ANPRO_Client_Connected,
    ANPRO_Client_Waiting,
  } state;
} ANPRO_Client;

////////////////////////////////////////////////////////////////////////////////
// 
// module private prototypes
//
////////////////////////////////////////////////////////////////////////////////
static void anpro_init_message_q(ANPRO_TCP_ClientMgr* mgr);
static void anpro_handle_message_q(ANPRO_TCP_ClientMgr* mgr);
static void anpro_timer_tick_callback(void);
static void anpro_init_timer(ANPRO_TCP_ClientMgr* mgr);
static void anpro_tx_timer_callback(SGTimerElem* te); 
static void anpro_client_check_rxtx_set(ANPRO_Client* client, fd_set* rset, fd_set* wset);
static s32_t anpro_client_handle_rx_event(ANPRO_Client* client);
static s32_t anpro_client_handle_tx_event(ANPRO_Client* client);
static void anpro_client_reset(ANPRO_Client* client);
static void anpro_client_put_reconnect_wait(ANPRO_Client* client);

static void __on_anpro10_tx_req(ANPRO_TCP_ClientMgr* climgr, u8_t* msg, s32_t len, u8_t is_urgent_msg);
static void __on_anpro10_tx_req_normal(ANPRO_TCP_ClientMgr* climgr, u8_t* msg, s32_t len, u8_t is_urgent_msg);

static void anpro_client_reinit_udp(SGTimerElem* te);
static void anpro_client_init_udp(ANPRO_TCP_ClientMgr* mgr);
static void anpro_client_put_udp_to_wait_state(ANPRO_TCP_ClientMgr* mgr);

static void anpro_client_handle_debug(ANPRO_TCP_ClientMgr* mgr);

////////////////////////////////////////////////////////////////////////////////
// 
// module globals
//
////////////////////////////////////////////////////////////////////////////////
TSNUart   fake_uart_port_for_tcp_client = TSNUart();

////////////////////////////////////////////////////////////////////////////////
// 
// client utilities
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize EMBOS message Q and event sock for I/O multiplexing
 *
 * @param[in] mgr ANPRO_TCP_ClientMgr structure to initialize with
 *
 * @return none
 */
static void
anpro_init_message_q(ANPRO_TCP_ClientMgr* mgr)
{
  mgr->urgent_q = new TSNMessageQ();
  mgr->normal_q = new TSNMessageQ();
  mgr->queue_event    = anpro_net_create_eventfd();
}

static void
anpro_handle_message_q(ANPRO_TCP_ClientMgr* mgr)
{
  s32_t size;

  //
  // XXX : possible source of bug.
  // q_msg_buf is only 1K here.
  //
  if(mgr->urgent_q->GetMessageCond(mgr->q_msg_buf, &size) != 0)
  {
    // something to handle
    ioctlsocket(mgr->queue_event, FIONDECRECV, NULL);
    __on_anpro10_tx_req(mgr, mgr->q_msg_buf, size, 1);

    // return here so the next urgent message is handled properly
    // it's less efficient but doesn't make any noticeable difference
    return;
  }

  if(mgr->normal_q->GetMessageCond(mgr->q_msg_buf, &size) != 0)
  {
    ioctlsocket(mgr->queue_event, FIONDECRECV, NULL);
    __on_anpro10_tx_req_normal(mgr, mgr->q_msg_buf, size, 0);
  }
}

static void
anpro_client_reset(ANPRO_Client* client)
{
  close(client->sd);

  reset_circ_buffer(&client->tx_buffer);
  anpro10_reader_reset(&client->anp10_reader);

  client->tx_pending  = FALSE;
  client->state       = ANPRO_Client::ANPRO_Client_Not_Connected;
  
  client->sd =  init_anpro_client_socket();
}

static void
anpro_client_put_reconnect_wait(ANPRO_Client* client)
{
  client->state = ANPRO_Client::ANPRO_Client_Waiting;
  add_timer(&client->climgr->timer_mgr, &client->generic_timer, ANPRO_TCP_RECONNECT_TIMEOUT);
}

////////////////////////////////////////////////////////////////////////////////
// 
// timer related
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief stimulate an evnet socket to notify a TCP server that it's time to
 *        to drive a tick.
 *        This is EMBOS timer callback, thus, runs in IRQ or some other
 *        contexts other than TCP server thread.
 *        At the moment, timer resolution is 100ms.
 *
 * @return none
 */
static void
anpro_timer_tick_callback(void)
{
  OS_TIMER*             t = OS_GetpCurrentTimer();
  ANPRO_TCP_ClientMgr*  climgr = container_of(t, ANPRO_TCP_ClientMgr, os_timer_tick);

  ioctlsocket(climgr->timer_tick_event, FIONINCRECV, NULL);
  OS_RetriggerTimer(t);
}

/*
 * @brief initialize a timer manager for a client manager
 *
 * @param client manager instance to initialize timer instance with
 *
 * @return none
 */
static void
anpro_init_timer(ANPRO_TCP_ClientMgr* mgr)
{
  //
  // 100ms tick rate with 8 buckets
  // this gotta be enough for this application
  //
  init_timer(&mgr->timer_mgr, 100, 8);

  mgr->timer_tick_event  = anpro_net_create_eventfd();

  OS_CREATETIMER(&mgr->os_timer_tick, anpro_timer_tick_callback, 100);
}

////////////////////////////////////////////////////////////////////////////////
// 
// socket rx/tx 
//
////////////////////////////////////////////////////////////////////////////////
static s32_t
anpro_client_handle_rx_event(ANPRO_Client* client)
{
  u8_t    buffer[128];
  s32_t   len;

  len = read(client->sd, (s8_t*)buffer, 128);
  if(len <= 0)
  {
    anpro_client_reset(client);
    return -1;
  }

  anpro10_reader_feed(&client->anp10_reader, buffer, len);
  return 0;
}

static s32_t
anpro_client_handle_tx_event(ANPRO_Client* client)
{
  u8_t    buf[128];
  s32_t   circ_data_size,
          len,
          ret;

  del_timer(&client->climgr->timer_mgr, &client->generic_timer);
  client->tx_pending = FALSE;

  while((circ_data_size = get_circ_buffer_data_size(&client->tx_buffer)) != 0)
  {
    len = circ_data_size < 128 ? circ_data_size : 128;
    peek_circ_buffer(&client->tx_buffer, (char*)buf, len);

    ret = write(client->sd, buf, len);
    if(ret < 0)
    {
      if(!is_socket_error_would_block(client->sd))
      {
        anpro_client_reset(client);
        return -1;
      }
      
      client->tx_pending = TRUE;
      add_timer(&client->climgr->timer_mgr, &client->generic_timer, ANPRO_TCP_TX_TIMEOUT);
      return 0;
    }

    get_circ_buffer_no_copy(&client->tx_buffer, ret);
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 
// client session management
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_client_do_pre_select(ANPRO_TCP_ClientMgr* mgr, fd_set* rset, fd_set* wset, s32_t* maxfd)
{
  ANPRO_Client* client;

  if(mgr->use_udp_bcast_for_normal_msg && mgr->udp_state == ANPRO_TCP_ClientMgr::ANPRO_UDP_State_OK)
  {
    anpro_select_add_set(mgr->udp_sock, rset, maxfd);
  }

  list_for_each_entry(client, &mgr->anpro_clients, con_list, ANPRO_Client)
  {
    switch(client->state)
    {
    case ANPRO_Client::ANPRO_Client_Not_Connected:
      {
        connect(client->sd, (struct sockaddr*)&client->server_addr, sizeof(client->server_addr));

        anpro_select_add_set(client->sd, wset, maxfd);
        add_timer(&client->climgr->timer_mgr, &client->generic_timer, ANPRO_TCP_CONNECT_TIMEOUT);

        client->state = ANPRO_Client::ANPRO_Client_Connecting;
      }
      break;

    case ANPRO_Client::ANPRO_Client_Connecting:
      anpro_select_add_set(client->sd, wset, maxfd);
      break;

    case ANPRO_Client::ANPRO_Client_Connected:
      anpro_select_add_set(client->sd, rset, maxfd);
      if(client->tx_pending)
      {
        anpro_select_add_set(client->sd, wset, maxfd);
      }
      break;

    case ANPRO_Client::ANPRO_Client_Waiting:
      // nada
      break;
    }
  }
}

static void
anpro_client_check_rxtx_set(ANPRO_Client* client, fd_set* rset, fd_set* wset)
{
  switch(client->state)
  {
  case ANPRO_Client::ANPRO_Client_Not_Connected:
    // impossible to be here
    break;

  case ANPRO_Client::ANPRO_Client_Connecting:
    if(FD_ISSET(client->sd, wset))
    {
      int       err;
      socklen_t optlen = sizeof(err);

      lwip_getsockopt(client->sd, SOL_SOCKET, SO_ERROR, (void*)&err, &optlen);
      if(err == 0)
      {
        client->state = ANPRO_Client::ANPRO_Client_Connected;
        del_timer(&client->climgr->timer_mgr, &client->generic_timer);
      }
      else
      {
        anpro_client_reset(client);
        del_timer(&client->climgr->timer_mgr, &client->generic_timer);
        anpro_client_put_reconnect_wait(client);
      }
    }
    break;

  case ANPRO_Client::ANPRO_Client_Connected:
    if(FD_ISSET(client->sd, rset) && anpro_client_handle_rx_event(client) != 0)
    {
      anpro_client_put_reconnect_wait(client);
      return;
    }

    if(FD_ISSET(client->sd, wset) && anpro_client_handle_tx_event(client) != 0)
    {
      anpro_client_put_reconnect_wait(client);
      return;
    }
    break;

  case ANPRO_Client::ANPRO_Client_Waiting:
    // nada
    break;
  }

}

static void
anpro_client_do_post_select(ANPRO_TCP_ClientMgr* mgr, fd_set* rset, fd_set* wset)
{
  ANPRO_Client* client;
  struct list_head  tmp;

  //
  // be careful with the following logic.
  // connection can be removed from the list while
  // handling rx/tx event.
  // -hkim-
  INIT_LIST_HEAD(&tmp);
  list_cut_position(&tmp, &mgr->anpro_clients, mgr->anpro_clients.prev);

  while(!list_empty(&tmp))
  {
    client = list_first_entry(&tmp, ANPRO_Client, con_list);
    list_del(&client->con_list);
    list_add_tail(&client->con_list, &mgr->anpro_clients);

    anpro_client_check_rxtx_set(client, rset, wset);
  }

  if(mgr->use_udp_bcast_for_normal_msg && mgr->udp_state == ANPRO_TCP_ClientMgr::ANPRO_UDP_State_OK)
  {
    if(FD_ISSET(mgr->udp_sock, rset))
    {
      anpro10_rx_udp_message(mgr->udp_sock, &mgr->anp10_udp_reader);
    }
  }
}


////////////////////////////////////////////////////////////////////////////////
// 
// ANPRO10 RX/TX 
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_client_tx_to(ANPRO_Client* client, u8_t* buf, s32_t len)
{
  s32_t nwritten = 0,
        ret;

  if(client->tx_pending)
  {
    // something is already queued up
    if(put_circ_buffer(&client->tx_buffer, (char*)buf, len)  == -1)
    {
      // XXX circular buffer overflow. count the stat for better debugging
    }
    return;
  }

  while(nwritten < len)
  {
    ret = write(client->sd, &buf[nwritten], len - nwritten);
    if(ret < 0)
    {
      if(!is_socket_error_would_block(client->sd))
      {
        anpro_client_reset(client);
        anpro_client_put_reconnect_wait(client);
        return;
      }

      client->tx_pending = TRUE;

      put_circ_buffer(&client->tx_buffer, (char*)&buf[nwritten], len - nwritten);
      add_timer(&client->climgr->timer_mgr, &client->generic_timer, ANPRO_TCP_TX_TIMEOUT);
      return;
    }
    nwritten += ret;
  }
}

static inline ANPRO_Client*
anpro10_route_message(ANPRO_TCP_ClientMgr* mgr, u8_t rx_addr, u8_t rx_id)
{
  ANPRO_Client* client;

  list_for_each_entry(client, &mgr->anpro_clients, con_list, ANPRO_Client)
  {
    //if(client->station_id == rx_addr && client->state == ANPRO_Client::ANPRO_Client_Connected)
    if(client->state == ANPRO_Client::ANPRO_Client_Connected)
    {
      return client;
    }
  }
  return NULL;
}

static void
__on_anpro10_tx_req(ANPRO_TCP_ClientMgr* climgr, u8_t* msg, s32_t len, u8_t is_urgent_msg)
{
  ANPRO_Client*                 dest_route;
  u8_t                          *pkt_pos;
  QueueANPRO10_CommandHeading*  UCmd = (QueueANPRO10_CommandHeading*)msg;
  QueueANPRO10_CommandHeading*  NCmd = (QueueANPRO10_CommandHeading*)msg;

  dest_route = is_urgent_msg ?
                anpro10_route_message(climgr, UCmd->TxInfo.rxAddr, UCmd->TxInfo.rxId) :
                anpro10_route_message(climgr, NCmd->TxInfo.rxAddr, NCmd->TxInfo.rxId);

  if(dest_route == NULL)
  {
    return;
  }

  pkt_pos  = climgr->tx_bounce_buffer;
  pkt_pos += ANPRO10_AddPacketPreAmble(pkt_pos);

  pkt_pos += is_urgent_msg ? ANPRO10_AddPacketHeading(pkt_pos, UCmd->TxInfo.rxAddr, UCmd->TxInfo.rxId) :
                             ANPRO10_AddPacketHeading(pkt_pos, NCmd->TxInfo.rxAddr, NCmd->TxInfo.rxId);

  pkt_pos += is_urgent_msg ? ANPRO10_AddCommand(pkt_pos, (u8_t*)&UCmd->Data) :
                             ANPRO10_AddCommand(pkt_pos, (u8_t*)&NCmd->Data);

  pkt_pos += ANPRO10_AddPacketTail(climgr->tx_bounce_buffer, (pkt_pos - climgr->tx_bounce_buffer), false);

  //
  // XXX
  // with TCP, there is no ANPRO10 preamble.
  //
  anpro_client_tx_to(dest_route,
      &climgr->tx_bounce_buffer[ANPRO10_PREAMBLE_SIZE],   // XXX hack. we don't send preamble
      (pkt_pos - climgr->tx_bounce_buffer) - ANPRO10_PREAMBLE_SIZE);
}

static void
__on_anpro10_tx_req_normal(ANPRO_TCP_ClientMgr* climgr, u8_t* msg, s32_t len, u8_t is_urgent_msg)
{
  if(climgr->use_udp_bcast_for_normal_msg)
  {
    if(climgr->udp_state != ANPRO_TCP_ClientMgr::ANPRO_UDP_State_OK)
    {
      return;
    }

    if(anpro10_udp_unicast(climgr->udp_sock, climgr->udp_port_number, msg, len) <= 0)
    {
      anpro_client_put_udp_to_wait_state(climgr);
    }
  }
  else
  {
    __on_anpro10_tx_req(climgr, msg, len, is_urgent_msg);
  }
}

static s32_t
__on_rx_anpro10_message(ANPRO10_Reader* reader, u8_t* msg, s32_t len)
{
  ANPRO10_UnpackPacket(reader->bounce_buffer, &fake_uart_port_for_tcp_client);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 
// socket TX buffer overflow timeout management
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_tx_timer_callback(SGTimerElem* te)
{
  ANPRO_Client*   client = container_of(te, ANPRO_Client, generic_timer);

  switch(client->state)
  {
  case ANPRO_Client::ANPRO_Client_Connecting:
    // connect timeout
    anpro_client_reset(client);
    anpro_client_put_reconnect_wait(client);
    break;

  case ANPRO_Client::ANPRO_Client_Connected:
    // tx timeout
    anpro_client_reset(client);
    anpro_client_put_reconnect_wait(client);
    break;

  case ANPRO_Client::ANPRO_Client_Waiting:
    client->state = ANPRO_Client::ANPRO_Client_Not_Connected;
    break;
  }
}

////////////////////////////////////////////////////////////////////////////////
// 
// anpro udp initialization 
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_client_reinit_udp(SGTimerElem* te)
{
  ANPRO_TCP_ClientMgr* mgr = container_of(te, ANPRO_TCP_ClientMgr, udp_wait_timer);

  anpro_client_init_udp(mgr);
}

static void
anpro_client_init_udp(ANPRO_TCP_ClientMgr* mgr)
{
  mgr->udp_sock = init_anpro_udp_socket(mgr->udp_port_number);
  anpro10_reader_init(&mgr->anp10_udp_reader, __on_rx_anpro10_message);

  mgr->udp_state = ANPRO_TCP_ClientMgr::ANPRO_UDP_State_OK;
  init_timer_elem(&mgr->udp_wait_timer);

  mgr->udp_wait_timer.cb = anpro_client_reinit_udp;
}

static void
anpro_client_put_udp_to_wait_state(ANPRO_TCP_ClientMgr* mgr)
{
  close(mgr->udp_sock);
  mgr->udp_state = ANPRO_TCP_ClientMgr::ANPRO_UDP_State_Waiting;
  add_timer(&mgr->timer_mgr, &mgr->udp_wait_timer, ANPRO_UDP_TIMEOUT);
}
  

////////////////////////////////////////////////////////////////////////////////
// 
// client manager thread
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief main TCP client manager task.
 *        It just polls socket/queue/timer event and
 *        executes appropriate handlers
 *
 */
static void 
anpro_client_thread(void* arg)
{
  ANPRO_TCP_ClientMgr*  mgr;
  s32_t                 maxfd,
                        ret;
  fd_set                rset,
                        wset;
  struct timeval        tv;

  mgr = (ANPRO_TCP_ClientMgr*)arg;

  if(mgr->use_udp_bcast_for_normal_msg)
  {
    anpro_client_init_udp(mgr);
  }

  for(;;)
  {
    maxfd = 0;
    FD_ZERO(&rset);
    FD_ZERO(&wset);

    tv.tv_sec  = 0;
    tv.tv_usec = ANPRO_CLIENT_SELECT_TIMEOUT;

    anpro_select_add_set(mgr->queue_event,  &rset, &maxfd);
    anpro_select_add_set(mgr->timer_tick_event, &rset, &maxfd);

    anpro_client_do_pre_select(mgr, &rset, &wset, &maxfd);

    ret = select(maxfd + 1, &rset, &wset, 0, &tv);

    anpro_client_handle_debug(mgr);

    if(ret <= 0)
    {
      continue;
    }

    if(FD_ISSET(mgr->timer_tick_event, &rset))
    {
      drive_timer(&mgr->timer_mgr);
      ioctlsocket(mgr->timer_tick_event, FIONDECRECV, NULL);
    }

    if(FD_ISSET(mgr->queue_event, &rset))
    {
      anpro_handle_message_q(mgr);
    }

    anpro_client_do_post_select(mgr, &rset, &wset);
  }
}

////////////////////////////////////////////////////////////////////////////////
// 
// debug interface
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_client_debug_handler(ANPRO_TCP_ClientMgr* mgr)
{
  char* buf_ptr = (char*)mgr->msg_buf;

  if(strcmp((char*)mgr->msg_buf, "list_conn") == 0)
  {
    ANPRO_Client* con;
    int               i = 0;

    buf_ptr += sprintf(buf_ptr, "======== Client List =======\r\n");

    list_for_each_entry(con, &mgr->anpro_clients, con_list, ANPRO_Client)
    {
      uint32_t addr, port;

      addr = ntohl(con->server_addr.sin_addr.s_addr);
      port = ntohs(con->server_addr.sin_port);

      buf_ptr += sprintf(buf_ptr, "Client %d: Dest IP-Addr %d.%d.%d.%d\r\n", i, 
          ((addr >> 24) & 0xff),
          ((addr >> 16) & 0xff),
          ((addr >> 8) & 0xff),
          ((addr >> 0) & 0xff));
      buf_ptr += sprintf(buf_ptr, "Client %d: Dest Port %d\r\n", i, port);
      buf_ptr += sprintf(buf_ptr, "Client %d: Station ID %d\r\n", i, con->station_id);
      buf_ptr += sprintf(buf_ptr, "Client %d: State %d\r\n", i, con->state);
      i++;
    }
  } else {
    sprintf(buf_ptr, "Unknown Command\r\n");
  }
}

static void
anpro_client_handle_debug(ANPRO_TCP_ClientMgr* mgr)
{
  if(OS_EVENT_Get(&mgr->debug_req_event) == 0)
  {
    return;
  }

  OS_EVENT_Wait(&mgr->debug_req_event);

  anpro_client_debug_handler(mgr);

  OS_EVENT_Set(&mgr->debug_rsp_event);
}

static void
anpro_client_debug_init(ANPRO_TCP_ClientMgr* mgr)
{
  OS_CREATERSEMA(&mgr->debug_lock);
  OS_EVENT_Create(&mgr->debug_req_event);
  OS_EVENT_Create(&mgr->debug_rsp_event);
  mgr->msg_buf = NULL;
}

void
anpro_client_debug(ANPRO_TCP_ClientMgr* mgr, char* msg_buf)
{
  OS_Use(&mgr->debug_lock);

  mgr->msg_buf = msg_buf;

  // notify the tasky
  OS_EVENT_Set(&mgr->debug_req_event);

  // wait for the debug complete
  OS_EVENT_Wait(&mgr->debug_rsp_event);

  OS_Unuse(&mgr->debug_lock);
}


////////////////////////////////////////////////////////////////////////////////
// 
// public interface
//
////////////////////////////////////////////////////////////////////////////////
void
anpro_client_mgr_init(ANPRO_TCP_ClientMgr* mgr, u8_t use_udp, u16_t udp_port_number)
{
  INIT_LIST_HEAD(&mgr->anpro_clients);
  anpro_init_message_q(mgr);
  anpro_init_timer(mgr);
  mgr->initialized = 1;

  mgr->use_udp_bcast_for_normal_msg         = use_udp;
  mgr->udp_port_number                      = udp_port_number;

  fake_uart_port_for_tcp_client.SystemMatch = true;

  anpro_client_debug_init(mgr);
}

void
anpro_client_connection_register(ANPRO_TCP_ClientMgr* mgr, struct sockaddr_in* server_addr, u16_t dest_station)
{
  ANPRO_Client* client;
  s32_t         sd;

  sd = init_anpro_client_socket();
  if(sd < 0)
  {
    return;
  }

  client = (ANPRO_Client*)malloc(sizeof(ANPRO_Client));
  if(client == NULL)
  {
    close(sd);
    return;
  }

  if(init_circ_buffer(&client->tx_buffer, MAX_ANPRO10_MESSAGE_SIZE) != 0)
  {
    free(client);
    close(sd);
    return;
  }

  client->sd         = sd;
  client->station_id = dest_station;
  memcpy(&client->server_addr, server_addr, sizeof(struct sockaddr_in));

  anpro10_reader_init(&client->anp10_reader, __on_rx_anpro10_message);
  client->tx_pending = FALSE;

  init_timer_elem(&client->generic_timer);
  client->generic_timer.cb     = anpro_tx_timer_callback;

  client->climgr = mgr;
  client->state = ANPRO_Client::ANPRO_Client_Not_Connected;

  INIT_LIST_HEAD(&client->con_list);
  list_add_tail(&client->con_list, &mgr->anpro_clients);
}

void
anpro_client_mgr_start(ANPRO_TCP_ClientMgr* mgr)
{
  sys_thread_new("anpro_climgr", anpro_client_thread, mgr, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}

u8_t
is_this_port_for_anpro_tcp_client(TSNUart* port)
{
  if(port == &fake_uart_port_for_tcp_client)
  {
    return 1;
  }
  return 0;
}

s8_t
anpro_client_post_message_urgent(ANPRO_TCP_ClientMgr* climgr, void* msg, int size)
{
  if(!climgr->initialized)
  {
    return -1;
  }

  if(!climgr->urgent_q->PostMessage(msg, size))
  {
    //
    // 32k size queue and enqueue fails?
    // this means something is fucked up seriously!!!
    // at the moment, we do nada
    //
    return -1;
  }

  // signal the event socket
  ioctl(climgr->queue_event, FIONINCRECV, NULL);
  return 0;
}

s8_t
anpro_client_post_message_normal(ANPRO_TCP_ClientMgr* climgr, void* msg, int size)
{
  if(!climgr->initialized)
  {
    return -1;
  }

  if(!climgr->normal_q->PostMessage(msg, size))
  {
    //
    // 32k size queue and enqueue fails?
    // this means something is fucked up seriously!!!
    // at the moment, we do nada
    //
    return -1;
  }

  // signal the event socket
  ioctl(climgr->queue_event, FIONINCRECV, NULL);
  return 0;
}

#endif /* LWIP_SOCKET */
