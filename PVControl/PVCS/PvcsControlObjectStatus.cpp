#include "StdAfx.h"
#include "pvcscontrolobjectStatus.h"
#include "pvcs v1.0.h"
#include "pvcscontrolobjectinfo.h"
#include "pvcswagocontrol.h"
#include "DxfLayout.h"

CPvcsControlObjectStatus::CPvcsControlObjectStatus(void)
{
}


// Function name   : CPvcsControlObjectStatus::~CPvcsControlObjectStatus
// Description     : Destructor
// Return type     : 
// Argument        : void

CPvcsControlObjectStatus::~CPvcsControlObjectStatus(void)
{
}


// Function name   : CPvcsControlObjectStatus::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectStatus::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	int nStatus = 0;
	bool bValue = false;

	// The status is determined as follows:
	// Digital input 1 true: Status = 1
	// Digital input 2 true: Status = 2
	// Digital input 1 false and 2 false: Status = 3
	// Digital input 1 true and 2 true: Status = 4

	if( param_info.GetInputDigitalSignalList().size() >= 1 )
	{
		if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue,param_info.GetWagoUnitType() ) )
		{
            if( bValue ){
				nStatus = 2;
			}else {
				nStatus = 1;
			}

		} // if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue ) )

	} // if( param_info.GetInputDigitalSignalList().size() > 1 )
    
	return nStatus;
}


// Function name   : CPvcsControlObjectStatus::GetColor
// Description     : Returns the object color corresponding to the current status
// Return type     : const COLORREF& 
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectStatus::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2)
{
	return param_info.GetStatusColor( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectStatus::GetInText
// Description     : Returns the Intext corresponding to the current status
// Return type     : const CString& 
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectStatus::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return param_info.GetStatusInText( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectStatus::GetValueString
// Description     : Not implemented
// Return type     : CString 
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectStatus::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return CString();
}


// Function name   : CPvcsControlObjectStatus::OnButton
// Description     : Sends the control instruction to the object corresponding to button click
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectStatus::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{ 
	return false;
}


// Function name   : CPvcsControlObjectStatus::OnSetSpin
// Description     : Not implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectStatus::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
	return false;
}


// Function name   : CPvcsControlObjectStatus::GetSpinInitInfo
// Description     : Not implemented
// Return type     : void 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strValue

void CPvcsControlObjectStatus::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue)
{
}

