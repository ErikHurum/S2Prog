#include "StdAfx.h"
#include ".\pvcsconfiguration.h"


// Function name   : theConfiguration
// Description     : This function returns the reference to the global object of
//                   CPvcsConfiguration class
// Return type     : CPvcsConfiguration&

CPvcsConfiguration& theConfiguration()
{
    static CPvcsConfiguration Config;
    return Config;
}


// Function name   : CPvcsConfiguration::CPvcsConfiguration
// Description     : Default Constructor
// Return type     :
// Argument        : void

CPvcsConfiguration::CPvcsConfiguration(void)
{
    if ( !obj_SystemConfig.LoadXMLFile("XMLFILES\\config.xml") )
        XmlLogError("Error opening file: XMLFILES\\config.xml");

    if ( !obj_ReadDXF.LoadXMLFile(obj_SystemConfig.GetdxfFile()) )
        XmlLogError("Error opening Dxf file config");

    if ( !obj_ObjectDetail.LoadXMLFile(obj_SystemConfig.GetDetailConfFile()) ) {
        XmlLogError("Error opening detail config file");
        AfxMessageBox("Error in Detail Configuration file", MB_ICONERROR );
    }
}


// Function name   : CPvcsConfiguration::~CPvcsConfiguration
// Description     : Destructor
// Return type     :
// Argument        : void

CPvcsConfiguration::~CPvcsConfiguration(void)
{
}



// Function name   : CPvcsConfiguration::GetTankName
// Description     : Returns the name of the tank
// Return type     : CString
// Argument        : const int& param_iIndex

CString CPvcsConfiguration::GetTankName(const int& param_iIndex)
{
    return obj_ReadDXF.GetTankName(param_iIndex);
}


// Function name   : CPvcsConfiguration::GetTankFile
// Description     : Returns the name of th etank file
// Return type     : CString
// Argument        : const int& param_iTankID

CString CPvcsConfiguration::GetTankFile(const int& param_iTankID)
{
    return obj_ReadDXF.GetTankDXFFile(param_iTankID);
}


bool CPvcsConfiguration::GetBackupState(void)
{
    return obj_SystemConfig.GetBackupState();
}

bool CPvcsConfiguration::GetSplashState(void)
{
    return obj_SystemConfig.GetSplashState();
}


UINT CPvcsConfiguration::GetWagoUnitCount(void)
{
    return obj_SystemConfig.GetWagoUnitCount();
}

// To get IP address of the wago unit to which to connect.
CString CPvcsConfiguration::GetWagoIP(const UINT& param_nID)
{
    return obj_SystemConfig.GetWagoIP( param_nID );
}
// Is this a Wago unit
int CPvcsConfiguration::GetIsModbusDeviceType(const UINT& param_nID)
{
    return obj_SystemConfig.GetIsModbusDeviceType( param_nID );
}


// To get the first IP address of the wago unit to which to connect.
CString CPvcsConfiguration::GetWagoFirstIP(const UINT& param_nID)
{
    return obj_SystemConfig.GetWagoFirstIP( param_nID );
}
// to get the second IP of wago unit to which to connect
CString CPvcsConfiguration::GetWagoSecondIP(const UINT& param_nID)
{
    return obj_SystemConfig.GetWagoSecondIP(param_nID);
}
// to get the file name in which to log the data
CString CPvcsConfiguration::GetLogFileName(void)
{
    return obj_SystemConfig.GetLogFileName();
}


// To get the value to check if the workstation is having the command permission or not
CString CPvcsConfiguration::GetMasterIP(void)
{
    return obj_SystemConfig.GetMasterIP();
}

// to get the configuration file version
CString CPvcsConfiguration::GetConfigDataVersion(void)
{
    return obj_SystemConfig.GetConfigDataVersion();
}

//Get screen count
int CPvcsConfiguration::GetScreenCount(void)
{
    return obj_SystemConfig.GetScreenCount();
}
//Get SplitScreen
int CPvcsConfiguration::GetSplitScreens(void)
{
    return obj_SystemConfig.GetSplitScreens();
}
//Get ZoomEnabled
bool CPvcsConfiguration::GetZoomEnabled(void)
{
    return obj_SystemConfig.GetZoomEnabled();
}

//Get X-scale
double CPvcsConfiguration::GetScaleX(const int& param_iTankID)
{
    return obj_ReadDXF.GetScaleX(param_iTankID);
}

//Get Y-scale
double CPvcsConfiguration::GetScaleY(const int& param_iTankID)
{
    return obj_ReadDXF.GetScaleY(param_iTankID);
}

//Get X-scale
double CPvcsConfiguration::GetScaleX(void)
{
    return obj_SystemConfig.GetScaleX();
}

//Get Y-scale
double CPvcsConfiguration::GetScaleY(void)
{
    return obj_SystemConfig.GetScaleY();
}

    //Get password
CString CPvcsConfiguration::GetPassword(void)
{
    return obj_SystemConfig.GetPassword();
}


	//Get GetBackGroundColor
