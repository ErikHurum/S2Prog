#pragma once

#include "resource.h"

// CPvcsDialogCargoClose dialog

class CPvcsDialogCargoClose : public CDialog
{
	DECLARE_DYNAMIC(CPvcsDialogCargoClose)

public:
	CPvcsDialogCargoClose(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPvcsDialogCargoClose();

// Dialog Data
	enum { IDD = IDD_PVCSDIALOGCARGOCLOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
