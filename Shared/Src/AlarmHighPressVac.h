//---------------------------------------------------------------------------
#ifndef AlarmHighPressVacH
#define AlarmHighPressVacH
class PROTankPressure;
class AlarmHighPressVac:public AlarmHighPressure{
public:
    static unsigned NumberOfAlarmSettings;
    AlarmHighPressVac(PRogramObjectBase *PROPtr);
	AlarmHighPressVac(PRogramObjectBase *PROPtr, float Lim, bool Visible);
    void Init(PRogramObjectBase *PROPtr);
};

//---------------------------------------------------------------------------
#endif
