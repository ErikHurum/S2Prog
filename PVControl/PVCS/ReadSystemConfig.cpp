#include "StdAfx.h"

#include ".\readsystemconfig.h"
#include ".\convertdata.h"
CReadSystemConfig::CReadSystemConfig(void) {
}

CReadSystemConfig::~CReadSystemConfig(void) {
}

// Function returns the SURVEYOR IP from The Config file
CString CReadSystemConfig::GetSurveyorIP(void) {
    CString pcRetData;
    pcRetData = GetTagData("SURVEYORIP");
    return pcRetData;
}



// Function to get the Data By tag Name and return the Node TEXT
CString CReadSystemConfig::GetTagData(IN CString param_pcTagName) {
    static CString pcRetValue;

    for (MSXML2::IXMLDOMNodePtr m_pNodeList = m_pDocRoot->firstChild; m_pNodeList != NULL; m_pNodeList = m_pNodeList->nextSibling) {
        if (!strcmp(m_pNodeList->nodeName, param_pcTagName)) {
            pcRetValue.Format(_T("%s"), (LPCTSTR)m_pNodeList->text);
            return pcRetValue;
        } else {
            pcRetValue = "";
        }
    }
    return pcRetValue;
}

// To get The IP of WAGO Control UNIT
CString CReadSystemConfig::GetControlUnitIP(void) {
    CString pcRetData;
    pcRetData = GetTagData("WagoIP");
    return pcRetData;
}

// To get the path where DXF are stored
CString CReadSystemConfig::GetDXFPath(void) {
    CString pcRetData;
    pcRetData = GetTagData("dxfpath");
    return pcRetData;
}

// To get the Port number on which connection with Surveyor is established
unsigned int CReadSystemConfig::GetConnectionPort(void) {
    CString pcRetData;
    pcRetData = GetTagData("Porttouse");
    return atoi(pcRetData);
}

// To give the name of the dxf configutaion file
CString CReadSystemConfig::GetdxfFile(void) {
    CString pcRetData;
    pcRetData = GetTagData("dxffileconfig");
    return pcRetData;
}

// To read the detail confiuration file name from main config file
CString CReadSystemConfig::GetDetailConfFile(void) {
    CString pcRetData;
    pcRetData = GetTagData("objectdetailfile");
    return pcRetData;
}

// to get Total Number of Wago Units Connected
UINT CReadSystemConfig::GetWagoUnitCount(void) {
    CString pcRetData;
    pcRetData = GetTagData("TotalWagoUnit");
    return atoi(pcRetData);
}

// To get IP address of the particular  Wago Unit
CString CReadSystemConfig::GetWagoIP(UINT param_uiWagoUnitNo) {
    CString pcRetData;
    CString strname;
    strname.Format("WagoUnitIP%d", param_uiWagoUnitNo);
    pcRetData = GetTagData(strname);
    return pcRetData;
}
// To get IP address of the particular  Wago Unit
CString CReadSystemConfig::GetWagoFirstIP(UINT param_uiWagoOne) {
    CString pcRetData;
    CString strname;
    strname.Format("WagoUnitIP%d0", param_uiWagoOne);
    pcRetData = GetTagData(strname);
    return pcRetData;
}
// to get secondary or back up IP of the ethernet on wago port
CString CReadSystemConfig::GetWagoSecondIP(UINT param_uiWagoTwo) {
    CString pcRetData;
    CString strname;
    strname.Format("WagoUnitIP%d1", param_uiWagoTwo);
    pcRetData = GetTagData(strname);
    return pcRetData;
}

// Is this a Wago module???
int CReadSystemConfig::GetIsModbusDeviceType(UINT param_uiWagoUnitNo) {
    CString strTagName;
    strTagName.Format("ModbusDeviceType%d", param_uiWagoUnitNo);
    CString pcRetData = GetTagData(strTagName);
	int DeviceType = MODBUS_DEVICE_WAGO;  // Default
    if (!pcRetData.IsEmpty()) {
		if (pcRetData == "WAGO") {
			DeviceType = MODBUS_DEVICE_WAGO;
		}
		if (pcRetData == "WÄRTSILA") {
			DeviceType = MODBUS_DEVICE_WÄRTSILA;
		}
	}
	return DeviceType;
}

