#pragma once
#include <windows.h>
// STL for Stings
#include <string>
using std::string;
// Winsock Library
#include <winsock2.h>
#include <afxsock.h>

#define IN
#define OUT

class CSendData:public CAsyncSocket
{
public:
	// Class Constructor
	CSendData();
	// Class Destructor
	virtual ~CSendData(void);
	// To Send data to PVCS from SURVEYOR 
	bool SendData(IN const void* param_ucData ,OUT const UINT& param_uiSize);
	// Listens for request on the Socket
	bool ReceiveRequest();
	// Connects to PVCS
	bool ConnectPVCS(IN CString param_csIPAddress);
	// Handle for the thread function
	HANDLE m_thThreadHandle;
	// Disconnect The Socket n Ports
	bool DisconnectPVCS(void);
	// returns the status of the Connection state connected or not connected
	bool GetConnectionStatus(void);
	// to store the Status of connection  and socket
	bool a_bolConnectionStatus;
	// the IP Address of Local machine
	static char ipaddress[17];
private:
	// To Initialize the Socket for communication
	bool InitSocket(IN CString param_csIPAddress);
	// Handle for Winsock Connection at the SURVEYOR end
    static SOCKET m_socConnection;
	// IP of surveyor
	static CString m_ucSurveyorIPAddress;
	// Thread Listining for connection request from PVCS
	static UINT MTIPSServerThread(LPVOID param_pParam);
	

	
};
