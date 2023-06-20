#define IN
#define OUT

#pragma once
#include <string>
using namespace std;
// XML DOM dll MSXML 4
#import <msxml6.dll> 
using namespace MSXML2;
/////////////////////////////////////////////////////////////////////
// Class to Initialize XML pointers to be used for writing XMLfiles//
/////////////////////////////////////////////////////////////////////
class CInitXML
{
public:
	// Pointer to XML DOM Document
	MSXML2::IXMLDOMDocumentPtr m_plDomDocument;
	// Pointer to XML Document root
	MSXML2::IXMLDOMElementPtr m_pDocRoot;
	// XML Node Pointer
	MSXML2::IXMLDOMNodePtr m_pNode;	

	CInitXML(void);
	virtual ~CInitXML(void);
	// Function to initialize com object before starting
	bool InitCOM(void);
	// To initialze DOM MSXML library
	HRESULT Initialize(void);
};

