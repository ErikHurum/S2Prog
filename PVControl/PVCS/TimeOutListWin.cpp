// TimeOutListWin.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "TimeOutListWin.h"
#include "writetimeouts.h"
#include ".\timeoutlistwin.h"
bool CTimeOutListWin::WarningTimeoutStatus=false;
// CTimeOutListWin dialog

CTimeOutListWin& theCTimeOut()
{
	static CTimeOutListWin TimeOutObj;
	return TimeOutObj;
}

IMPLEMENT_DYNAMIC(CTimeOutListWin, CDialog)
CTimeOutListWin::CTimeOutListWin(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeOutListWin::IDD, pParent)	
{
}

CTimeOutListWin::~CTimeOutListWin()
{
}

void CTimeOutListWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Time_Out_LIST, m_TimeoutList);
}


BEGIN_MESSAGE_MAP(CTimeOutListWin, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTimeOutListWin message handlers


BOOL CTimeOutListWin::OnInitDialog()
{
CDialog::OnInitDialog();
BuildList();
CWriteTimeouts WriteTimeoutsObj;
//SetTimer( IDD_Time_out_Dialog, 5000, NULL );

//if ( WriteTimeoutsObj.LoadTimeOutXML(WriteTimeoutsObj.GetWarningFilePath()))
//{
	//WriteTimeoutsObj.GetWarningTimeoutDataVector();
	int VectorSize=WriteTimeoutsObj.m_WarningTimeout.size(); 
	//WriteTimeoutsObj.UnloadXMLFile();//"XMLFILES\\warningTimeOut.xml");
	for(int i=0;i<VectorSize;i++)
	{
		m_TimeoutList.InsertItem(i,WriteTimeoutsObj.m_WarningTimeout[i].ObjID);
		m_TimeoutList.SetItemText(i,1,WriteTimeoutsObj.m_WarningTimeout[i].TimeRaised);
		m_TimeoutList.SetItemText(i,2,WriteTimeoutsObj.m_WarningTimeout[i].MachineIP);
		m_TimeoutList.SetItemText(i,3,WriteTimeoutsObj.m_WarningTimeout[i].Message);
	}	
return true;
//}
//else
//{
 //  return false;
//}
}
void CTimeOutListWin::BuildList()
{
	m_TimeoutList.SetExtendedStyle( m_TimeoutList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	// determine the columns 
	m_TimeoutList.InsertColumn( 0, "Object ID");
	m_TimeoutList.InsertColumn( 1, "Time Raised");
	m_TimeoutList.InsertColumn( 2, "Machine IP");
	m_TimeoutList.InsertColumn( 3, "Message");
	m_TimeoutList.SetColumnWidth( 0, 75);
	m_TimeoutList.SetColumnWidth( 1, 200);
	m_TimeoutList.SetColumnWidth( 2, 100);
	m_TimeoutList.SetColumnWidth( 3, 100);	
	
}

void CTimeOutListWin::CreateTimeoutListWindow(void)
{


}
void CTimeOutListWin::OnBnClickedButton1()
{
	//TRACE("\n************************************************On ok start\n");
	theCTimeOut().WarningTimeoutStatus=false;
	KillTimer(IDD_Time_out_Dialog);
	ShowWindow(SW_HIDE);
	DestroyWindow();
	//TRACE("\n************************************************On ok end\n");
}

void CTimeOutListWin::OnTimer(UINT nIDEvent)
{
	//TRACE("\n************************************************On Timer start\n");
	//m_TimeoutList.DeleteAllItems();

	XmlQueue *tempXmlQueue;

	tempXmlQueue = new XmlQueue;

	tempXmlQueue->eType = TimeoutWin;
	tempXmlQueue->strScreenNumber = "";
	tempXmlQueue->strObjectName = "";
	tempXmlQueue->strMessage = "";

	tempXmlQueue->strMachineIP = "";
	tempXmlQueue->strTime = "";
	tempXmlQueue->bIsWarning_Timeout = false;

	//Thread that push item into the queue
	AfxBeginThread(XmlWTQueuePush_Thread,tempXmlQueue);


	//if(!theApp.IsServerMachine())
	//{
	//	//Get new warningTimeOut.xml file from the server
	//	theApp.Warning_TimeOut_XMLFileTransfereClient(3,-1);
	//}

	//CString FilePath = "";
	//FilePath = "xmlfiles\\warningTimeOut.xml";

	//CWriteTimeouts CWriteTimeoutsTempobj2;
	//
	////Clear the Vector
	//int size=CWriteTimeoutsTempobj2.m_WarningTimeout.size();
	//if(size>0)
	//	CWriteTimeoutsTempobj2.m_WarningTimeout.clear();
	//
	//if(CWriteTimeoutsTempobj2.LoadTimeOutXML(FilePath))
	//{
	//	CWriteTimeoutsTempobj2.FillVector_TimeOut();
	//	CWriteTimeoutsTempobj2.SaveXMLFile(FilePath);
	//}
	//

	while(!m_bIsVectorUpdated)
		Sleep(30);

	m_TimeoutList.DeleteAllItems();
	CWriteTimeouts tempObjCWriteTimeouts;
	int VectorSize1=tempObjCWriteTimeouts.m_WarningTimeout.size(); 

	for(int i=0;i<VectorSize1;i++)
	{
		m_TimeoutList.InsertItem(i,tempObjCWriteTimeouts.m_WarningTimeout[i].ObjID);
		m_TimeoutList.SetItemText(i,1,tempObjCWriteTimeouts.m_WarningTimeout[i].TimeRaised);
		m_TimeoutList.SetItemText(i,2,tempObjCWriteTimeouts.m_WarningTimeout[i].MachineIP);
		m_TimeoutList.SetItemText(i,3,tempObjCWriteTimeouts.m_WarningTimeout[i].Message);
	}	

	m_bIsVectorUpdated = false;

	//TRACE("\n************************************************On Timer End\n");
	CDialog::OnTimer(nIDEvent);
}

void CTimeOutListWin::SetVectorUpdated(bool State)
{
	m_bIsVectorUpdated = State;
	return;
}