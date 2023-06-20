
;CodeVisionAVR C Compiler V3.50 Advanced
;(C) Copyright 1998-2023 Pavel Haiduc, HP InfoTech S.R.L.
;http://www.hpinfotech.ro

;Build configuration    : Release
;Chip type              : AVR64DB64
;Program type           : Application
;Clock frequency        : 4,000960 MHz
;Memory model           : Small
;Optimize for           : Speed
;(s)printf features     : float, width, precision
;(s)scanf features      : No
;External RAM size      : 0
;Data Stack size        : 2048 byte(s)
;Heap size              : 0 byte(s)
;Promote 'char' to 'int': Yes
;'char' is unsigned     : Yes
;8 bit enums            : Yes
;Global 'const' stored in FLASH: Yes
;Enhanced function parameter passing: Mode 2
;Enhanced core instructions: On
;Automatic register allocation for global variables: On
;Smart register allocation: On

	#define _MODEL_SMALL_

	#pragma AVRPART ADMIN PART_NAME AVR64DB64
	#pragma AVRPART MEMORY PROG_FLASH 65536
	#pragma AVRPART MEMORY EEPROM 512
	#pragma AVRPART MEMORY INT_SRAM SIZE 8192
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x6000

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU CCP=0x34
	.EQU RAMPZ=0x3B
	.EQU WDT_CTRLA=0x100
	.EQU WDT_STATUS=0x101
	.EQU CPUINT_CTRLA=0x110
	.EQU NVMCTRL_CTRLA=0x1000
	.EQU NVMCTRL_CTRLB=0x1001
	.EQU NVMCTRL_STATUS=0x1002
	.EQU NVMCTRL_INTCTRL=0x1003
	.EQU NVMCTRL_INTFLAGS=0x1004
	.EQU NVMCTRL_DATAL=0x1006
	.EQU NVMCTRL_DATAH=0x1007
	.EQU NVMCTRL_ADDRL=0x1008
	.EQU NVMCTRL_ADDRH=0x1009
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F
	.EQU GPR_GPR0=0x1C
	.EQU GPR_GPR1=0x1D
	.EQU GPR_GPR2=0x1E
	.EQU GPR_GPR3=0x1F

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __SRAM_START=0x6000
	.EQU __SRAM_END=0x7FFF
	.EQU __DSTACK_SIZE=0x0800
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.EQU __FLASH_PAGE_SIZE=0x100

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETW1P
	LD   R30,X+
	LD   R31,X
	SBIW R26,1
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __GETD1P_INC
	LD   R30,X+
	LD   R31,X+
	LD   R22,X+
	LD   R23,X+
	.ENDM

	.MACRO __GETD1P_DEC
	LD   R23,-X
	LD   R22,-X
	LD   R31,-X
	LD   R30,-X
	.ENDM

	.MACRO __PUTDP1
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __PUTDP1_DEC
	ST   -X,R23
	ST   -X,R22
	ST   -X,R31
	ST   -X,R30
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __CPD10
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	.ENDM

	.MACRO __CPD20
	SBIW R26,0
	SBCI R24,0
	SBCI R25,0
	.ENDM

	.MACRO __ADDD12
	ADD  R30,R26
	ADC  R31,R27
	ADC  R22,R24
	ADC  R23,R25
	.ENDM

	.MACRO __ADDD21
	ADD  R26,R30
	ADC  R27,R31
	ADC  R24,R22
	ADC  R25,R23
	.ENDM

	.MACRO __SUBD12
	SUB  R30,R26
	SBC  R31,R27
	SBC  R22,R24
	SBC  R23,R25
	.ENDM

	.MACRO __SUBD21
	SUB  R26,R30
	SBC  R27,R31
	SBC  R24,R22
	SBC  R25,R23
	.ENDM

	.MACRO __ANDD12
	AND  R30,R26
	AND  R31,R27
	AND  R22,R24
	AND  R23,R25
	.ENDM

	.MACRO __ORD12
	OR   R30,R26
	OR   R31,R27
	OR   R22,R24
	OR   R23,R25
	.ENDM

	.MACRO __XORD12
	EOR  R30,R26
	EOR  R31,R27
	EOR  R22,R24
	EOR  R23,R25
	.ENDM

	.MACRO __XORD21
	EOR  R26,R30
	EOR  R27,R31
	EOR  R24,R22
	EOR  R25,R23
	.ENDM

	.MACRO __COMD1
	COM  R30
	COM  R31
	COM  R22
	COM  R23
	.ENDM

	.MACRO __MULD2_2
	LSL  R26
	ROL  R27
	ROL  R24
	ROL  R25
	.ENDM

	.MACRO __LSRD1
	LSR  R23
	ROR  R22
	ROR  R31
	ROR  R30
	.ENDM

	.MACRO __LSLD1
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R23
	.ENDM

	.MACRO __ASRB4
	ASR  R30
	ASR  R30
	ASR  R30
	ASR  R30
	.ENDM

	.MACRO __ASRW8
	MOV  R30,R31
	CLR  R31
	SBRC R30,7
	SER  R31
	.ENDM

	.MACRO __LSRD16
	MOV  R30,R22
	MOV  R31,R23
	LDI  R22,0
	LDI  R23,0
	.ENDM

	.MACRO __LSLD16
	MOV  R22,R30
	MOV  R23,R31
	LDI  R30,0
	LDI  R31,0
	.ENDM

	.MACRO __CWD1
	MOV  R22,R31
	ADD  R22,R22
	SBC  R22,R22
	MOV  R23,R22
	.ENDM

	.MACRO __CWD2
	MOV  R24,R27
	ADD  R24,R24
	SBC  R24,R24
	MOV  R25,R24
	.ENDM

	.MACRO __SETMSD1
	SER  R31
	SER  R22
	SER  R23
	.ENDM

	.MACRO __ADDW1R15
	CLR  R0
	ADD  R30,R15
	ADC  R31,R0
	.ENDM

	.MACRO __ADDW2R15
	CLR  R0
	ADD  R26,R15
	ADC  R27,R0
	.ENDM

	.MACRO __EQB12
	CP   R30,R26
	LDI  R30,1
	BREQ PC+2
	CLR  R30
	.ENDM

	.MACRO __NEB12
	CP   R30,R26
	LDI  R30,1
	BRNE PC+2
	CLR  R30
	.ENDM

	.MACRO __LEB12
	CP   R30,R26
	LDI  R30,1
	BRGE PC+2
	CLR  R30
	.ENDM

	.MACRO __GEB12
	CP   R26,R30
	LDI  R30,1
	BRGE PC+2
	CLR  R30
	.ENDM

	.MACRO __LTB12
	CP   R26,R30
	LDI  R30,1
	BRLT PC+2
	CLR  R30
	.ENDM

	.MACRO __GTB12
	CP   R30,R26
	LDI  R30,1
	BRLT PC+2
	CLR  R30
	.ENDM

	.MACRO __LEB12U
	CP   R30,R26
	LDI  R30,1
	BRSH PC+2
	CLR  R30
	.ENDM

	.MACRO __GEB12U
	CP   R26,R30
	LDI  R30,1
	BRSH PC+2
	CLR  R30
	.ENDM

	.MACRO __LTB12U
	CP   R26,R30
	LDI  R30,1
	BRLO PC+2
	CLR  R30
	.ENDM

	.MACRO __GTB12U
	CP   R30,R26
	LDI  R30,1
	BRLO PC+2
	CLR  R30
	.ENDM

	.MACRO __CPW01
	CLR  R0
	CP   R0,R30
	CPC  R0,R31
	.ENDM

	.MACRO __CPW02
	CLR  R0
	CP   R0,R26
	CPC  R0,R27
	.ENDM

	.MACRO __CPD12
	CP   R30,R26
	CPC  R31,R27
	CPC  R22,R24
	CPC  R23,R25
	.ENDM

	.MACRO __CPD21
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	CPC  R25,R23
	.ENDM

	.MACRO __BSTB1
	CLT
	TST  R30
	BREQ PC+2
	SET
	.ENDM

	.MACRO __LNEGB1
	TST  R30
	LDI  R30,1
	BREQ PC+2
	CLR  R30
	.ENDM

	.MACRO __LNEGW1
	OR   R30,R31
	LDI  R30,1
	BREQ PC+2
	LDI  R30,0
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD2M
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __POINTW2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	LDI  R24,BYTE3(2*@0+(@1))
	LDI  R25,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	PUSH R26
	PUSH R27
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	POP  R27
	POP  R26
	ICALL
	.ENDM

	.MACRO __CALL2EX
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	CALL __EEPROMRDD
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R30,SPL
	IN   R31,SPH
	ADIW R30,@0+1
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1STACK
	IN   R30,SPL
	IN   R31,SPH
	ADIW R30,@0+1
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z
	MOVW R30,R0
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	CALL __GETW1Z
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	CALL __GETD1Z
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	CALL __GETW2X
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	CALL __GETD2X
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

;GPR_GPR0-GPR_GPR3 INITIALIZATION VALUES
	.EQU __GPR_GPR0_INIT=0x00
	.EQU __GPR_GPR1_INIT=0x00
	.EQU __GPR_GPR2_INIT=0x00
	.EQU __GPR_GPR3_INIT=0x00

;GLOBAL REGISTER VARIABLES INITIALIZATION VALUES
	.EQU __R2_INIT=0x00
	.EQU __R3_INIT=0x00
	.EQU __R4_INIT=0x00
	.EQU __R5_INIT=0x00
	.EQU __R6_INIT=0x00
	.EQU __R7_INIT=0x00
	.EQU __R8_INIT=0x00
	.EQU __R9_INIT=0x00
	.EQU __R10_INIT=0x00
	.EQU __R11_INIT=0x00
	.EQU __R12_INIT=0x00
	.EQU __R13_INIT=0x00
	.EQU __R14_INIT=0x00

	.CSEG
	.ORG 0x00

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  _usart0_rx_isr
	JMP  _usart0_tx_isr
	JMP  0x00
	JMP  _portd_int_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  _portc_int_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  _porte_int_isr
	JMP  _tca1_ovf_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_crc:
	.DB  0x0,0x5E,0xBC,0xE2,0x61,0x3F,0xDD,0x83
	.DB  0xC2,0x9C,0x7E,0x20,0xA3,0xFD,0x1F,0x41
	.DB  0x9D,0xC3,0x21,0x7F,0xFC,0xA2,0x40,0x1E
	.DB  0x5F,0x1,0xE3,0xBD,0x3E,0x60,0x82,0xDC
	.DB  0x23,0x7D,0x9F,0xC1,0x42,0x1C,0xFE,0xA0
	.DB  0xE1,0xBF,0x5D,0x3,0x80,0xDE,0x3C,0x62
	.DB  0xBE,0xE0,0x2,0x5C,0xDF,0x81,0x63,0x3D
	.DB  0x7C,0x22,0xC0,0x9E,0x1D,0x43,0xA1,0xFF
	.DB  0x46,0x18,0xFA,0xA4,0x27,0x79,0x9B,0xC5
	.DB  0x84,0xDA,0x38,0x66,0xE5,0xBB,0x59,0x7
	.DB  0xDB,0x85,0x67,0x39,0xBA,0xE4,0x6,0x58
	.DB  0x19,0x47,0xA5,0xFB,0x78,0x26,0xC4,0x9A
	.DB  0x65,0x3B,0xD9,0x87,0x4,0x5A,0xB8,0xE6
	.DB  0xA7,0xF9,0x1B,0x45,0xC6,0x98,0x7A,0x24
	.DB  0xF8,0xA6,0x44,0x1A,0x99,0xC7,0x25,0x7B
	.DB  0x3A,0x64,0x86,0xD8,0x5B,0x5,0xE7,0xB9
	.DB  0x8C,0xD2,0x30,0x6E,0xED,0xB3,0x51,0xF
	.DB  0x4E,0x10,0xF2,0xAC,0x2F,0x71,0x93,0xCD
	.DB  0x11,0x4F,0xAD,0xF3,0x70,0x2E,0xCC,0x92
	.DB  0xD3,0x8D,0x6F,0x31,0xB2,0xEC,0xE,0x50
	.DB  0xAF,0xF1,0x13,0x4D,0xCE,0x90,0x72,0x2C
	.DB  0x6D,0x33,0xD1,0x8F,0xC,0x52,0xB0,0xEE
	.DB  0x32,0x6C,0x8E,0xD0,0x53,0xD,0xEF,0xB1
	.DB  0xF0,0xAE,0x4C,0x12,0x91,0xCF,0x2D,0x73
	.DB  0xCA,0x94,0x76,0x28,0xAB,0xF5,0x17,0x49
	.DB  0x8,0x56,0xB4,0xEA,0x69,0x37,0xD5,0x8B
	.DB  0x57,0x9,0xEB,0xB5,0x36,0x68,0x8A,0xD4
	.DB  0x95,0xCB,0x29,0x77,0xF4,0xAA,0x48,0x16
	.DB  0xE9,0xB7,0x55,0xB,0x88,0xD6,0x34,0x6A
	.DB  0x2B,0x75,0x97,0xC9,0x4A,0x14,0xF6,0xA8
	.DB  0x74,0x2A,0xC8,0x96,0x15,0x4B,0xA9,0xF7
	.DB  0xB6,0xE8,0xA,0x54,0xD7,0x89,0x6B,0x35

_0xC00F6:
	.DB  0xAE,0x8C,0xB6,0xB5,0xF3,0x49,0xDD,0x3A
	.DB  0xCC,0x41,0xD0,0xBC,0x2D,0xE5,0xA,0xB6
	.DB  0x6E,0x74,0x84,0x3B,0x20,0x43,0x87,0xBD
	.DB  0xD,0xE0,0x21,0x40,0xA4,0x30,0x75,0xC3
_0x2000000:
	.DB  0x2D,0x4E,0x41,0x4E,0x0
_0x2080060:
	.DB  0x1
_0x2080000:
	.DB  0x2D,0x4E,0x41,0x4E,0x0,0x49,0x4E,0x46
	.DB  0x0

__GLOBAL_INI_TBL:
	.DW  0x01
	.DW  __seed_G104
	.DW  _0x2080060*2

_0xFFFFFFFF:
	.DW  0

#define __GLOBAL_INI_TBL_PRESENT 1

__RESET:
	CLI
	CLR  R30

;INTERRUPT VECTORS ARE PLACED AT THE START
;OF THE BOOT SECTION OF THE FLASH
	LDI  R31,0xD8
	LDI  R26,0x40
	OUT  CCP,R31
	STS  CPUINT_CTRLA,R26

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,LOW(__SRAM_START)
	LDI  R27,HIGH(__SRAM_START)
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;GPR_GPR0-GPR_GPR3 INITIALIZATION
	LDI  R30,__GPR_GPR0_INIT
	OUT  GPR_GPR0,R30
	;__GPR_GPR1_INIT = __GPR_GPR0_INIT
	OUT  GPR_GPR1,R30
	;__GPR_GPR2_INIT = __GPR_GPR0_INIT
	OUT  GPR_GPR2,R30
	;__GPR_GPR3_INIT = __GPR_GPR0_INIT
	OUT  GPR_GPR3,R30

;HARDWARE STACK POINTER INITIALIZATION
	LDI  R30,LOW(__SRAM_END-__HEAP_SIZE)
	OUT  SPL,R30
	LDI  R30,HIGH(__SRAM_END-__HEAP_SIZE)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(__SRAM_START+__DSTACK_SIZE)
	LDI  R29,HIGH(__SRAM_START+__DSTACK_SIZE)

	JMP  _main

	.ESEG
	.ORG 0x00

	.DSEG
	.ORG 0x6800

	.CSEG
;void main(void)
; 0000 004F {

	.CSEG
_main:
; .FSTART _main
; 0000 0050 // Declare your local variables here
; 0000 0051 unsigned char n;
; 0000 0052 
; 0000 0053 //unsigned char  Buf[] = { 0x02,0x02 ,0xFE ,0x0A ,0x00 ,0x14 ,0x2F ,0x0A ,0x0D ,0x0A ,0x68 ,0x76 ,0x00 ,0x00 ,0xBF ,0x0E ,0x80 ,0x3F ,0x05 ,0x00 };
; 0000 0054 
; 0000 0055 //int Size = sizeof(Buf);
; 0000 0056 //
; 0000 0057 //unsigned char CheckSum = 0;
; 0000 0058 //unsigned char Cnt;
; 0000 0059 //unsigned char tmpBuf;
; 0000 005A //unsigned char Index;
; 0000 005B //unsigned char TmPIndex;
; 0000 005C //unsigned char CRC_or;
; 0000 005D //
; 0000 005E //unsigned char CRCTest;
; 0000 005F //unsigned char RunSYS=0;
; 0000 0060 // Interrupt system initialization
; 0000 0061 // Optimize for speed
; 0000 0062 #pragma optsize-
; 0000 0063 // Make sure the interrupts are disabled
; 0000 0064 #asm("cli")
;	n -> R17
	CLI
; 0000 0065 // Round-robin scheduling for level 0 interrupt: Off
; 0000 0066 // The interrupt vectors will be placed at the start of the Application FLASH section
; 0000 0067 n=0;
	LDI  R17,LOW(0)
; 0000 0068 CPU_CCP=CCP_IOREG_gc;
	LDI  R30,LOW(216)
	OUT  0x34,R30
; 0000 0069 CPUINT.CTRLA=n;
	STS  272,R17
; 0000 006A // Restore optimization for size if needed
; 0000 006B #pragma optsize_default
; 0000 006C 
; 0000 006D // The vectors with lower addresses will have
; 0000 006E // higher interrupt level 0 priority (default)
; 0000 006F CPUINT.LVL0PRI=0;
	LDI  R30,LOW(0)
	STS  274,R30
; 0000 0070 
; 0000 0071 // The higher interrupt priority level 1 is not used
; 0000 0072 CPUINT.LVL1VEC=0;
	STS  275,R30
; 0000 0073 
; 0000 0074 // System clocks initialization
; 0000 0075 system_clocks_init();
	CALL _system_clocks_init
; 0000 0076 
; 0000 0077 // Brown-Out Detector and Voltage Level Monitor initialization
; 0000 0078 // The settings below are applied to the BODCFG fuse
; 0000 0079 // that will be programmed if the
; 0000 007A // Project|Configure|After Build|Action: Program the Chip|Program Fuses
; 0000 007B // menu option is enabled in the IDE
; 0000 007C // BOD operation in Active or Idle modes: Enabled
; 0000 007D // BOD operation in Standby or Power-Down sleep modes: Disabled
; 0000 007E // BOD level: 1,90V
; 0000 007F // BODCFG=0x04
; 0000 0080 
; 0000 0081 // The Multi-Voltage I/O is disabled by programming the
; 0000 0082 // MVSYSCFG bits of the SYSCFG1 fuse to Single-Supply configuration
; 0000 0083 // SYSCFG1=0x10
; 0000 0084 // This setting will be applied if the
; 0000 0085 // Project|Configure|After Build|Action: Program the Chip|Program Fuses
; 0000 0086 // menu option is enabled in the IDE
; 0000 0087 
; 0000 0088 // I/O Ports initialization
; 0000 0089 ports_init();
	CALL _ports_init
; 0000 008A 
; 0000 008B // Timer/Counter TCA0 initialization
; 0000 008C tca0_init();
	CALL _tca0_init
; 0000 008D 
; 0000 008E // Timer/Counter TCA1 initialization
; 0000 008F tca1_init();
	CALL _tca1_init
; 0000 0090 
; 0000 0091 // USART0 initialization
; 0000 0092 usart0_init();
	CALL _usart0_init
; 0000 0093 
; 0000 0094 // SPI1 initialization
; 0000 0095 spi1_init();
	CALL _spi1_init
; 0000 0096 
; 0000 0097 
; 0000 0098 /*
; 0000 0099 InitRegs();  done with Codevision Wizard
; 0000 009A */
; 0000 009B // see Routine.c
; 0000 009C InitVar();
	CALL _InitVar
; 0000 009D InitStartup();
	CALL _InitStartup
; 0000 009E InitEEprom();   // init EEprom clear if first time
	CALL _InitEEprom
; 0000 009F Led (4,ON);
	LDI  R30,LOW(4)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _Led
; 0000 00A0 ResetADCBySW();
	CALL _ResetADCBySW
; 0000 00A1 ADC_CS_LOW;
	LDI  R30,LOW(8)
	STS  1094,R30
; 0000 00A2 //#asm("sei")
; 0000 00A3 set_interrupt_mask(0);	/* Enable interrupt */
	LDI  R26,LOW(0)
	CALL _set_interrupt_mask
; 0000 00A4 //    SCI0_SCR = 0x7c;            /* enable rx0/tx0 + rx0 interrupt */
; 0000 00A5 
; 0000 00A6 Led (4,OFF);
	LDI  R30,LOW(4)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _Led
; 0000 00A7 CheckEepChannel()   ;
	CALL _CheckEepChannel
; 0000 00A8 
; 0000 00A9 while ( TRUE )
_0x3:
; 0000 00AA {
; 0000 00AB #asm("wdr"); //KickDog();
	WDR
; 0000 00AC /* communication starts here */
; 0000 00AD if ( rx_indx > rx_hndx )
	LDS  R30,_rx_hndx
	LDS  R26,_rx_indx
	CP   R30,R26
	BRLO PC+3
	JMP _0x6
; 0000 00AE {   /* new char in buffer ? */
; 0000 00AF if ( ReceiveRxPacket() )
	CALL _ReceiveRxPacket
	SBIW R30,0
	BRNE PC+3
	JMP _0x7
; 0000 00B0 {
; 0000 00B1 HandleRxPacket() ;          /* Handle here */
	CALL _HandleRxPacket
; 0000 00B2 ResetRxPointer() ;          /* reset pointer */
	CALL _ResetRxPointer
; 0000 00B3 }
; 0000 00B4 }
_0x7:
; 0000 00B5 /* AD convert starts here */
; 0000 00B6 CheckConvert();
_0x6:
	CALL _CheckConvert
; 0000 00B7 }
	RJMP _0x3
_0x5:
; 0000 00B8 }
_0x8:
	RJMP _0x8
; .FEND
;void system_clocks_init(void)
; 0001 0011 {

	.CSEG
_system_clocks_init:
; .FSTART _system_clocks_init
; 0001 0012 unsigned char n,s;
; 0001 0013 
; 0001 0014 // Optimize for speed
; 0001 0015 #pragma optsize-
; 0001 0016 // Save interrupts enabled/disabled state
; 0001 0017 s=CPU_SREG;
	ST   -Y,R17
	ST   -Y,R16
;	n -> R17
;	s -> R16
	IN   R16,63
; 0001 0018 // Disable interrupts
; 0001 0019 #asm("cli")
	CLI
; 0001 001A 
; 0001 001B // Ensure that the external high-frequency clock source
; 0001 001C // is first disabled before modifying its settings
; 0001 001D n=0<<CLKCTRL_ENABLE_bp;
	LDI  R17,LOW(0)
; 0001 001E CPU_CCP=CCP_IOREG_gc;
	LDI  R30,LOW(216)
	OUT  0x34,R30
; 0001 001F CLKCTRL.XOSCHFCTRLA=n;
	STS  128,R17
; 0001 0020 
; 0001 0021 // Configure the external high-frequency clock source
; 0001 0022 // External source type: External Clock on XTALHF1 Pin
; 0001 0023 n=CLKCTRL_SELHF_EXTCLOCK_gc;
	LDI  R17,LOW(2)
; 0001 0024 CPU_CCP=CCP_IOREG_gc;
	OUT  0x34,R30
; 0001 0025 CLKCTRL.XOSCHFCTRLA=n;
	STS  128,R17
; 0001 0026 
; 0001 0027 // Enable the external high-frequency clock source
; 0001 0028 n|=1<<CLKCTRL_ENABLE_bp;
	ORI  R17,LOW(1)
; 0001 0029 CPU_CCP=CCP_IOREG_gc;
	OUT  0x34,R30
; 0001 002A CLKCTRL.XOSCHFCTRLA=n;
	STS  128,R17
; 0001 002B 
; 0001 002C // Main clock source: External Clock
; 0001 002D // Peripheral clock output on CLKOUT (PORTA, Pin 7): Off
; 0001 002E n=CLKCTRL_CLKSEL_EXTCLK_gc | (0<<CLKCTRL_CLKOUT_bp);
	LDI  R17,LOW(3)
; 0001 002F CPU_CCP=CCP_IOREG_gc;
	OUT  0x34,R30
; 0001 0030 CLKCTRL.MCLKCTRLA=n;
	STS  96,R17
; 0001 0031 
; 0001 0032 // Main clock prescaler division ratio: 1
; 0001 0033 // CPU and Peripheral clock: 4000,960 kHz
; 0001 0034 n=0;
	LDI  R17,LOW(0)
; 0001 0035 CPU_CCP=CCP_IOREG_gc;
	OUT  0x34,R30
; 0001 0036 CLKCTRL.MCLKCTRLB=n;
	STS  97,R17
; 0001 0037 
; 0001 0038 // Configure the Clock Failure Detection
; 0001 0039 // CFD interrupt: Disabled
; 0001 003A n=0<<CLKCTRL_CFD_bp;
	LDI  R17,LOW(0)
; 0001 003B CPU_CCP=CCP_IOREG_gc;
	OUT  0x34,R30
; 0001 003C CLKCTRL.MCLKINTCTRL=n;
	STS  99,R17
; 0001 003D 
; 0001 003E // Clock source to be monitored for a failure condition: Main Clock
; 0001 003F // CFD enabled
; 0001 0040 n=CLKCTRL_CFDSRC_CLKMAIN_gc | (1<<CLKCTRL_CFDEN_bp);
	LDI  R17,LOW(1)
; 0001 0041 CPU_CCP=CCP_IOREG_gc;
	OUT  0x34,R30
; 0001 0042 CLKCTRL.MCLKCTRLC=n;
	STS  98,R17
; 0001 0043 
; 0001 0044 // Restore interrupts enabled/disabled state
; 0001 0045 CPU_SREG=s;
	OUT  0x3F,R16
; 0001 0046 // Restore optimization for size if needed
; 0001 0047 #pragma optsize_default
; 0001 0048 }
	LD   R16,Y+
	LD   R17,Y+
	RET
; .FEND
;void ports_init(void)
; 0002 0013 {

	.CSEG
_ports_init:
; .FSTART _ports_init
; 0002 0014 // PORTA initialization
; 0002 0015 // OUT register
; 0002 0016 PORTA.OUT=0x10;
	LDI  R30,LOW(16)
	STS  1028,R30
; 0002 0017 // Pin0: Input
; 0002 0018 // Pin1: Input
; 0002 0019 // Pin2: Output
; 0002 001A // Pin3: Input
; 0002 001B // Pin4: Output
; 0002 001C // Pin5: Input
; 0002 001D // Pin6: Input
; 0002 001E // Pin7: Output
; 0002 001F PORTA.DIR=0x94;
	LDI  R30,LOW(148)
	STS  1024,R30
; 0002 0020 // Pin0 Inverted: Off
; 0002 0021 // Pin0 Pullup on input: Off
; 0002 0022 // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0023 // Pin0 Input level: Schmitt Tg.
; 0002 0024 PORTA.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1040,R30
; 0002 0025 // Pin1 Inverted: Off
; 0002 0026 // Pin1 Pullup on input: Off
; 0002 0027 // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0028 // Pin1 Input level: Schmitt Tg.
; 0002 0029 PORTA.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1041,R30
; 0002 002A // Pin2 Inverted: Off
; 0002 002B // Pin2 Pullup on input: Off
; 0002 002C // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 002D // Pin2 Input level: Schmitt Tg.
; 0002 002E PORTA.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1042,R30
; 0002 002F // Pin3 Inverted: Off
; 0002 0030 // Pin3 Pullup on input: On
; 0002 0031 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0032 // Pin3 Input level: Schmitt Tg.
; 0002 0033 PORTA.PIN3CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1043,R30
; 0002 0034 // Pin4 Inverted: Off
; 0002 0035 // Pin4 Pullup on input: Off
; 0002 0036 // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0037 // Pin4 Input level: Schmitt Tg.
; 0002 0038 PORTA.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1044,R30
; 0002 0039 // Pin5 Inverted: Off
; 0002 003A // Pin5 Pullup on input: On
; 0002 003B // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 003C // Pin5 Input level: Schmitt Tg.
; 0002 003D PORTA.PIN5CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1045,R30
; 0002 003E // Pin6 Inverted: Off
; 0002 003F // Pin6 Pullup on input: On
; 0002 0040 // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0041 // Pin6 Input level: Schmitt Tg.
; 0002 0042 PORTA.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1046,R30
; 0002 0043 // Pin7 Inverted: Off
; 0002 0044 // Pin7 Pullup on input: Off
; 0002 0045 // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0046 // Pin7 Input level: Schmitt Tg.
; 0002 0047 PORTA.PIN7CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1047,R30
; 0002 0048 
; 0002 0049 // PORTB initialization
; 0002 004A // OUT register
; 0002 004B PORTB.OUT=0x00;
	STS  1060,R30
; 0002 004C // Pin0: Output
; 0002 004D // Pin1: Output
; 0002 004E // Pin2: Output
; 0002 004F // Pin3: Output
; 0002 0050 // Pin4: Output
; 0002 0051 // Pin5: Output
; 0002 0052 // Pin6: Output
; 0002 0053 // Pin7: Output
; 0002 0054 PORTB.DIR=0xFF;
	LDI  R30,LOW(255)
	STS  1056,R30
; 0002 0055 // Pin0 Inverted: Off
; 0002 0056 // Pin0 Pullup on input: Off
; 0002 0057 // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0058 // Pin0 Input level: Schmitt Tg.
; 0002 0059 PORTB.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1072,R30
; 0002 005A // Pin1 Inverted: Off
; 0002 005B // Pin1 Pullup on input: Off
; 0002 005C // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 005D // Pin1 Input level: Schmitt Tg.
; 0002 005E PORTB.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1073,R30
; 0002 005F // Pin2 Inverted: Off
; 0002 0060 // Pin2 Pullup on input: Off
; 0002 0061 // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0062 // Pin2 Input level: Schmitt Tg.
; 0002 0063 PORTB.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1074,R30
; 0002 0064 // Pin3 Inverted: Off
; 0002 0065 // Pin3 Pullup on input: Off
; 0002 0066 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0067 // Pin3 Input level: Schmitt Tg.
; 0002 0068 PORTB.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1075,R30
; 0002 0069 // Pin4 Inverted: Off
; 0002 006A // Pin4 Pullup on input: Off
; 0002 006B // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 006C // Pin4 Input level: Schmitt Tg.
; 0002 006D PORTB.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1076,R30
; 0002 006E // Pin5 Inverted: Off
; 0002 006F // Pin5 Pullup on input: Off
; 0002 0070 // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0071 // Pin5 Input level: Schmitt Tg.
; 0002 0072 PORTB.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1077,R30
; 0002 0073 // Pin6 Inverted: Off
; 0002 0074 // Pin6 Pullup on input: On
; 0002 0075 // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0076 // Pin6 Input level: Schmitt Tg.
; 0002 0077 PORTB.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1078,R30
; 0002 0078 // Pin7 Inverted: Off
; 0002 0079 // Pin7 Pullup on input: On
; 0002 007A // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 007B // Pin7 Input level: Schmitt Tg.
; 0002 007C PORTB.PIN7CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1079,R30
; 0002 007D 
; 0002 007E // PORTC initialization
; 0002 007F // OUT register
; 0002 0080 PORTC.OUT=0x08;
	STS  1092,R30
; 0002 0081 // Pin0: Output
; 0002 0082 // Pin1: Input
; 0002 0083 // Pin2: Output
; 0002 0084 // Pin3: Output
; 0002 0085 // Pin4: Input
; 0002 0086 // Pin5: Output
; 0002 0087 // Pin6: Output
; 0002 0088 // Pin7: Output
; 0002 0089 PORTC.DIR=0xED;
	LDI  R30,LOW(237)
	STS  1088,R30
; 0002 008A // Pin0 Inverted: Off
; 0002 008B // Pin0 Pullup on input: Off
; 0002 008C // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 008D // Pin0 Input level: Schmitt Tg.
; 0002 008E PORTC.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1104,R30
; 0002 008F // Pin1 Inverted: Off
; 0002 0090 // Pin1 Pullup on input: On
; 0002 0091 // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0092 // Pin1 Input level: Schmitt Tg.
; 0002 0093 PORTC.PIN1CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1105,R30
; 0002 0094 // Pin2 Inverted: Off
; 0002 0095 // Pin2 Pullup on input: Off
; 0002 0096 // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0097 // Pin2 Input level: Schmitt Tg.
; 0002 0098 PORTC.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1106,R30
; 0002 0099 // Pin3 Inverted: Off
; 0002 009A // Pin3 Pullup on input: Off
; 0002 009B // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 009C // Pin3 Input level: Schmitt Tg.
; 0002 009D PORTC.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1107,R30
; 0002 009E // Pin4 Inverted: Off
; 0002 009F // Pin4 Pullup on input: On
; 0002 00A0 // Pin4 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 00A1 // Pin4 Input level: Schmitt Tg.
; 0002 00A2 PORTC.PIN4CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(11)
	STS  1108,R30
; 0002 00A3 // Pin5 Inverted: Off
; 0002 00A4 // Pin5 Pullup on input: Off
; 0002 00A5 // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00A6 // Pin5 Input level: Schmitt Tg.
; 0002 00A7 PORTC.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1109,R30
; 0002 00A8 // Pin6 Inverted: Off
; 0002 00A9 // Pin6 Pullup on input: Off
; 0002 00AA // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00AB // Pin6 Input level: Schmitt Tg.
; 0002 00AC PORTC.PIN6CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1110,R30
; 0002 00AD // Pin7 Inverted: Off
; 0002 00AE // Pin7 Pullup on input: Off
; 0002 00AF // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00B0 // Pin7 Input level: Schmitt Tg.
; 0002 00B1 PORTC.PIN7CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1111,R30
; 0002 00B2 
; 0002 00B3 // PORTD initialization
; 0002 00B4 // OUT register
; 0002 00B5 PORTD.OUT=0x00;
	STS  1124,R30
; 0002 00B6 // Pin0: Input
; 0002 00B7 // Pin1: Input
; 0002 00B8 // Pin2: Input
; 0002 00B9 // Pin3: Input
; 0002 00BA // Pin4: Input
; 0002 00BB // Pin5: Input
; 0002 00BC // Pin6: Input
; 0002 00BD // Pin7: Input
; 0002 00BE PORTD.DIR=0x00;
	STS  1120,R30
; 0002 00BF // Pin0 Inverted: Off
; 0002 00C0 // Pin0 Pullup on input: On
; 0002 00C1 // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00C2 // Pin0 Input level: Schmitt Tg.
; 0002 00C3 PORTD.PIN0CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1136,R30
; 0002 00C4 // Pin1 Inverted: Off
; 0002 00C5 // Pin1 Pullup on input: On
; 0002 00C6 // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00C7 // Pin1 Input level: Schmitt Tg.
; 0002 00C8 PORTD.PIN1CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1137,R30
; 0002 00C9 // Pin2 Inverted: Off
; 0002 00CA // Pin2 Pullup on input: On
; 0002 00CB // Pin2 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 00CC // Pin2 Input level: Schmitt Tg.
; 0002 00CD PORTD.PIN2CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(11)
	STS  1138,R30
; 0002 00CE // Pin3 Inverted: Off
; 0002 00CF // Pin3 Pullup on input: On
; 0002 00D0 // Pin3 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 00D1 // Pin3 Input level: Schmitt Tg.
; 0002 00D2 PORTD.PIN3CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1139,R30
; 0002 00D3 // Pin4 Inverted: Off
; 0002 00D4 // Pin4 Pullup on input: On
; 0002 00D5 // Pin4 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 00D6 // Pin4 Input level: Schmitt Tg.
; 0002 00D7 PORTD.PIN4CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1140,R30
; 0002 00D8 // Pin5 Inverted: Off
; 0002 00D9 // Pin5 Pullup on input: On
; 0002 00DA // Pin5 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 00DB // Pin5 Input level: Schmitt Tg.
; 0002 00DC PORTD.PIN5CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1141,R30
; 0002 00DD // Pin6 Inverted: Off
; 0002 00DE // Pin6 Pullup on input: On
; 0002 00DF // Pin6 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 00E0 // Pin6 Input level: Schmitt Tg.
; 0002 00E1 PORTD.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1142,R30
; 0002 00E2 // Pin7 Inverted: Off
; 0002 00E3 // Pin7 Pullup on input: On
; 0002 00E4 // Pin7 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 00E5 // Pin7 Input level: Schmitt Tg.
; 0002 00E6 PORTD.PIN7CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1143,R30
; 0002 00E7 
; 0002 00E8 // PORTE initialization
; 0002 00E9 // OUT register
; 0002 00EA PORTE.OUT=0x00;
	LDI  R30,LOW(0)
	STS  1156,R30
; 0002 00EB // Pin0: Input
; 0002 00EC // Pin1: Input
; 0002 00ED // Pin2: Input
; 0002 00EE // Pin3: Input
; 0002 00EF // Pin4: Input
; 0002 00F0 // Pin5: Input
; 0002 00F1 // Pin6: Input
; 0002 00F2 // Pin7: Input
; 0002 00F3 PORTE.DIR=0x00;
	STS  1152,R30
; 0002 00F4 // Pin0 Inverted: Off
; 0002 00F5 // Pin0 Pullup on input: On
; 0002 00F6 // Pin0 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 00F7 // Pin0 Input level: Schmitt Tg.
; 0002 00F8 PORTE.PIN0CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(11)
	STS  1168,R30
; 0002 00F9 // Pin1 Inverted: Off
; 0002 00FA // Pin1 Pullup on input: On
; 0002 00FB // Pin1 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 00FC // Pin1 Input level: Schmitt Tg.
; 0002 00FD PORTE.PIN1CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1169,R30
; 0002 00FE // Pin2 Inverted: Off
; 0002 00FF // Pin2 Pullup on input: On
; 0002 0100 // Pin2 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 0101 // Pin2 Input level: Schmitt Tg.
; 0002 0102 PORTE.PIN2CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1170,R30
; 0002 0103 // Pin3 Inverted: Off
; 0002 0104 // Pin3 Pullup on input: On
; 0002 0105 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0106 // Pin3 Input level: Schmitt Tg.
; 0002 0107 PORTE.PIN3CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1171,R30
; 0002 0108 // Pin4 Inverted: Off
; 0002 0109 // Pin4 Pullup on input: On
; 0002 010A // Pin4 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 010B // Pin4 Input level: Schmitt Tg.
; 0002 010C PORTE.PIN4CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(11)
	STS  1172,R30
; 0002 010D // Pin5 Inverted: Off
; 0002 010E // Pin5 Pullup on input: On
; 0002 010F // Pin5 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 0110 // Pin5 Input level: Schmitt Tg.
; 0002 0111 PORTE.PIN5CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1173,R30
; 0002 0112 // Pin6 Inverted: Off
; 0002 0113 // Pin6 Pullup on input: On
; 0002 0114 // Pin6 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 0115 // Pin6 Input level: Schmitt Tg.
; 0002 0116 PORTE.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1174,R30
; 0002 0117 // Pin7 Inverted: Off
; 0002 0118 // Pin7 Pullup on input: On
; 0002 0119 // Pin7 Input/Sense configuration: Int. enabled, Sense falling edge
; 0002 011A // Pin7 Input level: Schmitt Tg.
; 0002 011B PORTE.PIN7CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
	STS  1175,R30
; 0002 011C 
; 0002 011D // PORTF initialization
; 0002 011E // OUT register
; 0002 011F PORTF.OUT=0x00;
	LDI  R30,LOW(0)
	STS  1188,R30
; 0002 0120 // Pin0: Input
; 0002 0121 // Pin1: Output
; 0002 0122 // Pin2: Output
; 0002 0123 // Pin3: Output
; 0002 0124 // Pin4: Output
; 0002 0125 // Pin5: Output
; 0002 0126 // Pin6: Input
; 0002 0127 PORTF.DIR=0x3E;
	LDI  R30,LOW(62)
	STS  1184,R30
; 0002 0128 // Pin0 Inverted: Off
; 0002 0129 // Pin0 Pullup on input: On
; 0002 012A // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 012B // Pin0 Input level: Schmitt Tg.
; 0002 012C PORTF.PIN0CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1200,R30
; 0002 012D // Pin1 Inverted: Off
; 0002 012E // Pin1 Pullup on input: Off
; 0002 012F // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0130 // Pin1 Input level: Schmitt Tg.
; 0002 0131 PORTF.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1201,R30
; 0002 0132 // Pin2 Inverted: Off
; 0002 0133 // Pin2 Pullup on input: Off
; 0002 0134 // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0135 // Pin2 Input level: Schmitt Tg.
; 0002 0136 PORTF.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1202,R30
; 0002 0137 // Pin3 Inverted: Off
; 0002 0138 // Pin3 Pullup on input: Off
; 0002 0139 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 013A // Pin3 Input level: Schmitt Tg.
; 0002 013B PORTF.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1203,R30
; 0002 013C // Pin4 Inverted: Off
; 0002 013D // Pin4 Pullup on input: Off
; 0002 013E // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 013F // Pin4 Input level: Schmitt Tg.
; 0002 0140 PORTF.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1204,R30
; 0002 0141 // Pin5 Inverted: Off
; 0002 0142 // Pin5 Pullup on input: Off
; 0002 0143 // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0144 // Pin5 Input level: Schmitt Tg.
; 0002 0145 PORTF.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1205,R30
; 0002 0146 // Pin6 Inverted: Off
; 0002 0147 // Pin6 Pullup on input: Off
; 0002 0148 // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0149 // Pin6 Input level: Schmitt Tg.
; 0002 014A PORTF.PIN6CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1206,R30
; 0002 014B 
; 0002 014C // PORTG initialization
; 0002 014D // OUT register
; 0002 014E PORTG.OUT=0x00;
	STS  1220,R30
; 0002 014F // Pin0: Output
; 0002 0150 // Pin1: Output
; 0002 0151 // Pin2: Output
; 0002 0152 // Pin3: Output
; 0002 0153 // Pin4: Output
; 0002 0154 // Pin5: Output
; 0002 0155 // Pin6: Output
; 0002 0156 // Pin7: Output
; 0002 0157 PORTG.DIR=0xFF;
	LDI  R30,LOW(255)
	STS  1216,R30
; 0002 0158 // Pin0 Inverted: Off
; 0002 0159 // Pin0 Pullup on input: Off
; 0002 015A // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 015B // Pin0 Input level: Schmitt Tg.
; 0002 015C PORTG.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1232,R30
; 0002 015D // Pin1 Inverted: Off
; 0002 015E // Pin1 Pullup on input: Off
; 0002 015F // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0160 // Pin1 Input level: Schmitt Tg.
; 0002 0161 PORTG.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1233,R30
; 0002 0162 // Pin2 Inverted: Off
; 0002 0163 // Pin2 Pullup on input: Off
; 0002 0164 // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0165 // Pin2 Input level: Schmitt Tg.
; 0002 0166 PORTG.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1234,R30
; 0002 0167 // Pin3 Inverted: Off
; 0002 0168 // Pin3 Pullup on input: Off
; 0002 0169 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 016A // Pin3 Input level: Schmitt Tg.
; 0002 016B PORTG.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1235,R30
; 0002 016C // Pin4 Inverted: Off
; 0002 016D // Pin4 Pullup on input: Off
; 0002 016E // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 016F // Pin4 Input level: Schmitt Tg.
; 0002 0170 PORTG.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1236,R30
; 0002 0171 // Pin5 Inverted: Off
; 0002 0172 // Pin5 Pullup on input: Off
; 0002 0173 // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0174 // Pin5 Input level: Schmitt Tg.
; 0002 0175 PORTG.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1237,R30
; 0002 0176 // Pin6 Inverted: Off
; 0002 0177 // Pin6 Pullup on input: Off
; 0002 0178 // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0179 // Pin6 Input level: Schmitt Tg.
; 0002 017A PORTG.PIN6CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1238,R30
; 0002 017B // Pin7 Inverted: Off
; 0002 017C // Pin7 Pullup on input: Off
; 0002 017D // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 017E // Pin7 Input level: Schmitt Tg.
; 0002 017F PORTG.PIN7CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1239,R30
; 0002 0180 }
	RET
; .FEND
;interrupt [(31)  ] void portc_int_isr(void)
; 0002 0186 {
_portc_int_isr:
; .FSTART _portc_int_isr
	ST   -Y,R30
	IN   R30,SREG
	ST   -Y,R30
; 0002 0187 // Clear the PORTC interrupt flags
; 0002 0188 // test if Pin4 port C trigger interrupt
; 0002 0189 // DRDY_INTERRUPT_FLAG = 0b00010000 PINC.4
; 0002 018A unsigned char tmp;
; 0002 018B tmp=PORTC.INTFLAGS;
	ST   -Y,R17
;	tmp -> R17
	LDS  R17,1097
; 0002 018C PORTC.INTFLAGS=PORTC.INTFLAGS;
	LDS  R30,1097
	STS  1097,R30
; 0002 018D if ( (tmp&DRDY_INTERRUPT_FLAG)==DRDY_INTERRUPT_FLAG)    //
	MOV  R30,R17
	ANDI R30,LOW(0x10)
	CPI  R30,LOW(0x10)
	BREQ PC+3
	JMP _0x40003
; 0002 018E {
; 0002 018F // Write your code here
; 0002 0190 if ( ad_mode & 0x20 )
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x20)
	BRNE PC+3
	JMP _0x40004
; 0002 0191 {                                               /* ok for int */
; 0002 0192 ad_state++ ;                                /* Go to next state */
	LDS  R30,_ad_state
	SUBI R30,-LOW(1)
	STS  _ad_state,R30
; 0002 0193 ad_mode &= ~0x20;                           /* int ok, reset flag */
	LDS  R30,_ad_mode
	ANDI R30,0xDF
	STS  _ad_mode,R30
; 0002 0194 }
; 0002 0195 }
_0x40004:
; 0002 0196 }
_0x40003:
	LD   R17,Y+
	LD   R30,Y+
	OUT  SREG,R30
	LD   R30,Y+
	RETI
; .FEND
;interrupt [(25)  ] void portd_int_isr(void)
; 0002 019A {
_portd_int_isr:
; .FSTART _portd_int_isr
	ST   -Y,R24
	ST   -Y,R26
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0002 019B // Clear the PORTD interrupt flags
; 0002 019C PORTD.INTFLAGS=PORTD.INTFLAGS;
	LDS  R30,1129
	STS  1129,R30
; 0002 019D 
; 0002 019E // Write your code here
; 0002 019F if (WASHTRAC1 ==1 ^ (washtrac_prev & 0x01))
	LDS  R30,1128
	ANDI R30,LOW(0x80)
	LDI  R26,LOW(0)
	__NEB12
	LDI  R26,LOW(1)
	__EQB12
	MOV  R26,R30
	LDS  R30,_washtrac_prev
	ANDI R30,LOW(0x1)
	EOR  R30,R26
	BRNE PC+3
	JMP _0x40005
; 0002 01A0 {   delay_us (WASHTRAC_DELAY);
	__DELAY_USB 7
; 0002 01A1 if ( WASHTRAC1==1)
	LDS  R30,1128
	ANDI R30,LOW(0x80)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40006
; 0002 01A2 washtrac[0] ++;
	LDS  R30,_washtrac
	LDS  R31,_washtrac+1
	ADIW R30,1
	STS  _washtrac,R30
	STS  _washtrac+1,R31
; 0002 01A3 }
_0x40006:
; 0002 01A4 if (WASHTRAC2 ==1 ^ (washtrac_prev & 0x02))
_0x40005:
	LDS  R30,1128
	ANDI R30,LOW(0x40)
	LDI  R26,LOW(0)
	__NEB12
	LDI  R26,LOW(1)
	__EQB12
	MOV  R26,R30
	LDS  R30,_washtrac_prev
	ANDI R30,LOW(0x2)
	EOR  R30,R26
	BRNE PC+3
	JMP _0x40007
; 0002 01A5 {   delay_us (WASHTRAC_DELAY);
	__DELAY_USB 7
; 0002 01A6 if ( WASHTRAC2==1)
	LDS  R30,1128
	ANDI R30,LOW(0x40)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40008
; 0002 01A7 washtrac[1] ++;
	__GETW1MN _washtrac,2
	ADIW R30,1
	__PUTW1MN _washtrac,2
; 0002 01A8 }
_0x40008:
; 0002 01A9 if (WASHTRAC3 ==1 ^ (washtrac_prev & 0x04))
_0x40007:
	LDS  R30,1128
	ANDI R30,LOW(0x20)
	LDI  R26,LOW(0)
	__NEB12
	LDI  R26,LOW(1)
	__EQB12
	MOV  R26,R30
	LDS  R30,_washtrac_prev
	ANDI R30,LOW(0x4)
	EOR  R30,R26
	BRNE PC+3
	JMP _0x40009
; 0002 01AA {   delay_us (WASHTRAC_DELAY);
	__DELAY_USB 7
; 0002 01AB if ( WASHTRAC3==1)
	LDS  R30,1128
	ANDI R30,LOW(0x20)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x4000A
; 0002 01AC washtrac[2] ++;
	__GETW1MN _washtrac,4
	ADIW R30,1
	__PUTW1MN _washtrac,4
; 0002 01AD }
_0x4000A:
; 0002 01AE if (WASHTRAC4 ==1 ^ (washtrac_prev & 0x08))
_0x40009:
	LDS  R30,1128
	ANDI R30,LOW(0x10)
	LDI  R26,LOW(0)
	__NEB12
	LDI  R26,LOW(1)
	__EQB12
	MOV  R26,R30
	LDS  R30,_washtrac_prev
	ANDI R30,LOW(0x8)
	EOR  R30,R26
	BRNE PC+3
	JMP _0x4000B
; 0002 01AF {   delay_us (WASHTRAC_DELAY);
	__DELAY_USB 7
; 0002 01B0 if ( WASHTRAC4==1)
	LDS  R30,1128
	ANDI R30,LOW(0x10)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x4000C
; 0002 01B1 washtrac[3] ++;
	__GETW1MN _washtrac,6
	ADIW R30,1
	__PUTW1MN _washtrac,6
; 0002 01B2 }
_0x4000C:
; 0002 01B3 washtrac_prev=0;
_0x4000B:
	LDI  R30,LOW(0)
	STS  _washtrac_prev,R30
; 0002 01B4 if (WASHTRAC1 ==1)
	LDS  R30,1128
	ANDI R30,LOW(0x80)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x4000D
; 0002 01B5 washtrac_prev|=0x01;
	LDS  R30,_washtrac_prev
	ORI  R30,1
	STS  _washtrac_prev,R30
; 0002 01B6 if (WASHTRAC2 ==1)
_0x4000D:
	LDS  R30,1128
	ANDI R30,LOW(0x40)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x4000E
; 0002 01B7 washtrac_prev|=0x02;
	LDS  R30,_washtrac_prev
	ORI  R30,2
	STS  _washtrac_prev,R30
; 0002 01B8 if (WASHTRAC3 ==1)
_0x4000E:
	LDS  R30,1128
	ANDI R30,LOW(0x20)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x4000F
; 0002 01B9 washtrac_prev|=0x04;
	LDS  R30,_washtrac_prev
	ORI  R30,4
	STS  _washtrac_prev,R30
; 0002 01BA if (WASHTRAC4 ==1)
_0x4000F:
	LDS  R30,1128
	ANDI R30,LOW(0x10)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40010
; 0002 01BB washtrac_prev|=0x08;
	LDS  R30,_washtrac_prev
	ORI  R30,8
	STS  _washtrac_prev,R30
; 0002 01BC }
_0x40010:
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R26,Y+
	LD   R24,Y+
	RETI
; .FEND
;interrupt [(47)  ] void porte_int_isr(void)
; 0002 01C0 {
_porte_int_isr:
; .FSTART _porte_int_isr
	ST   -Y,R26
	ST   -Y,R30
	IN   R30,SREG
	ST   -Y,R30
; 0002 01C1 // Clear the PORTE interrupt flags
; 0002 01C2 PORTE.INTFLAGS=PORTE.INTFLAGS;
	LDS  R30,1161
	STS  1161,R30
; 0002 01C3 
; 0002 01C4 // Write your code here
; 0002 01C5 highlevel=0;
	LDI  R30,LOW(0)
	STS  _highlevel,R30
; 0002 01C6 if ( HIGHLEVEL1 == 1)
	LDS  R30,1160
	ANDI R30,LOW(0x80)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40011
; 0002 01C7 highlevel|=0x01;
	LDS  R30,_highlevel
	ORI  R30,1
	STS  _highlevel,R30
; 0002 01C8 if ( HIGHLEVEL2 == 1)
_0x40011:
	LDS  R30,1160
	ANDI R30,LOW(0x40)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40012
; 0002 01C9 highlevel|=0x02;
	LDS  R30,_highlevel
	ORI  R30,2
	STS  _highlevel,R30
; 0002 01CA if ( HIGHLEVEL3 == 1)
_0x40012:
	LDS  R30,1160
	ANDI R30,LOW(0x20)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40013
; 0002 01CB highlevel|=0x04;
	LDS  R30,_highlevel
	ORI  R30,4
	STS  _highlevel,R30
; 0002 01CC if ( HIGHLEVEL4 == 1)
_0x40013:
	LDS  R30,1160
	ANDI R30,LOW(0x10)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40014
; 0002 01CD highlevel|=0x08;
	LDS  R30,_highlevel
	ORI  R30,8
	STS  _highlevel,R30
; 0002 01CE if ( HIGHLEVEL5 == 1)
_0x40014:
	LDS  R30,1160
	ANDI R30,LOW(0x8)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40015
; 0002 01CF highlevel|=0x10;
	LDS  R30,_highlevel
	ORI  R30,0x10
	STS  _highlevel,R30
; 0002 01D0 if ( HIGHLEVEL6 == 1)
_0x40015:
	LDS  R30,1160
	ANDI R30,LOW(0x4)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40016
; 0002 01D1 highlevel|=0x20;
	LDS  R30,_highlevel
	ORI  R30,0x20
	STS  _highlevel,R30
; 0002 01D2 if ( HIGHLEVEL7 == 1)
_0x40016:
	LDS  R30,1160
	ANDI R30,LOW(0x2)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40017
; 0002 01D3 highlevel|=0x40;
	LDS  R30,_highlevel
	ORI  R30,0x40
	STS  _highlevel,R30
; 0002 01D4 if ( HIGHLEVEL8 == 1)
_0x40017:
	LDS  R30,1160
	ANDI R30,LOW(0x1)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x40018
; 0002 01D5 highlevel|=0x80;
	LDS  R30,_highlevel
	ORI  R30,0x80
	STS  _highlevel,R30
; 0002 01D6 
; 0002 01D7 }
_0x40018:
	LD   R30,Y+
	OUT  SREG,R30
	LD   R30,Y+
	LD   R26,Y+
	RETI
; .FEND
;void tca_disable(TCA_t *ptca)
; 0003 0010 {

	.CSEG
_tca_disable:
; .FSTART _tca_disable
; 0003 0011 // Timer/Counter TCA is disabled
; 0003 0012 ptca->SINGLE.CTRLA=0<<TCA_SINGLE_ENABLE_bp;
	ST   -Y,R17
	ST   -Y,R16
	MOVW R16,R26
;	*ptca -> R16,R17
	LDI  R30,LOW(0)
	ST   X,R30
; 0003 0013 // Operate in 16-bit mode
; 0003 0014 ptca->SINGLE.CTRLD=0<<TCA_SINGLE_SPLITM_bp;
	ADIW R26,3
	ST   X,R30
; 0003 0015 // Issue a reset command
; 0003 0016 ptca->SINGLE.CTRLECLR=TCA_SINGLE_CMD_RESET_gc;
	MOVW R26,R16
	ADIW R26,4
	LDI  R30,LOW(12)
	ST   X,R30
; 0003 0017 }
	LD   R16,Y+
	LD   R17,Y+
	RET
; .FEND
;void tca0_init(void)
; 0003 001B {
_tca0_init:
; .FSTART _tca0_init
; 0003 001C // First disable and reset the Timer/Counter TCA0
; 0003 001D // Use 16-bit mode
; 0003 001E tca_disable(&TCA0);
	LDI  R26,LOW(2560)
	LDI  R27,HIGH(2560)
	CALL _tca_disable
; 0003 001F 
; 0003 0020 // Clock divider: 1
; 0003 0021 // Clock frequency: 4000,960 kHz
; 0003 0022 // TCA0 runs in standby: Off
; 0003 0023 TCA0.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1_gc+(0<<TCA_SINGLE_RUNSTDBY_bp);
	LDI  R30,LOW(0)
	STS  2560,R30
; 0003 0024 
; 0003 0025 // Operating mode: Frequency Generation 16-bit OVF=TOP (CMP0)
; 0003 0026 // Set the waveform outputs configuration:
; 0003 0027 // WO0: Off
; 0003 0028 // WO1: Off
; 0003 0029 // WO2: PORTA, Pin 2
; 0003 002A TCA0.SINGLE.CTRLB=TCA_SINGLE_WGMODE_FRQ_gc+
; 0003 002B (0<<TCA_SINGLE_CMP0EN_bp)+
; 0003 002C (0<<TCA_SINGLE_CMP1EN_bp)+
; 0003 002D (1<<TCA_SINGLE_CMP2EN_bp);
	LDI  R30,LOW(65)
	STS  2561,R30
; 0003 002E 
; 0003 002F // Set the waveform outputs mapping
; 0003 0030 PORTMUX.TCAROUTEA=(PORTMUX.TCAROUTEA & (~PORTMUX_TCA0_gm)) | PORTMUX_TCA0_PORTA_gc;
	LDS  R30,1510
	ANDI R30,LOW(0xF8)
	STS  1510,R30
; 0003 0031 // Note: The configuration for the waveform output signals
; 0003 0032 // is set in the ports_init function from ports_init.c
; 0003 0033 
; 0003 0034 // Set the Timer Counter register
; 0003 0035 TCA0.SINGLE.CNT=0x00;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	STS  2592,R30
	STS  2592+1,R31
; 0003 0036 
; 0003 0037 // In Frequency Generation mode the Timer Compare 0 register sets the
; 0003 0038 // specified frequency for the WO0, WO1, WO2 outputs: 1000 kHz
; 0003 0039 // Obtained frequency: 1000,24 kHz, -0,02 % error
; 0003 003A TCA0.SINGLE.CMP0=0x01;
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	STS  2600,R30
	STS  2600+1,R31
; 0003 003B 
; 0003 003C // The Timer Compare 1 register sets the specified
; 0003 003D // phase for the WO1 output relative to WO0: 0,00�
; 0003 003E TCA0.SINGLE.CMP1=0x00;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	STS  2602,R30
	STS  2602+1,R31
; 0003 003F 
; 0003 0040 // The Timer Compare 2 register sets the specified
; 0003 0041 // phase for the WO2 output relative to WO0: 50,00�
; 0003 0042 TCA0.SINGLE.CMP2=0x00;
	STS  2604,R30
	STS  2604+1,R31
; 0003 0043 
; 0003 0044 // Set the Event Control register
; 0003 0045 // Event input A: No action
; 0003 0046 // Event input B: No action
; 0003 0047 TCA0.SINGLE.EVCTRL=(0<<TCA_SINGLE_CNTAEI_bp)+(0<<TCA_SINGLE_CNTBEI_bp);
	STS  2569,R30
; 0003 0048 
; 0003 0049 // Set TCA0 interrupts:
; 0003 004A // Overflow interrupt: Off
; 0003 004B // Compare Channel 0 interrupt: Off
; 0003 004C // Compare Channel 1 interrupt: Off
; 0003 004D // Compare Channel 2 interrupt: Off
; 0003 004E TCA0.SINGLE.INTCTRL=
; 0003 004F (0<<TCA_SINGLE_OVF_bp)+
; 0003 0050 (0<<TCA_SINGLE_CMP0_bp)+
; 0003 0051 (0<<TCA_SINGLE_CMP1_bp)+
; 0003 0052 (0<<TCA_SINGLE_CMP2_bp);
	STS  2570,R30
; 0003 0053 
; 0003 0054 // Initialization finished, enable TCA0
; 0003 0055 TCA0.SINGLE.CTRLA|=TCA_SINGLE_ENABLE_bm;
	LDS  R30,2560
	ORI  R30,1
	STS  2560,R30
; 0003 0056 }
	RET
; .FEND
;void tca1_init(void)
; 0003 005A {
_tca1_init:
; .FSTART _tca1_init
; 0003 005B // First disable and reset the Timer/Counter TCA1
; 0003 005C // Use 16-bit mode
; 0003 005D tca_disable(&TCA1);
	LDI  R26,LOW(2624)
	LDI  R27,HIGH(2624)
	CALL _tca_disable
; 0003 005E 
; 0003 005F // Clock divider: 1
; 0003 0060 // Clock frequency: 4000,960 kHz
; 0003 0061 // TCA1 runs in standby: Off
; 0003 0062 TCA1.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1_gc+(0<<TCA_SINGLE_RUNSTDBY_bp);
	LDI  R30,LOW(0)
	STS  2624,R30
; 0003 0063 
; 0003 0064 // Operating mode: Normal 16-bit OVF=TOP
; 0003 0065 TCA1.SINGLE.CTRLB=TCA_SINGLE_WGMODE_NORMAL_gc;
	STS  2625,R30
; 0003 0066 
; 0003 0067 // Set the Timer Counter register
; 0003 0068 TCA1.SINGLE.CNT=0x00;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	STS  2656,R30
	STS  2656+1,R31
; 0003 0069 
; 0003 006A // Set the Timer Period register
; 0003 006B // Specified period: 1 ms
; 0003 006C // Obtained: 1,00001 ms, 0,00 % error
; 0003 006D TCA1.SINGLE.PER=0xFA0;
	LDI  R30,LOW(4000)
	LDI  R31,HIGH(4000)
	STS  2662,R30
	STS  2662+1,R31
; 0003 006E 
; 0003 006F // Set the Event Control register
; 0003 0070 // Event input A: No action
; 0003 0071 // Event input B: No action
; 0003 0072 TCA1.SINGLE.EVCTRL=(0<<TCA_SINGLE_CNTAEI_bp)+(0<<TCA_SINGLE_CNTBEI_bp);
	LDI  R30,LOW(0)
	STS  2633,R30
; 0003 0073 
; 0003 0074 // Set TCA1 interrupts:
; 0003 0075 // Overflow interrupt: On
; 0003 0076 // Compare Channel 0 interrupt: Off
; 0003 0077 // Compare Channel 1 interrupt: Off
; 0003 0078 // Compare Channel 2 interrupt: Off
; 0003 0079 TCA1.SINGLE.INTCTRL=
; 0003 007A (1<<TCA_SINGLE_OVF_bp)+
; 0003 007B (0<<TCA_SINGLE_CMP0_bp)+
; 0003 007C (0<<TCA_SINGLE_CMP1_bp)+
; 0003 007D (0<<TCA_SINGLE_CMP2_bp);
	LDI  R30,LOW(1)
	STS  2634,R30
; 0003 007E 
; 0003 007F // Initialization finished, enable TCA1
; 0003 0080 TCA1.SINGLE.CTRLA|=TCA_SINGLE_ENABLE_bm;
	LDS  R30,2624
	ORI  R30,1
	STS  2624,R30
; 0003 0081 }
	RET
; .FEND
;interrupt [(48)  ] void tca1_ovf_isr(void)
; 0003 0086 {
_tca1_ovf_isr:
; .FSTART _tca1_ovf_isr
	ST   -Y,R0
	ST   -Y,R1
	ST   -Y,R15
	ST   -Y,R22
	ST   -Y,R23
	ST   -Y,R24
	ST   -Y,R25
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0003 0087 // Ensure that the Overflow/Underflow interrupt flag is cleared
; 0003 0088 TCA1.SINGLE.INTFLAGS=TCA_SINGLE_OVF_bm;
	LDI  R30,LOW(1)
	STS  2635,R30
; 0003 0089 
; 0003 008A // Write your code here
; 0003 008B ms_cnt++;
	LDS  R30,_ms_cnt
	LDS  R31,_ms_cnt+1
	ADIW R30,1
	STS  _ms_cnt,R30
	STS  _ms_cnt+1,R31
; 0003 008C 
; 0003 008D if ( ms_delay_cnt ) {                         /* count down 1 ms delay */
	LDS  R30,_ms_delay_cnt
	LDS  R31,_ms_delay_cnt+1
	SBIW R30,0
	BRNE PC+3
	JMP _0x60003
; 0003 008E ms_delay_cnt-- ;
	SBIW R30,1
	STS  _ms_delay_cnt,R30
	STS  _ms_delay_cnt+1,R31
; 0003 008F }
; 0003 0090 
; 0003 0091 if ( !--sec_cnt )
_0x60003:
	LDS  R30,_sec_cnt
	LDS  R31,_sec_cnt+1
	SBIW R30,1
	STS  _sec_cnt,R30
	STS  _sec_cnt+1,R31
	SBIW R30,0
	BREQ PC+3
	JMP _0x60004
; 0003 0092 {               /* counter for 1 sec. */
; 0003 0093 sec_cnt = SEC_CNT_INIT;
	LDI  R30,LOW(1000)
	LDI  R31,HIGH(1000)
	STS  _sec_cnt,R30
	STS  _sec_cnt+1,R31
; 0003 0094 if ( time_b_cnt ) {           /* timer for temperature readings */
	LDS  R30,_time_b_cnt
	CPI  R30,0
	BRNE PC+3
	JMP _0x60005
; 0003 0095 time_b_cnt-- ;
	SUBI R30,LOW(1)
	STS  _time_b_cnt,R30
; 0003 0096 }
; 0003 0097 if ( time_e_cnt ) {           /* timer for eed check*/
_0x60005:
	LDS  R30,_time_e_cnt
	CPI  R30,0
	BRNE PC+3
	JMP _0x60006
; 0003 0098 time_e_cnt-- ;
	SUBI R30,LOW(1)
	STS  _time_e_cnt,R30
; 0003 0099 }
; 0003 009A }
_0x60006:
; 0003 009B 
; 0003 009C if ( ad_settling ) {                          /* count down ad setling time */
_0x60004:
	LDS  R30,_ad_settling
	LDS  R31,_ad_settling+1
	SBIW R30,0
	BRNE PC+3
	JMP _0x60007
; 0003 009D if ( !--ad_settling ) {
	SBIW R30,1
	STS  _ad_settling,R30
	STS  _ad_settling+1,R31
	SBIW R30,0
	BREQ PC+3
	JMP _0x60008
; 0003 009E ad_mode |= 0x20;                        /* Ok for int 1 */
	LDS  R30,_ad_mode
	ORI  R30,0x20
	STS  _ad_mode,R30
; 0003 009F }
; 0003 00A0 }
_0x60008:
; 0003 00A1 /* timeout ad converter */
; 0003 00A2 if ( ad_timeout_cnt )
_0x60007:
	LDS  R30,_ad_timeout_cnt
	LDS  R31,_ad_timeout_cnt+1
	SBIW R30,0
	BRNE PC+3
	JMP _0x60009
; 0003 00A3 {
; 0003 00A4 if ( !--ad_timeout_cnt )
	SBIW R30,1
	STS  _ad_timeout_cnt,R30
	STS  _ad_timeout_cnt+1,R31
	SBIW R30,0
	BREQ PC+3
	JMP _0x6000A
; 0003 00A5 {
; 0003 00A6 ad_state = IDLE ;
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0003 00A7 ResetADCBySW() ;
	CALL _ResetADCBySW
; 0003 00A8 }
; 0003 00A9 }
_0x6000A:
; 0003 00AA 
; 0003 00AB if ( rx_timeout ) {                               /* check timeout on tx0  */
_0x60009:
	LDS  R30,_rx_timeout
	CPI  R30,0
	BRNE PC+3
	JMP _0x6000B
; 0003 00AC if ( !--rx_timeout )
	SUBI R30,LOW(1)
	STS  _rx_timeout,R30
	CPI  R30,0
	BREQ PC+3
	JMP _0x6000C
; 0003 00AD {
; 0003 00AE ResetRxPointer();
	CALL _ResetRxPointer
; 0003 00AF }
; 0003 00B0 }
_0x6000C:
; 0003 00B1 
; 0003 00B2 
; 0003 00B3 if ( tx_tail ) {                                  /* check tx0 driver */
_0x6000B:
	LDS  R30,_tx_tail
	CPI  R30,0
	BRNE PC+3
	JMP _0x6000D
; 0003 00B4 if ( !--tx_tail ) {
	SUBI R30,LOW(1)
	STS  _tx_tail,R30
	CPI  R30,0
	BREQ PC+3
	JMP _0x6000E
; 0003 00B5 TxDriver(OFF);
	LDI  R26,LOW(0)
	CALL _TxDriver
; 0003 00B6 tx_complete = TRUE;
	LDI  R30,LOW(1)
	STS  _tx_complete,R30
; 0003 00B7 ResetRxPointer() ;          /* reset pointer */
	CALL _ResetRxPointer
; 0003 00B8 Led(1, OFF) ;
	LDI  R30,LOW(1)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _Led
; 0003 00B9 }
; 0003 00BA }
_0x6000E:
; 0003 00BB 
; 0003 00BC if ( wait_for_pc ) {                          /* delay before sending ch0 */
_0x6000D:
	LDS  R30,_wait_for_pc
	CPI  R30,0
	BRNE PC+3
	JMP _0x6000F
; 0003 00BD ad_mode |= 0x01 ;                /* mark that byte as sent */
	LDS  R30,_ad_mode
	ORI  R30,1
	STS  _ad_mode,R30
; 0003 00BE if ( !--wait_for_pc )
	LDS  R30,_wait_for_pc
	SUBI R30,LOW(1)
	STS  _wait_for_pc,R30
	CPI  R30,0
	BREQ PC+3
	JMP _0x60010
; 0003 00BF {
; 0003 00C0 //            SCI0_TDR = tx_buff[tx_indx++];
; 0003 00C1 //            SCI0_SSR &= ~SSR_TDRE;              /* clear TDRE-flag */
; 0003 00C2 //            SCI0_SCR |= SCR_TIE;                    /*  enable  tx int */
; 0003 00C3 Led(1, ON) ;
	LDI  R30,LOW(1)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _Led
; 0003 00C4 }
; 0003 00C5 }
_0x60010:
; 0003 00C6 }
_0x6000F:
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	LD   R25,Y+
	LD   R24,Y+
	LD   R23,Y+
	LD   R22,Y+
	LD   R15,Y+
	LD   R1,Y+
	LD   R0,Y+
	RETI
; .FEND
;void usart0_init(void)
; 0004 0013 {

	.CSEG
_usart0_init:
; .FSTART _usart0_init
; 0004 0014 // Note: The correct PORTA direction for the USART signals
; 0004 0015 // is configured in the ports_init function.
; 0004 0016 
; 0004 0017 // The USART0 signals are remapped:
; 0004 0018 // RxD: PORTA.5, TxD: PORTA.4
; 0004 0019 PORTMUX.USARTROUTEA=(PORTMUX.USARTROUTEA & ~PORTMUX_USART0_gm) | (1<<PORTMUX_USART0_gp);
	LDS  R30,1506
	ANDI R30,LOW(0xFC)
	ORI  R30,1
	STS  1506,R30
; 0004 001A 
; 0004 001B // Transmitter is enabled
; 0004 001C // Set TxD=1
; 0004 001D PORTA.OUTSET=0x10;
	LDI  R30,LOW(16)
	STS  1029,R30
; 0004 001E 
; 0004 001F // Communication mode: Asynchronous USART
; 0004 0020 // USART0 Mode: Asynchronous USART
; 0004 0021 // Data bits: 8
; 0004 0022 // Stop bits: 1
; 0004 0023 // Parity: Disabled
; 0004 0024 USART0.CTRLC=USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc | USART_CHSIZE_8BIT_gc;
	LDI  R30,LOW(3)
	STS  2055,R30
; 0004 0025 
; 0004 0026 // Receive complete interrupt: On
; 0004 0027 // Note: The transmitter Data Register Empty interrupt will be enabled later
; 0004 0028 // RS485 Mode: TxD buffer direction is controlled externally
; 0004 0029 USART0.CTRLA=(1<<USART_RXCIE_bp) | USART_RS485_EXT_gc;
	LDI  R30,LOW(129)
	STS  2053,R30
; 0004 002A 
; 0004 002B // Required Baud rate: 9600
; 0004 002C // Real Baud Rate: 9600,4 (x1 Mode), Error: 0,0 %
; 0004 002D USART0.BAUD=0x0683;
	LDI  R30,LOW(1667)
	LDI  R31,HIGH(1667)
	STS  2056,R30
	STS  2056+1,R31
; 0004 002E 
; 0004 002F // Receiver: On
; 0004 0030 // Transmitter: On
; 0004 0031 // TxD open drain: Off
; 0004 0032 // Double transmission speed mode: Off
; 0004 0033 // Multi-processor communication mode: Off
; 0004 0034 USART0.CTRLB=(1<<USART_RXEN_bp) | (1<<USART_TXEN_bp) | (0<<USART_ODME_bp) | USART_RXMODE_NORMAL_gc | (0<<USART_MPCM_bp);
	LDI  R30,LOW(192)
	STS  2054,R30
; 0004 0035 }
	RET
; .FEND
;char getchar(void)
; 0004 006B {
; 0004 006C char data;
; 0004 006D 
; 0004 006E while (rx_counter_usart0==0);
;	data -> R17
; 0004 006F data=rx_buffer_usart0[rx_rd_index_usart0++];
; 0004 0070 #if RX_BUFFER_SIZE_USART0 != 256
; 0004 0071 if (rx_rd_index_usart0 == RX_BUFFER_SIZE_USART0) rx_rd_index_usart0=0;
; 0004 0072 #endif
; 0004 0073 #asm("cli")
; 0004 0074 --rx_counter_usart0;
; 0004 0075 #asm("sei")
; 0004 0076 return data;
; 0004 0077 }
;void putchar(char c)
; 0004 0096 {
; 0004 0097 while (tx_counter_usart0 == TX_BUFFER_SIZE_USART0);
;	c -> R17
; 0004 0098 #asm("cli")
; 0004 0099 if (tx_counter_usart0 || ((USART0.STATUS & USART_DREIF_bm)==0))
; 0004 009A {
; 0004 009B tx_buffer_usart0[tx_wr_index_usart0++]=c;
; 0004 009C #if TX_BUFFER_SIZE_USART0 != 256
; 0004 009D if (tx_wr_index_usart0 == TX_BUFFER_SIZE_USART0) tx_wr_index_usart0=0;
; 0004 009E #endif
; 0004 009F ++tx_counter_usart0;
; 0004 00A0 }
; 0004 00A1 else
; 0004 00A2 {
; 0004 00A3 USART0.CTRLA|=USART_DREIE_bm;
; 0004 00A4 USART0.TXDATAL=c;
; 0004 00A5 }
; 0004 00A6 #asm("sei")
; 0004 00A7 }
;void spi1_init(void)
; 0005 000F {

	.CSEG
_spi1_init:
; .FSTART _spi1_init
; 0005 0010 // The SPI1 signals are not remapped:
; 0005 0011 // MOSI: PORTC.0, MISO: PORTC.1, SCK: PORTC.2, /SS: PORTC.3
; 0005 0012 PORTMUX.SPIROUTEA&= ~PORTMUX_SPI1_gm;
	LDS  R30,1508
	ANDI R30,LOW(0xF3)
	STS  1508,R30
; 0005 0013 // Note: The MOSI (PORTC, Pin 0), SCK (PORTC, Pin 2) and /SS (PORTC, Pin 3)
; 0005 0014 // signals are configured as outputs in the ports_init function.
; 0005 0015 
; 0005 0016 // SPI1 is enabled
; 0005 0017 // SPI mode: 3
; 0005 0018 // Operating as: Master
; 0005 0019 // Data order: MSB First
; 0005 001A // SCK clock prescaler: 128
; 0005 001B // SCK clock doubled: Off
; 0005 001C // SCK clock frequency: 31,257 kHz
; 0005 001D SPI1.CTRLA=SPI_ENABLE_bm | (1<<SPI_MASTER_bp) | (0<<SPI_DORD_bp) |
; 0005 001E SPI_PRESC_DIV128_gc | (0<<SPI_CLK2X_bp);
	LDI  R30,LOW(39)
	STS  2400,R30
; 0005 001F 
; 0005 0020 // SPI mode: 3
; 0005 0021 // /SS signal used as chip select: On
; 0005 0022 SPI1.CTRLB=SPI_MODE_3_gc | (0<<SPI_SSD_bp);
	LDI  R30,LOW(3)
	STS  2401,R30
; 0005 0023 
; 0005 0024 // SPI1 interrupt: Off
; 0005 0025 SPI1.INTCTRL=(0<<SPI_IE_bp);
	LDI  R30,LOW(0)
	STS  2402,R30
; 0005 0026 }
	RET
; .FEND
;unsigned char spi1_master_tx_rx(unsigned char c)
; 0005 002D {
_spi1_master_tx_rx:
; .FSTART _spi1_master_tx_rx
; 0005 002E // Transmit data in Master mode
; 0005 002F SPI1.DATA=c;
	ST   -Y,R17
	MOV  R17,R26
;	c -> R17
	STS  2404,R17
; 0005 0030 // Wait for the data to be transmitted/received
; 0005 0031 while ((SPI1.INTFLAGS & SPI_IF_bm)==0);
_0xA0003:
	LDS  R30,2403
	ANDI R30,LOW(0x80)
	BREQ PC+3
	JMP _0xA0005
	RJMP _0xA0003
_0xA0005:
; 0005 0032 // Return the received data
; 0005 0033 return SPI1.DATA;
	LDS  R30,2404
	LD   R17,Y+
	RET
; 0005 0034 }
; .FEND
;void    InitVar(void)
; 0006 00AD {

	.CSEG
_InitVar:
; .FSTART _InitVar
; 0006 00AE /*************************************************************************
; 0006 00AF *
; 0006 00B0 *	Initialize variables
; 0006 00B1 *
; 0006 00B2 *************************************************************************/
; 0006 00B3 
; 0006 00B4 short i;
; 0006 00B5 /*
; 0006 00B6 **	Init the the com cannal variables
; 0006 00B7 */
; 0006 00B8 tx_indx = 0 ;
	ST   -Y,R17
	ST   -Y,R16
;	i -> R16,R17
	LDI  R30,LOW(0)
	STS  _tx_indx,R30
; 0006 00B9 tx_complete = TRUE ;
	LDI  R30,LOW(1)
	STS  _tx_complete,R30
; 0006 00BA tx_bytes = 0 ;
	LDI  R30,LOW(0)
	STS  _tx_bytes,R30
; 0006 00BB tx_tail = 0 ;
	STS  _tx_tail,R30
; 0006 00BC wait_for_pc = 0 ;
	STS  _wait_for_pc,R30
; 0006 00BD rx_indx = 1 ;
	LDI  R30,LOW(1)
	STS  _rx_indx,R30
; 0006 00BE rx_hndx = 1 ;
	STS  _rx_hndx,R30
; 0006 00BF rx_start = 0 ;
	LDI  R30,LOW(0)
	STS  _rx_start,R30
; 0006 00C0 rx_buff[0] = 0 ;
	STS  _rx_buff,R30
; 0006 00C1 rx_counter = 0 ;
	STS  _rx_counter,R30
; 0006 00C2 rx_state = SYNC ;
	STS  _rx_state,R30
; 0006 00C3 rx_timeout = 0 ;
	STS  _rx_timeout,R30
; 0006 00C4 
; 0006 00C5 /*
; 0006 00C6 **	Init channel variables
; 0006 00C7 */
; 0006 00C8 for ( i = 0; i< NOIOCH; i += 2 ) {
	__GETWRN 16,17,0
_0xC0004:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xC0005
; 0006 00C9 ch_stat[i] = 0x0c ;         /*channel setup, try pressure */
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LDI  R30,LOW(12)
	ST   X,R30
; 0006 00CA }
_0xC0003:
	__ADDWRN 16,17,2
	RJMP _0xC0004
_0xC0005:
; 0006 00CB for ( i = 1; i< NOIOCH; i += 2 ) {
	__GETWRN 16,17,1
_0xC0007:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xC0008
; 0006 00CC ch_stat[i] = 0x04 ;         /*channel setup, try temp */
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LDI  R30,LOW(4)
	ST   X,R30
; 0006 00CD }
_0xC0006:
	__ADDWRN 16,17,2
	RJMP _0xC0007
_0xC0008:
; 0006 00CE for ( i = 0; i< NOPSD; i++ ) {
	__GETWRN 16,17,0
_0xC000A:
	__CPWRN 16,17,8
	BRLO PC+3
	JMP _0xC000B
; 0006 00CF eep_type[i] = 0 ;               /*eeprom status */
	LDI  R26,LOW(_eep_type)
	LDI  R27,HIGH(_eep_type)
	ADD  R26,R16
	ADC  R27,R17
	LDI  R30,LOW(0)
	ST   X,R30
; 0006 00D0 }
_0xC0009:
	__ADDWRN 16,17,1
	RJMP _0xC000A
_0xC000B:
; 0006 00D1 for ( i = 0; i< NOIOCH; i++ ) {
	__GETWRN 16,17,0
_0xC000D:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xC000E
; 0006 00D2 offset[i] = 0 ;                         /*channel setup, offest */
	MOVW R30,R16
	LDI  R26,LOW(_offset)
	LDI  R27,HIGH(_offset)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	ST   X+,R30
	ST   X,R31
; 0006 00D3 gain[i] = 1.0;
	MOVW R30,R16
	LDI  R26,LOW(_gain)
	LDI  R27,HIGH(_gain)
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1N 0x3F800000
	__PUTDP1
; 0006 00D4 }
_0xC000C:
	__ADDWRN 16,17,1
	RJMP _0xC000D
_0xC000E:
; 0006 00D5 
; 0006 00D6 /*
; 0006 00D7 **	Init other variables
; 0006 00D8 */
; 0006 00D9 
; 0006 00DA cal_gain = 1.0 ;
	__GETD1N 0x3F800000
	STS  _cal_gain,R30
	STS  _cal_gain+1,R31
	STS  _cal_gain+2,R22
	STS  _cal_gain+3,R23
; 0006 00DB cal_zero = 0 ;
	STS  _cal_zero,R30
	STS  _cal_zero+1,R30
; 0006 00DC p_filter = 5 ;
	LDI  R30,LOW(5)
	STS  _p_filter,R30
; 0006 00DD t_filter = 2 ;
	LDI  R30,LOW(2)
	STS  _t_filter,R30
; 0006 00DE o_filter = 2 ;
	STS  _o_filter,R30
; 0006 00DF sec_cnt = SEC_CNT_INIT;                 /* initvalue for 1 sec counter */
	LDI  R30,LOW(1000)
	LDI  R31,HIGH(1000)
	STS  _sec_cnt,R30
	STS  _sec_cnt+1,R31
; 0006 00E0 ms_cnt   = 0;
	LDI  R30,LOW(0)
	STS  _ms_cnt,R30
	STS  _ms_cnt+1,R30
; 0006 00E1 ad_state = IDLE ;                           /* no convertion */
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 00E2 curr_ad_ch = NOIOCH  ;
	LDI  R30,LOW(14)
	STS  _curr_ad_ch,R30
; 0006 00E3 ad_mode = 0x88 ;                            /* test mode on and start with press.*/
	LDI  R30,LOW(136)
	STS  _ad_mode,R30
; 0006 00E4 ad_mode |= 0x10 ;                           /* mark restart of card */
	ORI  R30,0x10
	STS  _ad_mode,R30
; 0006 00E5 ad_gain = 0 ;                               /* gain 1 */
	LDI  R30,LOW(0)
	STS  _ad_gain,R30
; 0006 00E6 time_b_temp = 15 ;                      /* temp readings in sec */
	LDI  R30,LOW(15)
	STS  _time_b_temp,R30
; 0006 00E7 time_b_cnt = time_b_temp ;
	STS  _time_b_cnt,R30
; 0006 00E8 time_e_cnt = TIME_BETWEEN_EEP ;
	STS  _time_e_cnt,R30
; 0006 00E9 not_mes_data = 0 ;
	LDI  R30,LOW(0)
	STS  _not_mes_data,R30
; 0006 00EA not_raw_data = 0 ;
	STS  _not_raw_data,R30
; 0006 00EB not_cal_data = 0 ;
	STS  _not_cal_data,R30
; 0006 00EC 
; 0006 00ED 
; 0006 00EE }
	LD   R16,Y+
	LD   R17,Y+
	RET
; .FEND
;void    InitStartup(void)
; 0006 00F1 {
_InitStartup:
; .FSTART _InitStartup
; 0006 00F2 
; 0006 00F3 ResetADCByHW();             // CS is low
	CALL _ResetADCByHW
; 0006 00F4 //P5DR |= ADCLK ;                             /*	set AD clock line high */
; 0006 00F5 ADC_CLOCK_HIGH;                             /*	set AD clock line high */
	LDI  R30,LOW(4)
	STS  1093,R30
; 0006 00F6 Led(1, OFF) ;                               /* switch leds off */
	LDI  R30,LOW(1)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _Led
; 0006 00F7 Led(2, OFF) ;
	LDI  R30,LOW(2)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _Led
; 0006 00F8 Led(3, OFF) ;
	LDI  R30,LOW(3)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _Led
; 0006 00F9 Led(4, OFF) ;
	LDI  R30,LOW(4)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _Led
; 0006 00FA 
; 0006 00FB TxDriver(OFF) ;                             /* tx enable off */
	LDI  R26,LOW(0)
	CALL _TxDriver
; 0006 00FC SetEepromChannel(EEPCHOFF) ;            /* set eeprom channel off */
	LDI  R26,LOW(9)
	CALL _SetEepromChannel
; 0006 00FD SetMuxChannel(MUXCHOFF) ;               /* set mux channel off */
	LDI  R26,LOW(16)
	CALL _SetMuxChannel
; 0006 00FE SetSupplyChannel(SUPPCHOFF) ;            /* set supply channel off */
	LDI  R26,LOW(16)
	CALL _SetSupplyChannel
; 0006 00FF SetGNDChannel (GNDCHOFF);
	LDI  R26,LOW(9)
	CALL _SetGNDChannel
; 0006 0100 SetSupplyCurrent(1);                        /* set 1 mA supply */
	LDI  R26,LOW(1)
	CALL _SetSupplyCurrent
; 0006 0101 
; 0006 0102 //GetMyAddress() ;                            /* get my address */
; 0006 0103 my_address=MYADRESS_LOCAL;
	LDI  R30,LOW(9)
	STS  _my_address,R30
; 0006 0104 }
	RET
; .FEND
;void Led(unsigned char no, unsigned char state)
; 0006 0107 {
_Led:
; .FSTART _Led
; 0006 0108 switch ( no )
	ST   -Y,R17
	ST   -Y,R16
	MOV  R17,R26
	LDD  R16,Y+2
;	no -> R16
;	state -> R17
	MOV  R30,R16
	LDI  R31,0
; 0006 0109 {
; 0006 010A case    1:                                      /* LED 1 */
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0012
; 0006 010B switch ( state ) {
	MOV  R30,R17
	LDI  R31,0
; 0006 010C case ON :
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0016
; 0006 010D LED1_ON;
	LDI  R30,LOW(16)
	STS  1062,R30
; 0006 010E break ;
	RJMP _0xC0015
; 0006 010F case OFF :
_0xC0016:
	SBIW R30,0
	BREQ PC+3
	JMP _0xC0018
; 0006 0110 default :
_0xC0018:
; 0006 0111 LED1_OFF;
	LDI  R30,LOW(16)
	STS  1061,R30
; 0006 0112 break ;
; 0006 0113 }
_0xC0015:
; 0006 0114 break ;
	RJMP _0xC0011
; 0006 0115 
; 0006 0116 case    2:                                      /* LED 2 */
_0xC0012:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0019
; 0006 0117 switch ( state ) {
	MOV  R30,R17
	LDI  R31,0
; 0006 0118 case ON :
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC001D
; 0006 0119 LED2_ON;
	LDI  R30,LOW(32)
	STS  1062,R30
; 0006 011A break ;
	RJMP _0xC001C
; 0006 011B case OFF :
_0xC001D:
	SBIW R30,0
	BREQ PC+3
	JMP _0xC001F
; 0006 011C default :
_0xC001F:
; 0006 011D LED2_OFF;
	LDI  R30,LOW(32)
	STS  1061,R30
; 0006 011E break ;
; 0006 011F }
_0xC001C:
; 0006 0120 break ;
	RJMP _0xC0011
; 0006 0121 
; 0006 0122 case 3:
_0xC0019:
	CPI  R30,LOW(0x3)
	LDI  R26,HIGH(0x3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0020
; 0006 0123 switch ( state ) {
	MOV  R30,R17
	LDI  R31,0
; 0006 0124 case ON :
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0024
; 0006 0125 LED3_ON;
	LDI  R30,LOW(64)
	STS  1062,R30
; 0006 0126 break ;
	RJMP _0xC0023
; 0006 0127 case OFF :
_0xC0024:
	SBIW R30,0
	BREQ PC+3
	JMP _0xC0026
; 0006 0128 default :
_0xC0026:
; 0006 0129 LED3_OFF;
	LDI  R30,LOW(64)
	STS  1061,R30
; 0006 012A break ;
; 0006 012B }
_0xC0023:
; 0006 012C break ;
	RJMP _0xC0011
; 0006 012D 
; 0006 012E 
; 0006 012F case 4:
_0xC0020:
	CPI  R30,LOW(0x4)
	LDI  R26,HIGH(0x4)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC002E
; 0006 0130 
; 0006 0131 switch ( state ) {
	MOV  R30,R17
	LDI  R31,0
; 0006 0132 case ON :
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC002B
; 0006 0133 LED4_ON;
	LDI  R30,LOW(128)
	STS  1062,R30
; 0006 0134 break ;
	RJMP _0xC002A
; 0006 0135 case OFF :
_0xC002B:
	SBIW R30,0
	BREQ PC+3
	JMP _0xC002D
; 0006 0136 default :
_0xC002D:
; 0006 0137 LED4_OFF;
	LDI  R30,LOW(128)
	STS  1061,R30
; 0006 0138 break ;
; 0006 0139 }
_0xC002A:
; 0006 013A break;
	RJMP _0xC0011
; 0006 013B default :
_0xC002E:
; 0006 013C LED1_OFF;
	LDI  R30,LOW(16)
	STS  1061,R30
; 0006 013D LED2_OFF;
	LDI  R30,LOW(32)
	STS  1061,R30
; 0006 013E LED3_OFF;
	LDI  R30,LOW(64)
	STS  1061,R30
; 0006 013F LED4_OFF;
	LDI  R30,LOW(128)
	STS  1061,R30
; 0006 0140 break ;
; 0006 0141 }
_0xC0011:
; 0006 0142 }
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,3
	RET
; .FEND
;void TxDriver(unsigned char state)
; 0006 0149 {
_TxDriver:
; .FSTART _TxDriver
; 0006 014A switch ( state ) {
	ST   -Y,R17
	MOV  R17,R26
;	state -> R17
	MOV  R30,R17
	LDI  R31,0
; 0006 014B case ON :                           /* driver on */
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0032
; 0006 014C SETBIT( PORTA.OUT,7);
	LDI  R30,LOW(128)
	STS  1029,R30
; 0006 014D //delay_ms(5);
; 0006 014E USART0.CTRLA|=USART_DREIE_bm;      //enable sending
	LDS  R30,2053
	ORI  R30,0x20
	STS  2053,R30
; 0006 014F //USART0.TXDATAL=0;
; 0006 0150 break;
	RJMP _0xC0031
; 0006 0151 case OFF :
_0xC0032:
	SBIW R30,0
	BREQ PC+3
	JMP _0xC0034
; 0006 0152 //delay_ms(5);                          /* driver off */
; 0006 0153 CLRBIT( PORTA.OUT,7);
	LDI  R30,LOW(128)
	STS  1030,R30
; 0006 0154 break;
	RJMP _0xC0031
; 0006 0155 default :
_0xC0034:
; 0006 0156 break;
; 0006 0157 }
_0xC0031:
; 0006 0158 }
	LD   R17,Y+
	RET
; .FEND
;void SetEepromChannel(unsigned char channel)
; 0006 015F {
_SetEepromChannel:
; .FSTART _SetEepromChannel
; 0006 0160 SetGNDChannel ( channel);   // set GND on
	ST   -Y,R17
	MOV  R17,R26
;	channel -> R17
	CALL _SetGNDChannel
; 0006 0161 
; 0006 0162 if ( channel == EEPCHOFF )
	CPI  R17,9
	BREQ PC+3
	JMP _0xC0035
; 0006 0163 {
; 0006 0164 /* switch off any channel */
; 0006 0165 CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 0166 CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 0167 CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 0168 CLR_408E2;
	LDI  R30,LOW(8)
	STS  1222,R30
; 0006 0169 }
; 0006 016A else
	RJMP _0xC0036
_0xC0035:
; 0006 016B {   CLR_408E2;
	LDI  R30,LOW(8)
	STS  1222,R30
; 0006 016C switch (channel)
	MOV  R30,R17
	LDI  R31,0
; 0006 016D {  default:
	RJMP _0xC003A
_0xC003B:
; 0006 016E case 0:  //add 1
	RJMP _0xC003C
_0xC003A:
	SBIW R30,0
	BREQ PC+3
	JMP _0xC003D
_0xC003C:
; 0006 016F CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 0170 CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 0171 CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 0172 
; 0006 0173 break;
	RJMP _0xC0039
; 0006 0174 
; 0006 0175 case 1: //add 2
_0xC003D:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC003E
; 0006 0176 SET_408A0;
	LDI  R30,LOW(1)
	STS  1221,R30
; 0006 0177 CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 0178 CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 0179 break;
	RJMP _0xC0039
; 0006 017A 
; 0006 017B case 2:  //add 3
_0xC003E:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC003F
; 0006 017C CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 017D SET_408A1;
	LDI  R30,LOW(2)
	STS  1221,R30
; 0006 017E CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 017F break;
	RJMP _0xC0039
; 0006 0180 
; 0006 0181 case 3:  //add 4
_0xC003F:
	CPI  R30,LOW(0x3)
	LDI  R26,HIGH(0x3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0040
; 0006 0182 SET_408A0;
	LDI  R30,LOW(1)
	STS  1221,R30
; 0006 0183 SET_408A1;
	LDI  R30,LOW(2)
	STS  1221,R30
; 0006 0184 CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 0185 break;
	RJMP _0xC0039
; 0006 0186 
; 0006 0187 case 4:  //add 5
_0xC0040:
	CPI  R30,LOW(0x4)
	LDI  R26,HIGH(0x4)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0041
; 0006 0188 CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 0189 CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 018A SET_408A2;
	LDI  R30,LOW(4)
	STS  1221,R30
; 0006 018B break;
	RJMP _0xC0039
; 0006 018C 
; 0006 018D case 5:  //add 6
_0xC0041:
	CPI  R30,LOW(0x5)
	LDI  R26,HIGH(0x5)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0042
; 0006 018E SET_408A0;
	LDI  R30,LOW(1)
	STS  1221,R30
; 0006 018F CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 0190 SET_408A2;
	LDI  R30,LOW(4)
	STS  1221,R30
; 0006 0191 break;
	RJMP _0xC0039
; 0006 0192 
; 0006 0193 case 6:  //add 7
_0xC0042:
	CPI  R30,LOW(0x6)
	LDI  R26,HIGH(0x6)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0043
; 0006 0194 CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 0195 SET_408A1;
	LDI  R30,LOW(2)
	STS  1221,R30
; 0006 0196 SET_408A2;
	LDI  R30,LOW(4)
	STS  1221,R30
; 0006 0197 break;
	RJMP _0xC0039
; 0006 0198 
; 0006 0199 case 7:  //add 8
_0xC0043:
	CPI  R30,LOW(0x7)
	LDI  R26,HIGH(0x7)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC003B
; 0006 019A SET_408A0;
	LDI  R30,LOW(1)
	STS  1221,R30
; 0006 019B SET_408A1;
	LDI  R30,LOW(2)
	STS  1221,R30
; 0006 019C SET_408A2;
	LDI  R30,LOW(4)
	STS  1221,R30
; 0006 019D break;
; 0006 019E }
_0xC0039:
; 0006 019F SET_408E2 ;  /* set channel and enable bit */
	LDI  R30,LOW(8)
	STS  1221,R30
; 0006 01A0 }
_0xC0036:
; 0006 01A1 }
	LD   R17,Y+
	RET
; .FEND
;void SetSupplyChannel(unsigned char channel)
; 0006 01A8 {
_SetSupplyChannel:
; .FSTART _SetSupplyChannel
; 0006 01A9 
; 0006 01AA if ( channel == SUPPCHOFF )
	ST   -Y,R17
	MOV  R17,R26
;	channel -> R17
	CPI  R17,16
	BREQ PC+3
	JMP _0xC0045
; 0006 01AB {
; 0006 01AC CLR_406A0;                                 /* switch off any channel */
	LDI  R30,LOW(8)
	STS  1062,R30
; 0006 01AD CLR_406A1;
	LDI  R30,LOW(4)
	STS  1062,R30
; 0006 01AE CLR_406A2;
	LDI  R30,LOW(2)
	STS  1062,R30
; 0006 01AF CLR_406A3;
	LDI  R30,LOW(1)
	STS  1062,R30
; 0006 01B0 CLR_406E1;
	LDI  R30,LOW(128)
	STS  1094,R30
; 0006 01B1 }
; 0006 01B2 else
	RJMP _0xC0046
_0xC0045:
; 0006 01B3 {   CLR_406E1;  // turn off mux power
	LDI  R30,LOW(128)
	STS  1094,R30
; 0006 01B4 switch (channel)
	MOV  R30,R17
	LDI  R31,0
; 0006 01B5 {      default:
	RJMP _0xC004A
_0xC004B:
; 0006 01B6 case 0:
	RJMP _0xC004C
_0xC004A:
	SBIW R30,0
	BREQ PC+3
	JMP _0xC004D
_0xC004C:
; 0006 01B7 CLR_406A0;
	LDI  R30,LOW(8)
	STS  1062,R30
; 0006 01B8 CLR_406A1;
	LDI  R30,LOW(4)
	STS  1062,R30
; 0006 01B9 CLR_406A2;
	LDI  R30,LOW(2)
	STS  1062,R30
; 0006 01BA CLR_406A3;
	LDI  R30,LOW(1)
	STS  1062,R30
; 0006 01BB SetGNDChannel (0);
	LDI  R26,LOW(0)
	CALL _SetGNDChannel
; 0006 01BC break;
	RJMP _0xC0049
; 0006 01BD 
; 0006 01BE case 1:
_0xC004D:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC004E
; 0006 01BF SET_406A0;
	LDI  R30,LOW(8)
	STS  1061,R30
; 0006 01C0 CLR_406A1;
	LDI  R30,LOW(4)
	STS  1062,R30
; 0006 01C1 CLR_406A2;
	LDI  R30,LOW(2)
	STS  1062,R30
; 0006 01C2 CLR_406A3;
	LDI  R30,LOW(1)
	STS  1062,R30
; 0006 01C3 SetGNDChannel (0);
	LDI  R26,LOW(0)
	CALL _SetGNDChannel
; 0006 01C4 break;
	RJMP _0xC0049
; 0006 01C5 
; 0006 01C6 case 2:
_0xC004E:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC004F
; 0006 01C7 CLR_406A0;
	LDI  R30,LOW(8)
	STS  1062,R30
; 0006 01C8 SET_406A1;
	LDI  R30,LOW(4)
	STS  1061,R30
; 0006 01C9 CLR_406A2;
	LDI  R30,LOW(2)
	STS  1062,R30
; 0006 01CA CLR_406A3;
	LDI  R30,LOW(1)
	STS  1062,R30
; 0006 01CB SetGNDChannel (1);
	LDI  R26,LOW(1)
	CALL _SetGNDChannel
; 0006 01CC break;
	RJMP _0xC0049
; 0006 01CD 
; 0006 01CE case 3:
_0xC004F:
	CPI  R30,LOW(0x3)
	LDI  R26,HIGH(0x3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0050
; 0006 01CF SET_406A0;
	LDI  R30,LOW(8)
	STS  1061,R30
; 0006 01D0 SET_406A1;
	LDI  R30,LOW(4)
	STS  1061,R30
; 0006 01D1 CLR_406A2;
	LDI  R30,LOW(2)
	STS  1062,R30
; 0006 01D2 CLR_406A3;
	LDI  R30,LOW(1)
	STS  1062,R30
; 0006 01D3 SetGNDChannel (1);
	LDI  R26,LOW(1)
	CALL _SetGNDChannel
; 0006 01D4 break;
	RJMP _0xC0049
; 0006 01D5 
; 0006 01D6 case 4:
_0xC0050:
	CPI  R30,LOW(0x4)
	LDI  R26,HIGH(0x4)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0051
; 0006 01D7 CLR_406A0;
	LDI  R30,LOW(8)
	STS  1062,R30
; 0006 01D8 CLR_406A1;
	LDI  R30,LOW(4)
	STS  1062,R30
; 0006 01D9 SET_406A2;
	LDI  R30,LOW(2)
	STS  1061,R30
; 0006 01DA CLR_406A3;
	LDI  R30,LOW(1)
	STS  1062,R30
; 0006 01DB SetGNDChannel (2);
	LDI  R26,LOW(2)
	CALL _SetGNDChannel
; 0006 01DC break;
	RJMP _0xC0049
; 0006 01DD 
; 0006 01DE case 5:
_0xC0051:
	CPI  R30,LOW(0x5)
	LDI  R26,HIGH(0x5)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0052
; 0006 01DF SET_406A0;
	LDI  R30,LOW(8)
	STS  1061,R30
; 0006 01E0 CLR_406A1;
	LDI  R30,LOW(4)
	STS  1062,R30
; 0006 01E1 SET_406A2;
	LDI  R30,LOW(2)
	STS  1061,R30
; 0006 01E2 CLR_406A3;
	LDI  R30,LOW(1)
	STS  1062,R30
; 0006 01E3 SetGNDChannel (2);
	LDI  R26,LOW(2)
	CALL _SetGNDChannel
; 0006 01E4 break;
	RJMP _0xC0049
; 0006 01E5 
; 0006 01E6 case 6:
_0xC0052:
	CPI  R30,LOW(0x6)
	LDI  R26,HIGH(0x6)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0053
; 0006 01E7 CLR_406A0;
	LDI  R30,LOW(8)
	STS  1062,R30
; 0006 01E8 SET_406A1;
	LDI  R30,LOW(4)
	STS  1061,R30
; 0006 01E9 SET_406A2;
	LDI  R30,LOW(2)
	STS  1061,R30
; 0006 01EA CLR_406A3;
	LDI  R30,LOW(1)
	STS  1062,R30
; 0006 01EB SetGNDChannel (3);
	LDI  R26,LOW(3)
	CALL _SetGNDChannel
; 0006 01EC break;
	RJMP _0xC0049
; 0006 01ED 
; 0006 01EE case 7:
_0xC0053:
	CPI  R30,LOW(0x7)
	LDI  R26,HIGH(0x7)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0054
; 0006 01EF SET_406A0;
	LDI  R30,LOW(8)
	STS  1061,R30
; 0006 01F0 SET_406A1;
	LDI  R30,LOW(4)
	STS  1061,R30
; 0006 01F1 SET_406A2;
	LDI  R30,LOW(2)
	STS  1061,R30
; 0006 01F2 CLR_406A3;
	LDI  R30,LOW(1)
	STS  1062,R30
; 0006 01F3 SetGNDChannel (3);
	LDI  R26,LOW(3)
	CALL _SetGNDChannel
; 0006 01F4 break;
	RJMP _0xC0049
; 0006 01F5 
; 0006 01F6 case 8:
_0xC0054:
	CPI  R30,LOW(0x8)
	LDI  R26,HIGH(0x8)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0055
; 0006 01F7 CLR_406A0;
	LDI  R30,LOW(8)
	STS  1062,R30
; 0006 01F8 CLR_406A1;
	LDI  R30,LOW(4)
	STS  1062,R30
; 0006 01F9 CLR_406A2;
	LDI  R30,LOW(2)
	STS  1062,R30
; 0006 01FA SET_406A3;
	LDI  R30,LOW(1)
	STS  1061,R30
; 0006 01FB SetGNDChannel (4);
	LDI  R26,LOW(4)
	CALL _SetGNDChannel
; 0006 01FC break;
	RJMP _0xC0049
; 0006 01FD 
; 0006 01FE case 9:
_0xC0055:
	CPI  R30,LOW(0x9)
	LDI  R26,HIGH(0x9)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0056
; 0006 01FF SET_406A0;
	LDI  R30,LOW(8)
	STS  1061,R30
; 0006 0200 CLR_406A1;
	LDI  R30,LOW(4)
	STS  1062,R30
; 0006 0201 CLR_406A2;
	LDI  R30,LOW(2)
	STS  1062,R30
; 0006 0202 SET_406A3;
	LDI  R30,LOW(1)
	STS  1061,R30
; 0006 0203 SetGNDChannel (4);
	LDI  R26,LOW(4)
	CALL _SetGNDChannel
; 0006 0204 break;
	RJMP _0xC0049
; 0006 0205 
; 0006 0206 case 10:
_0xC0056:
	CPI  R30,LOW(0xA)
	LDI  R26,HIGH(0xA)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0057
; 0006 0207 CLR_406A0;
	LDI  R30,LOW(8)
	STS  1062,R30
; 0006 0208 SET_406A1;
	LDI  R30,LOW(4)
	STS  1061,R30
; 0006 0209 CLR_406A2;
	LDI  R30,LOW(2)
	STS  1062,R30
; 0006 020A SET_406A3;
	LDI  R30,LOW(1)
	STS  1061,R30
; 0006 020B SetGNDChannel (5);
	LDI  R26,LOW(5)
	CALL _SetGNDChannel
; 0006 020C break;
	RJMP _0xC0049
; 0006 020D 
; 0006 020E case 11:
_0xC0057:
	CPI  R30,LOW(0xB)
	LDI  R26,HIGH(0xB)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0058
; 0006 020F SET_406A0;
	LDI  R30,LOW(8)
	STS  1061,R30
; 0006 0210 SET_406A1;
	LDI  R30,LOW(4)
	STS  1061,R30
; 0006 0211 CLR_406A2;
	LDI  R30,LOW(2)
	STS  1062,R30
; 0006 0212 SET_406A3;
	LDI  R30,LOW(1)
	STS  1061,R30
; 0006 0213 SetGNDChannel (5);
	LDI  R26,LOW(5)
	CALL _SetGNDChannel
; 0006 0214 break;
	RJMP _0xC0049
; 0006 0215 
; 0006 0216 case 12:
_0xC0058:
	CPI  R30,LOW(0xC)
	LDI  R26,HIGH(0xC)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0059
; 0006 0217 CLR_406A0;
	LDI  R30,LOW(8)
	STS  1062,R30
; 0006 0218 CLR_406A1;
	LDI  R30,LOW(4)
	STS  1062,R30
; 0006 0219 SET_406A2;
	LDI  R30,LOW(2)
	STS  1061,R30
; 0006 021A SET_406A3;
	LDI  R30,LOW(1)
	STS  1061,R30
; 0006 021B SetGNDChannel (6);
	LDI  R26,LOW(6)
	CALL _SetGNDChannel
; 0006 021C break;
	RJMP _0xC0049
; 0006 021D 
; 0006 021E case 13:
_0xC0059:
	CPI  R30,LOW(0xD)
	LDI  R26,HIGH(0xD)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC005A
; 0006 021F SET_406A0;
	LDI  R30,LOW(8)
	STS  1061,R30
; 0006 0220 CLR_406A1;
	LDI  R30,LOW(4)
	STS  1062,R30
; 0006 0221 SET_406A2;
	LDI  R30,LOW(2)
	STS  1061,R30
; 0006 0222 SET_406A3;
	LDI  R30,LOW(1)
	STS  1061,R30
; 0006 0223 SetGNDChannel (6);
	LDI  R26,LOW(6)
	CALL _SetGNDChannel
; 0006 0224 break;
	RJMP _0xC0049
; 0006 0225 
; 0006 0226 case 14:
_0xC005A:
	CPI  R30,LOW(0xE)
	LDI  R26,HIGH(0xE)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC005B
; 0006 0227 CLR_406A0;
	LDI  R30,LOW(8)
	STS  1062,R30
; 0006 0228 SET_406A1;
	LDI  R30,LOW(4)
	STS  1061,R30
; 0006 0229 SET_406A2;
	LDI  R30,LOW(2)
	STS  1061,R30
; 0006 022A SET_406A3;
	LDI  R30,LOW(1)
	STS  1061,R30
; 0006 022B SetGNDChannel (7);
	LDI  R26,LOW(7)
	CALL _SetGNDChannel
; 0006 022C break;
	RJMP _0xC0049
; 0006 022D 
; 0006 022E case 15:
_0xC005B:
	CPI  R30,LOW(0xF)
	LDI  R26,HIGH(0xF)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC004B
; 0006 022F SET_406A0;
	LDI  R30,LOW(8)
	STS  1061,R30
; 0006 0230 SET_406A1;
	LDI  R30,LOW(4)
	STS  1061,R30
; 0006 0231 SET_406A2;
	LDI  R30,LOW(2)
	STS  1061,R30
; 0006 0232 SET_406A3;
	LDI  R30,LOW(1)
	STS  1061,R30
; 0006 0233 SetGNDChannel (7);
	LDI  R26,LOW(7)
	CALL _SetGNDChannel
; 0006 0234 break;
; 0006 0235 }
_0xC0049:
; 0006 0236 SET_406E1;  // Enable Mux power
	LDI  R30,LOW(128)
	STS  1093,R30
; 0006 0237 }
_0xC0046:
; 0006 0238 }
	LD   R17,Y+
	RET
; .FEND
;void SetGNDChannel(unsigned char channel)
; 0006 0240 {
_SetGNDChannel:
; .FSTART _SetGNDChannel
; 0006 0241 if ( channel == EEPCHOFF )
	ST   -Y,R17
	MOV  R17,R26
;	channel -> R17
	CPI  R17,9
	BREQ PC+3
	JMP _0xC005D
; 0006 0242 {
; 0006 0243 /* switch off any channel */
; 0006 0244 CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 0245 CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 0246 CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 0247 CLR_408E1;
	LDI  R30,LOW(16)
	STS  1222,R30
; 0006 0248 }
; 0006 0249 else
	RJMP _0xC005E
_0xC005D:
; 0006 024A {   CLR_408E1;
	LDI  R30,LOW(16)
	STS  1222,R30
; 0006 024B switch (channel)
	MOV  R30,R17
	LDI  R31,0
; 0006 024C {  default:
	RJMP _0xC0062
_0xC0063:
; 0006 024D case 0:  //add 1
	RJMP _0xC0064
_0xC0062:
	SBIW R30,0
	BREQ PC+3
	JMP _0xC0065
_0xC0064:
; 0006 024E CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 024F CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 0250 CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 0251 
; 0006 0252 break;
	RJMP _0xC0061
; 0006 0253 
; 0006 0254 case 1: //add 2
_0xC0065:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0066
; 0006 0255 SET_408A0;
	LDI  R30,LOW(1)
	STS  1221,R30
; 0006 0256 CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 0257 CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 0258 break;
	RJMP _0xC0061
; 0006 0259 
; 0006 025A case 2:  //add 3
_0xC0066:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0067
; 0006 025B CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 025C SET_408A1;
	LDI  R30,LOW(2)
	STS  1221,R30
; 0006 025D CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 025E break;
	RJMP _0xC0061
; 0006 025F 
; 0006 0260 case 3:  //add 4
_0xC0067:
	CPI  R30,LOW(0x3)
	LDI  R26,HIGH(0x3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0068
; 0006 0261 SET_408A0;
	LDI  R30,LOW(1)
	STS  1221,R30
; 0006 0262 SET_408A1;
	LDI  R30,LOW(2)
	STS  1221,R30
; 0006 0263 CLR_408A2;
	LDI  R30,LOW(4)
	STS  1222,R30
; 0006 0264 break;
	RJMP _0xC0061
; 0006 0265 
; 0006 0266 case 4:  //add 5
_0xC0068:
	CPI  R30,LOW(0x4)
	LDI  R26,HIGH(0x4)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0069
; 0006 0267 CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 0268 CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 0269 SET_408A2;
	LDI  R30,LOW(4)
	STS  1221,R30
; 0006 026A break;
	RJMP _0xC0061
; 0006 026B 
; 0006 026C case 5:  //add 6
_0xC0069:
	CPI  R30,LOW(0x5)
	LDI  R26,HIGH(0x5)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC006A
; 0006 026D SET_408A0;
	LDI  R30,LOW(1)
	STS  1221,R30
; 0006 026E CLR_408A1;
	LDI  R30,LOW(2)
	STS  1222,R30
; 0006 026F SET_408A2;
	LDI  R30,LOW(4)
	STS  1221,R30
; 0006 0270 break;
	RJMP _0xC0061
; 0006 0271 
; 0006 0272 case 6:  //add 7
_0xC006A:
	CPI  R30,LOW(0x6)
	LDI  R26,HIGH(0x6)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC006B
; 0006 0273 CLR_408A0;
	LDI  R30,LOW(1)
	STS  1222,R30
; 0006 0274 SET_408A1;
	LDI  R30,LOW(2)
	STS  1221,R30
; 0006 0275 SET_408A2;
	LDI  R30,LOW(4)
	STS  1221,R30
; 0006 0276 break;
	RJMP _0xC0061
; 0006 0277 
; 0006 0278 case 7:  //add 8
_0xC006B:
	CPI  R30,LOW(0x7)
	LDI  R26,HIGH(0x7)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0063
; 0006 0279 SET_408A0;
	LDI  R30,LOW(1)
	STS  1221,R30
; 0006 027A SET_408A1;
	LDI  R30,LOW(2)
	STS  1221,R30
; 0006 027B SET_408A2;
	LDI  R30,LOW(4)
	STS  1221,R30
; 0006 027C break;
; 0006 027D 
; 0006 027E }
_0xC0061:
; 0006 027F SET_408E1 ;  /* set channel and enable bit */
	LDI  R30,LOW(16)
	STS  1221,R30
; 0006 0280 }
_0xC005E:
; 0006 0281 }
	LD   R17,Y+
	RET
; .FEND
;void SetMuxChannel(unsigned char channel)
; 0006 028B {
_SetMuxChannel:
; .FSTART _SetMuxChannel
; 0006 028C 
; 0006 028D if ( channel == MUXCHOFF )
	ST   -Y,R17
	MOV  R17,R26
;	channel -> R17
	CPI  R17,16
	BREQ PC+3
	JMP _0xC006D
; 0006 028E {
; 0006 028F CLR_407E1 ;                             /* switch off any channel */
	LDI  R30,LOW(32)
	STS  1094,R30
; 0006 0290 CLR_407E2 ;                             /* switch off any channel */
	LDI  R30,LOW(64)
	STS  1094,R30
; 0006 0291 }
; 0006 0292 else
	RJMP _0xC006E
_0xC006D:
; 0006 0293 {
; 0006 0294 CLR_407E1 ;                             /* switch off any channel */
	LDI  R30,LOW(32)
	STS  1094,R30
; 0006 0295 CLR_407E2 ;
	LDI  R30,LOW(64)
	STS  1094,R30
; 0006 0296 switch (channel)
	MOV  R30,R17
	LDI  R31,0
; 0006 0297 {
; 0006 0298 default:
	RJMP _0xC0072
_0xC0073:
; 0006 0299 case 0:
	RJMP _0xC0074
_0xC0072:
	SBIW R30,0
	BREQ PC+3
	JMP _0xC0075
_0xC0074:
; 0006 029A CLR_407A0;
	LDI  R30,LOW(32)
	STS  1222,R30
; 0006 029B CLR_407A1;
	LDI  R30,LOW(64)
	STS  1222,R30
; 0006 029C CLR_407A2;
	LDI  R30,LOW(128)
	STS  1222,R30
; 0006 029D SET_407E1;
	LDI  R30,LOW(32)
	STS  1093,R30
; 0006 029E break;
	RJMP _0xC0071
; 0006 029F 
; 0006 02A0 case 1:
_0xC0075:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0076
; 0006 02A1 SET_407A0;
	LDI  R30,LOW(32)
	STS  1221,R30
; 0006 02A2 CLR_407A1;
	LDI  R30,LOW(64)
	STS  1222,R30
; 0006 02A3 CLR_407A2;
	LDI  R30,LOW(128)
	STS  1222,R30
; 0006 02A4 SET_407E1;
	LDI  R30,LOW(32)
	STS  1093,R30
; 0006 02A5 break;
	RJMP _0xC0071
; 0006 02A6 
; 0006 02A7 case 2:
_0xC0076:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0077
; 0006 02A8 CLR_407A0;
	LDI  R30,LOW(32)
	STS  1222,R30
; 0006 02A9 SET_407A1;
	LDI  R30,LOW(64)
	STS  1221,R30
; 0006 02AA CLR_407A2;
	LDI  R30,LOW(128)
	STS  1222,R30
; 0006 02AB SET_407E1;
	LDI  R30,LOW(32)
	STS  1093,R30
; 0006 02AC break;
	RJMP _0xC0071
; 0006 02AD 
; 0006 02AE case 3:
_0xC0077:
	CPI  R30,LOW(0x3)
	LDI  R26,HIGH(0x3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0078
; 0006 02AF SET_407A0;
	LDI  R30,LOW(32)
	STS  1221,R30
; 0006 02B0 SET_407A1;
	LDI  R30,LOW(64)
	STS  1221,R30
; 0006 02B1 CLR_407A2;
	LDI  R30,LOW(128)
	STS  1222,R30
; 0006 02B2 SET_407E1;
	LDI  R30,LOW(32)
	STS  1093,R30
; 0006 02B3 break;
	RJMP _0xC0071
; 0006 02B4 
; 0006 02B5 case 4:
_0xC0078:
	CPI  R30,LOW(0x4)
	LDI  R26,HIGH(0x4)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0079
; 0006 02B6 CLR_407A0;
	LDI  R30,LOW(32)
	STS  1222,R30
; 0006 02B7 CLR_407A1;
	LDI  R30,LOW(64)
	STS  1222,R30
; 0006 02B8 SET_407A2;
	LDI  R30,LOW(128)
	STS  1221,R30
; 0006 02B9 SET_407E1;
	LDI  R30,LOW(32)
	STS  1093,R30
; 0006 02BA break;
	RJMP _0xC0071
; 0006 02BB 
; 0006 02BC case 5:
_0xC0079:
	CPI  R30,LOW(0x5)
	LDI  R26,HIGH(0x5)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC007A
; 0006 02BD SET_407A0;
	LDI  R30,LOW(32)
	STS  1221,R30
; 0006 02BE CLR_407A1;
	LDI  R30,LOW(64)
	STS  1222,R30
; 0006 02BF SET_407A2;
	LDI  R30,LOW(128)
	STS  1221,R30
; 0006 02C0 SET_407E1;
	LDI  R30,LOW(32)
	STS  1093,R30
; 0006 02C1 break;
	RJMP _0xC0071
; 0006 02C2 
; 0006 02C3 case 6:
_0xC007A:
	CPI  R30,LOW(0x6)
	LDI  R26,HIGH(0x6)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC007B
; 0006 02C4 CLR_407A0;
	LDI  R30,LOW(32)
	STS  1222,R30
; 0006 02C5 SET_407A1;
	LDI  R30,LOW(64)
	STS  1221,R30
; 0006 02C6 SET_407A2;
	LDI  R30,LOW(128)
	STS  1221,R30
; 0006 02C7 SET_407E1;
	LDI  R30,LOW(32)
	STS  1093,R30
; 0006 02C8 break;
	RJMP _0xC0071
; 0006 02C9 
; 0006 02CA case 7:
_0xC007B:
	CPI  R30,LOW(0x7)
	LDI  R26,HIGH(0x7)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC007C
; 0006 02CB SET_407A0;
	LDI  R30,LOW(32)
	STS  1221,R30
; 0006 02CC SET_407A1;
	LDI  R30,LOW(64)
	STS  1221,R30
; 0006 02CD SET_407A2;
	LDI  R30,LOW(128)
	STS  1221,R30
; 0006 02CE SET_407E1;
	LDI  R30,LOW(32)
	STS  1093,R30
; 0006 02CF break;
	RJMP _0xC0071
; 0006 02D0 
; 0006 02D1 case 8:
_0xC007C:
	CPI  R30,LOW(0x8)
	LDI  R26,HIGH(0x8)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC007D
; 0006 02D2 CLR_407A0;
	LDI  R30,LOW(32)
	STS  1222,R30
; 0006 02D3 CLR_407A1;
	LDI  R30,LOW(64)
	STS  1222,R30
; 0006 02D4 CLR_407A2;
	LDI  R30,LOW(128)
	STS  1222,R30
; 0006 02D5 SET_407E2;
	LDI  R30,LOW(64)
	STS  1093,R30
; 0006 02D6 break;
	RJMP _0xC0071
; 0006 02D7 
; 0006 02D8 case 9:
_0xC007D:
	CPI  R30,LOW(0x9)
	LDI  R26,HIGH(0x9)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC007E
; 0006 02D9 SET_407A0;
	LDI  R30,LOW(32)
	STS  1221,R30
; 0006 02DA CLR_407A1;
	LDI  R30,LOW(64)
	STS  1222,R30
; 0006 02DB CLR_407A2;
	LDI  R30,LOW(128)
	STS  1222,R30
; 0006 02DC SET_407E2;
	LDI  R30,LOW(64)
	STS  1093,R30
; 0006 02DD break;
	RJMP _0xC0071
; 0006 02DE 
; 0006 02DF case 10:
_0xC007E:
	CPI  R30,LOW(0xA)
	LDI  R26,HIGH(0xA)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC007F
; 0006 02E0 CLR_407A0;
	LDI  R30,LOW(32)
	STS  1222,R30
; 0006 02E1 SET_407A1;
	LDI  R30,LOW(64)
	STS  1221,R30
; 0006 02E2 CLR_407A2;
	LDI  R30,LOW(128)
	STS  1222,R30
; 0006 02E3 SET_407E2;
	LDI  R30,LOW(64)
	STS  1093,R30
; 0006 02E4 break;
	RJMP _0xC0071
; 0006 02E5 
; 0006 02E6 case 11:
_0xC007F:
	CPI  R30,LOW(0xB)
	LDI  R26,HIGH(0xB)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0080
; 0006 02E7 SET_407A0;
	LDI  R30,LOW(32)
	STS  1221,R30
; 0006 02E8 SET_407A1;
	LDI  R30,LOW(64)
	STS  1221,R30
; 0006 02E9 CLR_407A2;
	LDI  R30,LOW(128)
	STS  1222,R30
; 0006 02EA SET_407E2;
	LDI  R30,LOW(64)
	STS  1093,R30
; 0006 02EB break;
	RJMP _0xC0071
; 0006 02EC 
; 0006 02ED case 12:
_0xC0080:
	CPI  R30,LOW(0xC)
	LDI  R26,HIGH(0xC)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0081
; 0006 02EE CLR_407A0;
	LDI  R30,LOW(32)
	STS  1222,R30
; 0006 02EF CLR_407A1;
	LDI  R30,LOW(64)
	STS  1222,R30
; 0006 02F0 SET_407A2;
	LDI  R30,LOW(128)
	STS  1221,R30
; 0006 02F1 SET_407E2;
	LDI  R30,LOW(64)
	STS  1093,R30
; 0006 02F2 break;
	RJMP _0xC0071
; 0006 02F3 
; 0006 02F4 case 13:
_0xC0081:
	CPI  R30,LOW(0xD)
	LDI  R26,HIGH(0xD)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0082
; 0006 02F5 SET_407A0;
	LDI  R30,LOW(32)
	STS  1221,R30
; 0006 02F6 CLR_407A1;
	LDI  R30,LOW(64)
	STS  1222,R30
; 0006 02F7 SET_407A2;
	LDI  R30,LOW(128)
	STS  1221,R30
; 0006 02F8 SET_407E2;
	LDI  R30,LOW(64)
	STS  1093,R30
; 0006 02F9 break;
	RJMP _0xC0071
; 0006 02FA 
; 0006 02FB case 14:         // Set cal 1K
_0xC0082:
	CPI  R30,LOW(0xE)
	LDI  R26,HIGH(0xE)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0083
; 0006 02FC CLR_407A0;
	LDI  R30,LOW(32)
	STS  1222,R30
; 0006 02FD SET_407A1;
	LDI  R30,LOW(64)
	STS  1221,R30
; 0006 02FE SET_407A2;
	LDI  R30,LOW(128)
	STS  1221,R30
; 0006 02FF SET_407E2;
	LDI  R30,LOW(64)
	STS  1093,R30
; 0006 0300 break;
	RJMP _0xC0071
; 0006 0301 
; 0006 0302 case 15:         // not used
_0xC0083:
	CPI  R30,LOW(0xF)
	LDI  R26,HIGH(0xF)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC0073
; 0006 0303 SET_407A0;
	LDI  R30,LOW(32)
	STS  1221,R30
; 0006 0304 SET_407A1;
	LDI  R30,LOW(64)
	STS  1221,R30
; 0006 0305 SET_407A2;
	LDI  R30,LOW(128)
	STS  1221,R30
; 0006 0306 SET_407E2;
	LDI  R30,LOW(64)
	STS  1093,R30
; 0006 0307 break;
; 0006 0308 }
_0xC0071:
; 0006 0309 }
_0xC006E:
; 0006 030A }
	LD   R17,Y+
	RET
; .FEND
;void SetSupplyCurrent(unsigned char current)
; 0006 0312 {
_SetSupplyCurrent:
; .FSTART _SetSupplyCurrent
; 0006 0313 if ( current == 10 )
	ST   -Y,R17
	MOV  R17,R26
;	current -> R17
	CPI  R17,10
	BREQ PC+3
	JMP _0xC0085
; 0006 0314 {
; 0006 0315 CUR_10MA;                    /* set 10 mA */
	LDI  R30,LOW(4)
	STS  1190,R30
; 0006 0316 }
; 0006 0317 else
	RJMP _0xC0086
_0xC0085:
; 0006 0318 {
; 0006 0319 CUR_1MA ;                    /* set 1 mA */
	LDI  R30,LOW(4)
	STS  1189,R30
; 0006 031A }
_0xC0086:
; 0006 031B }
	LD   R17,Y+
	RET
; .FEND
;void SetCalResistance(unsigned char value)
; 0006 0324 {
_SetCalResistance:
; .FSTART _SetCalResistance
; 0006 0325 switch ( value )
	ST   -Y,R17
	MOV  R17,R26
;	value -> R17
	MOV  R30,R17
	LDI  R31,0
; 0006 0326 {
; 0006 0327 case OHM_1R :   // 1 ohm resistor
	CPI  R30,LOW(0x40)
	LDI  R26,HIGH(0x40)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC008A
; 0006 0328 SET_RES1R ;
	LDI  R30,LOW(16)
	STS  1189,R30
; 0006 0329 CLR_RES1K ;
	LDI  R30,LOW(8)
	STS  1190,R30
; 0006 032A break ;
	RJMP _0xC0089
; 0006 032B case OHM_1K :  // 1000 ohm resistor
_0xC008A:
	CPI  R30,LOW(0x80)
	LDI  R26,HIGH(0x80)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC008C
; 0006 032C SET_RES1K ;
	LDI  R30,LOW(8)
	STS  1189,R30
; 0006 032D CLR_RES1R ;
	LDI  R30,LOW(16)
	STS  1190,R30
; 0006 032E break ;
	RJMP _0xC0089
; 0006 032F default :     // both off
_0xC008C:
; 0006 0330 CLR_RES1R ;
	LDI  R30,LOW(16)
	STS  1190,R30
; 0006 0331 CLR_RES1K;
	LDI  R30,LOW(8)
	STS  1190,R30
; 0006 0332 break ;
; 0006 0333 }
_0xC0089:
; 0006 0334 }
	LD   R17,Y+
	RET
; .FEND
;void CheckConvert(void)
; 0006 033B {
_CheckConvert:
; .FSTART _CheckConvert
; 0006 033C 
; 0006 033D if ( ad_state == IDLE ) {            /* New channel? */
	LDS  R26,_ad_state
	CPI  R26,LOW(0x7)
	BREQ PC+3
	JMP _0xC008D
; 0006 033E ad_state = START_NEW_POINT ;
	LDI  R30,LOW(1)
	STS  _ad_state,R30
; 0006 033F if ( curr_ad_ch < (NOIOCH-1) )
	LDS  R26,_curr_ad_ch
	CPI  R26,LOW(0xD)
	BRLT PC+3
	JMP _0xC008E
; 0006 0340 {   old_curr_ad_ch= curr_ad_ch; // debugg
	LDS  R30,_curr_ad_ch
	STS  _old_curr_ad_ch,R30
; 0006 0341 curr_ad_ch++ ;
	LDS  R30,_curr_ad_ch
	SUBI R30,-LOW(1)
	STS  _curr_ad_ch,R30
; 0006 0342 }
; 0006 0343 else
	RJMP _0xC008F
_0xC008E:
; 0006 0344 {
; 0006 0345 curr_ad_ch = 0 ;
	LDI  R30,LOW(0)
	STS  _curr_ad_ch,R30
; 0006 0346 if ( !time_e_cnt ) {
	LDS  R30,_time_e_cnt
	CPI  R30,0
	BREQ PC+3
	JMP _0xC0090
; 0006 0347 if ( ad_mode & 0x80 ) {               /* test */
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x80)
	BRNE PC+3
	JMP _0xC0091
; 0006 0348 ad_mode &= ~0x80 ;              /* test mode off */
	LDS  R30,_ad_mode
	ANDI R30,0x7F
	STS  _ad_mode,R30
; 0006 0349 }
; 0006 034A CheckEepChannel()   ;                   /* Check the sensordata */
_0xC0091:
	CALL _CheckEepChannel
; 0006 034B time_e_cnt = TIME_BETWEEN_EEP ;
	LDI  R30,LOW(15)
	STS  _time_e_cnt,R30
; 0006 034C }
; 0006 034D if ( not_mes_data && (ad_mode & 0x02) )
_0xC0090:
	LDS  R30,_not_mes_data
	CPI  R30,0
	BRNE PC+3
	JMP _0xC0093
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x2)
	BRNE PC+3
	JMP _0xC0093
	RJMP _0xC0094
_0xC0093:
	RJMP _0xC0092
_0xC0094:
; 0006 034E {     /* autosend? */
; 0006 034F BuildHeader() ;                     /* Build send packet header */
	CALL _BuildHeader
; 0006 0350 BuildMPData();                      /* Build data p. for pressure */
	CALL _BuildMPData
; 0006 0351 BuildMTData();                      /* Build data p. for temp */
	CALL _BuildMTData
; 0006 0352 BuildMOData();                      /* Build data p. for other */
	CALL _BuildMOData
; 0006 0353 BuildTail(NO_MORE_DATA, 0) ;    /* Build tail */
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _BuildTail
; 0006 0354 not_mes_data-- ;
	LDS  R30,_not_mes_data
	SUBI R30,LOW(1)
	STS  _not_mes_data,R30
; 0006 0355 }
; 0006 0356 else if ( not_raw_data && (ad_mode & 0x02) )
	RJMP _0xC0095
_0xC0092:
	LDS  R30,_not_raw_data
	CPI  R30,0
	BRNE PC+3
	JMP _0xC0097
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x2)
	BRNE PC+3
	JMP _0xC0097
	RJMP _0xC0098
_0xC0097:
	RJMP _0xC0096
_0xC0098:
; 0006 0357 {  /* autosend? */
; 0006 0358 BuildHeader() ;                     /* Build send packet header */
	CALL _BuildHeader
; 0006 0359 BuildRPData();                      /* Build data p. for pressure */
	CALL _BuildRPData
; 0006 035A BuildRTData();                      /* Build data p. for temp */
	CALL _BuildRTData
; 0006 035B BuildROData();                      /* Build data p. for other */
	CALL _BuildROData
; 0006 035C BuildTail(NO_MORE_DATA, 0) ;    /* Build tail */
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _BuildTail
; 0006 035D not_raw_data-- ;
	LDS  R30,_not_raw_data
	SUBI R30,LOW(1)
	STS  _not_raw_data,R30
; 0006 035E }
; 0006 035F else if ( not_cal_data && (ad_mode & 0x02) ) {  /* autosend? */
	RJMP _0xC0099
_0xC0096:
	LDS  R30,_not_cal_data
	CPI  R30,0
	BRNE PC+3
	JMP _0xC009B
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x2)
	BRNE PC+3
	JMP _0xC009B
	RJMP _0xC009C
_0xC009B:
	RJMP _0xC009A
_0xC009C:
; 0006 0360 BuildHeader() ;                     /* Build send packet header */
	CALL _BuildHeader
; 0006 0361 BuildCalData();                     /* Build data p. for calib */
	CALL _BuildCalData
; 0006 0362 BuildTail(NO_MORE_DATA, 0) ;    /* Build tail */
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _BuildTail
; 0006 0363 not_cal_data-- ;
	LDS  R30,_not_cal_data
	SUBI R30,LOW(1)
	STS  _not_cal_data,R30
; 0006 0364 }
; 0006 0365 if ( ad_mode & 0x08 )
_0xC009A:
_0xC0099:
_0xC0095:
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x8)
	BRNE PC+3
	JMP _0xC009D
; 0006 0366 {           /* temp readings */
; 0006 0367 ad_mode &= ~0x0e ;
	LDS  R30,_ad_mode
	ANDI R30,LOW(0xF1)
	STS  _ad_mode,R30
; 0006 0368 ad_mode |= 0x02 ;
	ORI  R30,2
	STS  _ad_mode,R30
; 0006 0369 ad_state = START_CALIBRATION ;
	LDI  R30,LOW(4)
	STS  _ad_state,R30
; 0006 036A }
; 0006 036B else if ( ad_mode & 0x04 )
	RJMP _0xC009E
_0xC009D:
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x4)
	BRNE PC+3
	JMP _0xC009F
; 0006 036C {    /* "other" */
; 0006 036D ad_mode &= ~0x0e ;
	LDS  R30,_ad_mode
	ANDI R30,LOW(0xF1)
	STS  _ad_mode,R30
; 0006 036E ad_mode |= 0x08 ;
	ORI  R30,8
	STS  _ad_mode,R30
; 0006 036F ad_state = START_CALIBRATION ;
	LDI  R30,LOW(4)
	STS  _ad_state,R30
; 0006 0370 }
; 0006 0371 else if ( ad_mode & 0x02 )
	RJMP _0xC00A0
_0xC009F:
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x2)
	BRNE PC+3
	JMP _0xC00A1
; 0006 0372 {            /* pressure */
; 0006 0373 if ( !time_b_cnt )
	LDS  R30,_time_b_cnt
	CPI  R30,0
	BREQ PC+3
	JMP _0xC00A2
; 0006 0374 {
; 0006 0375 ad_mode &= ~0x0e ;
	LDS  R30,_ad_mode
	ANDI R30,LOW(0xF1)
	STS  _ad_mode,R30
; 0006 0376 ad_mode |= 0x04 ;                   /* convert temp */
	ORI  R30,4
	STS  _ad_mode,R30
; 0006 0377 ad_state = START_CALIBRATION ;
	LDI  R30,LOW(4)
	STS  _ad_state,R30
; 0006 0378 time_b_cnt = time_b_temp ;      /* reload counter */
	LDS  R30,_time_b_temp
	STS  _time_b_cnt,R30
; 0006 0379 }
; 0006 037A }
_0xC00A2:
; 0006 037B else
	RJMP _0xC00A3
_0xC00A1:
; 0006 037C {
; 0006 037D ad_mode &= ~0x0e ;
	LDS  R30,_ad_mode
	ANDI R30,LOW(0xF1)
	STS  _ad_mode,R30
; 0006 037E ad_mode |= 0x04 ;                       /* next pressure */
	ORI  R30,4
	STS  _ad_mode,R30
; 0006 037F }
_0xC00A3:
_0xC00A0:
_0xC009E:
; 0006 0380 }
_0xC008F:
; 0006 0381 }
; 0006 0382 if ( tx_complete ) {
_0xC008D:
	LDS  R30,_tx_complete
	CPI  R30,0
	BRNE PC+3
	JMP _0xC00A4
; 0006 0383 ADConvert() ;                                   /* convert data */
	CALL _ADConvert
; 0006 0384 }
; 0006 0385 }
_0xC00A4:
	RET
; .FEND
;void ADConvert(void)
; 0006 038E {
_ADConvert:
; .FSTART _ADConvert
; 0006 038F unsigned short ad_data ;
; 0006 0390 unsigned char tmpSwitch;
; 0006 0391 switch ( ad_state )
	CALL __SAVELOCR4
;	ad_data -> R16,R17
;	tmpSwitch -> R19
	LDS  R30,_ad_state
	LDI  R31,0
; 0006 0392 {
; 0006 0393 case    START_NEW_POINT :
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00A8
; 0006 0394 ad_mode &= ~0x01 ;                           /* reset tx check marker */
	LDS  R30,_ad_mode
	ANDI R30,0xFE
	STS  _ad_mode,R30
; 0006 0395 ad_timeout_cnt = AD_TIMEOUT ;                   /* timeout ad cnv */
	LDI  R30,LOW(2000)
	LDI  R31,HIGH(2000)
	STS  _ad_timeout_cnt,R30
	STS  _ad_timeout_cnt+1,R31
; 0006 0396 tmpSwitch = (ch_stat[curr_ad_ch]>> 2) & 0x03;
	LDS  R30,_curr_ad_ch
	LDI  R31,0
	SUBI R30,LOW(-_ch_stat)
	SBCI R31,HIGH(-_ch_stat)
	LD   R30,Z
	LSR  R30
	LSR  R30
	ANDI R30,LOW(0x3)
	MOV  R19,R30
; 0006 0397 //switch ( (ch_stat[curr_ad_ch]>> 2) & 0x03 ) { // OLDCODE
; 0006 0398 switch (tmpSwitch )
	LDI  R31,0
; 0006 0399 {
; 0006 039A case 0x03 :              /* pressure */
	CPI  R30,LOW(0x3)
	LDI  R26,HIGH(0x3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00AC
; 0006 039B if ( ad_mode & 0x02 ) {                       /* pressure readings */
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x2)
	BRNE PC+3
	JMP _0xC00AD
; 0006 039C SetCalResistance(OHM_1R);
	LDI  R26,LOW(64)
	CALL _SetCalResistance
; 0006 039D SetSupplyChannel(curr_ad_ch) ;
	LDS  R26,_curr_ad_ch
	CALL _SetSupplyChannel
; 0006 039E SetSupplyCurrent(10) ;  // 10mA
	LDI  R26,LOW(10)
	CALL _SetSupplyCurrent
; 0006 039F SetMuxChannel(curr_ad_ch) ;
	LDS  R26,_curr_ad_ch
	CALL _SetMuxChannel
; 0006 03A0 ad_gain = 3 ;
	LDI  R30,LOW(3)
	STS  _ad_gain,R30
; 0006 03A1 spi1_master_tx_rx(ad_gain | 0x10) ; // Next write SetupRegister
	ORI  R30,0x10
	MOV  R26,R30
	CALL _spi1_master_tx_rx
; 0006 03A2 //spi1_master_tx_rx(0x2a) ;         // Ad setup data, bipolar
; 0006 03A3 spi1_master_tx_rx(0b00011000) ;       // MD1&0:00, CLK=0 FS1&9 11 B/U:0 BUF=0 FSYNC 0
	LDI  R26,LOW(24)
	CALL _spi1_master_tx_rx
; 0006 03A4 ad_settling = AD_SET_TIME ;         /* wait 67 ms */
	LDI  R30,LOW(67)
	LDI  R31,HIGH(67)
	STS  _ad_settling,R30
	STS  _ad_settling+1,R31
; 0006 03A5 ad_state = WAIT_FOR_INTERRUPT ;         /* next state */
	LDI  R30,LOW(2)
	STS  _ad_state,R30
; 0006 03A6 } else {
	RJMP _0xC00AE
_0xC00AD:
; 0006 03A7 ad_state = IDLE ;
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 03A8 }
_0xC00AE:
; 0006 03A9 break;
	RJMP _0xC00AB
; 0006 03AA case 0x02 :               /* "OTHER " */
_0xC00AC:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00AF
; 0006 03AB if ( ad_mode & 0x04 ) {                       /* other readings */
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x4)
	BRNE PC+3
	JMP _0xC00B0
; 0006 03AC SetCalResistance(OHM_1K);
	LDI  R26,LOW(128)
	CALL _SetCalResistance
; 0006 03AD SetSupplyChannel(curr_ad_ch) ;
	LDS  R26,_curr_ad_ch
	CALL _SetSupplyChannel
; 0006 03AE SetSupplyCurrent(1) ;
	LDI  R26,LOW(1)
	CALL _SetSupplyCurrent
; 0006 03AF SetMuxChannel(curr_ad_ch) ;
	LDS  R26,_curr_ad_ch
	CALL _SetMuxChannel
; 0006 03B0 ad_gain = 0 ;
	LDI  R30,LOW(0)
	STS  _ad_gain,R30
; 0006 03B1 spi1_master_tx_rx(ad_gain | 0x10) ;            /* Next write data */
	ORI  R30,0x10
	MOV  R26,R30
	CALL _spi1_master_tx_rx
; 0006 03B2 //spi1_master_tx_rx(0x2a) ;                      /* Ad setup data */
; 0006 03B3 spi1_master_tx_rx(0b00011000) ;       // MD1&0:00, CLK=0 FS1&9 11 B/U:0 BUF=0 FSYNC 0
	LDI  R26,LOW(24)
	CALL _spi1_master_tx_rx
; 0006 03B4 ad_settling = AD_SET_TIME ;          /* wait 67 ms */
	LDI  R30,LOW(67)
	LDI  R31,HIGH(67)
	STS  _ad_settling,R30
	STS  _ad_settling+1,R31
; 0006 03B5 ad_state = WAIT_FOR_INTERRUPT ;          /* next state */
	LDI  R30,LOW(2)
	STS  _ad_state,R30
; 0006 03B6 } else {
	RJMP _0xC00B1
_0xC00B0:
; 0006 03B7 ad_state = IDLE ;
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 03B8 }
_0xC00B1:
; 0006 03B9 break;
	RJMP _0xC00AB
; 0006 03BA case 0x01 :               /* temp */
_0xC00AF:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00B5
; 0006 03BB if ( ad_mode & 0x08 ) {                       /* convert temp? */
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x8)
	BRNE PC+3
	JMP _0xC00B3
; 0006 03BC SetCalResistance(OHM_1K);
	LDI  R26,LOW(128)
	CALL _SetCalResistance
; 0006 03BD SetSupplyChannel(curr_ad_ch) ;
	LDS  R26,_curr_ad_ch
	CALL _SetSupplyChannel
; 0006 03BE SetSupplyCurrent(1) ;
	LDI  R26,LOW(1)
	CALL _SetSupplyCurrent
; 0006 03BF SetMuxChannel(curr_ad_ch) ;
	LDS  R26,_curr_ad_ch
	CALL _SetMuxChannel
; 0006 03C0 ad_gain = 0 ;
	LDI  R30,LOW(0)
	STS  _ad_gain,R30
; 0006 03C1 spi1_master_tx_rx(ad_gain | 0x10) ;            /* Next write data */
	ORI  R30,0x10
	MOV  R26,R30
	CALL _spi1_master_tx_rx
; 0006 03C2 //spi1_master_tx_rx(0x2a) ;                     /* Ad setup data, bipolar*/
; 0006 03C3 spi1_master_tx_rx(0b00011000) ;       // MD1&0:00, CLK=0 FS1&9 11 B/U:0 BUF=0 FSYNC 0
	LDI  R26,LOW(24)
	CALL _spi1_master_tx_rx
; 0006 03C4 ad_settling = AD_SET_TIME ;          /* wait 67 ms */
	LDI  R30,LOW(67)
	LDI  R31,HIGH(67)
	STS  _ad_settling,R30
	STS  _ad_settling+1,R31
; 0006 03C5 ad_state = WAIT_FOR_INTERRUPT ;          /* next state */
	LDI  R30,LOW(2)
	STS  _ad_state,R30
; 0006 03C6 } else {
	RJMP _0xC00B4
_0xC00B3:
; 0006 03C7 ad_state = IDLE ;
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 03C8 }
_0xC00B4:
; 0006 03C9 break;
	RJMP _0xC00AB
; 0006 03CA default :
_0xC00B5:
; 0006 03CB ad_state = IDLE ;
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 03CC break ;
; 0006 03CD }
_0xC00AB:
; 0006 03CE break ;
	RJMP _0xC00A7
; 0006 03CF case    WAIT_FOR_INTERRUPT :
_0xC00A8:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00B6
; 0006 03D0 break ;
	RJMP _0xC00A7
; 0006 03D1 case    CONV_COMPLETE :
_0xC00B6:
	CPI  R30,LOW(0x3)
	LDI  R26,HIGH(0x3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00B7
; 0006 03D2 spi1_master_tx_rx(ad_gain | 0x38) ;                   /* Next read data */
	LDS  R30,_ad_gain
	ORI  R30,LOW(0x38)
	MOV  R26,R30
	CALL _spi1_master_tx_rx
; 0006 03D3 ad_data = spi1_master_tx_rx(0xFF)* 256 ;              /* read data 16 bit data from ad */
	LDI  R26,LOW(255)
	CALL _spi1_master_tx_rx
	MOV  R31,R30
	LDI  R30,0
	MOVW R16,R30
; 0006 03D4 ad_data += spi1_master_tx_rx(0xFF);
	LDI  R26,LOW(255)
	CALL _spi1_master_tx_rx
	LDI  R31,0
	__ADDWRR 16,17,30,31
; 0006 03D5 if ( ad_mode & 0x40 ) {                           /* cal point ? */
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x40)
	BRNE PC+3
	JMP _0xC00B8
; 0006 03D6 ad_mode &= ~0x40 ;
	LDS  R30,_ad_mode
	ANDI R30,0xBF
	STS  _ad_mode,R30
; 0006 03D7 SetSupplyCurrent(1) ;
	LDI  R26,LOW(1)
	CALL _SetSupplyCurrent
; 0006 03D8 SetMuxChannel(MUXCHOFF) ;
	LDI  R26,LOW(16)
	CALL _SetMuxChannel
; 0006 03D9 SetSupplyChannel(SUPPCHOFF) ;
	LDI  R26,LOW(16)
	CALL _SetSupplyChannel
; 0006 03DA SetCalResistance(OFF);
	LDI  R26,LOW(0)
	CALL _SetCalResistance
; 0006 03DB ad_state = IDLE ;
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 03DC ad_timeout_cnt = 0 ;                            /* timeout off */
	LDI  R30,LOW(0)
	STS  _ad_timeout_cnt,R30
	STS  _ad_timeout_cnt+1,R30
; 0006 03DD if ( !(ad_mode & 0x01) ) {                    /* tx during conv? */
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x1)
	BREQ PC+3
	JMP _0xC00B9
; 0006 03DE short tmp_cal_data = ad_data - 32767 ;    /* no, use data  */
; 0006 03DF float cal_val = tmp_cal_data* cal_gain;
; 0006 03E0 cal_data[curr_ad_ch] = (short)tmp_cal_data ;     /* adjust for resistor errors */
	SBIW R28,6
;	tmp_cal_data -> Y+4
;	cal_val -> Y+0
	MOVW R30,R16
	SUBI R30,LOW(32767)
	SBCI R31,HIGH(32767)
	STD  Y+4,R30
	STD  Y+4+1,R31
	LDS  R30,_cal_gain
	LDS  R31,_cal_gain+1
	LDS  R22,_cal_gain+2
	LDS  R23,_cal_gain+3
	LDD  R26,Y+4
	LDD  R27,Y+4+1
	CLR  R24
	CLR  R25
	CALL __CDF2
	CALL __MULF12
	__PUTD1S 0
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_cal_data)
	LDI  R27,HIGH(_cal_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	LDD  R26,Y+4
	LDD  R27,Y+4+1
	STD  Z+0,R26
	STD  Z+1,R27
; 0006 03E1 tmpSwitch = (ch_stat[curr_ad_ch]>> 2) & 0x03;
	LDS  R30,_curr_ad_ch
	LDI  R31,0
	SUBI R30,LOW(-_ch_stat)
	SBCI R31,HIGH(-_ch_stat)
	LD   R30,Z
	LSR  R30
	LSR  R30
	ANDI R30,LOW(0x3)
	MOV  R19,R30
; 0006 03E2 //switch ( (ch_stat[curr_ad_ch]>> 2) & 0x03 )  //old code just to debugg
; 0006 03E3 switch ( tmpSwitch )
	LDI  R31,0
; 0006 03E4 {
; 0006 03E5 
; 0006 03E6 case 0x03 :                /* pressure */
	CPI  R30,LOW(0x3)
	LDI  R26,HIGH(0x3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00BD
; 0006 03E7 if ( (cal_val > MAX_PRE_CAL) ||
; 0006 03E8 (cal_val < MIN_PRE_CAL) ) {
	__GETD2S 0
	__GETD1N 0x4708B800
	CALL __CMPF12
	BREQ PC+4
	BRCS PC+3
	JMP  _0xC00BF
	__GETD1N 0x46435000
	CALL __CMPF12
	BRSH PC+3
	JMP _0xC00BF
	RJMP _0xC00BE
_0xC00BF:
; 0006 03E9 ch_stat[curr_ad_ch] |= 0x02 ;         /* Calibration fail */
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ORI  R30,2
	ST   X,R30
; 0006 03EA }
; 0006 03EB else
	RJMP _0xC00C1
_0xC00BE:
; 0006 03EC {
; 0006 03ED ch_stat[curr_ad_ch] &= ~0x02 ;  /* Calibration OK */
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ANDI R30,0xFD
	ST   X,R30
; 0006 03EE }
_0xC00C1:
; 0006 03EF 
; 0006 03F0 if ( (cal_val > FMAX_PRE_CAL)||
; 0006 03F1 (cal_val < FMIN_PRE_CAL) )
	__GETD2S 0
	__GETD1N 0x46AFC800
	CALL __CMPF12
	BREQ PC+4
	BRCS PC+3
	JMP  _0xC00C3
	__GETD1N 0x45EA6000
	CALL __CMPF12
	BRSH PC+3
	JMP _0xC00C3
	RJMP _0xC00C2
_0xC00C3:
; 0006 03F2 {
; 0006 03F3 ch_stat[curr_ad_ch] |= 0x01 ;       /* Reading fail */
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ORI  R30,1
	ST   X,R30
; 0006 03F4 eep_type[curr_ad_ch >> 1] = 0 ;     /* clear read status */
	LDS  R30,_curr_ad_ch
	LDI  R31,0
	SBRC R30,7
	SER  R31
	ASR  R31
	ROR  R30
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	LDI  R26,LOW(0)
	STD  Z+0,R26
; 0006 03F5 mes_data[curr_ad_ch] = 0.0 ;       /* ASt mark ?? */
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1N 0x0
	__PUTDP1
; 0006 03F6 raw_data[curr_ad_ch] = curr_sens_data ; /* sen raw raw */
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	LDS  R26,_curr_sens_data
	LDS  R27,_curr_sens_data+1
	STD  Z+0,R26
	STD  Z+1,R27
; 0006 03F7 if ( ad_mode & 0x80 )
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x80)
	BRNE PC+3
	JMP _0xC00C5
; 0006 03F8 {               /* test */
; 0006 03F9 ch_stat[curr_ad_ch] &= ~0x60 ;  /* no sensor */
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ANDI R30,LOW(0x9F)
	ST   X,R30
; 0006 03FA }
; 0006 03FB }
_0xC00C5:
; 0006 03FC else
	RJMP _0xC00C6
_0xC00C2:
; 0006 03FD {
; 0006 03FE // debugg
; 0006 03FF //  curr_sens_data-->INT
; 0006 0400 //  cal_zero --> INT
; 0006 0401 
; 0006 0402 //                     float msrd_snsdata = curr_sens_data -cal_zero;
; 0006 0403 //                     if (cal_val){
; 0006 0404 //                        msrd_snsdata *= 20000.0/cal_val;
; 0006 0405 //                     } else{
; 0006 0406 //                        msrd_snsdata = 0.0;
; 0006 0407 //                     }
; 0006 0408 // use long not float
; 0006 0409 long msrd_snsdata = curr_sens_data -cal_zero;
; 0006 040A if (cal_val){
	SBIW R28,4
;	tmp_cal_data -> Y+8
;	cal_val -> Y+4
;	msrd_snsdata -> Y+0
	LDS  R26,_cal_zero
	LDS  R27,_cal_zero+1
	LDS  R30,_curr_sens_data
	LDS  R31,_curr_sens_data+1
	SUB  R30,R26
	SBC  R31,R27
	CLR  R22
	CLR  R23
	__PUTD1S 0
	__GETD1S 4
	__CPD10
	BRNE PC+3
	JMP _0xC00C7
; 0006 040B msrd_snsdata *= 20000/cal_val;
	__GETD2N 0x469C4000
	CALL __DIVF21
	__GETD2S 0
	CALL __CDF2
	CALL __MULF12
	__PUTD1S 0
; 0006 040C } else{
	RJMP _0xC00C8
_0xC00C7:
; 0006 040D msrd_snsdata = 0;
	LDI  R30,LOW(0)
	__CLRD1S 0
; 0006 040E }
_0xC00C8:
; 0006 040F if ( ad_mode & 0x80 )
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x80)
	BRNE PC+3
	JMP _0xC00C9
; 0006 0410 {               /* test */
; 0006 0411 ch_stat[curr_ad_ch] |= 0x6c ;   /* pr. sensor  OK*/
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ORI  R30,LOW(0x6C)
	ST   X,R30
; 0006 0412 }
; 0006 0413 ch_stat[curr_ad_ch] &= ~0x01 ;  /* Reading OK */
_0xC00C9:
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ANDI R30,0xFE
	ST   X,R30
; 0006 0414 //curr_sens_data -= cal_zero ;
; 0006 0415 raw_data[curr_ad_ch] = ( short)msrd_snsdata ;
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	LD   R26,Y
	LDD  R27,Y+1
	STD  Z+0,R26
	STD  Z+1,R27
; 0006 0416 CalcPress(curr_ad_ch) ;             /* calculate pressure */
	LDS  R26,_curr_ad_ch
	CALL _CalcPress
; 0006 0417 }
	ADIW R28,4
_0xC00C6:
; 0006 0418 
; 0006 0419 break;
	RJMP _0xC00BC
; 0006 041A 
; 0006 041B case 0x02 :                                 /* "other" */
_0xC00BD:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00CA
; 0006 041C break;
	RJMP _0xC00BC
; 0006 041D 
; 0006 041E case 0x01 :                                 /* temp */
_0xC00CA:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00D6
; 0006 041F if ( (cal_val > MAX_TMP_CAL ) ||
; 0006 0420 (cal_val < MIN_TMP_CAL ) ) {
	__GETD2S 0
	__GETD1N 0x46C73800
	CALL __CMPF12
	BREQ PC+4
	BRCS PC+3
	JMP  _0xC00CD
	__GETD1N 0x461C4000
	CALL __CMPF12
	BRSH PC+3
	JMP _0xC00CD
	RJMP _0xC00CC
_0xC00CD:
; 0006 0421 ch_stat[curr_ad_ch] |= 0x02 ;         /* Calibration fail */
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ORI  R30,2
	ST   X,R30
; 0006 0422 }
; 0006 0423 else
	RJMP _0xC00CF
_0xC00CC:
; 0006 0424 {
; 0006 0425 ch_stat[curr_ad_ch] &= ~0x02 ;        /* Calibration OK */
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ANDI R30,0xFD
	ST   X,R30
; 0006 0426 }
_0xC00CF:
; 0006 0427 if ( (cal_val > FMAX_TMP_CAL) ||(cal_val < FMIN_TMP_CAL) )
	__GETD2S 0
	__GETD1N 0x46D6D800
	CALL __CMPF12
	BREQ PC+4
	BRCS PC+3
	JMP  _0xC00D1
	__GETD1N 0x459C4000
	CALL __CMPF12
	BRSH PC+3
	JMP _0xC00D1
	RJMP _0xC00D0
_0xC00D1:
; 0006 0428 {
; 0006 0429 ch_stat[curr_ad_ch] |= 0x01 ;       /* Reading fail */
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ORI  R30,1
	ST   X,R30
; 0006 042A mes_data[curr_ad_ch] = 0.0 ;         /* ASt mark ?? */
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1N 0x0
	__PUTDP1
; 0006 042B raw_data[curr_ad_ch] = curr_sens_data ; /* sen raw raw */
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	LDS  R26,_curr_sens_data
	LDS  R27,_curr_sens_data+1
	STD  Z+0,R26
	STD  Z+1,R27
; 0006 042C if ( ad_mode & 0x80 )
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x80)
	BRNE PC+3
	JMP _0xC00D3
; 0006 042D {               /* test */
; 0006 042E ch_stat[curr_ad_ch] &= ~0x60 ;  /* no sensor */
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ANDI R30,LOW(0x9F)
	ST   X,R30
; 0006 042F }
; 0006 0430 }
_0xC00D3:
; 0006 0431 else
	RJMP _0xC00D4
_0xC00D0:
; 0006 0432 {
; 0006 0433 if ( ad_mode & 0x80 ) {
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x80)
	BRNE PC+3
	JMP _0xC00D5
; 0006 0434 ch_stat[curr_ad_ch] |= 0x24 ;   /* tmp sensor  OK*/
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ORI  R30,LOW(0x24)
	ST   X,R30
; 0006 0435 }
; 0006 0436 ch_stat[curr_ad_ch] &= ~0x01 ;  /* Reading OK */
_0xC00D5:
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ANDI R30,0xFE
	ST   X,R30
; 0006 0437 raw_data[curr_ad_ch] = (short)(((float)curr_sens_data * 1000.0
; 0006 0438 / (float)cal_data[curr_ad_ch] ) * 10.0);
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	PUSH R31
	PUSH R30
	LDS  R30,_curr_sens_data
	LDS  R31,_curr_sens_data+1
	CLR  R22
	CLR  R23
	CALL __CDF1
	__GETD2N 0x447A0000
	CALL __MULF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_cal_data)
	LDI  R27,HIGH(_cal_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	CLR  R22
	CLR  R23
	CALL __CDF1
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	__GETD2N 0x41200000
	CALL __MULF12
	CALL __CFD1U
	POP  R26
	POP  R27
	ST   X+,R30
	ST   X,R31
; 0006 0439 
; 0006 043A CalcTemp(curr_ad_ch) ;              /* calculate temperature */
	LDS  R26,_curr_ad_ch
	CALL _CalcTemp
; 0006 043B }
_0xC00D4:
; 0006 043C break;
	RJMP _0xC00BC
; 0006 043D default :
_0xC00D6:
; 0006 043E break ;
; 0006 043F }
_0xC00BC:
; 0006 0440 }
	ADIW R28,6
; 0006 0441 else
	RJMP _0xC00D7
_0xC00B9:
; 0006 0442 {
; 0006 0443 curr_ad_ch-- ;                                 // remeasure the chanell if skipped due to UART TX
	LDS  R30,_curr_ad_ch
	SUBI R30,LOW(1)
	STS  _curr_ad_ch,R30
; 0006 0444 }
_0xC00D7:
; 0006 0445 }
; 0006 0446 else
	RJMP _0xC00D8
_0xC00B8:
; 0006 0447 {                                                /* normal conv enter point */
; 0006 0448 curr_sens_data = (short)(ad_data - 32767) ;        /* use ad data */
	MOVW R30,R16
	SUBI R30,LOW(32767)
	SBCI R31,HIGH(32767)
	STS  _curr_sens_data,R30
	STS  _curr_sens_data+1,R31
; 0006 0449 tmpSwitch=(ch_stat[curr_ad_ch]>> 2) & 0x03;
	LDS  R30,_curr_ad_ch
	LDI  R31,0
	SUBI R30,LOW(-_ch_stat)
	SBCI R31,HIGH(-_ch_stat)
	LD   R30,Z
	LSR  R30
	LSR  R30
	ANDI R30,LOW(0x3)
	MOV  R19,R30
; 0006 044A //            switch ( (ch_stat[curr_ad_ch]>> 2) & 0x03 ) {
; 0006 044B switch (tmpSwitch)
	LDI  R31,0
; 0006 044C {
; 0006 044D case 0x03 :               /* pressure */
	CPI  R30,LOW(0x3)
	LDI  R26,HIGH(0x3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00DC
; 0006 044E SetMuxChannel(PRE_CAL_CH) ;         /* cal channel */
	LDI  R26,LOW(15)
	CALL _SetMuxChannel
; 0006 044F ad_mode |= 0x40 ;                           /* next cal */
	LDS  R30,_ad_mode
	ORI  R30,0x40
	STS  _ad_mode,R30
; 0006 0450 ad_settling = AD_SET_TIME ;         /* wait 67 ms */
	LDI  R30,LOW(67)
	LDI  R31,HIGH(67)
	STS  _ad_settling,R30
	STS  _ad_settling+1,R31
; 0006 0451 ad_state = WAIT_FOR_INTERRUPT ;         /* wait for cal int */
	LDI  R30,LOW(2)
	STS  _ad_state,R30
; 0006 0452 UnpackSensData(curr_ad_ch) ;            /* Unpack data */
	LDS  R26,_curr_ad_ch
	CALL _UnpackSensData
; 0006 0453 break;
	RJMP _0xC00DB
; 0006 0454 case 0x02 :                /* other */
_0xC00DC:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00DD
; 0006 0455 SetSupplyCurrent(1) ;                   /* no cal on this */
	LDI  R26,LOW(1)
	CALL _SetSupplyCurrent
; 0006 0456 SetMuxChannel(MUXCHOFF) ;
	LDI  R26,LOW(16)
	CALL _SetMuxChannel
; 0006 0457 SetSupplyChannel(SUPPCHOFF) ;
	LDI  R26,LOW(16)
	CALL _SetSupplyChannel
; 0006 0458 SetCalResistance(OFF);
	LDI  R26,LOW(0)
	CALL _SetCalResistance
; 0006 0459 ad_state = IDLE ;
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 045A raw_data[curr_ad_ch] = curr_sens_data ;
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	LDS  R26,_curr_sens_data
	LDS  R27,_curr_sens_data+1
	STD  Z+0,R26
	STD  Z+1,R27
; 0006 045B cal_data[curr_ad_ch] = 0 ;         /* do no use caldata  */
	LDS  R30,_curr_ad_ch
	LDI  R26,LOW(_cal_data)
	LDI  R27,HIGH(_cal_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	ST   X+,R30
	ST   X,R31
; 0006 045C ch_stat[curr_ad_ch] &= ~0x03 ;      /* Cal. and readings set to OK */
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ANDI R30,LOW(0xFC)
	ST   X,R30
; 0006 045D ad_timeout_cnt = 0 ;                        /* timeout off */
	LDI  R30,LOW(0)
	STS  _ad_timeout_cnt,R30
	STS  _ad_timeout_cnt+1,R30
; 0006 045E if ( ad_mode & 0x80 ) {                   /* test */
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x80)
	BRNE PC+3
	JMP _0xC00DE
; 0006 045F ch_stat[curr_ad_ch] |= 0x48 ;       /* other sensor  OK*/
	LDS  R26,_curr_ad_ch
	LDI  R27,0
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ORI  R30,LOW(0x48)
	ST   X,R30
; 0006 0460 }
; 0006 0461 CalcOther(curr_ad_ch) ;                 /* calculate "other" */
_0xC00DE:
	LDS  R26,_curr_ad_ch
	CALL _CalcOther
; 0006 0462 break;
	RJMP _0xC00DB
; 0006 0463 case 0x01 :               /* temp */
_0xC00DD:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00E0
; 0006 0464 SetMuxChannel(TMP_CAL_CH) ;         /* cal channel */
	LDI  R26,LOW(14)
	CALL _SetMuxChannel
; 0006 0465 ad_mode |= 0x40 ;                           /* next cal */
	LDS  R30,_ad_mode
	ORI  R30,0x40
	STS  _ad_mode,R30
; 0006 0466 ad_settling = AD_SET_TIME ;         /* wait 67 ms */
	LDI  R30,LOW(67)
	LDI  R31,HIGH(67)
	STS  _ad_settling,R30
	STS  _ad_settling+1,R31
; 0006 0467 ad_state = WAIT_FOR_INTERRUPT ;         /* wait for cal int */
	LDI  R30,LOW(2)
	STS  _ad_state,R30
; 0006 0468 break;
	RJMP _0xC00DB
; 0006 0469 default :
_0xC00E0:
; 0006 046A ad_state = IDLE ;                           /* Start new point */
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 046B break ;
; 0006 046C }
_0xC00DB:
; 0006 046D }
_0xC00D8:
; 0006 046E break ;
	RJMP _0xC00A7
; 0006 046F case    START_CALIBRATION :                         // calibrate the AD chip itself
_0xC00B7:
	CPI  R30,LOW(0x4)
	LDI  R26,HIGH(0x4)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00E1
; 0006 0470 Led(2, ON) ;                                        /* Led 2 on */
	LDI  R30,LOW(2)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _Led
; 0006 0471 ad_timeout_cnt = AD_TIMEOUT ;                   /* timeout ad cnv */
	LDI  R30,LOW(2000)
	LDI  R31,HIGH(2000)
	STS  _ad_timeout_cnt,R30
	STS  _ad_timeout_cnt+1,R31
; 0006 0472 ad_settling = 20 ;                              /* wait >mclock/128  */
	LDI  R30,LOW(20)
	LDI  R31,HIGH(20)
	STS  _ad_settling,R30
	STS  _ad_settling+1,R31
; 0006 0473 if ( tx_complete == TRUE ) {
	LDS  R26,_tx_complete
	CPI  R26,LOW(0x1)
	BREQ PC+3
	JMP _0xC00E2
; 0006 0474 if ( ad_mode & 0x02 ) {                       /* pressure readings */
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x2)
	BRNE PC+3
	JMP _0xC00E3
; 0006 0475 ad_gain = 3;
	LDI  R30,LOW(3)
	STS  _ad_gain,R30
; 0006 0476 } else {
	RJMP _0xC00E4
_0xC00E3:
; 0006 0477 ad_gain = 0;
	LDI  R30,LOW(0)
	STS  _ad_gain,R30
; 0006 0478 }
_0xC00E4:
; 0006 0479 ad_state = WAIT_FOR_CAL_INT ;               /* next state */
	LDI  R30,LOW(5)
	STS  _ad_state,R30
; 0006 047A spi1_master_tx_rx(ad_gain | 0x10) ;               /* Next write setup reg */
	LDS  R30,_ad_gain
	ORI  R30,0x10
	MOV  R26,R30
	CALL _spi1_master_tx_rx
; 0006 047B //spi1_master_tx_rx(0x6a) ;                     /*  Ad setup data, bipolar */
; 0006 047C spi1_master_tx_rx(0b01011000) ;   // MD1&0: 01 CLK:0,FSx:11, B/U:0 ;BUF:0 FSYNC:0
	LDI  R26,LOW(88)
	CALL _spi1_master_tx_rx
; 0006 047D 
; 0006 047E }
; 0006 047F break ;
_0xC00E2:
	RJMP _0xC00A7
; 0006 0480 case    WAIT_FOR_CAL_INT :
_0xC00E1:
	CPI  R30,LOW(0x5)
	LDI  R26,HIGH(0x5)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00E5
; 0006 0481 break ;
	RJMP _0xC00A7
; 0006 0482 case    CAL_COMPLETE :
_0xC00E5:
	CPI  R30,LOW(0x6)
	LDI  R26,HIGH(0x6)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00E6
; 0006 0483 ad_timeout_cnt = 0 ;                                /* timeout off */
	LDI  R30,LOW(0)
	STS  _ad_timeout_cnt,R30
	STS  _ad_timeout_cnt+1,R30
; 0006 0484 curr_ad_ch -= 1 ;                                   /* To start with ch 0 !! */
	LDS  R30,_curr_ad_ch
	SUBI R30,LOW(1)
	STS  _curr_ad_ch,R30
; 0006 0485 ad_state = IDLE ;
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 0486 Led(2, OFF) ;                                       /* Led 2 off */
	LDI  R30,LOW(2)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _Led
; 0006 0487 break ;
	RJMP _0xC00A7
; 0006 0488 case    IDLE :
_0xC00E6:
	CPI  R30,LOW(0x7)
	LDI  R26,HIGH(0x7)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC00E8
; 0006 0489 break ;
	RJMP _0xC00A7
; 0006 048A default :
_0xC00E8:
; 0006 048B ad_state = IDLE ;
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0006 048C break ;
; 0006 048D }
_0xC00A7:
; 0006 048E }
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
;void CalcPress(signed char ch)
; 0006 0496 {
_CalcPress:
; .FSTART _CalcPress
; 0006 0497 
; 0006 0498 float temp_data ;
; 0006 0499 
; 0006 049A Led(2, ON)  ;                               /* Led 2 on */
	SBIW R28,4
	ST   -Y,R17
	MOV  R17,R26
;	ch -> R17
;	temp_data -> Y+1
	LDI  R30,LOW(2)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _Led
; 0006 049B 
; 0006 049C if ( (sens_data[0]>0) && (raw_data[ch] < sens_data[0]) ) {
	LDS  R26,_sens_data
	LDS  R27,_sens_data+1
	__CPW02
	BRLO PC+3
	JMP _0xC00EA
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	MOVW R26,R30
	LDS  R30,_sens_data
	LDS  R31,_sens_data+1
	CP   R26,R30
	CPC  R27,R31
	BRLO PC+3
	JMP _0xC00EA
	RJMP _0xC00EB
_0xC00EA:
	RJMP _0xC00E9
_0xC00EB:
; 0006 049D temp_data = CalcPercent((sens_data[1]-sens_data[0]), sens_data[0],
; 0006 049E raw_data[ch], 0.0) ;
	__GETW2MN _sens_data,2
	LDS  R30,_sens_data
	LDS  R31,_sens_data+1
	SUB  R26,R30
	SBC  R27,R31
	ST   -Y,R27
	ST   -Y,R26
	ST   -Y,R31
	ST   -Y,R30
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	ST   -Y,R31
	ST   -Y,R30
	__GETD2N 0x0
	CALL _CalcPercent
	__PUTD1S 1
; 0006 049F temp_data *= 40.0 ;             /* caluclate %, using 0-40% cal data*/
	__GETD2S 1
	__GETD1N 0x42200000
	CALL __MULF12
	__PUTD1S 1
; 0006 04A0 
; 0006 04A1 }
; 0006 04A2 else if ( raw_data[ch] <  sens_data[1] ) {
	RJMP _0xC00EC
_0xC00E9:
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	MOVW R26,R30
	__GETW1MN _sens_data,2
	CP   R26,R30
	CPC  R27,R31
	BRLO PC+3
	JMP _0xC00ED
; 0006 04A3 temp_data = CalcPercent((sens_data[1]-sens_data[0]), sens_data[0],
; 0006 04A4 raw_data[ch], (float)sens_nl1) ;
	__GETW2MN _sens_data,2
	LDS  R30,_sens_data
	LDS  R31,_sens_data+1
	SUB  R26,R30
	SBC  R27,R31
	ST   -Y,R27
	ST   -Y,R26
	ST   -Y,R31
	ST   -Y,R30
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	ST   -Y,R31
	ST   -Y,R30
	LDS  R30,_sens_nl1
	CALL __CBD1
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	CALL _CalcPercent
	__PUTD1S 1
; 0006 04A5 temp_data *= 40.0 ;             /* caluclate % */
	__GETD2S 1
	__GETD1N 0x42200000
	CALL __MULF12
	__PUTD1S 1
; 0006 04A6 
; 0006 04A7 }
; 0006 04A8 else if ( raw_data[ch] < sens_data[2] ) {
	RJMP _0xC00EE
_0xC00ED:
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	MOVW R26,R30
	__GETW1MN _sens_data,4
	CP   R26,R30
	CPC  R27,R31
	BRLO PC+3
	JMP _0xC00EF
; 0006 04A9 temp_data = CalcPercent((sens_data[2]-sens_data[1]), sens_data[1],
; 0006 04AA raw_data[ch], (float)(sens_nl2 / 3)) ;
	__GETW2MN _sens_data,4
	__GETW1MN _sens_data,2
	SUB  R26,R30
	SBC  R27,R31
	ST   -Y,R27
	ST   -Y,R26
	ST   -Y,R31
	ST   -Y,R30
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	ST   -Y,R31
	ST   -Y,R30
	LDS  R26,_sens_nl2
	LDI  R27,0
	SBRC R26,7
	SER  R27
	LDI  R30,LOW(3)
	LDI  R31,HIGH(3)
	CALL __DIVW21
	__CWD1
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	CALL _CalcPercent
	__PUTD1S 1
; 0006 04AB temp_data = temp_data*(60.0 - 40.0)+40.0 ;              /* caluclate % */
	__GETD2S 1
	__GETD1N 0x41A00000
	CALL __MULF12
	__GETD2N 0x42200000
	CALL __ADDF12
	__PUTD1S 1
; 0006 04AC 
; 0006 04AD }
; 0006 04AE else if ( raw_data[ch] < sens_data[3] ) {
	RJMP _0xC00F0
_0xC00EF:
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	MOVW R26,R30
	__GETW1MN _sens_data,6
	CP   R26,R30
	CPC  R27,R31
	BRLO PC+3
	JMP _0xC00F1
; 0006 04AF temp_data = CalcPercent((sens_data[3]-sens_data[2]), sens_data[2],
; 0006 04B0 raw_data[ch], (float)sens_nl2 ) ;
	__GETW2MN _sens_data,6
	__GETW1MN _sens_data,4
	SUB  R26,R30
	SBC  R27,R31
	ST   -Y,R27
	ST   -Y,R26
	ST   -Y,R31
	ST   -Y,R30
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	ST   -Y,R31
	ST   -Y,R30
	LDS  R30,_sens_nl2
	CALL __CBD1
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	CALL _CalcPercent
	__PUTD1S 1
; 0006 04B1 temp_data = temp_data*(100.0 - 60.0)+60.0 ;             /* caluclate % */
	__GETD2S 1
	__GETD1N 0x42200000
	CALL __MULF12
	__GETD2N 0x42700000
	CALL __ADDF12
	__PUTD1S 1
; 0006 04B2 
; 0006 04B3 }
; 0006 04B4 else {
	RJMP _0xC00F2
_0xC00F1:
; 0006 04B5 temp_data = CalcPercent((sens_data[3]-sens_data[2]), sens_data[2],
; 0006 04B6 raw_data[ch], 0.0) ;
	__GETW2MN _sens_data,6
	__GETW1MN _sens_data,4
	SUB  R26,R30
	SBC  R27,R31
	ST   -Y,R27
	ST   -Y,R26
	ST   -Y,R31
	ST   -Y,R30
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	ST   -Y,R31
	ST   -Y,R30
	__GETD2N 0x0
	CALL _CalcPercent
	__PUTD1S 1
; 0006 04B7 temp_data = temp_data*(100.0 - 60.0)+60.0 ;             /* caluclate % */
	__GETD2S 1
	__GETD1N 0x42200000
	CALL __MULF12
	__GETD2N 0x42700000
	CALL __ADDF12
	__PUTD1S 1
; 0006 04B8 }
_0xC00F2:
_0xC00F0:
_0xC00EE:
_0xC00EC:
; 0006 04B9 
; 0006 04BA temp_data *= ((((float)packed_data[ch >> 1][6]/10.0) -
; 0006 04BB (float) packed_data[ch >> 1][5] / 100.0) /100.0 ) * 10.197162;
	MOV  R30,R17
	LDI  R31,0
	SBRC R30,7
	SER  R31
	ASR  R31
	ROR  R30
	LDI  R26,LOW(40)
	LDI  R27,HIGH(40)
	CALL __MULW12U
	__ADDW1MN _packed_data,6
	LD   R30,Z
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x41200000
	CALL __DIVF21
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	MOV  R30,R17
	LDI  R31,0
	SBRC R30,7
	SER  R31
	ASR  R31
	ROR  R30
	LDI  R26,LOW(40)
	LDI  R27,HIGH(40)
	CALL __MULW12U
	__ADDW1MN _packed_data,5
	LD   R30,Z
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x42C80000
	CALL __DIVF21
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __SWAPD12
	CALL __SUBF12
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x42C80000
	CALL __DIVF21
	__GETD2N 0x41232793
	CALL __MULF12
	__GETD2S 1
	CALL __MULF12
	__PUTD1S 1
; 0006 04BC temp_data -= ((float) offset[ch] / 1000.0) ;
	MOV  R30,R17
	LDI  R26,LOW(_offset)
	LDI  R27,HIGH(_offset)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	CLR  R22
	CLR  R23
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x447A0000
	CALL __DIVF21
	__GETD2S 1
	CALL __SWAPD12
	CALL __SUBF12
	__PUTD1S 1
; 0006 04BD temp_data *=  gain[ch] ;
	MOV  R30,R17
	LDI  R26,LOW(_gain)
	LDI  R27,HIGH(_gain)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	__GETD2S 1
	CALL __MULF12
	__PUTD1S 1
; 0006 04BE temp_data += ((float) packed_data[ch >> 1][5] / 100.0)  * 10.197162 ;
	MOV  R30,R17
	LDI  R31,0
	SBRC R30,7
	SER  R31
	ASR  R31
	ROR  R30
	LDI  R26,LOW(40)
	LDI  R27,HIGH(40)
	CALL __MULW12U
	__ADDW1MN _packed_data,5
	LD   R30,Z
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x42C80000
	CALL __DIVF21
	__GETD2N 0x41232793
	CALL __MULF12
	__GETD2S 1
	CALL __ADDF12
	__PUTD1S 1
; 0006 04BF mes_data[ch] += (temp_data - mes_data[ch])/ ((float)p_filter + 1.0) ;
	MOV  R30,R17
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R30,R26
	ADC  R31,R27
	PUSH R31
	PUSH R30
	MOVW R26,R30
	__GETD1P_INC
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	MOV  R30,R17
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	__GETD2S 1
	CALL __SWAPD12
	CALL __SUBF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	LDS  R30,_p_filter
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	__GETD2N 0x3F800000
	CALL __ADDF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __ADDF12
	POP  R26
	POP  R27
	__PUTDP1
; 0006 04C0 if ( (mes_data[ch] > 500.0) || (mes_data[ch] < -50.0) ) {
	MOV  R30,R17
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x43FA0000
	CALL __CMPF12
	BREQ PC+4
	BRCS PC+3
	JMP  _0xC00F4
	MOV  R30,R17
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0xC2480000
	CALL __CMPF12
	BRSH PC+3
	JMP _0xC00F4
	RJMP _0xC00F3
_0xC00F4:
; 0006 04C1 mes_data[ch] = 0.0 ;
	MOV  R30,R17
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1N 0x0
	__PUTDP1
; 0006 04C2 }
; 0006 04C3 Led(2, OFF) ;                                   /* Led 2 off */
_0xC00F3:
	LDI  R30,LOW(2)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _Led
; 0006 04C4 
; 0006 04C5 }
	LDD  R17,Y+0
	ADIW R28,5
	RET
; .FEND
; 0006 04CD float nl)
;float nl)
; 0006 04CE {
_CalcPercent:
; .FSTART _CalcPercent
; 0006 04CF 
; 0006 04D0 float x, yy, fspan, range ;
; 0006 04D1 
; 0006 04D2 range = (float)raw_data - (float)low_span ;
	CALL __PUTPARD2
	SBIW R28,16
	CALL __SAVELOCR6
	__GETWRS 16,17,26
	__GETWRS 18,19,28
	__GETWRS 20,21,30
;	span -> R20,R21
;	low_span -> R18,R19
;	raw_data -> R16,R17
;	nl -> Y+22
;	x -> Y+18
;	yy -> Y+14
;	fspan -> Y+10
;	range -> Y+6
	MOVW R30,R16
	CLR  R22
	CLR  R23
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	MOVW R30,R18
	CLR  R22
	CLR  R23
	CALL __CDF1
	CALL __SWAPD12
	CALL __SUBF12
	__PUTD1S 6
; 0006 04D3 fspan = (float)span ;
	MOVW R30,R20
	CLR  R22
	CLR  R23
	CALL __CDF1
	__PUTD1S 10
; 0006 04D4 
; 0006 04D5 x = range/fspan ;
	__GETD2S 6
	CALL __DIVF21
	__PUTD1S 18
; 0006 04D6 yy = (fspan - fspan*x)*fspan*x*nl/(fspan * fspan / 4.0) ;
	__GETD2S 10
	CALL __MULF12
	__GETD2S 10
	CALL __SWAPD12
	CALL __SUBF12
	__GETD2S 10
	CALL __MULF12
	__GETD2S 18
	CALL __MULF12
	__GETD2S 22
	CALL __MULF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	__GETD1S 10
	__GETD2S 10
	CALL __MULF12
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x40800000
	CALL __DIVF21
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	__PUTD1S 14
; 0006 04D7 return(range - yy)/fspan ;
	__GETD2S 14
	__GETD1S 6
	CALL __SUBF12
	MOVW R26,R30
	MOVW R24,R22
	__GETD1S 10
	CALL __DIVF21
	CALL __LOADLOCR6
	ADIW R28,32
	RET
; 0006 04D8 
; 0006 04D9 }
; .FEND
;float GetTempFromR(float R)
; 0006 04E1 {     float Tmp;
_GetTempFromR:
; .FSTART _GetTempFromR
; 0006 04E2 const float C0 = -245.19;
; 0006 04E3 const float C1 = 2.5293;
; 0006 04E4 const float C2 = -0.066046;
; 0006 04E5 const float C3 = 4.0422e-3;
; 0006 04E6 const float C4 = -2.0697e-6;
; 0006 04E7 const float C5 = -0.025422;
; 0006 04E8 const float C6 = 1.6883e-3;
; 0006 04E9 const float C7 = -1.3601e-6;
; 0006 04EA Tmp = C0 + R*(C1+R*(C2+R*(C3+C4*R)))/(1+R*(C5+R*(C6+C7*R)));
	CALL __PUTPARD2
	SBIW R28,36
	LDI  R24,32
	__GETWRN 22,23,0
	LDI  R30,LOW(_0xC00F6*2)
	LDI  R31,HIGH(_0xC00F6*2)
	CALL __INITLOCB
;	R -> Y+36
;	Tmp -> Y+32
;	C0 -> Y+28
;	C1 -> Y+24
;	C2 -> Y+20
;	C3 -> Y+16
;	C4 -> Y+12
;	C5 -> Y+8
;	C6 -> Y+4
;	C7 -> Y+0
	__GETD1S 36
	__GETD2N 0xB60AE52D
	CALL __MULF12
	__GETD2N 0x3B84746E
	CALL __ADDF12
	__GETD2S 36
	CALL __MULF12
	__GETD2N 0xBD874320
	CALL __ADDF12
	__GETD2S 36
	CALL __MULF12
	__GETD2N 0x4021E00D
	CALL __ADDF12
	__GETD2S 36
	CALL __MULF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	__GETD1S 36
	__GETD2N 0xB5B68CAE
	CALL __MULF12
	__GETD2N 0x3ADD49F3
	CALL __ADDF12
	__GETD2S 36
	CALL __MULF12
	__GETD2N 0xBCD041CC
	CALL __ADDF12
	__GETD2S 36
	CALL __MULF12
	__GETD2N 0x3F800000
	CALL __ADDF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	__GETD2N 0xC37530A4
	CALL __ADDF12
	__PUTD1S 32
; 0006 04EB return Tmp;
	ADIW R28,40
	RET
; 0006 04EC }
; .FEND
;void CalcTemp(signed char ch)
; 0006 04EF {   float temp_data;
_CalcTemp:
; .FSTART _CalcTemp
; 0006 04F0 
; 0006 04F1 
; 0006 04F2 float resist = (float)raw_data[ch] ;
; 0006 04F3 resist /= 10.0 ;
	ST   -Y,R26
	SBIW R28,8
;	ch -> Y+8
;	temp_data -> Y+4
;	resist -> Y+0
	LDD  R30,Y+8
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	CLR  R22
	CLR  R23
	CALL __CDF1
	__PUTD1S 0
	__GETD2S 0
	__GETD1N 0x41200000
	CALL __DIVF21
	__PUTD1S 0
; 0006 04F4 if ( resist > 500.0 ) {                              /* Pt 1000 ?*/
	__GETD2S 0
	__GETD1N 0x43FA0000
	CALL __CMPF12
	BREQ PC+2
	BRCC PC+3
	JMP  _0xC00F7
; 0006 04F5 resist /= 10.0 ;                                /* Yes */
	__GETD1N 0x41200000
	CALL __DIVF21
	__PUTD1S 0
; 0006 04F6 }
; 0006 04F7 temp_data = GetTempFromR(resist);
_0xC00F7:
	__GETD2S 0
	CALL _GetTempFromR
	__PUTD1S 4
; 0006 04F8 /*
; 0006 04F9 float temp_resist = resist - 100.0 ;
; 0006 04FA temp_data = (temp_resist / 0.390802) +
; 0006 04FB ((temp_resist * temp_resist)/1000.0) ;
; 0006 04FC */
; 0006 04FD temp_data -= (float) offset[ch] / 10.0 ;
	LDD  R30,Y+8
	LDI  R26,LOW(_offset)
	LDI  R27,HIGH(_offset)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	CLR  R22
	CLR  R23
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x41200000
	CALL __DIVF21
	__GETD2S 4
	CALL __SWAPD12
	CALL __SUBF12
	__PUTD1S 4
; 0006 04FE temp_data *= gain[ch] ;
	LDD  R30,Y+8
	LDI  R26,LOW(_gain)
	LDI  R27,HIGH(_gain)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	__GETD2S 4
	CALL __MULF12
	__PUTD1S 4
; 0006 04FF mes_data[ch] += (temp_data - mes_data[ch])/ ((float)t_filter + 1.0) ;
	LDD  R30,Y+8
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R30,R26
	ADC  R31,R27
	PUSH R31
	PUSH R30
	MOVW R26,R30
	__GETD1P_INC
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	LDD  R30,Y+8
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	__GETD2S 4
	CALL __SWAPD12
	CALL __SUBF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	LDS  R30,_t_filter
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	__GETD2N 0x3F800000
	CALL __ADDF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __ADDF12
	POP  R26
	POP  R27
	__PUTDP1
; 0006 0500 }
	ADIW R28,9
	RET
; .FEND
;void CalcOther(signed char ch)
; 0006 0508 {
_CalcOther:
; .FSTART _CalcOther
; 0006 0509 
; 0006 050A float temp_data ;
; 0006 050B 
; 0006 050C temp_data = (float)(raw_data[ch]) * 2.5 / 32767.0 ;
	SBIW R28,4
	ST   -Y,R17
	MOV  R17,R26
;	ch -> R17
;	temp_data -> Y+1
	MOV  R30,R17
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	CLR  R22
	CLR  R23
	CALL __CDF1
	__GETD2N 0x40200000
	CALL __MULF12
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x46FFFE00
	CALL __DIVF21
	__PUTD1S 1
; 0006 050D /*input * 2.5 volt / +-15 bit*/
; 0006 050E temp_data -= (float) offset[ch]/ 10000.0 ;
	MOV  R30,R17
	LDI  R26,LOW(_offset)
	LDI  R27,HIGH(_offset)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	CLR  R22
	CLR  R23
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x461C4000
	CALL __DIVF21
	__GETD2S 1
	CALL __SWAPD12
	CALL __SUBF12
	__PUTD1S 1
; 0006 050F temp_data *= gain[ch] ;
	MOV  R30,R17
	LDI  R26,LOW(_gain)
	LDI  R27,HIGH(_gain)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	__GETD2S 1
	CALL __MULF12
	__PUTD1S 1
; 0006 0510 mes_data[ch] += (temp_data - mes_data[ch])/ ((float)o_filter + 1.0) ;
	MOV  R30,R17
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R30,R26
	ADC  R31,R27
	PUSH R31
	PUSH R30
	MOVW R26,R30
	__GETD1P_INC
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	MOV  R30,R17
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	__GETD2S 1
	CALL __SWAPD12
	CALL __SUBF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	LDS  R30,_o_filter
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	__GETD2N 0x3F800000
	CALL __ADDF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __DIVF21
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __ADDF12
	POP  R26
	POP  R27
	__PUTDP1
; 0006 0511 
; 0006 0512 }
	LDD  R17,Y+0
	ADIW R28,5
	RET
; .FEND
;void UnpackSensData(signed char ch)
; 0006 051A {
_UnpackSensData:
; .FSTART _UnpackSensData
; 0006 051B unsigned int data_low;
; 0006 051C unsigned int data_high;
; 0006 051D 
; 0006 051E short knst, d_knst, g1, g2, g3 ;
; 0006 051F float temp_data ;
; 0006 0520 unsigned char  temp_byte ;
; 0006 0521 signed char c_ch ;
; 0006 0522 
; 0006 0523 temp_byte = FindTemp(ch);
	ST   -Y,R26
	SBIW R28,14
	CALL __SAVELOCR6
;	ch -> Y+20
;	data_low -> R16,R17
;	data_high -> R18,R19
;	knst -> R20,R21
;	d_knst -> Y+18
;	g1 -> Y+16
;	g2 -> Y+14
;	g3 -> Y+12
;	temp_data -> Y+8
;	temp_byte -> Y+7
;	c_ch -> Y+6
	LDD  R26,Y+20
	CALL _FindTemp
	STD  Y+7,R30
; 0006 0524 if ( temp_byte >= NOIOCH ) {                 /* no temp. found */
	LDD  R26,Y+7
	CPI  R26,LOW(0xE)
	BRSH PC+3
	JMP _0xC00F8
; 0006 0525 temp_data = 0 ;                                 /* 25. 0 - 25.0  */
	LDI  R30,LOW(0)
	__CLRD1S 8
; 0006 0526 } else {
	RJMP _0xC00F9
_0xC00F8:
; 0006 0527 temp_data = mes_data[temp_byte] - 25.0 ;
	LDD  R30,Y+7
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x41C80000
	CALL __SWAPD12
	CALL __SUBF12
	__PUTD1S 8
; 0006 0528 }
_0xC00F9:
; 0006 0529 temp_data /= 100.0 ;              /* use 1/100 deg C in calc. */
	__GETD2S 8
	__GETD1N 0x42C80000
	CALL __DIVF21
	__PUTD1S 8
; 0006 052A 
; 0006 052B c_ch = ch >>1 ;                         /* start calculate data for 0 % FRO */
	LDD  R30,Y+20
	ASR  R30
	STD  Y+6,R30
; 0006 052C if ( (eep_type[c_ch] & 0x01) || (eep_type[c_ch] & 0x10) ) { /* OK data */
	LDI  R31,0
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	LD   R30,Z
	ANDI R30,LOW(0x1)
	BREQ PC+3
	JMP _0xC00FB
	LDD  R30,Y+6
	LDI  R31,0
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	LD   R30,Z
	ANDI R30,LOW(0x10)
	BREQ PC+3
	JMP _0xC00FB
	RJMP _0xC00FA
_0xC00FB:
; 0006 052D knst =  ((short) packed_data[c_ch][8] +
; 0006 052E packed_data[c_ch][9] * 256) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,8
	LD   R22,Z
	CLR  R23
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,9
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(256)
	LDI  R31,HIGH(256)
	CALL __MULW12
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	MOVW R20,R30
; 0006 052F 
; 0006 0530 if ( knst & 0x1000 ) {                /* negative */
	SBRS R21,4
	RJMP _0xC00FD
; 0006 0531 knst |= 0xe000 ;
	ORI  R21,HIGH(57344)
; 0006 0532 }
; 0006 0533 g1 =  ((short) ((packed_data[c_ch][9] >> 5) & 0x07) +
_0xC00FD:
; 0006 0534 (packed_data[c_ch][10] * 8) +
; 0006 0535 ((packed_data[c_ch][11] & 0x03) * 2048)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,9
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(5)
	CALL __ASRW12
	ANDI R30,LOW(0x7)
	ANDI R31,HIGH(0x7)
	MOVW R22,R30
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,10
	LD   R26,Z
	LDI  R30,LOW(8)
	MUL  R30,R26
	MOVW R30,R0
	__ADDWRR 22,23,30,31
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,11
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x3)
	ANDI R31,HIGH(0x3)
	LSL  R30
	LSL  R30
	LSL  R30
	MOV  R31,R30
	LDI  R30,0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+16,R30
	STD  Y+16+1,R31
; 0006 0536 if ( g1 & 0x1000 ) {                /* negative */
	LDD  R30,Y+17
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC00FE
; 0006 0537 g1 |= 0xe000 ;
	LDD  R30,Y+17
	ORI  R30,LOW(0xE0)
	STD  Y+17,R30
; 0006 0538 }
; 0006 0539 g2 =  ((short) ((packed_data[c_ch][11] >> 2) & 0x3f) +
_0xC00FE:
; 0006 053A ((packed_data[c_ch][12] & 0x7f)* 64 )) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,11
	LD   R30,Z
	LDI  R31,0
	CALL __ASRW2
	ANDI R30,LOW(0x3F)
	ANDI R31,HIGH(0x3F)
	MOVW R22,R30
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,12
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x7F)
	ANDI R31,HIGH(0x7F)
	CALL __LSLW2
	CALL __LSLW4
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+14,R30
	STD  Y+14+1,R31
; 0006 053B if ( g2 & 0x1000 ) {                /* negative */
	LDD  R30,Y+15
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC00FF
; 0006 053C g2 |= 0xe000 ;
	LDD  R30,Y+15
	ORI  R30,LOW(0xE0)
	STD  Y+15,R30
; 0006 053D }
; 0006 053E g3 =  ((short) ((packed_data[c_ch][12] >> 7) & 0x01) +
_0xC00FF:
; 0006 053F (packed_data[c_ch][13] * 2) +
; 0006 0540 ((packed_data[c_ch][14] & 0x0f) * 512)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,12
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(7)
	CALL __ASRW12
	ANDI R30,LOW(0x1)
	ANDI R31,HIGH(0x1)
	MOVW R22,R30
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,13
	LD   R26,Z
	LDI  R30,LOW(2)
	MUL  R30,R26
	MOVW R30,R0
	__ADDWRR 22,23,30,31
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,14
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0xF)
	ANDI R31,HIGH(0xF)
	LSL  R30
	MOV  R31,R30
	LDI  R30,0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+12,R30
	STD  Y+12+1,R31
; 0006 0541 if ( g3 & 0x1000 ) {                /* negative */
	LDD  R30,Y+13
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0100
; 0006 0542 g3 |= 0xe000 ;
	LDD  R30,Y+13
	ORI  R30,LOW(0xE0)
	STD  Y+13,R30
; 0006 0543 }
; 0006 0544 sens_data[0] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
_0xC0100:
	__MULBNWRU 20,21,2
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	__GETD2S 16
	CALL _CalcSensData
	STS  _sens_data,R30
	STS  _sens_data+1,R31
; 0006 0545 /* sens value 0%FRO @ temp */
; 0006 0546 
; 0006 0547 /* start calculate data for 40 % FRO */
; 0006 0548 d_knst =  ((short) ((packed_data[c_ch][14] >> 4) & 0x0f) +
; 0006 0549 (packed_data[c_ch][15] * 16) +
; 0006 054A ((packed_data[c_ch][16] & 0x01) * 4096))& 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,14
	LD   R30,Z
	LDI  R31,0
	CALL __ASRW4
	ANDI R30,LOW(0xF)
	ANDI R31,HIGH(0xF)
	MOVW R22,R30
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,15
	LD   R26,Z
	LDI  R30,LOW(16)
	MUL  R30,R26
	MOVW R30,R0
	__ADDWRR 22,23,30,31
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,16
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x1)
	ANDI R31,HIGH(0x1)
	SWAP R30
	ANDI R30,0xF0
	MOV  R31,R30
	LDI  R30,0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+18,R30
	STD  Y+18+1,R31
; 0006 054B 
; 0006 054C g1 =  ((short) ((packed_data[c_ch][16] >> 1) & 0x7f) +
; 0006 054D ((packed_data[c_ch][17] & 0x3f) * 128)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,16
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	ANDI R30,LOW(0x7F)
	ANDI R31,HIGH(0x7F)
	MOVW R22,R30
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,17
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x3F)
	ANDI R31,HIGH(0x3F)
	CALL __LSLW3
	CALL __LSLW4
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+16,R30
	STD  Y+16+1,R31
; 0006 054E if ( g1 & 0x1000 ) {                /* negative */
	LDD  R30,Y+17
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0101
; 0006 054F g1 |= 0xe000 ;
	LDD  R30,Y+17
	ORI  R30,LOW(0xE0)
	STD  Y+17,R30
; 0006 0550 }
; 0006 0551 g2 =  ((short) ((packed_data[c_ch][17] >> 6) & 0x03) +
_0xC0101:
; 0006 0552 (packed_data[c_ch][18] * 4) +
; 0006 0553 ((packed_data[c_ch][19]& 0x07) * 1024)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,17
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(6)
	CALL __ASRW12
	ANDI R30,LOW(0x3)
	ANDI R31,HIGH(0x3)
	MOVW R22,R30
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,18
	LD   R26,Z
	LDI  R30,LOW(4)
	MUL  R30,R26
	MOVW R30,R0
	__ADDWRR 22,23,30,31
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,19
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x7)
	ANDI R31,HIGH(0x7)
	LSL  R30
	LSL  R30
	MOV  R31,R30
	LDI  R30,0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+14,R30
	STD  Y+14+1,R31
; 0006 0554 if ( g2 & 0x1000 ) {                /* negative */
	LDD  R30,Y+15
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0102
; 0006 0555 g2 |= 0xe000 ;
	LDD  R30,Y+15
	ORI  R30,LOW(0xE0)
	STD  Y+15,R30
; 0006 0556 }
; 0006 0557 g3 =  ((short) ((packed_data[c_ch][19] >> 3) & 0x1f) +
_0xC0102:
; 0006 0558 (packed_data[c_ch][20] * 32)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,19
	LD   R30,Z
	LDI  R31,0
	CALL __ASRW3
	ANDI R30,LOW(0x1F)
	ANDI R31,HIGH(0x1F)
	MOVW R22,R30
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,20
	LD   R26,Z
	LDI  R30,LOW(32)
	MUL  R30,R26
	MOVW R30,R0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+12,R30
	STD  Y+12+1,R31
; 0006 0559 if ( g3 & 0x1000 ) {                /* negative */
	LDD  R30,Y+13
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0103
; 0006 055A g3 |= 0xe000 ;
	LDD  R30,Y+13
	ORI  R30,LOW(0xE0)
	STD  Y+13,R30
; 0006 055B }
; 0006 055C knst += d_knst;                                 /* remember new value */
_0xC0103:
	LDD  R30,Y+18
	LDD  R31,Y+18+1
	__ADDWRR 20,21,30,31
; 0006 055D sens_data[1] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
	__MULBNWRU 20,21,2
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	__GETD2S 16
	CALL _CalcSensData
	__PUTW1MN _sens_data,2
; 0006 055E /* sens value 40%FRO @ temp */
; 0006 055F 
; 0006 0560 /* start calculate data for 60 % FRO */
; 0006 0561 d_knst =  ((short) packed_data[c_ch][21] +
; 0006 0562 packed_data[c_ch][22] * 256) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,21
	LD   R22,Z
	CLR  R23
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,22
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(256)
	LDI  R31,HIGH(256)
	CALL __MULW12
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+18,R30
	STD  Y+18+1,R31
; 0006 0563 
; 0006 0564 g1 =  ((short) ((packed_data[c_ch][22] >> 5) & 0x07) +
; 0006 0565 (packed_data[c_ch][23] * 8) +
; 0006 0566 ((packed_data[c_ch][24] & 0x03) * 2048)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,22
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(5)
	CALL __ASRW12
	ANDI R30,LOW(0x7)
	ANDI R31,HIGH(0x7)
	MOVW R22,R30
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,23
	LD   R26,Z
	LDI  R30,LOW(8)
	MUL  R30,R26
	MOVW R30,R0
	__ADDWRR 22,23,30,31
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,24
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x3)
	ANDI R31,HIGH(0x3)
	LSL  R30
	LSL  R30
	LSL  R30
	MOV  R31,R30
	LDI  R30,0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+16,R30
	STD  Y+16+1,R31
; 0006 0567 if ( g1 & 0x1000 ) {                /* negative */
	LDD  R30,Y+17
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0104
; 0006 0568 g1 |= 0xe000 ;
	LDD  R30,Y+17
	ORI  R30,LOW(0xE0)
	STD  Y+17,R30
; 0006 0569 }
; 0006 056A g2 =  ((short) ((packed_data[c_ch][24] >> 2) & 0x3f) +
_0xC0104:
; 0006 056B ((packed_data[c_ch][25] & 0x7f)* 64 )) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,24
	LD   R30,Z
	LDI  R31,0
	CALL __ASRW2
	ANDI R30,LOW(0x3F)
	ANDI R31,HIGH(0x3F)
	MOVW R22,R30
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,25
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x7F)
	ANDI R31,HIGH(0x7F)
	CALL __LSLW2
	CALL __LSLW4
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+14,R30
	STD  Y+14+1,R31
; 0006 056C if ( g2 & 0x1000 ) {                /* negative */
	LDD  R30,Y+15
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0105
; 0006 056D g2 |= 0xe000 ;
	LDD  R30,Y+15
	ORI  R30,LOW(0xE0)
	STD  Y+15,R30
; 0006 056E }
; 0006 056F g3 =  ((short)((packed_data[c_ch][25] >> 7) & 0x01) +
_0xC0105:
; 0006 0570 (packed_data[c_ch][26] * 2) +
; 0006 0571 ((packed_data[c_ch][27] & 0x0f) * 512)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,25
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(7)
	CALL __ASRW12
	ANDI R30,LOW(0x1)
	ANDI R31,HIGH(0x1)
	MOVW R22,R30
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,26
	LD   R26,Z
	LDI  R30,LOW(2)
	MUL  R30,R26
	MOVW R30,R0
	__ADDWRR 22,23,30,31
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,27
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0xF)
	ANDI R31,HIGH(0xF)
	LSL  R30
	MOV  R31,R30
	LDI  R30,0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+12,R30
	STD  Y+12+1,R31
; 0006 0572 if ( g3 & 0x1000 ) {                /* negative */
	LDD  R30,Y+13
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0106
; 0006 0573 g3 |= 0xe000 ;
	LDD  R30,Y+13
	ORI  R30,LOW(0xE0)
	STD  Y+13,R30
; 0006 0574 }
; 0006 0575 knst += d_knst;                                 /* remember new value */
_0xC0106:
	LDD  R30,Y+18
	LDD  R31,Y+18+1
	__ADDWRR 20,21,30,31
; 0006 0576 sens_data[2] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
	__MULBNWRU 20,21,2
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	__GETD2S 16
	CALL _CalcSensData
	__PUTW1MN _sens_data,4
; 0006 0577 /* sens value 60%FRO @ temp */
; 0006 0578 
; 0006 0579 /* start calculate data for 100 % FRO */
; 0006 057A d_knst = ((short)((packed_data[c_ch][27] >> 4) & 0x0f) +
; 0006 057B (packed_data[c_ch][28] * 16) +
; 0006 057C ((packed_data[c_ch][29] & 0x01)) * 4096)& 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,27
	LD   R30,Z
	LDI  R31,0
	CALL __ASRW4
	ANDI R30,LOW(0xF)
	ANDI R31,HIGH(0xF)
	MOVW R22,R30
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,28
	LD   R26,Z
	LDI  R30,LOW(16)
	MUL  R30,R26
	MOVW R30,R0
	__ADDWRR 22,23,30,31
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,29
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x1)
	ANDI R31,HIGH(0x1)
	SWAP R30
	ANDI R30,0xF0
	MOV  R31,R30
	LDI  R30,0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+18,R30
	STD  Y+18+1,R31
; 0006 057D 
; 0006 057E g1 =  ((short) ((packed_data[c_ch][29] >> 1) & 0x7f) +
; 0006 057F ((packed_data[c_ch][30] & 0x3f) * 128)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,29
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	ANDI R30,LOW(0x7F)
	ANDI R31,HIGH(0x7F)
	MOVW R22,R30
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,30
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x3F)
	ANDI R31,HIGH(0x3F)
	CALL __LSLW3
	CALL __LSLW4
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+16,R30
	STD  Y+16+1,R31
; 0006 0580 if ( g1 & 0x1000 ) {                /* negative */
	LDD  R30,Y+17
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0107
; 0006 0581 g1 |= 0xe000 ;
	LDD  R30,Y+17
	ORI  R30,LOW(0xE0)
	STD  Y+17,R30
; 0006 0582 }
; 0006 0583 g2 =  ((short) ((packed_data[c_ch][30] >> 6) & 0x03) +
_0xC0107:
; 0006 0584 (packed_data[c_ch][31] * 4) +
; 0006 0585 ((packed_data[c_ch][32]& 0x07) * 1024)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,30
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(6)
	CALL __ASRW12
	ANDI R30,LOW(0x3)
	ANDI R31,HIGH(0x3)
	MOVW R22,R30
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,31
	LD   R26,Z
	LDI  R30,LOW(4)
	MUL  R30,R26
	MOVW R30,R0
	__ADDWRR 22,23,30,31
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,32
	LD   R30,Z
	LDI  R31,0
	ANDI R30,LOW(0x7)
	ANDI R31,HIGH(0x7)
	LSL  R30
	LSL  R30
	MOV  R31,R30
	LDI  R30,0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+14,R30
	STD  Y+14+1,R31
; 0006 0586 if ( g2 & 0x1000 ) {                /* negative */
	LDD  R30,Y+15
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0108
; 0006 0587 g2 |= 0xe000 ;
	LDD  R30,Y+15
	ORI  R30,LOW(0xE0)
	STD  Y+15,R30
; 0006 0588 }
; 0006 0589 g3 =  ((short) ((packed_data[c_ch][32] >> 3) & 0x1f) +
_0xC0108:
; 0006 058A (packed_data[c_ch][33] * 32)) & 0x1fff ;
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,32
	LD   R30,Z
	LDI  R31,0
	CALL __ASRW3
	ANDI R30,LOW(0x1F)
	ANDI R31,HIGH(0x1F)
	MOVW R22,R30
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,33
	LD   R26,Z
	LDI  R30,LOW(32)
	MUL  R30,R26
	MOVW R30,R0
	MOVW R26,R22
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(8191)
	LDI  R31,HIGH(8191)
	AND  R30,R26
	AND  R31,R27
	STD  Y+12,R30
	STD  Y+12+1,R31
; 0006 058B if ( g3 & 0x1000 ) {                /* negative */
	LDD  R30,Y+13
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xC0109
; 0006 058C g3 |= 0xe000 ;
	LDD  R30,Y+13
	ORI  R30,LOW(0xE0)
	STD  Y+13,R30
; 0006 058D }
; 0006 058E knst += d_knst;                                 /* remember new value */
_0xC0109:
	LDD  R30,Y+18
	LDD  R31,Y+18+1
	__ADDWRR 20,21,30,31
; 0006 058F sens_data[3] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
	__MULBNWRU 20,21,2
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(2)
	CALL __MULB1W2U
	ST   -Y,R31
	ST   -Y,R30
	__GETD2S 16
	CALL _CalcSensData
	__PUTW1MN _sens_data,6
; 0006 0590 /* sens value 100%FRO @ temp */
; 0006 0591 
; 0006 0592 sens_nl1 = (signed char)((packed_data[c_ch][34] >> 3) & 0x0f) ; /*  NL1 */
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,34
	LD   R30,Z
	LSR  R30
	LSR  R30
	LSR  R30
	ANDI R30,LOW(0xF)
	STS  _sens_nl1,R30
; 0006 0593 if ( (packed_data[c_ch][34]) & 0x80 ) {
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,34
	LD   R30,Z
	ANDI R30,LOW(0x80)
	BRNE PC+3
	JMP _0xC010A
; 0006 0594 sens_nl1 |= 0xf0 ;
	LDS  R30,_sens_nl1
	ORI  R30,LOW(0xF0)
	STS  _sens_nl1,R30
; 0006 0595 }
; 0006 0596 sens_nl1 *= 3 ;
_0xC010A:
	LDS  R30,_sens_nl1
	LDI  R26,LOW(3)
	MULS R30,R26
	MOVW R30,R0
	STS  _sens_nl1,R30
; 0006 0597 
; 0006 0598 sens_nl2 = (signed char) (packed_data[c_ch][34] & 0x07) ;         /* NL2 */
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,34
	LD   R30,Z
	ANDI R30,LOW(0x7)
	STS  _sens_nl2,R30
; 0006 0599 if ( (packed_data[c_ch][34]) & 0x04 ) {
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,34
	LD   R30,Z
	ANDI R30,LOW(0x4)
	BRNE PC+3
	JMP _0xC010B
; 0006 059A sens_nl2 |= 0xf8 ;
	LDS  R30,_sens_nl2
	ORI  R30,LOW(0xF8)
	STS  _sens_nl2,R30
; 0006 059B }
; 0006 059C sens_nl2 *= 3 ;
_0xC010B:
	LDS  R30,_sens_nl2
	LDI  R26,LOW(3)
	MULS R30,R26
	MOVW R30,R0
	STS  _sens_nl2,R30
; 0006 059D 
; 0006 059E offset[ch] =  (short) (packed_data[c_ch][35] +(packed_data[c_ch][36] * 256)) ;           /*offset*/
	LDD  R30,Y+20
	LDI  R26,LOW(_offset)
	LDI  R27,HIGH(_offset)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	MOVW R24,R30
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,35
	LD   R22,Z
	CLR  R23
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,36
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(256)
	LDI  R31,HIGH(256)
	CALL __MULW12
	ADD  R30,R22
	ADC  R31,R23
	MOVW R26,R24
	ST   X+,R30
	ST   X,R31
; 0006 059F data_low= packed_data[c_ch][37];
	LDD  R30,Y+6
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,37
	LD   R16,Z
	CLR  R17
; 0006 05A0 data_high= packed_data[c_ch][38] * 256;
	LDD  R30,Y+6
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,38
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(256)
	LDI  R31,HIGH(256)
	CALL __MULW12
	MOVW R18,R30
; 0006 05A1 gain[ch] =  1.0 + (float)((int)((data_low + data_high))/100000.0) ;  /*gain*/
	LDD  R30,Y+20
	LDI  R26,LOW(_gain)
	LDI  R27,HIGH(_gain)
	LDI  R31,0
	CALL __LSLW2
	ADD  R30,R26
	ADC  R31,R27
	PUSH R31
	PUSH R30
	MOVW R30,R18
	ADD  R30,R16
	ADC  R31,R17
	__CWD1
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x47C35000
	CALL __DIVF21
	__GETD2N 0x3F800000
	CALL __ADDF12
	POP  R26
	POP  R27
	__PUTDP1
; 0006 05A2 //gain[ch] =  1.0 + (float)((packed_data[c_ch][37] + packed_data[c_ch][38] * 256)/100000.0) ;  /*gain*/
; 0006 05A3 /* 256 can not be 256.0 !!!*/
; 0006 05A4 } else {
	RJMP _0xC010C
_0xC00FA:
; 0006 05A5 sens_data[0] =     0 ;                  /* dummy values to prevent */
	LDI  R30,LOW(0)
	STS  _sens_data,R30
	STS  _sens_data+1,R30
; 0006 05A6 sens_data[1] =  4000 ;             /* divide by zero */
	__POINTW1MN _sens_data,2
	LDI  R26,LOW(4000)
	LDI  R27,HIGH(4000)
	STD  Z+0,R26
	STD  Z+1,R27
; 0006 05A7 sens_data[2] =  8000 ;
	__POINTW1MN _sens_data,4
	LDI  R26,LOW(8000)
	LDI  R27,HIGH(8000)
	STD  Z+0,R26
	STD  Z+1,R27
; 0006 05A8 sens_data[3] = 12000 ;
	__POINTW1MN _sens_data,6
	LDI  R26,LOW(12000)
	LDI  R27,HIGH(12000)
	STD  Z+0,R26
	STD  Z+1,R27
; 0006 05A9 sens_nl1 = 0 ;
	LDI  R30,LOW(0)
	STS  _sens_nl1,R30
; 0006 05AA sens_nl2 = 0 ;
	STS  _sens_nl2,R30
; 0006 05AB offset[ch] =  0 ;                       /*offset*/
	LDD  R30,Y+20
	LDI  R26,LOW(_offset)
	LDI  R27,HIGH(_offset)
	LDI  R31,0
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	ST   X+,R30
	ST   X,R31
; 0006 05AC gain[ch] =  1.0 ;                       /* gain */
	LDD  R30,Y+20
	LDI  R26,LOW(_gain)
	LDI  R27,HIGH(_gain)
	LDI  R31,0
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1N 0x3F800000
	__PUTDP1
; 0006 05AD }
_0xC010C:
; 0006 05AE if ( (eep_type[7] & 0x01) || (eep_type[7] & 0x10) ) {     /* ok data */
	__GETB1MN _eep_type,7
	ANDI R30,LOW(0x1)
	BREQ PC+3
	JMP _0xC010E
	__GETB1MN _eep_type,7
	ANDI R30,LOW(0x10)
	BREQ PC+3
	JMP _0xC010E
	RJMP _0xC010D
_0xC010E:
; 0006 05AF cal_zero = (short) packed_data[7][35] + packed_data[7][36] * 256 ;
	__GETBRMN 22,_packed_data,315
	CLR  R23
	__GETB2MN _packed_data,316
	LDI  R27,0
	LDI  R30,LOW(256)
	LDI  R31,HIGH(256)
	CALL __MULW12
	ADD  R30,R22
	ADC  R31,R23
	STS  _cal_zero,R30
	STS  _cal_zero+1,R31
; 0006 05B0 data_low= packed_data[7][37];
	__GETBRMN 16,_packed_data,317
	CLR  R17
; 0006 05B1 data_high= packed_data[7][38] * 256;
	__GETB2MN _packed_data,318
	LDI  R27,0
	LDI  R30,LOW(256)
	LDI  R31,HIGH(256)
	CALL __MULW12
	MOVW R18,R30
; 0006 05B2 cal_gain =  1.0 + (float)((int)((data_low + data_high))/100000.0) ; /*gain*/
	ADD  R30,R16
	ADC  R31,R17
	__CWD1
	CALL __CDF1
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x47C35000
	CALL __DIVF21
	__GETD2N 0x3F800000
	CALL __ADDF12
	STS  _cal_gain,R30
	STS  _cal_gain+1,R31
	STS  _cal_gain+2,R22
	STS  _cal_gain+3,R23
; 0006 05B3 //cal_gain =  1.0 + (float)((packed_data[7][37] + packed_data[7][38] * 256)/100000.0) ; /*gain*/
; 0006 05B4 /* 256 can not be 256.0 !!!*/
; 0006 05B5 } else {
	RJMP _0xC0110
_0xC010D:
; 0006 05B6 cal_zero = 0 ;
	LDI  R30,LOW(0)
	STS  _cal_zero,R30
	STS  _cal_zero+1,R30
; 0006 05B7 cal_gain = 1.0 ;
	__GETD1N 0x3F800000
	STS  _cal_gain,R30
	STS  _cal_gain+1,R31
	STS  _cal_gain+2,R22
	STS  _cal_gain+3,R23
; 0006 05B8 }
_0xC0110:
; 0006 05B9 }
	CALL __LOADLOCR6
	ADIW R28,21
	RET
; .FEND
;unsigned int CalcSensData(unsigned int knst, unsigned int g1, unsigned int g2, unsigned int g3, float temp)
; 0006 05C0 {
_CalcSensData:
; .FSTART _CalcSensData
; 0006 05C1 
; 0006 05C2 return(knst + (g1 * temp) +
	CALL __PUTPARD2
	CALL __SAVELOCR6
	__GETWRS 16,17,10
	__GETWRS 18,19,12
	__GETWRS 20,21,14
;	knst -> Y+16
;	g1 -> R20,R21
;	g2 -> R18,R19
;	g3 -> R16,R17
;	temp -> Y+6
; 0006 05C3 (g2 * temp * temp) +
; 0006 05C4 (g3 * temp * temp * temp)) ;    /* sens value ?%FRO @ temp */
	__GETD1S 6
	MOVW R26,R20
	CLR  R24
	CLR  R25
	CALL __CDF2
	CALL __MULF12
	LDD  R26,Y+16
	LDD  R27,Y+16+1
	CLR  R24
	CLR  R25
	CALL __CDF2
	CALL __ADDF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	__GETD1S 6
	MOVW R26,R18
	CLR  R24
	CLR  R25
	CALL __CDF2
	CALL __MULF12
	__GETD2S 6
	CALL __MULF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __ADDF12
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	__GETD1S 6
	MOVW R26,R16
	CLR  R24
	CLR  R25
	CALL __CDF2
	CALL __MULF12
	__GETD2S 6
	CALL __MULF12
	__GETD2S 6
	CALL __MULF12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __ADDF12
	CALL __CFD1U
	CALL __LOADLOCR6
	ADIW R28,18
	RET
; 0006 05C5 
; 0006 05C6 }
; .FEND
;unsigned int FindTemp(signed char ch)
; 0006 05CE {
_FindTemp:
; .FSTART _FindTemp
; 0006 05CF 
; 0006 05D0 short temp_ch, i ;
; 0006 05D1 
; 0006 05D2 temp_ch = (short) ch + 1 ;
	CALL __SAVELOCR6
	MOV  R21,R26
;	ch -> R21
;	temp_ch -> R16,R17
;	i -> R18,R19
	MOV  R30,R21
	LDI  R31,0
	SBRC R30,7
	SER  R31
	ADIW R30,1
	MOVW R16,R30
; 0006 05D3 if ( ((ch_stat[temp_ch] & 0x0c) == 0x04) &&
; 0006 05D4 (mes_data[temp_ch] < 150.0) &&                     /* to high or */
; 0006 05D5 (mes_data[temp_ch] > -80.0) &&                     /* to low temp or */
; 0006 05D6 (!(ch_stat[temp_ch] & 0x01)) ) {                    /* convertion error */
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0xC)
	CPI  R30,LOW(0x4)
	BREQ PC+3
	JMP _0xC0112
	MOVW R30,R16
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x43160000
	CALL __CMPF12
	BRLO PC+3
	JMP _0xC0112
	MOVW R30,R16
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0xC2A00000
	CALL __CMPF12
	BREQ PC+2
	BRCC PC+3
	JMP  _0xC0112
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0x1)
	BREQ PC+3
	JMP _0xC0112
	RJMP _0xC0113
_0xC0112:
	RJMP _0xC0111
_0xC0113:
; 0006 05D7 } else {
	RJMP _0xC0114
_0xC0111:
; 0006 05D8 temp_ch = NOIOCH ;                         /* used if no temp */
	__GETWRN 16,17,14
; 0006 05D9 for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 18,19,0
_0xC0116:
	__CPWRN 18,19,14
	BRLO PC+3
	JMP _0xC0117
; 0006 05DA if ( (ch_stat[i] & 0x0c) == 0x04 ) {  /* temp ? */
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R18
	ADC  R27,R19
	LD   R30,X
	ANDI R30,LOW(0xC)
	CPI  R30,LOW(0x4)
	BREQ PC+3
	JMP _0xC0118
; 0006 05DB if ( (mes_data[i] < 150.0) &&         /* to high or */
; 0006 05DC (mes_data[i] > -80.0) &&     /* to low temp or */
; 0006 05DD !(ch_stat[i] & 0x01) ) {         /* convertion error */
	MOVW R30,R18
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0x43160000
	CALL __CMPF12
	BRLO PC+3
	JMP _0xC011A
	MOVW R30,R18
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	MOVW R26,R30
	MOVW R24,R22
	__GETD1N 0xC2A00000
	CALL __CMPF12
	BREQ PC+2
	BRCC PC+3
	JMP  _0xC011A
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R18
	ADC  R27,R19
	LD   R30,X
	ANDI R30,LOW(0x1)
	BREQ PC+3
	JMP _0xC011A
	RJMP _0xC011B
_0xC011A:
	RJMP _0xC0119
_0xC011B:
; 0006 05DE temp_ch = i ;
	MOVW R16,R18
; 0006 05DF i = NOIOCH ;                               /* exit */
	__GETWRN 18,19,14
; 0006 05E0 }
; 0006 05E1 }
_0xC0119:
; 0006 05E2 }
_0xC0118:
_0xC0115:
	__ADDWRN 18,19,1
	RJMP _0xC0116
_0xC0117:
; 0006 05E3 }
_0xC0114:
; 0006 05E4 
; 0006 05E5 return temp_ch ;
	MOVW R30,R16
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; 0006 05E6 }
; .FEND
;void ResetRxPointer(void)
; 0006 05EE {
_ResetRxPointer:
; .FSTART _ResetRxPointer
; 0006 05EF 
; 0006 05F0 rx_indx = 1 ;
	LDI  R30,LOW(1)
	STS  _rx_indx,R30
; 0006 05F1 rx_hndx = 0 ;
	LDI  R30,LOW(0)
	STS  _rx_hndx,R30
; 0006 05F2 rx_start = 0 ;
	STS  _rx_start,R30
; 0006 05F3 rx_buff[0] = 0 ;
	STS  _rx_buff,R30
; 0006 05F4 rx_buff[1] = 0 ;
	__PUTB1MN _rx_buff,1
; 0006 05F5 rx_buff[2] = 0 ;
	__PUTB1MN _rx_buff,2
; 0006 05F6 rx_state = SYNC ;                   /* error in pack len */
	STS  _rx_state,R30
; 0006 05F7 rx_timeout = OFF ;                 /* timeout on channel */
	STS  _rx_timeout,R30
; 0006 05F8 }
	RET
; .FEND
;int CalcRxChecksum(void)
; 0006 0600 {
_CalcRxChecksum:
; .FSTART _CalcRxChecksum
; 0006 0601 
; 0006 0602 int             cnt ;
; 0006 0603 unsigned char   csum ;
; 0006 0604 
; 0006 0605 csum = 0 ;
	CALL __SAVELOCR4
;	cnt -> R16,R17
;	csum -> R19
	LDI  R19,LOW(0)
; 0006 0606 for ( cnt=rx_start ; cnt < (rx_start+rx_packlen-2) ; cnt++ ) {
	LDS  R16,_rx_start
	CLR  R17
_0xC011D:
	LDS  R26,_rx_start
	CLR  R27
	LDS  R30,_rx_packlen
	LDI  R31,0
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(2)
	LDI  R31,HIGH(2)
	CALL __SWAPW12
	SUB  R30,R26
	SBC  R31,R27
	CP   R16,R30
	CPC  R17,R31
	BRLT PC+3
	JMP _0xC011E
; 0006 0607 csum = crc[csum ^ rx_buff[cnt]] ;
	MOV  R0,R19
	CLR  R1
	LDI  R26,LOW(_rx_buff)
	LDI  R27,HIGH(_rx_buff)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	LDI  R31,0
	EOR  R30,R0
	EOR  R31,R1
	SUBI R30,LOW(-_crc*2)
	SBCI R31,HIGH(-_crc*2)
	LPM  R19,Z
; 0006 0608 }
_0xC011C:
	__ADDWRN 16,17,1
	RJMP _0xC011D
_0xC011E:
; 0006 0609 if ( csum == (rx_buff[rx_start + rx_packlen - 2]) ) {
	LDS  R26,_rx_start
	CLR  R27
	LDS  R30,_rx_packlen
	LDI  R31,0
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(2)
	LDI  R31,HIGH(2)
	CALL __SWAPW12
	SUB  R30,R26
	SBC  R31,R27
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R30,Z
	CP   R30,R19
	BREQ PC+3
	JMP _0xC011F
; 0006 060A return TRUE ;
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; 0006 060B } else {
_0xC011F:
; 0006 060C return FALSE ;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; 0006 060D }
_0xC0120:
; 0006 060E }
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
;void HandleRxPacket(void)
; 0006 0617 {
_HandleRxPacket:
; .FSTART _HandleRxPacket
; 0006 0618 short     pointer, ndb, more ;
; 0006 0619 
; 0006 061A Led(1, ON) ;
	CALL __SAVELOCR6
;	pointer -> R16,R17
;	ndb -> R18,R19
;	more -> R20,R21
	LDI  R30,LOW(1)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _Led
; 0006 061B sendtail = FALSE ;
	LDI  R30,LOW(0)
	STS  _sendtail,R30
; 0006 061C more    = TRUE ;
	__GETWRN 20,21,1
; 0006 061D pointer = 0 ;
	__GETWRN 16,17,0
; 0006 061E ndb = 2 ;                                           /* point to first command */
	__GETWRN 18,19,2
; 0006 061F pointer = rx_start;                             /* Point to  command */
	LDS  R16,_rx_start
	CLR  R17
; 0006 0620 while ( more && (pointer < (rx_packlen + rx_start)) ) {
_0xC0121:
	MOV  R0,R20
	OR   R0,R21
	BRNE PC+3
	JMP _0xC0124
	LDS  R26,_rx_packlen
	CLR  R27
	LDS  R30,_rx_start
	LDI  R31,0
	ADD  R30,R26
	ADC  R31,R27
	CP   R16,R30
	CPC  R17,R31
	BRLO PC+3
	JMP _0xC0124
	RJMP _0xC0125
_0xC0124:
	RJMP _0xC0123
_0xC0125:
; 0006 0621 pointer = pointer + ndb + 2;                /* Point to  command */
	MOVW R30,R18
	ADD  R30,R16
	ADC  R31,R17
	ADIW R30,2
	MOVW R16,R30
; 0006 0622 ndb = rx_buff[pointer+1]    ;               /* Save pointer to next command */
	__ADDW1MN _rx_buff,1
	LD   R18,Z
	CLR  R19
; 0006 0623 if ( !CheckAction(pointer) ) {
	MOVW R26,R16
	CALL _CheckAction
	SBIW R30,0
	BREQ PC+3
	JMP _0xC0126
; 0006 0624 more = FALSE ;                              /* terminate while  */
	__GETWRN 20,21,0
; 0006 0625 }
; 0006 0626 }
_0xC0126:
	RJMP _0xC0121
_0xC0123:
; 0006 0627 Led(1, OFF) ;
	LDI  R30,LOW(1)
	ST   -Y,R30
	LDI  R26,LOW(0)
	CALL _Led
; 0006 0628 }
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; .FEND
;int ReceiveRxPacket(void)
; 0006 0630 {
_ReceiveRxPacket:
; .FSTART _ReceiveRxPacket
; 0006 0631 //    int   ret_val, cnt, new_sync ;
; 0006 0632 int   ret_val ;
; 0006 0633 
; 0006 0634 ret_val = FALSE ;
	ST   -Y,R17
	ST   -Y,R16
;	ret_val -> R16,R17
	__GETWRN 16,17,0
; 0006 0635 rx_timeout = RX_TO_TIME ;               /* timeout on channel */
	LDI  R30,LOW(232)
	STS  _rx_timeout,R30
; 0006 0636 while ( rx_indx > rx_hndx )
_0xC0127:
	LDS  R30,_rx_hndx
	LDS  R26,_rx_indx
	CP   R30,R26
	BRLO PC+3
	JMP _0xC0129
; 0006 0637 {                     /* more char to check */
; 0006 0638 switch ( rx_state )
	LDS  R30,_rx_state
	LDI  R31,0
; 0006 0639 {                     /* check state */
; 0006 063A case SYNC :
	SBIW R30,0
	BREQ PC+3
	JMP _0xC012D
; 0006 063B // all functionallity moved to inerrupt routine for receive
; 0006 063C // on version 10
; 0006 063D break ;
	RJMP _0xC012C
; 0006 063E case HEADER :
_0xC012D:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC012E
; 0006 063F if ( (rx_hndx-rx_start) >= 3 )
	LDS  R26,_rx_hndx
	CLR  R27
	LDS  R30,_rx_start
	LDI  R31,0
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,3
	BRGE PC+3
	JMP _0xC012F
; 0006 0640 {             /* rec. header */
; 0006 0641 rx_packlen = ((rx_buff[rx_start+2] * 256) + rx_buff[rx_start+3] ) ;             /* calc. pack.len */
	LDS  R30,_rx_start
	LDI  R31,0
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDS  R30,_rx_start
	LDI  R31,0
	__ADDW1MN _rx_buff,3
	LD   R30,Z
	STS  _rx_packlen,R30
; 0006 0642 if ( (rx_packlen < ((short) RX_SIZE-rx_hndx)) &&    /* chk. header */
; 0006 0643 (rx_packlen >= MIN_PACK_LEN) &&
; 0006 0644 (rx_buff[rx_start+1] != 0xff) )
	LDS  R30,_rx_hndx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	CALL __SWAPW12
	SUB  R30,R26
	SBC  R31,R27
	LDS  R26,_rx_packlen
	LDI  R27,0
	CP   R26,R30
	CPC  R27,R31
	BRLT PC+3
	JMP _0xC0131
	LDS  R26,_rx_packlen
	CPI  R26,LOW(0x5)
	BRSH PC+3
	JMP _0xC0131
	LDS  R30,_rx_start
	LDI  R31,0
	__ADDW1MN _rx_buff,1
	LD   R26,Z
	CPI  R26,LOW(0xFF)
	BRNE PC+3
	JMP _0xC0131
	RJMP _0xC0132
_0xC0131:
	RJMP _0xC0130
_0xC0132:
; 0006 0645 {
; 0006 0646 rx_state = RECEIVE ;                    /* header ok */
	LDI  R30,LOW(2)
	STS  _rx_state,R30
; 0006 0647 rx_counter = rx_hndx - rx_start + 1 ;
	LDS  R26,_rx_start
	LDS  R30,_rx_hndx
	SUB  R30,R26
	SUBI R30,-LOW(1)
	STS  _rx_counter,R30
; 0006 0648 } else
	RJMP _0xC0133
_0xC0130:
; 0006 0649 {
; 0006 064A ResetRxPointer() ;
	CALL _ResetRxPointer
; 0006 064B }
_0xC0133:
; 0006 064C }
; 0006 064D break ;
_0xC012F:
	RJMP _0xC012C
; 0006 064E case RECEIVE :
_0xC012E:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xC013D
; 0006 064F if ( ++rx_counter >= rx_packlen ) {
	LDS  R26,_rx_counter
	SUBI R26,-LOW(1)
	STS  _rx_counter,R26
	LDS  R30,_rx_packlen
	CP   R26,R30
	BRSH PC+3
	JMP _0xC0135
; 0006 0650 if ( (rx_buff[rx_packlen + rx_start-1]) == ETX ) {
	LDS  R26,_rx_packlen
	CLR  R27
	LDS  R30,_rx_start
	LDI  R31,0
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CALL __SWAPW12
	SUB  R30,R26
	SBC  R31,R27
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R26,Z
	CPI  R26,LOW(0x3)
	BREQ PC+3
	JMP _0xC0136
; 0006 0651 if ( CalcRxChecksum() )
	CALL _CalcRxChecksum
	SBIW R30,0
	BRNE PC+3
	JMP _0xC0137
; 0006 0652 {
; 0006 0653 if ( rx_buff[rx_start + 1] < PC_START_ADDRESS )
	LDS  R30,_rx_start
	LDI  R31,0
	__ADDW1MN _rx_buff,1
	LD   R26,Z
	CPI  R26,LOW(0xF0)
	BRLO PC+3
	JMP _0xC0138
; 0006 0654 {
; 0006 0655 }
; 0006 0656 if ( (rx_buff[rx_start] == MYADRESS_LOCAL)||
_0xC0138:
; 0006 0657 (rx_buff[rx_start] == 0) )
	LDS  R30,_rx_start
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R26,Z
	CPI  R26,LOW(0x9)
	BRNE PC+3
	JMP _0xC013A
	LDS  R30,_rx_start
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R26,Z
	CPI  R26,LOW(0x0)
	BRNE PC+3
	JMP _0xC013A
	RJMP _0xC0139
_0xC013A:
; 0006 0658 {        /* don't use address*/
; 0006 0659 ret_val = TRUE ;
	__GETWRN 16,17,1
; 0006 065A }
; 0006 065B }
_0xC0139:
; 0006 065C else
	RJMP _0xC013C
_0xC0137:
; 0006 065D {
; 0006 065E ResetRxPointer() ;              /* reset pointer */
	CALL _ResetRxPointer
; 0006 065F }
_0xC013C:
; 0006 0660 }
; 0006 0661 }
_0xC0136:
; 0006 0662 break ;
_0xC0135:
	RJMP _0xC012C
; 0006 0663 default :
_0xC013D:
; 0006 0664 ResetRxPointer() ;                          /* reset pointer */
	CALL _ResetRxPointer
; 0006 0665 break ;
; 0006 0666 }                                                       /* end switch */
_0xC012C:
; 0006 0667 if ( ++rx_hndx >= RX_SIZE ) {                 /* check pointer */
	LDS  R26,_rx_hndx
	SUBI R26,-LOW(1)
	STS  _rx_hndx,R26
	CPI  R26,LOW(0xC8)
	BRSH PC+3
	JMP _0xC013E
; 0006 0668 ResetRxPointer() ;                          /* reset pointer */
	CALL _ResetRxPointer
; 0006 0669 }
; 0006 066A }                                                           /* end while.. */
_0xC013E:
	RJMP _0xC0127
_0xC0129:
; 0006 066B return ret_val ;
	MOVW R30,R16
	LD   R16,Y+
	LD   R17,Y+
	RET
; 0006 066C }
; .FEND
;void     ResetADCBySW(void)
; 0006 066F {   spi1_master_tx_rx (0xFF);
_ResetADCBySW:
; .FSTART _ResetADCBySW
	LDI  R26,LOW(255)
	CALL _spi1_master_tx_rx
; 0006 0670 spi1_master_tx_rx (0xFF);
	LDI  R26,LOW(255)
	CALL _spi1_master_tx_rx
; 0006 0671 spi1_master_tx_rx (0xFF);
	LDI  R26,LOW(255)
	CALL _spi1_master_tx_rx
; 0006 0672 spi1_master_tx_rx (0xFF);
	LDI  R26,LOW(255)
	CALL _spi1_master_tx_rx
; 0006 0673 
; 0006 0674 }
	RET
; .FEND
;void     ResetADCByHW(void)
; 0006 0676 {   ADC_CS_LOW;
_ResetADCByHW:
; .FSTART _ResetADCByHW
	LDI  R30,LOW(8)
	STS  1094,R30
; 0006 0677 delay_us(50);
	__DELAY_USB 67
; 0006 0678 ADC_RST_LOW;
	LDI  R30,LOW(32)
	STS  1190,R30
; 0006 0679 delay_ms(10);
	LDI  R26,LOW(10)
	LDI  R27,0
	CALL _delay_ms
; 0006 067A ADC_RST_HIGH;
	LDI  R30,LOW(32)
	STS  1189,R30
; 0006 067B //ADC_CS_HIGH;
; 0006 067C delay_us(50);
	__DELAY_USB 67
; 0006 067D }
	RET
; .FEND
;interrupt [(23)  ] void usart0_tx_isr(void)
; 0006 068A {
_usart0_tx_isr:
; .FSTART _usart0_tx_isr
	ST   -Y,R0
	ST   -Y,R1
	ST   -Y,R15
	ST   -Y,R22
	ST   -Y,R23
	ST   -Y,R24
	ST   -Y,R25
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0006 068B if ( tx_indx < tx_bytes )         /* More to send ? */
	LDS  R30,_tx_bytes
	LDS  R26,_tx_indx
	CP   R26,R30
	BRLO PC+3
	JMP _0xC013F
; 0006 068C {   USART0.TXDATAL = tx_buff[tx_indx++];
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LD   R30,Z
	STS  2050,R30
; 0006 068D ad_mode |= 0x01 ;
	LDS  R30,_ad_mode
	ORI  R30,1
	STS  _ad_mode,R30
; 0006 068E }
; 0006 068F else
	RJMP _0xC0140
_0xC013F:
; 0006 0690 {   delay_ms(2);// ADD TO FINSIH SENDING
	LDI  R26,LOW(2)
	LDI  R27,0
	CALL _delay_ms
; 0006 0691 USART0.CTRLA&= ~USART_DREIE_bm;
	LDS  R30,2053
	ANDI R30,0xDF
	STS  2053,R30
; 0006 0692 tx_tail = TXTAIL ;            /* driver on for last char */
	LDI  R30,LOW(2)
	STS  _tx_tail,R30
; 0006 0693 }
_0xC0140:
; 0006 0694 }
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	LD   R25,Y+
	LD   R24,Y+
	LD   R23,Y+
	LD   R22,Y+
	LD   R15,Y+
	LD   R1,Y+
	LD   R0,Y+
	RETI
; .FEND
;interrupt [(22)  ] void usart0_rx_isr(void)
; 0006 069F {
_usart0_rx_isr:
; .FSTART _usart0_rx_isr
	ST   -Y,R0
	ST   -Y,R1
	ST   -Y,R15
	ST   -Y,R22
	ST   -Y,R23
	ST   -Y,R24
	ST   -Y,R25
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0006 06A0 
; 0006 06A1 char status, bufch;
; 0006 06A2 
; 0006 06A3 status=USART0.RXDATAH;
	ST   -Y,R17
	ST   -Y,R16
;	status -> R17
;	bufch -> R16
	LDS  R17,2049
; 0006 06A4 bufch=USART0.RXDATAL;
	LDS  R16,2048
; 0006 06A5 if ((status & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm)) == 0)
	MOV  R30,R17
	ANDI R30,LOW(0x46)
	BREQ PC+3
	JMP _0xC0141
; 0006 06A6 {    if ( tx_complete )
	LDS  R30,_tx_complete
	CPI  R30,0
	BRNE PC+3
	JMP _0xC0142
; 0006 06A7 {                      /* ok to receive? */
; 0006 06A8 switch ( rx_state ) {                     /* check state */
	LDS  R30,_rx_state
	LDI  R31,0
; 0006 06A9 case SYNC :
	SBIW R30,0
	BREQ PC+3
	JMP _0xC014B
; 0006 06AA if ( bufch == STX )
	CPI  R16,2
	BREQ PC+3
	JMP _0xC0147
; 0006 06AB {
; 0006 06AC sync_cnt ++ ;               // cont sync
	LDS  R30,_sync_cnt
	SUBI R30,-LOW(1)
	STS  _sync_cnt,R30
; 0006 06AD }
; 0006 06AE else if ( sync_cnt >= 2 )
	RJMP _0xC0148
_0xC0147:
	LDS  R26,_sync_cnt
	CPI  R26,LOW(0x2)
	BRSH PC+3
	JMP _0xC0149
; 0006 06AF {
; 0006 06B0 sync_cnt = 0 ;              // reset counter
	LDI  R30,LOW(0)
	STS  _sync_cnt,R30
; 0006 06B1 rx_state = HEADER ;
	LDI  R30,LOW(1)
	STS  _rx_state,R30
; 0006 06B2 rx_indx = 0 ;
	LDI  R30,LOW(0)
	STS  _rx_indx,R30
; 0006 06B3 rx_hndx = 0 ;
	STS  _rx_hndx,R30
; 0006 06B4 rx_start = rx_hndx ;            /* start after the two STX */
	STS  _rx_start,R30
; 0006 06B5 rx_buff[rx_indx++] = bufch;
	LDS  R30,_rx_indx
	SUBI R30,-LOW(1)
	STS  _rx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	ST   Z,R16
; 0006 06B6 }
; 0006 06B7 else
	RJMP _0xC014A
_0xC0149:
; 0006 06B8 {
; 0006 06B9 sync_cnt = 0 ;                  // start over once more
	LDI  R30,LOW(0)
	STS  _sync_cnt,R30
; 0006 06BA }
_0xC014A:
_0xC0148:
; 0006 06BB break;
	RJMP _0xC0145
; 0006 06BC default:
_0xC014B:
; 0006 06BD rx_buff[rx_indx++] = bufch;
	LDS  R30,_rx_indx
	SUBI R30,-LOW(1)
	STS  _rx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	ST   Z,R16
; 0006 06BE break;
; 0006 06BF }
_0xC0145:
; 0006 06C0 if ( rx_indx >= RX_SIZE ) {           /* check rx pointer */
	LDS  R26,_rx_indx
	CPI  R26,LOW(0xC8)
	BRSH PC+3
	JMP _0xC014C
; 0006 06C1 ResetRxPointer() ;              // reset pointer
	CALL _ResetRxPointer
; 0006 06C2 }
; 0006 06C3 }
_0xC014C:
; 0006 06C4 }
_0xC0142:
; 0006 06C5 }
_0xC0141:
	LD   R16,Y+
	LD   R17,Y+
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	LD   R25,Y+
	LD   R24,Y+
	LD   R23,Y+
	LD   R22,Y+
	LD   R15,Y+
	LD   R1,Y+
	LD   R0,Y+
	RETI
; .FEND
;unsigned int CheckAction(unsigned int data)
; 0007 002D {

	.CSEG
_CheckAction:
; .FSTART _CheckAction
; 0007 002E short i, test, ret_val = TRUE ;
; 0007 002F unsigned char d_buff[PACKED_DATA_SIZE] ;
; 0007 0030 unsigned int pointer=data;
; 0007 0031 switch ( rx_buff[pointer] ) {                      /* check action */
	ST   -Y,R27
	ST   -Y,R26
	SBIW R28,42
	CALL __SAVELOCR6
;	data -> Y+48
;	i -> R16,R17
;	test -> R18,R19
;	ret_val -> R20,R21
;	d_buff -> Y+8
;	pointer -> Y+6
	__GETWRN 20,21,1
	LDD  R30,Y+48
	LDD  R31,Y+48+1
	STD  Y+6,R30
	STD  Y+6+1,R31
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R30,Z
	LDI  R31,0
; 0007 0032 case SEND_M_DATA :
	CPI  R30,LOW(0xA)
	LDI  R26,HIGH(0xA)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0006
; 0007 0033 not_mes_data = rx_buff[pointer+2] ;     /* number of transmissions */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	STS  _not_mes_data,R30
; 0007 0034 not_raw_data = 0 ;
	LDI  R30,LOW(0)
	STS  _not_raw_data,R30
; 0007 0035 not_cal_data = 0 ;
	STS  _not_cal_data,R30
; 0007 0036 if ( not_mes_data ) {                         /* check if not 0 and send one */
	LDS  R30,_not_mes_data
	CPI  R30,0
	BRNE PC+3
	JMP _0xE0007
; 0007 0037 not_mes_data-- ;
	SUBI R30,LOW(1)
	STS  _not_mes_data,R30
; 0007 0038 }
; 0007 0039 if ( !sendtail ) {                            /* make header ? */
_0xE0007:
	LDS  R30,_sendtail
	CPI  R30,0
	BREQ PC+3
	JMP _0xE0008
; 0007 003A BuildHeader() ;                             /* Build send packet header */
	CALL _BuildHeader
; 0007 003B sendtail |= MAKE ;              /* build tail*/
	LDS  R30,_sendtail
	ORI  R30,1
	STS  _sendtail,R30
; 0007 003C }
; 0007 003D if ( (sendtail & TX_ERR) || ((TX_SIZE - tx_indx) < 10 ) ) {
_0xE0008:
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE000A
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,10
	BRGE PC+3
	JMP _0xE000A
	RJMP _0xE0009
_0xE000A:
; 0007 003E sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 003F } else {
	RJMP _0xE000C
_0xE0009:
; 0007 0040 BuildMTData() ;                     /* Build data p. for temp. */
	CALL _BuildMTData
; 0007 0041 }
_0xE000C:
; 0007 0042 if ( (sendtail & TX_ERR) || ((TX_SIZE - tx_indx) < 10 ) ) {
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE000E
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,10
	BRGE PC+3
	JMP _0xE000E
	RJMP _0xE000D
_0xE000E:
; 0007 0043 sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 0044 } else {
	RJMP _0xE0010
_0xE000D:
; 0007 0045 BuildMPData();                          /* Build data p. for pressure */
	CALL _BuildMPData
; 0007 0046 }
_0xE0010:
; 0007 0047 if ( (sendtail & TX_ERR) || ((TX_SIZE - tx_indx) < 10 ) ) {
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE0012
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,10
	BRGE PC+3
	JMP _0xE0012
	RJMP _0xE0011
_0xE0012:
; 0007 0048 sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 0049 } else {
	RJMP _0xE0014
_0xE0011:
; 0007 004A BuildMOData() ;                         /* Build data p. for other */
	CALL _BuildMOData
; 0007 004B }
_0xE0014:
; 0007 004C if ( (sendtail & TX_ERR) || ((TX_SIZE - tx_indx) < 10 ) ) {
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE0016
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,10
	BRGE PC+3
	JMP _0xE0016
	RJMP _0xE0015
_0xE0016:
; 0007 004D sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 004E } else {
	RJMP _0xE0018
_0xE0015:
; 0007 004F BuildWHData();                        // Send high level and washtrac
	CALL _BuildWHData
; 0007 0050 }
_0xE0018:
; 0007 0051 break ;
	RJMP _0xE0005
; 0007 0052 
; 0007 0053 case SEND_R_DATA :
_0xE0006:
	CPI  R30,LOW(0xD)
	LDI  R26,HIGH(0xD)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0019
; 0007 0054 not_raw_data = rx_buff[pointer+2] ;     /* number of transmissions */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	STS  _not_raw_data,R30
; 0007 0055 not_mes_data = 0 ;
	LDI  R30,LOW(0)
	STS  _not_mes_data,R30
; 0007 0056 not_cal_data = 0 ;
	STS  _not_cal_data,R30
; 0007 0057 if ( not_raw_data ) {                         /* check if not 0 and send one */
	LDS  R30,_not_raw_data
	CPI  R30,0
	BRNE PC+3
	JMP _0xE001A
; 0007 0058 not_raw_data-- ;
	SUBI R30,LOW(1)
	STS  _not_raw_data,R30
; 0007 0059 }
; 0007 005A if ( !sendtail ) {                            /* make header ? */
_0xE001A:
	LDS  R30,_sendtail
	CPI  R30,0
	BREQ PC+3
	JMP _0xE001B
; 0007 005B BuildHeader() ;                             /* Build send packet header */
	CALL _BuildHeader
; 0007 005C sendtail |= MAKE ;              /* build tail*/
	LDS  R30,_sendtail
	ORI  R30,1
	STS  _sendtail,R30
; 0007 005D }
; 0007 005E if ( (sendtail & TX_ERR) ||
_0xE001B:
; 0007 005F ((TX_SIZE - tx_indx) < 56 ) ) {
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE001D
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,56
	BRGE PC+3
	JMP _0xE001D
	RJMP _0xE001C
_0xE001D:
; 0007 0060 sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 0061 } else {
	RJMP _0xE001F
_0xE001C:
; 0007 0062 BuildRTData() ;                         /* Build data p. for temp. */
	CALL _BuildRTData
; 0007 0063 }
_0xE001F:
; 0007 0064 if ( (sendtail & TX_ERR) ||
; 0007 0065 ((TX_SIZE - tx_indx) < 28 ) ) {
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE0021
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,28
	BRGE PC+3
	JMP _0xE0021
	RJMP _0xE0020
_0xE0021:
; 0007 0066 sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 0067 } else {
	RJMP _0xE0023
_0xE0020:
; 0007 0068 BuildRPData() ;                             /* Build data p. for pressure */
	CALL _BuildRPData
; 0007 0069 }
_0xE0023:
; 0007 006A if ( (sendtail & TX_ERR) ||
; 0007 006B ((TX_SIZE - tx_indx) < 28 ) ) {
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE0025
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,28
	BRGE PC+3
	JMP _0xE0025
	RJMP _0xE0024
_0xE0025:
; 0007 006C sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 006D } else {
	RJMP _0xE0027
_0xE0024:
; 0007 006E BuildROData() ;                     /* Build data p. for other */
	CALL _BuildROData
; 0007 006F }
_0xE0027:
; 0007 0070 break ;
	RJMP _0xE0005
; 0007 0071 case SEND_C_DATA :
_0xE0019:
	CPI  R30,LOW(0x10)
	LDI  R26,HIGH(0x10)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0028
; 0007 0072 not_cal_data = rx_buff[pointer+2] ;     /* number of transmissions */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	STS  _not_cal_data,R30
; 0007 0073 not_raw_data = 0 ;
	LDI  R30,LOW(0)
	STS  _not_raw_data,R30
; 0007 0074 not_mes_data = 0 ;
	STS  _not_mes_data,R30
; 0007 0075 if ( not_cal_data ) {                         /* check if not 0 and send one */
	LDS  R30,_not_cal_data
	CPI  R30,0
	BRNE PC+3
	JMP _0xE0029
; 0007 0076 not_cal_data-- ;
	SUBI R30,LOW(1)
	STS  _not_cal_data,R30
; 0007 0077 }
; 0007 0078 if ( !sendtail ) {                            /* make header ? */
_0xE0029:
	LDS  R30,_sendtail
	CPI  R30,0
	BREQ PC+3
	JMP _0xE002A
; 0007 0079 BuildHeader() ;                             /* Build send packet header */
	CALL _BuildHeader
; 0007 007A sendtail |= MAKE ;              /* build tail*/
	LDS  R30,_sendtail
	ORI  R30,1
	STS  _sendtail,R30
; 0007 007B }
; 0007 007C if ( (sendtail & TX_ERR) ||
_0xE002A:
; 0007 007D ((TX_SIZE - tx_indx) < 56 ) ) {
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE002C
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,56
	BRGE PC+3
	JMP _0xE002C
	RJMP _0xE002B
_0xE002C:
; 0007 007E sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 007F } else {
	RJMP _0xE002E
_0xE002B:
; 0007 0080 BuildCalData() ;                        /* Build calibration data */
	CALL _BuildCalData
; 0007 0081 }
_0xE002E:
; 0007 0082 break ;
	RJMP _0xE0005
; 0007 0083 case SEND_CONFIG :
_0xE0028:
	CPI  R30,LOW(0x11)
	LDI  R26,HIGH(0x11)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE002F
; 0007 0084 if ( !sendtail ) {                            /* make header ? */
	LDS  R30,_sendtail
	CPI  R30,0
	BREQ PC+3
	JMP _0xE0030
; 0007 0085 BuildHeader() ;                             /* Build send packet header */
	CALL _BuildHeader
; 0007 0086 sendtail |= MAKE ;              /* build tail*/
	LDS  R30,_sendtail
	ORI  R30,1
	STS  _sendtail,R30
; 0007 0087 }
; 0007 0088 if ( (sendtail & TX_ERR) ||
_0xE0030:
; 0007 0089 ((TX_SIZE - tx_indx) < 42 ) ) {
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE0032
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,42
	BRGE PC+3
	JMP _0xE0032
	RJMP _0xE0031
_0xE0032:
; 0007 008A sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 008B } else {
	RJMP _0xE0034
_0xE0031:
; 0007 008C BuildConfData() ;                           /* Build config data */
	CALL _BuildConfData
; 0007 008D }
_0xE0034:
; 0007 008E break ;
	RJMP _0xE0005
; 0007 008F case REC_EEP_DATA :
_0xE002F:
	CPI  R30,LOW(0x12)
	LDI  R26,HIGH(0x12)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0035
; 0007 0090 RecEepData(pointer+2) ;                     /* new eeprom data for a channel*/
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	ADIW R26,2
	CALL _RecEepData
; 0007 0091 break ;
	RJMP _0xE0005
; 0007 0092 case REC_OFF_GAIN :
_0xE0035:
	CPI  R30,LOW(0x13)
	LDI  R26,HIGH(0x13)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0036
; 0007 0093 RecOGData(pointer) ;                            /* offset and gain from PC */
	LDD  R26,Y+6
	CALL _RecOGData
; 0007 0094 break ;
	RJMP _0xE0005
; 0007 0095 case REC_SET_UP :
_0xE0036:
	CPI  R30,LOW(0x14)
	LDI  R26,HIGH(0x14)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0037
; 0007 0096 RecSetupData(pointer + 2) ;             /* setup for channels */
	LDD  R26,Y+6
	SUBI R26,-LOW(2)
	CALL _RecSetupData
; 0007 0097 break ;
	RJMP _0xE0005
; 0007 0098 case REC_TBTR :
_0xE0037:
	CPI  R30,LOW(0x15)
	LDI  R26,HIGH(0x15)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0038
; 0007 0099 time_b_temp = rx_buff[pointer+2]  ;     /* seconds between temp reading*/
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	STS  _time_b_temp,R30
; 0007 009A time_b_cnt = time_b_temp ;                  /* reload counter */
	STS  _time_b_cnt,R30
; 0007 009B break ;
	RJMP _0xE0005
; 0007 009C case CMD_WRITE_EEP :
_0xE0038:
	CPI  R30,LOW(0x16)
	LDI  R26,HIGH(0x16)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0039
; 0007 009D test = TRUE ;
	__GETWRN 18,19,1
; 0007 009E if ( eep_type[rx_buff[pointer+2]>>1] & 0x09 ) {
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	LD   R30,Z
	ANDI R30,LOW(0x9)
	BRNE PC+3
	JMP _0xE003A
; 0007 009F for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
	__GETWRN 16,17,0
_0xE003C:
	__CPWRN 16,17,40
	BRLO PC+3
	JMP _0xE003D
; 0007 00A0 d_buff[i] = packed_data[rx_buff[pointer+2]>>1][i] ; /*copy buffer */
	MOVW R30,R16
	MOVW R26,R28
	ADIW R26,8
	ADD  R30,R26
	ADC  R31,R27
	MOVW R22,R30
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	LDI  R26,LOW(40)
	LDI  R27,HIGH(40)
	CALL __MULW12U
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	ADD  R30,R16
	ADC  R31,R17
	LD   R30,Z
	MOVW R26,R22
	ST   X,R30
; 0007 00A1 }
_0xE003B:
	__ADDWRN 16,17,1
	RJMP _0xE003C
_0xE003D:
; 0007 00A2 if ( !Eeprom(rx_buff[pointer+2]>>1, WRITE_SP) ) {
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(15)
	CALL _Eeprom
	SBIW R30,0
	BREQ PC+3
	JMP _0xE003E
; 0007 00A3 test= FALSE ;                               /* write data to scratchpad */
	__GETWRN 18,19,0
; 0007 00A4 }
; 0007 00A5 if ( !Eeprom(rx_buff[pointer+2]>>1, READ_SP) ) {
_0xE003E:
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(170)
	CALL _Eeprom
	SBIW R30,0
	BREQ PC+3
	JMP _0xE003F
; 0007 00A6 test = FALSE ;                          /* Read data from scratchpad */
	__GETWRN 18,19,0
; 0007 00A7 }
; 0007 00A8 for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
_0xE003F:
	__GETWRN 16,17,0
_0xE0041:
	__CPWRN 16,17,40
	BRLO PC+3
	JMP _0xE0042
; 0007 00A9 if ( d_buff[i] != packed_data[rx_buff[pointer+2]>>1][i] ) {
	MOVW R26,R28
	ADIW R26,8
	ADD  R26,R16
	ADC  R27,R17
	LD   R22,X
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	LDI  R26,LOW(40)
	LDI  R27,HIGH(40)
	CALL __MULW12U
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	ADD  R30,R16
	ADC  R31,R17
	LD   R30,Z
	CP   R30,R22
	BRNE PC+3
	JMP _0xE0043
; 0007 00AA test = FALSE;                                  /*compare buffer */
	__GETWRN 18,19,0
; 0007 00AB }
; 0007 00AC }
_0xE0043:
_0xE0040:
	__ADDWRN 16,17,1
	RJMP _0xE0041
_0xE0042:
; 0007 00AD } else {
	RJMP _0xE0044
_0xE003A:
; 0007 00AE test = FALSE ;
	__GETWRN 18,19,0
; 0007 00AF }
_0xE0044:
; 0007 00B0 if ( !sendtail ) {                                /* make header ? */
	LDS  R30,_sendtail
	CPI  R30,0
	BREQ PC+3
	JMP _0xE0045
; 0007 00B1 BuildHeader() ;                             /* Build send packet header */
	CALL _BuildHeader
; 0007 00B2 sendtail |= MAKE ;                      /* build tail*/
	LDS  R30,_sendtail
	ORI  R30,1
	STS  _sendtail,R30
; 0007 00B3 }
; 0007 00B4 if ( !(sendtail & TX_ERR) ) {
_0xE0045:
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE0046
; 0007 00B5 tx_buff[tx_indx++] = TX_WRITE_EEP ;     /* Command  */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(42)
	STD  Z+0,R26
; 0007 00B6 tx_buff[tx_indx++] = 1 ;                    /* One byte data  */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(1)
	STD  Z+0,R26
; 0007 00B7 tx_buff[tx_indx] = 1 ;              /* Write status code FAIL */
	LDS  R30,_tx_indx
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	STD  Z+0,R26
; 0007 00B8 if ( test == TRUE ) {                             /* write to eep OK */
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R18
	CPC  R31,R19
	BREQ PC+3
	JMP _0xE0047
; 0007 00B9 if ( Eeprom(rx_buff[pointer+2]>>1, COPY_SP_NV) ) {    /* copy data to NV-ram */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(85)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0xE0048
; 0007 00BA tx_buff[tx_indx] = 0 ;              /* Write status code OK*/
	LDS  R30,_tx_indx
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(0)
	STD  Z+0,R26
; 0007 00BB }
; 0007 00BC }
_0xE0048:
; 0007 00BD tx_indx++ ;                                     /* Write status code FAIL */
_0xE0047:
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
; 0007 00BE }
; 0007 00BF break ;
_0xE0046:
	RJMP _0xE0005
; 0007 00C0 case CMD_WRITE_ADR :
_0xE0039:
	CPI  R30,LOW(0x17)
	LDI  R26,HIGH(0x17)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0049
; 0007 00C1 test = TRUE ;
	__GETWRN 18,19,1
; 0007 00C2 if ( eep_type[rx_buff[pointer+2]>>1] & 0x09 ) {
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	LD   R30,Z
	ANDI R30,LOW(0x9)
	BRNE PC+3
	JMP _0xE004A
; 0007 00C3 for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
	__GETWRN 16,17,0
_0xE004C:
	__CPWRN 16,17,40
	BRLO PC+3
	JMP _0xE004D
; 0007 00C4 d_buff[i] = packed_data[rx_buff[pointer+2]>>1][i] ; /*copy buffer */
	MOVW R30,R16
	MOVW R26,R28
	ADIW R26,8
	ADD  R30,R26
	ADC  R31,R27
	MOVW R22,R30
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	LDI  R26,LOW(40)
	LDI  R27,HIGH(40)
	CALL __MULW12U
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	ADD  R30,R16
	ADC  R31,R17
	LD   R30,Z
	MOVW R26,R22
	ST   X,R30
; 0007 00C5 }
_0xE004B:
	__ADDWRN 16,17,1
	RJMP _0xE004C
_0xE004D:
; 0007 00C6 if ( !Eeprom(rx_buff[pointer+2]>>1, WRITE_APPREG) ) {
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(153)
	CALL _Eeprom
	SBIW R30,0
	BREQ PC+3
	JMP _0xE004E
; 0007 00C7 test = FALSE ;                      /* write data to adreg */
	__GETWRN 18,19,0
; 0007 00C8 }
; 0007 00C9 if ( !Eeprom(rx_buff[pointer+2]>>1, READ_APPREG) ) {
_0xE004E:
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(195)
	CALL _Eeprom
	SBIW R30,0
	BREQ PC+3
	JMP _0xE004F
; 0007 00CA test = FALSE ;                          /* Read data from adreg */
	__GETWRN 18,19,0
; 0007 00CB }
; 0007 00CC for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
_0xE004F:
	__GETWRN 16,17,0
_0xE0051:
	__CPWRN 16,17,40
	BRLO PC+3
	JMP _0xE0052
; 0007 00CD if ( d_buff[i] != packed_data[rx_buff[pointer+2]>>1][i] ) {
	MOVW R26,R28
	ADIW R26,8
	ADD  R26,R16
	ADC  R27,R17
	LD   R22,X
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	LDI  R26,LOW(40)
	LDI  R27,HIGH(40)
	CALL __MULW12U
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	ADD  R30,R16
	ADC  R31,R17
	LD   R30,Z
	CP   R30,R22
	BRNE PC+3
	JMP _0xE0053
; 0007 00CE test = FALSE;                                  /*compare buffer */
	__GETWRN 18,19,0
; 0007 00CF }
; 0007 00D0 }
_0xE0053:
_0xE0050:
	__ADDWRN 16,17,1
	RJMP _0xE0051
_0xE0052:
; 0007 00D1 } else {
	RJMP _0xE0054
_0xE004A:
; 0007 00D2 test = FALSE ;
	__GETWRN 18,19,0
; 0007 00D3 }
_0xE0054:
; 0007 00D4 if ( !sendtail ) {                                /* make header ? */
	LDS  R30,_sendtail
	CPI  R30,0
	BREQ PC+3
	JMP _0xE0055
; 0007 00D5 BuildHeader() ;                             /* Build send packet header */
	CALL _BuildHeader
; 0007 00D6 sendtail |= MAKE ;                      /* build tail*/
	LDS  R30,_sendtail
	ORI  R30,1
	STS  _sendtail,R30
; 0007 00D7 }
; 0007 00D8 if ( !(sendtail & TX_ERR) )
_0xE0055:
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE0056
; 0007 00D9 {
; 0007 00DA tx_buff[tx_indx++] = TX_WRITE_ADR ;     /* Command  */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(43)
	STD  Z+0,R26
; 0007 00DB tx_buff[tx_indx++] = 1 ;                    /* One data byte  */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(1)
	STD  Z+0,R26
; 0007 00DC if ( test == TRUE )
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R18
	CPC  R31,R19
	BREQ PC+3
	JMP _0xE0057
; 0007 00DD {
; 0007 00DE if (    (rx_buff[pointer+3] == 'L')
; 0007 00DF && (rx_buff[pointer+4] == 'O')
; 0007 00E0 && (rx_buff[pointer+5] == 'C')
; 0007 00E1 && (rx_buff[pointer+6] == 'K') )
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,3
	LD   R26,Z
	CPI  R26,LOW(0x4C)
	BREQ PC+3
	JMP _0xE0059
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,4
	LD   R26,Z
	CPI  R26,LOW(0x4F)
	BREQ PC+3
	JMP _0xE0059
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,5
	LD   R26,Z
	CPI  R26,LOW(0x43)
	BREQ PC+3
	JMP _0xE0059
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,6
	LD   R26,Z
	CPI  R26,LOW(0x4B)
	BREQ PC+3
	JMP _0xE0059
	RJMP _0xE005A
_0xE0059:
	RJMP _0xE0058
_0xE005A:
; 0007 00E2 {     /* LOCK AP? */
; 0007 00E3 test = FALSE ;
	__GETWRN 18,19,0
; 0007 00E4 if ( Eeprom(rx_buff[pointer+2]>>1, LOCK_APP) )
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(90)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0xE005B
; 0007 00E5 {   /* LOCK APP REG. */
; 0007 00E6 test = TRUE ;
	__GETWRN 18,19,1
; 0007 00E7 
; 0007 00E8 }
; 0007 00E9 if ( test == TRUE ) {
_0xE005B:
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R18
	CPC  R31,R19
	BREQ PC+3
	JMP _0xE005C
; 0007 00EA tx_buff[tx_indx++] = 0 ;                /* Write status code OK*/
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(0)
	STD  Z+0,R26
; 0007 00EB }
; 0007 00EC else {
	RJMP _0xE005D
_0xE005C:
; 0007 00ED tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL*/
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(1)
	STD  Z+0,R26
; 0007 00EE }
_0xE005D:
; 0007 00EF 
; 0007 00F0 }
; 0007 00F1 else if (  (rx_buff[pointer+3] == 'U')
	RJMP _0xE005E
_0xE0058:
; 0007 00F2 && (rx_buff[pointer+4] == 'N')
; 0007 00F3 && (rx_buff[pointer+5] == 'L')
; 0007 00F4 && (rx_buff[pointer+6] == 'O')
; 0007 00F5 && (rx_buff[pointer+7] == 'C')
; 0007 00F6 && (rx_buff[pointer+8] == 'K') )
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,3
	LD   R26,Z
	CPI  R26,LOW(0x55)
	BREQ PC+3
	JMP _0xE0060
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,4
	LD   R26,Z
	CPI  R26,LOW(0x4E)
	BREQ PC+3
	JMP _0xE0060
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,5
	LD   R26,Z
	CPI  R26,LOW(0x4C)
	BREQ PC+3
	JMP _0xE0060
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,6
	LD   R26,Z
	CPI  R26,LOW(0x4F)
	BREQ PC+3
	JMP _0xE0060
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,7
	LD   R26,Z
	CPI  R26,LOW(0x43)
	BREQ PC+3
	JMP _0xE0060
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,8
	LD   R26,Z
	CPI  R26,LOW(0x4B)
	BREQ PC+3
	JMP _0xE0060
	RJMP _0xE0061
_0xE0060:
	RJMP _0xE005F
_0xE0061:
; 0007 00F7 {     /* UNLOCK AP? */
; 0007 00F8 test = TRUE ;
	__GETWRN 18,19,1
; 0007 00F9 SerielNummerLock= UNLOCK_BYTE;
	LDI  R26,LOW(_SerielNummerLock)
	LDI  R27,HIGH(_SerielNummerLock)
	LDI  R30,LOW(170)
	CALL __EEPROMWRB
; 0007 00FA EEpromStatusByte=DEFAULT_EEPROM_STATUS;
	LDI  R26,LOW(_EEpromStatusByte)
	LDI  R27,HIGH(_EEpromStatusByte)
	LDI  R30,LOW(0)
	CALL __EEPROMWRB
; 0007 00FB if ( test == TRUE ) {
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R18
	CPC  R31,R19
	BREQ PC+3
	JMP _0xE0062
; 0007 00FC tx_buff[tx_indx++] = 0 ;                /* Write status code OK*/
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(0)
	STD  Z+0,R26
; 0007 00FD }
; 0007 00FE else {
	RJMP _0xE0063
_0xE0062:
; 0007 00FF tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL*/
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(1)
	STD  Z+0,R26
; 0007 0100 }
_0xE0063:
; 0007 0101 }
; 0007 0102 else
	RJMP _0xE0064
_0xE005F:
; 0007 0103 {
; 0007 0104 tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(1)
	STD  Z+0,R26
; 0007 0105 }
_0xE0064:
_0xE005E:
; 0007 0106 
; 0007 0107 if ( test == TRUE ) {
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R18
	CPC  R31,R19
	BREQ PC+3
	JMP _0xE0065
; 0007 0108 tx_buff[tx_indx++] = 0 ;                /* Write status code OK*/
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(0)
	STD  Z+0,R26
; 0007 0109 } else {
	RJMP _0xE0066
_0xE0065:
; 0007 010A tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL*/
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(1)
	STD  Z+0,R26
; 0007 010B }
_0xE0066:
; 0007 010C }
; 0007 010D else
	RJMP _0xE0067
_0xE0057:
; 0007 010E {   tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(1)
	STD  Z+0,R26
; 0007 010F }
_0xE0067:
; 0007 0110 }
; 0007 0111 break ;
_0xE0056:
	RJMP _0xE0005
; 0007 0112 case SEND_EEP_DATA :
_0xE0049:
	CPI  R30,LOW(0x18)
	LDI  R26,HIGH(0x18)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0068
; 0007 0113 if ( !sendtail ) {                                /* make header ? */
	LDS  R30,_sendtail
	CPI  R30,0
	BREQ PC+3
	JMP _0xE0069
; 0007 0114 BuildHeader() ;                             /* Build send packet header */
	CALL _BuildHeader
; 0007 0115 sendtail |= MAKE ;                      /* build tail*/
	LDS  R30,_sendtail
	ORI  R30,1
	STS  _sendtail,R30
; 0007 0116 }
; 0007 0117 if ( (sendtail & TX_ERR) ||
_0xE0069:
; 0007 0118 ((TX_SIZE - tx_indx) < PACKED_DATA_SIZE ) ) {
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE006B
	LDS  R30,_tx_indx
	LDI  R31,0
	LDI  R26,LOW(200)
	LDI  R27,HIGH(200)
	SUB  R26,R30
	SBC  R27,R31
	SBIW R26,40
	BRGE PC+3
	JMP _0xE006B
	RJMP _0xE006A
_0xE006B:
; 0007 0119 sendtail |= TX_ERR ;
	LDS  R30,_sendtail
	ORI  R30,2
	STS  _sendtail,R30
; 0007 011A } else {
	RJMP _0xE006D
_0xE006A:
; 0007 011B BuildEepData(rx_buff[pointer+2]) ;  /* Build eeprom data for a channel*/
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R26,Z
	CALL _BuildEepData
; 0007 011C }
_0xE006D:
; 0007 011D break ;
	RJMP _0xE0005
; 0007 011E case CMD_READ_EEP :
_0xE0068:
	CPI  R30,LOW(0x19)
	LDI  R26,HIGH(0x19)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE006E
; 0007 011F eep_type[rx_buff[pointer+2]>>1] |= 0x20 ;     /* Error before read */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	MOVW R26,R30
	LD   R30,X
	ORI  R30,0x20
	ST   X,R30
; 0007 0120 eep_type[rx_buff[pointer+2]>>1] &= ~0x10 ;
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	MOVW R26,R30
	LD   R30,X
	ANDI R30,0xEF
	ST   X,R30
; 0007 0121 if ( Eeprom(rx_buff[pointer+2]>>1, COPY_NV_SP) ) {
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(240)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0xE006F
; 0007 0122 if ( Eeprom(rx_buff[pointer+2]>>1, READ_SP) ) {
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(170)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0xE0070
; 0007 0123 if ( Eeprom(rx_buff[pointer+2]>>1, READ_APPREG) ) {
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(195)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0xE0071
; 0007 0124 if ( CheckADData(&packed_data[rx_buff[pointer+2]>>1][0]) &&
; 0007 0125 CheckEepData(&packed_data[rx_buff[pointer+2]>>1][8]) ) { /*check checksum */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	LDI  R26,LOW(40)
	LDI  R27,HIGH(40)
	CALL __MULW12U
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	MOVW R26,R30
	CALL _CheckADData
	CPI  R30,0
	BRNE PC+3
	JMP _0xE0073
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	LDI  R26,LOW(40)
	LDI  R27,HIGH(40)
	CALL __MULW12U
	__ADDW1MN _packed_data,8
	MOVW R26,R30
	CALL _CheckEepData
	CPI  R30,0
	BRNE PC+3
	JMP _0xE0073
	RJMP _0xE0074
_0xE0073:
	RJMP _0xE0072
_0xE0074:
; 0007 0126 eep_type[rx_buff[pointer+2]>>1] |= 0x10 ;     /* OK from eeprom */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	MOVW R26,R30
	LD   R30,X
	ORI  R30,0x10
	ST   X,R30
; 0007 0127 eep_type[rx_buff[pointer+2]>>1] &= ~0x20 ;     /* Error from eeprom */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	MOVW R26,R30
	LD   R30,X
	ANDI R30,0xDF
	ST   X,R30
; 0007 0128 }
; 0007 0129 }
_0xE0072:
; 0007 012A }
_0xE0071:
; 0007 012B }
_0xE0070:
; 0007 012C break ;
_0xE006F:
	RJMP _0xE0005
; 0007 012D case REC_FILTER :
_0xE006E:
	CPI  R30,LOW(0x1A)
	LDI  R26,HIGH(0x1A)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0075
; 0007 012E p_filter = rx_buff[pointer+2] ;
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	STS  _p_filter,R30
; 0007 012F t_filter = rx_buff[pointer+3] ;
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,3
	LD   R30,Z
	STS  _t_filter,R30
; 0007 0130 o_filter = rx_buff[pointer+4] ;                     /* set new filter */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,4
	LD   R30,Z
	STS  _o_filter,R30
; 0007 0131 break ;                    /* press, temp, other */
	RJMP _0xE0005
; 0007 0132 case SEND_CARD_STAT :
_0xE0075:
	CPI  R30,LOW(0x1B)
	LDI  R26,HIGH(0x1B)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0076
; 0007 0133 if ( !sendtail ) {                                /* make header ? */
	LDS  R30,_sendtail
	CPI  R30,0
	BREQ PC+3
	JMP _0xE0077
; 0007 0134 BuildHeader() ;                             /* Build send packet header */
	CALL _BuildHeader
; 0007 0135 sendtail |= MAKE ;                      /* build tail*/
	LDS  R30,_sendtail
	ORI  R30,1
	STS  _sendtail,R30
; 0007 0136 }
; 0007 0137 if ( !(sendtail & TX_ERR) ) {
_0xE0077:
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE0078
; 0007 0138 BuildCSData() ;                             /* Build datablock for status */
	CALL _BuildCSData
; 0007 0139 }
; 0007 013A break ;
_0xE0078:
	RJMP _0xE0005
; 0007 013B case SEND_SER_NO :                              /* Serial no from eeprom */
_0xE0076:
	CPI  R30,LOW(0x1C)
	LDI  R26,HIGH(0x1C)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0079
; 0007 013C if ( !sendtail ) {                                /* make header ? */
	LDS  R30,_sendtail
	CPI  R30,0
	BREQ PC+3
	JMP _0xE007A
; 0007 013D BuildHeader() ;                             /* Build send packet header */
	CALL _BuildHeader
; 0007 013E sendtail |= MAKE ;                      /* build tail*/
	LDS  R30,_sendtail
	ORI  R30,1
	STS  _sendtail,R30
; 0007 013F }
; 0007 0140 if ( !(sendtail & TX_ERR) )
_0xE007A:
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	BREQ PC+3
	JMP _0xE007B
; 0007 0141 {
; 0007 0142 tx_buff[tx_indx++] = TX_SER_NO ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(48)
	STD  Z+0,R26
; 0007 0143 tx_buff[tx_indx++] = 10 ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(10)
	STD  Z+0,R26
; 0007 0144 tx_buff[tx_indx++] = rx_buff[pointer+2] ; /*channel no */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R26,R30
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	ST   X,R30
; 0007 0145 if ( Eeprom(rx_buff[pointer+2]>>1, READ_ROM) )
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(51)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0xE007C
; 0007 0146 {  /* EEP serial number */
; 0007 0147 tx_indx += 8 ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(8)
	STS  _tx_indx,R30
; 0007 0148 if ( Eeprom(rx_buff[pointer+2]>>1, READ_STATUS) ) { /* EEP status register */
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	__ADDW1MN _rx_buff,2
	LD   R30,Z
	LSR  R30
	ST   -Y,R30
	LDI  R26,LOW(102)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0xE007D
; 0007 0149 tx_buff[tx_indx++] = eep_status ;    /* status */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDS  R26,_eep_status
	STD  Z+0,R26
; 0007 014A } else {
	RJMP _0xE007E
_0xE007D:
; 0007 014B tx_buff[tx_indx++] = 0x0f ;          /* status */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(15)
	STD  Z+0,R26
; 0007 014C }
_0xE007E:
; 0007 014D }
; 0007 014E else
	RJMP _0xE007F
_0xE007C:
; 0007 014F {
; 0007 0150 for ( i = 0; i < 9; i++ )
	__GETWRN 16,17,0
_0xE0081:
	__CPWRN 16,17,9
	BRLO PC+3
	JMP _0xE0082
; 0007 0151 {
; 0007 0152 tx_buff[tx_indx++] = 0x00 ;             /*  send 0's when error */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(0)
	STD  Z+0,R26
; 0007 0153 }
_0xE0080:
	__ADDWRN 16,17,1
	RJMP _0xE0081
_0xE0082:
; 0007 0154 }
_0xE007F:
; 0007 0155 }
; 0007 0156 break ;
_0xE007B:
	RJMP _0xE0005
; 0007 0157 case SEND_ACK :                                     /* No more data, send ack. */
_0xE0079:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BREQ PC+3
	JMP _0xE0083
; 0007 0158 case NO_MORE_DATA :                             /* No more data */
	RJMP _0xE0084
_0xE0083:
	SBIW R30,0
	BREQ PC+3
	JMP _0xE0089
_0xE0084:
; 0007 0159 if ( sendtail )
	LDS  R30,_sendtail
	CPI  R30,0
	BRNE PC+3
	JMP _0xE0086
; 0007 015A {
; 0007 015B if ( rx_buff[pointer] == SEND_ACK )
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R26,Z
	CPI  R26,LOW(0x1)
	BREQ PC+3
	JMP _0xE0087
; 0007 015C {
; 0007 015D BuildTail(TX_ACK, sendtail & TX_ERR) ;  /* Build t. w/ err code */
	LDI  R30,LOW(5)
	ST   -Y,R30
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	MOV  R26,R30
	CALL _BuildTail
; 0007 015E }
; 0007 015F else
	RJMP _0xE0088
_0xE0087:
; 0007 0160 {
; 0007 0161 BuildTail(NO_MORE_DATA,  sendtail & TX_ERR) ;/* Build tail */
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDS  R30,_sendtail
	ANDI R30,LOW(0x2)
	MOV  R26,R30
	CALL _BuildTail
; 0007 0162 }
_0xE0088:
; 0007 0163 }
; 0007 0164 ret_val = FALSE ;
_0xE0086:
	__GETWRN 20,21,0
; 0007 0165 break ;
	RJMP _0xE0005
; 0007 0166 default:                                                /* I don't understand this */
_0xE0089:
; 0007 0167 break ;
; 0007 0168 }
_0xE0005:
; 0007 0169 return ret_val ;
	MOVW R30,R20
	CALL __LOADLOCR6
	ADIW R28,50
	RET
; 0007 016A }
; .FEND
;void BuildHeader(void)
; 0007 0173 {
_BuildHeader:
; .FSTART _BuildHeader
; 0007 0174 tx_indx = 0;
	LDI  R30,LOW(0)
	STS  _tx_indx,R30
; 0007 0175 
; 0007 0176 tx_buff[tx_indx++] = STX ;                  /* STX */
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(2)
	STD  Z+0,R26
; 0007 0177 tx_buff[tx_indx++] = STX ;                  /* STX */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	STD  Z+0,R26
; 0007 0178 tx_buff[tx_indx++] = rx_buff[rx_start+1] ; /* Rx address */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R26,R30
	LDS  R30,_rx_start
	LDI  R31,0
	__ADDW1MN _rx_buff,1
	LD   R30,Z
	ST   X,R30
; 0007 0179 tx_buff[tx_indx++] = MYADRESS_LOCAL ;           /* Tx address */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(9)
	STD  Z+0,R26
; 0007 017A tx_buff[tx_indx++] = 0 ;                          /* packlen HB, dont know yet */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(0)
	STD  Z+0,R26
; 0007 017B tx_buff[tx_indx++] = 0 ;                     /* packlen LB, dont know yet */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	STD  Z+0,R26
; 0007 017C }
	RET
; .FEND
;void BuildMPData(void)
; 0007 0184 {
_BuildMPData:
; .FSTART _BuildMPData
; 0007 0185 
; 0007 0186 short i, ntna;
; 0007 0187 char senddata[4] ;
; 0007 0188 
; 0007 0189 tx_buff[tx_indx++] = TX_MP_DATA ;           /* action */
	SBIW R28,4
	CALL __SAVELOCR4
;	i -> R16,R17
;	ntna -> R18,R19
;	senddata -> Y+4
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(30)
	STD  Z+0,R26
; 0007 018A ntna = tx_indx++ ;                                  /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R18,R30
	CLR  R19
; 0007 018B for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 16,17,0
_0xE008B:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xE008C
; 0007 018C if ( (ch_stat[i] & 0x0c) == 0x0c ) {    /* find pressure sensors */
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0xC)
	CPI  R30,LOW(0xC)
	BREQ PC+3
	JMP _0xE008D
; 0007 018D *((float*)&senddata[0]) = mes_data[i] ;       /* data */
	MOVW R30,R16
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	__PUTD1S 4
; 0007 018E tx_buff[tx_indx++] = i ;                /* channel number */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R16
; 0007 018F tx_buff[tx_indx++] = (ch_stat[i]   ) ;     /* cal/conv status */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 0190 //            tx_buff[tx_indx++] = senddata[3] ;
; 0007 0191 //            tx_buff[tx_indx++] = senddata[2] ;
; 0007 0192 //            tx_buff[tx_indx++] = senddata[1] ;
; 0007 0193 //            tx_buff[tx_indx++] = senddata[0] ;
; 0007 0194 tx_buff[tx_indx++] = senddata[0] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+4
	STD  Z+0,R26
; 0007 0195 tx_buff[tx_indx++] = senddata[1] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+5
	STD  Z+0,R26
; 0007 0196 tx_buff[tx_indx++] = senddata[2] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+6
	STD  Z+0,R26
; 0007 0197 tx_buff[tx_indx++] = senddata[3] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+7
	STD  Z+0,R26
; 0007 0198 }
; 0007 0199 }
_0xE008D:
_0xE008A:
	__ADDWRN 16,17,1
	RJMP _0xE008B
_0xE008C:
; 0007 019A tx_buff[ntna] = tx_indx - ntna - 1  ;                /* length of data block */
	MOVW R30,R18
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R18
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 019B }
	CALL __LOADLOCR4
	ADIW R28,8
	RET
; .FEND
;void BuildMTData(void)
; 0007 01A3 {
_BuildMTData:
; .FSTART _BuildMTData
; 0007 01A4 
; 0007 01A5 short i, ntna;
; 0007 01A6 char senddata[4];
; 0007 01A7 
; 0007 01A8 tx_buff[tx_indx++] = TX_MT_DATA ;           /* action */
	SBIW R28,4
	CALL __SAVELOCR4
;	i -> R16,R17
;	ntna -> R18,R19
;	senddata -> Y+4
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(31)
	STD  Z+0,R26
; 0007 01A9 ntna = tx_indx++ ;                                  /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R18,R30
	CLR  R19
; 0007 01AA for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 16,17,0
_0xE008F:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xE0090
; 0007 01AB if ( (ch_stat[i] & 0x0c)  == 0x04 ) {    /* find temperature sensors */
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0xC)
	CPI  R30,LOW(0x4)
	BREQ PC+3
	JMP _0xE0091
; 0007 01AC *((float*)&senddata[0]) = mes_data[i] ;      /* data */
	MOVW R30,R16
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	__PUTD1S 4
; 0007 01AD tx_buff[tx_indx++] = i ;                /* channel number */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R16
; 0007 01AE tx_buff[tx_indx++] = ( ch_stat[i]  ) ;     /* cal/conv status */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 01AF //            tx_buff[tx_indx++] = senddata[3] ;
; 0007 01B0 //            tx_buff[tx_indx++] = senddata[2] ;
; 0007 01B1 //            tx_buff[tx_indx++] = senddata[1] ;
; 0007 01B2 //            tx_buff[tx_indx++] = senddata[0] ;
; 0007 01B3 
; 0007 01B4 tx_buff[tx_indx++] = senddata[0] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+4
	STD  Z+0,R26
; 0007 01B5 tx_buff[tx_indx++] = senddata[1] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+5
	STD  Z+0,R26
; 0007 01B6 tx_buff[tx_indx++] = senddata[2] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+6
	STD  Z+0,R26
; 0007 01B7 tx_buff[tx_indx++] = senddata[3] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+7
	STD  Z+0,R26
; 0007 01B8 }
; 0007 01B9 }
_0xE0091:
_0xE008E:
	__ADDWRN 16,17,1
	RJMP _0xE008F
_0xE0090:
; 0007 01BA tx_buff[ntna] = tx_indx - ntna - 1 ;                /* length of data block */
	MOVW R30,R18
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R18
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 01BB }
	CALL __LOADLOCR4
	ADIW R28,8
	RET
; .FEND
;void BuildMOData(void)
; 0007 01C3 {
_BuildMOData:
; .FSTART _BuildMOData
; 0007 01C4 
; 0007 01C5 short i, ntna;
; 0007 01C6 char senddata[4] ;
; 0007 01C7 
; 0007 01C8 tx_buff[tx_indx++] = TX_MO_DATA ;           /* action */
	SBIW R28,4
	CALL __SAVELOCR4
;	i -> R16,R17
;	ntna -> R18,R19
;	senddata -> Y+4
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(32)
	STD  Z+0,R26
; 0007 01C9 ntna = tx_indx++ ;                                  /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R18,R30
	CLR  R19
; 0007 01CA for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 16,17,0
_0xE0093:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xE0094
; 0007 01CB if ( (ch_stat[i] & 0x0c)  == 0x08 ) {    /* find other sensors */
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0xC)
	CPI  R30,LOW(0x8)
	BREQ PC+3
	JMP _0xE0095
; 0007 01CC *((float*)&senddata[0]) = mes_data[i] ;                               /* data */
	MOVW R30,R16
	LDI  R26,LOW(_mes_data)
	LDI  R27,HIGH(_mes_data)
	CALL __LSLW2
	ADD  R26,R30
	ADC  R27,R31
	__GETD1P_INC
	__PUTD1S 4
; 0007 01CD tx_buff[tx_indx++] = i ;                /* channel number */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R16
; 0007 01CE tx_buff[tx_indx++] = ch_stat[i] ;     /* cal/conv status */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 01CF //            tx_buff[tx_indx++] = senddata[3] ;
; 0007 01D0 //            tx_buff[tx_indx++] = senddata[2] ;
; 0007 01D1 //            tx_buff[tx_indx++] = senddata[1] ;
; 0007 01D2 //            tx_buff[tx_indx++] = senddata[0] ;
; 0007 01D3 tx_buff[tx_indx++] = senddata[0] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+4
	STD  Z+0,R26
; 0007 01D4 tx_buff[tx_indx++] = senddata[1] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+5
	STD  Z+0,R26
; 0007 01D5 tx_buff[tx_indx++] = senddata[2] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+6
	STD  Z+0,R26
; 0007 01D6 tx_buff[tx_indx++] = senddata[3] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+7
	STD  Z+0,R26
; 0007 01D7 }
; 0007 01D8 }
_0xE0095:
_0xE0092:
	__ADDWRN 16,17,1
	RJMP _0xE0093
_0xE0094:
; 0007 01D9 tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
	MOVW R30,R18
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R18
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 01DA }
	CALL __LOADLOCR4
	ADIW R28,8
	RET
; .FEND
;void BuildWHData(void)
; 0007 01E5 {
_BuildWHData:
; .FSTART _BuildWHData
; 0007 01E6 short ntna, i ;
; 0007 01E7 /*  // AN-SGCNV_EXT not connected
; 0007 01E8 if ( P7DR & 0x80 )
; 0007 01E9 {
; 0007 01EA return;
; 0007 01EB }
; 0007 01EC */
; 0007 01ED if (SELECT_EXTBOARD_1 ==1)  // AN-SGCNV_EXT not connected
	CALL __SAVELOCR4
;	ntna -> R16,R17
;	i -> R18,R19
	LDS  R30,1128
	ANDI R30,LOW(0x1)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0xE0096
; 0007 01EE {    return;
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; 0007 01EF }
; 0007 01F0 else {
_0xE0096:
; 0007 01F1 tx_buff[tx_indx++] = TX_WH_DATA ;               // action
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(49)
	STD  Z+0,R26
; 0007 01F2 ntna = tx_indx++ ;                              // remember index
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R16,R30
	CLR  R17
; 0007 01F3 for ( i = 0; i< NOWT; i++ ) {
	__GETWRN 18,19,0
_0xE0099:
	__CPWRN 18,19,4
	BRLO PC+3
	JMP _0xE009A
; 0007 01F4 unsigned short WTCnt = washtrac[i];
; 0007 01F5 washtrac[i] = 0;
	SBIW R28,2
;	WTCnt -> Y+0
	MOVW R30,R18
	LDI  R26,LOW(_washtrac)
	LDI  R27,HIGH(_washtrac)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	ST   Y,R30
	STD  Y+1,R31
	MOVW R30,R18
	LDI  R26,LOW(_washtrac)
	LDI  R27,HIGH(_washtrac)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	ST   X+,R30
	ST   X,R31
; 0007 01F6 tx_buff[tx_indx++] = WTCnt & 0xff;         // add washtrack
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R26,R30
	LD   R30,Y
	ST   X,R30
; 0007 01F7 tx_buff[tx_indx++] = (WTCnt >> 8) & 0xff;         // add washtrack
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R26,R30
	LDD  R30,Y+1
	ANDI R31,HIGH(0x0)
	ST   X,R30
; 0007 01F8 }
	ADIW R28,2
_0xE0098:
	__ADDWRN 18,19,1
	RJMP _0xE0099
_0xE009A:
; 0007 01F9 tx_buff[tx_indx++] = highlevel;                 // add highlevel
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDS  R26,_highlevel
	STD  Z+0,R26
; 0007 01FA {
; 0007 01FB unsigned short TNow = ms_cnt;
; 0007 01FC ms_cnt = 0;
	SBIW R28,2
;	TNow -> Y+0
	LDS  R30,_ms_cnt
	LDS  R31,_ms_cnt+1
	ST   Y,R30
	STD  Y+1,R31
	LDI  R30,LOW(0)
	STS  _ms_cnt,R30
	STS  _ms_cnt+1,R30
; 0007 01FD tx_buff[tx_indx++] = TNow & 0xff;               // add washtrack
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R26,R30
	LD   R30,Y
	ST   X,R30
; 0007 01FE tx_buff[tx_indx++] = (TNow >> 8) & 0xff;        // add washtrack
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R26,R30
	LDD  R30,Y+1
	ANDI R31,HIGH(0x0)
	ST   X,R30
; 0007 01FF }
	ADIW R28,2
; 0007 0200 tx_buff[ntna] = tx_indx - ntna - 1 ;            // length of data block
	MOVW R30,R16
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R16
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 0201 }
_0xE0097:
; 0007 0202 }
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
;void BuildRPData(void)
; 0007 020A {
_BuildRPData:
; .FSTART _BuildRPData
; 0007 020B 
; 0007 020C short i, ntna ;
; 0007 020D //    char senddata[2];
; 0007 020E 
; 0007 020F tx_buff[tx_indx++] = TX_RP_DATA ;           /* action */
	CALL __SAVELOCR4
;	i -> R16,R17
;	ntna -> R18,R19
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(33)
	STD  Z+0,R26
; 0007 0210 ntna = tx_indx++ ;                                  /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R18,R30
	CLR  R19
; 0007 0211 for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 16,17,0
_0xE009C:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xE009D
; 0007 0212 if ( (ch_stat[i] & 0x0c) == 0x0c )
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0xC)
	CPI  R30,LOW(0xC)
	BREQ PC+3
	JMP _0xE009E
; 0007 0213 {    /* find pressure sensors */
; 0007 0214 //            char *senddata = (char*)&raw_data[i] ;                           /* data */
; 0007 0215 tx_buff[tx_indx++] = i ;                /* channel number */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R16
; 0007 0216 tx_buff[tx_indx++] = ch_stat[i] ;     /* cal/conv status */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 0217 //            tx_buff[tx_indx++] = senddata[1] ;            /* data  LB */
; 0007 0218 //            tx_buff[tx_indx++] = senddata[0] ;            /* data  HB */
; 0007 0219 tx_buff[tx_indx++] = raw_data[i]&0x00ff ;            /* data  LB */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	MOVW R30,R16
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 021A tx_buff[tx_indx++] = raw_data[i] >>8 ;            /* data  HB */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	MOVW R30,R16
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	MOV  R30,R31
	LDI  R31,0
	MOVW R26,R0
	ST   X,R30
; 0007 021B }
; 0007 021C }
_0xE009E:
_0xE009B:
	__ADDWRN 16,17,1
	RJMP _0xE009C
_0xE009D:
; 0007 021D tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
	MOVW R30,R18
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R18
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 021E }
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
;void BuildRTData(void)
; 0007 0226 {
_BuildRTData:
; .FSTART _BuildRTData
; 0007 0227 
; 0007 0228 short i, ntna ;
; 0007 0229 //    char senddata[2];
; 0007 022A 
; 0007 022B tx_buff[tx_indx++] = TX_RT_DATA ;           /* action */
	CALL __SAVELOCR4
;	i -> R16,R17
;	ntna -> R18,R19
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(34)
	STD  Z+0,R26
; 0007 022C ntna = tx_indx++ ;                                  /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R18,R30
	CLR  R19
; 0007 022D for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 16,17,0
_0xE00A0:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xE00A1
; 0007 022E if ( (ch_stat[i] & 0x0c)  == 0x04 ) {    /* find temperature sensors */
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0xC)
	CPI  R30,LOW(0x4)
	BREQ PC+3
	JMP _0xE00A2
; 0007 022F //            *((short*)&senddata[0]) = raw_data[i] ;                           /* data */
; 0007 0230 tx_buff[tx_indx++] = i ;                /* channel number */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R16
; 0007 0231 tx_buff[tx_indx++] = ch_stat[i] ;     /* cal/conv status */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 0232 tx_buff[tx_indx++] = raw_data[i]&0x00ff ;            /* data  LB */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	MOVW R30,R16
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 0233 tx_buff[tx_indx++] = raw_data[i] >>8 ;            /* data  HB */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	MOVW R30,R16
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	MOV  R30,R31
	LDI  R31,0
	MOVW R26,R0
	ST   X,R30
; 0007 0234 
; 0007 0235 //            tx_buff[tx_indx++] = senddata[0] ;            /* data  HB */
; 0007 0236 //            tx_buff[tx_indx++] = senddata[1] ;            /* data  LB */
; 0007 0237 }
; 0007 0238 }
_0xE00A2:
_0xE009F:
	__ADDWRN 16,17,1
	RJMP _0xE00A0
_0xE00A1:
; 0007 0239 tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
	MOVW R30,R18
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R18
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 023A }
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
;void BuildROData(void)
; 0007 0242 {
_BuildROData:
; .FSTART _BuildROData
; 0007 0243 
; 0007 0244 short i, ntna ;
; 0007 0245 //    char senddata[2];
; 0007 0246 
; 0007 0247 tx_buff[tx_indx++] = TX_RO_DATA ;           /* action */
	CALL __SAVELOCR4
;	i -> R16,R17
;	ntna -> R18,R19
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(35)
	STD  Z+0,R26
; 0007 0248 ntna = tx_indx++ ;                                  /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R18,R30
	CLR  R19
; 0007 0249 for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 16,17,0
_0xE00A4:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xE00A5
; 0007 024A if ( (ch_stat[i] & 0x0c)  == 0x08 ) {    /* find other sensors */
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0xC)
	CPI  R30,LOW(0x8)
	BREQ PC+3
	JMP _0xE00A6
; 0007 024B //            *((short*)&senddata[0]) = raw_data[i] ;                           /* data */
; 0007 024C tx_buff[tx_indx++] = i ;                /* channel number */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R16
; 0007 024D tx_buff[tx_indx++] = ch_stat[i] ;     /* cal/conv status */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 024E //            tx_buff[tx_indx++] = senddata[1] ;            /* data  LB */
; 0007 024F //            tx_buff[tx_indx++] = senddata[0] ;            /* data  HB */
; 0007 0250 tx_buff[tx_indx++] = raw_data[i]&0x00ff ;            /* data  LB */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	MOVW R30,R16
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 0251 tx_buff[tx_indx++] = raw_data[i] >>8 ;            /* data  HB */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	MOVW R30,R16
	LDI  R26,LOW(_raw_data)
	LDI  R27,HIGH(_raw_data)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	MOV  R30,R31
	LDI  R31,0
	MOVW R26,R0
	ST   X,R30
; 0007 0252 
; 0007 0253 }
; 0007 0254 }
_0xE00A6:
_0xE00A3:
	__ADDWRN 16,17,1
	RJMP _0xE00A4
_0xE00A5:
; 0007 0255 tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
	MOVW R30,R18
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R18
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 0256 }
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
;void BuildCalData(void)
; 0007 025E {
_BuildCalData:
; .FSTART _BuildCalData
; 0007 025F 
; 0007 0260 short i, ntna ;
; 0007 0261 //    char  senddata[2];
; 0007 0262 
; 0007 0263 tx_buff[tx_indx++] = TX_CAL_DATA ;              /* action */
	CALL __SAVELOCR4
;	i -> R16,R17
;	ntna -> R18,R19
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(36)
	STD  Z+0,R26
; 0007 0264 ntna = tx_indx++ ;                                  /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R18,R30
	CLR  R19
; 0007 0265 for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 16,17,0
_0xE00A8:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xE00A9
; 0007 0266 //       *((short*)&senddata[0]) = cal_data[i] ;   /* data */
; 0007 0267 tx_buff[tx_indx++] = i ;                        /* channel number */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R16
; 0007 0268 tx_buff[tx_indx++] = ch_stat[i] ;             /* cal status */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 0269 tx_buff[tx_indx++] = cal_data[i]&0x00ff ;            /* data  LB */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	MOVW R30,R16
	LDI  R26,LOW(_cal_data)
	LDI  R27,HIGH(_cal_data)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 026A tx_buff[tx_indx++] = cal_data[i] >>8 ;            /* data  HB */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	MOVW R30,R16
	LDI  R26,LOW(_cal_data)
	LDI  R27,HIGH(_cal_data)
	LSL  R30
	ROL  R31
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X+
	LD   R31,X+
	MOV  R30,R31
	LDI  R31,0
	MOVW R26,R0
	ST   X,R30
; 0007 026B 
; 0007 026C }
_0xE00A7:
	__ADDWRN 16,17,1
	RJMP _0xE00A8
_0xE00A9:
; 0007 026D tx_buff[ntna] = tx_indx - ntna - 1  ;             /* length of data block */
	MOVW R30,R18
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R18
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 026E }
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
;void BuildConfData(void)
; 0007 0276 {
_BuildConfData:
; .FSTART _BuildConfData
; 0007 0277 
; 0007 0278 short i, ntna ;
; 0007 0279 
; 0007 027A tx_buff[tx_indx++] = TX_CONFIG ;                  /* action */
	CALL __SAVELOCR4
;	i -> R16,R17
;	ntna -> R18,R19
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(37)
	STD  Z+0,R26
; 0007 027B ntna = tx_indx++ ;                                /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R18,R30
	CLR  R19
; 0007 027C for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 16,17,0
_0xE00AB:
	__CPWRN 16,17,14
	BRLO PC+3
	JMP _0xE00AC
; 0007 027D tx_buff[tx_indx++] = i ;                      /* channel number */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R16
; 0007 027E tx_buff[tx_indx++] = ch_stat[i] ;             /* channel setup */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R0,R30
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0007 027F tx_buff[tx_indx++] = eep_type[i >> 1] ;           /* eeprom setup */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R26,R30
	MOVW R30,R16
	LSR  R31
	ROR  R30
	SUBI R30,LOW(-_eep_type)
	SBCI R31,HIGH(-_eep_type)
	LD   R30,Z
	ST   X,R30
; 0007 0280 }
_0xE00AA:
	__ADDWRN 16,17,1
	RJMP _0xE00AB
_0xE00AC:
; 0007 0281 tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
	MOVW R30,R18
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R18
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 0282 }
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
;void BuildEepData(unsigned char channel)
; 0007 028A {
_BuildEepData:
; .FSTART _BuildEepData
; 0007 028B 
; 0007 028C short i, ntna;
; 0007 028D tx_buff[tx_indx++] = TX_EEP_DATA ;              /* action */
	CALL __SAVELOCR6
	MOV  R21,R26
;	channel -> R21
;	i -> R16,R17
;	ntna -> R18,R19
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(44)
	STD  Z+0,R26
; 0007 028E ntna = tx_indx++ ;                                  /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R18,R30
	CLR  R19
; 0007 028F tx_buff[tx_indx++] = channel ;          /* channel number */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R21
; 0007 0290 channel >>= 1 ;
	LSR  R21
; 0007 0291 for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
	__GETWRN 16,17,0
_0xE00AE:
	__CPWRN 16,17,40
	BRLO PC+3
	JMP _0xE00AF
; 0007 0292 tx_buff[tx_indx++] = packed_data[channel][i]; /* data */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDI  R26,LOW(40)
	MUL  R21,R26
	MOVW R30,R0
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	ADD  R30,R16
	ADC  R31,R17
	LD   R30,Z
	MOVW R26,R22
	ST   X,R30
; 0007 0293 }
_0xE00AD:
	__ADDWRN 16,17,1
	RJMP _0xE00AE
_0xE00AF:
; 0007 0294 tx_buff[ntna] = tx_indx - ntna - 1  ;      /* length of data block */
	MOVW R30,R18
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R18
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 0295 ch_stat[channel << 1]  &= ~0x80 ;                  /* Release new sensor flag */
	MOV  R30,R21
	LDI  R31,0
	LSL  R30
	ROL  R31
	SUBI R30,LOW(-_ch_stat)
	SBCI R31,HIGH(-_ch_stat)
	MOVW R26,R30
	LD   R30,X
	ANDI R30,0x7F
	ST   X,R30
; 0007 0296 }
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; .FEND
;void BuildCSData(void)
; 0007 029E {
_BuildCSData:
; .FSTART _BuildCSData
; 0007 029F 
; 0007 02A0 short ntna ;
; 0007 02A1 char senddata[4] ;
; 0007 02A2 
; 0007 02A3 tx_buff[tx_indx++] = TX_CARD_STAT ;         /* action */
	SBIW R28,4
	ST   -Y,R17
	ST   -Y,R16
;	ntna -> R16,R17
;	senddata -> Y+2
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(47)
	STD  Z+0,R26
; 0007 02A4 ntna = tx_indx++ ;                                  /* remember index */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	MOV  R16,R30
	CLR  R17
; 0007 02A5 tx_buff[tx_indx++] = (unsigned char) VERSION; /* software version */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(14)
	STD  Z+0,R26
; 0007 02A6 //    tx_buff[tx_indx] = GetMyAddress();        /* get the address */
; 0007 02A7 tx_buff[tx_indx] = MYADRESS_LOCAL;        /* get the address */
	LDS  R30,_tx_indx
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(9)
	STD  Z+0,R26
; 0007 02A8 
; 0007 02A9 if ( ad_mode & 0x10 ) {
	LDS  R30,_ad_mode
	ANDI R30,LOW(0x10)
	BRNE PC+3
	JMP _0xE00B0
; 0007 02AA tx_buff[tx_indx] |= 0x80 ;                   /* restart flag */
	LDS  R26,_tx_indx
	LDI  R27,0
	SUBI R26,LOW(-_tx_buff)
	SBCI R27,HIGH(-_tx_buff)
	LD   R30,X
	ORI  R30,0x80
	ST   X,R30
; 0007 02AB }
; 0007 02AC tx_indx++  ;
_0xE00B0:
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
; 0007 02AD ad_mode &= ~0x10 ;                                   /* reset restart flag */
	LDS  R30,_ad_mode
	ANDI R30,0xEF
	STS  _ad_mode,R30
; 0007 02AE tx_buff[tx_indx++] = (unsigned char) RX_SIZE; /* rx buffer size */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(200)
	STD  Z+0,R26
; 0007 02AF tx_buff[tx_indx++] = (unsigned char) TX_SIZE; /* tx buffer size */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	STD  Z+0,R26
; 0007 02B0 tx_buff[tx_indx++] = (unsigned char) cal_zero ;     /* cal zero */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDS  R26,_cal_zero
	STD  Z+0,R26
; 0007 02B1 tx_buff[tx_indx++] = (unsigned char) cal_zero >> 8 ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDI  R30,LOW(8)
	CALL __LSRB12
	MOVW R26,R22
	ST   X,R30
; 0007 02B2 
; 0007 02B3 *((float*)&senddata[0]) = cal_gain ;              /* calibration gain */
	LDS  R30,_cal_gain
	LDS  R31,_cal_gain+1
	LDS  R22,_cal_gain+2
	LDS  R23,_cal_gain+3
	__PUTD1S 2
; 0007 02B4 //    tx_buff[tx_indx++] = senddata[3] ;
; 0007 02B5 //    tx_buff[tx_indx++] = senddata[2] ;
; 0007 02B6 //    tx_buff[tx_indx++] = senddata[1] ;
; 0007 02B7 //    tx_buff[tx_indx++] = senddata[0] ;
; 0007 02B8 tx_buff[tx_indx++] = senddata[0] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+2
	STD  Z+0,R26
; 0007 02B9 tx_buff[tx_indx++] = senddata[1] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+3
	STD  Z+0,R26
; 0007 02BA tx_buff[tx_indx++] = senddata[2] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+4
	STD  Z+0,R26
; 0007 02BB tx_buff[tx_indx++] = senddata[3] ;
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDD  R26,Y+5
	STD  Z+0,R26
; 0007 02BC 
; 0007 02BD tx_buff[ntna] = tx_indx - ntna - 1 ;                /* length of data block */
	MOVW R30,R16
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R22,R30
	LDS  R26,_tx_indx
	SUB  R26,R16
	LDI  R30,LOW(1)
	CALL __SWAPB12
	SUB  R30,R26
	MOVW R26,R22
	ST   X,R30
; 0007 02BE }
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,6
	RET
; .FEND
;void BuildTail(unsigned char type, unsigned char error)
; 0007 02C6 {  unsigned char tmp_crc;
_BuildTail:
; .FSTART _BuildTail
; 0007 02C7 
; 0007 02C8 tx_buff[tx_indx++] = type ;                 /* action end */
	CALL __SAVELOCR4
	MOV  R16,R26
	LDD  R19,Y+4
;	type -> R19
;	error -> R16
;	tmp_crc -> R17
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R19
; 0007 02C9 tx_buff[tx_indx++] = error ;                /* error code */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R16
; 0007 02CA 
; 0007 02CB tx_buff[4] = tx_indx >> 8 ;                /* packet len high */
	LDS  R26,_tx_indx
	LDI  R30,LOW(8)
	CALL __LSRB12
	__PUTB1MN _tx_buff,4
; 0007 02CC tx_buff[5] = tx_indx ;                          /* correct length because stx's*/
	LDS  R30,_tx_indx
	__PUTB1MN _tx_buff,5
; 0007 02CD tmp_crc=CalcTxChecksum(tx_indx);
	CLR  R27
	CALL _CalcTxChecksum
	MOV  R17,R30
; 0007 02CE //    BuffCRC[BuffCRC_Index]=tmp_crc;
; 0007 02CF //    BuffCRC_Index++;
; 0007 02D0 //    tx_buff[tx_indx++] = CalcTxChecksum(tx_indx) ; /* Get checksum */
; 0007 02D1 tx_buff[tx_indx++] = tmp_crc ; /* Get checksum */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	ST   Z,R17
; 0007 02D2 
; 0007 02D3 tx_buff[tx_indx++] = ETX ;                  /* ETX */
	LDS  R30,_tx_indx
	SUBI R30,-LOW(1)
	STS  _tx_indx,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	LDI  R26,LOW(3)
	STD  Z+0,R26
; 0007 02D4 
; 0007 02D5 tx_bytes = tx_indx;                         /*bytes to send */
	LDS  R30,_tx_indx
	STS  _tx_bytes,R30
; 0007 02D6 tx_indx = 0;                                    /* reset cunter */
	LDI  R30,LOW(0)
	STS  _tx_indx,R30
; 0007 02D7 tx_complete = FALSE;
	STS  _tx_complete,R30
; 0007 02D8 wait_for_pc = PC_SLOW;                      /* delay before send */
	LDI  R30,LOW(20)
	STS  _wait_for_pc,R30
; 0007 02D9 TxDriver(ON);                                   /* driver on */
	LDI  R26,LOW(1)
	CALL _TxDriver
; 0007 02DA Led(1, ON) ;
	LDI  R30,LOW(1)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _Led
; 0007 02DB }
	CALL __LOADLOCR4
	ADIW R28,5
	RET
; .FEND
;void RecEepData(unsigned int pointer)
; 0007 02E3 {
_RecEepData:
; .FSTART _RecEepData
; 0007 02E4 
; 0007 02E5 short i, ch ;
; 0007 02E6 //    unsigned char temp_data[PACKED_DATA_SIZE];
; 0007 02E7 unsigned char   *e_data, *a_data ;
; 0007 02E8 
; 0007 02E9 ch = (rx_buff[pointer++] >> 1 ) ;                               /* get channel */
	ST   -Y,R27
	ST   -Y,R26
	SBIW R28,2
	CALL __SAVELOCR6
;	pointer -> Y+8
;	i -> R16,R17
;	ch -> R18,R19
;	*e_data -> R20,R21
;	*a_data -> Y+6
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	ADIW R30,1
	STD  Y+8,R30
	STD  Y+8+1,R31
	SBIW R30,1
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R30,Z
	LDI  R31,0
	ASR  R31
	ROR  R30
	MOVW R18,R30
; 0007 02EA a_data = &rx_buff[pointer] ;
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	STD  Y+6,R30
	STD  Y+6+1,R31
; 0007 02EB e_data = &rx_buff[pointer + 8] ;
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	__ADDW1MN _rx_buff,8
	MOVW R20,R30
; 0007 02EC 
; 0007 02ED if ( CheckEepData(e_data) && CheckADData(a_data) &&
; 0007 02EE (rx_buff[pointer + PACKED_DATA_SIZE] & 0x01) ) { /* check legale packet */
	MOVW R26,R20
	CALL _CheckEepData
	CPI  R30,0
	BRNE PC+3
	JMP _0xE00B2
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	CALL _CheckADData
	CPI  R30,0
	BRNE PC+3
	JMP _0xE00B2
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	__ADDW1MN _rx_buff,40
	LD   R30,Z
	ANDI R30,LOW(0x1)
	BRNE PC+3
	JMP _0xE00B2
	RJMP _0xE00B3
_0xE00B2:
	RJMP _0xE00B1
_0xE00B3:
; 0007 02EF for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
	__GETWRN 16,17,0
_0xE00B5:
	__CPWRN 16,17,40
	BRLO PC+3
	JMP _0xE00B6
; 0007 02F0 packed_data[ch][i] = rx_buff[pointer++];            /* copy data */
	__MULBNWRU 18,19,40
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	ADD  R30,R16
	ADC  R31,R17
	MOVW R26,R30
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	ADIW R30,1
	STD  Y+8,R30
	STD  Y+8+1,R31
	SBIW R30,1
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R30,Z
	ST   X,R30
; 0007 02F1 }
_0xE00B4:
	__ADDWRN 16,17,1
	RJMP _0xE00B5
_0xE00B6:
; 0007 02F2 eep_type[ch] &= ~0x0f ;
	MOVW R26,R18
	SUBI R26,LOW(-_eep_type)
	SBCI R27,HIGH(-_eep_type)
	LD   R30,X
	ANDI R30,LOW(0xF0)
	ST   X,R30
; 0007 02F3 eep_type[ch] |= 0x09 ;               /* use PC data */
	MOVW R26,R18
	SUBI R26,LOW(-_eep_type)
	SBCI R27,HIGH(-_eep_type)
	LD   R30,X
	ORI  R30,LOW(0x9)
	ST   X,R30
; 0007 02F4 } else {
	RJMP _0xE00B7
_0xE00B1:
; 0007 02F5 eep_type[ch] &= ~0x0f ;
	MOVW R26,R18
	SUBI R26,LOW(-_eep_type)
	SBCI R27,HIGH(-_eep_type)
	LD   R30,X
	ANDI R30,LOW(0xF0)
	ST   X,R30
; 0007 02F6 eep_type[ch] |= 0x02 ;                          /* fail from pc */
	MOVW R26,R18
	SUBI R26,LOW(-_eep_type)
	SBCI R27,HIGH(-_eep_type)
	LD   R30,X
	ORI  R30,2
	ST   X,R30
; 0007 02F7 }
_0xE00B7:
; 0007 02F8 }
	CALL __LOADLOCR6
	ADIW R28,10
	RET
; .FEND
;void RecOGData(unsigned char pointer)
; 0007 0301 {
_RecOGData:
; .FSTART _RecOGData
; 0007 0302 
; 0007 0303 short i, number, channel ;
; 0007 0304 float gai;
; 0007 0305 
; 0007 0306 number = rx_buff[++pointer] / 5 ;   /* number of channels (5 bytes each ch) */
	ST   -Y,R26
	SBIW R28,4
	CALL __SAVELOCR6
;	pointer -> Y+10
;	i -> R16,R17
;	number -> R18,R19
;	channel -> R20,R21
;	gai -> Y+6
	LDD  R30,Y+10
	SUBI R30,-LOW(1)
	STD  Y+10,R30
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(5)
	LDI  R31,HIGH(5)
	CALL __DIVW21
	MOVW R18,R30
; 0007 0307 for ( i = 0; i < number; i++ ) {
	__GETWRN 16,17,0
_0xE00B9:
	__CPWRR 16,17,18,19
	BRLO PC+3
	JMP _0xE00BA
; 0007 0308 channel = rx_buff[++pointer] ;         /* Remember channel */
	LDD  R30,Y+10
	SUBI R30,-LOW(1)
	STD  Y+10,R30
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R20,Z
	CLR  R21
; 0007 0309 /* Must be like this due to error in compiler, compiles from right to left!!! */
; 0007 030A offset[channel] = (rx_buff[++pointer] * 256) ;
	MOVW R30,R20
	LDI  R26,LOW(_offset)
	LDI  R27,HIGH(_offset)
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	MOVW R22,R30
	LDD  R30,Y+10
	SUBI R30,-LOW(1)
	STD  Y+10,R30
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R26,Z
	LDI  R27,0
	LDI  R30,LOW(256)
	LDI  R31,HIGH(256)
	CALL __MULW12
	MOVW R26,R22
	ST   X+,R30
	ST   X,R31
; 0007 030B offset[channel] += rx_buff[++pointer] ;
	MOVW R30,R20
	LDI  R26,LOW(_offset)
	LDI  R27,HIGH(_offset)
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	MOVW R0,R30
	MOVW R26,R30
	LD   R30,X+
	LD   R31,X+
	MOVW R26,R30
	LDD  R30,Y+10
	SUBI R30,-LOW(1)
	STD  Y+10,R30
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R30,Z
	LDI  R31,0
	ADD  R30,R26
	ADC  R31,R27
	MOVW R26,R0
	ST   X+,R30
	ST   X,R31
; 0007 030C /* Must be like this due to error in compiler, compiles from right to left!!! */
; 0007 030D gai = (float)(rx_buff[++pointer]) * 256.0 ;
	LDD  R30,Y+10
	SUBI R30,-LOW(1)
	STD  Y+10,R30
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R30,Z
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	__GETD2N 0x43800000
	CALL __MULF12
	__PUTD1S 6
; 0007 030E gai += (float)(rx_buff[++pointer]) ;
	LDD  R30,Y+10
	SUBI R30,-LOW(1)
	STD  Y+10,R30
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R30,Z
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __CDF1
	__GETD2S 6
	CALL __ADDF12
	__PUTD1S 6
; 0007 030F gain[channel] = 1.0 + (gai / 100000.0) ;   /*gain*/
	MOVW R30,R20
	LDI  R26,LOW(_gain)
	LDI  R27,HIGH(_gain)
	CALL __LSLW2
	ADD  R30,R26
	ADC  R31,R27
	PUSH R31
	PUSH R30
	__GETD2S 6
	__GETD1N 0x47C35000
	CALL __DIVF21
	__GETD2N 0x3F800000
	CALL __ADDF12
	POP  R26
	POP  R27
	__PUTDP1
; 0007 0310 }
_0xE00B8:
	__ADDWRN 16,17,1
	RJMP _0xE00B9
_0xE00BA:
; 0007 0311 }
	CALL __LOADLOCR6
	ADIW R28,11
	RET
; .FEND
;void RecSetupData(unsigned char pointer)
; 0007 031A {
_RecSetupData:
; .FSTART _RecSetupData
; 0007 031B unsigned char temp;
; 0007 031C short i, test ;
; 0007 031D unsigned char d_buff[PACKED_DATA_SIZE] ;
; 0007 031E 
; 0007 031F for ( i = 0; i < NOIOCH; i++ )
	SBIW R28,40
	CALL __SAVELOCR6
	MOV  R16,R26
;	pointer -> R16
;	temp -> R17
;	i -> R18,R19
;	test -> R20,R21
;	d_buff -> Y+6
	__GETWRN 18,19,0
_0xE00BC:
	__CPWRN 18,19,14
	BRLO PC+3
	JMP _0xE00BD
; 0007 0320 {
; 0007 0321 ch_stat[i] &= ~0x1c ;
	MOVW R26,R18
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	ANDI R30,LOW(0xE3)
	ST   X,R30
; 0007 0322 //        ch_stat[i] |= (rx_buff[pointer++] & 0x1c);  /* Setup for channel */
; 0007 0323 temp= rx_buff[pointer] & 0x1c;
	MOV  R30,R16
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R30,Z
	ANDI R30,LOW(0x1C)
	MOV  R17,R30
; 0007 0324 ch_stat[i] |= temp;  /* Setup for channel */
	MOVW R26,R18
	SUBI R26,LOW(-_ch_stat)
	SBCI R27,HIGH(-_ch_stat)
	LD   R30,X
	OR   R30,R17
	ST   X,R30
; 0007 0325 pointer++;
	SUBI R16,-1
; 0007 0326 }
_0xE00BB:
	__ADDWRN 18,19,1
	RJMP _0xE00BC
_0xE00BD:
; 0007 0327 if ( rx_buff[pointer] )
	MOV  R30,R16
	LDI  R31,0
	SUBI R30,LOW(-_rx_buff)
	SBCI R31,HIGH(-_rx_buff)
	LD   R30,Z
	CPI  R30,0
	BRNE PC+3
	JMP _0xE00BE
; 0007 0328 {
; 0007 0329 for ( i = 0; i < NOIOCH; i++ ) {
	__GETWRN 18,19,0
_0xE00C0:
	__CPWRN 18,19,14
	BRLO PC+3
	JMP _0xE00C1
; 0007 032A packed_data[7][i+8] = (ch_stat[i] & 0x0c) ; /* copy setup to eeprom */
	__POINTW2MN _packed_data,280
	MOVW R30,R18
	ADIW R30,8
	ADD  R30,R26
	ADC  R31,R27
	MOVW R0,R30
	LDI  R26,LOW(_ch_stat)
	LDI  R27,HIGH(_ch_stat)
	ADD  R26,R18
	ADC  R27,R19
	LD   R30,X
	ANDI R30,LOW(0xC)
	MOVW R26,R0
	ST   X,R30
; 0007 032B }
_0xE00BF:
	__ADDWRN 18,19,1
	RJMP _0xE00C0
_0xE00C1:
; 0007 032C MakeEepChksum(&packed_data[7][8]) ;
	__POINTW2MN _packed_data,288
	CALL _MakeEepChksum
; 0007 032D 
; 0007 032E for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
	__GETWRN 18,19,0
_0xE00C3:
	__CPWRN 18,19,40
	BRLO PC+3
	JMP _0xE00C4
; 0007 032F d_buff[i] = packed_data[7][i] ;                 /*copy buffer */
	MOVW R26,R28
	ADIW R26,6
	ADD  R26,R18
	ADC  R27,R19
	__POINTW1MN _packed_data,280
	ADD  R30,R18
	ADC  R31,R19
	LD   R30,Z
	ST   X,R30
; 0007 0330 }
_0xE00C2:
	__ADDWRN 18,19,1
	RJMP _0xE00C3
_0xE00C4:
; 0007 0331 test = TRUE ;
	__GETWRN 20,21,1
; 0007 0332 // Intern EEprom
; 0007 0333 if ( !Eeprom(7, WRITE_SP) ) {
	LDI  R30,LOW(7)
	ST   -Y,R30
	LDI  R26,LOW(15)
	CALL _Eeprom
	SBIW R30,0
	BREQ PC+3
	JMP _0xE00C5
; 0007 0334 test= FALSE ;                               /* write data to scratchpad */
	__GETWRN 20,21,0
; 0007 0335 }
; 0007 0336 if ( !Eeprom(7, READ_SP) ) {
_0xE00C5:
	LDI  R30,LOW(7)
	ST   -Y,R30
	LDI  R26,LOW(170)
	CALL _Eeprom
	SBIW R30,0
	BREQ PC+3
	JMP _0xE00C6
; 0007 0337 test = FALSE ;                          /* Read data from scratchpad */
	__GETWRN 20,21,0
; 0007 0338 }
; 0007 0339 for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
_0xE00C6:
	__GETWRN 18,19,0
_0xE00C8:
	__CPWRN 18,19,40
	BRLO PC+3
	JMP _0xE00C9
; 0007 033A if ( d_buff[i] != packed_data[7][i] ) {
	MOVW R26,R28
	ADIW R26,6
	ADD  R26,R18
	ADC  R27,R19
	LD   R26,X
	__POINTW1MN _packed_data,280
	ADD  R30,R18
	ADC  R31,R19
	LD   R30,Z
	CP   R30,R26
	BRNE PC+3
	JMP _0xE00CA
; 0007 033B test = FALSE;                                  /*compare buffer */
	__GETWRN 20,21,0
; 0007 033C }
; 0007 033D }
_0xE00CA:
_0xE00C7:
	__ADDWRN 18,19,1
	RJMP _0xE00C8
_0xE00C9:
; 0007 033E if ( test == TRUE ) {                             /* write to eep OK */
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R20
	CPC  R31,R21
	BREQ PC+3
	JMP _0xE00CB
; 0007 033F if ( Eeprom(7, COPY_SP_NV) ) {    /* copy data to NV-ram */
	LDI  R30,LOW(7)
	ST   -Y,R30
	LDI  R26,LOW(85)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0xE00CC
; 0007 0340 }
; 0007 0341 }
_0xE00CC:
; 0007 0342 }
_0xE00CB:
; 0007 0343 ad_state = IDLE ;                               /* Restart convertion */
_0xE00BE:
	LDI  R30,LOW(7)
	STS  _ad_state,R30
; 0007 0344 curr_ad_ch = NOIOCH  ;
	LDI  R30,LOW(14)
	STS  _curr_ad_ch,R30
; 0007 0345 ad_mode = 0x04 ;                            /* start with press.*/
	LDI  R30,LOW(4)
	STS  _ad_mode,R30
; 0007 0346 
; 0007 0347 }
	CALL __LOADLOCR6
	ADIW R28,46
	RET
; .FEND
;unsigned char CalcTxChecksum(unsigned int pack_len)
; 0007 034F {
_CalcTxChecksum:
; .FSTART _CalcTxChecksum
; 0007 0350 
; 0007 0351 unsigned int             cnt ;
; 0007 0352 unsigned char   csum ;
; 0007 0353 
; 0007 0354 csum = 0 ;
	CALL __SAVELOCR6
	MOVW R20,R26
;	pack_len -> R20,R21
;	cnt -> R16,R17
;	csum -> R19
	LDI  R19,LOW(0)
; 0007 0355 for ( cnt = 2 ; cnt < (pack_len) ; cnt++ )
	__GETWRN 16,17,2
_0xE00CE:
	__CPWRR 16,17,20,21
	BRLO PC+3
	JMP _0xE00CF
; 0007 0356 {
; 0007 0357 csum = crc[csum ^ tx_buff[cnt]] ;
	MOV  R0,R19
	CLR  R1
	LDI  R26,LOW(_tx_buff)
	LDI  R27,HIGH(_tx_buff)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	LDI  R31,0
	EOR  R30,R0
	EOR  R31,R1
	SUBI R30,LOW(-_crc*2)
	SBCI R31,HIGH(-_crc*2)
	LPM  R19,Z
; 0007 0358 }
_0xE00CD:
	__ADDWRN 16,17,1
	RJMP _0xE00CE
_0xE00CF:
; 0007 0359 return csum ;
	MOV  R30,R19
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; 0007 035A }
; .FEND
;unsigned int Eeprom(unsigned char channel, unsigned char command)
; 0008 0030 {

	.CSEG
_Eeprom:
; .FSTART _Eeprom
; 0008 0031 //if channel 7, read from EEprom
; 0008 0032 char   ret_val = FALSE;
; 0008 0033 unsigned char   *data ;
; 0008 0034 unsigned char i;
; 0008 0035 unsigned char value;
; 0008 0036 unsigned char localCRC;
; 0008 0037 if ( channel==7)    // intern eeprom
	ST   -Y,R26
	CALL __SAVELOCR6
;	channel -> Y+7
;	command -> Y+6
;	ret_val -> R17
;	*data -> R18,R19
;	i -> R16
;	value -> R21
;	localCRC -> R20
	LDI  R17,0
	LDD  R26,Y+7
	CPI  R26,LOW(0x7)
	BREQ PC+3
	JMP _0x100003
; 0008 0038 {
; 0008 0039 switch ( command ) {          /* find command */
	LDD  R30,Y+6
	LDI  R31,0
; 0008 003A case READ_SP :          /* read scratchpad */
	CPI  R30,LOW(0xAA)
	LDI  R26,HIGH(0xAA)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100007
; 0008 003B data = &packed_data[channel][8] ;   /* nvram block */
	LDD  R30,Y+7
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,8
	MOVW R18,R30
; 0008 003C for ( i =0; i < 32;i++)
	LDI  R16,LOW(0)
_0x100009:
	CPI  R16,32
	BRLO PC+3
	JMP _0x10000A
; 0008 003D {   *data++ = EEpromScratchpad[i];
	PUSH R19
	PUSH R18
	__ADDWRN 18,19,1
	MOV  R26,R16
	LDI  R27,0
	SUBI R26,LOW(-_EEpromScratchpad)
	SBCI R27,HIGH(-_EEpromScratchpad)
	CALL __EEPROMRDB
	POP  R26
	POP  R27
	ST   X,R30
; 0008 003E }
_0x100008:
	SUBI R16,-1
	RJMP _0x100009
_0x10000A:
; 0008 003F ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 0040 break ;
	RJMP _0x100006
; 0008 0041 case WRITE_SP :         /* write scratchpad */
_0x100007:
	CPI  R30,LOW(0xF)
	LDI  R26,HIGH(0xF)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x10000B
; 0008 0042 data = &packed_data[channel][8] ;   /* nvram block */
	LDD  R30,Y+7
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,8
	MOVW R18,R30
; 0008 0043 for ( i =0; i < 32;i++)
	LDI  R16,LOW(0)
_0x10000D:
	CPI  R16,32
	BRLO PC+3
	JMP _0x10000E
; 0008 0044 {   EEpromScratchpad[i] =*data++;
	MOV  R30,R16
	LDI  R31,0
	SUBI R30,LOW(-_EEpromScratchpad)
	SBCI R31,HIGH(-_EEpromScratchpad)
	MOVW R0,R30
	MOVW R26,R18
	__ADDWRN 18,19,1
	LD   R30,X
	MOVW R26,R0
	CALL __EEPROMWRB
; 0008 0045 }
_0x10000C:
	SUBI R16,-1
	RJMP _0x10000D
_0x10000E:
; 0008 0046 break ;
	RJMP _0x100006
; 0008 0047 case READ_STATUS :          /* Read status register */
_0x10000B:
	CPI  R30,LOW(0x66)
	LDI  R26,HIGH(0x66)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x10000F
; 0008 0048 data = &eep_status ;                        /* status */
	__POINTWRM 18,19,_eep_status
; 0008 0049 *data = EEpromStatusByte;          // eeprom status   status
	LDI  R26,LOW(_EEpromStatusByte)
	LDI  R27,HIGH(_EEpromStatusByte)
	CALL __EEPROMRDB
	MOVW R26,R18
	ST   X,R30
; 0008 004A ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 004B break ;
	RJMP _0x100006
; 0008 004C case COPY_SP_NV :                                   /* Copy scrpad to eeprom */
_0x10000F:
	CPI  R30,LOW(0x55)
	LDI  R26,HIGH(0x55)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100010
; 0008 004D ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 004E break ;
	RJMP _0x100006
; 0008 004F case COPY_NV_SP :                                   /* Copy eeprom to scrpad */
_0x100010:
	CPI  R30,LOW(0xF0)
	LDI  R26,HIGH(0xF0)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100011
; 0008 0050 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 0051 break ;
	RJMP _0x100006
; 0008 0052 case READ_APPREG :                          /* Read APP-REG */
_0x100011:
	CPI  R30,LOW(0xC3)
	LDI  R26,HIGH(0xC3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100012
; 0008 0053 data = &packed_data[channel][0] ;   /* ID-REG block */
	LDD  R30,Y+7
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	MOVW R18,R30
; 0008 0054 //ReadEepromData(data, 8) ;               /* Read 8 bytes */
; 0008 0055 localCRC=0;
	LDI  R20,LOW(0)
; 0008 0056 for ( i =0; i < 8;i++)
	LDI  R16,LOW(0)
_0x100014:
	CPI  R16,8
	BRLO PC+3
	JMP _0x100015
; 0008 0057 {   value=EESerielNummer[i];
	MOV  R26,R16
	LDI  R27,0
	SUBI R26,LOW(-_EESerielNummer)
	SBCI R27,HIGH(-_EESerielNummer)
	CALL __EEPROMRDB
	MOV  R21,R30
; 0008 0058 *data++ =value;
	PUSH R19
	PUSH R18
	__ADDWRN 18,19,1
	POP  R26
	POP  R27
	ST   X,R30
; 0008 0059 }
_0x100013:
	SUBI R16,-1
	RJMP _0x100014
_0x100015:
; 0008 005A // control CRC
; 0008 005B ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 005C break ;
	RJMP _0x100006
; 0008 005D case WRITE_APPREG :          /* Write ID-REG */
_0x100012:
	CPI  R30,LOW(0x99)
	LDI  R26,HIGH(0x99)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100016
; 0008 005E data = &packed_data[channel][0] ;    /* ID-REG block */
	LDD  R30,Y+7
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	MOVW R18,R30
; 0008 005F value= SerielNummerLock;        // Read Seriel nummer lockbyte.
	LDI  R26,LOW(_SerielNummerLock)
	LDI  R27,HIGH(_SerielNummerLock)
	CALL __EEPROMRDB
	MOV  R21,R30
; 0008 0060 if ( value != LOCK_BYTE )   // can write Seriem Nummer if not lock
	CPI  R21,85
	BRNE PC+3
	JMP _0x100017
; 0008 0061 {   localCRC=0;
	LDI  R20,LOW(0)
; 0008 0062 for ( i =0; i < 8;i++)
	LDI  R16,LOW(0)
_0x100019:
	CPI  R16,8
	BRLO PC+3
	JMP _0x10001A
; 0008 0063 {   value=*data++;
	MOVW R26,R18
	__ADDWRN 18,19,1
	LD   R21,X
; 0008 0064 EESerielNummer[i]=value;
	MOV  R26,R16
	LDI  R27,0
	SUBI R26,LOW(-_EESerielNummer)
	SBCI R27,HIGH(-_EESerielNummer)
	MOV  R30,R21
	CALL __EEPROMWRB
; 0008 0065 localCRC= crc[ localCRC ^value ];
	MOV  R26,R20
	CLR  R27
	LDI  R31,0
	EOR  R30,R26
	EOR  R31,R27
	SUBI R30,LOW(-_crc*2)
	SBCI R31,HIGH(-_crc*2)
	LPM  R20,Z
; 0008 0066 }
_0x100018:
	SUBI R16,-1
	RJMP _0x100019
_0x10001A:
; 0008 0067 EESerielNummerCRC=localCRC;
	MOV  R30,R20
	LDI  R26,LOW(_EESerielNummerCRC)
	LDI  R27,HIGH(_EESerielNummerCRC)
	CALL __EEPROMWRB
; 0008 0068 SerielNummerLock= LOCK_BYTE;    // lock Seriel nummer
	LDI  R26,LOW(_SerielNummerLock)
	LDI  R27,HIGH(_SerielNummerLock)
	LDI  R30,LOW(85)
	CALL __EEPROMWRB
; 0008 0069 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 006A }
; 0008 006B //else {} Return False
; 0008 006C break ;
_0x100017:
	RJMP _0x100006
; 0008 006D case LOCK_APP :              /* Lock data in ID-Reg */
_0x100016:
	CPI  R30,LOW(0x5A)
	LDI  R26,HIGH(0x5A)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x10001B
; 0008 006E // if CRC ok lock data
; 0008 006F localCRC=0;
	LDI  R20,LOW(0)
; 0008 0070 for ( i =0; i < 8;i++)
	LDI  R16,LOW(0)
_0x10001D:
	CPI  R16,8
	BRLO PC+3
	JMP _0x10001E
; 0008 0071 {   value=EESerielNummer[i];
	MOV  R26,R16
	LDI  R27,0
	SUBI R26,LOW(-_EESerielNummer)
	SBCI R27,HIGH(-_EESerielNummer)
	CALL __EEPROMRDB
	MOV  R21,R30
; 0008 0072 localCRC= crc[ localCRC ^value ];
	MOV  R26,R20
	CLR  R27
	LDI  R31,0
	EOR  R30,R26
	EOR  R31,R27
	SUBI R30,LOW(-_crc*2)
	SBCI R31,HIGH(-_crc*2)
	LPM  R20,Z
; 0008 0073 }
_0x10001C:
	SUBI R16,-1
	RJMP _0x10001D
_0x10001E:
; 0008 0074 value=EESerielNummerCRC;
	LDI  R26,LOW(_EESerielNummerCRC)
	LDI  R27,HIGH(_EESerielNummerCRC)
	CALL __EEPROMRDB
	MOV  R21,R30
; 0008 0075 if (localCRC==value)
	CP   R21,R20
	BREQ PC+3
	JMP _0x10001F
; 0008 0076 {   SerielNummerLock= LOCK_BYTE;    // lock Seriel nummer
	LDI  R26,LOW(_SerielNummerLock)
	LDI  R27,HIGH(_SerielNummerLock)
	LDI  R30,LOW(85)
	CALL __EEPROMWRB
; 0008 0077 EEpromStatusByte=PROGRAMED_EEPROM_STATUS;
	LDI  R26,LOW(_EEpromStatusByte)
	LDI  R27,HIGH(_EEpromStatusByte)
	LDI  R30,LOW(15)
	CALL __EEPROMWRB
; 0008 0078 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 0079 }
; 0008 007A 
; 0008 007B break ;
_0x10001F:
	RJMP _0x100006
; 0008 007C case READ_ROM :          /* Read id from eeprom */
_0x10001B:
	CPI  R30,LOW(0x33)
	LDI  R26,HIGH(0x33)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100024
; 0008 007D data = &tx_buff[tx_indx] ;                  /* Tx buffer */
	LDS  R30,_tx_indx
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R18,R30
; 0008 007E //ReadEepromData(data, 8) ;            /* Read 8 bytes */
; 0008 007F for ( i =0; i < 8;i++)
	LDI  R16,LOW(0)
_0x100022:
	CPI  R16,8
	BRLO PC+3
	JMP _0x100023
; 0008 0080 {   value=EEpromDallasSN[i];
	MOV  R26,R16
	LDI  R27,0
	SUBI R26,LOW(-_EEpromDallasSN)
	SBCI R27,HIGH(-_EEpromDallasSN)
	CALL __EEPROMRDB
	MOV  R21,R30
; 0008 0081 *data++ =value;
	PUSH R19
	PUSH R18
	__ADDWRN 18,19,1
	POP  R26
	POP  R27
	ST   X,R30
; 0008 0082 }
_0x100021:
	SUBI R16,-1
	RJMP _0x100022
_0x100023:
; 0008 0083 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 0084 
; 0008 0085 break ;
	RJMP _0x100006
; 0008 0086 default :
_0x100024:
; 0008 0087 break ;
; 0008 0088 }
_0x100006:
; 0008 0089 }
; 0008 008A else
	RJMP _0x100025
_0x100003:
; 0008 008B {
; 0008 008C 
; 0008 008D SetCalResistance(OHM_1R) ;                      /* use 1 ohm res. on return. */
	LDI  R26,LOW(64)
	CALL _SetCalResistance
; 0008 008E SetEepromChannel(channel) ;                 /* connect to the right eeprom && Set GND*/
	LDD  R26,Y+7
	CALL _SetEepromChannel
; 0008 008F SetMuxChannel(MUXCHOFF) ;                       /* mux channel off */
	LDI  R26,LOW(16)
	CALL _SetMuxChannel
; 0008 0090 SetSupplyChannel(SUPPCHOFF) ;                   /* set channel off */
	LDI  R26,LOW(16)
	CALL _SetSupplyChannel
; 0008 0091 SetSupplyCurrent(1);                                /* set 1mA supply */
	LDI  R26,LOW(1)
	CALL _SetSupplyCurrent
; 0008 0092 delay_ms(5);    //OneMsecDelay(5) ;                       /* supply the unit before read */
	LDI  R26,LOW(5)
	LDI  R27,0
	CALL _delay_ms
; 0008 0093 set_interrupt_mask(1);                          /* Disable interrupt */
	LDI  R26,LOW(1)
	CALL _set_interrupt_mask
; 0008 0094 #asm("wdr");    //KickDog() ; /* kick dog due to long read time*/
	WDR
; 0008 0095 
; 0008 0096 switch ( command ) {          /* find command */
	LDD  R30,Y+6
	LDI  R31,0
; 0008 0097 case READ_SP :          /* read scratchpad */
	CPI  R30,LOW(0xAA)
	LDI  R26,HIGH(0xAA)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100029
; 0008 0098 if ( SendEepromCommand(command, 0, 1) ) { /* Start at adderss 0 */
	LDD  R30,Y+6
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _SendEepromCommand
	CPI  R30,0
	BRNE PC+3
	JMP _0x10002A
; 0008 0099 data = &packed_data[channel][8] ;   /* nvram block */
	LDD  R30,Y+7
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,8
	MOVW R18,R30
; 0008 009A ReadEepromData(data, 32)    ;           /* Read 32 bytes */
	ST   -Y,R19
	ST   -Y,R18
	LDI  R26,LOW(32)
	CALL _ReadEepromData
; 0008 009B ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 009C }
; 0008 009D break ;
_0x10002A:
	RJMP _0x100028
; 0008 009E case WRITE_SP :         /* write scratchpad */
_0x100029:
	CPI  R30,LOW(0xF)
	LDI  R26,HIGH(0xF)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x10002B
; 0008 009F if ( SendEepromCommand(command, 0, 1) ) { /* Start at adderss 0 */
	LDD  R30,Y+6
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _SendEepromCommand
	CPI  R30,0
	BRNE PC+3
	JMP _0x10002C
; 0008 00A0 data = &packed_data[channel][8] ;   /* nvram block */
	LDD  R30,Y+7
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	__ADDW1MN _packed_data,8
	MOVW R18,R30
; 0008 00A1 WriteEepromData(data, 32)   ;           /* Write 32 bytes */
	ST   -Y,R19
	ST   -Y,R18
	LDI  R26,LOW(32)
	CALL _WriteEepromData
; 0008 00A2 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 00A3 }
; 0008 00A4 break ;
_0x10002C:
	RJMP _0x100028
; 0008 00A5 case READ_STATUS :          /* Read status register */
_0x10002B:
	CPI  R30,LOW(0x66)
	LDI  R26,HIGH(0x66)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x10002D
; 0008 00A6 if ( SendEepromCommand(command, 0, 1) ) {  /* Command 0 */
	LDD  R30,Y+6
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _SendEepromCommand
	CPI  R30,0
	BRNE PC+3
	JMP _0x10002E
; 0008 00A7 data = &eep_status ;                        /* status */
	__POINTWRM 18,19,_eep_status
; 0008 00A8 ReadEepromData(data, 1) ;               /* Read 1 bytes */
	ST   -Y,R19
	ST   -Y,R18
	LDI  R26,LOW(1)
	CALL _ReadEepromData
; 0008 00A9 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 00AA }
; 0008 00AB break ;
_0x10002E:
	RJMP _0x100028
; 0008 00AC case COPY_SP_NV :                                   /* Copy scrpad to eeprom */
_0x10002D:
	CPI  R30,LOW(0x55)
	LDI  R26,HIGH(0x55)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x10002F
; 0008 00AD if ( SendEepromCommand(command, 0xa5, 1) ) {
	LDD  R30,Y+6
	ST   -Y,R30
	LDI  R30,LOW(165)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _SendEepromCommand
	CPI  R30,0
	BRNE PC+3
	JMP _0x100030
; 0008 00AE set_interrupt_mask(0);                  /* Enable interrupt due to*/
	LDI  R26,LOW(0)
	CALL _set_interrupt_mask
; 0008 00AF delay_ms (100); //OneMsecDelay(100) ;   /* the 100 ms delay */
	LDI  R26,LOW(100)
	LDI  R27,0
	CALL _delay_ms
; 0008 00B0 
; 0008 00B1 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 00B2 }
; 0008 00B3 break ;
_0x100030:
	RJMP _0x100028
; 0008 00B4 case COPY_NV_SP :                                   /* Copy eeprom to scrpad */
_0x10002F:
	CPI  R30,LOW(0xF0)
	LDI  R26,HIGH(0xF0)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100031
; 0008 00B5 if ( SendEepromCommand(command, 0, 1) ) {
	LDD  R30,Y+6
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _SendEepromCommand
	CPI  R30,0
	BRNE PC+3
	JMP _0x100032
; 0008 00B6 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 00B7 }
; 0008 00B8 break ;
_0x100032:
	RJMP _0x100028
; 0008 00B9 case READ_APPREG :                          /* Read APP-REG */
_0x100031:
	CPI  R30,LOW(0xC3)
	LDI  R26,HIGH(0xC3)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100033
; 0008 00BA if ( SendEepromCommand(command, 0, 1) ) {     /* Start at addrss 0 */
	LDD  R30,Y+6
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _SendEepromCommand
	CPI  R30,0
	BRNE PC+3
	JMP _0x100034
; 0008 00BB data = &packed_data[channel][0] ;   /* ID-REG block */
	LDD  R30,Y+7
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	MOVW R18,R30
; 0008 00BC ReadEepromData(data, 8) ;               /* Read 8 bytes */
	ST   -Y,R19
	ST   -Y,R18
	LDI  R26,LOW(8)
	CALL _ReadEepromData
; 0008 00BD ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 00BE }
; 0008 00BF break ;
_0x100034:
	RJMP _0x100028
; 0008 00C0 case WRITE_APPREG :          /* Write ID-REG */
_0x100033:
	CPI  R30,LOW(0x99)
	LDI  R26,HIGH(0x99)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100035
; 0008 00C1 if ( SendEepromCommand(command, 0, 1) ) {  /* Start at addrss 0 */
	LDD  R30,Y+6
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _SendEepromCommand
	CPI  R30,0
	BRNE PC+3
	JMP _0x100036
; 0008 00C2 data = &packed_data[channel][0] ;    /* ID-REG block */
	LDD  R30,Y+7
	LDI  R26,LOW(40)
	MUL  R30,R26
	MOVW R30,R0
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	MOVW R18,R30
; 0008 00C3 WriteEepromData(data, 8)    ;            /* Write 8 bytes */
	ST   -Y,R19
	ST   -Y,R18
	LDI  R26,LOW(8)
	CALL _WriteEepromData
; 0008 00C4 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 00C5 }
; 0008 00C6 break ;
_0x100036:
	RJMP _0x100028
; 0008 00C7 case LOCK_APP :              /* Lock data in ID-Reg */
_0x100035:
	CPI  R30,LOW(0x5A)
	LDI  R26,HIGH(0x5A)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x100037
; 0008 00C8 if ( SendEepromCommand(command, 0xa5, 1) ) { /* Command importent */
	LDD  R30,Y+6
	ST   -Y,R30
	LDI  R30,LOW(165)
	ST   -Y,R30
	LDI  R26,LOW(1)
	CALL _SendEepromCommand
	CPI  R30,0
	BRNE PC+3
	JMP _0x100038
; 0008 00C9 set_interrupt_mask(0);                  /* Enable interrupt due to*/
	LDI  R26,LOW(0)
	CALL _set_interrupt_mask
; 0008 00CA delay_ms(100);          //OneMsecDelay(100) ;  /* the 100 ms delay */
	LDI  R26,LOW(100)
	LDI  R27,0
	CALL _delay_ms
; 0008 00CB ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 00CC }
; 0008 00CD break ;
_0x100038:
	RJMP _0x100028
; 0008 00CE case READ_ROM :          /* Read id from eeprom */
_0x100037:
	CPI  R30,LOW(0x33)
	LDI  R26,HIGH(0x33)
	CPC  R31,R26
	BREQ PC+3
	JMP _0x10003B
; 0008 00CF if ( SendEepromCommand(command, 0, -1) ) {     /* No skip rom command!! */
	LDD  R30,Y+6
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(255)
	CALL _SendEepromCommand
	CPI  R30,0
	BRNE PC+3
	JMP _0x10003A
; 0008 00D0 data = &tx_buff[tx_indx] ;                  /* Tx buffer */
	LDS  R30,_tx_indx
	LDI  R31,0
	SUBI R30,LOW(-_tx_buff)
	SBCI R31,HIGH(-_tx_buff)
	MOVW R18,R30
; 0008 00D1 ReadEepromData(data, 8) ;            /* Read 8 bytes */
	ST   -Y,R19
	ST   -Y,R18
	LDI  R26,LOW(8)
	CALL _ReadEepromData
; 0008 00D2 ret_val = TRUE ;
	LDI  R17,LOW(1)
; 0008 00D3 }
; 0008 00D4 break ;
_0x10003A:
	RJMP _0x100028
; 0008 00D5 default :
_0x10003B:
; 0008 00D6 break ;
; 0008 00D7 }
_0x100028:
; 0008 00D8 set_interrupt_mask(0);                          /* Enable interrupt */
	LDI  R26,LOW(0)
	CALL _set_interrupt_mask
; 0008 00D9 SetSupplyCurrent(1);                                /* set 1mA supply */
	LDI  R26,LOW(1)
	CALL _SetSupplyCurrent
; 0008 00DA SetEepromChannel(EEPCHOFF) ;                    /* 9 = off */
	LDI  R26,LOW(9)
	CALL _SetEepromChannel
; 0008 00DB SetSupplyChannel(SUPPCHOFF) ;                   /* 16 = off */
	LDI  R26,LOW(16)
	CALL _SetSupplyChannel
; 0008 00DC SetCalResistance(OFF) ;                         /* Switch off cal. res. */
	LDI  R26,LOW(0)
	CALL _SetCalResistance
; 0008 00DD #asm("wdr");        //KickDog() ; /* kick dog due to long read time*/
	WDR
; 0008 00DE }
_0x100025:
; 0008 00DF return ret_val ;
	MOV  R30,R17
	LDI  R31,0
	CALL __LOADLOCR6
	ADIW R28,8
	RET
; 0008 00E0 }
; .FEND
;char SendEepromCommand(unsigned char command, unsigned char cmd_byte, unsigned char number)
; 0008 00E8 {
_SendEepromCommand:
; .FSTART _SendEepromCommand
; 0008 00E9 
; 0008 00EA 
; 0008 00EB //    if ( ResetEeprom() )
; 0008 00EC if ( ResetONEWIRE ())
	CALL __SAVELOCR4
	MOV  R17,R26
	LDD  R16,Y+4
	LDD  R19,Y+5
;	command -> R19
;	cmd_byte -> R16
;	number -> R17
	CALL _ResetONEWIRE
	CPI  R30,0
	BRNE PC+3
	JMP _0x10003C
; 0008 00ED {                /* Reset the chip */
; 0008 00EE if ( number != -1 )
	MOV  R26,R17
	LDI  R30,LOW(255)
	LDI  R27,0
	SER  R31
	CP   R30,R26
	CPC  R31,R27
	BRNE PC+3
	JMP _0x10003D
; 0008 00EF {
; 0008 00F0 //WriteEepromByte(SKIP_ROM) ;       /* skip rom */
; 0008 00F1 WriteTo_1Wire(SKIP_ROM) ;       /* skip rom */
	LDI  R26,LOW(204)
	CALL _WriteTo_1Wire
; 0008 00F2 }
; 0008 00F3 //WriteEepromByte(command) ;                  /* Write command */
; 0008 00F4 WriteTo_1Wire(command) ;                  /* Write command */
_0x10003D:
	MOV  R26,R19
	CALL _WriteTo_1Wire
; 0008 00F5 
; 0008 00F6 if ( number == 1 )
	CPI  R17,1
	BREQ PC+3
	JMP _0x10003E
; 0008 00F7 {                          /* one cmd */
; 0008 00F8 //WriteEepromByte(cmd_byte) ;         /* Write 2. command */
; 0008 00F9 WriteTo_1Wire(cmd_byte) ;         /* Write 2. command */
	MOV  R26,R16
	CALL _WriteTo_1Wire
; 0008 00FA }
; 0008 00FB return TRUE ;
_0x10003E:
	LDI  R30,LOW(1)
	CALL __LOADLOCR4
	ADIW R28,6
	RET
; 0008 00FC }
; 0008 00FD else
_0x10003C:
; 0008 00FE {
; 0008 00FF return FALSE ;
	LDI  R30,LOW(0)
	CALL __LOADLOCR4
	ADIW R28,6
	RET
; 0008 0100 }
_0x10003F:
; 0008 0101 }
	CALL __LOADLOCR4
	ADIW R28,6
	RET
; .FEND
;void ReadEepromData(unsigned char *data, char NofBytes)
; 0008 010A {
_ReadEepromData:
; .FSTART _ReadEepromData
; 0008 010B short       i;
; 0008 010C 
; 0008 010D for ( i = 0; i < NofBytes; i++ )
	CALL __SAVELOCR6
	MOV  R19,R26
	__GETWRS 20,21,6
;	*data -> R20,R21
;	NofBytes -> R19
;	i -> R16,R17
	__GETWRN 16,17,0
_0x100041:
	MOV  R30,R19
	MOVW R26,R16
	LDI  R31,0
	CP   R26,R30
	CPC  R27,R31
	BRLO PC+3
	JMP _0x100042
; 0008 010E {
; 0008 010F *data++ = Read_1Wire() ;
	PUSH R21
	PUSH R20
	__ADDWRN 20,21,1
	CALL _Read_1Wire
	POP  R26
	POP  R27
	ST   X,R30
; 0008 0110 }
_0x100040:
	__ADDWRN 16,17,1
	RJMP _0x100041
_0x100042:
; 0008 0111 }
	CALL __LOADLOCR6
	ADIW R28,8
	RET
; .FEND
;void WriteEepromData(unsigned char* data, char NofBytes)
; 0008 0119 {
_WriteEepromData:
; .FSTART _WriteEepromData
; 0008 011A short       i;
; 0008 011B 
; 0008 011C 
; 0008 011D for ( i = 0; i < NofBytes; i++ ) {
	CALL __SAVELOCR6
	MOV  R19,R26
	__GETWRS 20,21,6
;	*data -> R20,R21
;	NofBytes -> R19
;	i -> R16,R17
	__GETWRN 16,17,0
_0x100044:
	MOV  R30,R19
	MOVW R26,R16
	LDI  R31,0
	CP   R26,R30
	CPC  R27,R31
	BRLO PC+3
	JMP _0x100045
; 0008 011E //WriteEepromByte(*data++) ;
; 0008 011F WriteTo_1Wire(*data++);
	MOVW R26,R20
	__ADDWRN 20,21,1
	LD   R26,X
	CALL _WriteTo_1Wire
; 0008 0120 }
_0x100043:
	__ADDWRN 16,17,1
	RJMP _0x100044
_0x100045:
; 0008 0121 
; 0008 0122 }
	CALL __LOADLOCR6
	ADIW R28,8
	RET
; .FEND
;unsigned int CheckEepChannel(void)
; 0008 01B0 {
_CheckEepChannel:
; .FSTART _CheckEepChannel
; 0008 01B1 
; 0008 01B2 short ch, i  ;
; 0008 01B3 
; 0008 01B4 /* read the on board eeprom */
; 0008 01B5 if ( !(eep_type[7] & 0x10 ) && !(eep_type[7] & 0x09) ) {   /* ok sens || ok pc*/
	CALL __SAVELOCR4
;	ch -> R16,R17
;	i -> R18,R19
	__GETB1MN _eep_type,7
	ANDI R30,LOW(0x10)
	BREQ PC+3
	JMP _0x100047
	__GETB1MN _eep_type,7
	ANDI R30,LOW(0x9)
	BREQ PC+3
	JMP _0x100047
	RJMP _0x100048
_0x100047:
	RJMP _0x100046
_0x100048:
; 0008 01B6 eep_type[7] |= 0x20 ;               /* Error before OK proved */
	__GETB1MN _eep_type,7
	ORI  R30,0x20
	__PUTB1MN _eep_type,7
; 0008 01B7 eep_type[7] &= ~0x10 ;
	ANDI R30,0xEF
	__PUTB1MN _eep_type,7
; 0008 01B8 if ( Eeprom(7, COPY_NV_SP) ) {
	LDI  R30,LOW(7)
	ST   -Y,R30
	LDI  R26,LOW(240)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0x100049
; 0008 01B9 if ( Eeprom(7, READ_SP) ) {
	LDI  R30,LOW(7)
	ST   -Y,R30
	LDI  R26,LOW(170)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0x10004A
; 0008 01BA if ( Eeprom(7, READ_APPREG) ) {
	LDI  R30,LOW(7)
	ST   -Y,R30
	LDI  R26,LOW(195)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0x10004B
; 0008 01BB if ( CheckADData(&packed_data[7][0]) &&
; 0008 01BC CheckEepData(&packed_data[7][8]) ) {          /*check checksum */
	__POINTW2MN _packed_data,280
	CALL _CheckADData
	CPI  R30,0
	BRNE PC+3
	JMP _0x10004D
	__POINTW2MN _packed_data,288
	CALL _CheckEepData
	CPI  R30,0
	BRNE PC+3
	JMP _0x10004D
	RJMP _0x10004E
_0x10004D:
	RJMP _0x10004C
_0x10004E:
; 0008 01BD eep_type[7] &= ~0x20 ;
	__GETB1MN _eep_type,7
	ANDI R30,0xDF
	__PUTB1MN _eep_type,7
; 0008 01BE eep_type[7] |= 0x10 ;           /* OK from eeprom */
	ORI  R30,0x10
	__PUTB1MN _eep_type,7
; 0008 01BF for ( i=0; i < NOIOCH; i++ ) {
	__GETWRN 18,19,0
_0x100050:
	__CPWRN 18,19,14
	BRLO PC+3
	JMP _0x100051
; 0008 01C0 ch_stat[i] = packed_data[7][i+8] ;    /* copy setup */
	MOVW R30,R18
	SUBI R30,LOW(-_ch_stat)
	SBCI R31,HIGH(-_ch_stat)
	MOVW R0,R30
	__POINTW2MN _packed_data,280
	MOVW R30,R18
	ADIW R30,8
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X
	MOVW R26,R0
	ST   X,R30
; 0008 01C1 }
_0x10004F:
	__ADDWRN 18,19,1
	RJMP _0x100050
_0x100051:
; 0008 01C2 }
; 0008 01C3 }
_0x10004C:
; 0008 01C4 }
_0x10004B:
; 0008 01C5 }
_0x10004A:
; 0008 01C6 }
_0x100049:
; 0008 01C7 for ( ch=0; ch < NOPSD-1; ch++ ) {
_0x100046:
	__GETWRN 16,17,0
_0x100053:
	__CPWRN 16,17,7
	BRLO PC+3
	JMP _0x100054
; 0008 01C8 if ( !(eep_type[ch] & 0x10 ) && !(eep_type[ch]& 0x09) &&    /* ok sens || ok pc*/
; 0008 01C9 ((ch_stat[ch<<1] & 0x1c) || (ch_stat[ch<<1] & 0x60)) ) { /* && pressure */
	LDI  R26,LOW(_eep_type)
	LDI  R27,HIGH(_eep_type)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0x10)
	BREQ PC+3
	JMP _0x100056
	LDI  R26,LOW(_eep_type)
	LDI  R27,HIGH(_eep_type)
	ADD  R26,R16
	ADC  R27,R17
	LD   R30,X
	ANDI R30,LOW(0x9)
	BREQ PC+3
	JMP _0x100056
	MOVW R30,R16
	LSL  R30
	ROL  R31
	SUBI R30,LOW(-_ch_stat)
	SBCI R31,HIGH(-_ch_stat)
	LD   R30,Z
	ANDI R30,LOW(0x1C)
	BREQ PC+3
	JMP _0x100057
	MOVW R30,R16
	LSL  R30
	ROL  R31
	SUBI R30,LOW(-_ch_stat)
	SBCI R31,HIGH(-_ch_stat)
	LD   R30,Z
	ANDI R30,LOW(0x60)
	BREQ PC+3
	JMP _0x100057
	RJMP _0x100056
_0x100057:
	RJMP _0x100059
_0x100056:
	RJMP _0x100055
_0x100059:
; 0008 01CA eep_type[ch] |= 0x20 ;              /* Error before OK proved */
	MOVW R26,R16
	SUBI R26,LOW(-_eep_type)
	SBCI R27,HIGH(-_eep_type)
	LD   R30,X
	ORI  R30,0x20
	ST   X,R30
; 0008 01CB eep_type[ch] &= ~0x10 ;
	MOVW R26,R16
	SUBI R26,LOW(-_eep_type)
	SBCI R27,HIGH(-_eep_type)
	LD   R30,X
	ANDI R30,0xEF
	ST   X,R30
; 0008 01CC if ( Eeprom(ch, COPY_NV_SP) ) {
	ST   -Y,R16
	LDI  R26,LOW(240)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0x10005A
; 0008 01CD if ( Eeprom(ch, READ_SP) ) {
	ST   -Y,R16
	LDI  R26,LOW(170)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0x10005B
; 0008 01CE if ( Eeprom(ch, READ_APPREG) ) {
	ST   -Y,R16
	LDI  R26,LOW(195)
	CALL _Eeprom
	SBIW R30,0
	BRNE PC+3
	JMP _0x10005C
; 0008 01CF if ( CheckADData(&packed_data[ch][0]) &&
; 0008 01D0 CheckEepData(&packed_data[ch][8]) ) { /*check checksum */
	__MULBNWRU 16,17,40
	SUBI R30,LOW(-_packed_data)
	SBCI R31,HIGH(-_packed_data)
	MOVW R26,R30
	CALL _CheckADData
	CPI  R30,0
	BRNE PC+3
	JMP _0x10005E
	__MULBNWRU 16,17,40
	__ADDW1MN _packed_data,8
	MOVW R26,R30
	CALL _CheckEepData
	CPI  R30,0
	BRNE PC+3
	JMP _0x10005E
	RJMP _0x10005F
_0x10005E:
	RJMP _0x10005D
_0x10005F:
; 0008 01D1 eep_type[ch] &= ~0x20 ;
	MOVW R26,R16
	SUBI R26,LOW(-_eep_type)
	SBCI R27,HIGH(-_eep_type)
	LD   R30,X
	ANDI R30,0xDF
	ST   X,R30
; 0008 01D2 eep_type[ch] |= 0x10 ;           /* OK from eeprom */
	MOVW R26,R16
	SUBI R26,LOW(-_eep_type)
	SBCI R27,HIGH(-_eep_type)
	LD   R30,X
	ORI  R30,0x10
	ST   X,R30
; 0008 01D3 ch_stat[ch << 1] |= 0x80 ;            /* New sensor flagged */
	MOVW R30,R16
	LSL  R30
	ROL  R31
	SUBI R30,LOW(-_ch_stat)
	SBCI R31,HIGH(-_ch_stat)
	MOVW R26,R30
	LD   R30,X
	ORI  R30,0x80
	ST   X,R30
; 0008 01D4 }
; 0008 01D5 }
_0x10005D:
; 0008 01D6 }
_0x10005C:
; 0008 01D7 }
_0x10005B:
; 0008 01D8 }
_0x10005A:
; 0008 01D9 }
_0x100055:
_0x100052:
	__ADDWRN 16,17,1
	RJMP _0x100053
_0x100054:
; 0008 01DA return 0;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; 0008 01DB }
; .FEND
;unsigned char CheckADData(unsigned char *data)
; 0008 01E3 {
_CheckADData:
; .FSTART _CheckADData
; 0008 01E4 
; 0008 01E5 int             cnt ;
; 0008 01E6 unsigned char   csum, ok ;
; 0008 01E7 
; 0008 01E8 ok = FALSE ;
	CALL __SAVELOCR6
	MOVW R20,R26
;	*data -> R20,R21
;	cnt -> R16,R17
;	csum -> R19
;	ok -> R18
	LDI  R18,LOW(0)
; 0008 01E9 csum = 0 ;
	LDI  R19,LOW(0)
; 0008 01EA for ( cnt = 0 ; cnt < 7 ; cnt++ )
	__GETWRN 16,17,0
_0x100061:
	__CPWRN 16,17,7
	BRLT PC+3
	JMP _0x100062
; 0008 01EB {
; 0008 01EC if ( *data != 0x00 ) {
	MOVW R26,R20
	LD   R30,X
	CPI  R30,0
	BRNE PC+3
	JMP _0x100063
; 0008 01ED ok = TRUE ;
	LDI  R18,LOW(1)
; 0008 01EE }
; 0008 01EF csum = crc[csum ^ *data++] ;
_0x100063:
	MOV  R0,R19
	CLR  R1
	MOVW R26,R20
	__ADDWRN 20,21,1
	LD   R30,X
	LDI  R31,0
	EOR  R30,R0
	EOR  R31,R1
	SUBI R30,LOW(-_crc*2)
	SBCI R31,HIGH(-_crc*2)
	LPM  R19,Z
; 0008 01F0 }
_0x100060:
	__ADDWRN 16,17,1
	RJMP _0x100061
_0x100062:
; 0008 01F1 if ( (csum == *data) && (ok == TRUE) )
	MOVW R26,R20
	LD   R30,X
	CP   R30,R19
	BREQ PC+3
	JMP _0x100065
	CPI  R18,1
	BREQ PC+3
	JMP _0x100065
	RJMP _0x100066
_0x100065:
	RJMP _0x100064
_0x100066:
; 0008 01F2 {   //LED3_OFF;
; 0008 01F3 return TRUE ;
	LDI  R30,LOW(1)
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; 0008 01F4 
; 0008 01F5 }
; 0008 01F6 else
_0x100064:
; 0008 01F7 {   //LED3_ON;
; 0008 01F8 return FALSE ;
	LDI  R30,LOW(0)
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; 0008 01F9 
; 0008 01FA }
_0x100067:
; 0008 01FB }
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; .FEND
;unsigned char CheckEepData(unsigned char *data)
; 0008 0204 {
_CheckEepData:
; .FSTART _CheckEepData
; 0008 0205 
; 0008 0206 int             cnt ;
; 0008 0207 //    unsigned char   csum, ok ;
; 0008 0208 unsigned char   csum;
; 0008 0209 
; 0008 020A csum = 0 ;
	CALL __SAVELOCR6
	MOVW R20,R26
;	*data -> R20,R21
;	cnt -> R16,R17
;	csum -> R19
	LDI  R19,LOW(0)
; 0008 020B for ( cnt = 8 ; cnt < (PACKED_DATA_SIZE -1) ; cnt++ ) {
	__GETWRN 16,17,8
_0x100069:
	__CPWRN 16,17,39
	BRLT PC+3
	JMP _0x10006A
; 0008 020C csum = crc[csum ^ *data++] ;
	MOV  R0,R19
	CLR  R1
	MOVW R26,R20
	__ADDWRN 20,21,1
	LD   R30,X
	LDI  R31,0
	EOR  R30,R0
	EOR  R31,R1
	SUBI R30,LOW(-_crc*2)
	SBCI R31,HIGH(-_crc*2)
	LPM  R19,Z
; 0008 020D }
_0x100068:
	__ADDWRN 16,17,1
	RJMP _0x100069
_0x10006A:
; 0008 020E if ( csum == *data )
	MOVW R26,R20
	LD   R30,X
	CP   R30,R19
	BREQ PC+3
	JMP _0x10006B
; 0008 020F {   //LED4_OFF;
; 0008 0210 return TRUE ;
	LDI  R30,LOW(1)
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; 0008 0211 }
; 0008 0212 else
_0x10006B:
; 0008 0213 {   //LED4_ON;
; 0008 0214 return FALSE ;
	LDI  R30,LOW(0)
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; 0008 0215 }
_0x10006C:
; 0008 0216 }
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; .FEND
;void MakeEepChksum(unsigned char *data)
; 0008 021E {
_MakeEepChksum:
; .FSTART _MakeEepChksum
; 0008 021F 
; 0008 0220 int             cnt ;
; 0008 0221 unsigned char   csum ;
; 0008 0222 
; 0008 0223 csum = 0 ;
	CALL __SAVELOCR6
	MOVW R20,R26
;	*data -> R20,R21
;	cnt -> R16,R17
;	csum -> R19
	LDI  R19,LOW(0)
; 0008 0224 for ( cnt = 8 ; cnt < (PACKED_DATA_SIZE -1) ; cnt++ ) {
	__GETWRN 16,17,8
_0x10006E:
	__CPWRN 16,17,39
	BRLT PC+3
	JMP _0x10006F
; 0008 0225 csum = crc[csum ^ *data++] ;
	MOV  R0,R19
	CLR  R1
	MOVW R26,R20
	__ADDWRN 20,21,1
	LD   R30,X
	LDI  R31,0
	EOR  R30,R0
	EOR  R31,R1
	SUBI R30,LOW(-_crc*2)
	SBCI R31,HIGH(-_crc*2)
	LPM  R19,Z
; 0008 0226 }
_0x10006D:
	__ADDWRN 16,17,1
	RJMP _0x10006E
_0x10006F:
; 0008 0227 *data = csum ;
	MOV  R30,R19
	MOVW R26,R20
	ST   X,R30
; 0008 0228 }
	CALL __LOADLOCR6
	ADIW R28,6
	RET
; .FEND
;void set_interrupt_mask (unsigned char data)
; 0008 022B {
_set_interrupt_mask:
; .FSTART _set_interrupt_mask
; 0008 022C if (data==0)
	ST   -Y,R17
	MOV  R17,R26
;	data -> R17
	CPI  R17,0
	BREQ PC+3
	JMP _0x100070
; 0008 022D #asm("sei");
	SEI
; 0008 022E else
	RJMP _0x100071
_0x100070:
; 0008 022F #asm("cli");
	CLI
; 0008 0230 }
_0x100071:
	LD   R17,Y+
	RET
; .FEND
;char ResetONEWIRE (void)
; 0009 0015 {   unsigned char result=0;

	.CSEG
_ResetONEWIRE:
; .FSTART _ResetONEWIRE
; 0009 0016 unsigned char loop=1;
; 0009 0017 ONEWIRE_CLR;                // set pin low
	ST   -Y,R17
	ST   -Y,R16
;	result -> R17
;	loop -> R16
	LDI  R17,0
	LDI  R16,1
	LDI  R30,LOW(2)
	STS  1189,R30
; 0009 0018 delay_us( TRSTL ); // wait delay max from Maxim, see *.h the value
	__DELAY_USW 540
; 0009 0019 ONEWIRE_SET;    // Set pin high
	STS  1190,R30
; 0009 001A delay_us (TMSP);
	__DELAY_USB 89
; 0009 001B if (ONEWIRE_READ == 0 )  // confirm presence
	LDS  R30,1192
	ANDI R30,LOW(0x1)
	BREQ PC+3
	JMP _0x120003
; 0009 001C result = 0x01;
	LDI  R17,LOW(1)
; 0009 001D else
	RJMP _0x120004
_0x120003:
; 0009 001E result = 0x00;
	LDI  R17,LOW(0)
; 0009 001F // wait line release to High, if not sensor it is high with pull up.
; 0009 0020 while (loop)
_0x120004:
_0x120005:
	CPI  R16,0
	BRNE PC+3
	JMP _0x120007
; 0009 0021 {   if (ONEWIRE_READ == 1 )
	LDS  R30,1192
	ANDI R30,LOW(0x1)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x120008
; 0009 0022 loop=0; // exit
	LDI  R16,LOW(0)
; 0009 0023 }
_0x120008:
	RJMP _0x120005
_0x120007:
; 0009 0024 delay_us(TREC);
	__DELAY_USB 7
; 0009 0025 return result;
	MOV  R30,R17
	LD   R16,Y+
	LD   R17,Y+
	RET
; 0009 0026 }
; .FEND
;void    WriteTo_1Wire ( unsigned char data )
; 0009 002B {   unsigned char temp;
_WriteTo_1Wire:
; .FSTART _WriteTo_1Wire
; 0009 002C unsigned char nb_bit=8;
; 0009 002D temp=data;
	CALL __SAVELOCR4
	MOV  R19,R26
;	data -> R19
;	temp -> R17
;	nb_bit -> R16
	LDI  R16,8
	MOV  R17,R19
; 0009 002E while (nb_bit)
_0x120009:
	CPI  R16,0
	BRNE PC+3
	JMP _0x12000B
; 0009 002F {
; 0009 0030 if ( (temp & 0x01) == 0x01) // send "1"
	MOV  R30,R17
	ANDI R30,LOW(0x1)
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x12000C
; 0009 0031 {   ONEWIRE_CLR;    // set pin low
	LDI  R30,LOW(2)
	STS  1189,R30
; 0009 0032 delay_us( TW1_LOW ); //
	__DELAY_USB 7
; 0009 0033 ONEWIRE_SET;    // Set pin high
	STS  1190,R30
; 0009 0034 delay_us( TW1_SLOT ); // wait delay max from Maxim, see *.h the value
	__DELAY_USB 80
; 0009 0035 }
; 0009 0036 else    // send "0"
	RJMP _0x12000D
_0x12000C:
; 0009 0037 {   ONEWIRE_CLR;    // set pin low
	LDI  R30,LOW(2)
	STS  1189,R30
; 0009 0038 delay_us( TW0_LOW ); //
	__DELAY_USB 80
; 0009 0039 ONEWIRE_SET;    // Set pin high
	STS  1190,R30
; 0009 003A delay_us( TW0_SLOT ); // wait delay max from Maxim, see *.h the value
	__DELAY_USB 7
; 0009 003B }
_0x12000D:
; 0009 003C temp>>=1;
	LSR  R17
; 0009 003D nb_bit--;
	SUBI R16,1
; 0009 003E }
	RJMP _0x120009
_0x12000B:
; 0009 003F }
	CALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
;char    Read_1Wire (void)
; 0009 0043 {    unsigned char data=0;
_Read_1Wire:
; .FSTART _Read_1Wire
; 0009 0044 unsigned char nb_bit=8;
; 0009 0045 //		temp=data;
; 0009 0046 while (nb_bit)
	ST   -Y,R17
	ST   -Y,R16
;	data -> R17
;	nb_bit -> R16
	LDI  R17,0
	LDI  R16,8
_0x12000E:
	CPI  R16,0
	BRNE PC+3
	JMP _0x120010
; 0009 0047 {   // make pull from master:
; 0009 0048 ONEWIRE_CLR;    // set pin low
	LDI  R30,LOW(2)
	STS  1189,R30
; 0009 0049 delay_us( TW_RL ); //  set pin low
	__DELAY_USB 3
; 0009 004A ONEWIRE_SET;    // Set pin high
	STS  1190,R30
; 0009 004B delay_us( TW_MSR ); // wait delay max from Maxim, see *.h the value
	__DELAY_USB 17
; 0009 004C data>>=1;
	LSR  R17
; 0009 004D if ( ONEWIRE_READ ==1)
	LDS  R30,1192
	ANDI R30,LOW(0x1)
	LDI  R26,LOW(0)
	__NEB12
	CPI  R30,LOW(0x1)
	BREQ PC+3
	JMP _0x120011
; 0009 004E data|=0x80;     // LSB FIRST move 8 time
	ORI  R17,LOW(128)
; 0009 004F //data>>=1;
; 0009 0050 nb_bit--;
_0x120011:
	SUBI R16,1
; 0009 0051 delay_us (TWR_SLOT);
	__DELAY_USB 73
; 0009 0052 }
	RJMP _0x12000E
_0x120010:
; 0009 0053 return data;
	MOV  R30,R17
	LD   R16,Y+
	LD   R17,Y+
	RET
; 0009 0054 }
; .FEND
;void InitEEprom (void)
; 000A 0036 {   unsigned char data;

	.CSEG
_InitEEprom:
; .FSTART _InitEEprom
; 000A 0037 unsigned char buffer[8];
; 000A 0038 unsigned char localCRC=0;
; 000A 0039 unsigned char i;
; 000A 003A data= EEpromInitByte;
	SBIW R28,8
	CALL __SAVELOCR4
;	data -> R17
;	buffer -> Y+4
;	localCRC -> R16
;	i -> R19
	LDI  R16,0
	LDI  R26,LOW(_EEpromInitByte)
	LDI  R27,HIGH(_EEpromInitByte)
	CALL __EEPROMRDB
	MOV  R17,R30
; 000A 003B if ( data != LOCK_BYTE )
	CPI  R17,85
	BRNE PC+3
	JMP _0x140003
; 000A 003C {   EEpromInitByte = LOCK_BYTE;  // set eeprom to lock byte
	LDI  R26,LOW(_EEpromInitByte)
	LDI  R27,HIGH(_EEpromInitByte)
	LDI  R30,LOW(85)
	CALL __EEPROMWRB
; 000A 003D FirtByteEEprom = LOCK_BYTE;  // set eeprom to lock byte
	LDI  R26,LOW(_FirtByteEEprom)
	LDI  R27,HIGH(_FirtByteEEprom)
	CALL __EEPROMWRB
; 000A 003E EEpromStatusByte=DEFAULT_EEPROM_STATUS;
	LDI  R26,LOW(_EEpromStatusByte)
	LDI  R27,HIGH(_EEpromStatusByte)
	LDI  R30,LOW(0)
	CALL __EEPROMWRB
; 000A 003F data=SerielNummerLock;
	LDI  R26,LOW(_SerielNummerLock)
	LDI  R27,HIGH(_SerielNummerLock)
	CALL __EEPROMRDB
	MOV  R17,R30
; 000A 0040 if ( data!= LOCK_BYTE)  // clear all EEprom variable.
	CPI  R17,85
	BRNE PC+3
	JMP _0x140004
; 000A 0041 {   for (i=0; i < 4; i++)   // clear Serial nummer
	LDI  R19,LOW(0)
_0x140006:
	CPI  R19,4
	BRLO PC+3
	JMP _0x140007
; 000A 0042 { EESerielNummer[i]=0;
	MOV  R26,R19
	LDI  R27,0
	SUBI R26,LOW(-_EESerielNummer)
	SBCI R27,HIGH(-_EESerielNummer)
	LDI  R30,LOW(0)
	CALL __EEPROMWRB
; 000A 0043 }
_0x140005:
	SUBI R19,-1
	RJMP _0x140006
_0x140007:
; 000A 0044 EESerielNummerCRC=0;    // clear CRC
	LDI  R26,LOW(_EESerielNummerCRC)
	LDI  R27,HIGH(_EESerielNummerCRC)
	LDI  R30,LOW(0)
	CALL __EEPROMWRB
; 000A 0045 for (i=0; i < 32; i++)
	LDI  R19,LOW(0)
_0x140009:
	CPI  R19,32
	BRLO PC+3
	JMP _0x14000A
; 000A 0046 { EEpromScratchpad[i]=0;    // clear ScratchPad
	MOV  R26,R19
	LDI  R27,0
	SUBI R26,LOW(-_EEpromScratchpad)
	SBCI R27,HIGH(-_EEpromScratchpad)
	LDI  R30,LOW(0)
	CALL __EEPROMWRB
; 000A 0047 }
_0x140008:
	SUBI R19,-1
	RJMP _0x140009
_0x14000A:
; 000A 0048 SerielNummerLock= UNLOCK_BYTE;
	LDI  R26,LOW(_SerielNummerLock)
	LDI  R27,HIGH(_SerielNummerLock)
	LDI  R30,LOW(170)
	CALL __EEPROMWRB
; 000A 0049 }
; 000A 004A // Make EEpromDallesSN
; 000A 004B buffer[0]= 0;    //crc
_0x140004:
	LDI  R30,LOW(0)
	STD  Y+4,R30
; 000A 004C buffer[1]= 1;
	LDI  R30,LOW(1)
	STD  Y+5,R30
; 000A 004D buffer[2]= 4;
	LDI  R30,LOW(4)
	STD  Y+6,R30
; 000A 004E buffer[3]= 1;
	LDI  R30,LOW(1)
	STD  Y+7,R30
; 000A 004F buffer[4]= 2;
	LDI  R30,LOW(2)
	STD  Y+8,R30
; 000A 0050 buffer[5]= 2;
	STD  Y+9,R30
; 000A 0051 buffer[6]= 2;
	STD  Y+10,R30
; 000A 0052 buffer[7]= 0x14;
	LDI  R30,LOW(20)
	STD  Y+11,R30
; 000A 0053 for ( i =1; i < 7;i++)
	LDI  R19,LOW(1)
_0x14000C:
	CPI  R19,7
	BRLO PC+3
	JMP _0x14000D
; 000A 0054 {   data=buffer[i];
	MOV  R30,R19
	LDI  R31,0
	MOVW R26,R28
	ADIW R26,4
	ADD  R26,R30
	ADC  R27,R31
	LD   R17,X
; 000A 0055 localCRC= crc[ localCRC ^ data ];
	MOV  R26,R16
	CLR  R27
	MOV  R30,R17
	LDI  R31,0
	EOR  R30,R26
	EOR  R31,R27
	SUBI R30,LOW(-_crc*2)
	SBCI R31,HIGH(-_crc*2)
	LPM  R16,Z
; 000A 0056 }
_0x14000B:
	SUBI R19,-1
	RJMP _0x14000C
_0x14000D:
; 000A 0057 buffer[0]=localCRC;
	__PUTBSR 16,4
; 000A 0058 for ( i =0; i < 8;i++)
	LDI  R19,LOW(0)
_0x14000F:
	CPI  R19,8
	BRLO PC+3
	JMP _0x140010
; 000A 0059 {   EEpromDallasSN[i]= buffer[i];
	MOV  R30,R19
	LDI  R31,0
	SUBI R30,LOW(-_EEpromDallasSN)
	SBCI R31,HIGH(-_EEpromDallasSN)
	MOVW R0,R30
	MOV  R30,R19
	LDI  R31,0
	MOVW R26,R28
	ADIW R26,4
	ADD  R26,R30
	ADC  R27,R31
	LD   R30,X
	MOVW R26,R0
	CALL __EEPROMWRB
; 000A 005A }
_0x14000E:
	SUBI R19,-1
	RJMP _0x14000F
_0x140010:
; 000A 005B delay_ms(10);
	LDI  R26,LOW(10)
	LDI  R27,0
	CALL _delay_ms
; 000A 005C }
; 000A 005D }
_0x140003:
	CALL __LOADLOCR4
	ADIW R28,12
	RET
; .FEND

	.CSEG

	.CSEG

	.CSEG

	.CSEG

	.CSEG

	.DSEG

	.CSEG

	.DSEG
_tx_buff:
	.BYTE 0xC8
_rx_buff:
	.BYTE 0xC8
_tx_indx:
	.BYTE 0x1
_tx_bytes:
	.BYTE 0x1
_tx_tail:
	.BYTE 0x1
_wait_for_pc:
	.BYTE 0x1
_rx_indx:
	.BYTE 0x1
_rx_hndx:
	.BYTE 0x1
_rx_start:
	.BYTE 0x1
_rx_counter:
	.BYTE 0x1
_rx_packlen:
	.BYTE 0x1
_rx_timeout:
	.BYTE 0x1
_sync_cnt:
	.BYTE 0x1
_sens_data:
	.BYTE 0x8
_sens_nl1:
	.BYTE 0x1
_sens_nl2:
	.BYTE 0x1
_packed_data:
	.BYTE 0x140
_eep_status:
	.BYTE 0x1
_time_b_temp:
	.BYTE 0x1
_time_b_cnt:
	.BYTE 0x1
_time_e_cnt:
	.BYTE 0x1
_ad_timeout_cnt:
	.BYTE 0x2
_sec_cnt:
	.BYTE 0x2
_ms_cnt:
	.BYTE 0x2
_curr_sens_data:
	.BYTE 0x2
_cal_data:
	.BYTE 0x1C
_raw_data:
	.BYTE 0x1C
_mes_data:
	.BYTE 0x38
_highlevel:
	.BYTE 0x1
_washtrac:
	.BYTE 0x8
_washtrac_prev:
	.BYTE 0x1
_gain:
	.BYTE 0x38
_offset:
	.BYTE 0x1C
_cal_gain:
	.BYTE 0x4
_cal_zero:
	.BYTE 0x2
_not_mes_data:
	.BYTE 0x1
_not_raw_data:
	.BYTE 0x1
_not_cal_data:
	.BYTE 0x1
_curr_ad_ch:
	.BYTE 0x1
_old_curr_ad_ch:
	.BYTE 0x1
_ad_state:
	.BYTE 0x1
_ad_mode:
	.BYTE 0x1
_ms_delay_cnt:
	.BYTE 0x2
_ad_settling:
	.BYTE 0x2
_ad_gain:
	.BYTE 0x1
_ch_stat:
	.BYTE 0xE
_eep_type:
	.BYTE 0x8
_p_filter:
	.BYTE 0x1
_t_filter:
	.BYTE 0x1
_o_filter:
	.BYTE 0x1
_my_address:
	.BYTE 0x1
_rx_state:
	.BYTE 0x1
_tx_complete:
	.BYTE 0x1
_sendtail:
	.BYTE 0x1

	.ESEG
_FirtByteEEprom:
	.DB  0xAA
_EEpromInitByte:
	.DB  0xAA
_SerielNummerLock:
	.DB  0xAA
_EEpromScratchpad:
	.BYTE 0x20
_EESerielNummer:
	.BYTE 0x8
_EESerielNummerCRC:
	.DB  0xAA
_EEpromStatusByte:
	.DB  0xAA
_EEpromDallasSN:
	.BYTE 0x8

	.DSEG
_rx_buffer_usart0:
	.BYTE 0x8
_rx_rd_index_usart0:
	.BYTE 0x1
_rx_counter_usart0:
	.BYTE 0x1
_tx_buffer_usart0:
	.BYTE 0x8
_tx_wr_index_usart0:
	.BYTE 0x2
_tx_counter_usart0:
	.BYTE 0x1
__seed_G104:
	.BYTE 0x4

	.CSEG
;RUNTIME LIBRARY

	.CSEG
__SAVELOCR6:
	ST   -Y,R21
__SAVELOCR5:
	ST   -Y,R20
__SAVELOCR4:
	ST   -Y,R19
__SAVELOCR3:
	ST   -Y,R18
__SAVELOCR2:
	ST   -Y,R17
	ST   -Y,R16
	RET

__LOADLOCR6:
	LDD  R21,Y+5
__LOADLOCR5:
	LDD  R20,Y+4
__LOADLOCR4:
	LDD  R19,Y+3
__LOADLOCR3:
	LDD  R18,Y+2
__LOADLOCR2:
	LDD  R17,Y+1
	LD   R16,Y
	RET

__INITLOCB:
__INITLOCW:
	PUSH R26
	PUSH R27
	MOVW R26,R22
	ADD  R26,R28
	ADC  R27,R29
__INITLOC0:
	LPM  R0,Z+
	ST   X+,R0
	DEC  R24
	BRNE __INITLOC0
	POP  R27
	POP  R26
	RET

__ANEGW1:
	NEG  R31
	NEG  R30
	SBCI R31,0
	RET

__ANEGD1:
	COM  R31
	COM  R22
	COM  R23
	NEG  R30
	SBCI R31,-1
	SBCI R22,-1
	SBCI R23,-1
	RET

__LSRB12:
	TST  R30
	MOV  R0,R30
	MOV  R30,R26
	BREQ __LSRB12R
__LSRB12L:
	LSR  R30
	DEC  R0
	BRNE __LSRB12L
__LSRB12R:
	RET

__ASRW12:
	TST  R30
	MOV  R0,R30
	LDI  R30,8
	MOV  R1,R30
	MOVW R30,R26
	BREQ __ASRW12R
__ASRW12S8:
	CP   R0,R1
	BRLO __ASRW12L
	MOV  R30,R31
	LDI  R31,0
	SBRC R30,7
	LDI  R31,0xFF
	SUB  R0,R1
	BREQ __ASRW12R
__ASRW12L:
	ASR  R31
	ROR  R30
	DEC  R0
	BRNE __ASRW12L
__ASRW12R:
	RET

__LSLW4:
	LSL  R30
	ROL  R31
__LSLW3:
	LSL  R30
	ROL  R31
__LSLW2:
	LSL  R30
	ROL  R31
	LSL  R30
	ROL  R31
	RET

__ASRW4:
	ASR  R31
	ROR  R30
__ASRW3:
	ASR  R31
	ROR  R30
__ASRW2:
	ASR  R31
	ROR  R30
	ASR  R31
	ROR  R30
	RET

__CBD1:
	MOV  R31,R30
	ADD  R31,R31
	SBC  R31,R31
	MOV  R22,R31
	MOV  R23,R31
	RET

__MULW12U:
	MUL  R31,R26
	MOV  R31,R0
	MUL  R30,R27
	ADD  R31,R0
	MUL  R30,R26
	MOV  R30,R0
	ADD  R31,R1
	RET

__MULB1W2U:
	MOV  R22,R30
	MUL  R22,R26
	MOVW R30,R0
	MUL  R22,R27
	ADD  R31,R0
	RET

__MULW12:
	RCALL __CHKSIGNW
	RCALL __MULW12U
	BRTC __MULW121
	RCALL __ANEGW1
__MULW121:
	RET

__DIVW21U:
	CLR  R0
	CLR  R1
	LDI  R25,16
__DIVW21U1:
	LSL  R26
	ROL  R27
	ROL  R0
	ROL  R1
	SUB  R0,R30
	SBC  R1,R31
	BRCC __DIVW21U2
	ADD  R0,R30
	ADC  R1,R31
	RJMP __DIVW21U3
__DIVW21U2:
	SBR  R26,1
__DIVW21U3:
	DEC  R25
	BRNE __DIVW21U1
	MOVW R30,R26
	MOVW R26,R0
	RET

__DIVW21:
	RCALL __CHKSIGNW
	RCALL __DIVW21U
	BRTC __DIVW211
	RCALL __ANEGW1
__DIVW211:
	RET

__CHKSIGNW:
	CLT
	SBRS R31,7
	RJMP __CHKSW1
	RCALL __ANEGW1
	SET
__CHKSW1:
	SBRS R27,7
	RJMP __CHKSW2
	NEG  R27
	NEG  R26
	SBCI R27,0
	BLD  R0,0
	INC  R0
	BST  R0,0
__CHKSW2:
	RET

__PUTPARD2:
	ST   -Y,R25
	ST   -Y,R24
	ST   -Y,R27
	ST   -Y,R26
	RET

__CDF2U:
	SET
	RJMP __CDF2U0
__CDF2:
	CLT
__CDF2U0:
	RCALL __SWAPD12
	RCALL __CDF1U0

__SWAPD12:
	MOV  R1,R24
	MOV  R24,R22
	MOV  R22,R1
	MOV  R1,R25
	MOV  R25,R23
	MOV  R23,R1

__SWAPW12:
	MOV  R1,R27
	MOV  R27,R31
	MOV  R31,R1

__SWAPB12:
	MOV  R1,R26
	MOV  R26,R30
	MOV  R30,R1
	RET

__EEPROMRDB:
	WDR
	LDS  R30,NVMCTRL_STATUS
	SBRC R30,1
	RJMP __EEPROMRDB
	SUBI R27,-0x14
	LD   R30,X
	SUBI R27,0x14
	RET

__EEPROMWRB:
	RCALL __NVMREADY
	SUBI R27,-0x14
	LD   R24,X
	CP   R24,R30
	BRNE __EEPROMWRB1
	SUBI R27,0x14
	RET
__EEPROMWRB1:
	MOV  R25,R30

__EEPROMWRA:
	RCALL __NVMREADY
	PUSH R22
	PUSH R23
	IN   R23,SREG
	CLI
	STS  NVMCTRL_ADDRL,R26
	STS  NVMCTRL_ADDRH,R27
	LDI  R22,0x9D
	LDI  R24,0x13
	OUT  CCP,R22
	STS  NVMCTRL_CTRLA,R24
	ST   X,R25
	SUBI R27,0x14
	RCALL __NVMREADY
	LDI  R24,0
	STS  NVMCTRL_CTRLA,R24
	OUT  SREG,R23
	POP  R23
	POP  R22
	RET

__NVMREADY:
	WDR
	LDS  R24,NVMCTRL_STATUS
	SBRC R24,1
	RJMP __NVMREADY
	RET

__ROUND_REPACK:
	TST  R21
	BRPL __REPACK
	CPI  R21,0x80
	BRNE __ROUND_REPACK0
	SBRS R30,0
	RJMP __REPACK
__ROUND_REPACK0:
	ADIW R30,1
	ADC  R22,R25
	ADC  R23,R25
	BRVS __REPACK1

__REPACK:
	LDI  R21,0x80
	EOR  R21,R23
	BRNE __REPACK0
	PUSH R21
	RJMP __ZERORES
__REPACK0:
	CPI  R21,0xFF
	BREQ __REPACK1
	LSL  R22
	LSL  R0
	ROR  R21
	ROR  R22
	MOV  R23,R21
	RET
__REPACK1:
	PUSH R21
	TST  R0
	BRMI __REPACK2
	RJMP __MAXRES
__REPACK2:
	RJMP __MINRES

__UNPACK:
	LDI  R21,0x80
	MOV  R1,R25
	AND  R1,R21
	LSL  R24
	ROL  R25
	EOR  R25,R21
	LSL  R21
	ROR  R24

__UNPACK1:
	LDI  R21,0x80
	MOV  R0,R23
	AND  R0,R21
	LSL  R22
	ROL  R23
	EOR  R23,R21
	LSL  R21
	ROR  R22
	RET

__CFD1U:
	SET
	RJMP __CFD1U0
__CFD1:
	CLT
__CFD1U0:
	PUSH R21
	RCALL __UNPACK1
	CPI  R23,0x80
	BRLO __CFD10
	CPI  R23,0xFF
	BRCC __CFD10
	RJMP __ZERORES
__CFD10:
	LDI  R21,22
	SUB  R21,R23
	BRPL __CFD11
	NEG  R21
	CPI  R21,8
	BRTC __CFD19
	CPI  R21,9
__CFD19:
	BRLO __CFD17
	SER  R30
	SER  R31
	SER  R22
	LDI  R23,0x7F
	BLD  R23,7
	RJMP __CFD15
__CFD17:
	CLR  R23
	TST  R21
	BREQ __CFD15
__CFD18:
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R23
	DEC  R21
	BRNE __CFD18
	RJMP __CFD15
__CFD11:
	CLR  R23
__CFD12:
	CPI  R21,8
	BRLO __CFD13
	MOV  R30,R31
	MOV  R31,R22
	MOV  R22,R23
	SUBI R21,8
	RJMP __CFD12
__CFD13:
	TST  R21
	BREQ __CFD15
__CFD14:
	LSR  R23
	ROR  R22
	ROR  R31
	ROR  R30
	DEC  R21
	BRNE __CFD14
__CFD15:
	TST  R0
	BRPL __CFD16
	RCALL __ANEGD1
__CFD16:
	POP  R21
	RET

__CDF1U:
	SET
	RJMP __CDF1U0
__CDF1:
	CLT
__CDF1U0:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	BREQ __CDF10
	CLR  R0
	BRTS __CDF11
	TST  R23
	BRPL __CDF11
	COM  R0
	RCALL __ANEGD1
__CDF11:
	MOV  R1,R23
	LDI  R23,30
	TST  R1
__CDF12:
	BRMI __CDF13
	DEC  R23
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R1
	RJMP __CDF12
__CDF13:
	MOV  R30,R31
	MOV  R31,R22
	MOV  R22,R1
	PUSH R21
	RCALL __REPACK
	POP  R21
__CDF10:
	RET

__SWAPACC:
	PUSH R20
	MOVW R20,R30
	MOVW R30,R26
	MOVW R26,R20
	MOVW R20,R22
	MOVW R22,R24
	MOVW R24,R20
	MOV  R20,R0
	MOV  R0,R1
	MOV  R1,R20
	POP  R20
	RET

__UADD12:
	ADD  R30,R26
	ADC  R31,R27
	ADC  R22,R24
	RET

__NEGMAN1:
	COM  R30
	COM  R31
	COM  R22
	SUBI R30,-1
	SBCI R31,-1
	SBCI R22,-1
	RET

__SUBF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R25,0x80
	BREQ __ADDF129
	LDI  R21,0x80
	EOR  R1,R21

	RJMP __ADDF120

__ADDF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R25,0x80
	BREQ __ADDF129

__ADDF120:
	CPI  R23,0x80
	BREQ __ADDF128
__ADDF121:
	MOV  R21,R23
	SUB  R21,R25
	BRVS __ADDF1211
	BRPL __ADDF122
	RCALL __SWAPACC
	RJMP __ADDF121
__ADDF122:
	CPI  R21,24
	BRLO __ADDF123
	CLR  R26
	CLR  R27
	CLR  R24
__ADDF123:
	CPI  R21,8
	BRLO __ADDF124
	MOV  R26,R27
	MOV  R27,R24
	CLR  R24
	SUBI R21,8
	RJMP __ADDF123
__ADDF124:
	TST  R21
	BREQ __ADDF126
__ADDF125:
	LSR  R24
	ROR  R27
	ROR  R26
	DEC  R21
	BRNE __ADDF125
__ADDF126:
	MOV  R21,R0
	EOR  R21,R1
	BRMI __ADDF127
	RCALL __UADD12
	BRCC __ADDF129
	ROR  R22
	ROR  R31
	ROR  R30
	INC  R23
	BRVC __ADDF129
	RJMP __MAXRES
__ADDF128:
	RCALL __SWAPACC
__ADDF129:
	RCALL __REPACK
	POP  R21
	RET
__ADDF1211:
	BRCC __ADDF128
	RJMP __ADDF129
__ADDF127:
	SUB  R30,R26
	SBC  R31,R27
	SBC  R22,R24
	BREQ __ZERORES
	BRCC __ADDF1210
	COM  R0
	RCALL __NEGMAN1
__ADDF1210:
	TST  R22
	BRMI __ADDF129
	LSL  R30
	ROL  R31
	ROL  R22
	DEC  R23
	BRVC __ADDF1210

__ZERORES:
	CLR  R30
	CLR  R31
	MOVW R22,R30
	POP  R21
	RET

__MINRES:
	SER  R30
	SER  R31
	LDI  R22,0x7F
	SER  R23
	POP  R21
	RET

__MAXRES:
	SER  R30
	SER  R31
	LDI  R22,0x7F
	LDI  R23,0x7F
	POP  R21
	RET

__MULF12:
	PUSH R21
	RCALL __UNPACK
	CPI  R23,0x80
	BREQ __ZERORES
	CPI  R25,0x80
	BREQ __ZERORES
	EOR  R0,R1
	SEC
	ADC  R23,R25
	BRVC __MULF124
	BRLT __ZERORES
__MULF125:
	TST  R0
	BRMI __MINRES
	RJMP __MAXRES
__MULF124:
	PUSH R0
	PUSH R17
	PUSH R18
	PUSH R19
	PUSH R20
	CLR  R17
	CLR  R18
	CLR  R25
	MUL  R22,R24
	MOVW R20,R0
	MUL  R24,R31
	MOV  R19,R0
	ADD  R20,R1
	ADC  R21,R25
	MUL  R22,R27
	ADD  R19,R0
	ADC  R20,R1
	ADC  R21,R25
	MUL  R24,R30
	RCALL __MULF126
	MUL  R27,R31
	RCALL __MULF126
	MUL  R22,R26
	RCALL __MULF126
	MUL  R27,R30
	RCALL __MULF127
	MUL  R26,R31
	RCALL __MULF127
	MUL  R26,R30
	ADD  R17,R1
	ADC  R18,R25
	ADC  R19,R25
	ADC  R20,R25
	ADC  R21,R25
	MOV  R30,R19
	MOV  R31,R20
	MOV  R22,R21
	MOV  R21,R18
	POP  R20
	POP  R19
	POP  R18
	POP  R17
	POP  R0
	TST  R22
	BRMI __MULF122
	LSL  R21
	ROL  R30
	ROL  R31
	ROL  R22
	RJMP __MULF123
__MULF122:
	INC  R23
	BRVS __MULF125
__MULF123:
	RCALL __ROUND_REPACK
	POP  R21
	RET

__MULF127:
	ADD  R17,R0
	ADC  R18,R1
	ADC  R19,R25
	RJMP __MULF128
__MULF126:
	ADD  R18,R0
	ADC  R19,R1
__MULF128:
	ADC  R20,R25
	ADC  R21,R25
	RET

__DIVF21:
	PUSH R21
	RCALL __UNPACK
	CPI  R23,0x80
	BRNE __DIVF210
	TST  R1
__DIVF211:
	BRPL __DIVF219
	RJMP __MINRES
__DIVF219:
	RJMP __MAXRES
__DIVF210:
	CPI  R25,0x80
	BRNE __DIVF218
__DIVF217:
	RJMP __ZERORES
__DIVF218:
	EOR  R0,R1
	SEC
	SBC  R25,R23
	BRVC __DIVF216
	BRLT __DIVF217
	TST  R0
	RJMP __DIVF211
__DIVF216:
	MOV  R23,R25
	PUSH R17
	PUSH R18
	PUSH R19
	PUSH R20
	CLR  R1
	CLR  R17
	CLR  R18
	CLR  R19
	MOVW R20,R18
	LDI  R25,32
__DIVF212:
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	CPC  R20,R17
	BRLO __DIVF213
	SUB  R26,R30
	SBC  R27,R31
	SBC  R24,R22
	SBC  R20,R17
	SEC
	RJMP __DIVF214
__DIVF213:
	CLC
__DIVF214:
	ROL  R21
	ROL  R18
	ROL  R19
	ROL  R1
	ROL  R26
	ROL  R27
	ROL  R24
	ROL  R20
	DEC  R25
	BRNE __DIVF212
	MOVW R30,R18
	MOV  R22,R1
	POP  R20
	POP  R19
	POP  R18
	POP  R17
	TST  R22
	BRMI __DIVF215
	LSL  R21
	ROL  R30
	ROL  R31
	ROL  R22
	DEC  R23
	BRVS __DIVF217
__DIVF215:
	RCALL __ROUND_REPACK
	POP  R21
	RET

__CMPF12:
	TST  R25
	BRMI __CMPF120
	TST  R23
	BRMI __CMPF121
	CP   R25,R23
	BRLO __CMPF122
	BRNE __CMPF121
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	BRLO __CMPF122
	BREQ __CMPF123
__CMPF121:
	CLZ
	CLC
	RET
__CMPF122:
	CLZ
	SEC
	RET
__CMPF123:
	SEZ
	CLC
	RET
__CMPF120:
	TST  R23
	BRPL __CMPF122
	CP   R25,R23
	BRLO __CMPF121
	BRNE __CMPF122
	CP   R30,R26
	CPC  R31,R27
	CPC  R22,R24
	BRLO __CMPF122
	BREQ __CMPF123
	RJMP __CMPF121

_delay_ms:
	adiw r26,0
	breq __delay_ms1
__delay_ms0:
	wdr
	__DELAY_USW 0x3E8
	sbiw r26,1
	brne __delay_ms0
__delay_ms1:
	ret

;END OF CODE MARKER
__END_OF_CODE: