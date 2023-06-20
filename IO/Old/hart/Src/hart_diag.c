#include "iom1280.h"
#include "version.h"
#include "inavr.h"
#include "RTOS.h"

#include "constants.h"

#include "hart_common.h"
#include "hart.h"
#include "hart_diag.h"
#include "hart_gpio.h"
#include "structs.h"
#include "externals.h"
/////////////////////////////////////////////////////////////////////////////////////
//
// AD7715 summary.
// * some people are stupid enough not to write this down in the code. So I do.
//   -hkim-
//
//
// a. setup communication register
//
// 7        6       5       4       3       2       1       0
// must     must    rs1     rs0     r/w     sdby    g1      g0
// be 0     be 0                    r=1     1 =
//                                  w=0     p down  gain setup
//
// rs1    rs0
// ============
// 0      0       comm reg        8  bit
// 0      1       setup reg       8  bit
// 1      0       test reg        8  bit
// 1      1       data reg        16 bit
//
// g1     g0
// ============
//  0     0       x1
//  0     1       x2
//  1     0       x32
//  1     1       x128
//
// b. setup register (rs1,rs0= 0,1
//
// 7        6       5       4       3       2       1       0
// MD1      MD0     CLK     FS1     FS0     B/U     BUF     FSYNC
// mode selection   opr     output rate     bi/uni  buf     filter
//                  freq                    polar   control sync
//
// CLK should be set to 0 with 1 Mhz clock
//
// MD1    MD0
// ============
// 0      0       normal mode
// 0      1       self calib
// 1      0       zero scale calib
// 1      1       full scale calib
//
// CLK      FS1     FS0
// ================================
// 0        0       0           20 Hz
// 0        0       1           25 Hz
// 0        1       0           100 Hz
// 0        1       1           200 Hz
// 1        0       0           50 Hz
// 1        0       1           60 Hz
// 1        1       0           250 Hz
// 1        1       1           5600 Hz
//
// B/U : 0 bipolar, 1 unipolar
//
// c. test register (rs1,rs0 = 1,0
// just don't use it. chip maker doesn't want you to fuck up with this.
//
// d. data register (rs1,rs0 = 1,1)
//
/////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// private defines
//
////////////////////////////////////////////////////////////////////////////////
#define HART_DIAG_CONVERSION_COMPLETE         0x01

////////////////////////////////////////////////////////////////////////////////
//
// private prototypes
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// hart module privates
//
////////////////////////////////////////////////////////////////////////////////
static OS_STACKPTR int    _hart_diag_task_stack[60];
static OS_TASK            _hart_diag_task;
static uint16_t           _num_adc_fuckups = 0;

////////////////////////////////////////////////////////////////////////////////
//
// AD7715 related utilities
//
////////////////////////////////////////////////////////////////////////////////
static void
ad7715_toggle_debug_led(void) {
	static uint8_t    on_off = 1;

	hart_gpio_debug_led(on_off);
	on_off = !on_off;
}

static uint8_t
ad7715_read_byte(void) {
	uint8_t i, readbyte;

	readbyte = 0;

	for (i = 0; i <  8; i++) {
		readbyte <<= 1;                      // shift to next bit
		AD7715_CLK_LO();
		AD7715_CLK_HI();

		if (AD7715_MISO_READ()) {
			// data high
			readbyte |= 0x01;                   // set bit high
		}
	}
	return readbyte;
}

static void
ad7715_write_byte(uint8_t data) {
	uint8_t i;

	for (i = 0; i <  8; i++) {
		AD7715_CLK_LO();

		if (data & 0x80) {                        // data bit = 1?
			AD7715_MOSI_HI();
		} else {
			AD7715_MOSI_LO();
		}
		data <<= 1;                              // shift to next bit

		AD7715_CLK_HI();
	}
}

static void
ad7715_hard_reset(void) {
	hart_gpio_adc_reset(1);     // high
	OS_Delay(100);
	hart_gpio_adc_reset(0);     // low
	OS_Delay(500);
	hart_gpio_adc_reset(1);     // high
	OS_Delay(100);
}

static void
ad7715_put_on_hold(void) {
	// select setup reg
	ad7715_write_byte(0x10);

	// set fsync to put ADC on hold
	ad7715_write_byte(0x0f);
}

static void
ad7715_start_next_sample(void) {
	// select setup reg
	ad7715_write_byte(0x10);

	// clear fsync bit to start conversion
	ad7715_write_byte(0x0e);

	//
	// sample will be available after 3x1/output rate, which is 3x1/25 = 120ms.
	// code will be notified by /DRDY
	//
}

static uint16_t
ad7715_read_sample(void) {
	uint8_t   lo, hi;
	uint16_t  ret;

	// select data reg
	ad7715_write_byte(0x38);

	hi = ad7715_read_byte();
	lo = ad7715_read_byte();

	ret = (uint16_t)(hi << 8 | lo);

	return ret;
}

static uint8_t
ad7715_wait_for_drdy(void) {
	if (OS_WaitEventTimed(HART_DIAG_CONVERSION_COMPLETE, 1000) == 0) {
		_num_adc_fuckups++;
		return 1;
	}

	// ok
	return 0;
}

