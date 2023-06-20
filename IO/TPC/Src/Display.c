/****************************************************************************************
/  Display. routines
/
***************************************************************************************/
#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
#include "inavr.h"
#include "string.h"


/*************************************************************************
*   (This is a task)
*  Info-rmation
*
*************************************************************************/
void Info(void) {
    char Buf[7];

    Buf[0] = 'V';
    Buf[1] = '-';
    CharToAscii(PROG_VERSION, &Buf[2]);
    Buf[5] = 0;
    PrintComError(Buf, ALARM_OFF);      //AStmark test only
    OS_Delay(4000);
    CharToAscii(MyPriAddress, &Buf[0]);
    Buf[0] = Buf[1];                    // rotate left due to max 2 char in address
    Buf[1] = Buf[2];
    Buf[2] = ' ';
    CharToAscii(MySecAddress, &Buf[3]);
    Buf[6] = 0;
    PrintComError(Buf, ALARM_OFF);      //AStmark test only

    while ( 1 ) {
        OS_WaitEvent(1);  // wait for keyhit
        kbd_delay_cnt = true;
        OS_Delay(250);
        kbd_delay_cnt = false;
    }
}

/*************************************************************************
*   (This is a task)
*  Display blink
*
*************************************************************************/
void DisplayBlink(void) {

    while ( 1 ) {
        OS_Delay(125);
        BlinkStatus = 0x7f;
        OS_Delay(125 * 3);
        BlinkStatus = 0x00;
    }
}

/*************************************************************************
*   (This is a task)
*  Display handler
*
*************************************************************************/
void DisplayHandler(void) {
    static char pointer = 0, alarmLEDImg = 0;

    while ( 1 ) {
        OS_Delay(1);

        switch ( UnitID ) {
            /*     case TPC350:
                     PDR5 &= ~0x7f ;                                     // display driver off
                     if (Disp.image[pointer + 25] & 0x80) {                // Upper sergment and flashing ??
                         PDR6 = (~(Disp.image[pointer + 25] & flash)& 0x7f  ) ;
                     } else {
                         PDR6 = (~Disp.image[pointer + 25] & 0x7f ) ;
                     }
                     PDR6 |= 0x80 ;                                      // write pulse
                     PDR6 &= ~0x80 ;
                     if (Disp.image[pointer] & 0x80) {                     // Lower segment and flashing ??
                         PDR6 = (~(Disp.image[pointer] & flash)& 0x7f  ) ;
                     } else {
                         PDR6 = (~Disp.image[pointer] & 0x7f ) ;
                     }
                     PDR5 |= (pointer & 0x07) ;                          // set sinc drive
                     PDR5 |= DispDrv350[(pointer >> 3) & 0x03] ;
                     if (++pointer >= 25) {
                         pointer = 0 ;                                   // start over again
                     }
                     break;
           */
        case TPC196:
            // PORTA = 0x00 ;
            // PORTC = 0x00 ;
                if ( pointer < 20 ) {
                    PORTD = ~Disp.image[pointer + 20];                    // No flashing due to . is 0x80
                    //PORTB |= 0x80;                                      // write pulse - LE
                    //PORTB &= ~0x80;
                    if ( Disp.image[pointer] & 0x80 ) {                     // flashing
                        PORTD = ~(Disp.image[pointer] & 0x7f & BlinkStatus);
                    } else {
                        PORTD = ~(Disp.image[pointer] & 0x7f);
                    }
                    PORTA = DispDrv140[pointer][0];                      // Use the same decoding as tPC140
                    PORTC = DispDrv140[pointer][1];

                    ClrBit(PORTG, 0x0f);
                    SetBit(PORTG, DispDrv140[pointer][2]);

                } else {                                // another run for the green and yellow
                    PORTD = ~Disp.image[pointer];                    // No flasing due to . is 0x80
                    PORTB |= 0x80;                                      // write pulse - LE
                    PORTB &= ~0x80;
                    PORTD = 0x7f;
                    PORTA = DispDrv140[pointer - 20][0];                      // Use the same decoding as tPC140
                    PORTC = DispDrv140[pointer - 20][1];
                    ClrBit(PORTG, 0x0f);
                    SetBit(PORTG, DispDrv140[pointer - 20][2]);
                }
            if ( ++pointer >= 28 ) {
                pointer = 0;                                   // start over again
            }
            break;
        case TPC140:
            PORTA = 0x00;
            PORTC = 0x00;
            ClrBit(PORTG, 0x0f);
            if ( Disp.image[pointer] & 0x80 ) {                     // flashing
                PORTD = ~((Disp.image[pointer] & 0x7f & BlinkStatus) << 1);
            } else {
                PORTD = ~((Disp.image[pointer] & 0x7f) << 1);
            }
            PORTA = DispDrv140[pointer][0];
            PORTC = DispDrv140[pointer][1];
            SetBit(PORTG, DispDrv140[pointer][2]);
            if ( ++pointer >= 20 ) {
                pointer = 0;                                   // start over again
            }
            break;
        default:
            break;
        }
        if ( Disp.alarmLED == ALARM_FLASH ) {
            if ( BlinkStatus ) {
                SetBit(PORTG, ALARM_LED);
            } else {
                ClrBit(PORTG, ALARM_LED);
            }
        }
        if ( Disp.alarmLED != alarmLEDImg ) {
            switch ( Disp.alarmLED ) {
            case ALARM_ON:
                SetBit(PORTG, ALARM_LED);
                break;
            case ALARM_FLASH :
                SetBit(PORTG, ALARM_LED);
                break;
            case ALARM_OFF:
                ClrBit(PORTG, ALARM_LED);
                break;
            }
            alarmLEDImg = Disp.alarmLED;
        }
    }
}

