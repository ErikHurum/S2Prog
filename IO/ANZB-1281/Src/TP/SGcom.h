/*******************************************************

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*
*    * @file     SGcom.h
	 * @brief    SGcom Header File
	 * @version  V0.00
	 * @date     18. October 2022
	 * @note
*

*******************************************************/

/******************************************************************************
*                Version overview 
*          
*        Version 01 :        P906 Tester, LCSP
*        Version 02 :        First burned H8 for NEMKO and test
*        Version 03 :        Changed LED2 status to shorter blink(PressCalc)
*                                fixed address reading. 
*        Version 04 :        Fixed address reading, no pullup at the address line,
*                                redefined leds led1 = com led2 = convert,
*                                add 0x80 to card address to mark restart of card
*        Version 05 :        Fixed check routine for writing AP-reg. (Didn't exit!)
*        18.6.97                Use raw data and sensordata * 3 for better resolution 
*                                and new calc og nl2.    Clear con&cal error and caldata 
*                                for "other". Check for tx during conv and don't use 
*                                this conv. if so. Incteased time (14 us) before read  
*                                of bit from DALLAS and check for only zeros in packet 
*        Version 06 :        Hold "0" for 60ms during write to DALLAS  
*        20.10.97                Read EEPROM on PCB before sensors. Check for legal
*                                value at pressure. Correct conv. of gain < 1.
*        Version 07 :        Correct code in RecOGData()so high byte is read first.
*        25.03.98               This is due to fault in the compiler and to use this 
*                                function on older versions.
*        Version 08 :        Changed limit for cal and conv alarm on Pt100 sensor 
*        03.04.00
*        Version 09 :        Correct calculation for P104 sensors (parameter >32767/3) 
*        08.11.01
*        Version 10c :        Changed to measure pressure sensor value with negative signal
*        18.11.03            due to low tank press on new P/V valves.
*                           Changed cal_data, rew_data and curr_sens_data to signed.
*                           Changed check values for cal values to 1/2 og original.
*                           Multiplied values (measured and cal.) by 2, not 3.
*                           Transmit cal and raw data as short.
*                           Changed interruptroutine to handle sync of package
*                           Re-masure a channel if the TX during conv.
*                           Corrected buffercheck for TX buffer (combination of temp and other).
*       Version 11          Changed code or writing Dallas due to new specification on chip.
*       14.4.15             Add timer interrupt for hhlevel and washtrac.
*                           Add code for reading hhl and washtrac.
*                           Add send package for hhl and washtrac. Used Display (cmd 69)
*       Version 12          Changed code for WashTrack to avoid overrun of counter and
*       27.5.15             syncronize correctly with time.
*       Version 13          Added software reset of ADC at start up
*       15.3.17             Improved accuracy of calculation of Pt100/Pt1000 by a factor of 33 for the range
*                           -180 to 600 degrees. In that range max deviation is now 0.03 degrees.
*        Version 14         New HW with AVR32DB 
*       19-10-2022
******************************************************************************/

#ifndef ___SGCOM_H_
#define ___SGCOM_H_

#define VERSION 14                /* Software version 2022*/
//#define VERSION 13                /* Software version*/
#define MYADRESS_LOCAL 11      // HW 2 

unsigned int CheckAction(unsigned int data)  ;
void BuildHeader(void) ;
void BuildMPData(void) ;
void BuildMTData(void) ;
void BuildMOData(void) ;
void BuildWHData(void) ;
void BuildRPData(void) ;
void BuildRTData(void) ;
void BuildROData(void) ;
void BuildCalData(void) ;
void BuildConfData(void) ;
void BuildCSData(void) ;
void BuildTail(unsigned char, unsigned char) ;
//void RecOGData(unsigned char data) ;
//void RecSetupData(unsigned char data) ;
void RecSetupData(unsigned char pointer);


unsigned char CalcTxChecksum(unsigned int pack_len);
unsigned int CheckAction(unsigned int data);

void RecOGData(unsigned char pointer);
// RecEepData
void BuildEepData(unsigned char channel);

#endif 