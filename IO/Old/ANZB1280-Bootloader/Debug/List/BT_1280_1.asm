
;CodeVisionAVR C Compiler V3.50 Advanced
;(C) Copyright 1998-2023 Pavel Haiduc, HP InfoTech S.R.L.
;http://www.hpinfotech.ro

;Build configuration    : Debug
;Chip type              : ATmega1280
;Program type           : Bootloader
;Clock frequency        : 16,000000 MHz
;Memory model           : Medium
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

	#define _MODEL_MEDIUM_

	#pragma AVRPART ADMIN PART_NAME ATmega1280
	#pragma AVRPART MEMORY PROG_FLASH 131072
	#pragma AVRPART MEMORY EEPROM 4096
	#pragma AVRPART MEMORY INT_SRAM SIZE 8192
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x200

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU EECR=0x1F
	.EQU EEDR=0x20
	.EQU EEARL=0x21
	.EQU EEARH=0x22
	.EQU SPSR=0x2D
	.EQU SPDR=0x2E
	.EQU SMCR=0x33
	.EQU MCUSR=0x34
	.EQU MCUCR=0x35
	.EQU WDTCSR=0x60
	.EQU UCSR0A=0xC0
	.EQU UDR0=0xC6
	.EQU SPMCSR=0x37
	.EQU RAMPZ=0x3B
	.EQU EIND=0x3C
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F
	.EQU XMCRA=0x74
	.EQU XMCRB=0x75
	.EQU GPIOR0=0x1E

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

	.EQU __SRAM_START=0x0200
	.EQU __SRAM_END=0x21FF
	.EQU __DSTACK_SIZE=0x0800
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.EQU __FLASH_PAGE_SIZE=0x80
	.EQU __EEPROM_PAGE_SIZE=0x08

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

	.MACRO __GETBRPF
	OUT  RAMPZ,R22
	ELPM R@0,Z
	.ENDM

	.MACRO __GETBRPF_INC
	OUT  RAMPZ,R22
	ELPM R@0,Z+
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

;GPIOR0 INITIALIZATION VALUE
	.EQU __GPIOR0_INIT=0x00

	.CSEG
	.ORG 0xF000

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000
	JMP  0xF000

_BOOT_HEADER:
	.DB  0x43,0x56,0x41,0x56,0x52,0x42,0x4F,0x4F
	.DB  0x54,0x1,0x0,0x1E,0x97,0x3,0x0,0x20
	.DB  0x0,0x1,0x20,0x0,0x1
_tbl10_G102:
	.DB  0x10,0x27,0xE8,0x3,0x64,0x0,0xA,0x0
	.DB  0x1,0x0
_tbl16_G102:
	.DB  0x0,0x10,0x0,0x1,0x10,0x0,0x1,0x0

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF THE BOOTLOADER
	LDI  R31,1
	OUT  MCUCR,R31
	LDI  R31,2
	OUT  MCUCR,R31
	STS  XMCRA,R30
	STS  XMCRB,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,LOW(__SRAM_START)
	LDI  R27,HIGH(__SRAM_START)
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GPIOR0 INITIALIZATION
	LDI  R30,__GPIOR0_INIT
	OUT  GPIOR0,R30

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
	.ORG 0xA00

	.CSEG
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.EQU __sm_adc_noise_red=0x02
	.SET power_ctrl_reg=smcr
	#endif
;void boot_callback(unsigned char boot_status)
; 0000 0027 {

	.CSEG
_boot_callback:
; .FSTART _boot_callback
; 0000 0028 // Place your code here
; 0000 0029 
; 0000 002A }
	RET
