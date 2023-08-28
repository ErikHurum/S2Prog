#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

ANPRO10Object::ANPRO10Object(TSNUart *PortPtr)
{
	CPort         = PortPtr;
	FailCntTotal  =0;
	FailCnt       =0;

}

ANPRO10Object::~ANPRO10Object(void)
{
}

#ifndef ANCONF
//////////////////////////////////////////////////////////////
//
// Routines for communication
//
///////////////////////////////////////////////////////////////

bool ANPRO10Object::ANPRO10_IO_UnpackPacket(U8 *Buf)
{
	return(false);
}
#define MAX_TIME_BETWEEN_BYTE	15
bool ANPRO10Object::ANPRO10_IO_Receive(int Delay)
{
	int StartTime = clock();
	#ifdef S2TXU
	#if (USE_EMBOS_MEM_POOL==1) 
	U8 *RxBuf = (U8*)OS_MEMF_Alloc(&pANPRO10IOMemPool,PURPOSE_IO_RECEIVE);
	#else
	U8 RxBuf[MAX_ANPRO10_IO_SIZE];
	#endif
	#else
	U8 *RxBuf = new U8[MAX_ANPRO10_IO_SIZE];
	#endif
	volatile ANPRO10_PacketHeading *pPH =  (ANPRO10_PacketHeading*)RxBuf;
	volatile U8 Data;
	int SyncCnt=0;
	bool dataAvailable = false;
	bool PacketOK      = false;
	bool Echo          = false;
	//do {
		do {
			do {
				dataAvailable = CPort->Receive((U8*)&Data,sizeof(Data),Delay);
				//WriteByte(Data&0xFF);
			}  while ( dataAvailable && Data != ANPRO10_SYN );
			if ( dataAvailable ) {
				// A minimum of 2 SYN to accept start
				//Message("First SYN");
				//SyncCnt = 0;
				do {
					dataAvailable = CPort->Receive((U8*)&Data,sizeof(Data),MAX_TIME_BETWEEN_BYTE);
					if ( dataAvailable && (Data == ANPRO10_SYN) ) SyncCnt++;
				} while ( dataAvailable && (Data == ANPRO10_SYN) );
				if ( dataAvailable && SyncCnt && (Data == ANPRO10_SOH) ) {
					U8 *RxPtr = RxBuf;
					for ( unsigned i=0; dataAvailable && i < sizeof(NetHeading); i++ ) {
						dataAvailable = CPort->Receive(RxPtr++,sizeof(Data),MAX_TIME_BETWEEN_BYTE);
					}
					if ( dataAvailable ) {
						U8 HCSum = 0;
						{
							U8 *TmpRxPtr = RxBuf;
							for ( unsigned i=0; i < sizeof(ANPRO10_PacketHeading)-1; i++ ) {
								HCSum     = CRC[HCSum ^ *TmpRxPtr++];
							}

						}
						if ( HCSum == pPH->HCRC ) {
							//OS_Delay(1000);
							unsigned DataSize = (unsigned)pPH->nob;
							if ( DataSize > 3 && DataSize < MAX_ANPRO10_IO_SIZE ) {
								int Cnt=0;
								for ( unsigned i=0; dataAvailable && i < DataSize-sizeof(ANPRO10_PacketHeading); i++ ) {
									dataAvailable = CPort->Receive(RxPtr++,sizeof(Data),MAX_TIME_BETWEEN_BYTE);
									Cnt++;
								}
								if ( !dataAvailable ) {
									//OS_Delay(100);
								}
								if ( dataAvailable ) {
									RxPtr = RxBuf;
									volatile U8 CSum = 0;

									for ( unsigned i=0; i < DataSize-2; i++ ) {
										CSum     = CRC[CSum ^ *RxPtr++];
									}
									U8  PacketCheckSum = *((U8*)&RxBuf[DataSize-2]);
									if ( PacketCheckSum == CSum ) {
										SequenceNumber = RxBuf[DataSize-3];
										//U16 EndCommand = *((U16*)&ARxBuf[DataSize-6]);
										//                  U8 EndData = *((U8*)&ARxBuf[DataSize-4]);
										U8 EOTByte = *((U8*)&RxBuf[DataSize-1]);
										if ( EOTByte == ANPRO10_EOT ) {
											switch ( pPH->txtypeid ) {

											//int tID = pPH->txtypeid;
											//int rID = pPH->rxtypeid;
											//if ( tID != rID )
											//switch ( rID ) {
											case DEVICE_ZBHART :
												Echo = !ANPRO10_IO_UnpackPacket(RxBuf);
												if ( !Echo ) {
													PacketOK = true;
												}
												break;
											case DEVICE_ZBANA :
												Echo = !ANPRO10_IO_UnpackPacket(RxBuf);
												if ( !Echo ) {
													PacketOK = true;
												}
												break;
											case DEVICE_ZB485 :
												Echo = !ANPRO10_IO_UnpackPacket(RxBuf);
												if ( !Echo ) {
													PacketOK = true;
												}
												break;
											case DEVICE_TCU:
												Echo = true;
												break;
											default:
												break;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}while ( Echo && dataAvailable );
	//}while ( !PacketOK && CPort->HasMore() );
	#ifdef S2TXU
	#if (USE_EMBOS_MEM_POOL==1) 
	OS_MEMF_Release(&pANPRO10IOMemPool,RxBuf);
	#endif
	#else
	delete RxBuf;
	#endif
	if ( PacketOK ) {
		FailCnt=0;
	} else {
		if ( !FailCnt ) {
			TSN_Delay(0);
		}
		FailCntTotal++;
		FailCnt++;
	}
        int ReceiveTime = clock() - StartTime;
        ReceiveTime++;
	return(PacketOK);
}

bool ANPRO10Object::SendPacket(NetPacket &Packet)
{
	//U8 *TxBuf = new U8[Packet.Size+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
	#ifdef S2TXU
	#if (USE_EMBOS_MEM_POOL==1) 
	U8 *TxBuf = (U8*)OS_MEMF_Alloc(&pANPRO10IOMemPool,PURPOSE_IO_TRANSMIT);
	#else
    U8 TxBuf[MAX_ANPRO10_IO_SIZE] = {ANPRO10_SYN,ANPRO10_SYN,ANPRO10_SYN,ANPRO10_SOH};
	#endif
	#else
	U8 *TxBuf = new U8[MAX_ANPRO10_IO_SIZE];
	#endif
    TxBuf[0] = ANPRO10_SYN;
    TxBuf[1] = ANPRO10_SYN;
    TxBuf[2] = ANPRO10_SYN;
    TxBuf[3] = ANPRO10_SOH;
	NetHeading    *HPtr = (NetHeading*)&TxBuf[P_SYNC_SIZE];
	// Allways send to the master
	int Ptr = P_SYNC_SIZE+ANPRO10_AddPacketHeading((U8*)HPtr,Packet.RxAddress,Packet.RxTypeId);
	Ptr += AddPacket((U8*)&TxBuf[Ptr],Packet);
	Ptr += ANPRO10_AddPacketTail((U8*)TxBuf,Ptr,Packet.RequestAck);
	bool TxSignal = CPort->Send((U8*)TxBuf,Ptr,SEND_COMPLETE_EVENT);
	#ifdef S2TXU
	CPort->ClearRxBuffer();
	#if (USE_EMBOS_MEM_POOL==1) 
	OS_MEMF_Release(&pANPRO10IOMemPool,TxBuf);
	#endif
	#else
	delete TxBuf;
	#endif
	return(TxSignal);
}
#endif

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int  ANPRO10Object::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_IO_FAIL_CNT_CHK:
		MyRetValue = FailCnt;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_FAIL_CNT_TOT:
		MyRetValue = FailCntTotal;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	default:
		Status = PRogramObject::GetValue(ValueId,Index, MyRetValue,  DecPnt,Unit);
		break;
	}
	return(Status);
}

int ANPRO10Object::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	default:
		Status = PRogramObject::GetStringValue(ValueId,Index, MyString);
		break;
	}
	return(Status);
}

int ANPRO10Object::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	return(PRogramObject::PutValue( ValueId, Index, NewValue, Local,UnitId));
}

int ANPRO10Object::PutFloatValue( int ValueId, float NewValue)
{
	return(PRogramObject::PutFloatValue(ValueId,NewValue));
}


