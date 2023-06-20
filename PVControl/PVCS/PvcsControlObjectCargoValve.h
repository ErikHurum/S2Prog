#pragma once
#include "pvcscontrolobject.h"
#include "PvcsControlObjectInfo.h"

//Thread to set Throttle Valve value
UINT SetCargoButtonThread(LPVOID pParam);
UINT SetCargoValueThread(LPVOID pParam);

// Class: CPvcsControlObjectCargoValve
// Description: Class to control the Cargo valves
class CPvcsControlObjectCargoValve :
    public CPvcsControlObject
{
private:
    virtual int GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
    static bool CargoRegulator(CPvcsControlObjectInfo& param_info,clock_t TimeOut);
    static void CargoCheckAndSetValue(const DigitalSignal& param_DigPort, const bool param_bValue, CString pWagoUnit);
    static UINT SetCargoButtonThread(LPVOID pParam);
    static UINT SetCargoValueThread(LPVOID pParam);
    static void CargoThreadReset(int pIndex, int pSubIndex);

public:
    virtual ~CPvcsControlObjectCargoValve(void);

    virtual const COLORREF& GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
    virtual const CString& GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
    
    virtual CString GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);

    virtual bool OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed);
    virtual bool OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue);
    virtual void GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue);
};

