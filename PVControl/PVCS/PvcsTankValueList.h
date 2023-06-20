#pragma once
#include "pvcsshipdata.h"


// CPvcsTankValueList

class CPvcsTankValueList : public CWnd
{
	DECLARE_DYNAMIC(CPvcsTankValueList)
	HDC m_hMemDC;
	int m_iTankID;
private:
	static const float iTitleWidth;
	static const float fHeadingHeight;

	CPvcsShipData::TankMap *m_ptrTankMap;
    void DrawHeading(void);

public:
	CPvcsTankValueList();
	virtual ~CPvcsTankValueList();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void Draw(CPvcsShipData::TankMap *pTankMap);

public:
	void SetTankID(const int& param_iTankID);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


