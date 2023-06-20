#ifndef __ANPR10_NET_UTIL_H__
#define __ANPR10_NET_UTIL_H__

#include "RTOS.h"
#include "app/list.h"
#include "app/sg_timer.h"

#include "TSNIncludes.h"
#include "TSNMessageQ.h"

#include "lwip/sockets.h"

#define ANPRO10_ASSERT(msg, expr)       \
  if(!(expr))                           \
  {                                     \
    while(1)                            \
    {                                   \
    }                                   \
  }

#define ioctl         ioctlsocket

#define ANPRO_READER_BUFFER_SIZE        (1024*16)

struct __anpro10_reader;
typedef s32_t (*anpro10_reader_callback)(struct __anpro10_reader* reader, u8_t* anpro10_msg, s32_t len);

typedef struct __anpro10_reader
{
  enum 
  {
    ANPRO10_RX_Header,
    ANPRO10_RX_Body,
  } state;

  u8_t                      bounce_buffer[ANPRO_READER_BUFFER_SIZE];
  s32_t                     buffered_data_len;
  s32_t                     body_len_to_read;
  anpro10_reader_callback   callback;
} ANPRO10_Reader;

extern u8_t is_socket_error_would_block(s32_t sd);
extern void anpro_adjust_client_socket(s32_t sd);
extern s32_t anpro_net_create_eventfd(void);
extern void anpro_select_add_set(s32_t fd, fd_set* set, s32_t* max_fd);
extern s32_t init_anpro_server_socket(u16_t port);
extern s32_t init_anpro_client_socket(void);
extern s32_t init_anpro_udp_socket(u16_t port);

extern void anpro10_reader_reset(ANPRO10_Reader* reader);
extern void anpro10_reader_init(ANPRO10_Reader* reader, anpro10_reader_callback callback);
extern void anpro10_reader_feed(ANPRO10_Reader* reader, const u8_t* msg, s32_t len);
extern void anpro10_reader_decode(ANPRO10_Reader* reader, u8_t in);

static inline u8_t
anpro10_calc_csum(const u8_t* msg, s32_t len)
{
  s32_t   i;
  u8_t    csum = 0;
  extern  const U8 CRC[];

  for(i = 0; i < len; i++)
  {
    csum = CRC[csum ^ msg[i]];
  }

  return csum;
}

#endif //!__ANPR10_NET_UTIL_H__
