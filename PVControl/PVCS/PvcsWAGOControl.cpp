#include "StdAfx.h"
#include ".\pvcswagocontrol.h"
#include "pvcsconfiguration.h"
#include "PVCSAlarmCtrl.h"//Added EHS
#include "PVCS v1.0.h"

//Global Data
CPvcsWagoControl *CPvcsWagoControl::WagoUnit = NULL;
bool CPvcsWagoControl::hasCreatedWagoUnit = false;


CPvcsWagoControl& CPvcsWagoControl::theWagoUnit() {
	if (!WagoUnit && !hasCreatedWagoUnit) {
		WagoUnit = new CPvcsWagoControl;
		WagoUnit->InitObject();
	}
	return *WagoUnit;
}

CPvcsWagoControl::CPvcsWagoControl(void)
	: m_bWagoThreadClosed(false) {
	if (hasCreatedWagoUnit) {
		return;
	}
	hasCreatedWagoUnit = true;
}

CPvcsWagoControl::~CPvcsWagoControl(void) {
	if ( hasCreatedWagoUnit) {
		CControlWago750::ExitDll();
		hasCreatedWagoUnit = false;
	}
	if (WagoUnit) {
		WagoUnit = NULL;
		
		for (WagoList_it it = m_WagoList.begin(); it != m_WagoList.end(); ++it) delete *it;

		for (unsigned i = 0; i < theWagoStatus.size(); i++) delete theWagoStatus[i];
	}
}
#pragma warning (disable: 4101)

UINT WagoPreReadThread(LPVOID pParam) {
	/*
	CPvcsWagoControl::AnalogChannel  temp_ana_map;
	CPvcsWagoControl::DigitalChannel temp_dig_map;
	*/
	while (CPVCSApp::m_bIsAlive) {
		//BEGINTICK("ReadWago");
		try {
			CPvcsWagoControl::theWagoUnit().UpdateBuffer();
			Sleep(500);
		} catch (exception &e) {}
	} // while ( CPVCSApp::m_bIsAlive )
	CPvcsWagoControl::theWagoUnit().m_bWagoThreadClosed = true;
	return 0;
}

bool CPvcsWagoControl::WagoThreadClosed(void) {
	return m_bWagoThreadClosed;
}


bool CPvcsWagoControl::GetValue(PvcsControlObjectTypes::AnalogSignal param_sigAnalog, UINT &uiValue, CString param_strWagoType, CControlWago750::BufferOffsetEnum param_Offset) {
	bool bSuccess = false;
	using namespace PvcsControlObjectTypes;

	UINT wagoUnit = param_sigAnalog.Port.WagoUnit;
	UINT channel  = param_sigAnalog.Port.WagoChannel;

	try {
		CControlWago750 *pwc = dynamic_cast<CControlWago750 *>(m_WagoList.at(wagoUnit));

		if (!pwc) throw exception("Invalid Controller pointer");

		uiValue = pwc->GetValue(param_Offset, channel, param_strWagoType);

		bSuccess = true;
	} catch (exception &e) {
		//TRACE("*****CPvcswagocontrol-getvalue**+++++Analog**Channel = %d",channel);
		XmlLogError(e.what());
		bSuccess = false;
	}
	return bSuccess;
}

bool CPvcsWagoControl::GetValue(PvcsControlObjectTypes::DigitalSignal param_sigDigital, bool &bStatus, CString param_strWagoType, CControlWago750::BufferOffsetEnum param_Offset) {
	bool bSuccess = false;
	using namespace PvcsControlObjectTypes;

	UINT wagoUnit = param_sigDigital.Port.WagoUnit;
	UINT channel  = param_sigDigital.Port.WagoChannel;

	try {

		CControlWago750 *pwc = dynamic_cast<CControlWago750 *>(m_WagoList.at(wagoUnit));


		if (!pwc) throw exception("Invalid Controller pointer");
		if (param_sigDigital.BitNo != -1) {
			switch (param_Offset) {
			case CControlWago750::OffsetDigitalOut:
				param_Offset = CControlWago750::OffsetAnalogOutput;
				break;
			case CControlWago750::OffsetDigitalIn:
				param_Offset = CControlWago750::OffsetAnalogInput;
				break;
			}

		}


		if (param_sigDigital.BitNo == -1) {
			bStatus = pwc->GetValue(param_Offset, channel, param_strWagoType) != 0;
		} else {
			bStatus = (pwc->GetValue(param_Offset, channel, param_strWagoType) >> param_sigDigital.BitNo) & 0x01;
		}
		if (param_sigDigital.IsInverted) bStatus = !bStatus;

		bSuccess = true;
	} catch (exception &e) {
		//TRACE("*****CPvcswagocontrol-getvalue++++++ Digital******Channel = %d",channel);
		XmlLogError(e.what());
		bSuccess = false;
	}
	return bSuccess;
}
#pragma warning (disable: 4800)

