#include "StdAfx.h"
#include ".\controlwago750.h"
#include "MBT.h"
#include <cmath>
#include <string.h>
#include "pvcswagocontrol.h"

const UINT CControlWago750::m_uiPortNumber = 502;

HANDLE CControlWago750::m_hMutex = 0;
#define SLEEP_MS	25
CControlWago750::CControlWago750(const UINT &param_UnitID = 0, const CString &param_strIP = "192.168.227.90", int InpStatCommand, int InpStatRangeStart, int InpStatRangeStop, int ModBusDevType)  // WAGO750 Constructor
	: m_uiUnitID(param_UnitID)
	, m_strIP(param_strIP)
	, InputStatusCommand(InpStatCommand)
	, InputStatusRangeStart(InpStatRangeStart)
	, InputStatusRangeEnd(InpStatRangeStop)
	, ModBusDeviceType(ModBusDevType) {
	memset(DigInBuffer, 0, sizeof(DigInBuffer));
	memset(DigOutBuffer, 0, sizeof(DigOutBuffer));
	memset(RegInBuffer, 0, sizeof(RegInBuffer));
	memset(RegOutBuffer, 0, sizeof(RegOutBuffer));
	if (!m_hMutex) {
		m_hMutex = CreateMutex(NULL, false, "Wago DLL - Single Instance");
    }
    // connect to fieldbus and allocate buffer
    m_lWagoReturnStatus = ConnectFieldBus();

	if (m_lWagoReturnStatus != S_OK ) {
		// If not connected then log the message in XML file
		XmlLogError("Error Connecting to fieldbus");
	}
	MaxInRegister  = 0;
	MaxOutRegister = 0;
	MaxInDigital   = 0;
	MaxOutDigital  = 0;
	MinInRegister  = 0xffff;
	MinOutRegister = 0xffff;
	MinInDigital   = 0xffff;
	MinOutDigital  = 0xffff;

}

CControlWago750::~CControlWago750(void) { // Destructor
										  // disconnect from WAGO and delete the memory allocated to buffer
	if (m_hMutex) {
		//DisconnectWagoFieldBus();
		ExitWagoFiledBus();
		m_lWagoReturnStatus = MBTDisconnect(m_hWagoSocketHandle);

		CloseHandle(m_hMutex);
		m_hMutex = 0;
	}
}
#define DEFAULT_REQUEST_NUM_REG  125

// To Change status of WAGO Digital Output Cards On/Off
bool CControlWago750::SetStatusDigitalOutput(IN bool param_bolStatus, IN unsigned int param_uiChannelNumber, IN int param_uiBitNumber) {
	if (param_uiBitNumber == -1) {
		BYTE m_ucBuffer;
		if (param_bolStatus == true) {
			m_ucBuffer = 0x01;  // SET TO ON
		} else {
			m_ucBuffer = 0x00; // SET TO OFF
		}

		if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
			// Writing on coil to set the status of the channel as ON or OFF
			m_lWagoReturnStatus = MBTWriteCoils(
				m_hWagoSocketHandle,
				WORD(param_uiChannelNumber),
				1/*WORDS_NUMBITS*/,
				LPBYTE(&m_ucBuffer),
				NULL,
				0
				);

			ReleaseMutex(m_hMutex);
		}
		//Sleep(SLEEP_MS);
	} else if (param_uiChannelNumber < MODBUS_BUF_SIZE_STANDARD) {
		if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
			if ((m_lWagoReturnStatus = MBTReadRegisters(m_hWagoSocketHandle, MODBUSTCP_TABLE_OUTPUT_REGISTER, param_uiChannelNumber, 1, (LPBYTE)&RegOutBuffer[param_uiChannelNumber], NULL, 0)) != S_OK) {
				TRACE("", m_lWagoReturnStatus);
			} else {
				//Sleep(100);
			}
			WORD tmpRegVal = MBTSwapWord(RegOutBuffer[param_uiChannelNumber]);
			if (param_bolStatus) {
				tmpRegVal |= 1 << param_uiBitNumber;
			} else {
				tmpRegVal &= ~(1 << param_uiBitNumber);
			}

			WORD param_uiCurrentValue = MBTSwapWord(tmpRegVal);
			m_lWagoReturnStatus = MBTWriteRegisters(
				m_hWagoSocketHandle,
				WORD(param_uiChannelNumber),
				WORDS_NUMBITS,
				reinterpret_cast<LPBYTE>(&param_uiCurrentValue), // check the overflow and underflow conditions.
				NULL,
				0
				);
			ReleaseMutex(m_hMutex);
		}
	}
	if (S_OK == m_lWagoReturnStatus) {
		return true;
	} else {

		return false;
	}
}



