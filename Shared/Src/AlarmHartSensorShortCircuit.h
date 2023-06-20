#pragma once
#ifndef AlarmHartSensorShortCircuitH
#define AlarmHartSensorShortCircuitH

class AlarmHartSensorShortCircuit :
public AlarmBasic {
private:
	int Count;
public:
	AlarmHartSensorShortCircuit(void);
	~AlarmHartSensorShortCircuit(void);

	static unsigned NumberOfAlarms;
	AlarmHartSensorShortCircuit(PRogramObjectBase *PROPtr);
	void Check(void);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};
#endif
