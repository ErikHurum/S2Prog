#pragma once
#include "readsystemconfig.h"
#define MODBUS_BUF_SIZE_STANDARD  0x4000
#define DEFAULT_PORT             502
#define DEFAULT_SERVER_NAME      _T("192.168.227.90")
#define DEFAULT_PROTOCOL         false	/* UDP */ // TCP=true
#define DEFAULT_REQUEST_TIMEOUT  500   /* in ms */
#define DEFAULT_MUX_TIMEOUT      (DEFAULT_REQUEST_TIMEOUT*3)   /* in ms */
#define WORDS_NUMBITS			 1      /* Number Of Bits TO read in WORDS*/

// returns bit state 0 or 1
#define MB_GetBit(a, b)                ((((unsigned char*)a)[(b)>>3] >> ((b)&7)) & 1)
// set bit Boolean value to 1
#define SetBit(a, b)                (((unsigned char*)a)[(b)>>3] |= (1 << ((b)&7)))
// set bit Boolean value to 0
#define MB_ResetBit(a, b)              (((unsigned char*)a)[(b)>>3] &= ~(1 << ((b)&7)))
// toggle bit Boolean value
#define MB_XOrBit(a, b)                (((unsigned char*)a)[(b)>>3] ^= (1 << ((b)&7)))


/* Class to Establish Connection between WAGO Control Unit and PVCS and then
   Control Objects using The PVCS GUI
*/
class CControlWago750
{
public:
	CControlWago750(const UINT& param_UnitID, const CString& param_strIP, int InpStatCommand=1, int InpStatRangeStart=0, int InpStatRangeStop=255, int ModBusDevType=0);
	virtual ~CControlWago750(void);

	// Function To Change status of WAGO Digital Input Card ON/OFF devices
    bool SetStatusDigitalOutput(IN bool param_bolStatus, IN unsigned int param_uiChannelNumber, IN int param_uiBitNumber=-1);
	// To Disconnect the WAGO fieldBus connected to the Ethernet Port
	unsigned DisconnectWagoFieldBus(void);
	// To write Value in mA to WAGO Analog Output Card
	unsigned SetStatusAnalogOutput(IN unsigned int param_uiCurrentValue,IN  unsigned int param_uiChannelNumber);
	// To Terminate the ModBus/TCP Library
	bool ExitWagoFiledBus(void);
private:
	// To Connect To WAGO Fieldbus Coupler After successful intilization
	unsigned ConnectFieldBus();
	// To Initialize The MODBUS/TCP library
	long InitializeFieldbus(void);
	// To count the Number of instance
	static int m_iInstanceCount;
	// To control that more then one instance cannot be created
	void ControlInstance(void);

	static HANDLE m_hMutex;
    static CControlWago750 StaticObject;

protected:
	// return value of the functions called from MODBUS dll
	long m_lWagoReturnStatus;
	// Handler for the Socket that is initialized to be used by MODBUS
	HANDLE m_hWagoSocketHandle;

public:
	enum BufferOffsetEnum{
		OffsetDigitalIn = 0,
		OffsetDigitalOut,
		OffsetAnalogOutput,
		OffsetAnalogInput
	};

	// To get the status of last operation performed
	bool GetLastStatus(void);

	// to reestablish broken connection
	unsigned ReestablishConnection(void);
	//void ReConnectToWago(void);//By
	double ScaleValueTo16Bits(int param_uiValue,CString param_psWagoUnitType);

private:
	const UINT m_uiUnitID;

	BYTE  DigInBuffer[MODBUS_BUF_SIZE_STANDARD];
	BYTE  DigOutBuffer[MODBUS_BUF_SIZE_STANDARD];
	WORD  RegInBuffer[MODBUS_BUF_SIZE_STANDARD];
	WORD  RegOutBuffer[MODBUS_BUF_SIZE_STANDARD];
	unsigned MaxInRegister;
	unsigned MaxOutRegister;
	unsigned MaxInDigital;
	unsigned MaxOutDigital;

	unsigned MinInRegister ;
	unsigned MinOutRegister;
	unsigned MinInDigital  ;
	unsigned MinOutDigital ;

	static const UINT m_uiPortNumber;
public:
	static bool InitDll(void);
	static bool ExitDll(void);

	unsigned Read(void);
	UINT GetValue(CControlWago750::BufferOffsetEnum param_Offset, const UINT& param_channel,CString param_iWagoUnitType);
private:
	// for storing the IP
	CString m_strIP;
	int InputStatusRangeStart;
	int InputStatusRangeEnd;
	int InputStatusCommand;
	int ModBusDeviceType;
	static bool HasInitializedLib;
public:
	// To initialize and connect to the wago
	// To initialize and connect to the wago
	bool IsSuccess(void);
	void ResetAllCoils(void);
	int GetModBusDeviceType(void);
	int GetInputStatusCommand(void);

private:
	void WriteCoils(int FirstAddress, int LastAddress,char *Bits);
	bool ReadMultipleInRegisters(void);
	bool ReadMultipleOutRegisters(void);
	bool ReadMultipleInDigital(void);
	bool ReadMultipleOutDigital(void);

};

