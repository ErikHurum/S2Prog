#pragma once
#include "loadxml.h"
#include "convertdata.h"
////////////////////////////////////////////////////////////////////////
// Base Class used to read tag and nodes information for parsing XML files
//
////////////////////////////////////////////////////////////////////////
class CReadXMLTagNode :
	public CLoadXML,public CConvertData
{
public:
	CReadXMLTagNode(void);
	virtual ~CReadXMLTagNode(void);
	// To get all data og tags in node of teh document node name given as argument
	MSXML2::IXMLDOMNodeListPtr GetNode(CString param_pcNodeName);
};
