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

#include "lwip/debug.h"
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/sys.h"
#include "netif/etharp.h"
#include "netif/cs8900if.h"
#ifdef SNMP
    #include "snmp.h"
    #include "mib2if.h"
#endif




////////////////////////////////////////////////////////////////////////////////
//
// internal structure definitions
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __CS8900_USE_TX_QUEUE

    #ifndef __CS8900_USE_CRITICAL_SECTION
        #error "__CS8900_USE_CRITICAL_SECTION should be enabled to use TX QUEUE"
    #endif

    #include "app/list.h"

    #define CS8900_MAX_ETH_FRAME_SIZE   1532      // 4 byte alignment with some room
    #define CS8900_MAX_TX_QUEUE_SIZE    16

typedef struct {
    struct list_head   le;
    u32_t              len;
    u8_t               buffer[CS8900_MAX_ETH_FRAME_SIZE];
} CS8900TXBuf;

static volatile u8_t    _tx_busy;
#endif

////////////////////////////////////////////////////////////////////////////////
//
// module private prototypes
//
////////////////////////////////////////////////////////////////////////////////
static void cs8900_service(struct netif *netif);
static void cs8900_reset(void);
static void cs8900_set_macaddr(struct netif *netif);
static void cs8900_chip_init(struct netif *netif);
static void cs8900_init(struct netif *netif);
static err_t cs8900_output(struct netif *netif, struct pbuf *p);
static struct pbuf* cs8900_input(struct netif *netif);
static void cs8900if_input(struct netif *netif);

#ifdef __CS8900_DEBUG__
static void cs8900_debug(void);
#endif

#ifdef __CS8900_USE_CRITICAL_SECTION
static void cs8900_critical_section_init(void);
static void cs8900_enter_critical(void);
static void cs8900_leave_critical(void);
#endif

#ifdef __CS8900_USE_TX_QUEUE
static void cs8900_init_tx_queue(void);
static void cs8900_copy_pbuf_to_tx_buffer(struct pbuf *p, CS8900TXBuf *txbuf);
static void cs8900_tx_txbuf(struct cs8900if *cs8900if, CS8900TXBuf *txbuf);
static int cs8900_copy_pbuf_to_tx_queue(struct pbuf *p);
static CS8900TXBuf* cs8900_get_next_txbuf(void);
static void cs8900_free_tx_buf(CS8900TXBuf *txbuf);
static void cs8900_serve_tx_ready(struct cs8900if *cs8900if);
#endif

////////////////////////////////////////////////////////////////////////////////
//
// module private variables
//
////////////////////////////////////////////////////////////////////////////////
static unsigned char sector16[30] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
static unsigned char *eth_oui = &sector16[0];
static struct cs8900if    _g_cs8900_if;

#ifdef __CS8900_USE_CRITICAL_SECTION
static sys_sem_t    _cs8900_critical_lock;
#endif

#ifdef __CS8900_USE_TX_QUEUE
static CS8900TXBuf          _tx_buffers[CS8900_MAX_TX_QUEUE_SIZE];
static struct list_head     _free_tx_queue;
static struct list_head     _tx_queue;
#endif
volatile int         _num_pkts_in_tx_queue = 0;      // just for debug

////////////////////////////////////////////////////////////////////////////////
//
// utilities to access CS8900 registers
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief read from cs8900 registers
 * 
 * @param[out] regno register to read value from
 * @return register value
 */
static inline u16_t
cs8900_readreg(u16_t regno) {
    u16_t   t;

    PACKETPP = regno;
    t = PPDATA;
    return t;
}

/**
 * @brief write to cs8900 registers
 * 
 * @param[out] regno register to write value to
 * @param[out] value to write to register
 * @return none
 */
static inline void
cs8900_writereg(u16_t regno, u16_t value) {
    PACKETPP = regno;
    PPDATA = value;
}

/*
 * @brief initialize cs8900 stats to zero
 *
 * @param[in] cs8900if cs8900if structure
 * @return none
 */
