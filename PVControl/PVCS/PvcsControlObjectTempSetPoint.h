#pragma once
#include "pvcscontrolobject.h"

// Class: CPvcsControlObjectTempSetPoint
// Description: Controller class for the Teperature set point objects
class CPvcsControlObjectTempSetPoint :
	public CPvcsControlObject
{
	virtual int GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);

	static COLORREF m_Color;	// The default color 

public:
	virtual ~CPvcsControlObjectTempSetPoint(void);
	
	virtual const COLORREF& GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	virtual const CString& GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	
	virtual CString GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);

	virtual bool OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed);
	virtual bool OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue);
	virtual void GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue);
};
