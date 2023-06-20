//---------------------------------------------------------------------------
#ifndef AlarmIntHighPressure1H
#define AlarmIntHighPressure1H
class PROTankPressure;
class AlarmIntHighPressure1:public AlarmHighPressure{
public:
    static unsigned NumberOfAlarmSettings;
	AlarmIntHighPressure1(PRogramObjectBase *PROPtr, float Lim, bool Visible);
	float Get_Limit(void);
};

//---------------------------------------------------------------------------
#endif
