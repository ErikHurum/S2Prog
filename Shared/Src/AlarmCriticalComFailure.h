#ifndef AlarmCriticalComFailure_h
#define AlarmCriticalComFailure_h
#pragma once
class AlarmCriticalComFailure :
	public AlarmBasic
{
private:
	time_t LastSyncTime;
	AnsiString Name;

public:
	static bool ComFailure;
    static AlarmCriticalComFailure *CriticalComAlarm;

	AlarmCriticalComFailure(AnsiString Name, float Lim);
	~AlarmCriticalComFailure(void);

	static unsigned NumberOfAlarmSettings;
	AlarmCriticalComFailure(void);
protected:
	void AddAlarm(void);
	void RemoveAlarm(void);
public:
	void Check(void);
	void SyncReceived(void);


	AnsiString Get_CompleteMessage(void);
	AnsiString Get_Location(void);


// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

  int ReceiveData(U8* data);
  int SendData(U16 cmd);


};
#endif
