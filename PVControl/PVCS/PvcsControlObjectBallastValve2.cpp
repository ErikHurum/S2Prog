#include "StdAfx.h"
#include ".\pvcscontrolobjectballastvalve2.h"
#include "pvcscontrolobjectinfo.h"
#include "pvcswagocontrol.h"
#include ".\pvcs v1.0.h"
#include "DxfLayout.h"

#include <queue>


// The container to queue the timed digital signal off requests
//std::queue<PvcsControlObjectTypes::DigitalSignal> g_DigSigQ;

// Handle to the timer
HANDLE g_hTimer2;


// Function name   : CPvcsControlObjectBallastValve2::CPvcsControlObjectBallastValve2
// Description     : Constructor
// Return type     :

CPvcsControlObjectBallastValve2::CPvcsControlObjectBallastValve2()
: m_hTimerQ2( CreateTimerQueue() )
{
}

// Function name   : CPvcsControlObjectBallastValve2::~CPvcsControlObjectBallastValve2
// Description     : Destructor
// Return type     :
// Argument        : void

CPvcsControlObjectBallastValve2::~CPvcsControlObjectBallastValve2(void)
{
	DeleteTimerQueueEx( m_hTimerQ2, NULL );
}


// Function name   : CPvcsControlObjectBallastValve2::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectBallastValve2::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	int nStatus = 0;
	bool bValue = false;

	// The status is determined as follows:
	// Digital input 1 true: Status = 1
	// Digital input 2 true: Status = 2
	// Digital input 1 false and 2 false: Status = 4
	// Digital input 1 true and 2 true: Status = 3

	if ( param_info.GetInputDigitalSignalList().size() > 1 ) {
		DigitalSignal DigIp1, DigIp2;
		try{
			DigIp1  = param_info.GetInputDigitalSignalList().at( 0 );
			DigIp2  = param_info.GetInputDigitalSignalList().at( 1 );
		}
		catch( exception &e )
		{
			//TRACE("*****CPvcsControlObjectCargoValve2-GetSpinInitInfo*******");
			XmlLogError( e.what() );
		}

		if ( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue ,param_info.GetWagoUnitType()) ) {
			if ( bValue )
				nStatus = 1;

			if ( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 1 ), bValue ,param_info.GetWagoUnitType()) ) {
				if ( bValue )
					nStatus |= 2;

				if ( !nStatus ) {
					nStatus = 4;
				} // switch( nStatus )

			}// if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 1 ), bValue ) )

		} // if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue ) )

	} // if( param_info.GetInputDigitalSignalList().size() > 1 )

	return nStatus;
}


// Function name   : CPvcsControlObjectBallastValve2::GetColor
// Description     : Returns the object color corresponding to the current status
// Return type     : const COLORREF&
// Argument        : const CPvcsControlObjectInfo& param_info

