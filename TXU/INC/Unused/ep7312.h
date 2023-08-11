

#ifndef __EP7312_H__
#define __EP7312_H__

#define __PBDR          *(volatile OS_U8*)  0x80000001
#define __PBDDR         *(volatile OS_U8*)  0x80000041
#define __SYSCON1       *(volatile OS_U32*) 0x80000100
#define __INTSR1        *(volatile OS_U32*) 0x80000240
#define __INTMR1        *(volatile OS_U32*) 0x80000280
#define __TC1D          *(volatile OS_U16*) 0x80000300
#define __TC2D          *(volatile OS_U16*) 0x80000340
#define __UARTDR1       *(volatile OS_U16*) 0x80000480
#define __UBRLCR1       *(volatile OS_U32*) 0x800004C0
#define __TC1EOI        *(volatile OS_U32*) 0x800006C0
#define __TC2EOI        *(volatile OS_U32*) 0x80000700
#define __SYSFLG2       *(volatile OS_U32*) 0x80001140
#define __INTMR2        *(volatile OS_U32*) 0x80001280
#define __SYSCON3       *(volatile OS_U32*) 0x80002200
#define __PLLW          *(volatile OS_U32*) 0x80002610

#endif /* __EP7312_H__ */


