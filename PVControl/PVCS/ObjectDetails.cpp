#include "StdAfx.h"
#include ".\objectdetails.h"
#include <vector>

CObjectDetails::CObjectDetails(void) {

}

CObjectDetails::~CObjectDetails(void) {

}

// function to read the node and return data accordingly for all tags in the node
CString CObjectDetails::GetNodeData(IN CString param_pcObjLocation, IN CString param_pcObjID, IN CString param_pcTagName) {

	MSXML2::IXMLDOMNodeListPtr pNodeList;
	MSXML2::IXMLDOMNodePtr     pTempChild;
	MSXML2::IXMLDOMNodePtr     pTempChildVal;
	MSXML2::IXMLDOMElementPtr  pTempElement;
	_bstr_t                    strLegendIndex(CStrToBstr(param_pcObjID), FALSE);
	_bstr_t                    strLegendSubIndex(CStrToBstr(param_pcObjLocation), FALSE);
	BSTR                       TagNames;
	CString                    pcRetValue;

	TagNames = _com_util::ConvertStringToBSTR(param_pcTagName);


	pNodeList = GetNode("ObjectDetail");
	//int  ii = pNodeList->length;

	for (int j = 0; j < pNodeList->length; j++) {
		pNodeList->get_item(j, &pTempChild);


		pTempChildVal = pTempChild->selectSingleNode("ObjectLocation");
		if (pTempChildVal == NULL) {
			::SysFreeString(TagNames);
			::SysFreeString(strLegendSubIndex);
			::SysFreeString(strLegendIndex);
			return " ";
		} else {
			pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
			if (!strcmp(pcRetValue, strLegendSubIndex)) {
				//
				pTempChildVal = pTempChild->selectSingleNode("ObjectID");
				if (pTempChildVal == NULL) {
					::SysFreeString(TagNames);
					::SysFreeString(strLegendSubIndex);
					::SysFreeString(strLegendIndex);
					return " ";
				} else {
					pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
					if (!strcmp(pcRetValue, strLegendIndex)) {
						//
						pTempChildVal = pTempChild->selectSingleNode(TagNames);
						if (pTempChildVal == NULL) {
							::SysFreeString(strLegendIndex);
							::SysFreeString(strLegendSubIndex);
							::SysFreeString(TagNames);
							return " ";
						}
						pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
						::SysFreeString(strLegendIndex);
						::SysFreeString(strLegendSubIndex);
						::SysFreeString(TagNames);
						return pcRetValue;
					}
				}
			}
		}

	}
	::SysFreeString(TagNames);
	::SysFreeString(strLegendIndex);
	::SysFreeString(strLegendSubIndex);
	return " ";
}


// Function to return the Input Channel No on which Control Object is Connected
CString CObjectDetails::GetInputChannel(IN CString param_pcObjLocation, IN CString param_pcObjectID) {
	CString pcRetValue;
	pcRetValue = GetNodeData(param_pcObjLocation, param_pcObjectID, "WagoInputChannelNumber");
	return pcRetValue;
}


// Function to get the Output Connection type of Object Analog or Digital type
unsigned int CObjectDetails::GetOutputType(IN CString param_pcObjLocation, IN CString param_pcObjectID) {
	CString      pcRetValue;
	unsigned int iObjType   = INP_UNDEF;
	pcRetValue = GetNodeData(param_pcObjLocation, param_pcObjectID, "OOutputType");
	if (!strcmp(pcRetValue, "Digital")) {
		iObjType = INP_DIGITAL;
	} else if (!strcmp(pcRetValue, "DigReg")) {
		iObjType = INP_DIG_REG;
	} else if (!strcmp(pcRetValue, "Analog")) {
		iObjType = INP_ANALOG;
	} else {
		iObjType = INP_UNDEF;
	}

	return iObjType;
}