; .FEND
;void main(void)
; 0000 0032 {
_main:
; .FSTART _main
; 0000 0033 // Declare your local variables here
; 0000 0034 
; 0000 0035 // Check for entering bootloader mode or
; 0000 0036 // launching the code from the application section.
; 0000 0037 // Bringing the PORTE Pin 7 to 1 will start the bootloader.
; 0000 0038 // Otherwise the application code will be executed.
; 0000 0039 
; 0000 003A // Prepare to read the state of the input pin.
; 0000 003B // Ensure that PORTE Pin 7 is configured as an input.
; 0000 003C DDRE&= ~(1<<7);
	CBI  0xD,7
; 0000 003D 
; 0000 003E // Test pin state
; 0000 003F if ((PINE & (1<<7))==0)
	SBIC 0xC,7
	RJMP _0x3
; 0000 0040 {
; 0000 0041 // Pin is 0, execute the code from the application section
; 0000 0042 #asm("JMP  0x0")
	JMP  0x0
; 0000 0043 }
; 0000 0044 
; 0000 0045 // Crystal Oscillator division factor: 1
; 0000 0046 #pragma optsize-
_0x3:
; 0000 0047 CLKPR=(1<<CLKPCE);
	LDI  R30,LOW(128)
	STS  97,R30
; 0000 0048 CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
	LDI  R30,LOW(0)
	STS  97,R30
; 0000 0049 #ifdef _OPTIMIZE_SIZE_
; 0000 004A #pragma optsize+
; 0000 004B #endif
; 0000 004C 
; 0000 004D // Input/Output Ports initialization
; 0000 004E // Port A initialization
; 0000 004F // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 0050 DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
	OUT  0x1,R30
; 0000 0051 // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 0052 PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
	OUT  0x2,R30
; 0000 0053 
; 0000 0054 // Port B initialization
; 0000 0055 // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 0056 DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
	OUT  0x4,R30
; 0000 0057 // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 0058 PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);
	OUT  0x5,R30
; 0000 0059 
; 0000 005A // Port C initialization
; 0000 005B // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 005C DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
	OUT  0x7,R30
; 0000 005D // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 005E PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);
	OUT  0x8,R30
; 0000 005F 
; 0000 0060 // Port D initialization
; 0000 0061 // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 0062 DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
	OUT  0xA,R30
; 0000 0063 // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 0064 PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
	OUT  0xB,R30
; 0000 0065 
; 0000 0066 // Port E initialization
; 0000 0067 // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 0068 DDRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (0<<DDE2) | (0<<DDE1) | (0<<DDE0);
	OUT  0xD,R30
; 0000 0069 // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 006A PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (0<<PORTE2) | (0<<PORTE1) | (0<<PORTE0);
	OUT  0xE,R30
; 0000 006B 
; 0000 006C // Port F initialization
; 0000 006D // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 006E DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
	OUT  0x10,R30
; 0000 006F // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 0070 PORTF=(0<<PORTF7) | (0<<PORTF6) | (0<<PORTF5) | (0<<PORTF4) | (0<<PORTF3) | (0<<PORTF2) | (0<<PORTF1) | (0<<PORTF0);
	OUT  0x11,R30
; 0000 0071 
; 0000 0072 // Port G initialization
; 0000 0073 // Function: Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 0074 DDRG=(0<<DDG5) | (0<<DDG4) | (0<<DDG3) | (0<<DDG2) | (0<<DDG1) | (0<<DDG0);
	OUT  0x13,R30
; 0000 0075 // State: Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 0076 PORTG=(0<<PORTG5) | (0<<PORTG4) | (0<<PORTG3) | (0<<PORTG2) | (0<<PORTG1) | (0<<PORTG0);
	OUT  0x14,R30
; 0000 0077 
; 0000 0078 // Port H initialization
; 0000 0079 // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 007A DDRH=(0<<DDH7) | (0<<DDH6) | (0<<DDH5) | (0<<DDH4) | (0<<DDH3) | (0<<DDH2) | (0<<DDH1) | (0<<DDH0);
	STS  257,R30
; 0000 007B // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 007C PORTH=(0<<PORTH7) | (0<<PORTH6) | (0<<PORTH5) | (0<<PORTH4) | (0<<PORTH3) | (0<<PORTH2) | (0<<PORTH1) | (0<<PORTH0);
	STS  258,R30
; 0000 007D 
; 0000 007E // Port J initialization
; 0000 007F // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 0080 DDRJ=(0<<DDJ7) | (0<<DDJ6) | (0<<DDJ5) | (0<<DDJ4) | (0<<DDJ3) | (0<<DDJ2) | (0<<DDJ1) | (0<<DDJ0);
	STS  260,R30
; 0000 0081 // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 0082 PORTJ=(0<<PORTJ7) | (0<<PORTJ6) | (0<<PORTJ5) | (0<<PORTJ4) | (0<<PORTJ3) | (0<<PORTJ2) | (0<<PORTJ1) | (0<<PORTJ0);
	STS  261,R30
; 0000 0083 
; 0000 0084 // Port K initialization
; 0000 0085 // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 0086 DDRK=(0<<DDK7) | (0<<DDK6) | (0<<DDK5) | (0<<DDK4) | (0<<DDK3) | (0<<DDK2) | (0<<DDK1) | (0<<DDK0);
	STS  263,R30
; 0000 0087 // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 0088 PORTK=(0<<PORTK7) | (0<<PORTK6) | (0<<PORTK5) | (0<<PORTK4) | (0<<PORTK3) | (0<<PORTK2) | (0<<PORTK1) | (0<<PORTK0);
	STS  264,R30
; 0000 0089 
; 0000 008A // Port L initialization
; 0000 008B // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 008C DDRL=(0<<DDL7) | (0<<DDL6) | (0<<DDL5) | (0<<DDL4) | (0<<DDL3) | (0<<DDL2) | (0<<DDL1) | (0<<DDL0);
	STS  266,R30
; 0000 008D // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 008E PORTL=(0<<PORTL7) | (0<<PORTL6) | (0<<PORTL5) | (0<<PORTL4) | (0<<PORTL3) | (0<<PORTL2) | (0<<PORTL1) | (0<<PORTL0);
	STS  267,R30
; 0000 008F 
; 0000 0090 // Timer/Counter 0 initialization
; 0000 0091 // Clock source: System Clock
; 0000 0092 // Clock value: Timer 0 Stopped
; 0000 0093 // Mode: Normal top=0xFF
; 0000 0094 // OC0A output: Disconnected
; 0000 0095 // OC0B output: Disconnected
; 0000 0096 TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
	OUT  0x24,R30
; 0000 0097 TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
	OUT  0x25,R30
; 0000 0098 TCNT0=0x00;
	OUT  0x26,R30
; 0000 0099 OCR0A=0x00;
	OUT  0x27,R30
; 0000 009A OCR0B=0x00;
	OUT  0x28,R30
; 0000 009B 
; 0000 009C // Timer/Counter 1 initialization
; 0000 009D // Clock source: System Clock
; 0000 009E // Clock value: Timer1 Stopped
; 0000 009F // Mode: Normal top=0xFFFF
; 0000 00A0 // OC1A output: Disconnected
; 0000 00A1 // OC1B output: Disconnected
; 0000 00A2 // OC1C output: Disconnected
; 0000 00A3 // Noise Canceler: Off
; 0000 00A4 // Input Capture on Falling Edge
; 0000 00A5 // Timer1 Overflow Interrupt: Off
; 0000 00A6 // Input Capture Interrupt: Off
; 0000 00A7 // Compare A Match Interrupt: Off
; 0000 00A8 // Compare B Match Interrupt: Off
; 0000 00A9 // Compare C Match Interrupt: Off
; 0000 00AA TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (0<<WGM10);
	STS  128,R30
; 0000 00AB TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
	STS  129,R30
; 0000 00AC TCNT1H=0x00;
	STS  133,R30
; 0000 00AD TCNT1L=0x00;
	STS  132,R30
; 0000 00AE ICR1H=0x00;
	STS  135,R30
; 0000 00AF ICR1L=0x00;
	STS  134,R30
; 0000 00B0 OCR1AH=0x00;
	STS  137,R30
; 0000 00B1 OCR1AL=0x00;
	STS  136,R30
; 0000 00B2 OCR1BH=0x00;
	STS  139,R30
; 0000 00B3 OCR1BL=0x00;
	STS  138,R30
; 0000 00B4 OCR1CH=0x00;
	STS  141,R30
; 0000 00B5 OCR1CL=0x00;
	STS  140,R30
; 0000 00B6 
; 0000 00B7 // Timer/Counter 2 initialization
; 0000 00B8 // Clock source: System Clock
; 0000 00B9 // Clock value: Timer2 Stopped
; 0000 00BA // Mode: Normal top=0xFF
; 0000 00BB // OC2A output: Disconnected
; 0000 00BC // OC2B output: Disconnected
; 0000 00BD ASSR=(0<<EXCLK) | (0<<AS2);
	STS  182,R30
; 0000 00BE TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
	STS  176,R30
; 0000 00BF TCCR2B=(0<<WGM22) | (0<<CS22) | (0<<CS21) | (0<<CS20);
	STS  177,R30
; 0000 00C0 TCNT2=0x00;
	STS  178,R30
; 0000 00C1 OCR2A=0x00;
	STS  179,R30
; 0000 00C2 OCR2B=0x00;
	STS  180,R30
; 0000 00C3 
; 0000 00C4 // Timer/Counter 3 initialization
; 0000 00C5 // Clock source: System Clock
; 0000 00C6 // Clock value: Timer3 Stopped
; 0000 00C7 // Mode: Normal top=0xFFFF
; 0000 00C8 // OC3A output: Disconnected
; 0000 00C9 // OC3B output: Disconnected
; 0000 00CA // OC3C output: Disconnected
; 0000 00CB // Noise Canceler: Off
; 0000 00CC // Input Capture on Falling Edge
; 0000 00CD // Timer3 Overflow Interrupt: Off
; 0000 00CE // Input Capture Interrupt: Off
; 0000 00CF // Compare A Match Interrupt: Off
; 0000 00D0 // Compare B Match Interrupt: Off
; 0000 00D1 // Compare C Match Interrupt: Off
; 0000 00D2 TCCR3A=(0<<COM3A1) | (0<<COM3A0) | (0<<COM3B1) | (0<<COM3B0) | (0<<COM3C1) | (0<<COM3C0) | (0<<WGM31) | (0<<WGM30);
	STS  144,R30
; 0000 00D3 TCCR3B=(0<<ICNC3) | (0<<ICES3) | (0<<WGM33) | (0<<WGM32) | (0<<CS32) | (0<<CS31) | (0<<CS30);
	STS  145,R30
; 0000 00D4 TCNT3H=0x00;
	STS  149,R30
; 0000 00D5 TCNT3L=0x00;
	STS  148,R30
; 0000 00D6 ICR3H=0x00;
	STS  151,R30
; 0000 00D7 ICR3L=0x00;
	STS  150,R30
; 0000 00D8 OCR3AH=0x00;
	STS  153,R30
; 0000 00D9 OCR3AL=0x00;
	STS  152,R30
; 0000 00DA OCR3BH=0x00;
	STS  155,R30
; 0000 00DB OCR3BL=0x00;
	STS  154,R30
; 0000 00DC OCR3CH=0x00;
	STS  157,R30
; 0000 00DD OCR3CL=0x00;
	STS  156,R30
; 0000 00DE 
; 0000 00DF // Timer/Counter 4 initialization
; 0000 00E0 // Clock source: System Clock
; 0000 00E1 // Clock value: Timer4 Stopped
; 0000 00E2 // Mode: Normal top=0xFFFF
; 0000 00E3 // OC4A output: Disconnected
; 0000 00E4 // OC4B output: Disconnected
; 0000 00E5 // OC4C output: Disconnected
; 0000 00E6 // Noise Canceler: Off
; 0000 00E7 // Input Capture on Falling Edge
; 0000 00E8 // Timer4 Overflow Interrupt: Off
; 0000 00E9 // Input Capture Interrupt: Off
; 0000 00EA // Compare A Match Interrupt: Off
; 0000 00EB // Compare B Match Interrupt: Off
; 0000 00EC // Compare C Match Interrupt: Off
; 0000 00ED TCCR4A=(0<<COM4A1) | (0<<COM4A0) | (0<<COM4B1) | (0<<COM4B0) | (0<<COM4C1) | (0<<COM4C0) | (0<<WGM41) | (0<<WGM40);
	STS  160,R30
; 0000 00EE TCCR4B=(0<<ICNC4) | (0<<ICES4) | (0<<WGM43) | (0<<WGM42) | (0<<CS42) | (0<<CS41) | (0<<CS40);
	STS  161,R30
; 0000 00EF TCNT4H=0x00;
	STS  165,R30
; 0000 00F0 TCNT4L=0x00;
	STS  164,R30
; 0000 00F1 ICR4H=0x00;
	STS  167,R30
; 0000 00F2 ICR4L=0x00;
	STS  166,R30
; 0000 00F3 OCR4AH=0x00;
	STS  169,R30
; 0000 00F4 OCR4AL=0x00;
	STS  168,R30
; 0000 00F5 OCR4BH=0x00;
	STS  171,R30
; 0000 00F6 OCR4BL=0x00;
	STS  170,R30
; 0000 00F7 OCR4CH=0x00;
	STS  173,R30
; 0000 00F8 OCR4CL=0x00;
	STS  172,R30
; 0000 00F9 
; 0000 00FA // Timer/Counter 5 initialization
; 0000 00FB // Clock source: System Clock
; 0000 00FC // Clock value: Timer5 Stopped
; 0000 00FD // Mode: Normal top=0xFFFF
; 0000 00FE // OC5A output: Disconnected
; 0000 00FF // OC5B output: Disconnected
; 0000 0100 // OC5C output: Disconnected
; 0000 0101 // Noise Canceler: Off
; 0000 0102 // Input Capture on Falling Edge
; 0000 0103 // Timer5 Overflow Interrupt: Off
; 0000 0104 // Input Capture Interrupt: Off
; 0000 0105 // Compare A Match Interrupt: Off
; 0000 0106 // Compare B Match Interrupt: Off
; 0000 0107 // Compare C Match Interrupt: Off
; 0000 0108 TCCR5A=(0<<COM5A1) | (0<<COM5A0) | (0<<COM5B1) | (0<<COM5B0) | (0<<COM5C1) | (0<<COM5C0) | (0<<WGM51) | (0<<WGM50);
	STS  288,R30
; 0000 0109 TCCR5B=(0<<ICNC5) | (0<<ICES5) | (0<<WGM53) | (0<<WGM52) | (0<<CS52) | (0<<CS51) | (0<<CS50);
	STS  289,R30
; 0000 010A TCNT5H=0x00;
	STS  293,R30
; 0000 010B TCNT5L=0x00;
	STS  292,R30
; 0000 010C ICR5H=0x00;
	STS  295,R30
; 0000 010D ICR5L=0x00;
	STS  294,R30
; 0000 010E OCR5AH=0x00;
	STS  297,R30
; 0000 010F OCR5AL=0x00;
	STS  296,R30
; 0000 0110 OCR5BH=0x00;
	STS  299,R30
; 0000 0111 OCR5BL=0x00;
	STS  298,R30
; 0000 0112 OCR5CH=0x00;
	STS  301,R30
; 0000 0113 OCR5CL=0x00;
	STS  300,R30
; 0000 0114 
; 0000 0115 // Timer/Counter 0 Interrupt(s) initialization
; 0000 0116 TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);
	STS  110,R30
