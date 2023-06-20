#ifndef __ANPRO_UDP_DEF_H__
#define __ANPRO_UDP_DEF_H__

#include "anpro_net_util.h"

extern s32_t anpro10_udp_broadcast(s32_t sock, u16_t dest_port, u8_t* msg, s32_t len);
extern s32_t anpro10_udp_unicast(s32_t sock, u16_t dest_port, u8_t* msg, s32_t len);
extern void anpro10_rx_udp_message(s32_t sock, ANPRO10_Reader* reader);

#endif //!__ANPRO_UDP_DEF_H__
