////////////////////////////////////////////////////////////////////////////////
//
// Cirrus CS8900 10BT ethernet chip driver for LwIP on emBOS.
//
// Revision History
// - May/17/2016 : major revamp. still shitty but mostly working. -hkim-
//
////////////////////////////////////////////////////////////////////////////////
#include "RTOS.H"
#include "2410addr.h"
#include "2410lib.h"
/** @file
 * Copyright (c) 2001 Leon Woestenberg <leon.woestenberg@axon.nl>
 * Copyright (c) 2001 Axon Digital Design B.V., The Netherlands.
 * All rights reserved.
 *
 * This is a device driver for the Crystal Semiconductor CS8900
 * chip in combination with the lwIP stack.
 *
 * This is work under development. Please coordinate changes
 * and requests with Leon Woestenberg <leon.woestenberg@axon.nl>
 *
 * The Swedish Institute of Computer Science and Adam Dunkels
 * are specifically granted permission to redistribute this
 * source code under any conditions they seem fit.
 *
 * A quick function roadmap:
 *
 * cs8900_*() are low level, cs8900 hardware specific functions.
 * These are static functions of the device driver source and
 * SHOULD NOT need to be called from outside this source.
 *
 * cs8900if_*() are the lwIP network interface functions.
 *
 * cs8900_interrupt() is an early interrupt service routine (ISR).
 * It merely sets a flag to indicate the cs8900 needs servicing.
 * (This function MAY be tied to an interrupt vector, IF present).
 *
 * cs8900_service() is the actual interrupt event service routine.
 * It must be called whenever the cs8900 needs servicing. It MAY
 * be polled safely (so, you do NOT NEED interrupt support.)
 *
 * cs8900_init() sets up the cs8900, using its register set. When
 * using the driver on your particular hardware platform, make sure
 * the register setups match.
 * Function is called from cs8900if_init().
 *
 * cs8900_input() transfers a received packet from the chip.
 * Function is called from cs8900if_input().
 *
 * cs8900_output() transfers a packet to the chip for transmission.
 * Function is called from cs8900if_output().
 *
 * cs8900if_init() initializes the lwIP network interface, and
 * calls cs8900_init() to intialize the hardware.
 * Function is called from lwIP.
 *
 * cs8900if_service() is the service routine, which must be called
 * upon the need for service, or on a regular basis, in order to
 * service the Ethernet chip.
 *
 * cs8900if_input() calls cs8900_input() to get a received packet
 * and then forwards the packet to protocol(s) handler(s).
 * Function is called from cs8900_service().
 *
 * cs8900if_output() resolves the hardware address, then
 * calls cs8900_output() to transfer the packet.
 * Function is called from lwIP.
 *
 * Future development:
 *
 * Split the generic Ethernet functionality (a lot of the
 * cs8900if_*() functions) and the actual cs8900a dependencies.
 *
 * Enhance the interrupt handler to service the Ethernet
 * chip (to decrease latency); support early packet
 * inspection (during reception) to early drop unwanted
 * packets, minimize chip buffer use and maximize throughput.
 *
 * Statistics gathering.
 *
 */

#include "lwip/debug.h"

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/sys.h"
#include "netif/etharp.h"

#define DEBUG_CS8900 0
#if 0
#  define DBG_LEVEL 1
#  include "leds.h"
#  include "display.h"
//#  include "page.h"
#else
#  define leds_on()
#  define leds_off()
#endif

#include "arch\cs8900if.h"
#ifdef SNMP
#  include "snmp.h"
#  include "mib2if.h"
#endif

/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'
unsigned char sector16[30]; // A piece of ROM/RAM where the MAC resides Was deceleared extern far
unsigned char *eth_oui = &sector16[0]; // Ethernet MAC address Was deceleared far

static const struct eth_addr ethbroadcast = {{0xffU,0xffU,0xffU,0xffU,0xffU,0xffU}};

