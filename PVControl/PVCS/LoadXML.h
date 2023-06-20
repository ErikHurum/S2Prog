
#define IN
#define OUT

#pragma once
#include <string>
//using namespace std;
// XML DOM dll MSXML 4
#import <msxml6.dll> 


//////////////////////////////////////////////////////////////////////
// Class To load the XML file and Data that is to be parsed 
// All classes use this class as base class for parsing XML data or 
// XML file 
//////////////////////////////////////////////////////////////////////
class CLoadXML
{
public:
	CLoadXML(void);
	virtual ~CLoadXML(void);
	
protected:
	// Pointer to XML DOM Document
	MSXML2::IXMLDOMDocumentPtr m_plDomDocument;
	// Pointer to XML Document root
	MSXML2::IXMLDOMElementPtr m_pDocRoot;
	// XML Node Pointer
	MSXML2::IXMLDOMNodePtr m_pNode;		
	// To get the status of XML file its loaded or not
	bool XMLFileLoadStatus;
	// To Chk for Status of XML data i.e. XML data is loaded or not
	bool XMLDataLoadStatus;

	// Function to Initialize DOM and XML libraries to load XML file and Data
	HRESULT Initialize(void) const;

private:
	// Funtion to Initialize COM
	bool InitCOM(void);

public:
	// Function to load XML file
	bool LoadXMLFile(IN CString param_pcXMLFileName);
	// Function to Load XML data that is to be parced data directly from Buffer
	bool LoadXMLData(IN CString param_pcXMLData);
	// Function to return the total number of Nodes in the XML file 
	long CountNodes(void);
	// To Remove all the initialized variables
	bool UnloadXMLFile(void);
	// TO Deinitialize the COM components
	void UnInitCOM(void);
	
};
