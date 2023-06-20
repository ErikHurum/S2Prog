// OperationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "OperationDlg.h"

// COperationDlg

IMPLEMENT_DYNAMIC(COperationDlg, CCustomDialogEx)

COperationDlg::COperationDlg()
{

}

COperationDlg::~COperationDlg()
{
}


BEGIN_MESSAGE_MAP(COperationDlg, CCustomDialogEx)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



// COperationDlg 消息处理程序
void COperationDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CCustomDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		LoadData();
	}

}

BOOL COperationDlg::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();

	CWnd * pTitle = GetDlgItem(IDC_TITLE);

	if (pTitle != 0)
	{
		VERIFY(font.CreateFont(
			20,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("Arial"))); 
		pTitle->SetFont(&font);
	}

	CComboBox * pPointNumber = dynamic_cast<CComboBox*>(GetDlgItem(IDC_COMBO_POINTNUMBER));
	if (pPointNumber != 0)
	{
		if(pPointNumber->GetCount() > 1)
			pPointNumber->SetCurSel(1);
		//else
		//	pPointNumber->SetCurSel(0);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void COperationDlg::OnOK()
{
	SaveData();

	//CCustomDialogEx::OnOK();
}

void COperationDlg::OnCancel()
{
	LoadData();

	//CCustomDialogEx::OnCancel();
}