/*************************************************************************
*
*  Build Low display image
*
*************************************************************************/
void printLoDi(char val) {
    char i, j, nop, pos, nob, ct, LEDDum[20];
    if ( (Disp.lo_grdata[20] == val) && (val != ALARM_VT) ) {  // graph to display
        for ( i = 0; i < 20; i++ ) {
            LEDDum[i] = Disp.lo_grdata[i];                  // copy graph
        }
        if ( UnitID == TPC140 ) {                        // Mirror byte
            for ( j = 0; j < 20; j++ ) {
                ct = 0x00;
                if ( LEDDum[j] & 0x80 ) {
                    ct |= 0x01;
                }
                for ( i = 0; i < 7; i++ ) {
                    ct <<= 1;
                    if ( LEDDum[j] & 0x01 ) {
                        ct |= 0x01;
                    }
                    LEDDum[j] >>= 1;
                }
                LEDDum[j] = ct;
            }
        }
        for ( i = 0; i < 20; i++ ) {
            Disp.image[i] = LEDDum[i];                   // disp if
        }
    } else {
        nob = Disp.lo_data[val][0];                          // no of char to disp

        nop = 0;                                       // select char set
        for ( i = 0; (i < NO_OF_LOCH) && (i < nob);) {
            nop += ascii_table[Disp.lo_data[val][i + 1] - 0x20][WIDE_CHAR][0];   // number of pixels
            if ( ++i < nob ) {                            // inc i here!!
                nop++;                                 // add space
            }
        }
        if ( nop > 20 ) {
            ct = TINY_CHAR;
        } else {
            ct = WIDE_CHAR;
        }
        pos = 20;                                      // start from left (pos 19 first!!)
        for ( i = 0; (i < NO_OF_LOCH) && (i < nob) && (pos > 0);) {
            if ( (Disp.lo_data[val][i + 1] >= 0x20) && (Disp.lo_data[val][i + 1] <= 0x7f) ) {
                nop = ascii_table[Disp.lo_data[val][i + 1] - 0x20][ct][0];   // number of pixels
                for ( j = 0; (j < nop) && (pos > 0); j++ ) {
                    LEDDum[--pos] = ascii_table[Disp.lo_data[val][i + 1] - 0x20][ct][j + 1];
                }
            }
            if ( (++i < nob) && (pos > 0) ) {             // inc i here!!  V6: add check of pos
                LEDDum[--pos] = 0x00;                   // space if more char
            }
        }
        if ( pos > 0 ) {
            rorLoDis(LEDDum, pos);
        }

        switch ( UnitID ) {
        case TPC140:                        // Mirror byte
            for ( j = 0; j < 20; j++ ) {
                ct = 0x00;
                if ( LEDDum[j] & 0x80 ) {
                    ct |= 0x01;
                }
                for ( i = 0; i < 7; i++ ) {
                    ct <<= 1;
                    if ( LEDDum[j] & 0x01 ) {
                        ct |= 0x01;
                    }
                    LEDDum[j] >>= 1;
                }
                LEDDum[j] = ct;
            }
            for ( i = 0; i < 20; i++ ) {
                Disp.image[i] = LEDDum[i];                   // copy to displaybuffer
            }
            break;
        case TPC196:                        
            for ( i = 0; i < 20; i++ ) {
                // Rearrange columns due to hw fault
                if ( i>=8 && i < 19 ) {
                    Disp.image[i] = LEDDum[DispArr196[i - 8]]; 
                }else{
                    Disp.image[i] = LEDDum[i];                   // copy to displaybuffer
                }
            }
            break;
        }
        if ( val == ALARM_VT ) {
            if ( Disp.alarmLED == ALARM_FLASH ) {
                for ( i = 0; i < 20; i++ ) {
                    Disp.image[i] |= 0x80;               // disp blink on
                }
            } else {
                for ( i = 0; i < 20; i++ ) {
                    Disp.image[i] &= ~0x80;              // disp blink off
                }
            }
        }
    }
}

