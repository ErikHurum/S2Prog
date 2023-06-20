#include "lwip/opt.h"

#if LWIP_SOCKET

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "anpro_net_util.h"

#include "lwip/mem.h"
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/api.h"
#include "lwip/stats.h"

#include "app/circ_buffer.h"

#include "TSNIncludes.h"

#define ANPRO_TCP_MAX_SERVER_BACKLOG    5

////////////////////////////////////////////////////////////////////////////////
// 
// general socket utilities
//
////////////////////////////////////////////////////////////////////////////////
s32_t
init_anpro_server_socket(u16_t port)
{
  s32_t               listenfd;
  struct sockaddr_in  anpro_saddr;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  LWIP_ASSERT("anpro_server_thread: socket() failed.", listenfd >= 0);

  memset(&anpro_saddr, 0, sizeof(anpro_saddr));
  anpro_saddr.sin_family        = AF_INET;
  anpro_saddr.sin_addr.s_addr   = PP_HTONL(INADDR_ANY);
  anpro_saddr.sin_port          = htons(port);

  if(bind(listenfd, (struct sockaddr*)&anpro_saddr, sizeof(anpro_saddr)) == -1)
  {
    LWIP_ASSERT("anpro_server_thread: bind() failed.", 0);
  }

  if(listen(listenfd, ANPRO_TCP_MAX_SERVER_BACKLOG) == -1)
  {
    LWIP_ASSERT("anpro_server_thread: listen() failed.", 0);
  }

  return listenfd;
}

s32_t
init_anpro_client_socket(void)
{
  s32_t               clisock;

  clisock = socket(AF_INET, SOCK_STREAM, 0);
  LWIP_ASSERT("init_anpro_client_socket: socket() failed.", clisock >= 0);


  anpro_adjust_client_socket(clisock);
  return clisock;
}

void
anpro_select_add_set(s32_t fd, fd_set* set, s32_t* max_fd)
{
  FD_SET(fd, set);

  if(*max_fd < fd)
  {
    *max_fd = fd;
  }
}

