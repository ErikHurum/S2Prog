#pragma once
#include "initxml.h"
#include "convertdata.h"
/////////////////////////////////////////////////////////////////////////////
// XML writer class
// using MSXML 4.0 to write XML data to class
/////////////////////////////////////////////////////////////////////////////
class CWriteXML :
	public CInitXML, public CConvertData
{
public:
	CWriteXML(void);	
	virtual ~CWriteXML(void);

	MSXML2::IXMLDOMNodePtr m_pFileNode;
	MSXML2::IXMLDOMElementPtr  t_Preserve;
	
	void Ini();
	// To set the XML processing instruction in beghining of all XML files
	bool SetXMLHeader(void);
	// Function to write the root name
	bool WriteRootNode(CString param_pcRootNodeName);
	// To get the current system time 
	CString GetTime(void);
	// To create a Element for all pa ckets
	bool CreateElement(CString param_pcElementName);
	// to create a attribute
	void CreateAttribute(CString param_pcAttributeName, CString param_pcAttributeValue);
	// To Create Nodes Under Element Under Root
	bool CreateNode(CString param_pcNodeName,CString param_pcNodeValue);
	//  To set the values in the nodes created
	bool SetNodeValue(CString param_pcNodeValue, MSXML2::IXMLDOMElementPtr param_pTempNode);
	bool SaveXMLFile(CString param_pcXMLFileName);
};
