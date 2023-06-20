// PvcsDialogCargoClose.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsDialogCargoClose.h"


// CPvcsDialogCargoClose dialog

IMPLEMENT_DYNAMIC(CPvcsDialogCargoClose, CDialog)
CPvcsDialogCargoClose::CPvcsDialogCargoClose(CWnd* pParent /*=NULL*/)
	: CDialog(CPvcsDialogCargoClose::IDD, pParent)
{
	Create( IDD_PVCSDIALOGCARGOCLOSE );
}

CPvcsDialogCargoClose::~CPvcsDialogCargoClose()
{
}

void CPvcsDialogCargoClose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPvcsDialogCargoClose, CDialog)
END_MESSAGE_MAP()


// CPvcsDialogCargoClose message handlers
