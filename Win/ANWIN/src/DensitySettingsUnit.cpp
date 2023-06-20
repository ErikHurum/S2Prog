#include <vcl.h>
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#pragma hdrstop
#include "DensitySettingsUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma resource "*.dfm"

TDensitySettingDlg *DensitySettingDlg;

// ---------------------------------------------------------------------------
__fastcall TDensitySettingDlg::TDensitySettingDlg(TComponent* AOwner)
	: TForm(AOwner) {
}
// ---------------------------------------------------------------------------

void __fastcall TDensitySettingDlg::FormShow(TObject *Sender) {
	UpdateValues();
}
// ---------------------------------------------------------------------------

void TDensitySettingDlg::SetLabelList(void) {
    EditListEntries = 0;
    LabelUnitListEntries = 0;

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

    EditList[EditListEntries++] = Ballast;
	EditList[EditListEntries++] = HeavyFuel;
    EditList[EditListEntries++] = DieselOil;
    EditList[EditListEntries++] = Lubricant;
    EditList[EditListEntries++] = FreshWater;
    EditList[EditListEntries++] = SeaWater;

    LabelUnitList[LabelUnitListEntries++] = BallastUnit;
    LabelUnitList[LabelUnitListEntries++] = HeavyFuelUnit;
    LabelUnitList[LabelUnitListEntries++] = DieselOilUnit;
    LabelUnitList[LabelUnitListEntries++] = LubricantUnit;
    LabelUnitList[LabelUnitListEntries++] = FreshWaterUnit;
    LabelUnitList[LabelUnitListEntries++] = SeaWaterUnit;
}
// ---------------------------------------------------------------------------

void TDensitySettingDlg::UpdateValues(void) {
    if (PROSystemData::TXUSystemData) {
        for (int k = 0; k < EditListEntries; k++) {
            AnsiString TempValue, UnitStr;
            TempValue = LibGetValue(EditList[k]->Tag,
                PROSystemData::TXUSystemData, &UnitStr);
            if (EditList[k]->Text != TempValue) {
                EditList[k]->Text = TempValue;
            }
            if (k < LabelUnitListEntries && LabelUnitList[k]) {
                if (LabelUnitList[k]->Caption != UnitStr) {
                    LabelUnitList[k]->Caption = UnitStr;
                }
            }
        }
    }
}
// --------------------------------------------------------------------------

void TDensitySettingDlg::SetNewValues(void) {
    if (PROSystemData::TXUSystemData) {
        for (int k = 0; k < EditListEntries; k++) {
            AnsiString TempValue = EditList[k]->Text;
			LibPutValue(EditList[k]->Tag, PROSystemData::TXUSystemData, TempValue);
		}
    }
}
// --------------------------------------------------------------------------

void __fastcall TDensitySettingDlg::EditExit(TObject *Sender) {
    /* TEdit *EditPtr = (TEdit *)Sender;
     if( EditPtr->ReadOnly ){
     }else{
     String UserInput = EditPtr->Text;
     LibPutValue(EditPtr->Tag, PROSystemData::TXUSystemData, UserInput);
     } */
}
// ---------------------------------------------------------------------------

void __fastcall TDensitySettingDlg::EditKeyPress(TObject *Sender, char &Key) {
    /* TEdit *EditPtr = (TEdit *)Sender;
     String UserInput = EditPtr->Text;
     switch(Key){
     case VK_ESCAPE:
     break;
     case VK_RETURN:
     LibPutValue(EditPtr->Tag, PROSystemData::TXUSystemData, UserInput);
     break;
     default:
     break;
     } */
}
// ---------------------------------------------------------------------------

void __fastcall TDensitySettingDlg::FormClose(TObject *Sender,
    TCloseAction &Action) {
	Action = caFree;
}
// ---------------------------------------------------------------------------

void TDensitySettingDlg::ClearAllFields(void) {
    for (int k = 0; k < EditListEntries; k++) {
        String tempValue; // LibGetValue(EditPtr->Tag, CurrentCargoType);
        if (EditList[k]->Text != tempValue) {
            EditList[k]->Text = tempValue;
        }
    }
}
// ---------------------------------------------------------------------------

void __fastcall TDensitySettingDlg::SaveButtonClick(TObject *Sender) {
    SetNewValues();
}
// ---------------------------------------------------------------------------

void __fastcall TDensitySettingDlg::FormCreate(TObject *Sender)
{
	SetLabelList();
}
//---------------------------------------------------------------------------