// To Connect To WAGO Fieldbus Coupler After successful intilization
unsigned CControlWago750::ConnectFieldBus() {
	if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
		m_lWagoReturnStatus = MBTConnect(m_strIP, m_uiPortNumber, true, DEFAULT_REQUEST_TIMEOUT, &m_hWagoSocketHandle);
		ReleaseMutex(m_hMutex);
	}
	return m_lWagoReturnStatus;
}

// To Initialize The MODBUS/TCP library
long CControlWago750::InitializeFieldbus(void) {
	if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
		//MBTinit to initialize the MODBUS/TCP Library
		m_lWagoReturnStatus = MBTInit();
		ReleaseMutex(m_hMutex);
	}
	return m_lWagoReturnStatus;

}

unsigned CControlWago750::DisconnectWagoFieldBus(void) {
	if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
		// Terminate the Connection when ever PVCS Closes to free the SOcket i.e. Port and IP
		m_lWagoReturnStatus = MBTDisconnect(m_hWagoSocketHandle);
		//ReleaseMutex(m_hMutex);
		Sleep(100);
	}
	return m_lWagoReturnStatus;
}

// To write Value in mA to WAGO Analog Output Card
unsigned CControlWago750::SetStatusAnalogOutput(IN unsigned int param_uiCurrentValue, IN unsigned int param_uiChannelNumber) {
	// check gor current Range between 0 to 32760 where 0=4mA and 32760=20mA
	if (param_uiCurrentValue == 32761) {
		param_uiCurrentValue--;
	}
	if (param_uiCurrentValue < 0 || param_uiCurrentValue > 32760) {
		CString strErr;
		strErr.Format("Value[%d] out of Range", param_uiCurrentValue);
		//AfxMessageBox(strErr);
		return 0xffffffff;
	} else {
		param_uiCurrentValue = MBTSwapWord(WORD(param_uiCurrentValue));
		if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
			Sleep(50);
			m_lWagoReturnStatus = MBTWriteRegisters(
				m_hWagoSocketHandle,
				WORD(param_uiChannelNumber),
				WORDS_NUMBITS,
				reinterpret_cast<LPBYTE>(&param_uiCurrentValue), // check the overflow and underflow conditions.
				NULL,
				0
				);

			ReleaseMutex(m_hMutex);
		}
	}
	return m_lWagoReturnStatus;
}

// To Terminate the ModBus/TCP Library
bool CControlWago750::ExitWagoFiledBus(void) {
	DisconnectWagoFieldBus();
	// TO terminate the MODBUS/TCP library
	if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
		m_lWagoReturnStatus = MBTExit();

		ReleaseMutex(m_hMutex);
	}
	if (S_OK == m_lWagoReturnStatus) {
		return true;
	} else {
		return false; // functionality to be implemented in GUI.
	}
}

int CControlWago750::m_iInstanceCount;
// To control that more then one instance cannot be created
void CControlWago750::ControlInstance(void) {
	if (m_iInstanceCount == 1) {
		AfxMessageBox("No More Instance Allowed");
	} else {
		InitializeFieldbus();
		//ConnectFieldBus(DEFAULT_SERVER_NAME,DEFAULT_PORT);
		m_iInstanceCount = m_iInstanceCount + 1;
	}
}


// To get the status of last operation performed
bool CControlWago750::GetLastStatus(void) {
	if (m_lWagoReturnStatus == S_OK) {
		return true;
	} else {
		return false;
	}
}

// to initialize the wago dll
bool CControlWago750::InitDll(void) {
	return MBTInit() == S_OK ? true : false;
}
// to deinitialize the WAGO dll
bool CControlWago750::ExitDll(void) {
	return MBTExit() == S_OK ? true : false;
}


