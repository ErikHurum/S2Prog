#include "StdAfx.h"
#include ".\ipscommunication.h"

SOCKET CIPSCommunication::m_socConnection;
CString CIPSCommunication::m_pstrSurveyorIP=NULL;
UINT CIPSCommunication::m_pstrPortID=0;
bool CIPSCommunication::a_bolConnectionStatus=false;


CIPSCommunication::CIPSCommunication(void)
:m_bIsConnected(false)
, m_thThreadHandle(NULL)

{
	// to initialize WSA Socket
	InitializeSocket();
}

CIPSCommunication::~CIPSCommunication(void)
{
	closesocket(m_socConnection);
	//WSACleanup();
	//TRACE("Destructor Called"); 
	
}

// Initialize The WINSOCK parameters to request connection from IPS
bool CIPSCommunication::InitSocket(void)
{
	
	WSADATA wsaData;
	WORD wVersionrequested;

	wVersionrequested = MAKEWORD(2,0);
	if(WSAStartup(wVersionrequested, &wsaData) == 0)
		return true;
	else
		return false;
}
#pragma warning (disable: 4189)

// to Request Connection from IPS
bool CIPSCommunication::RequestConnect(IN CString param_SurveyorIP,UINT param_uiPort)
{
	
	//TRACE("Initial Request Connect Called\n");
	m_pstrSurveyorIP=param_SurveyorIP;
	m_pstrPortID=param_uiPort;


	struct sockaddr_in structServer;
		
	m_socConnection=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    //TRACE("SOCKET Number Is  %d",m_socConnection); 	
 	if(m_socConnection==INVALID_SOCKET)
	{
		return false;
	}

	structServer.sin_addr.s_addr=inet_addr(param_SurveyorIP);
	structServer.sin_family=AF_INET;
	structServer.sin_port=htons(u_short(param_uiPort));
	
	
	
	int sockerror = connect(m_socConnection,(struct sockaddr*)&structServer,sizeof(structServer));	
	UINT sockerr = WSAGetLastError();

	if(sockerror==0)
	{
		a_bolConnectionStatus=true;
		return true;
		
	}

	else
	{
		//TRACE("SockError %d",sockerr);
		//TRACE("Close Socket called");
		closesocket(m_socConnection);
		a_bolConnectionStatus=false;
		return false;	
	}
}

// To receive Buffer from IPS
bool CIPSCommunication::ReceiveIPSData(OUT char* param_ucData,OUT UINT& param_uiSize)
{
	//TRACE("RecieveIPS Data Called\n");

	timeval CheckTimeout;

	CheckTimeout.tv_sec = 7;//5 sec
	CheckTimeout.tv_usec = 0;

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(m_socConnection,&fds);

	int Result = select(m_socConnection,&fds,NULL,NULL,&CheckTimeout);

	FD_CLR(m_socConnection,&fds);

	if(Result == 0 || Result == -1)
	{
		return false;
	}

	int byteRecv;
	char sizeBuf[20];
	ULONG BufferSize;
	CString BufferData = "";	

	if(recv(m_socConnection,sizeBuf,20,0) != SOCKET_ERROR)
	{
		BufferSize = atol(sizeBuf);
		

		if(send(m_socConnection,"1",2,0) == SOCKET_ERROR)
		{
			return false;
		}

		ULONG nLeftCharLength = BufferSize;
		
		CString strData = "";
		char BufferData[8210];
        
		int nBufferLength = 0;
		
		while(nLeftCharLength > 0)
		{
			if(nLeftCharLength < 8192)
				nBufferLength = nLeftCharLength;
			else
				nBufferLength = 8192;
				
			timeval CheckTimeoutn;

			CheckTimeoutn.tv_sec = 5;//5 sec
			CheckTimeoutn.tv_usec = 0;
			
			fd_set fdsn;
			FD_ZERO(&fdsn);
			FD_SET(m_socConnection,&fdsn);

			int Result = select(m_socConnection,&fdsn,NULL,NULL,&CheckTimeoutn);
			
			FD_CLR(m_socConnection,&fdsn);
			
			if(Result == 0 || Result == -1)
			{
				return false;
			}

            byteRecv = recv(m_socConnection,BufferData,nBufferLength,0);
			if(byteRecv == SOCKET_ERROR)
			{
				int error = WSAGetLastError();
				return false;
			}
			
			
			BufferData[byteRecv] = '\0';
			strData += BufferData;
			
			if(byteRecv == 0)
			{
				break;
			}
            
			nLeftCharLength -= byteRecv;
			
		}

		param_uiSize = BufferSize;
		strcpy_s(param_ucData,100000,strData);
		
		return true;
	}
	else
	{
		return false;
	}
}
// To Send Request TO IPS for Sending Sensor data to PVCS
bool CIPSCommunication::SendDataRequest(void)
{
	char cSignal[6] = "SDATA";
	int iSendStatus;

	iSendStatus = send(m_socConnection,cSignal,strlen("SDATA"),0);
	if(iSendStatus == 5)
		return true;
	else
		return false;
}

// To Break Connection FROM IPS
bool CIPSCommunication::DisconnectFromIPS(void)
{
	//TRACE("\nDisconnect From IPS Called\n");
	closesocket(m_socConnection);
	//WSACleanup();
	return true;
}

// To give the status of connection
bool CIPSCommunication::GetConnectionStatus(void)
{
	//TRACE("Get Connection Sattus Called\n");
	if (a_bolConnectionStatus==true)
	{
		//TRACE("Connection Status True\n");
		return true;
	}
	else
	{
		//TRACE("Connection Status False\n");
		return false;
	}
}

// To Write the SURVEYOR DATA TO FILE
bool CIPSCommunication::SaveIPSDataToFile(BYTE*  param_ucData, UINT& param_uiSize)
{
	//TRACE("Save DataToFile\n");
	CFile destFile("C:\\cpy.xml",CFile::modeCreate | CFile::modeWrite);
	destFile.Write(param_ucData,param_uiSize);
	destFile.Close();
	param_ucData=NULL;
	return true;
}

// To chech and resart connection
bool CIPSCommunication::resatblishConnection(IN CString SurveyorIP,UINT param_uiPort)
{
	bool status = false;
    //TRACE("\nRestablishConnection function\n");
	status = RequestConnect(SurveyorIP,param_uiPort);
	return status;
}
// to initialize windows socket
void CIPSCommunication::InitializeSocket(void)
{
	//TRACE("Initialize socket function\n");
	a_bolConnectionStatus=false;
	InitSocket();
}

//Start Addition JSD
bool CIPSCommunication::SendDataToIPS(CString AlaramDataFromAlaramCtrl)
{
	CString AlaramData;
	//TRACE("\nSendData To IPS\n");
	AlaramData=AlaramDataFromAlaramCtrl;
	int length=strlen(AlaramData);
	int iSendStatus;
	iSendStatus=send(m_socConnection,AlaramData,length,0);
	if(iSendStatus==length)
		return true;
	else
		return false;
}
//End Addition JSD
