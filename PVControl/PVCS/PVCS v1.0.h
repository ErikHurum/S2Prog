// PVCS v1.0.h : main header file for the PVCS v1.0 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "pvcsshipdata.h"
#include "senddata.h"
#include "calibrationdata.h"//Added by JSD 30-08-2007
#include "objectdetails.h"//Added by JSD 30-08-2007
#include "afxwin.h"
#include "WagoUnitStatus.h"
#include "ManualControlDialog.h"
#include "PvcsLodingDialog.h"
#include "ListButton.h"
#include <queue>
#include ".\emgbuttonoperation.h"
#include ".\pvcswagocontrol.h"

#define ID_EMG_TIMER 4350
#define ID_ALARM_VECTOR_TIMER 4351

#define BSPORT 2080
#define BRPORT 2081
#define DEST_ADDR "255.255.255.255"

UINT EmgButtonActionThread(LPVOID pParam);
UINT XmlWTQueuePush_Thread(LPVOID pParam);//Thread that push item in the queue


namespace SystemCheckErrorCodes{
	enum SystemError{
		NoError = 0x00,
		ErrorLowResolutionOnOne = 0x01,
		ErrorLowResolutionOnTwo = 0x02,
		ErrorNoTwoMonitors = 0x04
	};
};

class CCalibrateChannels;
//For Queue
enum XmlQueueOperationType { Message = 1, Timeout = 2, TimeoutWin = 3};

struct XmlQueue
{
	CString strScreenNumber;
	CString strObjectName;
	CString strMachineIP;
	CString strTime;
	CString strMessage;
	XmlQueueOperationType eType;
	bool bIsWarning_Timeout;
};

// CPVCSApp:
// See PVCS v1.0.cpp for the implementation of this class
//
class CPVCSApp : public CWinApp
{
	ULONG_PTR m_gdiplusToken;

public:
	CPVCSApp();

private:
	CString m_strMasterIP;
	int m_iMasterPort;
    bool m_bZoom;

	CWagoUnitStatus 	 *pobjWagoUnitStatus;
	bool m_bIsServer;
	CPvcsLodingDialog * m_ptrCPvcsLoadingDialog;
	CCalibrateChannels * m_ptrCCalibrateChannels;
	CString m_strWagoDisconnectMessage;

public:
	CString GetMasterIP(void);
	int GetMasterPort(void);

	CWagoUnitStatus* GetWagoUnitStatusDialog(void);
	void SetNULLWagoUnitStatusDialog(void);


	CPvcsLodingDialog * GetPvcsLoadingDialog(void);
	CCalibrateChannels * GetCalibrateChannels(void);
	void SetWagoDisconnectMessage(CString Message);
	static bool bStartNewEmgThread;
	//for queue
	queue <XmlQueue> XmlWTQueue;
	CCriticalSection m_csXmlQueue;
	CCriticalSection m_csXmlWTFile;
	bool m_bAlarmSoundOFF;
	//int iEmrOperationOver;

//static variables used for client server
public:

	static bool m_bIsTimerStarted;
	static bool m_bIsAlive;
	bool m_bIsCalibrationFileTransferComplete;

	HWND g_hwndTimedOwner;
	BOOL g_bTimedOut;

	// Overrides
public:
	virtual BOOL InitInstance();


	static int ScreenCount;
	static int ScreenIndex;
	bool IsBackupMode;
	bool IsSplashScreen;

//////////////////////////////////////////////

	//For emergency Operation
	char * strBroadcast;

	SOCKET SenderSocketFD;
	sockaddr_in Broad_Sender_Sendaddr;
	sockaddr_in Broad_Sender_Recvaddr;

	SOCKET ReceiverSocketFD;
	sockaddr_in Broad_Receiver_Sendaddr;
	sockaddr_in Broad_Receiver_Recvaddr;

///////////////////////////////////////////////
	CManualControlDialog  *m_pdlgManualControl;
	bool bIsEmegencySwitchFault;

	static bool bIsShipDataThreadExit;
	static HANDLE hEvent_ScreenThread;
	static CWinThread * ptrScreenThread;

	vector <CString> ConnectedClientMachineIP;

	void StartTimerCloseThread(void);
	void CloseCommandThread(void);
	void CloseReceiveCalibrationFileThread(void);
	void CloseWarningTimeoutTransferFileThread(void);
	void ClosingSignalOfClientToServer(void);
	bool Warning_TimeOut_XMLFileTransfereClient(int TypeOfOperation, int ScreenNumber);
	bool TransmitCalibrationFile(CString RemoteIP);

///////////////////////////////////////////

