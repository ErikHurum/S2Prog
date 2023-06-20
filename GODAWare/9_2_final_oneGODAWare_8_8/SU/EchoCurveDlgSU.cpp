// EchoCurveDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "EchoCurveDlgSU.h"


// CEchoCurveDlgSU

IMPLEMENT_DYNAMIC(CEchoCurveDlgSU, CCustomDialogEx)

CEchoCurveDlgSU::CEchoCurveDlgSU()
{

}

CEchoCurveDlgSU::~CEchoCurveDlgSU()
{
}


BEGIN_MESSAGE_MAP(CEchoCurveDlgSU, CCustomDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CEchoCurveDlgSU::OnBnClickedBtnLoad)
	ON_WM_SIZE()
	//	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CEchoCurveDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()



// CEchoCurveDlgSU 消息处理程序



void CEchoCurveDlgSU::DoDataExchange(CDataExchange* pDX)
{


	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ECHOCURVE, m_echoCurve);
	DDX_Control(pDX, IDC_CHECK_ENVELOP, m_envelop);
	DDX_Control(pDX, IDC_CHECK_FALSEECHO, m_falseEcho);
	DDX_Control(pDX, IDC_CURVE, m_curveDraw);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

void CEchoCurveDlgSU::OnBnClickedBtnLoad()
{
	if (!m_echoCurve.GetCheck() && !m_envelop.GetCheck() && !m_falseEcho.GetCheck())
		return;

	if (!theApp.m_pClient->IsOnline())
	{
		return;
	}

	CProgress progress;

	int pn = m_comboPointNumber.GetCurSel()+1;


	float region = 10;
	theApp.m_pClient->LoadData(0x111, region, pn);


	m_curveDraw.SetUnit(CString("(m)"), CString("(dB)"));
	m_curveDraw.SetRange(0, region, 0 , 120);

	m_curveDraw.EchoCurveVisable(false);
	m_curveDraw.FalseEchoCurveVisable(false);
	m_curveDraw.WarpCurveVisable(false);

	double xScale = 1;



	if (m_echoCurve.GetCheck())
	{
		CArray<BYTE> byteArray;
		theApp.m_pClient->LoadData(0x991, byteArray, pn);

		UncompressData(byteArray, m_echoCurveVec, xScale, region);

		float arrow, sanjiao;
		theApp.m_pClient->LoadData(0x998, arrow, pn);
		theApp.m_pClient->LoadData(0x990, sanjiao, pn);



		m_curveDraw.SetEchoCurveValue(m_echoCurveVec);
		m_curveDraw.EchoCurveVisable(true);


		m_curveDraw.DrawArrow(arrow);
		m_curveDraw.DrawSanjiao(sanjiao);
		m_curveDraw.SetRange(0, region, 0 , 60);
		m_curveDraw.NBSet();
		m_curveDraw.RedrawWindow();

	}

	if (m_envelop.GetCheck())
	{
		CArray<BYTE> byteArray;
		theApp.m_pClient->LoadData(0x993, byteArray, pn);
		UncompressData(byteArray, m_envelopVec, xScale, region);
		m_curveDraw.SetWarpCurveValue(m_envelopVec);
		m_curveDraw.WarpCurveVisable(true);
		m_curveDraw.SetRange(0, region, 0 , 60);
		m_curveDraw.NBSet();
		m_curveDraw.RedrawWindow();
	}

	if (m_falseEcho.GetCheck())
	{
		CArray<BYTE> byteArray;
		theApp.m_pClient->LoadData(0x992, byteArray, pn);
		UncompressData(byteArray, m_falseEchoVec, xScale, region);
		m_curveDraw.SetFalseEchoCurveValue(m_falseEchoVec);
		m_curveDraw.FalseEchoCurveVisable(true);
		m_curveDraw.SetRange(0, region, 0 , 60);
		m_curveDraw.NBSet();
		m_curveDraw.RedrawWindow();
	}
}

BOOL CEchoCurveDlgSU::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();


	m_echoCurve.SetCheck(1);
	m_comboPointNumber.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CEchoCurveDlgSU::UncompressData( const CArray<BYTE>& byteArray , vector<curvevalue>& curveValueVec, double xScale, double maxXvalue)
{
	curveValueVec.clear();

	double y = 0;

	if (byteArray.GetSize() < 5320)
	{
		return;
	}


	for(int i = 0; i < 2324; i+=8)//14
	{
		int tempY = int(((byteArray[i+1] << 8) | byteArray[i]) & 0xfff);
		if (tempY == 0)
		{
			goto finished;
		}
		y = double(tempY) / 2047 * 120;

		curvevalue cv;
		cv.second = y; 
		curveValueVec.push_back(cv);

	}
	for(int i = 2324; i < 4648; i+=4)
	{
		int tempY = int(((byteArray[i+1] << 8) | byteArray[i]) & 0xfff);
		if (tempY == 0)
		{
			goto finished;
		}
		y = double(tempY) / 2047 * 120;

		curvevalue cv;
		cv.second = y; 
		curveValueVec.push_back(cv);

	}
	for(int i = 4648; i < 5820; i+=2)
	{
		int tempY = int(((byteArray[i+1] << 8) | byteArray[i]) & 0xfff);
		if (tempY == 0)
		{
			goto finished;
		}
		y = double(tempY) / 2047 * 120;

		curvevalue cv;
		cv.second = y; 
		curveValueVec.push_back(cv);

	}

finished:
	xScale = maxXvalue * 1.1 / curveValueVec.size();

	for (size_t i = 0; i < curveValueVec.size(); i++)
	{
		curveValueVec[i].first = xScale * i;
	}
}
void CEchoCurveDlgSU::OnSize(UINT nType, int cx, int cy)
{
	CCustomDialogEx::OnSize(nType, cx, cy);

	if (IsWindow(m_curveDraw.GetSafeHwnd()))
	{
		m_curveDraw.SetWindowPos(NULL, 0, 20, cx - 20, cy - 40, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
	Invalidate();

}

//int CEchoCurveDlgSU::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CCustomDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//	return 0;
//}

void CEchoCurveDlgSU::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码

	//m_curveDraw.RedrawWindow();
	// 不为绘图消息调用 CCustomDialogEx::OnPaint()
}

void CEchoCurveDlgSU::OnCbnSelchangeComboPointnumber()
{
	//theApp.m_pClient->SetDeviceNum(m_comboPointNumber.GetCurSel());
}
