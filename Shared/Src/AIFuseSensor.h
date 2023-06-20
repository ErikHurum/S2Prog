//---------------------------------------------------------------------------
#pragma once
#ifndef AIFuseSensorH
#define AIFuseSensorH

class AIFuseSensor:public AnalogInput {
private:
	bool  HasVoltage;

public:
	AIFuseSensor(void);
	~AIFuseSensor(void);

// Routines for the librarian
	void NewValue(float NewValue);
	float Calculate(void);

	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);

};

//---------------------------------------------------------------------------
#endif
