
#include "StdAfx.h"
#include ".\pvcscontrolobjectthrottlevalve.h"
#include "pvcsobjectcontroldlg.h"
#include "pvcscontrolobjecttimeoutinfo.h"
#include "pvcswagocontrol.h"
#include <time.h>
#include ".\pvcs v1.0.h"
#include "DxfLayout.h"

//global var
int g_tiIndex = -1;
int g_tiSubIndex = -1;
bool g_tbRegulatorStop = false;

//Reset Thread controlling parameter
void ThrottleThreadReset(int pIndex, int pSubIndex)
{
	CDxfLayout::SetThreadRunningState(pIndex,pSubIndex,false);
	CDxfLayout::SetThreadExitState(pIndex,pSubIndex,false);
	CDxfLayout::SetThreadExitedState(pIndex,pSubIndex,true);
}
//Check and Set value for the Throttle Value
void ThrottleCheckAndSetValue(const PvcsControlObjectTypes::DigitalSignal& param_DigPort, const bool& param_bValue, CString pWagoUnit)
{
	bool bValue = false;	

	//if( CPvcsWagoControl::theWagoUnit().GetValue( param_DigPort, bValue,pWagoUnit ) && bValue != param_bValue )
		CPvcsWagoControl::theWagoUnit().SetValue( param_DigPort, param_bValue );
}

bool ThrottleRegulator(CPvcsControlObjectInfo &param_info,clock_t TimeOut)
{
	long TimeBetweenPulses;
	UINT uiCurrentValue;
	int iCurrentValue;

	clock_t CurrentTime;
	using namespace PvcsControlObjectTypes;

	DigitalSignal DigOp1, DigOp2;
	AnalogSignal AnaIp;

	int iIndex = param_info.GetIndex();
	int iSubIndex = param_info.GetSubIndex();

	try
	{
		DigOp1	= param_info.GetOutputDigitalSignalList().at( 0 );
		DigOp2	= param_info.GetOutputDigitalSignalList().at( 1 );
		AnaIp	= param_info.GetInputAnalogSignalList().at( 0 );
	}
	catch( exception &e )
	{	
		XmlLogError(e.what());
		return false;
	}


	CString strWagoUnitType = param_info.GetWagoUnitType();
	CString strSpinValue = "";
	CDxfLayout::GetValueToBeSet(iIndex,iSubIndex,strSpinValue);
	int iSpinValue = atoi(strSpinValue);
	UINT uiObjMaxStop = param_info.GetObjectMaxStop();
	UINT uiObjMinStop = param_info.GetObjectMinStop();
	CurrentTime = clock();
	TimeBetweenPulses = param_info.GetTimeBetweenPulses();

	while(CurrentTime < TimeOut && CPVCSApp::m_bIsAlive)
	{
		//Check Thread closing signal
		if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
		{
			ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);
			ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
			g_tbRegulatorStop = true;
			return true;
		}

		Sleep(TimeBetweenPulses);
		if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if unable to get value of analog input, just return
		{
			uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject(param_info.GetInputAnalogSignalList().at(0).Value.Limit.MinValue,param_info.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue,uiCurrentValue,param_info.GetName(),strWagoUnitType);

			//if(uiCurrentValue > uiObjMaxStop)
			//	uiCurrentValue = uiObjMaxStop;
			//if(uiCurrentValue < uiObjMinStop)
			//	uiCurrentValue = uiObjMinStop;

			if(param_info.GetInputAnalogSignalList().at(0).Value.IsInverted) 
				iCurrentValue = uiObjMaxStop - uiCurrentValue;
			else
				iCurrentValue = uiCurrentValue;

			if(!((int(iSpinValue) - iCurrentValue) <= 1 && (int(iSpinValue) - iCurrentValue) >= -1))//value not between 1 to -1
			{
				if(iCurrentValue < iSpinValue)//if current value is less then required value, turn on the output 1 or in the case of underrun
				{
					ThrottleCheckAndSetValue(DigOp1,true,strWagoUnitType);
					Sleep(250);
					ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);
				}
				else if(iCurrentValue > iSpinValue)//if current value is more then required value, turn on the output 2 or in the case of overrun
				{
					ThrottleCheckAndSetValue(DigOp2,true,strWagoUnitType);
					Sleep(250);
					ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
				}
			}
			else //if value reach the range of 1 to -1, then break the operation
				break;
		}
		else//if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue))
		{
			return false;
		}

		CurrentTime = clock();
	}

	if(CurrentTime > TimeOut)

		return false;
	else
		return true;


}


// Function name   : CPvcsControlObjectThrottleValve::~CPvcsControlObjectThrottleValve
// Description     : Destructor
// Return type     : 
// Argument        : void

