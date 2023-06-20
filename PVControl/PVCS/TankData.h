#pragma once
#include "readxmltagnode.h"
#include <vector>

////////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////
class CTankData :
	public CReadXMLTagNode
{
private:
	// Function to assign values to the variables that hold tanker data
	CString AssignSensorData(MSXML2::IXMLDOMNodePtr param_pTempChild, CString param_pcTagName);
	// Function to assign the Values to the Class variales that hold data for each tank
	bool SetTankSensorData(IN MSXML2::IXMLDOMNodePtr param_pTempChild);
	// Global variable
	CRITICAL_SECTION CriticalSection;

public:
	CTankData(void);
	virtual ~CTankData(void);
	// Function to Get the Data of sensors for individual tank and assign it to the  Class Variables
	bool GetTankSensorsData(IN unsigned int param_uiTankNumber,IN CString param_strTankType);

	//Variables that HOLD TANK DATA
	// To store ULLAGE
	CString Ullage;
	// To store LEVEL
	CString Level;
	// TO return Volume Percentage
	CString VolumePercentage;
	// To return The Volume
	CString Volume;
	// TO get the Tanks Weight
	CString Weight;
	// To get The Tank Temperature
	CString Temperature;
	// To get The Tank Pressure
	CString TankPressure;
	// To get The Tanks Line Pressure
	CString LinePressure;
	// To get The Tank Cargo Type
	CString CargoType;
	// To get The Tanks Cargo  Color
	CString CargoColor;
	// To get The Tanks Load Rate
	CString LoadRate;
	// To get the Tanks alarm status
	CString Alarmstatus;
	// To store the Alarm text
	CString AlarmText;
	// ALARM NEW
	CString AlarmData;
	// To get the Count of total number of packets
	int GetCount(void);
	// To get the TagID of specific packet
	int GetTagID(unsigned int param_uiPacketNo);
	// Function to get the Free Values
	bool GetFreeValue(UINT param_uiTankNumber, CString param_strFreeValType, UINT param_uiValueKey=0);
	// To assign the free value data to the members varible to be accessed outside the class
	bool SetFreeValueData(MSXML2::IXMLDOMNodePtr param_pTempChild);
	// To assign free value data to the variable
	CString AssignFreeValue(MSXML2::IXMLDOMNodePtr param_pTempChild, CString param_pcTagName);
	CString m_strFreeValue;
	int m_AlarmState;
	// To get Alarm Data
	bool GetAlarmData(void);

	vector <CString> m_strAlarmData;
	vector <CString> m_strAckAlarmData;
	static CString m_AlarmStatus;
	CString m_AlarmCount;
	static bool AlarmListDraw;

	// To Get The ALarm Status
	CString GetAlarmStatus(void);
};
