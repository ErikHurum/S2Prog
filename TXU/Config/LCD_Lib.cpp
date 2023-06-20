#include "TSNConstants.h"
#include "2410addr.h"
#include "def.h"
#include "RTOS.h"
extern OS_RSEMA    GPEPortSema;


static const unsigned short DEMO256pal[]={
	0x0b5e,0xce9a,0xffd9,0x9d99,0xb63a,0xae7c,0xdd71,0x6c57,0xfd4d,0x00ae,0x9c4d,0xb5f8,0xad96,0x0131,0x0176,0xefff,0xcedd,0x9556,0xe4bf,0x00b6,0x22b7,0x002b,0x89de,0x002c,0x57df,0xab5f,0x3031,0x14bf,0x797e,0x5391,0x93ab,0x7239,0x7453,0xafdf,0x71b9,0x8c92,0x014d,0x302e,0x5175,0x0029,0x0969,0x004e,0x2a6d,0x0021,0x3155,0x4b6e,0xd677,0xf6b6,0x9b5f,0x4bb5,0xffd5,0x0027,0xdfdf,0x74d8,0x1256,0x6bcd,0x9b08,0x2ab2,0xbd72,0x84b5,0xfe52,0xd4ad,0x00ad,0xfffc,0x422b,0x73b0,0x0024,0x5246,0x8e5e,0x28b3,0x0050,0x3b52,0x2a4a,0x3a74,0x8559,0x3356,0x1251,0x9abf,0x4034,0x40b1,
	0x8cb9,0x00b3,0x5c55,0xdf3d,0x61b7,0x1f5f,0x00d9,0x4c59,0x0926,0xac3f,0x925f,0x85bc,0x29d2,0xc73f,0xef5c,0xcb9f,0x827b,0x5279,0x4af5,0x01b9,0x4290,0xf718,0x126d,0x21a6,0x515e,0xefbd,0xd75e,0x42ab,0x00aa,0x10b3,0x7349,0x63b5,0x61a3,0xaadf,0xcb27,0x87df,0x6359,0xc7df,0x4876,0xb5bc,0x4114,0xfe2e,0xef5e,0x65be,0x43b9,0xe5df,0x21c9,0x7d16,0x6abb,0x5c11,0x49f7,0xbc0b,0x9e1a,0x3b0f,0x202b,0xff12,0x821b,0x842f,0xbccf,0xdefb,0x8a3e,0x68fa,0xa4f1,0x38ae,0x28b7,0x21ad,0x31d7,0x0073,0x182b,0x1831,0x3415,0xbdf6,0x2dbf,0x0a5d,0xc73d,0x182c,0x293e,0x7b3d,0x643d,0x3cbd,
	0x92dd,0x09d4,0x1029,0x7cdd,0x6239,0x182e,0x5aea,0x11eb,0x8abc,0x7bfa,0x00a7,0x2153,0x1853,0x1318,0x0109,0x54fa,0x72a7,0x89e3,0x01cf,0x3a07,0x7b17,0x1a14,0x2150,0x23dc,0x4142,0x1b33,0x00a4,0xf6df,0x08fc,0x18ae,0x3a7e,0x18d1,0xa51c,0xff5a,0x1a0f,0x28fa,0xdfbe,0x82de,0x60d7,0x1027,0x48fa,0x5150,0x6213,0x89d6,0x110d,0x9bbb,0xbedd,0x28e1,0x1925,0xf449,0xaa79,0xd5f4,0x693c,0x110a,0x2889,0x08a2,0x923d,0x10a6,0xd9bc,0x5b2e,0x32ec,0xcf7f,0x1025,0x2148,0x74b4,0x6d59,0x9d14,0x0132,0x00f0,0x56bf,0x00f1,0xffff,0x0173,0x0133,0x00b0,0x00b1,0xf7ff,0x08b1,0xfffe,0x08b0,
	0x0171,0xf7bf,0x10f3,0xf7fe,0x08ef,0x1192,0xefbe,0x1131,0x2177,0xff9f,0x1116,0xffbc,0x5914,0x22ef,0xb285,0xa6df,
};


void Lcd_Palette8Bit_Init(void)
{
    int i;
    U32 *palette;
    rLCDCON5 &= ~(1<<11); // 5:5:5:1 Palette Setting
    palette=(U32 *)PALETTE;
    for(i=0;i<256;i++)
	*palette++=DEMO256pal[i];
}


#define M5D(n) ((n) & 0x1fffff)	// To get lower 21bits

//Timing parameter for NL3224BC35 VGA mode
#define VBPD_320240		(10-1)
#define VFPD_320240		(1-1)
#define VSPW_320240		(11-1)
#define HBPD_320240		(47-1)
#define HFPD_320240		(7-1)
#define HSPW_320240		(30-1)

#define LCD_XSIZE_TFT_320240 	(320)
#define LCD_YSIZE_TFT_320240 	(240)


///////////////////////////////////////////////////////////////////
//
//	LCD Constants
//
///////////////////////////////////////////////////////////////////


#define LCD_XSIZE			(LCD_XSIZE_TFT_320240)
#define LCD_YSIZE			(LCD_YSIZE_TFT_320240)
#define LCD_HOZVAL			(LCD_XSIZE-1)
#define LCD_LINEVAL			(LCD_YSIZE-1)

#define LCD_ORG_BASE			( 0 & 0x1fffff )
#define LCD_END_ADDRESS			( LCD_ORG_BASE + LCD_XSIZE*LCD_YSIZE)

 /*********************************************************************
*
*                   Define contents of registers
*
**********************************************************************
*/


void LCD_Init_Controller(void){

//	Lcd_Palette8Bit_Init();

	rLCDCON1 =   (6<<8)             /* Clock value set to 6. 90MHz/((6+1)*2) = 6.4 MHz	*/\
		      	|(0<<7)	          /* MMode each frame, as in example from AIJI */\
	            |(3<<5)	          /* TFT LCD                                   */\
		      	|(0xc<<1)           /* 0x0c = 16 bpp on TFT, 0x0b = 8 BPP        */
		      	|(0);                 /* OBS!! Disable the display here until addr setup */
	rLCDCON2 =   (VBPD_320240<<24)  /* Vertical back porch */ \
	            |(LCD_LINEVAL<<14)  /* lineval (vertical size -1)*/ \
	            |(VFPD_320240<<6)   /* vertical front porch */ \
	            |(VSPW_320240);     // vertical sync pulse width
	rLCDCON3 =   (HBPD_320240<<19)  /* hor. back porch */ \
	            |(LCD_HOZVAL<<8)    /* Hozval (hor. size -1) */ \
	            |(HFPD_320240);     // Hor. front porch
	rLCDCON4 =   (13<<8)            /* Mval (Stn) */ \
	            |(HSPW_320240);     // Hor. sync pulse width
	rLCDCON5 =   (0<<12)            /* 24 bit lb/hb */  \
	            |(1<<11)            /* FRM5:5:5:1 */    \
	            |(0<<10)            /* inverse v clock */ \
	            |(1<<9)             /* inverse HSYNC */  \
	            |(1<<8)             /* inverse VSYNC */ \
	            |(0<<7)             /* inverse VD */     \
	            |(0<<6)	          /* inverse VDEN */ \
	            |(0<<5)	          /* inverse PWrEN */ \
	            |(0<<4)	          /* inverse INVLEN */ \
	            |(0<<3)	          /* Enable PWREN */ \
	            |(0<<2)	          /* Enable LEND */ \
	            |(0<<1)	          /* Byte swap */ \
	            |(1);	          /* Half word swap */

        // 16BPP
	rLCDSADDR1= ((LCD_STARTADDRESS_PHY >>22) << 21) | ( M5D(LCD_STARTADDRESS_PHY >> 1) + 0);
    rLCDSADDR2= M5D(LCD_STARTADDRESS_PHY>>1)+(LCD_XSIZE)*(LCD_LINEVAL+1);
    rLCDSADDR3= (0 << 11) | ((LCD_XSIZE)>>1);

	rLCDINTMSK |=(3); // MASK LCD Sub Interrupt
	rLCDINTMSK &=~(3); // MASK LCD Sub Interrupt
	rLPCSEL    &=(~7); // Disable LPC3600
	rTPAL      =0; // Disable Temp Palette

    rLCDCON1 |=    0x01;      /* Turn on the display HERE after set up the addresses*/
}

static bool BackLightIsOn = false;
void LCD_BackLightOn(void)
{
	if ( !BackLightIsOn) {
			BackLightIsOn = true;
			OS_Use(&GPEPortSema);
			rGPEDAT &= ~(1 << 6);
			OS_Unuse(&GPEPortSema);
	}
}

void LCD_BackLightOff(void){
		if ( BackLightIsOn) {
				BackLightIsOn = false;
				OS_Use(&GPEPortSema);
				rGPEDAT |= 1 << 6;
				OS_Unuse(&GPEPortSema);
		}
}

void LCD_BackLightAdjust(int Adjust)
{
	if (Adjust >= 0) {
		OS_Use(&GPEPortSema);
		rGPEDAT |= ((1<<8) | (1<<7)); 		// Count up and clck high
		rGPEDAT &= ~(1<<9); 	// Enable pot and set clock low
		OS_Unuse(&GPEPortSema);
	} else {
		OS_Use(&GPEPortSema);
		rGPEDAT |= (1<<7); 		// Clock high
		rGPEDAT &= ~((1<<9) | (1<<8)); // Enable pot, count down
		OS_Unuse(&GPEPortSema);
		Adjust = -Adjust ;			// invert Adjust
	}
	for (int i = 0; i < Adjust; i++) {
		OS_Use(&GPEPortSema);
		rGPEDAT &= ~(1<<7); 		// clock down
		OS_Unuse(&GPEPortSema);
		OS_Delay(2);
		OS_Use(&GPEPortSema);
		rGPEDAT |= (1<<7); 		// clock up
		OS_Unuse(&GPEPortSema);
		OS_Delay(2);
	}
	OS_Use(&GPEPortSema);
	rGPEDAT |= (1<<9); 		// disable and save
	OS_Unuse(&GPEPortSema);

}
