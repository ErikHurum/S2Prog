//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ErrorMessageUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TErrrorWarningForm *ErrrorWarningForm;
//---------------------------------------------------------------------------
__fastcall TErrrorWarningForm::TErrrorWarningForm(TComponent* Owner)
	: : TChildForm(Owner)
{
}
// ---------------------------------------------------------------------------
__fastcall TGroupTable::TGroupTable(TComponent* Owner,
									vector<PRogramObjectBase*>ObjVector) : TChildForm(Owner, ObjVector) {
	TankTableAll = ObjVector;
	ObjectVector = ObjVector;
	InitForm();
}

//---------------------------------------------------------------------------
void __fastcall TErrrorWarningForm::InitForm(TObject *Sender)
{
	PRogramObject *PRoPtr = (PRogramObject*)CurrentTable[ARow - 2];
	AnsiString Str = LibGetValue(SVT_PRO_STATUS, PRoPtr);
	if ( Str == "A" ) {
		StringGrid->Hint = "ALARM(S):" + CrStr + PRoPtr->GetAlarms();
		StringGrid->ShowHint = true;
	} else if ( Str == "E" ) {
		StringGrid->Hint = "HARDWARE ERROR(S):" + CrStr + PRoPtr->GetHWAlarms();
		StringGrid->ShowHint = true;
	} else if ( Str == "W" ) {
		AnsiString AlarmWarnings = PRoPtr->GetWarnings();
		StringGrid->Hint = "WARNINGS:" + CrStr + PRoPtr->GetWarnings();
		StringGrid->ShowHint = true;
	} else {
		// StringGrid->ShowHint = false;
	}
}