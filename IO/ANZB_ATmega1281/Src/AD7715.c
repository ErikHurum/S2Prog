/****************************************************************************************
/ AD converter handling , AD7715
/
***************************************************************************************/

#include <math.h>
#include "iom1281.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"


#if USE_MODBUS_PROTOCOL == 1
    #include "common_def.h"

    #define EEPROM_OFFSET_ADDR(ch)    ((0x80 | ch) * sizeof(float) * 2)
    #define EEPROM_GAIN_ADDR(ch)      (((0x80 | ch) * sizeof(float) * 2) + sizeof(float))

    #define EEPROM_RSP_DELAY_ADDR(port)   (EEPROM_OFFGAIN + 1024 + port * sizeof(uint16_t))

    #define ADC_OFFSET_MIN        -2.0f
    #define ADC_OFFSET_MAX        2.0f

    #define ADC_GAIN_MIN          0.98f
    #define ADC_GAIN_MAX          1.02f

    #define ADC_FILTER_MIN        0.0f
    #define ADC_FILTER_MAX        2.0f

static void load_eeprom_misc(void);
#endif

static inline signed char
fcompare(float a, float b) {
    //
    // returns -1 when a < b
    //          1 when a > b
    //          0 when equal
    //
#define FLT_EPSILON 0.000001f

    float d = a - b;

    if (d >= -FLT_EPSILON && d <= FLT_EPSILON) {
        return 0;
    }

    if (d < -FLT_EPSILON) {
        // a is less than b
        return -1;
    }

    // a is bigger than b
    return 1;
}