const COLORREF& CPvcsControlObjectBallastValve2::GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{

	return param_info.GetStatusColor( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectBallastValve2::GetInText
// Description     : Returns the Intext corresponding to the current status
// Return type     : const CString&
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectBallastValve2::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return param_info.GetStatusInText( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectBallastValve2::GetValueString
// Description     : Not implemented
// Return type     : CString
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectBallastValve2::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	param_info;
	return CString();
}


// Function name   : CPvcsControlObjectBallastValve2::OnButton
// Description     : Sends the control instruction to the object corresponding to button click
// Return type     : bool
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectBallastValve2::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{
	bool     bResult	  = false;
	unsigned PulsDuration = param_info.GetDigitalOutputPulseDuration(param_nButton);
 
	if ( param_info.GetOutputDigitalSignalList().size() > 1 ) {
		DigitalSignal DigOp1, DigOp2;
		try{
			DigOp1  = param_info.GetOutputDigitalSignalList().at( 0 );
			DigOp2  = param_info.GetOutputDigitalSignalList().at( 1 );
		}
		catch( exception &e )
		{
			//TRACE("*****CPvcsControlObjectCargoValve2-GetSpinInitInfo*******");
			XmlLogError( e.what() );
		}

		CDxfLayout::SetControlOperationState(param_info.GetIndex(),param_info.GetSubIndex(),false);

		// If button is pressed
		if ( param_bIsPressed ) {

			//if output is not of pulse type, then set output to true
			if ( PulsDuration == 0) {
                if (param_nButton==1) {
                    bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp1,false);
					Sleep(100);
                    bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp2,true);
                }else{
                    bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp2,false);
					Sleep(100);
                    bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp1,true);
                }
			}
			//else if output is of pulse type, then send true signal for the specified time period
			else  {
				// Initialize the timer
				ASSERT( m_hTimerQ2 );

				if ( m_hTimerQ2 ) {
					// Push the output into the timer queue
					//g_DigSigQ.push(param_info.GetOutputDigitalSignalList().at( param_nButton ));
					using namespace PvcsControlObjectTypes;

					DigitalSignal *ptempInfo = new DigitalSignal( param_info.GetOutputDigitalSignalList().at( param_nButton ) );

					CreateTimerQueueTimer( &g_hTimer2, m_hTimerQ2, BVTimerCallback, (PVOID)(ptempInfo),
										   param_info.GetDigitalOutputPulseDuration( param_nButton ), 0, WT_EXECUTEINTIMERTHREAD);

					ASSERT(g_hTimer2);
				}

                if (param_nButton==1) {
                    bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp1,false);
					Sleep(100);
                    bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp2,true);
                }else{
                    bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp2,false);
					Sleep(100);
                    bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp1,true);
                }
				//bResult = CPvcsWagoControl::theWagoUnit().SetValue(param_info.GetOutputDigitalSignalList().at(param_nButton),true);
			} // if( param_info.GetDigitalOutputPulseDuration( param_nButton ) > 0 )

			// If last operation was successful
			if ( bResult ) {
				// Wait for feedback
				clock_t begin_tick = clock();
				clock_t cur_tick;
			    int nState = 0;
				int sState = 1 << param_nButton;

				// Change the cursor shape
				HCURSOR hCurs;
				hCurs = LoadCursor(NULL, IDC_WAIT);
				SetCursor( hCurs );

				// The "wait" loop
				while ( (nState != sState) && CPVCSApp::m_bIsAlive) {
					cur_tick = clock() - 100; //100ms for sleep time

					long time_elapsed = ( ( cur_tick - begin_tick ) * 1000 ) / CLOCKS_PER_SEC;
					if ( ( time_elapsed  > param_info.GetTimeOut() ) ) {
						// The "wait" timed out
						// ie the object failed to respond
                        string tStr = "WARNING\n"+param_info.GetName()+" TimeOut";
                        AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);

						bResult = false;
						break;
					} // if( ( time_elapsed  > param_info.GetTimeOut() ) )
					nState = GetStatus(param_info);

					Sleep(100);
				} // while( !bResult )

				if (!CPVCSApp::m_bIsAlive)	return false;
				if ( !PulsDuration ){
					if ( nState == sState){
						Sleep(500);
					}
					if (param_nButton==1) {
						bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp2,false);
					}else{
						bResult |= CPvcsWagoControl::theWagoUnit().SetValue(DigOp1,false);
					}
				}


				// 
				//bool bValue = false;
				//Sleep(param_info.GetTimeOut());
				//CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( param_nButton ), bValue );
				//bResult = bValue;

			} // if( bResult )

		}//if(param_bIsPressed)

		if (!param_bIsPressed) { //if button released
			//if output is of pulse type, then send true signal for the specified time period
			if (PulsDuration == 0) {	
				bResult = true;
			}
		}//else if(!param_bIsPressed)
	
		CDxfLayout::SetControlOperationState(param_info.GetIndex(),param_info.GetSubIndex(),true);
	}//if( param_info.GetOutputDigitalSignalList().size() > 1 )

	return bResult;
}


// Function name   : CPvcsControlObjectBallastValve2::OnSetSpin
// Description     : Not implemented
// Return type     : bool
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectBallastValve2::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
	return false;
}


// Function name   : CPvcsControlObjectBallastValve2::GetSpinInitInfo
// Description     : Not implemented
// Return type     : void
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strValue

void CPvcsControlObjectBallastValve2::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue)
{
}


// Function name   : BVTimerCallback
// Description     : The timer callback function to send the "off" signal to the queued control objects
// Return type     : VOID CALLBACK
// Argument        :  PVOID
// Argument        : BOOLEAN

VOID CALLBACK BVTimerCallback( PVOID pvData, BOOLEAN )
{
	//if( !g_DigSigQ.empty() )
	//{
	//	CPvcsWagoControl::theWagoUnit().SetValue( g_DigSigQ.front(), false );
	//	g_DigSigQ.pop();
	//}
	using namespace PvcsControlObjectTypes;

	DigitalSignal *ptempInfo = (DigitalSignal*)(pvData);


    CPvcsWagoControl::theWagoUnit().SetValue(*ptempInfo, false);
	delete ptempInfo;
}