/* Forward declarations. */
static void  cs8900if_input(struct netif *netif);
static err_t cs8900if_output(struct netif *netif, struct pbuf *p,
                   struct ip_addr *ipaddr);

static err_t cs8900_output(struct netif *netif, struct pbuf *p);
static struct pbuf *cs8900_input(struct netif *netif);
static void cs8900_service(struct netif *netif);

/* Define these to match your hardware setup */
#define MEM_BASE 0x29000000
#define IO_BASE  0x300      // Default IO Port Address Offset 300 internal in chip
#define INT_NR   0x10

#define RXTXREG  *((volatile u16_t *)(MEM_BASE + IO_BASE))
#define TXCMD    *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x04))
#define TXLENGTH *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x06))
#define ISQ      *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x08))
#define PACKETPP *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x0A))
#define PPDATA   *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x0C))

// CS8900 PacketPage register offsets

#define  CS_PP_EISA        0x0000          // EISA Registration number of CS8900
#define  CS_PP_PRODID      0x0002          // Product ID Number
#define  CS_PP_IOBASE      0x0020          // I/O Base Address
#define  CS_PP_INTNUM      0x0022          // Interrupt number (0,1,2, or 3)
#define  CS_PP_RXCFG       0x0102          // Receiver Configuration
#define  CS_PP_RXCTL       0x0104          // Receiver Control
#define  CS_PP_TXCFG       0x0106          // Transmit Configuration
#define  CS_PP_BUFCFG      0x010A          // Buffer Configuration
#define  CS_PP_LINECTL     0x0112          // Line Control Register offset
#define  CS_PP_SELFCTL     0x0114          // Self Control
#define  CS_PP_BUSCTL      0x0116          // Bus Control
#define  CS_PP_TESTCTL     0x0118          // Test Control
#define  CS_PP_ISQ         0x0120          // Interrupt status queue
#define  CS_PP_RXEVENT     0x0124          // Receiver Event
#define  CS_PP_TX_EVENT    0x0128          // Transmitter Event
#define  CS_PP_BUF_EVENT   0x012C          // Buffer Event
#define  CS_PP_RXMISS      0x0130          // Receiver Miss Counter
#define  CS_PP_TXCOL       0x0132          // Transmit Collision Counter
#define  CS_PP_LINESTATUS  0x0134          // Line Status
#define  CS_PP_SELFTEST    0x0136          // Self Status
#define  CS_PP_BUSSTATUS   0x0138          // Bus Status
#define  CS_PP_TXCMD       0x0144          // Transmit Command Request
#define  CS_PP_TXLEN       0x0146          // Transmit Length
#define  CS_PP_IA1         0x0158          // Individual Address (IA)
#define  CS_PP_IA2         0x015A          // Individual Address (IA)
#define  CS_PP_IA3         0x015C          // Individual Address (IA)

#define  CS_PP_RXSTATUS    0x0400          // Receive Status
#define  CS_PP_RXLEN       0x0402          // Receive Length
#define  CS_PP_RXFRAME     0x0404          // Receive Frame Location
#define  CS_PP_TXFRAME     0x0A00          // Transmit Frame Location

static u16_t
cs8900_readreg(u16_t regno)
{
  PACKPP  = regno;
  return PPDATA;
}

static void
cs8900_writereg(u16_t regno, u16_t value)
{
  PACKPP  = regno;
  PPDATA  = value;
}

#if DEBUG_CS8900
// network interface state
static struct netif *cs8900if_netif;
#endif
// hardware interrupt vector handler
void cs8900irq_handler(struct netif *netif)
{
  struct cs8900if *cs8900if = netif->state;
  // network interface is configured?
  if (cs8900if != NULL)
  {
    // chip needs service
    cs8900if->needs_service = 1;
#if (CS8900_STATS > 0)
    cs8900if->interrupts++;
#endif
  }
  leds_on();
}