bool CPvcsWagoControl::SetValue(PvcsControlObjectTypes::AnalogSignal param_sigAnalog, const UINT &param_uiValue) {
	bool bSuccess = false;
	if (!theApp.m_pdlgManualControl || theApp.bIsEmegencySwitchFault) {
		using namespace PvcsControlObjectTypes;

		UINT wagoUnit = param_sigAnalog.Port.WagoUnit;
		UINT channel  = param_sigAnalog.Port.WagoChannel;

		try {

			bSuccess =  bool(m_WagoList.at(wagoUnit)->SetStatusAnalogOutput(param_uiValue, channel));
			//UpdateBuffer();

		} catch (exception &e) {
			//bSuccess = false;
		}
	}
	return bSuccess;
}

bool CPvcsWagoControl::SetValue(PvcsControlObjectTypes::DigitalSignal param_sigDigital, const bool &param_bStatus) {
	bool bSuccess = false;
	if (!theApp.m_pdlgManualControl || theApp.bIsEmegencySwitchFault) {
		using namespace PvcsControlObjectTypes;
		bool bStatus = param_bStatus;
//TRACE("SetValue- start");
		UINT wagoUnit = param_sigDigital.Port.WagoUnit;
		UINT channel  = param_sigDigital.Port.WagoChannel;
		try {
			CControlWago750 *pwc = dynamic_cast<CControlWago750 *>(m_WagoList.at(wagoUnit));

			if (!pwc) throw exception("Invalid Controller pointer");

			if (param_sigDigital.IsInverted) bStatus = !bStatus;
			int Cnt = 0;
			while (!bSuccess && Cnt++ < 5) {
				bSuccess = pwc->SetStatusDigitalOutput(bStatus, channel, param_sigDigital.BitNo);
				if (!bSuccess) {
					Sleep(100);
				}
			}
			//UpdateBuffer();

		} catch (exception &e) {
			bSuccess = false;
		}
	}
	return bSuccess;
}



// to update the buffer at regular intervals
void CPvcsWagoControl::UpdateBuffer(void) {
	for (WagoList_it it = m_WagoList.begin(); it != m_WagoList.end(); ++it) {
		(*it)->Read();
	}
}
// to show the dialog window while comm with WAGO is interupted
void CPvcsWagoControl::ShowConnectDlg(void) {
	WagoList_it it = m_WagoList.begin();

	for (; it != m_WagoList.end(); ++it) if (!(*it)->IsSuccess()) {
			m_pdlgConnect->ShowWindow(SW_SHOW);
			break;
		}

	if (it == m_WagoList.end()) m_pdlgConnect->PostMessage(WM_CLOSE);
}

