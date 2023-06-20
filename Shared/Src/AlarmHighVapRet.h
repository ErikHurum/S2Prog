//---------------------------------------------------------------------------
#ifndef AlarmHighVapRetH
#define AlarmHighVapRetH
class PROTankPressure;
class AlarmHighVapRet:public AlarmHighPressure{
public:
    static unsigned NumberOfAlarmSettings;
    AlarmHighVapRet(PRogramObjectBase *PROPtr);
	AlarmHighVapRet(PRogramObjectBase *PROPtr, float Lim, bool Visible);
    void Init(PRogramObjectBase *PROPtr);
};

//---------------------------------------------------------------------------
#endif