/*************************************************************************
*
*  Build X display image
*
*************************************************************************/
void printXDi(char disno) {
    unsigned char i, pos, nob, LEDDum[4];

    if ( UnitID == TPC196 ) {
        nob = Disp.x_data[disno][0];                            // no of char to disp

        for ( i = 0; i < 4; i++ ) {                               // reset buffer
            LEDDum[i] = 0x00;
        }

        pos = 0;                                           // start from left
        for ( i = 0; (i < NO_OF_XCH) && (i < nob);) {
            if ( (Disp.x_data[disno][i + 1] >= 0x20) && (Disp.x_data[disno][i + 1] <= 0x7f) ) {
                LEDDum[pos] = ascii_table[Disp.x_data[disno][i + 1] - 0x20][SEVEN_SEG][0];
                i++;
            }
            if ( pos == 0 ) {
                if ( (Disp.x_data[disno][i] == 0x2c) || (Disp.x_data[disno][i] == 0x2e) ) {
                    LEDDum[pos] |= 0x80;                                          // check ./, on first char
                }
            }
            if ( i < nob ) {
                if ( (Disp.x_data[disno][i + 1] == 0x2c) || (Disp.x_data[disno][i + 1] == 0x2e) ) {   // , or .
                    LEDDum[pos] |= 0x80;
                    i++;
                }
            }
            if ( ++pos >= 4 ) {                             // no room for more characters
                i = NO_OF_XCH;
            }
        }
        for (; pos < 4; pos++ ) {                 // shift text right
            for ( i = 3; i > 0; i-- ) {
                LEDDum[i] = LEDDum[i - 1];
                LEDDum[i - 1] = 0x00;                        // clear leftmost char
            }
        }
        for ( i = 0; i < 4; i++ ) {
            Disp.image[20 + 4 * disno + i] = LEDDum[i];            // copy to displaybuffer
        }
    }
}

/*************************************************************************
*
*  Rotate right low display
*
*************************************************************************/
void rorLoDis(char *buf, char pos) {
    unsigned char i;
    for ( i = pos; i < 20; i++ ) {
        buf[i - pos] = buf[i];
    }
    for ( i = 0; i < pos; i++ ) {
        buf[19 - i] = 0x00;
    }
}

/*************************************************************************
*
* Refresh displays
*
*************************************************************************/
void RefreshDisplay(char value) {
    switch ( UnitID ) {
    case TPC350:
        /*      Write2416Data(value) ;        
              printBar(value) ;
              printBarSec(value) ;*/
        break;
    case TPC196:
        printXDi(0);
        printXDi(1);
        break;
    default:
        break;
    }
    printLoDi(value);
}

/*************************************************************************
*
*  Print measage on display
*
*************************************************************************/
void PrintComError(char *data, char led) {

    Disp.lo_data[ALARM_VT][0] = strlen(data); //5 ;                  // char to disp
    Disp.lo_data[ALARM_VT][1] = data[0];
    Disp.lo_data[ALARM_VT][2] = data[1];
    Disp.lo_data[ALARM_VT][3] = data[2];
    Disp.lo_data[ALARM_VT][4] = data[3];
    Disp.lo_data[ALARM_VT][5] = data[4];
    Disp.lo_data[ALARM_VT][6] = data[5];

    switch ( UnitID ) {
    case TPC350:
        Disp.hi_data[ALARM_VT][0] = 0;                  // char to disp
        Disp.ba_pdata[ALARM_VT] = 0;
        Disp.ba_sdata[ALARM_VT] = 0;
        break;
    case TPC196:
        Disp.x_data[0][0] = 0;                  // char to disp
        Disp.x_data[1][0] = 0;                  // char to disp
        break;
    default:
        break;
    }

    Disp.alarmLED = led;
    Disp.disp_vt = ALARM_VT;
    Disp.disp_vt_old = Disp.disp_vt + 1;                 // force printout
    printLoDi(0);

}