; 0000 0117 
; 0000 0118 // Timer/Counter 1 Interrupt(s) initialization
; 0000 0119 TIMSK1=(0<<ICIE1) | (0<<OCIE1C) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);
	STS  111,R30
; 0000 011A 
; 0000 011B // Timer/Counter 2 Interrupt(s) initialization
; 0000 011C TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (0<<TOIE2);
	STS  112,R30
; 0000 011D 
; 0000 011E // Timer/Counter 3 Interrupt(s) initialization
; 0000 011F TIMSK3=(0<<ICIE3) | (0<<OCIE3C) | (0<<OCIE3B) | (0<<OCIE3A) | (0<<TOIE3);
	STS  113,R30
; 0000 0120 
; 0000 0121 // Timer/Counter 4 Interrupt(s) initialization
; 0000 0122 TIMSK4=(0<<ICIE4) | (0<<OCIE4C) | (0<<OCIE4B) | (0<<OCIE4A) | (0<<TOIE4);
	STS  114,R30
; 0000 0123 
; 0000 0124 // Timer/Counter 5 Interrupt(s) initialization
; 0000 0125 TIMSK5=(0<<ICIE5) | (0<<OCIE5C) | (0<<OCIE5B) | (0<<OCIE5A) | (0<<TOIE5);
	STS  115,R30
