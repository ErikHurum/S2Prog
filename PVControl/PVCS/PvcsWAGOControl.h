#pragma once
#include "objectdetails.h"
#include "controlwago750.h"
#include "backuplog.h"
#include "writexml.h"
#include <memory>
#include "cominc.h"

#include "pvcscontrolobjectinfo.h"
#include "pvcswagoconnectdlg.h"




class CPvcsWagoControl
{
public:
	static CPvcsWagoControl& theWagoUnit();
	friend UINT WagoPreReadThread(LPVOID pParam);

	typedef map <UINT, bool> DigitalChannel;
	typedef DigitalChannel::iterator DigitalChannel_it;
	typedef DigitalChannel::value_type	DigitalChannelValue;

	typedef map <UINT, UINT> AnalogChannel;
	typedef AnalogChannel::iterator AnalogChannel_it;
	typedef AnalogChannel::value_type	AnalogChannelValue;

private:
    static bool hasCreatedWagoUnit;
    static CPvcsWagoControl *WagoUnit;

	CPvcsWagoControl(void);

	DigitalChannel	m_mapDigital;
	AnalogChannel	m_mapAnalog;

public:

	static UINT const WagoMinValue = 0;
	static UINT const WagoMaxValue = 32740;

	//struct having Wago Status
	struct WagoStatus
	{
		CString WagoIP;
		unsigned WagoConnectionStatus;
	};

	vector <WagoStatus*> theWagoStatus;

	~CPvcsWagoControl(void);

	CConvertData m_objConvert;
	CWriteXML m_objWriteXML;
	//CWriteLog m_objLog;
	CBackupLog m_objBackup;
	bool GetLastStatus(void);
private:

	typedef vector <CControlWago750*> WagoList;
	typedef WagoList::iterator WagoList_it;

	WagoList m_WagoList;

	//previously handled way to access Wago unit     volatile bool m_bDataLocked;

	//new way to control access to WAGO unit
	bool m_DataLocked;

	bool m_bWagoThreadClosed;
    CWinThread *cTh;
public:

	bool WagoThreadClosed(void);
	bool GetValue(PvcsControlObjectTypes::AnalogSignal param_sigAnalog, UINT& uiValue,CString param_strWagoType, CControlWago750::BufferOffsetEnum param_Offset=CControlWago750::OffsetAnalogInput);
	bool GetValue(PvcsControlObjectTypes::DigitalSignal param_sigDigital, bool& bStatus,CString param_strWagoType, CControlWago750::BufferOffsetEnum param_Offset=CControlWago750::OffsetDigitalIn);

	bool SetValue(PvcsControlObjectTypes::AnalogSignal param_sigAnalog, const UINT& param_uiValue);
	bool SetValue(PvcsControlObjectTypes::DigitalSignal param_sigDigital, const bool& param_bStatus);
	bool ResetAllValues(void);

	void UpdateBuffer(void);
	std::unique_ptr<CPvcsWagoConnectDlg> m_pdlgConnect;
	void ShowConnectDlg(void);
    void InitObject();
    static void DeleteWagoControl();


	//Get emergency button Input
	bool GetEmgButtonInput(int pWagoUint, int pChannel, bool pInverted, int pInputType, double pThreshold, bool& param_bStatus);
	//Get Pump button Input
	bool GetPumpButtonInput(int pWagoUint, int pChannel, bool pInverted, int pInputType, int pRegBit, double pThreshold, bool& param_bStatus);
	bool GetPumpButtonInput(DigitalSignal pDigitalSignal, bool& param_bStatus);
};

UINT WagoPreReadThread(LPVOID pParam);

