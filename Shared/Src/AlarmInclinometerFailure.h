#pragma once
#ifndef AlarmInclinometerFailure_h
#define AlarmInclinometerFailure_h
class AlarmInclinometerFailure :
   public AlarmBasic {

public:
    AlarmInclinometerFailure(PRogramObjectBase *PROPtr);
    ~AlarmInclinometerFailure(void);

    static unsigned NumberOfAlarmSettings;
    AlarmInclinometerFailure(void);

    void Check(void);



// Routines for the librarian
    AnsiString Get_CompleteMessage(void);

    int GetValue(int ValueId, int Index, float& MyValue,  int& DecPnt, int& Unit);
    int GetStringValue(int ValueId, int Index, AnsiString& MyString);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue(int ValueId, float NewValue);

};
#endif