// cs8900_init()
//
// initializes the CS8900A
static void cs8900_init(struct netif *netif)
{
  u16_t dummy;
  int StartTime = OS_Time;
  leds_off();

  /* MAC address */
  ((struct cs8900if *)netif->state)->ethaddr->addr[0] = eth_oui[0];
  ((struct cs8900if *)netif->state)->ethaddr->addr[1] = eth_oui[1];
  ((struct cs8900if *)netif->state)->ethaddr->addr[2] = eth_oui[2];
  ((struct cs8900if *)netif->state)->ethaddr->addr[3] = eth_oui[3];
  ((struct cs8900if *)netif->state)->ethaddr->addr[4] = eth_oui[4];
  ((struct cs8900if *)netif->state)->ethaddr->addr[5] = eth_oui[5];

  // set RESET bit
  PACKETPP = CS_PP_SELFCTL;
  PPDATA = 0x0055U;

  // { the RESET bit will be cleared by the cs8900a
  //   as a result of the reset }
#if (DBG_LEVEL > 0)
  page_printf("\f\vwaiting for RESET zero\n");
#endif
  // RESET bit cleared?
  while((PPDATA & 0x0040U) != 0); // TODO: add timeout
  OS_Delay(100);
  // { after full initialization of the cs8900a
  //   the INITD bit will be set }

  PACKETPP = CS_PP_SELFTEST;
#if (DBG_LEVEL > 0)
  page_printf("\f\vwaiting for INITD set\n");
#endif
  // INITD bit still clear?
   int StartInitTime = OS_Time;
   int InitTime;
  do{
     InitTime = OS_Time - StartInitTime;
    OS_Delay(10);
  }  while ((((PPDATA & 0x0080U) == 0)) && (InitTime < 1000)); // TODO: add timeout
  // { INITD bit is set }
  OS_Delay(100);

#if 0
#if (DBG_LEVEL > 0)
  page_printf("\f\vwaiting for SIBUSY zero\n");
#endif

  // SIBUSY bit still set?
  while ((PPDATA & 0x0100U) == 0x0100); // TODO: add timeout
  // { SIBUSY bit clear }
#endif

#if 0
  // datasheet section 3.3.3
  dummy = *(u16_t *)(MEM_BASE + IO_BASE + 0x0D);
  /* Dummy read, put chip in 16bit-mode */
  dummy = *(u16_t *)(MEM_BASE + IO_BASE + 0x0D);
#endif
  int FinishTime = OS_Time;
  int TTime = FinishTime-StartTime;
  // Set MAC address
  PACKETPP = CS_PP_IA1;
  PPDATA = (u16_t)((struct cs8900if *)netif->state)->ethaddr->addr[0] | ((u16_t)((struct cs8900if *)netif->state)->ethaddr->addr[1] << 8U);
  PACKETPP = CS_PP_IA2;
  PPDATA = (u16_t)((struct cs8900if *)netif->state)->ethaddr->addr[2] | ((u16_t)((struct cs8900if *)netif->state)->ethaddr->addr[3] << 8U);
  PACKETPP = CS_PP_IA3;
  PPDATA = (u16_t)((struct cs8900if *)netif->state)->ethaddr->addr[4] | ((u16_t)((struct cs8900if *)netif->state)->ethaddr->addr[5] << 8U);

  // accept valid unicast or broadcast frames
  PACKETPP = CS_PP_RXCTL;
  PPDATA = (0x0005U | 0x0800U/*broadcast*/ | 0x0400U/*individual*/ | 0x0100U/*RxOK*/);

  // enable receive interrupt
  PACKETPP = CS_PP_RXCFG;
  PPDATA = (0x0003U | 0x0100U/*RXIRQ*/);

  // disable transmit interrupt (is default)
  PACKETPP = CS_PP_TXCFG;
  PPDATA = (0x0007U | 0);

  // use interrupt number 0
  PACKETPP = CS_PP_INTNUM;
  PPDATA = (0x0000U);

  // generate interrupt event on:
  // - the RxMISS counter reaches 0x200, or
  // - a received frame is lost
  PACKETPP = CS_PP_BUFCFG;
  PPDATA = (0x000bU |
#if (CS8900_STATS > 0) // interrupt before counter overflow
  (0x2000U/*MissOvfloiE*/ | 0x1000U/*TxColOvfloiE*/) |
#endif
#if (CS8900_STATS > 1) // interrupt on counter increment
  (0x0400U/*RxMissiE*/) |
#endif
  0x0000);

  // enable interrupt generation
  PACKETPP = CS_PP_BUSCTL;
  PPDATA = (0x0017U | 0x8000U/*EnableIRQ*/);

  // enable:
  // - receiver
  // - transmitter
  PACKETPP = CS_PP_LINECTL;
  PPDATA = (0x0013U | 0x0080U/*SerTxOn*/ | 0x0040U/*SerRxOn*/);
  //page_printf("\f\vCS8900A configured\n");
}