// Function to read the status of analog and digital channels in buffer
// block reading of WAGO unit
unsigned CControlWago750::Read(void) {

	ReestablishConnection();
	// Read Special inputs if configured
	if (m_lWagoReturnStatus == S_OK) {
		if (!ReadMultipleInDigital()) {
			TRACE("", m_lWagoReturnStatus);
		} else {
			//Special for Wago that coils are mapped from 0x200
			if (!ReadMultipleOutDigital()) {
				TRACE("", m_lWagoReturnStatus);
			} else {
				if (!ReadMultipleInRegisters()) {
					TRACE("", m_lWagoReturnStatus);
				} else {
					if (!ReadMultipleOutRegisters()) {
						TRACE("", m_lWagoReturnStatus);
					}
				}
			}
		}
	}
	//ReConnectToWago(); //

	CPvcsWagoControl::theWagoUnit().ShowConnectDlg();
	CPvcsWagoControl::theWagoUnit().theWagoStatus[m_uiUnitID]->WagoConnectionStatus = m_lWagoReturnStatus;

	return m_lWagoReturnStatus;
}

// Get the value normalized to 16 bit signed integer
double CControlWago750::ScaleValueTo16Bits(int param_uiValue, CString param_psWagoUnitType) {
	const int param_uiMax = 0x7fff;
	const int param_uiMin = 0x0;
	int WagoType = atoi(param_psWagoUnitType);
	int MaxRange = 0x7fff;
	int MinRange = 0;
	int Status = 0;
	int AnalogIn = 0;
	switch (WagoType) {
	case 480:
		MaxRange = 0x7ffc;
		MinRange = 0x0;
		AnalogIn = param_uiValue & 0xfffc;
		break;
	case 461:
		MaxRange = 0x2710;
		MinRange = 0x14;
		Status = param_uiValue & 0xc000;
		if (Status) {
			AnalogIn = MinRange;
		} else {
			AnalogIn = param_uiValue & 0x3fff;
		}
		break;

	case 454:
		MaxRange = 0xfff;
		MinRange = 0;
		Status = param_uiValue & 7;
		switch (Status) {
		case 3:
			AnalogIn = 0;
			break;
		case 1:
			AnalogIn = 0xfff;
			break;
		default:
			AnalogIn = param_uiValue >> 3;
			break;
		}
		break;
	case 0:
		MaxRange = 0x7fff;
		MinRange = 0x0;
		AnalogIn = param_uiValue & 0xffff;
		break;
	case 1000: // Dummy for digital io
		return param_uiValue & 0xffff;
	}
	double a           = double(param_uiMax - param_uiMin) / (MaxRange - MinRange);
	double b           = double(param_uiMax) - a * MaxRange;
	double AnalogValue = a * double(AnalogIn) + b;
	return AnalogValue;
}

// to calculate and read individual channel value from the buffer
UINT CControlWago750::GetValue(CControlWago750::BufferOffsetEnum param_Offset, const UINT &param_channel, CString param_iWagoUnitType) {
	UINT Result = 0;
	switch (param_Offset) {
	case OffsetDigitalIn :
		MinInDigital  = __min(MinInDigital, param_channel);
		MaxInDigital  = __max(MaxInDigital, param_channel + 1);
		Result = MB_GetBit(DigInBuffer, param_channel - MinInDigital);
		break;

	case OffsetDigitalOut :
		MinOutDigital  = __min(MinOutDigital, param_channel);
		MaxOutDigital  = __max(MaxOutDigital, param_channel + 1);
		Result = MB_GetBit(DigOutBuffer, param_channel - MinOutDigital);
		break;
	case OffsetAnalogOutput :
		MinOutRegister  = __min(MinOutRegister, param_channel);
		MaxOutRegister  = __max(MaxOutRegister, param_channel + 1);
		{
			WORD Value = RegOutBuffer[param_channel - MinOutRegister];
			double ScaledVal = ScaleValueTo16Bits(MBTSwapWord(Value), param_iWagoUnitType);
			Result = (floor(ScaledVal) + 0.5) > ScaledVal ? UINT(floor(ScaledVal)) : UINT(ceil(ScaledVal));
		}
		break;
	case OffsetAnalogInput :
		MinInRegister  = __min(MinInRegister, param_channel);
		MaxInRegister  = __max(MaxInRegister, param_channel + 1);
		{
			WORD Value = RegInBuffer[param_channel - MinInRegister];
			double ScaledVal = ScaleValueTo16Bits(MBTSwapWord(Value), param_iWagoUnitType);
			Result = (floor(ScaledVal) + 0.5) > ScaledVal ? UINT(floor(ScaledVal)) : UINT(ceil(ScaledVal));
		}
		break;
	}
	return Result;
}


