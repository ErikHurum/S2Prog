#include <vcl.h>
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <Winapi.GDIPAPI.hpp>
#include <Winapi.GDIPOBJ.hpp>
#include "ANWinInc.h"
#include <Clipbrd.hpp>
#pragma hdrstop
#include <Dialogs.hpp>
#include "TankObjectUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma resource "*.dfm"
TTankObjectForm *TankObjectForm;

// ---------------------------------------------------------------------------
__fastcall TTankObjectForm::TTankObjectForm(TComponent* Owner)
	: TChildForm(Owner) {
	CurrentTankPtr = NULL;
}
// ---------------------------------------------------------------------------

void __fastcall TTankObjectForm::Timer1Timer(TObject *Sender) {
	// VolumeProgressBar->Progress = (int)(100*OnlineTank::Table[ValueKey]->VolumePercent[COND_ONLINE]);
	if (CurrentTankPtr) {
		UpdateValues();
		UpdateGraph();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTankObjectForm::UpdateValues(void) {
	AnsiString tempValue;
	AnsiString unitstr;
	if (CurrentTankPtr) {
		if (CurrentTankPtr->Type == C_PRO_CARGO) {
			// Ullage
			tempValue = LibGetValue(SVT_ULLAGE, CurrentTankPtr, &unitstr);
			UValueLabel->Caption = tempValue;
			UUnitLabel->Caption = unitstr;
		}
		else {
			// Level
			tempValue = LibGetValue(SVT_SOUNDING, CurrentTankPtr, &unitstr);
			UValueLabel->Caption = tempValue;
			UUnitLabel->Caption = unitstr;
		}
		// Volume%
		tempValue = LibGetValue(SVT_VOLPERCENT, CurrentTankPtr, &unitstr);
		VolumeLabel->Caption = tempValue;
		// Weight
		tempValue = LibGetValue(SVT_WEIGHT, CurrentTankPtr, &unitstr);
		WValueLabel->Caption = tempValue;
		WUnitLabel->Caption = unitstr;
		// Volume
		tempValue = LibGetValue(SVT_VOLUME, CurrentTankPtr, &unitstr);
		VValueLabel->Caption = tempValue;
		VUnitLabel->Caption = unitstr;
		// Temp
		tempValue = LibGetValue(SVT_TEMP, CurrentTankPtr, &unitstr);
		TValueLabel->Caption = tempValue;
		TUnitLabel->Caption = unitstr;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTankObjectForm::UpdateGraph(void) {
	Series1->Clear();
	Series2->Clear();
	Series3->Clear();
	Series4->Clear();
	Series5->Clear();
	Series6->Clear();
	Series7->Clear();
	// float Xvalue = 0;
	float Yvalue = 0;
	AnsiString XLabels;
	if (CurrentTankPtr) {
		AnsiString tempValue;
		AnsiString unitstr;
		int DecPnt, UnitId;
		CurrentTankPtr->GetValue(SVT_VOLPERCENT, 0, Yvalue, DecPnt, UnitId);
		Series1->AddXY(0, Yvalue, CurrentTankPtr->Name, (TColor)clTeeColor);
		Series1->AddXY(3, Yvalue, CurrentTankPtr->Name, (TColor)clTeeColor);

		// For alarm marks on Right axis
		AnsiString OEnablet = LibGetValue(SVT_HIHI_LEVEL_ENABLE, CurrentTankPtr);
		AnsiString HEnablet = LibGetValue(SVT_HI_LEVEL_ENABLE, CurrentTankPtr);
		AnsiString LEnablet = LibGetValue(SVT_LO_LEVEL_ENABLE, CurrentTankPtr);
		tempValue = LibGetValue(SVT_HIHI_VOLPCNT_LIM, CurrentTankPtr);
		float OYvalue;
		ConvertToFloat(&OYvalue, tempValue);
		tempValue = LibGetValue(SVT_HI_LEVEL_LIMIT, CurrentTankPtr);
		float HYvalue;
		ConvertToFloat(&HYvalue, tempValue);
		tempValue = LibGetValue(SVT_LO_LEVEL_LIMIT, CurrentTankPtr);
		float LYvalue;
		ConvertToFloat(&LYvalue, tempValue);
		if ((OEnablet == "1") && (HEnablet == "1") && ((OYvalue - HYvalue) < 6))
		{
			AnsiString XLabels5 = (AnsiString)" O" + OYvalue;
			Series5->AddXY(0, OYvalue, "", (TColor)clTeeColor);
			Series5->AddXY(1, OYvalue, XLabels5, (TColor)clTeeColor);

			Series2->AddXY(0, OYvalue, "", (TColor)clTeeColor);
			Series2->AddXY(3, OYvalue, "", (TColor)clTeeColor);

			AnsiString XLabels6 = (AnsiString)"         H" + HYvalue + "%";
			Series6->AddXY(0, HYvalue, "", (TColor)clTeeColor);
			Series6->AddXY(1, HYvalue, "", (TColor)clTeeColor);
			Series6->AddXY(2, HYvalue, XLabels6, (TColor)clTeeColor);

			Series3->AddXY(0, HYvalue, "", (TColor)clTeeColor);
			Series3->AddXY(3, HYvalue, "", (TColor)clTeeColor);
		}
		else {
			if (OEnablet == "1") {
				AnsiString XLabels5 = (AnsiString)"Overfill " + OYvalue + "%";
				Series5->AddXY(0, OYvalue, "", (TColor)clTeeColor);
				Series5->AddXY(1, OYvalue, XLabels5, (TColor)clTeeColor);

				Series2->AddXY(0, OYvalue, "", (TColor)clTeeColor);
				Series2->AddXY(3, OYvalue, "", (TColor)clTeeColor);
			}
			if (HEnablet == "1") {
				AnsiString XLabels6 = (AnsiString)" High " + HYvalue + "%";
				Series6->AddXY(0, HYvalue, "", (TColor)clTeeColor);
				Series6->AddXY(1, HYvalue, "", (TColor)clTeeColor);
				Series6->AddXY(2, HYvalue, XLabels6, (TColor)clTeeColor);

				Series3->AddXY(0, HYvalue, "", (TColor)clTeeColor);
				Series3->AddXY(3, HYvalue, "", (TColor)clTeeColor);
			}
		}
		if (LEnablet == "1") {
			AnsiString XLabels7 = (AnsiString)" Low " + LYvalue + "%";
			Series7->AddXY(0, LYvalue, "", (TColor)clTeeColor);
			Series7->AddXY(1, LYvalue, "", (TColor)clTeeColor);
			Series7->AddXY(2, LYvalue, "", (TColor)clTeeColor);
			Series7->AddXY(3, LYvalue, XLabels7, (TColor)clTeeColor);

			Series4->AddXY(0, LYvalue, "", (TColor)clTeeColor);
			Series4->AddXY(3, LYvalue, "", (TColor)clTeeColor);
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTankObjectForm::FormClose(TObject *Sender,
	TCloseAction &Action) {
	Action = caFree;
}

// ---------------------------------------------------------------------------
void __fastcall TTankObjectForm::SetObjectPtr(PROXRefObject* TankPtr) {
	TChildForm::SetObjectPtr(TankPtr);
	if (CurrentTankPtr) {

		TankNameLabel->Caption = CurrentTankPtr->Name;
		if (CurrentTankPtr->Type == C_PRO_CARGO) {
			if (((PROTank*)CurrentTankPtr)->UTIUllageAvailable()) {
				ULabel->Caption = "UTI Ull";
			}
			else {
				ULabel->Caption = "Ullage";
			}
		}
		else {
			ULabel->Caption = "Snding";
		}
	}
}

