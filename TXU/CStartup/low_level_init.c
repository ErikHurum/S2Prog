/**************************************************
 *
 * This module contains the function `__low_level_init', a function
 * that is called before the `main' function of the program.  Normally
 * low-level initializations - such as setting the prefered interrupt
 * level or setting the watchdog - can be performed here.
 *
 * Note that this function is called before the data segments are
 * initialized, this means that this function cannot rely on the
 * values of global or static variables.
 *
 * When this function returns zero, the startup code will inhibit the
 * initialization of the data segments. The result is faster startup,
 * the drawback is that neither global nor static data will be
 * initialized.
 *
 * Copyright 1999-2004 IAR Systems. All rights reserved.
 *
 * $Revision: 8621 $
 *
 **************************************************/

#include "def.h"
#include "2410addr.h"

#ifdef __cplusplus
extern "C" {
#endif
	extern void Timer_Start(int divider);

#pragma language=extended

	__interwork int __low_level_init(void);

	__interwork int __low_level_init(void)
	{
		/*==================================*/
		/*  Initialize hardware.            */
		/*==================================*/

		/*==================================*/
		/* Choose if segment initialization */
		/* should be done or not.           */
		/* Return: 0 to omit seg_init       */
		/*         1 to run seg_init        */
		/*==================================*/
		//return 1;
#if (WATCHDOG == 1)
	#ifdef ANBOOTLOADER
		rWTCON  = 0x00008000;			// Disable the watchdog
	#else
	//rWTCON  = 0x00008000;			// Disable the watchdog
	Timer_Start(3);
	#endif
#else
		rWTCON  = 0x00008000;			// Disable the watchdog
#endif

		rBWSCON = 0x22d44444;			// Set SDRAM width to 32 bit for bank 6 and 7	, 8 bit and 1 waitstate for 1 to 4, 16 bit, 1 wait state, Using nBE on bank 5

/*
 Bank 5, set to Ethernet
 */
	//rBANKCON5 =  0x0700;
	//rBANKCON5 =  0x7ff0;      // hkim. slowest speed at the moment
    // Page 205 S3C2410 manual
    //           Tacs=11  Tcos=11   Tacc=111 Tcoh=11  Tcah=11     Tacp=11    PMC=00
    rBANKCON5 = (3<<13)  |(3<<11) | (7<<8) | (3 << 6) | (3 << 4) | ( 0<<2) | (0);
    //rBANKCON5 = (1<<13)  |(1<<11) | (5<<8) | (2 << 6) | (2 << 4) | ( 0<<2) | (0);
/*
 Bank 6, set to SDRAM
 RAS to CAS delay; 0 = 2 clk, 1 = 3 clk, 2 = 4 clk
 Column address no; 0 = 8 bit, 1 = 9 bit, 2 = 10 bit
 */
		rBANKCON6 =  (3<<15) |(0<<2) |(1);
/*
 Bank 7, set to SDRAM
 RAS to CAS delay; 0 = 2 clk, 1 = 3 clk, 2 = 4 clk
 Column address no; 0 = 8 bit, 1 = 9 bit, 2 = 10 bit
 */
		rBANKCON7 =  (3<<15) |(0<<2) |(1);
/*
	rREFRESH =  (1<<23)  Enable refresh
			|(0<<22)  0 = autorefresh, 1 = Self refresh
			|(0<<20)  RAS pre charge time; 0=2 clk, 1=3clk, 2=4clk
			|(0<<18)  RC min time; 0=4clk, 1=5 clk, 2=6clk, 3=7clk
			|(0)       Refresh cnt; 2^11+1 -(90x15.6)
*/
		rREFRESH =  (1<<23) |(0<<22) |(0<<20) |(0<<18) |(0);
#ifdef ANBOOTLOADER
		rMRSRB6  =  (2<<4) ; // CAS latency; 0=1clk, 2=2clk, 3=3clk (USE 2!!)
		rMRSRB7  =  (2<<4) ; // CAS latency; 0=1clk, 2=2clk, 3=3clk (USE 2!!)
#endif
		rINTMSK  = BIT_ALLMSK;
                return 1;
	}

#pragma language=default

#ifdef __cplusplus
}
#endif


