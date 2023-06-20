;;  Copyright ARM Ltd 2003. All rights reserved.
;;  This code provides benchmarking for most Integrator core modules and platforms
;;  
;;  All cached cores have the cache enabled and the whole memory map set up cacheable with Write-Through strategy
;;
;;  This code must be run from a privileged mode


        AREA   PERFORMANCE, CODE, READONLY
        ENTRY
        CODE32


;; Possible compilation options
;;        IF :DEF: CM7TDMI
;;        IF :DEF: CM740T
;;        IF :DEF: CM940T
;;        IF :DEF: CM946ES
;;        IF :DEF: CM966ES
;;        IF :DEF: CM720T
;;        IF :DEF: CM920T
;;        IF :DEF: CM922T
;;        IF :DEF: CM926EJS
;;        IF :DEF: CM1020T
;;        IF :DEF: CM1020E

;;        CACHE_ENABLED

;-------------------------------------------------
; Private SDRAM and PCI setup
;-------------------------------------------------
        IF :DEF: CM1020E
; private SDRAM initialization
        LDR     r0,=0x0360000A
        LDR     r1,=0x3FC00000
        STR     r0,[r1]                     ; This sequence maps private SDRAM at address 0x30000000
        ENDIF




;-------------------------------------------------
; MMU/MPU, SDRAM and Cache setup
;-------------------------------------------------

        IF :DEF: CM740T

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean


       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
       BIC     r0, r0, #0x1                ; clear bit 0 
       MCR     p15, 0, r0, c1, c0, 0       ; write value back
       MOV     r0,#0                       ; disable any other regions 
       MCR     p15, 0, r0, c6, c1, 0
       MCR     p15, 0, r0, c6, c2, 0
       MCR     p15, 0, r0, c6, c3, 0
       MCR     p15, 0, r0, c6, c4, 0
       MCR     p15, 0, r0, c6, c5, 0
       MCR     p15, 0, r0, c6, c6, 0
       MCR     p15, 0, r0, c6, c7, 0

; Set up region 0 and enable: base address = 0, size = 4GB
        MOV     r0,#2_00111111
        MCR     p15, 0, r0, c6, c0, 0        ; region 0

; Set up cacheable/bufferable attributes
        MOV     r0, #2_00000001;
        MCR     p15, 0, r0, c2, c0, 0       ; cacheable
        MCR     p15, 0, r0, c3, c0, 0       ; bufferable (the cache is always Write-through)

; Set up access permissions = full access
        MOV     r0, #2_0000000000000011
        MCR     p15, 0, r0, c5, c0, 0        ; data access permissions

; set global core configurations 
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<3)          ; enable Write Buffer
        ORR     r0, r0, #(0x1 <<2)          ; enable Cache        
        ORR     r0, r0, #0x1                ; enable MPU
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        IF :DEF: CM940T

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean


       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
       BIC     r0, r0, #0x1                ; clear bit 0
       MCR     p15, 0, r0, c1, c0, 0       ; write value back

       MOV     r0,#0                       ; disable any other regions
       MCR     p15, 0, r0, c6, c1, 0
       MCR     p15, 0, r0, c6, c1, 1
       MCR     p15, 0, r0, c6, c2, 0
       MCR     p15, 0, r0, c6, c2, 1 
       MCR     p15, 0, r0, c6, c3, 0
       MCR     p15, 0, r0, c6, c3, 1 
       MCR     p15, 0, r0, c6, c4, 0
       MCR     p15, 0, r0, c6, c4, 1 
       MCR     p15, 0, r0, c6, c5, 0
       MCR     p15, 0, r0, c6, c5, 1 
       MCR     p15, 0, r0, c6, c6, 0
       MCR     p15, 0, r0, c6, c6, 1 
       MCR     p15, 0, r0, c6, c7, 0  
       MCR     p15, 0, r0, c6, c7, 1  

       MCR     p15, 0, r0, c7, c5, 0
       MCR     p15, 0, r0, c7, c6, 0        ; invalidate caches