static inline void
cs8900_reset_stats(struct cs8900if *cs8900if) {
    cs8900if->loop_cnt            = 0;
    cs8900if->interrupts          = 0;
    cs8900if->missed              = 0;
    cs8900if->collisions          = 0;
    cs8900if->tx_packets          = 0;
    cs8900if->tx_bytes            = 0;
    cs8900if->rx_packets          = 0;
    cs8900if->rx_bytes            = 0;
    cs8900if->rx_len_zero         = 0;
    cs8900if->rx_pbuf_alloc_fail  = 0;
    cs8900if->rx_lwip_input_err   = 0;
    cs8900if->tx_line_status_err  = 0;
    cs8900if->tx_timeout          = 0;
    cs8900if->loop_exit_by_limit  = 0;
    cs8900if->tx_buffering        = 0;

    cs8900if->tx_errors           = 0;
    cs8900if->tx_carrier_errors   = 0;
    cs8900if->tx_heartbeat_errors = 0;
    cs8900if->tx_window_errors    = 0;
    cs8900if->tx_aborted_errors   = 0;
    cs8900if->tx_underrun         = 0;

    cs8900if->rx_not_ok           = 0;
    cs8900if->rx_length_errors    = 0;
    cs8900if->rx_crc_errors       = 0;
    cs8900if->rx_frame_errors     = 0;
}

#ifdef __CS8900_USE_TX_QUEUE
////////////////////////////////////////////////////////////////////////////////
//
// TX Queue Management
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize tx queue for cs8900
 * 
 * @param none
 * @return none
 */
static void
cs8900_init_tx_queue(void) {
    CS8900TXBuf *tx_buf;

    INIT_LIST_HEAD(&_tx_queue);
    INIT_LIST_HEAD(&_free_tx_queue);

    _num_pkts_in_tx_queue = 0;

    for ( int i = 0; i < CS8900_MAX_TX_QUEUE_SIZE; i++ ) {
        tx_buf = &_tx_buffers[i];

        INIT_LIST_HEAD(&tx_buf->le);
        list_add_tail(&tx_buf->le, &_free_tx_queue);
    }
}

/**
 * @brief copies pbuf to tx buffer
 *
 * @param[in] p pbuf to copy from
 * @param[in] txbuf tx buffer to copy pbuf to
 *
 * @return none
 */
static void
cs8900_copy_pbuf_to_tx_buffer(struct pbuf *p, CS8900TXBuf *txbuf) {
    struct pbuf *q;
  u16_t         *buf_ptr  = (u16_t *)txbuf->buffer;

  for ( q = p; q != NULL; q = q->next ) {
    register u16_t i;
    register u16_t *ptr = (u16_t *)q->payload;

    for(i = 0; i < q->len; i += 2)
    {
      *buf_ptr++ = *ptr++;
    }
  }

    txbuf->len = p->tot_len;
}

/**
 * @brief sends txbuf to cs8900 for tx
 *        Note: BUSSTATUS should be tx ready before calling this function
 *
 * @param[in] cs8900if cs8900 if to send packet to
 * @param[in] txbuf tx buffer to transmit
 *
 * @return none
 */
static void
cs8900_tx_txbuf(struct cs8900if *cs8900if, CS8900TXBuf *txbuf) {
    register int   i;
  register u16_t *buf_ptr  = (u16_t *)txbuf->buffer;

    for (i = 0; i < txbuf->len; i++ ) {
        RXTXREG = *buf_ptr++;
    }
    cs8900if->tx_bytes += txbuf->len;
    cs8900if->tx_packets++;

#ifdef SNMP
    if_add_ifOutOctets(p->tot_len);
#endif
}


/**
 * @brief extracts txbuf from free queue, copies pbuf data
 *        and puts the txbuf to txqueue for tx
 *        XXX : this should be called with _cs8900_critical_lock held
 *
 * @param p pbuf to copy to
 * @return 0 on success, -1 on failure
 */
