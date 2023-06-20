////////////////////////////////////////////////////////////////////////////////
//
// ANPRO10 TCP server
//
// Revision History
// -June/23/2016 - initial release by hkim
//
////////////////////////////////////////////////////////////////////////////////
#include "lwip/opt.h"

#if LWIP_SOCKET

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "anpro_net.h"
#include "anpro_tcp_server.h"
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
#define ANPRO_SERVER_SELECT_TIMEOUT 100000        // 100ms  change it later to infinity or something

#define ANPRO_TCP_TX_BUFFER_SIZE    (1024*16)     // fix it to 1K for now
#define ANPRO_TCP_RX_BUFFER_SIZE    (1024*16)     // same

#define ANPRO_TCP_TX_TIMEOUT        15000         // if TX window situation doesn't get batter within this,
// we just kill the connection

#define ANPRO_UDP_TIMEOUT           1000

typedef struct __anpro_connection
{
    struct  list_head   con_list;     // list head for connection management
    s32_t               sd;           // socket descriptor
    CircBuffer          tx_buffer;    // circular buffer for async TX
    SGTimerElem         tx_timer;     // tx timer
    ANPRO_TCP_Server *server;       // tcp server this connection belongs to
    u32_t               client_addr;  // client IP Address
    u16_t               client_port;  // client TCP port
    u8_t                device_id;    // device ID
    u8_t                device_addr;  // device address
    ANPRO10_Reader      anp10_reader; // ANPRO10 RX handler
    u8_t                tx_pending;
    u8_t                system_match;
    u32_t               start_time;
} ANPRO_Connection;

////////////////////////////////////////////////////////////////////////////////
//
// module private prototypes
//
////////////////////////////////////////////////////////////////////////////////
static void anpro_server_init_new_connection(ANPRO_TCP_Server *server, s32_t newsd, struct sockaddr_in *cli_addr, u8_t from_flash_prog_port);
static void anpro_server_deinit_connection(ANPRO_Connection *con);
static void anpro_server_handle_new_connection(ANPRO_TCP_Server *server, u8_t from_flash_prog_port);
static s32_t anpro_server_handle_rx_event(ANPRO_Connection *con);
static s32_t anpro_server_handle_tx_event(ANPRO_Connection *con);
static void anpro_server_do_pre_select(ANPRO_TCP_Server *server, fd_set *rset, fd_set *wset, s32_t *maxfd);
static void anpro_server_check_rxtx_set(ANPRO_Connection *con, fd_set *rset, fd_set *wset);
static void anpro_server_do_post_select(ANPRO_TCP_Server *server, fd_set *rset, fd_set *wset);
static void anpro_server_thread(void *arg);
static void anpro_init_message_q(ANPRO_TCP_Server *server);
static void anpro_handle_message_q(ANPRO_TCP_Server *server);
static void anpro_init_timer(ANPRO_TCP_Server *server);
static void anpro_tx_timer_callback(SGTimerElem *te);
static void anpro_fill_client_station_info(ANPRO_Connection *con, struct sockaddr_in *cli_addr);
static void anpro_fill_flash_prog_station_info(ANPRO_Connection *con, struct sockaddr_in *cli_addr);
static void anpro_server_tx_to(ANPRO_Connection *con, u8_t *buf, s32_t len);
static void anpro_server_tx_broadcast(ANPRO_TCP_Server *server, u8_t *buf, s32_t len);
static void anpro_server_handle_debug(ANPRO_TCP_Server *server);

static inline ANPRO_Connection* anpro10_route_message(ANPRO_TCP_Server *server, u8_t rx_addr, u8_t rx_id, u8_t *is_broadcast);
static inline u8_t anpro10_is_broadcast_dest(u8_t rx_addr, u8_t rx_id);

static void __on_anpro10_tx_req(ANPRO_TCP_Server *server, u8_t *msg, s32_t len, u8_t is_urgent_msg);
static void __on_anpro10_tx_req_normal(ANPRO_TCP_Server *server, u8_t *msg, s32_t len, u8_t is_urgent_msg);
static s32_t __on_rx_anpro10_message(ANPRO10_Reader *con, u8_t *msg, s32_t len);

static void anpro_server_reinit_udp(SGTimerElem *te);
static void anpro_server_init_udp(ANPRO_TCP_Server *server);
static void anpro_server_put_udp_to_wait_state(ANPRO_TCP_Server *server);
static void anpro_server_clear_connection(ANPRO_TCP_Server *server, u8_t device_addr, u8_t device_id);

