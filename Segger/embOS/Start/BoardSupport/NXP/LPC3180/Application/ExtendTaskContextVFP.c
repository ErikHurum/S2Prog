/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co KG                  *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 1995 - 2008  SEGGER Microcontroller GmbH & Co KG         *
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
*       embOS version: 3.60d                                         *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File    : ExtendTaskContextVFP.c
Purpose : Sample program for embOS demonstrating how to dynamically
          extend the task context to use ARM VFP in the tasks.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "RTOS.h"

/*********************************************************************
*
*       Global variables
*/

OS_STACKPTR int StackHP[128], StackLP[128];          /* Task stacks */
OS_TASK TCBHP, TCBLP;                        /* Task-control-blocks */

float a, b;

/*********************************************************************
*
*       HPTask
*
*  Function description
*    During the execution of this function,
*    the VFP is thread-specific and may also be used by other tasks
*/
static void HPTask(void) {
  OS_ExtendTaskContext(&OS_VFP_ExtendContext);
  while (1) {
    b = 3 * a;    // Do something that uses VFP
    OS_Delay(10);
  }
}

/*********************************************************************
*
*       LPTask
*
*  Function description
*    During the execution of this function,
*    the VFP is thread-specific and may also be used by other tasks.
*    The task will be interrupted by higher priority tasks.
*/
static void LPTask(void) {
  OS_ExtendTaskContext(&OS_VFP_ExtendContext);
  while (1) {
    if ((a * 2) != 4) {
      while (1); // Error. Happens only when VFP Context is NOT saved.
    }
  }
}

/*********************************************************************
*
*       main
*/
int main(void) {
  a = 2;
  OS_IncDI();                      /* Initially disable interrupts  */
  OS_InitKern();                   /* initialize OS                 */
  OS_InitHW();                     /* initialize Hardware for OS    */
  /* You need to create at least one task here !                    */
  OS_CREATETASK(&TCBHP, "HP Task", HPTask, 100, StackHP);
  OS_CREATETASK(&TCBLP, "LP Task", LPTask,  50, StackLP);
  OS_Start();                      /* Start multitasking            */
  return 0;
}


