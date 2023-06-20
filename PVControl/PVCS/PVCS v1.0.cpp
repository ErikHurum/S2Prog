// PVCS v1.0.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
//#include <Ws2tcpip.h>
#include "splashwnd.h"
#include "pvcsconfiguration.h"
#include "PVCSAlarmCtrl.h"//Added JSD
#include "pvcstankdlg.h"//Added JSD
#include "afxwin.h"
//#include "objectdetails.h"  blocked JSD 30-08-2007
#include "calibratewago.h"
#include "afxcmn.h"
#include "pvcsScreenThread.h"
#include "pvcsscreeninfo.h"
//#include "LoadingPvcsFrame.h"
#include ".\pvcs v1.0.h"
#include "psapi.h"
#include "winsock2.h"
#include <ws2tcpip.h>
#include "TimeOutListWin.h"//Added JSD 07-09-2007
#include "writetimeouts.h"//Added JSD 05-10-2007

#include "PVCSWarningMessage.h"
#include "WagoUnitStatus.h"
#include "ListButton.h"
#include "errorlog.h"

#include "emgbuttonoperation.h"
//#include "PumpButtonOperation.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif



// CPVCSApp
int CPVCSApp::ScreenCount = -1;
int CPVCSApp::ScreenIndex = 0;
bool CPVCSApp::m_bIsAlive = true;
bool CPVCSApp::m_bIsTimerStarted = false;
HANDLE CPVCSApp::hEvent_ScreenThread = NULL;
CWinThread *CPVCSApp::ptrScreenThread = NULL;
bool CPVCSApp::bIsShipDataThreadExit = false;
bool CPVCSApp::bStartNewEmgThread = true;

//Calibration vector
struct CCalibrateChannels::CalibrateData;
vector<CCalibrateChannels::CalibrateData> CCalibrateChannels::m_CalibrationData;
vector<CCalibrateWago::CalibrateData> CCalibrateWago::m_CalibrateData;



UINT EmgOperationOver(LPVOID pParam); //Thread that keep track when emergency operation of all the control will be over and broadcast over message
UINT InitiateEmgOperation(LPVOID pParam); //Thread that initiate emergency operations
UINT ClientEmgOperation(LPVOID pParam); //Thread, client's response on emg. operation
UINT EmgOperation(LPVOID pParam); //Thread sense the input on wago unit for emergency operation
UINT ServerThreadProc(LPVOID pParam); //for request command, at master side
UINT ClientThreadProc(LPVOID pParam); //for take command, at client side
UINT Warning_TimeOut_XMLFileThread(LPVOID pParam); //for sending and receiving warning and timeout xml file data to and from client, at master side
UINT ReceiveCalibrateXmlFile(LPVOID pParam); //to receive calibration xml file data, at client side
UINT ClientSendUPSignalToServerThread(LPVOID pParam); //this thread inform the master machine about client IP, and also recv calibration xml file
UINT XmlWTQueueOperation_Thread(LPVOID pParam); //Thread for xml warning_timeout file update and pop item from the queue
UINT XmlWTQueuePush_Thread(LPVOID pParam); //Thread that push item in the queue
UINT PumpThreadProc(LPVOID pParam); // To handle pumps including transfer of command

BEGIN_MESSAGE_MAP(CPVCSApp, CWinApp)
ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
ON_COMMAND(ID_FILE_CALIBRATE, OnCalibrateChannels)
ON_COMMAND(ID_FILE_ALARM, OnFileAlarm)
ON_COMMAND(ID_APP_EXIT, OnAppExit)
ON_COMMAND(ID_ANWIN, OnAnwin)
ON_COMMAND(ID_FILE_TIMEOUTLIST, OnFileTimeoutlist)
ON_UPDATE_COMMAND_UI(ID_FILE_CALIBRATE, OnUpdateFileCalibrate)
ON_COMMAND(ID_FILE_WAGOUNITSTATUS, OnFileWagounitstatus)
END_MESSAGE_MAP()





CPVCSApp::CPVCSApp() {
}

CPVCSApp theApp;

// CPVCSApp initialization

