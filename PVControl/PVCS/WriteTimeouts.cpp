#include "StdAfx.h"
#include ".\writetimeouts.h"
#include "writetimeouts.h"
#include "pvcsobjectcontroldlg.h"
#include "TimeOutListWin.h"
using namespace std;

vector <WarningTimeout>CWriteTimeouts::m_WarningTimeout;

CWriteTimeouts::CWriteTimeouts(void)
: m_pcFilename(_T(""))
{
		InitCOM();
	 	Initialize();
}

CWriteTimeouts::~CWriteTimeouts(void)
{
	// Deinitialize COM
	//::CoUninitialize();
	
}

void CWriteTimeouts::GetRootPointer()
{
  t_Preserve =  m_plDomDocument->documentElement;
}
//required when you do not have screen number in xml
void CWriteTimeouts::PreserveRootPointer(CString sNumber)
{
	m_pFileNode=NULL;
	BSTR ElementName;
	
	ElementName=CStrToBstr(sNumber);
	m_pNode= m_plDomDocument->createElement(_T(ElementName));
	m_pFileNode = t_Preserve->appendChild(m_pNode);
	::SysFreeString(ElementName);
}
void CWriteTimeouts::Create_Element_Function(CString ElementName)
{
	CreateElement(ElementName);  
}

bool CWriteTimeouts::InitTimeoutHeader(CString param_pcFileName, CString param_strRootNodeName)
{
	/*InitCOM();
	Initialize();*/
	SetXMLHeader();
	
	WriteRootNode(param_strRootNodeName);
	m_pcFilename=param_pcFileName;
	/*m_plDomDocument;
	m_pDocRoot;*/
	return true;
}

// To write the block to the XML file
bool CWriteTimeouts::WriteTimeOutDataToFile(const CString& param_objectID, CString MachineIP)
{
	CString strLine;

	CreateNode( "ObjID", param_objectID );
	COleDateTime TempDate;
	TempDate = COleDateTime::GetCurrentTime();
	CString TimeRaised1;
	TimeRaised1=TempDate.Format();
	CreateNode( "TimeRaised",TimeRaised1);
	CreateNode("MachineIP",MachineIP);  
	CreateNode("Message","Warning TimeOut");
	WarningTimeout WarningTimeoutObj1;
	WarningTimeoutObj1.ObjID=param_objectID;
	WarningTimeoutObj1.TimeRaised=TimeRaised1;
	WarningTimeoutObj1.MachineIP=MachineIP;
	WarningTimeoutObj1.Message="Warning TimeOut";
	m_WarningTimeout.push_back(WarningTimeoutObj1);
	if(theCTimeOut().WarningTimeoutStatus==true)
	{
		int listSize1=theCTimeOut().m_TimeoutList.GetItemCount();
		theCTimeOut().m_TimeoutList.InsertItem(listSize1,param_objectID);
		theCTimeOut().m_TimeoutList.SetItemText(listSize1,1,TimeRaised1);
		theCTimeOut().m_TimeoutList.SetItemText(listSize1,2,MachineIP);
		theCTimeOut().m_TimeoutList.SetItemText(listSize1,3,"Warning TimeOut");
	}

//	SaveXMLFile(m_pcFilename);
	return false;
}

bool CWriteTimeouts::LoadTimeOutXML(CString t_FileName)
{
	 	/*InitCOM(); 
	 	Initialize();*/
	
	_bstr_t	 bstr_FileName =t_FileName.AllocSysString();

	 variant_t vResult;
	 vResult=m_plDomDocument->load(bstr_FileName);

	if((bool)vResult==true)
	{
		//element pointer
		m_pDocRoot =m_plDomDocument->documentElement;
	    ::SysFreeString(bstr_FileName);         	
		return true;
	}
	else
	{
		::SysFreeString(bstr_FileName);
		return false;
	}
}

bool CWriteTimeouts::ReadXMLFile(CString t_FileName)
{
	MSXML2::IXMLDOMNodePtr ptr;
	for(ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
	    
	   	_bstr_t text;  
		 text=ptr->Gettext();
		::SysFreeString(text);
	} 
	m_pNode = m_pDocRoot; 
	return true;
} 

MSXML2::IXMLDOMNodeListPtr CWriteTimeouts::GetNode(CString param_pcNodeName)
{
	//MSXML2::IXMLDOMNodeListPtr pNodeList;
	BSTR NodeNames;
	NodeNames=CStrToBstr(param_pcNodeName);
	pNodeList=m_plDomDocument->documentElement->selectNodes(NodeNames);
	::SysFreeString(NodeNames);
	return pNodeList;
}
#pragma warning (disable: 4189)


