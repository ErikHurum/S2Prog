//---------------------------------------------------------------------------
#ifndef AlarmLowIGPH
#define AlarmLowIGPH
class PROTankPressure;
class AlarmLowIGP:public AlarmLowPressure{
public:
    static unsigned NumberOfAlarmSettings;
    AlarmLowIGP(PRogramObjectBase *PROPtr);
	AlarmLowIGP(PRogramObjectBase *PROPtr, float Lim, bool Visible);
    void Init(PRogramObjectBase *PROPtr);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
};

//---------------------------------------------------------------------------
#endif