CPvcsControlObjectThrottleValve::~CPvcsControlObjectThrottleValve(void)
{
}


// Function name   : CPvcsControlObjectThrottleValve::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectThrottleValve::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	int nStatus = 0;

	// The status is determined as follows:
	// if Analog Input less or equal to "close" position: Status = 1
	// if Analog Input less or equal to "open" position: Status =  = 2
	// if Analog Input is between "open" or "close" position: Status =  3
	
	if( param_info.GetInputAnalogSignalList().size() > 0 )
	{
		UINT ObjMinStop;
		UINT ObjMaxStop;
		
		ObjMinStop = param_info.GetObjectMinStop();
		ObjMaxStop =param_info.GetObjectMaxStop();

		UINT uiValue = 0; 
		int Value;
		UINT CurrentAnalogInput = 0;
		if (CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputAnalogSignalList().at( 0 ), uiValue,param_info.GetWagoUnitType() ) )
			{
				CurrentAnalogInput = AnalogScaleWagoToObject(param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MaxValue, uiValue,param_info.GetName(),param_info.GetWagoUnitType()) ;
				//For Invert Feedback (5k-----0k)
				if(param_info.GetInputAnalogSignalList().at(0).Value.IsInverted)
				{
					Value = param_info.GetObjectMaxStop() - CurrentAnalogInput;
				}
				else
					Value = CurrentAnalogInput;

				
				if(Value <= (int)ObjMinStop)
					nStatus = 1;
				else if (Value >= (int)ObjMaxStop)
					nStatus = 2;
				else if (Value > (int)ObjMinStop && Value < (int)ObjMaxStop)
					nStatus = 3;
			}	
		else
			return nStatus;
	}
	return nStatus;
		
}

// Function name   : CPvcsControlObjectThrottleValve::GetColor
// Description     : Returns the object color corresponding to the current status
// Return type     : const COLORREF& 
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectThrottleValve::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2)
{
	return param_info.GetStatusColor( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectThrottleValve::GetInText
// Description     : Returns the Intext corresponding to the current status
// Return type     : const CString& 
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectThrottleValve::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return param_info.GetStatusInText( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectThrottleValve::GetValueString
// Description     : Returns the value string to be displayed
// Return type     : CString 
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectThrottleValve::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	CString strValue;
	bool bValue = false;
	UINT uiValue = 0;
	int Value;
	//Value = Analog Input%
	try{
	
		if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputAnalogSignalList().at( 0 ), uiValue,param_info.GetWagoUnitType() ) )
		{
            uiValue = AnalogScaleWagoToObject(param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MaxValue, uiValue,param_info.GetName(),param_info.GetWagoUnitType());
			
			if(param_info.GetInputAnalogSignalList().at(0).Value.IsInverted)
			{
				Value = param_info.GetObjectMaxStop() - uiValue;
			}
			else
				Value = uiValue;
			
			if(Value <= (int)param_info.GetObjectMinStop())
				Value = 0;
			if(Value >= (int)param_info.GetObjectMaxStop())
				Value = 100;

			strValue.Format("%d %%",Value);

		}
	}
	catch( std::out_of_range &e )
	{
		//TRACE("*****CPvcsControlObjectthrottlevalve-getvaluestring*std::out range******");
		XmlLogError( "Probable error: Input signal count is mismatched in config." );
		throw e;
	}
	catch( exception &e)
	{
		//TRACE("*****CPvcsControlObjectthrottlevalve-getvaluestring*******");
		XmlLogError( e.what() );
	}
	return strValue;
}


