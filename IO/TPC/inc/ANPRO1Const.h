#ifndef ANPRO1Const_h
#define ANPRO1Const_h
#define ANPRO1_MAX_SIZE     1024
#define ANPRO1_MAX_HEADING_SIZE     (5*sizeof(U32))
#define ANPRO1_MAX_DATA_SIZE (MAX_ANPRO10_SIZE-MAX_HEADING_SIZE)



#define ANPRO1_NUM_SYNC   2
#define ANPRO1_PREAMBLE_SIZE (ANPRO1_NUM_SYNC+1)

#define ANPRO1_HEADING_SIZE sizeof(NetHeading)
#define ANPRO1_COMMAND_SIZE 2

#define ANPRO1_START_SIZE ( P_HEADING_SIZE + P_SYNC_SIZE )


#define ANPRO1_SYN          0x2
#define ANPRO1_EOT          0x3

#define MAX_PROT_CMD        255         // Max commands defined in package (one char)

#define ANP1_MAX_ECMD       10
#define ANP1_ECMD_NMDWOACK   0                           // No more data without acknowledge
#define ANP1_ECMD_NMDRQACK   1                           // No more data, request acknowledge
#define ANP1_ECMD_SNDOK      2                           // OK to send for TPC*
#define ANP1_TX_ACK 		     5		// Replay with errorcode

// ANSGCNV				    cmd 10 - 49

#define ANP1_REQ_M_DATA	    10			/* Send measured data */
#define ANP1_REP_MP_DATA	30			/* Sending measured pressure data */
#define ANP1_REP_MT_DATA	31			/* Sending measured temperature data */
#define ANP1_REP_MO_DATA	32			/* Sending measured "other" data */

#define ANP1_REQ_R_DATA	    13	        /* Send raw data */
#define ANP1_REP_RP_DATA	33	        /* Sending raw pressure data */
#define ANP1_REP_RT_DATA	34	        /* Sending raw temperature	data */
#define ANP1_REP_RO_DATA	35	        /* Sending raw "other" data */

#define ANP1_REQ_C_DATA	    16			/* Send calibration data */
#define ANP1_REP_CAL_DATA	36			/* Sending calibration data */

#define ANP1_REQ_CONFIG	    17			/* Send configuration */
#define ANP1_REP_CONFIG	    37			/* Sending configuration */

#define ANP1_SND_EEP_DATA	18		    /* Receive ID-REG andsensor data for ch no. */
#define ANP1_ASK_EEP_DATA	38		        /* Ask for ID-REG andsensor data for ch no. */

#define ANP1_SND_OFF_GAIN   19		    /* Receive offset and gain */
#define ANP1_REP_OFF_GAIN	39		        /* Ask for offset and gain */

#define ANP1_SND_SET_UP	    20			/* Receive setudata */
#define ANP1_REP_SET_UP	    40			/* Ask for setudata */

#define ANP1_SND_TBTR	    21			/* Receive time between temp. readings */

#define ANP1_SND_WRITE_EEP  22			/* Write eep-data for a channel to eeprom */
#define ANP1_REP_WRITE_EEP	42			/* Ack. for writing snsdata to a eeprom */

#define ANP1_SND_WRITE_ADR  23			/* Write AD-REG for a channel to eeprom */
#define ANP1_REP_WRITE_ADR	43			/* Ack. for writing ID-REG  to eeprom */

#define ANP1_REQ_EEP_DATA   24			/* Send AD-REG and data for a channel */
#define ANP1_REP_EEP_DATA	  44			/* Sending ID-REG and data for a channel */

#define ANP1_SND_READ_EEP   25			/* Read AD-REG and sensor data from channel */
#define ANP1_SND_FILTER	    26			/* Receive filters */

#define ANP1_REQ_CARD_STAT	27			/* Send card status */
#define ANP1_REP_CARD_STAT	47			/* Sending card status */

