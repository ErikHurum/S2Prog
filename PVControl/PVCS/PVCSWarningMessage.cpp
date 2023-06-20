// PVCSWarningMessage.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PVCSWarningMessage.h"
#include ".\pvcswarningmessage.h"
#include "pvcscontrolobjectinfo.h"
#include "PvcsObjectControlDlg.h"
#include ".\PvcsObjectControlDlg.h"
#include "DxfLayout.h"
#include <string>

int PVCSWarningMessage::m_dialoginitalise=0;
CString PVCSWarningMessage::m_WarningMessage=" ";
bool PVCSWarningMessage::DialgVisible=false;
LPTSTR PVCSWarningMessage::WarningMessage1="";//Added JSD 29MARCH2007



// PVCSWarningMessage dialog
PVCSWarningMessage& theWarningMessage()
{
	static PVCSWarningMessage warningMessage;
	return warningMessage;
}

IMPLEMENT_DYNAMIC(PVCSWarningMessage, CDialog)
PVCSWarningMessage::PVCSWarningMessage(CWnd* pParent /*=NULL*/)
	: CDialog(PVCSWarningMessage::IDD, pParent)
{
	
}

PVCSWarningMessage::~PVCSWarningMessage()
{
}


//BOOL PVCSWarningMessage::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//	//if(m_dialoginitalise==1)
//	//m_warningMessage.GetWindowText(tempbuffer,50);
//	return true;
//}
void PVCSWarningMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_warningMessageedit);
	
}


BEGIN_MESSAGE_MAP(PVCSWarningMessage, CDialog)
	//ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_ON, OnBnClickedButtonOn)	
	ON_WM_CLOSE() 
END_MESSAGE_MAP()

CString PVCSWarningMessage::returnedittext()
{
	m_warningMessageedit.GetWindowText(tempbuffer,50);
	theWarningMessage().m_WarningMessage=tempbuffer;
	return tempbuffer;

}

void PVCSWarningMessage::OnClose()
{
	PVCSWarningMessage::DialgVisible=false;
	EndDialog(1);	
	//		CDialog::OnClose();  
}
// PVCSWarningMessage message handlers

//void PVCSWarningMessage::OnBnClickedButtonOk()
//{
//	//if(theController().GetWindowDC()!=NULL)
//	//{
//	//m_warningMessageedit.GetWindowText(m_WarningMessage);
//	////CString Tempcopy1=_T(Tempcopy);
//	////int length=Tempcopy1.GetLength();
//	////CPvcsControlObjectDlg::WarningMessage1=Tempcopy1.GetBuffer(length);
//	//////Tempcopy1.ReleaseBuffer();
//	////static_cast  <LPTSTR>
//	//	
//	////CPvcsControlObjectDlg::WarningMessage=
//	//m_dialoginitalise=0;
//	//OnOK();
//	//}
//	//else
//		//OnOK();
//
//}

void PVCSWarningMessage::OnEnChangeEdit1()
{

	m_dialoginitalise=1;
	m_warningMessageedit.LimitText(40);
	  
}

