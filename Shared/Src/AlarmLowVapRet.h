//---------------------------------------------------------------------------
#ifndef AlarmLowVapRetH
#define AlarmLowVapRetH
class PROTankPressure;
class AlarmLowVapRet:public AlarmLowPressure{
public:
    static unsigned NumberOfAlarmSettings;
    AlarmLowVapRet(PRogramObjectBase *PROPtr);
	AlarmLowVapRet(PRogramObjectBase *PROPtr, float Lim, bool Visible);
    void Init(PRogramObjectBase *PROPtr);
};

//---------------------------------------------------------------------------
#endif
