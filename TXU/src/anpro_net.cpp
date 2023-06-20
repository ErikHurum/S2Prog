#include "lwip/opt.h"


#if LWIP_SOCKET

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "anpro_net.h"

#include "lwip/tcp_impl.h"
#include "lwip/udp.h"
#include "lwip/tcpip.h"
#include "lwip/api.h"

#include "TSNIncludes.h"

extern bool Master;
extern TSNUart *fake_uart_port_for_tcp_clientPtr;
static ANPRO_TCP_Server       _anpro_tcp_server;
static ANPRO_TCP_ClientMgr    _tcp_client_mgr;

static void start_anpro_tcp_server(void) {
    anpro_server_init(&_anpro_tcp_server, PROProjectInfo::IP_TCP_ServerPort, 1, PROProjectInfo::IP_UDP_NetPort, ANPRO_TCP_FLASH_PROG_PORT/*PROProjectInfo::IP_TCP_FlashPort*/);
}

static void start_anpro_tcp_client(void) {
    struct sockaddr_in  server_addr;
    ip_addr_t           server_ip;
    if (PROProjectInfo::IP_AddressMain) {
        server_ip.addr = PROProjectInfo::IP_AddressMain + (PROProjectInfo::IP_AddressTCU_Master << 24);
    } else {
        ANPRO_MASTER_IP(&server_ip);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = server_ip.addr;
    server_addr.sin_port        = htons(PROProjectInfo::IP_TCP_ServerPort);

    anpro_client_mgr_init(&_tcp_client_mgr, 1, PROProjectInfo::IP_UDP_NetPort);
    anpro_client_connection_register(&_tcp_client_mgr, &server_addr, 0);
    anpro_client_mgr_start(&_tcp_client_mgr);
}

void start_anpro_net(void) {
    if (Master) {
        start_anpro_tcp_server();
    } else {
        start_anpro_tcp_client();
    }
}

void get_anpro_net_ip_address(ip_addr_t *ipaddr, uint8_t device_id, uint8_t device_address) {
    uint8_t   ipaddr_last_part = 0;


    switch (device_id) {
    case DEVICE_TDU:
        ipaddr_last_part = PROProjectInfo::IP_AddressTDUStart + device_address;
        break;
    case DEVICE_TCU:
        if (!Master) {
            ipaddr_last_part = PROProjectInfo::IP_AddressTCUSlaveStart + device_address;
        } else {
            ipaddr_last_part = PROProjectInfo::IP_AddressTCU_Master;
        }
        break;
    case DEVICE_PCSW: // Not needed as this code is for TCU/TDU only
        ipaddr_last_part = PROProjectInfo::IP_AddressPCStart + device_address;
        break;
    }
    if (PROProjectInfo::IP_AddressMain) {
        ipaddr->addr = PROProjectInfo::IP_AddressMain + (ipaddr_last_part << 24);
    } else {
        ANPRO_IPADDRESS(ipaddr, ipaddr_last_part);
    }
}
#pragma diag_suppress=Pe068 // IAR specific: No warning for integer conversion resulted in a change of sign
void get_anpro_net_subnet_broadcast_address(ip_addr_t *ipaddr) {
    if (PROProjectInfo::IP_AddressMain) {
        ipaddr->addr = PROProjectInfo::IP_AddressMain + (255 << 24);
    } else {
        ANPRO_BROADCAST_ADDRESS(ipaddr);
    }
}



void get_anpro_device_id_addr_from_ip_addr(u32_t ipaddr, u8_t *device_id, u8_t *device_addr) {
    u8_t    last_digit = (u8_t)(ipaddr & 0xff);
    // TCU slave
    if (last_digit >= PROProjectInfo::IP_AddressTCUSlaveStart && last_digit <= PROProjectInfo::IP_AddressTCUSlaveEnd) {   // slave TCU
        *device_id    = DEVICE_TCU;
        *device_addr  = last_digit - PROProjectInfo::IP_AddressTCUSlaveStart;
    } else if (last_digit >= PROProjectInfo::IP_AddressTDUStart && last_digit <= PROProjectInfo::IP_AddressTDUEnd) {   // TDU
        *device_id    = DEVICE_TDU;
        *device_addr  = last_digit - PROProjectInfo::IP_AddressTDUStart;
    } else if (last_digit >= PROProjectInfo::IP_AddressPCStart && last_digit <= PROProjectInfo::IP_AddressPCEnd) {   // PCSW
        *device_id    = DEVICE_PCSW;
        *device_addr  = last_digit - PROProjectInfo::IP_AddressPCStart;
    } else {   // obviously there is a bug if we hit this case
               // FIXME
               // just crash instead of this bullshit
        *device_id    = DEVICE_TCU;
        *device_addr  = last_digit - PROProjectInfo::IP_AddressTCUSlaveStart;
    }
}

void setup_anpro_network_address(struct netif *nif, ip_addr_t *netmask, ip_addr_t *gw, ip_addr_t *ipaddr) {
    ANPRO_MACADDR(nif->hwaddr, CurrentDeviceId, CurrentDeviceAddress);
    if (PROProjectInfo::IP_AddressMain) {
        // ANPRO Gateway address
        gw->addr = PROProjectInfo::IP_AddressMain + (PROProjectInfo::IP_AddressGateWay << 24);
    } else {
        ANPRO_GATEWEAY_IP(gw);
    }
    ANPRO_SUBNET(netmask);
    get_anpro_net_ip_address(ipaddr, CurrentDeviceId, CurrentDeviceAddress);
}

static void anpro_net_forward(QueueANPRO10_CommandHeading *Command, bool urgent) {
    if (Master) {
        if (urgent) {
            anpro_server_post_message_urgent(&_anpro_tcp_server, (void *)Command,
                                             Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        } else {
            anpro_server_post_message_normal(&_anpro_tcp_server, (void *)Command,
                                             Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        }
    } else {
        if (urgent) {
            anpro_client_post_message_urgent(&_tcp_client_mgr, (void *)Command,
                                             Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        } else {
            anpro_client_post_message_normal(&_tcp_client_mgr, (void *)Command,
                                             Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        }
    }
}

bool anpro_net_send_normal(void *Cmd) {
    QueueANPRO10_CommandHeading *Command  = (QueueANPRO10_CommandHeading *)Cmd;

        anpro_net_forward(Command, false);
    return true;
    }

bool anpro_net_send_urgent(void *Cmd) {
    QueueANPRO10_CommandHeading *Command  = (QueueANPRO10_CommandHeading *)Cmd;

        anpro_net_forward(Command, true);
    return true;
}

bool anpro_net_is_this_cmd_for_net_interface(QueueANPRO10_CommandHeading *cmd) {
    if (!fake_uart_port_for_tcp_clientPtr && cmd->TxInfo.Port == NULL) {
        return false;
    }

    if (Master) {
        return is_this_port_for_anpro_tcp_server(cmd->TxInfo.Port);
    }

    return is_this_port_for_anpro_tcp_client(cmd->TxInfo.Port);
}

//
// just for a test
//
extern "C"
void test_eventfd_for_anpro10_instance1(void) {
    u8_t    msg[16];

    memset(msg, 0xde, sizeof(msg));

    anpro_server_post_message_urgent(&_anpro_tcp_server, msg, sizeof(msg));
}

//
// server debug
//
extern "C"
void anpro_net_server_debug(char *msg_buf) {
    anpro_server_debug(&_anpro_tcp_server, msg_buf);
}

extern "C"
void anpro_net_client_debug(char *msg_buf) {
    anpro_client_debug(&_tcp_client_mgr, msg_buf);
}

#endif //!LWIP_SOCKET