// Function to get the INput Channel type Analog or digital it
// returns 0 for digital 1 for analog and 2 for error or undefined type
unsigned int CObjectDetails::GetInputType(IN CString param_pcObjLocation, IN CString param_pcObjectID) {
	CString      pcRetValue;
	unsigned int iObjType   = INP_UNDEF;
	pcRetValue = GetNodeData(param_pcObjLocation, param_pcObjectID, "OInputType");
	if (!strcmp(pcRetValue, "Digital")) {
		iObjType = INP_DIGITAL;
	} else if (!strcmp(pcRetValue, "DigReg")) {
		iObjType = INP_DIG_REG;
	} else if (!strcmp(pcRetValue, "Analog")) {
		iObjType = INP_ANALOG;
	} else {
		iObjType = INP_UNDEF;
	}

	return iObjType;
}

// Function to get the OUTPUT channel number of the controlled object
CString CObjectDetails::GetOutputChannel(IN CString param_pcObjLocation, IN CString param_pcObjectID) {
	CString pcRetValue;
	pcRetValue = GetNodeData(param_pcObjLocation, param_pcObjectID, "WagoOutputChannelNumber");
	return pcRetValue;
}


// To get the type of Object Controlled or not-controlled it returns 0 for controlled 1 for not controlled and 2 for other or undefined type
unsigned int CObjectDetails::GetObjectType(IN CString param_pcObjLocation, CString param_pcObjectID) {

	return atoi(GetNodeData(param_pcObjLocation, param_pcObjectID, "Objecttype"));
}

// To get the name of the Object
CString CObjectDetails::GetObjectName(CString param_pcObjLocation, CString param_pcObjectID) {
	return  GetNodeData(param_pcObjLocation, param_pcObjectID, "ONAME");
}

// To get the status text to show
CString CObjectDetails::GetStatusText(IN UINT param_pcObjLocation, UINT param_pcObjectID, unsigned int param_uiStatus) {

	CString strFormat;
	strFormat.Format("ObjInputStatusText%d", param_uiStatus);
	return  GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
}

// To get the minimum value for Analog device
UINT CObjectDetails::GetMinValue(IN UINT param_pcObjLocation, UINT param_pcObjectID) {
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "minval"));
}

// Function to return the max value for analog control
UINT CObjectDetails::GetMaxValue(IN UINT param_pcObjLocation, UINT param_pcObjectID) {
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "maxval"));
}

// Functiont o get the Step size for analog control
UINT CObjectDetails::GetSteps(IN UINT param_pcObjLocation, UINT param_pcObjectID) {
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "step"));
}

// To get the unit to display in case of analog card
CString CObjectDetails::GetAnalogUnit(IN UINT param_pcObjLocation, UINT param_pcObjectID) {
	//CString strFormat;
	//strFormat.Format("analogunit%d",param_uiID);
	return  GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "analogunit");
}

// to locate a tank and return true if it existes else return false
bool CObjectDetails::LocateTank(UINT param_pcObjLocation, UINT param_pcObjectID)
{	
	CString pcRetVal = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "ObjectLocation");
	if (pcRetVal == " ") return false;
	else return true;
}

// To the Tooltip Reference from the file
CString CObjectDetails::GetToolTipRef(IN UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString pcRetVal = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "ToolTipRef");
	if (pcRetVal == " ") return "";
	else return pcRetVal;
}

// To get the tool tip text to be displayed
CString CObjectDetails::GetToolTipText(IN UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString pcRetVal = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "ToolTipText");
	if (pcRetVal == " ") return "";
	else return pcRetVal;
}

// To get the number of total input digital and analog attached to a object
UINT CObjectDetails::GetObjectInputCount(UINT param_pcObjLocation, UINT param_pcObjectID) {
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "ObjectTotalInput"));
}

// Function to get total number of Analog and digital Output channels attached
UINT CObjectDetails::GetObjectOutputCount(UINT param_pcObjLocation, UINT param_pcObjectID) {
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "ObjectTotalOutput"));
}