; 0000 0126 
; 0000 0127 // External Interrupt(s) initialization
; 0000 0128 // INT0: Off
; 0000 0129 // INT1: Off
; 0000 012A // INT2: Off
; 0000 012B // INT3: Off
; 0000 012C // INT4: Off
; 0000 012D // INT5: Off
; 0000 012E // INT6: Off
; 0000 012F // INT7: Off
; 0000 0130 EICRA=(0<<ISC31) | (0<<ISC30) | (0<<ISC21) | (0<<ISC20) | (0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
	STS  105,R30
; 0000 0131 EICRB=(0<<ISC71) | (0<<ISC70) | (0<<ISC61) | (0<<ISC60) | (0<<ISC51) | (0<<ISC50) | (0<<ISC41) | (0<<ISC40);
	STS  106,R30
; 0000 0132 EIMSK=(0<<INT7) | (0<<INT6) | (0<<INT5) | (0<<INT4) | (0<<INT3) | (0<<INT2) | (0<<INT1) | (0<<INT0);
	OUT  0x1D,R30
; 0000 0133 // PCINT0 interrupt: Off
; 0000 0134 // PCINT1 interrupt: Off
; 0000 0135 // PCINT2 interrupt: Off
; 0000 0136 // PCINT3 interrupt: Off
; 0000 0137 // PCINT4 interrupt: Off
; 0000 0138 // PCINT5 interrupt: Off
; 0000 0139 // PCINT6 interrupt: Off
; 0000 013A // PCINT7 interrupt: Off
; 0000 013B // PCINT8 interrupt: Off
; 0000 013C // PCINT9 interrupt: Off
; 0000 013D // PCINT10 interrupt: Off
; 0000 013E // PCINT11 interrupt: Off
; 0000 013F // PCINT12 interrupt: Off
; 0000 0140 // PCINT13 interrupt: Off
; 0000 0141 // PCINT14 interrupt: Off
; 0000 0142 // PCINT15 interrupt: Off
; 0000 0143 // PCINT16 interrupt: Off
; 0000 0144 // PCINT17 interrupt: Off
; 0000 0145 // PCINT18 interrupt: Off
; 0000 0146 // PCINT19 interrupt: Off
; 0000 0147 // PCINT20 interrupt: Off
; 0000 0148 // PCINT21 interrupt: Off
; 0000 0149 // PCINT22 interrupt: Off
; 0000 014A // PCINT23 interrupt: Off
; 0000 014B PCMSK0=(0<<PCINT7) | (0<<PCINT6) | (0<<PCINT5) | (0<<PCINT4) | (0<<PCINT3) | (0<<PCINT2) | (0<<PCINT1) | (0<<PCINT0);
	STS  107,R30
; 0000 014C PCMSK1=(0<<PCINT15) | (0<<PCINT14) | (0<<PCINT13) | (0<<PCINT12) | (0<<PCINT11) | (0<<PCINT10) | (0<<PCINT9) | (0<<PCINT8);
	STS  108,R30
; 0000 014D PCMSK2=(0<<PCINT23) | (0<<PCINT22) | (0<<PCINT21) | (0<<PCINT20) | (0<<PCINT19) | (0<<PCINT18) | (0<<PCINT17) | (0<<PCINT16);
	STS  109,R30
; 0000 014E PCICR=(0<<PCIE2) | (0<<PCIE1) | (0<<PCIE0);
	STS  104,R30
; 0000 014F 
; 0000 0150 // USART0 initialization
; 0000 0151 // Communication Parameters: 8 Data, 1 Stop, No Parity
; 0000 0152 // USART0 Receiver: On
; 0000 0153 // USART0 Transmitter: On
; 0000 0154 // USART0 Mode: Asynchronous
; 0000 0155 // USART0 Baud Rate: 38400
; 0000 0156 UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
	STS  192,R30
; 0000 0157 UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
	LDI  R30,LOW(24)
	STS  193,R30
; 0000 0158 UCSR0C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
	LDI  R30,LOW(6)
	STS  194,R30
; 0000 0159 UBRR0H=0x00;
	LDI  R30,LOW(0)
	STS  197,R30
; 0000 015A UBRR0L=0x19;
	LDI  R30,LOW(25)
	STS  196,R30
; 0000 015B 
; 0000 015C // USART1 initialization
; 0000 015D // USART1 disabled
; 0000 015E UCSR1B=(0<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (0<<RXEN1) | (0<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);
	LDI  R30,LOW(0)
	STS  201,R30
; 0000 015F 
; 0000 0160 // USART2 initialization
; 0000 0161 // USART2 disabled
; 0000 0162 UCSR2B=(0<<RXCIE2) | (0<<TXCIE2) | (0<<UDRIE2) | (0<<RXEN2) | (0<<TXEN2) | (0<<UCSZ22) | (0<<RXB82) | (0<<TXB82);
	STS  209,R30
; 0000 0163 
; 0000 0164 // USART3 initialization
; 0000 0165 // USART3 disabled
; 0000 0166 UCSR3B=(0<<RXCIE3) | (0<<TXCIE3) | (0<<UDRIE3) | (0<<RXEN3) | (0<<TXEN3) | (0<<UCSZ32) | (0<<RXB83) | (0<<TXB83);
	STS  305,R30
; 0000 0167 
; 0000 0168 // Analog Comparator initialization
; 0000 0169 // Analog Comparator: Off
; 0000 016A // The Analog Comparator's positive input is
; 0000 016B // connected to the AIN0 pin
; 0000 016C // The Analog Comparator's negative input is
; 0000 016D // connected to the AIN1 pin
; 0000 016E ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
	LDI  R30,LOW(128)
	OUT  0x30,R30
; 0000 016F ADCSRB=(0<<ACME);
	LDI  R30,LOW(0)
	STS  123,R30
; 0000 0170 // Digital input buffer on AIN0: On
; 0000 0171 // Digital input buffer on AIN1: On
; 0000 0172 DIDR1=(0<<AIN0D) | (0<<AIN1D);
	STS  127,R30
; 0000 0173 
; 0000 0174 // ADC initialization
; 0000 0175 // ADC disabled
; 0000 0176 ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
	STS  122,R30
; 0000 0177 
; 0000 0178 // SPI initialization
; 0000 0179 // SPI disabled
; 0000 017A SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
	OUT  0x2C,R30
; 0000 017B 
; 0000 017C // TWI initialization
; 0000 017D // TWI disabled
; 0000 017E TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);
	STS  188,R30
; 0000 017F 
; 0000 0180 while (1)
_0x4:
; 0000 0181 {
; 0000 0182 // Execute the bootloader
; 0000 0183 if (bootloader(boot_callback)==BOOT_OK)
	LDI  R26,LOW(_boot_callback)
	LDI  R27,HIGH(_boot_callback)
	CALL _bootloader
	CPI  R30,0
	BRNE _0x7
; 0000 0184 {
; 0000 0185 // The bootloader has successfully uploaded the application
; 0000 0186 // Execute the application
; 0000 0187 #asm("JMP  0x0")
	JMP  0x0
; 0000 0188 }
; 0000 0189 }
_0x7:
	RJMP _0x4
; 0000 018A }
_0x8:
	RJMP _0x8
