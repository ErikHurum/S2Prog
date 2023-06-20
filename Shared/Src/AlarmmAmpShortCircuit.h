#pragma once
#ifndef AlarmmAmpShortCircuit_h
#define AlarmmAmpShortCircuit_h
class AlarmmAmpShortCircuit :
	public AlarmBasic
{
public:
	AlarmmAmpShortCircuit(void);
	~AlarmmAmpShortCircuit(void);

	static unsigned NumberOfAlarmSettings;
	AlarmmAmpShortCircuit(PRogramObjectBase *PROPtr);

	void Check(void);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};
#endif