// To get the Class Controlling the Behavior of particular type of control object
CString CObjectDetails::GetObjControllerClass(UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString pcRetVal = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "ControllerClass");
	if (pcRetVal == " ") return "";
	else return pcRetVal;
}

//To get Output status Text for the control object
CString CObjectDetails::GetObjStatusTextOut(UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString pcRetVal = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "ObjectStatusTextOut");
	if (pcRetVal == " ") return "NO TEXT";
	else return pcRetVal;
}

// To get the Wago Unit number to which the Wago Unit the object is attached
UINT CObjectDetails::GetObjectInputWagoUint(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("ObjectInput%dWagoUnit", param_uiID);
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}

// To get the Wago Unit number to which the Wago Unit the object is attached
UINT CObjectDetails::GetObjectOutputWagoUint(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("ObjectOutput%dWagoUnit", param_uiID);
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}

// To get the Invert value for mapping
bool CObjectDetails::GetOutputInvert(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("ObjOutput%dInvert", param_uiID);
	CString pcRetVal = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	if (pcRetVal == "YES") return true;
	else return false;
}
// To get the Input invert value
bool CObjectDetails::GetInputInvert(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("ObjInput%dInvert", param_uiID);
	CString pcRetVal = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	if (pcRetVal == "YES") return true;
	else return false;
}


// To get the Status Text Of all Inputs
CString CObjectDetails::GetStatusTextInput(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID, int SubIndex2) {
	CString strFormat;
	if (SubIndex2 == -1) {
		strFormat.Format("ObjInputStatusText%d", param_uiID);
	} else {
		strFormat.Format("ObjSubStatus%dText%d", param_uiID, SubIndex2);
	}
	CString pcRetVal = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	if (pcRetVal == " ") return "";
	else return pcRetVal;
}

// To get the Status test for status of Output 1
CString CObjectDetails::GetOutputStatusText(UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString strFormat;
	strFormat.Format("ObjOutputStatusText");
	CString pcRetVal = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	if (pcRetVal == " ") return "";
	else return pcRetVal;
}


// To get the channel number of first Input channel
UINT CObjectDetails::GetInputChannel(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID, int *pRegBit) {
	CString strFormat;
	strFormat.Format("WagoInputChannelNumber%d", param_uiID);
	CString tmpStr = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	int tmpChannel =atoi(tmpStr);
	if (pRegBit) {
		int Pos = tmpStr.Find('.');
		if ( Pos != -1 ){
			tmpStr = tmpStr.Right(tmpStr.GetLength() - Pos-1 );
			* pRegBit = atoi(tmpStr);
		}
	}
	return tmpChannel;
}

// To get the channel number of first Output channel
UINT CObjectDetails::GetOutputChannel(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID, int *pRegBit) {
	CString strFormat;
	strFormat.Format("WagoOutputChannelNumber%d", param_uiID);
	CString tmpStr = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	int tmpChannel =atoi(tmpStr);
	if (pRegBit) {
		int Pos = tmpStr.Find('.');
		if ( Pos != -1 ){
			tmpStr = tmpStr.Right(tmpStr.GetLength() - Pos-1 );
			* pRegBit = atoi(tmpStr);
		}
	}
	return tmpChannel;
}

// To get the Color in which status 1 to be displayed
CString CObjectDetails::GetStatusColor(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID, int SubIndex2) {
	CString pcRetValue;
	CString strFormat;
	if (SubIndex2 == -1) {
		strFormat.Format("ObjStatusColor%d", param_uiID);
	} else {
		strFormat.Format("ObjSubStatus%dColor%d", param_uiID, SubIndex2);
	}
	pcRetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	return pcRetValue;
}

// To get The Pluse of first Output
UINT CObjectDetails::GetOutputPluse(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("ObjOutputPulse%d", param_uiID);
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}

