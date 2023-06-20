#include "StdAfx.h"
#include ".\pvcscontrolobjectcargovalve.h"
#include "pvcsobjectcontroldlg.h"
#include "pvcscontrolobjecttimeoutinfo.h"
#include "pvcswagocontrol.h"
#include <time.h>
#include ".\pvcs v1.0.h"
#include "DxfLayout.h"

//global var
int g_ciIndex = -1;
int g_ciSubIndex = -1;
bool g_cbRegulatorStop = false;

//Reset Thread controlling parameter
void CPvcsControlObjectCargoValve::CargoThreadReset(int pIndex, int pSubIndex)
{
    CDxfLayout::SetThreadRunningState(pIndex,pSubIndex,false);
    CDxfLayout::SetThreadExitState(pIndex,pSubIndex,false);
    CDxfLayout::SetThreadExitedState(pIndex,pSubIndex,true);
}
//Check and Set value for the Cargo Value
void CPvcsControlObjectCargoValve::CargoCheckAndSetValue(const DigitalSignal& param_DigPort,const bool param_bValue, CString pWagoUnit)
{
    //bool bValue = false;  

    //if( CPvcsWagoControl::theWagoUnit().GetValue( param_DigPort, bValue,pWagoUnit ) && bValue != param_bValue )
        CPvcsWagoControl::theWagoUnit().SetValue( param_DigPort, param_bValue );
}