// Function name   : CPvcsControlObjectThrottleValve::OnButton
// Description     : Not Implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectThrottleValve::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{
	bool bResult = true;

	if( param_bIsPressed && param_info.GetInputAnalogSignalList().size() > 0 && param_info.GetOutputDigitalSignalList().size() > 1 )
	{
		CPvcsControlObjectInfo ObjControlObject;

		ObjControlObject = param_info; 

		int iIndex, iSubIndex;

		iIndex = ObjControlObject.GetIndex();
		iSubIndex = ObjControlObject.GetSubIndex();

		TRACE("\n\n\nButton - wait for Access\n\n\n");

		//wait for access
		while(CDxfLayout::GetThreadBusyState(iIndex,iSubIndex))
			Sleep(0);

		//get Access
		CDxfLayout::SetThreadBusyState(iIndex,iSubIndex,true);
		TRACE("\n\n\nButton - Get Access\n\n\n");

		//Check that thread runnning or not
		if(CDxfLayout::GetThreadRunningState(iIndex,iSubIndex))
		{
			TRACE("\n\n\nButton - wait for thread to end\n\n\n");
			CDxfLayout::SetThreadExitState(iIndex,iSubIndex,true);
			while(!CDxfLayout::GetThreadExitedState(iIndex,iSubIndex))
				Sleep(0);//wait for thread to end
		}

		CString strButtonCaption = ObjControlObject.GetButtonCaption(param_nButton);
		UINT uiValue = atoi(strButtonCaption);
		strButtonCaption.Format("%d",uiValue);
		CDxfLayout::SetValueToBeSet(iIndex, iSubIndex,strButtonCaption);

		while(g_tiIndex != -1 && g_tiSubIndex != -1)
			Sleep(0);

		g_tiIndex = iIndex;
		g_tiSubIndex = iSubIndex;

		TRACE("\n\n\nButton - wait for thread over\n\n\n");
		//Reset parameter for new thread
		CDxfLayout::SetThreadRunningState(iIndex,iSubIndex,true);
		CDxfLayout::SetThreadExitState(iIndex,iSubIndex,false);
		CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,false);


		//Create Thread
		CWinThread *pThread = AfxBeginThread(SetThrottleButtonThread,NULL);
		TRACE("\n\n\nButton - new thread start = %x\n\n\n",pThread->m_nThreadID);

	} //if( param_bIsPressed && param_info.GetInputAnalogSignalList().size() > 0 && param_info.GetOutputDigitalSignalList().size() > 1 )
	else
	{
		TRACE("\n\n\nButton - UP event\n\n\n");
	}
	return bResult;
}


// Function name   : CPvcsControlObjectThrottleValve::OnSetSpin
// Description     : Outputs control signals according to the spin box status
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectThrottleValve::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
  	bool bResult = true;

	if( param_info.GetInputAnalogSignalList().size() > 0 && param_info.GetOutputDigitalSignalList().size() > 1 )
	{
		CPvcsControlObjectInfo ObjControlObject;

		ObjControlObject = param_info; 

		int iIndex, iSubIndex;

		iIndex = ObjControlObject.GetIndex();
		iSubIndex = ObjControlObject.GetSubIndex();

		//wait for access
		while(CDxfLayout::GetThreadBusyState(iIndex,iSubIndex))
			Sleep(0);

		//Get Access
		CDxfLayout::SetThreadBusyState(iIndex,iSubIndex,true);

		//Check that thread running or not
		if(CDxfLayout::GetThreadRunningState(iIndex,iSubIndex))
		{
			CDxfLayout::SetThreadExitState(iIndex,iSubIndex,true);
			while(!CDxfLayout::GetThreadExitedState(iIndex,iSubIndex))
				Sleep(0); //wait for thread to end
		}

		CString strTempValuetobeSet = "";

		strTempValuetobeSet.Format("%d",param_uiValue);
		CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,strTempValuetobeSet);

		while(g_tiIndex != -1 && g_tiSubIndex != -1)
			Sleep(0);

		g_tiIndex = iIndex;
		g_tiSubIndex = iSubIndex;

		//Reset thread controlling parameter
		CDxfLayout::SetThreadRunningState(iIndex,iSubIndex,true);
		CDxfLayout::SetThreadExitState(iIndex,iSubIndex,false);
		CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,false);

		//Create thread
		CWinThread *pThread = AfxBeginThread(SetThrottleValueThread,NULL);


	}

	return bResult;
}


// Function name   : CPvcsControlObjectThrottleValve::GetSpinInitInfo
// Description     : Initializes the spinbox with the current status of the objects
// Return type     : void 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strInitValue

void CPvcsControlObjectThrottleValve::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strInitValue)
{
	try{
		param_uiMinValue = param_info.GetInputAnalogSignalList().at(0).Value.Limit.MinValue;
		param_uiMaxValue = param_info.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue;
		param_uiStep	 = param_info.GetInputAnalogSignalList().at(0).Value.Step;

		CString strValue;
		bool bValue = false;
		UINT uiValue = 0;
		int Value;

		if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputAnalogSignalList().at( 0 ), uiValue,param_info.GetWagoUnitType() ) )
		{
			uiValue = AnalogScaleWagoToObject(param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MaxValue, uiValue,param_info.GetName(),param_info.GetWagoUnitType());
			
            if(param_info.GetInputAnalogSignalList().at(0).Value.IsInverted)
			{
				Value = param_info.GetObjectMaxStop() - uiValue;
			}
			else
				Value = uiValue;

			
			if(Value <= (int)param_info.GetObjectMinStop())
				Value = 0;
			if(Value >= (int)param_info.GetObjectMaxStop())
				Value = 100;
			
			strValue.Format("%d", Value);
		}
		param_strInitValue = strValue;
	
	}
	catch( std::out_of_range &e )
	{
		//TRACE("*****CPvcsControlObjectthrottlevalve-getspininitinfo*std::out range******");
		XmlLogError( "Probable error: Analog Input count is less than Spin box count." );
		throw e;
	}
	catch( exception &e )
	{
		//TRACE("*****CPvcsControlObjectthrottlevalve-getspininitinfo*std::out range******");
		XmlLogError( e.what() );
	}
}

