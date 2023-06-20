//---------------------------------------------------------------------------
#ifndef IOUnitH
	#define IOUnitH
#include "TSNVersion.h"

class IOUnit:public ANPRO10Object {
protected:
	U8      CardChannel;
	U8      CardId;
	U8      CardAddress;
	U8      UnitProgVersion;
	U8      ComVersion;
	U8      StoreVersion;
	U16     RxBufSize;
	U16     TxBufSize;
	U8      ProgamTypeRunning;
	float   CardVoltage;
	U8      IOunitstatus;

	U8      SequenceNumber;
	time_t  PowerOnTime;
	U16     PowerStatus;
	U16		HART_Sensor;
	U8      FlashEraseStatus;
	U8      ProgrammingStatus;
	I16     TotalUnitRestart;

	time_t  ReqStatusTime;
public:
	static set<PRogramObject*>GlobalHW_UnitSet;
	static set<PRogramObject*>GlobalPRO_IOList;
	set<PRogramObject*>IOUniquePROSet;
	int TCUAddress;
	int TCUPortNo;
	int IOType;
	int IOAddress;
//  int IOPort;
//  int ADCardChannel;
	volatile U8     ResetStatus;
	volatile bool   Restart;

	IOUnit(int PortNo);
	~IOUnit(void);

// Routines for the Configuration
	AnsiString MakeConfigString(int ExtraTabs=0);
	bool LoadConfigString(TSNConfigString &ConfigString);
	virtual bool Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr);

	#ifndef ANCONF
// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);

	virtual void PowerOn(void);
	virtual void HandleIO(int Delay);

	virtual void SendToIO(U16 Command, void* Data, U16 Size, bool RequestAck);
	void Request(U16 Command);
	bool EraseFlash(void);
	bool ProgramFlash(U16 Address, U16 Size, char* ProgramImage);
	virtual bool UpdateProgram(void);
	virtual int GetRequestNumber(void);
	static void DeleteAll(void);
	#endif

};

//---------------------------------------------------------------------------
#endif
