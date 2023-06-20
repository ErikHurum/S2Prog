#include "StdAfx.h"
#include ".\pvcscontrolobjectstatic.h"
#include "pvcscontrolobjectinfo.h"



// Function name   : CPvcsControlObjectStatic::~CPvcsControlObjectStatic
// Description     : Destructor
// Return type     : 
// Argument        : void

CPvcsControlObjectStatic::~CPvcsControlObjectStatic(void)
{
}


// Function name   : CPvcsControlObjectStatic::GetColor
// Description     : Get the default color
// Return type     : const COLORREF& 
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectStatic::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2)
{
	return param_info.GetStatusColor( 1 );
}


// Function name   : CPvcsControlObjectStatic::GetInText
// Description     : Get the default in text
// Return type     : const CString& 
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectStatic::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return param_info.GetStatusInText( 1 );
}


// Function name   : CPvcsControlObjectStatic::GetValueString
// Description     : Not Implemented
// Return type     : CString 
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectStatic::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return CString();
}


// Function name   : CPvcsControlObjectStatic::OnButton
// Description     : Not Implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectStatic::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{
	return false;
}


// Function name   : CPvcsControlObjectStatic::OnSetSpin
// Description     : Not Implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectStatic::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
	return false;
}


// Function name   : CPvcsControlObjectStatic::GetStatus
// Description     : Not Implemented
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectStatic::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return 0;
}


// Function name   : CPvcsControlObjectStatic::GetSpinInitInfo
// Description     : Not Implemented
// Return type     : void 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strValue

void CPvcsControlObjectStatic::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue)
{
}
