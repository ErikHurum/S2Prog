#pragma once
#include "dxflayout.h"
#include "pvcsconfiguration.h"

// CPvcsShipView view

class CPvcsShipView : public CView
{
	DECLARE_DYNCREATE(CPvcsShipView)

protected:
	CPvcsShipView();           // protected constructor used by dynamic creation
	virtual ~CPvcsShipView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	CDxfLayout m_dxfShipLayout;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


