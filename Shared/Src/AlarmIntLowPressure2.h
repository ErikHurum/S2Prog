//---------------------------------------------------------------------------
#ifndef AlarmIntLowPressure2H
#define AlarmIntLowPressure2H
class PROTankPressure;
class AlarmIntLowPressure2:public AlarmLowPressure{
public:
    static unsigned NumberOfAlarmSettings;
	AlarmIntLowPressure2(PRogramObjectBase *PROPtr, float Lim, bool Visible);
	AnsiString Get_Message(void);
};

//---------------------------------------------------------------------------
#endif
