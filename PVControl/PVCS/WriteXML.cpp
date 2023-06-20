#include "StdAfx.h"
#include ".\writexml.h"

CWriteXML::CWriteXML(void)
{
	CInitXML::InitCOM();
	CInitXML::Initialize();
}

CWriteXML::~CWriteXML(void)
{
}

// To set the XML processing instruction in beghining of all XML files
void CWriteXML::Ini()
{
	CInitXML::InitCOM();
	CInitXML::Initialize();
}

bool CWriteXML::SetXMLHeader(void)
{
	MSXML2::IXMLDOMProcessingInstructionPtr m_pProcessInstruction = NULL;
	_variant_t vNullVal;

	m_pProcessInstruction =m_plDomDocument->createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");

		vNullVal.vt = VT_NULL;
		m_plDomDocument->insertBefore(m_pProcessInstruction, vNullVal);

	return true;
}

// Function to write the root name
bool CWriteXML::WriteRootNode(CString param_pcRootNodeName)
{
	//
	CString m_pcTime;
	m_pcTime=GetTime();
	m_pFileNode=NULL;
	BSTR RootNames;
	BSTR m_strTime=m_pcTime.AllocSysString();
	RootNames=CStrToBstr(param_pcRootNodeName);
	_variant_t m_varNodeType((short)MSXML2::NODE_TEXT);
	m_pNode= m_plDomDocument->createElement(_T(RootNames));
	m_pFileNode = m_plDomDocument->appendChild(m_pNode);
	t_Preserve =  m_plDomDocument->documentElement;
	::SysFreeString(m_strTime);
	::SysFreeString(RootNames);
	return true;

}

// To get the current system time
CString CWriteXML::GetTime(void)
{
	CTime m_ctTime;
	m_ctTime=CTime::GetCurrentTime();
	CString m_pcTime = m_ctTime.Format("%A, %B %d, %Y,%H:%M:%S");
	return m_pcTime;
}

// To create a Element for all packets
bool CWriteXML::CreateElement(CString param_pcElementName)
{
	m_pFileNode=NULL;
	BSTR ElementName;
	ElementName=CStrToBstr(param_pcElementName);
	m_pFileNode = m_pNode->appendChild(m_plDomDocument->createElement(ElementName));
	::SysFreeString(ElementName);
	return true;
}

// to create a attribute
void CWriteXML::CreateAttribute(CString param_pcAttributeName, CString param_pcAttributeValue)
{
	MSXML2::IXMLDOMAttributePtr m_pRecIdAttr = NULL;
	BSTR AttName=CStrToBstr(param_pcAttributeName);
	BSTR AttValue=CStrToBstr(param_pcAttributeValue);
	m_pRecIdAttr = m_plDomDocument->createAttribute(_T(AttName));
	m_pRecIdAttr->nodeTypedValue = _T(AttValue);
	m_pFileNode->attributes->setNamedItem(m_pRecIdAttr);
	::SysFreeString(AttName);
	::SysFreeString(AttValue);
}

// To Create Nodes Under Element Under Root
bool CWriteXML::CreateNode(CString param_pcNodeName,CString param_pcNodeValue)
{
	MSXML2::IXMLDOMDocumentFragmentPtr m_pFragment = NULL;
	MSXML2::IXMLDOMElementPtr m_pTempNode = NULL;
	BSTR NodeNames=CStrToBstr(param_pcNodeName);
	BSTR EoLn=CStrToBstr("\r\n");
	m_pFragment = m_plDomDocument->createDocumentFragment();
	m_pTempNode = m_plDomDocument->createElement(_T(NodeNames));
	SetNodeValue(param_pcNodeValue,m_pTempNode);
	m_pFragment->appendChild(m_pTempNode );
	m_pFileNode->appendChild(m_pFragment);
	m_pFileNode->put_text(EoLn);
	::SysFreeString(NodeNames);
	::SysFreeString(EoLn);
	return true;
}

//  To set the values in the nodes created
bool CWriteXML::SetNodeValue(CString param_pcNodeValue, MSXML2::IXMLDOMElementPtr param_pTempNode)
{
	BSTR NodeValue=CStrToBstr(param_pcNodeValue);
	param_pTempNode->nodeTypedValue = _T(NodeValue);
	::SysFreeString(NodeValue);
	return true;
}

// To save or add data to XML file
bool CWriteXML::SaveXMLFile(CString param_pcXMLFileName)
{

	BSTR FileName=CStrToBstr(param_pcXMLFileName);
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