// To Read the name of file in which object changes are to be logged
CString CReadSystemConfig::GetLogFileName(void) {
    CString pcRetData = GetTagData("ObjChangeLogFile");
    if (pcRetData == "") {
        pcRetData = "defaultlog.xml";
    }
    return pcRetData;
}

// To get the value of command to see if the PVCS is working in command mode or not
CString CReadSystemConfig::GetMasterIP(void) {
    CString pcRetData = GetTagData("MasterIP");
    return pcRetData;
}

// To get the configuration file version
CString CReadSystemConfig::GetConfigDataVersion(void) {
    CString pcRetData = GetTagData("FileVersion");
    if (pcRetData == "") {
        pcRetData = "0.0";
    }
    return pcRetData;

}

//to get no of screen count
int CReadSystemConfig::GetScreenCount(void) {
    CString ScreenCount = GetTagData("ScreenCount");
    if (ScreenCount.IsEmpty()) {
        return -1;
    } else {
        return atoi(ScreenCount);
    }
}
//to get splitscreen
int CReadSystemConfig::GetSplitScreens(void) {
    CString SplitScreens = GetTagData("SplitScreens");
    if (SplitScreens.IsEmpty()) {
        return 2;
    } else {
        return atoi(SplitScreens);
    }
}
//to get splitscreen
bool CReadSystemConfig::GetZoomEnabled(void) {
    CString ZoomEnabled = GetTagData("Zoom");
    if (ZoomEnabled.IsEmpty()) {
        return false;
    } else {
        return ((atoi(ZoomEnabled) > 0) ? true : false);
    }
}
//Get X-scale
double CReadSystemConfig::GetScaleX(void) {
    CString ScaleX = GetTagData("ScaleX");
    if (ScaleX.IsEmpty()) {
        return 1.0;
    } else {
        return atof(ScaleX);
    }
}

//Get Y-scale
double CReadSystemConfig::GetScaleY(void) {
    CString ScaleY = GetTagData("ScaleY");
    if (ScaleY.IsEmpty()) {
        return 1.0;
    } else {
        return atof(ScaleY);
    }
}
//Get Y-scale
CString CReadSystemConfig::GetPassword(void) {
    CString PassWord = GetTagData("Password");
    if (PassWord.IsEmpty()) {
        return "1111";
    } else {
        return PassWord;
    }
}


//to get the Master port
int CReadSystemConfig::GetMasterPort(void) {
    CString strMasterPort;
    strMasterPort = GetTagData("MasterPort");
    if (strMasterPort.IsEmpty()) return 4000;
    else return atoi(strMasterPort);
}

//to get the request timeout
int CReadSystemConfig::GetRequestTimeOut(void) {
    CString strRequestTimeOut;
    strRequestTimeOut = GetTagData("RequestTimeOut");
    if (strRequestTimeOut.IsEmpty()) return 10;
    else return atoi(strRequestTimeOut);
}
//to get the backup state
bool CReadSystemConfig::GetBackupState(void) {
    CString strReturnVal;
    strReturnVal = GetTagData("BackupMode");

    if (strReturnVal.IsEmpty()) return false;
    else if (atoi(strReturnVal) == 0) return false;
    else if (atoi(strReturnVal) == 1) return true;
    else return false;
}
//to get the splash window state
bool CReadSystemConfig::GetSplashState(void) {
    CString strReturnVal;
    strReturnVal = GetTagData("SplashScreen");

    if (strReturnVal.IsEmpty()) return false;
    else if (atoi(strReturnVal) == 0) return false;
    else if (atoi(strReturnVal) == 1) return true;
    else return false;
}

// To get the channel no to which the emg button is connected
int CReadSystemConfig::GetWagoInputEmgChNo(UINT param_uiChannelNo) {
    CString pcRetData;
    CString strname;
    strname.Format("WagoInputEmgChNo%d", param_uiChannelNo);
    pcRetData = GetTagData(strname);
    if (pcRetData.IsEmpty()) return -1;
    else return atoi(pcRetData);
}

