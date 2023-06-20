/*********************************************************************
*               SEGGER MICROCONTROLLER SYSTEME GmbH                  *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (C) 2005   SEGGER Microcontroller Systeme GmbH               *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS * Real time operating system for microcontrollers      *
*                                                                    *
*                                                                    *
*       Please note:                                                 *
*                                                                    *
*       Knowledge of this file may under no circumstances            *
*       be used to write a similar product or a real-time            *
*       operating system for in-house use.                           *
*                                                                    *
*       Thank you for your fairness !                                *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS version: 3.28h                                         *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File    : OS_Error.c
Purpose : embOS error handler. Not required in "R" (release) builds
          Feel free to modify this file acc. to your target system.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "RTOS.H"
#include "constants.h"

/*********************************************************************
*
*       Run-time error reaction (OS_Error)
*
**********************************************************************

 Run-time error reaction

 When this happens, a fatal error has occured and the kernel
 can not continue. In linux, the equivalent would be a
 "kernel panic"

 This routine can be modified to suit your needs ...
 E.g. a red LED could light up. When using an
 emulator, you may set a breakpoint here.
 In the release builds of the library (R), this routine is not required
 (as no checks are performed).
 In the stack check builds (S/SP), only error 120 may occur.
 In the debug builds(D/DP), all of the listed errors may occur.

 The following are the current errorcodes (V3.20) :
 (Please refer to the documentation for more info)
  
OS_ERR_STACK                          (120 = 0x78)
*** invalid or non-initialized data structures ***
OS_ERR_INV_TASK                       (128 = 0x80)
OS_ERR_INV_TIMER                      (129 = 0x81)
OS_ERR_INV_MAILBOX                    (130 = 0x82)
OS_ERR_INV_CSEMA                      (132 = 0x84)
OS_ERR_INV_RSEMA                      (133 = 0x85)

*** Using GetMail1, PutMail1, GetMailCond1 or PutMailCond1
*** on a non-1 byte mailbox  *********************

OS_ERR_MAILBOX_NOT1                   (135 = 0x87)

*** internal errors, please contact SEGGER Microcontrollersysteme ***
OS_ERR_MAILBOX_NOT_IN_LIST            (140 = 0x8C)
OS_ERR_TASKLIST_CORRUPT               (142 = 0x8E)

*** not matching routine calls or macro usage ****
OS_ERR_UNUSE_BEFORE_USE               (150 = 0x96)
OS_ERR_LEAVEREGION_BEFORE_ENTERREGION (151 = 0x97)
OS_ERR_LEAVEINT                       (152 = 0x98)
OS_ERR_DICNT                          (153 = 0x99)
OS_ERR_INTERRUPT_DISABLED             (154 = 0x9A)
OS_ERR_TASK_ENDS_WITHOUT_TERMINATE    (155 = 0x9B)

*** not a legal system call during interrupt *****
OS_ERR_ILLEGAL_IN_ISR                 (160 = 0xA0)

*** not a legal system call during timer *********
OS_ERR_ILLEGAL_IN_TIMER               (161 = 0xA1)

*** not a legal system call outside interrupt ****
OS_ERR_ILLEGAL_OUT_ISR                (162 = 0xA2) 

*** double used data structures **
OS_ERR_2USE_TASK                      (170 = 0xAA)
OS_ERR_2USE_TIMER                     (171 = 0xAB)
OS_ERR_2USE_MAILBOX                   (172 = 0xAC)
OS_ERR_2USE_BSEMA                     (173 = 0xAD)
OS_ERR_2USE_CSEMA                     (174 = 0xAE)
OS_ERR_2USE_RSEMA                     (175 = 0xAF)

*** Communication errors (OSCOM) **
OS_ERR_NESTED_RX_INT                  (180 = 0xB4)

*** Fixed block memory pool  ***
OS_ERR_MEMF_INV                       (190 = 0xBE)
OS_ERR_MEMF_INV_PTR                   (191 = 0xBF)
OS_ERR_MEMF_PTR_FREE                  (192 = 0xC0)
OS_ERR_MEMF_RELEASE                   (193 = 0xC1)

*** Task suspend / resume errors ***
OS_ERR_SUSPEND_TOO_OFTEN              (200 = 0xC8)
OS_ERR_RESUME_BEFORE_SUSPEND          (201 = 0xC9)

*/
__no_init int RestartCnt             @0x21FD;

void OS_Error(int ErrCode) {
    switch ( ErrCode ) {
    case ZB_REBOOT          :
    case ZB_ERR_MODEM_0     :
    case ZB_ERR_MODEM_1     :
    case ZB_ERR_MODEM_2     :
    case ZB_ERR_UART        :
    case ZB_ERR_EXT_ADC     :
    case ZB_ERR_INT_ADC     :
    case OS_ERR_2USE_TASK   : 
    case OS_ERR_2USE_TIMER  : 
    case OS_ERR_2USE_MAILBOX: 
    case OS_ERR_2USE_BSEMA  : 
    case OS_ERR_2USE_CSEMA  : 
    case OS_ERR_2USE_RSEMA  : 
    case OS_ERR_2USE_MEMF   :
    default:
        OS_EnterRegion();     /* Avoid further task switches            */
        OS_DICnt = 0;         /* Allow interrupts so we can communicate */
        OS_EI();
        OS_Status = (OS_U8)ErrCode;
        RestartCnt++;
        while ( OS_Status );
    }
}

/****** EOF *********************************************************/

