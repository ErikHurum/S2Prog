#pragma once
#include "pvcsconfiguration.h"
#include "pvcsshipdata.h"
#include "pvcslegendwnd.h"

// Class Name	: CPvcsLegendView
// Description	: View pane for the Legend

class CPvcsLegendView : public CView
{
	DECLARE_DYNCREATE(CPvcsLegendView)

private:
	CPvcsLegendWnd m_wndLegend;
	CPvcsShipData::TankMap *m_ptrTankMap;

protected:
    int SplitScreens;
	CPvcsLegendView();           // protected constructor used by dynamic creation
	virtual ~CPvcsLegendView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	void SetTankMap(CPvcsShipData::TankMap *pTankMap);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