static int
cs8900_copy_pbuf_to_tx_queue(struct pbuf *p) {
    CS8900TXBuf *txbuf;

    if ( list_empty(&_free_tx_queue) ) {
        // no free tx buffer available
        return -1;
    }

    txbuf = list_first_entry(&_free_tx_queue, CS8900TXBuf, le);
    list_del_init(&txbuf->le);

    cs8900_copy_pbuf_to_tx_buffer(p, txbuf);

    list_add_tail(&txbuf->le, &_tx_queue);

    _num_pkts_in_tx_queue++;
    return 0;
}

/**
 * @brief gets next tx buffer to tx from txqueue
 *        XXX : this should be called with driver lock held
 *
 * @return next txbuf from tx queue
 */
static CS8900TXBuf*
cs8900_get_next_txbuf(void) {
    CS8900TXBuf *txbuf;

    if ( list_empty(&_tx_queue) ) {
        return NULL;
    }

    txbuf = list_first_entry(&_tx_queue, CS8900TXBuf, le);

    return txbuf;
}

/**
 * @brief removex txbuf from txqueue and puts it back to free list
 *
 * @param[in] txbuf tx buffer to free
 *
 * @return none
 */
static void
cs8900_free_tx_buf(CS8900TXBuf *txbuf) {
    // remove from txqueue
    list_del_init(&txbuf->le);

    // add it to free queue
    list_add_tail(&txbuf->le, &_free_tx_queue);
    _num_pkts_in_tx_queue--;
}
#endif

////////////////////////////////////////////////////////////////////////////////
//
// for CS8900 RX/TX Locking
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __CS8900_USE_CRITICAL_SECTION
/**
 * @brief initialize critical section to prevent simultaneous rx/tx
 * @return none
 */
static void
cs8900_critical_section_init(void) {
    if ( sys_sem_new(&_cs8900_critical_lock, 1) != ERR_OK ) {
        // we are fucked up.
        // what is the best way to debug this?
        // just do infite loop so we can find this bug
        while ( 1 ) {}
    }
}

/**
 * @brief enter cs8900 critical section to prevent simultaneous rx/tx
 * @return none
 */
static void
cs8900_enter_critical(void) {
    sys_sem_wait(&_cs8900_critical_lock);
}

/**
 * @brief leave cs8900 critical section to prevent simultaneous rx/tx
 * @return none
 */
static void
cs8900_leave_critical(void) {
    sys_sem_signal(&_cs8900_critical_lock);
}
#endif

////////////////////////////////////////////////////////////////////////////////
//
// utilities for debugging
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief simple debug routine to dump cs8900 registers.
 *        segger jlink is quite inconvenient to print out debug messages. so
 *        instead of doing that, put a break point here and inspect reach value.
 * 
 * @return none
 */
#ifdef __CS8900_DEBUG__
static void
cs8900_debug(void) {
    u16_t   t;

    t = SWAP_U16(cs8900_readreg(CS_PP_EISA));       // EISA registration number
    t = SWAP_U16(cs8900_readreg(CS_PP_PRODID));     // product ID including revision
    t = cs8900_readreg(CS_PP_IOBASE);               // IO base
    t = cs8900_readreg(CS_PP_INTNUM);               // interrupt number
    t = cs8900_readreg(CS_PP_DMACHANN);             // dma channel number
    t = cs8900_readreg(CS_PP_EEPROM_CMD);           // eeprom command register

    t = cs8900_readreg(CS_PP_IA1);                  // mac addr 0/1
    t = cs8900_readreg(CS_PP_IA2);                  // mac addr 2/3
    t = cs8900_readreg(CS_PP_IA3);                  // mac addr 4/5


    t = cs8900_readreg(CS_PP_RXCFG);
    t = cs8900_readreg(CS_PP_TXCFG);
    t = cs8900_readreg(CS_PP_BUFCFG);
    t = cs8900_readreg(CS_PP_BUSCTL);

    // t = cs8900_readreg(CS_PP_ISQ);
    t = cs8900_readreg(CS_PP_RXEVENT);
    t = cs8900_readreg(CS_PP_TX_EVENT);
    t = cs8900_readreg(CS_PP_BUF_EVENT);
    t = cs8900_readreg(CS_PP_LINESTATUS);

    t = cs8900_readreg(CS_PP_SELFTEST);
    t = cs8900_readreg(CS_PP_BUSSTATUS);
    (void)t;  // hate warnings
}
#endif

