//===================================================================
// File Name : 2410lib.c
// Function  : S3C2410 PLL,Uart, LED, Port Init
// Program   : Shin, On Pil (SOP)
// Date      : May 14, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (February 20,2002) -> SOP
//===================================================================

#include "def.h"
#include "option.h"
#include "2410addr.h"
#include "2410lib.h"
#include "2410slib.h"

#include "TsnConstants.h"
#include "Anpro10Const.h"
#include "rtos.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//extern char Image$$RW$$Limit[];
//void *mallocPt=Image$$RW$$Limit;

//===========================[ PORTS ]===================================================*
///////////////////////////////////////////////////
//
// From TSNGlobalVariables.cpp
//
///////////////////////////////////////////////////

extern short CurrentDeviceId;
extern short CurrentDeviceAddress;
extern int OS_FSys;
#ifdef S2TXU
extern short GlobalDeviceHWId;
#else
short GlobalDeviceHWId              = 0;
#endif
void Port_Init(void)
{

    rGPECON = 0x0;
    rGPEUP  = 0x0;
    short Tmp = rGPEDAT;

    GlobalDeviceHWId  = (rGPEDAT >>14) & 0x3;

    switch ( GlobalDeviceHWId ) {
        case TCU_R1://TCU
        case TCU_R2://TCU CurrentDeviceId should be 0x21
            CurrentDeviceId  =  DEVICE_TCU; //EHSMARK
            CurrentDeviceAddress = ~(rGPEDAT >>10) & 0xf;

            rGPACON = 0x1ffff;

            rGPBCON = 0x1;       // REQ0/1 not set here
            rGPBUP  = 0x0;
            rGPBDAT |= 1;       // OK LED, System not OK yet


            rGPCCON = 0x0;
            rGPCUP  = 0x0;

            rGPDCON = 0x0;
            rGPDUP  = 0x0;
            /*
            rGPECON = 0x55001;
            rGPEUP  = 0x0;
            rGPEDAT = 0x0;
            */
            rGPECON = 0x54555;
            rGPEUP  = 0x0;
            rGPEDAT = 0x0;

            rGPFCON = 0xaaaa;   // Eint 0~7
            rGPFUP  = 0xff;     // Pullup 0~7

            rGPGCON = 0x00020002; // EINT8 && EINT16
            rGPGUP  = 0x0001; // Pullup int8 & int16    // hkim


            rGPHCON = 0x1aaa0;
            rGPHDAT &= ~0x100;  // Set not bit 8 for write protect
            rGPHUP  = 0x0;
            //External interrupt will be falling edge triggered.
            rEXTINT0 = 0x42424444;    // EINT[7:0] UART 1-4
            rEXTINT1 = 0x22222222;    // EINT[15:8]
#ifdef __NET_USE_ACTIVE_HIGH_INTERRUPT__
            rEXTINT2 = 0x22222229;    // EINT[23:16] // hkim EINT16 active high with filter
#else
            rEXTINT2 = 0x22222224;
#endif
            switch ( GlobalDeviceHWId ) {
            default:
            case TCU_R1:
                OS_FSys = OS_FSYS_180;
                break;
            case TCU_R2:
                OS_FSys = OS_FSYS_202;
                break;
            }
            break;
        case TDU_R1://TDU
        case TDU_R2://TDU CurrentDeviceId should be 0x31
            CurrentDeviceId      = DEVICE_TDU;
            CurrentDeviceAddress = ~(rGPEDAT >>10) & 0xf;
            /*
            if (CurrentDeviceAddress == 0xf) {
               CurrentDeviceAddress = 0;
            } 
            */ 
            rGPACON = 0x1ffff;

            rGPBCON = 0x0;
            rGPBUP  = 0x0;

            rGPCCON = 0xaaaaaaaa;
            rGPCUP  = 0x0;

            rGPDCON = 0xaaaaaaaa;
            rGPDUP  = 0x0;

            rGPECON = 0x55001;
            rGPEUP  = 0x0;
            rGPEDAT = 0x0;

            rGPFCON = 0x0;
            rGPFUP  = 0x0;

            rGPGCON = 0xff020000; // set touch screen lines on
            rGPGUP  = 0x0001;

            rGPHCON = 0x1aaa4;
            rGPHDAT &= ~0x100;  // Set not bit 8 for write protect
            rGPHUP  = 0x0;
            //External interrupt will be falling edge triggered.
            rEXTINT0 = 0x22222222;    // EINT[7:0]
            rEXTINT1 = 0x22222222;    // EINT[15:8]
            rEXTINT2 = 0x22222224;    // EINT[23:16]    // hkim EINT16 active high
            switch ( GlobalDeviceHWId ) {
            case TDU_R1:
                OS_FSys = OS_FSYS_180;
                break;
            case TDU_R2:
                OS_FSys   = OS_FSYS_180;
                //OS_FSys = OS_FSYS_202;
                break;
            }
            break;
    /*  case 3: // Eval Board
            rGPACON = 0x7fffff;

            rGPBCON = 0x044555;
            rGPBUP  = 0x7ff;     // The pull up function is disabled GPB[10:0]

            rGPCCON = 0xaaaaaaaa;
            rGPCUP  = 0xffff;     // The pull up function is disabled GPC[15:0]

            rGPDCON = 0xaaaaaaaa;
            rGPDUP  = 0xffff;     // The pull up function is disabled GPD[15:0]

            rGPECON = 0xaaaaaaaa;
            rGPEUP  = 0xffff;     // The pull up function is disabled GPE[15:0]

            rGPFCON = 0x55aa;
            rGPFUP  = 0xff;     // The pull up function is disabled GPF[7:0]

            rGPGCON = 0xff95ffba;
            rGPGUP  = 0xffff;    // The pull up function is disabled GPG[15:0]

            rGPHCON = 0x2afaaa;
            rGPHUP  = 0x7ff;    // The pull up function is disabled GPH[10:0]
            //External interrupt will be falling edge triggered.
            rEXTINT0 = 0x22222222;    // EINT[7:0]
            rEXTINT1 = 0x22222222;    // EINT[15:8]
            rEXTINT2 = 0x22222222;    // EINT[23:16]
            break;
*/
    }

}