	//For emergency operation
void InitBroadcast(void);
bool SendBroadcastMessage(CString Message);
void RecvBroadcastMessage(CString &Message,UINT Timetowait = 0);
void EmergencyOperation(void);
UINT GetBroadcastMessage(CString Message, CString &strIP, CString &strMessage);
bool ConnectEmgOptMachine(CString strIP);
bool ClientEmergencyOperation(void);
/////////////////////////////////////////

		// Implementation
	int inet_pton(int af, const char *src, void *dst);
	CString GetLocalIP();
	bool IsServerMachine(CString pServerIP, CString pLocalIP);
	bool IsServerMachine(void);
	bool ZoomEnabled(void);
	bool RevokingCommandFromClient(int RevokingScreenNumber);
	bool RequestingCommandFromMaster(int RequestingScreenNumber);
	bool RequestingCommandFromClient(int RequestingScreenNumber, CString CommandingMachineIP);
	bool SendAlarmDataToIPS(CString Buffer);


public:

	afx_msg void OnAppAbout();
	afx_msg void OnFileAlarm();

	////////////////////////////
	afx_msg void OnCalibrateChannels(void);
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	SystemCheckErrorCodes::SystemError CheckValidSystem(void);
public:
	void HideTaskBar(BOOL param_bHide = TRUE);

private:
	CString m_hresponse;
	HANDLE m_hMutex;

	// to start the server to handle the command request
	//CSendData m_CommandServer;
//public:

public:
	afx_msg void OnAppExit();
	afx_msg void OnAnwin();
	afx_msg void OnFileTimeoutlist();
	afx_msg void OnUpdateFileCalibrate(CCmdUI *pCmdUI);
	afx_msg void OnFileWagounitstatus();
};

extern CPVCSApp theApp;



//CCalibrateChannels class defination

class CCalibrateChannels : public CDialog,public CCalibrationData
{
public:
	CCalibrateChannels();

// Dialog Data
	enum { IDD = IDD_CALIBRATEWAGO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	bool CalibrateChannels();
	virtual BOOL OnInitDialog();


// Implementation
protected:
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	 struct CalibrateData
	{
		CString ObjectName;
		CString ObjectToolTip;
		CString TankName;
		CString WagoUnitType;
		CString Type;
		CString Channel;
		CString WagoUnitNumber;
		CString StartText;
		CString StopText;
		CListButton *ptrStartListButton;
		CListButton *ptrStopListButton;
		UINT uiControlIndex;
		UINT uiControlSubIndex;
		bool StartButtonClicked;
	};

	static vector <CalibrateData> m_CalibrationData;

	void UpdateView(void);
	void SetItemText(int Row, int Col, CString Text);
	void UpdateCalibrationXMLFile(int Row);

	CObjectDetails m_ObjectDetails;
	CObjectDetails Obj_ObjectDetails;

private:
	// Store stsrt value
	//CEdit m_StartValue;

public:

	// to fill the combo with object name
	 //CComboBox *m_ComboObjectName;
	 //CComboBox *m_ComboChannelNumber;
	 //CString m_intStartValue;
	 //CString m_intStopValue;
	 //CString m_ComboSelObjectName;
	 //CString m_ComboSelChannelNumber;
	 //CString m_strTankName;
	 //afx_msg void OnCbnSelchangeCombochannelnumber();
	 //afx_msg void OnBnClickedCancel();
	 // to chk xml file load
	 bool m_XMLFileload;
	 // to show calibration data
	 //CListCtrl m_ListCalibrationGrid;
	CListCtrl m_ListCalibrationList;
	 //afx_msg void OnLvnItemchangedCalibrationList(NMHDR *pNMHDR, LRESULT *pResult);
	 //CButton OnVariable;
	 //afx_msg void OnEnChangeEditstartcalibration();
	 //CString CurrentObjectWagoUnitType;
	 //CString CurrentTankName;

	 //void FillCalbrationGrid(void);
	 //
	 //afx_msg void OnNMClickCalibrationList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndScrollCalibrationList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnDividerdblclickCalibrationList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnEndtrackCalibrationList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnBegintrackCalibrationList(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_StatusText;


};

static void CALLBACK AlarmBeepTimer(HWND hwnd, UINT msg, UINT interval, DWORD dwTime);



