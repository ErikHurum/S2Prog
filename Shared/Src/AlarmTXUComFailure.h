#pragma once
#ifndef AlarmTXUComFailure_h
#define AlarmTXUComFailure_h
class AlarmTXUComFailure :
	public AlarmBasic
{

public:
	AlarmTXUComFailure(PRogramObjectBase *PROPtr, float Lim);
	~AlarmTXUComFailure(void);

	static unsigned NumberOfAlarmSettings;
	AlarmTXUComFailure(void);

	void Check(void);



// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

};
#endif