BOOL CPVCSApp::InitInstance() {
	m_pdlgManualControl = NULL;
	bIsEmegencySwitchFault = false;
	m_hMutex = CreateMutex(NULL, false, "PVCS - Single Instance");

	//if PVCS already running then, highlight the first screen
	if (WaitForSingleObject(m_hMutex, 1000) != WAIT_OBJECT_0) {
		HWND hWnd = FindWindow(NULL, "PVCS");
		char strScreenWndHandle[20];
		GetDlgItemText(hWnd, IDC_PVCS_HANDLE, strScreenWndHandle, 20);
		unsigned long iScreenHandle = atol(strScreenWndHandle);
		HWND hScreen = (HWND)iScreenHandle;
		ShowWindow(hScreen, SW_SHOW);
		SetForegroundWindow(hScreen);
		return FALSE;
	} // if( WaitForSingleObject( m_hMutex, 1000 ) != WAIT_OBJECT_0 )

	using namespace SystemCheckErrorCodes;

	InitCommonControls();
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	CWin32Exception::install_handler();
	CWinApp::InitInstance();

	//get splash screen need or not
	IsSplashScreen = theConfiguration().GetSplashState();

	if (IsSplashScreen) {
		CSplashWnd wndSplash;

		if (wndSplash.DoModal() == IDCANCEL) return FALSE;
	}


	//show loading pvcs dialog
	m_ptrCPvcsLoadingDialog = new CPvcsLodingDialog;

	m_pMainWnd = m_ptrCPvcsLoadingDialog;

	if (!theShipData()) {
		AfxMessageBox("Error in configuration file", MB_ICONERROR);
		delete m_ptrCPvcsLoadingDialog;
		return FALSE;
	}

	//get backup state
	IsBackupMode = theConfiguration().GetBackupState();

	if (!IsBackupMode) {
		HideTaskBar();

		CString errText("Following problems were detected during initialization. Pvcs may not work properly.\n");

		SystemError enumError = CheckValidSystem();
		using namespace SystemCheckErrorCodes;

		if (enumError & ErrorNoTwoMonitors) errText += " - Dual monitors not detected.\n";

		if (enumError & ErrorLowResolutionOnOne) errText += " - Resolution less than 1024 by 768 pixels on Screen One.\n";

		if (enumError & ErrorLowResolutionOnTwo) errText += " - Resolution less than 1024 by 768 pixels on Screen Two.\n";

		if (enumError != NoError) AfxMessageBox(errText, MB_OK | MB_ICONINFORMATION);
	}

	if (!AfxSocketInit()) {
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		delete m_ptrCPvcsLoadingDialog;
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit()) {
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		delete m_ptrCPvcsLoadingDialog;
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	try {

		CCalibrateWago objCalibrateWago;

		CCriticalSection objcriticalSection;

		objcriticalSection.Lock();

		if (objCalibrateWago.LoadXMLFile("xmlfiles\\calibrate.xml")) {
			CCalibrateWago::m_CalibrateData.clear();
			objCalibrateWago.GetCalibrationDataVector();
		}

		objcriticalSection.Unlock();

		pobjWagoUnitStatus = NULL;
		m_bIsServer = false;
		m_bZoom     = false;
		m_bIsCalibrationFileTransferComplete = true;
		m_strWagoDisconnectMessage = "";

		CPVCSApp::ScreenCount = theConfiguration().GetScreenCount();

		if (CPVCSApp::ScreenCount == -1) {
			AfxMessageBox("Unspecified number of screen count.", MB_APPLMODAL | MB_ICONERROR | MB_TOPMOST, 0);
			delete m_ptrCPvcsLoadingDialog;
			return FALSE;
		}

		m_ptrCPvcsLoadingDialog->m_PVCSProgressCtrl.SetRange(0, 100);
		m_ptrCPvcsLoadingDialog->m_PVCSProgressCtrl.SetPos(2);

		//Calculate step
		int StepValue = int(98 / ScreenCount);

		m_ptrCPvcsLoadingDialog->m_PVCSProgressCtrl.SetStep(StepValue);


		m_strMasterIP      = theConfiguration().GetMasterIP();
		CString strLocalIP = GetLocalIP();
		m_bIsServer = IsServerMachine(m_strMasterIP, strLocalIP);

		m_iMasterPort = theConfiguration().GetMasterPort();
		m_bZoom       = theConfiguration().GetZoomEnabled();




		if (m_strMasterIP.IsEmpty() ) {
			AfxMessageBox("Unable to get Master IP.", MB_ICONERROR | MB_APPLMODAL, 0);
			delete m_ptrCPvcsLoadingDialog;
			return false;
		}
		if (strLocalIP.IsEmpty()) {
			AfxMessageBox("Unable to get Local IP.", MB_ICONERROR | MB_APPLMODAL, 0);
			delete m_ptrCPvcsLoadingDialog;
			return false;
		}



		//For storing Button Info, and creating vector to hold the Control info for Buttons
		UINT uiEmgButtonCount = theConfiguration().GetEmgButtonCount();

		if (uiEmgButtonCount > 0) { //if any emergency button defined
			for (unsigned i = 1; i <= uiEmgButtonCount; i++) {
				CEmgButtonOperation::ButtonInfo  *pButtonInfo;
				pButtonInfo = new CEmgButtonOperation::ButtonInfo;

				pButtonInfo->Next_ControlInfo = NULL;
				pButtonInfo->strButtonText = "";
				pButtonInfo->bInvertInput = false;
				pButtonInfo->iWagoChNo = -1;
				pButtonInfo->iWagoUnit = -1;
				pButtonInfo->bButtonState = true;
				pButtonInfo->bIsOperationGoing = false;
				pButtonInfo->bIsEmgLightON = false;
				pButtonInfo->iTotalOperation = 0;
				pButtonInfo->bResetAllOutputs = false;

				CEmgButtonOperation::m_EmgButtonInfo.push_back(pButtonInfo);
			}
		}


		//For storing Button Info, and creating vector to hold the Control info for Buttons
		UINT uiPumpButtonCount = theConfiguration().GetPumpButtonCount();

		if (uiPumpButtonCount > 0) { //if any pump button defined
			for (unsigned i = 1; i <= uiPumpButtonCount; i++) {
				CPumpButtonOperation::ButtonInfo  *pButtonInfo;
				pButtonInfo = new CPumpButtonOperation::ButtonInfo;

				pButtonInfo->strButtonText = "";
				pButtonInfo->bButtonState = true;
				pButtonInfo->bIsOperationGoing = false;
				pButtonInfo->bIsPumpLightON = false;

				CPumpButtonOperation::m_PumpButtonInfo.push_back(pButtonInfo);
			}
		}

		//iEmrOperationOver = 0;

		//Thread creation
		CPVCSApp::hEvent_ScreenThread = CreateEvent(NULL, TRUE, FALSE, "Thread Event");
		SetEvent(CPVCSApp::hEvent_ScreenThread);
		for (int i = 1; i <= CPVCSApp::ScreenCount; i++) {
			//TRACE("%d Thread Starting\n",i);
			CPVCSApp::ScreenIndex = i;
			CWinThread *pThread = AfxBeginThread(RUNTIME_CLASS(CPvcsScreenThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
			pThread->m_bAutoDelete = true; //EHSMark
			pThread->ResumeThread();
			CString strLoading;
			strLoading.Format("Creating Picture - %s", theConfiguration().GetScreenTitle(i));
			m_ptrCPvcsLoadingDialog->SetDlgItemText(IDC_LOADING_PVCS_TEXT, strLoading);
			m_ptrCPvcsLoadingDialog->ShowWindow(SW_SHOWNA);
			m_ptrCPvcsLoadingDialog->UpdateWindow();
			//TRACE("Main Thread Waiting for %d thread finish\n",i);
			WaitForSingleObject(CPVCSApp::hEvent_ScreenThread, INFINITE);
			if (CPVCSApp::ScreenIndex == 1) {
				if (m_strWagoDisconnectMessage != "") AfxMessageBox(m_strWagoDisconnectMessage, MB_SETFOREGROUND | MB_ICONINFORMATION, 0);
			}
			if (CPVCSApp::ScreenIndex == CPVCSApp::ScreenCount) { //if last picture
				m_ptrCPvcsLoadingDialog->m_PVCSProgressCtrl.SetPos(100);
			} else m_ptrCPvcsLoadingDialog->m_PVCSProgressCtrl.StepIt();
			m_ptrCPvcsLoadingDialog->UpdateWindow();
			//TRACE("Main thread Wait Over for %d thread finish\n",i);
		}
		CloseHandle(CPVCSApp::hEvent_ScreenThread);

		//start thread to get data from the IPS
		AfxBeginThread(GetDataFromIPSThread, NULL);

		m_ptrCPvcsLoadingDialog->ShowWindow(SW_SHOWMINNOACTIVE);
		m_ptrCPvcsLoadingDialog->ShowWindow(SW_HIDE);
		//wait so that thread(GetDataFromIPSThread) perform some initial work
		Sleep(100);

		//showing and updating screen, for displaying in single stroke
		//for(int i=CPvcsScreenInfo::m_vecScreenInfo.size()-1; i>=0; i--)
		for (unsigned i = 0; i < CPvcsScreenInfo::m_vecScreenInfo.size(); i++) {
			CPvcsScreenInfo *CurrentScreen = (CPvcsScreenInfo *)CPvcsScreenInfo::m_vecScreenInfo[i];
			if (i == 0) { //storing screen handle in pvcs loading dialog , for reteriving handle.
				CString strScreenTitle = "";
				strScreenTitle.Format("%uld", CurrentScreen->m_ptrScreenFrame->m_hWnd);
				m_ptrCPvcsLoadingDialog->SetDlgItemText(IDC_PVCS_HANDLE, strScreenTitle);
			}
			CurrentScreen->m_ptrScreenFrame->ShowWindow(SW_SHOW);
			CurrentScreen->m_ptrScreenFrame->UpdateWindow();
			//for showing "ballast - command mode"
			CurrentScreen->m_ptrScreenFrame->SetTimer(IDT_UPDATE_VALUES, UPDATE_DELAY_TIMER, NULL);
			//wait so that thread (Screen Thread)perform some initial work
			Sleep(100);
		}

		m_ptrCPvcsLoadingDialog->ShowWindow(SW_SHOWMINNOACTIVE);
		m_ptrCPvcsLoadingDialog->ShowWindow(SW_HIDE);

		if (m_bIsServer) {
			AfxBeginThread(ServerThreadProc, 0); //Thread for Command, at server side for serving "Request Command"
			AfxBeginThread(PumpThreadProc, 0); //Thread to handle pumps including transfer of command
		}
		else AfxBeginThread(ClientSendUPSignalToServerThread, 0); //Thread for sending signal to master to inform about client ip and recv calibrate.xml file


		//if machine is server, then start server's thread, else client's thread
		if (m_bIsServer) {
			AfxBeginThread(Warning_TimeOut_XMLFileThread, 0); //Thread for transfer and receiving warning and timeout file data to and forth between client and master
		} else {
			AfxBeginThread(ClientThreadProc, 0); //Thread for command, at client side for serving "Take command"
			AfxBeginThread(ReceiveCalibrateXmlFile, 0); //Thread to receive calibration file
		}

		AfxBeginThread(XmlWTQueueOperation_Thread, 0); //Thread to do queue operation, for xml file

		//For Alarm button, filling Alarm vector
		SetTimer(NULL, ID_ALARM_VECTOR_TIMER, 5000, (TIMERPROC)AlarmBeepTimer);


		//For Emergency Operation
		InitBroadcast();

		//Thread to sense the wago input
		AfxBeginThread(EmgOperation, 0);

		//SetTimer(NULL,ID_EMG_TIMER,500,(TIMERPROC)EmgergencyTimer);


	} catch (exception &e) {
		//TRACE("*******cpvcsapp-initinstance*****");
		XmlLogError("Initialize Failed");
		XmlLogError(e.what());
		if (CPvcsScreenInfo::m_vecScreenInfo.size() > 0) {
			CPvcsScreenInfo *CurrentScreen = (CPvcsScreenInfo *)CPvcsScreenInfo::m_vecScreenInfo[0];
			CurrentScreen->m_ptrScreenFrame->SendMessage(WM_CLOSE);
		}
		delete m_ptrCPvcsLoadingDialog;
		return FALSE;
	}

	return TRUE;
}

CString CPVCSApp::GetMasterIP(void) {
	return m_strMasterIP;
}

int CPVCSApp::GetMasterPort(void) {
	return m_iMasterPort;
}


bool CPVCSApp::IsServerMachine(void) {
	return m_bIsServer;
}

bool CPVCSApp::ZoomEnabled(void) {
	return m_bZoom;
}


CPvcsLodingDialog* CPVCSApp::GetPvcsLoadingDialog(void) {
	return m_ptrCPvcsLoadingDialog;
}

///////////For emergency Operation/////////////

//function to initialize the broadcasting socket
void CPVCSApp::InitBroadcast(void) {

	strBroadcast = "1";
	//Sender Init
	if ((SenderSocketFD = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		AfxMessageBox("Error in creating sender socket", 0, 0);
	}

	if ((setsockopt(SenderSocketFD, SOL_SOCKET, SO_BROADCAST, strBroadcast, sizeof(strBroadcast))) == -1) {
		AfxMessageBox("Error in setting option of sender socket", 0, 0);
	}

	Broad_Sender_Sendaddr.sin_family = AF_INET;
	Broad_Sender_Sendaddr.sin_port = htons(BSPORT);
	Broad_Sender_Sendaddr.sin_addr.s_addr = INADDR_ANY;
	memset(Broad_Sender_Sendaddr.sin_zero, '\0', sizeof Broad_Sender_Sendaddr.sin_zero);

	if (bind(SenderSocketFD, (struct sockaddr *)&Broad_Sender_Sendaddr, sizeof Broad_Sender_Sendaddr) == -1) {
		AfxMessageBox("Error in binding sender socket", 0, 0);
	}

	Broad_Sender_Recvaddr.sin_family = AF_INET;
	Broad_Sender_Recvaddr.sin_port = htons(BRPORT);
	Broad_Sender_Recvaddr.sin_addr.s_addr = inet_addr(DEST_ADDR);
	memset(Broad_Sender_Recvaddr.sin_zero, '\0', sizeof Broad_Sender_Recvaddr.sin_zero);


	//Receiver Init
	if ((ReceiverSocketFD = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		AfxMessageBox("Error in creating receiver socket", 0, 0);
	}

	if ((setsockopt(ReceiverSocketFD, SOL_SOCKET, SO_BROADCAST, strBroadcast, sizeof(strBroadcast))) == -1) {
		AfxMessageBox("Error in setting option of receiver socket", 0, 0);
	}

	Broad_Receiver_Sendaddr.sin_family = AF_INET;
	Broad_Receiver_Sendaddr.sin_port = htons(BSPORT);
	Broad_Receiver_Sendaddr.sin_addr.s_addr = INADDR_ANY;
	memset(Broad_Receiver_Sendaddr.sin_zero, '\0', sizeof Broad_Receiver_Sendaddr.sin_zero);

	Broad_Receiver_Recvaddr.sin_family = AF_INET;
	Broad_Receiver_Recvaddr.sin_port = htons(BRPORT);
	Broad_Receiver_Recvaddr.sin_addr.s_addr = INADDR_ANY;
	memset(Broad_Receiver_Recvaddr.sin_zero, '\0', sizeof Broad_Receiver_Recvaddr.sin_zero);

	if (bind(ReceiverSocketFD, (struct sockaddr *)&Broad_Receiver_Recvaddr, sizeof Broad_Receiver_Recvaddr) == -1) {
		AfxMessageBox("Error in binding receiver socket", 0, 0);
	}

}

//function to send broadcast message
bool CPVCSApp::SendBroadcastMessage(CString Message) {
	CString strMessage = "";
	strMessage.Format("&&%s&&", Message);
	int cnBytesSend;

	int Addr_Len;
	char buf[100];

	Addr_Len = sizeof(Broad_Receiver_Sendaddr);

	if (cnBytesSend = sendto(SenderSocketFD, (LPCSTR)strMessage, strMessage.GetLength(), 0, (struct sockaddr *)&Broad_Sender_Recvaddr, sizeof Broad_Sender_Recvaddr) != -1) {
		recvfrom(ReceiverSocketFD, buf, sizeof buf, 0,(struct sockaddr *)&Broad_Receiver_Sendaddr,&Addr_Len);
		return true;
	} else return false;
}

//function to receive broadcast message
void CPVCSApp::RecvBroadcastMessage(CString &Message, UINT Timetowait) {
	int Addr_Len;
	char buf[100];
	buf[0] = '\0';
	Addr_Len = sizeof(Broad_Receiver_Sendaddr);

	if (Timetowait != 0) {
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(ReceiverSocketFD, &fds);
		//
		timeval CheckTimeOut;
		int Res;

		CheckTimeOut.tv_sec = Timetowait;
		CheckTimeOut.tv_usec = 0;

		Res = select(ReceiverSocketFD, &fds, NULL, NULL, &CheckTimeOut);

		//time over
		if (Res == 0) {
			Message = "timeout";
			return;
		}
	}

	recvfrom(ReceiverSocketFD, buf, sizeof buf, 0,(struct sockaddr *)&Broad_Receiver_Sendaddr,&Addr_Len);
	Message = buf;
}

UINT CPVCSApp::GetBroadcastMessage(CString Message, CString &strIP, CString &strMessage) {
	if (Message.MakeLower() == "timeout") return 1;
	else {
		int loc = Message.Find("&&");

		//"&&" found, starting marker
		if (loc != -1) {
			//removing starting marker
			Message.Delete(0, loc + 2);

			//finding end marker
			loc = Message.Find("&&");

			if (loc != -1)
				//removing ending marker
				Message.Delete(loc, Message.GetLength());
			else return 2;

			//finding "#"
			loc = Message.Find("#");

			if (loc != -1) {
				//seperating message into IP and Data
				strIP = Message.Left(loc);
				strMessage = Message.Right(Message.GetLength() - loc - 1);
				return 3;
			} else return 2;
		} else return 2;

	}

}

//connect to the machine that initiate the emergency operation
bool CPVCSApp::ConnectEmgOptMachine(CString strIP) {
	CString strMasterIP = theConfiguration().GetMasterIP();
	UINT port;

	if (strMasterIP == strIP) //Master machine initiate the emergency operation
		port = theApp.GetMasterPort();
	else //Client machine initiate the emergency operation
		port = theApp.GetMasterPort() - 1;

	SOCKET RequestSocket;

	//Create a socket
	RequestSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (RequestSocket == INVALID_SOCKET) return true;

	//connect socket to master machine
	sockaddr_in ServerRequestSocketaddr;

	ServerRequestSocketaddr.sin_family = AF_INET;
	ServerRequestSocketaddr.sin_addr.S_un.S_addr = inet_addr(strIP);
	ServerRequestSocketaddr.sin_port = htons((u_short)port);

	if (connect(RequestSocket, (SOCKADDR *)&ServerRequestSocketaddr, sizeof(ServerRequestSocketaddr)) == SOCKET_ERROR) {
		int iErrorCode = WSAGetLastError();

		closesocket(RequestSocket);
		//10064 = host is down, 10050 = network is down, 11001 = host not found, 10061 = connection refused
		if (iErrorCode == 10064 || iErrorCode == 10050 || iErrorCode == 11001 || iErrorCode == 10061) return false; //machine not present
		else return true;
	} else {
		//machine present
		closesocket(RequestSocket);
		return true;
	}

}

//Client machine sensing master initiating emergency operation
bool CPVCSApp::ClientEmergencyOperation(void) {
	CString strMessage = "";
	CString strIP = "";
	CString strData = "";
	UINT uReturnState = 0;

	while (1) {
		//wait for time based on IP, now 5 sec
		RecvBroadcastMessage(strMessage, 5);

		uReturnState = GetBroadcastMessage(strMessage, strIP, strData);

		if (uReturnState ==  1) { //message is timeout
								  //master machine not present, so client will start the operation
			break;
		} else if (uReturnState == 3) {
			//master initiated the operation
			if (strData.MakeLower() == "start") {
				//display operation strated message
				AfxMessageBox("Master machine initiated the Emergency operation.", MB_SETFOREGROUND | MB_ICONINFORMATION | MB_APPLMODAL | MB_TOPMOST, 0);

				//wait for operation over message from the master, and also check the master state
				while (1) {
					CString strConnectIP = "";
					CString strMachineIP = "";

					RecvBroadcastMessage(strMessage, 5);

					uReturnState = GetBroadcastMessage(strMessage, strMachineIP, strData);

					if (uReturnState == 3) {
						if (strData.MakeLower() == "over") { //master sends operation over message
															 //display message
							AfxMessageBox("Emergency operation completed.", MB_SETFOREGROUND | MB_ICONINFORMATION | MB_APPLMODAL | MB_TOPMOST, 0);
							break;
						} else if (strData.MakeLower() == "start") { //some other client machine sends operation start message
																	 //display operation strated message
							CString strTempIP = "";
							strTempIP.Format("Machine (%s) initiated the Emergency operation.", strMachineIP);
							strConnectIP = strMachineIP;
							AfxMessageBox(strTempIP, MB_SETFOREGROUND | MB_ICONINFORMATION | MB_APPLMODAL | MB_TOPMOST, 0);
						}
					} else if (uReturnState == 1) { //timeout, so check the machine state
													//operation initiating machine is not alive and now another machine will start the operation again
						strConnectIP = strIP;
						if (!ConnectEmgOptMachine(strConnectIP)) {
							;
						}
					} //else if(uReturnState == 1)
				} //while(1)
			} //if(strData.MakeLower() == "start")
			else continue;

			break;
		} //else if(uReturnState == 3)
	} //while(1)

	return true;
}





void CPVCSApp::EmergencyOperation(void) {
	CString strMessage = "";
	CString strSenderIP = "";
	CString strSenderMessage = "";

	//RecvBroadcastMessage(strMessage);

	strMessage = "4545&&10.140.1.114#yes&&111111111";
	//Valid message recv
	if (strMessage.MakeLower() != "timeout") {
		int loc = strMessage.Find("&&");
		//"&&" found
		if (loc != -1) {
			strMessage.Delete(0, loc + 2);
			loc = strMessage.Find("&&");
			if (loc != -1) strMessage.Delete(loc, strMessage.GetLength());
		}
		loc = strMessage.Find("#");
		if (loc != -1) {
			strSenderIP = strMessage.Left(loc);
			strSenderMessage = strMessage.Right(strMessage.GetLength() - loc - 1);
			if (strSenderMessage.MakeLower() == "yes") {
				CString strMessageBox = "";
				strMessageBox.Format("Emergency operation started by %s machine.", strSenderIP);
				///////////////
				AfxMessageBox(strMessageBox, 0, 0);

				while (true) {
					Sleep(5);
					//connect to the broadcasting machine

				}
			}
		}
	}
}

/////////////////////////////////////////////


//Thread for Queue
UINT XmlWTQueueOperation_Thread(LPVOID pParam) {
	while (theApp.m_bIsAlive) {
		for (int i = 0; theApp.XmlWTQueue.size(); i++) {
			XmlQueue tempXmlQueue;
			tempXmlQueue = theApp.XmlWTQueue.front(); //get first item

			if (tempXmlQueue.eType == Message) { //check type of message, if message
				CWriteTimeouts objWriteTimeout;

				theApp.m_csXmlWTFile.Lock(); //lock file access

				if (tempXmlQueue.bIsWarning_Timeout == true) { //when new warning message is added on the control
					if (objWriteTimeout.LoadTimeOutXML("xmlfiles\\warningTimeOut.xml")) {
						if (objWriteTimeout.FindScreen(tempXmlQueue.strScreenNumber)) { //if exists in xml file
							objWriteTimeout.NodeName_WarningMessage("WarningMessage", tempXmlQueue.strObjectName, tempXmlQueue.strMessage);
							objWriteTimeout.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
							theApp.m_csXmlWTFile.Unlock(); //Unlock file access
						} else { //if do not exists in xml file
							objWriteTimeout.GetRootPointer();
							objWriteTimeout.PreserveRootPointer(tempXmlQueue.strScreenNumber);
							objWriteTimeout.Create_Element_Function("WarningMessage");
							objWriteTimeout.WriteWarningMessageToFile(tempXmlQueue.strObjectName, tempXmlQueue.strMessage);
							objWriteTimeout.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
							theApp.m_csXmlWTFile.Unlock(); //Unlock file access
						}
					} else {
						objWriteTimeout.InitTimeoutHeader("xmlfiles\\warningTimeOut.xml", "Messages");
						objWriteTimeout.PreserveRootPointer(tempXmlQueue.strScreenNumber);
						objWriteTimeout.Create_Element_Function("WarningMessage");
						objWriteTimeout.WriteWarningMessageToFile(tempXmlQueue.strObjectName, tempXmlQueue.strMessage);
						objWriteTimeout.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
						theApp.m_csXmlWTFile.Unlock(); //Unlock file access
					}

					if (!theApp.IsServerMachine()) { //if client, then must send updated buffer to the master
						tempXmlQueue.strScreenNumber.MakeLower();
						tempXmlQueue.strScreenNumber.TrimLeft("sno");
						theApp.Warning_TimeOut_XMLFileTransfereClient(2, atoi(tempXmlQueue.strScreenNumber));
					}


					//int vectorsize = theController().WarningMessageVector.size();

					WarningMessageStroge tempobjWarningMessage;

					tempobjWarningMessage.ControlObjName = tempXmlQueue.strObjectName;

					CString tempabc;

					tempobjWarningMessage.ObjWarningMessage = tempXmlQueue.strMessage;

					theController().WarningMessageVector.push_back(tempobjWarningMessage);
				} //if(tempXmlQueue.bIsWarning_Timeout == true)
				else if (tempXmlQueue.bIsWarning_Timeout == false) { //when removing the warning message from the control
					if (objWriteTimeout.LoadTimeOutXML("xmlfiles\\warningTimeOut.xml")) {
						if (objWriteTimeout.FindScreen(tempXmlQueue.strScreenNumber)) { //if exists in xml file
							objWriteTimeout.Remove_ControlEntry_WarningMessage(tempXmlQueue.strScreenNumber, "WarningMessage", tempXmlQueue.strObjectName);
							objWriteTimeout.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
							theApp.m_csXmlWTFile.Unlock(); //Unlock file access
						} else theApp.m_csXmlWTFile.Unlock(); //Unlock file access
					} else theApp.m_csXmlWTFile.Unlock(); //Unlock file access
														  //send updated data to the master, on uncheck of warning message
					if (!theApp.IsServerMachine()) {
						tempXmlQueue.strScreenNumber.MakeLower();
						tempXmlQueue.strScreenNumber.TrimLeft("sno");
						theApp.Warning_TimeOut_XMLFileTransfereClient(2, atoi(tempXmlQueue.strScreenNumber));
					}
				}

			} else if (tempXmlQueue.eType == Timeout) { //check type of message, if timeout
				CWriteTimeouts objWriteTimeout;
				if (tempXmlQueue.bIsWarning_Timeout == true) {
					theApp.m_csXmlWTFile.Lock(); //lock file access
					if (objWriteTimeout.LoadTimeOutXML("xmlfiles\\warningTimeOut.xml")) {
						if (objWriteTimeout.FindScreen(tempXmlQueue.strScreenNumber)) { //if exists in xml file
							objWriteTimeout.NodeName_TimeOut("TimeOut", tempXmlQueue.strObjectName);
							objWriteTimeout.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
							theApp.m_csXmlWTFile.Unlock(); //Unlock file access
						} else { //if do not exists in xml file
							objWriteTimeout.GetRootPointer();
							objWriteTimeout.PreserveRootPointer(tempXmlQueue.strScreenNumber);
							objWriteTimeout.Create_Element_Function("TimeOut");
							objWriteTimeout.WriteTimeOutDataToFile(tempXmlQueue.strObjectName, tempXmlQueue.strMachineIP);
							objWriteTimeout.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
							theApp.m_csXmlWTFile.Unlock(); //Unlock file access
						}
					} else {
						objWriteTimeout.InitTimeoutHeader("xmlfiles\\warningTimeOut.xml", "Messages");
						objWriteTimeout.PreserveRootPointer(tempXmlQueue.strScreenNumber);
						objWriteTimeout.Create_Element_Function("TimeOut");
						objWriteTimeout.WriteTimeOutDataToFile(tempXmlQueue.strObjectName, tempXmlQueue.strMachineIP);
						objWriteTimeout.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
						theApp.m_csXmlWTFile.Unlock(); //Unlock file access
					}

					if (!theApp.IsServerMachine()) { //if client machine, then must send updated buffer to the master
						tempXmlQueue.strScreenNumber.MakeLower();
						tempXmlQueue.strScreenNumber.TrimLeft("sno");
						theApp.Warning_TimeOut_XMLFileTransfereClient(2, atoi(tempXmlQueue.strScreenNumber));
					}
				} else {   // write code to delete node from file.
					int vectorsize = CWriteTimeouts::m_WarningTimeout.size();
					if (vectorsize > 0) {
						for (int i = 0; i < vectorsize; i++) {
							CString objectName;
							objectName = CWriteTimeouts::m_WarningTimeout[i].ObjID;
							if (objectName == tempXmlQueue.strObjectName) {
								theApp.m_csXmlWTFile.Lock(); //lock file access
								if (objWriteTimeout.LoadTimeOutXML("xmlfiles\\warningTimeOut.xml")) {
									objWriteTimeout.Remove_ControlEntry_TimeOut(tempXmlQueue.strScreenNumber, "TimeOut", tempXmlQueue.strObjectName);

									objWriteTimeout.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
									theApp.m_csXmlWTFile.Unlock(); //Unlock file access
								} else theApp.m_csXmlWTFile.Unlock(); //Unlock file access
								if (!theApp.IsServerMachine()) {
									//this function send updated buffer to the master machine to update the xml file
									tempXmlQueue.strScreenNumber.MakeLower();
									tempXmlQueue.strScreenNumber.TrimLeft("sno");
									theApp.Warning_TimeOut_XMLFileTransfereClient(2, atoi(tempXmlQueue.strScreenNumber));
								}
							}
						}
					}
				}
			} else if (tempXmlQueue.eType == TimeoutWin) { //Time out window opens
				if (!theApp.IsServerMachine()) {
					//Get new updated timeout list from the server
					theApp.Warning_TimeOut_XMLFileTransfereClient(3, -1);
				}

				CWriteTimeouts objWriteTimeout;

				//Clear the Vector
				int size = objWriteTimeout.m_WarningTimeout.size();

				if (size > 0) objWriteTimeout.m_WarningTimeout.clear();

				theApp.m_csXmlWTFile.Lock(); //lock file access
				if (objWriteTimeout.LoadTimeOutXML("xmlfiles\\warningTimeOut.xml")) {
					objWriteTimeout.FillVector_TimeOut();
					objWriteTimeout.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
					theApp.m_csXmlWTFile.Unlock(); //unlock file access
				} else theApp.m_csXmlWTFile.Unlock(); //Unlock file access

				theCTimeOut().SetVectorUpdated(true); //Signal for the timer to update the list

				if (tempXmlQueue.bIsWarning_Timeout) { //only at the time of creating dialog
					if (theCTimeOut().m_TimeoutList) {
						theCTimeOut().m_TimeoutList.DeleteAllItems();
						int VectorSize1 = objWriteTimeout.m_WarningTimeout.size();

						for (int i = 0; i < VectorSize1; i++) {
							theCTimeOut().m_TimeoutList.InsertItem(i, objWriteTimeout.m_WarningTimeout[i].ObjID);
							theCTimeOut().m_TimeoutList.SetItemText(i, 1, objWriteTimeout.m_WarningTimeout[i].TimeRaised);
							theCTimeOut().m_TimeoutList.SetItemText(i, 2, objWriteTimeout.m_WarningTimeout[i].MachineIP);
							theCTimeOut().m_TimeoutList.SetItemText(i, 3, objWriteTimeout.m_WarningTimeout[i].Message);
						}
					}
				}
			}

			theApp.m_csXmlQueue.Lock();
			theApp.XmlWTQueue.pop(); //remove the item
			theApp.m_csXmlQueue.Unlock();
		}

		Sleep(2000);
	}
	return 0;
}

//thread push new xml message block into the queue
UINT XmlWTQueuePush_Thread(LPVOID pParam) {
	XmlQueue *ptrtempXmlQueue = (XmlQueue *)pParam;

	XmlQueue objtempXmlQueue;

	objtempXmlQueue.eType = ptrtempXmlQueue->eType;
	objtempXmlQueue.strMachineIP = ptrtempXmlQueue->strMachineIP;
	objtempXmlQueue.strMessage = ptrtempXmlQueue->strMessage;
	objtempXmlQueue.strObjectName = ptrtempXmlQueue->strObjectName;
	objtempXmlQueue.strScreenNumber = ptrtempXmlQueue->strScreenNumber;
	objtempXmlQueue.strTime = ptrtempXmlQueue->strTime;
	objtempXmlQueue.bIsWarning_Timeout = ptrtempXmlQueue->bIsWarning_Timeout;

	theApp.m_csXmlQueue.Lock();
	theApp.XmlWTQueue.push(objtempXmlQueue);
	theApp.m_csXmlQueue.Unlock();

	delete ptrtempXmlQueue;

	return 0;
}

// CPVCSApp message handlers

//Callback timer function, that post quit message, so that message box gets close on request timeout
void CALLBACK MessageBoxTimer(HWND hwnd, UINT uiMsg, UINT idEvent, DWORD dwTime) {
	theApp.g_bTimedOut = TRUE;
	if (theApp.g_hwndTimedOwner) EnableWindow(theApp.g_hwndTimedOwner, TRUE);
	PostQuitMessage(0);
}

//Timed message box function
int TimedMessageBox(HWND hwndOwner, LPCTSTR pszMessage, LPCTSTR pszTitle, UINT flags, DWORD dwTimeout) {
	UINT idTimer;
	int iResult;

	theApp.g_hwndTimedOwner = NULL;
	theApp.g_bTimedOut = FALSE;

	if (hwndOwner && IsWindowEnabled(hwndOwner)) theApp.g_hwndTimedOwner = hwndOwner;

	//
	// Set a timer to dismiss the message box.
	idTimer = SetTimer(NULL, 0, dwTimeout, (TIMERPROC)MessageBoxTimer);

	iResult = MessageBox(hwndOwner, pszMessage, pszTitle, flags);

	//
	// Finished with the timer.
	KillTimer(NULL, idTimer);

	//
	// See if there is a WM_QUIT message in the queue if we timed out.
	// Eat the message so we do not quit the whole application.
	if (theApp.g_bTimedOut) {
		MSG msg;
		PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);
		iResult = -1;
	}

	return iResult;
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog {
public:
	CAboutDlg();

	// Dialog Data
	enum {
		IDD = IDD_ABOUTBOX
	};

protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedEdit();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX) {
	CDialog::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog() {
	//CString ver = theConfiguration().GetConfigDataVersion();
	//SetDlgItemText(IDC_EDIT,"Version: 2.6.1.1\nConfiguration File Version:" + ver +"\nCopyright: Ariston Norway\nReleased: 29 Nov 2007");
	return true;
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
ON_BN_CLICKED(IDOK, OnBnClickedOk)
ON_STN_CLICKED(IDC_EDIT, OnStnClickedEdit)
END_MESSAGE_MAP()



// App command to run the dialog
void CPVCSApp::OnAppAbout() {
	//if any control window open, first close it
	if (theController().m_hWnd) ::SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);

	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//This function is used to send Ack Alarm to the IPS
bool CPVCSApp::SendAlarmDataToIPS(CString Buffer) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET PVCSSocket;

		PVCSSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (PVCSSocket == INVALID_SOCKET) {
			WSACleanup();
			return false;
		}

		//connect socket to IPS machine
		sockaddr_in PVCSSocketaddr;

		PVCSSocketaddr.sin_family = AF_INET;
		PVCSSocketaddr.sin_addr.S_un.S_addr = inet_addr(theConfiguration().GetSurveyorIP());
		PVCSSocketaddr.sin_port = htons((u_short)9997);

		if (connect(PVCSSocket, (SOCKADDR *)&PVCSSocketaddr, sizeof(PVCSSocketaddr)) == SOCKET_ERROR) {
			closesocket(PVCSSocket);
			WSACleanup();
			return false;
		} else { //if connect is oK, then send data
			int ByteSend = send(PVCSSocket, Buffer, Buffer.GetLength(), 0);
			if (ByteSend != SOCKET_ERROR) {
				closesocket(PVCSSocket);
				//WSACleanup();
				return true;
			}
			closesocket(PVCSSocket);
			WSACleanup();
			return false;
		}
	}
	return false;
}
// CPVCSApp message handlers

// CRequestCommandDlg dialog used for App About

class CCommandDlg : public CDialog {
public:
	CCommandDlg();

	// Dialog Data
	enum {
		IDD = ID_CONNECT
	};

protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	bool RequestCommand(CString param_IPAddress);


	// Implementation
protected:
	DECLARE_MESSAGE_MAP()


};

CCommandDlg::CCommandDlg() : CDialog(CCommandDlg::IDD) {
}

void CCommandDlg::DoDataExchange(CDataExchange *pDX) {
	CDialog::DoDataExchange(pDX);
}

bool CCommandDlg::RequestCommand(CString param_IPAddress) {
	return true;
}

BEGIN_MESSAGE_MAP(CCommandDlg, CDialog)

END_MESSAGE_MAP()


//added 5 feb rajan for calibration
// CPVCSApp message handlers

// CRequestCommandDlg dialog used for App About


void CPVCSApp::OnCalibrateChannels() {
	CCalibrateChannels obj_Calibrate;
	m_ptrCCalibrateChannels = &obj_Calibrate;
	obj_Calibrate.DoModal();

	CString strAnalog = "";

	//delete all CListButton pointers
	for (unsigned i = 0; i < CCalibrateChannels::m_CalibrationData.size(); i++) {
		strAnalog = CCalibrateChannels::m_CalibrationData[i].Type;

		if (strAnalog.MakeLower() == "analog") {
			delete CCalibrateChannels::m_CalibrationData[i].ptrStartListButton;
			delete CCalibrateChannels::m_CalibrationData[i].ptrStopListButton;

			CCalibrateChannels::m_CalibrationData[i].ptrStartListButton = NULL;
			CCalibrateChannels::m_CalibrationData[i].ptrStopListButton = NULL;
			CCalibrateChannels::m_CalibrationData[i].StartButtonClicked = false;
		}
	}


}

CCalibrateChannels* CPVCSApp::GetCalibrateChannels(void) {
	return m_ptrCCalibrateChannels;
}

CCalibrateChannels::CCalibrateChannels() : CDialog(CCalibrateChannels::IDD) {
	m_XMLFileload = false;
}

void CCalibrateChannels::DoDataExchange(CDataExchange *pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CALIBRATION_LIST, m_ListCalibrationList);
	DDX_Control(pDX, IDC_STATUS_TEXT, m_StatusText);
}


BEGIN_MESSAGE_MAP(CCalibrateChannels, CDialog)
ON_NOTIFY(LVN_ENDSCROLL, IDC_CALIBRATION_LIST, OnLvnEndScrollCalibrationList)
ON_NOTIFY(HDN_DIVIDERDBLCLICK, 0, OnHdnDividerdblclickCalibrationList)
ON_NOTIFY(HDN_ENDTRACK, 0, OnHdnEndtrackCalibrationList)
ON_NOTIFY(HDN_BEGINTRACK, 0, OnHdnBegintrackCalibrationList)
ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CCalibrateChannels::OnInitDialog() {
	CDialog::OnInitDialog();
	//m_ComboObjectName = (CComboBox *)GetDlgItem(IDC_OBJECTNAMECOMBO);
	//m_ComboChannelNumber = (CComboBox *)GetDlgItem(IDC_COMBOCHANNELNUMBER);
	InitializeXMLParcer();
	CString m_pcFilename;
	//m_ObjectDetails.GetCalibrationData();

	//InitializeXMLParcer();
	//m_XMLFileload = LoadXMLFile("XMLFILES\\calibrate.xml");

	//m_pcFilename="d:\\ariston\\sent14feb\\PVCS\\XMLFILES\\calibrate.xml";


	//CurrentObjectWagoUnitType = "461";
	//Obj_ObjectDetails.LoadXMLFile("XMLFILES\\detailconfig.xml");
//	Obj_ObjectDetails.GetCalibrationData();

	m_ListCalibrationList.SetExtendedStyle(m_ListCalibrationList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ListCalibrationList.InsertColumn(0, "Object Name");
	m_ListCalibrationList.InsertColumn(1, "Tool Tip Text");
	m_ListCalibrationList.InsertColumn(2, "Tank Name");
	m_ListCalibrationList.InsertColumn(3, "Wago Unit Type");
	m_ListCalibrationList.InsertColumn(4, "Channel Type");
	m_ListCalibrationList.InsertColumn(5, "Channel");
	m_ListCalibrationList.InsertColumn(6, "Start");
	m_ListCalibrationList.InsertColumn(7, "Stop");


	m_ListCalibrationList.SetColumnWidth(0, 100);
	m_ListCalibrationList.SetColumnWidth(1, 130);
	m_ListCalibrationList.SetColumnWidth(2, 100);
	m_ListCalibrationList.SetColumnWidth(3, 100);
	m_ListCalibrationList.SetColumnWidth(4, 100);
	m_ListCalibrationList.SetColumnWidth(5, 80);
	m_ListCalibrationList.SetColumnWidth(6, 120);
	m_ListCalibrationList.SetColumnWidth(7, 120);

	CString strAnalog = "";

	for (unsigned i = 0; i < m_CalibrationData.size(); i++) {
		CFont objFont;
		objFont.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Times New Roman");

		m_ListCalibrationList.SetFont(&objFont);
		m_ListCalibrationList.InsertItem(i, m_CalibrationData[i].ObjectName);
		m_ListCalibrationList.SetItemText(i, 1, m_CalibrationData[i].ObjectToolTip);
		m_ListCalibrationList.SetItemText(i, 2, m_CalibrationData[i].TankName);
		m_ListCalibrationList.SetItemText(i, 3, m_CalibrationData[i].WagoUnitType);
		m_ListCalibrationList.SetItemText(i, 4, m_CalibrationData[i].Type);

		strAnalog = m_CalibrationData[i].Type;

		if (strAnalog.MakeLower() == "analog") {
			CListButton * ptrStartListButtontemp,*ptrStopListButtontemp;

			ptrStartListButtontemp = new CListButton(i, 6);
			ptrStopListButtontemp = new CListButton(i, 7);

			CRect StartRect, StopRect;

			m_ListCalibrationList.GetSubItemRect(i, 6, LVIR_BOUNDS, StartRect);

			StartRect.left += 50;

			ptrStartListButtontemp->Create("Start", WS_CHILD | WS_VISIBLE, StartRect, (CWnd *)&m_ListCalibrationList, 12);
			ptrStartListButtontemp->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
			ptrStartListButtontemp->ShowWindow(SW_SHOW);

			m_ListCalibrationList.GetSubItemRect(i, 7, LVIR_BOUNDS, StopRect);

			StopRect.left += 50;

			ptrStopListButtontemp->Create("Stop", WS_CHILD | WS_VISIBLE, StopRect, (CWnd *)&m_ListCalibrationList, 13);
			ptrStopListButtontemp->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
			ptrStopListButtontemp->ShowWindow(SW_SHOW);

			m_CalibrationData[i].ptrStartListButton = ptrStartListButtontemp;
			m_CalibrationData[i].ptrStopListButton = ptrStopListButtontemp;

		}

		m_ListCalibrationList.SetItemText(i, 5, m_CalibrationData[i].Channel);
		m_ListCalibrationList.SetItemText(i, 6, m_CalibrationData[i].StartText);
		m_ListCalibrationList.SetItemText(i, 7, m_CalibrationData[i].StopText);

	}

	//CCalibrateWago objCalibrateWago;
	//
	////if calibrate.xml file exists
	//CCriticalSection objcriticalSection;

	//objcriticalSection.Lock();

	//if(objCalibrateWago.LoadXMLFile("xmlfiles\\calibrate.xml"))
	//{
	//	objCalibrateWago.GetCalibrationDataVector();

	for (unsigned i = 0; i < CCalibrateWago::m_CalibrateData.size(); i++) {
		CString strObjectName = "", strChannel = "";
		int iRow = atoi(CCalibrateWago::m_CalibrateData[i].Row);

		strObjectName = m_ListCalibrationList.GetItemText(iRow, 0);
		strChannel = m_ListCalibrationList.GetItemText(iRow, 5);

		if (strObjectName == CCalibrateWago::m_CalibrateData[i].ObjectName) {
			if (strChannel == CCalibrateWago::m_CalibrateData[i].Channel) {
				m_ListCalibrationList.SetItemText(iRow, 6, CCalibrateWago::m_CalibrateData[i].StartText);
				m_ListCalibrationList.SetItemText(iRow, 7, CCalibrateWago::m_CalibrateData[i].StopText);

			}
		}
	}
	//}

	//objcriticalSection.Unlock();

	//If sending file not completed, keep disable the controls
	if (theApp.m_bIsCalibrationFileTransferComplete) {
		CString strAnalog = "";
		for (unsigned i = 0; i < m_CalibrationData.size(); i++) {
			strAnalog = m_CalibrationData[i].Type;

			if (strAnalog.MakeLower() == "analog") {
				m_CalibrationData[i].ptrStartListButton->EnableWindow(1);
				m_CalibrationData[i].ptrStopListButton->EnableWindow(1);
			}
		}
		m_ListCalibrationList.EnableWindow(1);
		m_StatusText.ShowWindow(SW_HIDE);
	} else { //sending of file completed, enable the control
		CString strAnalog = "";
		for (unsigned i = 0; i < m_CalibrationData.size(); i++) {
			strAnalog = m_CalibrationData[i].Type;

			if (strAnalog.MakeLower() == "analog") {
				m_CalibrationData[i].ptrStartListButton->EnableWindow(0);
				m_CalibrationData[i].ptrStopListButton->EnableWindow(0);
			}
		}
		m_ListCalibrationList.EnableWindow(0);
		m_StatusText.ShowWindow(SW_SHOW);
	}

	SetTimer(1, 1000, NULL);
	return true;
}



void CPVCSApp::SetWagoDisconnectMessage(CString Message) {
	m_strWagoDisconnectMessage = Message;
}

// CPVCSApp message handlers
int CPVCSApp::ExitInstance() {
	//TRACE("\nCPVCSAPpp::ExitInstance");
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	//delete pobjWagoUnitStatus;

	ReleaseMutex(m_hMutex);
	CloseHandle(m_hMutex);

	for (unsigned i = 0; i < CCalibrateChannels::m_CalibrationData.size(); i++) {
		if (CCalibrateChannels::m_CalibrationData[i].Type.MakeLower() == "analog") {
			if (CCalibrateChannels::m_CalibrationData[i].ptrStartListButton != NULL) delete CCalibrateChannels::m_CalibrationData[i].ptrStartListButton;
			if (CCalibrateChannels::m_CalibrationData[i].ptrStopListButton != NULL) delete CCalibrateChannels::m_CalibrationData[i].ptrStopListButton;
		}
	}

	for (unsigned i = 0; i < CEmgButtonOperation::m_EmgButtonInfo.size(); i++) {
		CEmgButtonOperation::ControlInfo * pControlInfo,*pTempControlInfo;
		pControlInfo = CEmgButtonOperation::m_EmgButtonInfo[i]->Next_ControlInfo;
		delete CEmgButtonOperation::m_EmgButtonInfo[i];
		CEmgButtonOperation::m_EmgButtonInfo[i] = NULL;

		while (pControlInfo != NULL) {
			pTempControlInfo = pControlInfo->Next_ControlInfo;
			delete pControlInfo;
			pControlInfo = NULL;

			pControlInfo = pTempControlInfo;
		}

	}

	for (unsigned i = 0; i < CPumpButtonOperation::m_PumpButtonInfo.size(); i++) {
		CPumpButtonOperation::ControlInfo * pControlInfo,*pTempControlInfo;
		delete CPumpButtonOperation::m_PumpButtonInfo[i];
		CPumpButtonOperation::m_PumpButtonInfo[i] = NULL;
	}
	return CWinApp::ExitInstance();
}

SystemCheckErrorCodes::SystemError CPVCSApp::CheckValidSystem(void) {
	using namespace SystemCheckErrorCodes;
	UINT enumErrorCode = NoError;

	const int nReqRes = 1024;
	const int nMonitors = 2;

	int nMonOneRes  = GetSystemMetrics(SM_CXSCREEN);
	int nTotRes     = GetSystemMetrics(SM_CXVIRTUALSCREEN);

	if (GetSystemMetrics(SM_CMONITORS) != nMonitors) {
		enumErrorCode |= ErrorNoTwoMonitors;

		if (nMonOneRes < nReqRes) enumErrorCode |= ErrorLowResolutionOnOne;
	} else {
		if (nMonOneRes < nReqRes) enumErrorCode |= ErrorLowResolutionOnOne;

		if ((nTotRes - nMonOneRes) < nReqRes) enumErrorCode |= ErrorLowResolutionOnTwo;
	}

	return(SystemError)enumErrorCode;
}

void CPVCSApp::HideTaskBar(BOOL param_bHide) {
	// Find the shell AppBar
	HWND hWnd = ::FindWindow("Shell_traywnd", NULL);

	APPBARDATA AppBarData;
	AppBarData.hWnd = hWnd;
	AppBarData.cbSize = sizeof(AppBarData);

	// Get the AppBar state
	::SHAppBarMessage(ABM_GETSTATE, &AppBarData);

	// Set the AppBar to auto hide
	if (param_bHide) AppBarData.lParam = ABS_AUTOHIDE;
	else AppBarData.lParam = ABS_ALWAYSONTOP;

	::SHAppBarMessage(ABM_SETSTATE, &AppBarData);

	EnableWindow(hWnd, !param_bHide); // disable it
}





//jsd
void CPVCSApp::OnFileAlarm() { //Commented 23/04/2007 JSD
	if (CPVCSAlarmCtrl::IsAlmDlgOpen == false) {
		CPVCSAlarmCtrl::IsAlmDlgOpen = true;
		thePVCSAlmCtrl().DoModal();

	} else {
		thePVCSAlmCtrl().SetForegroundWindow();
	}
	//thePVCSAlmCtrl().Create(IDD_ALARM_DLG);
	//thePVCSAlmCtrl().ShowWindow(SW_SHOW);
}



void CPVCSApp::OnAppExit() {
	//if in backup mode then, send close message to the screen window
	if (IsBackupMode) {
		CPvcsScreenInfo *CurrentScreen = (CPvcsScreenInfo *)CPvcsScreenInfo::m_vecScreenInfo[0];
		CurrentScreen->m_ptrScreenFrame->PostMessage(WM_CLOSE);
	}
	/*
	CWriteTimeouts WriteTimeoutsObj2;
	int size2 = WriteTimeoutsObj2.m_WarningTimeout.size();
	if (size2 > 0) WriteTimeoutsObj2.m_WarningTimeout.clear();
	*/
	//CPvcsWagoControl::DeleteWagoControl();
	//exit(0);
}

//The following code is used to Enum window of a process
static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	DWORD dwPid;

	GetWindowThreadProcessId(hwnd, &dwPid);

	if (dwPid == (DWORD)lParam) {
		char cWindowTitle[255];
		GetWindowText(hwnd, cWindowTitle, 255);
		CString strWindowTitle = "";
		strWindowTitle.Format("%s", cWindowTitle);
		strWindowTitle.MakeLower();
		if (strWindowTitle.Find("anwin") == 0) {
			if (strWindowTitle.GetLength() > 5) {
				ShowWindow(hwnd, SW_SHOW);
				SetForegroundWindow(hwnd);
				return false;
			}
		}
	}

	return TRUE;
}

//Function to switch to AnWin
void CPVCSApp::OnAnwin() {
	//if any control window open, first close it
	if (theController().m_hWnd) ::SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);

	bool bAnwinFound = false;

	// Get the list of process identifiers.
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) return;

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.

	for (i = 0; i < cProcesses; i++) {
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);

		// Get the process name.
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded2;
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded2)) {
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));

				CString pro = szProcessName;
				if (pro.MakeLower() == "anwin.exe") {
					EnumWindows(EnumWindowsProc, aProcesses[i]);
					bAnwinFound = true;
					break;
				}
			}
		}
	}
	if (!bAnwinFound) AfxMessageBox("AnWin is not running on this machine.", MB_ICONINFORMATION | MB_TASKMODAL, 0);

}