////////////////////////////////////////////////////////////////////////////////
//
// module globals
//
////////////////////////////////////////////////////////////////////////////////
TSNUart   fake_uart_port_for_tcp = TSNUart();

////////////////////////////////////////////////////////////////////////////////
//
// utilities
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_fill_client_station_info(ANPRO_Connection *con, struct sockaddr_in *cli_addr) {
    con->client_addr  = ntohl(cli_addr->sin_addr.s_addr);
    con->client_port  = ntohs(cli_addr->sin_port);

    get_anpro_device_id_addr_from_ip_addr(con->client_addr, &con->device_id, &con->device_addr);
}

static void
anpro_fill_flash_prog_station_info(ANPRO_Connection *con, struct sockaddr_in *cli_addr) {
    con->client_addr  = ntohl(cli_addr->sin_addr.s_addr);
    con->client_port  = ntohs(cli_addr->sin_port);

    // dirty but clean. what an oxymoron!
    con->device_addr = (u8_t)(con->client_addr & 0xff);
    con->device_id = DEVICE_PC_FLASH_PROG;
}

////////////////////////////////////////////////////////////////////////////////
//
// new connection management
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_server_clear_connection(ANPRO_TCP_Server *server, u8_t device_addr, u8_t device_id) {
    ANPRO_Connection    * pos,
        *n;
    list_for_each_entry_safe(pos, n, &server->anpro_conns, con_list, ANPRO_Connection) {
        if ( pos->device_id == device_id && pos->device_addr == device_addr ) {
            anpro_server_deinit_connection(pos);
        }
    }
}

static void
anpro_server_init_new_connection(ANPRO_TCP_Server *server, s32_t newsd, struct sockaddr_in *cli_addr, u8_t from_flash_prog_port) {
    ANPRO_Connection *con;

    // alloc client connection for session management
    con = (ANPRO_Connection *)malloc(sizeof(ANPRO_Connection));
    if ( con == NULL ) {
        close(newsd);
        return;
    }

    con->start_time = time(NULL);

    con->sd   = newsd;

    // init tx circular buffer
    if ( init_circ_buffer(&con->tx_buffer, ANPRO_TCP_TX_BUFFER_SIZE) != 0 ) {
        free(con);
        close(newsd);
        return;
    }

    // initialize tx timer for tx timeout
    init_timer_elem(&con->tx_timer);
    con->tx_timer.cb    = anpro_tx_timer_callback;

    // adjust socket options for the newly connected socket
    anpro_adjust_client_socket(con->sd);

    con->server = server;

    if ( from_flash_prog_port ) {
        anpro_fill_flash_prog_station_info(con, cli_addr);
    } else {
        anpro_fill_client_station_info(con, cli_addr);
    }

    anpro10_reader_init(&con->anp10_reader, __on_rx_anpro10_message);

    con->tx_pending = FALSE;
    con->system_match = FALSE;

    // clear any previous connection that might be dangling
    anpro_server_clear_connection(server, con->device_addr, con->device_id);

    // finally add the new connection for internal managemnet
    INIT_LIST_HEAD(&con->con_list);
    list_add_tail(&con->con_list, &server->anpro_conns);

    //
    // for per connection version control the moment we got a new connection
    // we send out TCU version info to the client
    //
    ANPRO10_SendSysInfo(&fake_uart_port_for_tcp, con->device_addr, con->device_id);
}

static void
anpro_server_deinit_connection(ANPRO_Connection *con) {
    list_del_init(&con->con_list);

    deinit_circ_buffer(&con->tx_buffer);

    if ( is_timer_running(&con->tx_timer) ) {
        del_timer(&con->server->timer_mgr, &con->tx_timer);
    }

    close(con->sd);
    free(con);
}

static void
anpro_server_handle_new_connection(ANPRO_TCP_Server *server, u8_t from_flash_prog_port) {
    s32_t                 newsd;
    u32_t                 cli_addr_len;
    struct sockaddr_in    cli_addr;

    cli_addr_len = sizeof(cli_addr);

    if ( from_flash_prog_port ) {
        newsd = accept(server->flash_fd,  (struct sockaddr *)&cli_addr, &cli_addr_len);
    } else {
        newsd = accept(server->listen_fd,  (struct sockaddr *)&cli_addr, &cli_addr_len);
    }

    if ( newsd < 0 ) {
        // just return. wish I could print out some kind of debug message here
        return;
    }

    anpro_server_init_new_connection(server, newsd, &cli_addr, from_flash_prog_port);
}

