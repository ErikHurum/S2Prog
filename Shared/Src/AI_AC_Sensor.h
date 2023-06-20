//---------------------------------------------------------------------------
#pragma once
#ifndef AI_AC_SensorH
#define AI_AC_SensorH

class AI_AC_Sensor:public AnalogInput {
private:
	bool  HasVoltage;

public:
	AI_AC_Sensor(void);
	~AI_AC_Sensor(void);

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