//========================*[ Timer ]==============================**
void Timer_Start(int divider)  //0:16us,1:32us 2:64us 3:128us
{
    rWTDAT = 0xffff;  //Watch-dog timer data register
    rWTCNT = 0xffff;  //Watch-dog count register

    //Watch-dog timer enable & interrupt  disable
    rWTCON = ((PCLK/1000000-1)<<8)|(divider<<3) | ((1<<5) | 1 );  //Watch-dog timer control register
}

//=================================================================
int Timer_Stop(void)
{
    rWTCON = ((PCLK/1000000-1)<<8);
    return(0xffff - rWTCNT);
}


//========================*[ MPLL ]==============================*
void ChangeMPllValue(int mdiv,int pdiv,int sdiv)
{
    rMPLLCON = (mdiv<<12) | (pdiv<<4) | sdiv;
}


//========================[ HCLK, PCLK ]===========================
void ChangeClockDivider(int hdivn,int pdivn)
{
    // hdivn,pdivn FCLK:HCLK:PCLK
    //     0,0         1:1:1
    //     0,1         1:1:2
    //     1,0         1:2:2
    //     1,1         1:2:4
    rCLKDIVN = (hdivn<<1) | pdivn;

    if ( hdivn )
        MMU_SetAsyncBusMode();
    else
        MMU_SetFastBusMode();
}


//========================**[ UPLL ]==============================*
void ChangeUPllValue(int mdiv,int pdiv,int sdiv)
{
    rUPLLCON = (mdiv<<12) | (pdiv<<4) | sdiv;
}


//========================*[ General Library ]=====================*
/*
void * malloc(unsigned nbyte)
//Very simple; Use malloc() & free() like Stack
//void *mallocPt=Image$$RW$$Limit;
{
    void *returnPt = mallocPt;

    mallocPt = (int *)mallocPt+nbyte/4+((nbyte%4)>0); //To align 4byte

    if( (int)mallocPt > HEAPEND )
    {
        mallocPt = returnPt;
        return NULL;
    }
    return returnPt;
}


//-------------------------------------------------------------------
void free(void *pt)
{
    mallocPt = pt;
}
*/