////////////////////////////////////////////////////////////////////////////////
//
// chip initialization utilities
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief resets cs8900 by asserting POWER_ON_RESET through S/W register
 * 
 * @return none
 */
static void cs8900_reset(void) {
    int StartTime = OS_Time;
#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_enter_critical();
#endif
    cs8900_writereg(CS_PP_SELFCTL, POWER_ON_RESET);
    OS_Delay(30);

    while ( (cs8900_readreg(CS_PP_SELFTEST) & INIT_DONE) == 0 &&
            ((OS_Time - StartTime) < 1000) ) {
        // wait for reset complete or timeout
    }

    cs8900_writereg(CS_PP_RXCFG,    0);
    cs8900_writereg(CS_PP_TXCFG,    0);
    cs8900_writereg(CS_PP_BUFCFG,   0);
    cs8900_writereg(CS_PP_BUSCTL,   0);
    cs8900_writereg(CS_PP_LINECTL,  0);
#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_leave_critical();
#endif
}

/**
 * @brief sets predefined mac address to cs8900.
 * 
 * @param[in] netif lwip network interface to work with
 * @return none
 */
static void
cs8900_set_macaddr(struct netif *netif) {
    struct cs8900if *cs8900if;

    cs8900if = (struct cs8900if *)netif->state;
    cs8900_writereg(CS_PP_IA1, ((u16_t)cs8900if->ethaddr->addr[0] | (u16_t)(cs8900if->ethaddr->addr[1] << 8U)));
    cs8900_writereg(CS_PP_IA2, ((u16_t)cs8900if->ethaddr->addr[2] | (u16_t)(cs8900if->ethaddr->addr[3] << 8U)));
    cs8900_writereg(CS_PP_IA3, ((u16_t)cs8900if->ethaddr->addr[4] | (u16_t)(cs8900if->ethaddr->addr[5] << 8U)));
}

/**
 * @brief initialize cs8900
 * 
 * @param[in] netif lwip network interface to initialize with
 * @return none
 */
static void
cs8900_chip_init(struct netif *netif) {

    u16_t   t;

    cs8900_writereg(CS_PP_INTNUM, 0x04);

    cs8900_writereg(CS_PP_RXCFG, RX_OK_ENBL | RX_CRC_ERROR_ENBL);
    cs8900_writereg(CS_PP_RXCTL, DEF_RX_ACCEPT);

#ifdef __CS8900_USE_TX_QUEUE
    cs8900_writereg(CS_PP_TXCFG,  TX_LOST_CRS_ENBL    |
                    TX_SQE_ERROR_ENBL   |
                    TX_OK_ENBL          |
                    TX_LATE_COL_ENBL    |
                    TX_JBR_ENBL         |
                    TX_ANY_COL_ENBL     |
                    TX_16_COL_ENBL);
    //cs8900_writereg(CS_PP_TXCFG,  0);
#else
    cs8900_writereg(CS_PP_TXCFG,  0);
#endif

#if __CS8900_USE_FULL_DUPLEX
    cs8900_writereg(CS_PP_TESTCTL, 0x4000);
#endif

#if 1
    t = cs8900_readreg(CS_PP_SELFCTL);
    if ( (t & (HCB1 | HCB1_ENBL)) == (HCB1 | HCB1_ENBL) ) {
        cs8900_writereg(CS_PP_SELFCTL, HCB1_ENBL | HCB1);
    } else {
        cs8900_writereg(CS_PP_SELFCTL, HCB1_ENBL);
    }
    OS_Delay(50);
#endif

#ifdef __CS8900_USE_TX_QUEUE
    cs8900_writereg(CS_PP_BUFCFG, (READY_FOR_TX_ENBL           |
                                   TX_UNDERRUN_ENBL            |
                                   RX_MISS_COUNT_OVRFLOW_ENBL  |
                                   TX_COL_COUNT_OVRFLOW_ENBL));
#else
    cs8900_writereg(CS_PP_BUFCFG, (
                                   RX_MISS_COUNT_OVRFLOW_ENBL |
                                   TX_COL_COUNT_OVRFLOW_ENBL));
#endif

    cs8900_writereg(CS_PP_BUSCTL, ENABLE_IRQ);
    cs8900_writereg(CS_PP_LINECTL, SERIAL_RX_ON | SERIAL_TX_ON);

    // clear isq before enabling interrupts
    do {
        t = ISQ;
    } while ( t != 0 );

    cs8900_writereg(CS_PP_INTNUM, 0xfff8);
}

