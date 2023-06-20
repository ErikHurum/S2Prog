#pragma once


// CListButton

class CListButton : public CButton
{
	DECLARE_DYNAMIC(CListButton)

public:
	CListButton(int p_Row,int p_Col);
	virtual ~CListButton();

private:
	int m_Row;
	int m_Col;
	bool m_bStartButtonClicked;

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