void PVCSWarningMessage::OnBnClickedButtonOn()
{
 	m_warningMessageedit.GetWindowText(m_WarningMessage);
    
	if(m_WarningMessage != "")
	{
		int sNo =  theController().GetControlobjectInfo().GetScreenNumber();  	
		CString sn , temp_fileData;
		sn.Format("%d",sNo);
		sn = "SNO" + sn;
		CString O_Name = theController(). GetControlobjectInfo().GetName();

		theController().m_editwin.SetWindowText(m_WarningMessage);

		XmlQueue *tempXmlQueue;

		tempXmlQueue = new XmlQueue;


		tempXmlQueue->eType = Message;
		tempXmlQueue->strScreenNumber = sn;
		tempXmlQueue->strObjectName = O_Name;
		tempXmlQueue->strMessage = m_WarningMessage;

		tempXmlQueue->strMachineIP = "";
		tempXmlQueue->strTime = "";
		tempXmlQueue->bIsWarning_Timeout = true;

		//Thread that push item into the queue
		AfxBeginThread(XmlWTQueuePush_Thread,tempXmlQueue);
		
		theWarningMessage().m_WarningMessage="";
		m_dialoginitalise=0;
		PVCSWarningMessage::DialgVisible=false;
	}
	else
	{
		m_dialoginitalise=0;
		PVCSWarningMessage::DialgVisible=false;
	}

	OnOK();
	
//	CWriteTimeouts wt; 
//	if(m_WarningMessage !=  "")
//	{
//	if(wt.LoadTimeOutXML("xmlfiles\\warningTimeOut.xml"))
//		{
//		    if( wt.FindScreen(sn) ) //if exists in xml file
//		   {
////		       wt.GetNode("WarningMessage"); 
//			   //wt.Remove_ControlEntry_WarningMessage("WarningMessage",O_Name); 
//			  // wt.FillVector(); 
//			   wt.NodeName_WarningMessage("WarningMessage",O_Name,m_WarningMessage);
//			   wt.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
//		   }
//		   else      //if do not exists in xml file
//		   {
//		   wt.GetRootPointer();
//		   //wt.PreserveRootPointer(); 
//		   CString a;
//		   a.Format("%d",sNo); 
//		   a = "SNO" + a;
//		   wt.PreserveRootPointer(a);
//		   wt.Create_Element_Function("WarningMessage"); 
//           wt.WriteWarningMessageToFile(O_Name,m_WarningMessage);  
//		  /* wt.Create_Element_Function("TimeOut"); 
//		   wt.WriteTimeOutDataToFile("CurrentDisplayObjName","10.140.1.113","TimeOut");  */
//		   wt.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
//		   }
//		   
//		}
//		else 
//		{
//			wt.InitTimeoutHeader("xmlfiles\\warningTimeOut.xml","Messages");
//			CString a;
//			a.Format("%d",sNo); 
//			a = "SNO" + a;
//			wt.PreserveRootPointer(a);
//			wt.Create_Element_Function("WarningMessage");
//			
//			wt.WriteWarningMessageToFile(O_Name , m_WarningMessage  ); 
//			/*wt.Create_Element_Function("TimeOut"); 
//			wt.WriteTimeOutDataToFile("CurrentDisplayObjName","m_SystemIP","TimeOut"); */
//			wt.SaveXMLFile("xmlfiles\\warningTimeOut.xml");	
//		}
//
//		if(!theApp.IsServerMachine()) 
//		{
//			//this function send updated buffer to the master machine to update the xml file
//			theApp.Warning_TimeOut_XMLFileTransfereClient(2,sNo);
//		}
//
//	
//	//m_warningMessageedit.GetWindowText(m_WarningMessage);
//	int vectorsize = theController().WarningMessageVector.size();
//	
//	WarningMessageStroge tempobj0;
//	tempobj0.ControlObjName=theController().CurrentDisplayObjName;
//	CString tempabc;	
//	tempobj0.ObjWarningMessage=theWarningMessage().m_WarningMessage;	
//	theController().WarningMessageVector.push_back(tempobj0);
//	//START JSD 29MARCH2007
//	CString Tempcopy1=_T(theWarningMessage().m_WarningMessage);
//	int length=Tempcopy1.GetLength();
//	WarningMessage1=Tempcopy1.GetBuffer(length);
//	theController().m_editwin.SetWindowText(WarningMessage1);
//	Tempcopy1.ReleaseBuffer();
//	//END JSD 29MARCH2007
//	//START JSD 22-08-2007
////	char WarningMessageXMLFile[60]; 
////	CString FileLocation;
////	GetCurrentDirectory(60,WarningMessageXMLFile);
////	FileLocation=CString(WarningMessageXMLFile);
////	FileLocation+="\\XMLFILES\\WarningMessage.xml";
////	WIN32_FIND_DATA tempabcd;
////	bool CurrentNodeStatus;
////	if(FindFirstFile(FileLocation,&tempabcd)==INVALID_HANDLE_VALUE) 
////	{			
////		//WarningMessageObj1.InitAlarmHeader(FileLocation);
////        WarningMessageObj1.Ini();  
////		WarningMessageObj1.SetXMLHeader();
////		WarningMessageObj1.WriteRootNode("WarningMessage");
////		WarningMessageObj1.CreateNode(theController().CurrentDisplayObjName,theWarningMessage().m_WarningMessage);
////		WarningMessageObj1.SaveXMLFile(FileLocation);   
////	}
////	else
////	{
////		
////			//WarningMessageObj2.Load_Xml();
////		//WarningMessageObj2.Ini(); 
//////		WarningMessageObj2.InitAlarmHeader("\\XMLFILES\\WarningMessage.xml"); 
////		WarningMessageObj2.LoadXMLFile(FileLocation);
////		CurrentNodeStatus=WarningMessageObj2.GetNodeText(theController().CurrentDisplayObjName);
////		if(CurrentNodeStatus)
////		{
////			WarningMessageObj2.edit_xml(theController().CurrentDisplayObjName,theWarningMessage().m_WarningMessage);
////		}
////		else
////		{
////			
////			WarningMessageObj2.CreateNode(theController().CurrentDisplayObjName,theWarningMessage().m_WarningMessage);
////			WarningMessageObj2.SaveXMLFile(FileLocation); 
////		}
////		
////	}

	//END JSD 22-08-2007
	
}

void PVCSWarningMessage::onCommandTransfer()
{
	char WarningMessageXMLFile[90];
	CString FileLocation;
	GetCurrentDirectory(90,WarningMessageXMLFile);
	FileLocation=CString(WarningMessageXMLFile);
	FileLocation+="\\XMLFILES\\WarningMessage.xml";
	WIN32_FIND_DATA tempabc;	
	if(FindFirstFile(FileLocation,&tempabc)!=INVALID_HANDLE_VALUE) 
	{	
		CPvcsControlObjectDlg::WarningMessageVector.clear();		
		WarningMessageObj2.InitializeXMLParcer();
		if( WarningMessageObj2.LoadXMLFile(FileLocation) )
		{
		WarningMessageObj2.SaveXMLFile(FileLocation);  
		WarningMessageObj2.FillVector();
		}
	
	}
}

