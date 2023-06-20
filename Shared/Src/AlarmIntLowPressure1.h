//---------------------------------------------------------------------------
#ifndef AlarmIntLowPressure1H
#define AlarmIntLowPressure1H
class PROTankPressure;
class AlarmIntLowPressure1:public AlarmLowPressure{
public:
    static unsigned NumberOfAlarmSettings;
	AlarmIntLowPressure1(PRogramObjectBase *PROPtr, float Lim, bool Visible);
};

//---------------------------------------------------------------------------
#endif
