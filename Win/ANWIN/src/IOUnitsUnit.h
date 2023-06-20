// ---------------------------------------------------------------------------

#ifndef IOUnitsUnitH
#define IOUnitsUnitH
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>

// ---------------------------------------------------------------------------
struct HeaderInfo {
	int WordKey;
	int Width;
};

// ---------------------------------------------------------------------------
class TIOUnitForm : public TForm {
__published: // IDE-managed Components

	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TPanel *Panel1;
	TComboBox *ADCardComboBox;
	TStringGrid *StringGrid1;
	TTimer *Timer1;
	TTabSheet *TabSheet2;
	TPanel *Panel2;
	TComboBox *IOUnitComboBox;
	TStringGrid *StringGrid2;

	void __fastcall ADCardComboBoxSelect(TObject *Sender);
	void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol, int ARow,
		bool &CanSelect);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall IOUnitComboBoxSelect(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private: // User declarations

	int CurrentIOIndex;
	int CurrentHWIndex;
	PRogramObject *CurrentIOUnit;
	PRogramObject *CurrentHWUnit;
	vector<PRogramObjectBase*>DropdHWUnitList;
	vector<PRogramObjectBase*>DropdIOUnitList;

	void __fastcall InitSysWin(void);
	void __fastcall ClearList(TStringGrid *StringGrid);
	void __fastcall UpdateSysWin(void);
	void __fastcall UpdateSysWin2(void);
	void __fastcall SetListviewRow(int Row, int Ch, AnsiString NameStr,
		AnsiString LocStr, AnsiString TypeStr, AnsiString RawValStr,
		AnsiString ValStr, AnsiString GainStr, AnsiString OffsetStr,
		AnsiString EnableStr, AnsiString UnitStr);
	void __fastcall SetListviewRow(int Row, AnsiString CalVal,
		AnsiString CnvCalErr, AnsiString PromStat, AnsiString PCStat,
		AnsiString UsePCSetUp, AnsiString ADSns, AnsiString PCSns,
		AnsiString UseFromPc);
	void __fastcall SetListviewRow(int Row, int Ch, AnsiString NameStr,
		AnsiString LocStr, AnsiString TypeStr, AnsiString RawValStr,
		AnsiString ValStr, AnsiString GainStr, AnsiString OffsetStr,
		AnsiString EnableStr, AnsiString UnitStr,AnsiString FailCount1,AnsiString FailCount2);

public: // User declarations
	__fastcall TIOUnitForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TIOUnitForm *IOUnitForm;
// ---------------------------------------------------------------------------
#endif