static err_t cs8900_output(struct netif *netif, struct pbuf *p)
{
    int tries = 0;

  // exit if link has failed
  PACKETPP = CS_PP_LINESTATUS;
  if ((PPDATA & 0x0080U/*LinkOK*/) == 0) return ERR_CONN; // no Ethernet link

  // transmit command
  TXCMD = 0x00C9U;
  TXLENGTH = p->tot_len;

  PACKETPP = CS_PP_BUSSTATUS;
  // not ready for transmission and still within 100 retries?
  while(((PPDATA & 0x0100U/*Rdy4TxNOW*/) == 0) && (tries++ < 100))
  {
    // throw away the last committed received frame
    PACKETPP = CS_PP_RXCFG;
    PPDATA = (0x0003U | 0x0040U/*Skip_1*/ | 0x0100U/*RxOKiE*/);
    PACKETPP = CS_PP_BUSSTATUS;
    /* cs8900if->dropped++; // CHECK: we do not know if we actually will drop a frame here */
  }
  // ready to transmit?
  if(tries < 100)
  {
    // q traverses through linked list of pbuf's
    struct pbuf *q;
    for(q = p; q != NULL; q = q->next)
    {
      u16_t i;
      u16_t *ptr = (u16_t *)q->payload;
      // Send the data from the pbuf to the interface, one pbuf at a
      // time. The size of the data in each pbuf is kept in the ->len
      // variable.
      for(i = 0; i < q->len; i += 2)
      {
        RXTXREG = *ptr++;
      }
#if (CS8900_STATS > 0)
      ((struct cs8900if *)netif->state)->sentbytes += q->len;
#endif
#ifdef SNMP
    if_add_ifOutOctets(p->tot_len);
#endif
    }
#if (CS8900_STATS > 0)
    ((struct cs8900if *)netif->state)->sentpackets++;
#endif
  }
  else
  {
    // { not ready to transmit!? }
  }

  return ERR_OK;
}

/*
 * cs8900_input():
 *
 * Allocates a pbuf and transfers the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 */

// To be called just after reading an ISQ event
// containing the "Receiver Event" register.
//
// This function copies a frame from the CS8900A.
// It is designed fail-safe:
// - It does not assume a frame is actually present.
// - It checks for non-zero length
// - It does not overflow the frame buffer
static struct pbuf *cs8900_input(struct netif *netif)
{
  struct pbuf *p = 0, *q;
  u16_t len = 0;
  u16_t event_type;
  u16_t i;
  u16_t *ptr;

  // read RxStatus
  event_type = RXTXREG;

