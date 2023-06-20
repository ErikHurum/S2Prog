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

static char hasStartedHartDiag = false;

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
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
char StackTest5[] = {"123456789"};
#endif
OS_STACKPTR int  _hart_diag_task_stack[150];
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
char StackTest6[] = {"123456789"};
#endif
OS_TASK          TCB_AD7715;
uint16_t         _num_adc_fuckups    = 0;
OS_U32           Last_ADC_FuckUpTime = 0;
OS_U32           Last_ADC_OK_Time    = 0;
char             CriticalADC_Failure = FALSE;
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
    uint8_t readbyte = 0;
    for (uint8_t i = 0; i <  8; i++) {
        readbyte <<= 1;                      // shift to next bit
        AD7715_CLK_LO();
        OS_Delayus(10);
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
    for (uint8_t i = 0; i <  8; i++) {
        AD7715_CLK_LO();
        OS_Delayus(10);
        if (data & 0x80) {                        // data bit = 1?
            AD7715_MOSI_HI();
        } else {
            AD7715_MOSI_LO();
        }
        data <<= 1;                              // shift to next bit
        AD7715_CLK_HI();
        OS_Delayus(10);
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

static uint16_t ad7715_read_sample(void) {
    uint8_t   lo, hi;
    uint16_t  ret;

    // select data reg
    ad7715_write_byte(0x38);

    hi = ad7715_read_byte();
    lo = ad7715_read_byte();

    ret = (uint16_t)(hi << 8 | lo);

    return ret;
}

static uint8_t ad7715_wait_for_drdy(void) {
    char Status = OS_WaitSingleEventTimed(HART_DIAG_CONVERSION_COMPLETE, 1000);
    if (!Status) {
        Last_ADC_FuckUpTime = OS_Time;
        _num_adc_fuckups++;
    } else {
        Last_ADC_OK_Time = OS_Time;
    }
    return Status;
}

static void ad7715_do_calibration(void) {
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
    ad7715_wait_for_drdy();

    //
    // read dummy sample. /DRDY will go hi again after this
    //
    ad7715_read_sample();

    ad7715_put_on_hold();

    // back to 0
    hart_gpio_adc_channel_select(hart_channel_0);
}


////////////////////////////////////////////////////////////////////////////////
//
// ADC interrupt handler
//
////////////////////////////////////////////////////////////////////////////////
void INT_Handler_INT0(void) {
    if (hasStartedHartDiag) {
        OS_SignalEvent(HART_DIAG_CONVERSION_COMPLETE, &TCB_AD7715);
    }
}

#pragma vector=INT0_vect
__interrupt void IntHandler_INT0(void) {
    OS_CallISR(INT_Handler_INT0);
}



////////////////////////////////////////////////////////////////////////////////
//
// private utilities
//
////////////////////////////////////////////////////////////////////////////////
static void hart_diag_configure_adc(void) {
    ad7715_hard_reset();
    OS_Delay(10);
    ad7715_do_calibration();
    OS_Delay(10);
}

////////////////////////////////////////////////////////////////////////////////
//
// ADC raw to mA
//
////////////////////////////////////////////////////////////////////////////////
static void hart_diag_set_diag_value(hart_channel_t chnl, uint16_t raw_adc) {
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
    //float   voltage = 2.5f * ((float)(raw_adc)) / 65535.0;
    //float   current = voltage / 10.0 * 100.0f * TData.Hart.Gain[chnl]-TData.Hart.Offset[chnl];
    float   current = ((2.5f * ((float)(raw_adc)) / 65535.0) / 10.0 * 100.0f);// *(1.0 / 1.0028280); // * TData.Hart.Gain[chnl] - TData.Hart.Offset[chnl];
    // EHSMarkuint16_t    current_final = (uint16_t)(current * 10);       // 10 = 1mA, 1 = 0.1mA

    switch (chnl) {
    case hart_channel_0 :
    case hart_channel_1 :
    case hart_channel_2 :
    case hart_channel_3 :
    case hart_channel_4 :
    case hart_channel_5 :
    case hart_channel_6 :
    case hart_channel_7 :
    case hart_channel_8 :
    case hart_channel_9 :
    case hart_channel_10:
    case hart_channel_11:
        {
            current = current * TData.Hart.Gain[chnl] - TData.Hart.Offset[chnl];
            TData.Hart.ADCurrent[chnl] += (current - TData.Hart.ADCurrent[chnl]) / ((float)TData.Hart.Filter[chnl] + 1.0);
        }
        break;
    case 12:
    case 13:
        // Not connected
        break;
    case 14:
        {
            float Gain = 2.5 / current; 
            for (char ch = 0; ch < 12; ch++) {
                TData.Hart.Gain[ch]         = Gain; // Original gain on AN-ZBANA is 0.9985 or 0.9965
            }
        }
        break;
    case 15:
        {
            float Offset = current; 
            for (char ch = 0; ch < 12; ch++) {
                TData.Hart.Offset[ch] = Offset; // Original gain on AN-ZBANA is 0.9985 or 0.9965
            }
        }
        break;

    }
}

////////////////////////////////////////////////////////////////////////////////
//
// HART Diagnostic Task
//
////////////////////////////////////////////////////////////////////////////////
static void ad7715_read_diag_adc(hart_channel_t chnl) {

    hart_gpio_adc_channel_select(chnl);
    OS_Delay(10);
    ad7715_start_next_sample();
    if (ad7715_wait_for_drdy()) {
        uint16_t raw_adc = ad7715_read_sample();
        ad7715_put_on_hold();
        hart_diag_set_diag_value(chnl, raw_adc);
    }
}

static void HARTDiag_Task(void) {
    hart_channel_t      current;
    hasStartedHartDiag = true;
    hart_diag_init();

    //ad7715_hard_reset();
    while (1) {
        hart_for_each_channel(current) {
            ad7715_read_diag_adc(current);
            ad7715_toggle_debug_led();
            OS_Delay(200);
        }
#if 0 // for ADC debugging only
        //ad7715_read_diag_adc((hart_channel_t)12);
        //ad7715_read_diag_adc((hart_channel_t)13);
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
void hart_diag_init(void) {
    hart_diag_configure_adc();
    TData.Hart.PortUsed   = 0;
    TData.Hart.HartSensor = 0;
    for (char ch = 0; ch < 12; ch++) {
        TData.Hart.Filter[ch]       = 3;
        TData.Hart.Gain[ch]         = 1.0 / 1.0028280; // Original gain on AN-ZBANA is 0.9985 or 0.9965
        TData.Hart.Offset[ch]       = 0.0;
        TData.Hart.ADCurrent[ch]    = 4.0;
        TData.Hart.HartCmd[ch]      = 1;
    }
}

void hart_diag_task_start(void) {
    OS_CREATETASK(&TCB_AD7715, "HARTDiag", HARTDiag_Task, 135, _hart_diag_task_stack);
}
