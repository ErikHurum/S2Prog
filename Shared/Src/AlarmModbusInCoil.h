#pragma once
//---------------------------------------------------------------------------
#ifndef AlarmModbusInCoilH
#define AlarmModbusInCoilH

class AlarmModbusInCoil:public AlarmBasic{
public:
	static unsigned NumberOfAlarmSettings;
	AlarmModbusInCoil(PRogramObjectBase *PROPtr, AnsiString LocName, AnsiString Descr);

	void Check(void);
	AnsiString Get_Message(void);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

};

//---------------------------------------------------------------------------
#endif
