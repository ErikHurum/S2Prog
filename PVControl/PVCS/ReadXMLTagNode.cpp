#include "StdAfx.h"
#include ".\readxmltagnode.h"

CReadXMLTagNode::CReadXMLTagNode(void)
{
}

CReadXMLTagNode::~CReadXMLTagNode(void)
{
	
}

// To get all data og tags in node of teh document node name given as argument
MSXML2::IXMLDOMNodeListPtr CReadXMLTagNode::GetNode(CString param_pcNodeName)
{
	MSXML2::IXMLDOMNodeListPtr pNodeList;
	BSTR NodeNames;
	NodeNames=CStrToBstr(param_pcNodeName);
	pNodeList=m_plDomDocument->documentElement->selectNodes(NodeNames);
	::SysFreeString(NodeNames);
	return pNodeList;
}