bool CPvcsControlObjectCargoValve::CargoRegulator(CPvcsControlObjectInfo& param_info,clock_t TimeOut)
{
    UINT  uiCurrentValue;

    clock_t CurrentTime;
    using namespace PvcsControlObjectTypes;

    DigitalSignal DigOp1, DigOp2;
    DigitalSignal DigIp1, DigIp2;
    AnalogSignal AnaIp;
    bool bDigI1 = false;
    bool bDigI2 = false;

    int iIndex = param_info.GetIndex();
    int iSubIndex = param_info.GetSubIndex();

    try{
        DigOp1  = param_info.GetOutputDigitalSignalList().at( 0 );
        DigOp2  = param_info.GetOutputDigitalSignalList().at( 1 );
        DigIp1  = param_info.GetInputDigitalSignalList().at( 0 );
        DigIp2  = param_info.GetInputDigitalSignalList().at( 1 );
        AnaIp   = param_info.GetInputAnalogSignalList().at( 0 );
    }
    catch( exception &e )
    {
        //TRACE("*****CPvcsControlObjectCargoValveBackgroundControllerInfo-updatevalue*******");
        XmlLogError( e.what() );
        return false;
    }

    CString strWagoUnitType = param_info.GetWagoUnitType();

    CString strSpinValue = "";
    CDxfLayout::GetValueToBeSet(iIndex,iSubIndex,strSpinValue);
    int iSpinValue = atoi(strSpinValue);

    CurrentTime = clock();
    long TimeBetweenPulses = param_info.GetTimeBetweenPulses();
    int MinValue           = int(param_info.GetInputAnalogSignalList().at(0).Value.Limit.MinValue);
    int MaxValue           = int(param_info.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue);
    CString  ObjName       = param_info.GetName();
    while(CurrentTime < TimeOut && CPVCSApp::m_bIsAlive )
    {
        //Check Thread closing signal
        if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
        {
            CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
            CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
            g_cbRegulatorStop = true;
            return false;
        }

        Sleep(TimeBetweenPulses);
        if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if unable to get value of analog input, just return
        {
            int CurrentValue = int(CPvcsControlObject::AnalogScaleWagoToObject(MinValue,MaxValue,uiCurrentValue,ObjName,strWagoUnitType));

            //get digital input 1 and 2
            CPvcsWagoControl::theWagoUnit().GetValue(DigIp1,bDigI1,strWagoUnitType);
            CPvcsWagoControl::theWagoUnit().GetValue(DigIp2,bDigI2,strWagoUnitType);
            if ( iSpinValue == MaxValue ){
                if ( !bDigI1 ){ 
                    CargoCheckAndSetValue(DigOp1,true,strWagoUnitType);
                    Sleep(250);
                    CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
                }
            }else if (iSpinValue == MinValue ){
                if ( !bDigI2 ){ 
                    CargoCheckAndSetValue(DigOp2,true,strWagoUnitType);
                    Sleep(250);
                    CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
                }
            }else if ( abs(iSpinValue - CurrentValue) > 1 )
            {
            //if(!((int(iSpinValue) - int(uiCurrentValue)) <= 1 && (int(iSpinValue) - int(uiCurrentValue)) >= -1))//value not between 1 to -1
                if(CurrentValue < iSpinValue && bDigI1 == false)//if current value is less then required value, turn on the output 1 or in the case of underrun and digital input 2 is false
                {
                    CargoCheckAndSetValue(DigOp1,true,strWagoUnitType);
                    Sleep(250);
                    CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
                }
                else if(CurrentValue > iSpinValue && bDigI2 == false)//if current value is more then required value, turn on the output 2 or in the case of overrunand digital input 1 is false
                {
                    CargoCheckAndSetValue(DigOp2,true,strWagoUnitType);
                    Sleep(250);
                    CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
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


// Function name   : CPvcsControlObjectCargoValve::~CPvcsControlObjectCargoValve
// Description     : Destructor
// Return type     : 
// Argument        : void

CPvcsControlObjectCargoValve::~CPvcsControlObjectCargoValve(void)
{
}


// Function name   : CPvcsControlObjectCargoValve::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectCargoValve::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
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


// Function name   : CPvcsControlObjectCargoValve::GetColor
// Description     : Returns the object color corresponding to the current status
// Return type     : const COLORREF& 
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectCargoValve::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2)
{
    return param_info.GetStatusColor( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectCargoValve::GetInText
// Description     : Returns the Intext corresponding to the current status
// Return type     : const CString& 
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectCargoValve::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
    return param_info.GetStatusInText( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectCargoValve::GetValueString
// Description     : Returns the value string to be displayed
// Return type     : CString 
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectCargoValve::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
    CString strValue;
    bool bValue = false;
    UINT uiValue = 0;

    // The value string is determined as follows:
    // Digital input 1 true: Value = Max%
    // Digital input 2 true: Value = Min%
    // Default: Value = Analog Input%
    try{
        if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue,param_info.GetWagoUnitType() ) && bValue)
            strValue.Format("%d %%", param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MaxValue );
        else if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 1 ), bValue,param_info.GetWagoUnitType() ) && bValue)
            strValue.Format("%d %%", param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MinValue );
        else if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputAnalogSignalList().at( 0 ), uiValue,param_info.GetWagoUnitType() ) )
            strValue.Format("%d %%", AnalogScaleWagoToObject(param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MaxValue, uiValue,param_info.GetName(),param_info.GetWagoUnitType()) );
    }
    catch( std::out_of_range &e )
    {
        //TRACE("*******pvcscontrolobjectcargovale-getvaluestring* error - std::out range****");
        XmlLogError( "Probable error: Input signal count is mismatched in config." );
        throw e;
    }
    catch( exception &e)
    {
        //TRACE("*******pvcscontrolobjectcargovale-getvaluestring*****");
        XmlLogError( e.what() );
    }
    return strValue;
}


// Function name   : CPvcsControlObjectCargoValve::OnButton
// Description     : Not Implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectCargoValve::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{
    bool bResult = true;

    if(  param_bIsPressed && param_info.GetInputAnalogSignalList().size() > 0 && param_info.GetInputDigitalSignalList().size() > 1 && param_info.GetOutputDigitalSignalList().size() > 1 )
    {
        CPvcsControlObjectInfo ObjControlObject;

        ObjControlObject = param_info; 

        int iIndex = ObjControlObject.GetIndex();
        int iSubIndex = ObjControlObject.GetSubIndex();

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

        while(g_ciIndex != -1 && g_ciSubIndex != -1)
            Sleep(0);

        g_ciIndex = iIndex;
        g_ciSubIndex = iSubIndex;

        TRACE("\n\n\nButton - wait for thread over\n\n\n");
        //Reset parameter for new thread
        CDxfLayout::SetThreadRunningState(iIndex,iSubIndex,true);
        CDxfLayout::SetThreadExitState(iIndex,iSubIndex,false);
        CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,false);


        //Create Thread
        CWinThread *pThread = AfxBeginThread(SetCargoButtonThread,NULL);
        TRACE("\n\n\nButton - new thread start = %x\n\n\n",pThread->m_nThreadID);

    } //if( param_bIsPressed && param_info.GetInputAnalogSignalList().size() > 0 && param_info.GetOutputDigitalSignalList().size() > 1 )
    else
    {
        TRACE("\n\n\nButton - UP event\n\n\n");
    }
    return bResult;
    
}


