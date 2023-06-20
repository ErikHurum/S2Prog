//---------------------------------------------------------------------------
#ifndef AlarmLowPressVacH
#define AlarmLowPressVacH
class PROTankPressure;
class AlarmLowPressVac:public AlarmLowPressure{
public:
    static unsigned NumberOfAlarmSettings;
    AlarmLowPressVac(PRogramObjectBase *PROPtr);
	AlarmLowPressVac(PRogramObjectBase *PROPtr, float Lim, bool Visible);
    void Init(PRogramObjectBase *PROPtr);
};

//---------------------------------------------------------------------------
#endif