/**
 * @brief CS8900 chip initializer. first resets the chip, then sets
 *        mac address, then set up the chip so we can send/receive
 *        packets and interrupts.
 * 
 * @param[in] netif lwip network interface to initialize with
 * @return none
 */
static void
cs8900_init(struct netif *netif) {
    struct cs8900if *cs8900if = (struct cs8900if *)netif->state;

    cs8900_reset();
#ifdef __CS8900_DEBUG__
    cs8900_debug();
#endif
    cs8900_set_macaddr(netif);
    cs8900_chip_init(netif);
#ifdef __CS8900_DEBUG__
    cs8900_debug();
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
// CS8900 TX
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief mark tx busy status
 *
 * @param[in] tx_busy, 0 for not busy, 1 for busy
 * 
 * @return none
 */
static inline void
cs8900_set_tx_busy(u8_t tx_busy) {
    _tx_busy = tx_busy;
}

/**
 * @brief check tx busy status
 *
 * @return 1 if busy, 0 if not busy
 */
static inline u8_t
cs8900_is_tx_busy(void) {
    return _tx_busy;
}

/**
 * @brief set tx command for cs8900
 * 
 * @param[in] len packet lenght to tx
 *
 * @return none
 */
static inline void
cs8900_set_tx_bid(u16_t len) {
    cs8900_set_tx_busy(1);
    TXCMD     = CS8900_DEFAULT_TX_CMD;
    TXLENGTH  = len;
}

/**
 * @brief check if tx is possible
 *
 * @return 1 if possible, 0 if not
 */
static inline int
cs8900_check_for_tx_ready(void) {
    if ( (cs8900_readreg(CS_PP_BUSSTATUS) & READY_FOR_TX_NOW) == 0 ) {
        return 0;
    }
    return 1;
}

/**
 * @brief check ethernet line status
 *
 * @return 1 if link is up, 0 if link is down
 */
static inline int
cs8900_check_line_status(void) {
    if ( (cs8900_readreg(CS_PP_LINESTATUS) & 0x0080U) == 0 ) {
        return 0;
    }
    return 1;
}

/**
 * @brief write pbuf to cs8900
 *
 * @param[in] cs8900if cs8900if to send pbuf to
 * @param[in] p pbuf to tx
 * 
 * @return none
 */
static void
cs8900_write_pbuf(struct cs8900if *cs8900if, struct pbuf *p) {
    struct pbuf *q;

    for ( q = p; q != NULL; q = q->next ) {
        register u16_t i;
        register u16_t *ptr = (u16_t *)q->payload;

        for ( i = 0; i < q->len; i += 2 ) {
            RXTXREG = *ptr++;
        }

        cs8900if->tx_bytes += q->len;

#ifdef SNMP
        if_add_ifOutOctets(p->tot_len);
#endif
    }
}

#ifndef __CS8900_USE_TX_QUEUE
/**
 * @brief sends packet to cs8900.
 *        This one is called mostly in LwIP tcp stack task context.
 *        Also during initialization, this is called in network start-up
 *        task context for graduitous ARP and DHCP.
 *        This is the TX core
 * 
 * @param[in] netif lwip netif to send packet to
 * @param[in] p pbuf packet to send to cs8900
 * @return err_t status indicating tx success or failure
 */
static err_t
cs8900_output(struct netif *netif, struct pbuf *p) {
    struct cs8900if *cs8900if = (struct cs8900if *)netif->state;
    int                 tries = 0;

#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_enter_critical();
#endif

    if ( cs8900_check_line_status() == 0 ) {
        cs8900if->tx_line_status_err++;
        goto error;
    }

    cs8900_set_tx_bid(p->tot_len);

    while ( cs8900_check_for_tx_ready() == 0 && (tries++ < 100) ) {
        //OS_Delay(50);
        // nada
    }

    if ( tries < 100 ) {
        cs8900_write_pbuf(cs8900if, p);
        cs8900if->tx_packets++;
    } else {
        TXLENGTH = 0;
        cs8900if->tx_timeout++;
    }

#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_leave_critical();
#endif

    return ERR_OK;

error:
#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_leave_critical();
#endif
    return ERR_CONN;
}

#else

/**
 * @brief sends packet to cs8900.
 *        This one is called mostly in LwIP tcp stack task context.
 *        Also during initialization, this is called in network start-up
 *        task context for graduitous ARP and DHCP.
 *        This is the TX core
 * 
 * @param[in] netif lwip netif to send packet to
 * @param[in] p pbuf packet to send to cs8900
 * @return err_t status indicating tx success or failure
 */
static err_t
cs8900_output(struct netif *netif, struct pbuf *p) {
    struct cs8900if *cs8900if = (struct cs8900if *)netif->state;
    err_t               ret;

    cs8900_enter_critical();

    if ( cs8900_check_line_status() == 0 ) {
        cs8900if->tx_line_status_err++;
        goto error;
    }

    if ( cs8900_is_tx_busy() ) {
        // in case tx busy, just queue the packet
        cs8900if->tx_buffering++;
        if ( cs8900_copy_pbuf_to_tx_queue(p) == 0 ) {
            ret = ERR_OK;
        } else {
            cs8900if->tx_errors++;
            ret = ERR_CONN;
        }

        cs8900_leave_critical();
        return ret;
    }

    cs8900_set_tx_bid(p->tot_len);

    ret = ERR_OK;

    if ( cs8900_check_for_tx_ready() == 0 ) {
        // can't tx right away.
        // put pbuf to tx queue
        if ( cs8900_copy_pbuf_to_tx_queue(p) != 0 ) {
            cs8900if->tx_errors++;
            ret = ERR_CONN;
        } else {
            cs8900if->tx_buffering++;
        }
    } else {
        cs8900_write_pbuf(cs8900if, p);
        cs8900if->tx_packets++;
    }

#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_leave_critical();
#endif

    return ret;

error:
#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_leave_critical();
#endif
    return ERR_CONN;
}

/**
 * @brief handle tx ready event.
 *        if there is a packet in the tx queue, extracts it out and sends it to cs8900
 *        if there is next packet waiting, prepare for another tx ready event
 *
 * @param[in] cs8900if cs8900if that tx ready event originates from
 * 
 * @return none
 */
static void
cs8900_serve_tx_ready(struct cs8900if *cs8900if) {
    CS8900TXBuf *txbuf;

    txbuf = cs8900_get_next_txbuf();
    if ( txbuf == NULL ) {
        return;
    }

    cs8900_tx_txbuf(cs8900if, txbuf);
    cs8900_free_tx_buf(txbuf);

#if 0
    while((txbuf = cs8900_get_next_txbuf()) != NULL){
        cs8900_set_tx_bid(txbuf->len);

        if(!cs8900_check_for_tx_ready()){
            // can't tx right away
            return;
        }
        cs8900_tx_txbuf(cs8900if, txbuf);
        cs8900_free_tx_buf(txbuf);
    }
#endif
}

static void cs8900_serve_tx_complete(struct cs8900if *cs8900if) {
    // bid for tx
    CS8900TXBuf *txbuf;

    cs8900_set_tx_busy(0);

    txbuf = cs8900_get_next_txbuf();
    if ( txbuf == NULL ) {
        return;
    }

    cs8900_set_tx_bid(txbuf->len);

    if ( !cs8900_check_for_tx_ready() ) {
        // can't tx right away
        // wait for tx ready interrupt
        return;
    }

    cs8900_tx_txbuf(cs8900if, txbuf);
    cs8900_free_tx_buf(txbuf);
}
#endif

////////////////////////////////////////////////////////////////////////////////
//
// CS8900 RX
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief counts rx errors
 *
 * @param[in] status rx event status
 * @param[in] cs8900if cs8900 network interface structure
 *
 * @reutrn none
 */
static void cs8900_count_rx_errors(u16_t status, struct cs8900if *cs8900if) {
    cs8900if->rx_not_ok++;

    if ( status & RX_RUNT ) cs8900if->rx_length_errors++;

    if ( status & RX_EXTRA_DATA ) cs8900if->rx_length_errors++;

    if ( (status & RX_CRC_ERROR) && !(status & (RX_EXTRA_DATA | RX_RUNT)) ) cs8900if->rx_crc_errors++;

    if ( status & RX_DRIBBLE ) cs8900if->rx_frame_errors++;
}

/**
 * @brief reads received packet from cs8900 and and
 *        creates new pbuf
 *        This is the RX core.
 * 
 * @param[in] netif lwip netif to receive packet from
 * @return allocated pbuf with received data or NULL in case of error 
 *  
 * Optimize bug here. When optimize level > 3 
 */

static struct pbuf* cs8900_input(struct netif *netif) {
    struct pbuf  *p = 0,
                      *q;
  u16_t               len = 0,
                      event_type,
                      i;
  u16_t*              ptr;
  struct cs8900if *cs8900if = (struct cs8900if *)netif->state;

    // read RxStatus
  event_type  = RXTXREG;
  len         = RXTXREG;

    if ( (event_type & RX_OK) == 0 ) {
        cs8900_writereg(CS_PP_RXCFG, cs8900_readreg(CS_PP_RXCFG) | SKIP_1);
        cs8900_count_rx_errors(event_type, cs8900if);
        return NULL;
    }

    // positive length?
    if ( len > 0 ) {
        cs8900if->rx_packets++;
        cs8900if->rx_bytes += len;
        p = pbuf_alloc(PBUF_LINK, len, PBUF_POOL);

        if ( p != 0) {
            for ( q = p; q != 0; q = q->next ) {
        ptr = q->payload;
        for (i = 0; i < (q->len + 1) / 2; i++ ) {
                    *ptr = RXTXREG;
                    ptr++;
                }
            }
        } else {
            cs8900if->rx_pbuf_alloc_fail++;
      return NULL;
    }
    } else {
        cs8900if->rx_len_zero++;
    }
    return p;
}

/**
 * @brief reads received packet from CS8900, allocate pbuf and initialize it.
 *        If all goes ok, it tries to send up the pbuf to LwIP stack.
 * 
 * @param[in] netif lwip netif to receive packet from
 * @return none
 */
static void cs8900if_input(struct netif *netif) {
    struct pbuf *p;
    struct cs8900if *cs8900if = (struct cs8900if *)netif->state;

    p = cs8900_input(netif);

    if ( p == NULL ) {
        return;
    }

    if ( netif->input(p, netif) != ERR_OK ) {
        cs8900if->rx_lwip_input_err++;
        pbuf_free(p);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// CS8900 Interrupt Handling
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief this is the IRQ handling core for CS8900.
 *        It just tries to read all the events from CS8900 event queue and handle
 *        rx/tx events until there is no more event to process.
 * 
 * @param[in] netif to read events from
 * @return none
 */
static void cs8900_service(struct netif *netif) {
    struct cs8900if *cs8900if = (struct cs8900if *)(netif->state);
  u16_t irq_status = 0x0000U,
                    event_source,
                    tmp;

  cs8900if->loop_cnt++;
#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_enter_critical();
#endif

    irq_status = ISQ;

  while (irq_status) {
        event_source = irq_status & 0x003F;

        switch ( event_source ) {
        case ISQ_RECEIVER_EVENT:
            cs8900if_input(netif);
            break;
        case ISQ_TRANSMITTER_EVENT:
            cs8900_serve_tx_complete(cs8900if);
            if ( (irq_status & (TX_OK |
                                TX_LOST_CRS |
                                TX_SQE_ERROR |
                                TX_LATE_COL |
                                TX_16_COL)) != TX_OK ) {
                if ( (irq_status & TX_OK) == 0 ) cs8900if->tx_errors++;
                if ( irq_status & TX_LOST_CRS ) cs8900if->tx_carrier_errors++;
                if ( irq_status & TX_SQE_ERROR ) cs8900if->tx_heartbeat_errors++;
                if ( irq_status & TX_LATE_COL ) cs8900if->tx_window_errors++;
                if ( irq_status & TX_16_COL ) cs8900if->tx_aborted_errors++;
            }
            break;

        case ISQ_BUFFER_EVENT:
#ifdef __CS8900_USE_TX_QUEUE
            if ( irq_status & READY_FOR_TX ) {
                cs8900_serve_tx_ready(cs8900if);
            }

            if ( irq_status & TX_UNDERRUN ) {
                cs8900if->tx_underrun++;
                cs8900_serve_tx_complete(cs8900if);
            }
#endif
            break;
#if 1
        case ISQ_RX_MISS_EVENT:
            cs8900if->missed += (irq_status >> 6);
            break;
        case ISQ_TX_COL_EVENT:
            cs8900if->collisions += (irq_status >> 6);
            break;
#endif
        }
        irq_status = ISQ;
    }

    PACKETPP = CS_PP_RXMISS;
    tmp = (PPDATA >> 6);
    cs8900if->missed += tmp;

    PACKETPP = CS_PP_TXCOL;
    tmp = (PPDATA >> 6);
    cs8900if->collisions += tmp;
#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_leave_critical();
#endif

#ifdef __NET_USE_ACTIVE_HIGH_INTERRUPT__
    rEINTMASK &= ~BIT_SUB_EINT16;
// unmask network interrupt
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
// module public interfaces
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief just a public interface to handle CS8900 events in cs8900 task
 *        pretty much stupid legacy code but I leave it here 
 * 
 * @param[in] netif lwip to deal with
 * @return none
 */
void
cs8900if_service(struct netif *netif) {
    cs8900_service(netif);
}

/**
 * @brief tries to deplete CS8900 event queue
 *        It's called during cs8900 driver task startup 
 *        and runs with interrupts disabled.
 * 
 * @return none
 */
void
cs8900_deplete_event_queue(void) {
    u16_t   t;

    OS_IncDI();
    do {
        t = cs8900_readreg(CS_PP_ISQ);
    } while ( t != 0 );
    OS_DecRI();
}

/**
 * @brief public interface to initialize  CS8900 driver and chip.
 *        This is a callback function to LwIP network initialization code
 *        and called during LwIP network initialization in Network startup
 *         task context
 * @param[in] netif lwip to deal with
 * @return err_t indicating success or failure
 */
err_t
cs8900if_init(struct netif *netif) {
    struct cs8900if *cs8900if;

    //cs8900if = mem_malloc(sizeof(struct cs8900if));
    cs8900if = &_g_cs8900_if;
    if ( cs8900if == NULL ) return ERR_MEM;

    netif->state      = cs8900if;
    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;
    netif->output     = etharp_output;
    netif->linkoutput = cs8900_output;

    cs8900if->ethaddr       = (struct eth_addr *)&(netif->hwaddr[0]);
    cs8900_reset_stats(cs8900if);

    netif->hwaddr_len       = ETHARP_HWADDR_LEN;
    netif->mtu              = 1500;
    netif->flags            = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

#ifdef __CS8900_USE_CRITICAL_SECTION
    cs8900_critical_section_init();
#endif

#ifdef __CS8900_USE_TX_QUEUE
    cs8900_init_tx_queue();
#endif

    OS_IncDI();
    cs8900_init(netif);
    {
        extern void StartNetDriverTask(void);

        StartNetDriverTask();
    }
    OS_DecRI();

    return ERR_OK;
}
