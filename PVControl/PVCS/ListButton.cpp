// ListButton.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "ListButton.h"
#include "PvcsControlObjectInfo.h"
#include "PvcsWagoControl.h"
#include "DxfLayout.h"

// CListButton

IMPLEMENT_DYNAMIC(CListButton, CButton)
CListButton::CListButton(int p_Row,int p_Col)
{
	m_Row = p_Row;
	m_Col = p_Col;
	m_bStartButtonClicked = false;
}

CListButton::~CListButton()
{
}


BEGIN_MESSAGE_MAP(CListButton, CButton)
	ON_WM_LBUTTONUP() 
END_MESSAGE_MAP()


void CListButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	UINT CurrentValue = 0;
	AnalogSignal tempAnalogSignal;
	UINT uiControlIndex, uiControlSubIndex;

	tempAnalogSignal.Port.WagoChannel = atoi(CCalibrateChannels::m_CalibrationData[m_Row].Channel);
	tempAnalogSignal.Port.WagoUnit = atoi(CCalibrateChannels::m_CalibrationData[m_Row].WagoUnitNumber);
	uiControlIndex = CCalibrateChannels::m_CalibrationData[m_Row].uiControlIndex;
	uiControlSubIndex = CCalibrateChannels::m_CalibrationData[m_Row].uiControlSubIndex;

	CPvcsControlObjectInfo ObjControlObject;
	CDxfLayout::GetControlObject(uiControlIndex,uiControlSubIndex,ObjControlObject);

	bool bIsThrottleValve = false;

	if(ObjControlObject.GetClassName() == "CPvcsControlObjectThrottleValve")
		bIsThrottleValve = true;
	else
		bIsThrottleValve = false;


	if(m_Col == 6)//Click on start button
	{
		CCalibrateChannels::m_CalibrationData[m_Row].StartButtonClicked = true;

		if(CPvcsWagoControl::theWagoUnit().GetValue(tempAnalogSignal,CurrentValue,CCalibrateChannels::m_CalibrationData[m_Row].WagoUnitType ))
		{
			//If throttle Valve
			if(bIsThrottleValve)
			{
				if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted)
				{
					CString strWagoUnit = CCalibrateChannels::m_CalibrationData[m_Row].WagoUnitType;
					UINT uiWagoUnit = atoi(strWagoUnit);
					UINT uiMaxRange = 4096;
					if(uiWagoUnit == 461)
						uiMaxRange = 28026;
					else if (uiWagoUnit == 454)
						uiMaxRange = 4095;

					int uiValue = (uiMaxRange * ObjControlObject.GetObjectMaxStop())/100;
					int uiCalValue = uiValue - (int)CurrentValue;
					if(uiCalValue <0)
						uiCalValue = -(uiCalValue);
					CurrentValue = uiCalValue;
				}
			}
				
			CString strCurrentValue = "";
			strCurrentValue.Format("%d",CurrentValue);
			theApp.GetCalibrateChannels()->SetItemText(m_Row,m_Col,strCurrentValue);			
		}
		else
			AfxMessageBox("Error in reading data from Wago",MB_SETFOREGROUND|MB_ICONERROR,0); 

	}
	else if(m_Col == 7)//click on stop button
	{
		if(CCalibrateChannels::m_CalibrationData[m_Row].StartButtonClicked)//do operation only when once start button clicked
		{
			if(CPvcsWagoControl::theWagoUnit().GetValue(tempAnalogSignal,CurrentValue,CCalibrateChannels::m_CalibrationData[m_Row].WagoUnitType ))
			{
		
				//If throttle Valve
				if(bIsThrottleValve)
				{				
					if(ObjControlObject.GetInputAnalogSignalList().at(0).Value.IsInverted)
					{
						CString strWagoUnit = CCalibrateChannels::m_CalibrationData[m_Row].WagoUnitType;
						UINT uiWagoUnit = atoi(strWagoUnit);
						UINT uiMaxRange = 4096;
						if(uiWagoUnit == 461)
							uiMaxRange = 28026;
						else if (uiWagoUnit == 454)
							uiMaxRange = 4095;

						UINT uiValue = (uiMaxRange * ObjControlObject.GetObjectMaxStop())/100;
						int uiCalValue = uiValue - (int)CurrentValue;
						if(uiCalValue <0)
							uiCalValue = -(uiCalValue);
						CurrentValue = uiCalValue;
					}
				}

				CString strCurrentValue = "";
				strCurrentValue.Format("%d",CurrentValue);
				theApp.GetCalibrateChannels()->SetItemText(m_Row,m_Col,strCurrentValue);			
				theApp.GetCalibrateChannels()->UpdateCalibrationXMLFile(m_Row);
			}
			else
				AfxMessageBox("Error in reading data from Wago",MB_SETFOREGROUND|MB_ICONERROR,0); 

			CCalibrateChannels::m_CalibrationData[m_Row].StartButtonClicked = false;
		}
		
	}

	CButton::OnLButtonUp(nFlags, point);
}
// CListButton message handlers