bool CPVCSApp::IsServerMachine(CString pServerIP, CString pLocalIP) {
	if (_strcmpi(pServerIP, pLocalIP) == 0) return true;
	else return false;
}

int CPVCSApp::inet_pton(int af, const char *src, void *dst) {
	struct sockaddr_storage ss;
	int size = sizeof(ss);
	char src_copy[INET6_ADDRSTRLEN + 1];

	ZeroMemory(&ss, sizeof(ss));
	/* stupid non-const API */
	strncpy(src_copy, src, INET6_ADDRSTRLEN + 1);
	src_copy[INET6_ADDRSTRLEN] = 0;

	if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0) {
		switch (af) {
		case AF_INET:
			*(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
			return 1;
		case AF_INET6:
			*(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
			return 1;
		}
	}
	return 0;
}


//Function returns the Local IP of the machine
CString CPVCSApp::GetLocalIP(void) {
	WSADATA wsaData;
	WORD wVersionRequested;
	CString strIP;
	PHOSTENT hostinfo;
	struct in_addr MasterIPaddr;
	inet_pton(AF_INET, m_strMasterIP, &MasterIPaddr);
	wVersionRequested = MAKEWORD(2, 0);

	// Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		// Get local host name
		char szHostName[128] = "";

		if (gethostname(szHostName, sizeof(szHostName)) == 0) {
			struct hostent *pHost = 0;
			hostinfo = ::gethostbyname(szHostName);
			if (hostinfo != NULL) {
				switch (hostinfo->h_addrtype) {
				case AF_INET:
					//printf("AF_INET\n");
					// Find the correct IP address
					{
						int i = 0;
						while (hostinfo->h_addr_list[i] != 0) {
							struct in_addr addr;
							addr.s_addr = *(u_long *)hostinfo->h_addr_list[i++];
							// Check that the IP address belongs to the right address segment
							if ((addr.S_un.S_un_b.s_b1 == MasterIPaddr.S_un.S_un_b.s_b1)
								&& (addr.S_un.S_un_b.s_b2 == MasterIPaddr.S_un.S_un_b.s_b2)
								&& (addr.S_un.S_un_b.s_b3 == MasterIPaddr.S_un.S_un_b.s_b3)) {
								strIP = inet_ntoa(addr);
								break;
							}
						}
					}

					break;
				case AF_NETBIOS:
					//printf("AF_NETBIOS\n");
					break;
				default:
					//printf(" %d\n", hostinfo->h_addrtype);
					break;
				}
				//strIP = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		// Cleanup
		WSACleanup();
	}
	return strIP;
}
//function used to request command for specific screen by client from Master
bool CPVCSApp::RequestingCommandFromMaster(int RequestingScreenNumber) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		//TRACE("\n Request start");
		SOCKET RequestSocket;
		//Create a socket
		RequestSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (RequestSocket == INVALID_SOCKET) {
			AfxMessageBox("Unable to setup communication with Master, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
			WSACleanup();
			return false;
		}

		//connect socket to remote machine
		sockaddr_in ServerRequestSocketaddr;

		ServerRequestSocketaddr.sin_family = AF_INET;
		ServerRequestSocketaddr.sin_addr.S_un.S_addr = inet_addr(theApp.GetMasterIP());
		ServerRequestSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort());

		if (connect(RequestSocket, (SOCKADDR *)&ServerRequestSocketaddr, sizeof(ServerRequestSocketaddr)) == SOCKET_ERROR) {
			int LastError = WSAGetLastError();

			//this is the case where master is not up and client requesting for command, so grant it.
			if (LastError == 10065 || LastError == 10060 || LastError == 10061) {
				CErrorLog obj;

				if (LastError == 10065) {
					obj.WriteError("CPvcsAPP::RequestingCommandFromMaster", "Error occurs when client trying to connect to master machine", "10065:- No route to host. A socket operation was attempted to an unreachable host.");
				} else if (LastError == 10060) {
					obj.WriteError("CPvcsAPP::RequestingCommandFromMaster", "Error occurs when client trying to connect to master machine", "10060:- Connection timed out. A connection attempt failed because the connected party did not properly respond after a period of time, or the established connection failed because the connected host has failed to respond.");
				} else if (LastError == 10061) {
					obj.WriteError("CPvcsAPP::RequestingCommandFromMaster", "Error occurs when client trying to connect to master machine", "10061:- Connection refused. No connection could be made because the target computer actively refused it. This usually results from trying to connect to a service that is inactive on the foreign host—that is, one with no server application running.");
				}

				CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_bCommandStatus = true;
				CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strCommandingMachineIP = theApp.GetLocalIP();
				CString NewWindowTitle = "";

				if (IsBackupMode) //if in backup mode
					NewWindowTitle.Format("PVCS Backup - %s, Client in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strScreenTitle);
				else NewWindowTitle.Format("PVCS - %s, Client in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strScreenTitle);

				CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);

				closesocket(RequestSocket);
				WSACleanup();
				return true;
			} else AfxMessageBox("Unable to Connect to the Master machine, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);

			closesocket(RequestSocket);
			WSACleanup();
			return false;

		} else { //if connect is oK, then send request
			char SendBuf[5];
			SendBuf[0] = '\0';

			sprintf_s(SendBuf, "S%d", RequestingScreenNumber);

			//send request for specific screen number
			if (send(RequestSocket, SendBuf, strlen(SendBuf), 0) == SOCKET_ERROR) { //if error in send
				closesocket(RequestSocket);
				WSACleanup();
				AfxMessageBox("Unable to send Request command to server, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
				return false;
			}

			char IPBuf[18];

			int ByteRecv = recv(RequestSocket, IPBuf, sizeof(IPBuf), 0);

			if (ByteRecv != SOCKET_ERROR) IPBuf[ByteRecv] = '\0';

			CString CommandingMachineIP = IPBuf;

			//IpBuf != y, means master machine doesn't having command with him, so send IP of machine having command
			if (CommandingMachineIP != "y") {
				bool bResult = RequestingCommandFromClient(RequestingScreenNumber, CommandingMachineIP);

				//Inform the Master, about the request state
				if (bResult) {
					send(RequestSocket, "54", 4, 0);
					//this function get updated buffer from the master machine
					Warning_TimeOut_XMLFileTransfereClient(1, RequestingScreenNumber);
				} else send(RequestSocket, "45", 4, 0);

				closesocket(RequestSocket);
				WSACleanup();

				return bResult;
			}
			//when Master having command with him
			else if (CommandingMachineIP == "y") {
				fd_set fds;
				FD_ZERO(&fds);
				FD_SET(RequestSocket, &fds);
				//
				timeval CheckTimeOut;
				int Res;

				CheckTimeOut.tv_sec = theConfiguration().GetRequestTimeOut();    //Get time out from XML
				CheckTimeOut.tv_usec = 0;

				Res = select(RequestSocket, &fds, NULL, NULL, &CheckTimeOut);

				FD_CLR(RequestSocket, &fds);

				if (Res == 0) { //if timeout occured, then send timeout signal to server
					AfxMessageBox("No one on the Server machine to grant Request, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_TOPMOST | MB_APPLMODAL, 0);
					send(RequestSocket, "T1", strlen("T1"), 0);
					closesocket(RequestSocket);
					WSACleanup();
					return false;
				}
				//no time out
				char RecvBuf[5];
				//Clear buffer
				for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';
				int RecvDataLen;

				//recv dummy signal from the server for timeout
				recv(RequestSocket, RecvBuf, sizeof(RecvBuf), 0);

				//check for invalid screen request
				if (atoi(RecvBuf) == 3) {
					closesocket(RequestSocket);
					WSACleanup();
					AfxMessageBox("Requesting for invalid screen or Server doesn't has this screen.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
					return false;
				}

				//send no time out occured to the server
				send(RequestSocket, "T0", strlen("T0"), 0);

				//Clear buffer
				for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

				//receive response from server ("1" or "0")
				RecvDataLen = recv(RequestSocket, RecvBuf, sizeof(RecvBuf), 0);
				if (RecvDataLen == SOCKET_ERROR) { //if error in recv,
					int errorcode = WSAGetLastError();
					if (errorcode == 10038) {
						RecvDataLen = recv(RequestSocket, RecvBuf, sizeof(RecvBuf), 0);
						errorcode = WSAGetLastError();
					}
					closesocket(RequestSocket);
					WSACleanup();
					AfxMessageBox("Unable to receive response from the server, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
					return false;
				} else { //if recv is OK
					CString RecData = RecvBuf;
					RecData.MakeLower();
					int ResponseData = atoi(RecData);
					if (ResponseData == 1) { //if request granted by the server
											 //this function get updated buffer from the master machine
						theApp.Warning_TimeOut_XMLFileTransfereClient(1, RequestingScreenNumber);

						CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_bCommandStatus = true;
						CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strCommandingMachineIP = theApp.GetLocalIP();
						CString NewWindowTitle = "";

						if (IsBackupMode) //if in backup mode
							NewWindowTitle.Format("PVCS Backup - %s, Client in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strScreenTitle);
						else NewWindowTitle.Format("PVCS - %s, Client in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strScreenTitle);

						CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);

						closesocket(RequestSocket);
						WSACleanup();
						//TRACE("\n Request end");
						return true;
					} else if (ResponseData == 0) { //if request denied
						closesocket(RequestSocket);
						WSACleanup();
						AfxMessageBox("Request for command denied, Retry later", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
						return false;
					} else if (ResponseData == 3) { //if Invalid screen number
						closesocket(RequestSocket);
						WSACleanup();
						AfxMessageBox("Requesting for invalid screen or Server doesn't have this screen.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
						return false;
					} else if (ResponseData == 4) { //auto message close
						closesocket(RequestSocket);
						WSACleanup();
						return false;
					} else { //if recv something other
						closesocket(RequestSocket);
						WSACleanup();
						AfxMessageBox("Received some invalid data from server, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
						return false;
					}
				} //else, if rev ok
			} //else if(CommandingMachineIP == "0")
		} //else //if connect is ok, then send request
	} else AfxMessageBox("Unable to communicate with Master machine, Retry later", MB_SETFOREGROUND | MB_ICONERROR | MB_APPLMODAL | MB_TOPMOST, 0);

	return false;
}

//Function that request command for a screen by a client from a client (having command)
bool CPVCSApp::RequestingCommandFromClient(int RequestingScreenNumber, CString CommandingMachineIP) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		//Start new connection with commanding machine IP
		SOCKET RevokeSocket;
		//Create a socket
		if ((RevokeSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
			sockaddr_in CommandingSocketaddr;

			CommandingSocketaddr.sin_family = AF_INET;
			CommandingSocketaddr.sin_addr.S_un.S_addr = inet_addr(CommandingMachineIP);
			CommandingSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() - 1);

			if (connect(RevokeSocket, (SOCKADDR *)&CommandingSocketaddr, sizeof(CommandingSocketaddr)) == SOCKET_ERROR) {
				int ErrorCode = WSAGetLastError();

				//this is the case when client machine goes down with command, and another client trying to take command, so grant him
				if (ErrorCode == 10060 || ErrorCode == 10061 || ErrorCode == 10065) {
					CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_bCommandStatus = true;
					CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strCommandingMachineIP = theApp.GetLocalIP();
					CString NewWindowTitle = "";

					if (IsBackupMode) //if in backup mode
						NewWindowTitle.Format("PVCS Backup - %s, Client in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strScreenTitle);
					else NewWindowTitle.Format("PVCS - %s, Client in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strScreenTitle);

					CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);

					closesocket(RevokeSocket);
					WSACleanup();
					return true;
				} else AfxMessageBox("Unable to connect to Commanding machine, retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);

				closesocket(RevokeSocket);
				WSACleanup();
				return false;
			} else { //if connect is oK, then send data
				char RecvBuf[5];

				send(RevokeSocket, "R101", 5, 0);

				recv(RevokeSocket, RecvBuf, sizeof(RecvBuf), 0);

				char SendBuf[5];
				SendBuf[0] = '\0';

				sprintf_s(SendBuf, "%d", RequestingScreenNumber);
				//send request for specific screen number

				if (send(RevokeSocket, SendBuf, strlen(SendBuf), 0) == SOCKET_ERROR) { //if error in send
					closesocket(RevokeSocket);
					WSACleanup();
					AfxMessageBox("Unable to send Request to commanding machine, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
					return false;
				}


				fd_set fds;
				FD_ZERO(&fds);
				FD_SET(RevokeSocket, &fds);
				//
				timeval CheckTimeOut;
				int Res;

				CheckTimeOut.tv_sec = theConfiguration().GetRequestTimeOut();    //Get time out from XML
				CheckTimeOut.tv_usec = 0;

				Res = select(RevokeSocket, &fds, NULL, NULL, &CheckTimeOut);

				FD_CLR(RevokeSocket, &fds);

				if (Res == 0) { //if timeout occured, then send timeout signal to server
					AfxMessageBox("No one on the machine to grant Request, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_TOPMOST | MB_APPLMODAL, 0);
					send(RevokeSocket, "T1", strlen("T1"), 0);
					closesocket(RevokeSocket);
					WSACleanup();
					return false;
				}
				//no time out
				//Clear buffer

				for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';
				int RecvDataLen;

				//recv dummy signal from the client for timeout
				recv(RevokeSocket, RecvBuf, sizeof(RecvBuf), 0);

				//check for invalid screen request
				if (atoi(RecvBuf) == 3) {
					closesocket(RevokeSocket);
					WSACleanup();
					AfxMessageBox("Requesting for invalid screen or machine doesn't has this screen.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
					return false;
				}
				//send no time out occured to the client
				send(RevokeSocket, "T0", strlen("T0"), 0);

				//Clear buffer
				for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

				//receive response from client ("1" or "0" or "3")
				RecvDataLen = recv(RevokeSocket, RecvBuf, sizeof(RecvBuf), 0);
				if (RecvDataLen <= 0) { //if error in recv,
					closesocket(RevokeSocket);
					WSACleanup();
					AfxMessageBox("Unable to receive response from the commanding machine, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
					return false;
				} else { //if recv is OK
					CString RecData = RecvBuf;
					RecData.MakeLower();
					int ResponseData = atoi(RecData);
					if (ResponseData == 1) { //if request granted by the client
						CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_bCommandStatus = true;
						CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strCommandingMachineIP = theApp.GetLocalIP();
						CString NewWindowTitle = "";

						if (IsBackupMode) //if in backup mode
							NewWindowTitle.Format("PVCS Backup - %s, Client in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strScreenTitle);
						else NewWindowTitle.Format("PVCS - %s, Client in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_strScreenTitle);

						CPvcsScreenInfo::m_vecScreenInfo[RequestingScreenNumber - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);

						closesocket(RevokeSocket);
						WSACleanup();
						//TRACE("\n Request end");
						return true;
					} else if (ResponseData == 0) { //if request denied
						closesocket(RevokeSocket);
						WSACleanup();
						AfxMessageBox("Request for command denied, Retry later", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
						return false;
					} else if (ResponseData == 3) { //if Invalid screen number
						closesocket(RevokeSocket);
						WSACleanup();
						AfxMessageBox("Requesting for invalid screen or Server doesn't have this screen.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
						return false;
					} else if (ResponseData == 4) { //auto message close
						closesocket(RevokeSocket);
						WSACleanup();
						return false;
					} else { //if recv something other
						closesocket(RevokeSocket);
						WSACleanup();
						AfxMessageBox("Received some invalid data from commanding machine, Retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
						return false;
					}
				}
			}
		}

		WSACleanup();
		return false;
	}
	return false;
}

//function used to revoke command from command machine by server, "Take Command"
bool CPVCSApp::RevokingCommandFromClient(int RevokingScreenNumber) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	// Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		//TRACE("\n Revoke start");
		SOCKET RevokeSocket;
		//Create a socket
		RevokeSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (RevokeSocket == INVALID_SOCKET) {
			AfxMessageBox("Unable to setup communication with Client machine, retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
			WSACleanup();
			return false;
		}

		//connect socket to remote machine
		sockaddr_in ClientRevokeSocketaddr;

		ClientRevokeSocketaddr.sin_family = AF_INET;
		ClientRevokeSocketaddr.sin_addr.S_un.S_addr = inet_addr(CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strCommandingMachineIP);
		ClientRevokeSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() - 1);

		if (connect(RevokeSocket, (SOCKADDR *)&ClientRevokeSocketaddr, sizeof(ClientRevokeSocketaddr)) == SOCKET_ERROR) {
			int ErrorCode = WSAGetLastError();
			//this is the case when client machine goes down with command, and master trying to take command
			if (ErrorCode == 10060 || ErrorCode == 10061 || ErrorCode == 10065) {
				CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_bCommandStatus = true;
				CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strCommandingMachineIP = GetMasterIP();
				CString NewWindowTitle = "";

				if (IsBackupMode) //if in backup mode
					NewWindowTitle.Format("PVCS Backup - %s, Master in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strScreenTitle);
				else NewWindowTitle.Format("PVCS - %s, Master in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strScreenTitle);

				CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);

				closesocket(RevokeSocket);
				WSACleanup();
				return true;
			} else AfxMessageBox("Unable to connect to Client machine, retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);

			closesocket(RevokeSocket);
			WSACleanup();
			return false;
		} else { //if connect is oK, then send data
			char SendBuf[5];
			SendBuf[0] = '\0';

			sprintf_s(SendBuf, "R%d", RevokingScreenNumber);

			//send revoking screen number
			if (send(RevokeSocket, SendBuf, strlen(SendBuf), 0) == SOCKET_ERROR) {
				closesocket(RevokeSocket);
				WSACleanup();
				AfxMessageBox("Unable to send Revoke command to the Client machine, retry later.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
				return false;
			}

			char RecvBuf[5];
			//Clear buffer
			for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';
			int RecvDataLen;

			//receive response from server ("1" or "0")
			RecvDataLen = recv(RevokeSocket, RecvBuf, sizeof(RecvBuf), 0);

			CString RecData = RecvBuf;
			RecData.MakeLower();
			int ResponseData = atoi(RecData);

			//if invalid screen number on recv of "0"
			if (ResponseData == 0) {
				closesocket(RevokeSocket);
				WSACleanup();
				AfxMessageBox("Revoking from invalid screen or Client doesn't have this screen.", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
				return false;
			}

			CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_bCommandStatus = true;
			CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strCommandingMachineIP = GetMasterIP();
			CString NewWindowTitle = "";

			if (IsBackupMode) //if in backup mode
				NewWindowTitle.Format("PVCS Backup - %s, Master in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strScreenTitle);
			else NewWindowTitle.Format("PVCS - %s, Master in Command Mode", CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strScreenTitle);

			CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);

			closesocket(RevokeSocket);
			WSACleanup();
			//TRACE("\n Revoke end");
			return true;
		}
	} else AfxMessageBox("Unable to communicate with Client machine, Retry later", MB_SETFOREGROUND | MB_ICONERROR | MB_APPLMODAL | MB_TOPMOST, 0);

	return false;
}

//This function send signal to the server/client thread to terminate
void CPVCSApp::CloseCommandThread(void) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET CloseSocket;
		//Create a socket
		CloseSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (CloseSocket == INVALID_SOCKET) {
			WSACleanup();
			return;
		}


		//connect socket to local machine
		sockaddr_in CloseSocketaddr;

		CloseSocketaddr.sin_family = AF_INET;
		CloseSocketaddr.sin_addr.S_un.S_addr = inet_addr(GetLocalIP());

		if (m_bIsServer) //if machine is Server
			CloseSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort());
		else //else, if machine is client
			CloseSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() - 1);

		if (connect(CloseSocket, (SOCKADDR *)&CloseSocketaddr, sizeof(CloseSocketaddr)) == SOCKET_ERROR) {
			closesocket(CloseSocket);
			WSACleanup();
			return;
		} else { //if connect is OK, then send data
			char SendBuf[5];
			SendBuf[0] = '\0';

			//if server machine
			if (m_bIsServer) sprintf_s(SendBuf, "S100");
			else //else, client machine
				sprintf_s(SendBuf, "R100");

			//send request to close Server or Client Thread
			send(CloseSocket, SendBuf, strlen(SendBuf), 0);

			closesocket(CloseSocket);
			WSACleanup();
			return;
		}
	}

	return;
}

//This function sends close signal to the client machine to terminate ReceiveCalibrationFile Thread
void CPVCSApp::CloseReceiveCalibrationFileThread(void) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET CloseSocket;
		//Create a socket
		CloseSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (CloseSocket == INVALID_SOCKET) {
			WSACleanup();
			return;
		}

		//connect socket to client machine
		sockaddr_in CloseSocketaddr;

		CloseSocketaddr.sin_family = AF_INET;
		CloseSocketaddr.sin_addr.S_un.S_addr = inet_addr(theApp.GetLocalIP());
		CloseSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() + 1);

		if (connect(CloseSocket, (SOCKADDR *)&CloseSocketaddr, sizeof(CloseSocketaddr)) == SOCKET_ERROR) {
			closesocket(CloseSocket);
			WSACleanup();
			return;
		}
		send(CloseSocket, "F2", strlen("F2"), 0);
		closesocket(CloseSocket);
		WSACleanup();
	}

	return;
}

//this function used to send Close Signal To Server if any client going to close and also check for command
void CPVCSApp::ClosingSignalOfClientToServer(void) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET SendBackSocket;
		//Create a socket
		SendBackSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (SendBackSocket == INVALID_SOCKET) {
			WSACleanup();
			return;
		}

		//connect socket to Server machine
		sockaddr_in SendBackSocketaddr;

		SendBackSocketaddr.sin_family = AF_INET;
		SendBackSocketaddr.sin_addr.S_un.S_addr = inet_addr(theApp.GetMasterIP());
		SendBackSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort());

		if (connect(SendBackSocket, (SOCKADDR *)&SendBackSocketaddr, sizeof(SendBackSocketaddr)) == SOCKET_ERROR) {
			closesocket(SendBackSocket);
			WSACleanup();
			return;
		} else { //if connect is OK, then send data
			send(SendBackSocket, "S101", strlen("S101"), 0);

			char DummyBuf[2];

			//dummey recv
			recv(SendBackSocket, DummyBuf, sizeof(DummyBuf), 0);

			CString SendBuf = "";

			for (unsigned i = 0; i < CPvcsScreenInfo::m_vecScreenInfo.size(); i++) {
				if (CPvcsScreenInfo::m_vecScreenInfo[i]->m_bCommandStatus) {
					//send request to server to get back command
					CString Tempstr = "";
					Tempstr.Format("%d.", CPvcsScreenInfo::m_vecScreenInfo[i]->m_ptrScreenFrame->ScreenNumber);
					SendBuf += Tempstr;
				}
			}

			send(SendBackSocket, SendBuf, SendBuf.GetLength(), 0);
			closesocket(SendBackSocket);
			WSACleanup();
			return;
		}
	}

	return;
}


//This Thread call TransmitcalibrationFile() to send calibration file to all the connected client, calls on OK() of calibration window
UINT SendCalibrationFileToAllClient(LPVOID pParam) {
	for (unsigned i = 0; i < theApp.ConnectedClientMachineIP.size(); i++) theApp.TransmitCalibrationFile(theApp.ConnectedClientMachineIP[i]);

	//Reset when file transfer complete
	theApp.m_bIsCalibrationFileTransferComplete = true;

	return 0;
}
#pragma warning (disable: 4101)
//This Thread at client side waits to receive calibration file from server, at client side
UINT ReceiveCalibrateXmlFile(LPVOID pParam) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);
	bool IsCalibrateFileExists = false;

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET ReceiveSocket;
		ReceiveSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ReceiveSocket == INVALID_SOCKET) {
			WSACleanup();
			return 0;
		}
		sockaddr_in ReceiveSocketaddr;

		ReceiveSocketaddr.sin_family = AF_INET;
		ReceiveSocketaddr.sin_addr.s_addr = inet_addr(theApp.GetLocalIP());
		ReceiveSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() + 1);

		//pointer will be needed to cast to generic address type(struct sockaddr *)
		if (bind(ReceiveSocket, (SOCKADDR *)&ReceiveSocketaddr, sizeof(ReceiveSocketaddr)) == SOCKET_ERROR) {
			closesocket(ReceiveSocket);
			WSACleanup();
			return 0;
		}

		// Listen on the socket.
		if (listen(ReceiveSocket, 5) == SOCKET_ERROR) {
			closesocket(ReceiveSocket);
			WSACleanup();
			return 0;
		}

		SOCKET TransmitSocket;
		sockaddr_in TransmitSocketaddr;
		int TransmitSocketLen = sizeof(TransmitSocketaddr);

		CFile XmlFile;
		char StatusBuf[3];

		while (1) {

			TransmitSocket = accept(ReceiveSocket, (SOCKADDR *)&TransmitSocketaddr, &TransmitSocketLen);
			if (ReceiveSocket == INVALID_SOCKET) {
				WSACleanup();
				return 0;
			}


			StatusBuf[0] = '\0';

			//waits to get file signal from the master machine
			recv(TransmitSocket, StatusBuf, sizeof(StatusBuf), 0);

			CString Buf = StatusBuf;
			Buf.MakeLower();
			Buf.TrimLeft('f');
			if (atoi(Buf) == 1) { //file open successfully and file exists at server side
				try {
					if (XmlFile.Open("xmlfiles\\calibrate.xml", CFile::modeCreate | CFile::modeWrite)) {
						IsCalibrateFileExists = true;
						send(TransmitSocket, "F1", strlen("F1"), 0);
					} else {
						IsCalibrateFileExists = false;
						send(TransmitSocket, "F0", strlen("F0"), 0);
						closesocket(TransmitSocket);
					}
				} catch (CFileException *e) {
					send(TransmitSocket, "F0", strlen("F0"), 0);
					IsCalibrateFileExists = false;
					closesocket(TransmitSocket);
				}
			} else if (atoi(Buf) == 0) { //file does not exists at server side or unable to open,send F0, no need for transfer
				send(TransmitSocket, "F0", strlen("F0"), 0);
				IsCalibrateFileExists = false;
				closesocket(TransmitSocket);
			} else if (atoi(Buf) == 2) { //signal to close thread
				if (IsCalibrateFileExists) XmlFile.Close();
				closesocket(TransmitSocket);
				WSACleanup();
				return 0;
			}


			if (IsCalibrateFileExists) {
				XmlFile.SeekToBegin();

				char SizeBuf[20];
				char FileBuf[1024];
				FileBuf[0] = '\0';
				SizeBuf[0] = '\0';

				recv(TransmitSocket, SizeBuf, sizeof(SizeBuf), 0);

				ULONG FileSize = atol(SizeBuf);
				DWORD BytesRecv = 0;

				send(TransmitSocket, "1", strlen("1"), 0);

				while (FileSize > 0) {
					BytesRecv = recv(TransmitSocket, FileBuf, sizeof(FileBuf), 0);
					XmlFile.Write(FileBuf, BytesRecv);
					FileSize = FileSize - BytesRecv;
					FileBuf[0] = '\0';
				}

				XmlFile.Close();
				closesocket(TransmitSocket);
			}

		}
	}
	return 0;
}

//This function used to transmit calibration.xml file to all the clients
bool CPVCSApp::TransmitCalibrationFile(CString RemoteIP) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);
	bool IsCalibrateFileExists = false;
	bool DoTransfer = false;

	// Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET TransmitSocket;
		//Create a socket
		TransmitSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (TransmitSocket == INVALID_SOCKET) {
			WSACleanup();
			return false;
		}

		//connect socket to Server machine
		sockaddr_in ReceiveSocketaddr;

		ReceiveSocketaddr.sin_family = AF_INET;
		ReceiveSocketaddr.sin_addr.S_un.S_addr = inet_addr(RemoteIP);
		ReceiveSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() + 1);

		if (connect(TransmitSocket, (SOCKADDR *)&ReceiveSocketaddr, sizeof(ReceiveSocketaddr)) == SOCKET_ERROR) {
			closesocket(TransmitSocket);
			WSACleanup();
			return false;
		}

		CFile XmlFile;
		char StatusBuf[3];
		StatusBuf[0] = '\0';

		//For transmit xml file
		try {
			if (XmlFile.Open("xmlfiles\\calibrate.xml", CFile::modeRead)) {
				//If file exists or open correctly
				IsCalibrateFileExists = true;
				send(TransmitSocket, "F1", strlen("F1"), 0);
			} else {
				//If file does not exists or unable to open
				IsCalibrateFileExists = false;
				send(TransmitSocket, "F0", strlen("F0"), 0);
			}
		} catch (CFileException *e) {
			//file error so send a signal to client
			send(TransmitSocket, "F0", strlen("F0"), 0);
			IsCalibrateFileExists = false;
		}

		//recv file status from client
		recv(TransmitSocket, StatusBuf, sizeof(StatusBuf), 0);

		CString Buf = StatusBuf;
		Buf.MakeLower();
		Buf.TrimLeft('f');
		if (atoi(Buf) == 1) //if file opens correctly, do file transfer
			DoTransfer = true;
		else { //else don't transfer file
			if (IsCalibrateFileExists) XmlFile.Close();
			DoTransfer = false;
			closesocket(TransmitSocket);
			WSACleanup();
			return false;
		}

		if (DoTransfer && IsCalibrateFileExists) {
			XmlFile.SeekToBegin();
			ULONGLONG FileSize = XmlFile.GetLength();

			CString SizeBuf = "";
			SizeBuf.Format("%lu", FileSize);

			send(TransmitSocket, SizeBuf, SizeBuf.GetLength(), 0);

			recv(TransmitSocket, StatusBuf, sizeof(StatusBuf), 0);

			DWORD BytesRead;
			char FileBuf[1024];
			FileBuf[0] = '\0';

			while (FileSize > 0) {
				BytesRead = XmlFile.Read(FileBuf, sizeof(FileBuf));
				send(TransmitSocket, FileBuf, BytesRead, 0);
				FileSize = FileSize - BytesRead;
				FileBuf[0] = '\0';
				Sleep(50);
			}

			Sleep(100);
			XmlFile.Close();
			closesocket(TransmitSocket);
			WSACleanup();
			return true;
		}
	}

	return false;
}

//This function sends close signal to the master machine to terminate Warning_TimeOut_xmlfiletransferThread() Thread
void CPVCSApp::CloseWarningTimeoutTransferFileThread(void) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET CloseSocket;
		//Create a socket
		CloseSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (CloseSocket == INVALID_SOCKET) {
			WSACleanup();
			return;
		}

		//connect socket to client machine
		sockaddr_in CloseSocketaddr;

		CloseSocketaddr.sin_family = AF_INET;
		CloseSocketaddr.sin_addr.S_un.S_addr = inet_addr(theApp.GetLocalIP());
		CloseSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() + 2);

		if (connect(CloseSocket, (SOCKADDR *)&CloseSocketaddr, sizeof(CloseSocketaddr)) == SOCKET_ERROR) {
			closesocket(CloseSocket);
			WSACleanup();
			return;
		}
		send(CloseSocket, "E", strlen("E"), 0);
		closesocket(CloseSocket);
		WSACleanup();
	}

	return;
}