//Get emergency button Input
bool CPvcsWagoControl::GetEmgButtonInput(int pWagoUint, int pChannel, bool pInverted, int pInputType, double pThreshold, bool &param_bStatus) {

	bool bSuccess = false;
	using namespace PvcsControlObjectTypes;

	UINT wagoUnit = pWagoUint;
	UINT channel  = pChannel;

	try {

		CControlWago750 *pwc = dynamic_cast<CControlWago750 *>(m_WagoList.at(wagoUnit));

		if (!pwc) throw exception("Invalid Controller pointer");

		switch (pInputType) {
		case 0: // Digital
			{
				CControlWago750::BufferOffsetEnum Offset;
				switch (m_WagoList.at(wagoUnit)->GetModBusDeviceType()) {
				default:
				case MODBUS_DEVICE_WAGO:
					if (channel >= 0 && channel < 0x200) {
						Offset = CControlWago750::OffsetDigitalIn;
					} else {
						Offset = CControlWago750::OffsetDigitalOut;
					}
					break;
				case MODBUS_DEVICE_WÄRTSILA:
					Offset = CControlWago750::OffsetDigitalIn;
					break;
				}
				param_bStatus = pwc->GetValue(Offset, channel, " ") != 0;
			}
			if (pInverted) param_bStatus = !param_bStatus;
			break;
		case 1: // Analog
			{
				CControlWago750::BufferOffsetEnum Offset;
				switch (m_WagoList.at(wagoUnit)->GetModBusDeviceType()) {
				default:
				case MODBUS_DEVICE_WAGO:
					if (channel >= 0 && channel < 0x200) {
						Offset = CControlWago750::OffsetAnalogInput;
					} else {
						Offset = CControlWago750::OffsetAnalogOutput;
					}
					break;
					break;
				case MODBUS_DEVICE_WÄRTSILA:
					Offset = CControlWago750::OffsetAnalogInput;
					break;
				}

				unsigned RawVal   = pwc->GetValue(Offset, channel, " ");
				unsigned InputStatus  = RawVal & 0x3;
				switch (InputStatus) {
				case 3: // Open loop
					param_bStatus = false;
					if (!theApp.m_pdlgManualControl) {
						theApp.bIsEmegencySwitchFault = true;
						theApp.m_pdlgManualControl = new CManualControlDialog;
						theApp.m_pdlgManualControl->Create(IDD_PVCS_MANUAL_CTRL_DLG);
						theApp.m_pdlgManualControl->ShowWindow(SW_SHOW);
						RECT Rect;

						theApp.m_pdlgManualControl->GetClientRect(&Rect);

						theApp.m_pdlgManualControl->MoveWindow(Rect.left + 600, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, true);
					}
					theApp.m_pdlgManualControl->SetDlgItemText(IDC_STATIC, "Emergency button Short circuit!");
					break;
				case 1: // Short circuit
					param_bStatus = false;
					if (!theApp.m_pdlgManualControl) {
						theApp.bIsEmegencySwitchFault = true;
						theApp.m_pdlgManualControl = new CManualControlDialog;
						theApp.m_pdlgManualControl->Create(IDD_PVCS_MANUAL_CTRL_DLG);
						theApp.m_pdlgManualControl->ShowWindow(SW_SHOW);
						RECT Rect;
						theApp.m_pdlgManualControl->GetClientRect(&Rect);

						theApp.m_pdlgManualControl->MoveWindow(Rect.left + 600, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, true);
					}
					theApp.m_pdlgManualControl->SetDlgItemText(IDC_STATIC, "Emergency button Open loop!");
					break;
				case 0: // Input signal OK
					{
						double AnalogValue = 32 * double(RawVal >> 3) / double(0x1000) / 1000;
						if (AnalogValue >= pThreshold) {
							// Update text if open Warning window open.
							param_bStatus = true;
						} else {
							param_bStatus = false;
						}
						if (pInverted) {
							param_bStatus = !param_bStatus;
						}
						theApp.bIsEmegencySwitchFault = false;
					}
					break;
				}
			}
			break;
		}


		bSuccess = true;
	} catch (exception &e) {
		//TRACE("*****CPvcswagocontrol-getvalue++++++ Digital******Channel = %d",channel);
		XmlLogError(e.what());
		bSuccess = false;
	}
	return bSuccess;

}

bool CPvcsWagoControl::ResetAllValues(void) {
	using namespace PvcsControlObjectTypes;
	bool bSuccess = false;
//TRACE("SetValue- start");
	try {
		for (unsigned i = 0; i < m_WagoList.size(); i++) {
			CControlWago750 *pwc = dynamic_cast<CControlWago750 *>(m_WagoList.at(i));
			pwc->ResetAllCoils();
		}
	} catch (exception &e) {
		bSuccess = false;
	}
	return bSuccess;
}


void CPvcsWagoControl::InitObject() {
	CControlWago750::InitDll();

	UINT nCount = theConfiguration().GetWagoUnitCount();

	m_pdlgConnect.reset(new CPvcsWagoConnectDlg);

	m_pdlgConnect->Create(IDD_PVCSWAGOCONNECTDLG);

	try {
		//multiple Wago unit with one IP
		for (UINT i = 0; i < nCount; i++) {
			WagoStatus *structWagoStatus = new WagoStatus;
			structWagoStatus->WagoIP    = theConfiguration().GetWagoIP(i);
			int             ModbusDevice            = theConfiguration().GetIsModbusDeviceType(i);
			int             InputStatusRangeCommand = theConfiguration().GetInputStatusCommand(i);
			int             InputStatusRangeStart   = theConfiguration().GetInputStatusRangeStart(i);
			int             InputStatusRangeEnd     = theConfiguration().GetInputStatusRangeEnd(i);
			CControlWago750 *newWago750             = new CControlWago750(i, structWagoStatus->WagoIP, InputStatusRangeCommand, InputStatusRangeStart, InputStatusRangeEnd, ModbusDevice);
			m_WagoList.push_back(newWago750);
			theWagoStatus.push_back(structWagoStatus);
			newWago750->Read();
		}
		CString WagoErrorMessage = "";

		for (unsigned i = 0; i < theWagoStatus.size(); i++) {
			if (theWagoStatus[i]->WagoConnectionStatus) {
				CString ErrorMsg;
				ErrorMsg.Format("Unable to connect to Wago Unit %d\n", i);
				WagoErrorMessage += ErrorMsg;
			}
		}

		if (WagoErrorMessage != "") {
			theApp.SetWagoDisconnectMessage(WagoErrorMessage);
		}

		////Create Event to control access of wago unit
		//m_hDataLocked = CreateMutex(NULL,false,"wago access");
		////CreateEvent(NULL,true,false,"Wago Access");
		//SetEvent(m_hDataLocked); //set to signaled state, so that any one can take access of wago

	} catch (exception &e) {

		//TRACE("*****CPvcswagocontrol-constructor******");
		XmlLogError("Error creating new wago controller");
		XmlLogError(e.what());
	}

	if (m_objBackup.CheckFileSize(theConfiguration().GetLogFileName()) == true) {
		m_objBackup.BackUpLog(theConfiguration().GetLogFileName(), "c:\\Windows\\Temp\\backup.xml");
	}

	ShowConnectDlg();

	//m_objLog.InitLogHeader(theConfiguration().GetLogFileName() ,"ObjectState");

	AfxBeginThread(WagoPreReadThread, 0);
}

