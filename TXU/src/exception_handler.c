////////////////////////////////////////////////////////////////////////////////
//
// ARM exception analyer. At the moment, it's just a simple helper to ease
// the backtracking process.
//
// Revision History
// - June/1/2016 : humble initial release
//
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "RTOS.H"

////////////////////////////////////////////////////////////////////////////////
//
// externs from exception_helper.s
//
////////////////////////////////////////////////////////////////////////////////
#define CRASH_SC2410()                    \
{                                         \
  char* __crash__ = (char*)0x70000000;    \
  *__crash__ = 123;                       \
}

typedef void*     regparm_t;

typedef struct 
{
  regparm_t       r0;
  regparm_t       r1;
  regparm_t       r2;
  regparm_t       r3;
  regparm_t       r4;
  regparm_t       r5;
  regparm_t       r6;
  regparm_t       r7;
  regparm_t       r8;
  regparm_t       r9;
  regparm_t       r10;
  regparm_t       r11;
  regparm_t       r12;
  regparm_t       r13_sp;
  regparm_t       r14_lr_sys_mode_pc;
  regparm_t       cpsr;
  regparm_t       spsr;
  regparm_t       r13_sp_sys;
  regparm_t       r14_lr_sys;
} ARMRegisters;

////////////////////////////////////////////////////////////////////////////////
//
// module privates
//
////////////////////////////////////////////////////////////////////////////////
volatile unsigned int           _ever_aborted               = 0;
volatile unsigned int           _data_abort_occurred        = 0;
volatile unsigned int           _prefetch_abort_occurred    = 0;
volatile unsigned int           _undef_abort_occurred       = 0;
ARMRegisters                    _exception_backup_regs;
volatile OS_TASKID              _problem_task = NULL;

////////////////////////////////////////////////////////////////////////////////
//
// simple memory logger
//
////////////////////////////////////////////////////////////////////////////////
void
handle_abort()
{
  // accordig to emBOS ARM manual,
  // emBOS and all the applications run in system bode
  // and ARM exceptions are running in
  // each exception mode.
  // So here, we need to extract banked system mode registers
  // to gather evidence on what really caused the freaking exception
  // -hkim
  if(_ever_aborted)
  {
    // never return
    for(;;);
  }

  _problem_task = OS_GetTaskID();
  (void)_problem_task;
  _ever_aborted = 1;
  
  // never return
  for(;;);
}
