
;CodeVisionAVR C Compiler V3.49 Advanced
;(C) Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
;http://www.hpinfotech.ro

;Build configuration    : Debug
;Chip type              : AVR64DB64
;Program type           : Application
;Clock frequency        : 4,000960 MHz
;Memory model           : Small
;Optimize for           : Size
;(s)printf features     : int, width
;(s)scanf features      : int, width
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

	.MACRO __GETB1FN
	LDS  R30,0x8000+@0*2+(@1)
	.ENDM

	.MACRO __GETW1FN
	LDS  R30,0x8000+@0*2+(@1)
	LDS  R31,0x8001+@0*2+(@1)
	.ENDM

	.MACRO __GETD1FN
	LDS  R30,0x8000+@0*2+(@1)
	LDS  R31,0x8001+@0*2+(@1)
	LDS  R22,0x8002+@0*2+(@1)
	LDS  R23,0x8003+@0*2+(@1)
	.ENDM

	.MACRO __GETB2FN
	LDS  R26,0x8000+@0*2+(@1)
	.ENDM

	.MACRO __GETW2FN
	LDS  R26,0x8000+@0*2+(@1)
	LDS  R27,0x8001+@0*2+(@1)
	.ENDM

	.MACRO __GETD2FN
	LDS  R26,0x8000+@0*2+(@1)
	LDS  R27,0x8001+@0*2+(@1)
	LDS  R24,0x8002+@0*2+(@1)
	LDS  R25,0x8003+@0*2+(@1)
	.ENDM

	.MACRO __GETBRFN
	LDS  R@0,0x8000+@2*2+(@1)
	.ENDM

	.MACRO __GETWRFN
	LDS  R@0,0x8000+@3*2+(@2)
	LDS  R@1,0x8001+@3*2+(@2)
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
	JMP  0x00
	JMP  0x00
	JMP  0x00
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

_tbl10_G100:
	.DB  0x10,0x27,0xE8,0x3,0x64,0x0,0xA,0x0
	.DB  0x1,0x0
_tbl16_G100:
	.DB  0x0,0x10,0x0,0x1,0x10,0x0,0x1,0x0

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
; 0000 0034 {

	.CSEG
_main:
; .FSTART _main
; 0000 0035 // Declare your local variables here
; 0000 0036 unsigned char n;
; 0000 0037 
; 0000 0038 // Interrupt system initialization
; 0000 0039 // Optimize for speed
; 0000 003A #pragma optsize-
; 0000 003B // Make sure the interrupts are disabled
; 0000 003C #asm("cli")
;	n -> R17
	CLI
; 0000 003D // Round-robin scheduling for level 0 interrupt: Off
; 0000 003E // The interrupt vectors will be placed at the start of the Application FLASH section
; 0000 003F n=0;
	LDI  R17,LOW(0)
; 0000 0040 CPU_CCP=CCP_IOREG_gc;
	LDI  R30,LOW(216)
	OUT  0x34,R30
; 0000 0041 CPUINT.CTRLA=n;
	STS  272,R17
; 0000 0042 // Restore optimization for size if needed
; 0000 0043 #pragma optsize_default
; 0000 0044 
; 0000 0045 // The vectors with lower addresses will have
; 0000 0046 // higher interrupt level 0 priority (default)
; 0000 0047 CPUINT.LVL0PRI=0;
	LDI  R30,LOW(0)
	STS  274,R30
; 0000 0048 
; 0000 0049 // The higher interrupt priority level 1 is not used
; 0000 004A CPUINT.LVL1VEC=0;
	STS  275,R30
; 0000 004B 
; 0000 004C // System clocks initialization
; 0000 004D system_clocks_init();
	RCALL _system_clocks_init
; 0000 004E 
; 0000 004F // Brown-Out Detector and Voltage Level Monitor initialization
; 0000 0050 // The settings below are applied to the BODCFG fuse
; 0000 0051 // that will be programmed if the
; 0000 0052 // Project|Configure|After Build|Action: Program the Chip|Program Fuses
; 0000 0053 // menu option is enabled in the IDE
; 0000 0054 // BOD operation in Active or Idle modes: Enabled
; 0000 0055 // BOD operation in Standby or Power-Down sleep modes: Disabled
; 0000 0056 // BOD level: 1,90V
; 0000 0057 // BODCFG=0x04
; 0000 0058 
; 0000 0059 // The Multi-Voltage I/O is disabled by programming the
; 0000 005A // MVSYSCFG bits of the SYSCFG1 fuse to Single-Supply configuration
; 0000 005B // SYSCFG1=0x10
; 0000 005C // This setting will be applied if the
; 0000 005D // Project|Configure|After Build|Action: Program the Chip|Program Fuses
; 0000 005E // menu option is enabled in the IDE
; 0000 005F 
; 0000 0060 // I/O Ports initialization
; 0000 0061 ports_init();
	RCALL _ports_init
; 0000 0062 
; 0000 0063 // Timer/Counter TCA0 initialization
; 0000 0064 tca0_init();
	RCALL _tca0_init
; 0000 0065 
; 0000 0066 // Timer/Counter TCA1 initialization
; 0000 0067 tca1_init();
	RCALL _tca1_init
; 0000 0068 
; 0000 0069 // USART0 initialization
; 0000 006A usart0_init();
	RCALL _usart0_init
; 0000 006B 
; 0000 006C // SPI1 initialization
; 0000 006D spi1_init();
	RCALL _spi1_init
; 0000 006E 
; 0000 006F // Globally enable interrupts
; 0000 0070 #asm("sei")
	SEI
; 0000 0071 
; 0000 0072 while (1)
_0x3:
; 0000 0073 {
; 0000 0074 // Place your code here
; 0000 0075 
; 0000 0076 }
	RJMP _0x3
; 0000 0077 }
_0x6:
	RJMP _0x6
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
	RJMP _0x2060001
