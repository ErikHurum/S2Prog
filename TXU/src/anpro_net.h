#ifndef __ANPRO_NET_DEF_H__
#define __ANPRO_NET_DEF_H__

#include "anpro_tcp_server.h"
#include "anpro_tcp_client.h"

#include "lwip/mem.h"
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/api.h"
#include "lwip/stats.h"
#include "lwip/sockets.h"

//
// MAC Address.
// For TCU and TDU, we don't have MAC addresses publicly dedicated,
// so we just forge them here.
//
// The mac address is in the form of
// 0x00 : 0x01 : 0x02 : 0x03 : CurrentDeviceID : CurrentDeviceAddress
//
#define ANPRO_MACADDR(mac, p4, p5)      \
  mac[0]      = 0x00;                   \
  mac[1]      = 0x01;                   \
  mac[2]      = 0x02;                   \
  mac[3]      = 0x03;                   \
  mac[4]      = p4;                     \
  mac[5]      = p5;                   

//
// At the moment of this writing,
// The system uses a fixed private network of 192.168.227.X with subnet mask of 255.255.255.0.
//
// The gateway address is always 192.168.227.1
// 
// IP address allocation scheme goes as follows.
//
// TCU Master : 192.168.227.50
// TCU slaves : 192.168.227.100 + CurrentDeviceAddress
// TDU Slaves : 192.168.227.150 + CurrentDeviceAddress
// PC CLients : 192.168.227.200 - 250
//
// TCU Master : 192.168.227.30
// TCU slaves : 192.168.227.50 + CurrentDeviceAddress
// PC CLients : 192.168.227.80 - 149
// TDU Slaves : 192.168.227.150 + CurrentDeviceAddress
//
#define ANPRO_NET_GATEWAY               1
#define ANPRO_NET_TCU_MASTER            30
#define ANPRO_NET_TCU_MASTER_END        49  // Not in use
#define ANPRO_NET_TCU_SLAVE_START       50
#define ANPRO_NET_TCU_SLAVE_END         69
#define ANPRO_NET_PC_START              80
#define ANPRO_NET_PC_END                149
#define ANPRO_NET_TDU_START             150
#define ANPRO_NET_TDU_END               199

#define ANPRO_GATEWEAY_IP(gw)           IP4_ADDR(gw, 192, 168, 227, 1)
#define ANPRO_SUBNET(nm)                IP4_ADDR(nm, 255, 255, 255, 0)
#define ANPRO_IPADDRESS(ipaddr, last)   IP4_ADDR(ipaddr, 192,168, 227, last)
#define ANPRO_MASTER_IP(ipaddr)         IP4_ADDR(ipaddr, 192, 168, 227, ANPRO_NET_TCU_MASTER)
#define ANPRO_BROADCAST_ADDRESS(ipaddr) IP4_ADDR(ipaddr, 192, 168, 227, 255)

extern void start_anpro_net(void);
extern void get_anpro_net_ip_address(ip_addr_t* ipaddr, uint8_t device_id, uint8_t device_address);
extern void setup_anpro_network_address(struct netif* nif, ip_addr_t* netmask, ip_addr_t* gw, ip_addr_t* ipaddr);
extern void get_anpro_device_id_addr_from_ip_addr(u32_t ipaddr, u8_t* device_id, u8_t* device_addr);
extern void get_anpro_net_subnet_broadcast_address(ip_addr_t* ipaddr);
extern bool anpro_net_send_normal(void* Cmd);
extern bool anpro_net_send_urgent(void* Cmd);
extern bool anpro_net_is_this_cmd_for_net_interface(QueueANPRO10_CommandHeading* cmd);

#endif