bool  CWriteTimeouts::NodeName_WarningMessage(CString t_node,CString param_ObjectName,CString pram_Message)  
{
	
	MSXML2::IXMLDOMNodePtr pTempChild;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
    bool check = false;
	CString pcRetValue;
	BSTR NodeNames;
	_bstr_t text;
	  	
	int count = pNodeList->length;
	CString node_val;		
		
	for(int j=0;j<pNodeList->length;j++)
	{
	pNodeList->get_item(j, &pTempChild);
	NodeNames=CStrToBstr(t_node);
	pTempChildVal=pTempChild->selectSingleNode(NodeNames);

	if(pTempChildVal)  //if warning message tag exists
	{
		
		for(MSXML2::IXMLDOMNodePtr ptr=pTempChildVal->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
			{
	 		if(!strcmp(ptr->Gettext(),param_ObjectName))
				{				
					ptr->Puttext(param_ObjectName.AllocSysString ());
					check = true;
				    //else if (!strcmp(ptr->nodeName,"Warning"))
					ptr = ptr->nextSibling;			  
					ptr->Puttext(pram_Message.AllocSysString ());
				}
			}
		if(check == false )
		{
			m_pFileNode = pTempChildVal;
			WriteWarningMessageToFile(param_ObjectName,pram_Message);  	    
		}
		::SysFreeString(text); 
		::SysFreeString(NodeNames); 	
		return true;  
	}
	else   //if warning message tag does not exists
	{
		/*GetRootPointer();*/
		//pNodeList
		m_pNode  = pTempChild; 
		Create_Element_Function("WarningMessage");
		WriteWarningMessageToFile(param_ObjectName,pram_Message); 
		::SysFreeString(text); 
		::SysFreeString(NodeNames); 	
		return false;  
	}
   }
	return false;
}


bool CWriteTimeouts::FindScreen(CString param_sno)  
{
	MSXML2::IXMLDOMNodePtr ptr;
	
	for(ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
		CString nn = ptr->nodeName; 
		if(!strcmp(ptr->nodeName,param_sno))
		 {
			 pNodeList=GetNode(param_sno);
			 return true;
		 }
	} 
	//m_pNode = ptr;
	return false;
} 

bool CWriteTimeouts::WriteWarningMessageToFile(CString obName,CString message)
{
	CString strLine;
	CreateNode( "ObjectName", obName );
	CreateNode( "Warning",message );
	return true;
   
}

#pragma warning (disable: 4701 4702 4703 4715)
 
//node name can be TimeOut or WarningMessage
bool CWriteTimeouts::Remove_ControlEntry_WarningMessage(CString param_screenNumber,CString node_name ,CString param_controlName)
{
   if(FindScreen(param_screenNumber))
	{  
	MSXML2::IXMLDOMNodePtr pTempChild;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
    bool check = false;
	CString pcRetValue;
	BSTR NodeNames;
	_bstr_t text;
	//TagNames=_com_util::ConvertStringToBSTR(param_psObjectName);
	
	
  	
	int count = pNodeList->length;
	CString node_val;		
		
	for(int j=0;j<pNodeList->length;j++)
	{
	pNodeList->get_item(j, &pTempChild);
	NodeNames=CStrToBstr(node_name);
	pTempChildVal=pTempChild->selectSingleNode(NodeNames);
	if(pTempChildVal)  //if warning message tag exists
	{
		
		for(MSXML2::IXMLDOMNodePtr ptr=pTempChildVal->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
			{
	
				CString nn = ptr->Gettext();
				if(!strcmp(nn,param_controlName))
				{				
					MSXML2::IXMLDOMNodePtr temp_ptr;
					temp_ptr = ptr->nextSibling; 
					pTempChildVal->removeChild(ptr);
					pTempChildVal->removeChild(temp_ptr);  
					::SysFreeString(NodeNames);  
					::SysFreeString(text);  
					return true;
				}
			}
	 }
	}
	::SysFreeString(text);  
	::SysFreeString(NodeNames);  
	return true;   
	}
}


bool CWriteTimeouts::Remove_ControlEntry_TimeOut(CString param_ScreenNumber ,CString node_name ,CString param_controlName)
{
	if(FindScreen(param_ScreenNumber))
	{
    MSXML2::IXMLDOMNodePtr pTempChild;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
    bool check = false;
	CString pcRetValue;
	BSTR NodeNames;
	_bstr_t text;
	//TagNames=_com_util::ConvertStringToBSTR(param_psObjectName);
	
	
  	
	int count = pNodeList->length;
	CString node_val;		
		
	for(int j=0;j<pNodeList->length;j++)
	{
	pNodeList->get_item(j, &pTempChild);
	NodeNames=CStrToBstr(node_name);
	pTempChildVal=pTempChild->selectSingleNode(NodeNames);
	if(pTempChildVal)  //if warning message tag exists
	{
		
		int Vectorsize=m_WarningTimeout.size();
		int listSize=0;
		if(theCTimeOut().WarningTimeoutStatus==true)
		listSize = theCTimeOut().m_TimeoutList.GetItemCount();
		for(MSXML2::IXMLDOMNodePtr ptr=pTempChildVal->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
			{
	
				CString nn = ptr->Gettext();
				if(!strcmp(nn,param_controlName))
				{				
					MSXML2::IXMLDOMNodePtr temp_ptr;
					MSXML2::IXMLDOMNodePtr temp_ptr2;
					MSXML2::IXMLDOMNodePtr temp_ptr3;
					temp_ptr = ptr->nextSibling; 
					temp_ptr2 = temp_ptr->nextSibling;
					temp_ptr3 = temp_ptr2->nextSibling;
					pTempChildVal->removeChild(ptr);
					pTempChildVal->removeChild(temp_ptr);  
					pTempChildVal->removeChild(temp_ptr2); 
					pTempChildVal->removeChild(temp_ptr3); 
					::SysFreeString(NodeNames);  
					::SysFreeString(text); 					
				}
				for(int m=0;m<Vectorsize;m++)
				{
				
					if(m_WarningTimeout[m].ObjID==param_controlName)
					{
						if((m+1)==Vectorsize)
						{
							m_WarningTimeout.pop_back();
						}
						else
						m_WarningTimeout.erase(m_WarningTimeout.begin()+m);						
						
					}
				
					if(theCTimeOut().WarningTimeoutStatus)
					{
						if(theCTimeOut().m_TimeoutList.GetItemText(m,0)==param_controlName)
						{
							theCTimeOut().m_TimeoutList.DeleteItem(m);
						}
					}

					Vectorsize=m_WarningTimeout.size();
				}

			}
	 }
	}
	::SysFreeString(text);  
	::SysFreeString(NodeNames);  
	return true;   
	}
	return false;//EHSMark
}


CString CWriteTimeouts::Get_Machine_IP()
{
	char *ip,ipaddress[200];
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
	return ipaddress; 
}


bool CWriteTimeouts::NodeName_TimeOut(CString param_nodeName,CString param_ObjectName)
{
   	MSXML2::IXMLDOMNodePtr pTempChild;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
    bool check = false;
	CString pcRetValue;
	BSTR NodeNames;
	_bstr_t text;
	  	
	int count = pNodeList->length;
	CString node_val;		
		
	for(int j=0;j<pNodeList->length;j++)
	{
	pNodeList->get_item(j, &pTempChild);
	NodeNames=CStrToBstr(param_nodeName);
	pTempChildVal=pTempChild->selectSingleNode(NodeNames);

	if(pTempChildVal)  //if warning timeout tag exists
	{
		
		for(MSXML2::IXMLDOMNodePtr ptr=pTempChildVal->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
			{
				
				if(!strcmp(ptr->Gettext(),param_ObjectName))
				{				
					ptr->Puttext(param_ObjectName.AllocSysString ());
					check = true;
				    //else if (!strcmp(ptr->nodeName,"Warning"))
					ptr = ptr->nextSibling;			  
					COleDateTime TempDate;
					TempDate = COleDateTime::GetCurrentTime();
					CString TimeRaised1;
					TimeRaised1=TempDate.Format();
					ptr->Puttext(TimeRaised1.AllocSysString() );   
					ptr = ptr->nextSibling;			  
					ptr->Puttext(theApp.GetLocalIP().AllocSysString());   
					ptr = ptr->nextSibling;			  
					ptr->Puttext("Warning TimeOut");
					WarningTimeout WarningTimeoutObj;
					WarningTimeoutObj.ObjID=param_ObjectName;
					WarningTimeoutObj.TimeRaised=TimeRaised1;
					WarningTimeoutObj.MachineIP=theApp.GetLocalIP();
					WarningTimeoutObj.Message="Warning TimeOut";
					m_WarningTimeout.push_back(WarningTimeoutObj);
					
				}
			}
		if(check == false )
		{
			m_pFileNode = pTempChildVal;
			WriteTimeOutDataToFile(param_ObjectName,theApp.GetLocalIP());//,"WarningTimeOut");   
		//	WriteWarningMessageToFile(param_ObjectName,param_message );  	    
		}
		::SysFreeString(text); 
		::SysFreeString(NodeNames); 	
		return true;  
	}
	else   //if warning message tag does not exists
	{
		/*GetRootPointer();*/
		//pNodeList
		m_pNode  = pTempChild; 
		Create_Element_Function("TimeOut");
		WriteTimeOutDataToFile(param_ObjectName,theApp.GetLocalIP());//,"WarningTimeOut");   
		::SysFreeString(text); 
		::SysFreeString(NodeNames); 	
		return false;  
	}
   }
}
	
CString CWriteTimeouts::ReadFileData(CString param_ScreenNumber)
{
	CString t_data = "";
	if(LoadTimeOutXML("xmlfiles\\warningTimeOut.xml"))
	{
	
	MSXML2::IXMLDOMNodePtr ptr;
	for(ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
	    
	   	_bstr_t text;  
		_bstr_t t_nodeName;;  
	   	t_nodeName = ptr->GetbaseName();
		if(!strcmp(t_nodeName,param_ScreenNumber))
		{
			text=ptr->Getxml();
			t_data= text.copy ();
			t_nodeName = ptr->GetbaseName();
			SaveXMLFile("xmlfiles\\warningTimeOut.xml");
			return t_data;
		}
	} 
	SaveXMLFile("xmlfiles\\warningTimeOut.xml");
	}
 	return t_data; 
}
#pragma warning (disable: 4101)

void CWriteTimeouts::FillVector()
{
	CPvcsControlObjectDlg::WarningMessageVector.clear();
	MSXML2::IXMLDOMNodePtr ptr;
	bool isfirstinloop=true;
	CString check_Text;
	WarningMessageStroge WarningMessageStrogeObj;	
	for(ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
	    
	   	_bstr_t text;  
		 text=ptr->nodeName;

		if(FindScreen(LPCSTR(text)))
				{  
						MSXML2::IXMLDOMNodePtr pTempChild;
						MSXML2::IXMLDOMNodePtr pTempChildVal;
						bool check = false;
						CString pcRetValue;
						BSTR NodeNames;
						_bstr_t text;
						//TagNames=_com_util::ConvertStringToBSTR(param_psObjectName);
						
						
					  	
						int count = pNodeList->length;
						CString node_val;		
							
						for(int j=0;j<count;j++)
						{
						pNodeList->get_item(j, &pTempChild);
						//NodeNames=CStrToBstr(node_name);
						if(isfirstinloop)
						{
						pTempChildVal=pTempChild->selectSingleNode("WarningMessage");
						check_Text="WarningMessage";
						isfirstinloop=false;
						}
						else
						{
							pTempChildVal=pTempChild->nextSibling;
							check_Text=LPCSTR(pTempChild->Gettext());
						}
						if((pTempChildVal!=NULL) && (check_Text=="WarningMessage"))  //if warning message tag exists
						{
							
							for(MSXML2::IXMLDOMNodePtr ptr=pTempChildVal->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
								{
						
									CString nn = LPCSTR(ptr->Gettext());
									WarningMessageStrogeObj.ControlObjName=nn;									
									ptr=ptr->nextSibling;
									nn =LPCSTR(ptr->Gettext());
									WarningMessageStrogeObj.ObjWarningMessage=nn;									
									CPvcsControlObjectDlg::WarningMessageVector.push_back(WarningMessageStrogeObj);
								
								}	
								
						}
						}
						isfirstinloop=true;
						::SysFreeString(text);  
						//::SysFreeString(NodeNames);    
						//m_WarningData.push_back(m1_CData);
					}

				}
			}


bool CWriteTimeouts::RemoveUpdateScreenNumberInBuffer(CString param_screenNumber,CString param_writeData)
					{
					  bool t_check = false;
					  if(LoadTimeOutXML("xmlfiles\\warningTimeOut.xml"))
					  {
						MSXML2::IXMLDOMNodePtr ptr;
						MSXML2::IXMLDOMNodePtr temp_ptr;
						 
						CString temp;
						for(ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
						{
							CString nn = ptr->nodeName; 
							if(!strcmp(ptr->nodeName,param_screenNumber))
							{
								//temp_ptr =GetNode(param_screenNumber);
								m_pDocRoot->removeChild(ptr);	
								SaveXMLFile("xmlfiles\\warningTimeOut.xml");
								t_check  = true;
								LoadXMLData(param_writeData); 				 
								return true;
							}
						} 
						if( t_check == false )
						{
						  LoadXMLData(param_writeData);
						}
					  }
					  else
					  {
					    CreateXMLFile(param_writeData);    
					  }
 return false; 
}


// Function to Load XML data that is to be parced data directly from Buffer
bool CWriteTimeouts::LoadXMLData(IN CString param_pcXMLData)
{
	// variable to get the return value of load function
	_bstr_t text;  
	_bstr_t t_nodeName;  
	char temp=34;
	CString t_data ="<?xml version=";
	t_data+=temp;
	t_data+="1.0";
	t_data+=temp;
	t_data+=" encoding=";
	t_data+=temp;
	t_data+="UTF-8";
	t_data+=temp;
	t_data+="?>";	
	t_data+="\n";
	t_data+="<Messages>";
	t_data+="\n";
	variant_t vResult;
	MSXML2::IXMLDOMNodePtr ptr;
    t_nodeName = param_pcXMLData;  
	ptr=m_pDocRoot->firstChild;

	if(ptr != NULL)//if file not empty
	{
		for(;NULL!=ptr;ptr=ptr->nextSibling)
		{
	     	text=ptr->Getxml();
			t_nodeName  =  t_nodeName + text  ;
			
		}
		t_data= t_data + LPCSTR(t_nodeName);
	}
	else if(ptr == NULL )
		{//else file empty
			t_data+=LPCSTR(t_nodeName);
		}
	t_data+="\n";
	t_data+="</Messages>";
	
	// loading the XML file that is to be read
	_bstr_t bstrXMLData(t_data.AllocSysString() ,FALSE);
	vResult=m_plDomDocument->loadXML(bstrXMLData); //creates first chance exception
	
	// check if document is loaded successfully
	if (((bool)vResult) == TRUE) // success!
	{	

		// now that the document is loaded, we need to initialize the root pointer
		m_pDocRoot = m_plDomDocument->documentElement;
		SaveXMLFile ("xmlfiles\\warningTimeOut.xml");
		return true;
	}
	else  //if Failed
	{
		return false;
	}
	return true;
}



void CWriteTimeouts::FillVector_TimeOut()
{
	
	MSXML2::IXMLDOMNodePtr ptr;
	bool isfirstinloop_timeout=true;
	CString check_Text;
	WarningMessageStroge WarningMessageStrogeObj;	
	for(ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
	    
	   	_bstr_t text;  
		 text=ptr->nodeName;

		if(FindScreen(LPCSTR(text)))
				{  
						MSXML2::IXMLDOMNodePtr pTempChild;
						MSXML2::IXMLDOMNodePtr pTempChildVal;
						bool check = false;
						CString pcRetValue;
						BSTR NodeNames;
						_bstr_t text;
						//TagNames=_com_util::ConvertStringToBSTR(param_psObjectName);
						
						
					  	
						int count = pNodeList->length;
						CString node_val;		
							
						for(int j=0;j<count;j++)
						{
						pNodeList->get_item(j, &pTempChild);
						//NodeNames=CStrToBstr(node_name);
						if(isfirstinloop_timeout)
						{
						pTempChildVal=pTempChild->selectSingleNode("TimeOut");
						check_Text="TimeOut";
						isfirstinloop_timeout=false;
						}
						else
						{
							pTempChildVal=pTempChild->nextSibling;
							check_Text=LPCSTR(pTempChild->Gettext());
						}
						if((pTempChildVal!=NULL) && (check_Text=="TimeOut"))  //if warning message tag exists
						{
							
							for(MSXML2::IXMLDOMNodePtr ptr=pTempChildVal->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
								{
									WarningTimeout WarningTimeoutObj1;
									CString nn = LPCSTR(ptr->Gettext());
									WarningTimeoutObj1.ObjID=nn;// first value									
									ptr=ptr->nextSibling;
									nn =LPCSTR(ptr->Gettext()); //second value
									WarningTimeoutObj1.TimeRaised=nn;									
									ptr=ptr->nextSibling;	//third value
									nn =LPCSTR(ptr->Gettext());
									WarningTimeoutObj1.MachineIP=nn;
									ptr=ptr->nextSibling; //fourth value
									nn =LPCSTR(ptr->Gettext());
									WarningTimeoutObj1.Message=nn;
									m_WarningTimeout.push_back(WarningTimeoutObj1);
									
									
								}
								
						}
						}
						isfirstinloop_timeout=true;
						::SysFreeString(text);  
						//::SysFreeString(NodeNames);    
						//m_WarningData.push_back(m1_CData);
					}

				}
		}

bool CWriteTimeouts::UpdateXMLFile( CString param_screenNumber,CString param_NewBufferData)
{
   if(	RemoveUpdateScreenNumberInBuffer(param_screenNumber,param_NewBufferData)   )
   {
     return true;
   }
   else
   {
     return false;
   }
}

CString  CWriteTimeouts::GetDialogTimeOutFile()
{
	CString t_data = "";
	if(LoadTimeOutXML("xmlfiles\\warningTimeOut.xml"))
	{
	t_data = "<Messages>";
	MSXML2::IXMLDOMNodePtr ptr;
	bool isfirstinloop_timeout=true;
	CString check_Text;
	WarningMessageStroge WarningMessageStrogeObj;	
	for(ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
	    
	   	_bstr_t text1;  
		 text1=ptr->nodeName;
		 t_data  =  t_data  + "<" + (LPCSTR)text1 + ">";
       //  t_nodeName = ptr->GetbaseName();
		if(FindScreen(LPCSTR(text1)))
				{  
						MSXML2::IXMLDOMNodePtr pTempChild;
						MSXML2::IXMLDOMNodePtr pTempChildVal;
						bool check = false;
						CString pcRetValue;
						BSTR NodeNames;
						_bstr_t text;
						//TagNames=_com_util::ConvertStringToBSTR(param_psObjectName);
						
						
					  	
						int count = pNodeList->length;
						CString node_val;		
							
						for(int j=0;j<count;j++)
						{
						pNodeList->get_item(j, &pTempChild);
						//NodeNames=CStrToBstr(node_name);
						if(isfirstinloop_timeout)
						{
						pTempChildVal=pTempChild->selectSingleNode("TimeOut");
						check_Text="TimeOut";
						isfirstinloop_timeout=false;
						}
						else
						{
							pTempChildVal=pTempChild->nextSibling;
							check_Text=LPCSTR(pTempChild->Gettext());
						}
						if((pTempChildVal!=NULL) && (check_Text=="TimeOut"))  //if warning timeout tag exists
						{
							
							_bstr_t text;  	
							_bstr_t temp;
                            text =pTempChildVal->Getxml();
						    temp = text  + temp;
							t_data += (LPCSTR)temp;
							//t_data = t_data + "\n"; 
							t_data  =  t_data  + "</" + (LPCSTR)text1 + ">";
						 }
						}
						isfirstinloop_timeout=true;
						::SysFreeString(text);  
						//::SysFreeString(NodeNames);    
						//m_WarningData.push_back(m1_CData);
					}

				}
	/*
	  m_pDocRoot->Getxml();
	t_data = text.copy();  
	SaveXMLFile(GetWarningFilePath());*/
 	t_data  =  t_data  + "</Messages>";
	}
	return t_data; 
}

void CWriteTimeouts::CreateXMLFile(CString param_buffer)
{
	// variable to get the return value of load function
	_bstr_t text;  
	_bstr_t t_nodeName;  
	char temp=34;
	CString t_data ="<?xml version=";
	t_data+=temp;
	t_data+="1.0";
	t_data+=temp;
	t_data+=" encoding=";
	t_data+=temp;
	t_data+="UTF-8";
	t_data+=temp;
	t_data+="?>";	
	t_data+="\n";
	t_data+="<Messages>";
	t_data+="\n";
	variant_t vResult;

	t_data = t_data  + param_buffer;  

	t_data+="\n";
	t_data+="</Messages>";
	
	// loading the XML file that is to be read
	_bstr_t bstrXMLData(t_data.AllocSysString() ,FALSE);
	vResult=m_plDomDocument->loadXML(bstrXMLData); //creates first chance exception
	
	// check if document is loaded successfully
	if (((bool)vResult) == TRUE) // success!
	{	

		// now that the document is loaded, we need to initialize the root pointer
		m_pDocRoot = m_plDomDocument->documentElement;
		SaveXMLFile ("xmlfiles\\warningTimeOut.xml");
	}
}

void CWriteTimeouts::CreateDialogTimeOutFile(CString param_buffer)
{
 // variable to get the return value of load function
	_bstr_t text;  
	_bstr_t t_nodeName;  
	char temp=34;
	CString t_data ="<?xml version=";
	t_data+=temp;
	t_data+="1.0";
	t_data+=temp;
	t_data+=" encoding=";
	t_data+=temp;
	t_data+="UTF-8";
	t_data+=temp;
	t_data+="?>";	
	t_data+="\n";
	//t_data+="<Messages>";
	t_data+="\n";
	variant_t vResult;

	t_data = t_data  + param_buffer;  
   // t_data+="</Messages>";

	// loading the XML file that is to be read
	_bstr_t bstrXMLData(t_data.AllocSysString() ,FALSE);
	vResult=m_plDomDocument->loadXML(bstrXMLData); //creates first chance exception
	
	// check if document is loaded successfully
	if (((bool)vResult) == TRUE) // success!
	{	

		// now that the document is loaded, we need to initialize the root pointer
		m_pDocRoot = m_plDomDocument->documentElement;
		SaveXMLFile ("xmlfiles\\dialogTimeOut.xml");
	}
}


//function to return only timeouts from file
CString  CWriteTimeouts::GetOnlyTimeOutsFromFile(void)
{
	CString t_data = "";
	if(LoadTimeOutXML("xmlfiles\\warningTimeOut.xml"))
	{
	t_data = "<Messages>";
	MSXML2::IXMLDOMNodePtr ptr;
	bool isfirstinloop_timeout=true;
	CString check_Text;
	WarningMessageStroge WarningMessageStrogeObj;	
	for(ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
	    
	   	_bstr_t text1;  
		 text1=ptr->nodeName;
		
       	if(FindScreen(LPCSTR(text1)))
				{  
						MSXML2::IXMLDOMNodePtr pTempChild;
						MSXML2::IXMLDOMNodePtr pTempChildVal;
						bool check = false;
						CString pcRetValue;
						BSTR NodeNames;
						_bstr_t text;
						
					  	
						int count = pNodeList->length;
						CString node_val;		
							
						for(int j=0;j<count;j++)
						{
						pNodeList->get_item(j, &pTempChild);
						if(isfirstinloop_timeout)
						{
						pTempChildVal=pTempChild->selectSingleNode("TimeOut");
						check_Text="TimeOut";
						isfirstinloop_timeout=false;
						}
						else
						{
							pTempChildVal=pTempChild->nextSibling;
							check_Text=LPCSTR(pTempChild->Gettext());
						}
						if((pTempChildVal!=NULL) && (check_Text=="TimeOut"))  //if warning timeout tag exists
						{
							t_data  =  t_data  + "<" + (LPCSTR)text1 + ">";	
							_bstr_t text;  	
							_bstr_t temp;
                            text =pTempChildVal->Getxml();
						    temp = text  + temp;
							t_data += (LPCSTR)temp;
							t_data  =  t_data  + "</" + (LPCSTR)text1 + ">";
						 }
						}
						isfirstinloop_timeout=true;
						::SysFreeString(text);  
					}

				}
	 	t_data  =  t_data  + "</Messages>";
	}
	return t_data; 
}

#pragma warning (disable: 4800)


void CWriteTimeouts::Load_TimeOuts_FromFile_IN_XMLFormat(CString param_format)
{
	
	// loading the XML file that is to be read
	MSXML2::IXMLDOMDocumentPtr mm_plDomDocument;
	MSXML2::IXMLDOMElementPtr mm_pDocRoot;
	MSXML2::IXMLDOMTextPtr mm_pTextPtr; 
	MSXML2::IXMLDOMNodeListPtr pNodeList;
	MSXML2::IXMLDOMNodePtr mm_ptr;
	MSXML2::IXMLDOMNodePtr mmm_ptr;
	
	////////////////////////////////////////////////////////////////////////////////
	
	//HRESULT hrResult;
	//bool bolRet;
	//// Initialize COM
	//hrResult=::CoInitialize(NULL);
	//if(hrResult==S_OK)
	//{
	//	bolRet=true;
	//}
	//else
	//{
	//	bolRet=false; // if COM failed
	//}
	

	HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), 
									NULL, 
									CLSCTX_INPROC_SERVER, 
									__uuidof(MSXML2::IXMLDOMDocument), 
									(void**)&mm_plDomDocument);
	if (FAILED(hr))
 //		return hr;

	 mm_plDomDocument->put_resolveExternals(VARIANT_FALSE);


	///////////////////////////////////////////////////////////////////////////////

	
	_bstr_t node_Name;
	_bstr_t bstrXMLData;
	bstrXMLData=param_format.AllocSysString();
	bool vResult;
	vResult=mm_plDomDocument->loadXML(bstrXMLData); //creates first chance exception
	
	// check if document is loaded successfully
	if (((bool)vResult) == TRUE) // success!
	{	
		// now that the document is loaded, we need to initialize the root pointer
		mm_pDocRoot = mm_plDomDocument->documentElement;
		

		_bstr_t text;  
		for(mm_ptr=mm_pDocRoot->firstChild;NULL!=mm_ptr;mm_ptr=mm_ptr->nextSibling)
		{
			node_Name = mm_ptr->nodeName;
           	for(mmm_ptr=mm_ptr->firstChild;NULL!=mmm_ptr;mmm_ptr=mmm_ptr->nextSibling)
				{
	   				text = mmm_ptr->nodeName;
					CString name = (LPCSTR)text;
					if( name =="TimeOut" )
					{
						text=mmm_ptr->Getxml();
						bool check_file_existence =   Search_Replace((LPCSTR)node_Name,mmm_ptr) ;
						if( check_file_existence == false )
						{
						  LoadXML_ScreenNumberData((LPCSTR)bstrXMLData);
						  break;
						}
						else
						{
						  break;
						}
					}
					else
					{
					   ;
					}
				}
		}
		  
	}

}
#pragma warning (disable: 4189)

bool CWriteTimeouts::Search_Replace(/*MSXML2::IXMLDOMNodePtr*/CString param_nodeName,MSXML2::IXMLDOMElementPtr pt)//_bstr_t param_text)
{
 	if(LoadTimeOutXML("XMLFILES\\warningTimeOut.xml"))
  {
	if(FindScreen(param_nodeName))
	{
    MSXML2::IXMLDOMNodePtr pTempChild;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
    bool check = false;
	CString pcRetValue;
	BSTR NodeNames;
	_bstr_t text;
	  	
	int count = pNodeList->length;
	CString node_val;		
		
	for(int j=0;j<pNodeList->length;j++)
	{
	pNodeList->get_item(j, &pTempChild);
	NodeNames=CStrToBstr(param_nodeName);
	pTempChildVal=pTempChild->selectSingleNode("TimeOut");
	if(pTempChildVal)  //if timeout tag exists
	{
		pTempChild->removeChild(pTempChildVal);
		SaveXMLFile("XMLFILES\\warningTimeOut.xml");		 
		pTempChild->appendChild(pt);
		//LoadXMLData((LPCSTR)param_text);
		//for(MSXML2::IXMLDOMNodePtr ptr=pTempChildVal->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
			/*for(MSXML2::IXMLDOMNodePtr ptr=pTempChild->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
			{
				MSXML2::IXMLDOMNodePtr temp_ptr;
				MSXML2::IXMLDOMNodePtr temp_ptr2;
				MSXML2::IXMLDOMNodePtr temp_ptr3;
				temp_ptr = ptr->nextSibling; 
				temp_ptr2 = temp_ptr->nextSibling;
				temp_ptr3 = temp_ptr2->nextSibling;
				pTempChild->removeChild(ptr);
				pTempChild->removeChild(temp_ptr);  
				pTempChild->removeChild(temp_ptr2); 
				pTempChild->removeChild(temp_ptr3); 
				::SysFreeString(NodeNames);  
				::SysFreeString(text); 					
			}*/
	   }
	}
	::SysFreeString(text);  
	::SysFreeString(NodeNames);  
	}
   SaveXMLFile("XMLFILES\\warningTimeOut.xml");
   return true;
  }
	else   // code to create XML file if now existing
	{
		//InitTimeoutHeader("xmlfiles\\warningTimeOut.xml","Messages");
		//PreserveRootPointer(a);
		return  false;

	   
	}
 
//  LoadXMLData((LPCSTR)text);
}

bool CWriteTimeouts::LoadXML_ScreenNumberData(CString param_screenNumberData)
{
		// variable to get the return value of load function
	_bstr_t text;  
	_bstr_t t_nodeName;  
	char temp=34;
	CString t_data ="<?xml version=";
	t_data+=temp;
	t_data+="1.0";
	t_data+=temp;
	t_data+=" encoding=";
	t_data+=temp;
	t_data+="UTF-8";
	t_data+=temp;
	t_data+="?>";	
	t_data+="\n";
	variant_t vResult;
	MSXML2::IXMLDOMNodePtr ptr;
    
	t_data= t_data + LPCSTR(param_screenNumberData);

	
	
	// loading the XML file that is to be read
	_bstr_t bstrXMLData(t_data.AllocSysString() ,FALSE);
	vResult=m_plDomDocument->loadXML(bstrXMLData); //creates first chance exception
	
	// check if document is loaded successfully
	if (((bool)vResult) == TRUE) // success!
	{	

		// now that the document is loaded, we need to initialize the root pointer
		m_pDocRoot = m_plDomDocument->documentElement;
		SaveXMLFile ("xmlfiles\\warningTimeOut.xml");
		return true;
	}
	else  //if Failed
	{
		return false;
	}
	return true;

}