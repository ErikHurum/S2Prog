// TrendDlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "TrendDlgTU.h"


// CTrendDlgTU

IMPLEMENT_DYNAMIC(CTrendDlgTU, CCustomDialogEx)

CTrendDlgTU::CTrendDlgTU()
{

}

CTrendDlgTU::~CTrendDlgTU()
{
}


BEGIN_MESSAGE_MAP(CTrendDlgTU, CCustomDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CTrendDlgTU::OnBnClickedBtnLoad)
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CTrendDlgTU 消息处理程序



void CTrendDlgTU::OnBnClickedBtnLoad()
{
	if (!theApp.m_pClient->IsOnline())
	{
		return;
	}
	
	CProgress progress;
	CArray<BYTE> byteArray;
	theApp.m_pClient->LoadData(0x930, byteArray);

	INT16 currentPtr;
	theApp.m_pClient->LoadData(0x931, currentPtr);

	float lowPercent, low, highPercent, high;

	theApp.m_pClient->LoadData(0x110, lowPercent);
	theApp.m_pClient->LoadData(0x111, low);
	theApp.m_pClient->LoadData(0x112, highPercent);
	theApp.m_pClient->LoadData(0x113, high);


	double hightRatio = (low - high) / (highPercent - lowPercent);


	vector<curvevalue> curveValueVec;

	if (byteArray.GetSize() < 4320)
	{
		for (int i = 0; i < byteArray.GetSize(); i +=2)
		{
			curvevalue c;
			c.first = i/2;
			INT16 vol = *(INT16*)(&byteArray[i]);
			c.second = double(vol) / 2048 * hightRatio;
			TRACE("%d\n", vol);
			curveValueVec.push_back(c);
		}
	} 
	else if (byteArray.GetSize() == 4320)
	{
		for (int i = currentPtr * 2; i < 4320; i+=2)
		{
			curvevalue c;
			c.first = i/2 - currentPtr;
			INT16 vol = *(INT16*)(&byteArray[i]);
			c.second = double(vol) / 2048 * hightRatio;
			curveValueVec.push_back(c);
		}
		for (int i = 0; i < currentPtr * 2; i+=2)
		{
			curvevalue c;
			c.first = i/2 + 4320/2 - currentPtr;
			INT16 vol = *(INT16*)(&byteArray[i]);
			c.second = double(vol) / 2048 * hightRatio;
			curveValueVec.push_back(c);
		}
	}
	else
	{
		ASSERT(FALSE);
	}

	m_curveDraw.SetXAxisTime(true);	// added 20100309
	m_curveDraw.SetRange(0, curveValueVec.back().first, 0 , hightRatio);
	m_curveDraw.SetEchoCurveValue(curveValueVec);
	m_curveDraw.EchoCurveVisable(true);

	m_curveDraw.RedrawWindow();
}

void CTrendDlgTU::OnSize(UINT nType, int cx, int cy)
{
	CCustomDialogEx::OnSize(nType, cx, cy);

	if (IsWindow(m_curveDraw.GetSafeHwnd()))
	{
		m_curveDraw.SetWindowPos(NULL, 0, 20, cx - 20, cy - 40, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CTrendDlgTU::DoDataExchange(CDataExchange* pDX)
{


	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CURVE, m_curveDraw);
}