//this function to send request for warning and timeout file to master, at client side
bool CPVCSApp::Warning_TimeOut_XMLFileTransfereClient(int TypeOfOperation, int ScreenNumber) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET ReceiveSocket;
		//Create a socket
		ReceiveSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ReceiveSocket == INVALID_SOCKET) {
			WSACleanup();
			return false;
		}

		//connect socket to client machine
		sockaddr_in ReceiveSocketaddr;

		ReceiveSocketaddr.sin_family = AF_INET;
		ReceiveSocketaddr.sin_addr.S_un.S_addr = inet_addr(theApp.GetMasterIP());
		ReceiveSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() + 2);

		if (connect(ReceiveSocket, (SOCKADDR *)&ReceiveSocketaddr, sizeof(ReceiveSocketaddr)) == SOCKET_ERROR) {
			closesocket(ReceiveSocket);
			WSACleanup();
			return false;
		}

		char RecvBuf[3];

		if (TypeOfOperation == 1) { //When client need warning and timeout file
			send(ReceiveSocket, "C", 2, 0); //send "C" to request to master for data

			recv(ReceiveSocket, RecvBuf, sizeof(RecvBuf), 0); //recv "1" from master

			CString strScreenNumber;

			strScreenNumber.Format("%d", ScreenNumber);

			send(ReceiveSocket, strScreenNumber, strScreenNumber.GetLength(), 0); //send screen number

			char ScreenData[20000];

			int byterecv = recv(ReceiveSocket, ScreenData, 20000, 0);
			if (byterecv != SOCKET_ERROR) {
				ScreenData[byterecv] = '\0';

				CString strScreenData = ScreenData;
				strScreenNumber.Format("SNO%d", ScreenNumber);

				//*************************function that load screen data into buffer at client side
				CWriteTimeouts objWriteTimeout;
				m_csXmlWTFile.Lock(); //lock the xml file for single access
				objWriteTimeout.UpdateXMLFile(strScreenNumber, strScreenData);
				objWriteTimeout.FillVector(); //this function refill the vector of the warning message
				m_csXmlWTFile.Unlock(); //unlock the xml file
			}

			closesocket(ReceiveSocket);
			WSACleanup();
			return true;
		} else if (TypeOfOperation == 2) { //when client sending back warning and timeout file
			send(ReceiveSocket, "U", 2, 0); //send request to master to receive data from client

			recv(ReceiveSocket, RecvBuf, sizeof(RecvBuf), 0); //recv "1" form the master

			CString strScreenNumber;

			strScreenNumber.Format("%d", ScreenNumber);

			send(ReceiveSocket, strScreenNumber, strScreenNumber.GetLength(), 0); //send screen number

			recv(ReceiveSocket, RecvBuf, sizeof(RecvBuf), 0); //recv "1" form the master

			CString ScreenData;
			strScreenNumber.Format("SNO%d", ScreenNumber);

			//****************************function from where i will get data that is to be send
			CWriteTimeouts objWriteTimeOut;
			m_csXmlWTFile.Lock(); //lock the xml file for single access
			ScreenData = objWriteTimeOut.ReadFileData(strScreenNumber);
			m_csXmlWTFile.Unlock(); //unlock the xml file

			send(ReceiveSocket, ScreenData, ScreenData.GetLength(), 0); //send screen data to the master

			closesocket(ReceiveSocket);
			WSACleanup();
			return true;
		} else if (TypeOfOperation == 3) { //when client needs whole warning and timeout file, to display in the Timeout window
										   //TRACE("\n************************************************transfer start\n");

			send(ReceiveSocket, "D", sizeof("D"), 0); //send request to master for whole file

			char TimeOut[20000];

			int ByteRecv = recv(ReceiveSocket, TimeOut, sizeof(TimeOut), 0);

			if (ByteRecv != SOCKET_ERROR) {
				TimeOut[ByteRecv] = '\0';
				CString strTimeOut = TimeOut;

				//function that update local xml file for the Timeouts
				CWriteTimeouts objWriteTimeouts;
				m_csXmlWTFile.Lock(); //lock the xml file for single access
				objWriteTimeouts.Load_TimeOuts_FromFile_IN_XMLFormat(TimeOut);
				m_csXmlWTFile.Unlock(); //unlock the xml file
			}

			closesocket(ReceiveSocket);
			WSACleanup();
			//TRACE("\n************************************************transfer End\n");
			return true;

		}

	}

	return false;
}

