; /********************************************************
; *        SEGGER MICROCONTROLLER SYSTEME GmbH
; *  Solutions for real time microcontroller applications
; *********************************************************
; File        : RTOSVect.asm
; Purpose     : Interrupt vector handling for embOS_ARM_IAR
; --------------END-OF-HEADER----------------------------*/

        MODULE RTOSVECT
        RSEG   CODE:CODE:NOROOT(2)
        EXTERN OS_IntHandler                   ; RTOS.ASM
        EXTERN OS_irq_handler                  ; RTOSINIT.C
        EXTERN UndefInstruction        ; RTOSINIT.C
        EXTERN swiHandler                  ; RTOSINIT.C
        EXTERN AbortPrefetch                  ; RTOSINIT.C
        EXTERN AbortData                  ; RTOSINIT.C
         CODE32                                 ; Always ARM mode on interrupt
        PUBLIC OS_IRQ_SERVICE

; *********************************************************
; *
; *     Defines for Flag (PSR) register
; *
; *********************************************************

IRQ_MODE  = 0x12            ; Interrupt Request mode
SVC_MODE  = 0x13            ; SVC mode (Supervisor)
I_FLAG    = 0x80            ; interrupt disable flag




; *********************************************************
; *
; *     Interrupt service routine
; *
; *********************************************************
;
; This routine should be activated by a IRQ. IRQ on the
; ARM 7/9 will jump to 18h, where a jump to this routine
; should be located.
;
; Note: in the MSR instructions,
; c   means control field:        bits 0..7  (mode, T, F, I)
; x   means extension field       bits 8..15
; s   means status    field       bits 16..23
; f   means flag      field       bits 24..31

OS_IRQ_SERVICE:
;
; Save temp. registers
;
        STMDB   SP!,{R0-R3,R12,LR}             ; push
;
; push SPSR (req. if we allow nested interrupts)
;
        MRS     R0, SPSR                       ; load SPSR
        STMDB   SP!,{R0}                       ; push SPSR_irq on IRQ stack
;
; Switch to supervisor mode (svc mode)
;
        MSR     CPSR_c, #SVC_MODE| I_FLAG      ; Write CPSR: MODE = SVC, interrupt disabled
        STMDB   SP!, {LR}                      ; push LR_svc on SVC stack


;
; Call "C" interrupt handler in RTOSINIT.c
#if  1                  // This allows calling thumb application code ...
        LDR     R0,=OS_irq_handler
        mov     LR,PC
        BX      R0
#else                  // This is faster, but does not allow thumb code to be called
        bl      OS_irq_handler
#endif
        LDMIA   SP!, {LR}                      ; pop LR_svc from svc stack
;
; Switch back to IRQ mode
;
        MSR     CPSR_c, #IRQ_MODE| I_FLAG      ; Write CPSR: MODE = IRQ, interrupt disabled
;
; pop SPSR
;
        LDMIA   SP!, {R1}                      ; pop SPSR_irq from IRQ stack
        MSR     SPSR_cxfs, R1
;
; Restore temp registers
;
        LDMIA   SP!, {R0-R3,R12,LR}            ; pop
        SUBS    PC, LR, #4                     ; RETI
        ENDMOD

; *********************************************************
; *
; *     Define interrupt vector
; *
; *********************************************************

        PROGRAM ?INTVECT
        COMMON  INTVEC:CODE:ROOT(2)
        EXTERN  OS_IRQ_SERVICE
        CODE32                  ; Always ARM mode after reset
        ORG     18h

irq_Handler
        B       OS_IRQ_SERVICE  ; Only works with ROM here

        ENDMOD

; *********************************************************

        END

; ***** EOF ***********************************************