; .FEND
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.EQU __sm_adc_noise_red=0x02
	.SET power_ctrl_reg=smcr
	#endif
#if SPMCSR > 0x3F
	.MACRO SPMCSR_R22
	sts  SPMCSR, r22
	.ENDM
#else
	.MACRO SPMCSR_R22
	out  SPMCSR, r22
	.ENDM
#endif

	.CSEG
_nvm_exec_spm_r0_G100:
; .FSTART _nvm_exec_spm_r0_G100
	ST   -Y,R26
    in   r23, SREG
    cli
	ldd  r0, y + 1
	ld   r22, y
	SPMCSR_R22
	spm
    out  SREG, r23
_0x2000003:
	IN   R30,0x37
	SBRC R30,0
	RJMP _0x2000003
	ADIW R28,2
	RET
; .FEND
_nvm_exec_spm_addr_G100:
; .FSTART _nvm_exec_spm_addr_G100
	ST   -Y,R26
    in   r24, SREG
    cli
	ldd  r30, y + 1
	ldd  r31, y + 2
	ldd  r22, y + 3
	in   r23, RAMPZ
	out  RAMPZ, r22
	ld   r22, y
	SPMCSR_R22
	spm
	out  RAMPZ, r23
    out  SREG, r24
_0x2000006:
	IN   R30,0x37
	SBRC R30,0
	RJMP _0x2000006
	ADIW R28,5
	RET
