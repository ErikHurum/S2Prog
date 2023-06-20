// PvcsToolBarEmgButton.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsToolBarEmgButton.h"


// CPvcsToolBarEmgButton

IMPLEMENT_DYNAMIC(CPvcsToolBarEmgButton, CButton)
CPvcsToolBarEmgButton::CPvcsToolBarEmgButton()
{
	m_ToolTip = new CToolTipCtrl();
}

CPvcsToolBarEmgButton::~CPvcsToolBarEmgButton()
{
	delete m_ToolTip;
}


BEGIN_MESSAGE_MAP(CPvcsToolBarEmgButton, CButton)
END_MESSAGE_MAP()

void CPvcsToolBarEmgButton::AddToolTip(CString pTooltipText)
{
	if(!pTooltipText.IsEmpty())
	{
		m_ToolTip->Create( this, TTS_ALWAYSTIP );
		m_ToolTip->Activate( FALSE );
		m_ToolTip->AddTool(this, "Button");
	}
	return;
}

void CPvcsToolBarEmgButton::UpdateToolTip(CString pTooltipText)
{
	if(!pTooltipText.IsEmpty())
	{
		m_ToolTip->UpdateTipText(pTooltipText,this);
		m_ToolTip->Activate(true);
	}
	else if(::IsWindow(m_ToolTip->m_hWnd))
		m_ToolTip->Activate(false);

}

BOOL CPvcsToolBarEmgButton::PreTranslateMessage(MSG* pMsg)
{
	// Send message to the tool tip
	m_ToolTip->RelayEvent( pMsg );
	
	return CButton::PreTranslateMessage(pMsg);
}

// CPvcsToolBarEmgButton message handlers

