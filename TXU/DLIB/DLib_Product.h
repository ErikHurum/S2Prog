/*********************************************************************
*               SEGGER MICROCONTROLLER SYSTEME GmbH                  *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (C) 2006   SEGGER Microcontroller Systeme GmbH               *
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
*       embOS version: 3.32a                                         *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File    : DLIB_Product.h
Purpose : embOS specific configuration header for IAR libraries.
          Enables generation of thread safe system libraries.
          Do not modify any entry here.
          
--------  END-OF-HEADER  ---------------------------------------------
*/

#ifndef _DLIB_PRODUCTS_H_               /* Avoid multiple inclusion */
#define _DLIB_PRODUCTS_H_

/*********************************************************************
*
*       Configuration
*
*********************************************************************/

#define _DLIB_THREAD_SUPPORT 2   /* enable system and file locking  */ 

/*********************************************************************
*
*       Defines for locking functions.       
*
*********************************************************************/

#define _DLIB_THREAD_LOCK_ONCE_TYPE      unsigned
#define _DLIB_THREAD_LOCK_ONCE_MACRO(pControl_variable, init_function) {if (*pControl_variable == 0) init_function(); *pControl_variable = 1;}
#define _DLIB_THREAD_LOCK_ONCE_TYPE_INIT 0

/********************************************************************/

#endif  /* avoid multiple inclusion */

/****** EOF *********************************************************/

