#include "StdAfx.h"
#include ".\pvcscontrolobjectballastpump.h"
#include "pvcscontrolobjectinfo.h"
#include "pvcswagocontrol.h"
#include ".\pvcs v1.0.h"
#include <queue>
#include "DxfLayout.h"

// The container to queue the timed digital signal off requests
//std::queue<PvcsControlObjectTypes::DigitalSignal> g_DigSigQ;

// Handle to the timer
HANDLE g_hTimer;


// Function name   : CPvcsControlObjectBallastPump::CPvcsControlObjectBallastPump
// Description     : Constructor
// Return type     : 

CPvcsControlObjectBallastPump::CPvcsControlObjectBallastPump()
: m_hTimerQ( CreateTimerQueue() )
{
}

// Function name   : CPvcsControlObjectBallastPump::~CPvcsControlObjectBallastPump
// Description     : Destructor
// Return type     : 
// Argument        : void

CPvcsControlObjectBallastPump::~CPvcsControlObjectBallastPump(void)
{
	DeleteTimerQueueEx( m_hTimerQ, NULL );
}


// Function name   : CPvcsControlObjectBallastPump::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectBallastPump::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	int nStatus = 0;
	bool bValue;

	// If input is true, status is 1 else status is 2
	if( param_info.GetInputDigitalSignalList().size() != 0 
		&& CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ) , bValue,param_info.GetWagoUnitType() ) )
		nStatus = bValue ? 1 : 2;

	return nStatus;
}


// Function name   : CPvcsControlObjectBallastPump::GetColor
// Description     : Returns the object color corresponding to the current status
// Return type     : const COLORREF& 
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectBallastPump::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2)
{
	return param_info.GetStatusColor( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectBallastPump::GetInText
// Description     : Returns the Intext corresponding to the current status
// Return type     : const CString& 
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectBallastPump::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return param_info.GetStatusInText( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectBallastPump::GetValueString
// Description     : Not implemented
// Return type     : CString 
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectBallastPump::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	param_info;
	return CString();
}


// Function name   : CPvcsControlObjectBallastPump::OnButton
// Description     : Sends the control instruction to the object corresponding to button click
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectBallastPump::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{
	bool bResult = false;
//TRACE("onbutton- start");
	if( param_info.GetOutputDigitalSignalList().size() > 1 )
	{
		CDxfLayout::SetControlOperationState(param_info.GetIndex(),param_info.GetSubIndex(),false);
	
		// If button is pressed
		if( param_bIsPressed )
		{
			// Set the output to true
			bResult = 
				CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at( param_nButton ), true );

			// If the output was "pulse" type
			if( param_info.GetDigitalOutputPulseDuration( param_nButton ) > 0 )
			{
				// Initialize the timer
				ASSERT( m_hTimerQ );

				if( m_hTimerQ )
				{
					// Push the output into the timer queue
					//g_DigSigQ.push(param_info.GetOutputDigitalSignalList().at( param_nButton ));
					using namespace PvcsControlObjectTypes;

					DigitalSignal *ptempInfo = new DigitalSignal( param_info.GetOutputDigitalSignalList().at( param_nButton ) );

					CreateTimerQueueTimer( &g_hTimer, m_hTimerQ, TimerCallback, (PVOID)(ptempInfo),
							param_info.GetDigitalOutputPulseDuration( param_nButton ), 0, WT_EXECUTEINTIMERTHREAD);
					
					ASSERT(g_hTimer);
				}
			} // if( param_info.GetDigitalOutputPulseDuration( param_nButton ) > 0 )

			// If last operation was successful
			if( bResult )
			{
				// Wait for feedback
				clock_t begin_tick = clock();
				clock_t cur_tick;
				bool bValue;

				// Change the cursor shape
				HCURSOR hCurs; 
				hCurs = LoadCursor(NULL, IDC_WAIT); 
				SetCursor( hCurs );

				// The "wait" loop
				do{
					cur_tick = clock() - 100; //100ms for sleep time remove 

					long time_elapsed = ( ( cur_tick - begin_tick ) * 1000 ) / CLOCKS_PER_SEC;
					if( ( time_elapsed  > param_info.GetTimeOut() ) )
					{
						// The "wait" timed out
						// ie the object failed to respond
						bResult = false;
                        string tStr = "WARNING\n"+param_info.GetName()+" TimeOut";
                        AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);

						break;
					} // if( ( time_elapsed  > param_info.GetTimeOut() ) )

					CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue,param_info.GetWagoUnitType() );

					if( param_nButton == 1 )
						bValue = !bValue;

					Sleep(100);
				}while( !bValue && CPVCSApp::m_bIsAlive); //while( (param_nButton==0 && !bValue) ||(param_nButton==1 && bValue)  );
				
				if(!CPVCSApp::m_bIsAlive)
					return false;
			
				//by  
				//bool bValue = false;
				//Sleep(param_info.GetTimeOut());
				//CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue );

				//if( param_nButton == 1 )
				//bValue = !bValue;
				//bResult = bValue;
				
			} // if( bResult )

			
		} // if( param_bIsPressed ) 
		// else send the "off" signal at the release of the button if it was'nt a pulsed output
		else if( !param_bIsPressed && ( param_info.GetDigitalOutputPulseDuration( param_nButton ) == 0 ) )
			bResult = 
				CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at( param_nButton ), false );
	
		CDxfLayout::SetControlOperationState(param_info.GetIndex(),param_info.GetSubIndex(),true);

	} // if( param_info.GetOutputDigitalSignalList().size() > 0 )
    
	try{
		if( !param_bIsPressed && ( param_info.GetDigitalOutputPulseDuration( param_nButton ) != 0 ) )
			bResult = true;
	}
	catch( exception &e )
	{
		//TRACE("*******pvcscontrolobjectballastpump-onbutton*****");
		XmlLogError( e.what() );
	}
//TRACE("onbutton- end");
	return bResult;
}


// Function name   : CPvcsControlObjectBallastPump::OnSetSpin
// Description     : Not implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectBallastPump::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
	return false;
}


// Function name   : CPvcsControlObjectBallastPump::GetSpinInitInfo
// Description     : Not implemented
// Return type     : void 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strValue

void CPvcsControlObjectBallastPump::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue)
{
}


// Function name   : TimerCallback
// Description     : The timer callback function to send the "off" signal to the queued control objects
// Return type     : VOID CALLBACK 
// Argument        :  PVOID
// Argument        : BOOLEAN

VOID CALLBACK TimerCallback( PVOID pvData, BOOLEAN )
{
	//if( !g_DigSigQ.empty() )
	//{
	//	CPvcsWagoControl::theWagoUnit().SetValue( g_DigSigQ.front(), false );
	//	g_DigSigQ.pop();
	//}
	using namespace PvcsControlObjectTypes;

	DigitalSignal *ptempInfo = (DigitalSignal*)(pvData);

	CPvcsWagoControl::theWagoUnit().SetValue( *ptempInfo, false );

	delete ptempInfo;
}

