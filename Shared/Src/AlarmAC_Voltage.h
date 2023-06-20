//---------------------------------------------------------------------------
#pragma once
#ifndef AlarmAC_VoltageH
#define AlarmAC_VoltageH

class AlarmAC_Voltage:public AlarmBasic{
public:
	static unsigned NumberOfAlarmSettings;
	AlarmAC_Voltage(PRogramObjectBase *PROPtr);

	void Check(void);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};

//---------------------------------------------------------------------------
#endif
