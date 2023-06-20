// ----------------------------------------------------------------------------
#ifndef LCTrimListUnitH
#define LCTrimListUnitH
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include "OKCancelUnit.h"

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
class TTrimListSrcDlg : public TOKRightDlg {
__published:
	TButton *HelpBtn;
	TRadioGroup *TrimListSourceRadioGroup;
	TGroupBox *GroupBox1;
	TLabeledEdit *TrimLabeledEdit;
	TLabeledEdit *ListLabeledEdit;
	TGroupBox *GroupBox2;
	TLabel *BallastLable;
	TEdit *Ballast;
	TLabel *HeavyFuelLabel;
	TEdit *HeavyFuel;
	TLabel *HeavyFuelUnit;
	TLabel *BallastUnit;
	TLabel *DieselOilUnit;
	TEdit *DieselOil;
	TLabel *DieselOilLabel;
	TLabel *LubricantLabel;
	TLabel *FreshWaterLabel;
	TLabel *SeaWaterLabel;
	TEdit *FreshWater;
	TEdit *Lubricant;
	TEdit *SeaWater;
	TLabel *LubricantUnit;
	TLabel *FreshWaterUnit;
	TLabel *SeaWaterUnit;

	void __fastcall HelpBtnClick(TObject *Sender);
	void __fastcall OKBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:
	vector<TEdit*>EditList;
	vector<TLabel*>LabelUnitList;

	void __fastcall SetLabelList(void);
	void __fastcall UpdateValues(void);
	void __fastcall SetNewValues(void);

public:
	virtual __fastcall TTrimListSrcDlg(TComponent* AOwner);
};

// ----------------------------------------------------------------------------
extern PACKAGE TTrimListSrcDlg *TrimListSrcDlg;
// ----------------------------------------------------------------------------
#endif
