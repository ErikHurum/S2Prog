#ifndef Anpro10ConstH
#define Anpro10ConstH

/****************************************************************************
 **             - Anpro10Const.h -
 **
 **
 ***************************************************************************/

#define DEFAULT_BAUDRATE 115200
#define DEFAULT_BOOT_BAUDRATE DEFAULT_BAUDRATE
//ANPRO10 definitions
#define ANPRO10_SOH	        0x01
#define ANPRO10_EOT		    0x04
#define ANPRO10_SYN		    0x16

///////////////////////////////////////////////////
//
//	Devices
//
///////////////////////////////////////////////////
#define DEVICE_BROADCAST        0x0D
#define DEVICE_BROADCAST_TXU    0x0E
#define DEVICE_BROADCAST_IO     0x0F
#define DEVICE_BROADCAST_ADDR   0xFF
#define DEVICE_IO				0x10		// 0x10 - 0x1f
#define DEVICE_ZB485			0x10
#define DEVICE_ZBANA			0x11
#define DEVICE_ZBHART			0x13
#define DEVICE_TCU				0x20		// 0x20 - 0x2f
#define DEVICE_TCU_R1			0x21		// 0x20 - 0x2f
#define DEVICE_TCU_R2			0x22		// 0x20 - 0x2f
#define DEVICE_TDU				0x30		// 0x30 - 0x3f
#define DEVICE_TDU_R1			0x31		// 0x30 - 0x3f
#define DEVICE_TDU_R2			0x32		// 0x30 - 0x3f
#define DEVICE_PCSW				0x40		// 0x40 - 0x4f
#define DEVICE_PC_CONF_PROG		0x50
#define DEVICE_PC_FLASH_PROG	0x55
#define DEVICE_TCU_SIMULATOR	0xe0
#define DEVICE_TDU_SIMULATOR	0xe8
#define DEVICE_MASTER			0xfe 		// 0xff is reserved


#define MAX_ANPRO10_SIZE     16000     // Must be an even number!!!!
#define UNPACK_BLOCK_SIZE	(2*MAX_ANPRO10_SIZE+256)

#define MAX_HEADING_SIZE     (10*sizeof(U32))
#define MAX_ANPRO10_IO_SIZE   (1024)
#define MAX_ANPRO10_AD_DATA_SIZE 80

#define ANPRO10_MAX_DATA_SIZE (MAX_ANPRO10_SIZE-MAX_HEADING_SIZE)

#define P_SYNC_SIZE  4
#define ANPRO10_NUM_SYNC 3
#define ANPRO10_PREAMBLE_SIZE (ANPRO10_NUM_SYNC+1)

#define P_HEADING_SIZE sizeof(NetHeading)
#define P_COMMAND_SIZE 4
#define P_START_SIZE ( P_HEADING_SIZE + P_SYNC_SIZE )
/*
#define P_TAIL_SIZE  sizeof(Tail)
#define P_BUFFER_SIZE (MAX_ANPRO10_SIZE+P_START_SIZE+P_TAIL_SIZE+P_COMMAND_SIZE)
*/
// return values from ReceiveData/SendData object methods
#define E_OK				0
#define E_UNKNOWN_COMMAND	1
#define E_UNKNOWN_OBJECT	2	// returned from baseclass method
#define E_QUEUE_FULL	    3 // returned from baseclass method




// End command (ecmd)commands for ANPRO10
#define MAX_ECMD            100
#define ECMD_NMDWOACK       0                           // No more data without acknowledge
#define ECMD_NMDRQACK       1                           // No more data, request acknowledge


#define CMD_GENERIC_REALTIME_DATA       101
#define CMD_GENERIC_STATIC_DATA         102
#define CMD_GENERIC_MODBUS_RT_DATA      103

/*******************************************************************************************

 AN_PRO10 commands for ANZB*  (IO modules) (1000 - 1999)

*******************************************************************************************/

#define CMD_REQ_STATUS          1000                    // module status
#define CMD_REP_STATUS          (CMD_REQ_STATUS + 1)