//This Thread is for Sending, receving XML files data to and from client, at server side
UINT Warning_TimeOut_XMLFileThread(LPVOID pParam) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET TransmitSocket;
		TransmitSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (TransmitSocket == INVALID_SOCKET) {
			WSACleanup();
			return 0;
		}
		sockaddr_in TransmitSocketaddr;

		TransmitSocketaddr.sin_family = AF_INET;
		TransmitSocketaddr.sin_addr.s_addr = inet_addr(theApp.GetMasterIP());
		TransmitSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() + 2);

		//pointer will be needed to cast to generic address type(struct sockaddr *)
		if (bind(TransmitSocket, (SOCKADDR *)&TransmitSocketaddr, sizeof(TransmitSocketaddr)) == SOCKET_ERROR) {
			closesocket(TransmitSocket);
			WSACleanup();
			return 0;
		}

		// Listen on the socket.
		if (listen(TransmitSocket, 5) == SOCKET_ERROR) {
			closesocket(TransmitSocket);
			WSACleanup();
			return 0;
		}

		SOCKET ReceiveSocket;
		sockaddr_in ReceiveSocketaddr;
		int ReceiveSocketLen = sizeof(ReceiveSocketaddr);
		char RecvBuf[3];

		while (CPVCSApp::m_bIsAlive) {
			ReceiveSocket = accept(TransmitSocket, (SOCKADDR *)&ReceiveSocketaddr, &ReceiveSocketLen);

			//Clear buffer
			for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

			recv(ReceiveSocket, RecvBuf, 3, 0);

			if (RecvBuf[0] == 'C') { //if client had requested for command and granted then client needs XML too, so sending request
									 //Clear buffer
				for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

				send(ReceiveSocket, "1", strlen("1"), 0);

				recv(ReceiveSocket, RecvBuf, 3, 0); //receive screen number

				int ScreenNumber = atoi(RecvBuf);

				CString ScreenData = "";
				CString ScreenNo;

				ScreenNo.Format("SNO%d", ScreenNumber);

				//***************************function that get data from the xml file for the specified screen number
				CWriteTimeouts objWriteTimeOut;
				theApp.m_csXmlWTFile.Lock(); //lock the xml file for single access
				ScreenData = objWriteTimeOut.ReadFileData(ScreenNo);
				theApp.m_csXmlWTFile.Unlock(); //unlock the xml file

				send(ReceiveSocket, ScreenData, ScreenData.GetLength(), 0);

				Sleep(500);
				closesocket(ReceiveSocket);
			} else if (RecvBuf[0] == 'U') { //if Client updating the file at Master
											//Clear buffer
				for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

				send(ReceiveSocket, "1", strlen("1"), 0);

				recv(ReceiveSocket, RecvBuf, 3, 0); //recv screen number, for which client sending data

				int ScreenNumber = atoi(RecvBuf);
				CString ScreenNo;

				ScreenNo.Format("SNO%d", ScreenNumber);

				send(ReceiveSocket, "1", strlen("1"), 0);

				char ScreenData[20000];

				int ByteRecv = recv(ReceiveSocket, ScreenData, 20000, 0);
				if (ByteRecv != SOCKET_ERROR) {
					ScreenData[ByteRecv] = '\0';

					CString ScreenDataFromClient = ScreenData;

					closesocket(ReceiveSocket);

					//****************************function that update the xml file at Master for the specified screen
					CWriteTimeouts objWriteTimeOut;
					theApp.m_csXmlWTFile.Lock(); //lock the xml file for single access
					objWriteTimeOut.UpdateXMLFile(ScreenNo, ScreenDataFromClient);
					objWriteTimeOut.FillVector(); //this function refill the vector for the warning messages
					theApp.m_csXmlWTFile.Unlock(); //unlock the xml file
				}
			} else if (RecvBuf[0] == 'D') { //if client requesting full XML data as a result of click on 'Time Out List'

				CString TimeOut = "";

				//function that get all timeouts in the file, Screen wise,
				CWriteTimeouts objWriteTimeouts;
				theApp.m_csXmlWTFile.Lock(); //lock the xml file for single access
				TimeOut = objWriteTimeouts.GetOnlyTimeOutsFromFile();
				theApp.m_csXmlWTFile.Unlock(); //unlock the xml file

				send(ReceiveSocket, TimeOut, TimeOut.GetLength(), 0);

				closesocket(ReceiveSocket);
			} else if (RecvBuf[0] == 'E') { //to terminate thread
				closesocket(ReceiveSocket);
				WSACleanup();
				return 0;
			} else closesocket(ReceiveSocket);


		} //while(CPVCSApp::m_bIsAlive)
	}

	return 0;
}
//This Thread create server socket and perform as server
UINT ServerThreadProc(LPVOID pParam) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	// Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET ServerSocket;
		ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ServerSocket == INVALID_SOCKET) {
			AfxMessageBox("Unable to setup communication for Master machine. Restart PVCS", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
			WSACleanup();
			CPvcsScreenInfo::m_vecScreenInfo[0]->m_ptrScreenFrame->PostMessage(WM_CLOSE);
			return 0;
		}
		sockaddr_in ServerSocketaddr;

		ServerSocketaddr.sin_family = AF_INET;
		ServerSocketaddr.sin_addr.s_addr = inet_addr(theApp.GetMasterIP());
		ServerSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort());

		//pointer will be needed to cast to generic address type(struct sockaddr *)
		if (bind(ServerSocket, (SOCKADDR *)&ServerSocketaddr, sizeof(ServerSocketaddr)) == SOCKET_ERROR) {
			AfxMessageBox("Unable to bind Master machine to communication setup. Restart PVCS", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
			closesocket(ServerSocket);
			WSACleanup();
			CPvcsScreenInfo::m_vecScreenInfo[0]->m_ptrScreenFrame->PostMessage(WM_CLOSE);
			return 0;
		}

		// Listen on the socket.
		if (listen(ServerSocket, 5) == SOCKET_ERROR) {
			AfxMessageBox("Unable to listen Client request. Restart PVCS", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
			closesocket(ServerSocket);
			WSACleanup();
			CPvcsScreenInfo::m_vecScreenInfo[0]->m_ptrScreenFrame->PostMessage(WM_CLOSE);
			return 0;
		}

		SOCKET ClientSocket;
		sockaddr_in ClientSocketaddr;
		int ClientSocketLen = sizeof(ClientSocketaddr);
		char RecvBuf[5];

		int RecDataLen;

		while (CPVCSApp::m_bIsAlive) { //while PVCS application alive
									   //TRACE("\n Server waiting start");
			ClientSocket = accept(ServerSocket, (SOCKADDR *)&ClientSocketaddr, &ClientSocketLen);
			//clear buffer
			for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

			RecDataLen = recv(ClientSocket, RecvBuf, 5, 0);
			if (RecDataLen <= 0) { //if error in recv, do nothing
				closesocket(ClientSocket);
			} else { //if Recv is OK
				RecvBuf[RecDataLen] = '\0';
				CString RecData = RecvBuf;
				RecData.MakeLower();
				RecData.Trim('s');
				int RecvScreenNumber = atoi(RecData);

				//Signal To Close the Thread
				if (RecvScreenNumber == 100) {
					closesocket(ClientSocket);
					WSACleanup();
					return 0;
				}

				//client send "S200" when its up, and master send calibrate file to client
				else if (RecvScreenNumber == 200) {
					CString ClientIP = inet_ntoa(ClientSocketaddr.sin_addr);
					theApp.ConnectedClientMachineIP.push_back(ClientIP); //storing IP of the new client machine

					CFile XmlFile;
					bool IsCalibrateFileExists = false;
					bool DoTransfer = false;
					char StatusBuf[3];
					StatusBuf[0] = '\0';

					//For transmit xml file
					try {
						if (XmlFile.Open("xmlfiles\\calibrate.xml", CFile::modeRead)) {
							//If file exists or open correctly
							IsCalibrateFileExists = true;
							send(ClientSocket, "F1", strlen("F1"), 0);
						} else {
							//If file does not exists or unable to open
							IsCalibrateFileExists = false;
							send(ClientSocket, "F0", strlen("F0"), 0);
						}
					} catch (CFileException *e) {
						//file error so send a signal to client
						send(ClientSocket, "F0", strlen("F0"), 0);
						IsCalibrateFileExists = false;
					}

					//recv file status from client
					recv(ClientSocket, StatusBuf, sizeof(StatusBuf), 0);

					CString Buf = StatusBuf;
					Buf.MakeLower();
					Buf.TrimLeft('f');
					if (atoi(Buf) == 1) //if file opens correctly, do file transfer
						DoTransfer = true;
					else { //else don't transfer file
						if (IsCalibrateFileExists) XmlFile.Close();
						DoTransfer = false;
						closesocket(ClientSocket);
					}

					if (DoTransfer && IsCalibrateFileExists) {
						XmlFile.SeekToBegin();
						ULONGLONG FileSize = XmlFile.GetLength();

						CString SizeBuf = "";
						SizeBuf.Format("%lu", FileSize);

						send(ClientSocket, SizeBuf, SizeBuf.GetLength(), 0); //send file size

						recv(ClientSocket, StatusBuf, sizeof(StatusBuf), 0); //recv "1"

						DWORD BytesRead;
						char FileBuf[1024];
						FileBuf[0] = '\0';

						while (FileSize > 0) {
							BytesRead = XmlFile.Read(FileBuf, sizeof(FileBuf));
							send(ClientSocket, FileBuf, BytesRead, 0);
							FileSize = FileSize - BytesRead;
							FileBuf[0] = '\0';
							Sleep(50);
						}

						Sleep(100);
						XmlFile.Close();
						closesocket(ClientSocket);
					}
				}

				//Client having command and client is going to close
				else if (RecvScreenNumber == 101) {
					char RecvBuffer[100];
					RecvBuffer[0] = '\0';

					CString ClientIP = inet_ntoa(ClientSocketaddr.sin_addr);

					for (unsigned i = 0; i < theApp.ConnectedClientMachineIP.size(); i++) {
						if (ClientIP == theApp.ConnectedClientMachineIP[i]) {
							theApp.ConnectedClientMachineIP.erase(theApp.ConnectedClientMachineIP.begin() + i);
						}
					}

					//dummey send
					send(ClientSocket, "1", strlen("1"), 0);

					//recv screen numbers
					int ByteRecv = recv(ClientSocket, RecvBuffer, sizeof(RecvBuffer), 0);

					closesocket(ClientSocket);

					if (ByteRecv != SOCKET_ERROR) RecvBuffer[ByteRecv] = '\0';

					CString RecvData = RecvBuffer;
					CString TempData = "";

					for (int i = 0; i < RecvData.GetLength(); i++) {
						if (RecvData.GetAt(i) != '.') {
							TempData += RecvData.GetAt(i);
						} else {
							int RecvScreen = atoi(TempData);
							TempData = "";
							if (RecvScreen >= 1 && RecvScreen <= CPVCSApp::ScreenCount && !CPvcsScreenInfo::m_vecScreenInfo[RecvScreen - 1]->m_bCommandStatus) {
								CPvcsScreenInfo::m_vecScreenInfo[RecvScreen - 1]->m_bCommandStatus = true;
								CPvcsScreenInfo::m_vecScreenInfo[RecvScreen - 1]->m_strCommandingMachineIP = theApp.GetMasterIP();
								CString RevokingScreenTitle = CPvcsScreenInfo::m_vecScreenInfo[RecvScreen - 1]->m_strScreenTitle;
								CString NewWindowTitle = "";

								if (theApp.IsBackupMode) //if in backup mode
									NewWindowTitle.Format("PVCS Backup - %s, Master in Command Mode", RevokingScreenTitle);
								else NewWindowTitle.Format("PVCS - %s, Master in Command Mode", RevokingScreenTitle);

								CPvcsScreenInfo::m_vecScreenInfo[RecvScreen - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);
							}
						}
					}
				}


				//If request come for command
				else {
					//Check for command status, If Master doesn't having command with him
					if (!CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_bCommandStatus) {
						CString CommandingMachineIP = CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_strCommandingMachineIP;

						send(ClientSocket, CommandingMachineIP, CommandingMachineIP.GetLength(), 0);

						//clear buffer
						for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

						int ByteRecv = recv(ClientSocket, RecvBuf, sizeof(RecvBuf), 0);

						if (ByteRecv == SOCKET_ERROR) { //if fail in recv, then second check
							SOCKET RevokeSocket;
							//Create a socket
							if ((RevokeSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
								sockaddr_in CommandingSocketaddr;

								CommandingSocketaddr.sin_family = AF_INET;
								CommandingSocketaddr.sin_addr.S_un.S_addr = inet_addr(CommandingMachineIP);
								CommandingSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() - 1);

								if (connect(RevokeSocket, (SOCKADDR *)&CommandingSocketaddr, sizeof(CommandingSocketaddr)) == SOCKET_ERROR) closesocket(RevokeSocket);
								else {
									char Bufcommand[5];
									char DummyBuf[3];
									CString strScreenno = "";

									send(RevokeSocket, "R234", 5, 0);

									recv(RevokeSocket, DummyBuf, sizeof(DummyBuf), 0); //recv dummy

									strScreenno.Format("%d", RecvScreenNumber);

									send(RevokeSocket, strScreenno, strScreenno.GetLength(), 0); //send screen number

									recv(RevokeSocket, Bufcommand, 5, 0);

									int IsCommand = atoi(Bufcommand);

									if (IsCommand == 987) { //command changed
										CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_strCommandingMachineIP = inet_ntoa(ClientSocketaddr.sin_addr);
									}

									closesocket(RevokeSocket);
								}

								closesocket(RevokeSocket);
							}
						} //recv fails
						else if (atoi(RecvBuf) == 54) { //command granted
							CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_strCommandingMachineIP = inet_ntoa(ClientSocketaddr.sin_addr);
						}

						closesocket(ClientSocket);
					}
					//If Master machine having command
					else {
						//send signal to requesting machine, that master machine having command with him
						send(ClientSocket, "y", strlen("y"), 0);
						//check the recevied screen number is valid
						if (RecvScreenNumber >= 1 && RecvScreenNumber <= CPVCSApp::ScreenCount) {
							//retrive IP and machine name of the client machine
							CString ClientIP = "";
							CString MessageString = "";
							CString RequestingScreenTitle = "";
							char ClientName[NI_MAXHOST];
							char ClientService[NI_MAXSERV];

							RequestingScreenTitle = CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_strScreenTitle;

							ClientIP = inet_ntoa(ClientSocketaddr.sin_addr);

							if (getnameinfo((SOCKADDR *)&ClientSocketaddr, sizeof(sockaddr), ClientName, NI_MAXHOST, ClientService, NI_MAXSERV, NI_NUMERICSERV) == 0) { //if succeed
								if (_strcmpi(ClientName, ClientIP) != 0) { //if ClientName and Client Ip are not same, then show Client name with domain
									MessageString.Format("Computer %s (IP - %s) is requesting command for Screen - %s, Wish to grant request?", ClientName, ClientIP, RequestingScreenTitle);
								} else MessageString.Format("Computer (IP - %s) is requesting command for Screen - %s, Wish to grant request?", ClientIP, RequestingScreenTitle);
							} else MessageString.Format("Computer (IP - %s) is requesting command for Screen - %s, Wish to grant request?", ClientIP, RequestingScreenTitle);

							Beep(500, 100); //requiring attention of user by beep

							int MessageResponse = -1;

							MessageResponse = TimedMessageBox(NULL, MessageString, "PVCS", MB_SYSTEMMODAL | MB_SETFOREGROUND | MB_YESNO | MB_TOPMOST, ((theConfiguration().GetRequestTimeOut()) * 1000));

							//send Dummy signal to client, for select
							send(ClientSocket, "D", 2, 0);

							//Clear buffer
							for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

							//recv for time out check
							RecDataLen = recv(ClientSocket, RecvBuf, sizeof(RecvBuf), 0);

							if (RecDataLen <= 0) { //if recv error, then do nothing
								closesocket(ClientSocket);
							} else { //recv is OK
								RecData = RecvBuf;
								RecData.MakeLower();
								RecData.TrimLeft("t");
								int ResponseData = atoi(RecData);
								if (ResponseData == 1) { //TimeOut Occured
									closesocket(ClientSocket);
								} else if (ResponseData == 0) { //Timeout not occured
									if (MessageResponse == 6) { //Server ready to serve requset
																//send ok signal to client
										send(ClientSocket, "1", 2, 0);
										//if any control window opens then, close it
										if (theController().m_hWnd) {
											SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);
											theController().OnCloseWarningMessageWindow();
										}

										//Change server Commmand mode to Display Mode
										CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_bCommandStatus = false;
										CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_strCommandingMachineIP = ClientIP;
										CString NewWindowTitle = "";

										if (theApp.IsBackupMode) //if in backup mode
											NewWindowTitle.Format("PVCS Backup - %s, Master in Display Mode", RequestingScreenTitle);
										else NewWindowTitle.Format("PVCS - %s, Master in Display Mode", RequestingScreenTitle);

										CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);

										closesocket(ClientSocket);

									} else if (MessageResponse == 7) { //if messagebox return NO, send deninal message to client
										send(ClientSocket, "0", 2, 0); //send No signal to client
										closesocket(ClientSocket);
									} else if (MessageResponse == -1) {
										send(ClientSocket, "4", 2, 0); //send when time out occured
										closesocket(ClientSocket);
									} else {
										send(ClientSocket, "5", 2, 0); //send garbage signal
										closesocket(ClientSocket);
									}
									///TRACE("\n Server waiting end");
								} //if Timeout not occured, time out
							} //if recv OK, time out

						} //if screen number is vaild, then send "3" t show invalid screen number message to client
						else {
							send(ClientSocket, "3", 2, 0);
							closesocket(ClientSocket);
						}

					} //else, command with Master

				} //request come for command

			} //if recv is OK
		}
		closesocket(ServerSocket);
		WSACleanup();
	} else {
		AfxMessageBox("Unable to start system as Server. Restart PVCS", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
		WSACleanup();
		CPvcsScreenInfo::m_vecScreenInfo[0]->m_ptrScreenFrame->PostMessage(WM_CLOSE);
		return 0;
	}

	return 0;
}

