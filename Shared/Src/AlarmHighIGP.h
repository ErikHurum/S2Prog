//---------------------------------------------------------------------------
#ifndef AlarmHighIGPH
#define AlarmHighIGPH
class PROTankPressure;
class AlarmHighIGP:public AlarmHighPressure{
public:
    static unsigned NumberOfAlarmSettings;
    AlarmHighIGP(PRogramObjectBase *PROPtr);
	AlarmHighIGP(PRogramObjectBase *PROPtr, float Lim, bool Visible);
    void Init(PRogramObjectBase *PROPtr);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
};

//---------------------------------------------------------------------------
#endif