; .FEND
_nvm_write_flash_word:
; .FSTART _nvm_write_flash_word
	ST   -Y,R27
	ST   -Y,R26
    in   r24, SREG
    cli
	ldd  r30, y + 2
	ldd  r31, y + 3
	ldd  r22, y + 4
	in   r23, RAMPZ
	out  RAMPZ, r22
	ld   r0, y
	ldd  r1, y + 1
	ldi  r22, 0x01
	SPMCSR_R22
	spm
	out  RAMPZ, r23
    out  SREG, r24
	ADIW R28,6
	RET
; .FEND
_nvm_erase_write_flash_page:
; .FSTART _nvm_erase_write_flash_page
	CALL __PUTPARD2
_0x200000F:
	IN   R30,0x37
	SBRC R30,0
	RJMP _0x200000F
	CALL SUBOPT_0x0
	LDI  R26,LOW(3)
	CALL _nvm_exec_spm_addr_G100
	CALL SUBOPT_0x0
	LDI  R26,LOW(5)
	CALL _nvm_exec_spm_addr_G100
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(17)
	CALL _nvm_exec_spm_r0_G100
	ADIW R28,4
	RET
; .FEND
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.EQU __sm_adc_noise_red=0x02
	.SET power_ctrl_reg=smcr
	#endif

	.CSEG
_calc_crc16_G101:
; .FSTART _calc_crc16_G101
	CALL __SAVELOCR6
	MOVW R18,R26
	LDD  R21,Y+6
	LDI  R16,8
	EOR  R18,R21
_0x2020004:
	MOV  R30,R18
	ANDI R30,LOW(0x1)
	MOV  R17,R30
	LSR  R19
	ROR  R18
	CPI  R17,0
	BREQ _0x2020006
	LDI  R30,LOW(40961)
	LDI  R31,HIGH(40961)
	__EORWRR 18,19,30,31
_0x2020006:
	SUBI R16,LOW(1)
	BRNE _0x2020004
	MOVW R30,R18
	CALL __LOADLOCR6
	ADIW R28,7
	RET
; .FEND
_outbyte_G101:
; .FSTART _outbyte_G101
	ST   -Y,R17
	MOV  R17,R26
	RCALL _putchar
	__DELAY_USW 400
	RJMP _0x20A0001
; .FEND
_bootloader:
; .FSTART _bootloader
	ST   -Y,R27
	ST   -Y,R26
	SBIW R28,15
	CALL __SAVELOCR6
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	SBIW R30,0
	BRNE _0x2020007
	LDI  R30,LOW(4)
	RJMP _0x20A0002
_0x2020007:
	LDI  R30,LOW(0)
	__CLRD1S 17
_0x2020008:
	CALL SUBOPT_0x1
	CPI  R26,LOW(0x41)
	BRNE _0x202000B
	RCALL _getchar
	STD  Y+17,R30
	RCALL _getchar
	STD  Y+18,R30
	RCALL _getchar
	STD  Y+19,R30
	LDI  R30,LOW(0)
	STD  Y+20,R30
	LDI  R30,LOW(1)
	STD  Y+14,R30
	RJMP _0x202000C
_0x202000B:
	LDD  R26,Y+14
	CPI  R26,LOW(0x57)
	BREQ PC+2
	RJMP _0x202000D
	CALL SUBOPT_0x2
	CPI  R26,LOW(0x46)
	BRNE _0x202000F
	__CPWRN 18,19,2
	BRLO _0x202000F
	SBRS R18,0
	RJMP _0x2020010
_0x202000F:
	RJMP _0x202000E