/*************************************************************************
*   (This is a task)
*  AD7715 task 
*
*************************************************************************/
void AD7715(void) {
    char ch;
    float Tempfloat;

    for (ch = 0; ch<12; ch++) {
        TData.Ana.Filter[ch] = 1.0;
    }
    TData.Ana.PortUsed = ReadEEPROMByte(EEPROM_PORTSETUP) + (ReadEEPROMByte(EEPROM_PORTSETUP + 1) << 8); // Get setup from EEPROM
    SetAnaPort();

    WriteAdByte(0xff);             // Write 32 1's to reset
    WriteAdByte(0xff);
    WriteAdByte(0xff);
    WriteAdByte(0xff);

    // Calibrate and check if the card is layout rev 1?
    WriteAdByte(0x10);             // Next write setup reg
    WriteAdByte(0x4e);             //  Ad setup data, unipolar, calibrate
    OS_Delay(250);
    OS_ClearEvents(&TCB_AD7715);
    OS_WaitEventTimed(1, 1000);

    ClrBit(PORTE, 0xf0);                 // check channel 14 for 2.5 V
    SetBit(PORTE, (14 << 4) & 0xf0);    // check
    WriteAdByte(0x10);                 // Next write data
    WriteAdByte(0x0e);                 // Ad setup data, unipolar
    OS_Delay(85);
    OS_ClearEvents(&TCB_AD7715);
    OS_WaitEventTimed(1, 250);
    WriteAdByte(0x38);                 // Next read data
    for (ch = 0; ch < 12; ch++) {       // Get the gain and offset from the EEPROM
        TData.Ana.Offset[ch] = 0.0;
        TData.Ana.Gain[ch] = 1.00175; //0.9985;
    }
    for (ch = 0; ch < 12; ch++) {       // Get the gain and offset from the EEPROM
        ReadEEPROMBuffer((ch | 0x80) * sizeof(float) * 2, sizeof(float), (char *)&Tempfloat);

#if 0 // hkim. you shouldn't do floating point comparison like this
        if (IsFloat(Tempfloat) && Tempfloat > -2.0 && Tempfloat < 2.0 ) {
            *((float*)&TData.Ana.Offset[ch]) = *((float*)&Tempfloat);  //offset
        }

        ReadEEPROMBuffer( ((ch | 0x80) * sizeof(float)*2) + sizeof(float), sizeof(float), (char*)&Tempfloat );

        if (IsFloat(Tempfloat) && Tempfloat > 0.98 && Tempfloat < 1.02){
            *((float *)&TData.Ana.Gain[ch]) = *((float *)&Tempfloat); //gain
        }
#else
        if (IsFloat(Tempfloat) && fcompare(Tempfloat, -2.0) > 0 && fcompare(Tempfloat, 2.0) < 0) {
            *((float *)&TData.Ana.Offset[ch]) = *((float *)&Tempfloat); //offset
        }

        ReadEEPROMBuffer(((ch | 0x80) * sizeof(float) * 2) + sizeof(float), sizeof(float), (char *)&Tempfloat);

        if (IsFloat(Tempfloat) && fcompare(Tempfloat, 0.98) > 0 && fcompare(Tempfloat, 1.02) < 0) {
            *((float *)&TData.Ana.Gain[ch]) = *((float *)&Tempfloat);  //gain
        }
#endif
    }

    //
    // let modbus task that I'm done initializing
    //
#if USE_MODBUS_PROTOCOL == 1
    load_eeprom_misc();

    {
        extern void modbus_rtu_notify_go(void);
        modbus_rtu_notify_go();
    }
#endif

    while (1) {
        ClrBit(PORTE, 0xf0);
        SetBit(PORTE, (15 << 4) & 0xf0); // 0V at ch 16
        WriteAdByte(0x10);             // Next write setup reg
        WriteAdByte(0x8e);             //  AStark test zero scale calibrate
        OS_Delay(250);
        OS_ClearEvents(&TCB_AD7715);
        OS_WaitEventTimed(1, 1000);

        ClrBit(PORTE, 0xf0);
        SetBit(PORTE, (14 << 4) & 0xf0); // 2.5V at ch 15
        WriteAdByte(0x10);             // Next write setup reg
        WriteAdByte(0xce);             //  AStark test full scale calibrate
        OS_Delay(250);
        OS_ClearEvents(&TCB_AD7715);
        OS_WaitEventTimed(1, 1000);


        for (ch = 0; ch < 12; ch++) {
            ClrBit(PORTE, 0xf0);
            SetBit(PORTE, (ch << 4) & 0xf0);
            WriteAdByte(0x10);                 // Next write data
            WriteAdByte(0x0e);                          // Ad setup data, unipolar
            OS_Delay(85);
            OS_ClearEvents(&TCB_AD7715);
            OS_WaitEventTimed(1, 250);
            WriteAdByte(0x38);             // Next read data

            unsigned int addata;
            addata = ReadAdByte() * 256;        // read data 16 bit data from ad
            addata += ReadAdByte();

#if USE_MODBUS_PROTOCOL == 1
            OS_Use(&adc_lock);
#endif

            TData.Ana.Status[ch] = 0;                   // Result ok
            TData.Ana.Result[ch] += ((((((float)addata / 65535.0) * 25.0) * TData.Ana.Gain[ch]) - TData.Ana.Offset[ch] - TData.Ana.Result[ch])
                                     / (TData.Ana.Filter[ch] + 1.0));             // readed value / 16bit * 2.5 volt range

#if USE_MODBUS_PROTOCOL == 1
            OS_Unuse(&adc_lock);
#endif
        }
    }
}
/*************************************************************************
*
*  Set ports on or off
*
*************************************************************************/
    void SetAnaPort(void) {

        PORTC = (TData.Ana.PortUsed & 0xff);         // Set power on ports 0-7
        ClrBit(PORTB, 0xe1);                            // Set power on ports 8-11 off
        SetBit(PORTB, TData.Ana.PortUsed >> 8 & 0x01);    // Set power on port 8
        SetBit(PORTB, TData.Ana.PortUsed >> 4 & 0xe0);      // Set power on ports 9-11

    }

/*************************************************************************
*
*  Read from AD-converter
*
*************************************************************************/

    void SPI_Write(char data) {       /* SPI write data function */
        char flush_buffer;
        SPDR = data;            /* Write data to SPI data register */
        while (!(SPSR & (1 << SPIF))); /* Wait till transmission complete */
        flush_buffer = SPDR;        /* Flush received data */
/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
    }

    char SPI_Read() {             /* SPI read data function */
        SPDR = 0xFF;
        while (!(SPSR & (1 << SPIF))); /* Wait till reception complete */
        return (SPDR);           /* Return received data */
    }

    char ReadAdByte(void) {
#if ANZBANA_V8 == 1
        return SPI_Read();
#else
        char readbyte = 0;

        for (char i = 0; i <  8; i++) {
            readbyte <<= 1;                    // shift to next bit
            ClrBit(PORTD, ADCLK);
            SetBit(PORTD, ADCLK);                  // set clock line high
            if (PING & ADDO) {                  // data  = 1?
                readbyte |= 0x01;                    // set bit high
            } else {
                readbyte &= ~0x01;                   // set bit low
            }
        }
        return readbyte;
#endif
    }