; Set up region 0 and enable: base address = 0, size = 4GB
        MOV     r0,#2_00111111
        MCR     p15, 0, r0, c6, c0, 0        ; data region 0
        MCR     p15, 0, r0, c6, c0, 1        ; inst region 0

; Set up cacheable/bufferable attributes
        MOV     r0, #2_00000001;
        MCR     p15, 0, r0, c2, c0, 0        ; data cacheable
        MCR     p15, 0, r0, c2, c0, 1        ; instr cacheable 
        MOV     r0, #2_00000000;
        MCR     p15, 0, r0, c3, c0, 0        ; data not bufferable (Write-through)

; Set up access permissions = full access
        MOV     r0, #2_0000000000000011
        MCR     p15, 0, r0, c5, c0, 0        ; data access permissions
        MCR     p15, 0, r0, c5, c0, 1        ; instr access permissions

; set global core configurations 
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<12)         ; enable I Cache
        ORR     r0, r0, #(0x1 <<2)          ; enable D Cache        
        ORR     r0, r0, #(2_11 <<30)        ; enable asynchronous clocking mode
        ORR     r0, r0, #0x1                ; enable MPU
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        IF :DEF: CM946ES

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean

       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
       BIC     r0, r0, #0x1                ; clear bit 0
       BIC     r0, r0, #(0x1 <<12)         ; disble I Cache
       BIC     r0, r0, #(0x1 <<2)          ; disble D Cache        
       MCR     p15, 0, r0, c1, c0, 0       ; write value back

       MOV     r0,#0                       ; disable any other regions
       MCR     p15, 0, r0, c6, c1, 0
       MCR     p15, 0, r0, c6, c1, 1
       MCR     p15, 0, r0, c6, c2, 0
       MCR     p15, 0, r0, c6, c2, 1 
       MCR     p15, 0, r0, c6, c3, 0
       MCR     p15, 0, r0, c6, c3, 1 
       MCR     p15, 0, r0, c6, c4, 0
       MCR     p15, 0, r0, c6, c4, 1 
       MCR     p15, 0, r0, c6, c5, 0
       MCR     p15, 0, r0, c6, c5, 1 
       MCR     p15, 0, r0, c6, c6, 0
       MCR     p15, 0, r0, c6, c6, 1 
       MCR     p15, 0, r0, c6, c7, 0  
       MCR     p15, 0, r0, c6, c7, 1  

; Set up region 0 and enable: base address = 0, size = 4GB
        MOV     r0,#2_00111111
        MCR     p15, 0, r0, c6, c0, 0        ; region 0

; Set up cacheable/bufferable attributes
        MOV     r0, #2_00000001;
        MCR     p15, 0, r0, c2, c0, 0        ; data cacheable
        MCR     p15, 0, r0, c2, c0, 1        ; instr cacheable 
        MOV     r0, #2_00000000;
        MCR     p15, 0, r0, c3, c0, 0        ; data no bufferable (Write-through)

; Set up access permissions = full access
        MOV     r0, #2_0000000000000011
        MCR     p15, 0, r0, c5, c0, 0        ; data access permissions
        MCR     p15, 0, r0, c5, c0, 1        ; instr access permissions

; set global core configurations 
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<12)         ; enable I Cache
        ORR     r0, r0, #(0x1 <<2)          ; enable D Cache        
        ORR     r0, r0, #0x1                ; enable MPU
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        IF :DEF: CM966ES

; set global core configurations 
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<3)          ; enable Write Buffer
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        IF :DEF: CM720T

ttb_first_level EQU     0x00004000          ; base address for level 1 translation table


; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean and TLB flush

       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
       BIC     r0, r0, #(0x1 <<3)          ; disable write buffer
       BIC     r0, r0, #(0x1 <<2)          ; disable unified cache
       BIC     r0, r0, #0x1                ; disable MMU
       MCR     p15, 0, r0, c1, c0, 0       ; write value back
       
       MOV     r0,#0
       MCR     p15,0, r0, c7, c7, 0        ; invalidate caches

