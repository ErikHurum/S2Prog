//--------------------------------------------------------------------------
#ifndef IOUnitZB485H
#define IOUnitZB485H

class IOUnitZB485:
public IOUnit {
private:
	U8  SCType[2];
	U8  SequenceNumber;
	static ValueList IOUnitZB485ValueList[];

public:
	int 		DownloadEEPROMTime[2];
	static set<PRogramObjectBase*>ObjectSet;
	IOUnitZB485(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr);
	~IOUnitZB485(void);

	SignalConverter *SConverter[MAX_AN_ZB485_CHANNELS];

	bool Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr);

#ifndef ANCONF
	void PROCalculate(void);
	void CompCalculate(void);
	void ReadCh(int Ch);
	void ReadChannels(void);


// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	ValueList *GetValueInfoTable(int &Entries, int Index=0);
	// Routines for communication

	bool ANPRO10_IO_UnpackPacket(U8 *Buf);
	void SendToIO(U16 Command, void* Data, U16 Size, bool RequestAck);
    void PowerOn(void);
    void PowerOff(int PowerStatus);
	void HandleIO(int Delay);
	void RequestMeasuredData(int Channel, int  DataType);
	int ReceiveData(U8* data);
	int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
#endif
	int GetRequestNumber(void);

};

//---------------------------------------------------------------------------
#endif

