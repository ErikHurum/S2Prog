//---------------------------------------------------------------------------
#ifndef PROIOComponentH
	#define PROIOComponentH
class ANPRO10Object;

class PROIOComponent:
public PRogramObjectBase {
protected:
	set<ANPRO10Object*>IOModuleSet;
public:
	set<AlarmBasic*>AlarmSet;

	AnsiString SerialNumber;

	int TCUAddress;
	int TCUPortNo;
	int IOType;
	int IOAddress;
	int IOChannel;
	int ADCardChannel;
	volatile bool HWFailure;
	volatile bool MyHWFailure;

	PROIOComponent(void);
	~PROIOComponent(void);
	virtual U8 GetFilter(void);

	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	virtual bool LoadConfigString(TSNConfigString &ConfigString);
	virtual float Calculate(void);
	void AddAlarms(set<AlarmBasic*>&AlInfoList);
// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);

	// Misc routines
	virtual void SetStatus(U8 *NewStatus);
	virtual void NewValue(float NewValue);
	virtual int ReceiveData(U8* data);
	virtual int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
	bool HasActiveAlarms(void);
	void AddIOMdulePtr(ANPRO10Object *IOModule);
	virtual int GetEEPROM_Status(void);
};

//---------------------------------------------------------------------------
#endif