; .FEND
;void ports_init(void)
; 0002 000F {

	.CSEG
_ports_init:
; .FSTART _ports_init
; 0002 0010 // PORTA initialization
; 0002 0011 // OUT register
; 0002 0012 PORTA.OUT=0x10;
	LDI  R30,LOW(16)
	STS  1028,R30
; 0002 0013 // Pin0: Input
; 0002 0014 // Pin1: Input
; 0002 0015 // Pin2: Output
; 0002 0016 // Pin3: Input
; 0002 0017 // Pin4: Output
; 0002 0018 // Pin5: Input
; 0002 0019 // Pin6: Input
; 0002 001A // Pin7: Output
; 0002 001B PORTA.DIR=0x94;
	LDI  R30,LOW(148)
	STS  1024,R30
; 0002 001C // Pin0 Inverted: Off
; 0002 001D // Pin0 Pullup on input: Off
; 0002 001E // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 001F // Pin0 Input level: Schmitt Tg.
; 0002 0020 PORTA.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1040,R30
; 0002 0021 // Pin1 Inverted: Off
; 0002 0022 // Pin1 Pullup on input: Off
; 0002 0023 // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0024 // Pin1 Input level: Schmitt Tg.
; 0002 0025 PORTA.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1041,R30
; 0002 0026 // Pin2 Inverted: Off
; 0002 0027 // Pin2 Pullup on input: Off
; 0002 0028 // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0029 // Pin2 Input level: Schmitt Tg.
; 0002 002A PORTA.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1042,R30
; 0002 002B // Pin3 Inverted: Off
; 0002 002C // Pin3 Pullup on input: On
; 0002 002D // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 002E // Pin3 Input level: Schmitt Tg.
; 0002 002F PORTA.PIN3CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1043,R30
; 0002 0030 // Pin4 Inverted: Off
; 0002 0031 // Pin4 Pullup on input: Off
; 0002 0032 // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0033 // Pin4 Input level: Schmitt Tg.
; 0002 0034 PORTA.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1044,R30
; 0002 0035 // Pin5 Inverted: Off
; 0002 0036 // Pin5 Pullup on input: On
; 0002 0037 // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0038 // Pin5 Input level: Schmitt Tg.
; 0002 0039 PORTA.PIN5CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1045,R30
; 0002 003A // Pin6 Inverted: Off
; 0002 003B // Pin6 Pullup on input: On
; 0002 003C // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 003D // Pin6 Input level: Schmitt Tg.
; 0002 003E PORTA.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1046,R30
; 0002 003F // Pin7 Inverted: Off
; 0002 0040 // Pin7 Pullup on input: Off
; 0002 0041 // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0042 // Pin7 Input level: Schmitt Tg.
; 0002 0043 PORTA.PIN7CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1047,R30
; 0002 0044 
; 0002 0045 // PORTB initialization
; 0002 0046 // OUT register
; 0002 0047 PORTB.OUT=0x00;
	STS  1060,R30
; 0002 0048 // Pin0: Output
; 0002 0049 // Pin1: Output
; 0002 004A // Pin2: Output
; 0002 004B // Pin3: Output
; 0002 004C // Pin4: Output
; 0002 004D // Pin5: Output
; 0002 004E // Pin6: Output
; 0002 004F // Pin7: Output
; 0002 0050 PORTB.DIR=0xFF;
	LDI  R30,LOW(255)
	STS  1056,R30
; 0002 0051 // Pin0 Inverted: Off
; 0002 0052 // Pin0 Pullup on input: Off
; 0002 0053 // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0054 // Pin0 Input level: Schmitt Tg.
; 0002 0055 PORTB.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1072,R30
; 0002 0056 // Pin1 Inverted: Off
; 0002 0057 // Pin1 Pullup on input: Off
; 0002 0058 // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0059 // Pin1 Input level: Schmitt Tg.
; 0002 005A PORTB.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1073,R30
; 0002 005B // Pin2 Inverted: Off
; 0002 005C // Pin2 Pullup on input: Off
; 0002 005D // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 005E // Pin2 Input level: Schmitt Tg.
; 0002 005F PORTB.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1074,R30
; 0002 0060 // Pin3 Inverted: Off
; 0002 0061 // Pin3 Pullup on input: Off
; 0002 0062 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0063 // Pin3 Input level: Schmitt Tg.
; 0002 0064 PORTB.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1075,R30
; 0002 0065 // Pin4 Inverted: Off
; 0002 0066 // Pin4 Pullup on input: Off
; 0002 0067 // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0068 // Pin4 Input level: Schmitt Tg.
; 0002 0069 PORTB.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1076,R30
; 0002 006A // Pin5 Inverted: Off
; 0002 006B // Pin5 Pullup on input: Off
; 0002 006C // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 006D // Pin5 Input level: Schmitt Tg.
; 0002 006E PORTB.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1077,R30
; 0002 006F // Pin6 Inverted: Off
; 0002 0070 // Pin6 Pullup on input: On
; 0002 0071 // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0072 // Pin6 Input level: Schmitt Tg.
; 0002 0073 PORTB.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1078,R30
; 0002 0074 // Pin7 Inverted: Off
; 0002 0075 // Pin7 Pullup on input: On
; 0002 0076 // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0077 // Pin7 Input level: Schmitt Tg.
; 0002 0078 PORTB.PIN7CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1079,R30
; 0002 0079 
; 0002 007A // PORTC initialization
; 0002 007B // OUT register
; 0002 007C PORTC.OUT=0x08;
	STS  1092,R30
; 0002 007D // Pin0: Output
; 0002 007E // Pin1: Input
; 0002 007F // Pin2: Output
; 0002 0080 // Pin3: Output
; 0002 0081 // Pin4: Input
; 0002 0082 // Pin5: Output
; 0002 0083 // Pin6: Output
; 0002 0084 // Pin7: Output
; 0002 0085 PORTC.DIR=0xED;
	LDI  R30,LOW(237)
	STS  1088,R30
; 0002 0086 // Pin0 Inverted: Off
; 0002 0087 // Pin0 Pullup on input: Off
; 0002 0088 // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0089 // Pin0 Input level: Schmitt Tg.
; 0002 008A PORTC.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1104,R30
; 0002 008B // Pin1 Inverted: Off
; 0002 008C // Pin1 Pullup on input: On
; 0002 008D // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 008E // Pin1 Input level: Schmitt Tg.
; 0002 008F PORTC.PIN1CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1105,R30
; 0002 0090 // Pin2 Inverted: Off
; 0002 0091 // Pin2 Pullup on input: Off
; 0002 0092 // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0093 // Pin2 Input level: Schmitt Tg.
; 0002 0094 PORTC.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1106,R30
; 0002 0095 // Pin3 Inverted: Off
; 0002 0096 // Pin3 Pullup on input: Off
; 0002 0097 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0098 // Pin3 Input level: Schmitt Tg.
; 0002 0099 PORTC.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1107,R30
; 0002 009A // Pin4 Inverted: Off
; 0002 009B // Pin4 Pullup on input: On
; 0002 009C // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 009D // Pin4 Input level: Schmitt Tg.
; 0002 009E PORTC.PIN4CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1108,R30
; 0002 009F // Pin5 Inverted: Off
; 0002 00A0 // Pin5 Pullup on input: Off
; 0002 00A1 // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00A2 // Pin5 Input level: Schmitt Tg.
; 0002 00A3 PORTC.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1109,R30
; 0002 00A4 // Pin6 Inverted: Off
; 0002 00A5 // Pin6 Pullup on input: Off
; 0002 00A6 // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00A7 // Pin6 Input level: Schmitt Tg.
; 0002 00A8 PORTC.PIN6CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1110,R30
; 0002 00A9 // Pin7 Inverted: Off
; 0002 00AA // Pin7 Pullup on input: Off
; 0002 00AB // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00AC // Pin7 Input level: Schmitt Tg.
; 0002 00AD PORTC.PIN7CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1111,R30
; 0002 00AE 
; 0002 00AF // PORTD initialization
; 0002 00B0 // OUT register
; 0002 00B1 PORTD.OUT=0x00;
	STS  1124,R30
; 0002 00B2 // Pin0: Input
; 0002 00B3 // Pin1: Input
; 0002 00B4 // Pin2: Input
; 0002 00B5 // Pin3: Input
; 0002 00B6 // Pin4: Input
; 0002 00B7 // Pin5: Input
; 0002 00B8 // Pin6: Input
; 0002 00B9 // Pin7: Input
; 0002 00BA PORTD.DIR=0x00;
	STS  1120,R30
; 0002 00BB // Pin0 Inverted: Off
; 0002 00BC // Pin0 Pullup on input: On
; 0002 00BD // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00BE // Pin0 Input level: Schmitt Tg.
; 0002 00BF PORTD.PIN0CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1136,R30
; 0002 00C0 // Pin1 Inverted: Off
; 0002 00C1 // Pin1 Pullup on input: On
; 0002 00C2 // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00C3 // Pin1 Input level: Schmitt Tg.
; 0002 00C4 PORTD.PIN1CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1137,R30
; 0002 00C5 // Pin2 Inverted: Off
; 0002 00C6 // Pin2 Pullup on input: On
; 0002 00C7 // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00C8 // Pin2 Input level: Schmitt Tg.
; 0002 00C9 PORTD.PIN2CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1138,R30
; 0002 00CA // Pin3 Inverted: Off
; 0002 00CB // Pin3 Pullup on input: On
; 0002 00CC // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00CD // Pin3 Input level: Schmitt Tg.
; 0002 00CE PORTD.PIN3CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1139,R30
; 0002 00CF // Pin4 Inverted: Off
; 0002 00D0 // Pin4 Pullup on input: On
; 0002 00D1 // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00D2 // Pin4 Input level: Schmitt Tg.
; 0002 00D3 PORTD.PIN4CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1140,R30
; 0002 00D4 // Pin5 Inverted: Off
; 0002 00D5 // Pin5 Pullup on input: On
; 0002 00D6 // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00D7 // Pin5 Input level: Schmitt Tg.
; 0002 00D8 PORTD.PIN5CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1141,R30
; 0002 00D9 // Pin6 Inverted: Off
; 0002 00DA // Pin6 Pullup on input: On
; 0002 00DB // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00DC // Pin6 Input level: Schmitt Tg.
; 0002 00DD PORTD.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1142,R30
; 0002 00DE // Pin7 Inverted: Off
; 0002 00DF // Pin7 Pullup on input: On
; 0002 00E0 // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00E1 // Pin7 Input level: Schmitt Tg.
; 0002 00E2 PORTD.PIN7CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1143,R30
; 0002 00E3 
; 0002 00E4 // PORTE initialization
; 0002 00E5 // OUT register
; 0002 00E6 PORTE.OUT=0x00;
	LDI  R30,LOW(0)
	STS  1156,R30
; 0002 00E7 // Pin0: Input
; 0002 00E8 // Pin1: Input
; 0002 00E9 // Pin2: Input
; 0002 00EA // Pin3: Input
; 0002 00EB // Pin4: Input
; 0002 00EC // Pin5: Input
; 0002 00ED // Pin6: Input
; 0002 00EE // Pin7: Input
; 0002 00EF PORTE.DIR=0x00;
	STS  1152,R30
; 0002 00F0 // Pin0 Inverted: Off
; 0002 00F1 // Pin0 Pullup on input: On
; 0002 00F2 // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00F3 // Pin0 Input level: Schmitt Tg.
; 0002 00F4 PORTE.PIN0CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1168,R30
; 0002 00F5 // Pin1 Inverted: Off
; 0002 00F6 // Pin1 Pullup on input: On
; 0002 00F7 // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00F8 // Pin1 Input level: Schmitt Tg.
; 0002 00F9 PORTE.PIN1CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1169,R30
; 0002 00FA // Pin2 Inverted: Off
; 0002 00FB // Pin2 Pullup on input: On
; 0002 00FC // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 00FD // Pin2 Input level: Schmitt Tg.
; 0002 00FE PORTE.PIN2CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1170,R30
; 0002 00FF // Pin3 Inverted: Off
; 0002 0100 // Pin3 Pullup on input: On
; 0002 0101 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0102 // Pin3 Input level: Schmitt Tg.
; 0002 0103 PORTE.PIN3CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1171,R30
; 0002 0104 // Pin4 Inverted: Off
; 0002 0105 // Pin4 Pullup on input: On
; 0002 0106 // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0107 // Pin4 Input level: Schmitt Tg.
; 0002 0108 PORTE.PIN4CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1172,R30
; 0002 0109 // Pin5 Inverted: Off
; 0002 010A // Pin5 Pullup on input: On
; 0002 010B // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 010C // Pin5 Input level: Schmitt Tg.
; 0002 010D PORTE.PIN5CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1173,R30
; 0002 010E // Pin6 Inverted: Off
; 0002 010F // Pin6 Pullup on input: On
; 0002 0110 // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0111 // Pin6 Input level: Schmitt Tg.
; 0002 0112 PORTE.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1174,R30
; 0002 0113 // Pin7 Inverted: Off
; 0002 0114 // Pin7 Pullup on input: On
; 0002 0115 // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0116 // Pin7 Input level: Schmitt Tg.
; 0002 0117 PORTE.PIN7CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1175,R30
; 0002 0118 
; 0002 0119 // PORTF initialization
; 0002 011A // OUT register
; 0002 011B PORTF.OUT=0x00;
	LDI  R30,LOW(0)
	STS  1188,R30
; 0002 011C // Pin0: Input
; 0002 011D // Pin1: Output
; 0002 011E // Pin2: Output
; 0002 011F // Pin3: Output
; 0002 0120 // Pin4: Output
; 0002 0121 // Pin5: Output
; 0002 0122 // Pin6: Input
; 0002 0123 PORTF.DIR=0x3E;
	LDI  R30,LOW(62)
	STS  1184,R30
; 0002 0124 // Pin0 Inverted: Off
; 0002 0125 // Pin0 Pullup on input: On
; 0002 0126 // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0127 // Pin0 Input level: Schmitt Tg.
; 0002 0128 PORTF.PIN0CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(8)
	STS  1200,R30
; 0002 0129 // Pin1 Inverted: Off
; 0002 012A // Pin1 Pullup on input: Off
; 0002 012B // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 012C // Pin1 Input level: Schmitt Tg.
; 0002 012D PORTF.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1201,R30
; 0002 012E // Pin2 Inverted: Off
; 0002 012F // Pin2 Pullup on input: Off
; 0002 0130 // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0131 // Pin2 Input level: Schmitt Tg.
; 0002 0132 PORTF.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1202,R30
; 0002 0133 // Pin3 Inverted: Off
; 0002 0134 // Pin3 Pullup on input: Off
; 0002 0135 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0136 // Pin3 Input level: Schmitt Tg.
; 0002 0137 PORTF.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1203,R30
; 0002 0138 // Pin4 Inverted: Off
; 0002 0139 // Pin4 Pullup on input: Off
; 0002 013A // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 013B // Pin4 Input level: Schmitt Tg.
; 0002 013C PORTF.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1204,R30
; 0002 013D // Pin5 Inverted: Off
; 0002 013E // Pin5 Pullup on input: Off
; 0002 013F // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0140 // Pin5 Input level: Schmitt Tg.
; 0002 0141 PORTF.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1205,R30
; 0002 0142 // Pin6 Inverted: Off
; 0002 0143 // Pin6 Pullup on input: Off
; 0002 0144 // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0145 // Pin6 Input level: Schmitt Tg.
; 0002 0146 PORTF.PIN6CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1206,R30
; 0002 0147 
; 0002 0148 // PORTG initialization
; 0002 0149 // OUT register
; 0002 014A PORTG.OUT=0x00;
	STS  1220,R30
; 0002 014B // Pin0: Output
; 0002 014C // Pin1: Output
; 0002 014D // Pin2: Output
; 0002 014E // Pin3: Output
; 0002 014F // Pin4: Output
; 0002 0150 // Pin5: Output
; 0002 0151 // Pin6: Output
; 0002 0152 // Pin7: Output
; 0002 0153 PORTG.DIR=0xFF;
	LDI  R30,LOW(255)
	STS  1216,R30
; 0002 0154 // Pin0 Inverted: Off
; 0002 0155 // Pin0 Pullup on input: Off
; 0002 0156 // Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0157 // Pin0 Input level: Schmitt Tg.
; 0002 0158 PORTG.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	LDI  R30,LOW(0)
	STS  1232,R30
; 0002 0159 // Pin1 Inverted: Off
; 0002 015A // Pin1 Pullup on input: Off
; 0002 015B // Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 015C // Pin1 Input level: Schmitt Tg.
; 0002 015D PORTG.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1233,R30
; 0002 015E // Pin2 Inverted: Off
; 0002 015F // Pin2 Pullup on input: Off
; 0002 0160 // Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0161 // Pin2 Input level: Schmitt Tg.
; 0002 0162 PORTG.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1234,R30
; 0002 0163 // Pin3 Inverted: Off
; 0002 0164 // Pin3 Pullup on input: Off
; 0002 0165 // Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0166 // Pin3 Input level: Schmitt Tg.
; 0002 0167 PORTG.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1235,R30
; 0002 0168 // Pin4 Inverted: Off
; 0002 0169 // Pin4 Pullup on input: Off
; 0002 016A // Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 016B // Pin4 Input level: Schmitt Tg.
; 0002 016C PORTG.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1236,R30
; 0002 016D // Pin5 Inverted: Off
; 0002 016E // Pin5 Pullup on input: Off
; 0002 016F // Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0170 // Pin5 Input level: Schmitt Tg.
; 0002 0171 PORTG.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1237,R30
; 0002 0172 // Pin6 Inverted: Off
; 0002 0173 // Pin6 Pullup on input: Off
; 0002 0174 // Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 0175 // Pin6 Input level: Schmitt Tg.
; 0002 0176 PORTG.PIN6CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1238,R30
; 0002 0177 // Pin7 Inverted: Off
; 0002 0178 // Pin7 Pullup on input: Off
; 0002 0179 // Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
; 0002 017A // Pin7 Input level: Schmitt Tg.
; 0002 017B PORTG.PIN7CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
	STS  1239,R30
; 0002 017C }
	RET