int CPvcsConfiguration::GetBackGroundColor(const int& param_iTankID, bool *Success)
{
    return obj_ReadDXF.GetBackGroundColor(param_iTankID, Success);
}
    //Get Object color-scale
int CPvcsConfiguration::GetObjectColor(const int& param_iTankID, bool *Success)
{
    return obj_ReadDXF.GetObjectColor(param_iTankID, Success);
}

	//Get GetLineColor
int CPvcsConfiguration::GetLineColor(const int& param_iTankID, bool *Success)
{
    return obj_ReadDXF.GetLineColor(param_iTankID, Success);
}
    //Get Text color
int CPvcsConfiguration::GetTextColor(const int& param_iTankID, bool *Success)
{
    return obj_ReadDXF.GetTextColor(param_iTankID, Success);
}


	// To get The text color of the object whose index is provided
int CPvcsConfiguration::GetUndefObjectColor(const int& param_iTankID, bool *Success)
{
    return obj_ReadDXF.GetUndefObjectColor(param_iTankID, Success);
}

//Get screen file
CString CPvcsConfiguration::GetScreenFile(int ScreenIndex)
{
    return obj_ReadDXF.GetScreenFile(ScreenIndex);
}
//Get screen tank layer
CString CPvcsConfiguration::GetScreenTankLayer(int ScreenIndex)
{
    return obj_ReadDXF.GetScreenTankLayer(ScreenIndex);
}
//Get screen title
CString CPvcsConfiguration::GetScreenTitle(int ScreenIndex)
{
    return obj_ReadDXF.GetScreenTitle(ScreenIndex);
}


    //Get Object color-scale
int CPvcsConfiguration::GetScreenColor(int ScreenIndex, bool *Success)
{
    return obj_ReadDXF.GetScreenColor(ScreenIndex, Success);
}
    //Get back ground color-scale
int CPvcsConfiguration::GetScreenBckGndColor(int ScreenIndex, bool *Success)
{
    return obj_ReadDXF.GetScreenBckGndColor(ScreenIndex, Success);
}

	// To get The line color of the object whose index is provided
int CPvcsConfiguration::GetScreenLineColor(int ScreenIndex, bool *Success)
{
    return obj_ReadDXF.GetScreenLineColor(ScreenIndex,Success);
}
	// To get The text color of the object whose index is provided
int CPvcsConfiguration::GetScreenTextColor(int ScreenIndex, bool *Success)
{
    return obj_ReadDXF.GetScreenTextColor(ScreenIndex,Success);
}

//Get master port
int CPvcsConfiguration::GetMasterPort(void)
{
    return obj_SystemConfig.GetMasterPort();
}
//Get request time out
int CPvcsConfiguration::GetRequestTimeOut(void)
{
    return obj_SystemConfig.GetRequestTimeOut();
}
//Get Surveyor IP
CString CPvcsConfiguration::GetSurveyorIP(void)
{
    return obj_SystemConfig.GetSurveyorIP();
}
//Get Emergency Button count
UINT CPvcsConfiguration::GetEmgButtonCount(void)
{
    return obj_SystemConfig.GetEmgButtonCount();
}

//Get Emergency Buttton Text
CString CPvcsConfiguration::GetEmgButtonText(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetEmgButtonText(param_uiButtonIndex);
}


//Get Emergency Button Tooltip
CString CPvcsConfiguration::GetEmgButtonTooltip(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetEmgButtonToolTip(param_uiButtonIndex);
}

//Get Emergency Button wago channel number
int CPvcsConfiguration::GetWagoInputEmgChNo(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetWagoInputEmgChNo(param_uiButtonIndex);
}

//Get Emergency button Input invert state
bool CPvcsConfiguration::GetEmgObjInputInvert(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetEmgObjInputInvert(param_uiButtonIndex);
}
//Get Emergency button Input invert state
int CPvcsConfiguration::GetEmgObjInputType(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetEmgObjInputType(param_uiButtonIndex);
}
//Get Emergency button Input invert state
double CPvcsConfiguration::GetEmgObjInputThreshold(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetEmgObjInputThreshold(param_uiButtonIndex);
}
//Get Emergency button wago unit no
int CPvcsConfiguration::GetEmgWagoUnit(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetEmgWagoUnit(param_uiButtonIndex);
}
//Get Emergency button state
int CPvcsConfiguration::GetEmgButtonState(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetEmgButtonState(param_uiButtonIndex);
}

int CPvcsConfiguration::GetEmgButtonResetAllStatus(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetEmgButtonResetAllStatus(param_uiButtonIndex);
}
int CPvcsConfiguration::GetEmgButRemoteControl(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetEmgButRemoteControl(param_uiButtonIndex);
}

int CPvcsConfiguration::GetInputStatusRangeStart(UINT param_nID)
{
    return obj_SystemConfig.GetInputStatusRangeStart(param_nID);
}
int CPvcsConfiguration::GetInputStatusRangeEnd(UINT param_nID)
{
    return obj_SystemConfig.GetInputStatusRangeEnd(param_nID);
}
int CPvcsConfiguration::GetInputStatusCommand(UINT param_nID)
{
    return obj_SystemConfig.GetInputStatusCommand(param_nID);
}


