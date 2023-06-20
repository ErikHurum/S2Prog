#include "stdafx.h"
#include "InputDlg.h"

CMap<int, int, CString, CString&> MessageMap;

void WarnMessageBox(unsigned id)
{
	AfxMessageBox(id, MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
}

int ConfirmMessageBox( unsigned id )
{
	return AfxMessageBox(id, MB_OKCANCEL | MB_ICONWARNING | MB_SYSTEMMODAL);
}

bool GetNumMessageBox( unsigned id, double& result)
{
	CInputDlg dlg;
	CString str;
	BOOL bNameValid = str.LoadString(id);
	ASSERT(bNameValid);
	dlg.SetLabel(str);
	if (dlg.DoModal() == IDOK)
	{
		result = dlg.GetDouble();
		return true;
	}
	else
	{
		return false;
	}
}

bool GetNumMessageBox( unsigned id, double low, double high, double& result )
{
	CInputDlg dlg(low, high);
	CString str;
	BOOL bNameValid = str.LoadString(id);
	ASSERT(bNameValid);
	dlg.SetLabel(str);
	if (dlg.DoModal() == IDOK)
	{
		result =  dlg.GetDouble();
		return true;
	}
	else
	{
		return false;
	}
}

bool GetNumMessageBox( unsigned id, int& result )
{
	double tempResult;
	if (GetNumMessageBox( id, tempResult))
	{
		result = (int)tempResult;
		return true;
	}
	else
	{
		return false;
	}
}

bool GetNumMessageBox( unsigned id, int low, int high, int& result )
{
	double tempResult;
	if (GetNumMessageBox( id, low, high, tempResult))
	{
		result = (int)tempResult;
		return true;
	}
	else
	{
		return false;
	}
}

bool GetStrMessageBox( unsigned id, CString& result )
{
	CInputDlg dlg;
	CString str;
	BOOL bNameValid = str.LoadString(id);
	ASSERT(bNameValid);
	dlg.SetLabel(str);
	if (dlg.DoModal() == IDOK)
	{
		result = dlg.GetString();
		return true;
	}
	else
	{
		return false;
	}
}

void InfoMessageBox( unsigned id )
{
	AfxMessageBox(id, MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);

}

void SaveInfoMessageBox( unsigned dataId, bool saveOK )
{
	CString str, dataStr;
	BOOL bNameValid;

	if (!MessageMap.Lookup(dataId, dataStr))
	{
		dataStr.Format(_T("Î´ÖªÊý¾Ý 0x%x"), dataId);
	}
	if (saveOK)
	{
		bNameValid = str.LoadString(IDS_SAVEOK);

		ASSERT(bNameValid);

		CString message;
		message.Format(_T("%s %s"), dataStr, str);

		AfxMessageBox(message, MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
	}
	else
	{
		bNameValid = str.LoadString(IDS_SAVEFAIL);

		ASSERT(bNameValid);

		CString message;
		message.Format(_T("%s %s"), dataStr, str);

		AfxMessageBox(message, MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
	}

}

void InitMessage()
{
//#include "Params.txt"
#include "ParamsEN.txt"

}

