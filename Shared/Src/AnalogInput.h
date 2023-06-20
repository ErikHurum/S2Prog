#pragma once
//---------------------------------------------------------------------------
#ifndef AnalogInputH
	#define AnalogInputH

class PRogramObject;
class AnalogInput:
public PROIOComponent {
private:
	//static set<AnalogInput*> AIPtrSet;
	static ValueList ServiceReportSensorValueList[];
protected:
	int   BasicSensorType;
	int   BasicSensorTypeWord;
	int   LocationKWord;
	int   OutsideCnt;
	bool  IsPressureSns;
    bool  HasDistance;



public:
	static vector<AnalogInput*> AIPtrVector;
	AnalogInput(void);
	void Init(void);
	~AnalogInput(void);
	PRogramObject *PROPtr;
	int   	Location;
	float 	Distance;
	float 	AdjustedDistance;
	bool  	Enable;
	bool  	Modified;
	bool  	ResultOK;
	bool  	NewSensor;
	U8    	Failure;
	float 	Gain  ;
	float 	Offset;
	float 	FilteredValue;
	float 	CalcValue;
	bool  	IsStartUp;

	time_t 	TimeModified;
	clock_t TimeChecked;
	int		ModifiedBy;


// Calibration data
	float MinRange;
	float MaxRange;

// Routines for the Configuration

	static unsigned GetFirstFreeId(set<unsigned> &AISet);
	static void CreateIdNum(void);
	void SetPROPtr(PRogramObject *PPtr);
	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	virtual bool LoadConfigString(TSNConfigString &ConfigString);
	void SetLocationKeyWord(int KWd);
// Routines for Saving of Settings
	virtual AnsiString SaveAISettings(int ExtraTab=0);
	virtual bool RestoreAISettings(TSNConfigString *ConfigString);

// Routines for Calculation of values
	int AdjustSensor(AnsiString NewValue, int Unit, float Min,float Max,bool Local);
	int AdjustSensorF(float Operator_Val,bool Local);
	virtual void UpdateAllDependingSensorOffsets(float OffsetChange,bool IsLocal);
	virtual float Calculate(void);

// Routines for the librarian
	int FindPROStatus(AnsiString &MyString);
	AnsiString GetName(void);
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
	virtual int CheckInput(float Operator_Val, int &Action);
	virtual int ReceiveData(U8* data);
	virtual int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
	virtual void SetStatus(U8 *NewStatus);
	virtual void NewValue(float NewValue);
	void SetModifiedFlag(void);
	virtual ValueList *GetValueInfoTable(int &Entries, int Index=0);
	virtual ValueList *GetServiceValueInfoTable(int &Entries);
	static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);
	static ValueList *GetServiceValueInfoTableStatic(int &Entries);
	static vector<int>GetValueIdVector(int Index);
	static vector<ValueList>GetValueInfoVector(int Index);
	static vector<ValueList>GetServiceValueInfoVector(void);
	int GetBasicSensorType(void);
	void SetIsPressureSns(bool TPressState=true);
	bool GetIsPressureSns(void);
	bool CanCalculate(void);
	virtual void SetNewStatus(bool NewStatus);
    virtual bool GetErrorStatus(void);
	static vector<PRogramObjectBase*>GetProgramObjectBaseVector(vector<AnalogInput*>MyVect);
};

//---------------------------------------------------------------------------
#endif