// To get The extra function
UINT CObjectDetails::GetOutputFunction(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("ObjOutputFunction%d", param_uiID);
	CString pcRetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	if (pcRetValue == " ") {
		return -1;
	}
	return atoi(pcRetValue);
}



// To get the type of connection for first Input Connection (Analog/Digital)
UINT CObjectDetails::GetInputConnType(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	unsigned int iObjType   = INP_UNDEF;
	CString      strFormat;
	strFormat.Format("OInput%dType", param_uiID);
	CString pcRetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	if (!strcmp(pcRetValue, "Digital")) {
		iObjType = INP_DIGITAL;
	} else if (!strcmp(pcRetValue, "DigReg")) {
		iObjType = INP_DIG_REG;
	} else if (!strcmp(pcRetValue, "Analog")) {
		iObjType = INP_ANALOG;
	} else {
		iObjType = INP_UNDEF;
	}

	return iObjType;
}

// To get the type of connection for Third Input Connection (Analog/Digital)
UINT CObjectDetails::GetOutputConnType(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString      pcRetValue;
	unsigned int iObjType   = INP_UNDEF;
	CString      strFormat;
	strFormat.Format("OOutput%dType", param_uiID);
	pcRetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
	if (!strcmp(pcRetValue, "Digital")) {
		iObjType = INP_DIGITAL;
	} else if (!strcmp(pcRetValue, "DigReg")) {
		iObjType = INP_DIG_REG;
	} else if (!strcmp(pcRetValue, "Analog")) {
		iObjType = INP_ANALOG;
	} else {
		iObjType = INP_UNDEF;
	}


	return iObjType;
}

// To get the unit to display in case of analog card
CString CObjectDetails::GetObjAnalogUnit(IN UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("Obj%dAnalogUnit", param_uiID);
	return  GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
}

// Function to get the Step size for analog control
UINT CObjectDetails::GetAnalogObjSteps(IN UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("AnalogObj%dStep", param_uiID);
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}
// To get the minimum value for Analog device
UINT CObjectDetails::GetAnalogObjMinValue(IN UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("Obj%dminval", param_uiID);
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}

// Function to return the max value for analog control
UINT CObjectDetails::GetAnalogObjMaxValue(IN UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("Obj%dmaxval", param_uiID);
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}

// To get total number of buttons
UINT CObjectDetails::GetButtonCount(UINT param_pcObjLocation, UINT param_pcObjectID) {
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "ObjButtonCount"));
}

// To get the Text of the particular button for which ID is provided
CString CObjectDetails::GetButtonText(IN UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("ObjButtonText%d", param_uiID);
	return  GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
}

// To get total number of Spins
UINT CObjectDetails::GetObjSpinCount(UINT param_pcObjLocation, UINT param_pcObjectID) {
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "ObjSpinCount"));
}
// Function returning min value for the Analog Inout Object
UINT CObjectDetails::GetAnalogIObjMinValue(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("IObj%dminval", param_uiID);
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}

// Function returning max value for the Analog Inout Object
UINT CObjectDetails::GetAnalogIObjMaxValue(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("IObj%dmaxval", param_uiID);
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}

// To Get the count of total number of status text
UINT CObjectDetails::GetInputStatusTextCount(UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString strFormat;
	strFormat.Format("ObjIStatusTextCount");
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}

// To Get the count of total number of sub status text and color
UINT CObjectDetails::GetSubStatusCount(UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString strFormat;
	strFormat.Format("ObjSubStatusCount");
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}


// Function to get the Step size for analog control
UINT CObjectDetails::GetAnalogIObjSteps(IN UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiID) {
	CString strFormat;
	strFormat.Format("AnalogIObj%dStep", param_uiID);
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}

// To get the timeout of object
long CObjectDetails::GetObjectTimeout(IN UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString strFormat;
	strFormat.Format("ObjTimeout");
	return  atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat));
}


