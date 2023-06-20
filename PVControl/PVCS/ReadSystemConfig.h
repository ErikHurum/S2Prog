#pragma once
#include "loadxml.h"
/////////////////////////////////////////////////////////////////////////
// class to read system configuration from the XML configuration file
////////////////////////////////////////////////////////////////////////// 
/// 
#define INP_DIGITAL  0
#define INP_DIG_REG  1
#define INP_ANALOG   2
#define INP_UNDEF    3

#define INP_FUNC_UNDEF 					0
#define INP_FUNC_IN_HAS_CONTROL 		1
#define INP_FUNC_IN_CONTROL_REQUEST 	2
#define INP_FUNC_OUT_REQUEST_CONTROL 	3
#define INP_FUNC_OUT_RELEASE_CONTROL	4
#define INP_FUNC_OUT_ABORT_REQUEST	 	5

#define MODBUS_DEVICE_WAGO      0
#define MODBUS_DEVICE_WÄRTSILA  1
class CReadSystemConfig :
    public CLoadXML, public CConvertData
{
public:
    CReadSystemConfig(void);
    virtual ~CReadSystemConfig(void);
    // Function returns the SURVEYOR IP from The Config file
    CString GetSurveyorIP(void);
    // Function to get the Data By tag Name and return the Node TEXT
    CString GetTagData(IN CString param_pcTagName);
    // To get The IP of WAGO Control UNIT
    CString GetControlUnitIP(void);
    //Function returns machine's localIP
    CString GetLocalIP(void);
    // To get the path where DXF are stored
    CString GetDXFPath(void);
    // To get the Port number on which connection with Surveyor is established
    unsigned int GetConnectionPort(void);
    // To give the name of the dxf configutaion file
    CString GetdxfFile(void);
    // To read the detail confiuration file name from main config file
    CString GetDetailConfFile(void);
    // to get Total Number of Wago Units Connected
    UINT GetWagoUnitCount(void);
        // To get IP address of the particular  Wago Unit
    CString GetWagoIP(UINT param_uiWagoUnitNo);
    // To Read the name of file in which object changes are to be logged
    CString GetLogFileName(void);
    // To get the master/server ip
    CString GetMasterIP(void);
    CString GetWagoFirstIP(UINT param_uiWagoOne);
    // to get secondary or back up IP of the ethernet on wago port
    CString GetWagoSecondIP(UINT param_uiWagoTwo);
// to get secondary or back up IP of the ethernet on wago port
    int GetIsModbusDeviceType(UINT param_uiWagoUnitNo);

    // To get the IP Address of the machine/ workstation having the command
    CString GetCommandIP(void);
    // To get the configuration file version
    CString GetConfigDataVersion(void);
    bool Start_Server(void);

    //Get no of screen count
    int GetScreenCount(void);
    //Get splitscreen
    int GetSplitScreens(void);
    //Get Zoom enabled
    bool GetZoomEnabled(void);

    //Get X-scale
    double GetScaleX(void);
    //Get Y-scale
    double GetScaleY(void);
    //Get password 
    CString GetPassword(void);

    //Get the Master port
    int GetMasterPort(void); 
    //Get the request timeout
    int GetRequestTimeOut(void);
    //Get the backup state
    bool GetBackupState(void);
    //Get the splash window state
    bool GetSplashState(void);
    //Get the channel no to which the emg button is connected
    int GetWagoInputEmgChNo(UINT param_uiChannelNo);
    // To get the input type, analog/digital for the emg button connected
    UINT GetEmgObjInputType(UINT param_uiChannelNo);
    // To get the input threshold for active button
    double GetEmgObjInputThreshold(UINT param_uiChannelNo);
    //Get that the input to channel no is inverted or not
    bool GetEmgObjInputInvert(UINT param_uiChannelNo);
    //Get Emergency button count
    UINT GetEmgButtonCount(void);
    //Get Emergency button Text
    CString GetEmgButtonText(UINT param_uiButtonIndex);
    //Get Emergency button Tooltip
    CString GetEmgButtonToolTip(UINT param_uiButtonIndex);
    //Get Emergency button wago unit no
    int GetEmgWagoUnit(UINT param_uiButtonIndex);
    //Get emergency button state
    int GetEmgButtonState(UINT param_uiButtonIndex);
    //Get emergency button state
    int GetEmgButtonResetAllStatus(UINT param_uiButtonIndex);
    int GetEmgButRemoteControl(UINT param_uiButtonIndex);

    int GetInputStatusRangeStart(UINT param_uiWagoUnitNo);
    int GetInputStatusRangeEnd(UINT param_uiWagoUnitNo);
    int GetInputStatusCommand(UINT param_uiWagoUnitNo);


    //Get Pump Control button channel
    int GetPumpButWagoInputChNo(UINT param_uiChannelNo, UINT param_uiID, int *pRegBit=NULL);
    //Get Pump Control button channel
    int GetPumpButWagoOutputChNo(UINT param_uiChannelNo, UINT param_uiID, int *pRegBit=NULL);
    // To get the input threshold for active button
    double GetPumpButInputThreshold(UINT param_uiChannelNo, UINT param_uiID);
    //Get that the input to channel no is inverted or not
    bool GetPumpButInputInvert(UINT param_uiChannelNo, UINT param_uiID);
    //Get that the output to channel no is inverted or not
    bool GetPumpButOutputInvert(UINT param_uiChannelNo, UINT param_uiID);
    //Get Emergency button count
    UINT GetPumpButtonCount(void);
    //Get Pump Control button Text
    CString GetPumpButtonText(UINT param_uiButtonIndex);
    //Get Pump Control button Tooltip
    CString GetPumpButtonToolTip(UINT param_uiButtonIndex);
    //Get Pump Control button wago unit no
    int GetPumpButWagoOutputUnit(UINT param_uiButtonIndex, UINT param_uiID);
    //Get Pump Control button wago unit no
    int GetPumpButWagoInputUnit(UINT param_uiButtonIndex, UINT param_uiID);
    //Get Pump Control button state
    int GetPumpButtonState(UINT param_uiButtonIndex);
    //Get Pump Control button state
    int GetPumpButRemoteControl(UINT param_uiButtonIndex);

    // To get the bit from output register
    UINT GetPumpOutputRegBitNo(UINT param_uiButtonIndex, UINT param_uiID);
    // To get the bit from input register
    UINT GetPumpInputRegBitNo(UINT param_uiButtonIndex, UINT param_uiID);
	// To get the number of total input digital and analog attached to a object
	UINT GetPumpButInputCount(UINT param_uiButtonIndex);
	// Function to get total number of Analog and digital Output channels attached
	UINT GetPumpButOutputCount(UINT param_uiButtonIndex);
	// To get the type of connection for first Input Connection (Analog/Digital)
	UINT GetPumpButInputConnType(UINT param_uiButtonIndex, UINT param_uiID);
	// To get the type of connection for first Output Connection (Analog/Digital)
	UINT GetPumpButOutputConnType(UINT param_uiButtonIndex, UINT param_uiID);
	// To get the function of output bit
	UINT GetPumpOutputFunction(UINT param_uiButtonIndex, UINT param_uiID);
	// To get the function of input bit
	UINT GetPumpInputFunction(UINT param_uiButtonIndex, UINT param_uiID);
};
