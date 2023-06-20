#include "StdAfx.h"
#include ".\initxml.h"

CInitXML::CInitXML(void)
{
}

CInitXML::~CInitXML(void)
{
	
}

// Function to initialize COM object before start using MSXML
bool CInitXML::InitCOM(void)
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
		bolRet=false; // if COM failed
	}

	return bolRet;
}

// To initialze DOM MSXML library
HRESULT CInitXML::Initialize(void)
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
