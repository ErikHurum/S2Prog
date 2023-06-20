#pragma once
//---------------------------------------------------------------------------
#ifndef AIPressSensorH
#define AIPressSensorH

class AIPressSensor:
public AnalogInput {
private:
	float *TempPtr;
	float  PrevTemp;
protected:
    bool NoShortCircuitAlarm;

public:
    float CableLengthShip;
    float CableLengthSensor;
    float CableResistanceShip;
    float CableResistanceSensor;
    float CableMsrdResistance;
    float CableOffset;
    bool  hasCableResistanceShip;
    bool  hasCableResistanceSensor;
    bool  hasCableLengthSensor;
	float RefPressDiff;
	AIPressSensor(bool IsAtmRef=false);
	AIPressSensor(int SnsType, bool IsAtmRef=false);
	~AIPressSensor(void);
    void Initialize(void);
    static float AtmPressure;
	set<AIPressSensor*>RefPressSensorSet;
	set<AIPressSensor*>SensorSet;
	static set<AIPressSensor*>ObjectSet;


// Routines for the Configuration
	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	virtual bool LoadConfigString(TSNConfigString &ConfigString);
	void SetRefSnsPtr(AIPressSensor *SnsPtr);
	virtual void AddTempRefSensor(float *TmpPtr);
	virtual float Calculate(void);
// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
	int CheckInput(float Operator_Val, int &Action);
	int GetUnitId(int *DecPntPtr=NULL);
	// This routine should have been on the Atmospheric sensor,
	// but lack of multiple inheritance makes this the second best
	static void AdjustOffsets(float OffsetChange,bool IsLocal);
	float CalcRefPressure(void);
	int InputToLinkedRefSensors(int ValueId, float NewValu,bool Local);
	int InputToLinkedLevelSensors(int ValueId,float NewValue,bool Local);
	void AddLevelPressSensor(AIPressSensor* SnsPtr);
	virtual void SetTmpSnsPtr(AITempSensor *SnsPtr);
	virtual AITempSensor *GetTmpSnsPtr(void);
	virtual void AdjustOffset(float OffsetAdjust);
    virtual void AddShortCircuitAlarm(void);
#ifdef ANWIN
	static void PrepareDatabase(TLiteQuery *LiteQuery);
	void AddSensorRecord(TLiteQuery *LiteQuery);
	static void LogData(TLiteQuery *LiteQuery, const volatile bool &Terminated, int Delay);
	void LogDataFromSensor(TLiteQuery *LiteQuery);
	static void CleanLogDataFromSensor(TLiteQuery *LiteQuery, int MaxAge);
	bool IsallreadyAdded(TLiteQuery *LiteQuery);
#endif
};

//---------------------------------------------------------------------------
#endif
