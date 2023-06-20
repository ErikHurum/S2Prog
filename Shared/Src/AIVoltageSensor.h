//---------------------------------------------------------------------------
#pragma once
#ifndef AIVoltageSensorH
#define AIVoltageSensorH

class AIVoltageSensor:public AnalogInput {
private:
	float MaxVoltage;
	float MinVoltage;

public:
	AIVoltageSensor(int Loc,int BasicSnsType, float MinVolt, float MaxVolt);
	~AIVoltageSensor(void);

// Routines for the librarian
	virtual void NewValue(float NewValue);
	float Calculate(void);

	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);

};

//---------------------------------------------------------------------------
#endif