//Thread start when Button is used
UINT SetThrottleButtonThread(LPVOID pParam)
{
	int iIndex, iSubIndex;

	iIndex = g_tiIndex;
	iSubIndex = g_tiSubIndex;

	CPvcsControlObjectInfo ObjControlObject;

	CDxfLayout::GetControlObject(iIndex,iSubIndex,ObjControlObject);

	g_tiIndex = -1;
	g_tiSubIndex = -1;
	
	//Release access
	CDxfLayout::SetThreadBusyState(iIndex,iSubIndex,false);
	TRACE("\n\n\nButton - Access release\n\n\n");

	CString strWagoUnitType;
	CString strObjectName;
	UINT uiMinValue, uiMaxValue;
	UINT uiObjMaxStop, uiObjMinStop;
	CString strButtonCaption = "";
	UINT uiCurrentValue;
	int iCurrentValue;



	strWagoUnitType = ObjControlObject.GetWagoUnitType();
	strObjectName = ObjControlObject.GetName();
	uiMinValue = ObjControlObject.GetInputAnalogSignalList().at(0).Value.Limit.MinValue;
	uiMaxValue = ObjControlObject.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue;
	uiObjMaxStop = ObjControlObject.GetObjectMaxStop();
	uiObjMinStop = ObjControlObject.GetObjectMinStop();



	clock_t CurrentTime;

	clock_t TimeoutTime = clock() + ((ObjControlObject.GetTimeOut()/ 1000) * CLOCKS_PER_SEC);

	using namespace PvcsControlObjectTypes;

	DigitalSignal DigOp1, DigOp2;
	AnalogSignal AnaIp;

	TRACE("\n\n\nThrottle Button - Thread Started\n\n\n"); 

	try
	{
		DigOp1	= ObjControlObject.GetOutputDigitalSignalList().at( 0 );
		DigOp2	= ObjControlObject.GetOutputDigitalSignalList().at( 1 );
		AnaIp	= ObjControlObject.GetInputAnalogSignalList().at( 0 );
	}
	catch( exception &e )
	{	
		//TRACE("*****CPvcsControlObjectthrottlevalvebackgroundcontrollerinfo-updatevalue*std::out range******");
		XmlLogError( e.what() );

		CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");


		//Reset Thread parameter
		ThrottleThreadReset(iIndex,iSubIndex);
		TRACE("\n\n\nThrottle Button - catch exit\n\n\n");
		//TRACE("\n\n====1========Thread exit by normal proram==Value to be set =%d\n\n",pObjControlObject->GetSpinValue());
		return 0;
	}

	CDxfLayout::SetControlOperationState(iIndex,iSubIndex,false);

	CString strSpinValue;

	CDxfLayout::GetValueToBeSet(iIndex,iSubIndex,strSpinValue);

	if(atoi(strSpinValue) == 100)//If 100% button clicked
	{
		//Get current value
		if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if able to get value of analog input
		{
			uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
			//if(uiCurrentValue > uiObjMaxStop)
			//	uiCurrentValue = uiObjMaxStop;
			//if(uiCurrentValue < uiObjMinStop)
			//	uiCurrentValue = uiObjMinStop;
			if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted) 
				iCurrentValue = uiObjMaxStop - uiCurrentValue;
			else
				iCurrentValue = uiCurrentValue;
		}
		else//if unable to get current value then so Time out
		{
			TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
			if( it != theTimeOutInfo().end() )
				((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
			CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");


			//Reset Thread parameter
			ThrottleThreadReset(iIndex,iSubIndex);
			CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
			TRACE("\n\n\nThrottle Button - 100 - Exit Normal - 1\n\n\n");
			return 0;
		}

		if(iCurrentValue >= int(uiObjMaxStop))
		{
			ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);
			TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
			if( it != theTimeOutInfo().end() )
				((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);
			CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

			//Reset Thread parameter
			ThrottleThreadReset(iIndex,iSubIndex);
			CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
			TRACE("\n\n\nThrottle Button - 0 - Exit equal- 1\n\n\n");
			return 0;
		}

		CurrentTime = clock();

		bool bIsOutputSet = false;

		while(CPVCSApp::m_bIsAlive) //for 100%
		{
			//Check for thread closing signal
			if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
			{
				ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);
				CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

				CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
				CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
				TRACE("\n\n\nThrottle Button - 100 - Exit Force - 1\n\n\n");
				return 0;
			}

			//if timeout occurred and value still lower than 100% or uiObjMaxStop
			if(CurrentTime > TimeoutTime && iCurrentValue < int(uiObjMaxStop))
			{
				ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);
				TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
				if( it != theTimeOutInfo().end() ){
					((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
					string tStr = "WARNING\n"+strObjectName+" TimeOut";
					AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);

                }
				CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

				//Reset Thread parameter
				ThrottleThreadReset(iIndex,iSubIndex);
				CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
				TRACE("\n\n\nThrottle Button - 100 - Exit Normal - 2\n\n\n");
				return 0;
			}

			//Set digital output to true to open Valve 100% or uiObjMaxStop
			if(iCurrentValue < int(uiObjMaxStop))
			{
				if(!bIsOutputSet) //set output true once
				{
					ThrottleCheckAndSetValue(DigOp1,true,strWagoUnitType);
					bIsOutputSet = true;
				}
			}
			else //keep the output for another 10 seconds for external calibration support
			{

				for(int i =1; i<= 10; i++)
				{
					//Check for thread closing signal
					if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
					{
						ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);
						CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");
						CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
						CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
						TRACE("\n\n\nThrottle Button - 100 - Exit force - 2\n\n\n");
						return 0;
					}
					else
						Sleep(1000);
				}

				ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);
				TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
				if( it != theTimeOutInfo().end() )
					((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);
				CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,""); 

				//Reset Thread parameter
				ThrottleThreadReset(iIndex,iSubIndex);
				CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
				TRACE("\n\n\nThrottle Button - 100 - Exit Normal - 3\n\n\n");
				return 0;
			}

			//Get new current value
			if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))
			{
				uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
				//if(uiCurrentValue > uiObjMaxStop)
				//	uiCurrentValue = uiObjMaxStop;
				//if(uiCurrentValue < uiObjMinStop)
				//	uiCurrentValue = uiObjMinStop;
				if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted) 
					iCurrentValue = uiObjMaxStop - uiCurrentValue;	
				else
					iCurrentValue = uiCurrentValue;
			}

			//Get new current time
			CurrentTime = clock() - 100;//100ms for sleep
			Sleep(100);

		}//while(CPVCSApp::m_bIsAlive) end
	}//for 100% end
	else if(atoi(strSpinValue) == 0)//If 0% button clicked
	{
		if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if able to get value of analog input
		{
			uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);	
			//if(uiCurrentValue > uiObjMaxStop)
			//	uiCurrentValue = uiObjMaxStop;
			//if(uiCurrentValue < uiObjMinStop)
			//	uiCurrentValue = uiObjMinStop;
			if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted) 
				iCurrentValue = uiObjMaxStop - uiCurrentValue;
			else
				iCurrentValue = uiCurrentValue; 
		}
		else
		{
			TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
			if( it != theTimeOutInfo().end() )
				((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
			CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

			//Reset Thread parameter
			ThrottleThreadReset(iIndex,iSubIndex);
			CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
			TRACE("\n\n\nThrottle Button  - 0 - Exit Normal - 1\n\n\n");
			return 0;
		}

		if(iCurrentValue <= int(uiObjMinStop))
		{
			ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
			TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
			if( it != theTimeOutInfo().end() )
				((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);
			CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

			//Reset Thread parameter
			ThrottleThreadReset(iIndex,iSubIndex);
			CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
			TRACE("\n\n\nThrottle Button - 0 - Exit equal- 2\n\n\n");
			return 0;
		}

		CurrentTime = clock();

		bool bIsOutputSet = false;

		while(CPVCSApp::m_bIsAlive) //for 0%
		{

			//Check for thread closing signal
			if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
			{
				ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
				CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");
				CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
				CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
				TRACE("\n\n\nThrottle Button - 0 - Exit force - 1\n\n\n");
				return 0;
			}

			//if timeout occurred and value still greater than 0%
			if(CurrentTime > TimeoutTime && iCurrentValue > int(uiObjMinStop))
			{
				ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
				TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
				if( it != theTimeOutInfo().end() ){
					((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
					string tStr = "WARNING\n"+strObjectName+" TimeOut";
					AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);
                }
				CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

				//Reset Thread parameter
				ThrottleThreadReset(iIndex,iSubIndex);
				CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
				TRACE("\n\n\nThrottle Button - 0 - Exit Normal - 2\n\n\n");
				return 0;
			}

			//Set digital output to true to close Valve (0%)
			if(iCurrentValue > int(uiObjMinStop))
			{
				if(!bIsOutputSet) //set output true once
				{
					ThrottleCheckAndSetValue(DigOp2,true,strWagoUnitType);
					bIsOutputSet = true;
				}
			}
			else //keep the output for another 10 seconds for external calibration support
			{

				for(int i =1; i<= 10; i++)
				{
					//Check for thread closing signal
					if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
					{
						ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
						CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");
						CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
						CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
						TRACE("\n\n\nThrottle Button - 0 - Exit force - 2\n\n\n");
						return 0;
					}
					else
						Sleep(1000);
				}

				ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
				TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
				if( it != theTimeOutInfo().end() )
					((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);
				CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

				//Reset Thread parameter
				ThrottleThreadReset(iIndex,iSubIndex);
				CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
				TRACE("\n\n\nThrottle Button - 0 - Exit Normal - 3\n\n\n");
				return 0;
			}

			//Get new current value
			if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))
			{
				uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
				//if(uiCurrentValue > uiObjMaxStop)
				//	uiCurrentValue = uiObjMaxStop;
				//if(uiCurrentValue < uiObjMinStop)
				//	uiCurrentValue = uiObjMinStop;
				if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted) 
					iCurrentValue = uiObjMaxStop - uiCurrentValue;
				else
					iCurrentValue = uiCurrentValue;
			}

			//Get new current time
			CurrentTime = clock() - 100;//100ms for sleep
			Sleep(100);

		}//while(1) end
	}//for 0% end
	else
	{
		CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

		//Reset Thread parameter
		ThrottleThreadReset(iIndex,iSubIndex);
		CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
		TRACE("\n\n\nThrottle Button - Nothing - Exit Normal - 4\n\n\n");
		return 0;
	}

}