s32_t
anpro_net_create_eventfd(void)
{
  s32_t                 udp_sock;
  struct sockaddr_in    my_addr;

  udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
  LWIP_ASSERT("anpro_server_thread: event_socket() failed.", udp_sock >= 0);
  //
  // bind the udp socket to any port available in local loopback
  // interface
  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family        = AF_INET;
  my_addr.sin_addr.s_addr   = inet_addr("127.0.0.1");   
  my_addr.sin_port          = 0;      

  if(bind(udp_sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1)
  {
    LWIP_ASSERT("anpro_server_thread: event_socket bind() failed.", 0);
  }

  return udp_sock;
}

void
anpro_adjust_client_socket(s32_t sd)
{
  const s32_t     const_int_1   = 1;
  s32_t           keep_idle,
                  keep_intvl,
                  keep_cnt,
                  ret;

  keep_idle   = 10;   // 60 sec
  keep_intvl  = 2;   // 10 sec
  keep_cnt    = 5;    // 5 retry

  // 1. enable keep alive so that we won't get any dead lingering connections
  ret = setsockopt(sd, SOL_SOCKET, SO_KEEPALIVE, &const_int_1, sizeof(const_int_1));

  ret = setsockopt(sd, IPPROTO_TCP, TCP_KEEPALIVE, &const_int_1, sizeof(const_int_1));
  ANPRO10_ASSERT("keepalive enable failed", ret == 0);

  ret = setsockopt(sd, IPPROTO_TCP, TCP_KEEPIDLE,   &keep_idle,   sizeof(keep_idle));
  ANPRO10_ASSERT("keep idle set failed", ret == 0);

  ret = setsockopt(sd, IPPROTO_TCP, TCP_KEEPINTVL,  &keep_intvl,  sizeof(keep_intvl));
  ANPRO10_ASSERT("keep interval set failed", ret == 0);

  ret = setsockopt(sd, IPPROTO_TCP, TCP_KEEPCNT,    &keep_cnt,    sizeof(keep_cnt));
  ANPRO10_ASSERT("keep count set failed", ret == 0);

  // put the socket in non-blocking mode so that tx blocking doesn't fuck up
  // the entire server thread
  ioctl(sd, FIONBIO, (char*)&const_int_1);
}

u8_t
is_socket_error_would_block(s32_t sd)
{
  int err;
  socklen_t optlen = sizeof(err);

  // check error number
  lwip_getsockopt(sd, SOL_SOCKET, SO_ERROR, (void*)&err, &optlen);

  if(err == EWOULDBLOCK)
  {
    return TRUE;
  }
  return FALSE;
}

s32_t
init_anpro_udp_socket(u16_t port)
{
  s32_t                 sock;
  struct sockaddr_in    anpro_saddr;

  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  LWIP_ASSERT("anpro_server_thread: udp socket() failed.", sock >= 0);

  memset(&anpro_saddr, 0, sizeof(anpro_saddr));
  anpro_saddr.sin_family        = AF_INET;
  anpro_saddr.sin_addr.s_addr   = PP_HTONL(INADDR_ANY);
  anpro_saddr.sin_port          = htons(port);

  if(bind(sock, (struct sockaddr*)&anpro_saddr, sizeof(anpro_saddr)) == -1)
  {
    LWIP_ASSERT("anpro_server_thread: udp bind() failed.", 0);
  }
  return sock;
}

////////////////////////////////////////////////////////////////////////////////
// 
// ANPRO10 Reader
//
////////////////////////////////////////////////////////////////////////////////
void
anpro10_reader_reset(ANPRO10_Reader* reader)
{
  reader->state             = ANPRO10_Reader::ANPRO10_RX_Header;
  reader->buffered_data_len = 0;
  reader->body_len_to_read  = 0;
}

/**
 * @brief initialize ANPRO10 Reader
 *
 * @param reader reader context to initialize
 * @param callback callback function when a full ANPRO10 message is received
 *
 * @return none
 */
void
anpro10_reader_init(ANPRO10_Reader* reader, anpro10_reader_callback callback)
{
  anpro10_reader_reset(reader);
  reader->callback          = callback;
}

void
anpro10_reader_decode(ANPRO10_Reader* reader, u8_t in)
{
  reader->bounce_buffer[reader->buffered_data_len++] = in;

  switch(reader->state)
  {
  case ANPRO10_Reader::ANPRO10_RX_Header:
    // be careful about alignment shit. NetHeading is 7 bytes long. 
    if(reader->buffered_data_len >= sizeof(struct ANPRO10_PacketHeading))
    {
      const struct ANPRO10_PacketHeading* pH =
                   (struct ANPRO10_PacketHeading*)reader->bounce_buffer;
      u8_t csum;


      csum = anpro10_calc_csum(reader->bounce_buffer, sizeof(struct ANPRO10_PacketHeading) -1);
      if(csum != pH->HCRC)
      {
        anpro10_reader_reset(reader);
        return;
      }

      reader->body_len_to_read = pH->nob - sizeof(struct ANPRO10_PacketHeading);
      if(reader->body_len_to_read <= 3)
      { // this shift appears to happen with RS485. anyway
        anpro10_reader_reset(reader);
        return;
      }
      reader->state = ANPRO10_Reader::ANPRO10_RX_Body;
    }
    break;

  case ANPRO10_Reader::ANPRO10_RX_Body:
    if(reader->buffered_data_len >= (reader->body_len_to_read + sizeof(struct ANPRO10_PacketHeading)))
    { // bingo. we got the message
      u8_t csum;
      u8_t pcsum;
      const struct ANPRO10_PacketHeading* pH =
                   (struct ANPRO10_PacketHeading*)reader->bounce_buffer;

      csum = anpro10_calc_csum(reader->bounce_buffer, pH->nob - 2);

      pcsum = reader->bounce_buffer[pH->nob -2];
      if(pcsum == csum)
      { // another bingo
        reader->callback(reader, reader->bounce_buffer, reader->buffered_data_len);
      }
      anpro10_reader_reset(reader);
    }
    break;
  }
}

void
anpro10_reader_feed(ANPRO10_Reader* reader, const u8_t* msg, s32_t len)
{
  s32_t     i;

  for(i = 0; i < len; i++)
  {
    if(reader->buffered_data_len >= ANPRO_READER_BUFFER_SIZE)
    {
      // something is seriously fucked up here.
      anpro10_reader_reset(reader);
      continue;
    }
    anpro10_reader_decode(reader, msg[i]);
  }
}

#endif //!LWIP_SOCKET