void CPvcsWagoControl::DeleteWagoControl() {
	if (WagoUnit) {
		delete WagoUnit;
	}
}




//Get Pump button Input
bool CPvcsWagoControl::GetPumpButtonInput(int pWagoUint, int pChannel, bool pInverted, int pInputType, int pRegBit, double pThreshold, bool &param_bStatus) {

	bool bSuccess = false;
	using namespace PvcsControlObjectTypes;

	UINT wagoUnit = pWagoUint;
	UINT channel  = pChannel;

	try {

		CControlWago750 *pwc = dynamic_cast<CControlWago750 *>(m_WagoList.at(wagoUnit));

		if (!pwc) throw exception("Invalid Controller pointer");
		if (pRegBit != -1) {
			pInputType = 2;
		}
		switch (pInputType) {
		case 0: // Digital
			{
				CControlWago750::BufferOffsetEnum Offset;
				switch (m_WagoList.at(wagoUnit)->GetModBusDeviceType()) {
				default:
				case MODBUS_DEVICE_WAGO:
					if (channel >= 0 && channel < 0x200) {
						Offset = CControlWago750::OffsetDigitalIn;
					} else {
						Offset = CControlWago750::OffsetDigitalOut;
					}
					break;
				case MODBUS_DEVICE_WÄRTSILA:
					Offset = CControlWago750::OffsetDigitalIn;
					break;
				}
				param_bStatus = pwc->GetValue(Offset, channel, " ") != 0;
			}
			if (pInverted) param_bStatus = !param_bStatus;
			break;

		case 2: // Digital regbit
			{
				CControlWago750::BufferOffsetEnum Offset;
				switch (m_WagoList.at(wagoUnit)->GetModBusDeviceType()) {
				default:
				case MODBUS_DEVICE_WAGO:
					if (channel >= 0 && channel < 0x200) {
						Offset = CControlWago750::OffsetAnalogInput;
					} else {
						Offset = CControlWago750::OffsetAnalogOutput;
					}
					break;
				case MODBUS_DEVICE_WÄRTSILA:
					Offset = CControlWago750::OffsetAnalogInput;
					break;
				}
				param_bStatus = pwc->GetValue(Offset, channel, " ") >> pRegBit & 1;
			}
			if (pInverted) param_bStatus = !param_bStatus;
			break;
		case 1: // Analog
			{
				CControlWago750::BufferOffsetEnum Offset;
				switch (m_WagoList.at(wagoUnit)->GetModBusDeviceType()) {
				default:
				case MODBUS_DEVICE_WAGO:
					if (channel >= 0 && channel < 0x200) {
						Offset = CControlWago750::OffsetAnalogInput;
					} else {
						Offset = CControlWago750::OffsetAnalogOutput;
					}
					break;
				case MODBUS_DEVICE_WÄRTSILA:
					Offset = CControlWago750::OffsetAnalogInput;
					break;
				}

				unsigned RawVal   = pwc->GetValue(Offset, channel, " ");
				unsigned InputStatus  = RawVal & 0x3;
				switch (InputStatus) {
				case 3: // Open loop
					param_bStatus = false;
					if (!theApp.m_pdlgManualControl) {
						theApp.bIsEmegencySwitchFault = true;
						theApp.m_pdlgManualControl = new CManualControlDialog;
						theApp.m_pdlgManualControl->Create(IDD_PVCS_MANUAL_CTRL_DLG);
						theApp.m_pdlgManualControl->ShowWindow(SW_SHOW);
						RECT Rect;

						theApp.m_pdlgManualControl->GetClientRect(&Rect);

						theApp.m_pdlgManualControl->MoveWindow(Rect.left + 600, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, true);
					}
					theApp.m_pdlgManualControl->SetDlgItemText(IDC_STATIC, "Pump button Short circuit!");
					break;
				case 1: // Short circuit
					param_bStatus = false;
					if (!theApp.m_pdlgManualControl) {
						theApp.bIsEmegencySwitchFault = true;
						theApp.m_pdlgManualControl = new CManualControlDialog;
						theApp.m_pdlgManualControl->Create(IDD_PVCS_MANUAL_CTRL_DLG);
						theApp.m_pdlgManualControl->ShowWindow(SW_SHOW);
						RECT Rect;
						theApp.m_pdlgManualControl->GetClientRect(&Rect);

						theApp.m_pdlgManualControl->MoveWindow(Rect.left + 600, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, true);
					}
					theApp.m_pdlgManualControl->SetDlgItemText(IDC_STATIC, "Pump button Open loop!");
					break;
				case 0: // Input signal OK
					{
						double AnalogValue = 32 * double(RawVal >> 3) / double(0x1000) / 1000;
						if (AnalogValue >= pThreshold) {
							// Update text if open Warning window open.
							param_bStatus = true;
						} else {
							param_bStatus = false;
						}
						if (pInverted) {
							param_bStatus = !param_bStatus;
						}
						theApp.bIsEmegencySwitchFault = false;
					}
					break;
				}
			}
			break;
		}


		bSuccess = true;
	} catch (exception &e) {
		//TRACE("*****CPvcswagocontrol-getvalue++++++ Digital******Channel = %d",channel);
		XmlLogError(e.what());
		bSuccess = false;
	}
	return bSuccess;

}