//this thread send signal to the master machine that client comes up
UINT ClientSendUPSignalToServerThread(LPVOID pParam) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		//TRACE("\n Request start");
		SOCKET RequestSocket;
		//Create a socket
		RequestSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (RequestSocket == INVALID_SOCKET) {
			//AfxMessageBox("Unable to setup communication with Master, Retry later.",MB_ICONWARNING|MB_APPLMODAL,0);
			WSACleanup();
			return 0;
		}


		//connect socket to remote machine
		sockaddr_in ServerRequestSocketaddr;

		ServerRequestSocketaddr.sin_family = AF_INET;
		ServerRequestSocketaddr.sin_addr.S_un.S_addr = inet_addr(theApp.GetMasterIP());
		ServerRequestSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort());

		if (connect(RequestSocket, (SOCKADDR *)&ServerRequestSocketaddr, sizeof(ServerRequestSocketaddr)) == SOCKET_ERROR) {
			//AfxMessageBox("Unable to Connect to the Master machine, Retry later.",MB_ICONWARNING|MB_APPLMODAL,0);
			closesocket(RequestSocket);
			WSACleanup();
			return 0;
		} else { //if connect is oK, then send data
			if (send(RequestSocket, "S200", strlen("S200"), 0) == SOCKET_ERROR) { //if error in send
																				  //AfxMessageBox("Unable to send Request command to server, Retry later.",MB_ICONWARNING|MB_APPLMODAL,0);
				closesocket(RequestSocket);
				WSACleanup();
				return 0;
			}

			CFile XmlFile;
			char StatusBuf[3];
			bool IsCalibrateFileExists = false;

			//waits to get file signal from the master machine
			recv(RequestSocket, StatusBuf, sizeof(StatusBuf), 0);

			CString Buf = StatusBuf;
			Buf.MakeLower();
			Buf.TrimLeft('f');
			if (atoi(Buf) == 1) { //file open successfully and file exists at server side
				try {
					if (XmlFile.Open("xmlfiles\\calibrate.xml", CFile::modeCreate | CFile::modeWrite)) {
						IsCalibrateFileExists = true;
						send(RequestSocket, "F1", strlen("F1"), 0);
					} else {
						IsCalibrateFileExists = false;
						send(RequestSocket, "F0", strlen("F0"), 0);
						closesocket(RequestSocket);
						WSACleanup();
						return 0;
					}
				} catch (CFileException *e) {
					send(RequestSocket, "F0", strlen("F0"), 0);
					IsCalibrateFileExists = false;
					closesocket(RequestSocket);
					WSACleanup();
					return 0;
				}
			} else if (atoi(Buf) == 0) { //file does not exists at server side or unable to open,send F0, no need for transfer
				send(RequestSocket, "F0", strlen("F0"), 0);
				IsCalibrateFileExists = false;
				closesocket(RequestSocket);
				WSACleanup();
				return 0;
			}

			if (IsCalibrateFileExists) {
				XmlFile.SeekToBegin();

				char SizeBuf[20];
				char FileBuf[1024];
				FileBuf[0] = '\0';
				SizeBuf[0] = '\0';

				recv(RequestSocket, SizeBuf, sizeof(SizeBuf), 0);

				ULONG FileSize = atol(SizeBuf);
				DWORD BytesRecv = 0;

				send(RequestSocket, "1", strlen("1"), 0);

				while (FileSize > 0) {
					BytesRecv = recv(RequestSocket, FileBuf, sizeof(FileBuf), 0);
					XmlFile.Write(FileBuf, BytesRecv);
					FileSize = FileSize - BytesRecv;
					FileBuf[0] = '\0';
				}

				XmlFile.Close();
				closesocket(RequestSocket);
				WSACleanup();
			}
		}
	}
	return 0;

}

