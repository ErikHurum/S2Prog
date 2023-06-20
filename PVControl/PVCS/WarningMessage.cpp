/////////////////////////////////////////////////////////
///  Class Added By JSD for Warning Message XML//////////
/////////////////////////////////////////////////////////

#include "StdAfx.h"
#include ".\warningmessage.h"
#include "writexml.h"
#include "PvcsObjectControlDlg.h"
CWarningMessage::CWarningMessage(void)
{
}

CWarningMessage::~CWarningMessage(void)
{
	// Deinitialize COM
	//::CoUninitialize();
}
bool CWarningMessage::InitAlarmHeader(CString param_pcFileName)
{
	InitCOM();
	Initialize();
	//SetXMLHeader();
	//WriteRootNode("WarningMessage");
	m_pcFilename=param_pcFileName;

	return true;
}

bool CWarningMessage::LoadXMLFile(CString param_pcXMLFileName)
{
	
		//InitCOM();
	 	//Initialize();
	m_plDomDocument;
	// Pointer to XML Document root
	m_pDocRoot;
	// XML Node Pointer
	// variable to get the return value of load function
	variant_t vResult;

	//binary string to store the file name of XML that DOM can handle
	// & Convert XML File name string to format COM can Handle
	BSTR bstrFileName;
	bstrFileName=param_pcXMLFileName.AllocSysString();

	// loading the XML file that is to be read
	vResult=m_plDomDocument->load(bstrFileName);

	// check if document is loaded successfully
	if (((bool)vResult) == TRUE) // success!
	{	
		// now that the document is loaded, we need to initialize the root pointer
		m_pDocRoot = m_plDomDocument->documentElement;
		
	//	XMLFileLoadStatus=true;
		::SysFreeString(bstrFileName);
		return true;
	}
	else  //if Failed
	{
		//AfxMessageBox("Document FAILED to load!");
//		XMLFileLoadStatus=false;
		::SysFreeString(bstrFileName);
		return false;
	}
}
void CWarningMessage::edit_xml(CString node_val,CString response)
{
	_bstr_t text;
	BSTR FileName;
	HRESULT hr;
	for(MSXML2::IXMLDOMNodePtr ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
	  	if(!strcmp(ptr->nodeName,node_val))
		{
		   //text=ptr->Gettext();
		   ptr->Puttext(response.AllocSysString());
		}
	}
    try
	{
		CString fn="XMLFILES\\WarningMessage.xml"; 
		FileName=fn.AllocSysString();//  XML_MAIN_CONFIGURATION_FILE;
		hr=m_plDomDocument->save(_T(FileName));
	    if(hr==S_OK)
		{
	
		}
		else
		{
		   ; 
		}
		::SysFreeString(FileName); 
		::SysFreeString(text); 
	}
	catch(exception  e)
	{
		//TRACE("*****warningmessage-createnode******");
		::SysFreeString(text);
		::SysFreeString(FileName); 
		e.what(); 
	}
}  

bool CWarningMessage::GetNodeText(CString NodeName)
{
  static CString pcRetValue="NULL";
  int status;
  status=0;
  for(MSXML2::IXMLDOMNodePtr ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
		//Line added by mohit to test (find the value)	
		 if(!strcmp(ptr->nodeName,NodeName))
		 {
			 status=1;
			 
		 }		
			
	}
	
	if (status==1)
		return(true);
	else
	    m_pFileNode = m_pDocRoot;
		return(false);
}


void CWarningMessage::Remove_child_Node(CString nodeName)
{
  	_bstr_t text;
	BSTR FileName;
	HRESULT hr;
	for(MSXML2::IXMLDOMNodePtr ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
	     if(!strcmp(ptr->nodeName,nodeName))
		{
		   //text=ptr->Gettext();
		    m_pDocRoot->removeChild(ptr);
		}
	}
    try
	{
		CString fn="XMLFILES\\WarningMessage.xml"; 
		FileName=fn.AllocSysString();//  XML_MAIN_CONFIGURATION_FILE;
		hr=m_plDomDocument->save(_T(FileName));
	    if(hr==S_OK)
		{
		//   AfxMessageBox("saved");
		}
		else
		{
		   ;//AfxMessageBox("Error In Saving File"); 
		}
		::SysFreeString(FileName); 
		::SysFreeString(text); 
	}
	catch(exception  e)
	{
		//TRACE("*****warningmessage-createnode******");
		::SysFreeString(text);
		::SysFreeString(FileName); 
		e.what(); 
	}
}

void  CWarningMessage::FillVector()
{
	WarningMessageStroge objtemp;
	static CString pcRetValue="NULL";
	CString Node_Text;
	CString NodeValue_Text;
	for(MSXML2::IXMLDOMNodePtr ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
		Node_Text="";
		NodeValue_Text="";
		Node_Text=LPCSTR(LPSTR(ptr->nodeName));		
		pcRetValue.Format(_T("%s"), (LPCTSTR)ptr->text);
		NodeValue_Text=	pcRetValue;
		objtemp.ControlObjName=Node_Text;
		objtemp.ObjWarningMessage =NodeValue_Text;
		CPvcsControlObjectDlg::WarningMessageVector.push_back(objtemp);
	}
	
}

HRESULT CWarningMessage::InitializeXMLParcer(void)
{
	HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), 
									NULL, 
									CLSCTX_INPROC_SERVER, 
									__uuidof(MSXML2::IXMLDOMDocument), 
									(void**)&m_plDomDocument);
	if (FAILED(hr))
		return hr;

	return m_plDomDocument->put_resolveExternals(VARIANT_FALSE);
}