// To get the input type, analog/digital for the emg button connected
UINT CReadSystemConfig::GetEmgObjInputType(UINT param_uiChannelNo) {
    CString pcRetData;
    CString strname;
    unsigned iObjType = 0; // To maintain backward compatibility
    strname.Format("EmgInputType%d", param_uiChannelNo);
    pcRetData = GetTagData(strname);
    if (!strcmp(pcRetData, "Digital")) {
        iObjType = 0;
    } else if (!strcmp(pcRetData, "Analog")) {
        iObjType = 1;
    }
    return iObjType;
}

// To get the input threshold for active button
double CReadSystemConfig::GetEmgObjInputThreshold(UINT param_uiChannelNo) {
    CString strname;
    strname.Format("EmgInputThreshold%d", param_uiChannelNo);
    CString pcRetData = GetTagData(strname);
    if (pcRetData.IsEmpty()) return 1.0;
	
	double RetVal = atof((LPCSTR)pcRetData);
	return RetVal;
}


// To get that the input to channel no is inverted or not
bool CReadSystemConfig::GetEmgObjInputInvert(UINT param_uiChannelNo) {
    CString pcRetVal;
    CString strFormat;
    strFormat.Format("ObjInput%dInvert", param_uiChannelNo);
    pcRetVal = GetTagData(strFormat);
    if (pcRetVal.IsEmpty()) return false;
    else {
        if (pcRetVal == "YES") return true;
        else return false;
    }
}

//Get Emergency button count
UINT CReadSystemConfig::GetEmgButtonCount(void) {
    CString pcRetData;
    pcRetData = GetTagData("EmgButtonCount");
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}

