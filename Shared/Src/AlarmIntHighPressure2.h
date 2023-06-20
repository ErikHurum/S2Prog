//---------------------------------------------------------------------------
#ifndef AlarmIntHighPressure2H
#define AlarmIntHighPressure2H
class PROTankPressure;
class AlarmIntHighPressure2:public AlarmHighPressure{
public:
    static unsigned NumberOfAlarmSettings;
	AlarmIntHighPressure2(PRogramObjectBase *PROPtr, float Lim, bool Visible);
	AnsiString Get_Message(void);
};

//---------------------------------------------------------------------------
#endif
