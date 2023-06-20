#ifdef S2TXU
	#include "TDUincludes.h"
#else
	#ifdef ANTDUSIM
		#pragma warning( disable : 4060 4065 4101 4244 4267 4305 4311 4800)
	#endif
	#include "TSNIncludes.h"
	#pragma hdrstop
	#ifdef BORLAND
#pragma package(smart_init)
#endif

#endif

U16 AddPacketHeading(U8 *TxBuf, U8 RxAddress)
{
	TxBuf[0] = ANPRO1_SYN;
	TxBuf[1] = ANPRO1_SYN;
	ANPRO1_NetHeading    *HPtr = (ANPRO1_NetHeading*)&TxBuf[ANPRO1_NUM_SYNC];
	HPtr->RxAddress = RxAddress;
	HPtr->TxAddress = CurrentDeviceAddress;
	return(ANPRO1_NUM_SYNC+sizeof(ANPRO1_PacketHeading));
}

U16 AddCommand(U8 *TxBuf,U16 Ptr, U8 Command, U8* Data, U8  Size)
{
	TxBuf[0+Ptr] = Command;
	TxBuf[1+Ptr] = Size;
	if ( Data && Size )	memcpy(&TxBuf[2+Ptr],Data,Size);
	return(Size+2);
}

U16 AddPacketTail(U8 *TxBuf, U16 Size, U8 Cmd)
{
	ANPRO1_NetHeading *HPtr = (ANPRO1_NetHeading*)&TxBuf[ANPRO1_NUM_SYNC];
	ANPRO1_PacketTail *TPtr = (ANPRO1_PacketTail*)&TxBuf[Size];
	TPtr->ecmd   = Cmd;
	TPtr->edata  = 0;
	Size += sizeof(ANPRO1_PacketTail);
	HPtr->HiSize =  (Size-2) >> 8;
	HPtr->LoSize =  (Size-2) & 0xFF;
	U8 CS = 0;
	for ( int Cnt = 2; Cnt < Size-2; Cnt++ ) {
		CS = CRC[CS ^ TxBuf[Cnt]];
	}
	TPtr->PCRC = CS;
	TPtr->EOT  = ANPRO1_EOT;
	return(sizeof(ANPRO1_PacketTail));
}



#define ANPRO1_BUF_SIZE 500
bool ANPRO1Receive(TSNUart *PortPtr,int Delay, U8 Address,set<PRogramObjectBase*>&CurrenttpPCxList, bool (*UnpackFunction)(TSNUart*,U8*,int,set<PRogramObjectBase*>))
{
	int PacketCnt =0;
	U8 RxBuf[ANPRO1_BUF_SIZE];
	memset(RxBuf,0,ANPRO1_BUF_SIZE);
	const ANPRO1_PacketHeading *pPH =  (ANPRO1_PacketHeading*)RxBuf;
	U8 Data;
	int SyncCnt;
	bool dataAvailable = false;
	bool Echo          = false;
	do {
		do {
			dataAvailable = PortPtr->Receive(&Data,sizeof(Data),Delay);
			//WriteByte(Data&0xFF);
		}  while ( dataAvailable && Data != ANPRO1_SYN );
		PacketCnt++;
		if ( dataAvailable ) {
			// A minimum of 2 SYN to accept start
			//Message("First SYN");
			SyncCnt = 0;
			do {
				dataAvailable = PortPtr->Receive(&Data,sizeof(Data),30);
				if ( dataAvailable && (Data == ANPRO1_SYN) )
					SyncCnt++;
			} while ( dataAvailable && (Data == ANPRO1_SYN) );
			if ( dataAvailable && SyncCnt ) {
				// We allready have one byte of the heading. Move it to the RxBuffer and
				// receive the rest of the heading
				U8 *RxPtr = RxBuf;
				RxBuf[0]  = Data;
				RxPtr++;
				for ( unsigned i=1; dataAvailable && i < sizeof(ANPRO1_NetHeading); i++ ) {
					dataAvailable = PortPtr->Receive(RxPtr++,sizeof(Data),30);
				}
				if ( dataAvailable ) {
					unsigned DataSize = (pPH->HiSize<<8) |pPH->LoSize;
					if ( DataSize > 3 && DataSize < ANPRO1_BUF_SIZE ) {
						int Cnt=0;
						for ( unsigned i=0; dataAvailable && i < DataSize-sizeof(ANPRO1_PacketHeading); i++ ) {
							dataAvailable = PortPtr->Receive(RxPtr++,sizeof(Data),30);
							Cnt++;
						}
						if ( !dataAvailable ) {
							//OS_Delay(100);
						}
						if ( dataAvailable ) {
							U8 EOTByte = *((U8*)&RxBuf[DataSize-1]);
							if ( EOTByte == ANPRO1_EOT ) {
								RxPtr = RxBuf;
								U8 CSum = 0;
								for ( unsigned i=0; i < DataSize-2; i++ ) {
									CSum     = CRC[CSum ^ *RxPtr++];
								}
								U8  PacketCheckSum = *((U8*)&RxBuf[DataSize-2]);
								if ( PacketCheckSum == CSum ) {
									if ( pPH->TxAddress == Address ) {
										(*UnpackFunction)(PortPtr,&RxBuf[sizeof(ANPRO1_PacketHeading)],DataSize,CurrenttpPCxList);
										Echo = false;
									} else {
										Echo = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}while ( Echo && dataAvailable );
	return(bool)( PacketCnt > 1 );
}


