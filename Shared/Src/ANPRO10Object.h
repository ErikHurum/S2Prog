#pragma once
#ifndef ANPRO10ObjectH
#define ANPRO10ObjectH
class ANPRO10Object:public PRogramObject
{
protected:
	TSNUart *CPort;
	U8 SequenceNumber;

public:
	U32 FailCntTotal;
	volatile U32 FailCnt;
	ANPRO10Object(TSNUart *PortPtr);
	~ANPRO10Object(void);
#ifndef ANCONF
	bool ANPRO10_IO_Receive(int Delay = MAX_IO_RESPONSE_TIME);
	bool SendPacket(NetPacket &Packet);
	virtual bool ANPRO10_IO_UnpackPacket(U8 *Buf);
#endif
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);

};
#endif