  // correctly received frame, either broadcast or individual address?
  // TODO: think where these checks should appear: here or in cs8900_input()
  if ((event_type & 0x0100U/*RxOK*/) && (event_type & 0x0c00U/*Broadcast | Individual*/))
  {
#ifdef SNMP
//    if (event_type & 0x0400U/*Individual*/) if_inc_ifInUcastPkts() else if_inc_ifInNUcastPkts();
#endif
    event_type = 0;
    // read RxLength
    len = RXTXREG;
    //DEBUGF(ETH_DEBUG, ("cs8900_input: packet len %u\n", len));
#ifdef SNMP
    if_add_ifInOctets(len);
#endif
    // positive length?
    if (len > 0)
    {
      // allocate a pbuf chain with total length 'len'
      p = pbuf_alloc(PBUF_LINK, len, PBUF_POOL);
      if (p != 0)
      {
        for (q = p; q != 0; q = q->next)
          {
          //DEBUGF(ETH_DEBUG, ("cs8900_input: pbuf @%p len %u\n", q, q->len));
            ptr = q->payload;
          // TODO: CHECK: what if q->len is odd? we don't use the last byte?
            for (i = 0; i < (q->len + 1) / 2; i++)
          {
              *ptr = RXTXREG;
              ptr++;
          }
        }
      }
      // could not allocate a pbuf
      else
      {
        // skip received frame
        // TODO: maybe do not skip the frame at this point in time?
        PACKETPP = CS_PP_RXCFG;
        PPDATA = (0x0003U | 0x0100U/*RxOKiE*/ | 0x0040U/*Skip_1*/);
#if (CS8900_STATS > 0)
        ((struct cs8900if *)netif->state)->dropped++;
#endif
#ifdef SNMP
        if_inc_ifInDiscards();
#endif
        len = 0;
      }
    }
    // length was zero
    else
    {
    }
  }
  return p;
}


// To be called when the cs8900a needs service. Does
// not assume the cs8900a needs service. Does test the
// cs8900a whether it needs service.
//
// As such, may be used robustly called as a deferred
// (or "late") interrupt handler, or may be called in
// a loop to implement polling, or both.
//
// Use cs8900if_service() from your application instead
// of this function.

static void cs8900_service(struct netif *netif)
{
  // amount of ISQ's to handle (> 0) in one cs8900_service() call
  unsigned char events2service = 100;
  // NOTES:
  // static, so only initialized to zero at program start.
  // irq_status will always hold the last ISQ event register that
  // still needs service. As such, we may leave this function if
  // we encounter an event we cannot service yet, and return later
  // to try to service it.
  static u16_t irq_status = 0x0000U;

  // The "cs8900_needs_service" flag indicates whether any events
  // still need to be serviced.
  // clear flag here.
  // a receive interrupt can, *concurrently with this function*,
  // set this flag on new ISQ event occurences.
  // we will re-evaluate the correct setting of this flag at
  // function exit (below).
  ((struct cs8900if *)netif->state)->needs_service = 0;
  leds_off();

  // no unhandled irq_status left?
  if (irq_status == 0x0000U)
  {
    // read ISQ register
    irq_status = ISQ;
  }
  // ISQ interrupt event, and allowed to service in this loop?
  while ((irq_status != 0x0000U) && (events2service-- > 0))
  {
    // investigate event
    if ((irq_status & 0x003fU) == 0x0004U/*Receiver Event*/)
    {
      // correctly received frame, either broadcast or individual address
      // TODO: think where these checks should appear: here or in cs8900_input()
      if ((irq_status & 0x0100U/*RxOK*/) && (irq_status & 0x0c00U/*Broadcast | Individual*/))
      {
        // read the frame from the cs8900a
        cs8900if_input(netif);
      }
      else
      {
        // skip this frame
        PACKETPP = CS_PP_RXCFG;
        PPDATA |= 0x0040U/*Skip_1*/;
#if (CS8900_STATS > 0)
        ((struct cs8900if *)netif->state)->dropped++;
#endif
      }
    }
#if (CS8900_STATS > 0)
    else if ((irq_status & 0x003fU) == 0x0010U/*RxMISS Event*/)
    {
      ((struct cs8900if *)netif->state)->missed += (irq_status >> 6);
    }
    else if ((irq_status & 0x003fU) == 0x0012U/*TxCOL Event*/)
    {
      ((struct cs8900if *)netif->state)->collisions += (irq_status >> 6);
    }
#endif
    // Cannot have delay from interrupt OS_Delay(5);
    // read ISQ register
    irq_status = ISQ;
  }

  // we did not deplete the ISQ?
  if (irq_status != 0x0000U)
  {
    // the cs8900a still needs service
    ((struct cs8900if *)netif->state)->needs_service = 1;
    leds_on();
  }
#if (CS8900_STATS > 1)
  // read RxMiss Counter (zeroes itself upon read)
  PACKETPP = CS_PP_RXMISS;
  ((struct cs8900if *)netif->state)->missed += (PPDATA >> 6);
  // read RxCol Counter (zeroes itself upon read)
  PACKETPP = CS_PP_TXCOL;
  ((struct cs8900if *)netif->state)->collisions += (PPDATA >> 6);
#endif
}