// Function name   : CPvcsControlObjectCargoValve::OnSetSpin
// Description     : Outputs control signals according to the spin box status
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectCargoValve::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
    bool bResult = true;

    if( param_info.GetInputAnalogSignalList().size() > 0 && param_info.GetInputDigitalSignalList().size() > 1 && param_info.GetOutputDigitalSignalList().size() > 1 )
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

        while(g_ciIndex != -1 && g_ciSubIndex != -1)
            Sleep(0);

        g_ciIndex = iIndex;
        g_ciSubIndex = iSubIndex;

        //Reset thread controlling parameter
        CDxfLayout::SetThreadRunningState(iIndex,iSubIndex,true);
        CDxfLayout::SetThreadExitState(iIndex,iSubIndex,false);
        CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,false);

        //Create thread
        CWinThread *pThread = AfxBeginThread(SetCargoValueThread,NULL);
    }

    return bResult;
}


// Function name   : CPvcsControlObjectCargoValve::GetSpinInitInfo
// Description     : Initializes the spinbox with the current status of the objects
// Return type     : void 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strInitValue

void CPvcsControlObjectCargoValve::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strInitValue)
{
    try{
        param_uiMinValue = param_info.GetInputAnalogSignalList().at(0).Value.Limit.MinValue;
        param_uiMaxValue = param_info.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue;
        param_uiStep     = param_info.GetInputAnalogSignalList().at(0).Value.Step;

        CString strValue;
        bool bValue = false;
        UINT uiValue = 0;

        if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue,param_info.GetWagoUnitType() ) && bValue)
            strValue.Format("%d", param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MaxValue );
        else if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 1 ), bValue ,param_info.GetWagoUnitType()) && bValue)
            strValue.Format("%d", param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MinValue );
        else if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputAnalogSignalList().at( 0 ), uiValue ,param_info.GetWagoUnitType()) )
            strValue.Format("%d", AnalogScaleWagoToObject(param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MaxValue, uiValue,param_info.GetName(),param_info.GetWagoUnitType()) );

        param_strInitValue = strValue;
    
    }
    catch( std::out_of_range &e )
    {
        //TRACE("*******pvcscontrolobjectcargovale-getspin init info - std::out of range*****");
        XmlLogError( "Probable error: Analog Input count is less than Spin box count." );
        throw e;
    }
    catch( exception &e )
    {
        //TRACE("*******pvcscontrolobjectcargovale-getspin init info*****");
        XmlLogError( e.what() );
    }
}