init_ttb
        LDR     r0,=ttb_first_level         ; set start of Translation Table base (16k Boundary)
        MCR     p15, 0, r0, c2, c0, 0       ; write to CP15 register 2

; Create translation table for flat mapping
; Create 4096 entries from 000xxxxx to fffxxxxx

        LDR     r1,=0xfff                   ; loop counter 4096 entries of 1MB size. Total 4GB
        MOV     r2,#2_110000000000          ; set access permissions (AP) for full access SVC/USR (11:10)
        ORR     r2,r2,#2_000111100000       ; set for domain 15 (8:5)
        ORR     r2,r2,#2_000000010000       ; must be 1 (4)
        ORR     r2,r2,#2_000000001100       ; set CB bits to Write-through mode with write buffer enabled (3:2)
        ORR     r2,r2,#2_000000000010       ; set for 1Mb section (1:0)
init_ttb_1
        ORR     r3,r2,r1,lsl#20             ; use loop counter to create individual table entries
        STR     r3,[r0,r1,lsl#2]            ; str r3 at TTB base + loopcount*4
        SUBS    r1,r1,#1                    ; decrement loop counter
        BPL     init_ttb_1

;init_domains
        MOV     r0,#(2_01 << 30)            ; must define behaviour for domain 15 (31:30), set client
        MCR     p15, 0, r0, c3, c0, 0       ; write to CP15 register 5

; set global core configurations 
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<3)          ; enable write buffer
        ORR     r0, r0, #(0x1 <<2)          ; enable unified cache
        ORR     r0, r0, #0x1                ; enable MMU
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        IF :DEF: CM920T

ttb_first_level EQU     0x00004000          ; base address for level 1 translation table

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean and TLB flush

       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
       BIC     r0, r0, #0x1                ; clear bit MMU enable bit
       BIC     r0, r0, #0x1000             ; disable I cache
       BIC     r0, r0, #0x0004             ; disable D cache
       MCR     p15, 0, r0, c1, c0, 0       ; write value back

init_ttb
        LDR     r0,=ttb_first_level         ; set start of Translation Table base (16k Boundary)
        MCR     p15, 0, r0, c2, c0, 0       ; write to CP15 register 2

; Create translation table for flat mapping
; Create 4096 entries from 000xxxxx to fffxxxxx

        LDR     r1,=0xfff                   ; loop counter
        MOV     r2,#2_110000000000          ; set access permissions (AP) for full access SVC/USR (11:10)
        ORR     r2,r2,#2_000111100000       ; set for domain 15 (8:5)
        ORR     r2,r2,#2_000000010000       ; must be 1 (4)
        ORR     r2,r2,#2_000000001000       ; set write-through (CB) (3:2)
        ORR     r2,r2,#2_000000000010       ; set for 1Mb section (1:0)
init_ttb_1
        ORR     r3,r2,r1,lsl#20             ; use loop counter to create individual table entries
        STR     r3,[r0,r1,lsl#2]            ; str r3 at TTB base + loopcount*4
        SUBS    r1,r1,#1                    ; decrement loop counter
        BPL     init_ttb_1

;init_domains
        MOV     r0,#(2_01 << 30)            ; must define behaviour for domain 15 (31:30), set client
        MCR     p15, 0, r0, c3, c0, 0       ; write to CP15 register 5

; set global core configurations
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<12)         ; enable I Cache
        ORR     r0, r0, #(0x1 <<2)          ; enable D Cache
        ORR     r0, r0, #(2_11 <<30)        ; enable asynchronous clocking mode
        ORR     r0, r0, #0x1                ; enable MMU
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        IF :DEF: CM922T

