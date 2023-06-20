/***** SGEXT.H **************************************************************
*
*     Headerfile for SG*.C, signal convertion card
*
*     Company: ARISTON Norway as
*
*     Author: Asle Straume
*
*     Date: 1-aug-96.
*
*************************************************************************/


extern unsigned char		tx_buff[TX_SIZE] ;
extern unsigned char		rx_buff[RX_SIZE] ;
extern unsigned char		tx_indx ;
extern unsigned char		tx_bytes ;
extern unsigned char	tx_tail;
extern unsigned char	wait_for_pc ;
extern char					rx_indx ;
extern char					rx_hndx ;
extern char					rx_start ;
extern unsigned char		rx_counter ;
extern unsigned char		rx_packlen ;
extern unsigned char		rx_timeout ;

extern unsigned char		packed_data[NOPSD][PACKED_DATA_SIZE] ; /* packed sensor data */
																			/* and the on board eep*/
extern unsigned char		scratch_data[UNPACKED_DATA_SIZE] ;		/* unpacked data size */
extern unsigned char		eep_status;									/* status byte of the eep*/
extern unsigned char		sensor_low_range ;						/* low range of sensor */
extern unsigned char		sensor_high_range ;						/* high range of sensor */
extern unsigned char		time_b_temp;								/* time between temp read */
extern unsigned char		time_b_cnt;								/* time between temp cnt */

extern short	current_sens_data ;			/* sensor data from ad conv. */
extern short	cal_data[14] ;					/* calibration data */
extern short	raw_data[14] ;					/* raw data from senors */
extern float				mes_data[14];					/* measured data result */
extern short				offset[14] ;					/* offset for sendors */
extern float				gain[14] ;						/* gain for seensors */
extern float				cal_gain ;						/* gain for cal resistor */
extern short				cal_zero ;						/* gain for cal resistor */
extern unsigned char		not_mes_data ;					/* number of tx of measured data */
extern unsigned char		not_raw_data ;					/* number of tx of raw data */
extern unsigned char		not_cal_data ;					/* number of tx of calib. data */

extern unsigned char		ad_state	;						/* status for ad conversion */
extern unsigned long		ms_delay_cnt ;			/* increased each millisecond */
extern unsigned long		wait_update ;				/* time between DA updates */
extern unsigned short	ad_settling ;				/* ad settling timer */

extern unsigned char		ch_stat[14] ;			/* sensor status */
extern unsigned char		eep_type[8] ;			/* eeprom status*/
extern unsigned char		p_filter ;				/* pressure filter */
extern unsigned char		t_filter ;				/* temperature filter */
extern unsigned char		o_filter ;				/* "other" filter */
extern unsigned char		my_address ;			/* my address */
extern unsigned char		rx_state ;				/* rx state */
extern unsigned char		tx_complete ;			/* tx state */
extern unsigned char		ad_mode ;
extern signed char			curr_ad_ch ;
extern unsigned char		sendtail ;
extern unsigned char		display[NO_OF_DISP] ;	/* display mode */

extern const crc[] ;