// to reestablish broken connection
unsigned CControlWago750::ReestablishConnection(void) {
	switch (m_lWagoReturnStatus) {
	default:
	case 1:
		Sleep(1);
	case 0xef010005:
	case 0xef010006:
	case 0x80072746:
		DisconnectWagoFieldBus();
		Sleep(1000);
		m_lWagoReturnStatus = ConnectFieldBus();
		CPvcsWagoControl::theWagoUnit().theWagoStatus[m_uiUnitID]->WagoConnectionStatus = m_lWagoReturnStatus;
		break;
	case S_OK:
		break;
	}
	return m_lWagoReturnStatus;

}
// to get value of status flag that tells about current status of connection with WAGO
bool CControlWago750::IsSuccess(void) {

	return !m_lWagoReturnStatus;
}


void CControlWago750::WriteCoils(int FirstAddress, int numBits, char *Bits) {
	if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
		if ((m_lWagoReturnStatus = MBTWriteCoils(m_hWagoSocketHandle, WORD(FirstAddress), WORD(numBits), (LPBYTE)Bits, NULL, 0)) != S_OK) {
			TRACE("", m_lWagoReturnStatus);
		}
		ReleaseMutex(m_hMutex);
	}
}

void CControlWago750::ResetAllCoils(void) {
	char tmpBuf[0x200 >> 3];
	memset(tmpBuf, 0, 0x200 >> 3);

	if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
		WriteCoils(0, 0x200, tmpBuf);
		ReleaseMutex(m_hMutex);
	}
}

int CControlWago750::GetModBusDeviceType(void) {
	return ModBusDeviceType;
}


int CControlWago750::GetInputStatusCommand(void) {
	return InputStatusCommand;
}
#define MAX_IN_REGISTERS	125
bool CControlWago750::ReadMultipleInRegisters(void) {
	bool RequestOK = true;
	if (MaxInRegister && (MinInRegister != 0xffff)) {
		int Count1 = MaxInRegister / MAX_IN_REGISTERS;
		int Count2 = MaxInRegister % MAX_IN_REGISTERS;
		for (int i = 0; RequestOK && i < Count1; i++) {
			if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
				RequestOK = bool((m_lWagoReturnStatus = MBTReadRegisters(m_hWagoSocketHandle, MODBUSTCP_TABLE_INPUT_REGISTER, i * MAX_IN_REGISTERS + MinInRegister, MAX_IN_REGISTERS, (LPBYTE)&RegInBuffer[i * MAX_IN_REGISTERS], NULL, 0)) == S_OK);
				ReleaseMutex(m_hMutex);
				Sleep(SLEEP_MS);
			}
		}
		if (Count2-MinInRegister) {
			if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
				RequestOK = bool((m_lWagoReturnStatus = MBTReadRegisters(m_hWagoSocketHandle, MODBUSTCP_TABLE_INPUT_REGISTER, Count1 * MAX_IN_REGISTERS + MinInRegister, 	Count2 - MinInRegister, (LPBYTE)&RegInBuffer[Count1 * MAX_IN_REGISTERS/*+MinInRegister*/], NULL, 0)) == S_OK);
				ReleaseMutex(m_hMutex);
				Sleep(SLEEP_MS);
			}
		}
	}
	return RequestOK;
}

