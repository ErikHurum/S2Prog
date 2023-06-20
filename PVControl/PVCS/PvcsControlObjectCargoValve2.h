#pragma once
#include "pvcscontrolobject.h"
#include "PvcsControlObjectInfo.h"

//Thread to set Throttle Valve value
UINT SetCargoButtonThread(LPVOID pParam);
UINT SetCargoValueThread(LPVOID pParam);

// Class: CPvcsControlObjectCargoValve2
// Description: Class to control the Cargo valves
class CPvcsControlObjectCargoValve2 :
    public CPvcsControlObject
{
private:
    HANDLE m_hTimerQ2; // The handle to the timer queue implemented by the controller
    virtual int GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);

public:
    virtual ~CPvcsControlObjectCargoValve2(void);

    virtual const COLORREF& GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
    virtual const CString& GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
    
    virtual CString GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);

    virtual bool OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed);
    virtual bool OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue);
    virtual void GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue);



};