static void
ad7715_do_calibration(void) {
	//
	// set current channel to 2.5V reference
	//
	hart_gpio_adc_channel_select((hart_channel_t)14);

	//
	// select setup reg (0,1)
	// 7        6         5         4         3         2         1         0
	// 0        0         0         1         0         0         0         0
	//                    setup reg           write     no        gain x1
	//                                                  stby
	ad7715_write_byte(0x10);

	//
	// setup reg to perform calib
	//
	// 7        6         5         4         3         2         1         0
	// 0        1         0         0         1         1         1         0
	// seld calib         1 Mhz     25 Hz Rate          Unipolar  buffed    no fsync
	// mode               clk
	//
	ad7715_write_byte(0x4e);

	//
	// calibration will be complete after 6 x 1/outpur rate
	// which is 6 * 1/25 = roughly 240ms and /DRDY will be asserted.
	//
	(void)ad7715_wait_for_drdy();

	//
	// read dummy sample. /DRDY will go hi again after this
	//
	(void)ad7715_read_sample();

	ad7715_put_on_hold();

	// back to 0
	hart_gpio_adc_channel_select(hart_channel_0);
}


////////////////////////////////////////////////////////////////////////////////
//
// ADC interrupt handler
//
////////////////////////////////////////////////////////////////////////////////
#pragma vector=INT0_vect
__interrupt void IntHandler_INT0(void) {
	OS_EnterInterrupt();
	OS_EnterIntStack();

	OS_SignalEvent(HART_DIAG_CONVERSION_COMPLETE, &_hart_diag_task);

	OS_LeaveIntStack();
	OS_LeaveInterruptNoSwitch();
}

////////////////////////////////////////////////////////////////////////////////
//
// private utilities
//
////////////////////////////////////////////////////////////////////////////////
static void
hart_diag_configure_adc(void) {
	ad7715_hard_reset();
	ad7715_do_calibration();
}

////////////////////////////////////////////////////////////////////////////////
//
// ADC raw to mA
//
////////////////////////////////////////////////////////////////////////////////
static void
hart_diag_set_diag_value(hart_channel_t chnl, uint16_t raw_adc) {
	// the H/W circuit is created using INA138 current shunt and 5 ohm resistor.
	//
	// The input current is between 0 and 20mA. So voltage drop across the 5 Ohm
	// resistor will be between 0 and 0.1V. This voltage difference is fed into
	// INA138 and with 100K RL resistor, the voltage is amplied by 20 times.
	//
	// So the measured voltage to the ADC is in the range of 0V and 2V, where
	// 0V corresponds to 0mA and 2V corresponds to 20mA.
	//
	// Additionally ADC ref voltage is 2.5V, which means 0xffff corresponds 2.5V
	//
	// hkim is kind enough to analyze this freaking circuit himself and leave a
	// record here. Appreciate him.
	//
	// -hkim-
	//
	float       voltage = 2.5f * ((float)(raw_adc)) / 65535.0;
	float       current = voltage / 10.0 * 100.0;
	current /= 1.0028280;
	// EHSMarkuint16_t    current_final = (uint16_t)(current * 10);       // 10 = 1mA, 1 = 0.1mA

	if (chnl <= hart_channel_11) {
		HartChannel *hchannel = hart_channel_get_with_lock(chnl);

		hchannel->MsrdCurrent = current;  //current_final with correction;

		// Always update the mA from the ADC for diagnostics purpose
		TData.Hart.ADCurrent[chnl] = current;               // PROData 0 is the Hart PV(Primary Value)
		hart_channel_put_with_unlock(hchannel);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// HART Diagnostic Task
//
////////////////////////////////////////////////////////////////////////////////
static void
ad7715_read_diag_adc(hart_channel_t chnl) {

	hart_gpio_adc_channel_select(chnl);
	ad7715_start_next_sample();
	ad7715_wait_for_drdy();
	uint16_t raw_adc = ad7715_read_sample();
	ad7715_put_on_hold();

	hart_diag_set_diag_value(chnl, raw_adc);
}

static void
HARTDiag_Task(void) {
	hart_channel_t      current;

	hart_diag_configure_adc();

	while (1) {
		hart_for_each_channel(current) {
			ad7715_read_diag_adc(current);
			ad7715_toggle_debug_led();
		}

#if 0 // for ADC debugging only
		ad7715_read_diag_adc((hart_channel_t)12);
		ad7715_read_diag_adc((hart_channel_t)13);
		//
		// 2.5V reference check for debugging
		//
		ad7715_read_diag_adc((hart_channel_t)14);

		//
		// 0V ground
		//
		ad7715_read_diag_adc((hart_channel_t)15);
#endif
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// public interfaces
//
////////////////////////////////////////////////////////////////////////////////
void
hart_diag_init(void) {
	// FIXME initialize diag data structure
}

void
hart_diag_task_start(void) {
	OS_CREATETASK(&_hart_diag_task, "HARTDiag", HARTDiag_Task, 90, _hart_diag_task_stack);
}
