
#ifndef __KS32C50100_H__
#define __KS32C50100_H__

#define __SYSCFG  *(volatile OS_U32*) 0x03ff0000

#define __INTMOD  *(volatile OS_U32*) 0x03ff4000
#define __INTPND  *(volatile OS_U32*) 0x03ff4004
#define __INTMSK  *(volatile OS_U32*) 0x03ff4008

#define __IOPMOD  *(volatile OS_U32*) 0x03ff5000
#define __IOPDATA *(volatile OS_U32*) 0x03ff5008

#define __TMOD    *(volatile OS_U32*) 0x03ff6000
#define __TDATA0  *(volatile OS_U32*) 0x03ff6004
#define __TDATA1  *(volatile OS_U32*) 0x03ff6008
#define __TCNT0   *(volatile OS_U32*) 0x03ff600c
#define __TCNT1   *(volatile OS_U32*) 0x03ff6010

#define __ULCON0  *(volatile OS_U32*) 0x03ffd000
#define __UCON0   *(volatile OS_U32*) 0x03ffd004
#define __USTAT0  *(volatile OS_U32*) 0x03ffd008
#define __UTXBUF0 *(volatile OS_U32*) 0x03ffd00c
#define __URXBUF0 *(volatile OS_U32*) 0x03ffd010
#define __UBRDIV0 *(volatile OS_U32*) 0x03ffd014

#endif


