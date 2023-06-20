#include "StdAfx.h"
#include ".\calibrationdata.h"


CCalibrationData::CCalibrationData(void)
{
}

CCalibrationData::~CCalibrationData(void)
{
}

// TO initialize dom testydhfbdshfhsdfgdhfg
HRESULT CCalibrationData::InitializeXMLParcer(void)
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

// to load xmlfile
bool CCalibrationData::LoadXMLFile(CString param_pcXMLFileName)
{
	// variable to get the return value of load function
	variant_t vResult;
	m_pNode; 
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
		m_pNode = m_pDocRoot;
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

bool CCalibrationData::SaveCalibrationFile(CString param_pcFileName)
{
	BSTR FileName=CStrToBstr(param_pcFileName);
	HRESULT result = m_plDomDocument->save(_T(FileName));
	if(result == S_OK)
	{
		::SysFreeString(FileName);
		return true;
	}
	else
	{
		return false;
	}
}

// to create node
bool CCalibrationData::CreateNode(CString param_pcNodeName, CString param_pcNodeValue)
{
	MSXML2::IXMLDOMDocumentFragmentPtr m_pFragment = NULL;
	MSXML2::IXMLDOMElementPtr m_pTempNode = NULL;
	BSTR NodeNames=CStrToBstr(param_pcNodeName);
	m_pFragment = m_plDomDocument->createDocumentFragment();
	m_pTempNode = m_plDomDocument->createElement(_T(NodeNames));
	BSTR NodeValue=CStrToBstr(param_pcNodeValue);
	m_pTempNode->nodeTypedValue = _T(NodeValue);
	m_pFragment->appendChild(m_pTempNode);
	m_pFileNode->appendChild(m_pFragment);
	::SysFreeString(NodeNames);

	
	
	

	return true;
}

// add root node
bool CCalibrationData::WriteRootNode(CString param_pcRootNodeName)
{
	//MSXML2::IXMLDOMNodePtr m_pNode;	
	CString m_pcTime;
//	m_pcTime=GetTime();
	m_pFileNode=NULL;
	BSTR RootNames;
	//BSTR m_strTime=m_pcTime.AllocSysString();
	RootNames=CStrToBstr(param_pcRootNodeName);
	_variant_t m_varNodeType((short)MSXML2::NODE_TEXT);
	m_pNode= m_plDomDocument->createElement(_T(RootNames));
	m_pFileNode = m_plDomDocument->appendChild(m_pNode);
	//m_pFileNode = m_plDomDocument->appendChild(m_pNode);
	//::SysFreeString(m_strTime);
	::SysFreeString(RootNames);
	return true;
}

bool CCalibrationData::CreateElement(CString param_pcElementName)
{
	m_pFileNode=NULL;
	BSTR ElementName;
	//m_pNode= m_plDomDocument->getElementsByTagName("Calibration");
	ElementName=CStrToBstr(param_pcElementName);
	//m_pNode= m_plDomDocument->createElement(_T("xcxc"));
//*	m_pNode= m_plDomDocument->createElement(_T(ElementName));
//	m_pFileNode = m_plDomDocument->appendChild(m_pNode);
	m_pFileNode = m_pNode->appendChild(m_plDomDocument->createElement(ElementName));
	::SysFreeString(ElementName);
	return true;
}

// to write data to calibration file

bool CCalibrationData::WriteDataToFile(CString param_psObjName, CString param_psStartValue, CString param_psStopValue)
{
	m_FileHandle.Open("XMLFILES\\calibrate.xml",CFile::modeCreate|CFile::modeReadWrite);
	m_FileHandle.Write("<Data>",7);
	m_FileHandle.Write("<ObjectName>",12);
	m_FileHandle.Close();
	return false;
}

bool CCalibrationData::Remove_Node(CString  param_psObjName, CString param_ChannelNumber)
{
   MSXML2::IXMLDOMNodePtr ptr;
   MSXML2::IXMLDOMNodePtr pTempChild;
   MSXML2::IXMLDOMNodePtr pTempChildVal;
   BSTR temp_NodeText;
   CString t_text ;
   CString temp_buffer,temp_buffer_2;

   int i = -1,j = -1;
   for(ptr=m_pDocRoot->firstChild;NULL!=ptr;ptr=ptr->nextSibling)
	{
		//<Channelnumber>17</Channelnumber
		
	     temp_NodeText  =ptr->Gettext();
		 temp_buffer   = temp_NodeText; 
		 
		 i = -1;
		 j = -1;
		 
		 i = temp_buffer.Find(param_psObjName,0);
		
         
		 if( i >= 0  )
		 {
		   for(pTempChild = ptr->firstChild;NULL!=pTempChild;pTempChild=pTempChild->nextSibling)
			{
				temp_NodeText  = pTempChild->nodeName;
				temp_buffer   = temp_NodeText; 
				
				if(!strcmp( temp_buffer ,"Channelnumber"))
				{
				  t_text  = LPCSTR(pTempChild->Gettext()); 
				  if( param_ChannelNumber ==  t_text )
				  {
				     j = 0;
				  }
				}
			}
//			j = temp_buffer.Find(param_ChannelNumber,0);
			if( j == 0)
			 {
				m_pDocRoot->removeChild(ptr);	
				return true;			
			 }
			
		 }
		::SysFreeString(temp_NodeText);
	} 
	return false;
}


bool CCalibrationData::SetXMLHeader(void)
{
	MSXML2::IXMLDOMProcessingInstructionPtr m_pProcessInstruction = NULL;
	_variant_t vNullVal;
	
	m_pProcessInstruction =m_plDomDocument->createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
	
		vNullVal.vt = VT_NULL;
		m_plDomDocument->insertBefore(m_pProcessInstruction, vNullVal);

	return true;
}