// . to get time between pulses for the throttle valve
long CObjectDetails::GetTimeBetweenPulses(IN UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString strTimeBetweenPulses = "";
	strTimeBetweenPulses = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "TimeBetweenPulses");
	if (strTimeBetweenPulses == " ") return (1000);
	else return atoi(strTimeBetweenPulses);
}

// . to get percentage to stop for the throttle valve
int CObjectDetails::GetPercentagetoStop(IN UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString strPercentagetoStop = "";
	strPercentagetoStop = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "PercentageToStop");
	if (strPercentagetoStop == " ") return (5);
	else return atoi(strPercentagetoStop);
}



// to get object type
CString CObjectDetails::ReadWagoUnitType(UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString strFormat;
	strFormat.Format("ObjectWagoUnit");
	return  GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strFormat);
}

CString CObjectDetails::ReadWagoUnitType(CString param_strObjName) {
	return CString();
}
int CObjectDetails::GetTotalInputCount(UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString RetValueFormat = "ObjectTotalInput";
	CString RetValue       = "";
	RetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), RetValueFormat);
	if (RetValue == " ") return 0;
	else return atoi(RetValue);
}

int CObjectDetails::GetTotalOutputCount(UINT param_pcObjLocation, UINT param_pcObjectID) {
	CString RetValueFormat = "ObjectTotalOutput";
	CString RetValue       = "";
	RetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), RetValueFormat);
	if (RetValue == " ") return 0;
	else return atoi(RetValue);
}

CString CObjectDetails::GetWagoInputChannel(UINT param_pcObjLocation, UINT param_pcObjectID, int Index) {
	CString RetValueFormat = "";
	RetValueFormat.Format("WagoInputChannelNumber%d", Index);
	CString RetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), RetValueFormat);
	if (RetValue == " ") return " ";
	else return RetValue;
}

CString CObjectDetails::GetWagoOutputChannel(UINT param_pcObjLocation, UINT param_pcObjectID, int Index) {
	CString RetValueFormat = "";
	RetValueFormat.Format("WagoOutputChannelNumber%d", Index);
	CString RetValue = " ";
	RetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), RetValueFormat);
	if (RetValue == " ") return " ";
	else return RetValue;
}

CString CObjectDetails::GetObjectInputType(UINT param_pcObjLocation, UINT param_pcObjectID, int Index) {
	CString RetValueFormat = "";
	RetValueFormat.Format("OInput%dType", Index);
	CString RetValue = "";
	RetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), RetValueFormat);
	if (RetValue == " ") return " ";
	else return RetValue;
}

CString CObjectDetails::GetObjectOutputType(UINT param_pcObjLocation, UINT param_pcObjectID, int Index) {
	CString RetValueFormat = "";
	RetValueFormat.Format("OOutput%dType", Index);
	CString RetValue = "";
	RetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), RetValueFormat);
	if (RetValue == " ") return " ";
	else return RetValue;
}

CString CObjectDetails::GetObjectInputWagoUnitNumber(UINT param_pcObjLocation, UINT param_pcObjectID, int Index) {
	CString RetValueFormat = "";
	RetValueFormat.Format("ObjectInput%dWagoUnit", Index);
	CString RetValue = "";
	RetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), RetValueFormat);
	if (RetValue == " ") return " ";
	else return RetValue;
}

CString CObjectDetails::GetObjectOutputWagoUnitNumber(UINT param_pcObjLocation, UINT param_pcObjectID, int Index) {
	CString RetValueFormat = "";
	RetValueFormat.Format("ObjectOutput%dWagoUnit", Index);
	CString RetValue = "";
	RetValue = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), RetValueFormat);
	if (RetValue == " ") return " ";
	else return RetValue;

}

