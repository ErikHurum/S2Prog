#include "StdAfx.h"
#include ".\pvcs v1.0.h"
#include ".\pvcscontrolobjecttimeoutinfo.h"
#include "warningmessage.h"
#include "writetimeouts.h"
#include "dxflayout.h"
#include <set>


TimeOutInfoSet& theTimeOutInfo()
{
	static TimeOutInfoSet timeOutInfo;

	return timeOutInfo;
}

CPvcsControlObjectTimeOutInfo::CPvcsControlObjectTimeOutInfo(const UINT& param_uiIndex, const UINT& param_uiSubIndex)
: m_uiIndex(param_uiIndex)
, m_uiSubIndex(param_uiSubIndex)
, m_bTimedOut(false)
{
}

CPvcsControlObjectTimeOutInfo::~CPvcsControlObjectTimeOutInfo(void)
{
}

void CPvcsControlObjectTimeOutInfo::SetTimeOut(const bool& param_bIsTimeOut)
{
	m_bTimedOut = param_bIsTimeOut;

	//where you can get time out at particular screen
	CString t_name =  CDxfLayout::GetObjectName(m_uiIndex,m_uiSubIndex,-1);
	int a= CDxfLayout::GetControlScreenNumber(m_uiIndex,m_uiSubIndex,-1); 
	CString a1;
	a1.Format("%d",a);
	a1 = "SNO" + a1  ;

	COleDateTime TempDate;

	TempDate = COleDateTime::GetCurrentTime();
	
	CString TimeRaised;
	
	TimeRaised = TempDate.Format();

	XmlQueue *tempXmlQueue;

	tempXmlQueue = new XmlQueue;


	tempXmlQueue->eType = Timeout;
	tempXmlQueue->strScreenNumber = a1;
	tempXmlQueue->strObjectName = t_name;
	tempXmlQueue->strMessage = "Warning Timeout";

	tempXmlQueue->strMachineIP = theApp.GetLocalIP();
	tempXmlQueue->strTime = TimeRaised;
	tempXmlQueue->bIsWarning_Timeout = m_bTimedOut;

	//Thread that push item into the queue
	AfxBeginThread(XmlWTQueuePush_Thread,tempXmlQueue);




	//CWriteTimeouts wt; 
	//if( param_bIsTimeOut == true )
	//{
	//   if(wt.LoadTimeOutXML("xmlfiles\\warningTimeOut.xml"))
	//{
	//    if(wt.FindScreen(a1))
	//	{
	//		   //wt.GetNode("TimeOut"); 
	//		   //wt.Remove_ControlEntry_WarningMessage("WarningMessage",O_Name); 
	//		   wt.NodeName_TimeOut("TimeOut",t_name);
	//		   if(theApp.IsServerMachine())
	//			   theApp.m_bIsTimeOutUpdated = true;
	//		   wt.SaveXMLFile("xmlfiles\\warningTimeOut.xml");	
	//	}
	//	else
	//	{
	//		wt.GetRootPointer();
	//		wt.PreserveRootPointer(a1); 
	//		wt.Create_Element_Function("TimeOut"); 
	//		wt.WriteTimeOutDataToFile(t_name,theApp.GetLocalIP());  
	//	  /* wt.Create_Element_Function("TimeOut"); 
	//	   wt.WriteTimeOutDataToFile("CurrentDisplayObjName","10.140.1.113","TimeOut");  */
	//		if(theApp.IsServerMachine())
	//			theApp.m_bIsTimeOutUpdated = true;
	//		wt.SaveXMLFile("xmlfiles\\warningTimeOut.xml" );
	//	}
	//}
	//else 
	//{
	//	   
	//		wt.InitTimeoutHeader("xmlfiles\\warningTimeOut.xml","Messages");
	//		wt.PreserveRootPointer(a1);
	//		wt.Create_Element_Function("TimeOut");
	//		wt.WriteTimeOutDataToFile(t_name,theApp.GetLocalIP()); 
	//		/*wt.Create_Element_Function("TimeOut"); 
	//		wt.WriteTimeOutDataToFile("CurrentDisplayObjName","m_SystemIP","TimeOut"); */
	//		if(theApp.IsServerMachine())
	//			theApp.m_bIsTimeOutUpdated = true;
	//		wt.SaveXMLFile("xmlfiles\\warningTimeOut.xml");	
	//	}	
 // 		
	//if(!theApp.IsServerMachine()) 
	//{
	//	//this function send updated buffer to the master machine to update the xml file, for the timeout occures on client side
	//	theApp.Warning_TimeOut_XMLFileTransfereClient(2,a);
	//}

	//}
	//else   // write code to delete node from file.
	//{
	//	int vectorsize=CWriteTimeouts::m_WarningTimeout.size();
	//	if(vectorsize>0)
	//	{
	//		for(int i=0;i<vectorsize;i++)
	//		{
	//			CString objectName;
	//			objectName=CWriteTimeouts::m_WarningTimeout[i].ObjID;
	//			if(objectName==t_name)
	//			{
	//				if(wt.LoadTimeOutXML("xmlfiles\\warningTimeOut.xml") )
	//				{
	//					wt.Remove_ControlEntry_TimeOut(a1,"TimeOut",objectName );
	//					
	//					wt.SaveXMLFile("xmlfiles\\warningTimeOut.xml");
	//				}
	//				if(theApp.IsServerMachine())
	//					theApp.m_bIsTimeOutUpdated = true;
	//				else 
	//				{
	//				//this function send updated buffer to the master machine to update the xml file
	//				theApp.Warning_TimeOut_XMLFileTransfereClient(2,a);
	//				}
	//			}
	//		}
	//	
	//	
	//	}

	//}


}
const bool& CPvcsControlObjectTimeOutInfo::GetTimeOut(void) const
{
	return m_bTimedOut;
}

UINT CPvcsControlObjectTimeOutInfo::GetIndex(void)
{
	return m_uiIndex; 
}
bool operator<(const CPvcsControlObjectTimeOutInfo& lhsInfo, const CPvcsControlObjectTimeOutInfo& rhsInfo)
{
	return lhsInfo.m_uiIndex == rhsInfo.m_uiIndex ? 
		lhsInfo.m_uiSubIndex < rhsInfo.m_uiSubIndex
		: lhsInfo.m_uiIndex < rhsInfo.m_uiIndex;
}