/*************************************************************************
*
*  Write to AD-converter
*
*************************************************************************/
    void WriteAdByte(char data) {
#if ANZBANA_V8 == 1
        SPI_Write(data);
#else

        for (char i = 0; i <  8; i++) {
            ClrBit(PORTD, ADCLK);                  // set clock line low
            if (data & 0x80) {                  // data bit = 1?
                SetBit(PORTG, ADDI);                  // set data high
            } else {
                ClrBit(PORTG, ADDI);                 // set data low
            }
            data <<= 1;                        // shift to next bit
            SetBit(PORTD, ADCLK);                  // set clock line high
        }
#endif
    }

/*************************************************************************
*  
* public utilities
*
*************************************************************************/
#if USE_MODBUS_PROTOCOL == 1
    static inline float
        u16_to_float_offset(uint16_t offset) {
        return ((float)offset - 20000.0f) / 10000.0f;
    }

    static inline uint16_t
        float_offset_to_u16(float offset) {
        return (uint16_t)(floor(offset * 10000 + 0.5f)) + 20000;
    }

    static inline float
        u16_to_float_gain(uint16_t gain) {
        return ((float)gain) / 10000.0f;
    }

    static inline uint16_t
        float_gain_to_u16(float gain) {
        return (uint16_t)(floor(gain * 10000.0f + 0.5f));
    }

    static inline float
        u16_to_float_filter(uint16_t filter) {
        return filter / 10000.0f;
    }

    static inline uint16_t
        float_filter_to_u16(float filter) {
        return (uint16_t)(floor(filter * 10000 + 0.5f));
    }

    static inline uint16_t
        float_ma_to_u16(float ma) {
        return (uint16_t)(floor(ma * 1000.0f + 0.5f));
    }

    static void
        load_eeprom_misc(void) {
        char ch;
        uint16_t temp;

        for (ch = 0; ch < 2; ch++) {
            ReadEEPROMBuffer(EEPROM_RSP_DELAY_ADDR(ch), sizeof(uint16_t), (char *)&temp);

            if (temp > 0 && temp <= 5000) {
                TData.Ana.Rsp_Delay[ch] = temp;
            } else {
                TData.Ana.Rsp_Delay[ch] = 0;
            }
        }
    }

//
// gain
//
    static inline void
        __adc_task_set_gain(uint8_t ch, uint16_t gain) {
        float gain_f;
        uint16_t gain_cur = float_gain_to_u16(TData.Ana.Gain[ch]);

        if (gain == gain_cur) {
            return;
        }

        gain_f = u16_to_float_gain(gain);
        if (fcompare(gain_f, ADC_GAIN_MIN) <= 0 || fcompare(gain_f, ADC_GAIN_MAX) >= 0) {
            // invalid value just silently ignore
            return;
        }

        TData.Ana.Gain[ch] = gain_f;
        WriteEEPROMBufferSync(EEPROM_GAIN_ADDR(ch), sizeof(float), (char *)&gain_f);
    }

    void
        adc_task_set_gain(uint8_t ch, uint16_t gain) {
        OS_Use(&adc_lock);
        __adc_task_set_gain(ch, gain);
        OS_Unuse(&adc_lock);
    }

    uint16_t
        adc_task_get_gain(uint8_t ch) {
        uint16_t ret;

        OS_Use(&adc_lock);
        ret = float_gain_to_u16(TData.Ana.Gain[ch]);
        OS_Unuse(&adc_lock);

        return ret;
    }

//
// offset
//
    static void
        __adc_task_set_offset(uint8_t ch, uint16_t offset) {
        float offset_f;
        uint16_t offset_cur = float_offset_to_u16(TData.Ana.Offset[ch]);

        if (offset == offset_cur) {
            return;
        }

        offset_f = u16_to_float_offset(offset);
        if (fcompare(offset_f, ADC_OFFSET_MIN) <= 0 || fcompare(offset_f, ADC_OFFSET_MAX) >= 0) {
            // invalid value just silently ignore
            return;
        }

        TData.Ana.Offset[ch] = offset_f;

        WriteEEPROMBufferSync(EEPROM_OFFSET_ADDR(ch), sizeof(float), (char *)&offset_f);
    }

    void
        adc_task_set_offset(uint8_t ch, uint16_t offset) {
        OS_Use(&adc_lock);
        __adc_task_set_offset(ch, offset);
        OS_Unuse(&adc_lock);
    }

    uint16_t
        adc_task_get_offset(uint8_t ch) {
        uint16_t ret;

        OS_Use(&adc_lock);
        ret =  float_offset_to_u16(TData.Ana.Offset[ch]);
        OS_Unuse(&adc_lock);

        return ret;
    }