////////////////////////////////////////////////////////////////////////////////
//
// socket TX buffer overflow timeout management
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_tx_timer_callback(SGTimerElem *te) {
    // TCP tx buffer situation hasn't gotten better within
    // the timeout.
    // just close the socket.
    ANPRO_Connection *con = container_of(te, ANPRO_Connection, tx_timer);

    anpro_server_deinit_connection(con);
}

////////////////////////////////////////////////////////////////////////////////
//
// socket rx/tx
//
////////////////////////////////////////////////////////////////////////////////
static s32_t
anpro_server_handle_rx_event(ANPRO_Connection *con) {
    u8_t    buffer[128];
    s32_t   len;

    len = read(con->sd, (s8_t *)buffer, 128);
    if ( len <= 0 ) {
        // connection error or close
        anpro_server_deinit_connection(con);
        return -1;
    }

    anpro10_reader_feed(&con->anp10_reader, buffer, len);
    return 0;
}

static s32_t
anpro_server_handle_tx_event(ANPRO_Connection *con) {
    u8_t    buf[128];
    s32_t   circ_data_size,
        len,
        ret;

    del_timer(&con->server->timer_mgr, &con->tx_timer);
    con->tx_pending = FALSE;

    while ( (circ_data_size = get_circ_buffer_data_size(&con->tx_buffer)) != 0 ) {
        len = circ_data_size < 128 ? circ_data_size : 128;
        peek_circ_buffer(&con->tx_buffer, (char *)buf, len);

        ret = write(con->sd, buf, len);
        if ( ret < 0 ) {
            if ( !is_socket_error_would_block(con->sd) ) {
                anpro_server_deinit_connection(con);
                return -1;
            }

            con->tx_pending = TRUE;
            add_timer(&con->server->timer_mgr, &con->tx_timer, ANPRO_TCP_TX_TIMEOUT);
            return 0;
        }

        get_circ_buffer_no_copy(&con->tx_buffer, ret);
    }
    return 0;
}

static void
anpro_server_tx_to(ANPRO_Connection *con, u8_t *buf, s32_t len) {
    s32_t nwritten = 0,
        ret;

    if ( con->tx_pending )
    //if(get_circ_buffer_data_size(&con->tx_buffer) != 0)
    {
        // something is already queued up
        if ( put_circ_buffer(&con->tx_buffer, (char *)buf, len) == -1 ) {
            // XXX circular buffer overflow. count the stat for better debugging
        }
        return;
    }

    while ( nwritten < len ) {
        ret = write(con->sd, &buf[nwritten], len - nwritten);
        if ( ret < 0 ) {
            if ( !is_socket_error_would_block(con->sd) ) {
                anpro_server_deinit_connection(con);
                return;
            }

            con->tx_pending = TRUE;

            put_circ_buffer(&con->tx_buffer, (char *)&buf[nwritten], len - nwritten);
            add_timer(&con->server->timer_mgr, &con->tx_timer, ANPRO_TCP_TX_TIMEOUT);
            return;
        }
        nwritten += ret;
    }
}

