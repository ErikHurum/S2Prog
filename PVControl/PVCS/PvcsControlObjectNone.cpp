#include "StdAfx.h"
#include ".\pvcscontrolobjectnone.h"
#include "pvcscontrolobjectinfo.h"



// Function name   : CPvcsControlObjectNone::~CPvcsControlObjectNone
// Description     : Destructor
// Return type     : 
// Argument        : void

CPvcsControlObjectNone::~CPvcsControlObjectNone(void)
{
}


// Function name   : CPvcsControlObjectNone::GetColor
// Description     : Gets the default color
// Return type     : const COLORREF& 
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectNone::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2)
{
	return param_info.GetStatusColor( 1 );
}


// Function name   : CPvcsControlObjectNone::GetInText
// Description     : Gets the default in text
// Return type     : const CString& 
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectNone::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return param_info.GetStatusInText( 1 );
}


// Function name   : CPvcsControlObjectNone::GetValueString
// Description     : Not Implemented
// Return type     : CString 
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectNone::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return CString();
}


// Function name   : CPvcsControlObjectNone::OnButton
// Description     : Not Implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectNone::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{
	return false;
}


// Function name   : CPvcsControlObjectNone::OnSetSpin
// Description     : Not Implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectNone::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
	return false;
}


// Function name   : CPvcsControlObjectNone::GetStatus
// Description     : Not Implemented
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectNone::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return 0;
}


// Function name   : CPvcsControlObjectNone::GetSpinInitInfo
// Description     : Not Implemented
// Return type     : void 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strValue

void CPvcsControlObjectNone::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue)
{
}