//this thread used for revoking command, in respect of 'Take Command' click from server side
UINT ClientThreadProc(LPVOID pParam) {
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	// Initialize winsock dll
	if (WSAStartup(wVersionRequested, &wsaData) == 0) {
		SOCKET ClientSocket;
		ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ClientSocket == INVALID_SOCKET) {
			AfxMessageBox("Unable to setup communication for Client machine. Restart PVCS", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
			WSACleanup();
			CPvcsScreenInfo::m_vecScreenInfo[0]->m_ptrScreenFrame->PostMessage(WM_CLOSE);
			return 0;
		}
		CString ClientIP;

		ClientIP = theApp.GetLocalIP();
		sockaddr_in ClientSocketaddr;

		ClientSocketaddr.sin_family = AF_INET;
		ClientSocketaddr.sin_addr.S_un.S_addr = inet_addr(ClientIP);
		ClientSocketaddr.sin_port = htons((u_short)theApp.GetMasterPort() - 1);

		//pointer will be needed to cast to generic address type(struct sockaddr *)
		if (bind(ClientSocket, (SOCKADDR *)&ClientSocketaddr, sizeof(ClientSocketaddr)) == SOCKET_ERROR) {
			AfxMessageBox("Unable to bind Client machine to communication setup. Restart PVCS", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
			closesocket(ClientSocket);
			WSACleanup();
			CPvcsScreenInfo::m_vecScreenInfo[0]->m_ptrScreenFrame->PostMessage(WM_CLOSE);
			return 0;
		}

		// Listen on the socket.
		if (listen(ClientSocket, 5) == SOCKET_ERROR) {
			AfxMessageBox("Unable to listen Master request. Restart PVCS", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
			closesocket(ClientSocket);
			WSACleanup();
			CPvcsScreenInfo::m_vecScreenInfo[0]->m_ptrScreenFrame->PostMessage(WM_CLOSE);
			return 0;
		}

		SOCKET ServerSocket;
		sockaddr_in ServerSocketaddr;
		int ServerSocketLen = sizeof(ServerSocketaddr);
		char RecvBuf[5];
		int RecDataLen;

		while (CPVCSApp::m_bIsAlive) { //while PVCS application alive
									   //TRACE("\n Client waiting start");
			ServerSocket = accept(ClientSocket, (SOCKADDR *)&ServerSocketaddr, &ServerSocketLen);

			//Clear buffer
			for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

			RecDataLen = recv(ServerSocket, RecvBuf, 5, 0);
			if (RecDataLen <= 0) { //if error in recv, restart the thread
				closesocket(ServerSocket);
			} else { //if recv OK
				CString RecvData = RecvBuf;

				//Clear buffer
				for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

				RecvData.MakeLower();
				RecvData.TrimLeft('r');
				int RevokingScreenNumber = atoi(RecvData);

				//check for close thread signal
				if (RevokingScreenNumber == 100) {
					closesocket(ServerSocket);
					WSACleanup();
					return 0;
				} else if (RevokingScreenNumber == 234) { //check for command status
					char ScreenNumber[5];

					send(ServerSocket, "d", 3, 0); //send dummay

					recv(ServerSocket, ScreenNumber, 5, 0); //recv screen number

					int iScreenNumber = atoi(ScreenNumber);

					if (CPvcsScreenInfo::m_vecScreenInfo[iScreenNumber - 1]->m_bCommandStatus) send(ServerSocket, "678", 5, 0);
					else send(ServerSocket, "987", 5, 0);

					closesocket(ServerSocket);

				}
				//if revoking command from a client machine, Client - Client (Command request - Command revoke)
				else if (RevokingScreenNumber == 101) {
					send(ServerSocket, "1", 2, 0);

					int ByteRecv = recv(ServerSocket, RecvBuf, sizeof(RecvBuf), 0);


					int RecvScreenNumber = atoi(RecvBuf);

					//check the recevied screen number is valid
					if (RecvScreenNumber >= 1 && RecvScreenNumber <= CPVCSApp::ScreenCount) {
						//retrive IP and machine name of the client machine
						CString ClientIP = "";
						CString MessageString = "";
						CString RequestingScreenTitle = "";
						char ClientName[NI_MAXHOST];
						char ClientService[NI_MAXSERV];

						RequestingScreenTitle = CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_strScreenTitle;

						ClientIP = inet_ntoa(ServerSocketaddr.sin_addr);

						if (getnameinfo((SOCKADDR *)&ServerSocketaddr, sizeof(sockaddr), ClientName, NI_MAXHOST, ClientService, NI_MAXSERV, NI_NUMERICSERV) == 0) { //if succeed
							if (_strcmpi(ClientName, ClientIP) != 0) { //if ClientName and Client Ip are not same, then show Client name with domain
								MessageString.Format("Computer %s (IP - %s) is requesting command for Screen - %s, Wish to grant request?", ClientName, ClientIP, RequestingScreenTitle);
							} else MessageString.Format("Computer (IP - %s) is requesting command for Screen - %s, Wish to grant request?", ClientIP, RequestingScreenTitle);
						} else MessageString.Format("Computer (IP - %s) is requesting command for Screen - %s, Wish to grant request?", ClientIP, RequestingScreenTitle);

						Beep(500, 100); //requiring attention of user by beep

						// NULL first parameter is important.
						int MessageResponse = -1;
						MessageResponse = TimedMessageBox(NULL, MessageString, "PVCS", MB_SETFOREGROUND | MB_SYSTEMMODAL | MB_YESNO | MB_TOPMOST, ((theConfiguration().GetRequestTimeOut()) * 1000));

						//int MessageResponse = AfxMessageBox(MessageString,MB_APPLMODAL|MB_YESNO|MB_TOPMOST,0);

						//send Dummy signal to client, for select
						send(ServerSocket, "D", 2, 0);

						//Clear buffer
						for (int i = 0; i < sizeof(RecvBuf); i++) RecvBuf[i] = ' ';

						//recv for time out check
						RecDataLen = recv(ServerSocket, RecvBuf, sizeof(RecvBuf), 0);

						if (RecDataLen <= 0) { //if recv error, then do nothing
							closesocket(ServerSocket);
						} else { //recv is OK
							RecvData = RecvBuf;
							RecvData.MakeLower();
							RecvData.TrimLeft("t");
							int ResponseData = atoi(RecvData);
							if (ResponseData == 1) { //TimeOut Occured
								closesocket(ServerSocket);
							} else if (ResponseData == 0) { //Timeout not occured
								if (MessageResponse == 6) { //Server ready to serve requset
															//send ok signal to client
									send(ServerSocket, "1", 2, 0);
									//if any control window opens then, close it
									if (theController().m_hWnd) {
										SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);
										theController().OnCloseWarningMessageWindow();
									}

									//Change client Commmand mode to Display Mode
									CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_bCommandStatus = false;
									CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_strCommandingMachineIP = ClientIP;
									CString NewWindowTitle = "";

									if (theApp.IsBackupMode) //if in backup mode
										NewWindowTitle.Format("PVCS Backup - %s, Client in Display Mode", RequestingScreenTitle);
									else NewWindowTitle.Format("PVCS - %s, Client in Display Mode", RequestingScreenTitle);

									CPvcsScreenInfo::m_vecScreenInfo[RecvScreenNumber - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);

									closesocket(ServerSocket);

								} else if (MessageResponse == 7) { //if messagebox return NO, send deninal message to client
									send(ServerSocket, "0", 2, 0); //send No signal to client
									closesocket(ServerSocket);
								} else if (MessageResponse == -1) {
									send(ServerSocket, "4", 2, 0); //send when time out occured
									closesocket(ServerSocket);
								} else {
									send(ServerSocket, "5", 2, 0); //send garbage signal
									closesocket(ServerSocket);
								}
								//TRACE("\n Server waiting end");
							} //if Timeout not occured, time out
						} //if recv OK, time out
					} else {
						send(ServerSocket, "3", 2, 0);
						closesocket(ServerSocket);
					}


				} else { //for revoking command by Master machine
						 //if revoking request for valid screen
					if (RevokingScreenNumber >= 1 && RevokingScreenNumber <= CPVCSApp::ScreenCount) {
						//if any control window opens then, close it
						if (theController().m_hWnd) {
							SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);
							theController().OnCloseWarningMessageWindow();
						}

						//if screen having command, then revoke it
						send(ServerSocket, "1", 2, 0);
						closesocket(ServerSocket);

						if (CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_bCommandStatus) {
							CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_bCommandStatus = false;
							CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strCommandingMachineIP = theApp.GetMasterIP();

							CString NewWindowTitle = "";

							if (theApp.IsBackupMode) NewWindowTitle.Format("PVCS Backup - %s, Client in Display Mode", CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strScreenTitle);
							else NewWindowTitle.Format("PVCS - %s, Client in Display Mode", CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_strScreenTitle);

							CPvcsScreenInfo::m_vecScreenInfo[RevokingScreenNumber - 1]->m_ptrScreenFrame->SetWindowText(NewWindowTitle);
						}
						//TRACE("\n Client waiting end");

					} else { //if revoking request for invalid screen number
						send(ServerSocket, "0", 2, 0);
						closesocket(ServerSocket);
					}
				}

			}
		}
		closesocket(ClientSocket);
		WSACleanup();
	} else {
		AfxMessageBox("Unable to start system as Client. Restart PVCS", MB_SETFOREGROUND | MB_ICONWARNING | MB_APPLMODAL | MB_TOPMOST, 0);
		WSACleanup();
		CPvcsScreenInfo::m_vecScreenInfo[0]->m_ptrScreenFrame->PostMessage(WM_CLOSE);
		return 0;
	}

	return 0;
}

void CPVCSApp::OnFileTimeoutlist() {
	if (theCTimeOut().WarningTimeoutStatus == false) {
		XmlQueue *tempXmlQueue;

		tempXmlQueue = new XmlQueue;

		tempXmlQueue->eType = TimeoutWin;
		tempXmlQueue->strScreenNumber = "";
		tempXmlQueue->strObjectName = "";
		tempXmlQueue->strMessage = "";

		tempXmlQueue->strMachineIP = "";
		tempXmlQueue->strTime = "";
		tempXmlQueue->bIsWarning_Timeout = true;

		//Thread that push item into the queue
		AfxBeginThread(XmlWTQueuePush_Thread, tempXmlQueue);


		theCTimeOut().Create(IDD_Time_out_Dialog);
		theCTimeOut().ShowWindow(SW_SHOW);
		theCTimeOut().WarningTimeoutStatus = true;


	}
}





void CPVCSApp::OnUpdateFileCalibrate(CCmdUI *pCmdUI) {
	if (m_bIsServer) pCmdUI->Enable(1);
	else pCmdUI->Enable(0);
}




void CPVCSApp::OnFileWagounitstatus() {
	if (pobjWagoUnitStatus == NULL) pobjWagoUnitStatus = new CWagoUnitStatus();
	else {
		pobjWagoUnitStatus->SendMessage(WM_CLOSE);
		pobjWagoUnitStatus = new CWagoUnitStatus();
	}
}

CWagoUnitStatus* CPVCSApp::GetWagoUnitStatusDialog(void) {
	return pobjWagoUnitStatus;
}

void CPVCSApp::SetNULLWagoUnitStatusDialog(void) {
	pobjWagoUnitStatus = NULL;
}

//This function to update the view, for redrawing the button
void CCalibrateChannels::UpdateView(void) {
	CString strAnalog = "";

	for (unsigned i = 0; i < m_CalibrationData.size(); i++) {
		strAnalog = m_CalibrationData[i].Type;

		if (strAnalog.MakeLower() == "analog") {
			CRect StartRect, StopRect;

			CRect ClientRect;

			m_CalibrationData[i].ptrStartListButton->ShowWindow(SW_HIDE);
			m_CalibrationData[i].ptrStopListButton->ShowWindow(SW_HIDE);

			m_ListCalibrationList.GetClientRect(&ClientRect);

			m_ListCalibrationList.GetSubItemRect(i, 6, LVIR_BOUNDS, StartRect);

			if (ClientRect.top < StartRect.top && StartRect.left < ClientRect.right) {
				StartRect.left += 50;

				m_CalibrationData[i].ptrStartListButton->SetWindowPos(&CWnd::wndTop, StartRect.left, StartRect.top, StartRect.Width(), StartRect.Height(), SWP_SHOWWINDOW);

				m_CalibrationData[i].ptrStartListButton->ShowWindow(SW_SHOW);

				m_ListCalibrationList.GetSubItemRect(i, 7, LVIR_BOUNDS, StopRect);

				StopRect.left += 50;

				m_CalibrationData[i].ptrStopListButton->SetWindowPos(&CWnd::wndTop, StopRect.left, StopRect.top, StopRect.Width(), StopRect.Height(), SWP_SHOWWINDOW);

				m_CalibrationData[i].ptrStopListButton->ShowWindow(SW_SHOW);
			} else {
				m_ListCalibrationList.SetItemText(0, 6, "Start");
				m_ListCalibrationList.SetItemText(0, 7, "Stop");
			}

		} else {
			m_ListCalibrationList.SetItemText(i, 6, m_CalibrationData[i].StartText);
			m_ListCalibrationList.SetItemText(i, 7, m_CalibrationData[i].StopText);
		}

	}

}

