/***** SGEEP.C *************************************************************
*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Asle Straume
*
*     Date: 1-aug-96.
*
*************************************************************************/

#include "math.h"
#include "stdio.h"
#include "ioh8325.h"
#include "inth8325.h"

#include "tbsg.h"
#include "tbsgext.h"

/*************************************************************************
*
*  Test the connected eeprom DS2430
*
*
*************************************************************************/
short TestEep(void)
{

	short		cnt, test ;
	unsigned char	csum ;
	unsigned char data[] = "Test 1  This unit has been tested       "  ;


	Led(1, OFF) ;
	Led(2, OFF) ;

	csum = 0 ;
	for (cnt = 0 ; cnt < 7 ; cnt++) {
		csum = crc[csum ^ data[cnt]] ;
	}
	data[cnt] = csum ;

	csum = 0 ;
	for (cnt = 8 ; cnt < (PACKED_DATA_SIZE -1) ; cnt++) {
		csum = crc[csum ^ data[cnt]] ;
	}
	data[cnt] = csum ;

	for (cnt = 0; cnt < PACKED_DATA_SIZE ; cnt++) {
		packed_data[0][cnt] = data[cnt] ;
	}

	test = FALSE ;
	if (Eeprom(0, WRITE_SP)) {
		for (cnt = 8; cnt < PACKED_DATA_SIZE ; cnt++) {
			packed_data[0][cnt] = 0x00 ;
		}
		if (Eeprom(0, READ_SP)) {
			if (CheckEepData(&packed_data[0][8])){ /*check checksum */
				test = TRUE ;
				for (cnt = 8; cnt < PACKED_DATA_SIZE ; cnt++) {
					if (packed_data[0][cnt] != data[cnt]){
						test = FALSE ;
					}
				}
			}
		}
	}
	if (test) {
		test = FALSE ;
		Eeprom(0, COPY_SP_NV) ;
		OneMsecDelay(500) ;
		Eeprom(0, COPY_NV_SP) ;
		Eeprom(0, READ_SP) ;
		if (CheckEepData(&packed_data[0][8])){ /*check checksum */
			test = TRUE ;
			for (cnt = 8; cnt < PACKED_DATA_SIZE ; cnt++) {
				if (packed_data[0][cnt] != data[cnt]){
					test = FALSE ;
				}
			}
		}
	}
	if (test) {
		test = FALSE ;
		if (Eeprom(0, WRITE_APPREG)) {
			if (Eeprom(0, READ_APPREG)) {
				if (CheckADData(&packed_data[0][0])) {
					test = TRUE ;
					for (cnt = 0; cnt < 8 ; cnt++) {
						if (packed_data[0][cnt] != data[cnt]){
							test = FALSE ;
						}
					}
				}
			}
		}
	}
	if (test) {
		Led(1, OFF) ;
		Led(2, ON) ;
	} else {
		for (cnt = 0; cnt < PACKED_DATA_SIZE ; cnt++) {
			packed_data[0][cnt] = 0x00 ;
		}

		Led(1, ON) ;
		Led(2, OFF) ;
		OneMsecDelay(500) ;
		Led(1, OFF) ;
		OneMsecDelay(500) ;
		Led(1, ON) ;
		OneMsecDelay(500) ;
		Led(1, OFF) ;
		OneMsecDelay(500) ;
		Led(1, ON) ;
		OneMsecDelay(500) ;
		Led(1, OFF) ;
		OneMsecDelay(500) ;
		Led(1, ON) ;
	}
}