//Get emergency button action
CString CObjectDetails::GetEmgAction(UINT param_pcObjLocation, UINT param_pcObjectID, UINT param_uiButtonIndex) {
	CString pcRetData  = "";
	CString strTagName = "";
	strTagName.Format("ObjEmgAction%d", param_uiButtonIndex);
	pcRetData = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), strTagName);
	if (pcRetData == " ") return "";
	else return pcRetData;
}

UINT CObjectDetails::GetObjectStopCount(UINT param_pcObjLocation, UINT param_pcObjID) {
	CString pcRetData  = "";
	CString strTagName = "ObjStopCount";
	pcRetData = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjID), strTagName);
	if (pcRetData == " ") return 0;
	else return atoi(pcRetData);
}

UINT CObjectDetails::GetObjectMinStop(UINT param_pcObjLocation, UINT param_pcObjID, int Index) {
	if (Index >= 0) {
		CString strTagName;
		strTagName.Format("Obj%dMinStop", Index);
		CString pcRetData = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjID), strTagName);
		if (pcRetData == " ") return 0;
		else return atoi(pcRetData);
	} else {
		CString strTagName = "ObjMinStop";
		CString pcRetData = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjID), strTagName);
		if (pcRetData == " ") return 0;
		else return atoi(pcRetData);
	}
}

UINT CObjectDetails::GetObjectMaxStop(UINT param_pcObjLocation, UINT param_pcObjID, int Index) {
	if (Index >= 0) {
		CString strTagName;
		strTagName.Format("Obj%dMaxStop", Index);
		CString pcRetData = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjID), strTagName);
		if (pcRetData == " ") return 100;
		else return atoi(pcRetData);
	} else {
		CString strTagName = "ObjMaxStop";
		CString pcRetData = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjID), strTagName);
		if (pcRetData == " ") return 100;
		else return atoi(pcRetData);
	}

}

UINT CObjectDetails::GetObjectStatusOr(UINT param_pcObjLocation, UINT param_pcObjID, int Index) {
	CString strTagName;
	strTagName.Format("ObjStatusOr%d", Index);
	CString pcRetData  = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjID), strTagName);
	if (pcRetData == " ") {
		return 0;
	} else {
		char *EndPtr;
		UINT Value   = strtol(pcRetData.GetBuffer(), &EndPtr, 0);
		return Value;
	}
}
UINT CObjectDetails::GetObjectStatusOrNot(UINT param_pcObjLocation, UINT param_pcObjID, int Index) {
	CString strTagName;
	strTagName.Format("ObjStatusOrNot%d", Index);
	CString pcRetData  = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjID), strTagName);
	if (pcRetData == " ") {
		return 0;
	} else {
		char *EndPtr;
		UINT Value   = strtol(pcRetData.GetBuffer(), &EndPtr, 0);
		return Value;
	}
}

UINT CObjectDetails::GetObjectStatusAnd(UINT param_pcObjLocation, UINT param_pcObjID, int Index) {
	CString strTagName;
	strTagName.Format("ObjStatusAnd%d", Index);
	CString pcRetData  = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjID), strTagName);
	if (pcRetData == " ") {
		return 0;
	} else {
		char *EndPtr;
		UINT Value   = strtol(pcRetData.GetBuffer(), &EndPtr, 0);
		return Value;
	}
}

UINT CObjectDetails::GetObjectStatusAndNot(UINT param_pcObjLocation, UINT param_pcObjID, int Index) {
	CString strTagName;
	strTagName.Format("ObjStatusAndNot%d", Index);
	CString pcRetData  = GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjID), strTagName);
	if (pcRetData == " ") {
		return 0;
	} else {
		char *EndPtr;
		UINT Value   = strtol(pcRetData.GetBuffer(), &EndPtr, 0);
		return Value;
	}
}

// To get The Password
bool CObjectDetails::GetPassword(UINT param_pcObjLocation, UINT param_pcObjectID) {
	return  (atoi(GetNodeData(IntToCStr(param_pcObjLocation), IntToCStr(param_pcObjectID), "Password")) > 0 ? true : false);
}

