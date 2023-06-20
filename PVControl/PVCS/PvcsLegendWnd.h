#pragma once

#include "cominc.h"
#include "pvcsshipdata.h"

#include "pvcsobjectcontroldlg.h"

// Class Name	: CPvcsLegendWnd
// Description	: Window class for drawing Legend

class CPvcsLegendWnd : public CWnd
{
	DECLARE_DYNAMIC(CPvcsLegendWnd)

public:
	CPvcsLegendWnd();
	virtual ~CPvcsLegendWnd();

protected:
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()

private:
	int SplitScreens;
    int m_PrevScrollY;
	map <CString, COLORREF> m_mapLegend;
	HDC m_hMemDC;
    HGDIOBJ m_hMemDC_Scaled;

	CPvcsShipData::TankMap *m_ptrTankMap;

    typedef set<CPvcsControlObjectInfo>::iterator Info_it;

public:
	void Draw(void);
	void LoadLegendList(void);
	void SetTankMap(CPvcsShipData::TankMap *pTankMap);

};