ttb_first_level EQU     0x00004000          ; base address for level 1 translation table

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean and TLB flush

       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
       BIC     r0, r0, #0x1                ; clear bit MMU enable bit
       BIC     r0, r0, #0x1000             ; disable I cache
       BIC     r0, r0, #0x0004             ; disable D cache
       MCR     p15, 0, r0, c1, c0, 0       ; write value back

       MOV     r0,#0
       MCR     p15, 0, r0, c7, c7, 0       ; invalidate caches
       MCR     p15, 0, r0, c7, c5, 0       ; invalidate instruction cache

init_ttb
        LDR     r0,=ttb_first_level         ; set start of Translation Table base (16k Boundary)
        MCR     p15, 0, r0, c2, c0, 0       ; write to CP15 register 2

; Create translation table for flat mapping
; Create 4096 entries from 000xxxxx to fffxxxxx

        LDR     r1,=0xfff                   ; loop counter
        MOV     r2,#2_110000000000          ; set access permissions (AP) for full access SVC/USR (11:10)
        ORR     r2,r2,#2_000111100000       ; set for domain 15 (8:5)
        ORR     r2,r2,#2_000000010000       ; must be 1 (4)
        ORR     r2,r2,#2_000000001000       ; set write-through (CB) (3:2)
        ORR     r2,r2,#2_000000000010       ; set for 1Mb section (1:0)
init_ttb_1
        ORR     r3,r2,r1,lsl#20             ; use loop counter to create individual table entries
        STR     r3,[r0,r1,lsl#2]            ; str r3 at TTB base + loopcount*4
        SUBS    r1,r1,#1                    ; decrement loop counter
        BPL     init_ttb_1

;init_domains
        MOV     r0,#(2_01 << 30)            ; must define behaviour for domain 15 (31:30), set client
        MCR     p15, 0, r0, c3, c0, 0       ; write to CP15 register 5

; set global core configurations
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<12)         ; enable I Cache
        ORR     r0, r0, #(0x1 <<2)          ; enable D Cache
        ORR     r0, r0, #(2_11 <<30)        ; enable asynchronous clocking mode
        ORR     r0, r0, #0x1                ; enable MMU
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        IF :DEF: CM926EJS

ttb_first_level EQU     0x00004000          ; base address for level 1 translation table

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean and TLB flush

       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
       BIC     r0, r0, #0x1                ; clear bit MMU enable bit
       BIC     r0, r0, #0x1000             ; disable I cache
       BIC     r0, r0, #0x0004             ; disable D cache
       MCR     p15, 0, r0, c1, c0, 0       ; write value back

init_ttb
        LDR     r0,=ttb_first_level         ; set start of Translation Table base (16k Boundary)
        MCR     p15, 0, r0, c2, c0, 0       ; write to CP15 register 2

; Create translation table for flat mapping
; Create 4096 entries from 000xxxxx to fffxxxxx

        LDR     r1,=0xfff                   ; loop counter
        MOV     r2,#2_110000000000          ; set access permissions (AP) for full access SVC/USR (11:10)
        ORR     r2,r2,#2_000111100000       ; set for domain 15 (8:5)
        ORR     r2,r2,#2_000000010000       ; must be 1 (4)
        ORR     r2,r2,#2_000000001000       ; set write-through (CB) (3:2)
        ORR     r2,r2,#2_000000000010       ; set for 1Mb section (1:0)
init_ttb_1
        ORR     r3,r2,r1,lsl#20             ; use loop counter to create individual table entries
        STR     r3,[r0,r1,lsl#2]            ; str r3 at TTB base + loopcount*4
        SUBS    r1,r1,#1                    ; decrement loop counter
        BPL     init_ttb_1

;init_domains
        MOV     r0,#(2_01 << 30)            ; must define behaviour for domain 15 (31:30), set client
        MCR     p15, 0, r0, c3, c0, 0       ; write to CP15 register 5

; set global core configurations 
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<12)         ; enable I Cache
        ORR     r0, r0, #(0x1 <<2)          ; enable D Cache        
        ORR     r0, r0, #0x1                ; enable MMU
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        IF :DEF: CM1020T

