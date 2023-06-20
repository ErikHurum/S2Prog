//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <vector.h>
#include "CalculationUnit.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::EditLevelChange(TObject *Sender)
{
	TEdit *EditPtr = (TEdit*)Sender;
	if (!EditPtr->Text.IsEmpty()) {
		AnsiString tmpStr;
		double Level = EditPtr->Text.ToDouble();
		double LCF,TCF, LCG,TCG;
		CFTable.CalculateCG(Level,&LCG,&TCG);
		CFTable.CalcCF(Level,LCF,TCF);
		LabelLCG->Caption = tmpStr.sprintf("%6.3f",LCG);
		LabelTCG->Caption = tmpStr.sprintf("%6.3f",TCG);
		LabelLCF->Caption = tmpStr.sprintf("%6.3f",LCF);
		LabelTCF->Caption = tmpStr.sprintf("%6.3f",TCF);

	}


}
//---------------------------------------------------------------------------

