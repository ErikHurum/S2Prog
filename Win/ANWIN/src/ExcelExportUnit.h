// ---------------------------------------------------------------------------

#ifndef ExcelExportUnitH
#define ExcelExportUnitH
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <OleServer.hpp>
#include <StdCtrls.hpp>
#include "ChildUnit.h"
#include "excel_xp_srvr.h"
#include "Excel_XP_srvr.h"
#include <Vcl.Mask.hpp>

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class TExcelExportForm : public TChildForm {
__published: // IDE-managed Components

	TButton *Button1;
	TTimer *Timer1;
	TLabeledEdit *FrequencyLabeledEdit;
	TButton *StopButton;
	TLabel *Label1;
	TLabel *CntLabel;
	TRadioGroup *UnitRadioGroup;
	TExcelApplication *ExcelApplication1;
	TExcelWorksheet *ExcelWorksheet1;
	TExcelWorkbook *ExcelWorkbook1;

	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FrequencyLabeledEditChange(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private: // User declarations

	vector<vector<vector<AnsiString> > >LogVector;
	vector<PRogramObjectBase*>ObjectVector;
	vector<int>ValueIdVector;
	vector<AnsiString>TimeStrVect;

public: // User declarations
	static set<TExcelExportForm*>MySet;

	__fastcall TExcelExportForm(TComponent* Owner);
	__fastcall ~TExcelExportForm(void);
	void __fastcall SetMiscVectors(vector<PRogramObjectBase*>ObjVector,
		vector<int>ValIdVector);
};

// ---------------------------------------------------------------------------
extern PACKAGE TExcelExportForm *ExcelExportForm;
// ---------------------------------------------------------------------------
#endif
