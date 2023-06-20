/*******************************************************
System clock initialization created by the
CodeWizardAVR V3.49 Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
*******************************************************/

// I/O Registers definitions
#include <avr64db64.h>
#include <delay.h>
#include <iobits.h>

// Standard definitions
#include <stddef.h>
#include "1WIRE_COM.h"

// Turn off power for ONEWIRE device and test presence
    char ResetONEWIRE (void)
    {   unsigned char result=0;  
        unsigned char loop=1;
        ONEWIRE_CLR;                // set pin low
        delay_us( TRSTL ); // wait delay max from Maxim, see *.h the value
        ONEWIRE_SET;    // Set pin high  
        delay_us (TMSP);
        if (ONEWIRE_READ == 0 )  // confirm presence
            result = 0x01;
        else
            result = 0x00;  
        // wait line release to High, if not sensor it is high with pull up.
        while (loop)        
        {   if (ONEWIRE_READ == 1 )
                loop=0; // exit
        } 
        delay_us(TREC);
        return result;  
    }
    
// Wire Byte to ONEWIRE device lsb first

    void    WriteTo_1Wire ( unsigned char data )
    {   unsigned char temp;
        unsigned char nb_bit=8;
		temp=data;
        while (nb_bit)
        {   
            if ( (temp & 0x01) == 0x01) // send "1"
            {   ONEWIRE_CLR;    // set pin low
                delay_us( TW1_LOW ); // 
                ONEWIRE_SET;    // Set pin high
                delay_us( TW1_SLOT ); // wait delay max from Maxim, see *.h the value
            }
            else    // send "0"
            {   ONEWIRE_CLR;    // set pin low
                delay_us( TW0_LOW ); // 
                ONEWIRE_SET;    // Set pin high
                delay_us( TW0_SLOT ); // wait delay max from Maxim, see *.h the value
            }
            temp>>=1;
            nb_bit--;
        }
    }
    
//read Byte
    char    Read_1Wire (void)
    {    unsigned char data=0;
        unsigned char nb_bit=8;
//		temp=data;
        while (nb_bit)
        {   // make pull from master: 
            ONEWIRE_CLR;    // set pin low
            delay_us( TW_RL ); //  set pin low
            ONEWIRE_SET;    // Set pin high           
            delay_us( TW_MSR ); // wait delay max from Maxim, see *.h the value  
			data>>=1;
            if ( ONEWIRE_READ ==1)
                data|=0x80;     // LSB FIRST move 8 time            
            //data>>=1;
            nb_bit--;  
            delay_us (TWR_SLOT);
        }  
        return data;
    }         