//
// filter
//
    static void
        __adc_task_set_filter(uint8_t ch, uint16_t filter) {
        float filter_f;
        uint16_t filter_cur = float_filter_to_u16(TData.Ana.Filter[ch]);

        if (filter_cur == filter) {
            return;
        }

        filter_f = u16_to_float_filter(filter);
        if (fcompare(filter_f, ADC_FILTER_MIN) <= 0 || fcompare(filter_f, ADC_FILTER_MAX) >= 0) {
            // invalid value just silently ignore
            return;
        }

        TData.Ana.Filter[ch] = filter_f;
    }

    void
        adc_task_set_filter(uint8_t ch, uint16_t filter) {
        OS_Use(&adc_lock);
        __adc_task_set_filter(ch, filter);
        OS_Unuse(&adc_lock);
    }

    uint16_t
        adc_task_get_filter(uint8_t ch) {
        uint16_t ret;

        OS_Use(&adc_lock);
        ret = float_filter_to_u16(TData.Ana.Filter[ch]);
        OS_Unuse(&adc_lock);

        return ret;
    }

//
// power
//
    static void
        adc_task_control_port_power(uint8_t ch, uint8_t on) {
        switch (ch) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            // PORTC 0-7
            if (on) {
                SetBit(PORTC, _BV(ch));
            } else {
                ClrBit(PORTC, _BV(ch));
            }
            break;

        case 8:
            // PORTB 0
            if (on) {
                SetBit(PORTB, _BV(0));
            } else {
                ClrBit(PORTB, _BV(0));
            }
            break;

        case 9:
        case 10:
        case 11:
            // PORTB 5-7
            if (on) {
                SetBit(PORTB, _BV(ch - 4));
            } else {
                ClrBit(PORTB, _BV(ch - 4));
            }
            break;
        }
    }

    static void
        __adc_task_set_power(uint8_t ch, uint8_t on) {
        uint8_t current;

        current = (TData.Ana.PortUsed >> ch) & 0x01;

        if (current == on) {
            // no need to waste time
            return;
        }

        adc_task_control_port_power(ch, on);

        // save to eeprom
        if (on) {
            TData.Ana.PortUsed |= (1 << ch);
        } else {
            TData.Ana.PortUsed &= ~(1 << ch);
        }

        WriteEEPROMByte(EEPROM_PORTSETUP + 0, (TData.Ana.PortUsed & 0xff));
        WriteEEPROMByte(EEPROM_PORTSETUP + 1, (TData.Ana.PortUsed >> 8) & 0xff);
    }

    void
        adc_task_set_power(uint8_t ch, uint8_t on) {
        OS_Use(&adc_lock);
        __adc_task_set_power(ch, on);
        OS_Unuse(&adc_lock);
    }

    uint8_t
        adc_task_get_power(uint8_t ch) {
        uint8_t status;

        OS_Use(&adc_lock);
        status = (TData.Ana.PortUsed >> ch) & 0x01;
        OS_Unuse(&adc_lock);

        return status;
    }

//
// status
//
    uint8_t
        adc_task_get_status(uint8_t ch) {
        uint8_t status;

        OS_Use(&adc_lock);
        status = TData.Ana.Status[ch];
        OS_Unuse(&adc_lock);

        return status;
    }

//
// ma
//
    uint16_t
        adc_task_get_ma(uint8_t ch) {
        float ma_f;

        OS_Use(&adc_lock);
        ma_f = TData.Ana.Result[ch];
        OS_Unuse(&adc_lock);

        return float_ma_to_u16(ma_f);
    }

    static void
        __adc_task_set_rsp_delay(char port, uint16_t delay) {
        uint16_t cur_delay = TData.Ana.Rsp_Delay[port];

        if (cur_delay == delay) {
            return;
        }

        if (delay > 5000) {
            return;
        }

        TData.Ana.Rsp_Delay[port] = delay;

        WriteEEPROMBufferSync(EEPROM_RSP_DELAY_ADDR(port), sizeof(uint16_t), (char *)&delay);
    }

    void
        adc_task_set_rsp_delay(char port, uint16_t delay) {
        OS_Use(&adc_lock);
        __adc_task_set_rsp_delay(port, delay);
        OS_Unuse(&adc_lock);
    }

    uint16_t
        adc_task_get_rsp_delay(char port) {
        uint16_t    ret;

        OS_Use(&adc_lock);
        ret = TData.Ana.Rsp_Delay[port];
        OS_Unuse(&adc_lock);

        return ret;
    }

#endif /* USE_MODBUS_PROTOCOL == 1 */


    