#define CMD_EEPROM_RESET        1010                      // Command to reset the eeprom
#define CMD_GOTO_BOOTLOADER     1020                      // Command to enter the bootloader

#define CMD_SND_EEPROM_DATA     1070                        // Send EEPROM data to AN-ZB***
#define CMD_REQ_EEPROM_DATA     1080                        // Get EEPROM data from AN-ZB***
#define CMD_REP_EEPROM_DATA     (CMD_REQ_EEPROM_DATA + 1)

#define CMD_REQ_INT_DATA        1090                        // Get data from internal AD
#define CMD_REP_INT_DATA        (CMD_REQ_INT_DATA + 1)

// AN-ZB485 commands
#define CMD_SND_RS4_SETUP       1100                        // Setup of AN-ZB485
#define CMD_REQ_RS4_SETUP       1110                        // Get setup of AN-ZB485
#define CMD_REP_RS4_SETUP       (CMD_REQ_RS4_SETUP + 1)

#define CMD_REQ_RS4_DATA        1140                        // Get data from AN-ZB485
#define CMD_REP_RS4_MDATA       (CMD_REQ_RS4_DATA + 1)      // measure data
#define CMD_REP_RS4_RDATA       (CMD_REQ_RS4_DATA + 2)      // Raw / cal data

#define CMD_SND_RS4_ADBUF       1160                        // send data to AD card
#define CMD_REP_RS4_ADBUF       (CMD_SND_RS4_ADBUF + 1)     // replay data from AD card
                                                            //
#define CMD_SND_RS4_WHBUF       1180                        // send WH data to AD card
#define CMD_REP_RS4_WHBUF       (CMD_SND_RS4_WHBUF + 1)     // replay WH data from AD card

// AN-ZBANA commands
#define CMD_SND_ANA_SETUP       1200                        // Setup of AN-ZBANA
#define CMD_REQ_ANA_SETUP       1210                        // Get setup of AN-ZBANA
#define CMD_REP_ANA_SETUP       (CMD_REQ_ANA_SETUP + 1)

#define CMD_SND_ANA_FILTER      1220                        // Filter for AN-ZBANA
#define CMD_REQ_ANA_FILTER      1230                        // Get filter of AN-ZBANA
#define CMD_REP_ANA_FILTER      (CMD_REQ_ANA_FILTER + 1)

#define CMD_REQ_ANA_DATA        1240                        // Get data from AN-ZBANA
#define CMD_REP_ANA_MDATA       (CMD_REQ_ANA_DATA + 1)      // measure data
#define CMD_REP_ANA_RDATA       (CMD_REQ_ANA_DATA + 2)      // Raw and Cal data
// AN-ZBHART commands
#define CMD_SND_HART_SETUP      1250                        // Setup of AN-ZBANA
#define CMD_REQ_HART_SETUP      1260                        // Get setup of AN-ZBANA
#define CMD_REP_HART_SETUP      (CMD_REQ_HART_SETUP + 1)

#define CMD_SND_HART_FILTER     1270                        // Filter for AN-ZBANA
#define CMD_REQ_HART_FILTER     1280                        // Get filter of AN-ZBANA
#define CMD_REP_HART_FILTER     (CMD_REQ_HART_FILTER + 1)

#define CMD_REQ_HART_DATA       1290                        // Get data from AN-ZBANA
#define CMD_REP_HART_MDATA      (CMD_REQ_HART_DATA + 1)      // measure data
#define CMD_REP_HART_RDATA      (CMD_REQ_HART_DATA + 2)      // Raw and Cal data

// System commands
#define CMD_GET_STACKSTATUS     1910                        // Command to get the stack status
#define CMD_REP_STACKSTATUS     (CMD_GET_STACKSTATUS + 1)

#define CMD_GET_PROMDATA         1920                        // Command to get the Skarpenord Promdata
#define CMD_REP_PROMDATA         (CMD_GET_PROMDATA  + 1)

