#pragma once
#include "readxmltagnode.h"
#include <vector>
//////////////////////////////////////////////////////////////////////
// Class to read configuration and other detaisl related to objects //
// specially the controlled objects connected to WAGO				//
//////////////////////////////////////////////////////////////////////

#define INP_DIGITAL  0
#define INP_DIG_REG  1
#define INP_ANALOG   2
#define INP_UNDEF    3

class CObjectDetails :
	public CReadXMLTagNode
{
public:
	CObjectDetails(void);
	virtual ~CObjectDetails(void);
	// Function to return the Input Channel No on which Control Object is Connected
	CString GetInputChannel(IN CString param_pcObjLocation,IN CString param_pcObjectID);
private:
	// function to read the node and return data accordingly for all tags in the node
	CString GetNodeData(IN CString param_pcObjLocation,IN CString param_pcObjID,IN CString param_pcTagName);
public:
	// Function to get the Output Connection type of Object Analog or Digital
	unsigned int GetOutputType(IN CString param_pcObjLocation,IN CString param_pcObjectID);
	// Function to get the INput Channel type Analog or digital it returns 0 for digital 1 for analog and 2 for error or undefined type
	unsigned int GetInputType(IN CString param_pcObjLocation,IN CString param_pcObjectID);
	// Function to get the OUTPUT channel number of teh controlled object
	CString GetOutputChannel(IN CString param_pcObjLocation,IN CString param_pcObjectID);
	// To get the type of Object Controlled or not-controlled it returns 0 for controlled 1 for not controlled and 2 for other or undefined type
	unsigned int GetObjectType(IN CString param_pcObjLocation,CString param_pcObjectID);
	// To get the name of the Object
	CString GetObjectName(CString param_pcObjLocation, CString param_pcObjectID);
	// To get the status text to show
	CString GetStatusText(IN UINT param_pcObjLocation,UINT param_pcObjectID,unsigned int param_uiStatus);
	// To get the minimum value for Analog device
	UINT GetMinValue(IN UINT param_pcObjLocation,UINT param_pcObjectID);
	// Function to return the max value for analog control
	UINT GetMaxValue(IN UINT param_pcObjLocation,UINT param_pcObjectID);
	// Functiont o get the Step size for analog control
	UINT GetSteps(IN UINT param_pcObjLocation,UINT param_pcObjectID);
	// To get the unit to display in case of analog card
	CString GetAnalogUnit(IN UINT param_pcObjLocation,UINT param_pcObjectID);
	// to locate a tank and return true if it existes else return false
	bool LocateTank(UINT param_pcObjLocation,UINT param_pcObjectID);
	// To the Tooltip text from the file
	CString GetToolTipRef(IN UINT param_pcObjLocation,UINT param_pcObjectID);
	// To get the tool tip text to be displayed
	CString GetToolTipText(IN UINT param_pcObjLocation,UINT param_pcObjectID);
	// To get the number of total input digital and analog attached to a object
	UINT GetObjectInputCount(UINT param_pcObjLocation, UINT param_pcObjectID);
	// Function to get total number of Analog and digital Output channels attached
	UINT GetObjectOutputCount(UINT param_pcObjLocation, UINT param_pcObjectID);
	// To get the Class Controlling the Behavior of particular type of control object
	CString GetObjControllerClass(UINT param_pcObjLocation, UINT param_pcObjectID);
	//To get Output status Text for the control object
	CString GetObjStatusTextOut(UINT param_pcObjLocation, UINT param_pcObjectID);
	// To get the Wago Unit number for INPUT channels (DIGITAL/ANALOG)to which the Wago Unit the object is attached
	UINT GetObjectInputWagoUint(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID);
	// To get the Wago Unit number for OUTPUT channels (DIGITAL/ANALOG)to which the Wago Unit the object is attached
	UINT GetObjectOutputWagoUint(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID);
	// To get the Invert value for mapping for first digital Output
	bool GetOutputInvert(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID);
	// To get the Input invert value for first digital input
	bool GetInputInvert(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID);


	// To get the Status Text Of First Input
	CString GetStatusTextInput(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID, int SubIndex2=-1);
	// To get the Status test for status of Output 1
	CString GetOutputStatusText(UINT param_pcObjLocation, UINT param_pcObjectID);
	// To get the channel number of first Input channel
	UINT GetInputChannel(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID, int *pRegBit=NULL);
	// To get the channel number of first Output channel
	UINT GetOutputChannel(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID, int *pRegBit=NULL);
	// To get the Color in which status 1 to be displayed
	CString GetStatusColor(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID, int SubIndex2=-1);
	// To get The Pluse of first Output
	UINT GetOutputPluse(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID);
	// To get The extra Function
	UINT GetOutputFunction(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID);
	// To get the type of connection for first Input Connection (Analog/Digital)
	UINT GetInputConnType(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID);
	// To get the type of connection for first Input Connection (Analog/Digital)
	UINT GetOutputConnType(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID);
	// To get the unit to display in case of analog card
	CString GetObjAnalogUnit(IN UINT param_pcObjLocation,UINT param_pcObjectID,UINT param_uiID);
	// Functiont o get the Step size for analog control
	UINT GetAnalogObjSteps(IN UINT param_pcObjLocation,UINT param_pcObjectID,UINT param_uiID);
	// To get the minimum value for Analog device
	UINT GetAnalogObjMinValue(IN UINT param_pcObjLocation,UINT param_pcObjectID,UINT param_uiID);
	// Function to return the max value for analog control
	UINT GetAnalogObjMaxValue(IN UINT param_pcObjLocation,UINT param_pcObjectID,UINT param_uiID);
	// To get total number of buttons
	UINT GetButtonCount(UINT param_pcObjLocation, UINT param_pcObjectID);
	// To get the Text of the particular button for which ID is provided
	CString GetButtonText(IN UINT param_pcObjLocation,UINT param_pcObjectID,UINT param_uiID);
	// Function returning min value for the Analog Inout Object
	UINT GetAnalogIObjMinValue(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID);
	// To get total number of spins
	UINT GetObjSpinCount(UINT param_pcObjLocation, UINT param_pcObjectID);
	// Function returning max value for the Analog Inout Object
	UINT GetAnalogIObjMaxValue(UINT param_pcObjLocation, UINT param_pcObjectID,UINT param_uiID);
	// To Get the count of total number of status text
	UINT GetInputStatusTextCount(UINT param_pcObjLocation, UINT param_pcObjectID);
	// To Get the count of total number of sub status text and color
	UINT CObjectDetails::GetSubStatusCount(UINT param_pcObjLocation, UINT param_pcObjectID);

	UINT GetAnalogIObjSteps(IN UINT param_pcObjLocation,UINT param_pcObjectID,UINT param_uiID);

	// To get the timeout of object
	long GetObjectTimeout(IN UINT param_pcObjLocation,UINT param_pcObjectID);

	// to get the channel number and the data block to add the calibration data to it
	UINT GetChannelData(UINT param_uintChannelNumber);

	//Get Percentage to stop for the throttle valve
	int GetPercentagetoStop(IN UINT param_pcObjLocation,UINT param_pcObjectID);
	//Get time between pulses for the throttle valve
	long GetTimeBetweenPulses(IN UINT param_pcObjLocation,UINT param_pcObjectID);

	//typedef struct CalibrateData{
	//	CString ObjectName;
	//	CString TankName;
	//	CString UnitType;
	//	CString Channel;
	//	CString Type;
	//	CString StartText;
	//	CString StopText;
	//
	//}CalibrateData;

	//typedef vector <CalibrateData> CalibrateDataList;
	//// to return object name and channels in a vector
	//
	//CalibrateDataList m_CalibrateData;
	//// to get calibration window data
	//void GetCalibrationData(void);
	//// to assign calibration data
	//CalibrateData m_CData;
	// to get object type
	CString ReadWagoUnitType(UINT param_pcObjLocation, UINT param_pcObjectID);
	CString ReadWagoUnitType(CString param_strObjName);

	int GetTotalInputCount(UINT param_pcObjLocation, UINT param_pcObjectID);
	int GetTotalOutputCount(UINT param_pcObjLocation, UINT param_pcObjectID);

	CString GetWagoInputChannel(UINT param_pcObjLocation, UINT param_pcObjectID, int Index);
	CString GetWagoOutputChannel(UINT param_pcObjLocation, UINT param_pcObjectID, int Index);

	CString GetObjectInputType(UINT param_pcObjLocation, UINT param_pcObjectID, int Index);
	CString GetObjectOutputType(UINT param_pcObjLocation, UINT param_pcObjectID, int Index);

	CString GetObjectInputWagoUnitNumber(UINT param_pcObjLocation, UINT param_pcObjectID, int Index);
	CString GetObjectOutputWagoUnitNumber(UINT param_pcObjLocation, UINT param_pcObjectID, int Index);

	//Get Emergency button action
	CString GetEmgAction(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiButtonIndex);

    UINT GetObjectStopCount(UINT param_pcObjLocation, UINT param_pcObjID);
    UINT GetObjectMinStop(UINT param_pcObjLocation, UINT param_pcObjID, int Index=-1);
	UINT GetObjectMaxStop(UINT param_pcObjLocation, UINT param_pcObjID, int Index=-1);

	UINT GetObjectStatusOr(UINT param_pcObjLocation, UINT param_pcObjID, int Index);
	UINT GetObjectStatusOrNot(UINT param_pcObjLocation, UINT param_pcObjID, int Index);
	UINT GetObjectStatusAnd(UINT param_pcObjLocation, UINT param_pcObjID, int Index);
	UINT GetObjectStatusAndNot(UINT param_pcObjLocation, UINT param_pcObjID, int Index);
	bool GetPassword(UINT param_pcObjLocation, UINT param_pcObjID);
};