//Get Pump button Input
bool CPvcsWagoControl::GetPumpButtonInput(DigitalSignal pDigitalSignal, bool &param_bStatus) {

	bool bSuccess = false;
	using namespace PvcsControlObjectTypes;

	try {

		CControlWago750 *pwc = dynamic_cast<CControlWago750 *>(m_WagoList.at(pDigitalSignal.Port.WagoUnit));

		if (!pwc) throw exception("Invalid Controller pointer");
		if (pDigitalSignal.BitNo == -1) {
			CControlWago750::BufferOffsetEnum Offset;
			switch (m_WagoList.at(pDigitalSignal.Port.WagoUnit)->GetModBusDeviceType()) {
			default:
			case MODBUS_DEVICE_WAGO:
				if (pDigitalSignal.Port.WagoChannel >= 0 && pDigitalSignal.Port.WagoChannel < 0x200) {
					Offset = CControlWago750::OffsetDigitalIn;
				} else {
					Offset = CControlWago750::OffsetDigitalOut;
				}
				break;
			case MODBUS_DEVICE_WÄRTSILA:
				Offset = CControlWago750::OffsetDigitalIn;
				break;
			}
			param_bStatus = pwc->GetValue(Offset, pDigitalSignal.Port.WagoChannel, " ") != 0;
			if (pDigitalSignal.IsInverted) param_bStatus = !param_bStatus;
		} else {
			CControlWago750::BufferOffsetEnum Offset;
			switch (m_WagoList.at(pDigitalSignal.Port.WagoUnit)->GetModBusDeviceType()) {
			default:
			case MODBUS_DEVICE_WAGO:
				if (pDigitalSignal.Port.WagoChannel >= 0 && pDigitalSignal.Port.WagoChannel < 0x200) {
					Offset = CControlWago750::OffsetAnalogInput;
				} else {
					Offset = CControlWago750::OffsetAnalogOutput;
				}
				break;
			case MODBUS_DEVICE_WÄRTSILA:
				Offset = CControlWago750::OffsetAnalogInput;
				break;
			}
			param_bStatus = pwc->GetValue(Offset, pDigitalSignal.Port.WagoChannel, " ") >> pDigitalSignal.BitNo & 1;
			if (pDigitalSignal.IsInverted) param_bStatus = !param_bStatus;
		}
		bSuccess = true;
	} catch (exception &e) {
		//TRACE("*****CPvcswagocontrol-getvalue++++++ Digital******Channel = %d",channel);
		XmlLogError(e.what());
		bSuccess = false;
	}
	return bSuccess;

}


bool GetPumpButtonInput(DigitalSignal pDigitalSignal, bool &param_bStatus);
