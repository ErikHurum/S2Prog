// QtDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "QtDlg.h"
#include <math.h>

// CQtDlg 对话框

IMPLEMENT_DYNAMIC(CQtDlg, CDialog)

CQtDlg::CQtDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQtDlg::IDD, pParent)
	, R(0)
{

}

CQtDlg::~CQtDlg()
{
}

void CQtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_R, R);
}

void CQtDlg::GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 )
{
	const double PI = 3.1415926535897932384626434;

	hightArray.RemoveAll();
	valArray.RemoveAll();


	for (int i = 0; i < 33; i++)
	{
		hightArray.Add(0.0);
		valArray.Add(0.0);
	}

	hightArray[0] = valArray[0] = 0.0;	
	for(int i = 1; i < 33; i++)
	{
		hightArray[i] = i * 0.03125*P006;
		valArray[i] = 1/3.0*PI*pow(hightArray[i],2.0)*(3.0*R - hightArray[i]);
	}	
}


BEGIN_MESSAGE_MAP(CQtDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CQtDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CQtDlg 消息处理程序

void CQtDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (R*2 < P006)
	{
		WarnMessageBox(IDS_MAPPINGWARN1);
		return;
	}
	OnOK();
}
