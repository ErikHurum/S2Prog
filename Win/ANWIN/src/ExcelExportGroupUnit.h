// ---------------------------------------------------------------------------

#ifndef ExcelExportGroupUnitH
#define ExcelExportGroupUnitH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ChildUnit.h"
#include <ExtCtrls.hpp>
#include "Excel_XP_srvr.h"
#include <OleServer.hpp>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

// ---------------------------------------------------------------------------
class TExcelExportGroupForm : public TChildForm {
__published: // IDE-managed Components

	TExcelApplication *ExcelApplication1;
	TExcelWorksheet *ExcelWorksheet1;
	TExcelWorkbook *ExcelWorkbook1;
	TLabel *Label1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private: // User declarations
		public : // User declarations

	__fastcall TExcelExportGroupForm(TComponent* Owner);
	void __fastcall SetMiscVectors(vector<PRogramObjectBase*>CurrentTable,
		vector<int>CurrentValueTable);

};

// ---------------------------------------------------------------------------
extern PACKAGE TExcelExportGroupForm *ExcelExportGroupForm;
// ---------------------------------------------------------------------------
#endif
