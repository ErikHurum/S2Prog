#ifndef __NETIF_CS8900IF_H__
#define __NETIF_CS8900IF_H__

#include "lwip/netif.h"

struct cs8900if
{
  struct eth_addr*      ethaddr;
  volatile u32_t        loop_cnt;
  volatile u32_t        interrupts;
  volatile u32_t        missed;
  volatile u32_t        collisions;
  volatile u32_t        tx_packets;
  volatile u32_t        tx_bytes;
  volatile u32_t        rx_packets;
  volatile u32_t        rx_bytes;
  volatile u32_t        sentbytes;
  volatile u32_t        rx_len_zero;
  volatile u32_t        rx_pbuf_alloc_fail;
  volatile u32_t        rx_lwip_input_err;
  volatile u32_t        tx_line_status_err;
  volatile u32_t        tx_timeout;
  volatile u32_t        loop_exit_by_limit;
  volatile u32_t        tx_buffering;

  volatile u32_t        tx_errors;
  volatile u32_t        tx_carrier_errors;
  volatile u32_t        tx_heartbeat_errors;
  volatile u32_t        tx_window_errors;
  volatile u32_t        tx_aborted_errors;
  volatile u32_t        tx_underrun;

  volatile u32_t        rx_not_ok;
  volatile u32_t        rx_length_errors;
  volatile u32_t        rx_crc_errors;
  volatile u32_t        rx_frame_errors;
};

#ifdef __cplusplus
extern "C" {
#endif

extern err_t cs8900if_init(struct netif *netif);
extern void cs8900if_service(struct netif *);
//extern u16_t cs8900_readreg(u16_t regno);
//extern void cs8900_writereg(u16_t regno, u16_t value);
extern void cs8900_count_rx_errors(u16_t status, struct cs8900if *cs8900if);

#ifdef __cplusplus
}
#endif




#define __CS8900_USE_CRITICAL_SECTION       0
#define __CS8900_USE_TX_QUEUE               1 
#define __CS8900_USE_FULL_DUPLEX            0
////////////////////////////////////////////////////////////////////////////////
//
// internal defines
//
////////////////////////////////////////////////////////////////////////////////
#define IFNAME0 'e'
#define IFNAME1 'n'

#define MEM_BASE 0x29000000
#define IO_BASE  0x300
#define INT_NR   0x10

#define RXTXREG  *((volatile u16_t *)(MEM_BASE + IO_BASE))
#define TXCMD    *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x04))
#define TXLENGTH *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x06))
#define ISQ      *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x08))
#define PACKETPP *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x0A))
#define PPDATA   *((volatile u16_t *)(MEM_BASE + IO_BASE + 0x0C))

#define  CS_PP_EISA        0x0000          // EISA Registration number of CS8900
#define  CS_PP_PRODID      0x0002          // Product ID Number
#define  CS_PP_IOBASE      0x0020          // I/O Base Address
#define  CS_PP_INTNUM      0x0022          // Interrupt number (0,1,2, or 3)
#define  CS_PP_DMACHANN    0x0024          // DMA channel number
#define  CS_PP_EEPROM_CMD  0x0040          // EEPROM Command Register
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

#define  CS_PP_ADD_PORT    0x000A
#define  CS_PP_DATA_PORT   0x000C

#define  CS_PP_RXSTATUS    0x0400          // Receive Status
#define  CS_PP_RXLEN       0x0402          // Receive Length
#define  CS_PP_RXFRAME     0x0404          // Receive Frame Location
#define  CS_PP_TXFRAME     0x0A00          // Transmit Frame Location

#define  POWER_ON_RESET    0x0040
#define  INIT_DONE         0x0080
#define  ENABLE_IRQ        0x8000
#define  MEMORY_ON         0x0400
#define  HCB0_ENBL         0x1000
#define  HCB1_ENBL         0x2000
#define  HCB0              0x4000
#define  HCB1              0x8000

/* PP_LineCTL - Line Control bit definition - Read/write */
#define  SERIAL_RX_ON     0x0040
#define  SERIAL_TX_ON     0x0080
#define  AUI_ONLY         0x0100
#define  AUTO_AUI_10BASET 0x0200
#define  MODIFIED_BACKOFF 0x0800
#define  NO_AUTO_POLARITY 0x1000
#define  TWO_PART_DEFDIS  0x2000
#define  LOW_RX_SQUELCH   0x4000