; .FEND
;void tca_disable(TCA_t *ptca)
; 0003 000F {

	.CSEG
_tca_disable:
; .FSTART _tca_disable
; 0003 0010 // Timer/Counter TCA is disabled
; 0003 0011 ptca->SINGLE.CTRLA=0<<TCA_SINGLE_ENABLE_bp;
	ST   -Y,R17
	ST   -Y,R16
	MOVW R16,R26
;	*ptca -> R16,R17
	LDI  R30,LOW(0)
	ST   X,R30
; 0003 0012 // Operate in 16-bit mode
; 0003 0013 ptca->SINGLE.CTRLD=0<<TCA_SINGLE_SPLITM_bp;
	ADIW R26,3
	ST   X,R30
; 0003 0014 // Issue a reset command
; 0003 0015 ptca->SINGLE.CTRLECLR=TCA_SINGLE_CMD_RESET_gc;
	MOVW R26,R16
	ADIW R26,4
	LDI  R30,LOW(12)
	ST   X,R30
; 0003 0016 }
_0x2060001:
	LD   R16,Y+
	LD   R17,Y+
	RET
; .FEND
;void tca0_init(void)
; 0003 001A {
_tca0_init:
; .FSTART _tca0_init
; 0003 001B // First disable and reset the Timer/Counter TCA0
; 0003 001C // Use 16-bit mode
; 0003 001D tca_disable(&TCA0);
	LDI  R26,LOW(2560)
	LDI  R27,HIGH(2560)
	RCALL _tca_disable
; 0003 001E 
; 0003 001F // Clock divider: 1
; 0003 0020 // Clock frequency: 4000,960 kHz
; 0003 0021 // TCA0 runs in standby: Off
; 0003 0022 TCA0.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1_gc+(0<<TCA_SINGLE_RUNSTDBY_bp);
	LDI  R30,LOW(0)
	STS  2560,R30
; 0003 0023 
; 0003 0024 // Operating mode: Frequency Generation 16-bit OVF=TOP (CMP0)
; 0003 0025 // Set the waveform outputs configuration:
; 0003 0026 // WO0: Off
; 0003 0027 // WO1: Off
; 0003 0028 // WO2: PORTA, Pin 2
; 0003 0029 TCA0.SINGLE.CTRLB=TCA_SINGLE_WGMODE_FRQ_gc+
; 0003 002A (0<<TCA_SINGLE_CMP0EN_bp)+
; 0003 002B (0<<TCA_SINGLE_CMP1EN_bp)+
; 0003 002C (1<<TCA_SINGLE_CMP2EN_bp);
	LDI  R30,LOW(65)
	STS  2561,R30
; 0003 002D 
; 0003 002E // Set the waveform outputs mapping
; 0003 002F PORTMUX.TCAROUTEA=(PORTMUX.TCAROUTEA & (~PORTMUX_TCA0_gm)) | PORTMUX_TCA0_PORTA_gc;
	LDS  R30,1510
	ANDI R30,LOW(0xF8)
	STS  1510,R30
; 0003 0030 // Note: The configuration for the waveform output signals
; 0003 0031 // is set in the ports_init function from ports_init.c
; 0003 0032 
; 0003 0033 // Set the Timer Counter register
; 0003 0034 TCA0.SINGLE.CNT=0x00;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	STS  2592,R30
	STS  2592+1,R31
; 0003 0035 
; 0003 0036 // In Frequency Generation mode the Timer Compare 0 register sets the
; 0003 0037 // specified frequency for the WO0, WO1, WO2 outputs: 1000 kHz
; 0003 0038 // Obtained frequency: 1000,24 kHz, -0,02 % error
; 0003 0039 TCA0.SINGLE.CMP0=0x01;
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	STS  2600,R30
	STS  2600+1,R31
; 0003 003A 
; 0003 003B // The Timer Compare 1 register sets the specified
; 0003 003C // phase for the WO1 output relative to WO0: 0,00°
; 0003 003D TCA0.SINGLE.CMP1=0x00;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	STS  2602,R30
	STS  2602+1,R31
; 0003 003E 
; 0003 003F // The Timer Compare 2 register sets the specified
; 0003 0040 // phase for the WO2 output relative to WO0: 50,00°
; 0003 0041 TCA0.SINGLE.CMP2=0x00;
	STS  2604,R30
	STS  2604+1,R31
; 0003 0042 
; 0003 0043 // Set the Event Control register
; 0003 0044 // Event input A: No action
; 0003 0045 // Event input B: No action
; 0003 0046 TCA0.SINGLE.EVCTRL=(0<<TCA_SINGLE_CNTAEI_bp)+(0<<TCA_SINGLE_CNTBEI_bp);
	STS  2569,R30
; 0003 0047 
; 0003 0048 // Set TCA0 interrupts:
; 0003 0049 // Overflow interrupt: Off
; 0003 004A // Compare Channel 0 interrupt: Off
; 0003 004B // Compare Channel 1 interrupt: Off
; 0003 004C // Compare Channel 2 interrupt: Off
; 0003 004D TCA0.SINGLE.INTCTRL=
; 0003 004E (0<<TCA_SINGLE_OVF_bp)+
; 0003 004F (0<<TCA_SINGLE_CMP0_bp)+
; 0003 0050 (0<<TCA_SINGLE_CMP1_bp)+
; 0003 0051 (0<<TCA_SINGLE_CMP2_bp);
	STS  2570,R30
; 0003 0052 
; 0003 0053 // Initialization finished, enable TCA0
; 0003 0054 TCA0.SINGLE.CTRLA|=TCA_SINGLE_ENABLE_bm;
	LDS  R30,2560
	ORI  R30,1
	STS  2560,R30
; 0003 0055 }
	RET