//Thread start when Spin ctrl is used
UINT SetThrottleValueThread(LPVOID pParam)
{
	int iIndex, iSubIndex;

	iIndex = g_tiIndex;
	iSubIndex = g_tiSubIndex;

	CPvcsControlObjectInfo ObjControlObject;

	CDxfLayout::GetControlObject(iIndex,iSubIndex,ObjControlObject);

	g_tiIndex = -1;
	g_tiSubIndex = -1;
	g_tbRegulatorStop = false;

	//Release access
	CDxfLayout::SetThreadBusyState(iIndex,iSubIndex,false);

	UINT uiCurrentValue;
	int iCurrentValue;
	DigitalSignal DigOp1, DigOp2;
	AnalogSignal AnaIp;
	clock_t CurrentTime;
	clock_t TimeoutTime;
	CString strWagoUnitType = "";
	CString strObjectName = "";
	UINT uiMinValue, uiMaxValue;
	UINT uiObjMaxStop,uiObjMinStop;

	using namespace PvcsControlObjectTypes;

	try 
	{

		TimeoutTime = clock() + ((ObjControlObject.GetTimeOut() / 1000) * CLOCKS_PER_SEC);

		strWagoUnitType = ObjControlObject.GetWagoUnitType();
		strObjectName = ObjControlObject.GetName();
		uiMinValue = ObjControlObject.GetInputAnalogSignalList().at(0).Value.Limit.MinValue;
		uiMaxValue = ObjControlObject.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue;
		uiObjMaxStop = ObjControlObject.GetObjectMaxStop();
		uiObjMinStop = ObjControlObject.GetObjectMinStop();

		DigOp1	= ObjControlObject.GetOutputDigitalSignalList().at( 0 );
		DigOp2	= ObjControlObject.GetOutputDigitalSignalList().at( 1 );
		AnaIp	= ObjControlObject.GetInputAnalogSignalList().at( 0 );
	}
	catch( exception &e )
	{	
		//TRACE("*****CPvcsControlObjectthrottlevalvebackgroundcontrollerinfo-updatevalue*std::out range******");
		XmlLogError( e.what() );

		CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

		//Reset Thread parameter
		ThrottleThreadReset(iIndex,iSubIndex);
		//TRACE("\n\n====1========Thread exit by normal proram==Value to be set =%d\n\n",pObjControlObject->GetSpinValue());
		return 0;
	}


	if (CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType) )
	{
		uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
		//if(uiCurrentValue > uiObjMaxStop)
		//	uiCurrentValue = uiObjMaxStop;
		//if(uiCurrentValue < uiObjMinStop)
		//	uiCurrentValue = uiObjMinStop;
		if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted) 
			iCurrentValue = uiObjMaxStop - uiCurrentValue;
		else
			iCurrentValue = uiCurrentValue;

		int PercentageToStop = ObjControlObject.GetPercentagetoStop();

		CString strSpinValue = "";
		CDxfLayout::GetValueToBeSet(iIndex,iSubIndex,strSpinValue);

		int iSpinvalue = atoi(strSpinValue);

		int DiffInValue = iCurrentValue - int(iSpinvalue);

		if(DiffInValue < 0)
			DiffInValue = -(DiffInValue);

		if(DiffInValue > PercentageToStop)//this is the case where difference in Percentage to set is higher than Percentage to stop, then do regulatory work
		{
			int NewValueToBeSet;

			if(iSpinvalue > iCurrentValue)//set digital output 1 to true
			{
				NewValueToBeSet = iSpinvalue - PercentageToStop;

				if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if unable to get value of analog input, just return
				{
					uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
					//if(uiCurrentValue > uiObjMaxStop)
					//	uiCurrentValue = uiObjMaxStop;
					//if(uiCurrentValue < uiObjMinStop)
					//	uiCurrentValue = uiObjMinStop;
					if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted) 
						iCurrentValue = uiObjMaxStop - uiCurrentValue;
					else
						iCurrentValue = uiCurrentValue;
				}
				else//Set time out true
				{
					TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
					if( it != theTimeOutInfo().end() )
						((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
					CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

					//Reset Thread parameter
					ThrottleThreadReset(iIndex,iSubIndex);

					//TRACE("\n\n===12=========Thread exit by normal proram==Value to be set =%d\n\n",pObjControlObject->GetSpinValue());
					return 0;
				}

				CurrentTime = clock();

				bool bIsOutputSet = false;

				while(CPVCSApp::m_bIsAlive) //for New Value to be set
				{
					//Check for Thread closing signal
					if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
					{
						ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);
						CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");
						CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
						return 0;
					}

					//if timeout occurred and value still lower than NewValueToBeSet%
					if(CurrentTime > TimeoutTime && iCurrentValue < NewValueToBeSet)
					{
						ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);
						TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
						if( it != theTimeOutInfo().end() ){
							((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
                            string tStr = "WARNING\n"+strObjectName+" TimeOut";
                            AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);
                        }
						CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

						//Reset Thread parameter
						ThrottleThreadReset(iIndex,iSubIndex);
						return 0;
					}

					//Set digital output to true to open Valve to NewValueToBeSet%
					if(iCurrentValue < NewValueToBeSet)
					{
						if(!bIsOutputSet) //set output true once
						{
							ThrottleCheckAndSetValue(DigOp1,true,strWagoUnitType);
							bIsOutputSet = true;
						}
					}
					else //Now do the Regulation work
					{
						ThrottleCheckAndSetValue(DigOp1,false,strWagoUnitType);

						for(int CallCounter = 1; CallCounter<=3 && !g_tbRegulatorStop; CallCounter++)
						{

							//Call regulator function
							if(ThrottleRegulator(ObjControlObject,TimeoutTime))
							{
								//Operation done within Timelimit, so no timeout
								TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
								if( it != theTimeOutInfo().end() )
									((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);
							}
							else
							{
								//Operation not done within Timelimit, so timeout
								TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
								if( it != theTimeOutInfo().end() ){
									((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(true);
                                    string tStr = "WARNING\n"+strObjectName+" TimeOut";
                                    AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);
                                }
							}
							Sleep(1000);
						}
						CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

						//Reset Thread parameter
						ThrottleThreadReset(iIndex,iSubIndex);
						return 0;
					}

					//Get new current value
					if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))
					{
						uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
						//if(uiCurrentValue > uiObjMaxStop)
						//	uiCurrentValue = uiObjMaxStop;
						//if(uiCurrentValue < uiObjMinStop)
						//	uiCurrentValue = uiObjMinStop;
						if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted) 
							iCurrentValue = uiObjMaxStop - uiCurrentValue;
						else
							iCurrentValue = uiCurrentValue;
					}

					//Get new current time
					CurrentTime = clock() - 100;//100ms for sleep
					Sleep(100);

				}//while(CPVCSApp::m_bIsAlive) end
			}//if set digital output 1 is true end
			else if(iSpinvalue  < iCurrentValue)//set digital output 2 is true
			{
				NewValueToBeSet = iSpinvalue + PercentageToStop;

				if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if unable to get value of analog input, just return
				{
					uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
					//if(uiCurrentValue > uiObjMaxStop)
					//	uiCurrentValue = uiObjMaxStop;
					//if(uiCurrentValue < uiObjMinStop)
					//	uiCurrentValue = uiObjMinStop;
					if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted) 
						iCurrentValue = uiObjMaxStop - uiCurrentValue;
					else
						iCurrentValue = uiCurrentValue;
				}
				else//Set time out true
				{
					TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
					if( it != theTimeOutInfo().end() )
						((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
					CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

					//Reset Thread parameter
					ThrottleThreadReset(iIndex,iSubIndex);
					//TRACE("\n\n====16========Thread exit by normal proram==Value to be set =%d\n\n",pObjControlObject->GetSpinValue());
					return 0;
				}

				CurrentTime = clock();

				bool bIsOutputSet = false;

				while(CPVCSApp::m_bIsAlive) //for NewValueToBeSet%
				{
					//Check for Thread closing signal
					if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
					{
						ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
						CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");
						CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
						return 0;
					}


					//if timeout occurred and value still greater than NewValueToBeSet%
					if(CurrentTime > TimeoutTime && iCurrentValue > NewValueToBeSet)
					{
						ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
						TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
						if( it != theTimeOutInfo().end() ){
							((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
                            string tStr = "WARNING\n"+strObjectName+" TimeOut";
                            AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);
                        }
						CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

						//Reset Thread parameter
						ThrottleThreadReset(iIndex,iSubIndex);
						return 0;
					}

					//Set digital output to true to close Valve (NewValueToBeSet%)
					if(iCurrentValue > NewValueToBeSet)
					{
						if(!bIsOutputSet) //set output true once
						{
							ThrottleCheckAndSetValue(DigOp2,true,strWagoUnitType);
							bIsOutputSet = true;
						}
					}
					else //Now do the Regulation work
					{
						ThrottleCheckAndSetValue(DigOp2,false,strWagoUnitType);
						for(int CallCounter = 1; CallCounter<=3 && !g_tbRegulatorStop; CallCounter++)
						{
							//Call regulator function
							if(ThrottleRegulator(ObjControlObject,TimeoutTime))
							{
								//Operation done within Timelimit, so no timeout
								TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
								if( it != theTimeOutInfo().end() )
									((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);

							}
							else
							{
								//Operation not done within Timelimit, so timeout
								TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
								if( it != theTimeOutInfo().end() ){
									((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(true);
                                    string tStr = "WARNING\n"+strObjectName+" TimeOut";
                                    AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);
                                }
							}
							Sleep(1000);
						}

						CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

						//Reset Thread parameter
						ThrottleThreadReset(iIndex,iSubIndex);
						return 0;
					}

					//Get new current value
					if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))
					{
						uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
						//if(uiCurrentValue > uiObjMaxStop)
						//	uiCurrentValue = uiObjMaxStop;
						//if(uiCurrentValue < uiObjMinStop)
						//	uiCurrentValue = uiObjMinStop;
						if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted) 
							iCurrentValue = uiObjMaxStop - uiCurrentValue;
						else
							iCurrentValue = uiCurrentValue;
					}

					//Get new current time
					CurrentTime = clock() - 100;//100ms for sleep
					Sleep(100);

				}//while(1) end
			}//if set digital output 2 is true end
		}//if(DiffInValue > PercentageToStop) end
		else //this is the case where Percentage to set is lower than Percentage to stop, then do pulsing
		{
			//Call regulator
			for(int CallCounter = 1; CallCounter<=3 && !g_tbRegulatorStop; CallCounter++)
			{
				if(ThrottleRegulator(ObjControlObject,TimeoutTime))
				{
					TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
					if( it != theTimeOutInfo().end() ){
						CPvcsControlObjectTimeOutInfo CPvcsControlObjectTimeOutInfoPtr = *it;
						CPvcsControlObjectTimeOutInfoPtr.SetTimeOut(false);
					}

				}
				else
				{
					TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
					if( it != theTimeOutInfo().end() )
						((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(true);
				}
				Sleep(1000);
			}
			CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

			//Reset Thread parameter
			ThrottleThreadReset(iIndex,iSubIndex);
			//TRACE("\n\n====21========Thread exit by normal proram==Value to be set =%d\n\n",pObjControlObject->GetSpinValue());
			return 0;
		}
	}
	else
	{
		TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
		if( it != theTimeOutInfo().end() )
			((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(true);
		CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

		//Reset Thread parameter
		ThrottleThreadReset(iIndex,iSubIndex);

		//TRACE("\n\n====22========Thread exit by normal proram==Value to be set =%d\n\n",pObjControlObject->GetSpinValue());
		return 0;
	}



	//TRACE("\n\n=====23=======Thread exit by normal proram==Value to be set =%d\n\n",pObjControlObject->GetSpinValue());
	return 0;
}

