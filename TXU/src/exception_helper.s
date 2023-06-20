;=====================================================================
; File Name : exception_helper.s
;
; - initially for exception stack backtrace by hkim, June/2016
;
;=====================================================================
  rseg ICODE:CODE(2)
  code32


;=====================================================================
;
; exception handlers
;
;=====================================================================
MODE_BITS	DEFINE	0x1F		; Bit mask for mode bits in CPSR
SYS_MODE	DEFINE	0x1F		; System mode

    EXTERN _ever_aborted
    EXTERN _data_abort_occurred
    EXTERN _prefetch_abort_occurred
    EXTERN _undef_abort_occurred
    EXTERN _exception_backup_regs
    EXTERN handle_abort
    EXPORT data_handler
    EXPORT prefetch_handler
    EXPORT undef_handler

data_handler:
  sub r14, r14, #8            ; data abort has offset -8 for PC

  ; mark that data abort occurred
  push {r0, r1}
  ldr  r0, =_data_abort_occurred
  mov  r1, #1
  str  r1, [r0]
  pop  {r0, r1}

  b  common_exception_handler

prefetch_handler:
  sub r14, r14, #4            ; prefertch abort has offset -4 for PC

  ; mark that prefetch abort occurred
  push {r0, r1}
  ldr  r0, =_prefetch_abort_occurred
  mov  r1, #1
  str  r1, [r0]
  pop  {r0, r1}

  b  common_exception_handler

undef_handler:
  sub r14, r14, #4            ; undef abort has offset -4 for PC

  ; mark that undef abort occurred
  push {r0, r1}
  ldr  r0, =_undef_abort_occurred
  mov  r1, #1
  str  r1, [r0]
  pop  {r0, r1}

  b  common_exception_handler


common_exception_handler:
  ; check if we ever double faulted
  push  {r0, r1}
  ldr r0, =_ever_aborted
  ldr r1, [r0]
  cmp r1, #0
  blne handle_abort
  pop {r0,r1}

  ; save r0
  push {r0}

  ; load r0 with our backup register address
  ldr   r0, =_exception_backup_regs
  ; save register to out debug memory
  stm   r0!, {r0-r14}
  ; now we can mess with other registers
  mrs   r1, cpsr
  mrs   r2, spsr
  stm   r0!, {r1, r2}

  ; restore original r0 to r2
  pop   {r2}

  ; refresh r0 so we can move r1 there
  ldr   r0, =_exception_backup_regs
  ; save original r0 in r2 to debug memory
  str   r2, [r0]

  ; now switch back to system mode to get system
  ; mode stack pointer. emBOS runs in system mode
  mov     r0, #0
  orr     r0,r0,#SYS_MODE                     ; Set System mode bits
  msr     cpsr_c,r0

  ; store system mode stack pointer to our debug memory
  ; load r0 with our memory address just for convenience
  ldr   r0, =_exception_backup_regs
  add   r0, r0, #68
  stm   r0!, {r13-r14}

  ; r1 has pervious cpsr
  msr     cpsr_c, r1
  ;
  ; now call C based exception handler
  bl handle_abort

  END