_0x2020010:
	CALL SUBOPT_0x3
	CALL SUBOPT_0x4
	CALL SUBOPT_0x3
	__PUTD1S 10
_0x2020012:
	RCALL _getchar
	MOV  R20,R30
	ST   -Y,R20
	CALL SUBOPT_0x5
	RCALL _getchar
	MOV  R21,R30
	ST   -Y,R21
	CALL SUBOPT_0x5
	CALL SUBOPT_0x3
	CALL __PUTPARD1
	MOVW R26,R20
	CALL _nvm_write_flash_word
	CALL SUBOPT_0x3
	__ADDD1N 2
	CALL SUBOPT_0x6
	LDD  R30,Y+17
	ANDI R30,LOW(0xFF)
	BREQ _0x2020015
	__CPWRN 18,19,3
	BRSH _0x2020014
_0x2020015:
	RJMP _0x2020013
_0x2020014:
	__SUBWRN 18,19,2
	MOV  R0,R18
	OR   R0,R19
	BRNE _0x2020012
_0x2020013:
	LDI  R30,LOW(2)
	CALL SUBOPT_0x7
	BRNE _0x2020017
	__GETD2S 10
	RCALL _nvm_erase_write_flash_page
	CALL SUBOPT_0x8
	RJMP _0x202000C
_0x2020017:
	RJMP _0x2020018
_0x202000E:
	LDD  R26,Y+14
	CPI  R26,LOW(0x45)
	BRNE _0x202001A
	__CPWRN 18,19,1
	BRLO _0x202001A
	__CPWRN 18,19,33
	BRLO _0x202001B
_0x202001A:
	RJMP _0x2020019
_0x202001B:
	__POINTWRM 16,17,_buffer_G101
	MOV  R20,R18
	MOV  R21,R20
_0x202001D:
	RCALL _getchar
	STD  Y+14,R30
	CALL SUBOPT_0x9
	PUSH R17
	PUSH R16
	__ADDWRN 16,17,1
	LDD  R30,Y+14
	POP  R26
	POP  R27
	ST   X,R30
	SUBI R20,LOW(1)
	CPI  R20,0
	BRNE _0x202001D
	LDI  R30,LOW(3)
	CALL SUBOPT_0x7
	BRNE _0x202001F
	__POINTWRM 16,17,_buffer_G101
	MOV  R20,R21
_0x2020021:
	MOVW R26,R16
	__ADDWRN 16,17,1
	LD   R30,X
	LDD  R26,Y+17
	LDD  R27,Y+17+1
	CALL __EEPROMWRB
	LDD  R30,Y+17
	LDD  R31,Y+17+1
	ADIW R30,1
	STD  Y+17,R30
	STD  Y+17+1,R31
	SUBI R20,LOW(1)
	CPI  R20,0
	BRNE _0x2020021
_0x202000C:
	LDI  R26,LOW(13)
	RCALL _outbyte_G101
	RJMP _0x2020023
_0x202001F:
_0x2020018:
	LDI  R26,LOW(33)
	RCALL _outbyte_G101
	LDD  R26,Y+14
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	LDI  R30,LOW(1)
	RJMP _0x20A0002
_0x2020019:
	RJMP _0x2020024
_0x202000D:
	LDD  R26,Y+14
	CPI  R26,LOW(0x52)
	BREQ PC+2
	RJMP _0x2020026
	CALL SUBOPT_0x2
	CPI  R26,LOW(0x46)
	BRNE _0x2020028
	__CPWRN 18,19,2
	BRLO _0x2020028
	SBRS R18,0
	RJMP _0x2020029
_0x2020028:
	RJMP _0x2020027
_0x2020029:
	CALL SUBOPT_0xA
	CALL SUBOPT_0x3
	CALL SUBOPT_0x4
_0x202002B:
	CALL SUBOPT_0xB
	LDD  R26,Y+14
	RCALL _outbyte_G101
	CALL SUBOPT_0xB
	LDD  R26,Y+14
	RCALL _outbyte_G101
	__SUBWRN 18,19,2
	MOV  R0,R18
	OR   R0,R19
	BRNE _0x202002B
	CALL SUBOPT_0x8
	LDI  R30,LOW(4)
	RJMP _0x202003A
_0x2020027:
	LDD  R26,Y+14
	CPI  R26,LOW(0x45)
	BRNE _0x202002E
	CALL SUBOPT_0xA
_0x202002F:
	MOV  R0,R18
	OR   R0,R19
	BREQ _0x2020031
	LDD  R26,Y+17
	LDD  R27,Y+17+1
	CALL __EEPROMRDB
	STD  Y+14,R30
	CALL SUBOPT_0x9
	LDD  R26,Y+14
	RCALL _outbyte_G101
	CALL SUBOPT_0x3
	__SUBD1N -1
	CALL SUBOPT_0x6
	__SUBWRN 18,19,1
	RJMP _0x202002F
_0x2020031:
	LDI  R30,LOW(5)
_0x202003A:
	STD  Y+14,R30
	LDD  R26,Y+15
	RCALL _outbyte_G101
	LDD  R26,Y+16
	RCALL _outbyte_G101
	RJMP _0x2020023
_0x202002E:
	RJMP _0x2020024
_0x2020026:
	LDD  R26,Y+14
	CPI  R26,LOW(0x53)
	BRNE _0x2020033
	CALL SUBOPT_0xA
	__POINTD1FN _BOOT_HEADER,0
	__PUTD1S 6
	LDI  R30,LOW(21)
	STD  Y+14,R30