; .FEND
;void tca1_init(void)
; 0003 0059 {
_tca1_init:
; .FSTART _tca1_init
; 0003 005A // First disable and reset the Timer/Counter TCA1
; 0003 005B // Use 16-bit mode
; 0003 005C tca_disable(&TCA1);
	LDI  R26,LOW(2624)
	LDI  R27,HIGH(2624)
	RCALL _tca_disable
; 0003 005D 
; 0003 005E // Clock divider: 1
; 0003 005F // Clock frequency: 4000,960 kHz
; 0003 0060 // TCA1 runs in standby: Off
; 0003 0061 TCA1.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1_gc+(0<<TCA_SINGLE_RUNSTDBY_bp);
	LDI  R30,LOW(0)
	STS  2624,R30
; 0003 0062 
; 0003 0063 // Operating mode: Normal 16-bit OVF=TOP
; 0003 0064 TCA1.SINGLE.CTRLB=TCA_SINGLE_WGMODE_NORMAL_gc;
	STS  2625,R30
; 0003 0065 
; 0003 0066 // Set the Timer Counter register
; 0003 0067 TCA1.SINGLE.CNT=0x00;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	STS  2656,R30
	STS  2656+1,R31
; 0003 0068 
; 0003 0069 // Set the Timer Period register
; 0003 006A // Specified period: 1 ms
; 0003 006B // Obtained: 1,00001 ms, 0,00 % error
; 0003 006C TCA1.SINGLE.PER=0xFA0;
	LDI  R30,LOW(4000)
	LDI  R31,HIGH(4000)
	STS  2662,R30
	STS  2662+1,R31
; 0003 006D 
; 0003 006E // Set the Event Control register
; 0003 006F // Event input A: No action
; 0003 0070 // Event input B: No action
; 0003 0071 TCA1.SINGLE.EVCTRL=(0<<TCA_SINGLE_CNTAEI_bp)+(0<<TCA_SINGLE_CNTBEI_bp);
	LDI  R30,LOW(0)
	STS  2633,R30
; 0003 0072 
; 0003 0073 // Set TCA1 interrupts:
; 0003 0074 // Overflow interrupt: On
; 0003 0075 // Compare Channel 0 interrupt: Off
; 0003 0076 // Compare Channel 1 interrupt: Off
; 0003 0077 // Compare Channel 2 interrupt: Off
; 0003 0078 TCA1.SINGLE.INTCTRL=
; 0003 0079 (1<<TCA_SINGLE_OVF_bp)+
; 0003 007A (0<<TCA_SINGLE_CMP0_bp)+
; 0003 007B (0<<TCA_SINGLE_CMP1_bp)+
; 0003 007C (0<<TCA_SINGLE_CMP2_bp);
	LDI  R30,LOW(1)
	STS  2634,R30
; 0003 007D 
; 0003 007E // Initialization finished, enable TCA1
; 0003 007F TCA1.SINGLE.CTRLA|=TCA_SINGLE_ENABLE_bm;
	LDS  R30,2624
	ORI  R30,1
	STS  2624,R30
; 0003 0080 }
	RET
