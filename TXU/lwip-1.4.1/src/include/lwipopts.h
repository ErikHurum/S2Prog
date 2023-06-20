/*
 * Copyright (c) 2001, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: lwipopts.h,v 1.13 2005/01/24 04:29:45 millin Exp $
 */
#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__
#define LWIP_NOASSERT

// hkim. for header include in C++ sources
#ifdef __cplusplus
extern "C" {
#endif

//--------- start of hkim addition ---------------
#define NO_SYS                        0           // just to make sure. we are running on RTOS!
#define LWIP_ETHERNET                 1           // very obvious
#define LWIP_ARP                      1           // again very obvious
#define TCPIP_THREAD_STACKSIZE        4096 //2048        // big enough for LwIP task
#define DEFAULT_THREAD_STACKSIZE      (4*2096 ) //2048
#define DEFAULT_THREAD_PRIO           180           // same as TCPIP_THREAD_PRIO EHSMark
#define TCPIP_MBOX_SIZE               64
//--------- end of hkim addition   ---------------


#define LWIP_NETCONN                    1
#define LWIP_SOCKET                     1
// , struct align....
//------------------------------------------------
#define ETH_PAD_SIZE 					0
//------------------------------------------------

//------------------------------------------------
/* Critical Region Protection */
//------------------------------------------------
/** SYS_LIGHTWEIGHT_PROT
 * define SYS_LIGHTWEIGHT_PROT in lwipopts.h if you want inter-task protection
 * for certain critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define  SYS_LIGHTWEIGHT_PROT	1 //millin
//----------------------------------------------------------------------
/* ---------- Memory options ---------- */
//----------------------------------------------------------------------

/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#define MEM_ALIGNMENT           4

/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
//#define MEM_SIZE                20480//32768//20480
#define MEM_SIZE                  (256 * 1024)  // EHSMark was 256

#define MEMP_NUM_TCPIP_MSG_INPKT      64

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#define MEMP_NUM_PBUF           128  // EHSMark was 64

/* Number of raw connection PCBs */
#define MEMP_NUM_RAW_PCB        8

/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#define MEMP_NUM_UDP_PCB        16

/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB        16

/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#define MEMP_NUM_TCP_PCB_LISTEN 8

/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG        64

/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT    64


//----------------------------------------------------------------------
/* The following four are used only with the sequential API and can be
   set to 0 if the application only will use the raw API. */
//----------------------------------------------------------------------
/* MEMP_NUM_NETBUF: the number of struct netbufs. */
#define MEMP_NUM_NETBUF         64

/* MEMP_NUM_NETCONN: the number of struct netconns. */
#define MEMP_NUM_NETCONN        16

//----------------------------------------------------------------------
/* ---------- Pbuf options ---------- */
//----------------------------------------------------------------------
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE          64

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE       512



//----------------------------------------------------------------------
/* ---------- ARP options ---------- */
//----------------------------------------------------------------------
/** Number of active hardware address, IP address pairs cached */
#define ARP_TABLE_SIZE	8
/**
 * If enabled, outgoing packets are queued during hardware address
 * resolution.
 *
 * This feature has not stabilized yet. Single-packet queueing is
 * believed to be stable, multi-packet queueing is believed to
 * clash with the TCP segment queueing.
 *
 * As multi-packet-queueing is currently disabled, enabling this
 * _should_ work, but we need your testing feedback on lwip-users.
 *
 */
#define ARP_QUEUEING	0
// if TCP was used, must disable this in v1.1.0 //millin


//----------------------------------------------------------------------
/* ---------- IP options ---------- */
//----------------------------------------------------------------------
/* Define IP_FORWARD to 1 if you wish to have the ability to forward
   IP packets across network interfaces. If you are going to run lwIP
   on a device with only one network interface, define this to 0. */
#define IP_FORWARD              0

/* If defined to 1, IP options are allowed (but not parsed). If
   defined to 0, all packets with IP options are dropped. */
#define IP_OPTIONS              0

/** IP reassembly and segmentation. Even if they both deal with IP
 *  fragments, note that these are orthogonal, one dealing with incoming
 *  packets, the other with outgoing packets
 */

/** Reassemble incoming fragmented IP packets */
#define IP_REASSEMBLY                   1

/** Fragment outgoing IP packets if their size exceeds MTU */
#define IP_FRAG                         1


//----------------------------------------------------------------------
/* ---------- DHCP options ---------- */
//----------------------------------------------------------------------

/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. DHCP is not implemented in lwIP 0.5.1, however, so
   turning this on does currently not work. */
#define LWIP_DHCP               0

/* 1 if you want to do an ARP check on the offered address
   (recommended). */
//#define DHCP_DOES_ARP_CHECK     1


//----------------------------------------------------------------------
/* ---------- UDP options ---------- */
//----------------------------------------------------------------------
#define LWIP_UDP                1


//----------------------------------------------------------------------
/* ---------- TCP options ---------- */
//----------------------------------------------------------------------
#define LWIP_TCP                1

/* TCP receive window. */
#define TCP_WND                 (4 * TCP_MSS)

/* Maximum number of retransmissions of data segments. */
#define TCP_MAXRTX              4

/* Maximum number of retransmissions of SYN segments. */
#define TCP_SYNMAXRTX           4

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ         1

/* TCP Maximum segment size. */
#define TCP_MSS                 536 //512		//1476

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF            (4 * TCP_MSS)  //EHSMark was 2

#define CHECKSUM_GEN_TCP	1
//----------------------------------------------------------------------
/* ---------- Other options ---------- */
//----------------------------------------------------------------------

/* Support loop interface (127.0.0.1) */
#define LWIP_HAVE_LOOPIF				        0

#define LWIP_COMPAT_SOCKETS             1


#define LWIP_TCP_KEEPALIVE              1   // hkim
//----------------------------------------------------------------------
/* ---------- Socket Options ---------- */
//----------------------------------------------------------------------

/* Enable SO_REUSEADDR and SO_REUSEPORT options */
#define SO_REUSE 1


//----------------------------------------------------------------------
/* ---------- Statistics options ---------- */
//----------------------------------------------------------------------

#define STATS		1
#define LWIP_STATS	1

#if LWIP_STATS

#define LWIP_STATS_DISPLAY	1
#define LINK_STATS			1
#define IP_STATS			1
#define IPFRAG_STATS		1
#define ICMP_STATS			1
#define UDP_STATS			1
#define TCP_STATS			1
#define MEM_STATS			1
#define MEMP_STATS			1
#define PBUF_STATS			1
#define SYS_STATS			1
#endif /* STATS */


//----------------------------------------------------------------------
/* ------------if you need to do debug-------------*/
//----------------------------------------------------------------------
/*
define LWIP_DEBUG in compiler    and following...
*/
//#define DBG_MIN_LEVEL					DBG_LEVEL_SERIOUS
#define DBG_MIN_LEVEL					LWIP_DBG_LEVEL_OFF
//DBG_LEVEL_WARNING DBG_LEVEL_SERIOUS DBG_LEVEL_SEVERE

#define DBG_TYPES_ON					0//DBG_TRACE | DBG_STATE |DBG_FRESH | DBG_HALT
/*
Then, define debug class in opt.h
* --------------------------------------------------*/

#define ETHARP_DEBUG                    DBG_OFF
#define NETIF_DEBUG                     DBG_OFF
#define PBUF_DEBUG                      DBG_OFF
#define API_LIB_DEBUG                   DBG_OFF
#define API_MSG_DEBUG                   DBG_OFF
#define SOCKETS_DEBUG                   DBG_OFF
#define ICMP_DEBUG                      DBG_OFF
#define INET_DEBUG                      DBG_OFF
#define IP_DEBUG                        DBG_OFF
#define IP_REASS_DEBUG                  DBG_OFF
#define RAW_DEBUG                       DBG_OFF
#define MEM_DEBUG                       DBG_OFF
#define MEMP_DEBUG                      DBG_OFF
#define SYS_DEBUG                       DBG_OFF
#define TCP_DEBUG                       DBG_OFF
#define TCP_INPUT_DEBUG                 DBG_OFF
#define TCP_FR_DEBUG                    DBG_OFF
#define TCP_RTO_DEBUG                   DBG_OFF
//#define TCP_REXMIT_DEBUG                DBG_OFF
#define TCP_CWND_DEBUG                  DBG_OFF
#define TCP_WND_DEBUG                   DBG_OFF
#define TCP_OUTPUT_DEBUG                DBG_OFF
#define TCP_RST_DEBUG                   DBG_OFF
#define TCP_QLEN_DEBUG                  DBG_OFF
#define UDP_DEBUG                       DBG_OFF
#define TCPIP_DEBUG                     DBG_OFF
#define PPP_DEBUG                       DBG_OFF
#define SLIP_DEBUG                      DBG_OFF
#define DHCP_DEBUG                      DBG_OFF

#define DEFAULT_RAW_RECVMBOX_SIZE       8
#define DEFAULT_UDP_RECVMBOX_SIZE       32
#define DEFAULT_TCP_RECVMBOX_SIZE       32
#define DEFAULT_ACCEPTMBOX_SIZE         16

#define LWIP_PROVIDE_ERRNO                1

/* for eventfd like mechanism for LWIP */
#define LWIP_EVENT_IOCTL                  1

/* added this since I am sick and tired of the stupid shell */
#define LWIP_SO_RCVTIMEO                  1

// hkim. for header include in C++ sources
#ifdef __cplusplus
}
#endif

#endif /* __LWIPOPTS_H__ */