//Get Pump Control Button count
UINT CPvcsConfiguration::GetPumpButtonCount(void)
{
    return obj_SystemConfig.GetPumpButtonCount();
}

//Get Pump Control Buttton Text
CString CPvcsConfiguration::GetPumpButtonText(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetPumpButtonText(param_uiButtonIndex);
}


//Get Pump Control Button Tooltip
CString CPvcsConfiguration::GetPumpButtonTooltip(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetPumpButtonToolTip(param_uiButtonIndex);
}

//Get Pump Control Button wago channel number
int CPvcsConfiguration::GetPumpButWagoInputChNo(UINT param_uiButtonIndex, UINT param_uiID, int *pRegBit)
{
    return obj_SystemConfig.GetPumpButWagoInputChNo(param_uiButtonIndex, param_uiID, pRegBit);
}

//Get Pump Control Button wago channel number
int CPvcsConfiguration::GetPumpButWagoOutputChNo(UINT param_uiButtonIndex, UINT param_uiID, int *pRegBit)
{
    return obj_SystemConfig.GetPumpButWagoOutputChNo(param_uiButtonIndex, param_uiID, pRegBit);
}
//Get Pump Control button Input invert state
bool CPvcsConfiguration::GetPumpButInputInvert(UINT param_uiButtonIndex, UINT param_uiID)
{
    return obj_SystemConfig.GetPumpButInputInvert(param_uiButtonIndex,  param_uiID);
}

//Get Pump Control button Output invert state
bool CPvcsConfiguration::GetPumpButOutputInvert(UINT param_uiButtonIndex, UINT param_uiID)
{
    return obj_SystemConfig.GetPumpButInputInvert(param_uiButtonIndex,  param_uiID);
}
//Get Pump Control button Input invert state
double CPvcsConfiguration::GetPumpButInputThreshold(UINT param_uiButtonIndex, UINT param_uiID)
{
    return obj_SystemConfig.GetPumpButInputThreshold(param_uiButtonIndex, param_uiID);
}
//Get Pump Control button wago unit no
int CPvcsConfiguration::GetPumpButWagoOutputUnit(UINT param_uiButtonIndex, UINT param_uiID)
{
    return obj_SystemConfig.GetPumpButWagoOutputUnit(param_uiButtonIndex, param_uiID);
}
//Get Pump Control button wago unit no
int CPvcsConfiguration::GetPumpButWagoInputUnit(UINT param_uiButtonIndex, UINT param_uiID)
{
    return obj_SystemConfig.GetPumpButWagoInputUnit(param_uiButtonIndex, param_uiID);
}
//Get Pump Control button state
int CPvcsConfiguration::GetPumpButtonState(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetPumpButtonState(param_uiButtonIndex);
}

int CPvcsConfiguration::GetPumpButRemoteControl(UINT param_uiButtonIndex)
{
    return obj_SystemConfig.GetPumpButRemoteControl(param_uiButtonIndex);
}

// To get the Input Bit number
UINT CPvcsConfiguration::GetPumpInputRegBitNo(UINT param_uiButtonIndex, UINT param_uiID) {
	return obj_SystemConfig.GetPumpInputRegBitNo(param_uiButtonIndex, param_uiID);
}

// To get the output Bit number
UINT CPvcsConfiguration::GetPumpOutputRegBitNo(UINT param_uiButtonIndex, UINT param_uiID) {
    return obj_SystemConfig.GetPumpOutputRegBitNo(param_uiButtonIndex, param_uiID);
}

// To get the number of total input digital and analog attached to a object
UINT CPvcsConfiguration::GetPumpButInputCount(UINT param_uiButtonIndex) {
    return obj_SystemConfig.GetPumpButInputCount(param_uiButtonIndex);
}

// Function to get total number of Analog and digital Output channels attached
UINT CPvcsConfiguration::GetPumpButOutputCount(UINT param_uiButtonIndex) {
    return obj_SystemConfig.GetPumpButOutputCount(param_uiButtonIndex);
}


// To get the type of connection for first Input Connection (Analog/Digital)
UINT CPvcsConfiguration::GetPumpButInputConnType(UINT param_uiButtonIndex, UINT param_uiID)
{
    return obj_SystemConfig.GetPumpButInputConnType(param_uiButtonIndex,param_uiID);
}

// To get the type of connection for first Output Connection (Analog/Digital)
UINT CPvcsConfiguration::GetPumpButOutputConnType(UINT param_uiButtonIndex, UINT param_uiID)
{
    return obj_SystemConfig.GetPumpButOutputConnType(param_uiButtonIndex,param_uiID);
}

// To get the function of output bit
UINT CPvcsConfiguration::GetPumpOutputFunction(UINT param_uiButtonIndex, UINT param_uiID) {
	return obj_SystemConfig.GetPumpOutputFunction(param_uiButtonIndex, param_uiID);
}

// To get the function of input bit
UINT CPvcsConfiguration::GetPumpInputFunction(UINT param_uiButtonIndex, UINT param_uiID) {
    return obj_SystemConfig.GetPumpInputFunction(param_uiButtonIndex, param_uiID);
}
