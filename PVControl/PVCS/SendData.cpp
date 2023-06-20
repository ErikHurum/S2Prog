#include "StdAfx.h"
#include ".\senddata.h"
char CSendData::ipaddress[17];
CSendData::CSendData()
: a_bolConnectionStatus(0)
, m_thThreadHandle(NULL)
{
	a_bolConnectionStatus=false;
}

CSendData::~CSendData(void)
{

}

//added
UINT CSendData::MTIPSServerThread(LPVOID param_pParam)
{
	WSADATA m_wsaData;
	ULONG m_ulNonBlock;
	
	struct sockaddr_in m_structserver;
	int m_iwsaret=WSAStartup(MAKEWORD(2,2),&m_wsaData);
	if(m_iwsaret)	
			return false;
	m_socConnection=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if( m_socConnection == INVALID_SOCKET )
			return false;
	
	m_structserver.sin_addr.s_addr=inet_addr(m_ucSurveyorIPAddress);
	m_structserver.sin_family=AF_INET;
	// To listen on specified machine IP on port 9999
	m_structserver.sin_port=htons(9999);

	if ( bind( m_socConnection, (struct sockaddr*)&m_structserver, sizeof(m_structserver) ) == SOCKET_ERROR )
	{
			//Socket Initialization Failed
		 AfxMessageBox("Error In Establishing TCP/IP Connection");
		 closesocket(m_socConnection);
		 return false;
	}
	
	// Listen on the socket.
	if ( listen( m_socConnection, 1 ) == SOCKET_ERROR )
	{
		//Error Listening on socket
		AfxMessageBox("Error In Establishing TCP/IP Connection");
	}
	
	// Accept connections.
    SOCKET m_socAcceptSocket;
	
	// Waiting for Connection Infinitely
		while (1) 
		{
			//
			m_socAcceptSocket = SOCKET(SOCKET_ERROR);
				while ( m_socAcceptSocket == SOCKET_ERROR ) 
				{
					m_socAcceptSocket = accept(m_socConnection, NULL, NULL );
				}
			m_socConnection = m_socAcceptSocket; 
			m_ulNonBlock = 1;
			if (ioctlsocket(m_socConnection, FIONBIO, &m_ulNonBlock) == SOCKET_ERROR)
			{
				return false;
			}
			return true;
			break;
		};
	return 0;
}

// to here

// To Initialize the Socket for communication
bool CSendData::InitSocket(IN CString param_csIPAddress)
{	
	DWORD m_dwID[1];
	
	m_ucSurveyorIPAddress=ipaddress;
	m_thThreadHandle=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)MTIPSServerThread,NULL,0,&m_dwID[0]);
    return true;	
}


// To Send data to PVCS from SURVEYOR 
bool CSendData::SendData(IN const void* param_ucData ,OUT const UINT& param_uiSize)
{
   	//bool m_bolSendStatus;
	int m_iBytesSend;
	m_iBytesSend=send(m_socConnection,reinterpret_cast<const char*>(param_ucData),param_uiSize,0);
	if(m_iBytesSend==-1)
	{
		//TRACE("NOT CONNECTED\n");
	}
	if( m_iBytesSend == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
// Listens for request on the Socket
bool CSendData::ReceiveRequest()
{		
	char m_cSignal[10];
	int m_iDataRecvSize;
	m_iDataRecvSize=recv(m_socConnection,m_cSignal,sizeof(m_cSignal), 0);
	int errorcode=WSAGetLastError();
	//TRACE("ERROR CODE = %d \n",errorcode);
	if(errorcode==10054)
	{
		DisconnectPVCS();
		ConnectPVCS("127.0.0.1");
	}
	if(strcmp(m_cSignal,"SDATA")==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Connects to PVCS
bool CSendData::ConnectPVCS(IN CString param_csIPAddress)
{ 
	//added 12.12
	char *ip;
	char name[255];
	PHOSTENT hostinfo;
	
	//added 12.12
	ip=new char;
	gethostname ( name, sizeof(name)) ;
	if((hostinfo = gethostbyname(name)) != NULL)
	{
		ip = inet_ntoa (*(struct in_addr *)hostinfo->h_addr_list[0]);
		strcpy_s(ipaddress,ip);
	}
	//
	bool m_bConnectionStatus;
	
	if(a_bolConnectionStatus==false)
	{
		m_bConnectionStatus=InitSocket(ip);
		if(m_bConnectionStatus == true)
		{
			a_bolConnectionStatus=true;
		}
		else 
		{
			a_bolConnectionStatus=false;
		}
	}
	else
	{
		a_bolConnectionStatus=true;
	}
	delete [] ip;
	return a_bolConnectionStatus;
}

// Disconnect The Socket n Ports
bool CSendData::DisconnectPVCS(void)
{
	 if(closesocket(m_socConnection) == SOCKET_ERROR)
	 {
		return false;
	 }
	 else
	 {	
		 a_bolConnectionStatus=false;
		 WSACleanup();
		 return true;
	 }
}

// returns the status of the Connection state connected or not connected
bool CSendData::GetConnectionStatus(void)
{
	if(a_bolConnectionStatus==true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

SOCKET CSendData::m_socConnection;
CString CSendData::m_ucSurveyorIPAddress;