_0x2020035:
	MOVW R26,R28
	ADIW R26,6
	__GETD1P_INC
	__ADDD1N 1
	__PUTDP1_DEC
	__SUBD1N 1
	__GETBRPF 26
	RCALL _outbyte_G101
	LDD  R30,Y+14
	SUBI R30,LOW(1)
	STD  Y+14,R30
	BRNE _0x2020035
	LDI  R30,LOW(0)
	STD  Y+14,R30
_0x2020023:
	LDD  R26,Y+14
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	RJMP _0x2020037
_0x2020033:
	LDD  R26,Y+14
	CPI  R26,LOW(0x45)
	BRNE _0x2020038
	CALL SUBOPT_0xA
	LDI  R26,LOW(13)
	RCALL _outbyte_G101
	LDI  R26,LOW(6)
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	LDI  R30,LOW(0)
	RJMP _0x20A0002
_0x2020038:
_0x2020024:
	CALL SUBOPT_0xA
	LDI  R26,LOW(63)
	RCALL _outbyte_G101
	LDI  R30,LOW(4)
	RJMP _0x20A0002
_0x2020037:
	RJMP _0x2020008
_0x20A0002:
	CALL __LOADLOCR6
	ADIW R28,23
	RET
; .FEND
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.EQU __sm_adc_noise_red=0x02
	.SET power_ctrl_reg=smcr
	#endif

	.CSEG
_getchar:
; .FSTART _getchar
_0x2040003:
	LDS  R30,192
	ANDI R30,LOW(0x80)
	BREQ _0x2040003
	LDS  R30,198
	RET
; .FEND
_putchar:
; .FSTART _putchar
	ST   -Y,R17
	MOV  R17,R26
_0x2040006:
	LDS  R30,192
	ANDI R30,LOW(0x20)
	BREQ _0x2040006
	STS  198,R17
_0x20A0001:
	LD   R17,Y+
	RET
; .FEND

	.CSEG

	.CSEG

	.DSEG
_buffer_G101:
	.BYTE 0x100

	.CSEG
;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x0:
	__GETD1S 0
	CALL __PUTPARD1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x1:
	CALL _getchar
	STD  Y+14,R30
	LDD  R26,Y+14
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x2:
	LDI  R30,LOW(65535)
	LDI  R31,HIGH(65535)
	STD  Y+15,R30
	STD  Y+15+1,R31
	CALL _getchar
	MOV  R18,R30
	CALL _getchar
	MOV  R19,R30
	RJMP SUBOPT_0x1

;OPTIMIZER ADDED SUBROUTINE, CALLED 10 TIMES, CODE SIZE REDUCTION:15 WORDS
SUBOPT_0x3:
	__GETD1S 17
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x4:
	__LSLD1
	__PUTD1S 17
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:17 WORDS
SUBOPT_0x5:
	LDD  R26,Y+16
	LDD  R27,Y+16+1
	CALL _calc_crc16_G101
	STD  Y+15,R30
	STD  Y+15+1,R31
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x6:
	__PUTD1S 17
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:6 WORDS
SUBOPT_0x7:
	STD  Y+14,R30
	CALL _getchar
	MOV  R20,R30
	CALL _getchar
	MOV  R21,R30
	LDD  R30,Y+15
	LDD  R31,Y+15+1
	CP   R30,R20
	CPC  R31,R21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x8:
	RCALL SUBOPT_0x3
	__LSRD1
	RJMP SUBOPT_0x6

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x9:
	LDD  R30,Y+14
	ST   -Y,R30
	RJMP SUBOPT_0x5

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0xA:
	LDI  R26,LOW(5)
	LDI  R27,0
	JMP  _delay_ms

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:11 WORDS
SUBOPT_0xB:
	RCALL SUBOPT_0x3
	__SUBD1N -1
	RCALL SUBOPT_0x6
	SBIW R30,1
	SBCI R22,0
	SBCI R23,0
	__GETBRPF 0
	STD  Y+14,R0
	RJMP SUBOPT_0x9

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

__PUTPARD1:
	ST   -Y,R23
	ST   -Y,R22
	ST   -Y,R31
	ST   -Y,R30
	RET

__PUTPARD2:
	ST   -Y,R25
	ST   -Y,R24
	ST   -Y,R27
	ST   -Y,R26
	RET

__EEPROMRDB:
	SBIC EECR,EEWE
	RJMP __EEPROMRDB
	PUSH R31
	IN   R31,SREG
	CLI
	OUT  EEARL,R26
	OUT  EEARH,R27
	SBI  EECR,EERE
	IN   R30,EEDR
	OUT  SREG,R31
	POP  R31
	RET

__EEPROMWRB:
	SBIS EECR,EEWE
	RJMP __EEPROMWRB1
	WDR
	RJMP __EEPROMWRB
__EEPROMWRB1:
	IN   R25,SREG
	CLI
	OUT  EEARL,R26
	OUT  EEARH,R27
	SBI  EECR,EERE
	IN   R24,EEDR
	CP   R30,R24
	BREQ __EEPROMWRB0
	OUT  EEDR,R30
	SBI  EECR,EEMWE
	SBI  EECR,EEWE
__EEPROMWRB0:
	OUT  SREG,R25
	RET

_delay_ms:
	adiw r26,0
	breq __delay_ms1
__delay_ms0:
	wdr
	__DELAY_USW 0xFA0
	sbiw r26,1
	brne __delay_ms0
__delay_ms1:
	ret

;END OF CODE MARKER
__END_OF_CODE:
