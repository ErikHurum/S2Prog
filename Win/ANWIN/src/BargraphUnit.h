// ---------------------------------------------------------------------------

#ifndef BargraphUnitH
#define BargraphUnitH
#include "ChildUnit.h"
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
class TBarGraphForm : public TChildForm {
__published: // IDE-managed Components

	TPanel *Panel1;
	TTimer *Timer1;
	TChart *Chart1;
	TBarSeries *Series1;
	TBarSeries *Series2;
	TToolBar *ToolBar1;
	TLabel *Label5;
	TButton *SelectValueButton;
	TLabel *Label1;
	TBitBtn *FirstBitBtn;
	TLabel *Label3;
	TBitBtn *PreviousBitBtn;
	TLabel *Label2;
	TBitBtn *NextBitBtn;
	TLabel *Label4;
	TBitBtn *LastBitBtn;

	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall NextBitBtnClick(TObject *Sender);
	void __fastcall PreviousBitBtnClick(TObject *Sender);
	void __fastcall LastBitBtnClick(TObject *Sender);
	void __fastcall FirstBitBtnClick(TObject *Sender);
	void __fastcall SelectValueButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Chart1AllowScroll(TChartAxis *Sender, double &AMin, double &AMax,
          bool &AllowScroll);

private: // User declarations

	int Type;
	float *TrendLog;

	void __fastcall PopupMenuValueTypeExecute(TObject *Sender);
	void __fastcall ReadRegistry(void);
	void __fastcall WriteRegistry(void);
protected:
	String RegNameKey;
	int ValueKey;
	AnsiString ValueName;
public: // User declarations
	__fastcall TBarGraphForm(TComponent* Owner);
	__fastcall TBarGraphForm(TComponent* Owner,
		vector<PRogramObjectBase*>ObjVector, bool FromTable = false);

	void __fastcall SetObjectTable(vector<PRogramObjectBase*>CurrTab);
	void __fastcall Init(void);

};

// ---------------------------------------------------------------------------
extern PACKAGE TBarGraphForm *BarGraphForm;
// ---------------------------------------------------------------------------
#endif
