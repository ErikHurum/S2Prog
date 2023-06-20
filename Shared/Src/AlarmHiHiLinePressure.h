//---------------------------------------------------------------------------
#ifndef AlarmHiHiLinePressureH
#define AlarmHiHiLinePressureH

class PROLinePressure;
class AlarmHiHiLinePressure:public AlarmHighLinePressure{
public:
	static unsigned NumberOfAlarmSettings;
	AlarmHiHiLinePressure(PRogramObjectBase *PROPtr);
};

//---------------------------------------------------------------------------
#endif