static void
anpro_server_tx_broadcast(ANPRO_TCP_Server *server, u8_t *buf, s32_t len) {
    ANPRO_Connection    * pos,
        *n;
    //
    // XXX be careful. connection might be deleted during TX.
    //
    list_for_each_entry_safe(pos, n, &server->anpro_conns, con_list, ANPRO_Connection) {
        anpro_server_tx_to(pos, buf, len);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// client session management
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_server_do_pre_select(ANPRO_TCP_Server *server, fd_set *rset, fd_set *wset, s32_t *maxfd) {
    ANPRO_Connection *con;

    if ( server->use_udp_bcast_for_normal_msg && server->udp_state == ANPRO_TCP_Server::ANPRO_UDP_State_OK ) {
        anpro_select_add_set(server->udp_sock, rset, maxfd);
    }

    list_for_each_entry(con, &server->anpro_conns, con_list, ANPRO_Connection) {
        anpro_select_add_set(con->sd, rset, maxfd);

        if ( con->tx_pending ) {
            anpro_select_add_set(con->sd, wset, maxfd);
        }
    }
}

static void
anpro_server_check_rxtx_set(ANPRO_Connection *con, fd_set *rset, fd_set *wset) {
    if ( FD_ISSET(con->sd, rset) && anpro_server_handle_rx_event(con) != 0 ) {
        // connection closed.
        return;
    }

    if ( con->tx_pending && FD_ISSET(con->sd, wset) && anpro_server_handle_tx_event(con) != 0 ) {
        // connection closed.
        return;
    }
}

static void
anpro_server_do_post_select(ANPRO_TCP_Server *server, fd_set *rset, fd_set *wset) {
    ANPRO_Connection *con;
    struct list_head  tmp;

    //
    // be careful with the following logic.
    // connection can be removed from the list while
    // handling rx/tx event.
    // -hkim-
    INIT_LIST_HEAD(&tmp);
    list_cut_position(&tmp, &server->anpro_conns, server->anpro_conns.prev);
    while ( !list_empty(&tmp) ) {
        con = list_first_entry(&tmp, ANPRO_Connection, con_list);
        list_del(&con->con_list);
        list_add_tail(&con->con_list, &server->anpro_conns);

        anpro_server_check_rxtx_set(con, rset, wset);
    }

    if ( server->use_udp_bcast_for_normal_msg && server->udp_state == ANPRO_TCP_Server::ANPRO_UDP_State_OK ) {
        if ( FD_ISSET(server->udp_sock, rset) ) {
            anpro10_rx_udp_message(server->udp_sock, &server->anp10_udp_reader);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// anpro udp initialization
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_server_reinit_udp(SGTimerElem *te) {
    ANPRO_TCP_Server *server = container_of(te, ANPRO_TCP_Server, udp_wait_timer);

    anpro_server_init_udp(server);
}

static void
anpro_server_init_udp(ANPRO_TCP_Server *server) {
    server->udp_sock = init_anpro_udp_socket(server->udp_port_number);
    anpro10_reader_init(&server->anp10_udp_reader, __on_rx_anpro10_message);
    server->udp_state = ANPRO_TCP_Server::ANPRO_UDP_State_OK;
    init_timer_elem(&server->udp_wait_timer);

    server->udp_wait_timer.cb = anpro_server_reinit_udp;
}

static void
anpro_server_put_udp_to_wait_state(ANPRO_TCP_Server *server) {
    close(server->udp_sock);
    server->udp_state = ANPRO_TCP_Server::ANPRO_UDP_State_Waiting;
    add_timer(&server->timer_mgr, &server->udp_wait_timer, ANPRO_UDP_TIMEOUT);
}

////////////////////////////////////////////////////////////////////////////////
//
// anpro tcp main server task
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief main TCP server task.
 *        It just polls socket/queue/timer event and
 *        executes appropriate handlers
 *
 */
static void 
anpro_server_thread(void *arg) {
    ANPRO_TCP_Server *server;
    s32_t             maxfd,
        ret;
    fd_set            rset,
        wset;
    struct timeval    tv;

    server = (ANPRO_TCP_Server *)arg;
    server->listen_fd = init_anpro_server_socket(server->port_number);

    if ( server->flash_port != 0 ) {
        server->flash_fd  = init_anpro_server_socket(server->flash_port);
    } else {
        server->flash_fd = -1;
    }

    if ( server->use_udp_bcast_for_normal_msg ) {
        anpro_server_init_udp(server);
    }

    for (;;) {
        maxfd = 0;
        FD_ZERO(&rset);
        FD_ZERO(&wset);

        tv.tv_sec  = 0;
        tv.tv_usec = ANPRO_SERVER_SELECT_TIMEOUT;

        anpro_select_add_set(server->listen_fd, &rset, &maxfd);
        if ( server->flash_fd != -1 ) {
            anpro_select_add_set(server->flash_fd, &rset, &maxfd);
        }
        anpro_select_add_set(server->queue_event,  &rset, &maxfd);
        anpro_select_add_set(server->timer_tick_event, &rset, &maxfd);

        anpro_server_do_pre_select(server, &rset, &wset, &maxfd);

        ret = select(maxfd + 1, &rset, &wset, 0, &tv);

        anpro_server_handle_debug(server);

        if ( ret <= 0 ) {
            continue;
        }

        if ( FD_ISSET(server->timer_tick_event, &rset) ) {
            drive_timer(&server->timer_mgr);
            ioctlsocket(server->timer_tick_event, FIONDECRECV, NULL);
        }

        if ( FD_ISSET(server->queue_event, &rset) ) {
            anpro_handle_message_q(server);
        }

        if ( FD_ISSET(server->listen_fd, &rset) ) {
            anpro_server_handle_new_connection(server, 0);
        }

        if ( server->flash_fd != -1 && FD_ISSET(server->flash_fd, &rset) ) {
            anpro_server_handle_new_connection(server, 1);
        }

        anpro_server_do_post_select(server, &rset, &wset);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// EmBOS message queue handling
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize EMBOS message Q and event sock for I/O multiplexing
 *
 * @param[in] server ANPRO_TCP_Server structure to initialize with
 *
 * @return none
 */
static void
anpro_init_message_q(ANPRO_TCP_Server *server) {
    server->urgent_q = new TSNMessageQ();
    server->normal_q = new TSNMessageQ();
    server->queue_event    = anpro_net_create_eventfd();
}

/**
 * @brief reads from EMBOS message Q and handles it
 *
 * @param[in] server ANPRO_TCP_Server structure to read message from
 *
 * @return none
 */
static void
anpro_handle_message_q(ANPRO_TCP_Server *server) {
    s32_t size;

    //
    // XXX : possible source of bug.
    // q_msg_buf is only 1K here.
    //
    if ( server->urgent_q->GetMessageCond(server->q_msg_buf, &size) != 0 ) {
        // something to handle
        ioctlsocket(server->queue_event, FIONDECRECV, NULL);
        __on_anpro10_tx_req(server, server->q_msg_buf, size, 1);

        // return here so the next urgent message is handled properly
        // it's less efficient but doesn't make any noticeable difference
        return;
    }

    if ( server->normal_q->GetMessageCond(server->q_msg_buf, &size) != 0 ) {
        ioctlsocket(server->queue_event, FIONDECRECV, NULL);
        __on_anpro10_tx_req_normal(server, server->q_msg_buf, size, 0);
    }
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
anpro_timer_tick_callback(void) {
    OS_TIMER *t = OS_GetpCurrentTimer();
    ANPRO_TCP_Server *server = container_of(t, ANPRO_TCP_Server, os_timer_tick);

    ioctlsocket(server->timer_tick_event, FIONINCRECV, NULL);

    OS_RetriggerTimer(t);
}

/**
 * @brief initialize a timer manager for a server
 *
 * @param server instance to initialize timer instance with
 *
 * @return none
 */
static void
anpro_init_timer(ANPRO_TCP_Server *server) {
    //
    // 100ms tick rate with 8 buckets
    // this gotta be enough for this application
    //
    init_timer(&server->timer_mgr, 100, 8);

    server->timer_tick_event  = anpro_net_create_eventfd();

    OS_CREATETIMER(&server->os_timer_tick, anpro_timer_tick_callback, 100);
}

////////////////////////////////////////////////////////////////////////////////
//
// ANPRO10 RX/TX
//
////////////////////////////////////////////////////////////////////////////////
static s32_t
__on_rx_anpro10_message(ANPRO10_Reader *reader, u8_t *msg, s32_t len) {
    ANPRO_Connection *con;

    con = container_of(reader, ANPRO_Connection, anp10_reader);
    //
    // dirty hack to deal with system match per connection
    //
    fake_uart_port_for_tcp.SystemMatch = con->system_match ? true : false;
    ANPRO10_UnpackPacket(reader->bounce_buffer, &fake_uart_port_for_tcp);
    if ( fake_uart_port_for_tcp.SystemMatch ) {
        con->system_match = 1;
    } else {
        con->system_match = 0;
    }

    return 0;
}

static inline u8_t
anpro10_is_broadcast_dest(u8_t rx_addr, u8_t rx_id) {
    if ( rx_id == DEVICE_BROADCAST || rx_addr == DEVICE_BROADCAST_ADDR ) {
        return 1;
    }
    return 0;
}

static inline ANPRO_Connection*
anpro10_route_message(ANPRO_TCP_Server *server, u8_t rx_addr, u8_t rx_id, u8_t *is_broadcast) {
    ANPRO_Connection *con;

    *is_broadcast = 0;

    if ( anpro10_is_broadcast_dest(rx_addr, rx_id) ) {
        *is_broadcast = 1;
        return NULL;
    }

    list_for_each_entry(con, &server->anpro_conns, con_list, ANPRO_Connection) {
        if ( con->device_id == rx_id && con->device_addr == rx_addr ) {
            return con;
        }
    }
    return NULL;
}

static void
__on_anpro10_tx_req(ANPRO_TCP_Server *server, u8_t *msg, s32_t len, u8_t is_urgent_msg) {
    ANPRO_Connection *dest_route;
    u8_t                          *pkt_pos,
        is_broadcast;
    QueueANPRO10_CommandHeading *UCmd = (QueueANPRO10_CommandHeading *)msg;
    QueueANPRO10_CommandHeading *NCmd = (QueueANPRO10_CommandHeading *)msg;

    dest_route = is_urgent_msg ?
        anpro10_route_message(server, UCmd->TxInfo.rxAddr, UCmd->TxInfo.rxId, &is_broadcast) :
        anpro10_route_message(server, NCmd->TxInfo.rxAddr, NCmd->TxInfo.rxId, &is_broadcast);
    // XXX
    // at the moment, no broadcast support
    //
    if ( !is_broadcast && dest_route == NULL ) {
        return;
    }

    pkt_pos  = server->tx_bounce_buffer;
    pkt_pos += ANPRO10_AddPacketPreAmble(pkt_pos);

    pkt_pos += is_urgent_msg ? ANPRO10_AddPacketHeading(pkt_pos, UCmd->TxInfo.rxAddr, UCmd->TxInfo.rxId) :
        ANPRO10_AddPacketHeading(pkt_pos, NCmd->TxInfo.rxAddr, NCmd->TxInfo.rxId);

    pkt_pos += is_urgent_msg ? ANPRO10_AddCommand(pkt_pos, (u8_t *)&UCmd->Data) :
        ANPRO10_AddCommand(pkt_pos, (u8_t *)&NCmd->Data);

    pkt_pos += ANPRO10_AddPacketTail(server->tx_bounce_buffer, (pkt_pos - server->tx_bounce_buffer), false);

    //
    // XXX
    // with TCP, there is no ANPRO10 preamble.
    //
    if ( !is_broadcast ) {
        anpro_server_tx_to(dest_route,
                           &server->tx_bounce_buffer[ANPRO10_PREAMBLE_SIZE],   // XXX hack. we don't send preamble
                           (pkt_pos - server->tx_bounce_buffer) - ANPRO10_PREAMBLE_SIZE);
    } else {
        anpro_server_tx_broadcast(server,
                                  &server->tx_bounce_buffer[ANPRO10_PREAMBLE_SIZE],   // XXX hack. we don't send preamble
                                  (pkt_pos - server->tx_bounce_buffer) - ANPRO10_PREAMBLE_SIZE);
    }
}

static void
__on_anpro10_tx_req_normal(ANPRO_TCP_Server *server, u8_t *msg, s32_t len, u8_t is_urgent_msg) {
    if ( server->use_udp_bcast_for_normal_msg ) {
        if ( server->udp_state != ANPRO_TCP_Server::ANPRO_UDP_State_OK ) {
            return;
        }

        if ( anpro10_udp_broadcast(server->udp_sock, server->udp_port_number, msg, len) <= 0 ) {
            anpro_server_put_udp_to_wait_state(server);
        }
    } else {
        __on_anpro10_tx_req(server, msg, len, is_urgent_msg);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// debug interface
//
////////////////////////////////////////////////////////////////////////////////
static void
anpro_server_debug_handler(ANPRO_TCP_Server *server) {
    char *buf_ptr = (char *)server->msg_buf;

    if ( strcmp((char *)server->msg_buf, "list_conn") == 0 ) {
        ANPRO_Connection *con;
        int               i = 0;

        buf_ptr += sprintf(buf_ptr, "======== Connected Clients =======\r\n");

        list_for_each_entry(con, &server->anpro_conns, con_list, ANPRO_Connection) {
            buf_ptr += sprintf(buf_ptr, "Client %d: IP-Addr %d.%d.%d.%d\r\n", i,
                               ((con->client_addr >> 24) & 0xff),
                               ((con->client_addr >> 16) & 0xff),
                               ((con->client_addr >> 8) & 0xff),
                               ((con->client_addr >> 0) & 0xff));
            buf_ptr += sprintf(buf_ptr, "Client %d: Port %d\r\n", i, con->client_port);
            buf_ptr += sprintf(buf_ptr, "Client %d: Device ID %d\r\n", i, con->device_id);
            buf_ptr += sprintf(buf_ptr, "Client %d: Device Addr %d\r\n", i, con->device_addr);
            buf_ptr += sprintf(buf_ptr, "Client %d: TX Pending %d\r\n", i, con->tx_pending);
            buf_ptr += sprintf(buf_ptr, "Client %d: System Match %d\r\n", i, con->system_match);
            buf_ptr += sprintf(buf_ptr, "Client %d: Start Time %d\r\n", i, con->start_time);
            i++;
        }
    } else {
        sprintf(buf_ptr, "Unknown Command\r\n");
    }
}

static void
anpro_server_handle_debug(ANPRO_TCP_Server *server) {
    if ( OS_EVENT_Get(&server->debug_req_event) == 0 ) {
        return;
    }

    OS_EVENT_Wait(&server->debug_req_event);

    anpro_server_debug_handler(server);

    OS_EVENT_Set(&server->debug_rsp_event);
}

static void
anpro_server_debug_init(ANPRO_TCP_Server *server) {
    OS_CREATERSEMA(&server->debug_lock);
    OS_EVENT_Create(&server->debug_req_event);
    OS_EVENT_Create(&server->debug_rsp_event);
    server->msg_buf = NULL;
}

void
anpro_server_debug(ANPRO_TCP_Server *server, char *msg_buf) {
    OS_Use(&server->debug_lock);

    server->msg_buf = msg_buf;

    // notify the tasky
    OS_EVENT_Set(&server->debug_req_event);

    // wait for the debug complete
    OS_EVENT_Wait(&server->debug_rsp_event);

    OS_Unuse(&server->debug_lock);
}

////////////////////////////////////////////////////////////////////////////////
//
// public interface
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize a single TCP server instance
 *
 * @param server TCP server instance to initialize with
 * @param port tcp port number for server to bind to
 * @param use_udp flash to indicate whether to use udp broadcast or not
 * @param udp_port udp port number to use for braodcast message
 * 
 * @return none
 */
void
anpro_server_init(ANPRO_TCP_Server *server, u16_t port, u8_t use_udp, u16_t udp_port, u16_t flash_port) {
    INIT_LIST_HEAD(&server->anpro_conns);
    anpro_init_message_q(server);
    anpro_init_timer(server);
    server->initialized   = 1;
    server->port_number   = port;
    server->flash_port    = flash_port;

    server->use_udp_bcast_for_normal_msg      = use_udp;
    server->udp_port_number                   = udp_port;

    fake_uart_port_for_tcp.SystemMatch = true;

    anpro_server_debug_init(server);

    sys_thread_new("anpro_server", anpro_server_thread, server, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}

/**
 * @brief post a message to send over a TCP connection to this tcp server
 *
 * @param server TCP server instance to send message to
 * @param msg message buffer to send
 * @param size message size
 *
 * @return 0 if message is queued successfully into the embos message Q
 *        -1 if enqueue fails
 */
s8_t
anpro_server_post_message_urgent(ANPRO_TCP_Server *server, void *msg, int size) {
    if ( !server->initialized ) {
        return -1;
    }

    if ( !server->urgent_q->PostMessage(msg, size) ) {
        //
        // 32k size queue and enqueue fails?
        // this means something is fucked up seriously!!!
        // at the moment, we do nada
        //
        return -1;
    }

    // signal the event socket
    ioctl(server->queue_event, FIONINCRECV, NULL);
    return 0;
}

s8_t
anpro_server_post_message_normal(ANPRO_TCP_Server *server, void *msg, int size) {
    if ( !server->initialized ) {
        return -1;
    }

    if ( !server->normal_q->PostMessage(msg, size) ) {
        //
        // 32k size queue and enqueue fails?
        // this means something is fucked up seriously!!!
        // at the moment, we do nada
        //
        return -1;
    }

    // signal the event socket
    ioctl(server->queue_event, FIONINCRECV, NULL);
    return 0;
}

u8_t
is_this_port_for_anpro_tcp_server(TSNUart *port) {
    if ( port == &fake_uart_port_for_tcp ) {
        return 1;
    }
    return 0;
}
#endif /* LWIP_SOCKET */
