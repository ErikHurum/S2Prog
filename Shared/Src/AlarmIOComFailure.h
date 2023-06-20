#pragma once
#ifndef AlarmIOComFailure_h
#define AlarmIOComFailure_h
class AlarmIOComFailure :
	public AlarmBasic
{

public:
	AlarmIOComFailure(PRogramObjectBase *PROPtr, float Lim);
	~AlarmIOComFailure(void);

	static unsigned NumberOfAlarmSettings;
	AlarmIOComFailure(void);

	void Check(void);



// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

};
#endif
