// ---------------------------------------------------------------------
#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "NewSolidsUnit.h"
// ---------------------------------------------------------------------
#pragma resource "*.dfm"
TNewSolidDlg *NewSolidDlg;

// ---------------------------------------------------------------------
__fastcall TNewSolidDlg::TNewSolidDlg(TComponent* AOwner) : TForm(AOwner) {
	SolidPtr = NULL;
}
// ---------------------------------------------------------------------

void __fastcall TNewSolidDlg::BitBtnOKClick(TObject *Sender) {
	if (SolidPtr) {
		LibPutValue(SVT_NAME, (PRogramObjectBase*)SolidPtr,
			NameLabeledEdit->Text);
		SolidPtr = NULL;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TNewSolidDlg::SetPointer(LCVariableSolidData *SPtr) {
	if (SPtr) {
		int Status;
		SolidPtr = SPtr;
		NameLabeledEdit->Text = LibGetValue(SVT_NAME, (PRogramObjectBase*)SPtr,
			&Status);
	}
}

void __fastcall TNewSolidDlg::BitBtnCancelClick(TObject *Sender) {
	SolidPtr = NULL;
}
// ---------------------------------------------------------------------------
