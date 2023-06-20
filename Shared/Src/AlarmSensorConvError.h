#pragma once
#ifndef AlarmSensorConvErrorH
#define AlarmSensorConvErrorH
class AlarmSensorConvError :
public AlarmBasic {
private:
	ConfigPacket *ADConfigDataPtr;
public:
	AlarmSensorConvError(void);
	~AlarmSensorConvError(void);

	static unsigned NumberOfAlarmSettings;
	AlarmSensorConvError(PRogramObjectBase *PROPtr,ConfigPacket *ADConfDataPtr);
	void Check(void);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};
#endif