/* PP_RxCTL - Receive Control bit definition - Read/write */
#define  RX_IA_HASH_ACCEPT          0x0040
#define  RX_PROM_ACCEPT             0x0080
#define  RX_OK_ACCEPT               0x0100
#define  RX_MULTCAST_ACCEPT         0x0200
#define  RX_IA_ACCEPT               0x0400
#define  RX_BROADCAST_ACCEPT        0x0800
#define  RX_BAD_CRC_ACCEPT          0x1000
#define  RX_RUNT_ACCEPT             0x2000
#define  RX_EXTRA_DATA_ACCEPT       0x4000
//#define  RX_ALL_ACCEPT (RX_PROM_ACCEPT|RX_BAD_CRC_ACCEPT|RX_RUNT_ACCEPT|RX_EXTRA_DATA_ACCEPT)
/*  Default receive mode - individually addressed, broadcast, and error free */
#define  DEF_RX_ACCEPT (RX_IA_ACCEPT | RX_BROADCAST_ACCEPT | RX_OK_ACCEPT)

/* PP_RxCFG - Receive  Configuration and Interrupt Mask bit definition -  Read/write */
#define  SKIP_1                     0x0040
#define  RX_STREAM_ENBL             0x0080
#define  RX_OK_ENBL                 0x0100
#define  RX_DMA_ONLY                0x0200
#define  AUTO_RX_DMA                0x0400
#define  BUFFER_CRC                 0x0800
#define  RX_CRC_ERROR_ENBL          0x1000
#define  RX_RUNT_ENBL               0x2000
#define  RX_EXTRA_DATA_ENBL         0x4000

/* PP_TxCFG - Transmit Configuration Interrupt Mask bit definition - Read/write */
#define  TX_LOST_CRS_ENBL           0x0040
#define  TX_SQE_ERROR_ENBL          0x0080
#define  TX_OK_ENBL                 0x0100
#define  TX_LATE_COL_ENBL           0x0200
#define  TX_JBR_ENBL                0x0400
#define  TX_ANY_COL_ENBL            0x0800
#define  TX_16_COL_ENBL             0x8000

/* PP_BufCFG - Buffer Configuration Interrupt Mask bit definition - Read/write */
#define  GENERATE_SW_INTERRUPT      0x0040
#define  RX_DMA_ENBL                0x0080
#define  READY_FOR_TX_ENBL          0x0100
#define  TX_UNDERRUN_ENBL           0x0200
#define  RX_MISS_ENBL               0x0400
#define  RX_128_BYTE_ENBL           0x0800
#define  TX_COL_COUNT_OVRFLOW_ENBL  0x1000
#define  RX_MISS_COUNT_OVRFLOW_ENBL 0x2000
#define  RX_DEST_MATCH_ENBL         0x8000

#define  REVISON_BITS               0x1F00

#define  ISQ_RECEIVER_EVENT         0x04
#define  ISQ_TRANSMITTER_EVENT      0x08
#define  ISQ_BUFFER_EVENT           0x0c
#define  ISQ_RX_MISS_EVENT          0x10
#define  ISQ_TX_COL_EVENT           0x12

/* PP_TxEvent - Transmit Event Bit definition - Read-only */
#define  TX_LOST_CRS                0x0040
#define  TX_SQE_ERROR               0x0080
#define  TX_OK                      0x0100
#define  TX_LATE_COL                0x0200
#define  TX_JBR                     0x0400
#define  TX_16_COL                  0x8000
#define  TX_SEND_OK_BITS            (TX_OK|TX_LOST_CRS)
#define  TX_COL_COUNT_MASK          0x7800

/* PP_BufEvent - Buffer Event Bit definition - Read-only */
#define  SW_INTERRUPT               0x0040
#define  RX_DMA                     0x0080
#define  READY_FOR_TX               0x0100
#define  TX_UNDERRUN                0x0200
#define  RX_MISS                    0x0400
#define  RX_128_BYTE                0x0800
#define  TX_COL_OVRFLW              0x1000
#define  RX_MISS_OVRFLW             0x2000
#define  RX_DEST_MATCH              0x8000

/* PP_BusST - ISA Bus Status bit definition */
#define  TX_BID_ERROR               0x0080
#define  READY_FOR_TX_NOW           0x0100


#define  RX_DRIBBLE                 0x0080
#define  RX_OK                      0x0100
#define  RX_CRC_ERROR               0x1000
#define  RX_RUNT                    0x2000
#define  RX_EXTRA_DATA              0x4000

#define  SI_BUSY                    0x0100

#define SWAP_U16(t)     (t << 8 | t >> 8)

//#define CS8900_DEFAULT_TX_CMD       0x00c0      // after all
#define CS8900_DEFAULT_TX_CMD       0x0040        // after 381 bytes
//#define CS8900_DEFAULT_TX_CMD       0x0000      // after 5 bytes
#endif /* __NETIF_CS8900IF_H__ */