void cs8900if_service(struct netif *netif)
{
  // is there a reason to call the service routine?
  if ((((struct cs8900if *)netif->state)->needs_service) || (((struct cs8900if *)netif->state)->use_polling))
  {
    cs8900_service(netif);
  }
}

/*-----------------------------------------------------------------------------------*/
/*
 * cs8900if_output():
 *
 * This function is called by the TCP/IP stack when an IP packet
 * should be sent. After ARP address lookup, it calls cs8900_output() to
 * do the actual transmission of the packet.
 *
 */
/*-----------------------------------------------------------------------------------*/
static err_t cs8900if_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr)
{
  struct cs8900if *cs8900if = netif->state;
  err_t Err = etharp_output(netif, p, ipaddr);
  // Possibly inverted
  if (Err == ERR_OK)
  {
    return cs8900_output(netif, p);
  }
  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
/*
 * cs8900if_input():
 *
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function cs8900_input() that
 * should handle the actual reception of bytes from the network
 * interface.
 *
 */
/*-----------------------------------------------------------------------------------*/
static void
cs8900if_input(struct netif *netif)
{
  struct cs8900if *cs8900if = netif->state;
  struct eth_hdr *ethhdr;
  struct pbuf *p;

  p = cs8900_input(netif);

  if(p == NULL) {
    return;
  }
  ethhdr = p->payload;

  switch(htons(ethhdr->type)) {
  case ETHTYPE_IP:
    etharp_ip_input(netif, p);
    pbuf_header(p, -14);
    netif->input(p, netif);
    break;
  case ETHTYPE_ARP:
    {
        etharp_arp_input(netif, ((struct cs8900if *)netif->state)->ethaddr, p);
        cs8900_output(netif, p);
        pbuf_free(p);
    }
    break;
  default:
    pbuf_free(p);
    break;
  }
}
/*-----------------------------------------------------------------------------------*/
/*
 * cs8900if_init():
 *
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 */
/*-----------------------------------------------------------------------------------*/
err_t
cs8900if_init(struct netif *netif)
{
  struct cs8900if *cs8900if;

  // TODO: check result!
  cs8900if = mem_malloc(sizeof(struct cs8900if));
    if (cs8900if == NULL) return ERR_MEM;

  netif->state      = cs8900if;
  netif->name[0]    = IFNAME0;
  netif->name[1]    = IFNAME1;
  netif->output     = cs8900if_output;
  netif->linkoutput = cs8900_output;

  cs8900if->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);
  // initially assume no ISQ event
  cs8900if->needs_service = 0;
  // set to 1 if polling method is used
  cs8900if->use_polling = 0;
    /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;
  /* maximum transfer unit */
  netif->mtu = 1500;
  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;


#if (CS8900_STATS > 0)
  // number of interrupts (vector calls)
  cs8900if->interrupts = 0;
  cs8900if->missed = 0;
  cs8900if->dropped = 0;
  cs8900if->sentpackets = 0;
  cs8900if->sentbytes = 0;
#endif

  cs8900_init(netif);

  // TODO: remove this hack
#if DEBUG_CS8900
  cs8900if_netif = netif;
#endif
 etharp_init();
    return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/

// this basically dumps a array of bytes, length "len" into a UDP message. It bypasses
// any functionality within lwIP, acting as a low level debug output function (in case
// your hardware has no, or limited, display output available) to debug lwIP itself.
//
#if DEBUG_CS8900
void cs8900_send_debug(unsigned char *p, unsigned int len)
{
    int tries = 0, i;

  // exit if link has failed
  PACKETPP = CS_PP_LINESTATUS;
  if ((PPDATA & 0x0080U/*LinkOK*/) == 0) return; // TODO: find a correct error code

  /* transmit command */
  TXCMD = 0x00C9U;
  TXLENGTH = (14 + 20 + 8 + len < 60)?60:(14 + 20 + 8 + len);

  PACKETPP = CS_PP_BUSSTATUS;
  // not ready for transmission and still within 100 retries?
  while(((PPDATA & 0x0100U/*Rdy4TxNOW*/) == 0) && (tries++ < 100))
  {
    // throw away the last committed received frame
    PACKETPP = CS_PP_RXCFG;
    PPDATA = (0x0003U | 0x0040U/*Skip_1*/ | 0x0100U/*RxOKiE*/);
    PACKETPP = CS_PP_BUSSTATUS;
    /* cs8900if->dropped++; CHECK: we do not know if we actually will drop a frame here, do we? */
  }
  // ready to transmit?
  if((PPDATA & 0x0100U/*Rdy4TxNOW*/) != 0)
  {
    u16_t data, checksum = 0;

    // destination Ethernet address
    RXTXREG = 0xffffU;//htons((0x00 << 8) | 0x0a);
    RXTXREG = 0xffffU;//htons((0x24 << 8) | 0xc5);
    RXTXREG = 0xffffU;//htons((0x72 << 8) | 0x6d);
    // source Ethernet address
    RXTXREG = htons(((u16_t)eth_oui[0] << 8U) | (u16_t)eth_oui[1]);
    RXTXREG = htons(((u16_t)eth_oui[2] << 8U) | (u16_t)eth_oui[3]);
    RXTXREG = htons(((u16_t)eth_oui[4] << 8U) | (u16_t)eth_oui[5]);
    // frame type
    RXTXREG = htons(0x0800);
    // TOS, version
    RXTXREG = htons(data = ((0x40 | 0x05) << 8) | 0x00);
    checksum += data;
    // length
    RXTXREG = htons(data = 20 + 12 + len);
    checksum += data;
    // identifier
    RXTXREG = htons(data = 0);
    checksum += data;
    // fragment offset
    RXTXREG = htons(data = 0);
    checksum += data;
    // TTL, UDP protocol
    RXTXREG = htons(data = (255U << 8) | 17U);
    checksum += data;

    checksum += (htonl(cs8900if_netif->ip_addr.addr) & 0xffff0000U) >> 16;
    checksum += htonl(cs8900if_netif->ip_addr.addr) & 0x0000ffffU;
    checksum += 0xc0a8U;
    checksum += 0x0001U;
    checksum += 2; // LW: kludge/hack: checksum calculation seems to be wrong somehow
    // LW: this seems (?) to fix it
    // checksum
    RXTXREG = htons(~checksum);

    // source IP
    RXTXREG = htons((htonl(cs8900if_netif->ip_addr.addr) & 0xffff0000U) >> 16);
    // source IP
    RXTXREG = htons(htonl(cs8900if_netif->ip_addr.addr) & 0x0000ffffU);
    // destination IP
    RXTXREG = htons(0xc0a8U);
    // destination IP
    RXTXREG = htons(0x0001U);
    // source port 3000
    RXTXREG = htons(3000U);
    // destination port 3000
    RXTXREG = htons(3000U);
    // UDP length
    RXTXREG = htons(len);
    // UDP checksum
    RXTXREG = htons(0);
    for (i = 0; i < len; i += 2)
    {
      RXTXREG = htons((p[i] << 8) | p[i + 1]);
    }
        while (i < 60)
        {
      RXTXREG = 0;
            i += 2;
        }
  }
}

void cs8900_init_debug()
{
  leds_off();

  // set RESET bit
  PACKETPP = CS_PP_SELFCTL;
  PPDATA = 0x0055U;

  // { the RESET bit will be cleared by the cs8900a
  //   as a result of the reset }
  // RESET bit cleared?
  while((PPDATA & 0x0040U) != 0); // TODO: add timeout

  // { after full initialization of the cs8900a
  //   the INITD bit will be set }

  PACKETPP = CS_PP_SELFTEST;
  // INITD bit still clear?
  while ((PPDATA & 0x0080U) == 0); // TODO: add timeout
  // { INITD bit is set }

  // Set MAC address
  PACKETPP = CS_PP_IA1;
  PPDATA = (u16_t)0x00 | ((u16_t)0x03 << 8U);
  PACKETPP = CS_PP_IA2;
  PPDATA = (u16_t)0x41 | ((u16_t)0x00 << 8U);
  PACKETPP = CS_PP_IA3;
  PPDATA = (u16_t)0x00 | ((u16_t)0x00 << 8U);

  // accept valid unicast or broadcast frames
  PACKETPP = CS_PP_RXCTL;
  PPDATA = (0x0005U | 0x0800U/*broadcast*/ | 0x0400U/*individual*/ | 0x0100U/*RxOK*/);

  // enable receive interrupt
  PACKETPP = CS_PP_RXCFG;
  PPDATA = (0x0003U | 0x0100U/*RXIRQ*/);

  // disable transmit interrupt (is default)
  PACKETPP = CS_PP_TXCFG;
  PPDATA = (0x0007U | 0);

  // use interrupt number 0
  PACKETPP = CS_PP_INTNUM;
  PPDATA = (0x0000U);

  // generate interrupt event on:
  // - the RxMISS counter reaches 0x200, or
  // - a received frame is lost
  PACKETPP = CS_PP_BUFCFG;
  PPDATA = (0x000bU |
#if (CS8900_STATS > 0) // interrupt before counter overflow
  (0x2000U/*MissOvfloiE*/ | 0x1000U/*TxColOvfloiE*/) |
#endif
#if (CS8900_STATS > 1) // interrupt on counter increment
  (0x0400U/*RxMissiE*/) |
#endif
  0x0000U);

  // enable interrupt generation
  PACKETPP = CS_PP_BUSCTL;
  PPDATA = (0x0017U | 0x8000U/*EnableIRQ*/);

  // enable:
  // - receiver
  // - transmitter
  PACKETPP = CS_PP_LINECTL;
  PPDATA = (0x0013U | 0x0080U/*SerTxOn*/ | 0x0040U/*SerRxOn*/);
}
#endif

/**
 * Service the CS8900.
 *
 * Can be called in a polling manner, or only after the CS8900 has raised
 * an interrupt request.
 */
void cs8900if_poll(struct netif *netif)
{
    int irq_status = ISQ;

    // see if link is up
    PACKETPP = CS_PP_LINESTATUS;
    if ( (PPDATA & 0x0080U/*LinkOK*/) != 0 )
    {
        if ( netif_is_link_up(netif) == 0 )
        {
            netif_set_link_up(netif);
        }
    } else if ( netif_is_link_up(netif) != 0 )
    {
        netif_set_link_down(netif);
    }
    //cs8900if_input(netif);
}