bool CControlWago750::ReadMultipleOutRegisters(void) {
	bool RequestOK = true;
	if (MaxOutRegister && (MinOutRegister != 0xffff)) {
		int Count1 = MaxOutRegister / MAX_IN_REGISTERS;
		int Count2 = MaxOutRegister % MAX_IN_REGISTERS;
		for (int i = 0; RequestOK && i < Count1; i++) {
			if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
				RequestOK = bool((m_lWagoReturnStatus = MBTReadRegisters(m_hWagoSocketHandle, MODBUSTCP_TABLE_OUTPUT_REGISTER, i * MAX_IN_REGISTERS, MAX_IN_REGISTERS + MinOutRegister, (LPBYTE)&RegOutBuffer[i * MAX_IN_REGISTERS], NULL, 0)) == S_OK);
				ReleaseMutex(m_hMutex);
				Sleep(SLEEP_MS);
			}
		}
		if (Count2-MinOutRegister) {
			if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
				RequestOK = bool((m_lWagoReturnStatus = MBTReadRegisters(m_hWagoSocketHandle, MODBUSTCP_TABLE_OUTPUT_REGISTER, Count1 * MAX_IN_REGISTERS + MinOutRegister, 	Count2 - MinOutRegister, (LPBYTE)&RegOutBuffer[Count1 * MAX_IN_REGISTERS/*+MinOutRegister*/], NULL, 0)) == S_OK);
				ReleaseMutex(m_hMutex);
				Sleep(SLEEP_MS);
			}
		}
	}
	return RequestOK;
}

#define MAX_IN_DIGITAL	0x7d0
bool CControlWago750::ReadMultipleInDigital(void) {
	bool RequestOK = true;
	if (MaxInDigital && (MinInDigital != 0xffff)) {
		int Count1 = MaxInDigital / MAX_IN_DIGITAL;
		int Count2 = MaxInDigital % MAX_IN_DIGITAL;
		for (int i = 0; RequestOK && i < Count1; i++) {
			if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
				RequestOK = bool((m_lWagoReturnStatus = MBTReadCoils(m_hWagoSocketHandle, MODBUSTCP_TABLE_INPUT_COIL, i * MAX_IN_DIGITAL + MinInDigital, MAX_IN_DIGITAL, (LPBYTE)&DigInBuffer[i * MAX_IN_DIGITAL/8], NULL, 0)) == S_OK);
				ReleaseMutex(m_hMutex);
				Sleep(SLEEP_MS);
			}
		}
		if (Count2 - MinInDigital) {
			if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
				RequestOK = bool((m_lWagoReturnStatus = MBTReadCoils(m_hWagoSocketHandle, MODBUSTCP_TABLE_INPUT_COIL, Count1 * MAX_IN_REGISTERS + MinInDigital, Count2 - MinInDigital, (LPBYTE)&DigInBuffer[Count1 * MAX_IN_DIGITAL/8], NULL, 0)) == S_OK);
				ReleaseMutex(m_hMutex);
				Sleep(SLEEP_MS);
			}
		}
	}
	return RequestOK;
}


bool CControlWago750::ReadMultipleOutDigital(void) {
	bool RequestOK = true;
	if (MaxOutDigital && (MinOutDigital != 0xffff)) {
		int Count1 = MaxOutDigital / MAX_IN_DIGITAL;
		int Count2 = MaxOutDigital % MAX_IN_DIGITAL;
		for (int i = 0; RequestOK && i < Count1; i++) {
			if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
				RequestOK = bool((m_lWagoReturnStatus = MBTReadCoils(m_hWagoSocketHandle, MODBUSTCP_TABLE_OUTPUT_COIL, i * MAX_IN_DIGITAL + MinOutDigital, MAX_IN_DIGITAL, (LPBYTE)&DigOutBuffer[i * MAX_IN_DIGITAL/8], NULL, 0)) == S_OK);
				ReleaseMutex(m_hMutex);
				Sleep(SLEEP_MS);
			}
		}
		if (Count2-MinOutDigital) {
			if (WaitForSingleObject(m_hMutex, DEFAULT_MUX_TIMEOUT) == WAIT_OBJECT_0) {
				RequestOK = bool((m_lWagoReturnStatus = MBTReadCoils(m_hWagoSocketHandle, MODBUSTCP_TABLE_OUTPUT_COIL, Count1 * MAX_IN_REGISTERS + MinOutDigital, Count2 - MinOutDigital, (LPBYTE)&DigOutBuffer[Count1 * MAX_IN_DIGITAL/8], NULL, 0)) == S_OK);
				ReleaseMutex(m_hMutex);
				Sleep(SLEEP_MS);
			}
		}
	}
	return RequestOK;
}