//Get Emergency button Text
CString CReadSystemConfig::GetEmgButtonText(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("EmgButText%d", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    return pcRetData;
}
//Get Emergency button Tooltip
CString CReadSystemConfig::GetEmgButtonToolTip(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("EmgButTooltip%d", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    return pcRetData;
}
//Get Emergency button wago unit no
int CReadSystemConfig::GetEmgWagoUnit(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("EmgButWagoUnit%d", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return -1;
    else return atoi(pcRetData);
}
//Get Emergency button State
int CReadSystemConfig::GetEmgButtonState(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("EmgButState%d", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}
//Get Emergency button additional functionality status
int CReadSystemConfig::GetEmgButtonResetAllStatus(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("EmgButResetAll%d", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}

//Get Emergency button additional functionality status
int CReadSystemConfig::GetEmgButRemoteControl(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("EmgButRemoteControl%d", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}


int CReadSystemConfig::GetInputStatusRangeStart(UINT param_uiWagoUnitNo) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("WagoUnitInpStatRangeStart%d", param_uiWagoUnitNo);
    pcRetData = GetTagData(strTagName);
    pcRetData = pcRetData.Mid(pcRetData.Find('-'));
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}
int CReadSystemConfig::GetInputStatusRangeEnd(UINT param_uiWagoUnitNo) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("WagoUnitInpStatRangeEnd%d", param_uiWagoUnitNo);
    pcRetData = GetTagData(strTagName);
    pcRetData = pcRetData.Mid(pcRetData.Find('-') + 1);
    if (pcRetData.IsEmpty()) return 0x200;
    else return atoi(pcRetData);
}

int CReadSystemConfig::GetInputStatusCommand(UINT param_uiWagoUnitNo) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("WagoUnitInpStatCmd%d", param_uiWagoUnitNo);
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return MODBUSTCP_TABLE_INPUT_COIL;
    else return atoi(pcRetData);
}


// To get the channel no to which the pump button is connected
int CReadSystemConfig::GetPumpButWagoInputChNo(UINT param_uiChannelNo, UINT param_uiID, int *pRegBit) {
    CString pcRetData;
    CString strname;
    strname.Format("PumpBut%dInput%dChNo", param_uiChannelNo, param_uiID);
    pcRetData = GetTagData(strname);
    if (pcRetData.IsEmpty()) return -1;

	int tmpChannel =atoi(pcRetData);
	if (pRegBit) {
	   * pRegBit = int((atof(pcRetData) - tmpChannel)*10+0.1);
	}
	return tmpChannel;
}

// To get the channel no to which the pump button is connected
int CReadSystemConfig::GetPumpButWagoOutputChNo(UINT param_uiChannelNo, UINT param_uiID, int *pRegBit) {
    CString pcRetData;
    CString strname;
    strname.Format("PumpBut%dOutput%dChNo", param_uiChannelNo,param_uiID);
    pcRetData = GetTagData(strname);
    if (pcRetData.IsEmpty()) return -1;
	int tmpChannel =atoi(pcRetData);
	if (pRegBit) {
	   * pRegBit = int((atof(pcRetData) - tmpChannel)*10+0.1);
	}
	return tmpChannel;
}
// To get the input threshold for active button
double CReadSystemConfig::GetPumpButInputThreshold(UINT param_uiChannelNo, UINT param_uiID) {
    CString strname;
    strname.Format("PumpBut%dInput%dThreshold", param_uiChannelNo,param_uiID);
    CString pcRetData = GetTagData(strname);
    if (pcRetData.IsEmpty()) return 1.0;
	
	double RetVal = atof((LPCSTR)pcRetData);
	return RetVal;
}


// To get that the input to channel no is inverted or not
bool CReadSystemConfig::GetPumpButInputInvert(UINT param_uiChannelNo, UINT param_uiID) {
    CString pcRetVal;
    CString strFormat;
    strFormat.Format("PumpBut%dInput%dInvert", param_uiChannelNo,param_uiID);
    pcRetVal = GetTagData(strFormat);
    if (pcRetVal.IsEmpty()) return false;
    else {
        if (pcRetVal == "YES") return true;
        else return false;
    }
}

// To get that the output to channel no is inverted or not
bool CReadSystemConfig::GetPumpButOutputInvert(UINT param_uiChannelNo, UINT param_uiID) {
    CString pcRetVal;
    CString strFormat;
    strFormat.Format("PumpBut%dOutput%dInvert", param_uiChannelNo,param_uiID);
    pcRetVal = GetTagData(strFormat);
    if (pcRetVal.IsEmpty()) return false;
    else {
        if (pcRetVal == "YES") return true;
        else return false;
    }
}
//Get Pump Control button count
UINT CReadSystemConfig::GetPumpButtonCount(void) {
    CString pcRetData;
    pcRetData = GetTagData("PumpButtonCount");
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}

//Get Pump Control button Text
CString CReadSystemConfig::GetPumpButtonText(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("PumpButText%d", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    return pcRetData;
}
//Get Pump Control button Tooltip
CString CReadSystemConfig::GetPumpButtonToolTip(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("PumpButTooltip%d", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    return pcRetData;
}
//Get Pump Control button wago unit no
int CReadSystemConfig::GetPumpButWagoOutputUnit(UINT param_uiButtonIndex, UINT param_uiID) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("PumpBut%dOutputWagoUnit%d", param_uiButtonIndex, param_uiID);
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return -1;
    else return atoi(pcRetData);
}
//Get Pump Control button wago unit no
int CReadSystemConfig::GetPumpButWagoInputUnit(UINT param_uiButtonIndex, UINT param_uiID) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("PumpBut%dInputWagoUnit%d", param_uiButtonIndex, param_uiID);
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return -1;
    else return atoi(pcRetData);
}
//Get Pump Control button State
int CReadSystemConfig::GetPumpButtonState(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("PumpBut%dState", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}

//Get Pump Control button additional functionality status
int CReadSystemConfig::GetPumpButRemoteControl(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;
    strTagName.Format("PumpButRemoteControl%d", param_uiButtonIndex);
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}


// To get the Input Bit number
UINT CReadSystemConfig::GetPumpInputRegBitNo(UINT param_uiButtonIndex, UINT param_uiID) {
    CString pcRetData;
    CString strTagName;

    strTagName.Format( "PumpBut%dInput%dRegBit", param_uiButtonIndex,param_uiID );
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}

// To get the output Bit number
UINT CReadSystemConfig::GetPumpOutputRegBitNo(UINT param_uiButtonIndex, UINT param_uiID) {
    CString pcRetData;
    CString strTagName;

    strTagName.Format( "PumpBut%dOutput%dRegBit", param_uiButtonIndex,param_uiID );
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}

// To get the number of total input digital and analog attached to a object
UINT CReadSystemConfig::GetPumpButInputCount(UINT param_uiButtonIndex) {
    CString pcRetData;
    CString strTagName;

    strTagName.Format( "PumpBut%dTotalInput", param_uiButtonIndex );
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}

// Function to get total number of Analog and digital Output channels attached
UINT CReadSystemConfig::GetPumpButOutputCount(UINT param_uiButtonIndex) {

    CString pcRetData;
    CString strTagName;

    strTagName.Format( "PumpBut%dTotalOutput", param_uiButtonIndex );
    pcRetData = GetTagData(strTagName);
    if (pcRetData.IsEmpty()) return 0;
    else return atoi(pcRetData);
}

// To get the type of connection for first Input Connection (Analog/Digital)
UINT CReadSystemConfig::GetPumpButInputConnType(UINT param_uiButtonIndex, UINT param_uiID) {
    unsigned int iObjType   = INP_UNDEF;
    CString pcRetData;
    CString strTagName;

    strTagName.Format( "PumpBut%dInput%dType", param_uiButtonIndex, param_uiID );
    pcRetData = GetTagData(strTagName);
    if (!pcRetData.IsEmpty()){
        if (!_stricmp( pcRetData, "Digital" )) {
            iObjType = INP_DIGITAL;
        } else if (!_stricmp( pcRetData, "DigReg" )) {
            iObjType = INP_DIG_REG;
        } else if (!_stricmp( pcRetData, "Analog" )) {
            iObjType = INP_ANALOG;
        } else {
            iObjType = INP_UNDEF;
        }
    }
    return iObjType;
}

// To get the type of connection for Third Input Connection (Analog/Digital)
UINT CReadSystemConfig::GetPumpButOutputConnType(UINT param_uiButtonIndex, UINT param_uiID) {
    unsigned int iObjType   = INP_UNDEF;
    CString pcRetData;
    CString strTagName;

    strTagName.Format( "PumpBut%dOutput%dType", param_uiButtonIndex, param_uiID );
    pcRetData = GetTagData(strTagName);
    if (!pcRetData.IsEmpty()){
        if (!_stricmp( pcRetData, "Digital" )) {
            iObjType = INP_DIGITAL;
        } else if (!_stricmp( pcRetData, "DigReg" )) {
            iObjType = INP_DIG_REG;
        } else if (!_stricmp( pcRetData, "Analog" )) {
            iObjType = INP_ANALOG;
        } else {
            iObjType = INP_UNDEF;
        }
    }
    return iObjType;
}


// To get the function of output bit
UINT CReadSystemConfig::GetPumpOutputFunction(UINT param_uiButtonIndex, UINT param_uiID) {
    unsigned int iFunction   = INP_FUNC_UNDEF;
    CString pcRetData;
    CString strTagName;

    strTagName.Format( "PumpBut%dOutput%dFunction", param_uiButtonIndex, param_uiID );
    pcRetData = GetTagData(strTagName);
    if (!pcRetData.IsEmpty()){
        if (!_stricmp( pcRetData, "RequestControl" )) {
            iFunction = INP_FUNC_OUT_REQUEST_CONTROL;
        } else if (!_stricmp( pcRetData, "ReleaseControl" )) {
            iFunction = INP_FUNC_OUT_RELEASE_CONTROL;
        } else if (!_stricmp( pcRetData, "AbortControlRequest" )) {
            iFunction = INP_FUNC_OUT_ABORT_REQUEST;
        } else {
            iFunction = INP_FUNC_UNDEF;
        }
    }
    return iFunction;
}


// To get the function of output bit
UINT CReadSystemConfig::GetPumpInputFunction(UINT param_uiButtonIndex, UINT param_uiID) {
    unsigned int iFunction   = INP_FUNC_UNDEF;
    CString pcRetData;
    CString strTagName;

    strTagName.Format( "PumpBut%dInput%dFunction", param_uiButtonIndex, param_uiID );
    pcRetData = GetTagData(strTagName);
    if (!pcRetData.IsEmpty()){
        if (!_stricmp( pcRetData, "HasControl" )) {
            iFunction = INP_FUNC_IN_HAS_CONTROL;
        } else if (!_stricmp( pcRetData, "ControlRequest" )) {
            iFunction = INP_FUNC_IN_CONTROL_REQUEST;
        } else {
            iFunction = INP_FUNC_UNDEF;
        }
    }
    return iFunction;
}