//Thread start when button is used
UINT CPvcsControlObjectCargoValve::SetCargoButtonThread(LPVOID pParam)
{
    int iIndex, iSubIndex;

    iIndex = g_ciIndex;
    iSubIndex = g_ciSubIndex;

    CPvcsControlObjectInfo ObjControlObject;

    CDxfLayout::GetControlObject(iIndex,iSubIndex,ObjControlObject);

    //Release access
    CDxfLayout::SetThreadBusyState(iIndex,iSubIndex,false);
    
    g_ciIndex = -1;
    g_ciSubIndex = -1;
    

    UINT uiCurrentValue;

    clock_t CurrentTime;

    clock_t TimeoutTime;
    CString strWagoUnitType = "";
    CString strObjectName = "";
    UINT uiMinValue, uiMaxValue;

    using namespace PvcsControlObjectTypes;

    DigitalSignal DigOp1, DigOp2;
    DigitalSignal DigIp1, DigIp2;
    AnalogSignal AnaIp;
    //AnalogSignal AnaOp;
    bool bDigI1 = false;
    bool bDigI2 = false;
    try
    {

        TimeoutTime = clock() + ((ObjControlObject.GetTimeOut() / 1000) * CLOCKS_PER_SEC);

        strWagoUnitType = ObjControlObject.GetWagoUnitType();
        strObjectName = ObjControlObject.GetName();
        uiMinValue = ObjControlObject.GetInputAnalogSignalList().at(0).Value.Limit.MinValue;
        uiMaxValue = ObjControlObject.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue;

        DigOp1  = ObjControlObject.GetOutputDigitalSignalList().at( 0 );
        DigOp2  = ObjControlObject.GetOutputDigitalSignalList().at( 1 );
        DigIp1  = ObjControlObject.GetInputDigitalSignalList().at( 0 );
        DigIp2  = ObjControlObject.GetInputDigitalSignalList().at( 1 );
        AnaIp   = ObjControlObject.GetInputAnalogSignalList().at( 0 );
       // AnaOp   = ObjControlObject.GetOutputAnalogSignalList().at( 0 );
    }
    catch( exception &e )
    {
        TRACE("*****CPvcsControlObjectCargoValveBackgroundControllerInfo-updatevalue*******");
        XmlLogError( e.what() );
        CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

        //Reset Thread parameter
        CargoThreadReset(iIndex,iSubIndex);
        return 0;
    }

    CDxfLayout::SetControlOperationState(iIndex,iSubIndex,false);

    CString strSpinValue = "";

    CDxfLayout::GetValueToBeSet(iIndex,iSubIndex,strSpinValue);

    if(atoi(strSpinValue) == int(uiMaxValue))//If 100% button clicked
    {
        //Get current value
        if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if able to get value of analog input
        {
            uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
        }
        else//if unable to get current value then so Time out
        {
            TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
            if( it != theTimeOutInfo().end() )
               ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
            CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");


            //Reset Thread parameter
            CargoThreadReset(iIndex,iSubIndex);
            CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
            return 0;
        }
            //get digital input 1 and 2
        CPvcsWagoControl::theWagoUnit().GetValue(DigIp1,bDigI1,strWagoUnitType);

        if(bDigI1 )
        {
            CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
            TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
            if( it != theTimeOutInfo().end() )
                ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);
            CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

            //Reset Thread parameter
            CargoThreadReset(iIndex,iSubIndex);
            TRACE("\n\n\nThrottle Button - 0 - Exit equal- 1\n\n\n");
            CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
            return 0;
        }

        CurrentTime = clock();

        bool bIsOutputSet = false;

        while(CPVCSApp::m_bIsAlive) //for 100%
        {

            //Check for thread closing signal
            if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
            {
                CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
                CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
                CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
                TRACE("\n\n\nThrottle Button - 100 - Exit Force - 1\n\n\n");
                return 0;
            }
            //get digital input 1 state
            CPvcsWagoControl::theWagoUnit().GetValue(DigIp1,bDigI1,strWagoUnitType);

            //if timeout occurred and value still lower than 100% and digitial input 1 is false
            if(CurrentTime > TimeoutTime &&  !bDigI1 )
            {
                CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
                TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
                if( it != theTimeOutInfo().end() )
                    ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
                CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                //Reset Thread parameter
                CargoThreadReset(iIndex,iSubIndex);
                CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
                string tStr = "WARNING\n"+strObjectName+" TimeOut";
                AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);

                return 0;
            }

            //Set digital output to true to open Valve 100%, as current value less and igital input 1 is false
            if(!bDigI1 )
            {
                if(!bIsOutputSet) //set output true once
                {
                    CargoCheckAndSetValue(DigOp1,true,strWagoUnitType);
                    bIsOutputSet = true;
                }
            }
            else //keep the output for another 15 seconds for external calibration support
            {

                for(int i =1; i<= 15; i++)
                {
                    //Check for thread closing signal
                    if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
                    {
                        CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
                        CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");
                        CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
                        CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
                        return 0;
                    }
                    else
                        Sleep(1000);
                }


                CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
                TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
                if( it != theTimeOutInfo().end() )
                    ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);
                CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                //Reset Thread parameter
                CargoThreadReset(iIndex,iSubIndex);
                CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
                return 0;
            }

            //Get new current value
            if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))
            {
                uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
            }

            //Get new current time
            CurrentTime = clock() - 100;//100ms for sleep
            Sleep(100);

        }//while(1) end
    }//for 100% end
    else if(atoi(strSpinValue) == int(uiMinValue))//If 0% button clicked
    {
        if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if able to get value of analog input
        {
            uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);  
        }
        else
        {
            TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
            if( it != theTimeOutInfo().end() )
                ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
            CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

            //Reset Thread parameter
            CargoThreadReset(iIndex,iSubIndex);
            CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
            return 0;
        }
        CPvcsWagoControl::theWagoUnit().GetValue(DigIp2,bDigI2,strWagoUnitType);

        if(bDigI2)
        {
            CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
            TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
            if( it != theTimeOutInfo().end() )
               ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);
            CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

            //Reset Thread parameter
            CargoThreadReset(iIndex,iSubIndex);
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
                CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
                CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
                CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
                TRACE("\n\n\nThrottle Button - 100 - Exit Force - 1\n\n\n");
                return 0;
            }
            //get digital input 2 state
            CPvcsWagoControl::theWagoUnit().GetValue(DigIp2,bDigI2,strWagoUnitType);

            //if timeout occurred and value still greater than 0% and digitial input 2 is false
            if(CurrentTime > TimeoutTime && !bDigI2)
            {
                CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
                TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
                if( it != theTimeOutInfo().end() )
                    ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
                CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                //Reset Thread parameter
                CargoThreadReset(iIndex,iSubIndex);
                CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
                string tStr = "WARNING\n"+strObjectName+" TimeOut";
                AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);

                return 0;
            }

            //Set digital output to true to close Valve (0%) and digitial input 2 is false
            if(!bDigI2)
            {
                if(!bIsOutputSet) //set output true once
                {
                    CargoCheckAndSetValue(DigOp2,true,strWagoUnitType);
                    bIsOutputSet = true;
                }
            }
            else //keep the output for another 15 seconds for external calibration support
            {

                for(int i =1; i<=15 ; i++)
                {
                    //Check for thread closing signal
                    if(CDxfLayout::GetThreadExitState(iIndex,iSubIndex))
                    {
                        CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
                        CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");
                        CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
                        CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
                        return 0;
                    }
                    else
                        Sleep(1000);
                }
                CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
                TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
                if( it != theTimeOutInfo().end() )
                    ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);
                CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                //Reset Thread parameter
                CargoThreadReset(iIndex,iSubIndex);
                CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
                return 0;
            }

            //Get new current value
            if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))
            {
                uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
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
        CargoThreadReset(iIndex,iSubIndex);
        CDxfLayout::SetControlOperationState(iIndex,iSubIndex,true);
        TRACE("\n\n\nThrottle Button - Nothing - Exit Normal - 4\n\n\n");
        return 0;
    }

}

