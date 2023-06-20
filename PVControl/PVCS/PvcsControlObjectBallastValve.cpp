#include "StdAfx.h"
#include ".\pvcscontrolobjectballastvalve.h"
#include ".\pvcs v1.0.h"
#include "pvcscontrolobjectinfo.h"
#include "pvcswagocontrol.h"
#include "DxfLayout.h"



// Function name   : CPvcsControlObjectBallastValve::~CPvcsControlObjectBallastValve
// Description     : Destructor
// Return type     : 
// Argument        : void

CPvcsControlObjectBallastValve::~CPvcsControlObjectBallastValve(void)
{
}


// Function name   : CPvcsControlObjectBallastValve::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectBallastValve::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	int nStatus = 0;
	bool bValue = false;

	// The status is determined as follows:
	// Digital input 1 true: Status = 1
	// Digital input 2 true: Status = 2
	// Digital input 1 false and 2 false: Status = 3
	// Digital input 1 true and 2 true: Status = 4

	if( param_info.GetInputDigitalSignalList().size() > 1 )
	{
		if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue,param_info.GetWagoUnitType() ) )
		{
            if( bValue )
				nStatus = 1;

			if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 1 ), bValue,param_info.GetWagoUnitType() ) )
			{
				if( bValue )
					nStatus |= 2;

				switch( nStatus )
				{
				case 0 : nStatus = 3;
					break;
				case 3 : nStatus = 4;
					break;
				} // switch( nStatus )

			} // if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 1 ), bValue ) )

		} // if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue ) )

	} // if( param_info.GetInputDigitalSignalList().size() > 1 )
    
	return nStatus;
}


// Function name   : CPvcsControlObjectBallastValve::GetColor
// Description     : Returns the object color corresponding to the current status
// Return type     : const COLORREF& 
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectBallastValve::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2)
{
	return param_info.GetStatusColor( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectBallastValve::GetInText
// Description     : Returns the Intext corresponding to the current status
// Return type     : const CString& 
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectBallastValve::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return param_info.GetStatusInText( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectBallastValve::GetValueString
// Description     : Not implemented
// Return type     : CString 
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectBallastValve::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return CString();
}


// Function name   : CPvcsControlObjectBallastValve::OnButton
// Description     : Sends the control instruction to the object corresponding to button click
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectBallastValve::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{ 
	bool bResult = false;

	if( param_bIsPressed && param_info.GetOutputDigitalSignalList().size() > 0 )
	{
		CDxfLayout::SetControlOperationState(param_info.GetIndex(),param_info.GetSubIndex(),false);

		// Set the digital output corresponding to the button being clicked
		bResult = param_nButton == 0 ?
			CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at(0), true )
			: CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at(0), false );

		// If last operation was successful
		if( bResult )
		{
			// Wait for feedback
			clock_t begin_tick = clock();
			clock_t cur_tick;
			bool bValue = false;

			// Change the cursor shape
			HCURSOR hCurs; 
			hCurs = LoadCursor(NULL, IDC_WAIT); 
			SetCursor( hCurs );

			// The "wait" loop
			while( !bValue && CPVCSApp::m_bIsAlive)
			{
				cur_tick = clock() - 100;//100ms for Sleep time

				long time_elapsed = ( ( cur_tick - begin_tick ) * 1000 ) / CLOCKS_PER_SEC;
				if( ( time_elapsed  > param_info.GetTimeOut() ) )
				{
					// The "wait" timed out
					// ie the object failed to respond
					bResult = false;
					string tStr = "WARNING\n"+param_info.GetName()+" TimeOut";
					AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);

                    /*
					std::auto_ptr<CPvcsWagoConnectDlg> m_pdlgConnect;

					m_pdlgConnect.reset( new CPvcsWagoConnectDlg );

					m_pdlgConnect->Create( IDD_AlARMBUTTONHOLDER );
                    */

					break;
				} // if( ( time_elapsed  > param_info.GetTimeOut() ) )

				CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( param_nButton ), bValue,param_info.GetWagoUnitType() );

				Sleep(100);
			} // while( !bResult )
			
			if(!CPVCSApp::m_bIsAlive)
				return false;
		
			// 
			//bool bValue = false;
			//Sleep(param_info.GetTimeOut());
			//CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( param_nButton ), bValue );

			//bResult = bValue;

		} // if( bResult )

	CDxfLayout::SetControlOperationState(param_info.GetIndex(),param_info.GetSubIndex(),true);
	} // if( param_info.GetOutputDigitalSignalList().size() > 0 )
    
	if( !param_bIsPressed )
		bResult = true;

	return bResult;
}


// Function name   : CPvcsControlObjectBallastValve::OnSetSpin
// Description     : Not implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectBallastValve::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
	return false;
}


// Function name   : CPvcsControlObjectBallastValve::GetSpinInitInfo
// Description     : Not implemented
// Return type     : void 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strValue

void CPvcsControlObjectBallastValve::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue)
{
}

