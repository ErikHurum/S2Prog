;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Part one of the system initialization code, 
;; contains low-level
;; initialization.
;;
;; Copyright 2007 IAR Systems. All rights reserved.
;;
;; $Revision: 19651 $
;;

        MODULE  ?cstartup

        ;; Forward declaration of sections.

    SECTION FIQ_STACK:DATA:NOROOT(3)
    SECTION IRQ_STACK:DATA:NOROOT(3)
    SECTION SVC_STACK:DATA:NOROOT(3)
    SECTION ABT_STACK:DATA:NOROOT(3)
    SECTION UND_STACK:DATA:NOROOT(3)
    SECTION CSTACK:DATA:NOROOT(3)

;
; The module in this file are included in the libraries, and may be
; replaced by any user-defined modules that define the PUBLIC symbol
; __iar_program_start or a user defined start symbol.
;
; To override the cstartup defined in the library, simply add your
; modified version to the workbench project.

        SECTION .intvec:CODE:NOROOT(2)

        PUBLIC  __vector
        PUBLIC  __vector_0x14
        PUBLIC  __iar_program_start
        EXTERN  Undefined_Handler
        EXTERN  SWI_Handler
        EXTERN  Prefetch_Handler
        EXTERN  Abort_Handler
        EXTERN  IRQ_Handler
        EXTERN  FIQ_Handler

        ARM
__vector:
        ; All default exception handlers (except reset) are
        ; defined as weak symbol definitions.
        ; If a handler is defined by the application it will take precedence.
        LDR     PC,Reset_Addr           ; Reset
        LDR     PC,Undefined_Addr       ; Undefined instructions
        LDR     PC,SWI_Addr             ; Software interrupt (SWI/SVC)
        LDR     PC,Prefetch_Addr        ; Prefetch abort
        LDR     PC,Abort_Addr           ; Data abort
__vector_0x14:
        DCD     0                       ; RESERVED
        LDR     PC,IRQ_Addr             ; IRQ
        LDR     PC,FIQ_Addr             ; FIQ

Reset_Addr:     DCD   __iar_program_start
Undefined_Addr: DCD   Undefined_Handler
SWI_Addr:       DCD   SWI_Handler
Prefetch_Addr:  DCD   Prefetch_Handler
Abort_Addr:     DCD   Abort_Handler
IRQ_Addr:       DCD   IRQ_Handler
FIQ_Addr:       DCD   FIQ_Handler


; --------------------------------------------------
; ?cstartup -- low-level system initialization code.
;
; After a reset execution starts here, the mode is ARM, supervisor
; with interrupts disabled.
;



        SECTION .text:CODE:NOROOT(2)

;        PUBLIC  ?cstartup        
        EXTERN  ?main
        REQUIRE __vector

        ARM        
        
__iar_program_start:        
?cstartup:

;
; Add initialization needed before setup of stackpointers here.
;

;
; Initialize the stack pointers.
; The pattern below can be used for any of the exception stacks:
; FIQ, IRQ, SVC, ABT, UND, SYS.
; The USR mode uses the same stack as SYS.
; The stack segments must be defined in the linker command file,
; and be declared above.
;


; --------------------
; Mode, correspords to bits 0-5 in CPSR

MODE_MSK DEFINE 0x1F            ; Bit mask for mode bits in CPSR

USR_MODE DEFINE 0x10            ; User mode
FIQ_MODE DEFINE 0x11            ; Fast Interrupt Request mode
IRQ_MODE DEFINE 0x12            ; Interrupt Request mode
SVC_MODE DEFINE 0x13            ; Supervisor mode
ABT_MODE DEFINE 0x17            ; Abort mode
UND_MODE DEFINE 0x1B            ; Undefined Instruction mode
SYS_MODE DEFINE 0x1F            ; System mode


; Initialize the stack pointers.
; The pattern below can be used for any of the exception stacks:
; FIQ, IRQ, SVC, ABT, UND, SYS.
; The USR mode uses the same stack as SYS.
; The stack segments must be defined in the linker command file,
; and be declared above.

                mrs     r0,cpsr                             ; Original PSR value  
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits 
                orr     r0,r0,#SVC_MODE                     ; Set SVC mode bits   
                msr     cpsr_c,r0                           ; Change the mode     
                ldr     sp,=SFE(SVC_STACK)                  ; End of SVC_STACK    
                                                                                  
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits 
                orr     r0,r0,#UND_MODE                     ; Set UND mode bits   
                msr     cpsr_c,r0                           ; Change the mode     
                ldr     sp,=SFE(UND_STACK)                  ; End of UND_STACK    
                                                                                  
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits 
                orr     r0,r0,#ABT_MODE                     ; Set ABT mode bits   
                msr     cpsr_c,r0                           ; Change the mode     
                ldr     sp,=SFE(ABT_STACK)                  ; End of ABT_STACK    
                                                                                  
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits 
                orr     r0,r0,#FIQ_MODE                     ; Set FIQ mode bits   
                msr     cpsr_c,r0                           ; Change the mode     
                ldr     sp,=SFE(FIQ_STACK)                  ; End of FIQ_STACK    
                                                                                  
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits 
                orr     r0,r0,#IRQ_MODE                     ; Set IRQ mode bits   
                msr     cpsr_c,r0                           ; Change the mode     
                ldr     sp,=SFE(IRQ_STACK)                  ; End of IRQ_STACK    
                                                                                  
                bic     r0,r0,#MODE_BITS                    ; Clear the mode bits 
                orr     r0,r0,#SYS_MODE                     ; Set System mode bits
                msr     cpsr_c,r0                           ; Change the mode     
                ldr     sp,=SFE(CSTACK)                     ; End of CSTACK       
                                                                                  
#ifdef __ARMVFP__                                                                 
; Enable the VFP coprocessor.                                                     
                mov     r0, #0x40000000                 ; Set EN bit in VFP       
                fmxr    fpexc, r0                       ; FPEXC, clear others.    
                                                                                  
; Disable underflow exceptions by setting flush to zero mode.                     
; For full IEEE 754 underflow compliance this code should be removed              
; and the appropriate exception handler installed.                                
                mov     r0, #0x01000000		                  ; Set FZ bit in VFP    
                fmxr    fpscr, r0                       ; FPSCR, clear others.    
#endif

; Add more initialization here


; Continue to ?main for more IAR specific system startup

                ldr     r0,=?main
                bx      r0

    END         ;- Terminates the assembly of the last module in a file