// Goda commands
#define CMD_SND_RADAR_INFO       1930                        // Command to get the GODA serial number and version
#define CMD_REP_RADAR_INFO       (CMD_SND_RADAR_INFO  + 1)

// Bootloader commands
#define CMD_FLASH_ID            1940                      // Command to get the flash ID (processor id)
#define CMD_REP_FLASH_ID        (CMD_FLASH_ID + 1)

#define CMD_FLASH_ERASE         1950                      // Command to erase the flash
#define CMD_REP_FLASH_ERASE     (CMD_FLASH_ERASE + 1)

#define CMD_FLASH_PROG          1960                      // Command to prog the flash
#define CMD_REP_FLASH_PROG      (CMD_FLASH_PROG + 1)

#define CMD_FLASH_READ          1970                      // Command to read the flash
#define CMD_REP_FLASH_READ      (CMD_FLASH_READ + 1)

#define CMD_EXIT_BOOTLOADER     1990                      // Command to leave the bootloader

/*******************************************************************************************

 Commands for TXU  (2000 - 3999)


*******************************************************************************************/

#define CMD_TXU_REQ_SYSTEMINFO		 2000
#define CMD_TXU_REP_SYSTEMINFO      (CMD_TXU_REQ_SYSTEMINFO + 1)
#define CMD_TXU_STOP_TX		   	    (CMD_TXU_REQ_SYSTEMINFO + 2)
#define CMD_TXU_COMPRESSED_PACKET   (CMD_TXU_REQ_SYSTEMINFO + 3)
#define CMD_TXU_ACK_SYSTEMINFO  	(CMD_TXU_REQ_SYSTEMINFO + 4)
#define CMD_TXU_START_TX       	    (CMD_TXU_REQ_SYSTEMINFO + 5)


#define CMD_TXU_INPUT_PACKET            2010
#define CMD_TXU_INPUT_PACKET_RES        2011
#define CMD_TXU_TIME      			    2020

#define CMD_PRO_PRINT_OUT			    2402
#define CMD_PRO_PRINT_ACK               2403

#define CMD_PRO_ALARM_STATUS            3000
#define CMD_PRO_ALARM_ACK               3001
#define CMD_PRO_ALARM_ACK_ALL           3002

#define CMD_ALARM_SILENCE				3100
#define CMD_BUZZER_TEST					3110

#define CMD_ZSET_ALL_CARGO_LEVEL		3200
#define CMD_ZSET_ALL_CARGO_TANK_PRESS	3201
#define CMD_ZSET_ALL_BALLAST_LEVEL		3210
#define CMD_ZSET_ALL_BALLAST_TANK_PRESS	3211
#define CMD_ZSET_ALL_SERVICE_LEVEL	  	3220
#define CMD_ZSET_ALL_SERVICE_TANK_PRESS 3221
#define CMD_ZSET_ALL_TANK_PRESS			3230
#define CMD_ZSET_ALL_LINE_PRESS			3240
#define CMD_ZSET_ALL_VOIDSPACE_LEVEL	3250
#define CMD_ZSET_ALL_VOIDSPACE_PRESS	3251


#define CMD_START_PROGRAM_ON_TXU		3920
#define CMD_START_PROGRAM_NO_PROGRAM	3921
#define CMD_START_PROGRAM_NO_CONFIG	  	3922
#define CMD_START_PROGRAM_OK       	  	3923
#define CMD_ERASE_FLASH					3924
#define CMD_ACK_ERASE_FLASH  			3925

#define CMD_SEND_FLASH_PROG				3930
#define CMD_ACK_FLASH_PROG       		3931
#define CMD_REQ_FLASH_PROG_BTL          3932
#define CMD_SEND_FLASH_PROG_NO_RESTART	3933
#define CMD_REQ_FLASH_PRG_AND_CFG       3934
#define CMD_REQ_FLASH_PROG_PRG	        3935


#define CMD_SEND_CONFIG		    		3940
#define CMD_ACK_CONFIG		    		3941
#define CMD_REQ_CONFIG		    		3942