; .FEND
;interrupt [(48)  ] void tca1_ovf_isr(void)
; 0003 0084 {
_tca1_ovf_isr:
; .FSTART _tca1_ovf_isr
	ST   -Y,R30
; 0003 0085 // Ensure that the Overflow/Underflow interrupt flag is cleared
; 0003 0086 TCA1.SINGLE.INTFLAGS=TCA_SINGLE_OVF_bm;
	LDI  R30,LOW(1)
	STS  2635,R30
; 0003 0087 
; 0003 0088 // Write your code here
; 0003 0089 
; 0003 008A }
	LD   R30,Y+
	RETI
; .FEND
;void usart0_init(void)
; 0004 0012 {

	.CSEG
_usart0_init:
; .FSTART _usart0_init
; 0004 0013 // Note: The correct PORTA direction for the USART signals
; 0004 0014 // is configured in the ports_init function.
; 0004 0015 
; 0004 0016 // The USART0 signals are remapped:
; 0004 0017 // RxD: PORTA.5, TxD: PORTA.4
; 0004 0018 PORTMUX.USARTROUTEA=(PORTMUX.USARTROUTEA & ~PORTMUX_USART0_gm) | (1<<PORTMUX_USART0_gp);
	LDS  R30,1506
	ANDI R30,LOW(0xFC)
	ORI  R30,1
	STS  1506,R30
; 0004 0019 
; 0004 001A // Transmitter is enabled
; 0004 001B // Set TxD=1
; 0004 001C PORTA.OUTSET=0x10;
	LDI  R30,LOW(16)
	STS  1029,R30
; 0004 001D 
; 0004 001E // Communication mode: Asynchronous USART
; 0004 001F // USART0 Mode: Asynchronous USART
; 0004 0020 // Data bits: 8
; 0004 0021 // Stop bits: 1
; 0004 0022 // Parity: Disabled
; 0004 0023 USART0.CTRLC=USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc | USART_CHSIZE_8BIT_gc;
	LDI  R30,LOW(3)
	STS  2055,R30
; 0004 0024 
; 0004 0025 // Receive complete interrupt: On
; 0004 0026 // Note: The transmitter Data Register Empty interrupt will be enabled later
; 0004 0027 // RS485 Mode: TxD buffer direction is controlled externally
; 0004 0028 USART0.CTRLA=(1<<USART_RXCIE_bp) | USART_RS485_EXT_gc;
	LDI  R30,LOW(129)
	STS  2053,R30
; 0004 0029 
; 0004 002A // Required Baud rate: 9600
; 0004 002B // Real Baud Rate: 9600,4 (x1 Mode), Error: 0,0 %
; 0004 002C USART0.BAUD=0x0683;
	LDI  R30,LOW(1667)
	LDI  R31,HIGH(1667)
	STS  2056,R30
	STS  2056+1,R31
; 0004 002D 
; 0004 002E // Receiver: On
; 0004 002F // Transmitter: On
; 0004 0030 // TxD open drain: Off
; 0004 0031 // Double transmission speed mode: Off
; 0004 0032 // Multi-processor communication mode: Off
; 0004 0033 USART0.CTRLB=(1<<USART_RXEN_bp) | (1<<USART_TXEN_bp) | (0<<USART_ODME_bp) | USART_RXMODE_NORMAL_gc | (0<<USART_MPCM_bp);
	LDI  R30,LOW(192)
	STS  2054,R30
; 0004 0034 }
	RET
