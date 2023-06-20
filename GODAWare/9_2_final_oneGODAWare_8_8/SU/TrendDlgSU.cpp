// TrendDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "TrendDlgSU.h"


// CTrendDlgSU

IMPLEMENT_DYNAMIC(CTrendDlgSU, CCustomDialogEx)

CTrendDlgSU::CTrendDlgSU()
{

}

CTrendDlgSU::~CTrendDlgSU()
{
}


BEGIN_MESSAGE_MAP(CTrendDlgSU, CCustomDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CTrendDlgSU::OnBnClickedBtnLoad)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CTrendDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()



// CTrendDlgSU 消息处理程序



void CTrendDlgSU::OnBnClickedBtnLoad()
{
	if (!theApp.m_pClient->IsOnline())
	{
		return;
	}
	
	CProgress progress;

	int pn = m_comboPointNumber.GetCurSel()+1;

	CArray<BYTE> byteArray;
	if (!(theApp.m_pClient->LoadData(0x930, byteArray, pn)))
	{
		return;
	}

	INT16 currentPtr;
	if (!(theApp.m_pClient->LoadData(0x931, currentPtr, pn)))
	{
		return;
	}

	float lowPercent, low, highPercent, high;

	while(!(theApp.m_pClient->LoadData(0x110, lowPercent, pn)));
	while(!(theApp.m_pClient->LoadData(0x111, low, pn)));
	while(!(theApp.m_pClient->LoadData(0x112, highPercent, pn)));
	while(!(theApp.m_pClient->LoadData(0x113, high, pn)));


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

void CTrendDlgSU::OnSize(UINT nType, int cx, int cy)
{
	CCustomDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindow(m_curveDraw.GetSafeHwnd()))
	{
		m_curveDraw.SetWindowPos(NULL, 0, 20, cx - 20, cy - 40, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CTrendDlgSU::DoDataExchange(CDataExchange* pDX)
{


	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CURVE, m_curveDraw);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

BOOL CTrendDlgSU::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_comboPointNumber.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTrendDlgSU::OnCbnSelchangeComboPointnumber()
{
	// TODO: 在此添加控件通知处理程序代码
}