ttb_first_level EQU     0x00004000          ; base address for level 1 translation table

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean and TLB flush

       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
       BIC     r0, r0, #0x1                ; clear bit 0 
       MCR     p15, 0, r0, c1, c0, 0       ; write value back

       MOV     r0,#0
       MCR     p15, 0, r0, c7, c7, 0       ; invalidate caches
       MCR     p15, 0, r0, c7, c5, 0       ; invalidate instruction cache

init_ttb
        LDR     r0,=ttb_first_level         ; set start of Translation Table base (16k Boundary)
        MCR     p15, 0, r0, c2, c0, 0       ; write to CP15 register 2

; Create translation table for flat mapping
; Create 4096 entries from 000xxxxx to fffxxxxx

        LDR     r1,=0xfff                   ; loop counter
        MOV     r2,#2_110000000000          ; set access permissions (AP) for full access SVC/USR (11:10)
        ORR     r2,r2,#2_000111100000       ; set for domain 15 (8:5)
        ORR     r2,r2,#2_000000010000       ; must be 1 (4)
        ORR     r2,r2,#2_000000001000       ; set write-through (CB) (3:2)
        ORR     r2,r2,#2_000000000010       ; set for 1Mb section (1:0)
init_ttb_1
        ORR     r3,r2,r1,lsl#20             ; use loop counter to create individual table entries
        STR     r3,[r0,r1,lsl#2]            ; str r3 at TTB base + loopcount*4
        SUBS    r1,r1,#1                    ; decrement loop counter
        BPL     init_ttb_1

;init_domains
        MOV     r0,#(2_01 << 30)            ; must define behaviour for domain 15 (31:30), set client
        MCR     p15, 0, r0, c3, c0, 0       ; write to CP15 register 5

; set global core configurations 
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<12)         ; enable I Cache
        ORR     r0, r0, #(0x1 <<2)          ; enable D Cache        
        ORR     r0, r0, #0x1                ; enable MMU
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        IF :DEF: CM1020E

ttb_first_level EQU     0x00004000          ; base address for level 1 translation table

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean and TLB flush

       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
       BIC     r0, r0, #0x1                ; clear bit 0 
       MCR     p15, 0, r0, c1, c0, 0       ; write value back

       MOV     r0,#0
       MCR     p15, 0, r0, c7, c7, 0       ; invalidate caches
       MCR     p15, 0, r0, c7, c5, 0       ; invalidate instruction cache

init_ttb
        LDR     r0,=ttb_first_level         ; set start of Translation Table base (16k Boundary)
        MCR     p15, 0, r0, c2, c0, 0       ; write to CP15 register 2

; Create translation table for flat mapping
; Create 4096 entries from 000xxxxx to fffxxxxx

        LDR     r1,=0xfff                   ; loop counter
        MOV     r2,#2_110000000000          ; set access permissions (AP) for full access SVC/USR (11:10)
        ORR     r2,r2,#2_000111100000       ; set for domain 15 (8:5)
        ORR     r2,r2,#2_000000010000       ; must be 1 (4)
        ORR     r2,r2,#2_000000001000       ; set write-through (CB) (3:2)
        ORR     r2,r2,#2_000000000010       ; set for 1Mb section (1:0)
