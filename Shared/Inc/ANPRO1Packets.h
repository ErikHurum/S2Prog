#pragma once
//---------------------------------------------------------------------------
#ifndef Anpro1PacketsH
#define Anpro1PacketsH

#ifdef S2TXU
#pragma bitfields=reversed
#endif
#pragma pack(push,1)
struct ANPRO1_NetHeading {
	U8  RxAddress;
	U8	TxAddress;
	U8  HiSize;
	U8  LoSize;
} ;
struct ANPRO1_NetPacket {
	U16   Command;
	U16   Size;
	U8    RxTypeId,
	RxAddress;
	bool  RequestAck;
	void  *Data;
} ;
struct ANPRO1_PacketHeading {
	U8  RxAddress;
	U8 TxAddress;
	U8 HiSize;
	U8 LoSize;
};

struct ANPRO1_PacketTail {	// cmd 0 No ack / 1 with ack
	U8 ecmd;
	U8 edata;
	U8 PCRC;
	U8 EOT;
};

struct ANPRO1_CommandHeading {
	U8   CommandNo;
	U8   ndb;
};

struct ANPRO1_COMMAND_END {	// 0/1
	U8   CommandNo;
	U8   ndb;

	U8    edata; // 0 = no error
};

//struct ANPRO1_COMMAND_2000  // Request for TXU to send status (only heading)

struct ANPRO1_COMMAND_2001 {	// TXU status
	U16     CommandNo;
	U16     ndb;				// 85 bytes

	U8      UnitID;
	U8      UnitAdress;
	U8      ProgramType; // 0 = Bootloader, 1 = Application

	char      SystemID[7];	// #### 7 bytes for this??????
	char      DataVersion[25];
	char      ProgramVersion[25];
	char      ProgrDate[25];
};

struct AdjustPacket {
    U8 	ChNo;
    U8  OffsetHigh;
    U8	OffsetLow;
    U8	GainHigh;
    U8	GainLow;
} ;

#pragma pack(pop)

//---------------------------------------------------------------------------
#endif