; .FEND
;interrupt [(22)  ] void usart0_rx_isr(void)
; 0004 004A {
_usart0_rx_isr:
; .FSTART _usart0_rx_isr
	ST   -Y,R26
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0004 004B unsigned char status;
; 0004 004C char data;
; 0004 004D 
; 0004 004E status=USART0.RXDATAH;
	ST   -Y,R17
	ST   -Y,R16
;	status -> R17
;	data -> R16
	LDS  R17,2049
; 0004 004F data=USART0.RXDATAL;
	LDS  R16,2048
; 0004 0050 if ((status & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm)) == 0)
	MOV  R30,R17
	ANDI R30,LOW(0x46)
	BRNE _0x80003
; 0004 0051 {
; 0004 0052 rx_buffer_usart0[rx_wr_index_usart0++]=data;
	LDS  R30,_rx_wr_index_usart0
	SUBI R30,-LOW(1)
	STS  _rx_wr_index_usart0,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_rx_buffer_usart0)
	SBCI R31,HIGH(-_rx_buffer_usart0)
	ST   Z,R16
; 0004 0053 #if RX_BUFFER_SIZE_USART0 == 256
; 0004 0054 // special case for receiver buffer size=256
; 0004 0055 if (++rx_counter_usart0 == 0) rx_buffer_overflow_usart0=1;
; 0004 0056 #else
; 0004 0057 if (rx_wr_index_usart0 == RX_BUFFER_SIZE_USART0) rx_wr_index_usart0=0;
	LDS  R26,_rx_wr_index_usart0
	CPI  R26,LOW(0x80)
	BRNE _0x80004
	LDI  R30,LOW(0)
	STS  _rx_wr_index_usart0,R30
; 0004 0058 if (++rx_counter_usart0 == RX_BUFFER_SIZE_USART0)
_0x80004:
	LDS  R26,_rx_counter_usart0
	SUBI R26,-LOW(1)
	STS  _rx_counter_usart0,R26
	CPI  R26,LOW(0x80)
	BRNE _0x80005
; 0004 0059 {
; 0004 005A rx_counter_usart0=0;
	LDI  R30,LOW(0)
	STS  _rx_counter_usart0,R30
; 0004 005B rx_buffer_overflow_usart0=1;
	SBI  0x1C,0
; 0004 005C }
; 0004 005D #endif
; 0004 005E }
_0x80005:
; 0004 005F }
_0x80003:
	LD   R16,Y+
	LD   R17,Y+
	RJMP _0x80017
; .FEND
;char getchar(void)
; 0004 0067 {
; 0004 0068 char data;
; 0004 0069 
; 0004 006A while (rx_counter_usart0==0);
;	data -> R17
; 0004 006B data=rx_buffer_usart0[rx_rd_index_usart0++];
; 0004 006C #if RX_BUFFER_SIZE_USART0 != 256
; 0004 006D if (rx_rd_index_usart0 == RX_BUFFER_SIZE_USART0) rx_rd_index_usart0=0;
; 0004 006E #endif
; 0004 006F #asm("cli")
; 0004 0070 --rx_counter_usart0;
; 0004 0071 #asm("sei")
; 0004 0072 return data;
; 0004 0073 }
;interrupt [(23)  ] void usart0_tx_isr(void)
; 0004 0087 {
_usart0_tx_isr:
; .FSTART _usart0_tx_isr
	ST   -Y,R26
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0004 0088 if (tx_counter_usart0)
	LDS  R30,_tx_counter_usart0
	CPI  R30,0
	BREQ _0x8000C
; 0004 0089 {
; 0004 008A --tx_counter_usart0;
	LDS  R30,_tx_counter_usart0
	SUBI R30,LOW(1)
	STS  _tx_counter_usart0,R30
; 0004 008B USART0.TXDATAL=tx_buffer_usart0[tx_rd_index_usart0++];
	LDS  R30,_tx_rd_index_usart0
	SUBI R30,-LOW(1)
	STS  _tx_rd_index_usart0,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buffer_usart0)
	SBCI R31,HIGH(-_tx_buffer_usart0)
	LD   R30,Z
	STS  2050,R30
; 0004 008C #if TX_BUFFER_SIZE_USART0 != 256
; 0004 008D if (tx_rd_index_usart0 == TX_BUFFER_SIZE_USART0) tx_rd_index_usart0=0;
	LDS  R26,_tx_rd_index_usart0
	CPI  R26,LOW(0x80)
	BRNE _0x8000D
	LDI  R30,LOW(0)
	STS  _tx_rd_index_usart0,R30
; 0004 008E #endif
; 0004 008F }
_0x8000D:
; 0004 0090 else
	RJMP _0x8000E
_0x8000C:
; 0004 0091 USART0.CTRLA&= ~USART_DREIE_bm;
	LDS  R30,2053
	ANDI R30,0xDF
	STS  2053,R30
; 0004 0092 }
_0x8000E:
_0x80017:
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R26,Y+
	RETI
; .FEND
;void putchar(char c)
; 0004 009A {
; 0004 009B while (tx_counter_usart0 == TX_BUFFER_SIZE_USART0);
;	c -> R17
; 0004 009C #asm("cli")
; 0004 009D if (tx_counter_usart0 || ((USART0.STATUS & USART_DREIF_bm)==0))
; 0004 009E {
; 0004 009F tx_buffer_usart0[tx_wr_index_usart0++]=c;
; 0004 00A0 #if TX_BUFFER_SIZE_USART0 != 256
; 0004 00A1 if (tx_wr_index_usart0 == TX_BUFFER_SIZE_USART0) tx_wr_index_usart0=0;
; 0004 00A2 #endif
; 0004 00A3 ++tx_counter_usart0;
; 0004 00A4 }
; 0004 00A5 else
; 0004 00A6 {
; 0004 00A7 USART0.CTRLA|=USART_DREIE_bm;
; 0004 00A8 USART0.TXDATAL=c;
; 0004 00A9 }
; 0004 00AA #asm("sei")
; 0004 00AB }
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
; 0005 002E // Transmit data in Master mode
; 0005 002F SPI1.DATA=c;
;	c -> R17
; 0005 0030 // Wait for the data to be transmitted/received
; 0005 0031 while ((SPI1.INTFLAGS & SPI_IF_bm)==0);
; 0005 0032 // Return the received data
; 0005 0033 return SPI1.DATA;
; 0005 0034 }

	.CSEG

	.CSEG

	.CSEG

	.DSEG
_rx_buffer_usart0:
	.BYTE 0x80
_rx_wr_index_usart0:
	.BYTE 0x1
_rx_rd_index_usart0:
	.BYTE 0x1
_rx_counter_usart0:
	.BYTE 0x1
_tx_buffer_usart0:
	.BYTE 0x80
_tx_wr_index_usart0:
	.BYTE 0x1
_tx_rd_index_usart0:
	.BYTE 0x1
_tx_counter_usart0:
	.BYTE 0x1

	.CSEG
;RUNTIME LIBRARY

	.CSEG
;END OF CODE MARKER
__END_OF_CODE:
