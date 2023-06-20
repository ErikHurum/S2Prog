/***** B_SGpar.C *************************************************************
*
*     Program for calculating the sensorparameters
*
*     Company: ARISTON Norway as
*
*     Author: Asle Straume
*
*     Date: 16-oct-96.
*
*************************************************************************/

#include <math.h>
#include <stdio.h>
/*#include "ioh8325.h"
#include "inth8325.h"
*/
#include "b_sg.h"
#include "b_sgext.h"

short		fro_0 ;
short		g1_0 ;
short		g2_0 ;
short		g3_0 ;
short		fro_40 ;
short		g1_40 ;
short		g2_40 ;
short		g3_40 ;
short		fro_60 ;
short		g1_60 ;
short		g2_60 ;
short		g3_60 ;
short		fro_100 ;
short		g1_100 ;
short		g2_100 ;
short		g3_100 ;

short		nl1 ;
short 	nl2 ;

short 	off ;
short 	gai ;

/*************************************************************************
*
*	Initialize sensor variables
*
*************************************************************************/
void InitSensVar(void)
{

/*
	fro_0 	= 	-25 ;
	g1_0 		=	-27 ;
	g2_0 		=	-5 ;
	g3_0 		=	116 ;

	fro_40 	=	3122 ;
	g1_40 	=	-26 ;
	g2_40 	=	-85 ;
	g3_40 	=	138 ;

	fro_60 	=	1568 ;
	g1_60 	=	-27 ;
	g2_60 	=	-144 ;
	g3_60 	=	184;

	fro_100 	=	3148 ;
	g1_100 	=	-24 ;
	g2_100 	=	-303 ;
	g3_100 	=	342 ;

	nl1 		=	-3 ;
	nl2 		=	-1 ;
*/
              // Sensor S000748 //Oudaker
	fro_0 	=      	274 ;
	g1_0 	=	-80 ;
	g2_0   	=	31 ;
	g3_0   	=	-51 ;

	fro_40 	=	3983 - 274;
	g1_40 	=	-57 ;
	g2_40 	=	-87 ;
	g3_40 	=	107 ;

	fro_60 	=	5840 - 3983 ;
	g1_60 	=	-48 ;
	g2_60 	=	-144 ;
	g3_60 	=	212;

	fro_100  =      9560 - 5840;
	g1_100 	=	-23 ;
	g2_100 	=	-267 ;
	g3_100 	=	383 ;

	nl1 		=	-1 ;
	nl2 		=	-1 ;


	off	= 	0 ;
	gai 		= 0 ;

}

/*************************************************************************
*
*	Build the packed sensor data
*
*************************************************************************/
void BuildPackedSensData(void)
{

		unsigned char cnt ;
		unsigned char	csum ;
		short				i ;

	for (i = 0; i<  NOPSD; i++) {
		packed_data[i][0] = 126 ; 						/*put data into buffers */
		packed_data[i][1] = 211 ;
		packed_data[i][2] = 13 ;
		packed_data[i][3] = 0 ;
		packed_data[i][4] = 0 ;
		packed_data[i][5] = 85 ;
		packed_data[i][6] = 35 ;
		csum = 0 ;
		for (cnt = 0 ; cnt < 7 ; cnt++) {
			csum = crc[csum ^ packed_data[i][cnt]] ;
		}
		packed_data[i][7] = csum ;

		packed_data[i][8] = fro_0 & 0xff ;
		packed_data[i][9] = (fro_0 >> 8) & 0x1f ;
		packed_data[i][9] |= (g1_0 << 5) & 0xe0 ;
		packed_data[i][10] = (g1_0 >> 3) & 0xff ;
		packed_data[i][11] = (g1_0 >> 11) & 0x03;
		packed_data[i][11] |= (g2_0 << 2) & 0xfc ;
		packed_data[i][12] = (g2_0 >> 6 ) & 0x7f ;
		packed_data[i][12] |= (g3_0 << 7) & 0x80  ;
		packed_data[i][13] = (g3_0 >> 1 ) & 0xff ;
		packed_data[i][14] = (g3_0 >> 9 ) & 0x0f ;
		packed_data[i][14] |= (fro_40 << 4) & 0xf0;
		packed_data[i][15] = (fro_40 >> 4) & 0xff ;
		packed_data[i][16] = (fro_40 >> 12) & 0x01 ;
		packed_data[i][16] |= (g1_40 << 1) & 0xfe ;
		packed_data[i][17] = (g1_40 >> 7) & 0x3f ;
		packed_data[i][17] |= (g2_40 << 6) & 0xc0 ;
		packed_data[i][18] = (g2_40 >> 2) & 0xff ;
		packed_data[i][19] = (g2_40 >> 10) & 0x07 ;
		packed_data[i][19] |= (g3_40 << 3) & 0xf8 ;
		packed_data[i][20] = (g3_40 >> 5) & 0xff ;
		packed_data[i][21] = fro_60 & 0xff ;
		packed_data[i][22] = (fro_60 >> 8) & 0x1f ;
		packed_data[i][22] |= (g1_60 << 5) & 0xe0 ;
		packed_data[i][23] = (g1_60 >> 3) & 0xff ;
		packed_data[i][24] = (g1_60 >> 11) & 0x03;
		packed_data[i][24] |= (g2_60 << 2) & 0xfc ;
		packed_data[i][25] = (g2_60 >> 6 ) & 0x7f ;
		packed_data[i][25] |= (g3_60 << 7) & 0x80  ;
		packed_data[i][26] = (g3_60 >> 1 ) & 0xff ;
		packed_data[i][27] = (g3_60 >> 9 ) & 0x0f ;
		packed_data[i][27] |= (fro_100 << 4) & 0xf0;
		packed_data[i][28] = (fro_100 >> 4) & 0xff ;
		packed_data[i][29] = (fro_100 >> 12) & 0x01 ;
		packed_data[i][29] |= (g1_100 << 1) & 0xfe ;
		packed_data[i][30] = (g1_100 >> 7) & 0x3f ;
		packed_data[i][30] |= (g2_100 << 6) & 0xc0 ;
		packed_data[i][31] = (g2_100 >> 2) & 0xff ;
		packed_data[i][32] = (g2_100 >> 10) & 0x07 ;
		packed_data[i][32] |= (g3_100 << 3) & 0xf8 ;
		packed_data[i][33] = (g3_100 >> 5) & 0xff ;
		packed_data[i][34] = nl2 & 0x07 ;
		packed_data[i][34] |= (nl1 << 3) & 0xf8 ;
		packed_data[i][35] = off & 0xff ;
		packed_data[i][36] = (off >> 8) & 0xff ;
		packed_data[i][37] = gai & 0xff ;
		packed_data[i][38] = (gai >> 8) & 0xff ;
		csum = 0 ;
		for (cnt = 8 ; cnt < PACKED_DATA_SIZE-1 ; cnt++) {
			csum = crc[csum ^ packed_data[i][cnt]] ;
		}
		packed_data[i][39] = csum ;
	}


}

