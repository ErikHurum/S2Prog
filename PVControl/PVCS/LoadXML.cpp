#include "StdAfx.h"
#include ".\loadxml.h"

CLoadXML::CLoadXML(void)
{
	// Initialize COM and XML objects
	InitCOM();
	Initialize();
	XMLDataLoadStatus=false;

}

CLoadXML::~CLoadXML(void)
{
UnloadXMLFile();
UnInitCOM();
}

// Function to Initialize DOM and XML libraries to load XML file and Data
HRESULT CLoadXML::Initialize(void) const
{
	using namespace MSXML2;

	HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), 
									NULL, 
									CLSCTX_INPROC_SERVER, 
									__uuidof(MSXML2::IXMLDOMDocument), 
									(void**)&m_plDomDocument);
	if (FAILED(hr))
		return hr;

	
	return m_plDomDocument->put_resolveExternals(VARIANT_FALSE);
}

// Funtion to Initialize COM
bool CLoadXML::InitCOM(void)
{
	HRESULT hrResult;
	bool bolRet;
	// Initialize COM
	hrResult=::CoInitialize(NULL);
	if(hrResult==S_OK)
	{
		bolRet=true;
	}
	else
	{
		bolRet=false;
	}

	return bolRet;
}

// Function to load XML file
bool CLoadXML::LoadXMLFile(IN CString param_pcXMLFileName)
{
	
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
	//	AfxMessageBox("Document loaded successfully!");
		
		XMLFileLoadStatus=true;
		::SysFreeString(bstrFileName);
		return true;
	}
	else  //if Failed
	{
		//AfxMessageBox("Document FAILED to load!");
		XMLFileLoadStatus=false;
		::SysFreeString(bstrFileName);
		return false;
	}

}

// Function to Load XML data that is to be parced data directly from Buffer
bool CLoadXML::LoadXMLData(IN CString param_pcXMLData)
{
	// variable to get the return value of load function
	variant_t vResult;
	
	//binary string to store the XML Data that DOM can handle
	//& Convert XML Data string to format COM can Handle
	//BSTR m_bstrXMLData;
	//m_bstrXMLData=param_pcXMLData.AllocSysString();
	_bstr_t bstrXMLData(param_pcXMLData.AllocSysString(),FALSE);
	// Convert XML Data string to format COM can Handle
	//m_bstrXMLData=param_pcXMLData.AllocSysString();

	// loading the XML file that is to be read
	vResult=m_plDomDocument->loadXML(bstrXMLData); //creates first chance exception
	
	// check if document is loaded successfully
	if (((bool)vResult) == TRUE) // success!
	{	

		// now that the document is loaded, we need to initialize the root pointer
		m_pDocRoot = m_plDomDocument->documentElement;
		//AfxMessageBox("XML Data Loaded successfully!");	
		XMLDataLoadStatus=true;
		//::SysFreeString(m_bstrXMLData);
		return true;
	}
	
	else  //if Failed
	{
		XMLDataLoadStatus=false;	
		return false;
	}
}

// Function to return the total number of Nodes in the XML file 
long CLoadXML::CountNodes(void)
{
	

	MSXML2::IXMLDOMNodeListPtr pNodeList;
	long m_uiNodeCount=0;

	pNodeList=m_plDomDocument->documentElement->selectNodes("Packet");
	if(pNodeList==NULL)
	{
		m_uiNodeCount=0;
	}
	else
	{
	m_uiNodeCount=pNodeList->length;
	}
	
	return m_uiNodeCount;
	
}

// To Remove all the initialized variables
bool CLoadXML::UnloadXMLFile(void)
{
	//m_plDomDocument=NULL; 
	m_pDocRoot=NULL; 
	m_pNode=NULL;
	return true;
 
}

// TO Deinitialize the COM components
void CLoadXML::UnInitCOM(void)
{
	m_plDomDocument=NULL;
	::CoUninitialize();
}