void CCalibrateChannels::SetItemText(int Row, int Col, CString Text) {
	m_ListCalibrationList.SetItemText(Row, Col, Text);
}

void CCalibrateChannels::UpdateCalibrationXMLFile(int Row) {
	CString strRow = "";
	strRow.Format("%d", Row);

	CCriticalSection objcriticalSection;

	objcriticalSection.Lock();

	if (LoadXMLFile("XMLFILES\\calibrate.xml")) {
		if (Remove_Node(CCalibrateChannels::m_CalibrationData[Row].ObjectName, CCalibrateChannels::m_CalibrationData[Row].Channel)) {
			SaveCalibrationFile("XMLFILES\\calibrate.xml");
		}

		CreateElement("Data");
		CreateNode("ObjectName", m_ListCalibrationList.GetItemText(Row, 0));
		CreateNode("Row", strRow);
		CreateNode("Channelnumber", m_ListCalibrationList.GetItemText(Row, 5));
		CreateNode("Start", m_ListCalibrationList.GetItemText(Row, 6));
		CreateNode("Stop", m_ListCalibrationList.GetItemText(Row, 7));
		SaveCalibrationFile("xmlfiles\\calibrate.xml");
	} else {

		WriteRootNode("Calibration");
		CreateElement("Data");
		CreateNode("ObjectName", m_ListCalibrationList.GetItemText(Row, 0));
		CreateNode("Row", strRow);
		CreateNode("Channelnumber", m_ListCalibrationList.GetItemText(Row, 5));
		CreateNode("Start", m_ListCalibrationList.GetItemText(Row, 6));
		CreateNode("Stop", m_ListCalibrationList.GetItemText(Row, 7));
		SaveCalibrationFile("xmlfiles\\calibrate.xml");
	}

	CCalibrateWago objCalibrateWago;

	if (objCalibrateWago.LoadXMLFile("xmlfiles\\calibrate.xml")) {
		CCalibrateWago::m_CalibrateData.clear();
		objCalibrateWago.GetCalibrationDataVector();
	}

	objcriticalSection.Unlock();

	if (theApp.ConnectedClientMachineIP.size() > 0) {
		CString strAnalog = "";
		for (unsigned i = 0; i < m_CalibrationData.size(); i++) {
			strAnalog = m_CalibrationData[i].Type;

			if (strAnalog.MakeLower() == "analog") {
				m_CalibrationData[i].ptrStartListButton->EnableWindow(0);
				m_CalibrationData[i].ptrStopListButton->EnableWindow(0);;
			}
		}
		m_ListCalibrationList.EnableWindow(0);

		theApp.m_bIsCalibrationFileTransferComplete = false;

		m_StatusText.ShowWindow(SW_SHOW);

		//worker thread that send calibrate.xml file to all connected clients
		AfxBeginThread(SendCalibrationFileToAllClient, 0);
	}
}

void CCalibrateChannels::OnLvnEndScrollCalibrationList(NMHDR *pNMHDR, LRESULT *pResult) {
	// This feature requires Internet Explorer 5.5 or greater.
	// The symbol _WIN32_IE must be >= 0x0560.
	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
	UpdateView();
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CCalibrateChannels::OnHdnDividerdblclickCalibrationList(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	UpdateView();
	*pResult = 0;
}

void CCalibrateChannels::OnTimer(UINT_PTR nIDEvent) {
	if (theApp.m_bIsCalibrationFileTransferComplete && !m_ListCalibrationList.IsWindowEnabled()) {
		CString strAnalog = "";
		for (unsigned i = 0; i < m_CalibrationData.size(); i++) {
			strAnalog = m_CalibrationData[i].Type;

			if (strAnalog.MakeLower() == "analog") {
				m_CalibrationData[i].ptrStartListButton->EnableWindow(1);
				m_CalibrationData[i].ptrStopListButton->EnableWindow(1);
			}
		}
		m_ListCalibrationList.EnableWindow(1);
		m_StatusText.ShowWindow(SW_HIDE);
	}
	CDialog::OnTimer(nIDEvent);

}
void CCalibrateChannels::OnHdnEndtrackCalibrationList(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	UpdateView();
	*pResult = 0;
}

void CCalibrateChannels::OnHdnBegintrackCalibrationList(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	CString strAnalog = "";

	for (unsigned i = 0; i < m_CalibrationData.size(); i++) {
		strAnalog = m_CalibrationData[i].Type;

		if (strAnalog.MakeLower() == "analog") {
			m_CalibrationData[i].ptrStartListButton->ShowWindow(SW_HIDE);
			m_CalibrationData[i].ptrStopListButton->ShowWindow(SW_HIDE);
		}
	}
	*pResult = 0;
}






void CAboutDlg::OnBnClickedOk() {
	// TODO: Add your control notification handler code here
	OnOK();
}

void CAboutDlg::OnStnClickedEdit() {
	// TODO: Add your control notification handler code here
}

//Thread that keep track when emergency operation of all the control will be over and broadcast over message
UINT EmgOperationOver(LPVOID pParam) {
	int *Temp = (int *)pParam;
	int  iEmgBtn = *Temp;
	int iCurrentOperationOver = 0;

	int iTotalControls = CEmgButtonOperation::m_EmgButtonInfo[iEmgBtn]->iTotalOperation;

	while (iTotalControls != iCurrentOperationOver) {

		iCurrentOperationOver = 0;
		CEmgButtonOperation::ControlInfo *pControlInfo;
		pControlInfo = CEmgButtonOperation::m_EmgButtonInfo[iEmgBtn]->Next_ControlInfo;

		while (pControlInfo != NULL) {
			if (!CPVCSApp::m_bIsAlive) return 0;
			if (CDxfLayout::GetControlOperationState(pControlInfo->uiControlIndex, pControlInfo->uiControlSubIndex)) iCurrentOperationOver++;

			pControlInfo = pControlInfo->Next_ControlInfo;
		}

		Sleep(3000);
	}

	if (iTotalControls == iCurrentOperationOver) {
		//operation over
		CEmgButtonOperation::m_EmgButtonInfo[iEmgBtn]->bIsOperationGoing = false;

		CString strMsg = "";
		strMsg.Format("%s#over", theApp.GetLocalIP());
		theApp.SendBroadcastMessage(strMsg);
	}

	return 0;
}

//Thread that initiate emergency operations
UINT InitiateEmgOperation(LPVOID pParam) {
	int *Temp = (int *)pParam;

	int iButtonIndex = *Temp;

	CString strMsg = "";

	strMsg.Format("%s#start", theApp.GetLocalIP());

	//broadcast "start" message
	theApp.SendBroadcastMessage(strMsg);

	bool ResetAllDigitalOut = CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->bResetAllOutputs;
	if (ResetAllDigitalOut) {
		CPvcsWagoControl::theWagoUnit().ResetAllValues();
	} else {
		//start emergency operation control object thread
		CEmgButtonOperation::ControlInfo *pControlInfo;
		pControlInfo = CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->Next_ControlInfo;

		//Keep on while having control object for the particular button
		while (pControlInfo != NULL) {
			if (CPVCSApp::bStartNewEmgThread) {
				CDxfLayout::SetControlOperationState(pControlInfo->uiControlIndex, pControlInfo->uiControlSubIndex, false);
				CWinThread *pThread = AfxBeginThread(EmgButtonActionThread, pControlInfo, THREAD_PRIORITY_HIGHEST);
				CPVCSApp::bStartNewEmgThread = false;
				pControlInfo = pControlInfo->Next_ControlInfo;
			} else Sleep(10);
		}

		//start thread, that check for control object emg. operation over
		AfxBeginThread(EmgOperationOver, &iButtonIndex, THREAD_PRIORITY_HIGHEST);
	}
	Sleep(5000);

	return 0;
}

//Thread, client's response on emg. operation
UINT ClientEmgOperation(LPVOID pParam) {
	int *Temp = (int *)pParam;

	int iButtonIndex = *Temp;

	CString strMessage = "";
	CString strIP = "";
	CString strData = "";
	UINT uReturnState = 0;

	while (CPVCSApp::m_bIsAlive) {
		//wait for time based on IP,
		CString strLocalIP = theApp.GetLocalIP();

		CString str = "";

		for (int i = strLocalIP.GetLength() - 1; i > 0; i--) {
			char t = strLocalIP.GetAt(i);
			if (t != '.') str += t;
			else break;
		}

		str.MakeReverse();

		int iIP = atoi(str);

		iIP = iIP % 10;

		iIP = (iIP * 5) + 5;

		theApp.RecvBroadcastMessage(strMessage, iIP);

		uReturnState = theApp.GetBroadcastMessage(strMessage, strIP, strData);

		if (uReturnState ==  1) { //message is timeout
								  //master machine not present, so client will start the operation
			AfxBeginThread(InitiateEmgOperation, &iButtonIndex, THREAD_PRIORITY_HIGHEST);
			Sleep(5000);
			break;
		} else if (uReturnState == 3) {
			//master initiated the operation
			if (strData.MakeLower() == "start") {
				CString strMsg = "";

				if (strIP == theApp.GetMasterIP()) strMsg.Format("Master machine initiated the Emergency operation.");
				else strMsg.Format("Machine having IP - %s, initiated the Emergency operation.", strIP);
				//display operation strated message
				AfxMessageBox(strMsg, MB_SETFOREGROUND | MB_ICONINFORMATION | MB_APPLMODAL | MB_TOPMOST, 0);

				//wait for operation over message from the master, and also check the master state
				while (CPVCSApp::m_bIsAlive) {
					CString strConnectIP = "";
					CString strMachineIP = "";

					theApp.RecvBroadcastMessage(strMessage, iIP);

					uReturnState = theApp.GetBroadcastMessage(strMessage, strMachineIP, strData);

					if (uReturnState == 3) {
						if (strData.MakeLower() == "over") { //master sends operation over message
															 //operation over
							CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->bIsOperationGoing = false;
							//display message
							AfxMessageBox("Emergency operation completed.", MB_SETFOREGROUND | MB_ICONINFORMATION | MB_APPLMODAL | MB_TOPMOST, 0);
							break;
						} else if (strData.MakeLower() == "start") { //some other client machine sends operation start message
																	 //display operation strated message
							CString strTempIP = "";
							strTempIP.Format("Machine having IP - %s, initiated the Emergency operation.", strMachineIP);
							strIP = strMachineIP;
							AfxMessageBox(strTempIP, MB_SETFOREGROUND | MB_ICONINFORMATION | MB_APPLMODAL | MB_TOPMOST, 0);
						}
					} else if (uReturnState == 1) { //timeout, so check the machine state
													//operation initiating machine is not alive and now another machine will start the operation again
						strConnectIP = strIP;
						if (!theApp.ConnectEmgOptMachine(strConnectIP)) {
							//initiate emg operation
							AfxBeginThread(InitiateEmgOperation, &iButtonIndex, THREAD_PRIORITY_HIGHEST);
							Sleep(5000);
							break;
						}
					} //else if(uReturnState == 1)
				} //while(1)
			} //if(strData.MakeLower() == "start")
			else continue;

			break;
		} //else if(uReturnState == 3)
	} //while(1)

	return 0;
}

//Thread sense the input on wago unit for emergency operation
UINT EmgOperation(LPVOID pParam) {
	unsigned ButtonSize = CEmgButtonOperation::m_EmgButtonInfo.size();;
	if (ButtonSize) {
		bool EmgButtonStatus = false;
		vector<bool>bInvertInput;
		vector<double>dTreshold;
		vector<int>iInputType;
		vector<int>iWagoUnit;
		vector<int>iWagoChNo;
		vector<bool>bRemoteControl;

		for (unsigned i = 0; i < ButtonSize; i++) {
			bInvertInput.push_back(CEmgButtonOperation::m_EmgButtonInfo[i]->bInvertInput);
			dTreshold.push_back(CEmgButtonOperation::m_EmgButtonInfo[i]->dInputThreshold);
			iInputType.push_back(CEmgButtonOperation::m_EmgButtonInfo[i]->iInputType);
			iWagoUnit.push_back(CEmgButtonOperation::m_EmgButtonInfo[i]->iWagoUnit);
			iWagoChNo.push_back(CEmgButtonOperation::m_EmgButtonInfo[i]->iWagoChNo);
			bRemoteControl.push_back(CEmgButtonOperation::m_EmgButtonInfo[i]->bRemoteControl);
		}

		while (CPVCSApp::m_bIsAlive) {
			for (unsigned ButtonCounter = 0; ButtonCounter < CEmgButtonOperation::m_EmgButtonInfo.size(); ButtonCounter++) {
				if (CPvcsWagoControl::theWagoUnit().GetEmgButtonInput(iWagoUnit[ButtonCounter], iWagoChNo[ButtonCounter], bInvertInput[ButtonCounter], iInputType[ButtonCounter], dTreshold[ButtonCounter], EmgButtonStatus)) {
					//CEmgButtonOperation::m_EmgButtonInfo[i]->bIsOperationGoing, for controlling one time operation
					if (EmgButtonStatus) {
						bool ResetAllDigitalOut = CEmgButtonOperation::m_EmgButtonInfo[ButtonCounter]->bResetAllOutputs;
						if (ResetAllDigitalOut) {
							CPvcsWagoControl::theWagoUnit().ResetAllValues();
						} else {
							if (!(CEmgButtonOperation::m_EmgButtonInfo[ButtonCounter]->bIsOperationGoing || CEmgButtonOperation::m_EmgButtonInfo[ButtonCounter]->bIsEmgLightON)) {
								CEmgButtonOperation::m_EmgButtonInfo[ButtonCounter]->bIsOperationGoing = true;
								CEmgButtonOperation::m_EmgButtonInfo[ButtonCounter]->bIsEmgLightON = true;

								//if machine is master
								if (theApp.IsServerMachine()) {
									//new thread master initiate the operation
									AfxBeginThread(InitiateEmgOperation, &ButtonCounter, THREAD_PRIORITY_HIGHEST);
								} else { //new thread client waiting for master initiation
										 //new thread client waits for emg. operation response from master machine
									AfxBeginThread(ClientEmgOperation, &ButtonCounter, THREAD_PRIORITY_HIGHEST);
								}

							}
						}
						if (bRemoteControl[ButtonCounter] && !theApp.m_pdlgManualControl) {
							theApp.m_pdlgManualControl = new CManualControlDialog;
							theApp.m_pdlgManualControl->Create(IDD_PVCS_MANUAL_CTRL_DLG);
							theApp.m_pdlgManualControl->ShowWindow(SW_SHOW);
						}
					} else if (!theApp.bIsEmegencySwitchFault) {
						//for re start the operation, only when light, give a pluse of low to high,
						CEmgButtonOperation::m_EmgButtonInfo[ButtonCounter]->bIsEmgLightON = false;
						if (/*bRemoteControl[ButtonCounter] &&*/theApp.m_pdlgManualControl) {
							CEmgButtonOperation::m_EmgButtonInfo[ButtonCounter]->bIsOperationGoing = false;
							theApp.m_pdlgManualControl->PostMessage(WM_CLOSE);
							theApp.m_pdlgManualControl->DestroyWindow();
							delete theApp.m_pdlgManualControl;
							theApp.m_pdlgManualControl = NULL;
						}
					}
				}

				Sleep(500);
			}
		}
	}
	return 0;
}


#pragma warning (disable: 4100)

static void CALLBACK AlarmBeepTimer(HWND hwnd, UINT msg, UINT interval, DWORD dwTime) {
	//int iActAlarmSize = theShipData().m_AlarmData.size();
	////int iAckAlarmSize = theShipData().m_AckAlarmData.size();
	CTankData TempObj;

	TempObj.GetAlarmStatus();

	//Beep only when recv. "1" from the ANWIN.
	if (!theApp.m_bAlarmSoundOFF) {
		if (CTankData::m_AlarmStatus != "" && CTankData::m_AlarmStatus == "1") Beep(200, 200);
	} else theApp.m_bAlarmSoundOFF = false;

	////Old way to beep
	//if(iActAlarmSize > 0)//Active Red
	//{
	//	if(CPVCSApp::ActAlarmCount == -1)
	//	{
	//		Beep(200,200);
	//	}
	//	else if(CPVCSApp::ActAlarmCount < iActAlarmSize )
	//	{
	//		CPVCSApp::ActAlarmCount = -1;
	//		Beep(200,200);
	//	}
	//}
}
// To handle pumps including transfer of command
UINT PumpThreadProc(LPVOID pParam) {
	Sleep(5000);
	if (!CPvcsToolBarPumpButton::MySet.empty()) {
		while (CPVCSApp::m_bIsAlive) { //while PVCS application alive
			Sleep(250);

			set<CPvcsToolBarPumpButton *>::iterator pBIt;
			for (pBIt = CPvcsToolBarPumpButton::MySet.begin(); pBIt != CPvcsToolBarPumpButton::MySet.end(); pBIt++) {
				(*pBIt)->CheckInReleaseControlReq();
				if ((*pBIt)->HasReceivedControlRequest()) {
					CString mMessage = "Release pump control " + (*pBIt)->GetMessage() + "?";
					int MessageResponse = TimedMessageBox(NULL, mMessage, "PVCS", MB_SYSTEMMODAL | MB_SETFOREGROUND | MB_YESNO | MB_TOPMOST, ((theConfiguration().GetRequestTimeOut()) * 1000));
					(*pBIt)->ResetHasReceivedControlRequest();
					switch (MessageResponse) {
					case 6:
						(*pBIt)->SetReleaseControl(true);
						Sleep(100);
						(*pBIt)->SetAbortControlRequest(false);
						break;
					case 7:
						(*pBIt)->SetReleaseControl(false);
						Sleep(100);
						(*pBIt)->SetAbortControlRequest(true);
						break;
					}
				}
			}//For
		}//While
	}// If
	return 0;
}