#define CMD_SEND_SETTINGS		  		3950
#define CMD_ACK_SETTINGS		  		3951
#define CMD_REQ_SETTINGS		  		3952


/*******************************************************************************************

 Commands for PC  (4000 - 4999)

*******************************************************************************************/



/*********************************************************************

	Flash related constants

**********************************************************************/
#define	SECTOR_BOOT_START_R1				0
#define	SECTOR_BOOT_END_R1					5
#define SECTOR_PROG_START_R1				6
#define SECTOR_PROG_END_R1  				22
#define SECTOR_CONFIG_START_R1				23
#define SECTOR_CONFIG_END_R1   				26
#define SECTOR_CONFIG_BAK_START_R1			27
#define SECTOR_CONFIG_BAK_END_R1   			30
#define SECTOR_SETTINGS1_START_R1			31
#define SECTOR_SETTINGS1_END_R1				32
#define SECTOR_SETTINGS2_START_R1			33
#define SECTOR_SETTINGS2_END_R1				34
#define SECTOR_LOCAL_SETTINGS_START_R1  (SECTOR_PROG_END_R1-1) // Dirty!!!

#define	SECTOR_BOOT_START_R2				0
#define	SECTOR_BOOT_END_R2					9
#define SECTOR_PROG_START_R2				10
#define SECTOR_PROG_END_R2  				25
#define SECTOR_CONFIG_START_R2				26
#define SECTOR_CONFIG_END_R2   				29
#define SECTOR_CONFIG_BAK_START_R2			30
#define SECTOR_CONFIG_BAK_END_R2   			33
#define SECTOR_SETTINGS1_START_R2			34
#define SECTOR_SETTINGS1_END_R2				35
#define SECTOR_SETTINGS2_START_R2			36
#define SECTOR_SETTINGS2_END_R2				37
#define SECTOR_LOCAL_SETTINGS_START_R2  	38

#define FLASH_NO_ERROR						0
#define FLASH_ERASE_FAILURE 				1
#define FLASH_MARK_COMPLETE_FAILURE 		2
#define FLASH_PROGRAM_TIMEOUT				3
#define FLASH_PROGRAM_FAILURE       		4
#define FLASH_BLOCK_TO_LARGE        		5
#define FLASH_SEND_FAILURE					6
#define FLASH_BUSY         				  	7
#define FLASH_GET_BLOCK_INFO_ERROR  		8
#define FLASH_ERASE_UNKNOWN_COMMAND 		3

#define FLASH_ERASE_BOOTLOADER				0
#define FLASH_ERASE_UNUSED					1
#define FLASH_ERASE_PROGRAM					2
#define FLASH_ERASE_CONFIG					3
#define FLASH_ERASE_CONFIG_BACKUP			4
#define FLASH_ERASE_APP_DATA				5
#define FLASH_ERASE_APP_DATA_BACKUP			6
#define FLASH_ERASE_ALL_APP_DATA    		7

#define FLASH_IDLE							0
#define FLASH_BUSY_RECEIVE					1
#define FLASH_BUSY_SEND						2


#define SEND_COMPLETE_EVENT					1
#define SEND_FLASH_OK_EVENT					2
#define SYSINFO_RECEIVED_EVENT 				4



/////////////////////////////////////////////////////////
//
// Misc constants
//
//
#define PRINT_BUF_SIZE		4096
#define PRINT_SEND_OK_EVENT	1
#define PRINT_OK			0
#define PRINT_NO_ACK		1



#define MAX_ANPRO10_NUMBER_OF_TASKS     40
#define MAX_ANPRO10_NAME_LENGTH         20

////////////////////////////////////////////////////////
//
// Memory pool constants
//
////////////////////////////////////////////////////////

#define PURPOSE_DECOMPRESS		1
#define PURPOSE_COMPRESS      2
#define PURPOSE_IO_RECEIVE		3
#define PURPOSE_IO_TRANSMIT   4
//---------------------------------------------------------------------------
#endif