#define ANP1_REQ_SER_NO	    28			/* Send serial no of eeprom */
#define ANP1_REP_SER_NO	    48			/* Serial no for eeprom */

#define ANP1_SND_DISP_DATA  29			/* Receive data for display */
#define ANP1_REP_DISP_DATA	49			/* Send data for display */

// TPC                      cmd 50 - 99

#define ANP1_SND_LOTXT		50		// Receive text for low display
#define ANP1_SND_HITXT		51		// Receive text for high display
#define ANP1_SND_BAVAL		52		// Receive data for bar graph
#define ANP1_SND_BAVOL		53		// Receive data for bar graph old
#define ANP1_SND_ALSTA		54		// Receive data for alarm status

#define ANP1_REQ_ACKSTAT   	55		// Receive ack. status
#define ANP1_REP_DATA	    75		// Send alarm status data

#define ANP1_SND_LOGRA		56		// Receive data for low disp graph
#define ANP1_SND_HIIMG		57		// Receive data for bar image
#define ANP1_SND_EEPDATA  	58		// Receive data for eep

#define ANP1_REQ_STAT	    59		// request card Status
#define ANP1_REP_STAT	  	79		// Send status

#define ANP1_SND_CASET		60		// Receive card setup (addresses)
#define ANP1_SND_XTXT		61		// Receive text for tPC196 displays

#define ANP1_SND_WEEP		62		// Write eeprom
#define ANP1_REP_ACKWEEP   	82		// Ack. for writing eep

#define ANP1_SND_WAPR	  	63		// Write ap-reg
#define ANP1_REP_ACKWAPR   	83		// Ack. for writing ap-reg

#define ANP1_REQ_TXEEP		64		// Request data for eep and ap-reg
#define ANP1_REP_EEP	   	84		// Send data for eep and ap-reg

#define ANP1_SND_REEP	    65		// Read eep data and ap-reg
#define ANP1_SND_DVAL		66		// Value set to display
#define ANP1_SND_DISDVAL    67		// Diaable window

#define ANP1_REQ_TXSER  	68		// Request eep serial no
#define ANP1_REP_EEPSER		88		// Send serial no for eep

// WIS  			        cmd 100 - 129

#define ANP1_SND_WIS_STAT	100			/* Send WIS status */
#define ANP1_REP_WIS_STAT	126			/* Reply WIS status */

#define ANP1_SND_WIS_DATA	101			/* Send WIS measured data */
#define ANP1_REP_WIS_DATA	127			/* Reply WIS measured data */

#define ANP1_SND_WIS_XDATA	102			/* Send WIS measured data */
#define ANP1_REP_WIS_XDATA	128			/* Reply WIS measured data */

// System commands
#define ANP1_REQ_STACKSTATUS     230                        // Command to get the stack status
#define ANP1_REP_STACKSTATUS     (ANP1_REQ_STACKSTATUS + 1)

// Bootloader               cmd 240
#define ANP1_FLASH_ID            240                      // Command to get the flash ID (processor id)
#define ANP1_REP_FLASH_ID        (ANP1_FLASH_ID + 1)

#define ANP1_FLASH_ERASE         242                      // Command to erase the flash
#define ANP1_REP_FLASH_ERASE     (ANP1_FLASH_ERASE + 1)

#define ANP1_FLASH_PROG          244                      // Command to prog the flash
#define ANP1_REP_FLASH_PROG      (ANP1_FLASH_PROG + 1)

#define ANP1_FLASH_READ          246                      // Command to read the flash
#define ANP1_REP_FLASH_READ      (ANP1_FLASH_READ + 1)

#define ANP1_GOTO_BOOTLOADER     248                      // Command to enter the bootloader
#define ANP1_EXIT_BOOTLOADER     249                      // Command to leave the bootloader


#define TPC_LED_OFF			 				 0
#define TPC_LED_ON 			 				 1
#define TPC_LED_FLASH		 				 2
#endif
