#pragma once
#ifndef AlarmModbusComFailure_h
#define AlarmModbusComFailure_h
class AlarmModbusComFailure :
    public AlarmBasic
{

public:
    AlarmModbusComFailure(PRogramObjectBase *PROPtr, float Lim);
    ~AlarmModbusComFailure(void);

    static unsigned NumberOfAlarmSettings;
    AlarmModbusComFailure(void);

    void Check(void);



// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    int PutFloatValue( int ValueId, float NewValue);

};
#endif
