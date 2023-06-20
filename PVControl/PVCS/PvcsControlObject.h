#pragma once
#include ".\PvcsControlObjectInfo.h"
//using namespace PvcsControlObjectTypes;
#include <vector>
class CPvcsControlObjectInfo;
class CPvcsWagoControl;
class PvcsAlarmObject;
using namespace PvcsControlObjectTypes;

// Class: CPvcsControlObject
// Description: The abstract base class for the control objects.
class CPvcsControlObject
{

	virtual int GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1) = 0;

public:
	vector<PvcsAlarmObject*>AlarmVector;
	virtual ~CPvcsControlObject(void);

	virtual const Gdiplus::ARGB& GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1) = 0;
	virtual const CString& GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1) = 0;
	
	virtual CString GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1) = 0;

	virtual bool OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed) = 0;
	virtual bool OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue) = 0;
	virtual void GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue) = 0;
	static UINT AnalogScaleWagoToObject(const UINT& param_uiMin, const UINT& param_uiMax, const UINT& param_uiValue,CString param_psObjectName,CString param_psWagoUnitType);
	static double AnalogScaleWagoToObjectD(const UINT& param_uiMin, const UINT& param_uiMax, const UINT& param_uiValue,CString param_psWagoUnitType);
	static UINT AnalogScaleObjectToWago(const UINT& param_uiMin, const UINT& param_uiMax, const UINT& param_uiValue,CString param_psWagoUnitType);
	virtual bool CheckAlarm(DigitalSignal DigitalInput,CString WagoUnitType);
};