//Thread Start when Spin ctrl is used
UINT CPvcsControlObjectCargoValve::SetCargoValueThread(LPVOID pParam)
{
    int iIndex, iSubIndex;

    iIndex = g_ciIndex;
    iSubIndex = g_ciSubIndex;

    CPvcsControlObjectInfo ObjControlObject;

    CDxfLayout::GetControlObject(iIndex,iSubIndex,ObjControlObject);
    //Release access
    CDxfLayout::SetThreadBusyState(iIndex,iSubIndex,false);
    g_ciIndex = -1;
    g_ciSubIndex = -1;
    g_cbRegulatorStop = false;

    UINT uiCurrentValue;

    clock_t CurrentTime;

    clock_t TimeoutTime;
    CString strWagoUnitType = "";
    CString strObjectName = "";
    UINT uiMinValue, uiMaxValue;

    using namespace PvcsControlObjectTypes;

    DigitalSignal DigOp1, DigOp2;
    DigitalSignal DigIp1, DigIp2;
    AnalogSignal AnaIp;
    bool bDigI1 = false;
    bool bDigI2 = false;
    try
    {



        TimeoutTime = clock() + ((ObjControlObject.GetTimeOut() / 1000) * CLOCKS_PER_SEC);

        strWagoUnitType = ObjControlObject.GetWagoUnitType();
        strObjectName = ObjControlObject.GetName();
        uiMinValue = ObjControlObject.GetInputAnalogSignalList().at(0).Value.Limit.MinValue;
        uiMaxValue = ObjControlObject.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue;




        DigOp1  = ObjControlObject.GetOutputDigitalSignalList().at( 0 );
        DigOp2  = ObjControlObject.GetOutputDigitalSignalList().at( 1 );
        DigIp1  = ObjControlObject.GetInputDigitalSignalList().at( 0 );
        DigIp2  = ObjControlObject.GetInputDigitalSignalList().at( 1 );
        AnaIp   = ObjControlObject.GetInputAnalogSignalList().at( 0 );
    }
    catch( exception &e )
    {
        TRACE("*****CPvcsControlObjectCargoValveBackgroundControllerInfo-updatevalue*******");
        XmlLogError( e.what() );
        CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

        //Reset Thread parameter
        CargoThreadReset(iIndex,iSubIndex);
        return 0;
    }


    if (CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType) )
    {
        int CurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);

        int PercentageToStop = ObjControlObject.GetPercentagetoStop();

        CString strSpinValue = "";
        CDxfLayout::GetValueToBeSet(iIndex,iSubIndex,strSpinValue);

        int iSpinvalue = atoi(strSpinValue);


        int DiffInValue = abs(int(uiCurrentValue) - iSpinvalue);

        if(DiffInValue < 0)
            DiffInValue = -(DiffInValue);

        if(DiffInValue > PercentageToStop)//this is the case where difference in Percentage to set is higher than Percentage to stop, then do regulatory work
        {
            unsigned NewValueToBeSet;

            if(iSpinvalue > CurrentValue)//set digital output 1 to true
            {
                NewValueToBeSet = iSpinvalue - PercentageToStop;

                if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if unable to get value of analog input, just return
                {
                    uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
                }
                else//Set time out true
                {
                    TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
                    if( it != theTimeOutInfo().end() )
                        ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
                    CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                    //Reset Thread parameter
                    CargoThreadReset(iIndex,iSubIndex);
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
                        CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
                        CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");
                        CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
                        return 0;
                    }

                    //get digital input 1 state
                    CPvcsWagoControl::theWagoUnit().GetValue(DigIp1,bDigI1,strWagoUnitType);

                    //if timeout occurred and value still lower than NewValueToBeSet% and digitial input 1 is false
                    if(CurrentTime > TimeoutTime && uiCurrentValue < NewValueToBeSet && bDigI1 == false )
                    {
                        CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);
                        TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
                        if( it != theTimeOutInfo().end() )
                            ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
                        CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                        //Reset Thread parameter
                        CargoThreadReset(iIndex,iSubIndex);
                        string tStr = "WARNING\n"+strObjectName+" TimeOut";
                        AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);
                        return 0;
                    }
                    if ( (uiMaxValue == NewValueToBeSet )&& !bDigI1 ){
                        if(!bIsOutputSet) //set output true once
                        {
                            CargoCheckAndSetValue(DigOp1,true,strWagoUnitType);
                            bIsOutputSet = true;
                        }
                    }
                    //Set digital output to true to open Valve to NewValueToBeSet% and digitial input 1 is false
                    else if(( uiCurrentValue < NewValueToBeSet ) && bDigI1 == false)
                    {
                        if(!bIsOutputSet) //set output true once
                        {
                            CargoCheckAndSetValue(DigOp1,true,strWagoUnitType);
                            bIsOutputSet = true;
                        }
                    }
                    else //Now do the Regulation work
                    {
                        CargoCheckAndSetValue(DigOp1,false,strWagoUnitType);

                        for(int CallCounter = 1; CallCounter<=3 && !g_cbRegulatorStop; CallCounter++)
                        {
                            //Call regulator function
                            if(CargoRegulator(ObjControlObject,TimeoutTime))
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
                        CargoThreadReset(iIndex,iSubIndex);
                        return 0;
                    }

                    //Get new current value
                    if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))
                    {
                        uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
                    }

                    //Get new current time
                    CurrentTime = clock() - 100;//100ms for sleep
                    Sleep(100);

                }//while(1) end
            }//if set digital output 1 is true end
            else if(iSpinvalue  < CurrentValue)//set digital output 2 is true
            {
                NewValueToBeSet = iSpinvalue + PercentageToStop;

                if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))//if unable to get value of analog input, just return
                {
                    uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
                }
                else//Set time out true
                {
                    TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
                    if( it != theTimeOutInfo().end() )
                        ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
                    CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                    //Reset Thread parameter
                    CargoThreadReset(iIndex,iSubIndex);
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
                        CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
                        CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");
                        CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,true);
                        return 0;
                    }


                    //get digital input 2 state
                    CPvcsWagoControl::theWagoUnit().GetValue(DigIp2,bDigI2,strWagoUnitType);

                    //if timeout occurred and value still greater than NewValueToBeSet% and digitial input 2 is false
                    if(CurrentTime > TimeoutTime && uiCurrentValue > NewValueToBeSet && bDigI2 == false)
                    {
                        CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);
                        TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex));
                        if( it != theTimeOutInfo().end() )
                            ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
                        CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,"");

                        //Reset Thread parameter
                        CargoThreadReset(iIndex,iSubIndex);
                        string tStr = "WARNING\n"+strObjectName+" TimeOut";
                        AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);

                        return 0;
                    }
                    if ( (uiMinValue == NewValueToBeSet )&& !bDigI2 ){
                        if(!bIsOutputSet) //set output true once
                        {
                            CargoCheckAndSetValue(DigOp2,true,strWagoUnitType);
                            bIsOutputSet = true;
                        }
                    }

                    //Set digital output to true to close Valve (NewValueToBeSet%)and digitial input 2 is false
                    else if(uiCurrentValue > NewValueToBeSet && bDigI2 == false)
                    {
                        if(!bIsOutputSet) //set output true once
                        {
                            CargoCheckAndSetValue(DigOp2,true,strWagoUnitType);
                            bIsOutputSet = true;
                        }
                    }
                    else //Now do the Regulation work
                    {
                        CargoCheckAndSetValue(DigOp2,false,strWagoUnitType);

                        for(int CallCounter = 1; CallCounter<=3&& !g_cbRegulatorStop; CallCounter++)
                        {
                            //Call regulator function
                            if(CargoRegulator(ObjControlObject,TimeoutTime))
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
                        CargoThreadReset(iIndex,iSubIndex);
                        return 0;
                    }

                    //Get new current value
                    if(CPvcsWagoControl::theWagoUnit().GetValue(AnaIp,uiCurrentValue,strWagoUnitType))
                    {
                        uiCurrentValue = CPvcsControlObject::AnalogScaleWagoToObject( uiMinValue,uiMaxValue,uiCurrentValue,strObjectName,strWagoUnitType);
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
            for(int CallCounter = 1; CallCounter<=3&& !g_cbRegulatorStop; CallCounter++)
            {
                if(CargoRegulator(ObjControlObject,TimeoutTime))
                {
                    TimeOutInfoSet::iterator it = theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));
                    if( it != theTimeOutInfo().end() )
                        ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);

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
            CargoThreadReset(iIndex,iSubIndex);
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
        CargoThreadReset(iIndex,iSubIndex);
        //TRACE("\n\n====22========Thread exit by normal proram==Value to be set =%d\n\n",pObjControlObject->GetSpinValue());
        return 0;
    }



    //TRACE("\n\n=====23=======Thread exit by normal proram==Value to be set =%d\n\n",pObjControlObject->GetSpinValue());
    return 0;
}

