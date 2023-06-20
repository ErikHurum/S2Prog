#pragma once

namespace WAGOControlDlg
{
	class CWAGOControlDialog
	{
		CWAGOControlDialog(void);
	public:
		~CWAGOControlDialog(void);

		friend CWAGOControlDialog& ControlDlg();
	};

	CWAGOControlDialog& ControlDlg()
	{
		static CWAGOControlDialog dlgControl;
		return dlgControl;
	}
}