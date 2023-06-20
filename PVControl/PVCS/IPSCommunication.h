#pragma once
#include "afxsock.h"
#include "winsock2.h"

////////////////////////////////////////////////////////////////////////////////////
// Class for establishing connection with Machine running SURVEYOR using winsock 
// and receiving data from IT
////////////////////////////////////////////////////////////////////////////////////

class CIPSCommunication :
	public CAsyncSocket
{
public:
	CIPSCommunication(void);
	virtual ~CIPSCommunication(void);
	
private:
	// Initialize The WINSOCK parameters to request connection from IPS
	static bool InitSocket(void);
protected: 
	static int counter;
public:
	// to Request Connection from IPS
	static bool RequestConnect(IN CString SurveyorIP,UINT param_uiPort);
   	// To receive Buffer from IPS
	bool ReceiveIPSData(OUT char* param_ucData,OUT UINT& param_uiSize);
	// To Send Request TO IPS for Sending Sensor data to PVCS
	bool SendDataRequest(void);
	// To Break Connection FROM IPS
	bool DisconnectFromIPS(void);
	// Connection Handle
	static SOCKET m_socConnection;

	
	
private:
	// To tell the status of connection connected or not connected
	static bool a_bolConnectionStatus;
public:
	// To give the status of connection
	bool GetConnectionStatus(void);
	// To Write the SURVEYOR DATA TO FILE
	bool SaveIPSDataToFile(BYTE*  param_ucData, UINT& param_uiSize);
		// To chech and resart connection
	bool resatblishConnection(IN CString SurveyorIP,UINT param_uiPort);
	// to initialize windows socket
	static void InitializeSocket(void);
	
	// Handle for the thread function
	HANDLE m_thThreadHandle;

private:
	// variable to have state of connection
	volatile bool m_bIsConnected;
	// Surveyor IP
	static CString m_pstrSurveyorIP;
	static UINT m_pstrPortID;
public:

	bool SendDataToIPS(CString AlaramDataFromAlaramCtrl);//Added JSD 09-08-2007
};
