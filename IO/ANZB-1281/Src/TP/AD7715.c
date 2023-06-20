/*
  ******************************************************************************
  * @file    ad7715.c
  * @author   
  * @brief   AD7715 routines
  ******************************************************************************
  */
#include "AD7715.h"
#include <string.h>
#include "PinName.h"

// I/O Registers definitions
#include <avr64db64.h>
#include <delay.h>
#include <iobits.h>
// SPI initialization functions
#include "spi_init.h"

// Standard definitions
#include <stddef.h>

///** Local variables */
//static     uint16_t adcreadout;

/**
  * Reset AD7715.... send 32 "ones" 
  */
void AD7715_Reset(void)
{
    ADC_CS_LOW; 
    delay_us(50);
    ADC_RST_LOW;
    delay_ms(10);
    ADC_RST_HIGH;
    ADC_CS_HIGH; 
    delay_us(50); 
}

/**
  * AD7715 Thread: perform continuous conversion, calculate calibrated values and 
  * and store the values to buffer.
  */
//void AD7715_Init (unsigned char polarity ) 
//{
//
////    unsigned char adcbuf[2];
//    AD7715_CommReg_t CommReg; 
//    AD7715_SetupReg_t SetupReg; 
////    unsigned int rd;
//    
//    /* Reset AD7715 */
//    AD7715_Reset();
//    
//    /** Write to setup register */
//    CommReg.b.DRDY = 0;
//    CommReg.b.Zero = 0;
//    CommReg.b.RS = AD7715_REG_SETUP;    // 2BIT: 01
//    CommReg.b.RW = AD7715_RW_WRITE;    
//    CommReg.b.STBY = AD7715_STBY_POWERUP;
//    CommReg.b.Gain = AD7715_GAIN_1; 
//
//  /** Setup register */  
//    if (polarity ==1) 
//        SetupReg.b.BU = AD7715_BU_BIPOLAR; 
//    else
//        SetupReg.b.BU = AD7715_BU_UNIPOLAR;
//        
//    SetupReg.b.BUF = AD7715_BUF_BYPASSED;
//    SetupReg.b.CLK = AD7715_CLK_1MHZ;
//    SetupReg.b.FS = AD7715_FS_20HZ;         // 1Mclk
//    SetupReg.b.FSYNC = 0;
//    SetupReg.b.MD = AD7715_MODE_SELFCAL;
//  
//    ADC_CS_LOW; delay_us(5);        // Set CS low
//    spi1_master_tx_rx(CommReg.B);
//    spi1_master_tx_rx(SetupReg.B);  
//    
//    delay_us(50); ADC_CS_HIGH;
// 
//
//  /* Set normal operation */
//     SetupReg.b.MD = AD7715_MODE_NORMAL;
//    
//    ADC_CS_LOW; 
//    delay_us(50);
//    spi1_master_tx_rx(CommReg.B);
//    spi1_master_tx_rx(SetupReg.B);
//    delay_us(50);
//    ADC_CS_HIGH;
//}
//
//int ReadData (unsigned char gain)
//    
// {      unsigned char adcbuf[2];
//        AD7715_CommReg_t CommReg; 
////        AD7715_SetupReg_t SetupReg; 
//        unsigned int rd=0XAAAA;
//        
//        
//        /** Read from comm register, poll DRDY */
//        CommReg.b.DRDY = 0;
//        CommReg.b.Zero = 0;
//        CommReg.b.RS = AD7715_REG_COMM;
//        CommReg.b.RW = AD7715_RW_READ;    
//        CommReg.b.STBY = AD7715_STBY_POWERUP; 
//        if (gain == 1)
//            CommReg.b.Gain = AD7715_GAIN_1; 
//        else if (gain == 2)
//            CommReg.b.Gain = AD7715_GAIN_2; 
//        else if (gain == 32)
//            CommReg.b.Gain = AD7715_GAIN_32; 
//        else if (gain == 128)
//            CommReg.b.Gain = AD7715_GAIN_128;   
//        else
//            CommReg.b.Gain = AD7715_GAIN_1;
//        ADC_CS_LOW;delay_us(5);
//        spi1_master_tx_rx(CommReg.B);
//        CommReg.B = spi1_master_tx_rx(0xff);
//        delay_us(50);  ADC_CS_HIGH;
//        
//        if ((CommReg.b.DRDY) == 0) 
//        {
//            // read data
//            CommReg.b.DRDY = 0;
//            CommReg.b.Zero = 0;
//            CommReg.b.RS = AD7715_REG_DATA;
//            CommReg.b.RW = AD7715_RW_READ;    
//            CommReg.b.STBY = AD7715_STBY_POWERUP;
//            if (gain == 1)
//                CommReg.b.Gain = AD7715_GAIN_1; 
//            else if (gain == 2)
//                CommReg.b.Gain = AD7715_GAIN_2; 
//            else if (gain == 32)
//                CommReg.b.Gain = AD7715_GAIN_32; 
//            else if (gain == 128)
//                CommReg.b.Gain = AD7715_GAIN_128;   
//            else
//                CommReg.b.Gain = AD7715_GAIN_1;
//
//            ADC_CS_LOW;delay_us(5);
//            //spi1_master_tx_rx(CommReg.B);
//            spi1_master_tx_rx(0X38);
//            adcbuf[1] = spi1_master_tx_rx(0xff);
//            adcbuf[0] = spi1_master_tx_rx(0xff);
//            delay_us(50);
//            ADC_CS_HIGH;
//            memcpy(&rd, adcbuf, 2);            
//        } 
//        return rd;           
//}

//void ADConvert (void);