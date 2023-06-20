#include <vcl.h>
#include "TSNIncludes.h"
#pragma hdrstop
#include "PasswordUnit.h"
#include "ChildUnit.h"


//---------------------------------------------------------------------
#pragma resource "*.dfm"
TPasswordDlg *PasswordDlg;
//---------------------------------------------------------------------
__fastcall TPasswordDlg::TPasswordDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TPasswordDlg::OKBtnClick(TObject *Sender)
{
	int PINCode = PasswordEdit->Text.ToIntDef(0);
	int DefaultPinCode = PROSystemData::TXUSystemData->UserPinCode.ToIntDef(DEFAULT_PIN_CODE);
	if ( DefaultPinCode == PINCode){
		ModalResult = mrOk;
	}else{
		switch(PINCode){
		case SECRET_PIN_CODE :
			ModalResult = mrAll;
			break;
		case UNLOCK_PIN_CODE :
			ModalResult = mrOk;
			break;
		default:
			ModalResult = mrNo;
			break;
	  }
	}
}
//---------------------------------------------------------------------------





void __fastcall TPasswordDlg::FormActivate(TObject *Sender)
{
	PasswordEdit->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::PasswordEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key==13) {
		int PINCode = PasswordEdit->Text.ToIntDef(0);
		int DefaultPinCode = PROSystemData::TXUSystemData->UserPinCode.ToIntDef(DEFAULT_PIN_CODE);
		if ( DefaultPinCode == PINCode){
			OKBtnClick(Sender);
		}else{
			switch(PINCode){
			case SECRET_PIN_CODE :
			case UNLOCK_PIN_CODE :
				OKBtnClick(Sender);
				break;
			default:
				Label2->Caption = "Incorrect PWD!";
				break;
		  }
		}
	} else{
		Label2->Caption = "";
    }
}
//---------------------------------------------------------------------------


