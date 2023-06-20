#pragma once
#include "writexml.h"

class CWarningMessage :public CWriteXML 
{
public:
	CWarningMessage(void);
	~CWarningMessage(void);
	CString m_pcFilename;
	bool InitAlarmHeader(CString param_pcFileName);
	bool LoadXMLFile(CString param_pcXMLFileName);
	void edit_xml(CString node_val,CString response);
	void Remove_child_Node(CString); 
	bool GetNodeText(CString NodeName);
	//bool CreateNode(CString param_pcNodeName,CString param_pcNodeValue);
	void FillVector();
	HRESULT InitializeXMLParcer(void);
	bool createElement(BSTR param_pcElementName);
	protected:
		/* MSXML2::IXMLDOMDocumentPtr m_plDomDocument;
		 MSXML2::IXMLDOMElementPtr m_pDocRoot;
	   	 MSXML2::IXMLDOMTextPtr m_pTextPtr; 
		 MSXML2::IXMLDOMNodePtr m_pNode;*/
		 bstr_t bstr_FileName;
};
