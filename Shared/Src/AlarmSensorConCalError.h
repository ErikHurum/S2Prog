#pragma once
#ifndef AlarmSensorConCalErrorH
#define AlarmSensorConCalErrorH

#define MAX_CON_CAL_ERRORS		5
class AlarmSensorConCalError :
public AlarmBasic {
private:
	ConfigPacket *ADConfigDataPtr;
public:
	AlarmSensorConCalError(void);
	~AlarmSensorConCalError(void);

	static unsigned NumberOfAlarms;
	AlarmSensorConCalError(PRogramObjectBase *PROPtr,ConfigPacket *ADConfDataPtr);
	void Check(void);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};
#endif
