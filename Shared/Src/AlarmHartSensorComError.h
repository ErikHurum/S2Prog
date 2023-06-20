#pragma once
#ifndef AlarmHartSensorComErrorH
#define AlarmHartSensorComErrorH

#define MAX_HART_COM_ERRORS		20
class AlarmHartSensorComError :
public AlarmBasic {
private:
	int &Count;
public:
	~AlarmHartSensorComError(void);

	static unsigned NumberOfAlarms;
	AlarmHartSensorComError(PRogramObjectBase *PROPtr, int &HartComErrorCnt);
	void Check(void);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};
#endif
