
#include "lwip/opt.h"

#if LWIP_SOCKET
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "anpro_net.h"
#include "anpro_net_util.h"
#include "anpro_tcp_server.h"
#include "anpro_udp.h"

#include "RTOS.h"
#include "app/list.h"
#include "app/sg_timer.h"

#include "TSNIncludes.h"
#include "TSNMessageQ.h"

#include "lwip/mem.h"
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/api.h"
#include "lwip/stats.h"
#include "lwip/sockets.h"

#include "app/circ_buffer.h"
extern U32 IP_AddressMain;
static u8_t   _bounce_buffer[MAX_ANPRO10_MESSAGE_SIZE];

static s32_t
anpro10_udp_subnet_broadcast(s32_t sock, u16_t port, u8_t* msg, s32_t len)
{
  struct sockaddr_in    anpro_daddr;
  ip_addr_t             bcast_addr;
  s32_t                 ret;

  // XXX split message logic if necessary

  get_anpro_net_subnet_broadcast_address(&bcast_addr);

  memset(&anpro_daddr, 0, sizeof(anpro_daddr));
  anpro_daddr.sin_family        = AF_INET;
  anpro_daddr.sin_addr.s_addr   = bcast_addr.addr;
  anpro_daddr.sin_port          = htons(port);

  ret = sendto(sock, msg, len, 0, (struct sockaddr*)&anpro_daddr, sizeof(anpro_daddr));
  
  return ret;
}

static s32_t
anpro10_udp_tx_to_master(s32_t sock, u16_t port, u8_t* msg, s32_t len)
{
  struct sockaddr_in    anpro_daddr;
  ip_addr_t             bcast_addr;
  s32_t                 ret;

  // XXX split message logic if necessary


  memset(&anpro_daddr, 0, sizeof(anpro_daddr));
  anpro_daddr.sin_family        = AF_INET;
  if (PROProjectInfo::IP_AddressMain) {
      anpro_daddr.sin_addr.s_addr   = PROProjectInfo::IP_AddressMain + (PROProjectInfo::IP_AddressTCUSlaveStart << 24);
  } else {
      anpro_daddr.sin_addr.s_addr   = inet_addr("192.168.227.50");
  }
  anpro_daddr.sin_port          = htons(port);

  ret = sendto(sock, msg, len, 0, (struct sockaddr*)&anpro_daddr, sizeof(anpro_daddr));
  return ret;
}

s32_t
anpro10_udp_broadcast(s32_t sock, u16_t dest_port, u8_t* msg, s32_t len)
{
  QueueANPRO10_CommandHeading*  NCmd = (QueueANPRO10_CommandHeading*)msg;
  u8_t*                         pkt_pos;

  pkt_pos  = _bounce_buffer;
  pkt_pos += ANPRO10_AddPacketPreAmble(pkt_pos);
  pkt_pos += ANPRO10_AddPacketHeading(pkt_pos, NCmd->TxInfo.rxAddr, NCmd->TxInfo.rxId);
  pkt_pos += ANPRO10_AddCommand(pkt_pos, (u8_t*)&NCmd->Data);
  pkt_pos += ANPRO10_AddPacketTail(_bounce_buffer, (pkt_pos - _bounce_buffer), false);

  return anpro10_udp_subnet_broadcast(sock, dest_port, 
      &_bounce_buffer[ANPRO10_PREAMBLE_SIZE],
      (pkt_pos - _bounce_buffer) - ANPRO10_PREAMBLE_SIZE);
}

s32_t
anpro10_udp_unicast(s32_t sock, u16_t dest_port, u8_t* msg, s32_t len)
{
  QueueANPRO10_CommandHeading*  NCmd = (QueueANPRO10_CommandHeading*)msg;
  u8_t*                         pkt_pos;

  pkt_pos  = _bounce_buffer;
  pkt_pos += ANPRO10_AddPacketPreAmble(pkt_pos);
  pkt_pos += ANPRO10_AddPacketHeading(pkt_pos, NCmd->TxInfo.rxAddr, NCmd->TxInfo.rxId);
  pkt_pos += ANPRO10_AddCommand(pkt_pos, (u8_t*)&NCmd->Data);
  pkt_pos += ANPRO10_AddPacketTail(_bounce_buffer, (pkt_pos - _bounce_buffer), false);

  return anpro10_udp_tx_to_master(sock, dest_port, 
      &_bounce_buffer[ANPRO10_PREAMBLE_SIZE],
      (pkt_pos - _bounce_buffer) - ANPRO10_PREAMBLE_SIZE);
}

void
anpro10_rx_udp_message(s32_t sock, ANPRO10_Reader* reader)
{
  s32_t               len;
  u32_t               from_len;
  struct sockaddr_in  from;
  ip_addr_t           myaddr;

  // XXX split message logic if necessary

  from_len = sizeof(from);
  len = recvfrom(sock, _bounce_buffer, MAX_ANPRO10_MESSAGE_SIZE, 0, (struct sockaddr*)&from, &from_len); 

  if(len <= 0)
  {
    return;
  }

  get_anpro_net_ip_address(&myaddr, CurrentDeviceId, CurrentDeviceAddress);

  if(from.sin_addr.s_addr == myaddr.addr)
  {
    return;
  }

  anpro10_reader_feed(reader, _bounce_buffer, len);
}

#endif //!LWIP_SOCKET
