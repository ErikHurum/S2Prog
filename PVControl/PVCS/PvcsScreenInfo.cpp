#include "StdAfx.h"
#include ".\pvcsscreeninfo.h"

vector<CPvcsScreenInfo*> CPvcsScreenInfo::m_vecScreenInfo; 

CPvcsScreenInfo::CPvcsScreenInfo(void)
{
	m_ptrScreenFrame = NULL;
	m_bCommandStatus = false;
	m_strScreenTitle = "";
	m_strCommandingMachineIP = "";
	m_ptrScreenThread = NULL;
	m_bScreenClose = false;
}

CPvcsScreenInfo::~CPvcsScreenInfo(void)
{
}
