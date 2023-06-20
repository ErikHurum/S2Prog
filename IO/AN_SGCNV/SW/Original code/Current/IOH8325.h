/* 			- IOH8325.H -

   This file #defines the internal register addresses.

     Created: [04/Apr/91 IANB]
     Revised: [23/Jan/92 IANB]
       
*/


/*			9 general I/O ports
			-------------------

	DDR is data direction-register
	DR  is data register
	CR  is control register						*/

#define P1DDR		(* (unsigned char *)	( 0xffb0 ))
#define P1DR		(* (unsigned char *)	( 0xffb2 ))

#define P2DDR		(* (unsigned char *)	( 0xffb1 ))
#define P2DR		(* (unsigned char *)	( 0xffb3 ))

#define P3DDR		(* (unsigned char *)	( 0xffb4 ))
#define P3DR		(* (unsigned char *)	( 0xffb6 ))

#define P4DDR		(* (unsigned char *)	( 0xffb5 ))
#define P4DR		(* (unsigned char *)	( 0xffb7 ))

#define P5DDR		(* (unsigned char *)	( 0xffb8 ))
#define P5DR		(* (unsigned char *)	( 0xffba ))

#define P6DDR		(* (unsigned char *)	( 0xffb9 ))
#define P6DR		(* (unsigned char *)	( 0xffbb ))

#define P7DDR		(* (unsigned char *)	( 0xffbc ))
#define P7DR		(* (unsigned char *)	( 0xffbe ))



/*		Three 16-bit free running timers
		--------------------------------

	TCR	timer control register
	TCSR	timer control/status register
	FRCH	free running counter (High)
	FRCL	free running counter (Low)
	OCRAH	output compare register "A" (High)
	OCRAL	output compare register "A" (Low)
	OCRBH	output compare register "B" (High)
	OCRBL	output compare register "B" (Low)
	ICRH	input capture register (High)
	ICRL	input capture register (Low)
	FNCR	noise canceler control register				*/

#define FRT_TCR		(* (unsigned char *)	( 0xff90 ))
#define FRT_TCSR	(* (unsigned char *)	( 0xff91 ))
#define FRT_FRC		(* (unsigned short *)	( 0xff92 ))
#define FRT_FRCH	(* (unsigned char *)	( 0xff92 ))
#define FRT_FRCL	(* (unsigned char *)	( 0xff93 ))
#define FRT_OCRA	(* (unsigned short *)	( 0xff94 ))
#define FRT_OCRAH	(* (unsigned char *)	( 0xff94 ))
#define FRT_OCRAL	(* (unsigned char *)	( 0xff95 ))
#define FRT_OCRB	(* (unsigned short *)	( 0xff96 ))
#define FRT_OCRBH	(* (unsigned char *)	( 0xff96 ))
#define FRT_OCRBL	(* (unsigned char *)	( 0xff97 ))
#define FRT_ICR		(* (unsigned short *)	( 0xff98 ))
#define FRT_ICRH	(* (unsigned char *)	( 0xff98 ))
#define FRT_ICRL	(* (unsigned char *)	( 0xff99 ))
#define FRT_FNCR	(* (unsigned char *)	( 0xffff ))



/*			8-bit timer registers
			---------------------

	TCR	timer control register
	TCSR	timer control/status register
	TCORA	timer constant register A
	TCORB	timer constant register B
	TCNT	timer counter						*/

#define TMR0_TCR	(* (unsigned char *)	( 0xffc8 ))
#define TMR0_TCSR	(* (unsigned char *)	( 0xffc9 ))
#define TMR0_TCORA	(* (unsigned char *)	( 0xffca ))
#define TMR0_TCORB	(* (unsigned char *)	( 0xffcb ))
#define TMR0_TCNT	(* (unsigned char *)	( 0xffcc ))

#define TMR1_TCR	(* (unsigned char *)	( 0xffd0 ))
#define TMR1_TCSR	(* (unsigned char *)	( 0xffd1 ))
#define TMR1_TCORA	(* (unsigned char *)	( 0xffd2 ))
#define TMR1_TCORB	(* (unsigned char *)	( 0xffd3 ))
#define TMR1_TCNT	(* (unsigned char *)	( 0xffd4 ))



/*		Two serial communication interfaces
		-----------------------------------

	SMR	serial mode register
	BRR	bit rate register
	SCR	serial control register
	TDR	transmit data register
	SSR	serial status register
	RDR	receive data register					*/

#define SCI0_SMR	(* (unsigned char *)	( 0xffd8 ))
#define SCI0_BRR	(* (unsigned char *)	( 0xffd9 ))
#define SCI0_SCR	(* (unsigned char *)	( 0xffda ))
#define SCI0_TDR	(* (unsigned char *)	( 0xffdb ))
#define SCI0_SSR	(* (unsigned char *)	( 0xffdc ))
#define SCI0_RDR	(* (unsigned char *)	( 0xffdd ))

#define SCI1_SMR	(* (unsigned char *)	( 0xffe0 ))
#define SCI1_BRR	(* (unsigned char *)	( 0xffe1 ))
#define SCI1_SCR	(* (unsigned char *)	( 0xffe2 ))
#define SCI1_TDR	(* (unsigned char *)	( 0xffe3 ))
#define SCI1_SSR	(* (unsigned char *)	( 0xffe4 ))
#define SCI1_RDR	(* (unsigned char *)	( 0xffe5 ))



/*			Interrupt controller
			--------------------

	SYSCR	system control register
	ISCR	IRQ sense control register
	IER	IRQ enable register					*/

#define SYSCR		(* (unsigned char *)	( 0xffc4 ))
#define ISCR		(* (unsigned char *)	( 0xffc6 ))
#define IER		(* (unsigned char *)	( 0xffc7 ))



/*			System control register
			-----------------------				*/

#define MDCR		(* (unsigned char *)	( 0xffc5 ))
#define HCSR		(* (unsigned char *)	( 0xfffe ))
