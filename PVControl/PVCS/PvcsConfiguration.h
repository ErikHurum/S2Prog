#pragma once

#include "cominc.h"
#include "readdxfconfig.h"
#include "readlegends.h"
#include "objectdetails.h"
#include "convertdata.h"
#include "readsystemconfig.h"

// Class Name   : CPvcsConfiguration
// Description  : Class to get the Configuration Settings

class CPvcsConfiguration {
    friend CPvcsConfiguration& theConfiguration();

public:
    ~CPvcsConfiguration(void);

private:
    CPvcsConfiguration(void);

    CReadDXFConfig obj_ReadDXF;
    CObjectDetails obj_ObjectDetail;
    CConvertData obj_ConvertData;
    CReadSystemConfig obj_SystemConfig;

public:
    int GetLegendCount(void);
    CString GetBallastFile(void);
    CString GetCargoFile(void);
    CString GetTankLayer(void);
    CString GetLogFileName(void);

    bool GetBackupState(void);
    bool GetSplashState(void);

    CString GetTankName(const int& param_iIndex);
    CString GetTankFile(const int& param_iTankID);
    UINT GetWagoUnitCount(void);

    CString GetWagoIP(const UINT& param_nID);
    int GetIsModbusDeviceType(const UINT& param_nID);

    CString GetWagoFirstIP(const UINT& param_nID);
    // to get the second port ip of wago ethernet
    CString GetWagoSecondIP(const UINT& param_nID);
    // To get the IP of the Machine who is the Command or owner
//  , remove this function  CString GetCommandMachineIP(void);
    // To get the Master/Server IP
    CString GetMasterIP(void);
    //To get the IP address of machine
    CString GetLocalIP(void);
    //To start machiine as server
    bool Start_Server(void);
    // to get the configuration file version
    CString GetConfigDataVersion(void);

    //Get screen count
    int GetScreenCount(void);
    //Get number of split screens
    int GetSplitScreens(void);
    // See if zoom is enabled
    bool GetZoomEnabled(void);
    //Get X-scale
    double GetScaleX(const int& param_iTankID);
    //Get Y-scale
    double GetScaleY(const int& param_iTankID);
    //Get X-scale
    double GetScaleX(void);
    //Get Y-scale
    double GetScaleY(void);
    // Get password
    CString GetPassword(void);

    //Get Background color-scale
    int GetBackGroundColor(const int& param_iTankID, bool *Success=NULL);
    //Get Object color-scale
    int GetObjectColor(const int& param_iTankID, bool *Success=NULL);
    //Get GetLineColor
    int GetLineColor(const int& param_iTankID, bool *Success=NULL);
    //Get GetTextColor
    int GetTextColor(const int& param_iTankID, bool *Success=NULL);
	// To get The text color of the object whose index is provided
	int GetUndefObjectColor(const int& param_iTankID, bool *Success=NULL);
    //Get screen title
    CString GetScreenTitle(int ScreenIndex);
    //Get screen file
    CString GetScreenFile(int ScreenIndex);
    //Get screen tank layer
    CString GetScreenTankLayer(int ScreenIndex);
    //Get screen color
    int GetScreenColor(int ScreenIndex, bool *Success=NULL);
    //Get screen color
    int GetScreenBckGndColor(int ScreenIndex, bool *Success=NULL);
	// To get The line color of the object whose index is provided
	int GetScreenLineColor(int ScreenIndex, bool *Success=NULL);
	// To get The text color of the object whose index is provided
	int GetScreenTextColor(int ScreenIndex, bool *Success=NULL);
    //Get Master port
    int GetMasterPort(void);
    //Get request time out
    int GetRequestTimeOut(void);
    //Get Surveyor IP
    CString GetSurveyorIP(void);
    //Get Emergency Button count
    UINT GetEmgButtonCount(void);

    //Get Emergency Buttton Text
    CString GetEmgButtonText(UINT param_uiButtonIndex);

    //Get Emergency Button Tooltip
    CString GetEmgButtonTooltip(UINT param_uiButtonIndex);

    //Get Emergency Button wago channel number
    int GetWagoInputEmgChNo(UINT param_uiButtonIndex);

    //Get Emergency button Input invert state
    bool GetEmgObjInputInvert(UINT param_uiButtonIndex);
    //Get Emergency button Input type
    int GetEmgObjInputType(UINT param_uiButtonIndex);
    //Get Emergency button Input threshold
    double GetEmgObjInputThreshold(UINT param_uiButtonIndex);

    //Get Emergency button wago unit no
    int GetEmgWagoUnit(UINT param_uiButtonIndex);

    //Get Emergency Button State
    int GetEmgButtonState(UINT param_uiButtonIndex);

    int GetEmgButtonResetAllStatus(UINT param_uiButtonIndex);
    int GetEmgButRemoteControl(UINT param_uiButtonIndex);

    int GetInputStatusRangeStart(UINT param_nID);
    int GetInputStatusRangeEnd(UINT param_nID);
    int GetInputStatusCommand(UINT param_nID);


    //Get Pump Control Button count
    UINT GetPumpButtonCount(void);

    //Get Pump Control Buttton Text
    CString GetPumpButtonText(UINT param_uiButtonIndex);

    //Get Pump Control Button Tooltip
    CString GetPumpButtonTooltip(UINT param_uiButtonIndex);

    //Get Pump Control Button wago channel number
    int GetPumpButWagoInputChNo(UINT param_uiButtonIndex, UINT param_uiID, int *pRegBit=NULL);
    //Get Pump Control Button wago channel number
    int GetPumpButWagoOutputChNo(UINT param_uiButtonIndex, UINT param_uiID, int *pRegBit=NULL);
    //Get Pump Control button Input invert state
    bool GetPumpButInputInvert(UINT param_uiButtonIndex, UINT param_uiID);
    //Get Pump Control button Input invert state
    bool GetPumpButOutputInvert(UINT param_uiButtonIndex, UINT param_uiID);
    //Get Pump Control button Input threshold
    double GetPumpButInputThreshold(UINT param_uiButtonIndex, UINT param_uiID);

    //Get Pump Control button wago unit no
    int GetPumpButWagoOutputUnit(UINT param_uiButtonIndex, UINT param_uiID);
	//Get Pump Control button wago unit no
	int GetPumpButWagoInputUnit(UINT param_uiButtonIndex, UINT param_uiID);

    //Get Pump Control Button State
    int GetPumpButtonState(UINT param_uiButtonIndex);

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

// The only function which can access this class
CPvcsConfiguration& theConfiguration();