init_ttb_1
        ORR     r3,r2,r1,lsl#20             ; use loop counter to create individual table entries
        STR     r3,[r0,r1,lsl#2]            ; str r3 at TTB base + loopcount*4
        SUBS    r1,r1,#1                    ; decrement loop counter
        BPL     init_ttb_1

;init_domains
        MOV     r0,#(2_01 << 30)            ; must define behaviour for domain 15 (31:30), set client
        MCR     p15, 0, r0, c3, c0, 0       ; write to CP15 register 5

; set global core configurations 
        IF CACHE_ENABLED = {TRUE}
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        ORR     r0, r0, #(0x1 <<12)         ; enable I Cache
        ORR     r0, r0, #(0x1 <<3)          ; enable write buffer
        ORR     r0, r0, #(0x1 <<2)          ; enable D Cache        
        ORR     r0, r0, #0x1                ; enable MMU
        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1
        ENDIF

        ENDIF
;-------------------------------------------------

        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP     ; Program trigger at this address


; List of addresses

; Set up clocks at FCLK = 80MHz, HCLK = 20MHz, SYSCLK = 20MHz
; Clocks, SDRAM DIMM and PCI system initialized by Boot Monitor
; ARM1020E private SDRAM -> Measure with SW loops -> Final tests
; Excalibur on-chip memory? -> Measure with SW loops -> Final tests

CM_SSRAM         EQU      0x00002000
CM_SDRAM         EQU      0x00200000
CM_SDRAM_ALIAS   EQU      0x80000000
CM_PRIVATE_SDRAM EQU      0x30000000    ;Only CM1020E
CM_REGISTERS     EQU      0x10000000

AP_FLASH         EQU      0x24000000
AP_SSRAM         EQU      0x28000000
AP_LM_SSRAM      EQU      0xC2000000
AP_REGISTERS     EQU      0x11000000
AP_PCI_MEMORY    EQU      0x40000000

CP_FLASH         EQU      0x24000000
CP_LM_SSRAM      EQU      0xD2000000
CP_REGISTERS     EQU      0xCB000000

XA_SDRAM         EQU      0x04000000
XA_SRAM          EQU      0x08000000
XA_DPSRAM        EQU      0x08100000
XA_FLASH         EQU      0x0F100000


; List of commands

LOAD_WORD        EQU      0
STORE_WORD       EQU      1
LOAD_HALF        EQU      2
STORE_HALF       EQU      3
LOAD_BYTE        EQU      4
STORE_BYTE       EQU      5

; Write the command to execute at address 0
; Write the address to read from/write to at address 4

        MOV     r0, #0
        LDR     r0, [r0]                    ; Load command to execute (r0) and activate oscilloscope trigger
        MOV     r12, #4
        LDR     r12, [r12]                  ; Get address to read from / write to (r12)

        CMP     r0, #LOAD_WORD
        LDMEQIA r12, {r1-r8}
        CMP     r0, #STORE_WORD
        STMEQIA r12, {r1-r8}
        CMP     r0, #LOAD_HALF
        LDREQH  r1, [r12], #2
        LDREQH  r1, [r12], #2
        LDREQH  r1, [r12], #2
        LDREQH  r1, [r12], #2
        LDREQH  r1, [r12], #2
        LDREQH  r1, [r12], #2
        LDREQH  r1, [r12], #2
        LDREQH  r1, [r12], #2
        CMP     r0, #STORE_HALF
        STREQH  r1, [r12], #2
        STREQH  r1, [r12], #2
        STREQH  r1, [r12], #2
        STREQH  r1, [r12], #2
        STREQH  r1, [r12], #2
        STREQH  r1, [r12], #2
        STREQH  r1, [r12], #2
        STREQH  r1, [r12], #2
        CMP     r0, #LOAD_BYTE
        LDREQB  r1, [r12], #1
        LDREQB  r1, [r12], #1
        LDREQB  r1, [r12], #1
        LDREQB  r1, [r12], #1
        LDREQB  r1, [r12], #1
        LDREQB  r1, [r12], #1
        LDREQB  r1, [r12], #1
        LDREQB  r1, [r12], #1
        CMP     r0, #STORE_BYTE
        STREQB  r1, [r12], #1
        STREQB  r1, [r12], #1
        STREQB  r1, [r12], #1
        STREQB  r1, [r12], #1
        STREQB  r1, [r12], #1
        STREQB  r1, [r12], #1
        STREQB  r1, [r12], #1
        STREQB  r1, [r12], #1

stop    B       stop

        END


