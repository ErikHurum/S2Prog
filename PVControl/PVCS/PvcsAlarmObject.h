#pragma once
#include "PvcsControlObjectInfo.h"
class CPvcsControlObject;
enum AlarmState {
    AlIdle,AlActive,AlAknowledged,AlBlocked
};
class PvcsAlarmObject
{
public:
	static vector<PvcsAlarmObject*>AlarmVector;
	AlarmState State;
	int AlarmCheckIndex;
	DigitalSignal	   DigitalInput;	// Digital input signals
	CPvcsControlObject *ObjectPtr;
	CString WagoUnitType;
	CString Tankid;
	CString TankNameDisplay;
	CString AlarmText;
	CString Limit;
	CString CurrentValue;
	CString Unit;
	CString TimeRaised;
	CString TimeAck;
	PvcsAlarmObject(CPvcsControlObject *ObjPtr);
	virtual ~PvcsAlarmObject(void);
	void SetActive(void);
	void Acknowledge(void);
	void SetIdle(void);
	void CheckAlarm(void);
	static void CheckAlarms(void);
};

