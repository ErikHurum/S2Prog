#include "ANWinInc.h"
#pragma hdrstop
#include "ConstantsANWIN.h"
#include "LCTrimListUnit.h"
// ---------------------------------------------------------------------
#pragma link "OKCancelUnit"
#pragma resource "*.dfm"
TTrimListSrcDlg *TrimListSrcDlg;

// ---------------------------------------------------------------------
__fastcall TTrimListSrcDlg::TTrimListSrcDlg(TComponent* AOwner)
	: TOKRightDlg(AOwner) {
}

// ---------------------------------------------------------------------
void __fastcall TTrimListSrcDlg::HelpBtnClick(TObject *Sender) {
	Application->HelpContext(HelpContext);
}

// ---------------------------------------------------------------------
void __fastcall TTrimListSrcDlg::OKBtnClick(TObject *Sender) {
	int Key = C_SD_LC_SOURCE_MAN;
	switch (TrimListSourceRadioGroup->ItemIndex) {
	case 0:
		Key = C_SD_LC_SOURCE_ONL;
		break;
	case 1:
		Key = C_SD_LC_SOURCE_MAN;
		break;
	case 2:
		Key = C_SD_LC_SOURCE;
		break;
	}
	AnsiString TrmLstSrc = KeyWord(Key);
	LibPutValue(SVT_LS_MANUAL_TRIM, LCShipData::LCShip, TrimLabeledEdit->Text);
	LibPutValue(SVT_LS_MANUAL_LIST_DEG, LCShipData::LCShip,
		ListLabeledEdit->Text);
	LibPutValue(SVT_LS_TRIM_LIST_SOURCE, LCShipData::LCShip, Key);
	SetLabelList();

	SetNewValues();

	Close();

}
// ---------------------------------------------------------------------------

void __fastcall TTrimListSrcDlg::FormCreate(TObject *Sender) {
	// TrimLabeledEdit->Tag = SVT_LS_MANUAL_TRIM;
	// ListLabeledEdit->Tag = SVT_LS_MANUAL_LIST_DEG;

	AnsiString Myunitstr;

	TrimLabeledEdit->Text = LibGetValue(SVT_LS_MANUAL_TRIM, LCShipData::LCShip,
		&Myunitstr);
	ListLabeledEdit->Text = LibGetValue(SVT_LS_MANUAL_LIST_DEG,
		LCShipData::LCShip, &Myunitstr);
	AnsiString TrmLstSrc = LibGetValue(SVT_LS_TRIM_LIST_SOURCE,
		LCShipData::LCShip, &Myunitstr);
	TrmLstSrc = TrmLstSrc.TrimRight();
	int TrimListKey = FindConfigKey(TrmLstSrc);
	switch (TrimListKey) {
	case C_SD_LC_SOURCE_ONL:
		TrimListSourceRadioGroup->ItemIndex = 0;
		break;
	case C_SD_LC_SOURCE_MAN:
		TrimListSourceRadioGroup->ItemIndex = 1;
		break;
	case C_SD_LC_SOURCE:
		TrimListSourceRadioGroup->ItemIndex = 2;
		break;
	}
	SetLabelList();
	UpdateValues();

}
// ---------------------------------------------------------------------------

void __fastcall TTrimListSrcDlg::CancelBtnClick(TObject *Sender) {
	Close();

}
// ---------------------------------------------------------------------------

void __fastcall TTrimListSrcDlg::FormClose(TObject *Sender,
	TCloseAction &Action) {
	Action = caFree;
}
// ---------------------------------------------------------------------------

void __fastcall TTrimListSrcDlg::SetLabelList(void) {
	Ballast->Tag = SVT_BALLAST_DNS;
	BallastUnit->Tag = SVT_BALLAST_DNS;
	HeavyFuel->Tag = SVT_HEAVY_FUEL_DNS;
	HeavyFuelUnit->Tag = SVT_HEAVY_FUEL_DNS;
	DieselOil->Tag = SVT_DIESEL_DNS;
	DieselOilUnit->Tag = SVT_DIESEL_DNS;
	Lubricant->Tag = SVT_LUBRICANTS_DNS;
	LubricantUnit->Tag = SVT_LUBRICANTS_DNS;
	FreshWater->Tag = SVT_FRESHWATER_DNS;
	FreshWaterUnit->Tag = SVT_FRESHWATER_DNS;
	SeaWater->Tag = SVT_SEAWATER_DNS;
	SeaWaterUnit->Tag = SVT_SEAWATER_DNS;

	EditList.push_back(Ballast);
	EditList.push_back(HeavyFuel);
	EditList.push_back(DieselOil);
	EditList.push_back(Lubricant);
	EditList.push_back(FreshWater);
	EditList.push_back(SeaWater);

	LabelUnitList.push_back(BallastUnit);
	LabelUnitList.push_back(HeavyFuelUnit);
	LabelUnitList.push_back(DieselOilUnit);
	LabelUnitList.push_back(LubricantUnit);
	LabelUnitList.push_back(FreshWaterUnit);
	LabelUnitList.push_back(SeaWaterUnit);
}
// ---------------------------------------------------------------------------

void __fastcall TTrimListSrcDlg::UpdateValues(void) {
	for (unsigned k = 0; k < EditList.size(); k++) {
		AnsiString TempValue, UnitStr;
		TempValue = LibGetValue(EditList[k]->Tag, PROSystemData::TXUSystemData,
			&UnitStr);
		if (EditList[k]->Text != TempValue) {
			EditList[k]->Text = TempValue;
		}
		if (k < LabelUnitList.size() && LabelUnitList[k]) {
			if (LabelUnitList[k]->Caption != UnitStr) {
				LabelUnitList[k]->Caption = UnitStr;
			}
		}
	}
}
// --------------------------------------------------------------------------

void __fastcall TTrimListSrcDlg::SetNewValues(void) {
	for (unsigned k = 0; k < EditList.size(); k++) {
		AnsiString TempValue = EditList[k]->Text;
		LibPutValue(EditList[k]->Tag, PROSystemData::TXUSystemData, TempValue);
	}
}
